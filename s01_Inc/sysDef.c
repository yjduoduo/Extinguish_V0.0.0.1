#define __sysDef_C__
/******************************************************************************
* @file    sysDef.c
* @author  yx
* @version V1.0
* @date    2012-01-05
* @brief   
* 
******************************************************************************/
#include  "sysDef.h"


//#include "incFile.h"
#include  "tmrTick.h"


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
static BOOL bTaskHasInitial[U_SYS_TASK_ID_MAX];

void InitAll_MyHdHaveIniSign(void)
{
U8 mTaskId;
	for(mTaskId=0; mTaskId<U_SYS_TASK_ID_MAX; mTaskId++)
	{
		bTaskHasInitial[mTaskId] = FALSE;
	}
}

void SetMyHdHaveIniSign(U8 mTaskId)
{
	if(mTaskId < U_SYS_TASK_ID_MAX)
	{
		bTaskHasInitial[mTaskId] = TRUE;
	}
}

void ClrMyHdHaveIniSign(U8 mTaskId)
{
	if(mTaskId < U_SYS_TASK_ID_MAX)
	{
		bTaskHasInitial[mTaskId] = FALSE;
	}
}

BOOL bMyHdHaveIniSign(U8 mTaskId)
{
	if(mTaskId < U_SYS_TASK_ID_MAX)
	{
		return bTaskHasInitial[mTaskId];
	}
	else
	{
		return FALSE;
	}
}

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

U8 Get_TmrId_100msLow(void)
{
	return TASK_100MS_LOW;
}
U8 Get_TmrId_1sLow(void)
{
	return TASK_1S_LOW;
}

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

U8 GetSysTaskId_FlsVerify(void)
{
	return U_SysTask_FlsVerify;
}

/******************************************************************************
* FUNC: //
******************************************************************************/

BOOL bMachineIdIsMe(U8 mMachine)
{
	return (mMachine == U_MACHINE_SELF);
}
U8 GetMachineMaster(void)
{
	return U_MACHINE_MASTER;
}
U8 GetLanguageChinese(void)
{
	return U_Chinese_LANGUAGE;
}


/******************************************************************************
* FUNC: // 
******************************************************************************/
U8 GetMachineMax(void)
{
	return U_MACHINE_MAX;
}
BOOL bMachineValid(U8 mMachine)
{
	return ((mMachine  < U_MACHINE_MAX)
		   ||(mMachine == U_MACHINE_SELF));
}



U8 GetPanelTotalSequMax(void)
{
	return U_PANEL_TOTAL_SEQU_MAX;
}
BOOL bPanelTotalSequValid(U8 mPnSequ)
{
	return (mPnSequ < U_PANEL_TOTAL_SEQU_MAX);
}

/******************************************************************************
* FUNC: // 是否 当前的用户满足操作权限
*   IN:
*  OUT: TRUE=满足。
******************************************************************************/
// BOOL bUserGradeMeetPurview
BOOL bUserGradeOk(U8 nowGrade, U8 mNeedGrade)
{
	return TRUE;
}

/******************************************************************************
* FUNC: // END
*   IN:
*  OUT: 
******************************************************************************/
