#define __hw11_Uart_C__
/******************************************************************************
* @file    hw11_Uart.c
* @author  yx
* @version V1.0
* @date    2013-08-22
* @Cpu     LPC177x_8x   
* @brief   
* 
******************************************************************************/
#include  "hw11_Uart.h"

#include  "lpc177x_8x_uart.h" 
#include  "LPC177x_8x.h" 

#include  "hwEx10_PinDef.h"

#include  "hw00_CallBack.h"
//#include "incFile.h"	


/*================= 常数 ============================================*/

/*================= 结构定义 ========================================*/
typedef struct{
	U8 uart_peri;
	LPC_UART_TypeDef *pUart;
	IRQn_Type  IRQn;
}TUartPeriDef_st;

// 只表明对应关系。变uart时，还是要注意，尤其是中断。
const TUartPeriDef_st cstUartPeriDef[U_PERI_UART_ID_MAX+1] = 
{
	{U_PERI_UART0_ID, (LPC_UART_TypeDef *)LPC_UART0, UART0_IRQn}, // 
		
	// default , 参考 U_PERI_UART_Default
	{U_PERI_UART0_ID, (LPC_UART_TypeDef *)LPC_UART0, UART0_IRQn}, 
};
/*================= 私有结构变量声明 ================================*/
U8 TxIntStat[U_PERI_UART_ID_MAX];
U8 UartRcvFlag[U_PERI_UART_ID_MAX];
/*================= 公有函数声明 ====================================*/

/*================= 私有函数声明 ====================================*/

/*=================  ================================================*/
		
/******************************************************************************
* FUNC: //
*   IN: mBps= bits/s
*  OUT: 
******************************************************************************/

void Init_CUart(U8 uartPeriId, U32 mBps)
{  
UART_CFG_Type 		UARTConfigStruct;
UART_FIFO_CFG_Type 	UARTFIFOConfigStruct;
LPC_UART_TypeDef 	*pNowUart;

	if(uartPeriId == U_PERI_UART0_ID)
		IniPinFunc_Uart0();
	else
		return;
	
	pNowUart = cstUartPeriDef[uartPeriId].pUart;
	
	//  Initialize UART Configuration parameter structure
	// UART_ConfigStructInit(&UARTConfigStruct);
	UARTConfigStruct.Baud_rate = mBps;          // Baudrate = 
	UARTConfigStruct.Databits = UART_DATABIT_8; // 8 data bit
	UARTConfigStruct.Parity = UART_PARITY_NONE; // None parity
	UARTConfigStruct.Stopbits = UART_STOPBIT_1; // 1 Stop bit
	
	// Initialize UART0 peripheral with given to corresponding parameter
	UART_Init(pNowUart, &UARTConfigStruct);


	/* Initialize FIFOConfigStruct to default state:
	 * 				- FIFO_DMAMode = DISABLE
	 * 				- FIFO_Level = UART_FIFO_TRGLEV0  // 1个字节rx中断
	 * 				- FIFO_ResetRxBuf = ENABLE
	 * 				- FIFO_ResetTxBuf = ENABLE
	 * 				- FIFO_State = ENABLE
	 */
	UART_FIFOConfigStructInit(&UARTFIFOConfigStruct);

	// Initialize FIFO for UART0 peripheral
	UART_FIFOConfig(pNowUart, &UARTFIFOConfigStruct);


	// Enable UART Transmit
	UART_TxCmd(pNowUart, ENABLE);

    /* Enable UART Rx interrupt */
	UART_IntConfig(pNowUart, UART_INTCFG_RBR, ENABLE);
	/* Enable UART line status interrupt */
	UART_IntConfig(pNowUart, UART_INTCFG_RLS, ENABLE);
	/*
	 * Do not enable transmit interrupt here, since it is handled by
	 * UART_Send() function, just to reset Tx Interrupt state for the
	 * first time
	 */
	TxIntStat[uartPeriId] = RESET;

	

    /* preemption = 1, sub-priority = 1 */
    NVIC_SetPriority(cstUartPeriDef[uartPeriId].IRQn, ((0x01<<3)|0x01));

	  /* Enable Interrupt for UART0 channel */
    NVIC_EnableIRQ(cstUartPeriDef[uartPeriId].IRQn);
	
	  // reset exit flag
//	  exitflag = RESET; 
   UartRcvFlag[uartPeriId] = RESET; 
}  

