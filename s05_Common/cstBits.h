#ifndef __cstBits_H__
#define __cstBits_H__
/******************************************************************************
* @file    cstBits.h
* @author  yx
* @version V1.0
* @date    2012-01-05
* @brief   
* 
#include  "cstBits.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

/*================= extern ============================================*/
#ifdef  __cstBits_C__
#define EX_cstBits
#else
#define EX_cstBits extern 
#endif
/*================= 常数 ============================================*/

/*================= 公有函数声明 ====================================*/
//EX_cstBits 

EX_cstBits const U8 cDeteLuBit[8];
EX_cstBits const U8 cBit8LowToHigh[8];
EX_cstBits const U8 cBit8HighToLow[8];
EX_cstBits const U16 cBit16LowToHigh[16];
EX_cstBits const U16 cBit16HighToLow[16];
EX_cstBits const U32 cBit32LowToHigh[32];
EX_cstBits const U32 cBit32HighToLow[32];
/*================= 私有函数声明 ====================================*/
#ifdef  __cstBits_C__

#endif  //__cstBits_C__


/******************************************************************************
// END :
******************************************************************************/
#endif // __cstBits_H__

