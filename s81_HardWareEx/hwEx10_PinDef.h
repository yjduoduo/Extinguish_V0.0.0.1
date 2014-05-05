#ifndef __hwEx10_PinDef_H__
#define __hwEx10_PinDef_H__
/******************************************************************************
* @file    hwEx10_PinDef.h
* @author  yx
* @version V1.0
* @date    2013-07-01
* @Board   JadeBird Extinguish V1.0
* @brief   
* 
#include  "hwEx10_PinDef.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

/*================= extern ============================================*/
#ifdef  __hwEx10_PinDef_C__
#define EX_hwEx10_PinDef
#else
#define EX_hwEx10_PinDef extern 
#endif
/*================= 常数 ============================================*/
enum emPinFunc
{	
	U_PIN_Can1_Rx_FUNC,
	U_PIN_Can1_Tx_FUNC,
	U_PIN_Can2_Rx_FUNC,
	U_PIN_Can2_Tx_FUNC,
	U_PIN_Uart0Rx_FUNC,
	U_PIN_Uart0Tx_FUNC,
	U_PIN_I2cSda_FUNC,
	U_PIN_I2cScl_FUNC,
	U_PIN_UsbD0p_FUNC,
	U_PIN_UsbD1r_FUNC,
	U_PIN_AdPwrCheckSwitch_FUNC, //  AD0[6];
	U_PIN_Buzzer_FUNC,
	
};

// U_PIN_EMC_Data_FUNC ;  P3.0~P3.31 
// U_PIN_EMC_Addr_FUNC ;  P4.00(A0) ~ P4.31(A31)
// U_PIN_EMC_CtrlLine_FUNC ;  P2.14  ~ P2.31
	
// U_PIN_NorFlash_Data_FUNC ;  P3.0~P3.15 
// U_PIN_NorFlash_Addr_FUNC ;  P4.01(A0) ~ P4.19(A18)
// U_PIN_NorFlash_CtrlLine_FUNC ;  P2.14  ~ P2.15
	
/*================= 结构体定义 ======================================*/
#ifdef  __hwEx10_PinDef_C__

#endif // __hwEx10_PinDef_C__
/*================= 公有结构变量声明 ================================*/

/*================= 私有函数声明 ====================================*/
#ifdef  __hwEx10_PinDef_C__

#endif  //__hwEx10_PinDef_C__
/*================= 公有函数声明 ====================================*/
//EX_hwEx10_PinDef 
extern void IniPinFunc(void);

extern void IniPinFunc_Can1(void);
extern void IniPinFunc_Can2(void);
	
extern void IniPinFunc_Uart0(void);
	
extern void IniPinFunc_IIC(void);
	
extern void IniPinFunc_USB(void);
	
extern void IniPinFunc_AD_PwrCheckSwitch(void);
	
extern void IniPinFunc_PWM_Buzzer(void);

extern void IniPinFunc_EMC_Data(void);
extern void IniPinFunc_EMC_Addr(void);
extern void IniPinFunc_EMC_CtrlLine(void);

extern void IniPinFunc_NorFlash_Data(void);
extern void IniPinFunc_NorFlash_Addr(void);
extern void IniPinFunc_NorFlash_CtrlLine(void);

/******************************************************************************
// END :
******************************************************************************/
#endif // __hwEx10_PinDef_H__

