#define __saveNote_C__
/******************************************************************************
* @file    saveNote.c
* @author  yx
* @version V1.0
* @date    2013-01-04
* @brief   
* 
******************************************************************************/
#include  "saveNote.h"

#include  "saveItem_incIn.h"


//#include "incFile.h"	


/*================= ���� ============================================*/
#define U_Note_MeDete_LoopMax   4
#define U_Note_MeDete_1Loop_AdrMax   0x80

#define U_Note_MeExtg_LoopMax   4
#define U_Note_MeExtg_1Loop_AdrMax   0x04
#define U_Note_MeExtg_AddrTotal_Max   0x80

/*================= �ṹ���� ========================================*/

/*================= ˽�нṹ�������� ================================*/

/*================= ���к������� ====================================*/

/*================= ˽�к������� ====================================*/

/*=================  ================================================*/
		
/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

BOOL FlsSave_Note(TDev_un *pDev, U8 *pNoteByte, U8 taskId, U8 flsId)
{
TFlsNote_st *pUnNote;
U8 *pBufS;
U8 ii;

	pBufS = pFlsHd_GetBufS();
	pUnNote = (TFlsNote_st*)(pBufS);
	
	pUnNote->stDev = *pDev;
	for(ii=0; ii<U_FLS_NOTE_BYTE_MAX; ii++)
	{
		pUnNote->note[ii] = *pNoteByte;
		pNoteByte++;
	}
	
	return FlashSaveNew(getFlsItem_Note(), taskId, flsId, pBufS);

}

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

BOOL FlsRd_Note(TDev_un *pDev, U8 *pRtnNote)
{
U8 mPart;
TFlsItemAddr stAdr;
U8 *pBufS;
U32 adr;
U32 mOffset;
U8 mFlsItem = getFlsItem_Note();

	
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
		if(!GetFlsOffsetAdr_Note_Rd(pDev, &mOffset))
		{
			continue;
		}
		adr = stAdr.adrS + mOffset;
		pBufS = pRtnNote;  //pFlsHd_GetBufS();
		FlsHd_Read_nByte(stAdr.chip, pBufS, U_FLS_NOTE_BYTE_MAX, adr);
		
		break;
		
	}
	
	if(mPart<FlsItem_PartMax(mFlsItem))
	{
		pBufS = pRtnNote;
		for(mOffset=0; mOffset<U_FLS_NOTE_BYTE_MAX; mOffset++)
		{
			if(*pBufS == 0xFF)
			{
				*pBufS = 0;
				break; // 0xFF Ҳ����һ�� '/0'
			}
			pBufS++;
		}
		return TRUE;
	}
	return FALSE;
}


/******************************************************************************
* FUNC: //����ע�͵�ƫ�Ƶ�ַ
*   IN:
*  OUT: 
******************************************************************************/
BOOL GetFlsOffsetAdr_Note_Wr(TDev_un *pDev, U32 *pRtnAdr)
{
	if(bMachineIdIsMe(pDev->stDete.machine))
	{
		return cacuFlsOffsetAdr_Note_machineMe(
										pDev, pRtnAdr);
	}
	return FALSE;
}

BOOL GetFlsOffsetAdr_Note_Rd(TDev_un *pDev, U32 *pRtnAdr)
{
	if(bMachineIdIsMe(pDev->stDete.machine))
	{
		return cacuFlsOffsetAdr_Note_machineMe(
										pDev, pRtnAdr);
	}
	return FALSE;
}



/******************************************************************************
* FUNC: //
******************************************************************************/
// ����note�洢��ַ��������
static BOOL cacuFlsOffsetAdr_Note_machineMe(
								TDev_un *pDev, U32 *pRtnAdr)
{
U8 mDevClass;

	if(!bMachineIdIsMe(pDev->stDete.machine))
	{
		return FALSE;
	}
	
	mDevClass = JdgDevClass(pDev); // OUT:  emDevClass
	switch(mDevClass)
	{
		case U_DEV_IS_ModuLine_TYPE: //��Ԫ-·-����
			if(pDev->stDete.pnType == GetPanelType_Extg())
			{
				return cacuFlsOffsetNote_me_extg(
								pDev, pRtnAdr);
			}
			break;
		case U_DEV_IS_Dete_TYPE: 	//��·�ֳ�����
		case U_DEV_IS_Channel_TYPE: //��·�ֳ�����
			if(pDev->stDete.pnType == GetPanelType_Loop())
			{
				return cacuFlsOffsetNote_me_dete(
								pDev, pRtnAdr);
			}
			break;
		
		case U_DEV_IS_Machine_TYPE: //������
		case U_DEV_IS_Panel_TYPE: 	//����Ԫ��
		case U_DEV_IS_PnModu_TYPE: 	//��Ԫ-·
		default:
			break;
	}
    return TRUE;
	
	//���������ֳ������ź� 0~; ��·������-����������
	// if(CacuDevSequ_0toMax(pDev, &mAdr))
		// *pRtnAdr = (mAdr * U_FLS_NOTE_BYTE_MAX);

}

/******************************************************************************
* FUNC: //
******************************************************************************/
// ����������
static BOOL cacuFlsOffsetNote_me_extg(
								TDev_un *pDev, U32 *pRtnAdr)
{
U8 mLoop;
//U8 mExtgModu;
U8 mExtgMduLine;
U8 mExtgAddr;

	mLoop        = pDev->pnModu.pnSequ - 1;
	//mExtgModu    = pDev->pnModu.modu;
	mExtgMduLine = pDev->pnModu.mduLine;
	
	if(mLoop >= U_Note_MeExtg_LoopMax)
	{
		return FALSE;
	}
	mExtgAddr = (mLoop)*U_Note_MeExtg_1Loop_AdrMax 
				+ mExtgMduLine;
	if(mExtgAddr >= U_Note_MeExtg_AddrTotal_Max)
	{
		return FALSE;
	}
	
	*pRtnAdr = mExtgAddr * U_FLS_NOTE_BYTE_MAX;
	return TRUE;
}

/******************************************************************************
* FUNC: //
******************************************************************************/
// ��������·�ڵ�ַ��
static BOOL cacuFlsOffsetNote_me_dete(
								TDev_un *pDev, U32 *pRtnAdr)
{
U8 mLoop;
U8 mDeteAddr;
U32 mAddr;

	// mLoop = pDev->stDete.pnSequ * U_OneBoard_LOOP_MAX + pDev->stDete.boardLoop;
	mLoop = pDev->stDete.pnSequ - 1;
	if(mLoop >= U_Note_MeDete_LoopMax)
	{
		return FALSE;
	}
	mDeteAddr = pDev->stDete.field;
	if(mDeteAddr >= U_Note_MeDete_1Loop_AdrMax)
	{
		return FALSE;
	}
	
	mAddr = ((mLoop * U_Note_MeDete_1Loop_AdrMax) + mDeteAddr);
	*pRtnAdr = mAddr * U_FLS_NOTE_BYTE_MAX;
	return TRUE;
}


/******************************************************************************
* FUNC: // END
*   IN:
*  OUT: 
******************************************************************************/
