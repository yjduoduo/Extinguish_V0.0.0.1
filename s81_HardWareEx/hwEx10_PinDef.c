#define __hwEx10_PinDef_C__
/******************************************************************************
* @file    hwEx10_PinDef.c
* @author  yx
* @version V1.0
* @date    2013-07-01
* @Board   JadeBird Extinguish V1.0
* @brief   
* 
******************************************************************************/
#include  "hwEx10_PinDef.h"


#include  "hd03_Gpio.h"
#include  "hd04_PinFunc.h"
#include  "CpuReg.h"
//#include "incFile.h"	


/*================= 常数 ============================================*/

/*================= 引脚定义 ========================================*/

const THdPinFuncItem_st  cstPinFunc[] = 
{
	{U_Periph_P0_PH, U_PIN_PE_0,  0}, // U_PIN_Can1_Rx_FUNC,
	{U_Periph_P0_PH, U_PIN_PE_0,  1}, // U_PIN_Can1_Tx_FUNC,
	{U_Periph_P0_PH, U_PIN_PE_0,  4}, // U_PIN_Can2_Rx_FUNC,
	{U_Periph_P0_PH, U_PIN_PE_0,  5}, // U_PIN_Can2_Tx_FUNC,
	{U_Periph_P0_PH, U_PIN_PE_0,  3}, // U_PIN_Uart0Rx_FUNC,
	{U_Periph_P0_PH, U_PIN_PE_0,  2}, // U_PIN_Uart0Tx_FUNC,
	{U_Periph_P0_PH, U_PIN_PE_0, 27}, // U_PIN_I2cSda_FUNC,
	{U_Periph_P0_PH, U_PIN_PE_0, 28}, // U_PIN_I2cScl_FUNC,
	{U_Periph_P0_PH, U_PIN_PE_0, 31}, // U_PIN_UsbD0p_FUNC,
	{U_Periph_P0_PH, U_PIN_PE_0, 32}, // U_PIN_UsbD1r_FUNC,
	{U_Periph_P0_PH, U_PIN_PE_0, 12}, // U_PIN_AdPwrCheckSwitch_FUNC, AD0[6];
	{U_Periph_P2_PH, U_PIN_PE_2,  0}, // U_PIN_Buzzer_FUNC,
	
};
	
/*================= 私有结构变量声明 ================================*/

/*================= 公有函数声明 ====================================*/

/*================= 私有函数声明 ====================================*/

/*=================  ================================================*/
		
/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

void IniPinFunc(void)
{
	IniPinFunc_Can1();
	IniPinFunc_Can2();
	
	IniPinFunc_Uart0();
	
	IniPinFunc_IIC();
	
	IniPinFunc_USB();
	
	IniPinFunc_AD_PwrCheckSwitch();
	
	IniPinFunc_PWM_Buzzer();
}


/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

void IniPinFunc_Can1(void)
{
	hdPinFunc_CAN(&cstPinFunc[U_PIN_Can1_Rx_FUNC]);
	hdPinFunc_CAN(&cstPinFunc[U_PIN_Can1_Tx_FUNC]);
}

void IniPinFunc_Can2(void)
{
	hdPinFunc_CAN(&cstPinFunc[U_PIN_Can2_Rx_FUNC]);
	hdPinFunc_CAN(&cstPinFunc[U_PIN_Can2_Tx_FUNC]);
}

void IniPinFunc_Uart0(void)
{
	hdPinFunc_UART(&cstPinFunc[U_PIN_Uart0Rx_FUNC]);
	hdPinFunc_UART(&cstPinFunc[U_PIN_Uart0Tx_FUNC]);
}

void IniPinFunc_IIC(void)
{
	hdPinFunc_IIC(&cstPinFunc[U_PIN_I2cSda_FUNC]);
	hdPinFunc_IIC(&cstPinFunc[U_PIN_I2cScl_FUNC]);
}


void IniPinFunc_USB(void)
{
	hdPinFunc_USB(&cstPinFunc[U_PIN_UsbD0p_FUNC]);
	hdPinFunc_USB(&cstPinFunc[U_PIN_UsbD1r_FUNC]);
}

void IniPinFunc_AD_PwrCheckSwitch(void)
{
	hdPinFunc_AD(&cstPinFunc[U_PIN_AdPwrCheckSwitch_FUNC]);

}

void IniPinFunc_PWM_Buzzer(void)
{
	hdPinFunc_PWM(&cstPinFunc[U_PIN_Buzzer_FUNC]);
}


/******************************************************************************
* FUNC: // EMC 引脚
*   IN:
*  OUT: 
// U_PIN_EMC_Data_FUNC ;  P3.0~P3.31 
// U_PIN_EMC_Addr_FUNC ;  P4.00(A0) ~ P4.31(A31)
// U_PIN_EMC_CtrlLine_FUNC ;  P2.14  ~ P2.31
******************************************************************************/

