#define __lcdCst_OpeaMenu_C__
/******************************************************************************
* @file    lcdCst_OpeaMenu.c
* @author  yx
* @version V1.1
* @date    2013.9.6
* @brief   菜单处理
* @in      主要是按键
* 
* V1.1, 2013.9.6
		菜单显示 用 PgMenuItem_SelectSign();
* V1.0, 2013-09-04
*
******************************************************************************/
#include  "lcdCst_OpeaMenu.h"

#include  "lcdCst_OpaMenu_Inc_extern.h"

#include  "lcdCst_Menu.h"
//#include "incFile.h"	


/*================= 常数 ============================================*/

/*================= 结构定义 ========================================*/

typedef struct{
	U8 pathMenuId;
	U8 pathMenuSequ;
}TMenuRow_st;

typedef struct    //
{
	U8 				vMnPathDepth;  //vMnPathBuf[vMnPathDepth]有内容，是当前显示的菜单ID和光标所在行。
	TMenuRow_st 	vMnPathBuf[U_MENU_GRD_MAX];  //菜单 目录  回用。
	
	U8 				vTotal;
	const TMenu* 	vMnWinBuf[U_MENU_SameGrade_ITEM_MAX];  //当前屏显示内容
	
	BOOL 			v_bMenuError;
	
}TMenuTask_st;	

// vStMn.vMnPathBuf[vStMn.vMnPathDepth].pathMenuSequ
// 为当前光标位置。

TMenuTask_st   vStMn;
/*================= 私有结构变量声明 ================================*/

/*================= 公有函数声明 ====================================*/

/*================= 私有函数声明 ====================================*/

// 菜单字符获取:
// char *pGet_Menu_Char(const TMenu *pOneMenu);
/*=================  ================================================*/
		
/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/


#if U_SYS_Test_Menu == U_Yes 

void testMenu(void)
{
	
	MenuFirstEntry();
	
	MenuReturn();
	MenuReturn();
	
	MenuEnter();
	MenuUp();
	MenuUp();
	MenuDown();
	MenuDown();
	
}

#endif // U_SYS_Test_Menu


/******************************************************************************
* FUNC: // 清除winBuf[]. //当前屏显示内容
*   IN:
*  OUT: 
******************************************************************************/
void clrMenuWinBuf(void)
{
	int sequ;
	
	for(sequ=0; sequ<U_MENU_SameGrade_ITEM_MAX; sequ++)
	{
		vStMn.vMnWinBuf[sequ] = pGetCstBufFirMenu(U_Menu_Invalid_ID);
	}
	vStMn.vTotal = 0;
}


/******************************************************************************
* FUNC: // mMenuId的菜单->winBuf[].
*   IN:
*  OUT: 
******************************************************************************/


BOOL fillMenuWinBuf(U8 mMenuId)
{
	U8 total;
	U8 sequ;
	
	clrMenuWinBuf();
	
	if(!GetMenuBufTotal(mMenuId, &total))
	{
		vStMn.vTotal = 0;
		return FALSE;
	}
	
	for(sequ=0; sequ<total; sequ++)
	{
		vStMn.vMnWinBuf[sequ] = pGetCstMenu(mMenuId, sequ);
	}
	vStMn.vTotal = total;
	
	return TRUE;
}

/******************************************************************************
* FUNC: // 清除 菜单路径 All。
*   IN:
*  OUT: 
******************************************************************************/

void clrMenuPathBuf(void)
{
	int pathId;
	
	for(pathId=0; pathId<U_MENU_GRD_MAX; pathId++)
	{
		clrMenuOnePathBuf(pathId);
	}
	vStMn.vMnPathDepth = 0;
	vStMn.vMnPathBuf[0].pathMenuId = U_Menu_Invalid_ID;
	vStMn.vMnPathBuf[0].pathMenuSequ = 0x0;
	
}

/******************************************************************************
* FUNC: // 清除 菜单路径 pathId。
******************************************************************************/
void clrMenuOnePathBuf(U8 pathId)
{
	vStMn.vMnPathBuf[pathId].pathMenuId = U_Menu_Invalid_ID;
	vStMn.vMnPathBuf[pathId].pathMenuSequ = 0xFF;
}

