#define __saveItemAux_C__
/******************************************************************************
* @file    saveItemAux.c
* @author  yx
* @version V1.0
* @date    2013-07-01
* @brief   
* auxiliary
******************************************************************************/
#include  "saveItemAux.h"

#include  "saveInc_Extern.h"
#include  "Save_Item_incOut.h"

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

void FlsMeStatus_Default(TFlsSysSet_un *pSet)
{
U8 ii;

	pSet->stSet.runAuto = FALSE;
	pSet->stSet.runManu = FALSE;
	
	for(ii=0; ii<U_PSSW1_BYTE_MAX; ii++)
	{
		pSet->stSet.pssw1[ii] = 1;
	}
	for(ii=0; ii<U_PSSW2_BYTE_MAX; ii++)
	{
		pSet->stSet.pssw2[ii] = 1;
	}
	
	pSet->stSet.machAdr = 1;
	pSet->stSet.machMasterOrSlave = GetMachineMaster();
	
	pSet->stSet.language = GetLanguageChinese();
	
	
}

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

BOOL FlsSetMeStatus_runAuto(U8 mSet, U8 taskId, U8 flsId)
{
TFlsSysSet_un *pSysSet;

	pSysSet = pGetFlsSysSet();
	pSysSet->stSet.runAuto = mSet;
	return FlsSysSetMeStatus_Save(taskId, flsId);
	
}


BOOL FlsSetMeStatus_runManu(U8 mSet, U8 taskId, U8 flsId)
{
TFlsSysSet_un *pSysSet;

	pSysSet = pGetFlsSysSet();
	pSysSet->stSet.runManu = mSet;
	return FlsSysSetMeStatus_Save(taskId, flsId);
	
}


BOOL FlsSetMeStatus_machAdr(U8 mSet, U8 taskId, U8 flsId)
{
TFlsSysSet_un *pSysSet;

	pSysSet = pGetFlsSysSet();
	pSysSet->stSet.machAdr = mSet;
	return FlsSysSetMeStatus_Save(taskId, flsId);
	
}


BOOL FlsSetMeStatus_machMasterOrSlave(U8 mSet, U8 taskId, U8 flsId)
{
TFlsSysSet_un *pSysSet;

	pSysSet = pGetFlsSysSet();
	pSysSet->stSet.machMasterOrSlave = mSet;
	return FlsSysSetMeStatus_Save(taskId, flsId);
	
}


BOOL FlsSetMeStatus_language(U8 mSet, U8 taskId, U8 flsId)
{
TFlsSysSet_un *pSysSet;

	pSysSet = pGetFlsSysSet();
	pSysSet->stSet.language = mSet;
	return FlsSysSetMeStatus_Save(taskId, flsId);
	
}


BOOL FlsSetMeStatus_pssw1(U8 *pByte, U8 taskId, U8 flsId)
{
U8 ii;
TFlsSysSet_un *pSysSet;

	pSysSet = pGetFlsSysSet();
	for(ii=0; ii<U_PSSW1_BYTE_MAX; ii++)
	{
		pSysSet->stSet.pssw1[ii] = *pByte;
		pByte++;
	}
	return FlsSysSetMeStatus_Save(taskId, flsId);
	
}


BOOL FlsSetMeStatus_pssw2(U8 *pByte, U8 taskId, U8 flsId)
{
U8 ii;
TFlsSysSet_un *pSysSet;

	pSysSet = pGetFlsSysSet();
	for(ii=0; ii<U_PSSW2_BYTE_MAX; ii++)
	{
		pSysSet->stSet.pssw2[ii] = *pByte;
		pByte++;
	}
	return FlsSysSetMeStatus_Save(taskId, flsId);
	
}

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/



/******************************************************************************
* FUNC: //
******************************************************************************/



/******************************************************************************
* FUNC: // END
*   IN:
*  OUT: 
******************************************************************************/
