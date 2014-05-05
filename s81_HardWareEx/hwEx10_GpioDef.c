#define __hwEx10_GpioDef_C__
/******************************************************************************
* @file    hwEx10_GpioDef.c
* @author  yx
* @version V1.0
* @date    2013-07-01
* @Board   JadeBird Extinguish V1.0
* @brief   
*   GpioKey_Scan();   GpioLed_All_Out();    GpioLcd_DataOut();
******************************************************************************/
#include  "hwEx10_GpioDef.h"

#include  "hd03_Gpio.h"
#include  "hd04_PinFunc.h"
#include  "CpuReg.h"

#include  "LPC177x_8x.h"

//#include "incFile.h"	


/*================= 常数 ============================================*/
#define U_LCD_PIN_DRIVER_USE_LIB    0
#define U_LedKey_PIN_DRIVER_USE_LIB    0

// GpioLcd_DataOut();
#if U_LCD_PIN_DRIVER_USE_LIB == 0
#else // now: U_LCD_PIN_DRIVER_USE_LIB == 1	
#endif // U_LCD_PIN_DRIVER_USE_LIB
/*================= 引脚定义 ========================================*/

const THdPinItem_st  cstGpioExStore[] = // U_Gpio_ExStore_FUNC_MAX
{
	
{U_Periph_P4_PH, U_PIN_PE_4, 30, U_PIN_Output, U_PIN_PullNo, U_PIN_HIGH}, // U_Gpio_Fls_CS0_FUNC,
{U_Periph_P2_PH, U_PIN_PE_2, 14, U_PIN_Output, U_PIN_PullNo, U_PIN_HIGH}, // U_Gpio_Fls_CS1_FUNC,
{U_Periph_P4_PH, U_PIN_PE_4, 31, U_PIN_Output, U_PIN_PullNo, U_PIN_HIGH}, // U_Gpio_Ram_CS2_FUNC,
{U_Periph_P2_PH, U_PIN_PE_2, 21, U_PIN_Input,  U_PIN_PullNo, U_PIN_HIGH}, // U_Gpio_Ram_R_B_FUNC,

};

const THdPinItem_st  cstGpioPwrState[] = // U_Gpio_PwrState_FUNC_MAX
{
{U_Periph_P0_PH, U_PIN_PE_0,  7, U_PIN_Input,  U_PIN_PullNo, U_PIN_HIGH}, // U_Gpio_Pwr_Main_FUNC,
{U_Periph_P0_PH, U_PIN_PE_0,  8, U_PIN_Input,  U_PIN_PullNo, U_PIN_HIGH}, // U_Gpio_Pwr_Baty_FUNC,
{U_Periph_P0_PH, U_PIN_PE_0,  6, U_PIN_Input,  U_PIN_PullNo, U_PIN_HIGH}, // U_Gpio_Pwr_Link_FUNC,

};


