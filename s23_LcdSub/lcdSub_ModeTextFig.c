
#define __lcdSub_ModeTextFig_C__
/******************************************************************************
* @file    lcdSub_ModeTextFig.c
* @author  yx
* @version V1.0
* @date    2012-01-05
* @brief   显示模式 和 行列管理。
		字符->buf 一起显示。
		尽量做成 "hwEx15_lcd_swBuf.h" 的唯一接口。
* 
*  涉及行列的都是半角字符。
******************************************************************************/
#include  "lcdSub_ModeTextFig.h"

//#include "..\\s00Prj\\incFile.h"	

//-----------------   --------------------------------// 
#include  "tsk_lcd_incIn.h"
//----- Me:
#include  "LcdLib_incOut.h"

/*================= 常数 ============================================*/
#define U_MENU_HEAD_START    0
#define U_MENU_HEAD_HEIGHT   0



/*================= 结构定义 ========================================*/

typedef struct{
	
	U8   figShow0; 			//U_LcdMode_FigShow0
	U8   figAlignMode; 		//U_LcdMode_FigAlignRight
	U8   textSize;  		//(0=1) ~ 4
	
	U8   mUseLib; // emShowUseLib_PIX
	
	
	TLcdXY_st stLcdXY; //temp
	TLcdRL_st stLcdRL; //行列
	
	U8 textMode; //emTextMode
}TLcdShow_st;

TLcdShow_st  vStLcdShow;

enum emTextMode{
	U_TextMode_MenuHead,
	U_TextMode_MenuItem,
	U_TextMode_Text,
};


TYPE_LCD_RL vRow;
TYPE_LCD_RL vLine;
TYPE_LCD_XY vSx;  // 
TYPE_LCD_XY vSy; // 192*64的屏，这个未用。

#define U_TEXT_BUF_MAX    200
static U32 vTextBfIn;
static U8 vTextBuf[U_TEXT_BUF_MAX];
/*================= 私有结构变量声明 ================================*/

/*================= 公有函数声明 ====================================*/

/*================= 私有函数声明 ====================================*/

/*=================  ================================================*/
		



/******************************************************************************
* FUNC: //
*  OUT: vSx, vSy
******************************************************************************/

TYPE_LCD_XY getPixYR_formRow(TYPE_LCD_RL mRow)
{

#if  U_CharLib_NOW==U_CharLib_12
TYPE_LCD_XY mPixRow;

	mPixRow = mRow * U_SHOW_HalfChar_HEIGHT;
	//if((mRow%2) == 0)
	{
		mPixRow += (mRow/2);
	}
	return mPixRow;
	
#else // now = U_CharLib_16
	return mRow * U_SHOW_HalfChar_HEIGHT;

#endif // U_CharLib_NOW
}

TYPE_LCD_XY getPixXL_formLine(TYPE_LCD_RL mLine)
{
	return mLine * U_SHOW_HalfChar_WIDE;
}
TYPE_LCD_XY getPixXL_Ascii8_formLine(TYPE_LCD_RL mLine)
{
	//return mLine * U_Show_OneAscii88_LinePix;
	return getPixXL_formLine(mLine);
}

TYPE_LCD_XY getPixXL_formCharNum(U8 mPreCnNum, U8 mPreEnNum)
{
	return (mPreCnNum* U_SHOW_CHAR_CN_WIDE 
		 + mPreEnNum * U_SHOW_CHAR_EN_WIDE);
}

/******************************************************************************
* FUNC: //
*  OUT: vSx, vSy
******************************************************************************/
void setPix_y_pixRow(TYPE_LCD_XY  mPixYR)
{
	vSy = mPixYR;
}
void setPix_x_pixLine(TYPE_LCD_XY  mPixXL)
{
	vSx = mPixXL;
}
void setPix_y_x_pixRowLine(TYPE_LCD_XY  mPixYR, TYPE_LCD_XY  mPixXL)
{
	vSx = mPixXL;
	vSy = mPixYR;
}


