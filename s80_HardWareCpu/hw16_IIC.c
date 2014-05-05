/*
*********************************************************************************************************
*                                                
*                               对象: hw16_IIC
*                        (c) Copyright 2010-2018, jxm
*                              All Rights Reserved
*                                    Ver1.0
* File : hw16_IIC.C
* @Cpu     LPC177x_8x   
* By   : jxm
* Date : 2012-07-20
*********************************************************************************************************
*/ 
#define   hw16_IIC_C   
#include  "hw16_IIC.h" 
#include  "lpc177x_8x_i2c.h"
#include  "lpc177x_8x_clkpwr.h"
#include  "lpc177x_8x_pinsel.h"  

/*****************************************************************************
** Function name:		I2CStart
**
** Descriptions:		Create I2C start condition, a timeout
**				value is set if the I2C never gets started,
**				and timed out. It's a fatal error. 
**
** parameters:			None
** Returned value:		true or false, return false if timed out
** 
*****************************************************************************/
uint32_t I2CStart( uint32_t portNum )
{
  uint32_t retVal = FALSE;
 
  timeout[portNum] = 0;
  /*--- Issue a start condition ---*/
  LPC_I2C[portNum]->CONSET = I2CONSET_STA;	/* Set Start flag */
    
  /*--- Wait until START transmitted ---*/
  while( 1 )
  {
	if ( I2CMasterState[portNum] == I2C_STARTED )
	{
	  retVal = TRUE;
	  break;	
	}
	if ( timeout[portNum] >= MAX_I2cTIMEOUT )
	{
	  retVal = FALSE;
	  break;
	}
	timeout[portNum]++;
  }
  return( retVal );
}

/*****************************************************************************
** Function name:		I2CStop
**
** Descriptions:		Set the I2C stop condition, if the routine
**				never exit, it's a fatal bus error.
**
** parameters:			None
** Returned value:		true or never return
** 
*****************************************************************************/
uint32_t I2CStop( uint32_t portNum )
{
  LPC_I2C[portNum]->CONSET = I2CONSET_STO;      /* Set Stop flag */ 
  LPC_I2C[portNum]->CONCLR = I2CONCLR_SIC;  /* Clear SI flag */ 
            
  /*--- Wait for STOP detected ---*/
  while( LPC_I2C[portNum]->CONSET & I2CONSET_STO );
  return TRUE;
}

 

//系统初始化函数
//板载使用的是I2C0
void Init_CI2c(void)
{   
	  I2C0Init();
}

void I2C0Init( void )
{
	  uint32_t ulFi2c1=cFi2c1;
	  LPC_SC->PCONP |= (0x01 << 7);                                      /* 打开I2C0模块功率控制位       */ 

	
	  /*--- Clear flags ---*/
    LPC_I2C0->CONCLR = I2CONCLR_AAC | I2CONCLR_SIC | I2CONCLR_STAC | I2CONCLR_I2ENC;  
	
	  LPC_IOCON->P0_27 &= ~0x1F;	/*  I2C I/O config */
    LPC_IOCON->P0_27 |= (0x01|(0x1<<10));  /* make it open-drain, I2C SDA */
    LPC_IOCON->P0_28 &= ~0x1F;	
    LPC_IOCON->P0_28 |= (0x01|(0x1<<10));  /* make it open-drain, I2C SCL */	
	
	
    if (ulFi2c1 > 400000) {
        ulFi2c1 = 400000;
    }
    LPC_I2C0->SCLH = (PeripheralClock / ulFi2c1) / 2;                // 设置I2C时钟为fi2c    
    LPC_I2C0->SCLL = (PeripheralClock / ulFi2c1) / 2; 
    
		
		RdIndex0 = 0;
    WrIndex0 = 0;
		
    
    /* Enable the I2C Interrupt */
    NVIC_EnableIRQ(I2C0_IRQn);
		//NVIC_SetPriority(I2C0_IRQn, 3);  
    LPC_I2C0->CONSET = I2CONSET_I2EN;
}


