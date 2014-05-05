
#define __lcdPg_aSchedu_C__
/******************************************************************************
* @file    lcdPg_aSchedu.c
* @author  yx
* @version V1.0
* @date    2012-01-05
* @brief   
* 
******************************************************************************/
#include  "lcdPg_aSchedu.h"

#include  "lcdCst_Page.h"
/******************************************************************************
window有几个状态：emWinBoolState
******************************************************************************/

//#include "..\\s00Prj\\incFile.h"	

//-----------------   --------------------------------// 
#include  "tsk_lcd_incIn.h"
#include  "Lcd_swBuf_Task.h"

#include  "lcdPg_MainOrEvt.h"

#include  "opeaMenuLib_incOut.h"
// 页面退出到 菜单:
//extern void PageRtnToMenu(void);

/*================= 常数 ============================================*/



/*================= 结构定义 ========================================*/

/*================= 私有结构变量声明 ================================*/
#define U_SUB_PAGE_MAX   10
#define U_BACK_PAGE_MAX   10



/*================= 公有函数声明 ====================================*/

/*================= 私有函数声明 ====================================*/


/*=================  ================================================*/
		
/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
// clr screen, newPage first();
void PageEntry(PAGEWORD mPage)
{
	
	if(SetPageNum(mPage))
	{
		LcdPage_function_First(mPage);
	}	
}


/******************************************************************************
* FUNC: //
******************************************************************************/
void PageReturn(void)
{
	
	PAGEWORD page;
	
	if(bWinBoolState(U_WIN_PageSubIng_Sta)) //子页面：
	{
		// 若是 subPage, back(); 执行 parent.first(), 且Set parent pageNum . 
		execPageBack();	
		return;
	}
	else if(bPageIsMenu())
	{
		MenuReturn();
		return;
	}
	else if(bPageIsUserLogin())
	{
		pgUserLogin_userExit();
	}
	else
	{
		// page_Back();
		execPageBack();
		
		if(bWinBoolState(U_WIN_EntryMenu_Sta))
		{
			PageRtnToMenu();
		}
		else if(bPageIsMCycle())
		{
			page = pageMCycleReturn();
			PageEntry(page);
		}
		else
		{
			PageMainOrEventFirst();
		}
		
	}
}


/******************************************************************************
* FUNC: //
******************************************************************************/

void IniPageSchedu(void)
{
	PageMainOrEventFirst();
}

/******************************************************************************
* FUNC: //
******************************************************************************/

void PageEsc(void)
{
	if(bPageIsMenu())
	{
		MenuEsc(); 
	}
	else
	{
		pageExitToMain_EntryMCycleWin();
	}
}


/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
// U_SIGN_bHaveTested	2013.10.15 by yx: 
// 带statusPage, 或不带，在 cstPgMCycDef[] 已测试。
******************************************************************************/

// 主页面 切换:
PAGEWORD pageMCycleReturn(void)
{
PAGEWORD pageIndex;
	
	GetPageNum(&pageIndex);
	if(!bPageIsMCycle())
	{
		return GetPgNum_Main();
	}
	else
	{
		if(JdgNextMCyclePage(&pageIndex))
		{
			return pageIndex;
		}
		else
		{
			return GetPgNum_Main();
		}
	}
}


/******************************************************************************
* FUNC: //exit from now & enter menu page
*   IN:
*  OUT:
******************************************************************************/
void PgExit_andMenuEntry(void)	
{
	pageExit_tillPageMain();
	MenuFirstEntry();
	
}

/******************************************************************************
* FUNC: //exit to P000, no first().
*   IN:
*  OUT:
******************************************************************************/
void PgExitToMain_NoFirstFuncExc(void)
{
	pageExit_tillPageMain();
}


/******************************************************************************
* FUNC: // 
// back() 直至  PageMain.back()执行一次;
// 但最后的页面不执行 first();
// OUT: pageNum = GetPgNum_Main();
******************************************************************************/