/******************************************************************************
* FUNC: // 从页面 首次进入菜单:
*   IN:
*  OUT: 
* Slave:  SetPgState_InMenu();  PgMenu_SetPageNum();  MenuEnter();
******************************************************************************/

void MenuFirstEntry(void)
{
	ClrMenuAllBufAndSign();
	
	SetPgState_InMenu();
	PgMenu_SetPageNum(); //pageNum = 菜单。
	
	vStMn.vMnPathBuf[0].pathMenuId = U_Menu_SysIni_ID;
	vStMn.vMnPathBuf[0].pathMenuSequ = 0;
	
	vStMn.vMnWinBuf[0] = pGetCstMenu(U_Menu_SysIni_ID, 0);
	
	MenuEnter();
	

}

/******************************************************************************
* FUNC: // 
*   IN:
*  OUT: 
******************************************************************************/
//Clr菜单R ； menu.back() 执行。
void ClrMenuAllBufAndSign(void)
{
	clrMenuPathBuf();
	
	clrMenuWinBuf();
	
	ClrPgState_InMenu();
	
	vStMn.vMnWinBuf[0] = pGetCstMenu(U_Menu_SysIni_ID, 0);
}

/******************************************************************************
* FUNC: // 菜单退出到主页面:
*   IN:
*  OUT: 
// slave: PgMenu_Exit();
******************************************************************************/

void MenuEsc(void)
{
	ClrMenuAllBufAndSign();
	PgMenu_Esc_Exit();
}

/******************************************************************************
* FUNC: // 返回到上级菜单:
*   IN:
*  OUT: 
// 最顶级菜单.return: PgMenu_Exit();
******************************************************************************/

void MenuReturn(void)
{
	U8 preMenuId;
	
	if(vStMn.vMnPathDepth == 0) //U_Menu_SysIni_ID, 或
	{
		ClrMenuAllBufAndSign();
		
		PgMenu_Return_Exit();
		return;
	}
	
	clrMenuOnePathBuf(vStMn.vMnPathDepth);
	vStMn.vMnPathDepth--;
	
	preMenuId = vStMn.vMnWinBuf[0]->preItemMenuBuf;
	if(preMenuId == U_Menu_SysIni_ID)
	{
		ClrMenuAllBufAndSign();
		
		PgMenu_Return_Exit();
		return;
	}
	
	fillMenuWinBuf(preMenuId);
	MenuDisp();
}

/******************************************************************************
* FUNC: // 菜单，光标上下移动，突出显示光标位置:
*   IN:
*  OUT: 
******************************************************************************/

void MenuUp(void)
{
	U8 *pCursor;
	pCursor = &vStMn.vMnPathBuf[vStMn.vMnPathDepth].pathMenuSequ;
	if(*pCursor == 0)
	{
		*pCursor = vStMn.vTotal-1;
	}
	else
	{
		*pCursor = *pCursor - 1;
	}
	MenuDisp();
}


void MenuDown(void)
{
	U8 *pCursor;
	pCursor = &vStMn.vMnPathBuf[vStMn.vMnPathDepth].pathMenuSequ;
	if(*pCursor == (vStMn.vTotal-1))
	{
		*pCursor = 0;
	}
	else
	{
		*pCursor = *pCursor + 1;
	}
	MenuDisp();
}



/******************************************************************************
* FUNC: // 菜单，直接用数字确定
*   IN:
*  OUT: 
******************************************************************************/

void MenuFigEnter(U8 mMenuSequ)
{
U8 *pCursor;
	if(mMenuSequ >= vStMn.vTotal)
	{
		return;
	}
	
	pCursor = &vStMn.vMnPathBuf[vStMn.vMnPathDepth].pathMenuSequ;
	*pCursor = mMenuSequ;
	
	MenuEnter();
}


/******************************************************************************
* FUNC: // 页面退出到 菜单:
*       // 直接显示win[]就可以。
*   IN:
*  OUT: 
// master: 调度，页面退出;
******************************************************************************/

void PageRtnToMenu(void)
{
	if(vStMn.vMnPathDepth == 0)
	{
		ClrMenuAllBufAndSign();
		PgMenu_Error();
	}
	else
	{
		PgMenu_SetPageNum(); //pageNum = 菜单。
	
		MenuDisp();
	}
	
}

