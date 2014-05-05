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
/*================= ���� ============================================*/
//#define 
/*================= �ṹ�嶨�� ======================================*/

/*================= ���нṹ�������� ================================*/

/*================= ˽�к������� ====================================*/
#ifdef  __CanTxTask_C__

// can����~ �����н���Ķ�ʱ��
void tmr_CanTxStart(U8 can_id);
void tmr_CanTxStop(U8 can_id);
BOOL bTmr_CanTxArrived(U8 can_id);

// ����ʧ�ܵĴ�����
void canTxFailed_inc(U8 can_id);
void canTxFailed_clr(U8 can_id);
BOOL bCanTxFailed_Max(U8 can_id);


// ��ⷢ�ͽ����״̬��
// TRUE=δ���ж���������һ֡δ���ͳɹ���
BOOL checkNowTxFailed(U8 can_id);

#endif  //__CanTxTask_C__
/*================= ���к������� ====================================*/
//EX_CanTxTask 


extern void Init_Can_TxTask(void);
extern void Exec_Can_TxTask(U8 can_id);


// ���taskIdδ���͵�֡��
extern void CanMange_ClrTaskIdTx(U8 can_id, U8 taskId);

// *Master: CanBufLib 
extern BOOL bCanTx_Tmr_Arrived(U8 can_id);
/******************************************************************************
// END :
******************************************************************************/
#endif // __CanTxTask_H__

