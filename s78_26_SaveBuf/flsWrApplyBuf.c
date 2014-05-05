#define __flsWrApplyBuf_C__
/******************************************************************************
* @file    flsWrApplyBuf.c
* @author  yx
* @version V1.0
* @date    2013-07-23
* @brief   配合flsWrApplySave.c， 做buf[]. 
		IN: FlsWr_AlyBuf_NewApply();
		存实际数据，因为各item的长度相差很大，所以不按 定长存储。
* 
******************************************************************************/
#include  "flsWrApplyBuf.h"

#include  "strFlsAdrDef.h"
#include  "strFlsItmStruct.h" 
#include  "strFlsItmStrCacu.h"
#include  "bufCircle.h"
#include  "codeComm.h"

//#include "incFile.h"	
/*================= 常数 ============================================*/

/*================= 私有结构变量声明 ================================*/

/*================= 存储byte队列 实际数据 ================================*/
U8 vFlsAlyBuf[U_FlsAly_BufByte_MAX];
TBufCircle  vCircleFlsAlyBuf; //成组加

/*================= 分配的次数 ================================*/

TFlsAlySec_st  vFlsAlySec[U_FlsAly_SecNum_MAX];
TBufCircle     vCircleFlsAlySec; //一个一个

/*================= 读出 ================================*/


/*================= 私有函数声明 ====================================*/
void init_FlsApplyOneBuf(TFlsAlySec_st *pOne);

/*=================  ================================================*/
		
/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
void Init_FlsApplyBuf(void)
{
#if U_SYS_IdleBuf_setFF == 1
U32 ii;
#endif //U_SYS_IdleBuf_setFF

	BufCircleIni(U_FlsAly_BufByte_MAX, &vCircleFlsAlyBuf);	
	BufCircleIni(U_FlsAly_SecNum_MAX, &vCircleFlsAlySec);	
	
#if U_SYS_IdleBuf_setFF == 1
	for(ii=0; ii<U_FlsAly_BufByte_MAX; ii++)
	{
		vFlsAlyBuf[ii] = ~0;
	}
		
	for(ii=0; ii<U_FlsAly_SecNum_MAX; ii++)
	{
		init_FlsApplyOneBuf(&vFlsAlySec[ii]);
	}
#endif //U_SYS_IdleBuf_setFF

}


void init_FlsApplyOneBuf(TFlsAlySec_st *pOne)
{
U8 byteMax = sizeof(TFlsAlySec_st);


	if(pOne == NULL)
	{
		return;
	}
	
	ClrRamIsFF((U8*)(pOne), byteMax); //全清FF
	
	
	// pOne->mFlsItem = ~0;
	// pOne->taskId = U_SYS_TASK_ID_Invalid;
	// pOne->flsId = ~0;
	// pOne->strFlsItmByte = ~0;
	// pOne->adrS = ~0;
	// pOne->adrE = ~0;
	
}

/******************************************************************************
* FUNC: // 申请空间, 把要写入的内容->buf
*   IN:  	(bSaveItemValid(mFlsItem))
		taskId < U_SYS_TASK_ID_MAX
		flsId
		pSrc ->  TFlsSysSet_un ...
*  OUT: U_SUCC
// U_SIGN_bHaveTested; 2013-07-011
******************************************************************************/
BOOL FlsWr_AlyBuf_NewApply(U8 mFlsItem, U8 taskId, 
									U8 flsId, U8 *pSrc)
{
U32 mSpaceByte; //buf[]剩余空间
TFlsAlySec_st *pOne;
U32 mStrByte;



	if(  (bFullBufCircle(&vCircleFlsAlySec)) 
	  || (!bSaveItemValid(mFlsItem))
	  )
	{
		return U_FAILED;
	}
	mStrByte = GetFlsItemBufBytes(mFlsItem);
	mSpaceByte = CircleSpaceBytes(&vCircleFlsAlyBuf);
	if(mStrByte >= mSpaceByte)
	{
		return U_FAILED;
	}
	if(bFullBufCircle(&vCircleFlsAlySec))
	{
		return U_FAILED;
	}
	
	pOne = &vFlsAlySec[vCircleFlsAlySec.in];
	pOne->mFlsItem = mFlsItem;
	pOne->taskId = taskId;
	pOne->flsId = flsId;
	pOne->strFlsItmByte = mStrByte;
	
	pOne->adrS = vCircleFlsAlyBuf.in;	
	CircleCopyByte(&vFlsAlyBuf[0], pSrc, mStrByte, &vCircleFlsAlyBuf); //copy字节
	BufCircle_In_Add(mStrByte, &vCircleFlsAlyBuf);	
	pOne->adrE = vCircleFlsAlyBuf.in;
	
	//succ add one
	BufCircle_InInc(&vCircleFlsAlySec);
	return U_SUCC;
}


/******************************************************************************
* FUNC: // 待写flash的任务，读出。
*   IN:
*  OUT: U_SUCC
		*pByteDest.. = 各结构体自身
// U_SIGN_bHaveTested; 2013-07-011
******************************************************************************/
BOOL FlsWr_AlyBuf_Read(U8 *pByteDest, 
							TFlsAlyOneHead_un *pRtnAlyHead)
{
TFlsAlySec_st *pOne;

	if(bEmptyBufCircle(&vCircleFlsAlySec))
	{
		return U_FAILED;
	}
	pOne = &vFlsAlySec[vCircleFlsAlySec.out];
	
	vCircleFlsAlyBuf.out = pOne->adrS;
	ByteCopyFromCircle(&vFlsAlyBuf[0], pByteDest, 
					  pOne->strFlsItmByte, 
					  &vCircleFlsAlyBuf);
	BufCircle_Out_Add(pOne->strFlsItmByte, &vCircleFlsAlyBuf);
	
	pRtnAlyHead->head.mFlsItem = pOne->mFlsItem;
	pRtnAlyHead->head.taskId = pOne->taskId;
	pRtnAlyHead->head.flsId = pOne->flsId;
	pRtnAlyHead->head.strFlsItemBytes = pOne->strFlsItmByte;
	
	//succ read
#if U_SYS_IdleBuf_setFF == 1
	init_FlsApplyOneBuf(pOne);
#endif //U_SYS_IdleBuf_setFF
	BufCircle_OutInc(&vCircleFlsAlySec);
	return U_SUCC;
}


/******************************************************************************
* FUNC: // 
*   IN:
*  OUT: 
******************************************************************************/

BOOL bFlsWr_AlyBuf_Empty(void)
{
	return bEmptyBufCircle(&vCircleFlsAlySec);
}

/******************************************************************************
* FUNC: // END
*   IN:
*  OUT: 
******************************************************************************/
