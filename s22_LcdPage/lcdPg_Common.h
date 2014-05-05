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
/*================= ���� ============================================*/
//#define 
/*================= �ṹ�嶨�� ======================================*/

/*================= ���нṹ�������� ================================*/
/*
typedef struct{
	U8 sequStart;
}TStruct_st;
TStruct_st stStruct;
*/

/*-----------------    ----------------------------------*/

/*================= ˽�к������� ====================================*/
#ifdef  __lcdPg_Common_C__

#endif  //__lcdPg_Common_C__
/*================= ���к������� ====================================*/
//EX_lcdPg_Common 

// ��ʾ �б䶯�� �Զ� �ֶ���
extern void ShowStr_AutoManuChangeState(
				TYPE_LCD_RL mRow, TYPE_LCD_RL mLine);
// ��ʾ ��ǰ �Զ� �ֶ���
extern void ShowStr_AutoManuNowState(
				TYPE_LCD_RL mRow, TYPE_LCD_RL mLine);
// ��ʾ para �Զ� �ֶ���
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

