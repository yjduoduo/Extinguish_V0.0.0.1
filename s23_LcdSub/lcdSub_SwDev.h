#ifndef __lcdSub_SwDev_H__
#define __lcdSub_SwDev_H__
/******************************************************************************
* @file    lcdSub_SwDev.h
* @author  yx
* @version V1.1
* @date    2013-09-06
* @brief   显示stDev.
* 
* V1.1，2013-09-06
		字符串in textBuf一起显示。
* V1.0，2012-01-05
*
#include  "lcdSub_SwDev.h"
******************************************************************************/

#include  "prjCompileCon.h"

#include  "strDevice.h"
#include  "lcd_Para.h"

/*================= extern ============================================*/
#ifdef  __lcdSub_SwDev_C__
#define EX_lcdSub_SwDev
#else
#define EX_lcdSub_SwDev extern 
#endif

/*================= 常数 ============================================*/
//#define 
/*================= 结构体定义 ======================================*/

/*================= 公有结构变量声明 ================================*/

/*================= 私有函数声明 ====================================*/
#ifdef __lcdSub_SwDev_C__

// OUT: pRtnFigStr-> 数字转bcd string.
void sw_dev_Fig(U32 fig, U8 bitTotal, U8 **pRtnFigStr);

#endif //__lcdSub_SwDev_C__
/*================= 私有函数声明 ====================================*/
#ifdef __lcdSub_SwDev_C__
// OUT: TextBuf[], 字符数：

U8 sw_DevPnModu_String(TDev_un *pDev);
U8 sw_DevPanel_String(TDev_un *pDev);
U8 sw_DevMachine_String(TDev_un *pDev);
U8 sw_DevMachinMe_String(void);

// 显示回路现场部件 设备类型
// OUT: TextBuf[], 字符数
U8 sw_DeteType_String(U8 mType);

// 字符形式 显示 回路现场部件:
//字符数= 2+4 +2+6 +3+4 +1+4 = 26.
U8 sw_Dete_String(TDev_un *pDev);

// 符号形式 显示 回路现场部件:
//字符数= 2+1 +2+1 +3 +1+1 = 11;
U8 sw_Dete_Char(TDev_un *pDev);

// 显示 回路现场部件, 无机器号，最后带" ":
// OUT: TextBuf[], 字符数
//字符数= bChar0Cn1=0: 2+1 + 3+1 +1   + 1 = 9;
//字符数= bChar0Cn1=1: 2+4 + 3+4 +1+4 + 1 = 19;
U8 sw_Dete_noMachine(TDev_un *pDev, BOOL bChar0Cn1);

#endif //__lcdSub_SwDev_C__
/*================= 公有函数声明 ====================================*/
// EX_lcdSub_SwDev

// 字符形式 显示 回路现场部件 设备类型:
extern TYPE_LCD_XY Show_Dete_Type_String(TYPE_LCD_RL mRow, 
									TYPE_LCD_RL mLine, 
									U8 type);

extern TYPE_LCD_XY Show_Dev_String(TYPE_LCD_RL mRow, 
									TYPE_LCD_RL mLine, 
									TDev_un *pDev);

// 字符形式 显示 回路现场部件:
extern TYPE_LCD_XY Show_Dete_String(TYPE_LCD_RL mRow, 
									TYPE_LCD_RL mLine, 
									TDev_un *pDev);

//OUT: 显示字符总数
// 符号形式 显示 回路现场部件:
extern TYPE_LCD_XY Show_Dete_Char(TYPE_LCD_RL mRow, 
									TYPE_LCD_RL mLine, 
									TDev_un *pDev);



/******************************************************************************
// END :
******************************************************************************/
#endif // __lcdSub_SwDev_H__

