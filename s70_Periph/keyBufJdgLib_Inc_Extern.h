#ifndef __keyBufJdgLib_Inc_Extern_H__
#define __keyBufJdgLib_Inc_Extern_H__
/******************************************************************************
* @file    keyBufJdgLib_Inc_Extern.h
* @author  yx
* @version V1.4
* @date    2013-09-29
* @brief   keyBufJdgLib 的 head文件。
* 
* V1.4, 2013-09-29
*		按键修改按下和等待的时间。emKeyDownTmr
* V1.3,2013-08-28
*
*
#include  "keyBufJdgLib_Inc_Extern.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

/*================= 常数 ============================================*/
#define U_KEY_JUDGE_MAX    32 // lib最多判断32个按键


#define U_KEY_BOARD_MAX  		U_KEY_JUDGE_MAX // 长按键
#define U_KEY_FUNCTION_MAX		(U_KEY_BOARD_MAX + U_KEY_JUDGE_MAX) // 长按键

/*================= 常数 ============================================*/

// 需要根据扫描一周的时间调整。
//5ms*7行扫描，35ms间隔
enum emKeyDownTmr{
	U_KeyEnter_Tmr_MAX	= 200,  //按键按下的最长时间,放计数溢出.在DITHER~LONG之间表示无LONG.
	U_KeyEnter_TmrDither = 3, //2  //抖动   2*35ms=70ms
	U_KeyEnter_TmrContinueSound = 3,//非长按键，去抖后buzzer响的时间。U_KeyEnter_TmrDither+1
	U_KeyEnter_TmrContinueMax = 20, //5 //非长按键，按下但无反应的时间。 8*35ms=280ms, 无长按功能，连续按下时计多个按键。
	
	// 长按功能与短按不同的按键，长时间按下：
	U_KeyEnter_TmrLongKey = 60, //28    //28*35ms=980ms
	
};
	
/*================= 结构体定义 ======================================*/

// 在应用程序的keyScan.c里定义。
// 按键属性定义：
// 与扫描相关的按键号、功能定义：
typedef struct TConstEveryKey_st{
	U8 have_long;     //1=需要长按键
	U8 KeySchId;      //扫描的按键顺序号和原理图的对应关系
	U8 NeedPassWord;  // emUserGrade
	U8 KeyNumber;     // emKey
}TConstEveryKey;

/*================= 公有函数声明 phIoKeyBufJudge 用 =================*/
// EX_phIoKeyScan

// 扫描按键的个数。
extern U8 GetScanKeyNum(void);

// TConstEveryKey 的定义
extern BOOL GetConstEveryKey(U8 mScanKey, TConstEveryKey **pEveryKey);

// 读取队列里的扫描 1 cycle 结果
extern BOOL GetKeyScanBuf(U32 *pRtnScanValue);

//按键保持时间。超时，自动clr.
extern void TmrStart_KeySave(void);
extern void TmrStop_KeySave(void);
extern void TmrJudge_KeySave(void);

/*================= 公有函数声明 phIoKeyBufJudge 用 =================*/
// EX_lcdSub_Pssw

// 按键 需要判断userGrade
extern void Pssw_KeyNeedPssw(U8 mKeyValue, U8 needUserGrade);

/******************************************************************************
// END :
******************************************************************************/
#endif // __keyBufJdgLib_Inc_Extern_H__