/******************************************************************************
* FUNC: //光标所在的next级菜单，并显示菜单，或进入页面。 //U_SYS_bShowNoFinished
*   IN: 
*  OUT: 
******************************************************************************/
// 需要判断 userGrade:
void MenuEnter(void)
{
const TMenu *pOneMenu;

	if(vStMn.vMnPathDepth >= U_MENU_GRD_MAX)
	{
		return;
	}
	pOneMenu = vStMn.vMnWinBuf[vStMn.vMnPathBuf[vStMn.vMnPathDepth].pathMenuSequ];
	if(!bValidCstMenu(pOneMenu))
	{
		vStMn.v_bMenuError = TRUE;
		return;
	}
	
	// 若userGrade已满足，会callBack  MenuEntr_NextMenuOrPage(); 
	Pssw_MenuNeedPssw(pOneMenu->userGrd);
	
}

/******************************************************************************
* FUNC: //光标所在的next级菜单，并显示菜单，或进入页面。
******************************************************************************/

// userGrade已满足，直接进入
void MenuEntr_NextMenuOrPage(void)
{	

const TMenu *pOneMenu;

	// 有可能从 psswPage过来，所以重设置一下。
	PgMenu_SetPageNum(); //pageNum = 菜单。

	
	if(vStMn.vMnPathDepth >= U_MENU_GRD_MAX)
	{
		return;
	}
	pOneMenu = vStMn.vMnWinBuf[vStMn.vMnPathBuf[vStMn.vMnPathDepth].pathMenuSequ];
	if(!bValidCstMenu(pOneMenu))
	{
		vStMn.v_bMenuError = TRUE;
		return;
	}
	
	
	if(pOneMenu->nextItemMenuBuf < U_MENU_IdMax)
	{
		menuNext();
	}
	else
	{
		menuPageEntry();
	}

}


/******************************************************************************
* FUNC: // menu -> 进入页面：
*   IN:
*  OUT: 
******************************************************************************/
void menuPageEntry(void)
{
	const TMenu *pOneMenu;
	
	pOneMenu = vStMn.vMnWinBuf[vStMn.vMnPathBuf[vStMn.vMnPathDepth].pathMenuSequ];	
	
	if(pOneMenu->nextItemMenuBuf == U_MENU_TO_PAGE)
	{
		PgMenu_toPage(pOneMenu->page);
	}
}


/******************************************************************************
* FUNC: // menu -> 光标所在的next级菜单，并显示菜单。
*   IN:
*  OUT: 
******************************************************************************/
void menuNext(void)
{
	const TMenu *pOneMenu;
	
	pOneMenu = vStMn.vMnWinBuf[vStMn.vMnPathBuf[vStMn.vMnPathDepth].pathMenuSequ];
	
	if(pOneMenu->nextItemMenuBuf < U_MENU_IdMax)
	{
		vStMn.vMnPathDepth++;
		vStMn.vMnPathBuf[vStMn.vMnPathDepth].pathMenuId = pOneMenu->nextItemMenuBuf;
		vStMn.vMnPathBuf[vStMn.vMnPathDepth].pathMenuSequ = 0;
		
		fillMenuWinBuf(pOneMenu->nextItemMenuBuf);
		MenuDisp();
	}
}

/******************************************************************************
* FUNC: // 菜单内容 显示:
*   IN:
*  OUT: 
******************************************************************************/

void MenuDisp(void)
{
#if U_MENU_SameGrade_ITEM_MAX <= U_OneScreen_Menu_MAX
	Menu_AllItem_Disp();
#else 
	Menu_Part_Disp();
#endif // U_MENU_SameGrade_ITEM_MAX <= U_OneScreen_Menu_MAX
}

/******************************************************************************
* FUNC: // 菜单内容 显示:
******************************************************************************/