const THdPinItem_st  cstGpioLcd[] =  // U_Gpio_Lcd_FUNC_MAX
{

{U_Periph_P1_PH, U_PIN_PE_1, 14, U_PIN_Output, U_PIN_PullNo, U_PIN_LOW}, // U_Gpio_Lcd_Light_FUNC,
{U_Periph_P1_PH, U_PIN_PE_1, 15, U_PIN_Output, U_PIN_PullNo, U_PIN_HIGH}, // U_Gpio_Lcd_CS1_FUNC,
{U_Periph_P1_PH, U_PIN_PE_1, 16, U_PIN_Output, U_PIN_PullNo, U_PIN_HIGH}, // U_Gpio_Lcd_CS2_FUNC,
{U_Periph_P1_PH, U_PIN_PE_1, 17, U_PIN_Output, U_PIN_PullNo, U_PIN_HIGH}, // U_Gpio_Lcd_CS3_FUNC,
{U_Periph_P1_PH, U_PIN_PE_1, 18, U_PIN_Output, U_PIN_PullNo, U_PIN_HIGH}, // U_Gpio_Lcd_RS_D_I_FUNC,
{U_Periph_P1_PH, U_PIN_PE_1, 19, U_PIN_Output, U_PIN_PullNo, U_PIN_HIGH}, // U_Gpio_Lcd_R_W_FUNC,
{U_Periph_P1_PH, U_PIN_PE_1, 20, U_PIN_Output, U_PIN_PullNo, U_PIN_HIGH}, // U_Gpio_Lcd_EN_FUNC,
{U_Periph_P1_PH, U_PIN_PE_1, 21, U_PIN_Output, U_PIN_PullNo, U_PIN_HIGH}, // U_Gpio_Lcd_RST_FUNC,
{U_Periph_P1_PH, U_PIN_PE_1, 22, U_PIN_Input,  U_PIN_PullNo, U_PIN_HIGH}, // U_Gpio_Lcd_D0_FUNC,
{U_Periph_P1_PH, U_PIN_PE_1, 23, U_PIN_Input,  U_PIN_PullNo, U_PIN_HIGH}, // D1
{U_Periph_P1_PH, U_PIN_PE_1, 24, U_PIN_Input,  U_PIN_PullNo, U_PIN_HIGH}, // D2
{U_Periph_P1_PH, U_PIN_PE_1, 25, U_PIN_Input,  U_PIN_PullNo, U_PIN_HIGH}, // D3
{U_Periph_P1_PH, U_PIN_PE_1, 26, U_PIN_Input,  U_PIN_PullNo, U_PIN_HIGH}, // D4
{U_Periph_P1_PH, U_PIN_PE_1, 27, U_PIN_Input,  U_PIN_PullNo, U_PIN_HIGH}, // D5
{U_Periph_P1_PH, U_PIN_PE_1, 28, U_PIN_Input,  U_PIN_PullNo, U_PIN_HIGH}, // D6
{U_Periph_P1_PH, U_PIN_PE_1, 29, U_PIN_Input,  U_PIN_PullNo, U_PIN_HIGH}, // U_Gpio_Lcd_D7_FUNC,
	
};
#define U_GPIO_BASE_LCD_DATA   U_PIN_PE_1
#define U_GPIO_LCD_DataWide          0xFF
#define U_GPIO_PIN_LCD_DATA_LShift   22
#define U_GPIO_Regist_LCD_DATA   	LPC_GPIO1
#define U_GPIO_Regist_LCD_CS     	LPC_GPIO1
#define U_GPIO_Regist_LCD_OTHERS     LPC_GPIO1


const THdPinItem_st  cstGpioLed[] =  // U_Gpio_Led_FUNC_MAX
{
	
{U_Periph_P1_PH, U_PIN_PE_1,  0, U_PIN_Output, U_PIN_PullNo, U_PIN_LOW}, // U_Gpio_Led_Alarm_FUNC,
{U_Periph_P1_PH, U_PIN_PE_1,  1, U_PIN_Output, U_PIN_PullNo, U_PIN_LOW}, // U_Gpio_Led_Auto_FUNC,
{U_Periph_P1_PH, U_PIN_PE_1,  2, U_PIN_Output, U_PIN_PullNo, U_PIN_LOW}, // U_Gpio_Led_Manu_FUNC,
{U_Periph_P1_PH, U_PIN_PE_1,  3, U_PIN_Output, U_PIN_PullNo, U_PIN_LOW}, // U_Gpio_Led_Silence_FUNC,
{U_Periph_P1_PH, U_PIN_PE_1,  4, U_PIN_Output, U_PIN_PullNo, U_PIN_LOW}, // U_Gpio_Led_PwrMain_FUNC,
{U_Periph_P1_PH, U_PIN_PE_1,  5, U_PIN_Output, U_PIN_PullNo, U_PIN_LOW}, // U_Gpio_Led_Run_FUNC,
{U_Periph_P1_PH, U_PIN_PE_1,  6, U_PIN_Output, U_PIN_PullNo, U_PIN_LOW}, // U_Gpio_Led_PwrCheckSw_FUNC,
{U_Periph_P1_PH, U_PIN_PE_1,  7, U_PIN_Output, U_PIN_PullNo, U_PIN_LOW}, // U_Gpio_Led_PwrBaty_FUNC,
{U_Periph_P1_PH, U_PIN_PE_1,  8, U_PIN_Output, U_PIN_PullNo, U_PIN_LOW}, // U_Gpio_Led_CpuFault_FUNC,
};
#define U_GPIO_Regist_LED   	LPC_GPIO1

#define U_GPIO_LED_DataWide   0x1FF
#define U_GPIO_BASE_LED   U_PIN_PE_1
#define U_GPIO_PIN_LED_DATA_LShift   0

