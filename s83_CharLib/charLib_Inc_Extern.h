#ifndef __charLib_Inc_Extern_H__
#define __charLib_Inc_Extern_H__
/******************************************************************************
* @file    charLib_Inc_Extern.h
* @author  yx
* @version V1.0
* @date    2012-02-01
* @brief   
* 
*
*
#include  "charLib_Inc_Extern.h"
******************************************************************************/
//
#include  "prjCompileCon.h"
#include  "hwEx11_lcd_Def_charLib.h"
#include  "hwEx11_lcd_DefPara.h"

/*================= 常数 ============================================*/

/*================= 变量定义 ======================================*/

/*================= 结构体定义 ======================================*/

/*================= 公有函数声明 =====================================*/
//EX_hwEx13_charLib 

extern const BYTE bbit[8];

extern BYTE *pGetLib1CharBuf(void); // 读取1个字的点阵的bufS
extern BYTE *pGetLib1TransCharBuf(void); // 转换1个字的点阵的bufS
extern void ClrLib1CharBufEnd2Bytes(void); // 最后2个字节置0

/******************************************************************************
// END :
******************************************************************************/
#endif // __charLib_Inc_Extern_H__

