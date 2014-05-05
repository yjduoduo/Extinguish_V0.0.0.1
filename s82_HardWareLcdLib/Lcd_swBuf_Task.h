#ifndef __Lcd_swBuf_Task_H__
#define __Lcd_swBuf_Task_H__
/******************************************************************************
* @file    Lcd_swBuf_Task.h
* @author  yx
* @version V1.9
* @date     2013.10.17 14:22 
* @brief   
*
* 
* 
#include  "Lcd_swBuf_Task.h"
******************************************************************************/
//
#include  "prjCompileCon.h"
#include  "hwEx11_lcd_DefPara.h"

/*================= 常数 ============================================*/

/*================= 公有函数声明 ====================================*/

/*================= 公有函数声明 ====================================*/
//EX_hwEx15_lcd_swBuf 


//新窗口，buf[]未处理完毕的，不需要继续处理了。
extern void NewWindows(TYPE_LCD_COLOR emColor);

//初始化 界面
extern void LcdSw_Page_Ini(void);

extern void LcdSw_ClrFullWindow(TYPE_LCD_COLOR emColor);

// 同页面显示内容非常多时用，一起刷新，以免太耗时。
extern void ExecAllToLcdRam(void);

//LCD Init; Clr show buf.
extern void InitLcdShow(void);

//有空就exec, 将buf数据送上lcd.
extern void ExecLcdShow(void);

//定时一起送上LCD显示。 带定时刷新。
// 批量显示时，可以避免某block重复显示工作。
extern void ExecTmrArrivedLcdShow(void);

/******************************************************************************
// END :
******************************************************************************/
#endif // __Lcd_swBuf_Task_H__

