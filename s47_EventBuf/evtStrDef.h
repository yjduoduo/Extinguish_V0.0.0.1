#ifndef __evtStrDef_H__
#define __evtStrDef_H__
/******************************************************************************
* @file    evtStrDef.h
* @author  yx
* @version V1.2
* @date    2013-09-23
* @brief   TEvtBufWho_st; 
*  		 各种事件的队列 结构;


* @Versin history:
* V1.2, 2013-09-23 
*		改变：TEvtLink_st， TEvtExtg_st  为单条模式
*		分离 "TEvtBufWho_st", "TEvtPos_st" -> "evtStrCommon"
* V1.1, 2013-09-11
*		改变：TEvtLink_st， TEvtExtg_st
* V1.0, 2012-09-09
* 
#include  "evtStrDef.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

#include  "strDevice.h"
#include  "strClock.h"

#include  "evt_Para.h"
#include  "evtStrCommon.h"
/*=================  ============================================*/


/*================= 事件队列 各个结构 ================================*/
#pragma pack(1)	
typedef struct{
	TEvtPos_st  stPos;
	U8 thing;
	TEvtClock_st evtClock;
}TEvtAlarm_st; //

typedef struct{
	TEvtPos_st  stPos;
	U8 thing;
	TEvtClock_st evtClock;
}TEvtFault_st; //


// typedef struct{
	// TEvtPos_st  stPos;
	// U8 thingAction; //动作状态
	// U8 delayActSec; // 动作延时 剩余s:
	// U8 thingAck;    //反馈状态
	// TEvtClock_st evtClockAction;
	// TEvtClock_st evtClockAck;
// }TEvtLink_st; // U_ModuEvt_EVT

typedef struct{
	TEvtPos_st  stPos;
	U8 thing; //动作，反馈 状态
	U8 delayActSec; // 动作延时 剩余s:
	TEvtClock_st evtClock;
}TEvtLink_st; // U_ModuEvt_EVT

// typedef struct{
	// TEvtPos_st  stPos;
	// U8 thingCircuit; 	 // 气灭流程: 声光动作，辅助设备动作，喷洒动作。
	// U8 thingAnnunciator; // 声光 可以单独控制 
	// U8 thingSpray;   	 // 喷洒动作，喷洒停止。
	// U8 thgSprayAck;   	 // 喷洒反馈
	// U8 delaySpraySec; 	 // 喷洒延时 剩余s:
	// TEvtClock_st evtClockAnnu; // 
	// TEvtClock_st evtClockSpray; // 喷洒;
	// TEvtClock_st evtClockSpryAck; // 喷洒反馈;
// }TEvtExtg_st; // U_ExtgEvt_EVT

typedef struct{
	TEvtPos_st  stPos;
	U8 thing; 	 // 气灭流程: 声光动作，辅助设备动作，喷洒动作。
	U8 delaySpraySec; 	 // 喷洒延时 剩余s:
	TEvtClock_st evtClock; //
}TEvtExtg_st; // U_ExtgEvt_EVT


typedef struct{
	TEvtPos_st  stPos;
	U8 thing;
	TEvtClock_st evtClock;
}TEvtSpvs_st; //

typedef struct{
	TEvtPos_st  stPos;
	U8 thing;
	TEvtClock_st evtClock;
}TEvtDsab_st; //
#pragma pack()





/******************************************************************************
// END :
******************************************************************************/
#endif // __evtStrDef_H__

