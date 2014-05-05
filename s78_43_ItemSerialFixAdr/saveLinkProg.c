#define __saveLinkProg_C__
/******************************************************************************
* @file    saveLinkProg.c
* @author  yx
* @version V1.0
* @date    2013-01-04
* @brief   
* 
******************************************************************************/
#include  "saveLinkProg.h"

#include  "saveItem_incIn.h"
//#include "incFile.h"	


/*================= ���� ============================================*/

#define U_Link_MeDete_LoopMax   4
#define U_Link_MeDete_1Loop_AdrMax   0xF0

#define U_Link_MeExtg_LoopMax   4
#define U_Link_MeExtg_1Loop_AdrMax   0x04
#define U_Link_MeExtg_AddrTotal_Max   0xF0

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

BOOL CacuFlsOffsetAdr_LinkProg(TDev_un *pDev, U32 *pRtnAdr)
{


	if(bMachineIdIsMe(pDev->stDete.machine))
	{
		return cacuFlsOffsetAdr_Link_machineMe(
										pDev, pRtnAdr);
	}
	return FALSE;

}


/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

BOOL FlsSave_LinkProg(TDev_un *pDev, U8 *pProgByte, U8 taskId, U8 flsId)
{
TFlsLinkProg_st *pUnProg;
U8 *pBufS;
U32 ii;//out of range if U8 type

	pBufS = pFlsHd_GetBufS();
	pUnProg = (TFlsLinkProg_st*)(pBufS);
	
	pUnProg->stDev = *pDev;
	for(ii=0; ii<U_FLS_LINK_PROG_BYTE_MAX; ii++)
	{
		pUnProg->byte[ii] = *pProgByte;
		pProgByte++;
	}
	
	return FlashSaveNew(getFlsItem_LinkProg(), taskId, flsId, pBufS);

}
/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/


BOOL FlsRd_LinkProg(TDev_un *pDev, U8 *pProgByte)
{
U8 mPart;
TFlsItemAddr stAdr;
U8 *pBufS;
U32 adr;
U32 mOffset;
U8 mFlsItem = getFlsItem_LinkProg();

	
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
		if(!CacuFlsOffsetAdr_LinkProg(pDev, &mOffset))
		{
			continue;
		}
		adr = stAdr.adrS + mOffset;
		pBufS = pProgByte;  //pFlsHd_GetBufS();
		FlsHd_Read_nByte(stAdr.chip, pBufS, U_FLS_LINK_PROG_BYTE_MAX, adr);
		
		return TRUE;
		
	}
	return FALSE;
}


/******************************************************************************
* FUNC: // 
*   IN:
*  OUT: 
******************************************************************************/

/******************************************************************************
* FUNC: //
******************************************************************************/
// ����link�洢��ַ��������
static BOOL cacuFlsOffsetAdr_Link_machineMe(
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
				return cacuFlsOffsetLink_me_extg(
								pDev, pRtnAdr);
			}
			break;
		case U_DEV_IS_Dete_TYPE: 	//��·�ֳ�����
		case U_DEV_IS_Channel_TYPE: //��·�ֳ�����
			if(pDev->stDete.pnType == GetPanelType_Loop())
			{
				return cacuFlsOffsetLink_me_dete(
								pDev, pRtnAdr);
			}
			break;
		
		case U_DEV_IS_Machine_TYPE: //������
		case U_DEV_IS_Panel_TYPE: 	//����Ԫ��
		case U_DEV_IS_PnModu_TYPE: 	//��Ԫ-·
		default:
			break;
	}
	return FALSE;
	
	//���������ֳ������ź� 0~; ��·������-����������
	// if(CacuDevSequ_0toMax(pDev, &mAdr))
		// *pRtnAdr = (mAdr * U_FLS_LINK_PROG_BYTE_MAX);

}

/******************************************************************************
* FUNC: //
******************************************************************************/
// ����������
static BOOL cacuFlsOffsetLink_me_extg(
								TDev_un *pDev, U32 *pRtnAdr)
{
U8 mLoop;
//U8 mExtgModu;
U8 mExtgMduLine;
U8 mExtgAddr;

	mLoop        = pDev->pnModu.pnSequ - 1;
	//mExtgModu    = pDev->pnModu.modu;
	mExtgMduLine = pDev->pnModu.mduLine;
	
	if(mLoop >= U_Link_MeExtg_LoopMax)
	{
		return FALSE;
	}
	mExtgAddr = (mLoop)*U_Link_MeExtg_1Loop_AdrMax 
				+ mExtgMduLine;
	if(mExtgAddr >= U_Link_MeExtg_AddrTotal_Max)
	{
		return FALSE;
	}
	
	*pRtnAdr = mExtgAddr * U_FLS_LINK_PROG_BYTE_MAX;
	return TRUE;
}

/******************************************************************************
* FUNC: //
******************************************************************************/
// ��������·�ڵ�ַ��
static BOOL cacuFlsOffsetLink_me_dete(
								TDev_un *pDev, U32 *pRtnAdr)
{
U8 mLoop;
U8 mDeteAddr;
U32 mAddr;

	// mLoop = pDev->stDete.pnSequ * U_OneBoard_LOOP_MAX + pDev->stDete.boardLoop;
	mLoop = pDev->stDete.pnSequ - 1;
	if(mLoop >= U_Link_MeDete_LoopMax)
	{
		return FALSE;
	}
	mDeteAddr = pDev->stDete.field;
	if(mDeteAddr >= U_Link_MeDete_1Loop_AdrMax)
	{
		return FALSE;
	}
	
	mAddr = ((mLoop * U_Link_MeDete_1Loop_AdrMax) + mDeteAddr);
	*pRtnAdr = mAddr * U_FLS_LINK_PROG_BYTE_MAX;
	return TRUE;
}



/******************************************************************************
* FUNC: // END
*   IN:
*  OUT: 
******************************************************************************/