void pageExit_tillPageMain(void)
{
PAGEWORD pageIndex;
PAGEWORD pageBack;
U8 num = 0;

	GetPageNum(&pageIndex);
	while(1)
	{
		if(bWinBoolState(U_WIN_PageSubIng_Sta))
		{
			// 子页面 在back里确定 parent pageNum;
			LcdPage_function_Back(pageIndex);
			GetPageNum(&pageBack);
		}
		else
		{
			pageBack = LcdCstPage_GetBackPgNum(pageIndex);
			LcdPage_function_Back(pageIndex);
		}
		
		if(pageIndex == GetPgNum_Menu())
		{
			// 清menuBuf的工作 在menu.back()里已调用
			// 不能使用 MenuEsc(); 因为其 自动退出到 MCycle页面，且易造成函数互锁。
			break;
		}
		if(pageIndex == GetPgNum_UserLogin())
		{
			pgUserLogin_userExit();
			GetPageNum(&pageBack); // 登录界面，可能退出到menu.
			break;
		}
		else if(  (pageIndex == GetPgNum_Main())
		  || (bPageIsMCycle())
		  )
		{
			break;
		}
		pageIndex = pageBack;
		SetPageNum(pageIndex);
		
		num++;
		if(num >= U_BACK_PAGE_MAX)
		{
			LcdPage_function_Back(GetPgNum_Main());
			break;
		}
	}
	SetPageNum(GetPgNum_Main());
	
}

/******************************************************************************
* FUNC: // 原exit & 新first
*   IN:
*  OUT:
******************************************************************************/
void PageExit_andNewPageFirst (PAGEWORD pageNew)
{
	PAGEWORD page;
	if(GetPageNum(&page))
	{
		LcdPage_function_Back(page);
	}
	PageEntry(pageNew);
}	





/******************************************************************************
* FUNC: //
*   IN:
*  OUT:
******************************************************************************/
// page_Back();
// 若是 subPage, back(); 执行 parent.first(), 且Set parent pageNum . 
void execPageBack(void)
{
	PAGEWORD page;
	if(GetPageNum(&page))
	{
		LcdPage_function_Back(page); // page_Back();
	}
}

void execPageError(void)
{
	PageEntry(GetPgNum_Default());
}

/******************************************************************************
* FUNC: //
******************************************************************************/
// 上一页面的事已处理完毕，直接去判断事件页面:
void PageRtnTo_MainOrEvent(void)
{
	pageExitToMain_EntryMCycleWin();
}


/******************************************************************************
* FUNC: //
******************************************************************************/

void PageMainOrEventFirst(void)
{
	PAGEWORD page;

	page = JdgMainOrEvtHighPriorityPage();
	PageEntry(page);


	
}

/******************************************************************************
* FUNC: //
******************************************************************************/
//nowPageExit & 逐级back，直至判断事件页面:
void pageExitToMain_EntryMCycleWin(void)
{

	pageExit_tillPageMain();
	
	PageMainOrEventFirst();
	
}

/******************************************************************************
* FUNC: // END 
*   IN:
*  OUT: 
******************************************************************************/

void LcdPage_function_Back(PAGEWORD mPageNum)
{
	LcdCstPage_Back(mPageNum);
	ClrPageKey();
}

void LcdPage_function_First(PAGEWORD mPageNum)
{
	LcdSw_ClrFullWindow(U_COLOR_BackGroundDefault);
	
	// ShowCstCharRL(2, 0, &cstChar_PageNoCode);  // "Page: 000 页面功能未实现"
	// ShowXY_Fig_Pre0(2, 0, 6, mPageNum, 3);
	
	LcdCstPage_First(mPageNum);
	ClrPageKey();
	
	
}

void LcdPage_function_Usual(PAGEWORD mPageNum)
{
	LcdCstPage_Usual(mPageNum);
	ClrPageKey();
}

/******************************************************************************
* FUNC: // END 
*   IN:
*  OUT: 
******************************************************************************/
