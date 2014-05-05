#ifndef __phIoLed_H__
#define __phIoLed_H__
/******************************************************************************
* @file    phIoLed.h
* @author  yx
* @version V1.0
* @date    2012-01-05
* @brief   
* 
#include  "phIoLed.h"
******************************************************************************/

#include  "prjCompileCon.h"

/*================= extern ============================================*/
#ifdef  __phIoLed_C__
#define EX_phIoLed
#else
#define EX_phIoLed extern 
#endif

/*================= 常数 ============================================*/
enum emLed{
	U_LED_Alarm,
	U_LED_Manu,
	U_LED_Auto,
	U_LED_silence,
	U_LED_pwrMain,
	U_LED_Communicate,
	U_LED_ChkPwrSwitch,
	U_LED_pwrBty,
	U_LED_SysFault,
		
	
	U_LED_FUNC_MAX,
};
	
	
/*================= 私有定义 ======================================*/
	
#ifdef __phIoLed_C__
typedef enum{
	emLedSta_OFF,
	emLedSta_ON,
	emLedSta_BLINK,
}emLedState;

#endif // __phIoLed_C__
/*================= 结构体定义 ======================================*/

/*================= 公有结构变量声明 ================================*/

/*================= 公有函数声明 ====================================*/
//
EX_phIoLed void InitLedTask(void);
EX_phIoLed void ExecLedTask(void);
EX_phIoLed void LoadLedFuncToHd(void);

EX_phIoLed void LedFuncOn(U8 vLedFunc);
EX_phIoLed void LedFuncOff(U8 vLedFunc);
EX_phIoLed void LedFuncBlink(U8 vLedFunc);
EX_phIoLed void LedFuncAllOn(void);
EX_phIoLed void LedFuncAllOff(void);



EX_phIoLed void LedCheckStart(void);
EX_phIoLed void LedCheckStop(void);
EX_phIoLed void LedCheckNewStep(U32 checkTmrNum);

/******************************************************************************
// END :
******************************************************************************/
#endif // __phIoLed_H__