const THdPinItem_st  cstGpioKey[] =  // U_Gpio_Key_FUNC_MAX
{
	//注意OD // 不输出电压，低电平时接地，高电平时不接地
{U_Periph_P2_PH, U_PIN_PE_2, 22, U_PIN_Input,  U_PIN_PullUp, U_PIN_LOW}, // U_Gpio_KeyIn_1_FUNC,
{U_Periph_P2_PH, U_PIN_PE_2, 23, U_PIN_Input,  U_PIN_PullUp, U_PIN_LOW}, // U_Gpio_KeyIn_2_FUNC,
{U_Periph_P2_PH, U_PIN_PE_2, 24, U_PIN_Input,  U_PIN_PullUp, U_PIN_LOW}, // U_Gpio_KeyIn_3_FUNC,
{U_Periph_P2_PH, U_PIN_PE_2, 25, U_PIN_Output, U_PIN_PullNo, U_PIN_HIGH}, // U_Gpio_KeyScan_1_FUNC, 
{U_Periph_P2_PH, U_PIN_PE_2, 26, U_PIN_Output, U_PIN_PullNo, U_PIN_HIGH}, // U_Gpio_KeyScan_2_FUNC,
{U_Periph_P2_PH, U_PIN_PE_2, 27, U_PIN_Output, U_PIN_PullNo, U_PIN_HIGH}, // U_Gpio_KeyScan_3_FUNC,
{U_Periph_P2_PH, U_PIN_PE_2, 28, U_PIN_Output, U_PIN_PullNo, U_PIN_HIGH}, // U_Gpio_KeyScan_4_FUNC,
{U_Periph_P2_PH, U_PIN_PE_2, 29, U_PIN_Output, U_PIN_PullNo, U_PIN_HIGH}, // U_Gpio_KeyScan_5_FUNC,
{U_Periph_P2_PH, U_PIN_PE_2, 30, U_PIN_Output, U_PIN_PullNo, U_PIN_HIGH}, // U_Gpio_KeyScan_6_FUNC,
{U_Periph_P2_PH, U_PIN_PE_2, 31, U_PIN_Output, U_PIN_PullNo, U_PIN_HIGH}, // U_Gpio_KeyScan_7_FUNC,

};
#define U_GPIO_Regist_KEY_SCAN   	LPC_GPIO2
#define U_GPIO_Regist_KEY_IN	   	LPC_GPIO2

#define U_GPIO_BASE_KEY   			U_PIN_PE_2
#define U_GPIO_PIN_KEY_IN_LShift   	22
#define U_GPIO_KeyIn_DataWide   	0x07

#define U_GPIO_PIN_KEY_SCAN_LShift   25
#define U_GPIO_KeyScan_DataWide   	0x07F
#define U_GPIO_PIN_KEY_SCAN_Mask   0xFE000000 // U_GPIO_KeyScan_DataWide << U_GPIO_PIN_KEY_SCAN_LShift




/*================= 私有结构变量声明 ================================*/

/*================= 公有函数声明 ====================================*/

/*================= 私有函数声明 ====================================*/

/*=================  ================================================*/
		
/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
void IniSysPinPower(void) // pin 电源
{
	Periph_ModulePower(U_Periph_P0_PH, 1);
	Periph_ModulePower(U_Periph_P1_PH, 1);
	Periph_ModulePower(U_Periph_P2_PH, 1);
	Periph_ModulePower(U_Periph_P4_PH, 1);
	
}



/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/


void IniGpioExStore(void)
{
	U32 pinFunc;
	
	for(pinFunc=0; pinFunc<U_Gpio_ExStore_FUNC_MAX; pinFunc++)
	{
		GpioStrIni(&cstGpioExStore[pinFunc]);
	}
}

void gpioExStoreAllForbid(void)
{	
	GpioStr_PinSet(&cstGpioExStore[U_Gpio_Fls_CS0_FUNC], U_PIN_HIGH);
	GpioStr_PinSet(&cstGpioExStore[U_Gpio_Fls_CS1_FUNC], U_PIN_HIGH);
	GpioStr_PinSet(&cstGpioExStore[U_Gpio_Ram_CS2_FUNC], U_PIN_HIGH);
	
}

void GpioExStoreSelFls0(void)
{	
	gpioExStoreAllForbid();	
	GpioStr_PinSet(&cstGpioExStore[U_Gpio_Fls_CS0_FUNC], U_PIN_LOW);
}

void GpioExStoreSelFls1(void)
{	
	gpioExStoreAllForbid();	
	GpioStr_PinSet(&cstGpioExStore[U_Gpio_Fls_CS1_FUNC], U_PIN_LOW);
}

void GpioExStoreSelRam(void)
{	
	gpioExStoreAllForbid();	
	GpioStr_PinSet(&cstGpioExStore[U_Gpio_Ram_CS2_FUNC], U_PIN_LOW);
}


/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/


void IniGpioPwrState(void)
{
	U32 pinFunc;
	
	for(pinFunc=0; pinFunc<U_Gpio_PwrState_FUNC_MAX; pinFunc++)
	{
		GpioStrIni(&cstGpioPwrState[pinFunc]);
	}
}

