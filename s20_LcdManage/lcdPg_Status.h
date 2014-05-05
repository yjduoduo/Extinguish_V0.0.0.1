#ifndef __lcdPg_Status_H__
#define __lcdPg_Status_H__
/******************************************************************************
* @file    lcdPg_Status.h
* @author  yx
* @version V1.0
* @date    2013-07-01
* @brief   是否显示状态栏等
* 
#include  "lcdPg_Status.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

/*================= extern ============================================*/
#ifdef  __lcdPg_Status_C__
#define EX_lcdPg_Status
#else
#define EX_lcdPg_Status extern 
#endif
/*================= 常数 ============================================*/

typedef enum {
	
	//当前显示了 状态栏. 有些页面如"回路浏览"可能不显示WinState.
	U_WIN_ShowState_Sta,
		
	//SubPg.first()时, set(U_WIN_PageSubIng_Sta)状态。
	//SubPg.back()时，不返回到菜单。
	// 	clr(U_WIN_PageSubIng_Sta)状态 
	//	+ set parent PageNum 
	//	+ parent.first()，
	U_WIN_PageSubIng_Sta,	
	
	//页面是从menu进入的。相对于从页面直接进入。
	// page.return时，若是从menu进入的，退出到menu页面。
	U_WIN_EntryMenu_Sta,	
	
	// 按键 * # 有输入需求。一般是联动编程。
	// *#在 page 未用到的情况下，兼做 return 功能，
	// 因为无 key-return，而在输入数字的情况，key-left用于移动光标。
	// 若不兼用，用户就只有 key-ese选择了。
	U_WIN_NeedKey_StarPound_Sta, 
	
	// 按键 <-  ->用于翻页
	U_WIN_KeyLR_UseforPageUpDown_Sta, 
	//
	U_WIN_BOOL_Sta_MAX,
	
}emWinBoolState;

	
/*================= 结构体定义 ======================================*/

/*================= 公有结构变量声明 ================================*/

/*================= 私有函数声明 ====================================*/
#ifdef  __lcdPg_Status_C__

	BOOL vWinBoolState[U_WIN_BOOL_Sta_MAX];

#endif  //__lcdPg_Status_C__
/*================= 公有函数声明 ====================================*/
//EX_lcdPg_Status 

// 留待各页面自己处理的按键：
// 在读出key驱动的有效按键后，若需要页面自己处理，则set.
// 在 LcdPage_function_ ...() 函数后 clr.
extern void SetPageKey(U8 mKeyValue);
extern void ClrPageKey(void);
extern BOOL bGetPageKey(U8 *pRtnKey);

// 各处理 改变用途的按键：
void SetChangeFuncKey(U8 mKeyValue);
void ClrChangeFuncKey(void);
BOOL bGetChangeFuncKey_andClr(U8 *pRtnKey);

// 页面本身的属性。
// 在自己的 first()里set, 在back()里clr.
extern void SetWinBoolState(emWinBoolState mState);
extern void ClrWinBoolState(emWinBoolState mState);
extern BOOL bWinBoolState(emWinBoolState mState);

// 不显示状态栏 //不是subPage // 不是经由menu进入的page
extern void Ini_WinBoolState(void);

/******************************************************************************
// END :
******************************************************************************/
#endif // __lcdPg_Status_H__

