#ifndef __mTask_Test_H__
#define __mTask_Test_H__
/******************************************************************************
* @file    mTask_Test.h
* @author  yx
* @version V1.0
* @date    2013-09-25
* @brief   
* 
* 
* 
* 
* 
* 
#include  "mTask_Test.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

#include  "hwEx13_lcd_DataType.h"
#include  "hwEx11_lcd_DefPara.h"
#include  "strClock.h"
/*================= extern ============================================*/
#ifdef  __mTask_Test_C__
#define EX_mTask_Test
#else
#define EX_mTask_Test extern 
#endif
/*================= 常数 ============================================*/
/*================= 结构体定义 ======================================*/

/*================= 公有结构变量声明 ================================*/

/*================= 私有函数声明-显示 ====================================*/
#ifdef  __mTask_Test_C__


#endif  //__mTask_Test_C__
/*================= 私有函数声明 ====================================*/
#ifdef  __mTask_Test_C__

#if U_SYS_Test_Lcd == 1
// 测试LCD LIB的执行时间
void TestLcdTmr_Ing(void);
void TestLcdTmr_Start(void);

void test_MCycle_Return(void);
void test_MCycle_KeyReturn(void);


void sim_evt_show_one(U32 mVal);
void sim_evt_show_SetTmrArrivedRefresh(BOOL bArrived);
void sim_EvtShow(void);

void simInit_TimerAddEvt(void);
void simExec_TimerAddEvt(void);
void simAddOne_TimerAddEvt(U32 mVal);
void simAddOne_TimerRectangle(U32 mVal);

#endif // U_SYS_Test_Lcd

BOOL sim_LoadNewEvent(U8 mCls, U8 mAdrIni, U8 mThing, U8 auxDelayS);


#endif  //__mTask_Test_C__
/*================= 公有函数声明 ====================================*/
//EX_mTask_Test 

extern void SysTask_Test_Init(void);

extern void SysTask_Test_Exec(void);


/******************************************************************************
// END :
******************************************************************************/
#endif // __mTask_Test_H__

