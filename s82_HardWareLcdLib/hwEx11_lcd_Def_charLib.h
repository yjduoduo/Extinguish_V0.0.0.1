#ifndef __hwEx11_lcd_Def_charLib_H__
#define __hwEx11_lcd_Def_charLib_H__
/******************************************************************************
* @file    hwEx11_lcd_Def_charLib.h
* @author  yx
* @version V1.0
* @date    2013-07-01
* @brief   �ֿⶨ��
* 
#include  "hwEx11_lcd_Def_charLib.h"
******************************************************************************/
//
#include  "prjCompileCon.h"


/*================= ���� - �ֿ���� ============================================*/
#define U_Include_CharLib  U_NO // ��lcdLib�ﲻ�����ã���Ϊ�ֿ���master�
/*================= ���� - �ֿ�ѡ�� ============================================*/

#define U_CharLib_12    1 // ���� 12*12 ����
#define U_CharLib_16    2 // ���� 16*16 ����
#define U_CharLib_NOW    U_CharLib_12

#if U_CharLib_NOW == U_CharLib_12
	#define U_CharLib12_EnWide_8     8   
	#define U_CharLib12_EnWide_6     6   
	#define U_CharLib12_EnWide_NOW   U_CharLib12_EnWide_6
#endif  // U_CharLib_NOW

#define U_CharLibAscii8_Wide_8     8   
#define U_CharLibAscii8_Wide_6     6   
#define U_CharLibAscii8_Wide_NOW   U_CharLibAscii8_Wide_6


/*================= �ֿ�洢��ַ ============================================*/
#if  U_CharLib_NOW==U_CharLib_16
	#define U_CharLib16_Byte_CN_MAX  (256 * 0x400) // �ֿ��ֽ�max; 
	
	#define U_CharLib_ADR_START   0x3C000 // �ֿ� �� code ��ĵ�ַ
#else  // now: U_CharLib_NOW==U_CharLib_12
	#define U_CharLib12_Byte_CN_MAX  (256 * 0x400) // �ֿ��ֽ�max;
	
	#define U_CharLib_ADR_START     0x40000 // �ֿ� �� code ��ĵ�ַ
	#define U_AsciiLib12_ADR_START  0x3C000 // ( + 0x80*0x20)
#endif // U_CharLib_NOW

/*================= ���� - �ֿ���ÿ�ֵ��ֽ� =====================*/

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


/*================= ���� �ַ�����-������ʾ ============================================*/
#if  U_CharLib_NOW==U_CharLib_16

	#define U_SHOW_HalfChar_HEIGHT   8
	#define U_SHOW_HalfChar_WIDE      8  //
	#define U_SHOW_CHAR_EN_HEIGHT  16  //
	#define U_SHOW_CHAR_EN_WIDE    8  //
	#define U_SHOW_CHAR_CN_HEIGHT  16  //
	#define U_SHOW_CHAR_CN_WIDE    16  //
	#define U_SHOW_CHAR_Height_HalfUp    8  // ��һ��
	#define U_SHOW_CHAR_Height_HalfDown  8  // ��һ��
	
	// (���ַ��ĸ߶� == U_LCD_1RowPage_PIX_MAX)
	// 1 = ��ʾһ�� ���� Һ��ɨ���һ�С�
	// ����=0��Ϊ�˲��Դ��롣
	#define U_ShowCharHeight_IsOneRowPage  1
	
#else  // now: U_CharLib_NOW==U_CharLib_12

	#define U_SHOW_HalfChar_HEIGHT    6  // �ַ�����ֵĸ߶�pix
	#define U_SHOW_HalfChar_WIDE      6  //
	
	#define U_SHOW_CHAR_EN_HEIGHT  12  //	
	#define U_SHOW_CHAR_EN_WIDE    U_CharLib12_EnWide_NOW	
	#define U_SHOW_CHAR_CN_HEIGHT  12  //
	#define U_SHOW_CHAR_CN_WIDE    12  //
	#define U_SHOW_CHAR_Height_HalfUp    8  // ��һ��
	#define U_SHOW_CHAR_Height_HalfDown  4  // ��һ��


	// (���ַ��ĸ߶� == U_LCD_1RowPage_PIX_MAX)
	// 1 = ��ʾһ�� ���� Һ��ɨ���һ�С�
	// ����=0, ��Ϊ12*12����ȫ��Ӧ��Һ���� 8pix1Row�ϡ�
	#define U_ShowCharHeight_IsOneRowPage  0

#endif // U_CharLib_NOW

/*================= ���� - ascii �ַ����� ============================================*/
// #include  "hwEx11_lcd_cmd.h"
	#define U_SHOW_Ascii88_WIDE    U_CharLibAscii8_Wide_NOW  //
	#define U_SHOW_Ascii88_HEIGHT    8  //
	
/*=================  ======================================*/
// ��ʾ8*8�����ַ�ʱ,����λ�ü������:	

#define U_Show_OneAscii88_RowPix   U_SHOW_Ascii88_HEIGHT  
// #define U_ShowAscii88_RowPix   U_SHOW_HalfChar_HEIGHT //

#define U_Show_OneAscii88_LinePix   U_SHOW_Ascii88_WIDE  
// #define U_ShowAscii88_RowPix   U_SHOW_HalfChar_WIDE //

/******************************************************************************
// END :
******************************************************************************/
#endif // __hwEx11_lcd_Def_charLib_H__

