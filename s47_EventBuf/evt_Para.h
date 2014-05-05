#ifndef __evt_Para_H__
#define __evt_Para_H__
/******************************************************************************
* @file    evt_Para.h
* @author  yx
* @version V1.2
* @date    2013.10.15  14:30 
* @brief   事件队列的大小等定义
* 
* @Versin history:
* V1.2, 2013.10.15  14:30 
*		U_OneScr_Cls_MAX 的定义 由 evtStruct.h 改到 evt_Para.h.
* V1.1, 2013.9.23  15:30 
* 		add:  U_EvtVary_Insert_TYPE;
* V1.0, 2013-01-04
* 
#include  "evt_Para.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

/*================= 常数 ============================================*/

/*================= 常数 ============================================*/

#define U_EvtPos_Invalid  0xFFFF
typedef unsigned short   EVTWORD;

//一屏显示的事件类别MAX. 火警/联动。
#define U_OneScr_Cls_MAX   2 
/*================= 事件队列类别 ============================================*/

enum emEvtClass{ //事件队列类别
	U_EvtCls_Alarm = 0,
	U_EvtCls_Fault = 1,
	U_EvtCls_Link = 2,
	U_EvtCls_Extg = 3,
	U_EvtCls_Spvs = 4, //监管
	U_EvtCls_Dsab = 5, //屏蔽
	
	U_EvtCls_MAX = 6,  
	
};	
	
/*================= 操作 ============================================*/

enum emEvtVaryType{
	U_EvtVary_Add_TYPE =    (1<<0),
	U_EvtVary_Remove_TYPE = (1<<1),
	U_EvtVary_Insert_TYPE = (1<<2),
	U_EvtVary_Refresh_TYPE = (1<<3),
};
	
/******************************************************************************
// END :
******************************************************************************/
#endif // __evt_Para_H__

