#ifndef __mRunTask_H__
#define __mRunTask_H__
/******************************************************************************
* @file    mRunTask.h
* @author  yx
* @version V1.0
* @date    2012-01-05
* @brief   
* 
#include  "mRunTask.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

/*================= extern ============================================*/
#ifdef  __mRunTask_C__
#define EX_mRunTask
#else
#define EX_mRunTask extern 
#endif
/*================= 常数 ============================================*/
//#define 
/*================= 结构体定义 ======================================*/

/*================= 公有结构变量声明 ================================*/

/*================= 私有函数声明 ====================================*/
#ifdef  __mRunTask_C__

extern  void SysInit_WhenPowerOn(void);
extern  void SysInit_WhenReset(void);
void sys_CloseAllHd_AndIniTimer(void);

void sys_init_All(void);
void sys_init_Part(void);

void sys_exec_All(void);
void sys_exec_Part(void);


// 开始 定时器任务，需要一直运行的：
void init_Timer_TaskTmr(void);

#endif  //__mRunTask_C__
/*================= 公有函数声明 ====================================*/
//EX_mRunTask 

extern  void SysInit_WhenPowerOn(void);
extern  void SysInit_WhenReset(void);
extern  void Sys_Exec(void);

extern  void RunCycle_OnTime(void);
extern  void RunCycle_WhenFlashWaitIng(void);



/******************************************************************************
// END :
******************************************************************************/
#endif // __mRunTask_H__

