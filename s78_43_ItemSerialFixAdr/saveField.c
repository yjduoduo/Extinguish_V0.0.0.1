
#define __saveField_C__
/******************************************************************************
* @file    saveField.c
* @author  yx
* @version V1.0
* @date    2013-01-04
* @brief   
* 
******************************************************************************/
#include  "saveField.h"

#include  "saveItem_incIn.h"
#include  "saveDisable.h"


//#include "incFile.h"	

/*================= 常数 ============================================*/

/*================= 结构定义 ========================================*/

/*================= 私有结构变量声明 ================================*/

/*================= 公有函数声明 ====================================*/

/*================= 私有函数声明 ====================================*/

/*=================  ================================================*/
		
/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
// 检查field的定义 与 disable buf 是否对应：
BOOL bCorrespDisable_FieldAndBuf(void)
{
U8 mLoop;
U8 mAddr;
TDev_un stDev;
BOOL bCorres = TRUE;

	for(mLoop=1; mLoop<=U_SYS_LOOP_MAX; mLoop++)
	{
		if(!BuildToDev_Me_DeteMLA(mLoop, 1, &stDev))
		{
			break; 
		}
		for(mAddr=1; mAddr<=U_1LOOP_DETE_MAX; mAddr++)
		{
			stDev.stDete.field = mAddr;
			if(!bCorrespDisable_one_fieldAndBuf(
							mLoop, mAddr, &stDev))
			{
				bCorres = FALSE;
				break;
			}
		}
	}
	return bCorres;
}


/******************************************************************************
* FUNC: //
******************************************************************************/
BOOL bCorrespDisable_one_fieldAndBuf(
							U8 mLoop, U8 mAddr, TDev_un *pDev)
{
BOOL bDisableField;
BOOL bDisableInBuf;

	bDisableField = bFlsField_beDisabled(mLoop, mAddr);
	bDisableInBuf = FlsJdg_bDisableInBuf(pDev);
	
	return (bDisableField == bDisableInBuf);
}

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

//计算现场部件登记的偏移地址:

BOOL GetFlsOffsetAdr_Field(U8 mLoop, U8 mAddr, U32 *pRtnAdr)
{
U32 mAdr;

	if((mLoop == 0) || (mLoop > U_SYS_LOOP_MAX))
	{
		return FALSE;
	}
	mAdr = (mLoop - 1) * U_1LOOP_DETE_MAX;
	
	if(mAddr >= U_1LOOP_DETE_MAX)
	{
		return FALSE;
	}
	mAdr += (mAddr * U_FLS_Field_1Addr_BYTE_MAX);

	*pRtnAdr = mAdr;
	return TRUE;
}


/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
//查询field是否屏蔽:
//use: 不用 public buf;
BOOL bFlsField_beDisabled(U8 mLoop, U8 mAddr)
{
U8 mPart = U_FlsSave_Part0;
TFlsItemAddr stAdr;
U32 mOffset;
U32 adr;
U8 mBuf[U_FLS_Field_1Addr_BYTE_MAX];
U8 mFlsItem = getFlsItem_Field();
TFlsFieldOne_st *pFieldOne;
	
		if(!getFlsItem_Addr(mFlsItem, mPart, &stAdr))
		{
			return FALSE;
		}
		if(!GetFlsOffsetAdr_Field(mLoop, mAddr, &mOffset))
		{
			return FALSE;
		}
		adr = stAdr.adrS + mOffset;
		FlsHd_Read_nByte(stAdr.chip, &mBuf[0], 
					U_FLS_Field_1Addr_BYTE_MAX, 
					adr);
		
		pFieldOne = (TFlsFieldOne_st*)(&mBuf[0]);
		if(!pFieldOne->bRegist)
		{
			return FALSE;
		}
		else
		{
			return pFieldOne->bDisable;
		}
}



/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

