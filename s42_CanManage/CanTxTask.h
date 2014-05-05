#ifndef __CanTxTask_H__
#define __CanTxTask_H__
/******************************************************************************
* @file    CanTxTask.h
* @author  yx
* @version V1.0
* @date    2013-09-09
* @brief   
* 
#include  "CanTxTask.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

/*================= extern ============================================*/
#ifdef  __CanTxTask_C__
#define EX_CanTxTask
#else
#define EX_CanTxTask extern 
#endif
/*================= 常数 ============================================*/
//#define 
/*================= 结构体定义 ======================================*/

/*================= 公有结构变量声明 ================================*/

/*================= 私有函数声明 ====================================*/
#ifdef  __CanTxTask_C__

// can发送~ 发送有结果的定时：
void tmr_CanTxStart(U8 can_id);
void tmr_CanTxStop(U8 can_id);
BOOL bTmr_CanTxArrived(U8 can_id);

// 发送失败的次数：
void canTxFailed_inc(U8 can_id);
void canTxFailed_clr(U8 can_id);
BOOL bCanTxFailed_Max(U8 can_id);


// 检测发送结果的状态：
// TRUE=未到判定出错，但上一帧未发送成功。
BOOL checkNowTxFailed(U8 can_id);

#endif  //__CanTxTask_C__
/*================= 公有函数声明 ====================================*/
//EX_CanTxTask 


extern void Init_Can_TxTask(void);
extern void Exec_Can_TxTask(U8 can_id);


// 清除taskId未发送的帧：
extern void CanMange_ClrTaskIdTx(U8 can_id, U8 taskId);

// *Master: CanBufLib 
extern BOOL bCanTx_Tmr_Arrived(U8 can_id);
/******************************************************************************
// END :
******************************************************************************/
#endif // __CanTxTask_H__

