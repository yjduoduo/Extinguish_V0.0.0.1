#define __hd03_Gpio_C__
/******************************************************************************
* @file    hd03_Gpio.c
* @author  yx
* @version V1.0
* @date    2012-01-05
* @Cpu     LPC177x_8x   
* @brief   数字IO
* 
******************************************************************************/
#include  "hd03_Gpio.h"

#include "lpc177x_8x_gpio.h"	
#include "lpc177x_8x_pinsel.h"	
//#include "incFile.h"	
#include  "CpuReg.h"

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

void hdGpio_init(void)
{
	GPIO_Init();
	
}

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

/******************************************************************************
* FUNC: //
// U_SIGN_bHaveTested 2013.8.27 15:15 
******************************************************************************/
void GpioStrIni(const THdPinItem_st *pHdPin)
{
#if U_SYS_ForbidHardWare == U_Yes 
#else
	Periph_ModulePower(pHdPin->pin_PERIPH, 1);
	PINSEL_ConfigPin(pHdPin->pin_BASE, pHdPin->pin_PORT, 
					U_PIN_FUNC_IS_GPIO);
	
	GPIO_SetDir(pHdPin->pin_BASE, (1<<pHdPin->pin_PORT), pHdPin->pin_InOut);

	if(pHdPin->pin_InOut == U_PIN_Output)
	{
		GPIO_OutputValue(pHdPin->pin_BASE, (1<<pHdPin->pin_PORT), 
					pHdPin->pin_HighLow); 	
	}
	else if(pHdPin->pin_InOut == U_PIN_Input)
	{
		PINSEL_SetPinMode(pHdPin->pin_BASE, pHdPin->pin_PORT,  
					(PinSel_BasicMode)(pHdPin->pin_PullHL)); 
	}
#endif // U_SYS_ForbidHardWare
}

/******************************************************************************
* FUNC: //
******************************************************************************/
void GpioStr_SetIn(const THdPinItem_st *pHdPin)
{
#if U_SYS_ForbidHardWare == U_Yes 
#else
	GPIO_SetDir(pHdPin->pin_BASE, (1<<pHdPin->pin_PORT), U_PIN_Input);
	PINSEL_SetPinMode(pHdPin->pin_BASE, pHdPin->pin_PORT,  
					(PinSel_BasicMode)(pHdPin->pin_PullHL)); 
#endif // U_SYS_ForbidHardWare
}

/******************************************************************************
* FUNC: //
******************************************************************************/
void GpioStr_SetOut(const THdPinItem_st *pHdPin)
{
#if U_SYS_ForbidHardWare == U_Yes 
#else

	GPIO_SetDir(pHdPin->pin_BASE, (1<<pHdPin->pin_PORT), U_PIN_Output);
	
#endif // U_SYS_ForbidHardWare
}


/******************************************************************************
* FUNC: //
*   IN: 
*  OUT: 
******************************************************************************/

void GpioStr_SetOD(const THdPinItem_st *pHdPin)
{
	PINSEL_SetOpenDrainMode(pHdPin->pin_BASE, pHdPin->pin_PORT, 
						   ENABLE);
}

/******************************************************************************
* FUNC: //
*   IN: bitMask: 需要输出的bit为1;
*   IN: bitValue: 需要HIGH的bit为1;
// U_SIGN_bHaveTested 2013.8.27 15:15 
******************************************************************************/
void Gpio_OutSerial(unsigned int ulPort,
					unsigned int bitMask, unsigned int bitValue)
{
unsigned int bitH;
unsigned int bitL;

	bitH = bitMask & bitValue;
	GPIO_OutputValue(ulPort, bitH, U_PIN_HIGH);
	
	bitValue &= bitMask;
	bitL = bitMask ^ bitValue;
	GPIO_OutputValue(ulPort, bitL, U_PIN_LOW);
}


/******************************************************************************
* FUNC: //
******************************************************************************/
void Gpio_DirSerial(unsigned int ulPort,
					unsigned int bitMask, unsigned char mInOut)
{
	GPIO_SetDir(ulPort, bitMask, mInOut);
} // GpioStr_SetIn


/******************************************************************************
* FUNC: //
******************************************************************************/
unsigned int Gpio_PortRead(unsigned int ulPort)
{
	return GPIO_ReadValue(ulPort);
}


/******************************************************************************
* FUNC: //
*   IN: pinStatus = U_PIN_HIGH,  U_PIN_LOW.
******************************************************************************/
void GpioStr_PinSet(const THdPinItem_st *pHdPin, unsigned char pinStatus)
{
#if U_SYS_ForbidHardWare == U_Yes 
#else
	GPIO_OutputValue(pHdPin->pin_BASE, (1 << pHdPin->pin_PORT), 
					pinStatus); 	
#endif // U_SYS_ForbidHardWare

}

/******************************************************************************
* FUNC: //
******************************************************************************/
unsigned char GpioStr_PinRead(const THdPinItem_st *pHdPin)
{
#if U_SYS_ForbidHardWare == U_Yes 
	return U_PIN_HIGH;
#else

	if(GPIO_ReadValue(pHdPin->pin_BASE) & pHdPin->pin_PORT)
	{
		return U_PIN_HIGH;
	}
	else
	{
		return U_PIN_LOW;
	}
#endif // U_SYS_ForbidHardWare
}

/******************************************************************************
* FUNC: //
*   IN: ulPort[0~5]; ucPins[0~31].
******************************************************************************/
void GpioHigh(unsigned long ulPort, unsigned char ucPins)
{
	GPIO_OutputValue(ulPort, (1<<ucPins), U_PIN_HIGH);
}

void GpioLow(unsigned long ulPort, unsigned char ucPins)
{
	GPIO_OutputValue(ulPort, (1<<ucPins), U_PIN_LOW);
}

/******************************************************************************
* FUNC: //
******************************************************************************/
void GpioSet(unsigned long ulPort, unsigned char ucPins, unsigned char pinStatus)
{
	if(pinStatus == U_PIN_HIGH){
		GPIO_OutputValue(ulPort, (1<<ucPins), U_PIN_HIGH);
	}
	else{
		GPIO_OutputValue(ulPort, (1<<ucPins), U_PIN_LOW);
	}
}




/******************************************************************************
* FUNC: // END
*   IN:
*  OUT: 
******************************************************************************/
