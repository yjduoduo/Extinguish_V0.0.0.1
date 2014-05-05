#ifndef __hw11_Uart_H__
#define __hw11_Uart_H__
/******************************************************************************
* @file    hw11_Uart.h
* @author  yx
* @version V1.0
* @date    2013-08-22
* @Cpu     LPC177x_8x   
* @brief   
* 
#include  "hw11_Uart.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

/*================= extern ============================================*/
#ifdef  __hw11_Uart_C__
#define EX_hw11_Uart
#else
#define EX_hw11_Uart extern 
#endif
/*================= 常数 ============================================*/

#define U_PERI_UART0_ID		  0  // U8 uartPeriId;

#define U_PERI_UART_ID_MAX		1

#define U_PERI_UART_Default		U_PERI_UART0_ID

/*================= 结构体定义 ======================================*/

/*================= 公有结构变量声明 ================================*/

/*================= 私有函数声明 ====================================*/
#ifdef  __hw11_Uart_C__
// void UART0_IRQHandler(void);
// void UART1_IRQHandler(void);
// void UART2_IRQHandler(void);

void uartCommon_IRQHandler(U8 uartPeriId);

void hwUart_Int_Receive(U8 uartPeriId);
void hwUart_Int_Transmit(U8 uartPeriId);
void hwUart_Int_Err(U8 uartPeriId, U8 bLSErrType);


#endif  //__hw11_Uart_C__
/*================= 公有函数声明 ====================================*/
//EX_hw11_Uart 

extern void Init_CUart(U8 uartPeriId, U32 mBps);
extern void Close_CUart(U8 uartPeriId);

//  Int:
extern void UartRegi_Int_Enable(U8 uartPeriId);
extern void UartRegi_Int_Disable(U8 uartPeriId);

extern void HwUart_SendStart(U8 uartPeriId);

extern U32 HwUart_Read_RxBuf(U8 uartPeriId, U8 *rxbuf, U32 buflen);

extern BOOL bHwUart_Busy(U8 uartPeriId);



/******************************************************************************
// END :
#include  "hw00_CallBack.h"
extern void CallBack_Uart_RecNew(U8 uartPeriId, U8 *pRxByte, U8 byteTotal);
extern BOOL CallBack_Uart_TxFollowOne(U8 uartPeriId, U8 *pRtnByte);
extern BOOL bCallBack_Uart_TxBufEmpty(U8 uartPeriId);
******************************************************************************/
#endif // __hw11_Uart_H__

