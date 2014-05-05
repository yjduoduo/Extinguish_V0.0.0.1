#ifndef __opeaMenuLib_incOut_H__
#define __opeaMenuLib_incOut_H__
/******************************************************************************
* @file    opeaMenuLib_incOut.h
* @author  yx
* @version V1.6
* @date    2013.10.08 11:50
* @brief   菜单处理
* @in      主要是按键
*
* V1.6  2013.10.08 11:50  《OpeaMenu_Driver_V0.0.0.1_0.0.8》
*		add: MenuFigEnter(); // 菜单，直接用数字确定
* V1.5  2013.9.29 10:35   《OpeaMenu_Driver_V0.0.0.1_0.0.7》
		add: 菜单未显示head或end时，用字符提示。
* V1.4, 2013.9.17 16:17   《OpeaMenu_Driver_V0.0.0.1_0.0.6》
		add注释：函数的slave
* V1.3, 2013.9.13 09:28
		add: 一屏不能显示所有菜单情况的 MenuDisp();  -> Menu_Part_Disp();
* V1.2, 2013.9.11
* 		add: ClrMenuAllBufAndSign();
* V1.1，2013-09-09  加注释。
* V1.0，2013-09-04
* 
#include  "opeaMenuLib_incOut.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

/*================= 常数 ============================================*/

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
#endif // __opeaMenuLib_incOut_H__