TYPE_LCD_XY GetPix_x_pixLine(void)
{
	return vSx;
}

/******************************************************************************
* FUNC: //
*  OUT: vSx, vSy
******************************************************************************/
// 一个字符的 line pix, 
U32 GetSx_OneChar(void) 
{
	return U_SHOW_HalfChar_WIDE;
}
// 一个字符的  row pix, 
U32 GetSy_OneChar(void)
{
	return U_SHOW_HalfChar_HEIGHT;
}

// 由字符行列 计算 xyPix, 
// OUT: vSx, vSy.
void SetNowRL(TYPE_LCD_RL mRow, TYPE_LCD_RL mLine)
{
	vRow = mRow;
	vLine = mLine;
	switch(vStLcdShow.textMode)
	{
		case U_TextMode_MenuHead:
			vSx = 0; 					//line*16;
			vSy = 0;	//row*16;
			break;
		case U_TextMode_MenuItem:
			vSx = mLine*16;
			vSy = U_MENU_HEAD_HEIGHT + mRow*16;
			break;
		case U_TextMode_Text:
		default:
			vSx = getPixXL_formLine(mLine);
			vSy = getPixYR_formRow(mRow);
			break;
	}
}



/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
U8 *pGetCstChar(const TCstChar_st *pCstChar)
{
	U8 language;
	
	language = GetLanguage();
	switch(language)
	{
		case U_English_LANGUAGE:
			return (unsigned char *)(pCstChar->pEn);
			
			
		case U_Complex_LANGUAGE: //繁体 cmpl
			return (unsigned char *)(pCstChar->pComplex);
			
			
		case U_Chinese_LANGUAGE:
		default:
			return (unsigned char *)(pCstChar->pCn);
			
	}
}


/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
void SetMenuHeadMode(void)
{
	// LcdSw_SetForeColor(U_COLOR_Blue);
	// LcdSw_SetTextMode(U_LcdMode_NoBgColor, U_LcdMode_Bold, 1);
	// vStLcdShow.textSize = 1;
	
	// vStLcdShow.textMode = U_TextMode_MenuHead;
}

void SetMenuMode(U8 bSelect)
{
	// if(bSelect)
	// {
		// LcdSw_SetForeColor(U_COLOR_LightBlue);
		// LcdSw_SetTextMode(U_LcdMode_NoBgColor, U_LcdMode_Bold, 2);
		// vStLcdShow.textSize = 2;
	// }
	// else
	// {
		// LcdSw_SetForeColor(U_COLOR_Red);
		// LcdSw_SetTextMode(U_LcdMode_NoBgColor, U_LcdMode_NoBold, 2);
		// vStLcdShow.textSize = 2;
	// }
	// vStLcdShow.textMode = U_TextMode_MenuItem;
}

void SetTextMode(void)
{
	// LcdSw_SetTextMode(U_LcdMode_NoBgColor, U_LcdMode_NoBold, 2);
	// vStLcdShow.textMode = U_TextMode_Text;
}

/******************************************************************************
* FUNC: //
******************************************************************************/

void ShowMenu(TYPE_LCD_RL mRow, TYPE_LCD_RL mLine)
{
	ShowTextBuf(mRow, mLine);
}

//IN: AddToTextBuf()
void ShowMenuHead(void)
{
	ShowTextBuf(0, 0);	
}



/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 字符数
//参考char *pGetMenuChar(const TMenu *pOneMenu)

nowPixLine = ShowCstCharRL(1, 1, &cstChar_FirAlarm);
******************************************************************************/
TYPE_LCD_XY ShowCstCharRL(TYPE_LCD_RL mRow, TYPE_LCD_RL mLine, 
						const TCstChar_st *pCstChar)
{
U8 *pChar;
TYPE_LCD_XY mPixLine;
	
	SetNowRL(mRow, mLine);
	pChar = pGetCstChar(pCstChar);

	LcdSw_Text_XPixRtn(
					getPixYR_formRow(mRow), 
					getPixXL_formLine(mLine), 
					pChar, &mPixLine);
	setPix_y_x_pixRowLine(
				getPixYR_formRow(mRow), 
				mPixLine);
	
	return mPixLine;
	
}