/******************************************************************************
* FUNC: //
// OUT: U_ERR, U_USUAL :
******************************************************************************/

unsigned char GetGpioPwrState(unsigned char mGpioPwrState)
{
	unsigned char mPinHL;
	
	if(mGpioPwrState < U_Gpio_PwrState_FUNC_MAX)
	{
		mPinHL = GpioStr_PinRead(&cstGpioPwrState[mGpioPwrState]);
	}
	
	switch(mGpioPwrState)
	{
		case U_Gpio_Pwr_Main_FUNC:
			if(mPinHL == U_PIN_HIGH)
				return U_USUAL;
			break;
			
		case U_Gpio_Pwr_Baty_FUNC:
			if(mPinHL == U_PIN_LOW)
				return U_USUAL;
			break;
			
		case U_Gpio_Pwr_Link_FUNC:
			if(mPinHL == U_PIN_LOW)
				return U_USUAL;
			break;
	}
	return U_ERR;
}



/******************************************************************************
* FUNC: // LCD
*   IN:
*  OUT: 
******************************************************************************/

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
void IniGpioLcd(void)
{
	U32 pinFunc;
	
	for(pinFunc=0; pinFunc<U_Gpio_Lcd_FUNC_MAX; pinFunc++)
	{
		GpioStrIni(&cstGpioLcd[pinFunc]);
	}
	GpioLcd_DataDir_In();
	GpioLcd_RW_Read();
	GpioLcd_RS_Command();
}

/******************************************************************************
* FUNC: //
******************************************************************************/
void GpioLcd_Delay_RS(void) // command  data 
{
U32 ii;
	for(ii=0; ii<30; ii++); // 100=30us(70M); 这个时间太长了。
}

void GpioLcd_Delay_RW(void)
{
U32 ii;
	for(ii=0; ii<30; ii++);
}

void GpioLcd_Delay_EnLock(void)
{
U32 ii;
	for(ii=0; ii<30; ii++);
}

void GpioLcd_Delay_Rst(void)
{
U32 ii;
	for(ii=0; ii<30; ii++);
}

void GpioLcd_Delay_DataDir(void)
{
U32 ii;
	for(ii=0; ii<1; ii++);
}

void GpioLcd_Delay_DataOut(void)
{
U32 ii;
	for(ii=0; ii<1; ii++);
}


/******************************************************************************
* FUNC: //
******************************************************************************/
void GpioLcd_Light(unsigned char mState)
{
#if U_LCD_PIN_DRIVER_USE_LIB == 0
LPC_GPIO_TypeDef *pGPIO = U_GPIO_Regist_LCD_OTHERS;
	if(mState == U_PIN_HIGH)
	{
		pGPIO->SET = (1 << cstGpioLcd[U_Gpio_Lcd_Light_FUNC].pin_PORT);
	}
	else
	{
		pGPIO->CLR = (1 << cstGpioLcd[U_Gpio_Lcd_Light_FUNC].pin_PORT);
	}
#else // now: U_LCD_PIN_DRIVER_USE_LIB == 1	
	GpioStr_PinSet(&cstGpioLcd[U_Gpio_Lcd_Light_FUNC], mState);
#endif // U_LCD_PIN_DRIVER_USE_LIB
}

/******************************************************************************
* FUNC: //
******************************************************************************/
void GpioLcd_CS_AllOff(void)
{
#if U_LCD_PIN_DRIVER_USE_LIB == 0
LPC_GPIO_TypeDef *pGPIO = U_GPIO_Regist_LCD_CS;
	pGPIO->SET = ((1 << cstGpioLcd[U_Gpio_Lcd_CS1_FUNC].pin_PORT)
				 |(1 << cstGpioLcd[U_Gpio_Lcd_CS2_FUNC].pin_PORT)
				 |(1 << cstGpioLcd[U_Gpio_Lcd_CS3_FUNC].pin_PORT)
				 );
#else // now: U_LCD_PIN_DRIVER_USE_LIB == 1
	
	GpioStr_PinSet(&cstGpioLcd[U_Gpio_Lcd_CS1_FUNC], U_PIN_HIGH);
	GpioStr_PinSet(&cstGpioLcd[U_Gpio_Lcd_CS2_FUNC], U_PIN_HIGH);
	GpioStr_PinSet(&cstGpioLcd[U_Gpio_Lcd_CS3_FUNC], U_PIN_HIGH);
#endif // U_LCD_PIN_DRIVER_USE_LIB
}


