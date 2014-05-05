#ifndef __evtStrCommon_H__
#define __evtStrCommon_H__
/******************************************************************************
* @file    evtStrCommon.h
* @author  yx
* @version V1.0
* @date    2013-09-23
* @brief   各种事件共用的结构;
*
* @Versin history:
* V1.0, 2013-09-23
* 
#include  "evtStrCommon.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

#include  "strDevice.h"

#include  "evt_Para.h"
/*=================  ============================================*/

/*================= 一条事件 标识 ================================*/

typedef struct{
	EVTWORD sequ;  //序号  0~
	EVTWORD locat; //物理偏移
}TEvtBufWho_st; //一条事件。


/*================= Commmon 存储 ================================*/

#pragma pack(1)	
typedef struct{ //每种事件都有的。
	EVTWORD pre;
	EVTWORD next;
	
	TDev_un  unDev;   //是判断buf[N]是否有数据的判据
	U8     devType; //设备本身类型，非用户定义
}TEvtPos_st; //
#pragma pack()


/*================= 事件队列属性 ================================*/
	
//total = 0: head = end;  every.pre = next = MAX;
//total = 1: head = end;  every.pre = next = MAX;
//total = 2: head != end; every.pre != next

typedef struct{
	EVTWORD total;  
	EVTWORD head;
	EVTWORD end;  //有效数据
	U8 bFull;
	
	BOOL bVaryTotal;	//总数变 
	BOOL bVaryBuf;	   //buf有变 
}TPointEvt_st;

/******************************************************************************
// END :
******************************************************************************/
#endif // __evtStrCommon_H__

