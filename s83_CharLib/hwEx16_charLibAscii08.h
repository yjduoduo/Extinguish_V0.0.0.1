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

/*================= 常数 ============================================*/

/*================= 公有函数声明 ====================================*/

/*================= Ascii Pix8 Lib ============================================*/
#define U_ASCII_Pix8_LIB_CharMax  110
#define U_ASCII_Pix8_LIB_PixMax   U_CharLibAscii8_Wide_NOW

#define U_AsciiPix8Lib_Endless   	(0x20 + 96 ) // "∝"
#define U_AsciiPix8Lib_Right   		(0x20 + 97 ) // "→"
#define U_AsciiPix8Lib_Up   		(0x20 + 98 ) // "↑"
#define U_AsciiPix8Lib_Deviation   	(0x20 + 99 ) // " ±"
#define U_AsciiPix8Lib_Centigrade   (0x20 + 100 ) // "℃"
#define U_AsciiPix8Lib_ArrowRight	(0x20 + 101) // "|>" 右三角


/*================= 公有函数声明 =============================================*/
//hwEx16_charLibAscii08 

// lcd驱动若一次执行时间较长，调用一次。原则超过10ms就调用一次。
extern void LcdDriver_RunCycle(void);
/******************************************************************************
// END :
******************************************************************************/
#endif // __hwEx16_charLibAscii08_H__