void GpioLcd_SelCsX_1(unsigned char mLcdCs)
{
	if((mLcdCs >= U_Gpio_Lcd_CS1_FUNC) && (mLcdCs <= U_Gpio_Lcd_CS3_FUNC))
	{
#if U_LCD_PIN_DRIVER_USE_LIB == 0
LPC_GPIO_TypeDef *pGPIO = U_GPIO_Regist_LCD_CS;
		pGPIO->SET = (1 << cstGpioLcd[mLcdCs].pin_PORT);
#else // now: U_LCD_PIN_DRIVER_USE_LIB == 1
	
		GpioStr_PinSet(&cstGpioLcd[mLcdCs], U_PIN_HIGH);
#endif // U_LCD_PIN_DRIVER_USE_LIB
	}
}

void GpioLcd_SelCsX_0(unsigned char mLcdCs)
{
	if((mLcdCs >= U_Gpio_Lcd_CS1_FUNC) && (mLcdCs <= U_Gpio_Lcd_CS3_FUNC))
	{
#if U_LCD_PIN_DRIVER_USE_LIB == 0
LPC_GPIO_TypeDef *pGPIO = U_GPIO_Regist_LCD_CS;
		pGPIO->CLR = (1 << cstGpioLcd[mLcdCs].pin_PORT);
#else // now: U_LCD_PIN_DRIVER_USE_LIB == 1
		GpioStr_PinSet(&cstGpioLcd[mLcdCs], U_PIN_LOW);
#endif // U_LCD_PIN_DRIVER_USE_LIB
	}
}

/******************************************************************************
* FUNC: //
******************************************************************************/
// static U8 bLcdRsState = ~0;

void GpioLcd_RS_Command(void)
{
#if U_LCD_PIN_DRIVER_USE_LIB == 0
LPC_GPIO_TypeDef *pGPIO = U_GPIO_Regist_LCD_OTHERS;
#endif

	// if(bLcdRsState == 0)
	// {
		// return;
	// }
	
	
#if U_LCD_PIN_DRIVER_USE_LIB == 0
	pGPIO->CLR = (1 << cstGpioLcd[U_Gpio_Lcd_RS_D_I_FUNC].pin_PORT);
	GpioLcd_Delay_RS();
#else // now: U_LCD_PIN_DRIVER_USE_LIB == 1
	
	GpioStr_PinSet(&cstGpioLcd[U_Gpio_Lcd_RS_D_I_FUNC], U_PIN_LOW);
#endif // U_LCD_PIN_DRIVER_USE_LIB

	// bLcdRsState = 0;
}

void GpioLcd_RS_Data(void)
{
#if U_LCD_PIN_DRIVER_USE_LIB == 0
LPC_GPIO_TypeDef *pGPIO = U_GPIO_Regist_LCD_OTHERS;
#endif

	// if(bLcdRsState == 1)
	// {
		// return;
	// }
#if U_LCD_PIN_DRIVER_USE_LIB == 0
	pGPIO->SET = (1 << cstGpioLcd[U_Gpio_Lcd_RS_D_I_FUNC].pin_PORT);
	GpioLcd_Delay_RS();
#else // now: U_LCD_PIN_DRIVER_USE_LIB == 1
	GpioStr_PinSet(&cstGpioLcd[U_Gpio_Lcd_RS_D_I_FUNC], U_PIN_HIGH);
#endif // U_LCD_PIN_DRIVER_USE_LIB

	// bLcdRsState = 1;
}


/******************************************************************************
* FUNC: // 
******************************************************************************/
// static U8 bLcdRwState = ~0;

void GpioLcd_RW_Read(void)
{
#if U_LCD_PIN_DRIVER_USE_LIB == 0
LPC_GPIO_TypeDef *pGPIO = U_GPIO_Regist_LCD_OTHERS;
#endif

	// if(bLcdRwState == U_READ)
	// {
		// return;
	// }
	
#if U_LCD_PIN_DRIVER_USE_LIB == 0
	pGPIO->SET = (1 << cstGpioLcd[U_Gpio_Lcd_R_W_FUNC].pin_PORT);
	GpioLcd_Delay_RW();

#else // now: U_LCD_PIN_DRIVER_USE_LIB == 1
	
	GpioStr_PinSet(&cstGpioLcd[U_Gpio_Lcd_R_W_FUNC], U_PIN_HIGH);
#endif // U_LCD_PIN_DRIVER_USE_LIB
	// bLcdRwState = U_READ;
}