/******************************************************************************
* FUNC: // 显示 " " 内的字符：
*   IN:
*  OUT: 
// ShowCodeCharRL(0, 0, " ", FALSE);
******************************************************************************/

void ShowCodeCharRL(TYPE_LCD_RL mRow, TYPE_LCD_RL mLine, 
						const U8 *pCodeChar, BOOL bInverse)
{
U8 colorBackGround = U_COLOR_BackGroundDefault;
TYPE_LCD_XY mPixLine = 0;
	
	SetNowRL(mRow, mLine);
	if(bInverse)
	{
		colorBackGround = U_COLOR_Black;
	}
	mPixLine = LcdSw_color_cstText(getPixYR_formRow(mRow),
							getPixXL_formLine(mLine), 
									pCodeChar,
									U_COLOR_TextDefault, 
									colorBackGround);
	setPix_y_x_pixRowLine(
				getPixYR_formRow(mRow), 
				mPixLine);
}


void ShowXYCodeCharRL(TYPE_LCD_RL mRow, 
						U8 mPreCnNum, U8 mPreEnNum, 
						const U8 *pCodeChar, BOOL bInverse)
{
U8 colorBackGround = U_COLOR_BackGroundDefault;
TYPE_LCD_XY mPixLine = 0;
	
	// SetNowRL(mRow, mLine);
	if(bInverse)
	{
		colorBackGround = U_COLOR_Black;
	}
	mPixLine = LcdSw_color_cstText(
					getPixYR_formRow(mRow),
					getPixXL_formCharNum(mPreCnNum, mPreEnNum), 
									pCodeChar,
									U_COLOR_TextDefault, 
									colorBackGround);
	setPix_y_x_pixRowLine(
				getPixYR_formRow(mRow), 
				mPixLine);
}

void Show88CodeCharRL(TYPE_LCD_RL mRow, TYPE_LCD_RL mLine, 
						const U8 *pCodeChar, BOOL bInverse)
{
U8 colorBackGround = U_COLOR_BackGroundDefault;
TYPE_LCD_XY mPixLine = 0;
	
	SetNowRL(mRow, mLine);
	if(bInverse)
	{
		colorBackGround = U_COLOR_Black;
	}
	mPixLine = LcdSw_color_cstAscii88(
								getPixYR_formRow(mRow), 
						getPixXL_Ascii8_formLine(mLine), 
									pCodeChar,
									U_COLOR_TextDefault, 
									colorBackGround);
	setPix_y_x_pixRowLine(
				getPixYR_formRow(mRow), 
				mPixLine);
}
/******************************************************************************
* FUNC: // 显示一条的字符buf
*   IN:
*  OUT: 
******************************************************************************/
void IniTextBuf(emShowUseLib_PIX  mUseLib)
{
#if U_SYS_SoftSimulatState == U_Yes 
	int ii;
	for(ii=0; ii<U_TEXT_BUF_MAX; ii++)		
	{
		vTextBuf[ii] = '\0';
	}
#endif // U_SYS_SoftSimulatState
	
	
	vTextBfIn = 0;
	vStLcdShow.mUseLib = mUseLib;
	
}

// OUT: 字符数
// AddCodeStrToTextBuf("*__*");
U32 AddCodeStrToTextBuf(U8 *pChar)
{
	return AddToTextBuf((U8*)(pChar));
}

// swTotal += AddCstStrToTextBuf(&cstChar_Total);
U32 AddCstStrToTextBuf(const TCstChar_st *pCstChar)
{
	U8 *pChar;
	
	pChar = pGetCstChar(pCstChar);
	
	return AddToTextBuf((U8*)(pChar));
}

