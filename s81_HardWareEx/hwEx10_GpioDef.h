#ifndef __hwEx10_GpioDef_H__
#define __hwEx10_GpioDef_H__
/******************************************************************************
* @file    hwEx10_GpioDef.h
* @author  yx
* @version V1.1
* @date    2013-10-09 
* @Board   JadeBird Extinguish V1.0
* @brief   
* 
* V1.1 2013-10-09 12:03 
*		改变LCD控制pin输出后的延时时间。  U_LCD_PIN_DRIVER_USE_LIB 
* V1.0 2013-07-01
#include  "hwEx10_GpioDef.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

/*================= extern ============================================*/
#ifdef  __hwEx10_GpioDef_C__
#define EX_hwEx10_GpioDef
#else
#define EX_hwEx10_GpioDef extern 
#endif
/*================= 常数 ============================================*/
enum emGpioLed
{
	U_Gpio_Led_Alarm_FUNC,
	U_Gpio_Led_Auto_FUNC,
	U_Gpio_Led_Manu_FUNC,
	U_Gpio_Led_Silence_FUNC,
	U_Gpio_Led_PwrMain_FUNC,
	U_Gpio_Led_Run_FUNC,
	U_Gpio_Led_PwrCheckSw_FUNC,
	U_Gpio_Led_PwrBaty_FUNC,
	U_Gpio_Led_CpuFault_FUNC,
	
	U_Gpio_Led_FUNC_MAX,
};

enum emGpioKey
{
	U_Gpio_KeyIn_1_FUNC,
	U_Gpio_KeyIn_2_FUNC,
	U_Gpio_KeyIn_3_FUNC,
	U_Gpio_KeyScan_1_FUNC,
	U_Gpio_KeyScan_2_FUNC,
	U_Gpio_KeyScan_3_FUNC,
	U_Gpio_KeyScan_4_FUNC,
	U_Gpio_KeyScan_5_FUNC,
	U_Gpio_KeyScan_6_FUNC,
	U_Gpio_KeyScan_7_FUNC,
	
	U_Gpio_Key_FUNC_MAX,
};
#define U_Gpio_Key_ScanIn_MAX  3
#define U_Gpio_Key_ScanIn_MASK  0x07
#define U_Gpio_Key_ScanOut_MAX   7
#define U_Gpio_Key_Scan_L   U_Gpio_KeyScan_1_FUNC
#define U_Gpio_Key_Scan_H   (U_Gpio_KeyScan_7_FUNC+1)

#define U_HD_KEY_BIT_MAX    (3*7)
	
	
enum emGpioLcd
{
	U_Gpio_Lcd_Light_FUNC,
	U_Gpio_Lcd_CS1_FUNC,
	U_Gpio_Lcd_CS2_FUNC,
	U_Gpio_Lcd_CS3_FUNC,
	U_Gpio_Lcd_RS_D_I_FUNC,
	U_Gpio_Lcd_R_W_FUNC,
	U_Gpio_Lcd_EN_FUNC,
	U_Gpio_Lcd_RST_FUNC,
	U_Gpio_Lcd_D0_FUNC,
	U_Gpio_Lcd_D1_FUNC,
	U_Gpio_Lcd_D2_FUNC,
	U_Gpio_Lcd_D3_FUNC,
	U_Gpio_Lcd_D4_FUNC,
	U_Gpio_Lcd_D5_FUNC,
	U_Gpio_Lcd_D6_FUNC,
	U_Gpio_Lcd_D7_FUNC,
	
	U_Gpio_Lcd_FUNC_MAX,
};
	
enum emGpioPwrState
{
	U_Gpio_Pwr_Main_FUNC,
	U_Gpio_Pwr_Baty_FUNC,
	U_Gpio_Pwr_Link_FUNC,
	
	U_Gpio_PwrState_FUNC_MAX,
	
	
	U_Gpio_PwrCheckSwitch_FUNC, //借用这里进行类型分别
};
	
enum emGpioExStore
{
	
	U_Gpio_Fls_CS0_FUNC,
	U_Gpio_Fls_CS1_FUNC,
	U_Gpio_Ram_CS2_FUNC,
	U_Gpio_Ram_R_B_FUNC,
	//U_Gpio_Ram_CLE_FUNC,
	//U_Gpio_Ram_ALE_FUNC,
	
	U_Gpio_ExStore_FUNC_MAX,
};
	
/*================= 结构体定义 ======================================*/

/*================= 公有结构变量声明 ================================*/

/*================= 私有函数声明 ====================================*/
#ifdef  __hwEx10_GpioDef_C__
// emGpioLed
// emGpioKey
// emGpioLcd
// emGpioPwrState
// emGpioExStore

// const THdPinItem_st  cstGpioExStore[];
// const THdPinItem_st  cstGpioPwrState[];
// const THdPinItem_st  cstGpioLcd[];
// const THdPinItem_st  cstGpioLed[];
// const THdPinItem_st  cstGpioKey[];

#endif  //__hwEx10_GpioDef_C__
/*================= 公有函数声明 ====================================*/
//EX_hwEx10_GpioDef 

extern void IniSysPinPower(void); // pin 电源

extern void IniGpioExStore(void);
extern void gpioExStoreAllForbid(void);
extern void GpioExStoreSelFls0(void);
extern void GpioExStoreSelFls1(void);
extern void GpioExStoreSelRam(void);



extern void IniGpioPwrState(void);
// OUT: U_ERR, U_USUAL :
extern unsigned char GetGpioPwrState(unsigned char mGpioPwrState);


// extern void GpioLcd_Delay_RS(void); // command  data 
extern void IniGpioLcd(void);
extern void GpioLcd_Light(unsigned char mState);
extern void GpioLcd_CS_AllOff(void);
extern void GpioLcd_SelCsX_1(unsigned char mLcdCs);
extern void GpioLcd_SelCsX_0(unsigned char mLcdCs);
extern void GpioLcd_RS_Command(void); // RS
extern void GpioLcd_RS_Data(void);
extern void GpioLcd_RW_Read(void);
extern void GpioLcd_RW_Write(void);
extern void GpioLcd_EnLock_1_Ready(void);
extern void GpioLcd_EnLock_0_Go(void);
extern void GpioLcd_Rst_0_reset(void);
extern void GpioLcd_Rst_1_work(void);
extern void GpioLcd_DataDir_Out(void);
extern void GpioLcd_DataDir_In(void);
extern void GpioLcd_DataOut(unsigned char mData);
extern unsigned char GpioLcd_DataIn(void);



extern void IniGpioLed(void);
extern void GpioLed_All_On(void);
extern void GpioLed_All_Off(void);
extern void GpioLed_All_Out(unsigned int mLedBits);
extern void GpioLed_On(unsigned char mLed);
extern void GpioLed_Off(unsigned char mLed);

extern void IniGpioKey(void);
// extern void GpioKey_Scan(unsigned char mKeyScan);
extern void Key_ScanOut(unsigned char mKeyScanNum);
extern unsigned char GpioKey_In(void);




/******************************************************************************
// END :
******************************************************************************/
#endif // __hwEx10_GpioDef_H__

