#ifndef __lcdSub_Pssw_H__
#define __lcdSub_Pssw_H__
/******************************************************************************
* @file    lcdSub_Pssw.h
* @author  yx
* @version V1.0
* @date    2013-08-28
* @brief   按键，或menu，需要权限时的判断。
		 若不满足权限，需要给出输入框。
		 输入后若权限满足，继续执行用户要求进入的功能。
* @master  引发：lcdSub_Pssw.c; opeaMenu;
* @master  处理：lcdPg_pUserLogin.c;
* 
#include  "lcdSub_Pssw.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

/*================= extern ============================================*/
#ifdef  __lcdSub_Pssw_C__
#define EX_lcdSub_Pssw
#else
#define EX_lcdSub_Pssw extern 
#endif
/*================= 常数 ============================================*/
//#define 
/*================= 结构体定义 ======================================*/

typedef struct{
	BOOL bNeedPssw;
	U8   keyValue;
	U8	 needUserGrade;
}TNeedPsswKey_st;

typedef struct{
	BOOL bNeedPssw;
	U8	 needUserGrade;
}TNeedPsswMenu_st;

/*================= 公有结构变量声明 ================================*/

/*================= 私有函数声明 ====================================*/
#ifdef  __lcdSub_Pssw_C__

TNeedPsswKey_st   stNeedPsswKey;
TNeedPsswMenu_st  stNeedPsswMenu;


void set_UserGrade(U8 userGrade);

//进入登录界面： 
void needPssw_toLoginPage(U8 needUserGrade); 
// Key引起的登录，退出登录界面:
void needPsswKey_outLoginPage(void);
// Menu引起的登录，退出登录界面:
void needPsswMenu_outLoginPage(void);

#endif  //__lcdSub_Pssw_C__
/*================= 公有函数声明-extern  ====================================*/
//EX_lcdCst_OpeaMenu 


/*================= 公有函数声明 ====================================*/
//EX_lcdSub_Pssw 


extern void NeedPssw_Init(void);

extern void Clr_UserGrade(void);
extern U8 Get_UserGrade(void);

/*-----------------    ----------------------------------*/
// 按键 需要判断userGrade
// Master: keyBufJdg.c
extern void Pssw_KeyNeedPssw(U8 mKeyValue, U8 needUserGrade);

// if Key需要userGrade:
extern BOOL bNeedPsswKey_nowNeed(void);

// if 当前UserGrade 是否满足 key 要求的grade:
extern BOOL bNeedPsswKey_meetGrade(U8 mLoginUserGrade);

// 使用需要userGrade的按键:
// 因为涉及到 pageEsc, 需要在 pgPssw_Exit() 函数的 最后执行。
extern void NeedPsswKey_result_useKey(void);

// 放弃需要userGrade的按键:
// 因为涉及到 pageEsc, 需要在 pgPssw_Exit() 函数的 最后执行。
extern void NeedPsswKey_result_giveupKey(void);

/*-----------------    ----------------------------------*/
// 菜单 需要判断userGrade
// Master: lcdCst_OpaMenu.c
extern void Pssw_MenuNeedPssw(U8 needUserGrade);

// if Menu需要userGrade:
extern BOOL bNeedPsswMenu_nowNeed(void);

// if 当前UserGrade 是否满足 menu 要求的grade:
extern BOOL bNeedPsswMenu_meetGrade(U8 mLoginUserGrade);

// 放弃需要userGrade的 menu :
// 因为涉及到 pageEsc, 需要在 pgPssw_Exit() 函数的 最后执行。
extern void NeedPsswMenu_result_giveupNextMenu(void);

// 进入需要userGrade的menu:
// 因为涉及到 pageEsc, 需要在 pgPssw_Exit() 函数的 最后执行。
extern void NeedPsswMenu_result_entryMenuNext(void);


/******************************************************************************
// END :
******************************************************************************/
#endif // __lcdSub_Pssw_H__

