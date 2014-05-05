#ifndef __hwEx11_lcd_DefPara_H__
#define __hwEx11_lcd_DefPara_H__
/******************************************************************************
* @file    hwEx11_lcd_DefPara.h
* @author  yx
* @version V1.0
* @date    2013-07-01
* @brief   lcd�����ڲ�ʹ��
* 
#include  "hwEx11_lcd_DefPara.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

#include  "hwEx13_lcd_DataType.h"
#include  "hwEx11_lcd_Def_charLib.h" // �ֿⶨ��


/*================= ���� - Һ��Ӳ�� pix ============================================*/
// #include  "hwEx11_lcd_cmd.h"

// Һ��Ӳ�� pix:
#define U_LCD_CHIP_MAX   3

#define U_LCD_ROW_PIX_MAX 	64	// U_LCD_ChipRow_PIX_MAX
#define U_LCD_LINE_PIX_MAX 	192	// (U_LCD_ChipLine_PIX_MAX * U_LCD_CHIP_MAX) 

#define U_LCD_ChipRow_PIX_MAX			64
#define U_LCD_ChipLine_PIX_MAX			64
#define U_LCD_1RowPage_PIX_MAX			8
#define U_LCD_RowPage_MAX	\
				(U_LCD_ChipRow_PIX_MAX/U_LCD_1RowPage_PIX_MAX)

extern BOOL bLcdPixValid(TYPE_LCD_RL mPixRow, TYPE_LCD_RL mPixLine);
			
//��ʾ����
#define U_LCD_AXIX_NUM_POS_Y 180//��ʾ���ֵ�y����
#define U_LCD_AXIX_MUM_POS_X_32 25//��ʾ����32��x����
#define U_LCD_AXIX_MUM_POS_X_64 50//��ʾ����64��x����

/*=================  ======================================*/
// ע��ĩβ�������������
// Ӧ�ò�� ����

//  64/8=8;    64/6=10.4
#define U_LCD_ROW_MAX  (U_LCD_ROW_PIX_MAX/U_SHOW_HalfChar_HEIGHT)  
// 192/8=24;   192/6=32 
#define U_LCD_LINE_MAX  (U_LCD_LINE_PIX_MAX/U_SHOW_HalfChar_WIDE) 

/*=================  ======================================*/


enum emLcdTextMode{
	
	U_LcdMode_FigShow0 = 1, //��ʾ����ʱ����ʾǰ���0 // U8 figShow0
	U_LcdMode_DontFigShow0 = 0, 
	
	U_LcdMode_FigAlignRight = 1, //��ʾ����ʱ���Ҳ���� // U8 figAlignMode
	U_LcdMode_FigAlignLeft = 0, //
	
	U_FIG_SHOW_BITS_MAX  = 4,
	U_FIG_SHOW_MAX  = 10000, //��ʾ�������ֵ	
	U_FIG_SHOW_BCD_MASK  = 0xFFFF,
};

	
enum emLcdColor{
    U_COLOR_Black         = 0x00,  //��ɫ
    U_COLOR_White         = 0xFF,

    U_COLOR_BackGroundDefault = U_COLOR_White, // ��ɫ
    U_COLOR_TextDefault = U_COLOR_Black,

};


/******************************************************************************
// END :
******************************************************************************/
#endif // __hwEx11_lcd_DefPara_H__

