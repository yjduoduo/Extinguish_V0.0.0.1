#define __UartHd_Interface_C__
/******************************************************************************
* @file    UartHd_Interface.c
* @author  yx
* @version V1.0
* @date    2013-08-23
* @brief   
* 
******************************************************************************/
#include  "UartHd_Interface.h"

#include  "hw11_Uart.h"

#include  "bufCircle.h"
#include  "hw00_HdInt.h"
//#include "incFile.h"	


/*================= 常数 ============================================*/

/*================= 结构定义 ========================================*/

typedef struct{
	U8 uart_id;
	U8 uartPeriId;
	U8 hdPhInt_id; // int
	U32 bps;
}TUartProp_st;

const TUartProp_st cstUartPeriId[U_UART_ID_MAX+1] = 
{
	{U_Uart_Download_ID, U_PERI_UART0_ID, U_Hd_Int_UART_DownLoad, 2400}, // 
		
	{U_Uart_Download_ID, U_PERI_UART0_ID, U_Hd_Int_UART_DownLoad, 2400}, // default , 参考 U_UART_ID_Default
};
/*================= 私有结构变量声明 ================================*/
#define U_UartDownLoad_Tx_Buf_Max    100
#define U_UartDownLoad_Rx_Buf_Max    100

TBufCircle  stCircleUartTx;
U8 UartDownLoadBufTx[U_UartDownLoad_Tx_Buf_Max];
TBufCircle  stCircleUartRx;
U8 UartDownLoadBufRx[U_UartDownLoad_Rx_Buf_Max];

/*================= 公有函数声明 ====================================*/

/*================= 私有函数声明 ====================================*/

/*=================  ================================================*/
		
/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

void Uart_Hd_Init(U8 uart_id)
{
U8 hdPhInt_id;

	if(uart_id >= U_UART_ID_MAX)
	{
		return;
	}
	hdPhInt_id = cstUartPeriId[uart_id].hdPhInt_id;
	if(bGet_SysInt_Hd_Open(hdPhInt_id))
	{
		Uart_Hd_Close(uart_id);
	}
	Init_CUart(cstUartPeriId[uart_id].uartPeriId, 
			    cstUartPeriId[uart_id].bps);
	
	Notify_SysInt_Hd_Open(cstUartPeriId[uart_id].hdPhInt_id);
	MyInt_Enable(cstUartPeriId[uart_id].hdPhInt_id);
}
	

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
void Uart_Hd_Close(U8 uart_id)
{
U8 hdPhInt_id;
	
	if(uart_id >= U_UART_ID_MAX)
	{
		return;
	}
	hdPhInt_id = cstUartPeriId[uart_id].hdPhInt_id;
	if(!bGet_SysInt_Hd_Open(hdPhInt_id))
	{
		return;
	}
	MyInt_Disable(hdPhInt_id);
	
	Close_CUart(cstUartPeriId[uart_id].uartPeriId);
	
	Notify_SysInt_Hd_Close(hdPhInt_id);
	
}

/******************************************************************************
* FUNC: // Int:
*   IN:
*  OUT: 
******************************************************************************/
void UartHd_Int_Enable(U8 uart_id)
{
	if(uart_id >= U_UART_ID_MAX)
	{
		return;
	}
	UartRegi_Int_Enable(cstUartPeriId[uart_id].uartPeriId);
}

void UartHd_Int_Disable(U8 uart_id)
{
	if(uart_id >= U_UART_ID_MAX)
	{
		return;
	}
	UartRegi_Int_Disable(cstUartPeriId[uart_id].uartPeriId);
}

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

void Uart_HdAndBuf_Init(U8 uart_id)
{
	Uart_Hd_ClrBufTx(uart_id);
	Uart_Hd_ClrBufRx(uart_id);
	Uart_Hd_Init(uart_id);
}

void Uart_All_HdAndBuf_Init(void)
{
U8 uart_id;
	
	for(uart_id=0; uart_id<U_UART_ID_MAX; uart_id++)
	{
		Uart_HdAndBuf_Init(uart_id);
	}
}

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

void Uart_Hd_ClrBufTx(U8 uart_id)
{
	BufCircleIni(U_UartDownLoad_Tx_Buf_Max, &stCircleUartTx);
}

void Uart_Hd_ClrBufRx(U8 uart_id)
{
	BufCircleIni(U_UartDownLoad_Rx_Buf_Max, &stCircleUartRx);
}

/******************************************************************************
* FUNC: // 应用层 与 硬件 的canId 的对应关系：
*   IN:
*  OUT: 
******************************************************************************/

U8 GetUartPeriId_FromUartId(U8 uart_id)
{
	if(uart_id >= U_UART_ID_MAX)
	{
		return cstUartPeriId[U_UART_ID_MAX].uartPeriId;
	}
	return cstUartPeriId[uart_id].uartPeriId;
}

U8 GetUartId_FromUartPeriId(U8 uartPeriId)
{
U8 uart_id;

	for(uart_id=0; uart_id<U_UART_ID_MAX; uart_id++)
	{
		if(cstUartPeriId[uart_id].uartPeriId == uartPeriId)
		{
			break;
		}
	}
	if(uart_id >= U_UART_ID_MAX)
	{
		return cstUartPeriId[U_UART_ID_Default].uart_id;
	}
	return uart_id;
}


/******************************************************************************
* FUNC: // tx
*   IN:
*  OUT: 
******************************************************************************/

BOOL UartHd_LoadTxBuf(U8 uart_id, U8 *pByte, U32 byteTotal)
{
	CircleCopyByte(&UartDownLoadBufTx[0], pByte, byteTotal, 
				  &stCircleUartTx);
	return TRUE;
}

void UartHd_TxByteStart(U8 uart_id)
{
U8 hdPhInt_id;

	hdPhInt_id = GetUartPeriId_FromUartId(uart_id);
	HwUart_SendStart(hdPhInt_id);
	
}

BOOL UartHd_TxByteFollow(U8 uart_id, U8 *pRtnByte)
{
	U32 out;
	if(bEmptyBufCircle(&stCircleUartTx))
	{
		return FALSE;
	}
	out = BufCircle_GetOut(&stCircleUartTx);
	*pRtnByte = UartDownLoadBufTx[out];
	BufCircle_OutInc(&stCircleUartTx);
	
	return TRUE;
}

BOOL UartHd_TxBufEmpty(U8 uart_id)
{
	return (bEmptyBufCircle(&stCircleUartTx));
}

/******************************************************************************
* FUNC: // rx
*   IN:
*  OUT: 
******************************************************************************/
void UartHd_Rec(U8 uart_id, U8 *pByte, U32 byteTotal)
{
	if(bFullBufCircle(&stCircleUartRx))
	{
		return;
	}
	
	CircleCopyByte(&UartDownLoadBufRx[0], pByte, byteTotal, 
				  &stCircleUartRx);
	
}


/******************************************************************************
* FUNC: // END
*   IN:
*  OUT: 
******************************************************************************/
