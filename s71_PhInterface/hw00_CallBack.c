
#define __hw00_CallBack_C__
/******************************************************************************
* @file    hw00_CallBack.c
* @author  yx
* @version V1.0
* @date    2012-01-05
* @brief   �����Ļص�������
* 
*  ԭ���ϣ���s14HardWareCpu������ļ��������������κδ����Ӳ����ֻ��CPU�ͺ��йء�
*	���жϱ���Ҫ֪ͨ��task�����ԼӴ��ļ���
******************************************************************************/
#include  "hw00_CallBack.h"
#include  "HdInterface.h"

#include  "prjBool.h"


// #include "incFile.h"	

#include  "canFrame.h"
#include  "CanHd_Interface.h"
#include  "hw10_Can.h"

#include  "UartHd_Interface.h"
// #include  "bufCan.h"

// #include  "tmrTick.h"

#include  "mRunTask.h"
// extern  void RunCycle_WhenFlashWaitIng(void);

/*================= ���� ============================================*/

/*================= �ṹ���� ========================================*/

/*================= ˽�нṹ�������� ================================*/

/*================= ���к������� ====================================*/






/*================= ˽�к������� ====================================*/

/*=================  ================================================*/

/******************************************************************************
* FUNC: //
*   IN:   enum emTmrDriveId
*  OUT: 
******************************************************************************/
//ϵͳtick����timer0.
void CallBack_Tmr_Intr(U8 tmrDriveId)
{
	MyTimer_IntrHander(tmrDriveId);
}


/******************************************************************************
* FUNC:   //�ȴ��ڼ����ִ��1cycle���洦��
		// flashдor Erase�ڼ䣬����read.
*   IN:   
*  OUT: 
******************************************************************************/

void CallBack_RunInFlashWait(void)
{
	RunCycle_WhenFlashWaitIng();
}

/******************************************************************************
* FUNC: // Uart.driver.CallBack;
*   IN:
*  OUT: UartHd_Interface.c 
******************************************************************************/

void CallBack_Uart_RecNew(U8 uartPeriId, U8 *pRxByte, U8 byteTotal)
{
U8 uart_id;

	uart_id = GetUartId_FromUartPeriId(uartPeriId);
	UartHd_Rec(uart_id, pRxByte, byteTotal);
}


/******************************************************************************
* FUNC: // Uart.driver.CallBack;
******************************************************************************/
BOOL CallBack_Uart_TxFollowOne(U8 uartPeriId, U8 *pRtnByte)
{
U8 uart_id;

	uart_id = GetUartId_FromUartPeriId(uartPeriId);
	
	
	return UartHd_TxByteFollow(uart_id, pRtnByte);
}

/******************************************************************************
* FUNC: // Uart.driver.CallBack;
******************************************************************************/
BOOL bCallBack_Uart_TxBufEmpty(U8 uartPeriId)
{
U8 uart_id;

	uart_id = GetUartId_FromUartPeriId(uartPeriId);
	
	return UartHd_TxBufEmpty(uart_id);
}

/******************************************************************************
* FUNC: // CAN.driver.CallBack;
*   IN:
*  OUT: CanHd_Interface.c 
******************************************************************************/
extern void CanFrmType_MsgToFrm(CAN_MSG_Type *pMsg, THdCanFrame_st *pFrm);

/******************************************************************************
* FUNC: // ����
******************************************************************************/

extern BOOL CanIntBuf_Add(U8 can_id, U8 canMaskChannel, CAN_MSG_Type *pMsg);
extern void CanRxSuccInc(U8 can_id);

void CallBack_Can_RecNew(U8 canPeriId, U8 canMaskBuf, 
								CAN_MSG_Type *pCanMsg)
{
U8 can_id;

	can_id = GetCanId_FromCanPeriId(canPeriId);
	
	//
	// CanHd_IorE_Rec(can_id, canMaskBuf, pCanMsg);
	CanIntBuf_Add(can_id, canMaskBuf, pCanMsg);
	CanRxSuccInc(can_id);
	
}

/******************************************************************************
* FUNC: // ����, ��CAN����״̬
******************************************************************************/

void CallBack_Can_setTxIng(U8 canPeriId)
{
U8 can_id;
	can_id = GetCanId_FromCanPeriId(canPeriId);
	CanHd_IorE_setTxIng(can_id);	
}


void CallBack_Can_SendSucc(U8 canPeriId)
{
U8 can_id;
	can_id = GetCanId_FromCanPeriId(canPeriId);
	CanHd_IorE_TxSucc(can_id);
	
	// ICanTxOneFrmSucc();
	
	// ICanTxNewFrm(U_CallFromIntr);
	
}

void CallBack_Can_SendFailed(U8 canPeriId)
{
U8 can_id;
	can_id = GetCanId_FromCanPeriId(canPeriId);
	CanHd_IorE_TxFailed(can_id);	
}


void CallBack_Can_NoAck(U8 canPeriId)
{
U8 can_id;
	can_id = GetCanId_FromCanPeriId(canPeriId);
	CanHd_IorE_NoAck(can_id);	
}

void CallBack_Can_BitError(U8 canPeriId)
{
U8 can_id;
	can_id = GetCanId_FromCanPeriId(canPeriId);
	CanHd_IorE_bitError(can_id);	
}

void CallBack_Can_BusOff(U8 canPeriId)
{
U8 can_id;
	can_id = GetCanId_FromCanPeriId(canPeriId);
	CanHd_IorE_BusOff(can_id);	
}



/******************************************************************************
* FUNC: // END 
*   IN:
*  OUT: 
******************************************************************************/

