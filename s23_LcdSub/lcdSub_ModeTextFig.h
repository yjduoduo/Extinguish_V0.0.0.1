#ifndef __lcdSub_ModeTextFig_H__
#define __lcdSub_ModeTextFig_H__
/******************************************************************************
* @file    lcdSub_ModeTextFig.h
* @author  yx
* @version V1.4
* @date    2013.10.18 13:51 
* @brief   显示：管理字符和显示位置字符行列；
		显示模式 和 行列管理。字符->buf 一起显示。
		尽量做成 "LcdLib_incOut.h"   的唯一接口。 
* @slave  " hwEx15_lcd_swBuf "
* @paraIn  mRow,mLine参数计算的像素，是以 U_SHOW_HalfChar_HEIGHT U_SHOW_HalfChar_WIDE为单位的；
* @paraIn  mPreCnNum,mPreEnNum参数计算的像素, 列像素=mPreCnNum* U_SHOW_CHAR_CN_WIDE + mPreEnNum * U_SHOW_CHAR_EN_WIDE ;
* @		若想直接控制pix位置，那么用 "hwEx15_lcd_swBuf.h"。

* V1.4, 2013.10.18 13:51 
*		add: ShowTxtBufPix();
*		ShowTextBuf(); 
*		补充条件: (vTextBfIn == 0) (mLine >= U_LCD_LINE_MAX)
* V1.3, 2013.10.17 16:10 
*		add: ClrLcdRlRow();
* V1.2, 2013.09.26 23:38 
		lcd_swBuf函数的 位置参数全改成 pix, 方便 16*16 12*12汉字的统一。
		8*8字符的显示，显示位置的计算，依赖于 U_Show_OneAscii88_LinePix 的设置。
* V1.1, 2013.09.25 23:54 
		加 8*8 字符的函数。
* V1.0，2012-01-05
* 
#include  "lcdSub_ModeTextFig.h"
******************************************************************************/

#include  "prjCompileCon.h"

#include  "lcd_Para.h"
#include  "lcdCst_PgString.h"

/*================= extern ============================================*/
#ifdef  __lcdSub_ModeTextFig_C__
#define EX_lcdSub_ModeTextFig
#else
#define EX_lcdSub_ModeTextFig extern 
#endif

/*================= 常数 ============================================*/

typedef enum {  // emShowUseLib_PIX mUseLib;
	U_ShowUseLib_88orCn_CN = 0,   // 
	U_ShowUseLib_88orCn_88Ascii  = 1,
	U_ShowUseLib_88orCn_Invalid  = 2,
	
}emShowUseLib_PIX;
	
/*================= 结构体定义 ======================================*/

typedef struct{
	U32 fig;
	U8 bitTotal;
	
	BOOL bAllignRight;
	BOOL bShowPre0;
	U8 colorText;
	U8 colorBackGround;
}TShowFigPara_st;

/*================= 公有结构变量声明 ================================*/

/*================= 私有结构变量声明 ================================*/

#ifdef __lcdSub_ModeTextFig_C__
static TShowFigPara_st  vStFigPara;

#endif //__lcdSub_ModeTextFig_C__
/*================= 私有函数声明 ====================================*/
#ifdef __lcdSub_ModeTextFig_C__

// 一个字符的 line pix, 
U32 GetSx_OneChar(void);
// 一个字符的  row pix, 
U32 GetSy_OneChar(void);

U8 *pGetCstChar(const TCstChar_st *pCstChar);

// 由字符行列 计算 xyPix, 
// OUT: vSx, vSy.
TYPE_LCD_XY getPixYR_formRow(TYPE_LCD_RL mRow);
TYPE_LCD_XY getPixXL_formLine(TYPE_LCD_RL mLine);
TYPE_LCD_XY getPixXL_formCharNum(U8 mPreCnNum, U8 mPreEnNum);
TYPE_LCD_XY getPixXL_Ascii8_formLine(TYPE_LCD_RL mLine);

void SetNowRL(TYPE_LCD_RL mRow, TYPE_LCD_RL mLine);
void setPix_y_pixRow(TYPE_LCD_XY  mPixYR);
void setPix_x_pixLine(TYPE_LCD_XY  mPixXL);
void setPix_y_x_pixRowLine(TYPE_LCD_XY  mPixYR, TYPE_LCD_XY  mPixXL);
TYPE_LCD_XY GetPix_x_pixLine(void);

//  
static void sw_fig_setPara_usual(U32 fig, U8 bitTotal, 
							TShowFigPara_st *pShowFigPara);
