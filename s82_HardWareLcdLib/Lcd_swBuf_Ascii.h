#ifndef __Lcd_swBuf_Ascii_H__
#define __Lcd_swBuf_Ascii_H__
/******************************************************************************
* @file    Lcd_swBuf_Ascii.h
* @author  yx
* @version V1.0
* @date    2012-02-01
* @brief   
*
* 
* 
#include  "Lcd_swBuf_Ascii.h"
******************************************************************************/
//
#include  "prjCompileCon.h"
#include  "hwEx11_lcd_DefPara.h"

/*================= 常数 ============================================*/

/*================= 公有函数声明 ====================================*/

/*================= 公有函数声明-Ext. Ascii 字符 ====================================*/
//EX_hwEx15_lcd_swBuf 

extern TYPE_LCD_XY LcdSw_cstAscii88(
					TYPE_LCD_XY mPixRow, TYPE_LCD_XY mPixLine, 
					const U8 *pStart
					);
extern TYPE_LCD_XY LcdSw_color_cstAscii88(
					TYPE_LCD_XY mPixRow, TYPE_LCD_XY mPixLine, 
					const U8 *pStart,
					U8 colorText, U8 colorBackGround
					);
extern TYPE_LCD_XY LcdSw_Ascii88(
					TYPE_LCD_XY mPixRow, TYPE_LCD_XY mPixLine, 
					unsigned char *pStart
					);
extern void LcdSw_Ascii88_XPixRtn(
					TYPE_LCD_XY mPixRow, TYPE_LCD_XY mPixLine, 
					U8 *pStart, TYPE_LCD_XY *pRtnPixLine
					);
extern void LcdSw_color_Ascii88_XPixRtn(
					TYPE_LCD_XY mPixRow, TYPE_LCD_XY mPixLine, 
					U8 *pStart, TYPE_LCD_XY *pRtnPixLine,
					U8 colorText, U8 colorBackGround
					);

/******************************************************************************
// END :
******************************************************************************/
#endif // __Lcd_swBuf_Ascii_H__