/*****************************************************************************
** Function name:		I2C_IRQHandler
**
** Descriptions:		I2C interrupt handler, deal with master mode only.
**
** parameters:			None
** Returned value:		None
** 
*****************************************************************************/
void I2C0_IRQHandler(void) 
{
  uint8_t StatValue;

  timeout[0] = 0;
  /* this handler deals with master read and master write only */
  StatValue = LPC_I2C0->STAT;
  switch ( StatValue )
  {
	case 0x08:			/* A Start condition is issued. */
	WrIndex0 = 0;
	LPC_I2C0->DAT = I2CMasterBuffer[0][WrIndex0++];
	LPC_I2C0->CONCLR = (I2CONCLR_SIC | I2CONCLR_STAC);
	break;
	
	case 0x10:			/* A repeated started is issued */
	RdIndex0 = 0;
	/* Send SLA with R bit set, */
	LPC_I2C0->DAT = I2CMasterBuffer[0][WrIndex0++];
	LPC_I2C0->CONCLR = (I2CONCLR_SIC | I2CONCLR_STAC);
	break;
	
	case 0x18:			/* Regardless, it's a ACK */
	if ( I2CWriteLength[0] == 1 )
	{
	  LPC_I2C0->CONSET = I2CONSET_STO;      /* Set Stop flag */
	  I2CMasterState[0] = I2C_NO_DATA;
	}
	else
	{
	  LPC_I2C0->DAT = I2CMasterBuffer[0][WrIndex0++];
	}
	LPC_I2C0->CONCLR = I2CONCLR_SIC;
	break;

	case 0x28:	/* Data byte has been transmitted, regardless ACK or NACK */
	if ( WrIndex0 < I2CWriteLength[0] )
	{   
	  LPC_I2C0->DAT = I2CMasterBuffer[0][WrIndex0++]; /* this should be the last one */
	}
	else
	{
	  if ( I2CReadLength[0] != 0 )
	  {
		LPC_I2C0->CONSET = I2CONSET_STA;	/* Set Repeated-start flag */
	  }
	  else
	  {
		LPC_I2C0->CONSET = I2CONSET_STO;      /* Set Stop flag */
		I2CMasterState[0] = I2C_OK;
	  }
	}
	LPC_I2C0->CONCLR = I2CONCLR_SIC;
	break;

	case 0x30:
	LPC_I2C0->CONSET = I2CONSET_STO;      /* Set Stop flag */
	I2CMasterState[0] = I2C_NACK_ON_DATA;
	LPC_I2C0->CONCLR = I2CONCLR_SIC;
	break;
	
	case 0x40:	/* Master Receive, SLA_R has been sent */
	if ( (RdIndex0 + 1) < I2CReadLength[0] )
	{
	  /* Will go to State 0x50 */
	  LPC_I2C0->CONSET = I2CONSET_AA;	/* assert ACK after data is received */
	}
	else
	{
	  /* Will go to State 0x58 */
	  LPC_I2C0->CONCLR = I2CONCLR_AAC;	/* assert NACK after data is received */
	}
	LPC_I2C0->CONCLR = I2CONCLR_SIC;
	break;
	
	case 0x50:	/* Data byte has been received, regardless following ACK or NACK */
	I2CSlaveBuffer[0][RdIndex0++] = LPC_I2C0->DAT;
	if ( (RdIndex0 + 1) < I2CReadLength[0] )
	{   
	  LPC_I2C0->CONSET = I2CONSET_AA;	/* assert ACK after data is received */
	}
	else
	{
	  LPC_I2C0->CONCLR = I2CONCLR_AAC;	/* assert NACK on last byte */
	}
	LPC_I2C0->CONCLR = I2CONCLR_SIC;
	break;
	
	case 0x58:
	I2CSlaveBuffer[0][RdIndex0++] = LPC_I2C0->DAT;
	I2CMasterState[0] = I2C_OK;
	LPC_I2C0->CONSET = I2CONSET_STO;	/* Set Stop flag */ 
	LPC_I2C0->CONCLR = I2CONCLR_SIC;	/* Clear SI flag */
	break;

	case 0x20:		/* regardless, it's a NACK */
	case 0x48:
	LPC_I2C0->CONSET = I2CONSET_STO;      /* Set Stop flag */
	I2CMasterState[0] = I2C_NACK_ON_ADDRESS;
	LPC_I2C0->CONCLR = I2CONCLR_SIC;
	break;
	
	case 0x38:		/* Arbitration lost, in this example, we don't
					deal with multiple master situation */
	default:
	I2CMasterState[0] = I2C_ARBITRATION_LOST;
	LPC_I2C0->CONCLR = I2CONCLR_SIC;	
	break;
  }
  return;
}