U32 AddToTextBuf(U8 *pChar)
{
BOOL bHalf = FALSE;  //防止出现半角字符
BOOL bFinish = FALSE;
U32 nowIn;
	
	nowIn = vTextBfIn;
	while(1)
	{
		if(*pChar == '\0')
		{
			bFinish = TRUE;
		}
		
		else if(vTextBfIn < (U_TEXT_BUF_MAX-1)) // -1 是给最后的停止符留空
		{
			if(*pChar >= 160)
			{
				bHalf = LogicInverse(bHalf);
			}
			vTextBuf[vTextBfIn] = *pChar++;
			vTextBfIn++;
		}
		else
		{
			bFinish = TRUE;
		}
		
		if(bFinish)
		{
			if(bHalf)
			{
				vTextBfIn--;
			}
			//只有最后才加
			//vTextBuf[vTextBfIn] = '\0'; 
			//vTextBfIn++;
			break;
			
		}
	}
	return (vTextBfIn - nowIn);
}

BOOL bTextBufEmpty(void)
{
	return (vTextBfIn == 0);
}

// 显示 AddToTextBuf() 的 string.
// OUT : 列 像素地址
// (mRow, mLine)
TYPE_LCD_XY ShowTextBuf(TYPE_LCD_RL mRow, TYPE_LCD_RL mLine)
{
TYPE_LCD_XY mPixLine;

	if(  (vTextBfIn >= U_TEXT_BUF_MAX)
	  || (vTextBfIn == 0)
	  || (mRow >= U_LCD_ROW_MAX)
	  || (mLine >= U_LCD_LINE_MAX)
	  )
	{
		IniTextBuf(U_ShowUseLib_88orCn_Invalid);
		return getPixXL_formLine(mLine);
	}
	vTextBuf[vTextBfIn] = '\0';
	
	SetNowRL(mRow, mLine);
	
	if(vStLcdShow.mUseLib == U_ShowUseLib_88orCn_CN)
	{
		LcdSw_Text_XPixRtn(getPixYR_formRow(mRow),
						   getPixXL_formLine(mLine),
							&vTextBuf[0], &mPixLine);
	}
	else if(vStLcdShow.mUseLib == U_ShowUseLib_88orCn_88Ascii)
	{
		LcdSw_Ascii88_XPixRtn(getPixYR_formRow(mRow),
						   getPixXL_formLine(mLine),
							&vTextBuf[0], &mPixLine);
	}
	IniTextBuf(U_ShowUseLib_88orCn_Invalid);
	
	setPix_y_x_pixRowLine(
				getPixYR_formRow(mRow), 
				mPixLine);
	
	return mPixLine;
}


TYPE_LCD_XY ShowTxtBufPix(TYPE_LCD_XY mPixRow, TYPE_LCD_XY mPixLine)
{

	if(  (vTextBfIn >= U_TEXT_BUF_MAX)
	  || (vTextBfIn == 0)
	  || (mPixRow >= U_LCD_ROW_PIX_MAX)
	  || (mPixLine >= U_LCD_LINE_PIX_MAX)
	  )
	{
		IniTextBuf(U_ShowUseLib_88orCn_Invalid);
		return mPixLine;
	}
	vTextBuf[vTextBfIn] = '\0';
	
	setPix_y_x_pixRowLine(mPixRow, mPixLine);
	
	if(vStLcdShow.mUseLib == U_ShowUseLib_88orCn_CN)
	{
		LcdSw_Text_XPixRtn(mPixRow, mPixLine,
							&vTextBuf[0], &mPixLine);
	}
	else if(vStLcdShow.mUseLib == U_ShowUseLib_88orCn_88Ascii)
	{
		LcdSw_Ascii88_XPixRtn(mPixRow, mPixLine,
							&vTextBuf[0], &mPixLine);
	}
	IniTextBuf(U_ShowUseLib_88orCn_Invalid);
	
	setPix_y_x_pixRowLine(mPixRow, mPixLine);
	
	return mPixLine;
}