// 一屏不能显示所有菜单 显示：
void Menu_Part_Disp(void)
{
#if U_MENU_SameGrade_ITEM_MAX <= U_OneScreen_Menu_MAX
#else 

BOOL bNowSelect;
U8 nowCursor;
U8 menuTotal;
U8 menuSequ;
U8 mnSequS;
U8 mMenuRow;
BOOL bMenuIsValid;
	
	nowCursor = vStMn.vMnPathBuf[vStMn.vMnPathDepth].pathMenuSequ;
	menuTotal = vStMn.vTotal;
	
	PgMenu_ClrScreen();
	
	PgMenuShowMode_MenuHead();
	menuSwHead();
	
	if(!cacuMenuStartSequ(nowCursor, menuTotal, &mnSequS))
	{
		return;
	}
	
	mMenuRow = 0;
	for(menuSequ=mnSequS; menuSequ<menuTotal; menuSequ++)
	{
		bNowSelect = menuSwMode(menuSequ, mMenuRow, bNowSelect);
		
		// 菜单内容 显示一条:
		if(menu_OneItem_Disp(menuSequ, mMenuRow,
						bNowSelect, &bMenuIsValid))
		{
		}
		
		menu_Part_Dsp_promptHeadEnd(
						mMenuRow, menuSequ, menuTotal);
		
		mMenuRow++;
		if(mMenuRow >= GetMenu1PageItemMax())
		{
			break;
		}
		
	}
	
#endif // U_MENU_SameGrade_ITEM_MAX <= U_OneScreen_Menu_MAX
}


void menu_Part_Dsp_promptHeadEnd(
					U8 mMenuRow, U8 menuSequ, U8 menuTotal)
{
	
		if(mMenuRow == 0)
		{
			if(menuSequ != 0)
			{
				// 第一行显示的不是首条菜单：
				PgMenuShowMode_PrePgHaveMenu();
			}
		}
		else if(mMenuRow == (GetMenu1PageItemMax()-1))
		{
			if(menuSequ != (menuTotal-1))
			{
				//   末行显示的不是末条菜单：
				PgMenuShowMode_NextPgHaveMenu();
			}
			
		}
}

/******************************************************************************
* FUNC: // 计算 菜单起始 menuSequ.
******************************************************************************/

BOOL cacuMenuStartSequ(U8 nowCursor, U8 menuTotal, U8 *pRtnSequS)
{
U8 mnSequS;

	if(menuTotal < GetMenu1PageItemMax())
	{
		mnSequS = 0;
	}
	else if(nowCursor < (GetMenu1PageItemMax()-1))
	{
		mnSequS = 0;
	}
	// if: total=10, max=4, 那么：6,7,8,9 条是最后一页。
	// if: total= 5, max=4, 那么：1,2,3,4 条是最后一页。
	else if(nowCursor >= (menuTotal - GetMenu1PageItemMax() + 1))
	{
		mnSequS = menuTotal - GetMenu1PageItemMax();
	}
	else 
	{
		mnSequS = nowCursor - 1;
	}
	
	*pRtnSequS = mnSequS;
	return (mnSequS < menuTotal);
}

/******************************************************************************
* FUNC: // 菜单内容 显示一条:
******************************************************************************/
BOOL menu_OneItem_Disp(U8 mMenuSequ, U8 mMenuRow,
						BOOL bNowSelect, BOOL *pRtnMenuValid)
{
const TMenu *pOneMenu;
char *pChar;
	
	if(  (mMenuRow >= GetMenu1PageItemMax())
	  || (mMenuSequ >= U_MENU_SameGrade_ITEM_MAX)
	  )
	{
		*pRtnMenuValid = FALSE;
		return FALSE;
	}
	*pRtnMenuValid = TRUE;
	pOneMenu = vStMn.vMnWinBuf[mMenuSequ];
	
	if(bValidCstMenu(pOneMenu))
	{
		PgMenuItem_ClrTextBuf();
		
		// if(bNowSelect)
		{
			PgMenuItem_SelectSign(mMenuRow, bNowSelect);
		}
		
		pChar = pGetMenuChar(pOneMenu);
		PgMenuItem_AddText((U8 *)(pChar));
		
		if(pOneMenu->nextItemMenuBuf < U_MENU_IdMax) //to next menu
		{
			PgMenuItem_AddTxt_HaveNextMenu();
		}
#if U_SYS_Test_Menu == U_Yes 
		if(bNowSelect)
		{
			PgMenuItem_AddTxt_bSelect();
		}
#endif // U_SYS_Test_Menu
		PgMenuItem_show(mMenuRow);

		*pRtnMenuValid = TRUE;
		return TRUE;
	}
	else
	{
		*pRtnMenuValid = FALSE;
		return FALSE;
	}
}



