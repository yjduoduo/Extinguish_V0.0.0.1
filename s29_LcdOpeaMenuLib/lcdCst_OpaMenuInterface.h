#ifndef __lcdCst_OpaMenuInterface_H__
#define __lcdCst_OpaMenuInterface_H__
/******************************************************************************
* @file    lcdCst_OpaMenuInterface.h
* @author  yx
* @version V1.3
* @date    2013.9.17 16:17
* @brief   OpeaMenuLib的接口。
* 

* V1.4, 2013.9.29 10:10 
*		add:　 GetMenu1PageItemMax();
*			PgMenuShowMode_PrePgHaveMenu();  PgMenuShowMode_NextPgHaveMenu();
* V1.3, 2013.9.17 16:17 
		改 PgMenu_Esc_Exit();
* V1.2, 2013.9.11 00:19
		add: PgMenu_Error();
		改:  PgMenu_Exit() 的处理方式。
* V1.1, 2013.9.6
		add : PgMenuItem_SelectSign();
* V1.0, 2013-09-04
*
*
#include  "lcdCst_OpaMenuInterface.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

/*================= extern ============================================*/
#ifdef  __lcdCst_OpaMenuInterface_C__
#define EX_lcdCst_OpaMenuInterface
#else
#define EX_lcdCst_OpaMenuInterface extern 
#endif
/*================= 常数 ============================================*/

#if U_CharLib_NOW==U_CharLib_12
	#define U_OneScreen_Menu_MAX    4   
#else
	#define U_OneScreen_Menu_MAX    3   
#endif
/*================= 结构体定义 ======================================*/

/*================= 公有结构变量声明 ================================*/

/*================= 私有函数声明 ====================================*/
#ifdef  __lcdCst_OpaMenuInterface_C__

#endif  //__lcdCst_OpaMenuInterface_C__

/*================= 公有函数声明-字符显示 ====================================*/
//EX_lcdCst_OpaMenuInterface 


/*-----------------  一条menu:  ----------------------------------*/
// 菜单显示一行，clr all:
extern void PgMenuItem_ClrTextBuf(void);

// 菜单被选中标志:
// 在 PgMenuItem_ClrTextBuf()后，add 菜单字符前， 调用。
// 也可以做成记录bSelect状态，在PgMenuItem_show()时添加标志到其他列。
extern void PgMenuItem_SelectSign(U8 mMenuRow, BOOL bSelect);

// 菜单显示一行，add char:
extern void PgMenuItem_AddText(U8 *pChar);

// 菜单显示一行，add char, 标示有下级菜单:
extern void PgMenuItem_AddTxt_HaveNextMenu(void);

// 菜单显示一行，add char, 标示 当前行被选中:
extern void PgMenuItem_AddTxt_bSelect(void);

// 显示一条菜单字符:
extern void PgMenuItem_show(U8 mMenuRow);


/*-----------------  menuHead:  ----------------------------------*/
// 菜单head显示一行，clr all:
extern void PgMenuHead_ClrTextBuf(void);

// 菜单head显示一行，add char, 标示 连接符:
extern void PgMenuHead_AddTxt_Join(void);

// 菜单显示一行，add char:
extern void PgMenuHead_AddText(U8 *pChar);

// 显示菜单Head字符:
extern void PgMenuHead_show(void);

/*-----------------  showMode:  ----------------------------------*/
// 菜单显示模式: menuHead
extern void PgMenuShowMode_MenuHead(void);

// 菜单显示模式: 是否光标所在行。 在显示一行菜单前调用。
extern void PgMenuShowMode_Cursor(U8 mMenuRow, U8 bCursorAt);

// 第一行显示的不是首条菜单：
extern void PgMenuShowMode_PrePgHaveMenu(void);
//   末行显示的不是末条菜单：
extern void PgMenuShowMode_NextPgHaveMenu(void);

extern U8 GetMenu1PageItemMax(void);

/*================= 公有函数声明 ====================================*/
//EX_lcdCst_OpaMenuInterface 

extern void SetPgState_InMenu(void);
// 在 PgMenu_Exit()前用，标志着退出菜单状态。
extern void ClrPgState_InMenu(void);


// 菜单退出到 MCycle(事件和状态)页面。
// menu.return, menu.esc;
// if 需要判断显示页面，看 Schedu.c 对其怎么处理。
// Master: MenuReturn(): 最顶级菜单.return
// Master: MenuEsc(): use.
extern void PgMenu_Return_Exit(void);
extern void PgMenu_Esc_Exit(void);

// 菜单 不能自恢复，退出。
extern void PgMenu_Error(void);

// 菜单进入page:
extern void PgMenu_toPage(PAGEWORD mPage);

//pageNum = 菜单。
extern void PgMenu_SetPageNum(void);

// 菜单页面 清屏:
extern void PgMenu_ClrScreen(void);

/******************************************************************************
// END :
******************************************************************************/
#endif // __lcdCst_OpaMenuInterface_H__