void IniPinFunc_EMC_Data(void)
{
THdPinFuncItem_st  stPinFunc;
U8 pinPort;
	
	stPinFunc.pin_PERIPH = U_Periph_P3_PH;
	stPinFunc.pin_BASE   = U_PIN_PE_3;
	stPinFunc.pin_PORT   = 0;
	
	for(pinPort=0; pinPort<=31; pinPort++)
	{
		stPinFunc.pin_PORT   = pinPort;
		hdPinFunc_EMC(&stPinFunc);
	}
}

void IniPinFunc_EMC_Addr(void)
{
THdPinFuncItem_st  stPinFunc;
U8 pinPort;
	
	stPinFunc.pin_PERIPH = U_Periph_P4_PH;
	stPinFunc.pin_BASE   = U_PIN_PE_4;
	stPinFunc.pin_PORT   = 0;
	
	for(pinPort=0; pinPort<=31; pinPort++)
	{
		stPinFunc.pin_PORT   = pinPort;
		hdPinFunc_EMC(&stPinFunc);
	}
}


void IniPinFunc_EMC_CtrlLine(void)
{
THdPinFuncItem_st  stPinFunc;
U8 pinPort;
	
	stPinFunc.pin_PERIPH = U_Periph_P2_PH;
	stPinFunc.pin_BASE   = U_PIN_PE_2;
	stPinFunc.pin_PORT   = 14;
	
	for(pinPort=14; pinPort<=31; pinPort++)
	{
		stPinFunc.pin_PORT   = pinPort;
		hdPinFunc_EMC(&stPinFunc);
	}
}


/******************************************************************************
* FUNC: // EMC 引脚
*   IN:
*  OUT: 
// U_PIN_NorFlash_Data_FUNC ;  P3.0~P3.15 
// U_PIN_NorFlash_Addr_FUNC ;  P4.01(A0) ~ P4.19(A18)
// U_PIN_NorFlash_CtrlLine_FUNC ;  P2.14  ~ P2.15
******************************************************************************/

void IniPinFunc_NorFlash_Data(void)
{
THdPinFuncItem_st  stPinFunc;
U8 pinPort;
	
	stPinFunc.pin_PERIPH = U_Periph_P3_PH;
	stPinFunc.pin_BASE   = U_PIN_PE_3;
	stPinFunc.pin_PORT   = 0;
	
	for(pinPort=0; pinPort<=15; pinPort++)
	{
		stPinFunc.pin_PORT   = pinPort;
		hdPinFunc_EMC(&stPinFunc);
	}
}

void IniPinFunc_NorFlash_Addr(void)
{
THdPinFuncItem_st  stPinFunc;
U8 pinPort;
	
	stPinFunc.pin_PERIPH = U_Periph_P4_PH;
	stPinFunc.pin_BASE   = U_PIN_PE_4;
	stPinFunc.pin_PORT   = 1;
	
	for(pinPort=1; pinPort<=19; pinPort++)
	{
		stPinFunc.pin_PORT   = pinPort;
		hdPinFunc_EMC(&stPinFunc);
	}
}


void IniPinFunc_NorFlash_CtrlLine(void)
{
THdPinFuncItem_st  stPinFunc;
U8 pinPort;

	// 4.24:OE; 4.25:WE;
	stPinFunc.pin_PERIPH = U_Periph_P4_PH;
	stPinFunc.pin_BASE   = U_PIN_PE_4;
	stPinFunc.pin_PORT   = 24;
	
	for(pinPort=24; pinPort<=25; pinPort++)
	{
		stPinFunc.pin_PORT   = pinPort;
		hdPinFunc_EMC(&stPinFunc);
	}
	
	
	// 4.30: CS0-U7
	stPinFunc.pin_PERIPH = U_Periph_P4_PH;
	stPinFunc.pin_BASE   = U_PIN_PE_4;
	stPinFunc.pin_PORT   = 30;
	
	for(pinPort=30; pinPort<=30; pinPort++)
	{
		stPinFunc.pin_PORT   = pinPort;
		hdPinFunc_EMC(&stPinFunc);
	}
	
	
	//2.14:CS1-U8
	stPinFunc.pin_PERIPH = U_Periph_P2_PH;
	stPinFunc.pin_BASE   = U_PIN_PE_2;
	stPinFunc.pin_PORT   = 14;
	
	for(pinPort=14; pinPort<=15; pinPort++)
	{
		stPinFunc.pin_PORT   = pinPort;
		hdPinFunc_EMC(&stPinFunc);
	}
	
	
}


/******************************************************************************
* FUNC: // END
*   IN:
*  OUT: 
******************************************************************************/