BOOL FlsRd_Field(TFlsFieldHead_st *pHead, U8 *pRtnRegistByte)
{
U8 mPart;
TFlsItemAddr stAdr;
U8 *pBufS;
U32 adr;
U32 mOffset;
U8 mNeedGetAddrNum;
U8 mFlsItem = getFlsItem_Field();

	
	for(mPart=0; mPart<FlsItem_PartMax(mFlsItem); mPart++)
	{
		if(!getFlsItem_Addr(mFlsItem, mPart, &stAdr))
		{
			continue;
		}
		if(!bFlsItem_IsReadAllow(mFlsItem, mPart))
		{
			continue;
		}
		if(!GetFlsOffsetAdr_Field(pHead->mLoop, pHead->mAddrS, &mOffset))
		{
			continue;
		}
		adr = stAdr.adrS + mOffset;
		pBufS = pRtnRegistByte;  //pFlsHd_GetBufS();
		
		mNeedGetAddrNum = (pHead->mAddrE - pHead->mAddrS);
		FlsHd_Read_nByte(stAdr.chip, pBufS, 
					mNeedGetAddrNum * U_FLS_Field_1Addr_BYTE_MAX, 
					adr);
		
		return TRUE;
		
	}
	return FALSE;
	
}

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
// TFlsFieldOne_st
BOOL FlsSave_Field(TFlsFieldHead_st *pHead, U8 *pRegistByte, 
						U8 taskId, U8 flsId)
{
TFlsFieldHead_st *pBufHead;
U8 mNeedGetAddrNum;
U32 mRegiByteMax;
U8 *pBufS;
U8 *pBufNow;
U8 ii;

	pBufS = pFlsHd_GetBufS();
	
	pBufHead = (TFlsFieldHead_st*)(pBufS);
	*pBufHead = *pHead;
	
	if(pBufHead->mAddrS == pBufHead->mAddrE)
	{
		return FALSE;
	}
	if(pBufHead->mAddrS > pBufHead->mAddrE)
	{
		ExchangeU8(&pBufHead->mAddrS, &pBufHead->mAddrE);;
	}
	
	mNeedGetAddrNum = (pHead->mAddrE - pHead->mAddrS);
	mRegiByteMax = (mNeedGetAddrNum * U_FLS_Field_1Addr_BYTE_MAX);
	pBufNow = pBufS + U_FLS_Field_Head_BYTE_MAX;
	
	for(ii=0; ii<mRegiByteMax; ii++)
	{
		*pBufNow++ = *pRegistByte++;
	}
			
	return FlashSaveNew(getFlsItem_Field(), taskId, flsId, pBufS);

}



/******************************************************************************
* FUNC: // 
*   IN:
*  OUT: 
******************************************************************************/

BOOL FlsClr_Field(TFlsFieldHead_st *pHead,
						U8 taskId, U8 flsId)
{
U8 mPart;
TFlsItemAddr stAdr;
U32 mOffset;
TFlsItemAddr stEraseAdr;
U8 mFlsItem = getFlsItem_Field();

	for(mPart=0; mPart<FlsItem_PartMax(mFlsItem); mPart++)
	{
		if(!getFlsItem_Addr(mFlsItem, mPart, &stAdr))
		{
			return FALSE;
		}
		stEraseAdr.chip = stAdr.chip;
		if(!GetFlsOffsetAdr_Field(pHead->mLoop, pHead->mAddrS, &mOffset))
		{
			continue;
		}
		stEraseAdr.adrS = stAdr.adrS + mOffset;
		if(!GetFlsOffsetAdr_Field(pHead->mLoop, pHead->mAddrE, &mOffset))
		{
			continue;
		}
		stEraseAdr.adrE = stAdr.adrS + mOffset;
		
		FlsErase_New(mFlsItem, mPart, 
						taskId, flsId,
						&stEraseAdr);
	}

	return TRUE;
}

/******************************************************************************
* FUNC: // END
*   IN:
*  OUT: 
TFlsFieldHead_st  TFlsFieldOne_st
******************************************************************************/

