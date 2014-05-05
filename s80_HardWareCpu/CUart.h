/*
;*********************************************************************************************************
;*                                                
;*                            ¶ÔÏó: CUart
;*
;*                        (c) Copyright 2010-2018, ½¯Ñ©Ã·
;*                              All Rights Reserved
;*                                    Ver1.0
;* File : CUart.h
;* By   : ½¯Ñ©Ã·
;* Ê±¼ä : 2010-10-11
;*********************************************************************************************************
;*/
//#include  "CUart.h"

#ifndef CUart_H
#define CUart_H	  

#include  "prjCompileCon.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <LPC177x_8x.h>
#include "lpc_types.h"

// #include <GUI.h>	
#include  "core_cm3.h"

#ifdef  CUart_C
#define EX_CUart
#else
#define EX_CUart extern 
#endif

/*******************************************************************/
/******************       È«¾Ö³£Á¿¶¨Òå?    *********************/
/*******************************************************************/

//typedef unsigned char  uint8_t; 	//ÎÞ·ûºÅ8Î»ÕûÐÍ±äÁ¿
//typedef unsigned short uint16_t;	//ÎÞ·ûºÅ16Î»ÕûÐÍ±äÁ¿
//typedef unsigned long  uint32_t;	//ÎÞ·ûºÅ32Î»ÕûÐÍ±äÁ¿

/*******************************************************************/
/******************       È«¾Ö³£Á¿¶¨Òåý     *********************/
/*******************************************************************/
//constant
#define UART_TEST_NUM		0

#define MODEM_TEST	0

#define IER_RBR		0x01
#define IER_THRE	0x02
#define IER_RLS		0x04

#define IIR_PEND	0x01
#define IIR_RLS		0x03
#define IIR_RDA		0x02
#define IIR_CTI		0x06
#define IIR_THRE	0x01

#define LSR_RDR		0x01
#define LSR_OE		0x02
#define LSR_PE		0x04
#define LSR_FE		0x08
#define LSR_BI		0x10
#define LSR_THRE	0x20
#define LSR_TEMT	0x40
#define LSR_RXFE	0x80

#if (UART_TEST_NUM == 0)
#define	_LPC_UART			(LPC_UART_TypeDef *)LPC_UART0
#define _UART_IRQ			UART0_IRQn
#define _UART_IRQHander		UART0_IRQHandler
#elif (UART_TEST_NUM == 1)
#define _LPC_UART			(LPC_UART_TypeDef *)LPC_UART1
#define _UART_IRQ			UART1_IRQn
#define _UART_IRQHander		UART1_IRQHandler
#elif (UART_TEST_NUM == 2)
#define _LPC_UART			LPC_UART2
#define _UART_IRQ			UART2_IRQn
#define _UART_IRQHander		UART2_IRQHandler
#endif
/* buffer size definition */
#define UART_RING_BUFSIZE  256

/* Buf mask */
#define __BUF_MASK (UART_RING_BUFSIZE-1)
/* Check buf is full or not */
#define __BUF_IS_FULL(head, tail) ((tail&__BUF_MASK)==((head+1)&__BUF_MASK))
/* Check buf will be full in next receiving or not */
#define __BUF_WILL_FULL(head, tail) ((tail&__BUF_MASK)==((head+2)&__BUF_MASK))
/* Check buf is empty */
#define __BUF_IS_EMPTY(head, tail) ((head&__BUF_MASK)==(tail&__BUF_MASK))
/* Reset buf */
#define __BUF_RESET(bufidx)	(bufidx=0)
#define __BUF_INCR(bufidx)	(bufidx=(bufidx+1)&__BUF_MASK)

/*******************************************************************/
/******************       Êý¾Ý½á¹¹¶¨Òåý     *********************/
/*******************************************************************/
typedef struct
{
    __IO uint32_t tx_head;                /*!< UART Tx ring buffer head index */
    __IO uint32_t tx_tail;                /*!< UART Tx ring buffer tail index */
    __IO uint32_t rx_head;                /*!< UART Rx ring buffer head index */
    __IO uint32_t rx_tail;                /*!< UART Rx ring buffer tail index */
    __IO uint8_t  tx[UART_RING_BUFSIZE];  /*!< UART Tx data ring buffer */
    __IO uint8_t  rx[UART_RING_BUFSIZE];  /*!< UART Rx data ring buffer */
} UART_RING_BUFFER_T;


/*******************************************************************/
/****************     ¹«ÓÐ³ÉÔ±±äÁ¿,º¯Êý¼°³£Á¿     ******************/
/*******************************************************************/
//public:
EX_CUart   void   Init_CUart(void);    //³õÊ¼»¯

EX_CUart   void   UART0_IRQHandler(void);  
EX_CUart   void   UART1_IRQHandler(void);  

//EX_CUart  FlagStatus exitflag;
EX_CUart  FlagStatus UartRcvFlag;

EX_CUart   void   UART_IntErr(uint8_t bLSErrType);
EX_CUart   void   UART_IntTransmit(void);
EX_CUart   void   UART_IntReceive(void);  

//EX_CUart   void UartSend( uint32_t portNum, uint8_t *BufferPtr, uint32_t Length );

EX_CUart   uint32_t UARTReceive(LPC_UART_TypeDef *UARTPort, uint8_t *rxbuf, uint32_t buflen);
EX_CUart   uint32_t UARTSend(LPC_UART_TypeDef *UARTPort, uint8_t *txbuf, uint32_t buflen);
/*******************************************************************/
/********************* Ë½ÓÐ³ÉÔ±±äÁ¿,º¯Êý¼°³£Á¿    *******************/
/*******************************************************************/
//Private:
#ifdef  CUart_C


//volatile uint8_t UART0TxEmpty = 1, UART1TxEmpty = 1, UART2TxEmpty = 1, UART3TxEmpty = 1, UART4TxEmpty = 1;

 
// UART Ring buffer
UART_RING_BUFFER_T rb  __attribute__ ((section ("UART_RB_RAM"), zero_init));    ;

// Current Tx Interrupt enable state
__IO FlagStatus TxIntStat;

void   _UART_IRQHander(void);

#endif
#endif

