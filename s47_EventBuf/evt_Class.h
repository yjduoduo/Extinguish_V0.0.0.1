#ifndef __evt_Class_H__
#define __evt_Class_H__
/******************************************************************************
* @file    evt_Class.h
* @author  yx
* @version V1.0
* @date    2012-01-05
* @brief   
* 
#include  "evt_Class.h"
******************************************************************************/
//
#include  "prjCompileCon.h"
#include  "strEvtTrans.h"

/*================= extern ============================================*/
#ifdef  __evt_Class_C__
#define EX_evt_Class
#else
#define EX_evt_Class extern 
#endif
/*================= 常数 ============================================*/
//#define 
/*================= 结构体定义 ======================================*/

/*================= 公有结构变量声明 ================================*/

/*================= 私有函数声明 ====================================*/
#ifdef  __evt_Class_C__

#endif  //__evt_Class_C__
/*================= 公有函数声明 ====================================*/
//EX_evt_Class 

//历史记录保存 归类
// OUT: Bits: (1<<U_HIST_Alarm_CLASS ) 等
extern U32 EvtThing_toHistClsBits(TEvtTrans_st *pEvtTrans); 

// evtThingDef.h 部分读取:
extern U8 GetEvtThingDef_Fault(void);
extern U8 GetEvtThingDef_FlsErase(void);
extern U8 GetEvtThingDef_FlsCopyRenew(void);
extern U8 GetEvtThingDef_PwrOff(void);

/******************************************************************************
// END :
******************************************************************************/
#endif // __evt_Class_H__

