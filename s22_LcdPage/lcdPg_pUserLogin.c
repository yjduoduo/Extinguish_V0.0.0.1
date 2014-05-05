#define __lcdPg_pUserLogin_C__
/******************************************************************************
* @file    lcdPg_pUserLogin.c
* @author  yx
* @version V1.0
* @date    2013-09-05
* @brief   page: 用户登录，或 输入密码
* 
******************************************************************************/
#include  "lcdPg_pUserLogin.h"


#include  "lcdSub_Pssw.h" 
//#include "incFile.h"	


/*================= 常数 ============================================*/

/*================= 结构定义 ========================================*/

/*================= 私有结构变量声明 ================================*/

/*================= 公有函数声明 ====================================*/

/*================= 私有函数声明 ====================================*/

/*=================  ================================================*/
		

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/


// 用户登录 退出：
void pgUserLogin_userExit(void)
{
	if(bNeedPsswKey_nowNeed())
	{
		NeedPsswKey_result_giveupKey();
	}
	else if(bNeedPsswMenu_nowNeed()) // if Menu需要userGrade:
	{
		NeedPsswMenu_result_giveupNextMenu();
	}
	
}


/******************************************************************************
* FUNC: //
******************************************************************************/

// 用户登录 有 有效的userGrade:
// 因为涉及到 pageEsc, 需要在 pgPssw_Exit() 函数的 最后执行。
void pgUserLogin_Result(U8 mLoginUserGrade)
{
	if(bNeedPsswKey_nowNeed())
	{
		if(bNeedPsswKey_meetGrade(mLoginUserGrade))
		{
			NeedPsswKey_result_useKey();
		}
		else
		{
			NeedPsswKey_result_giveupKey();
		}
	}
	else if(bNeedPsswMenu_nowNeed()) // if Menu需要userGrade:
	{
		if(bNeedPsswMenu_meetGrade(mLoginUserGrade))
		{
			NeedPsswMenu_result_entryMenuNext();
		}
		else
		{
			NeedPsswMenu_result_giveupNextMenu();
		}
		
	}
	
}

/******************************************************************************
* FUNC: // END
*   IN:
*  OUT: 
******************************************************************************/