/******************************************************************************
* FUNC: // 菜单内容 显示:
******************************************************************************/
// 所有菜单 同时都能在一屏显示：
// 一次显示同级的所有菜单
void Menu_AllItem_Disp(void)
{
#if U_MENU_SameGrade_ITEM_MAX <= U_OneScreen_Menu_MAX
U8 sequ;
BOOL bNowSelect;
BOOL bMenuIsValid;
	
	PgMenu_ClrScreen();
	
	PgMenuShowMode_MenuHead();
	menuSwHead();
	
	
	for(sequ=0; sequ<vStMn.vTotal; sequ++)
	{
		bNowSelect = menuSwMode(sequ, sequ,bNowSelect);
		
		// 菜单内容 显示一条:
		if(menu_OneItem_Disp(sequ, sequ,
						bNowSelect, &bMenuIsValid))
		{
			continue;
		}
		else
		{
			break;
		}
		
	}
	
#else 
#endif // U_MENU_SameGrade_ITEM_MAX <= U_OneScreen_Menu_MAX
}


/******************************************************************************
* FUNC: // 菜单字符获取:
*   IN:
*  OUT: 
******************************************************************************/

//参考 U8 ShowCstChar(U8 row, U8 line, const TCstChar_st *pCstChar)
// char *pGet_Menu_Char(const TMenu *pOneMenu)
// {
	// U8 language;
	// language= GetLanguage();
	// switch(language)
	// {
		// case U_Complex_LANGUAGE:
			// return (char*)(pOneMenu->stLanguage.sComplex);
			
		// case U_English_LANGUAGE:
			// return (char*)(pOneMenu->stLanguage.sEn);
			
		// case U_Chinese_LANGUAGE:
		// default:
			// return (char*)(pOneMenu->stLanguage.sCn);
	// }
// }


/******************************************************************************
* FUNC: // 是否设置为被选中状态
若是当前的选中模式与新的不相符，则重新设置模式。
*   IN:
*  OUT: 
******************************************************************************/

BOOL menuSwMode(U8 menuSequ, U8 mMenuRow, BOOL bNowSelect) 
{
	BOOL bNeedSelect;
	
	if(menuSequ == vStMn.vMnPathBuf[vStMn.vMnPathDepth].pathMenuSequ){
		bNeedSelect = TRUE;
	}
	else{
		bNeedSelect = FALSE;
	}
	
	//首行一定预设
	if((mMenuRow == 0) || (bNowSelect != bNeedSelect))
	{
		if(bNeedSelect == TRUE){
			// 菜单显示模式: 是否光标所在行
			PgMenuShowMode_Cursor(mMenuRow, TRUE);
			bNowSelect = TRUE;
		}
		else{
			PgMenuShowMode_Cursor(mMenuRow, FALSE);
			bNowSelect = FALSE;
		}
	}
	return bNowSelect;
}

/******************************************************************************
* FUNC: // 显示 菜单路径
*   IN:
*  OUT: 
******************************************************************************/


void menuSwHead(void) 
{
	const TMenu *pOneMenu;
	U8 depth;
	char *pChar;
	
	PgMenuHead_ClrTextBuf();
	for(depth=0; depth<vStMn.vMnPathDepth; depth++)
	{
		pOneMenu = pGetCstMenu(vStMn.vMnPathBuf[depth].pathMenuId, vStMn.vMnPathBuf[depth].pathMenuSequ);
		if(bValidCstMenu(pOneMenu))
		{
			pChar = pGetMenuChar(pOneMenu);
			if(depth != 0)
			{
				PgMenuHead_AddTxt_Join();
			}
			PgMenuHead_AddText((U8 *)(pChar));
		}
		else
		{
			vStMn.v_bMenuError = TRUE;
			break;
		}
		
	}
	PgMenuHead_show();
}


/******************************************************************************
* FUNC: // 
*   IN:
*  OUT: 
******************************************************************************/



/******************************************************************************
* FUNC: // 
*   IN:
*  OUT: 
******************************************************************************/


/******************************************************************************
* FUNC: // 
*   IN:
*  OUT: 
******************************************************************************/



/******************************************************************************
* FUNC: //
******************************************************************************/



/******************************************************************************
* FUNC: // END
*   IN:
*  OUT: 
******************************************************************************/
