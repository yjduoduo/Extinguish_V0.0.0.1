#define __saveMeStatus_C__
/******************************************************************************
* @file    saveMeStatus.c
* @author  yx
* @version V1.0
* @date    2013-01-04
* @brief   
* 
******************************************************************************/
#include  "saveMeStatus.h"

#include  "saveItem_incIn.h"

//#include "incFile.h"	


/*================= ���� ============================================*/

/*================= �ṹ���� ========================================*/

/*================= ˽�нṹ�������� ================================*/

/*================= ���к������� ====================================*/

/*================= ˽�к������� ====================================*/

/*=================  ================================================*/
		
/******************************************************************************
* FUNC: // ��flash����
*   IN:
*  OUT: unSysSet 
******************************************************************************/

BOOL FlsRd_MeStatus(void)
{
U8 mFlsItem = getFlsItem_MeStatus();
U8 mPart;
TFlsItemAddr stAdr;
U8 *pBufS;
U32 adr;
	
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
		if(!bFlsSectorStart_isItem(stAdr.chip, stAdr.adrS, mFlsItem))
		{
			Set_FlsItemState(U_FlsItem_Error_State, mFlsItem, mPart);
			continue;
		}
		adr = stAdr.adrS + U_FLS_SectorStart_BYTES;
		pBufS = (U8*)(&unSysSet);  //pFlsHd_GetBufS();
		FlsHd_Read_nByte(stAdr.chip, pBufS, U_SYSSET_BYTE_MAX, adr);
		if(!JdgCrcOK(pBufS, U_SYSSET_BYTE_MAX))
		{
			Set_FlsItemState(U_FlsItem_Error_State, mFlsItem, mPart);
			continue;
		}
		
		return TRUE;
		
	}
	FlsMeStatus_Default(&unSysSet);
	return FALSE;
}




/******************************************************************************
* FUNC: // ����
*   IN:
*  OUT: 
******************************************************************************/

BOOL FlsSysSetMeStatus_Save(U8 taskId, U8 flsId)
{
	return FlashSaveNew(getFlsItem_MeStatus(), 
							taskId, flsId,(U8*)(&unSysSet));
	
}

/******************************************************************************
* FUNC: // �������ҿ��ܱ��ı����ݡ�
*   IN:
*  OUT: 
******************************************************************************/

TFlsSysSet_un *pGetFlsSysSet(void)
{
	return &unSysSet;
}



/******************************************************************************
* FUNC: // END
*   IN:
*  OUT: 
******************************************************************************/
