#ifndef __hwEx11_lcd_DefPara_H__
#define __hwEx11_lcd_DefPara_H__
/******************************************************************************
* @file    hwEx11_lcd_DefPara.h
* @author  yx
* @version V1.0
* @date    2013-07-01
* @brief   lcd驱动内部使用
* 
#include  "hwEx11_lcd_DefPara.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

#include  "hwEx13_lcd_DataType.h"
#include  "hwEx11_lcd_Def_charLib.h" // 字库定义


/*================= 常数 - 液晶硬件 pix ============================================*/
// #include  "hwEx11_lcd_cmd.h"

// 液晶硬件 pix:
#define U_LCD_CHIP_MAX   3

#define U_LCD_ROW_PIX_MAX 	64	// U_LCD_ChipRow_PIX_MAX
#define U_LCD_LINE_PIX_MAX 	192	// (U_LCD_ChipLine_PIX_MAX * U_LCD_CHIP_MAX) 

#define U_LCD_ChipRow_PIX_MAX			64
#define U_LCD_ChipLine_PIX_MAX			64
#define U_LCD_1RowPage_PIX_MAX			8
#define U_LCD_RowPage_MAX	\
				(U_LCD_ChipRow_PIX_MAX/U_LCD_1RowPage_PIX_MAX)

extern BOOL bLcdPixValid(TYPE_LCD_RL mPixRow, TYPE_LCD_RL mPixLine);
			
//显示汉字
#define U_LCD_AXIX_NUM_POS_Y 180//显示汉字的y坐标
#define U_LCD_AXIX_MUM_POS_X_32 25//显示汉字32的x坐标
#define U_LCD_AXIX_MUM_POS_X_64 50//显示汉字64的x坐标

/*=================  ======================================*/
// 注意末尾若有余数的情况
// 应用层的 行列

//  64/8=8;    64/6=10.4
#define U_LCD_ROW_MAX  (U_LCD_ROW_PIX_MAX/U_SHOW_HalfChar_HEIGHT)  
// 192/8=24;   192/6=32 
#define U_LCD_LINE_MAX  (U_LCD_LINE_PIX_MAX/U_SHOW_HalfChar_WIDE) 

/*=================  ======================================*/


enum emLcdTextMode{
	
	U_LcdMode_FigShow0 = 1, //显示数字时，显示前面的0 // U8 figShow0
	U_LcdMode_DontFigShow0 = 0, 
	
	U_LcdMode_FigAlignRight = 1, //显示数字时，右侧对齐 // U8 figAlignMode
	U_LcdMode_FigAlignLeft = 0, //
	
	U_FIG_SHOW_BITS_MAX  = 4,
	U_FIG_SHOW_MAX  = 10000, //显示数字最大值	
	U_FIG_SHOW_BCD_MASK  = 0xFFFF,
};

	
enum emLcdColor{
    U_COLOR_Black         = 0x00,  //黑色
    U_COLOR_White         = 0xFF,

    U_COLOR_BackGroundDefault = U_COLOR_White, // 底色
    U_COLOR_TextDefault = U_COLOR_Black,

};


/******************************************************************************
// END :
******************************************************************************/
#endif // __hwEx11_lcd_DefPara_H__

