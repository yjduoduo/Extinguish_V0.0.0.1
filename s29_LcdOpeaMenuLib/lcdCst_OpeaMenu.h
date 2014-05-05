#ifndef __lcdCst_OpeaMenu_H__
#define __lcdCst_OpeaMenu_H__
/******************************************************************************
* @file    lcdCst_OpeaMenu.h
* @author  yx
* @version V1.6
* @date    2013.10.08 11:50
* @brief   菜单处理
* @in      主要是按键
* @  U_SIGN_bHaveTested ; 2013.9.29 10:35
*
* V1.6  2013.10.08 11:50
*		add: MenuFigEnter(); // 菜单，直接用数字确定
* V1.5  2013.9.29 10:35 
		add: 菜单未显示head或end时，用字符提示。
* V1.4, 2013.9.17 16:17 
		add注释：函数的slave
* V1.3, 2013.9.13 09:28
		add: 一屏不能显示所有菜单情况的 MenuDisp();  -> Menu_Part_Disp();
* V1.2, 2013.9.11
* 		add: ClrMenuAllBufAndSign();
* V1.1, 2013.9.6
		菜单显示 用 PgMenuItem_SelectSign();
* V1.0, 2013-09-04
* 
#include  "lcdCst_OpeaMenu.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

/*================= extern ============================================*/
#ifdef  __lcdCst_OpeaMenu_C__
#define EX_lcdCst_OpeaMenu
#else
#define EX_lcdCst_OpeaMenu extern 
#endif
/*================= 常数 ============================================*/
//#define 
/*================= 结构体定义 ======================================*/

/*================= 公有结构变量声明 ================================*/

/*================= 私有函数声明 ====================================*/
#ifdef  __lcdCst_OpeaMenu_C__

// * FUNC: 菜单 showBuf[]：
// *   IN:
// *  OUT: 

// 清除winBuf[].//当前屏显示内容
void clrMenuWinBuf(void);
// mMenuId的菜单->winBuf[].
BOOL fillMenuWinBuf(U8 mMenuId);

// 清除 菜单路径 pathId。
void clrMenuOnePathBuf(U8 pathId);
// 清除 菜单路径 All。
void clrMenuPathBuf(void);





// * FUNC: 菜单 next：
// *   IN:
// *  OUT: 

// menu -> 进入页面：
void menuPageEntry(void);
// menu -> 光标所在的next级菜单，并显示菜单。
void menuNext(void);



// * FUNC: 菜单显示：
// *   IN:
// *  OUT: 

// 是否设置为被选中状态
// 若是当前的选中模式与新的不相符，则重新设置模式。
BOOL menuSwMode(U8 menuSequ, U8 mMenuRow, BOOL bNowSelect);

// 菜单内容 显示一条:
BOOL menu_OneItem_Disp(U8 mMenuSequ, U8 mMenuRow,
						BOOL bNowSelect, BOOL *pRtnMenuValid);
// * FUNC: // 计算 菜单起始 menuSequ.
BOOL cacuMenuStartSequ(U8 nowCursor, U8 menuTotal, 
										U8 *pRtnSequS);



// 显示 菜单路径
void menuSwHead(void);

// 菜单内容 显示:
void MenuDisp(void);
	// 一次显示同级的所有菜单
	void Menu_AllItem_Disp(void); 
	// 一屏不能显示所有菜单 显示：
	void Menu_Part_Disp(void);
void menu_Part_Dsp_promptHeadEnd(
					U8 mMenuRow, U8 menuSequ, U8 menuTotal);

#endif  //__lcdCst_OpeaMenu_C__
/*================= 公有函数声明 ====================================*/
//EX_lcdCst_OpeaMenu 

#if U_SYS_Test_Menu == U_Yes 
extern void testMenu(void);
#endif // U_SYS_Test_Menu
/*================= 公有函数声明 ====================================*/
//EX_lcdCst_OpeaMenu 

// 从页面 首次进入菜单:
// * Slave:  SetPgState_InMenu();  PgMenu_SetPageNum();  MenuEnter();
extern void MenuFirstEntry(void);

//光标所在的next级菜单，并显示菜单，或进入页面。 //U_SYS_bShowNoFinished
// * Slave:  Pssw_MenuNeedPssw();  需要判断 userGrade:
extern void MenuEnter(void);

// userGrade已满足，直接进入
// * Slave:  PgMenu_SetPageNum(); 
//		menuNext(); 
//		menuPageEntry()  -> PgMenu_toPage(); 
extern void MenuEntr_NextMenuOrPage(void);


// 菜单，光标上下移动，突出显示光标位置:
extern void MenuUp(void);
extern void MenuDown(void);
extern void MenuFigEnter(U8 mMenuSequ);



// 返回到上级菜单 或 MCycle(事件和状态)页面:
// * Slave:  
// 		最顶级菜单.return:  ClrMenuAllBufAndSign() 
//						+ PgMenu_Return_Exit();
extern void MenuReturn(void);

// 菜单退出到MCycle(事件和状态)页面:
// slave: ClrMenuAllBufAndSign() + PgMenu_Esc_Exit();
extern void MenuEsc(void);



// 页面退出到 菜单:
// master: 调度，页面退出;
// slave: PgMenu_SetPageNum(); 
extern void PageRtnToMenu(void);

//Clr菜单R ； menu.back() 执行。
// slave: ClrPgState_InMenu();
extern void ClrMenuAllBufAndSign(void);

/******************************************************************************
// END :
******************************************************************************/
#endif // __lcdCst_OpeaMenu_H__

