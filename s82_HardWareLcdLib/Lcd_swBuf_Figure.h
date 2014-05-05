#ifndef __Lcd_swBuf_Figure_H__
#define __Lcd_swBuf_Figure_H__
/******************************************************************************
* @file    Lcd_swBuf_Figure.h
* @author  yx
* @version V1.0
* @date    2012-02-01
* @brief   
*
* 
* 
#include  "Lcd_swBuf_Figure.h"
******************************************************************************/
//
#include  "prjCompileCon.h"
#include  "hwEx11_lcd_DefPara.h"

/*================= ���� ============================================*/

/*================= ���к������� ====================================*/

/*================= ���к�������-Ext. ���� ====================================*/
//EX_hwEx15_lcd_swBuf 

// *   IN: bFigShow0 = U_LcdMode_FigShow0, U_LcdMode_DontFigShow0;
// *   IN: bRightAlig = U_LcdMode_FigAlignRight, U_LcdMode_FigAlignLeft;
extern void LcdSw_SetFigMode(U8 figShow0, U8 figAlignMode);


// ����ǰ ������ LcdSw_SetFigMode(),һֱ��Ч��ֱ���޸ġ�
extern TYPE_LCD_XY LcdSw_Fig(
					TYPE_LCD_XY mPixRow, TYPE_LCD_XY mPixLine, 
					U32 fig, U8 bitTotal
					); //����BCD�����9999
// OUT: *pRtnPixLine = ��ʾ���xPix;
extern TYPE_LCD_XY LcdSw_color_Fig(
					TYPE_LCD_XY mPixRow, TYPE_LCD_XY mPixLine,
					U32 fig, U8 bitTotal,
					U8 colorText, U8 colorBackGround
					);

/******************************************************************************
// END :
******************************************************************************/
#endif // __Lcd_swBuf_Figure_H__

