#ifndef __hwEx16_charLibAscii08_H__
#define __hwEx16_charLibAscii08_H__
/******************************************************************************
* @file    hwEx16_charLibAscii08.h
* @author  yx
* @version V1.0
* @date    2012-02-01
* @brief   
*
* 
#include  "hwEx16_charLibAscii08.h"
******************************************************************************/
//
#include  "prjCompileCon.h"
#include  "hwEx11_lcd_DefPara.h"

/*================= ���� ============================================*/

/*================= ���к������� ====================================*/

/*================= Ascii Pix8 Lib ============================================*/
#define U_ASCII_Pix8_LIB_CharMax  110
#define U_ASCII_Pix8_LIB_PixMax   U_CharLibAscii8_Wide_NOW

#define U_AsciiPix8Lib_Endless   	(0x20 + 96 ) // "��"
#define U_AsciiPix8Lib_Right   		(0x20 + 97 ) // "��"
#define U_AsciiPix8Lib_Up   		(0x20 + 98 ) // "��"
#define U_AsciiPix8Lib_Deviation   	(0x20 + 99 ) // " ��"
#define U_AsciiPix8Lib_Centigrade   (0x20 + 100 ) // "��"
#define U_AsciiPix8Lib_ArrowRight	(0x20 + 101) // "|>" ������


/*================= ���к������� =============================================*/
//hwEx16_charLibAscii08 

// lcd������һ��ִ��ʱ��ϳ�������һ�Ρ�ԭ�򳬹�10ms�͵���һ�Ρ�
extern void LcdDriver_RunCycle(void);
/******************************************************************************
// END :
******************************************************************************/
#endif // __hwEx16_charLibAscii08_H__

