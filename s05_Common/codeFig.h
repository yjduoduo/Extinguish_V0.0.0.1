#ifndef __codeFig_H__
#define __codeFig_H__
/******************************************************************************
* @file    codeFig.h
* @author  yx
* @version V1.0
* @date    2013-09-05
* @brief   数字 HEX和BCD的转换。
* 
// U_SIGN_bHaveTested	//已经测试 2013.9.6 10:11 , yx.
* 
#include  "codeFig.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

/*================= extern ============================================*/
#ifdef  __codeFig_C__
#define EX_codeFig
#else
#define EX_codeFig extern 
#endif
/*================= 常数 ============================================*/
//#define 
/*================= 结构体定义 ======================================*/

/*================= 公有结构变量声明 ================================*/


/*================= 私有函数声明 ====================================*/
#ifdef  __codeFig_C__

// 不显示前面的0  &  !0  & 右对齐，用' '补前:
static void figToStr_dotShow0_AllignRight(
						U32 bcd, U8 bcdNum, U8 bitTotal);

// 不显示前面的0  &  !0  & 左对齐，显示的都是有效数字:
static void figToStr_dotShow0_AllignLeft(U32 bcd, U8 bcdNum);

// 不显示前面的0  & bcd=0:
static U8 figToStr_dotShow0_bcd0(
					U32 bcd, U8 bitTotal, BOOL bAllignRight);

// 显示前面的0. 此时对齐方式无意义
static void figToStr_Show0(U32 bcd, U8 bitTotal);


#endif  //__codeFig_C__

/*================= 公有函数声明 ====================================*/
//EX_codeFig 
#ifdef U_SYS_Test_GeneralCode
#if    U_SYS_Test_GeneralCode == 1 

	void test_FigToStr(void);  // 测试
#endif // U_SYS_Test_GeneralCode
#endif // U_SYS_Test_GeneralCode
/*================= 公有函数声明 ====================================*/
//EX_codeFig 

// * FUNC: // Hex数字 -> Bcd String .
// *  OUT: 字符数，不包括'\0'
// charNum  = FigToString(fig, bitTotal,  b右对齐, b显示0, **pRtnStr);
extern U8 FigToString(U32 fig, U8 bitTotal, 
							BOOL bAllignRight, BOOL bShowPre0, 
							U8 **pRtnFigStr);

// * FUNC: // HEX to BCD:
// *  OUT:  有效bcd的个数
extern U8 HexToBcdU32(U32 hexFigure, U32 *pRtnBcd);
// 限制 bcd 的个数：
extern U8 HexToBcd_LimitBcdNum(U32 hexFigure, U8 bcdNumMax, 
										U32 *pRtnBcd);
extern U32 HexToBcd(U8 hexFigure);



extern U8 BcdToHexU8(U8 bcdFigure);
extern U32 BcdToHexU32(U32 bcdFigure);

extern void BcdDecToHex(U32 num,U8* str);


/******************************************************************************
// END :
******************************************************************************/
#endif // __codeFig_H__

