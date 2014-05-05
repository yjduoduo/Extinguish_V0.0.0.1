#ifndef __lcdCst_Menu_H__
#define __lcdCst_Menu_H__
/******************************************************************************
* @file    lcdCst_Menu.h
* @author  yx
* @version V1.1
* @date    2013-09-13
* @brief   菜单定义
*
* V1.1，2013-09-13
* 		U_MENU_1SCR_SEQU_MAX  改名 U_MENU_SameGrade_ITEM_MAX。
		add: def:　U_OneScreen_Menu_MAX
* V1.0，2012-01-05
* 
#include  "lcdCst_Menu.h"
******************************************************************************/
//#include  "lcdCst_Menu.h"
				   

#include  "prjCompileCon.h"
/*================= extern ============================================*/
#ifdef  __lcdCst_Menu_C__
#define EX_lcdCst_Menu
#else
#define EX_lcdCst_Menu extern 
#endif

/*================= 常数 ============================================*/
 enum emMenuNum{
	 U_MENU_NEXT		= 0x0FC,  //Menu.page=有下级菜单时。取值需要大于PAGE_MAX
	 U_MENU_TO_PAGE	= 0x0FA,  //Menu.nextItemMenuBuf=无下级菜单时。取值需要大于U_MENU_XXth_MAX
	 U_MENU_IdMax	= 0x0F0,  // U_Menu_ID_MAX
	 U_MENU_IdInvalid  = 0x0,
 };


#define U_Menu_Invalid_ID   0xFF
#define U_Menu_SysIni_ID   0x02

//共N级菜单，0-N-1. M0 M1 MN-1都有效时显示的是N-1级菜单全部
#define U_MENU_GRD_MAX  6 

// 同级菜单最大数
#define U_MENU_SameGrade_ITEM_MAX  10 
// 一屏最多显示的菜单条数 


// emUserGrade 用户级别
	


/*================= 结构体定义 ======================================*/

/*================= 公有结构变量声明 ================================*/

typedef struct{
	const char *sCn;  //中文
	const char *sEn;  //英文
	const char *sComplex;
}TMenuLanguage_st;


typedef struct TMenu_st //菜单项
{
	TMenuLanguage_st  stLanguage;
	U8  userGrd;          //需要用户等级。 同时用于区分未定义的菜单，未定义时字段为FF或00.
	U8  preItemMenuBuf;   //
	U8  nextItemMenuBuf;  //若有下级菜单,0~； 		//没有下级=U_MENU_TO_PAGE
	
	PAGEWORD page;	      //U_MENU_NEXT表示有下级菜单；//需要进入的页面；
}TMenu;



/*================= 私有函数声明 ====================================*/
#ifdef  __lcdCst_Menu_C__

// *   IN: emMenuId
// *  OUT: TMenu[]的条数，和首条的指针。
const TMenu *pGetMenuBufFirAndTotal(U8 mMenuId, U8 *m_pRtnTotal);

#endif //  __lcdCst_Menu_C__
/*================= 公有函数声明 ====================================*/
// EX_lcdCst_Menu

extern BOOL GetCstMenu(U8 mMenuId, U8 mSequ, TMenu *pRtnMenu);
extern const TMenu *pGetCstMenu(U8 mMenuId, U8 mSequ);

extern const TMenu *pGetCstBufFirMenu(U8 mMenuId);
extern BOOL GetMenuBufTotal(U8 mMenuId, U8 *m_pRtnTotal);

extern BOOL bValidCstMenu (const TMenu *m_pMenu);
extern BOOL bMenuIdError(U8 mMenuId);

// 菜单字符获取:
extern char *pGetMenuChar(const TMenu *pOneMenu);


/******************************************************************************
// END :
******************************************************************************/
#endif // __lcdCst_Menu_H__