/******************************************************************************
* FUNC: // 
*   IN: uartPeriId: U_PERI_UART_ID_MAX
*  OUT:  
******************************************************************************/
void Close_CUart(U8 uartPeriId)
{
LPC_UART_TypeDef 	*pNowUart;

	if(uartPeriId >= U_PERI_UART_ID_MAX)
	{
		return;
	}
	UartRegi_Int_Disable(uartPeriId);
	
	pNowUart = cstUartPeriDef[uartPeriId].pUart;
	
	UART_DeInit(pNowUart);
}

/******************************************************************************
* FUNC: //  Int:
*   IN: uartPeriId: U_PERI_UART_ID_MAX
*  OUT:  
******************************************************************************/
void UartRegi_Int_Enable(U8 uartPeriId)
{
	if(uartPeriId >= U_PERI_UART_ID_MAX)
	{
		return;
	}
	NVIC_EnableIRQ(cstUartPeriDef[uartPeriId].IRQn);
}

void UartRegi_Int_Disable(U8 uartPeriId)
{
	if(uartPeriId >= U_PERI_UART_ID_MAX)
	{
		return;
	}
	NVIC_DisableIRQ(cstUartPeriDef[uartPeriId].IRQn);
}

/*********************************************************************//**
 * @brief		UART0 interrupt handler sub-routine
 * @param[in]	None
 * @return 		None
 **********************************************************************/
void UART0_IRQHandler(void)
{
	uartCommon_IRQHandler(U_PERI_UART0_ID);
}
void UART1_IRQHandler(void)
{
	//uartCommon_IRQHandler(U_PERI_UART1_ID);
}
void UART2_IRQHandler(void)
{
	//uartCommon_IRQHandler(U_PERI_UART2_ID);
}

/******************************************************************************
* FUNC: // 
******************************************************************************/
void uartCommon_IRQHandler(U8 uartPeriId)
{
U32 intsrc, tmp, tmp1;
LPC_UART_TypeDef 	*pNowUart;
  
	if(uartPeriId >= U_PERI_UART_ID_MAX)
		return;
	pNowUart = cstUartPeriDef[uartPeriId].pUart;
	
	/* Determine the interrupt source */
	intsrc = UART_GetIntId(pNowUart);
	tmp = intsrc & UART_IIR_INTID_MASK;

	// Receive Line Status
	if (tmp == UART_IIR_INTID_RLS){
		// Check line status
		tmp1 = UART_GetLineStatus(pNowUart);
		// Mask out the Receive Ready and Transmit Holding empty status
		tmp1 &= (UART_LSR_OE | UART_LSR_PE | UART_LSR_FE \
				| UART_LSR_BI | UART_LSR_RXFE);
		// If any error exist
		if (tmp1) 
		{
				hwUart_Int_Err(uartPeriId, tmp1);
		}
	}

	// Receive Data Available or Character time-out
	if ((tmp == UART_IIR_INTID_RDA) || (tmp == UART_IIR_INTID_CTI))
	{
			hwUart_Int_Receive(uartPeriId); 
		  //UartRcvFlag[uartPeriId] = SET;		
	}

	// Transmit Holding Empty
	if (tmp == UART_IIR_INTID_THRE)
	{
			hwUart_Int_Transmit(uartPeriId);
	}
	
}

/******************************************************************************
* FUNC: // 
*   IN:
*  OUT: 
******************************************************************************/

/********************************************************************//**
 * @brief 		UART receive function (ring buffer used)
 * @param[in]	None
 * @return 		None
 *********************************************************************/

extern void chkHd_Uart__UartRx(void);

void hwUart_Int_Receive(U8 uartPeriId)
{
U8 tmpc;
U32 rLen;
LPC_UART_TypeDef 	*pNowUart;

	if(uartPeriId >= U_PERI_UART_ID_MAX)
		return;
	pNowUart = cstUartPeriDef[uartPeriId].pUart;

	while(1)
	{
		// Call UART read function in UART driver
		rLen = UART_Receive(pNowUart, &tmpc, 1, NONE_BLOCKING);
		// If data received
		if (rLen)
		{
			UartRcvFlag[uartPeriId] = SET; 
			
			chkHd_Uart__UartRx();
			CallBack_Uart_RecNew(uartPeriId, &tmpc, 1);
		}
		// no more data
		else 
		{
			break;
		}
	}
}


