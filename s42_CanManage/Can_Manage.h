#ifndef __Can_Manage_H__
#define __Can_Manage_H__
/******************************************************************************
* @file    Can_Manage.h
* @author  yx
* @version V1.0
* @date    2013-09-09
* @brief   
* 
#include  "Can_Manage.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

/*================= extern ============================================*/
#ifdef  __Can_Manage_C__
#define EX_Can_Manage
#else
#define EX_Can_Manage extern 
#endif
/*================= ���� ============================================*/
//#define 
/*================= �ṹ�嶨�� ======================================*/

/*================= ���нṹ�������� ================================*/

/*================= ˽�к������� ====================================*/
#ifdef  __Can_Manage_C__

void can_rx_EvtFile(U8 can_id);
void can_rx_MesgFile(U8 can_id);
void can_rx_DataFrm(U8 can_id);

void Exec_Can_RxTask(U8 can_id);

void can_IorE_task_init(U8 can_id);
void canCheckError(U8 can_id);


#endif  //__Can_Manage_C__
/*================= ���к������� ====================================*/
//EX_Can_Manage 

extern void SetCanError(U8 can_id);
extern void ClrCanError(U8 can_id);
extern BOOL bCanError(U8 can_id);

extern void CanTxSuccInc(U8 can_id);
extern void CanRxSuccInc(U8 can_id);
extern void canTxRxSucc_Clr(U8 can_id);
extern BOOL bCanTxRxZero(U8 can_id);

extern void SetCanReInit(U8 can_id);
extern void ClrCanReInit(U8 can_id);
extern BOOL bCanReInitIng(U8 can_id);

/*================= ���к������� ====================================*/
//EX_Can_Manage 

extern void Can_Task_Init(void);
extern void Can_Task_Exec(void);

// �жϽ��յ�֡������ת�������У���������������
// ��Ҫ��ʱ����
// ���ʱ��Ϊ  (һ֡����ʱ�� * (CanHd_IntrRxBuf_MAX-2))
extern void CanIntrBuf_Move(void);

/******************************************************************************
// END :
******************************************************************************/
#endif // __Can_Manage_H__

