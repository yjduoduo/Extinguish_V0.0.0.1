#ifndef __evt_Buf_incIn_Extern_H__
#define __evt_Buf_incIn_Extern_H__
/******************************************************************************
* @file    evt_Buf_incIn_Extern.h
* @author  yx
* @version V1.0
* @date    2012-01-05
* @brief   各事件队列.c用。
* 
#include  "evt_Buf_incIn_Extern.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

/*=================  ============================================*/
// #include  "incSysCommon.h"
#include  "evt_Para.h"
#include  "evtThingDef.h"

#include  "evtStrDef.h"
#include  "evtStruct.h"
#include  "EventAndWinBuf.h"

/*================= ============================================*/

// if 一次翻页移动多条
extern BOOL  bSysStatus_TurnPageSerial(void);

/******************************************************************************
// END :
******************************************************************************/
#endif // __evt_Buf_incIn_Extern_H__

