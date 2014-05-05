#ifndef __hw10_Can_H__
#define __hw10_Can_H__
/******************************************************************************
* @file    hw10_Can.h
* @author  yx
* @version V1.0
* @date    2013-07-01
* @Cpu     LPC177x_8x   
* @brief   
* 
#include  "hw10_Can.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

#include  "lpc177x_8x_can.h" 
#include  "LPC177x_8x.h"

/*================= extern ============================================*/
#ifdef  __hw10_Can_C__
#define EX_hw10_Can
#else
#define EX_hw10_Can extern 
#endif
/*================= ���� ============================================*/

#define U_PERI_CAN1_ID		  (CAN_1) // ֻ��������
#define U_PERI_CAN2_ID		  (CAN_2) // ��Ҫ�Ķ�

/*================= �ṹ�嶨�� ======================================*/

/*================= ���нṹ�������� ================================*/
/*================= ˽�к�������- ���� ====================================*/
#ifdef  __hw10_Can_C__

	#if U_SYS_Test_CanHw == 1


void recordIntStatuInit(U8 canPeriId);
void recordInsStatus(U8 canPeriId, U32 IntStatus);
	#endif // U_SYS_Test_CanHw 

#endif  //__hw10_Can_C__
/*================= ˽�к������� ====================================*/
#ifdef  __hw10_Can_C__

void canRegi_PeriId_Clr_MsgTxRx(U8 canPeriId);
void canRegi_buf_Clr_MsgTxRx(U8 peri_can_buf_id);
void canRegi_Clr_1Msg(CAN_MSG_Type *pMsg);

CAN_MSG_Type *pGetCanRegi_RxBuf(U8 canPeriId);
U8 canRegi_GetBuf_FromPeriId(U8 canPeriId);

extern void canRegi_task_SetTxIdle(U8 canPeriId);
extern void canRegi_task_ClrTxIdle(U8 canPeriId);
extern unsigned char bCanRegi_task_TxIdle(U8 canPeriId);

void canRegi_ArbitrationLost_IntSet(U8 canPeriId);
void canRegi_BusError_IntSet(U8 canPeriId);
void canRegi_ErrorWarning_IntSet(U8 canPeriId);
void canRegi_JdgError(U8 canPeriId, U32 IntStatus);

// ���� ���� �� error����
void canRegi_Interupt(U8 canPeriId); // �жϴ���

#endif  //__hw10_Can_C__
/*================= ���к������� ====================================*/
//EX_hw10_Can 

// IN: canPeriId��lpc177x_8x_can.h�ﶨ���id; U_PERI_CAN1_ID, U_PERI_CAN2_ID
// IN: baudrate_us, �����ʣ���λus. ���� 1bit�ĳ��ȡ�
extern void CanRegi_Init(U8 canPeriId, U32 baudrate_us);
extern void CanRegi_Close(U8 canPeriId);

// Int:
extern void CanRegi_Int_Enable(U8 canPeriId);
extern void CanRegi_Int_Disable(U8 canPeriId);

// get ����͵�һ֡��driver�ṹ
extern CAN_MSG_Type *pGetCanRegi_TxBuf(U8 canPeriId);

// �ж�CAN�Ĵ������Ƿ����ڷ���
extern BOOL bCanRegi_Tx_Idle(U8 canPeriId);

// void  CAN_IRQHandler(void);  // �жϴ���

// ����: �ж� can��Tx״̬�Ĵ�����
extern BOOL CanRegi_Send(U8 canPeriId, CAN_MSG_Type *pMsg);


/******************************************************************************
// END :
******************************************************************************/
#endif // __hw10_Can_H__