static void sw_fig_setPara_mode(
						TShowFigPara_st *pShowFigPara,
						U8 *pRtnFigAlignMode, U8 *pRtnFigShow0);

void showLib_Figure(emShowUseLib_PIX mUseLib,
					TYPE_LCD_RL mRow, TYPE_LCD_RL mLine,
					TShowFigPara_st *pShowFigPara);
// * FUNC: // 显示与汉字同高的数字:
// *   IN:   mPreCnNum = 列，前面有mPreCnNum个汉字; 每个占16或12pix;
// *   IN:   mPreEnNum = 列，前面有mPreEnNum个字符; 每个占8 pix;
void showXY_Figure(TYPE_LCD_RL mRow, 
					U8 mPreCnNum, U8 mPreEnNum,
					TShowFigPara_st *pShowFigPara);


// 显示前面的0：
void showLib_Fig_Pre0(U8 mUseLib,
						TYPE_LCD_RL mRow, TYPE_LCD_RL mLine,
						U32 fig, U8 bitTotal
						);
// 不显示前面的0 + 右对齐：
void showLib_Fig_RightAllign(emShowUseLib_PIX mUseLib,
						TYPE_LCD_RL mRow, TYPE_LCD_RL mLine,
						U32 fig, U8 bitTotal
						);
// 不显示前面的0 + 左对齐：
void showLib_Fig_LeftAllign(emShowUseLib_PIX mUseLib, 
						TYPE_LCD_RL mRow, TYPE_LCD_RL mLine,
						U32 fig, U8 bitTotal
						);

// 1bit数字，正常显示 | 反显：
void showLib_1Fig_if_inverse(emShowUseLib_PIX mUseLib, 
						TYPE_LCD_RL mRow, TYPE_LCD_RL mLine,
						U8 fig, BOOL bInverse);
#endif //__lcdSub_ModeTextFig_C__


/*=========== 公有函数声明-数字-与汉字同高 - pixX来自前面的字符数 =============*/
//EX_lcdSub_ModeTextFig 

// 显示前面的0：
extern void ShowXY_Fig_Pre0(TYPE_LCD_RL mRow, U8 mPreCnNum, U8 mPreEnNum,
			 U32 fig, U8 bitTotal
			 );
// 不显示前面的0 + 右对齐：
extern void ShowXY_Fig_RightAllign(TYPE_LCD_RL mRow, U8 mPreCnNum, U8 mPreEnNum,
			 U32 fig, U8 bitTotal
			 );
// 不显示前面的0 + 左对齐：
extern void ShowXY_Fig_LeftAllign(TYPE_LCD_RL mRow, U8 mPreCnNum, U8 mPreEnNum,
			 U32 fig, U8 bitTotal
			 );
// 1bit数字，正常显示 | 反显：
extern void ShowXY_1Fig_if_inverse(TYPE_LCD_RL mRow, U8 mPreCnNum, U8 mPreEnNum,
							U8 fig, BOOL bInverse);
// 1bit数字，正常显示：
extern void ShowXY_1Fig_usual(TYPE_LCD_RL mRow, U8 mPreCnNum, U8 mPreEnNum,
							U8 fig );
// 1bit数字，反显：
extern void ShowXY_1Fig_inverse(TYPE_LCD_RL mRow, U8 mPreCnNum, U8 mPreEnNum,
							U8 fig );

/*========== 公有函数声明-数字-与汉字同高 - pixX 对齐半个汉字位置  ============*/
//EX_lcdSub_ModeTextFig 

// 与汉字同高 点阵 显示数字:
extern void Show_Figure(TYPE_LCD_RL mRow, TYPE_LCD_RL mLine,
					TShowFigPara_st *pShowFigPara);
// 显示前面的0：
extern void Show_Fig_Pre0(TYPE_LCD_RL mRow, TYPE_LCD_RL mLine,
			 U32 fig, U8 bitTotal
			 );
// 不显示前面的0 + 右对齐：
extern void Show_Fig_RightAllign(TYPE_LCD_RL mRow, TYPE_LCD_RL mLine,
			 U32 fig, U8 bitTotal
			 );
// 不显示前面的0 + 左对齐：
extern void Show_Fig_LeftAllign(TYPE_LCD_RL mRow, TYPE_LCD_RL mLine,
			 U32 fig, U8 bitTotal
			 );


// 1bit数字，正常显示 | 反显：
extern void Show_1Fig_if_inverse(TYPE_LCD_RL mRow, TYPE_LCD_RL mLine,
							U8 fig, BOOL bInverse);