/******************************************************************************
* FUNC: // 
*   IN:
*  OUT: 
******************************************************************************/

BOOL bHwUart_Busy(U8 uartPeriId)
{
LPC_UART_TypeDef 	*pNowUart;

	if(uartPeriId >= U_PERI_UART_ID_MAX)
		return FALSE;
	pNowUart = cstUartPeriDef[uartPeriId].pUart;
	
	return (UART_CheckBusy(pNowUart) == SET);
}


/********************************************************************//**
 * @brief 		UART transmit function (ring buffer used)
 * @param[in]	None
 * @return 		None
 *********************************************************************/
void hwUart_Int_Transmit(U8 uartPeriId)
{
LPC_UART_TypeDef 	*pNowUart;
U8 txByte;
U8 bTxState;

	if(uartPeriId >= U_PERI_UART_ID_MAX)
		return;
	pNowUart = cstUartPeriDef[uartPeriId].pUart;

    // Disable THRE interrupt
    UART_IntConfig(pNowUart, UART_INTCFG_THRE, DISABLE);

	/* Wait for FIFO buffer empty, transfer UART_TX_FIFO_SIZE bytes
	 * of data or break whenever ring buffers are empty */
	/* Wait until THR empty */
    while (UART_CheckBusy(pNowUart) == SET);
	
	
	if(!bCallBack_Uart_TxBufEmpty(uartPeriId))
	{
		CallBack_Uart_TxFollowOne(uartPeriId, &txByte);
		bTxState = UART_Send(pNowUart, &txByte, 1, NONE_BLOCKING);
		bTxState = bTxState;
		// 发送失败 未处理 
	}
	

    /* If there is no more data to send, disable the transmit
       interrupt - else enable it or keep it enabled */
	if(bCallBack_Uart_TxBufEmpty(uartPeriId))
	{
    	UART_IntConfig(pNowUart, UART_INTCFG_THRE, DISABLE);
    	// Reset Tx Interrupt state
    	TxIntStat[uartPeriId] = RESET;
    }
    else{
      	// Set Tx Interrupt state
		  TxIntStat[uartPeriId] = SET;
    	UART_IntConfig(pNowUart, UART_INTCFG_THRE, ENABLE);
    }
}


/*********************************************************************//**
 * @brief		UART Line Status Error
 * @param[in]	bLSErrType	UART Line Status Error Type
 * @return		None
 **********************************************************************/
void hwUart_Int_Err(U8 uartPeriId, U8 bLSErrType)
{
// LPC_UART_TypeDef 	*pNowUart;
	
	// if(uartPeriId >= U_PERI_UART_ID_MAX)
		// return;
	// pNowUart = cstUartPeriDef[uartPeriId].pUart;
}

/*-------------------------PRIVATE FUNCTIONS------------------------------*/
/*********************************************************************//**
 * @brief		UART transmit function for interrupt mode (using ring buffers)
 * @param[in]	UARTPort	Selected UART peripheral used to send data,
 * 				should be UART0
 * @param[out]	txbuf Pointer to Transmit buffer
 * @param[in]	buflen Length of Transmit buffer
 * @return 		Number of bytes actually sent to the ring buffer
 **********************************************************************/

void HwUart_SendStart(U8 uartPeriId)
{
LPC_UART_TypeDef *pNowUart;

	pNowUart = cstUartPeriDef[uartPeriId].pUart;
	
	/* Temporarily lock out UART transmit interrupts during this
	   read so the UART transmit interrupt won't cause problems
	   with the index values */
    UART_IntConfig(pNowUart, UART_INTCFG_THRE, DISABLE);


	/*
	 * Check if current Tx interrupt enable is reset,
	 * that means the Tx interrupt must be re-enabled
	 * due to call hwUart_Int_Transmit() function to trigger
	 * this interrupt type
	 */
	if (TxIntStat[uartPeriId] == RESET) 
	{
		  hwUart_Int_Transmit(uartPeriId);
	}
	/*
	 * Otherwise, re-enables Tx Interrupt
	 */
	else // 在此之前就是发送状态，所以当前的发送会跟在其后连续发送。
	{
		  UART_IntConfig(pNowUart, UART_INTCFG_THRE, ENABLE);
	}
	
}




/******************************************************************************
* FUNC: // 
*   IN:
*  OUT: 
******************************************************************************/


/******************************************************************************
* FUNC: // END
*   IN:
*  OUT: 
******************************************************************************/
