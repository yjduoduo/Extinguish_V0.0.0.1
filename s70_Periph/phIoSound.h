#ifndef __phIoSound_H__
#define __phIoSound_H__
/******************************************************************************
* @file    phIoSound.h
* @author  yx
* @version V1.1
* @date    2013.8.21
* @brief   
* 
#include  "phIoSound.h"
******************************************************************************/

#include  "prjCompileCon.h"

/*================= extern ============================================*/
#ifdef  __phIoSound_C__
#define EX_phIoSound
#else
#define EX_phIoSound extern 
#endif

/*================= 常数 ============================================*/
enum emSoundFunc{ // 按优先级排列，小的优先级高
	U_SOUND_Alarm_FUNC,
	U_SOUND_Fault_FUNC,
	U_SOUND_Action_FUNC,
	U_SOUND_Ack_FUNC,
	U_SOUND_Key_FUNC,
	U_SOUND_Silence_FUNC,
	
	U_SOUND_FUNC_MAX,
};
	
/*================= 私有定义 ======================================*/
	
#ifdef __phIoSound_C__

typedef struct{
	U32 cChkTmrMax;
	U8  cChkSoundFunc;
}TChkSound_st;

enum emChkSoundStep{	
	U_SOUND_ChkStep_Silence1,
	U_SOUND_ChkStep_Alarm,
	U_SOUND_ChkStep_Action,
	U_SOUND_ChkStep_Ack,
	U_SOUND_ChkStep_Key,
	U_SOUND_ChkStep_Silence2,
	
	U_SOUND_ChkStep_MAX,
	
};

const TChkSound_st cstChkSoundStep[U_SOUND_ChkStep_MAX] = {
	{     1, 	U_SOUND_Silence_FUNC},  //U_SOUND_ChkStep_Silence1
	{    15, 	U_SOUND_Alarm_FUNC},  	//U_SOUND_ChkStep_Alarm
	{    25, 	U_SOUND_Action_FUNC},  	//U_SOUND_ChkStep_Action
	{    35, 	U_SOUND_Ack_FUNC},  	//U_SOUND_ChkStep_Ack
	{    40, 	U_SOUND_Key_FUNC},  	//U_SOUND_ChkStep_Key
	{  40+4,	U_SOUND_Silence_FUNC},  //U_SOUND_ChkStep_Silence2
};
#define U_SOUND_ChkTmr_MAX  40+4+1

#endif // __phIoSound_C__
	
	
/*================= 结构体定义 ======================================*/

/*================= 公有结构变量声明 ================================*/

/*================= 私有函数声明 ====================================*/
#ifdef __phIoSound_C__

// 硬件输出
void loadSoundOut(U8 soundFunc);

#endif // __phIoSound_C__
/*================= 公有函数声明 ====================================*/
// EX_phIoSound

extern void InitSoundTask(void);

// 正常时判断按键音，自检时load当前时间段内容。
extern void LoadSoundFuncToHd(void);

extern void SoundNewSet(U8 soundFunc);
extern U8 GetNowSound(void);
extern void SoundSetSilence(void);
extern BOOL bSoundSilence(void);

extern void SoundCheckNewStep(U32 checkTmrNum);
extern void SoundCheckStart(void);
extern void SoundCheckStop(void);

/******************************************************************************
// END :
******************************************************************************/
#endif // __phIoSound_H__

