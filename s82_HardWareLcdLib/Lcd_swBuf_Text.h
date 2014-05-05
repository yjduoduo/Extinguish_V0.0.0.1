#ifndef __Lcd_swBuf_Text_H__
#define __Lcd_swBuf_Text_H__
/******************************************************************************
* @file    Lcd_swBuf_Text.h
* @author  yx
* @version V1.0
* @date    2012-02-01
* @brief   
*
* 
* 
#include  "Lcd_swBuf_Text.h"
******************************************************************************/
//
#include  "prjCompileCon.h"
#include  "hwEx11_lcd_DefPara.h"

/*================= 常数 ============================================*/

/*================= 公有函数声明 ====================================*/

/*================= 公有函数声明-Ext. 汉字或字符 ====================================*/
//EX_hwEx15_lcd_swBuf 

extern TYPE_LCD_XY LcdSw_cstText(
					TYPE_LCD_XY mPixRow, TYPE_LCD_XY mPixLine, 
					const U8 *pStart
					);
extern TYPE_LCD_XY LcdSw_color_cstText(
					TYPE_LCD_XY mPixRow, TYPE_LCD_XY mPixLine, 
					const U8 *pStart,
					U8 colorText, U8 colorBackGround
					);
extern TYPE_LCD_XY LcdSw_Text(
					TYPE_LCD_XY mPixRow, TYPE_LCD_XY mPixLine,
					unsigned char *pStart
					);
extern void LcdSw_Text_XPixRtn(
					TYPE_LCD_XY mPixRow, TYPE_LCD_XY mPixLine,
					U8 *pStart,  
					TYPE_LCD_XY *pRtnPixLine
					);
// OUT: *pRtnPixLine = 显示后的xPix;
extern void LcdSw_color_Text_XPixRtn(
					TYPE_LCD_XY mPixRow, TYPE_LCD_XY mPixLine, 
					U8 *pStart,  
					TYPE_LCD_XY *pRtnPixLine,
					U8 colorText, U8 colorBackGround
					);


/******************************************************************************
// END :
******************************************************************************/
#endif // __Lcd_swBuf_Text_H__

