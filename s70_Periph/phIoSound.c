
#define __phIoSound_C__
/******************************************************************************
* @file    phIoSound.c
* @author  yx
* @version V1.1
* @date    2013.8.21
* @brief   
* 
* V1.1， 加SoundSilence();  bSoundSilence();   loadSoundOut(); 
		2013.8.21
* V1.0， 2012-01-05
******************************************************************************/
#include  "phIoSound.h"


#include  "hwEx10_PinDef.h"

#include  "phIoKeyScan.h"
// extern BOOL bNeedKeySound(void);


/*================= 常数 ============================================*/

/*================= 结构定义 ========================================*/

/*================= 私有结构变量声明 ================================*/

typedef struct{
	U8 vSoundFunc;  //emSoundFunc 系统功能。
	
	BOOL bCheckIng;
	U32  vChkTmr;
	
	U8 vSoundChkFunc;  //emSoundFunc 灯检时 状态
	
	U8 vSoundNowOut;
}TPhIoSound_st;

TPhIoSound_st stVPhIoSound;

/*================= 公有函数声明 ====================================*/

/*================= 私有函数声明 ====================================*/

/*================= 常数 ============================================*/

/*=================  ================================================*/
/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

void InitSoundTask(void)
{
	IniPinFunc_PWM_Buzzer();
	
	stVPhIoSound.vSoundFunc   = U_SOUND_Silence_FUNC;
	stVPhIoSound.vSoundNowOut = U_SOUND_Silence_FUNC;
	
	stVPhIoSound.bCheckIng = FALSE;
	stVPhIoSound.vChkTmr = 0;
	stVPhIoSound.vSoundChkFunc  = U_SOUND_Silence_FUNC;
}
		
/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

void SoundNewSet(U8 soundFunc)
{
	if(soundFunc < U_SOUND_FUNC_MAX)
	{
		stVPhIoSound.vSoundFunc = soundFunc;
	}
}

U8 GetNowSound(void)
{
	return stVPhIoSound.vSoundFunc;
}


void SoundSetSilence(void)
{
	SoundNewSet(U_SOUND_Silence_FUNC);
}

BOOL bSoundSilence(void)
{
	return ( (stVPhIoSound.vSoundFunc == U_SOUND_Silence_FUNC)
		   ||(stVPhIoSound.vSoundFunc == U_SOUND_Key_FUNC)
		   );
}

/******************************************************************************
* FUNC: // intr 随 Exec_IoLedKeyScan()
******************************************************************************/

// 正常时判断按键音，自检时load当前时间段内容。
void LoadSoundFuncToHd(void)
{
	U8 soundFunc;
	
	if(stVPhIoSound.bCheckIng)
	{
		soundFunc = stVPhIoSound.vSoundChkFunc;
	}
	else
	{
		soundFunc = stVPhIoSound.vSoundFunc;
		if(soundFunc == U_SOUND_Silence_FUNC)
		{
			if(bNeedKeySound())
			{
				soundFunc = U_SOUND_Key_FUNC;
			}
		}
	}
	
	loadSoundOut(soundFunc);
}


// 硬件输出
void loadSoundOut(U8 soundFunc)
{
	if(soundFunc >= U_SOUND_FUNC_MAX)
	{
		return;
	}
	
	if(stVPhIoSound.vSoundNowOut != soundFunc)
	{
		stVPhIoSound.vSoundNowOut = soundFunc;
		
		// HdSoundSet(hdSoundPin); // 仅在有变化时更新
	}
	
	
}

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

	
//用stVPhIoSound.vChkTmr，是各检测的周期不同，而且防止初始化和 NewStep之间有更新。
void SoundCheckNewStep(U32 checkTmrNum)
{
	U8 chkStep;
	
	stVPhIoSound.vChkTmr = checkTmrNum;	
	if(stVPhIoSound.vChkTmr >= U_SOUND_ChkTmr_MAX)
	{
		stVPhIoSound.vChkTmr %= U_SOUND_ChkTmr_MAX;
	}
	
	for(chkStep=0; chkStep<U_SOUND_ChkStep_MAX; chkStep++)
	{
		if(stVPhIoSound.vChkTmr >= cstChkSoundStep[chkStep].cChkTmrMax)
		{
			break;
		}
	}
	
	if(chkStep<U_SOUND_ChkStep_MAX)
	{
		stVPhIoSound.vSoundChkFunc = cstChkSoundStep[chkStep].cChkSoundFunc;
	}
	
}

/******************************************************************************
* FUNC: //
******************************************************************************/
void SoundCheckStart(void)
{
	stVPhIoSound.bCheckIng = TRUE;
	stVPhIoSound.vChkTmr = 0;
	stVPhIoSound.vSoundChkFunc = U_SOUND_Silence_FUNC;
}

void SoundCheckStop(void)
{
	stVPhIoSound.bCheckIng = FALSE;
	stVPhIoSound.vChkTmr = 0;
	stVPhIoSound.vSoundChkFunc = U_SOUND_Silence_FUNC;
}

/******************************************************************************
* FUNC: //
******************************************************************************/



/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