/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

void ClrWindow_Page(void)
{
	LcdSw_ClrFullWindow(U_COLOR_BackGroundDefault);
}

void ClrWindow_Menu(void)
{
	LcdSw_ClrFullWindow(U_COLOR_BackGroundDefault);
}

// 清除行 mRowFrom ~ (mRowEnd-1) // 清除1行：(1,2)
void ClrLcdRlRow(TYPE_LCD_RL mRowFrom, TYPE_LCD_RL mRowEnd)
{
	LcdSw_ClrRectangle(
					getPixYR_formRow(mRowFrom), 
					0,
					getPixYR_formRow(mRowEnd), 
					U_LCD_LINE_PIX_MAX);
}


/******************************************************************************
* FUNC: //
// 与汉字同高 点阵 显示数字:
*   IN:
*  OUT: 
******************************************************************************/

void Show_Figure(TYPE_LCD_RL mRow, TYPE_LCD_RL mLine,
					TShowFigPara_st *pShowFigPara)
{
	showLib_Figure(U_ShowUseLib_88orCn_CN,
					mRow, mLine, pShowFigPara);
}


// 显示前面的0：
void Show_Fig_Pre0(TYPE_LCD_RL mRow, TYPE_LCD_RL mLine,
						U32 fig, U8 bitTotal
						)
{
	showLib_Fig_Pre0(U_ShowUseLib_88orCn_CN,
					mRow, mLine, fig, bitTotal);
}


// 不显示前面的0 + 右对齐：
void Show_Fig_RightAllign(TYPE_LCD_RL mRow, TYPE_LCD_RL mLine,
						U32 fig, U8 bitTotal
						)
{
	showLib_Fig_RightAllign(U_ShowUseLib_88orCn_CN,
					mRow, mLine, fig, bitTotal);
}

// 不显示前面的0 + 左对齐：
void Show_Fig_LeftAllign(TYPE_LCD_RL mRow, TYPE_LCD_RL mLine,
						U32 fig, U8 bitTotal
						)
{
	showLib_Fig_LeftAllign(U_ShowUseLib_88orCn_CN,
					mRow, mLine, fig, bitTotal);
}


/******************************************************************************
* FUNC: // 8*8 点阵显示数字
*   IN:
*  OUT: 
******************************************************************************/

void Show88_Figure(TYPE_LCD_RL mRow, TYPE_LCD_RL mLine,
					TShowFigPara_st *pShowFigPara)
{
	showLib_Figure(U_ShowUseLib_88orCn_88Ascii,
					mRow, mLine, pShowFigPara);
}


// 显示前面的0：
void Show88_Fig_Pre0(TYPE_LCD_RL mRow, TYPE_LCD_RL mLine,
						U32 fig, U8 bitTotal
						)
{
	showLib_Fig_Pre0(U_ShowUseLib_88orCn_88Ascii,
					mRow, mLine, fig, bitTotal);
}


// 不显示前面的0 + 右对齐：
void Show88_Fig_RightAllign(TYPE_LCD_RL mRow, TYPE_LCD_RL mLine,
						U32 fig, U8 bitTotal
						)
{
	showLib_Fig_RightAllign(U_ShowUseLib_88orCn_88Ascii,
					mRow, mLine, fig, bitTotal);
}

// 不显示前面的0 + 左对齐：
void Show88_Fig_LeftAllign(TYPE_LCD_RL mRow, TYPE_LCD_RL mLine,
						U32 fig, U8 bitTotal
						)
{
	showLib_Fig_LeftAllign(U_ShowUseLib_88orCn_88Ascii,
					mRow, mLine, fig, bitTotal);
}




/******************************************************************************
* FUNC: // 显示与汉字同高的数字:
*   IN:   mPreCnNum = 列，前面有mPreCnNum个汉字; 每个占16或12pix;
*   IN:   mPreEnNum = 列，前面有mPreEnNum个字符; 每个占8 pix;
*  OUT: 
******************************************************************************/


