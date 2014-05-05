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

/*================= ���к�������-lib�ⲿ ====================================*/
//EX_can22_TxState 

//ע���ڳ����ط�ǰҲ��һ�Σ������⵽txIng״̬��
extern void CanHdTxState_Init(void);
extern void CanHdTxState_OneCanId_Init(U8 can_id);

//can����һ֡��
//can���ڷ��ͣ�
// bTxIng=1; bHaveResult=0;
extern void Set_CanHdTxState_Start(U8 can_id);
extern BOOL bCanHdTxState_Is_TxIng(U8 can_id);


//��ʱ���ڣ�δ���ͳɹ���
extern void Set_CanHdTxState_Failed(U8 can_id);
//��ʱ���ڣ����ͳɹ���
extern void Set_CanHdTxState_Succeed(U8 can_id);


extern BOOL bCanHdTxState_HaveResult(U8 can_id, U8 *pRtnSucceed);
//��ѯ���Զ� Clr_CanHdTxState_HaveResult
extern BOOL bCanHdTxState_Failed(U8 can_id);
extern BOOL bCanHdTxState_Succeed(U8 can_id);


extern void Clr_CanHdTxState_HaveResult(U8 can_id);

/******************************************************************************
// END :
******************************************************************************/
#endif // __CanBufLib_TxState_H__

