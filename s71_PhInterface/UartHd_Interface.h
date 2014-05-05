#ifndef __UartHd_Interface_H__
#define __UartHd_Interface_H__
/******************************************************************************
* @file    UartHd_Interface.h
* @author  yx
* @version V1.0
* @date    2013-08-23
* @brief   
* 
#include  "UartHd_Interface.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

/*================= extern ============================================*/
#ifdef  __UartHd_Interface_C__
#define EX_UartHd_Interface
#else
#define EX_UartHd_Interface extern 
#endif
/*================= ���� ============================================*/

enum emUartLogicId{  // uint8 uart_id;
	U_Uart_Download_ID = 0, // ���漰Ӳ��
};
#define U_UART_ID_MAX  1

#define U_UART_ID_Default  U_Uart_Download_ID
/*================= ���� ============================================*/


/*================= �ṹ�嶨�� ======================================*/

/*================= ���нṹ�������� ================================*/
/*
typedef struct{
	U8 sequStart;
}TStruct_st;
TStruct_st stStruct;
*/

/*-----------------    ----------------------------------*/

/*================= ˽�к������� ====================================*/
#ifdef  __UartHd_Interface_C__

#endif  //__UartHd_Interface_C__
/*================= ���к������� ====================================*/
//EX_UartHd_Interface 

// Int:
extern void UartHd_Int_Enable(U8 uart_id);
extern void UartHd_Int_Disable(U8 uart_id);


// Ӧ�ò� �� Ӳ�� ��uartId �Ķ�Ӧ��ϵ��
extern U8 GetUartPeriId_FromUartId(U8 uart_id);
extern U8 GetUartId_FromUartPeriId(U8 uartPeriId);

// init:
extern void Uart_HdAndBuf_Init(U8 uart_id);
extern void Uart_Hd_Init(U8 uart_id);
extern void Uart_Hd_Close(U8 uart_id);
extern void Uart_All_HdAndBuf_Init(void);

extern void Uart_Hd_ClrBufTx(U8 uart_id);
extern void Uart_Hd_ClrBufRx(U8 uart_id);

// Send:
extern BOOL UartHd_LoadTxBuf(U8 uart_id, U8 *pByte, U32 byteTotal);
extern void UartHd_TxByteStart(U8 uart_id);
extern BOOL UartHd_TxByteFollow(U8 uart_id, U8 *pRtnByte);
extern BOOL UartHd_TxBufEmpty(U8 uart_id);
// rx:
extern void UartHd_Rec(U8 uart_id, U8 *pByte, U32 byteTotal);

/******************************************************************************
// END :
******************************************************************************/
#endif // __UartHd_Interface_H__

