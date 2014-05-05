/*
;*********************************************************************************************************
;*                                                
;*                            ¶ÔÏó: hw16_IIC
;*
;*                        (c) Copyright 2010-2018, ½¯Ñ©Ã·
;*                              All Rights Reserved
;*                                    Ver1.0
;* File : hw16_IIC.h
* @Cpu     LPC177x_8x   
;* By   : ½¯Ñ©Ã·
;* Ê±¼ä : 2012-07-20
;*********************************************************************************************************
;*/
//#include  "hw16_IIC.h"

#ifndef hw16_IIC_H
#define hw16_IIC_H	  

#include  "prjCompileCon.h"
#include  "LPC177x_8x.h"
 


#ifdef  hw16_IIC_C
#define EX_hw16_IIC
#else
#define EX_hw16_IIC extern 
#endif

/*******************************************************************/
/******************       È«¾Ö³£Á¿¶¨Òåý     *********************/
/*******************************************************************/
//constant
//50MÖ÷Æµ   ²ÉÓÃ10ms Ê±ÖÓ
#define uint8    uint8_t
#define INT16U   uint16_t
#define INT32U   uint32_t

#define cFi2c1   100000   //100000

#define cUseI2cPort         0   //¶¨ÒåÓÃ»§Ê¹ÓÃµÄI2C¿Ú

#define FAST_MODE_PLUS      0
#define TEST_CHIP           0

#define I2C_PORT_NUM        3
#define BUFSIZE             16
#define MAX_I2cTIMEOUT         0x00FFFFFF
#define cMAX_I2cTIMEBit        0x10 

static LPC_I2C_TypeDef (* const LPC_I2C[I2C_PORT_NUM]) = { LPC_I2C0, LPC_I2C1, LPC_I2C2 };

#define I2CMASTER           0x01
#define I2CSLAVE            0x02

#define  cI2CAddr_Mega88      0x10	//Æ÷¼þµØÖ·  
#define  cI2CAddr_PCF8563     0xA2	//Æ÷¼þµØÖ·  

/*******************************************************************/
/******************       Êý¾Ý½á¹¹¶¨Òåý     *********************/
/*******************************************************************/

 
 
/*******************************************************************/
/********************* Ë½ÓÐ³ÉÔ±±äÁ¿,º¯Êý¼°³£Á¿    *******************/
/*******************************************************************/
//Private:
#ifdef  hw16_IIC_C 

#define RD_BIT              0x01

#define I2C_IDLE              0
#define I2C_STARTED           1
#define I2C_RESTARTED         2
#define I2C_REPEATED_START    3
#define DATA_ACK              4
#define DATA_NACK             5
#define I2C_BUSY              6
#define I2C_NO_DATA           7
#define I2C_NACK_ON_ADDRESS   8
#define I2C_NACK_ON_DATA      9
#define I2C_ARBITRATION_LOST  10
#define I2C_TIME_OUT          11
#define I2C_OK                12

#define I2CONSET_I2EN       (0x1<<6)  /* I2C Control Set Register */
#define I2CONSET_AA         (0x1<<2)
#define I2CONSET_SI         (0x1<<3)
#define I2CONSET_STO        (0x1<<4)
#define I2CONSET_STA        (0x1<<5)

#define I2CONCLR_AAC        (0x1<<2)  /* I2C Control clear Register */
#define I2CONCLR_SIC        (0x1<<3)
#define I2CONCLR_STAC       (0x1<<5)
#define I2CONCLR_I2ENC      (0x1<<6)

#define I2DAT_I2C           0x00000000  /* I2C Data Reg */
#define I2ADR_I2C           0x00000000  /* I2C Slave Address Reg */
#define I2SCLH_SCLH         0x00000180  /* I2C SCL Duty Cycle High Reg */
#define I2SCLL_SCLL         0x00000180  /* I2C SCL Duty Cycle Low Reg */
#define I2SCLH_HS_SCLH      0x00000020  /* Fast Plus I2C SCL Duty Cycle High Reg */
#define I2SCLL_HS_SCLL      0x00000020  /* Fast Plus I2C SCL Duty Cycle Low Reg */


volatile uint32_t RdIndex0 = 0, RdIndex1 = 0, RdIndex2 = 0;
volatile uint32_t WrIndex0 = 0, WrIndex1 = 0, WrIndex2 = 0;
 
volatile uint8_t  I2CMasterBuffer[I2C_PORT_NUM][BUFSIZE];
volatile uint8_t  I2CSlaveBuffer[I2C_PORT_NUM][BUFSIZE];
volatile uint32_t I2CReadLength[I2C_PORT_NUM];
volatile uint32_t I2CWriteLength[I2C_PORT_NUM]; 
 
void I2C1_IRQHandler( void );
void I2C2_IRQHandler( void );
void I2C0Init( void );
void I2C1Init( void );
void I2C2Init( void );
uint32_t I2CStart( uint32_t portNum );
uint32_t I2CStop( uint32_t portNum );
uint32_t I2CEngine( uint32_t portNum );

volatile uint32_t I2CMasterState[I2C_PORT_NUM] = {I2C_IDLE,I2C_IDLE,I2C_IDLE};
volatile uint32_t timeout[I2C_PORT_NUM] = {0, 0, 0};


#endif // hw16_IIC_C

/*******************************************************************/
/****************     ¹«ÓÐ³ÉÔ±±äÁ¿,º¯Êý¼°³£Á¿     ******************/
/*******************************************************************/
//public:
EX_hw16_IIC   void   Init_CI2c(void);    //³õÊ¼»¯
 
EX_hw16_IIC   void   I2C0_IRQHandler(void);    //³õÊ¼»¯ 

EX_hw16_IIC   uint8  I2C_WriteNByte(uint8 vSlaveAddress,uint8 vSubAddress,uint8 *s, INT32U num);
EX_hw16_IIC   uint8  I2C_ReadNByte(uint8 vSlaveAddress,uint8 vSubAddress,uint8 *s, INT32U num);

 
/******************************************************************************
// END :
******************************************************************************/
#endif //hw16_IIC_H

