#ifndef __lcd_Para_H__
#define __lcd_Para_H__
/******************************************************************************
* @file    lcd_Para.h
* @author  yx
* @version V1.0
* @date    2012-01-05
* @brief   LCD�Ĳ�����
* 
#include  "lcd_Para.h"
******************************************************************************/

#include  "prjCompileCon.h"

#include  "hwEx13_lcd_DataType.h"
#include  "hwEx11_lcd_DefPara.h"
/*================= ���� ============================================*/

	
enum emLcdPara{
	U_Lcd_H_PIX_MAX = (U_LCD_ROW_PIX_MAX), // 64
	U_Lcd_W_PIX_MAX = (U_LCD_LINE_PIX_MAX),  //192
	
	U_Lcd_H_1CN_PIX_MAX = (16),
	U_Lcd_W_1CN_PIX_MAX = (16),
	U_Lcd_H_1EN_PIX_MAX	=(8),
	U_Lcd_W_1EN_PIX_MAX	=(8),
	
	
	U_LcdROW_EN_MAX		=	(U_LCD_ROW_MAX),	// 64/8=8
	U_LcdLINE_EN_MAX	=	(U_LCD_LINE_MAX),	//192/8=24
	U_LcdROW_CN_MAX		=	(U_LCD_ROW_MAX  / 2),	
	U_LcdLINE_CN_MAX	=	(U_LCD_LINE_MAX / 2),	
	
	
	U_LINE_WIDE_MAX  = 1, //�߿�
	U_SQUARE_WIDE_MAX  = 1, //�߿�
	
};
	
// ����
#define U_LCD_SCR_TOWARD_RIGHT	0	
#define U_LCD_SCR_TOWARD_LEFT	1	
#define U_LCD_SCR_TOWARD_UP		2	
#define U_LCD_SCR_TOWARD_DOWN	3	
#define U_LCD_SCR_TOWARD_MAX	4		

/*-----------------------------------*/

// �ֿ�
#define U_LcdRow_1CN_PixByteX	(2)

#define U_ONE_EN_PixByte_MAX	16 
#define U_ONE_CN_PixByte_MAX	32 

/*-----------------------------------*/

#define U_STRING_END		'\0'	//0  //�ַ�����ĩβ
	
/*================= ���� ============================================*/

// ״̬������ʾλ�á�
// 192*64����̫С�ˣ���������ʾ״̬����
enum emWindowXY{  
	U_WinState_sx = 1,
	U_WinState_sy = 3,
	U_WinState_ex = (U_LCD_LINE_PIX_MAX),
	U_WinState_ey = (U_LCD_ROW_PIX_MAX),
	
};

/*================= �ṹ�嶨�� ======================================*/
typedef struct{
	unsigned int sx;
	unsigned int sy;
	unsigned int ex;
	unsigned int ey;
}TLcdXY_st;

typedef struct{
	unsigned char row;
	unsigned char line;
}TLcdRL_st;

/*================= ���нṹ�������� ================================*/


/******************************************************************************
// END :
******************************************************************************/
#endif // __lcd_Para_H__

