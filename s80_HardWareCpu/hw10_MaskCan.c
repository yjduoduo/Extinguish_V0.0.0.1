#define __hw10_MaskCan_C__
/******************************************************************************
* @file    hw10_MaskCan.c
* @author  yx
* @version V1.0
* @date    2013-08-21
* @brief   CAN代码屏蔽。 涉及应用层的can结构。
* 
******************************************************************************/
#include  "hw10_MaskCan.h"


//#include "incFile.h"

#include  "CanHd_Interface.h"  // can_id 
#include  "CanBufLib_ReDef.h"

// #include  "canFrame.h"
#include  "meBoard.h"   // GetBoardICanAddr

/*================= 常数 ============================================*/

/*******************************************************************/
/******************       CAN屏蔽    *********************/
/*******************************************************************/
typedef struct {
	uint16 iMb;
	uint32 idSetData;
	uint32 idMaskBits;
}TCanMaskSet;

const TCanMaskSet  cstICanMaskSet[] =
{
	{U_iCanRxMaskBuf_IapFile, 	U_iCanMaskData_IapFile_ID, 	U_iCanMaskBits_IapFile},
	{U_iCanRxMaskBuf_IapData, 	U_iCanMaskData_IapData_ID, 	U_iCanMaskBits_IapData},
	
	{U_iCanRxMaskBuf_Reset, 	U_iCanMaskData_Reset_ID, 	U_iCanMaskBits_Reset},
	{U_iCanRxMaskBuf_Alarm, 	U_iCanMaskData_Alarm_ID, 	U_iCanMaskBits_Alarm},

	{U_iCanRxMaskBuf_PtoP, 		U_iCanMaskData_PtoP_ID, 	U_iCanMaskBits_PtoP},
	{U_iCanRxMaskBuf_Broad, 	U_iCanMaskData_Broad_ID, 	U_iCanMaskBits_Broad},

	
};


const TCanMaskSet  cstECanMaskSet[] =
{
	{U_eCanRxMaskBuf_Reset, 	U_eCanMaskData_Reset_ID, 	U_eCanMaskBits_Reset},
	{U_eCanRxMaskBuf_Alarm, 	U_eCanMaskData_Alarm_ID, 	U_eCanMaskBits_Alarm},
	
};

#define U_ICAN_MASK_BUS_MAX  (sizeof(cstICanMaskSet) / sizeof(TCanMaskSet))
#define U_ECAN_MASK_BUS_MAX  (sizeof(cstECanMaskSet) / sizeof(TCanMaskSet))

/*================= 结构定义 ========================================*/

/*================= 私有结构变量声明 ================================*/

/*================= 公有函数声明 ====================================*/

/*================= 私有函数声明 ====================================*/

/*=================  ================================================*/
		
/******************************************************************************
* FUNC: //
*   IN: iMB 是 CAN硬件屏蔽机制屏蔽后的结果， emCanFrmRxMaskBuf  内。
*  OUT:  emCanFrmRxMaskBuf
******************************************************************************/

//CAN 接收：
BOOL JdgCanFrmMaskBuf(U8 canPeriId, U8 iMB, CAN_MSG_Type *pReciveCan,
							U8 *pRtnMaskBuf)
{
#ifdef U_USE_CAN_MASK  //
	*pRtnMaskBuf = iMB;
	return TRUE;
#else //
	return jdgFrmMask_FromFrm(canPeriId, pReciveCan, pRtnMaskBuf);
#endif //
	
}


/******************************************************************************
* FUNC: // 中断接收： 判断can分类： 根据帧内容.
Use In :  CAN中断
*   IN:
*  OUT:
******************************************************************************/
#ifdef U_USE_CAN_MASK  //CanDrv.h
#else //U_USE_CAN_MASK
//
BOOL jdgFrmMask_FromFrm(U8 canPeriId, CAN_MSG_Type *pReciveCan, 
					  U8 *pRtnMaskBuf)
{
U8 can_id;

	can_id = GetCanId_FromCanPeriId(canPeriId);
	switch(can_id)
	{
		case U_iCAN_ID:
			return jdgFrmMask_iCan_FromFrm(pReciveCan, pRtnMaskBuf);
			
			
		case U_eCAN_ID:
			return jdgFrmMask_eCan_FromFrm(pReciveCan, pRtnMaskBuf);
			
		default:
			break;
	}
	*pRtnMaskBuf = U_CanRxMaskBuf_Error;
	return FALSE;
}

#endif //U_USE_CAN_MASK


BOOL jdgFrmMask_eCan_FromFrm(CAN_MSG_Type *pReciveCan, U8 *pRtnMaskBuf)
{
	//U8 iMB;
	U32 mMaskBufMax;
	U32 mMaskBufii;
	U32 mRcvIdWord;
	
	mRcvIdWord = pReciveCan->id;
	*pRtnMaskBuf = ~0;
	
	mMaskBufMax = U_ECAN_MASK_BUS_MAX;	
	
	for(mMaskBufii=0; mMaskBufii<mMaskBufMax; mMaskBufii++)
	{
		if((mRcvIdWord & cstECanMaskSet[mMaskBufii].idMaskBits) == 
			 (cstECanMaskSet[mMaskBufii].idSetData & cstECanMaskSet[mMaskBufii].idMaskBits))
		{
			*pRtnMaskBuf = cstECanMaskSet[mMaskBufii].iMb;
			return TRUE;
		}
	}
	
	*pRtnMaskBuf = U_eCanRxMaskBuf_Error;
	return FALSE;
}


BOOL jdgFrmMask_iCan_FromFrm(CAN_MSG_Type *pReciveCan, U8 *pRtnMaskBuf)
{
	U8 iMB;
	U32 mMaskBufMax;
	U32 mMaskBufii;
	U32 mRcvIdWord;
	U32 mMaskBits;
	U8 mCanDestAdr;
	
	mRcvIdWord = pReciveCan->id;
	
	mMaskBufMax = U_ICAN_MASK_BUS_MAX;	
	
	for(mMaskBufii=0; mMaskBufii<mMaskBufMax; mMaskBufii++)
	{
		iMB = cstICanMaskSet[mMaskBufii].iMb;
		
		if((iMB == U_iCanRxMaskBuf_PtoP))
		{
			mMaskBits = U_iCanMaskBits_PtoP;
			
			if((mRcvIdWord & mMaskBits) == (cstICanMaskSet[mMaskBufii].idSetData & mMaskBits))
			{
				mCanDestAdr = ((mRcvIdWord & U_iCanMaskBits_DestAdr) 
								>> U_iCanMaskBitRightShift_DestAdr);
				if(mCanDestAdr == GetBoardICanAddr())
				{
					*pRtnMaskBuf = iMB;
					return TRUE;
				}
			}	
			
		}		
		else if((mRcvIdWord & cstICanMaskSet[mMaskBufii].idMaskBits) == 
			 (cstICanMaskSet[mMaskBufii].idSetData & cstICanMaskSet[mMaskBufii].idMaskBits)) //或者数据^再&maskBits==0
		{
			*pRtnMaskBuf = iMB;
			return TRUE;
		}
	}
	
	
	*pRtnMaskBuf = U_iCanRxMaskBuf_Error;
	return FALSE;
	
}



/******************************************************************************
* FUNC: // END
*   IN:
*  OUT: 
******************************************************************************/
