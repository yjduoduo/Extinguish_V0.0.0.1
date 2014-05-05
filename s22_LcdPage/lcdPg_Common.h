#ifndef __lcdPg_Common_H__
#define __lcdPg_Common_H__
/******************************************************************************
* @file    lcdPg_Common.h
* @author  yx
* @version V1.0
* @date    2013-07-01
* @brief   
* 
#include  "lcdPg_Common.h"
******************************************************************************/
//
#include  "prjCompileCon.h"
#include  "lcd_Para.h"

/*================= extern ============================================*/
#ifdef  __lcdPg_Common_C__
#define EX_lcdPg_Common
#else
#define EX_lcdPg_Common extern 
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
#ifdef  __lcdPg_Common_C__

#endif  //__lcdPg_Common_C__
/*================= 公有函数声明 ====================================*/
//EX_lcdPg_Common 

// 显示 有变动的 自动 手动；
extern void ShowStr_AutoManuChangeState(
				TYPE_LCD_RL mRow, TYPE_LCD_RL mLine);
// 显示 当前 自动 手动；
extern void ShowStr_AutoManuNowState(
				TYPE_LCD_RL mRow, TYPE_LCD_RL mLine);
// 显示 para 自动 手动；
extern void ShowStr_AutoManuState(
				TYPE_LCD_RL mRow, TYPE_LCD_RL mLine,
				BOOL bAutoAllow, BOOL bManuAllow);
extern void ShowStr_Auto_Manu(TYPE_LCD_RL mRow, TYPE_LCD_RL mLine);
extern void ShowStr_Allow_Forbid(TYPE_LCD_RL mRow, TYPE_LCD_RL mLine,
						 BOOL bAllow);

extern void Show_Clock(TYPE_LCD_RL mRow, TYPE_LCD_RL mLine);

/******************************************************************************
// END :
******************************************************************************/
#endif // __lcdPg_Common_H__

