#ifndef __phIoKeyScan_H__
#define __phIoKeyScan_H__
/******************************************************************************
* @file    phIoKeyScan.h
* @author  yx
* @version V1.1
* @date    2013.8.21
* @brief   
* 
#include  "phIoKeyScan.h"
******************************************************************************/

#include  "prjCompileCon.h"
#include  "keyBufJdgLib_Inc_Extern.h"
/*================= extern ============================================*/
#ifdef  __phIoKeyScan_C__
#define EX_phIoKeyScan
#else
#define EX_phIoKeyScan extern 
#endif

/*================= 常数 ============================================*/
// 用户数字键或功能键的定义:
typedef enum { 
	
	U_KEY_Fig_Max = 10,
		
	U_KEY_Star = 10,
	U_KEY_Pound, // # 	//11
	U_KEY_Auto, 
		
	U_KEY_Up,
	U_KEY_Down,
	U_KEY_Left,
	U_KEY_Right,
	U_KEY_Enter,
	
	U_KEY_Return, // 18
	U_KEY_Reset,
	U_KEY_Silence,
	
	U_KEY_MAX,  // < U_HD_KEY_BIT_MAX
	
	U_KEY_Esc = (U_KEY_BOARD_MAX + U_KEY_Return),
	
	// 从 U_KEY_BOARD_MAX 开始，定义长按键的功能。
	// 无长按功能的，地址不能被占用。
	
}emKey;
	
#define  bKeyValueValid(__mKeyVal__)   \
				((__mKeyVal__) < (U_KEY_FUNCTION_MAX))
	
	
/*================= 常数 ============================================*/
// 与扫描相关的定义 放这里：



/*================= 结构体定义 ======================================*/



/*================= 私有结构变量声明 ================================*/
#ifdef __phIoKeyScan_C__

void KeyNewScanResult(U32 scanBits); //扫描结果

#endif // __phIoKeyScan_C__

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


/*================= 公有函数声明 ====================================*/
// EX_phIoKeyScan

extern void InitKeyScanTask(void);


extern BOOL bNeedKeySound(void);

// 中断里，或者保证一定时间内一定执行一次
extern void Key_Read_And_ScanOut(void);

/******************************************************************************
// END :
******************************************************************************/
#endif // __phIoKeyScan_H__