void GpioLcd_RW_Write(void)
{
#if U_LCD_PIN_DRIVER_USE_LIB == 0
LPC_GPIO_TypeDef *pGPIO = U_GPIO_Regist_LCD_OTHERS;
#endif

	// if(bLcdRwState == U_WRITE)
	// {
		// return;
	// }
#if U_LCD_PIN_DRIVER_USE_LIB == 0
	pGPIO->CLR = (1 << cstGpioLcd[U_Gpio_Lcd_R_W_FUNC].pin_PORT);
	GpioLcd_Delay_RW();

#else // now: U_LCD_PIN_DRIVER_USE_LIB == 1
	
	GpioStr_PinSet(&cstGpioLcd[U_Gpio_Lcd_R_W_FUNC], U_PIN_LOW);
#endif // U_LCD_PIN_DRIVER_USE_LIB
	// bLcdRwState = U_WRITE;
}


/******************************************************************************
* FUNC: // 
******************************************************************************/
void GpioLcd_EnLock_1_Ready(void)
{
#if U_LCD_PIN_DRIVER_USE_LIB == 0
LPC_GPIO_TypeDef *pGPIO = U_GPIO_Regist_LCD_OTHERS;
	pGPIO->SET = (1 << cstGpioLcd[U_Gpio_Lcd_EN_FUNC].pin_PORT);
	GpioLcd_Delay_EnLock();

#else // now: U_LCD_PIN_DRIVER_USE_LIB == 1
	
	GpioStr_PinSet(&cstGpioLcd[U_Gpio_Lcd_EN_FUNC], U_PIN_HIGH);
#endif // U_LCD_PIN_DRIVER_USE_LIB
}
void GpioLcd_EnLock_0_Go(void)
{
#if U_LCD_PIN_DRIVER_USE_LIB == 0
LPC_GPIO_TypeDef *pGPIO = U_GPIO_Regist_LCD_OTHERS;
	pGPIO->CLR = (1 << cstGpioLcd[U_Gpio_Lcd_EN_FUNC].pin_PORT);
	GpioLcd_Delay_EnLock();

#else // now: U_LCD_PIN_DRIVER_USE_LIB == 1
	
	GpioStr_PinSet(&cstGpioLcd[U_Gpio_Lcd_EN_FUNC], U_PIN_LOW);
#endif // U_LCD_PIN_DRIVER_USE_LIB
}

void GpioLcd_Rst_0_reset(void)
{
#if U_LCD_PIN_DRIVER_USE_LIB == 0
LPC_GPIO_TypeDef *pGPIO = U_GPIO_Regist_LCD_OTHERS;
	pGPIO->CLR = (1 << cstGpioLcd[U_Gpio_Lcd_RST_FUNC].pin_PORT);
	GpioLcd_Delay_Rst();

#else // now: U_LCD_PIN_DRIVER_USE_LIB == 1
	
	GpioStr_PinSet(&cstGpioLcd[U_Gpio_Lcd_RST_FUNC], U_PIN_LOW);
#endif // U_LCD_PIN_DRIVER_USE_LIB
}

void GpioLcd_Rst_1_work(void)
{
#if U_LCD_PIN_DRIVER_USE_LIB == 0
LPC_GPIO_TypeDef *pGPIO = U_GPIO_Regist_LCD_OTHERS;
	pGPIO->SET = (1 << cstGpioLcd[U_Gpio_Lcd_RST_FUNC].pin_PORT);
	GpioLcd_Delay_Rst();

#else // now: U_LCD_PIN_DRIVER_USE_LIB == 1
	
	GpioStr_PinSet(&cstGpioLcd[U_Gpio_Lcd_RST_FUNC], U_PIN_HIGH);
#endif // U_LCD_PIN_DRIVER_USE_LIB
}


/******************************************************************************
* FUNC: //
******************************************************************************/
static U8 bLcdDatLine_InOut = U_PIN_InOut_Invalid;



void GpioLcd_DataDir_Out(void)
{
#if U_LCD_PIN_DRIVER_USE_LIB == 0
LPC_GPIO_TypeDef *pGPIO;
#endif
	if(bLcdDatLine_InOut == U_PIN_Output)
	{
		return;
	}
#if U_LCD_PIN_DRIVER_USE_LIB == 0
	pGPIO = U_GPIO_Regist_LCD_DATA;
	pGPIO->DIR |= (0xFF << U_GPIO_PIN_LCD_DATA_LShift); // output
	GpioLcd_Delay_DataDir();
#else // now: U_LCD_PIN_DRIVER_USE_LIB == 1
	Gpio_DirSerial(U_GPIO_BASE_LCD_DATA,
					0xFF << U_GPIO_PIN_LCD_DATA_LShift, 
					U_PIN_Output);	
#endif // U_LCD_PIN_DRIVER_USE_LIB
	bLcdDatLine_InOut = U_PIN_Output;
}



