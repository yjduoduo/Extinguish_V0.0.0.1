
#define __phIoScan_C__
/******************************************************************************
* @file    phIoScan.c
* @author  yx
* @version V1.0
* @date    2012-01-05
* @brief   
* 
******************************************************************************/
#include  "phIoScan.h"

#include  "phIoLed.h"
#include  "phIoKeyScan.h"
#include  "keyBufJdgLib_incOut.h"

#include  "phIoSound.h"
#include  "phIoPwrChkSwitch.h"
#include  "phIoPwrState.h"

#include  "tmrTick.h"
// #include "incFile.h"	

/*================= ���� ============================================*/

/*================= �ṹ���� ========================================*/

/*================= ˽�нṹ�������� ================================*/

/*================= ���к������� ====================================*/

/*================= ˽�к������� ====================================*/

/*=================  ================================================*/
		
/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
void InitIoScan(void) //Led, Key, Sound
{
	// IniLedKeyPin();
	
	//LED:
	InitLedTask();
	LedFuncAllOff();
	
	LoadLedFuncToHd();
	
	//KEY:
	InitKeyScanTask();
	InitKeyJudgeTask();
		
	//Sound:
	InitSoundTask();
	SoundNewSet(U_SOUND_Silence_FUNC);
	LoadSoundFuncToHd();
	
	
	InitPwrStateTask();
	InitPwrChkSwcTask();
	
	SetTmrTickTask(TASK_IoTaskRefresh, TMR_IoTaskRefresh);
}

/******************************************************************************
* FUNC: //��ʱִ��. ledKey�������ж��ﾫ׼��ʱ��
* //���ж���ִ�У����Բ���ʱ
******************************************************************************/
void ExeInInt_IoLedKeyScan(void)
{
	
	Key_Read_And_ScanOut();	
	LoadLedFuncToHd();	
	LoadSoundFuncToHd();
}

/******************************************************************************
* FUNC: //��ʱִ��. ��������
* //
******************************************************************************/
void Exec_IoLedKeyScan(void)
{
	if(!GetTickTaskStatus(TASK_IoTaskRefresh))
	{
		return;
	}
	
	ExecPwrStateTask();
	ExecPwrChkSwcTask();
	
	Task_ExecKeyTask();
	

	
}


/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

