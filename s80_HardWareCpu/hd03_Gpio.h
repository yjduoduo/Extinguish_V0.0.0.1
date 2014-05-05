#ifndef __hd03_Gpio_H__
#define __hd03_Gpio_H__
/******************************************************************************
* @file    hd03_Gpio.h
* @author  yx
* @version V1.0
* @date    2012-01-05
* @Cpu     LPC177x_8x   
* @brief   数字IO
* 
#include  "hd03_Gpio.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

/*================= extern ============================================*/
#ifdef  __hd03_Gpio_C__
#define EX_hd03_Gpio
#else
#define EX_hd03_Gpio extern 
#endif
/*================= 常数 ============================================*/

/*================= 常数 ============================================*/
enum emGpioPeriph{
	U_PIN_PE_0,
	U_PIN_PE_1,
	U_PIN_PE_2,
	U_PIN_PE_3,
	U_PIN_PE_4,
	U_PIN_PE_5,
	U_PIN_PE_Max
};

#define U_PIN_Port_MAX  32
	
enum emGpioDir{ //根据 "lpc177x_8x_gpio"的值
	U_PIN_Input = 0,
	U_PIN_Output = 1,
	U_PIN_InOut_Invalid = ~0,
};
	
enum emGpioOut{ //根据 "lpc177x_8x_gpio"的值
	U_PIN_HIGH = 1,
	U_PIN_LOW = 0,
};
	
enum emGpioPull{ //根据 "lpc177x_8x_gpio"的值 PinSel_BasicMode
	U_PIN_PullNo 	= 0,
	U_PIN_PullDown 	= 1,
	U_PIN_PullUp 	= 2,
	U_PIN_PullTrans = 3,
};


enum emHdPinItem{
	U_PIN_ITEM_PERIPH = 0,
	U_PIN_ITEM_BASE = 1,
	U_PIN_ITEM_PORT = 2,
	U_PIN_ITEM_InOut = 3,
	U_PIN_ITEM_PullHL = 4,
	U_PIN_ITEM_HighLow = 5,
	U_PIN_ITEM_MAX = 6,
};

#define U_PIN_FUNC_IS_GPIO    0 //3bits
	
	
/*================= 结构体定义 ======================================*/
typedef struct{
	unsigned long pin_PERIPH;  //emCpuPeriph 外围设备的号，CPU指定；
	unsigned long pin_BASE;    //emGpioPeriph 
	unsigned long pin_PORT;    // 0~31,
	unsigned long pin_InOut;   // emGpioDir
	unsigned long pin_PullHL;  // emGpioPull
	unsigned long pin_HighLow; // emGpioOut
}THdPinItem_st;
// 注意 按键的扫描线输出 设置 OD = 1.  PINSEL_SetOpenDrainMode

/*================= 结构体定义 ======================================*/

/*================= 公有结构变量声明 ================================*/
/*
typedef struct{
	U8 sequStart;
}TStruct_st;
TStruct_st stStruct;
*/


/*================= 私有函数声明 ====================================*/
#ifdef  __hd03_Gpio_C__

#endif  //__hd03_Gpio_C__
/*================= 公有函数声明 ====================================*/
//EX_hd03_Gpio 

// *   IN: ulPort= emGpioPeriph, [0~5]; 
// *   IN: ucPins[0~31].
// *   IN: pinStatus = U_PIN_HIGH,  U_PIN_LOW.
extern void GpioHigh(unsigned long ulPort, unsigned char ucPins);
extern void GpioLow(unsigned long ulPort, unsigned char ucPins);
extern void GpioSet(unsigned long ulPort, unsigned char ucPins, 
										unsigned char pinStatus);

// *   IN: bitMask: 需要输出的bit为1;
// *   IN: bitValue: 需要HIGH的bit为1;
extern void Gpio_OutSerial(unsigned int ulPort,
					unsigned int bitMask, unsigned int bitValue);
extern void Gpio_DirSerial(unsigned int ulPort,
					unsigned int bitMask, unsigned char mInOut);
extern unsigned int Gpio_PortRead(unsigned int ulPort); // 读整个port.

extern void GpioStr_PinSet(const THdPinItem_st *pHdPin, 
									unsigned char pinStatus);
extern unsigned char GpioStr_PinRead(const THdPinItem_st *pHdPin);

extern void GpioStrIni(const THdPinItem_st *pHdPin);
extern void GpioStr_SetIn(const THdPinItem_st *pHdPin);
extern void GpioStr_SetOut(const THdPinItem_st *pHdPin);

extern void GpioStr_SetOD(const THdPinItem_st *pHdPin);

/******************************************************************************
// END :
******************************************************************************/
#endif // __hd03_Gpio_H__