void showXY_Figure(TYPE_LCD_RL mRow, U8 mPreCnNum, U8 mPreEnNum,
					TShowFigPara_st *pShowFigPara)
{
U8 figAlignMode;
U8 figShow0;
TYPE_LCD_XY mNowPixLine;

	// SetNowRL(mRow, mLine);
	
	sw_fig_setPara_mode(pShowFigPara,
					   &figAlignMode, &figShow0);

	LcdSw_SetFigMode(figShow0, figAlignMode);
	
	mNowPixLine = LcdSw_color_Fig(
				getPixYR_formRow(mRow),
				getPixXL_formCharNum(mPreCnNum, mPreEnNum), 
				pShowFigPara->fig, 
				pShowFigPara->bitTotal,
				pShowFigPara->colorText, 
				pShowFigPara->colorBackGround
				);
	setPix_y_x_pixRowLine(
				getPixYR_formRow(mRow), 
				mNowPixLine);
	
}


/******************************************************************************
* FUNC: // 显示与汉字同高的数字:
*   IN:   mPreCnNum = 列，前面有mPreCnNum个汉字; 每个占16或12pix;
*   IN:   mPreEnNum = 列，前面有mPreEnNum个字符; 每个占8 pix;
*  OUT: 
******************************************************************************/

// 显示前面的0：
void ShowXY_Fig_Pre0(TYPE_LCD_RL mRow, U8 mPreCnNum, U8 mPreEnNum,
			 U32 fig, U8 bitTotal
			 )
{
	vStFigPara.bShowPre0 = TRUE;
	vStFigPara.bAllignRight = TRUE;
	sw_fig_setPara_usual(fig, bitTotal, &vStFigPara);
	
	showXY_Figure(mRow, mPreCnNum, mPreEnNum, &vStFigPara);
	
}

// 不显示前面的0 + 右对齐：
void ShowXY_Fig_RightAllign(TYPE_LCD_RL mRow, U8 mPreCnNum, U8 mPreEnNum,
			 U32 fig, U8 bitTotal
			 )
{
	vStFigPara.bShowPre0 = FALSE;
	vStFigPara.bAllignRight = TRUE;
	sw_fig_setPara_usual(fig, bitTotal, &vStFigPara);
	
	showXY_Figure(mRow, mPreCnNum, mPreEnNum, &vStFigPara);
	
}

// 不显示前面的0 + 左对齐：
void ShowXY_Fig_LeftAllign(TYPE_LCD_RL mRow, U8 mPreCnNum, U8 mPreEnNum,
			 U32 fig, U8 bitTotal
			 )
{
	vStFigPara.bShowPre0 = FALSE;
	vStFigPara.bAllignRight = FALSE;
	sw_fig_setPara_usual(fig, bitTotal, &vStFigPara);
	
	showXY_Figure(mRow, mPreCnNum, mPreEnNum, &vStFigPara);
	
}

// 1bit数字，正常显示 | 反显：
void ShowXY_1Fig_if_inverse(TYPE_LCD_RL mRow, U8 mPreCnNum, U8 mPreEnNum,
							U8 fig, BOOL bInverse)
{
	vStFigPara.bShowPre0 = TRUE;
	vStFigPara.bAllignRight = TRUE;
	sw_fig_setPara_usual(fig, 1, &vStFigPara);
	if(bInverse)
	{
		vStFigPara.colorBackGround = U_COLOR_Black;
	}
	
	showXY_Figure(mRow, mPreCnNum, mPreEnNum, &vStFigPara);
	
}

// 1bit数字，正常显示：
void ShowXY_1Fig_usual(TYPE_LCD_RL mRow, U8 mPreCnNum, U8 mPreEnNum,
							U8 fig )
{
	ShowXY_1Fig_if_inverse(mRow, mPreCnNum, mPreEnNum, fig, FALSE);
}

