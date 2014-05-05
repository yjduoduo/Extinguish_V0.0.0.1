#define __saveTmrPwroffAndHist_C__
/******************************************************************************
* @file    saveTmrPwroffAndHist.c
* @author  yx
* @version V1.0
* @date    2012-01-05
* @brief   
* 
******************************************************************************/
#include  "saveTmrPwroffAndHist.h"
#include  "prjBool.h"

#include  "Save_Item_incOut.h"
#include  "Save_Hist_incOut.h"
#include  "tmrTick.h"
#include  "phClock.h"
#include  "evt_Buf_incOut.h"
#include  "evt_Class.h"

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
保存关机时间的控制：bSavePwrOff_Arrived(); -> FlsWr_pwrOff_Start();
******************************************************************************/

void SavePwrOff_Tmr_Init(void)
{
	SetTmrTickTask(TASK_SavePowerOff, TMR_SavePowerOff);
	
}
		
/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

BOOL bSavePwrOff_Arrived(void)
{
	return (GetTickTaskStatus(TASK_SavePowerOff) == TRUE);
}

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

void FlsWr_pwrOff_Start(void)
{
TEvtClock_st  stClock;

	GetRamEvtTimer(&stClock);
	FlsWr_pwrOff_New(&stClock);
}


/******************************************************************************
* FUNC: //历史记录，存关机时间
*   IN:
*  OUT: 
******************************************************************************/
BOOL PwrOff_toHist(void)
{
TEvtTrans_st  stEvt;


	if(!FlsRd_PwrOff(&stEvt.evtClock))
	{
		return FALSE;
	}
	DevSetInvalid(&stEvt.unDev);
	stEvt.thing = GetEvtThingDef_PwrOff();
	return HistNewEvent(&stEvt);
}



/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

void SaveHist_Tmr_Init(void)
{
	SetTmrTickTask(TASK_SaveHist, TMR_SaveHist);
}

BOOL bSaveHist_Arrived(void)
{
	return (GetTickTaskStatus(TASK_SaveHist) == TRUE);
}


/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

void SaveFlsId_Tmr_Init(void)
{
	SetTmrTickTask(TASK_SaveFlsId, TMR_SaveFlsId);
}

BOOL bSaveFlsId_Arrived(void)
{
	return (GetTickTaskStatus(TASK_SaveFlsId) == TRUE);
}



/******************************************************************************
* FUNC: // END
*   IN:
*  OUT: 
******************************************************************************/
