#ifndef __Lcd_swBuf_Graph_H__
#define __Lcd_swBuf_Graph_H__
/******************************************************************************
* @file    Lcd_swBuf_Graph.h
* @author  yx
* @version V1.0
* @date    2012-02-01
* @brief   
*
* 
* 
#include  "Lcd_swBuf_Graph.h"
******************************************************************************/
//
#include  "prjCompileCon.h"
#include  "hwEx11_lcd_DefPara.h"

/*================= ���� ============================================*/

/*================= ���к������� ====================================*/

/*================= ���к�������-Ext.ͼ�� ====================================*/
//EX_hwEx15_lcd_swBuf 


// ˮƽ�ߣ���ֱ�ߣ��ݲ�֧��б�ߡ�
extern void LcdSw_HvLine(	TYPE_LCD_XY mPixRow_S, 
							TYPE_LCD_XY mPixLine_S,
							TYPE_LCD_XY mPixRow_E, 
							TYPE_LCD_XY mPixLine_E);
extern void LcdSw_ClrHvLine(	TYPE_LCD_XY mPixRow_S, 
							TYPE_LCD_XY mPixLine_S,
							TYPE_LCD_XY mPixRow_E, 
							TYPE_LCD_XY mPixLine_E);


extern void LcdSw_ClrRectangle(
							TYPE_LCD_XY mPixRow_S, 
							TYPE_LCD_XY mPixLine_S,
							TYPE_LCD_XY mPixRow_E, 
							TYPE_LCD_XY mPixLine_E);
extern void LcdSw_SetRectangle(
							TYPE_LCD_XY mPixRow_S, 
							TYPE_LCD_XY mPixLine_S,
							TYPE_LCD_XY mPixRow_E, 
							TYPE_LCD_XY mPixLine_E);




/******************************************************************************
// END :
******************************************************************************/
#endif // __Lcd_swBuf_Graph_H__

