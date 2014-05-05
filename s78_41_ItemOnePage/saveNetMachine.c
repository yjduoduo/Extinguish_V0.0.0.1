#define __saveNetMachine_C__
/******************************************************************************
* @file    saveNetMachine.c
* @author  yx
* @version V1.0
* @date    2013-01-04
* @brief   
* 
******************************************************************************/
#include  "saveNetMachine.h"

#include  "saveItem_incIn.h"

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
				
BOOL FlsSave_NetMachine_Delete(U8 mMachS, U8 mMachE,
						U8 taskId, U8 flsId)
{
	return flsSave_NetMachine_change(mMachS, mMachE, 
						FALSE,
						taskId, flsId);
}
						
BOOL FlsSave_NetMachine_Add(U8 mMachS, U8 mMachE,
						U8 taskId, U8 flsId)
{
	return flsSave_NetMachine_change(mMachS, mMachE, 
						TRUE,
						taskId, flsId);
}

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

BOOL flsSave_NetMachine_change(U8 mMachS, U8 mMachE, BOOL bAdd,
						U8 taskId, U8 flsId)
{
TFlsMachineConfig_un *pUnMach;
U8 *pBufS;
U8 ii;
	
	if((!bMachineValid(mMachS)) || (!bMachineValid(mMachE)))
	{
		return FALSE;
	}
	pBufS = pFlsHd_GetBufS();
	pUnMach = (TFlsMachineConfig_un*)(pBufS);
	
	// OUT: pRtnBuf 读出的所有 netMachine的数据：
	if(!flsRd_NetMach_toBuf(U_FlsSave_Part0, &pUnMach->stSet.machNum[0]))
	{
		return FALSE;
	}
	
	if(mMachE < mMachS)
	{
		ExchangeU8(&mMachS, &mMachE);
	}
	for(ii=mMachS; ii<=mMachE; ii++)
	{
		if(bAdd)
		{
			pUnMach->stSet.machNum[ii] = 1;
		}
		else
		{
			pUnMach->stSet.machNum[ii] = 0xFF;
		}
	}
	
	return FlashSaveNew(getFlsItem_NetMachine(), taskId, flsId,pBufS);
}

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

// OUT: pRtnBuf 读出的所有 netMachine的数据：
BOOL flsRd_NetMach_toBuf(U8 mPart, U8 *pBufS)
{
TFlsItemAddr stAdr;
U32 adr;
U8 mFlsItem = getFlsItem_NetMachine();
	
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
					U_FLS_MachineConfig_BYTE_MAX, adr);
	
	if(JdgCrcOK(pBufS, U_FLS_MachineConfig_BYTE_MAX))
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
*  OUT: Machine_Regist();
******************************************************************************/

BOOL FlsRd_NetMachine(void)
{
U8 mPart;
U8 *pBufS;
U8 mMachineSequ;
U8 mFlsItem = getFlsItem_NetMachine();
	
	for(mPart=0; mPart<FlsItem_PartMax(mFlsItem); mPart++)
	{
		pBufS = pFlsHd_GetBufS();
		
		// OUT: pRtnBuf 读出的所有 netMachine的数据：
		if(!flsRd_NetMach_toBuf(mPart, pBufS))
		{
			continue;
		}
		
		for(mMachineSequ=0; mMachineSequ<GetMachineMax(); mMachineSequ++)
		{
			if(*pBufS == 1)
			{
				Machine_Regist(mMachineSequ, TRUE);
			}
			else
			{
				Machine_Regist(mMachineSequ, FALSE);
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
* FUNC: // END
*   IN:
*  OUT: 
******************************************************************************/
