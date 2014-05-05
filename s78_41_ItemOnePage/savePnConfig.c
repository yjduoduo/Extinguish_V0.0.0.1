
#define __savePnConfig_C__
/******************************************************************************
* @file    savePnConfig.c
* @author  yx
* @version V1.0
* @date    2013-01-04
* @brief   
* 
******************************************************************************/
#include  "savePnConfig.h"

#include  "saveItem_incIn.h"

// #include "incFile.h"	

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

BOOL flsSave_pnConf_change(U8 pnType, 
						  U8 mSequS, U8 mSequE, BOOL bAdd,
							U8 taskId, U8 flsId)
{
TFlsUnitConfig_un *pUnitConfig;
U8 *pBufS;
U8 ii;
	
	if((!bPnTypeIsValid(pnType))
	  || (!bPanelTotalSequValid(mSequS)) || (!bPanelTotalSequValid(mSequE)))
	{
		return FALSE;
	}
	pBufS = pFlsHd_GetBufS();
	pUnitConfig = (TFlsUnitConfig_un*)(pBufS);
	
	if(!flsRd_PnConf_toBuf(U_FlsSave_Part0, &pUnitConfig->stSet.pnNum[0]))
	{
		return FALSE;
	}
	
	if(mSequE < mSequS)
	{
		ExchangeU8(&mSequS, &mSequE);
	}
	for(ii=mSequS; ii<=mSequE; ii++)
	{
		if(bAdd)
		{
			pUnitConfig->stSet.pnNum[ii] = 1;
		}
		else
		{
			pUnitConfig->stSet.pnNum[ii] = 0xFF;
		}
	}
	
	return FlashSaveNew(getFlsItem_PnConfig(), taskId, flsId, pBufS);

}

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
BOOL FlsSave_PnConfig_Add(U8 pnType, U8 mSequS, U8 mSequE, 
					 U8 taskId, U8 flsId)
{
	return flsSave_pnConf_change(pnType, 
						  mSequS, mSequE, TRUE,
							taskId, flsId);
}


BOOL FlsSave_PnConfig_Delete(U8 pnType, U8 mSequS, U8 mSequE, 
					 U8 taskId, U8 flsId)
{
	return flsSave_pnConf_change(pnType, 
						  mSequS, mSequE, TRUE,
							taskId, flsId);
}

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

// OUT: pRtnBuf 读出的所有 pnConfig 的数据：
BOOL flsRd_PnConf_toBuf(U8 mPart, U8 *pBufS)
{
TFlsItemAddr stAdr;
U32 adr;
U8 mFlsItem = getFlsItem_PnConfig();
	
	if(!getFlsItem_Addr(mFlsItem, mPart, &stAdr))
	{
		return FALSE;
	}
	if(!bFlsItem_IsReadAllow(mFlsItem, mPart))
	{
		return FALSE;
	}
	if(!bFlsSectorStart_isItem(stAdr.chip, stAdr.adrS, mFlsItem))
	{
		Set_FlsItemState(U_FlsItem_Error_State, mFlsItem, mPart);
		return FALSE;
	}
	adr = stAdr.adrS + U_FLS_SectorStart_BYTES;
	
	FlsHd_Read_nByte(stAdr.chip, pBufS, 
					U_FLS_PanelConfig_BYTE_MAX, adr);
	
	if(JdgCrcOK(pBufS, U_FLS_PanelConfig_BYTE_MAX))
	{
		return TRUE;
	}
	else
	{
		Set_FlsItemState(U_FlsItem_Error_State, mFlsItem, mPart);
		return FALSE;
	}
}

/******************************************************************************
* FUNC: //
*   IN:
*  OUT:  pFlsHd_GetBufS();
******************************************************************************/

BOOL FlsRd_PnConfig(void)
{
U8 mFlsItem = getFlsItem_PnConfig();
U8 mPart;
U8 *pBufS;
U8 pnICanSequ;
	
	for(mPart=0; mPart<FlsItem_PartMax(mFlsItem); mPart++)
	{
		
		pBufS = pFlsHd_GetBufS();
		
		// OUT: pRtnBuf 读出的所有 netMachine的数据：
		if(!flsRd_PnConf_toBuf(mPart, pBufS))
		{
			continue;
		}
		
		for(pnICanSequ=0; pnICanSequ<GetPanelTotalSequMax(); pnICanSequ++)
		{
			if(*pBufS == 1)
			{
				Panel_Regist(pnICanSequ, TRUE);
			}
			else
			{
				Panel_Regist(pnICanSequ, FALSE);
			}
			pBufS++;
		}
		return TRUE;
		
	}
	return FALSE;
}




/******************************************************************************
* FUNC: //
******************************************************************************/



/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

