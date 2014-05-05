#define __lcdPg_Status_C__
/******************************************************************************
* @file    lcdPg_Status.c
* @author  yx
* @version V1.0
* @date    2013-07-01
* @brief   
* 
******************************************************************************/
#include  "lcdPg_Status.h"


//#include "incFile.h"	
#include  "phIoKeyScan.h"


/*================= 常数 ============================================*/

/*================= 结构定义 ========================================*/

/*================= 私有结构变量声明 ================================*/

/*================= 公有函数声明 ====================================*/

/*================= 私有函数声明 ====================================*/

/*=================  ================================================*/
		
/******************************************************************************
* FUNC: //
*   IN: emWinBoolState
*  OUT: 
******************************************************************************/
// 不显示状态栏 //不是subPage // 不是经由menu进入的page
void Ini_WinBoolState(void)
{
U8 mState;

	for(mState=0; mState<U_WIN_BOOL_Sta_MAX; mState++)
	{
		vWinBoolState[mState] = 0;
	}
	
	ClrWinBoolState(U_WIN_ShowState_Sta); // 不显示状态栏
	ClrWinBoolState(U_WIN_PageSubIng_Sta); //不是subPage
	ClrWinBoolState(U_WIN_EntryMenu_Sta); // 不是经由menu进入的page
	
	
	ClrPageKey();
	ClrChangeFuncKey();
}

/******************************************************************************
* FUNC: //
// 页面本身的属性。
// 在自己的 first()里set, 在back()里clr.
*   IN: emWinBoolState
*  OUT: 
******************************************************************************/


void SetWinBoolState(emWinBoolState mState)
{
	if(mState < U_WIN_BOOL_Sta_MAX)
	{
		vWinBoolState[mState] = TRUE;
	}
}

void ClrWinBoolState(emWinBoolState mState)
{
	if(mState < U_WIN_BOOL_Sta_MAX)
	{
		vWinBoolState[mState] = FALSE;
	}
}

BOOL bWinBoolState(emWinBoolState mState)
{
	
	if(mState < U_WIN_BOOL_Sta_MAX)
	{
		return vWinBoolState[mState];
	}
	else
	{
		return FALSE;
	}
}

/******************************************************************************
* FUNC: 
// 留待各页面自己处理的按键：
// 在读出key驱动的有效按键后，若需要页面自己处理，则set.
// 在 LcdPage_function_ ...() 函数后 clr.
*   IN:
*  OUT: 
******************************************************************************/
static BOOL bPageKeyNew = FALSE;
static U8   vPageKeyVaule = ~0;

void SetPageKey(U8 mKeyValue)
{
	if(bKeyValueValid(mKeyValue))
	{
		bPageKeyNew = TRUE;
		vPageKeyVaule = mKeyValue;
	}
}

void ClrPageKey(void)
{
	bPageKeyNew = FALSE;
	vPageKeyVaule = ~0;
}

BOOL bGetPageKey(U8 *pRtnKey)
{
	if(bPageKeyNew)
	{
		*pRtnKey = vPageKeyVaule;
		return TRUE;
	}
	else
	{
		*pRtnKey = ~0;
		return FALSE;
	}
}

/******************************************************************************
* FUNC: 
// // 各处理 改变用途的按键：
// 		在 判断按键时，等同于 user 按键处理。
*   IN:
*  OUT: 
******************************************************************************/
static BOOL bChangeFuncKeyNew = FALSE;
static U8   vChangeFuncKeyVaule = ~0;

void SetChangeFuncKey(U8 mKeyValue)
{
	if(bKeyValueValid(mKeyValue))
	{
		bChangeFuncKeyNew = TRUE;
		vChangeFuncKeyVaule = mKeyValue;
	}
}

void ClrChangeFuncKey(void)
{
	bChangeFuncKeyNew = FALSE;
	vChangeFuncKeyVaule = ~0;
}

BOOL bGetChangeFuncKey_andClr(U8 *pRtnKey)
{
	if(bChangeFuncKeyNew)
	{
		*pRtnKey = vChangeFuncKeyVaule;
		bChangeFuncKeyNew = FALSE;
		return TRUE;
	}
	else
	{
		*pRtnKey = ~0;
		return FALSE;
	}
}

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/


/******************************************************************************
* FUNC: // END
*   IN:
*  OUT: 
******************************************************************************/
