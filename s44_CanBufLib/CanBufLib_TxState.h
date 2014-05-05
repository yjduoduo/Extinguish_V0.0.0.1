#ifndef __CanBufLib_TxState_H__
#define __CanBufLib_TxState_H__
/******************************************************************************
* @file    CanBufLib_TxState.h  // #include  "can22_TxState.h"
* @author  yx
* @version V1.0
* @date    2013-07-24
* @brief   
* 
#include  "CanBufLib_TxState.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

/*================= 公有函数声明-lib外部 ====================================*/
//EX_can22_TxState 

//注意在出错重发前也用一次，以免检测到txIng状态。
extern void CanHdTxState_Init(void);
extern void CanHdTxState_OneCanId_Init(U8 can_id);

//can发送一帧：
//can正在发送：
// bTxIng=1; bHaveResult=0;
extern void Set_CanHdTxState_Start(U8 can_id);
extern BOOL bCanHdTxState_Is_TxIng(U8 can_id);


//定时间内，未发送成功。
extern void Set_CanHdTxState_Failed(U8 can_id);
//定时间内，发送成功。
extern void Set_CanHdTxState_Succeed(U8 can_id);


extern BOOL bCanHdTxState_HaveResult(U8 can_id, U8 *pRtnSucceed);
//查询后自动 Clr_CanHdTxState_HaveResult
extern BOOL bCanHdTxState_Failed(U8 can_id);
extern BOOL bCanHdTxState_Succeed(U8 can_id);


extern void Clr_CanHdTxState_HaveResult(U8 can_id);

/******************************************************************************
// END :
******************************************************************************/
#endif // __CanBufLib_TxState_H__