void GpioLcd_DataDir_In(void)
{
#if U_LCD_PIN_DRIVER_USE_LIB == 0
LPC_GPIO_TypeDef *pGPIO;
#endif

	if(bLcdDatLine_InOut == U_PIN_Input)
	{
		return;
	}
#if U_LCD_PIN_DRIVER_USE_LIB == 0
	pGPIO = U_GPIO_Regist_LCD_DATA;
	pGPIO->DIR &= ~(0xFF << U_GPIO_PIN_LCD_DATA_LShift);
	GpioLcd_Delay_DataDir();
	// pGPIO->DIR |= bitValue; // output
#else // now: U_LCD_PIN_DRIVER_USE_LIB == 1
	Gpio_DirSerial(U_GPIO_BASE_LCD_DATA,
					0xFF << U_GPIO_PIN_LCD_DATA_LShift, 
					U_PIN_Input);
	
#endif // U_LCD_PIN_DRIVER_USE_LIB
	bLcdDatLine_InOut = U_PIN_Input;
	
}


/******************************************************************************
* FUNC: //
******************************************************************************/
void GpioLcd_DataOut(unsigned char mData)
{
#if U_LCD_PIN_DRIVER_USE_LIB == 0
U32 mOutData;
LPC_GPIO_TypeDef *pGPIO;
unsigned int bitH;
unsigned int bitL;
unsigned int bitMask;
unsigned int bitValue;
	
	GpioLcd_DataDir_Out();
	
	mOutData = mData;
	bitMask = U_GPIO_LCD_DataWide << U_GPIO_PIN_LCD_DATA_LShift;
	bitValue = mOutData << U_GPIO_PIN_LCD_DATA_LShift;
	
	bitH = bitMask & bitValue;
	bitL = bitMask ^ bitH;
	
	pGPIO = U_GPIO_Regist_LCD_DATA;
	pGPIO->SET = bitH;
	pGPIO->CLR = bitL;
	// GpioLcd_Delay_DataOut();
#else // now: U_LCD_PIN_DRIVER_USE_LIB == 1	
U32 mOutData;
	
	GpioLcd_DataDir_Out();
	
	mOutData = mData;
	Gpio_OutSerial(U_GPIO_BASE_LCD_DATA,
					U_GPIO_LCD_DataWide << U_GPIO_PIN_LCD_DATA_LShift, 
					mOutData << U_GPIO_PIN_LCD_DATA_LShift);
	
#endif // U_LCD_PIN_DRIVER_USE_LIB

}


unsigned char GpioLcd_DataIn(void)
{
U32 mRdData;
#if U_LCD_PIN_DRIVER_USE_LIB == 0
LPC_GPIO_TypeDef *pGPIO = U_GPIO_Regist_LCD_DATA;
#endif
	GpioLcd_DataDir_In();
	
#if U_LCD_PIN_DRIVER_USE_LIB == 0
	mRdData = pGPIO->PIN;
#else // now: U_LCD_PIN_DRIVER_USE_LIB == 1
	mRdData = Gpio_PortRead(U_GPIO_BASE_LCD_DATA);
#endif // U_LCD_PIN_DRIVER_USE_LIB

	return ((mRdData >> U_GPIO_PIN_LCD_DATA_LShift) & 0xFF);
}


/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

void IniGpioLed(void)
{
	U32 pinFunc;
	
	
	for(pinFunc=0; pinFunc<U_Gpio_Led_FUNC_MAX; pinFunc++)
	{
		GpioStrIni(&cstGpioLed[pinFunc]);
	}
	
}


void GpioLed_All_On(void)
{
	Gpio_OutSerial(U_GPIO_BASE_LED,
					U_GPIO_LED_DataWide << U_GPIO_PIN_LED_DATA_LShift, 
					                 0  << U_GPIO_PIN_LED_DATA_LShift);
}
void GpioLed_All_Off(void)
{
	Gpio_OutSerial(U_GPIO_BASE_LED,
					U_GPIO_LED_DataWide << U_GPIO_PIN_LED_DATA_LShift, 
					U_GPIO_LED_DataWide << U_GPIO_PIN_LED_DATA_LShift);
}

// #define U_GPIO_Regist_LED   	LPC_GPIO1

