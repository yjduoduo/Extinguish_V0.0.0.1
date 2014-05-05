
#define __phIoKeyScan_C__
/******************************************************************************
* @file    phIoKeyScan.c
* @author  yx
* @version V1.1
* @date    2013.8.21
* @brief   
* 
* V1.1, 按键一直按下做连续输入，U_KeyEnter_TmrContinueMax; 2013.8.21
* V1.0, 2012-01-05
******************************************************************************/	
#include  "phIoKeyScan.h"


#include  "tmrTick.h"
#include  "bufCircle.h"
#include  "hwEx10_GpioDef.h"

#include  "keyBufJdgLib_incOut.h"  // extern BOOL bHaveKeyValidDown(void);

// #include "incFile.h"

/*================= 常数 ============================================*/

#define U_KEY_BUF_MAX   		20 // 20*35ms 内，必须查一次buf，否则有按键采样丢掉。

/*================= 常数 ============================================*/
// phIoKeyBufJudge 用:

#define U_KEY_SCAN_SW_NUM    U_HD_KEY_BIT_MAX // 扫描按键的个数

// 按键属性定义：
// 与扫描相关的按键号、功能定义：
const TConstEveryKey cstEveryKey[U_KEY_SCAN_SW_NUM]=
{
	// have_long, KeySchId, NeedMm, KeyNumber.
	{0, 3,0, 1}, 			{0,10,0, 4}, 			{0,17,0, 7}, 
	{0, 4,0, 2}, 			{0,11,0, 5}, 			{0,18,0, 8},
	{0, 5,0, 3}, 			{0,12,0, 6}, 			{0,19,0, 9},  
	{0, 6,0, U_KEY_Star}, 	{0,13,0, U_KEY_Pound},	{0,20,0, 0},  
	{0, 7,0, U_KEY_Auto}, 	{0,14,0, U_KEY_Left}, 	{0,21,0, U_KEY_Reset},  
	{0, 8,0, U_KEY_Up}, 	{0,15,0, U_KEY_Enter},	{0,22,0, U_KEY_Down},  
	{1, 9,0, U_KEY_Return}, {0,16,0, U_KEY_Right},	{0,23,0, U_KEY_Silence},  
	
};
	
/*================= 结构定义 ========================================*/

typedef struct{
	TBufCircle stPoint;
	U32 stBuf[U_KEY_BUF_MAX];
	
	
	U8 scanNum;
	U32 scanInAll;
		
}TKeyScanTask_st;

/*================= 私有结构变量声明 ================================*/
TKeyScanTask_st  stKeyScanTask;

/*================= 公有函数声明 ====================================*/

/*================= 私有函数声明 ====================================*/

/*=================  ================================================*/
		
/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
void InitKeyScanTask(void)
{

	IniGpioKey();
	
	BufCircleIni(U_KEY_BUF_MAX, &stKeyScanTask.stPoint);
	
	
	stKeyScanTask.scanNum = 0;
	Key_ScanOut(stKeyScanTask.scanNum);
	stKeyScanTask.scanInAll = 0;
}



/******************************************************************************
* FUNC: // 按键采样结果
*   IN: // 接收的扫描数据，bit=1表示有按键。
*  OUT: 
******************************************************************************/

void KeyNewScanResult(U32 scanBits)
{
	U32 in;
	
	if(bFullBufCircle(&stKeyScanTask.stPoint))
	{
		return;
	}
	in = BufCircle_GetIn(&stKeyScanTask.stPoint);
	stKeyScanTask.stBuf[in] = scanBits;
	
	BufCircle_InInc(&stKeyScanTask.stPoint);
}


/******************************************************************************
* FUNC: // 读取队列里的扫描 1 cycle 结果
******************************************************************************/
BOOL GetKeyScanBuf(U32 *pRtnScanValue)
{
	U32 out;
	
	if(bEmptyBufCircle(&stKeyScanTask.stPoint))
	{
		return FALSE;
	}
	out = BufCircle_GetOut(&stKeyScanTask.stPoint);
	*pRtnScanValue = stKeyScanTask.stBuf[out];
	BufCircle_OutInc(&stKeyScanTask.stPoint);
	
	return TRUE;
}


/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
//按键保持时间。超时，自动clr.
void TmrStart_KeySave(void)
{
	SetTmrTickTask(TASK_KeyHold, TMR_KeyHold);
}

void TmrStop_KeySave(void)
{
	KillTickTask(TASK_KeyHold);
}

void TmrJudge_KeySave(void)
{
	if(GetTickTaskStatus(TASK_KeyHold))
	{
		TmrArrived_KeySave();
		TmrStop_KeySave();
	}
}

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
BOOL bNeedKeySound(void)
{
	return bHaveKeyValidDown();
}

/******************************************************************************
* FUNC: //按键采样
******************************************************************************/
/******************************************************************************
* FUNC: // 按键扫描部分：
*   IN:
*  OUT: 
******************************************************************************/
// 中断里，或者保证一定时间内一定执行一次
void Key_Read_And_ScanOut(void)
{
U8 mKeyScanIn;

	mKeyScanIn = GpioKey_In();
	stKeyScanTask.scanInAll |= 
				((mKeyScanIn & U_Gpio_Key_ScanIn_MASK)
				<< (stKeyScanTask.scanNum * U_Gpio_Key_ScanIn_MAX));
	
	stKeyScanTask.scanNum++;
	if(stKeyScanTask.scanNum >= U_Gpio_Key_ScanOut_MAX)
	{
		stKeyScanTask.scanNum = 0;
		KeyNewScanResult(~stKeyScanTask.scanInAll);
		stKeyScanTask.scanInAll = 0;
	}
	Key_ScanOut(stKeyScanTask.scanNum);

}


/******************************************************************************
* FUNC: // 扫描按键的个数。
*   IN:
*  OUT: 
******************************************************************************/

U8 GetScanKeyNum(void)
{
	return U_KEY_SCAN_SW_NUM;
}

/******************************************************************************
* FUNC: // TConstEveryKey 的定义
******************************************************************************/

BOOL GetConstEveryKey(U8 mScanKey, TConstEveryKey **pEveryKey)
{
	if(mScanKey >= U_KEY_SCAN_SW_NUM)
	{
		return FALSE;
	}
	
	*pEveryKey = (TConstEveryKey*)(&cstEveryKey[mScanKey]);
	return TRUE;
}

/******************************************************************************
* FUNC: // END
*   IN:
*  OUT: 
******************************************************************************/
