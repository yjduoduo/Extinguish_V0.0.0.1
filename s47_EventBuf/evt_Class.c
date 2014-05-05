#define __evt_Class_C__
/******************************************************************************
* @file    evt_Class.c
* @author  yx
* @version V1.0
* @date    2012-01-05
* @brief   
* 
******************************************************************************/
#include  "evt_Class.h"

#include  "evtThingDef.h"
#include  "historyClsDef.h"

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


/******************************************************************************
* FUNC: //历史记录保存 归类
*   IN:
*  OUT: 
// OUT: Bits: (1<<U_HIST_Alarm_CLASS ) 等
******************************************************************************/

U32 EvtThing_toHistClsBits(TEvtTrans_st *pEvtTrans) //历史记录保存 归类
{
U8 thing = pEvtTrans->thing;
	
	if((thing >= U_Ala_EVT_Min) && (thing < U_Ala_EVT_Max))
	{
		return ((1<<U_HIST_Alarm_CLASS ) | (1<<U_HIST_All_CLASS ));
	}
	
	//	
	if((thing >= U_Fau_EVT_Min) && (thing < U_Fau_EVT_Max))
	{
		return ((1<<U_HIST_Fault_CLASS) | (1<<U_HIST_All_CLASS));
	}
	//	
	if((thing >= U_Link_EVT_Min) && (thing < U_Link_EVT_Max))
	{
		return ((1<<U_HIST_Link_CLASS) | (1<<U_HIST_All_CLASS));
	}
	//	
	if((thing >= U_Opea_EVT_Min) && (thing < U_Opea_EVT_Max))
	{
		return ((1<<U_HIST_Opea_CLASS) | (1<<U_HIST_All_CLASS));
	}
	//	
	if((thing >= U_Super_EVT_Min) && (thing < U_Super_EVT_Max))
	{
		return ((1<<U_HIST_Super_CLASS) );
	}
	
	//
	return 0;
}

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

U8 GetEvtThingDef_Fault(void)
{
	return U_Fault_EVT;
}
U8 GetEvtThingDef_FlsErase(void)
{
	return U_Super_FlsErase_EVT;
}
U8 GetEvtThingDef_FlsCopyRenew(void)
{
	return U_Super_FlsCopyRenew_EVT;
}

U8 GetEvtThingDef_PwrOff(void)
{
	return U_PwrOff_EVT;
}


/******************************************************************************
* FUNC: // END
*   IN:
*  OUT: 
******************************************************************************/
