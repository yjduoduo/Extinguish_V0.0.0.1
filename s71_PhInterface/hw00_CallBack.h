#ifndef __hw00_CallBack_H__
#define __hw00_CallBack_H__
/******************************************************************************
* @file    hw00_CallBack.h
* @author  yx
* @version V1.0
* @date    2012-01-05
* @brief   
* 
#include  "hw00_CallBack.h"
******************************************************************************/

#include  "prjCompileCon.h"

/*================= extern ============================================*/
#ifdef  __hw00_CallBack_C__
#define EX_hw00_CallBack
#else
#define EX_hw00_CallBack extern 
#endif

/*================= ���� ============================================*/


/*================= �ṹ�嶨�� ======================================*/

/*================= ���нṹ�������� ================================*/

/*================= ���к������� ====================================*/
// EX_hw00_CallBack 

extern void CallBack_RunInFlashWait(void);

//IN: enum emTmrDriveId
extern void CallBack_Tmr_Intr(U8 tmrDriveId); // ��ʱ�ж�


// * FUNC: // Uart.driver.CallBack;
// *   IN:
// *  OUT: UartHd_Interface.c 
extern void CallBack_Uart_RecNew(U8 uartPeriId, U8 *pRxByte, U8 byteTotal);
extern BOOL CallBack_Uart_TxFollowOne(U8 uartPeriId, U8 *pRtnByte);
extern BOOL bCallBack_Uart_TxBufEmpty(U8 uartPeriId);


// * FUNC: // CAN.driver.CallBack;
// *   IN:
// *  OUT: CanHd_Interface.c 
extern void CallBack_Can_setTxIng(U8 canPeriId);

//extern void CallBack_Can_RecNew(U8 canPeriId, U8 canMaskBuf, 
//								CAN_MSG_Type *pCanMsg);
extern void CallBack_Can_SendSucc(U8 canPeriId);
extern void CallBack_Can_SendFailed(U8 canPeriId);
extern void CallBack_Can_NoAck(U8 canPeriId);
extern void CallBack_Can_BitError(U8 canPeriId);
extern void CallBack_Can_BusOff(U8 canPeriId);

/******************************************************************************
// END :
******************************************************************************/
#endif // __hw00_CallBack_H__

