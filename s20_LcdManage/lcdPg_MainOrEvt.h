#ifndef __lcdPg_MainOrEvt_H__
#define __lcdPg_MainOrEvt_H__
/******************************************************************************
* @file    lcdPg_MainOrEvt.h
* @author  yx
* @version V1.0
* @date    2013-09-10
* @brief   MCycle页面的切换。切换的顺序在 "lcdTsk_PgNum.c" cstPgMCycDef[]
* @in	MCyclePage + keyReturn.
* 
#include  "lcdPg_MainOrEvt.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

/*================= extern ============================================*/
#ifdef  __lcdPg_MainOrEvt_C__
#define EX_lcdPg_MainOrEvt
#else
#define EX_lcdPg_MainOrEvt extern 
#endif
/*================= 常数 ============================================*/
//#define 
/*================= 结构体定义 ======================================*/

/*================= 公有结构变量声明 ================================*/

/*================= 私有函数声明 ====================================*/
#ifdef  __lcdPg_MainOrEvt_C__

// 查找优先级更低的事件页面。
// Pre:  pgEvt_jdgHaveEvent();
// IN: mFromSequ = 开始查找的sequ;
//	  mFromSequ < U_PgMCycDef_Event_MAX， 否则 Default = 0.
// OUT: FALSE = 无优先级更低的事件
BOOL jdgNextEvtCycSequ_defaultPageMain(U8 mFromSequ, 
									 PAGEWORD *pRtnPgNum);


// page Main. next MCycle:
PAGEWORD jdgPageMain_NextMCycle(void);
// page Main和event以外的. next MCycle:
PAGEWORD jdgPageMOther_NextMCycle(void);
// page event. next MCycle:
PAGEWORD jdgPageEvent_NextMCycle(void);


#endif  //__lcdPg_MainOrEvt_C__

/*================= 公有函数声明 ====================================*/
//EX_lcdPg_MainOrEvt 

//  查找 next MCycle Page:
extern BOOL JdgNextMCyclePage(PAGEWORD *pRtnPgNum);

// main or 事件 page;
// *  OUT: 当前优先级最高的事件页面。if all total==0, return MAIN.
extern PAGEWORD JdgMainOrEvtHighPriorityPage(void); 


/******************************************************************************
// END :
******************************************************************************/
#endif // __lcdPg_MainOrEvt_H__