// 1bit数字，反显：
void ShowXY_1Fig_inverse(TYPE_LCD_RL mRow, U8 mPreCnNum, U8 mPreEnNum,
							U8 fig )
{
	ShowXY_1Fig_if_inverse(mRow, mPreCnNum, mPreEnNum, fig, TRUE);
}




/******************************************************************************
* FUNC: //
*   IN:  
*  OUT: 
******************************************************************************/

void showLib_Figure(emShowUseLib_PIX mUseLib,
					TYPE_LCD_RL mRow, TYPE_LCD_RL mLine,
					TShowFigPara_st *pShowFigPara)
{
U8 figAlignMode;
U8 figShow0;
TYPE_LCD_XY mNowPixLine = 0;

	SetNowRL(mRow, mLine);
	
	sw_fig_setPara_mode(pShowFigPara,
					   &figAlignMode, &figShow0);

	LcdSw_SetFigMode(figShow0, figAlignMode);
	
	if(mUseLib == U_ShowUseLib_88orCn_CN)
	{
		mNowPixLine = LcdSw_color_Fig(
					getPixYR_formRow(mRow),
					getPixXL_formLine(mLine),
					pShowFigPara->fig, 
					pShowFigPara->bitTotal,
					pShowFigPara->colorText, 
					pShowFigPara->colorBackGround
					);
	}
	else 
	{
		mNowPixLine = LcdSw_color_Ascii88Fig(
					getPixYR_formRow(mRow),
					getPixXL_Ascii8_formLine(mLine), 
					pShowFigPara->fig, 
					pShowFigPara->bitTotal,
					pShowFigPara->colorText, 
					pShowFigPara->colorBackGround
					);
	}
	setPix_y_x_pixRowLine(
				getPixYR_formRow(mRow), 
				mNowPixLine);
	
}


/******************************************************************************
* FUNC: //
******************************************************************************/

// 显示前面的0：
void showLib_Fig_Pre0(emShowUseLib_PIX mUseLib,
						TYPE_LCD_RL mRow, TYPE_LCD_RL mLine,
						U32 fig, U8 bitTotal
						)
{
	
	vStFigPara.bShowPre0 = TRUE;
	vStFigPara.bAllignRight = TRUE;
	sw_fig_setPara_usual(fig, bitTotal, &vStFigPara);
	
	showLib_Figure(mUseLib, mRow, mLine, &vStFigPara);
}

/******************************************************************************
* FUNC: //
******************************************************************************/



// 不显示前面的0 + 右对齐：
void showLib_Fig_RightAllign(emShowUseLib_PIX mUseLib,
						TYPE_LCD_RL mRow, TYPE_LCD_RL mLine,
						U32 fig, U8 bitTotal
						)
{
	
	vStFigPara.bShowPre0 = FALSE;
	vStFigPara.bAllignRight = TRUE;
	sw_fig_setPara_usual(fig, bitTotal, &vStFigPara);
	
	showLib_Figure(mUseLib, mRow, mLine, &vStFigPara);
}

/******************************************************************************
* FUNC: //
******************************************************************************/

// 不显示前面的0 + 左对齐：
void showLib_Fig_LeftAllign(emShowUseLib_PIX mUseLib, 
						TYPE_LCD_RL mRow, TYPE_LCD_RL mLine,
						U32 fig, U8 bitTotal
						)
{
	vStFigPara.bShowPre0 = FALSE;
	vStFigPara.bAllignRight = FALSE;
	sw_fig_setPara_usual(fig, bitTotal, &vStFigPara);
	
	showLib_Figure(mUseLib, mRow, mLine, &vStFigPara);
}

/******************************************************************************
* FUNC: //
******************************************************************************/