// 1bit数字，正常显示：
extern void Show_1Fig_usual(TYPE_LCD_RL mRow, TYPE_LCD_RL mLine,
							U8 fig );
// 1bit数字，反显：
extern void Show_1Fig_inverse(TYPE_LCD_RL mRow, TYPE_LCD_RL mLine,
							U8 fig );


/*================= 公有函数声明-数字-8*8 点阵 ====================================*/
// 8*8 点阵显示数字:
extern void Show88_Figure(TYPE_LCD_RL mRow, TYPE_LCD_RL mLine,
					TShowFigPara_st *pShowFigPara);
// 显示前面的0：
extern void Show88_Fig_Pre0(TYPE_LCD_RL mRow, TYPE_LCD_RL mLine,
			 U32 fig, U8 bitTotal
			 );
// 不显示前面的0 + 右对齐：
extern void Show88_Fig_RightAllign(TYPE_LCD_RL mRow, TYPE_LCD_RL mLine,
			 U32 fig, U8 bitTotal
			 );
// 不显示前面的0 + 左对齐：
extern void Show88_Fig_LeftAllign(TYPE_LCD_RL mRow, TYPE_LCD_RL mLine,
			 U32 fig, U8 bitTotal
			 );

// 8*8 点阵显示数字:
// 1bit数字，正常显示 | 反显：
extern void Show88_1Fig_if_inverse(TYPE_LCD_RL mRow, TYPE_LCD_RL mLine,
							U8 fig, BOOL bInverse);
// 1bit数字，正常显示：
extern void Show88_1Fig_usual(TYPE_LCD_RL mRow, TYPE_LCD_RL mLine,
							U8 fig );
// 1bit数字，反显：
extern void Show88_1Fig_inverse(TYPE_LCD_RL mRow, TYPE_LCD_RL mLine,
							U8 fig );


/*================= 公有函数声明-字符或汉字 ====================================*/
//EX_lcdSub_ModeTextFig 

extern void SetMenuHeadMode(void);
extern void SetMenuMode(U8 bSelect);
extern void SetTextMode(void);

extern void ShowMenu(TYPE_LCD_RL mRow, TYPE_LCD_RL mLine);
extern void ShowMenuHead(void);

extern TYPE_LCD_XY ShowCstCharRL(TYPE_LCD_RL mRow, TYPE_LCD_RL mLine, 
							const TCstChar_st *pCstChar);

// 显示 " " 内的字符：  // ShowCodeCharRL(0, 0, " ", FALSE);
extern void ShowCodeCharRL(TYPE_LCD_RL mRow, TYPE_LCD_RL mLine, 
						const U8 *pCodeChar, BOOL bInverse);
extern void ShowXYCodeCharRL(TYPE_LCD_RL mRow, 
						U8 mPreCnNum, U8 mPreEnNum, 
						const U8 *pCodeChar, BOOL bInverse);
extern void Show88CodeCharRL(TYPE_LCD_RL mRow, TYPE_LCD_RL mLine, 
						const U8 *pCodeChar, BOOL bInverse);


extern void ClrWindow_Page(void);
extern void ClrWindow_Menu(void);

// 清除行 mRowFrom ~ (mRowEnd-1) // 清除1行：(1,2)
extern void ClrLcdRlRow(TYPE_LCD_RL mRowFrom, TYPE_LCD_RL mRowEnd);



/*================= 公有函数声明-字符或汉字 进入buf一起显示 ====================================*/
// EX_lcdSub_ModeTextFig

// 显示一条的字符buf
extern void IniTextBuf(emShowUseLib_PIX  mUseLib);
extern BOOL bTextBufEmpty(void);
extern U32 AddToTextBuf(U8 *pChar);
// AddCodeStrToTextBuf("*__*");
extern U32 AddCodeStrToTextBuf(U8 *pChar);
// swTotal += AddCstStrToTextBuf(&cstChar_Total);
extern U32 AddCstStrToTextBuf(const TCstChar_st *pCstChar);

// 显示 AddToTextBuf() 的 string.
// OUT : 列 像素地址
// (mRow, mLine)
extern TYPE_LCD_XY ShowTextBuf(TYPE_LCD_RL mRow, TYPE_LCD_RL mLine);
extern TYPE_LCD_XY ShowTxtBufPix(TYPE_LCD_XY mPixRow, TYPE_LCD_XY mPixLine);


/******************************************************************************
// END :
******************************************************************************/
#endif // __lcdSub_ModeTextFig_H__

