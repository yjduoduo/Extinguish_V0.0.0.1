#define __lcdSub_Pssw_C__
/******************************************************************************
* @file    lcdSub_Pssw.c
* @author  yx
* @version V1.0
* @date    2013-08-28
* @brief   按键，或menu，需要权限时的判断。
		 若不满足权限，需要给出输入框。
		 输入后若权限满足，继续执行用户要求进入的功能。
* 
******************************************************************************/
#include  "lcdSub_Pssw.h"

#include  "sysDef.h"

#include  "keyBufJdgLib_incOut.h"
// master: lcdSub_Pssw.c
// UserGrade确认正确后，set key:
// extern void SetKeyValueWhenPsswOk(U8 mKeyValue);

#include  "lcdCst_OpaMenuInterface.h"
#include  "opeaMenuLib_incOut.h"
// userGrade已满足，直接进入
// extern void MenuEntr_NextMenuOrPage(void);


#include  "lcdTsk_PgNum.h"
#include  "lcdPg_aSchedu.h"



//#include "incFile.h"	


/*================= 常数 ============================================*/

/*================= 结构定义 ========================================*/
typedef struct{
	U8 nowUserGrade;
}TNeedPssw_st;

TNeedPssw_st stNeedPssw;
/*================= 私有结构变量声明 ================================*/

/*================= 公有函数声明 ====================================*/

/*================= 私有函数声明 ====================================*/

/*=================  ================================================*/


/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
void NeedPssw_Init(void)
{
	Clr_UserGrade();
}

/******************************************************************************
* FUNC: // 当前 userGrade;
*   IN:
*  OUT: 
******************************************************************************/
void set_UserGrade(U8 userGrade)
{
	stNeedPssw.nowUserGrade = userGrade;
}

void Clr_UserGrade(void)
{
	stNeedPssw.nowUserGrade = U_UserGrd_Min;
}

U8 Get_UserGrade(void)
{
	return stNeedPssw.nowUserGrade;
}

/******************************************************************************
* FUNC: // to登录界面
*   IN:
*  OUT: 
******************************************************************************/

#if U_SYS_bShowNoFinished == 1 
	U_SYS_bShowNoFinished = 1;
#endif // U_SYS_bShowNoFinished

//进入登录界面： 
// 注意menu 不执行 back();
void needPssw_toLoginPage(U8 needUserGrade)
{
	if(bPageIsMCycle())
	{
		PageEntry(GetPgNum_UserLogin());
	}
	else if(bPageIsMenu())
	{
		PgMenu_toPage(GetPgNum_UserLogin());
	}
	else
	{
		PgExitToMain_NoFirstFuncExc();
		PageEntry(GetPgNum_UserLogin());
	}
}

// Key引起的登录，退出登录界面:
void needPsswKey_outLoginPage(void)
{
	//PgExitToMain_NoFirstFuncExc();
	
	// 比如声光按键，是不影响界面操作的，
	// 这时就需要退出到 登录前的界面，或者干脆重新判断 EventPage.	
	PageRtnTo_MainOrEvent();
}

// Menu引起的登录，退出登录界面:
void needPsswMenu_outLoginPage(void)
{
	// 因为有 退出到menu | 进入nextMenu or page,
	// 这里没什么可以做的。
}

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/


// 按键 需要判断userGrade
// Master: keyBufJdg.c
void Pssw_KeyNeedPssw(U8 mKeyValue, U8 needUserGrade)
{
	// bUserGradeOk(U8 nowGrade, U8 mNeedGrade);
	if(bUserGradeOk(Get_UserGrade(), needUserGrade))
	{
		// 为防止key有效后进入页面，当前页面先退出
		PageRtnTo_MainOrEvent();
		// master: lcdSub_Pssw.c
		// UserGrade确认正确后，set key:
		SetKeyValueWhenPsswOk(mKeyValue);
	}
	else
	{
		// 为防止key有效后进入页面，当前页面先退出
		PageRtnTo_MainOrEvent();
		
		stNeedPsswKey.bNeedPssw = TRUE;
		stNeedPsswKey.keyValue  = mKeyValue;
		stNeedPsswKey.needUserGrade = needUserGrade;
		
		// 显示：用户输入密码
		needPssw_toLoginPage(needUserGrade);
	}
	
}

