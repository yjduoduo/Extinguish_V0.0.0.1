
#define __phIoLed_C__
/******************************************************************************
* @file    phIoLed.c
* @author  yx
* @version V1.0
* @date    2012-01-05
* @brief   
* 
*  bit=1 =亮。
******************************************************************************/	
#include  "phIoLed.h"

#include  "hwEx10_GpioDef.h"
#include  "tmrTick.h"

// #include "incFile.h"

/*================= 常数 ============================================*/
#define U_LED_SCAN_NUM    U_Gpio_Led_FUNC_MAX // 扫描灯的个数

/*================= 私有结构变量声明 ================================*/

typedef struct{
	U32 vLedFuncBits;  //系统功能。
	
	BOOL bCheckIng;
	U32  vChkTmr;
	
	U32  vLedChkBits;  //灯检时 状态
	
	U8 vLedState[U_LED_FUNC_MAX];
}TPhIoLed_st;

TPhIoLed_st stVPhIoLed;

/*================= 结构定义 ========================================*/


typedef struct{
	U32 cChkTmrMax;
	U32  cChkLedFuncBits;
}TChkLed_st;

enum emChkLedStep{	
	U_LED_ChkStep_ALL_OFF1,
	U_LED_ChkStep_ALL_ON1,
	U_LED_ChkStep_ALL_OFF2,
	U_LED_ChkStep_Sigle,
	U_LED_ChkStep_ALL_OFF3,
	
	U_LED_ChkStep_MAX,
	
};

#define U_SelfCheck_LED_MAX   U_LED_SCAN_NUM
const TChkLed_st cstChkLedStep[U_LED_ChkStep_MAX] = {
	{     1, 					0},  //U_LED_ChkStep_ALL_OFF1
	{     5, 					~0},  	//U_LED_ChkStep_ALL_ON1
	{     7, 					0},  	//U_LED_ChkStep_ALL_OFF2
	{  7+U_SelfCheck_LED_MAX, 		1},  	//U_LED_ChkStep_Sigle
	{  7+U_SelfCheck_LED_MAX+1, 	0},  	//U_LED_ChkStep_ALL_OFF3
};
#define U_LED_ChkTmr_MAX 	7+U_SelfCheck_LED_MAX+2

const U32 cstLedChkSequ[U_SelfCheck_LED_MAX] = 
{
	(1<<0), (1<<5), (1<<8),
	(1<<1), (1<<2), (1<<6),
	(1<<3), (1<<7), (1<<4),
};
	
/*================= 公有函数声明 ====================================*/

/*================= 私有函数声明 ====================================*/

/*=================  ================================================*/

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
void InitLedTask(void)
{
U8 ii;

	for(ii=0; ii<U_LED_FUNC_MAX; ii++)
	{
		stVPhIoLed.vLedState[ii] = emLedSta_OFF;
	}
	stVPhIoLed.vLedFuncBits = 0;
	
	stVPhIoLed.bCheckIng = FALSE;
	stVPhIoLed.vChkTmr = 0;
	stVPhIoLed.vLedChkBits = 0;
	
	IniGpioLed();
	
	SetTmrTickTask(TASK_LedBlink, TMR_LedBlink);
	
}

void ExecLedTask(void)
{
U8 mLed;
	if(!GetTickTaskStatus(TASK_LedBlink))
	{
		return;
	}
	
	for(mLed=0; mLed<U_LED_FUNC_MAX; mLed++)
	{
		switch(stVPhIoLed.vLedState[mLed])
		{
			case emLedSta_ON:
				stVPhIoLed.vLedFuncBits |= (1 << mLed);
				break;
			case emLedSta_BLINK:
				stVPhIoLed.vLedFuncBits ^= (1 << mLed);
				break;
				
			case emLedSta_OFF:
			default:
				stVPhIoLed.vLedFuncBits &= ~(1 << mLed);
				break;
		}
	}
		
	
}

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
	
void LedFuncAllOn(void)
{
	stVPhIoLed.vLedFuncBits = ~0;
}
void LedFuncAllOff(void)
{
	stVPhIoLed.vLedFuncBits = 0;
}
	
/******************************************************************************
* FUNC: //
******************************************************************************/
void LedFuncBlink(U8 vLedFunc)
{
	if(vLedFunc >= U_LED_SCAN_NUM)
	{
		return;
	}
	stVPhIoLed.vLedState[vLedFunc] = emLedSta_BLINK;
}

void LedFuncOn(U8 vLedFunc)
{
	if(vLedFunc >= U_LED_SCAN_NUM)
	{
		return;
	}
	stVPhIoLed.vLedState[vLedFunc] = emLedSta_ON;
	stVPhIoLed.vLedFuncBits |= (1 << vLedFunc);
}


void LedFuncOff(U8 vLedFunc)
{
	if(vLedFunc >= U_LED_SCAN_NUM)
	{
		return;
	}
	stVPhIoLed.vLedState[vLedFunc] = emLedSta_OFF;
	stVPhIoLed.vLedFuncBits &= ~(1 << vLedFunc);	
}



/******************************************************************************
* FUNC: // intr 随 Exec_IoLedKeyScan()
******************************************************************************/

void LoadLedFuncToHd(void)
{
	if(stVPhIoLed.bCheckIng)
	{
		GpioLed_All_Out(stVPhIoLed.vLedChkBits);
	}
	else
	{
		GpioLed_All_Out(stVPhIoLed.vLedFuncBits);
	}
	
}



/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

//用stVPhIoLed.vChkTmr，是各检测的周期不同，而且防止初始化和 NewStep之间有更新。
void LedCheckNewStep(U32 checkTmrNum)
{
	U8 chkStep;
	U8 ledSequ;
	
	stVPhIoLed.vChkTmr = checkTmrNum;	
	if(stVPhIoLed.vChkTmr >= U_LED_ChkTmr_MAX)
	{
		stVPhIoLed.vChkTmr %= U_LED_ChkTmr_MAX;
	}
	
	for(chkStep=0; chkStep<U_LED_ChkStep_MAX; chkStep++)
	{
		if(stVPhIoLed.vChkTmr < cstChkLedStep[chkStep].cChkTmrMax)
		{
			break;
		}
	}
	
	if(chkStep>=U_LED_ChkStep_MAX)
	{
		stVPhIoLed.vLedChkBits = 0;
	}
	else
	{
		if(chkStep != U_LED_ChkStep_Sigle)
		{
			stVPhIoLed.vLedChkBits = cstChkLedStep[chkStep].cChkLedFuncBits;
		}
		else
		{
			ledSequ = stVPhIoLed.vChkTmr - cstChkLedStep[U_LED_ChkStep_ALL_OFF2].cChkTmrMax;
			if(ledSequ >= U_SelfCheck_LED_MAX)
			{
				ledSequ %= U_SelfCheck_LED_MAX;
			}
			stVPhIoLed.vLedChkBits = cstLedChkSequ[ledSequ];
		}
	}
	
}

/******************************************************************************
* FUNC: //
******************************************************************************/
void LedCheckStart(void)
{
	stVPhIoLed.bCheckIng = TRUE;
	stVPhIoLed.vChkTmr = 0;
	stVPhIoLed.vLedChkBits = 0;
}

void LedCheckStop(void)
{
	stVPhIoLed.bCheckIng = FALSE;
	stVPhIoLed.vChkTmr = 0;
	stVPhIoLed.vLedChkBits = 0;
}

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