/*****************************************************************************
** Function name:		I2CEngine
**
** Descriptions:		The routine to complete a I2C transaction
**						from start to stop. All the intermitten
**						steps are handled in the interrupt handler.
**						Before this routine is called, the read
**						length, write length, I2C master buffer,
**						and I2C command fields need to be filled.
**						see i2cmst.c for more details. 
**
** parameters:			I2C port number
** Returned value:		master state of current I2C port.
** 
*****************************************************************************/
uint32_t I2CEngine( uint32_t portNum ) 
{
  /*--- Issue a start condition ---*/
  LPC_I2C[portNum]->CONSET = I2CONSET_STA;	/* Set Start flag */

  I2CMasterState[portNum] = I2C_BUSY;	

  while ( I2CMasterState[portNum] == I2C_BUSY )
  {
			if ( timeout[portNum] >= MAX_I2cTIMEOUT )
			{
				I2CMasterState[portNum] = I2C_TIME_OUT;
				break;
			}
			timeout[portNum]++;
  }
  LPC_I2C[portNum]->CONCLR = I2CONCLR_STAC;

  return ( I2CMasterState[portNum] );
} 

uint8  I2C_WriteNByte(uint8 vSlaveAddress,uint8 vSubAddress,uint8 *s, INT32U num)
{ 
	  uint8  i; 
	  uint8  vSndLen=0; 
	  I2CMasterBuffer[cUseI2cPort][vSndLen++] = vSlaveAddress;
	  I2CMasterBuffer[cUseI2cPort][vSndLen++] = vSubAddress;
	  for(i=0;i<num;i++)
		{
			  I2CMasterBuffer[cUseI2cPort][vSndLen++] = *s++;  
		} 
	  I2CWriteLength[cUseI2cPort] =vSndLen;
    I2CReadLength[cUseI2cPort] =0;
	  I2CEngine(cUseI2cPort);  
	  return 1;
}

uint8  I2C_ReadNByte(uint8 vSlaveAddress,uint8 vSubAddress,uint8 *s, INT32U num)
{     
	  uint32  i; 
	  uint32  vDelay=30; 
	  uint8  vSndLen=0; 
	  I2CMasterBuffer[cUseI2cPort][vSndLen++] = vSlaveAddress;  //vSlaveAddress|RD_BIT; 
	  I2CMasterBuffer[cUseI2cPort][vSndLen++] = vSubAddress;
	  I2CMasterBuffer[cUseI2cPort][vSndLen++] = vSlaveAddress|RD_BIT; 
	  I2CWriteLength[cUseI2cPort] =2; 
    I2CReadLength[cUseI2cPort] =num; 
	  I2CEngine(cUseI2cPort); 
    //vDelay=cMAX_I2cTIMEBit*num; 	
	  for(i = 0; i < vDelay; i++);   
	  if(I2CMasterState[0] != I2C_OK)
		{
			  return 0;
		}
		else
		{
				vSndLen=0; 
				for(i=0;i<num;i++)
				{
					 *s++=I2CSlaveBuffer[cUseI2cPort][vSndLen++];  
				} 
				return 1;
	  }
}

 

/*********************************************************************************************************
** End Of File
*********************************************************************************************************/