/******************************************************************************
* FUNC: //
******************************************************************************/
// if Key需要userGrade:
BOOL bNeedPsswKey_nowNeed(void)
{
	return stNeedPsswKey.bNeedPssw;
}


/******************************************************************************
* FUNC: //
******************************************************************************/
// if 当前UserGrade 是否满足 key 要求的grade:
BOOL bNeedPsswKey_meetGrade(U8 mLoginUserGrade)
{
	// BOOL bUserGradeOk(U8 nowGrade, U8 mNeedGrade);
	return (bUserGradeOk(mLoginUserGrade, 
						stNeedPsswKey.needUserGrade));	
}

/******************************************************************************
* FUNC: //
******************************************************************************/
// 放弃需要userGrade的按键:
// 因为涉及到 pageEsc, 需要在 pgPssw_Exit() 函数的 最后执行。
void NeedPsswKey_result_giveupKey(void)
{
	needPsswKey_outLoginPage();
	
	stNeedPsswKey.bNeedPssw = FALSE;
}

/******************************************************************************
* FUNC: //
******************************************************************************/
// 使用需要userGrade的按键:
// 因为涉及到 pageEsc, 需要在 pgPssw_Exit() 函数的 最后执行。
void NeedPsswKey_result_useKey(void)
{
	needPsswKey_outLoginPage();
	
	// UserGrade确认正确后，set key:
	SetKeyValueWhenPsswOk(stNeedPsswKey.keyValue);
	
	stNeedPsswKey.bNeedPssw = FALSE;
}

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
// 菜单 需要判断userGrade
// Master: lcdCst_OpaMenu.c
void Pssw_MenuNeedPssw(U8 needUserGrade)
{
	// bUserGradeOk(U8 nowGrade, U8 mNeedGrade);
	if(bUserGradeOk(Get_UserGrade(), needUserGrade))
	{
		// master: lcdCst_OpaMenu.c
		// userGrade已满足，直接进入
		MenuEntr_NextMenuOrPage();
	}
	else
	{
		stNeedPsswMenu.bNeedPssw = TRUE;
		stNeedPsswMenu.needUserGrade = needUserGrade;
		
		// 显示：用户输入密码
		needPssw_toLoginPage(needUserGrade);
	}
	
}

/******************************************************************************
* FUNC: //
******************************************************************************/

// if Menu需要userGrade:
BOOL bNeedPsswMenu_nowNeed(void)
{
	return stNeedPsswMenu.bNeedPssw;
}



/******************************************************************************
* FUNC: //
******************************************************************************/

// if 当前UserGrade 是否满足 menu 要求的grade:
BOOL bNeedPsswMenu_meetGrade(U8 mLoginUserGrade)
{
	// BOOL bUserGradeOk(U8 nowGrade, U8 mNeedGrade);
	return (bUserGradeOk(mLoginUserGrade, 
						stNeedPsswMenu.needUserGrade));	
}



/******************************************************************************
* FUNC: //
******************************************************************************/

// 放弃需要userGrade的 menu :
// 因为涉及到 pageEsc, 需要在 pgPssw_Exit() 函数的 最后执行。
void NeedPsswMenu_result_giveupNextMenu(void)
{
	needPsswMenu_outLoginPage();
	
	// 页面退出到 菜单:
	PageRtnToMenu();
	
	stNeedPsswMenu.bNeedPssw = FALSE;
}



/******************************************************************************
* FUNC: //
******************************************************************************/


// 进入需要userGrade的menu:
// 因为涉及到 pageEsc, 需要在 pgPssw_Exit() 函数的 最后执行。
void NeedPsswMenu_result_entryMenuNext(void)
{
	needPsswMenu_outLoginPage();
	
	// master: lcdCst_OpaMenu.c
	// userGrade已满足，直接进入
	MenuEntr_NextMenuOrPage();
	
	stNeedPsswMenu.bNeedPssw = FALSE;
}



/******************************************************************************
* FUNC: // END
*   IN:
*  OUT: 
******************************************************************************/
