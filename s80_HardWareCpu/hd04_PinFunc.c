#define __hd04_PinFunc_C__
/******************************************************************************
* @file    hd04_PinFunc.c
* @author  yx
* @version V1.0
* @date    2013-07-01
* @Cpu     LPC177x_8x   
* @brief   
* 
******************************************************************************/
#include  "hd04_PinFunc.h"

#include "lpc177x_8x_gpio.h"	
#include "lpc177x_8x_pinsel.h"	

//#include "incFile.h"


/*================= 常数 ============================================*/

/*================= 结构定义 ========================================*/

/*================= 私有结构变量声明 ================================*/

/*================= 公有函数声明 ====================================*/

/*================= 私有函数声明 ====================================*/

/*=================  ================================================*/
		
/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

void hdPinFunc_AD(const THdPinFuncItem_st *pHdPin)
{
	// P0.12
	if(	(pHdPin->pin_BASE == 0) 
	  || (pHdPin->pin_PORT == 12))
	{
		PINSEL_ConfigPin(pHdPin->pin_BASE, pHdPin->pin_PORT, 
					3);
	}
	else
	{
		return; 
	}
	
	PINSEL_SetPinMode(pHdPin->pin_BASE, pHdPin->pin_PORT, 
					 PINSEL_BASICMODE_PLAINOUT);
	PINSEL_SetAnalogPinMode (pHdPin->pin_BASE, pHdPin->pin_PORT, 
						TRUE);
	
}

void hdPinFunc_CAN(const THdPinFuncItem_st *pHdPin)
{
	// P0.0, P0.1, P0.4,P0.5
	if(pHdPin->pin_BASE != 0)
	{
		return;
	}
	
	if(	(pHdPin->pin_PORT == 0) 
	  || (pHdPin->pin_PORT == 1))
	{
		PINSEL_ConfigPin(pHdPin->pin_BASE, pHdPin->pin_PORT, 
					1);
	}
	else if(	(pHdPin->pin_PORT == 4) 
		   || (pHdPin->pin_PORT == 5))
	{
		PINSEL_ConfigPin(pHdPin->pin_BASE, pHdPin->pin_PORT, 
					2);
	}
}

void hdPinFunc_UART(const THdPinFuncItem_st *pHdPin)
{
	// P0.3, P0.2
	
	if(pHdPin->pin_BASE != 0)
	{
		return;
	}
	
	if(	(pHdPin->pin_PORT == 3) 
	  || (pHdPin->pin_PORT == 2))
	{
		PINSEL_ConfigPin(pHdPin->pin_BASE, pHdPin->pin_PORT, 
					2);
	}
}

void hdPinFunc_USB(const THdPinFuncItem_st *pHdPin)
{
	if(pHdPin->pin_BASE != 0)
	{
		return;
	}
	
	if(	(pHdPin->pin_PORT == 29) 
	  || (pHdPin->pin_PORT == 30) 
	  || (pHdPin->pin_PORT == 31)
	  )
	{
		PINSEL_ConfigPin(pHdPin->pin_BASE, pHdPin->pin_PORT, 
					1);
	}
	
}

void hdPinFunc_PWM(const THdPinFuncItem_st *pHdPin)
{
	// P2.0
	
	if(pHdPin->pin_BASE != 2)
	{
		return;
	}
	
	if((pHdPin->pin_PORT == 0))
	{
		PINSEL_ConfigPin(pHdPin->pin_BASE, pHdPin->pin_PORT, 
					1);
	}
}


void hdPinFunc_IIC(const THdPinFuncItem_st *pHdPin)
{
	// P0.27， 0.28
	
	if(pHdPin->pin_BASE != 2)
	{
		return;
	}
	
	if(	(pHdPin->pin_PORT == 27) 
	  || (pHdPin->pin_PORT == 28) 
	  )
	{
		PINSEL_ConfigPin(pHdPin->pin_BASE, pHdPin->pin_PORT, 
					1);
	}
}


void hdPinFunc_EMC(const THdPinFuncItem_st *pHdPin)
{
U8 bHaveEmcFunc = FALSE;

	if((pHdPin->pin_BASE == 3)
	  ||(pHdPin->pin_BASE == 4))
	{
		bHaveEmcFunc = TRUE;
	}
	else if(pHdPin->pin_BASE == 5)
	{
		if(	(pHdPin->pin_PORT == 0) 
		  || (pHdPin->pin_PORT == 1) 
		  )
		{
			bHaveEmcFunc = TRUE;
		}
	}
	else if(pHdPin->pin_BASE == 2)
	{
		if(	(pHdPin->pin_PORT >= 16) 
		  || (pHdPin->pin_PORT <= 31) 
		  )
		{
			bHaveEmcFunc = TRUE;
		}
	}
	
	if(bHaveEmcFunc == TRUE)
	{
		PINSEL_ConfigPin(pHdPin->pin_BASE, pHdPin->pin_PORT, 
					1);
	}
}

/******************************************************************************
* FUNC: //
******************************************************************************/



/******************************************************************************
* FUNC: // END
*   IN:
*  OUT: 
******************************************************************************/