static void sw_fig_setPara_mode(TShowFigPara_st *pShowFigPara,
						U8 *pRtnFigAlignMode, U8 *pRtnFigShow0)
{
	*pRtnFigAlignMode = U_LcdMode_FigAlignLeft;
	
	if(pShowFigPara->bAllignRight)
	{
		*pRtnFigAlignMode = U_LcdMode_FigAlignRight;
	}
	
	
	*pRtnFigShow0 = U_LcdMode_DontFigShow0;
	if(pShowFigPara->bShowPre0)
	{
		*pRtnFigShow0 = U_LcdMode_FigShow0;
	}
}


/******************************************************************************
* FUNC: //
******************************************************************************/

static void sw_fig_setPara_usual(U32 fig, U8 bitTotal, 
								TShowFigPara_st *pShowFigPara)
{
	pShowFigPara->fig = fig;
	pShowFigPara->bitTotal = bitTotal;
	pShowFigPara->colorText = U_COLOR_TextDefault;
	pShowFigPara->colorBackGround = U_COLOR_BackGroundDefault;
}

/******************************************************************************
* FUNC: //
******************************************************************************/

// 1bit数字，正常显示 | 反显：
void showLib_1Fig_if_inverse(emShowUseLib_PIX mUseLib, 
							TYPE_LCD_RL mRow, TYPE_LCD_RL mLine,
							U8 fig, BOOL bInverse)
{
	vStFigPara.bShowPre0 = TRUE;
	vStFigPara.bAllignRight = TRUE;
	sw_fig_setPara_usual(fig, 1, &vStFigPara);
	if(bInverse)
	{
		vStFigPara.colorBackGround = U_COLOR_Black;
	}
	
	showLib_Figure(mUseLib, mRow, mLine, &vStFigPara);
}


/******************************************************************************
* FUNC: //
// 与汉字同高 点阵 显示数字:
*   IN:
*  OUT: 
******************************************************************************/
// 1bit数字，正常显示 | 反显：
void Show_1Fig_if_inverse(TYPE_LCD_RL mRow, TYPE_LCD_RL mLine,
							U8 fig, BOOL bInverse)
{
	showLib_1Fig_if_inverse(U_ShowUseLib_88orCn_CN,
					mRow, mLine, fig, bInverse);
}



// 1bit数字，正常显示：
void Show_1Fig_usual(TYPE_LCD_RL mRow, TYPE_LCD_RL mLine,
							U8 fig)
{
	showLib_1Fig_if_inverse(U_ShowUseLib_88orCn_CN,
					mRow, mLine, fig, FALSE);
}


// 1bit数字，反显：
void Show_1Fig_inverse(TYPE_LCD_RL mRow, TYPE_LCD_RL mLine,
							U8 fig )
{
	showLib_1Fig_if_inverse(U_ShowUseLib_88orCn_CN,
					mRow, mLine, fig, TRUE);
}


/******************************************************************************
* FUNC: //
// 8*8 点阵显示数字:
*   IN:
*  OUT: 
******************************************************************************/
// 1bit数字，正常显示 | 反显：
void Show88_1Fig_if_inverse(TYPE_LCD_RL mRow, TYPE_LCD_RL mLine,
							U8 fig, BOOL bInverse)
{
	showLib_1Fig_if_inverse(U_ShowUseLib_88orCn_88Ascii,
					mRow, mLine, fig, bInverse);
}



// 1bit数字，正常显示：
void Show88_1Fig_usual(TYPE_LCD_RL mRow, TYPE_LCD_RL mLine,
							U8 fig)
{
	showLib_1Fig_if_inverse(U_ShowUseLib_88orCn_88Ascii,
					mRow, mLine, fig, FALSE);
}


// 1bit数字，反显：
void Show88_1Fig_inverse(TYPE_LCD_RL mRow, TYPE_LCD_RL mLine,
							U8 fig )
{
	showLib_1Fig_if_inverse(U_ShowUseLib_88orCn_88Ascii,
					mRow, mLine, fig, TRUE);
}








/******************************************************************************
* FUNC: // END 
*   IN:
*  OUT: 
******************************************************************************/
