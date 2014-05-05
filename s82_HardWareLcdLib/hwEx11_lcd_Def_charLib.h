#ifndef __hwEx11_lcd_Def_charLib_H__
#define __hwEx11_lcd_Def_charLib_H__
/******************************************************************************
* @file    hwEx11_lcd_Def_charLib.h
* @author  yx
* @version V1.0
* @date    2013-07-01
* @brief   字库定义
* 
#include  "hwEx11_lcd_Def_charLib.h"
******************************************************************************/
//
#include  "prjCompileCon.h"


/*================= 常数 - 字库编译 ============================================*/
#define U_Include_CharLib  U_NO // 在lcdLib里不起作用，因为字库在master里。
/*================= 常数 - 字库选项 ============================================*/

#define U_CharLib_12    1 // 汉字 12*12 点阵
#define U_CharLib_16    2 // 汉字 16*16 点阵
#define U_CharLib_NOW    U_CharLib_12

#if U_CharLib_NOW == U_CharLib_12
	#define U_CharLib12_EnWide_8     8   
	#define U_CharLib12_EnWide_6     6   
	#define U_CharLib12_EnWide_NOW   U_CharLib12_EnWide_6
#endif  // U_CharLib_NOW

#define U_CharLibAscii8_Wide_8     8   
#define U_CharLibAscii8_Wide_6     6   
#define U_CharLibAscii8_Wide_NOW   U_CharLibAscii8_Wide_6


/*================= 字库存储地址 ============================================*/
#if  U_CharLib_NOW==U_CharLib_16
	#define U_CharLib16_Byte_CN_MAX  (256 * 0x400) // 字库字节max; 
	
	#define U_CharLib_ADR_START   0x3C000 // 字库 在 code 里的地址
#else  // now: U_CharLib_NOW==U_CharLib_12
	#define U_CharLib12_Byte_CN_MAX  (256 * 0x400) // 字库字节max;
	
	#define U_CharLib_ADR_START     0x40000 // 字库 在 code 里的地址
	#define U_AsciiLib12_ADR_START  0x3C000 // ( + 0x80*0x20)
#endif // U_CharLib_NOW

/*================= 常数 - 字库中每字的字节 =====================*/

#if  U_CharLib_NOW==U_CharLib_16

	#define U_CharLib_en_PixMax 0x10
	#define U_CharLib_cn_PixMax 0x20
	
	
#else  // now: U_CharLib_NOW==U_CharLib_12

		#define U_CharLib_cn_PixMax (12+12)
		
	#if  U_CharLib12_EnWide_NOW==U_CharLib12_EnWide_8
		#define U_CharLib_en_PixMax 0x10
	#else 
		#define U_CharLib_en_PixMax 12 
	#endif // U_CharLib12_EnWide_NOW
	
#endif // U_CharLib_NOW


/*================= 常数 字符点阵-用于显示 ============================================*/
#if  U_CharLib_NOW==U_CharLib_16

	#define U_SHOW_HalfChar_HEIGHT   8
	#define U_SHOW_HalfChar_WIDE      8  //
	#define U_SHOW_CHAR_EN_HEIGHT  16  //
	#define U_SHOW_CHAR_EN_WIDE    8  //
	#define U_SHOW_CHAR_CN_HEIGHT  16  //
	#define U_SHOW_CHAR_CN_WIDE    16  //
	#define U_SHOW_CHAR_Height_HalfUp    8  // 上一半
	#define U_SHOW_CHAR_Height_HalfDown  8  // 下一半
	
	// (半字符的高度 == U_LCD_1RowPage_PIX_MAX)
	// 1 = 显示一行 不是 液晶扫描的一行。
	// 这里=0是为了测试代码。
	#define U_ShowCharHeight_IsOneRowPage  1
	
#else  // now: U_CharLib_NOW==U_CharLib_12

	#define U_SHOW_HalfChar_HEIGHT    6  // 字符或半字的高度pix
	#define U_SHOW_HalfChar_WIDE      6  //
	
	#define U_SHOW_CHAR_EN_HEIGHT  12  //	
	#define U_SHOW_CHAR_EN_WIDE    U_CharLib12_EnWide_NOW	
	#define U_SHOW_CHAR_CN_HEIGHT  12  //
	#define U_SHOW_CHAR_CN_WIDE    12  //
	#define U_SHOW_CHAR_Height_HalfUp    8  // 上一半
	#define U_SHOW_CHAR_Height_HalfDown  4  // 下一半


	// (半字符的高度 == U_LCD_1RowPage_PIX_MAX)
	// 1 = 显示一行 不是 液晶扫描的一行。
	// 这里=0, 因为12*12不能全对应到液晶的 8pix1Row上。
	#define U_ShowCharHeight_IsOneRowPage  0

#endif // U_CharLib_NOW

/*================= 常数 - ascii 字符点阵 ============================================*/
// #include  "hwEx11_lcd_cmd.h"
	#define U_SHOW_Ascii88_WIDE    U_CharLibAscii8_Wide_NOW  //
	#define U_SHOW_Ascii88_HEIGHT    8  //
	
/*=================  ======================================*/
// 显示8*8点阵字符时,行列位置计算采用:	

#define U_Show_OneAscii88_RowPix   U_SHOW_Ascii88_HEIGHT  
// #define U_ShowAscii88_RowPix   U_SHOW_HalfChar_HEIGHT //

#define U_Show_OneAscii88_LinePix   U_SHOW_Ascii88_WIDE  
// #define U_ShowAscii88_RowPix   U_SHOW_HalfChar_WIDE //

/******************************************************************************
// END :
******************************************************************************/
#endif // __hwEx11_lcd_Def_charLib_H__

