#define __flsWrApplyBuf_C__
/******************************************************************************
* @file    flsWrApplyBuf.c
* @author  yx
* @version V1.0
* @date    2013-07-23
* @brief   ���flsWrApplySave.c�� ��buf[]. 
		IN: FlsWr_AlyBuf_NewApply();
		��ʵ�����ݣ���Ϊ��item�ĳ������ܴ����Բ��� �����洢��
* 
******************************************************************************/
#include  "flsWrApplyBuf.h"

#include  "strFlsAdrDef.h"
#include  "strFlsItmStruct.h" 
#include  "strFlsItmStrCacu.h"
#include  "bufCircle.h"
#include  "codeComm.h"

//#include "incFile.h"	
/*================= ���� ============================================*/

/*================= ˽�нṹ�������� ================================*/

/*================= �洢byte���� ʵ������ ================================*/
U8 vFlsAlyBuf[U_FlsAly_BufByte_MAX];
TBufCircle  vCircleFlsAlyBuf; //�����

/*================= ����Ĵ��� ================================*/

TFlsAlySec_st  vFlsAlySec[U_FlsAly_SecNum_MAX];
TBufCircle     vCircleFlsAlySec; //һ��һ��

/*================= ���� ================================*/


/*================= ˽�к������� ====================================*/
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
	
	ClrRamIsFF((U8*)(pOne), byteMax); //ȫ��FF
	
	
	// pOne->mFlsItem = ~0;
	// pOne->taskId = U_SYS_TASK_ID_Invalid;
	// pOne->flsId = ~0;
	// pOne->strFlsItmByte = ~0;
	// pOne->adrS = ~0;
	// pOne->adrE = ~0;
	
}

/******************************************************************************
* FUNC: // ����ռ�, ��Ҫд�������->buf
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
U32 mSpaceByte; //buf[]ʣ��ռ�
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
	CircleCopyByte(&vFlsAlyBuf[0], pSrc, mStrByte, &vCircleFlsAlyBuf); //copy�ֽ�
	BufCircle_In_Add(mStrByte, &vCircleFlsAlyBuf);	
	pOne->adrE = vCircleFlsAlyBuf.in;
	
	//succ add one
	BufCircle_InInc(&vCircleFlsAlySec);
	return U_SUCC;
}


/******************************************************************************
* FUNC: // ��дflash�����񣬶�����
*   IN:
*  OUT: U_SUCC
		*pByteDest.. = ���ṹ������
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
