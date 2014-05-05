#ifndef __CanIntCouple_H__
#define __CanIntCouple_H__
/******************************************************************************
* @file    CanIntCouple.h
* @author  yx
* @version V1.0
* @date    2013-07-25
* @brief   
* 
#include  "CanIntCouple.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

/*================= extern ============================================*/
#ifdef  __CanIntCouple_C__
#define EX_CanIntCouple
#else
#define EX_CanIntCouple extern 
#endif
/*================= 常数 ============================================*/
//#define 
/*================= 结构体定义 ======================================*/

/*================= 公有结构变量声明 ================================*/

/*================= 私有函数声明 ====================================*/
#ifdef  __CanIntCouple_C__

#endif  //__CanIntCouple_C__
/*================= 公有函数声明 ====================================*/
//EX_CanIntCouple 

//OUT: 中断的id由 enable变为disable的 bit。
extern U32 IntDisable_May_CanAdd(void);
//IN:  中断的id由 enable变为disable的 bit，现在恢复enable的状态。
extern void IntEnable_May_CanAdd(U32 whichDisable);

extern U32 IntDisable_May_iCanAdd(void);
extern void IntEnable_May_iCanAdd(U32 whichDisable);
extern U32 IntDisable_May_eCanAdd(void);
extern void IntEnable_May_eCanAdd(U32 whichDisable);


/******************************************************************************
// END :
******************************************************************************/
#endif // __CanIntCouple_H__

