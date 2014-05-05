#ifndef __lcdPg_pUserLogin_H__
#define __lcdPg_pUserLogin_H__
/******************************************************************************
* @file    lcdPg_pUserLogin.h
* @author  yx
* @version V1.0
* @date    2013-09-05
* @brief   page: 用户登录，或 输入密码
* @slave   lcdSub_Pssw.c
* 
#include  "lcdPg_pUserLogin.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

/*================= extern ============================================*/
#ifdef  __lcdPg_pUserLogin_C__
#define EX_lcdPg_pUserLogin
#else
#define EX_lcdPg_pUserLogin extern 
#endif
/*================= 常数 ============================================*/
//#define 
/*================= 结构体定义 ======================================*/

/*================= 公有结构变量声明 ================================*/
/*
typedef struct{
	U8 sequStart;
}TStruct_st;
TStruct_st stStruct;
*/

/*-----------------    ----------------------------------*/

/*================= 私有函数声明 ====================================*/
#ifdef  __lcdPg_pUserLogin_C__


// 用户登录 有 有效的userGrade:
// 因为涉及到 pageEsc, 需要在 pgPssw_Exit() 函数的 最后执行。
void pgUserLogin_Result(U8 mLoginUserGrade);



#endif  //__lcdPg_pUserLogin_C__
/*================= 公有函数声明 ====================================*/
//EX_lcdPg_pUserLogin 

// 用户登录 退出：
extern void pgUserLogin_userExit(void);

/******************************************************************************
// END :
******************************************************************************/
#endif // __lcdPg_pUserLogin_H__