// #define U_GPIO_LED_DataWide   0x1FF
// #define U_GPIO_BASE_LED   U_PIN_PE_1
// #define U_GPIO_PIN_LED_DATA_LShift   0
void GpioLed_All_Out(unsigned int mLedBits)
{
#if U_LedKey_PIN_DRIVER_USE_LIB == 0
LPC_GPIO_TypeDef *pGPIO = U_GPIO_Regist_LED;
unsigned int bitH;
unsigned int bitL;
unsigned int bitMask;
unsigned int bitValue;
#endif  
	U32 mOutData;
	mOutData = ~mLedBits; // 0亮
	
#if U_LedKey_PIN_DRIVER_USE_LIB == 0
	bitMask = U_GPIO_LED_DataWide << U_GPIO_PIN_LED_DATA_LShift;
	bitValue = mOutData << U_GPIO_PIN_LED_DATA_LShift;
	bitH = bitMask & bitValue;
	bitL = bitMask ^ bitH;
	
	pGPIO->SET = bitH;
	pGPIO->CLR = bitL;
#else // now: U_LedKey_PIN_DRIVER_USE_LIB == 1	
	Gpio_OutSerial(U_GPIO_BASE_LCD_DATA,
		U_GPIO_LED_DataWide << U_GPIO_PIN_LED_DATA_LShift, 
				 mOutData << U_GPIO_PIN_LED_DATA_LShift);
#endif // U_LCD_PIN_DRIVER_USE_LIB
}

void GpioLed_On(unsigned char mLed)
{
	if(mLed < U_Gpio_Led_FUNC_MAX)
	{
		GpioStr_PinSet(&cstGpioLed[mLed], U_PIN_LOW);
	}
}
void GpioLed_Off(unsigned char mLed)
{
	if(mLed < U_Gpio_Led_FUNC_MAX)
	{
		GpioStr_PinSet(&cstGpioLed[mLed], U_PIN_HIGH);
	}
}

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

void IniGpioKey(void)
{
	U32 pinFunc;
	
	for(pinFunc=U_Gpio_Key_Scan_L; pinFunc<U_Gpio_Key_Scan_H; pinFunc++)
	{
		GpioStr_SetOD(&cstGpioKey[pinFunc]);
	}
	
	for(pinFunc=0; pinFunc<U_Gpio_Key_FUNC_MAX; pinFunc++)
	{
		GpioStrIni(&cstGpioKey[pinFunc]);
	}
	
	for(pinFunc=U_Gpio_Key_Scan_L; pinFunc<U_Gpio_Key_Scan_H; pinFunc++)
	{
		GpioStr_SetOD(&cstGpioKey[pinFunc]);
	}
	
}


void GpioKey_Scan(unsigned char mKeyScan)
{
#if U_LedKey_PIN_DRIVER_USE_LIB == 0
LPC_GPIO_TypeDef *pGPIO = U_GPIO_Regist_KEY_SCAN;
#endif  

	if((mKeyScan >= U_Gpio_Key_Scan_L) && (mKeyScan < U_Gpio_Key_Scan_H))
	{
#if U_LedKey_PIN_DRIVER_USE_LIB == 0

	pGPIO->SET = U_GPIO_PIN_KEY_SCAN_Mask;	
	pGPIO->CLR = (1 << cstGpioKey[mKeyScan].pin_PORT);

#else // now: U_LedKey_PIN_DRIVER_USE_LIB == 1	
		Gpio_OutSerial(U_GPIO_BASE_KEY,
					U_GPIO_PIN_KEY_SCAN_Mask, 
					U_GPIO_PIN_KEY_SCAN_Mask);
		
		GpioStr_PinSet(&cstGpioKey[mKeyScan], U_PIN_LOW);
#endif // U_LCD_PIN_DRIVER_USE_LIB
	}
}

void Key_ScanOut(unsigned char mKeyScanNum)
{
	if(mKeyScanNum >= U_Gpio_Key_ScanOut_MAX)
		return;
	GpioKey_Scan(U_Gpio_Key_Scan_L + mKeyScanNum);
}

unsigned char GpioKey_In(void)
{
U32 mRdData;
#if U_LedKey_PIN_DRIVER_USE_LIB == 0
LPC_GPIO_TypeDef *pGPIO = U_GPIO_Regist_KEY_IN;

	mRdData = pGPIO->PIN;
#else // now: U_LedKey_PIN_DRIVER_USE_LIB == 1	
	mRdData = Gpio_PortRead(U_GPIO_BASE_KEY);
	
#endif // U_LCD_PIN_DRIVER_USE_LIB
	return ((mRdData >> U_GPIO_PIN_KEY_IN_LShift) & U_GPIO_KeyIn_DataWide);
}


/******************************************************************************
* FUNC: // END
*   IN:
*  OUT: 
******************************************************************************/
