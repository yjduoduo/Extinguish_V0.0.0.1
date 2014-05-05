#define __lcdCst_OpaMenuInterface_C__
/******************************************************************************
* @file    lcdCst_OpaMenuInterface.c
* @author  yx
* @version V1.1
* @date    2013.9.6
* @brief   OpeaMenuLib的接口。
* 
******************************************************************************/
#include  "lcdCst_OpaMenuInterface.h"

#include  "lcdPg_Status.h"

//#include "incFile.h"	

#include  "lcdSub_ModeTextFig.h"
// extern 
// extern void IniTextBuf(emShowUseLib_PIX  mUseLib);
// extern void AddToTextBuf(U8 *pChar);

#include  "lcdTsk_PgNum.h"
#include  "lcdPg_aSchedu.h"

/*================= 常数 ============================================*/

/******************************************************************************
由菜单进入页面时， 不能调用 menu.back(), 需要保留当前菜单的层次。
	-> PgMenu_toPage();
如果不是U_WIN_PageSubIng_Sta类型的页面，
	退出时需检查 bWinBoolState(U_WIN_EntryMenu_Sta)
	若是，退出到菜单，否则，到 MCycle;
******************************************************************************/
/*=================  ================================================*/

//
/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
// Master:  menuOpea lib ;
void SetPgState_InMenu(void)
{
	SetWinBoolState(U_WIN_EntryMenu_Sta);
}

// 在 PgMenu_Exit()前用，标志着退出菜单状态。
void ClrPgState_InMenu(void)
{
	ClrWinBoolState(U_WIN_EntryMenu_Sta);
}

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

// 菜单退出到 MCycle(事件和状态)页面。
// menu.return, menu.esc;
// if 需要判断显示页面，看 Schedu.c 对其怎么处理。
// Master: MenuReturn(): 最顶级菜单.return
// Master: MenuEsc(): use.

void PgMenu_Return_Exit(void)
{
	PageMainOrEventFirst();
	
}
void PgMenu_Esc_Exit(void)
{
	PageMainOrEventFirst();
}

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
// 菜单 不能自恢复，退出。
void PgMenu_Error(void)
{
	PageRtnTo_MainOrEvent();
}

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

// 菜单进入page:
// 注意不能 menu.back()，需要保留当前菜单的层次。
void PgMenu_toPage(PAGEWORD mPage)
{
	// clr screen, newPage first();
	PageEntry(mPage);
}

/******************************************************************************
* FUNC: //
******************************************************************************/
void PgMenu_SetPageNum(void) //pageNum = 菜单。
{
	SetPageNum(GetPgNum_Menu());
}


/******************************************************************************
* FUNC: //
******************************************************************************/
// 菜单页面 清屏:
void PgMenu_ClrScreen(void)
{
	ClrWindow_Menu();
}


/******************************************************************************
* FUNC: // 
*   IN:
*  OUT: 
******************************************************************************/

// 菜单显示一行，clr all:
void PgMenuItem_ClrTextBuf(void)
{
	IniTextBuf(U_ShowUseLib_88orCn_CN);
}

// 菜单被选中标志:
// 在 PgMenuItem_ClrTextBuf()后，add 菜单字符前， 调用。
// 也可以做成记录bSelect状态，在PgMenuItem_show()时添加标志到其他列。
void PgMenuItem_SelectSign(U8 mMenuRow, BOOL bSelect)
{
	if(bSelect)
	{
		AddCodeStrToTextBuf(">>");
	}
	else
	{
		AddCodeStrToTextBuf("  ");
	}
}

// 菜单显示一行，add char:
void PgMenuItem_AddText(U8 *pChar)
{
	AddToTextBuf(pChar);
}

// 菜单显示一行，add char, 标示有下级菜单:
void PgMenuItem_AddTxt_HaveNextMenu(void)
{
	AddToTextBuf("->");
}

// 菜单显示一行，add char, 标示 当前行被选中:
void PgMenuItem_AddTxt_bSelect(void)
{
	AddToTextBuf(". Select");
}

// 显示一条菜单字符:
void PgMenuItem_show(U8 mMenuRow)
{
	ShowTextBuf(mMenuRow*2+1, 1);  // (mRow, mLine)
}

/******************************************************************************
* FUNC: // 
* 当前 menuHead 不显示。
******************************************************************************/

// 菜单head显示一行，clr all:
void PgMenuHead_ClrTextBuf(void)
{
	IniTextBuf(U_ShowUseLib_88orCn_CN);
}

// 菜单head显示一行，add char, 标示 连接符:
void PgMenuHead_AddTxt_Join(void)
{
	// AddToTextBuf("-");
}

// 菜单显示一行，add char:
void PgMenuHead_AddText(U8 *pChar)
{
	// AddToTextBuf(pChar);
}


// 显示菜单Head字符:
void PgMenuHead_show(void)
{
	// ShowTextBuf(0, 0);  // (mRow, mLine)
}


/******************************************************************************
* FUNC: // 
******************************************************************************/


// 菜单显示模式: 是否光标所在行。 在显示一行菜单前调用。
// 可以设置成反选模式。
void PgMenuShowMode_Cursor(U8 mMenuRow, U8 bCursorAt)
{
	
}


// 菜单显示模式: menuHead
void PgMenuShowMode_MenuHead(void)
{
	
}

// 第一行显示的不是首条菜单：
void PgMenuShowMode_PrePgHaveMenu(void)
{
	ShowCodeCharRL(0, U_LCD_LINE_MAX-5, 
							"..<<", FALSE);
}
//   末行显示的不是末条菜单：
void PgMenuShowMode_NextPgHaveMenu(void)
{
	ShowCodeCharRL((U_LCD_ROW_MAX-2), U_LCD_LINE_MAX-5, 
							">>..", FALSE);
	
}
U8 GetMenu1PageItemMax(void)
{
	return U_OneScreen_Menu_MAX;
}


/******************************************************************************
* FUNC: // END
*   IN:
*  OUT: 
******************************************************************************/
