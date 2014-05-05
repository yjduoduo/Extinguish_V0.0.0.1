#ifndef __lcdSub_ModeTextFig_H__
#define __lcdSub_ModeTextFig_H__
/******************************************************************************
* @file    lcdSub_ModeTextFig.h
* @author  yx
* @version V1.4
* @date    2013.10.18 13:51 
* @brief   ��ʾ�������ַ�����ʾλ���ַ����У�
		��ʾģʽ �� ���й����ַ�->buf һ����ʾ��
		�������� "LcdLib_incOut.h"   ��Ψһ�ӿڡ� 
* @slave  " hwEx15_lcd_swBuf "
* @paraIn  mRow,mLine������������أ����� U_SHOW_HalfChar_HEIGHT U_SHOW_HalfChar_WIDEΪ��λ�ģ�
* @paraIn  mPreCnNum,mPreEnNum�������������, ������=mPreCnNum* U_SHOW_CHAR_CN_WIDE + mPreEnNum * U_SHOW_CHAR_EN_WIDE ;
* @		����ֱ�ӿ���pixλ�ã���ô�� "hwEx15_lcd_swBuf.h"��

* V1.4, 2013.10.18 13:51 
*		add: ShowTxtBufPix();
*		ShowTextBuf(); 
*		��������: (vTextBfIn == 0) (mLine >= U_LCD_LINE_MAX)
* V1.3, 2013.10.17 16:10 
*		add: ClrLcdRlRow();
* V1.2, 2013.09.26 23:38 
		lcd_swBuf������ λ�ò���ȫ�ĳ� pix, ���� 16*16 12*12���ֵ�ͳһ��
		8*8�ַ�����ʾ����ʾλ�õļ��㣬������ U_Show_OneAscii88_LinePix �����á�
* V1.1, 2013.09.25 23:54 
		�� 8*8 �ַ��ĺ�����
* V1.0��2012-01-05
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

/*================= ���� ============================================*/

typedef enum {  // emShowUseLib_PIX mUseLib;
	U_ShowUseLib_88orCn_CN = 0,   // 
	U_ShowUseLib_88orCn_88Ascii  = 1,
	U_ShowUseLib_88orCn_Invalid  = 2,
	
}emShowUseLib_PIX;
	
/*================= �ṹ�嶨�� ======================================*/

typedef struct{
	U32 fig;
	U8 bitTotal;
	
	BOOL bAllignRight;
	BOOL bShowPre0;
	U8 colorText;
	U8 colorBackGround;
}TShowFigPara_st;

/*================= ���нṹ�������� ================================*/

/*================= ˽�нṹ�������� ================================*/

#ifdef __lcdSub_ModeTextFig_C__
static TShowFigPara_st  vStFigPara;

#endif //__lcdSub_ModeTextFig_C__
/*================= ˽�к������� ====================================*/
#ifdef __lcdSub_ModeTextFig_C__

// һ���ַ��� line pix, 
U32 GetSx_OneChar(void);
// һ���ַ���  row pix, 
U32 GetSy_OneChar(void);

U8 *pGetCstChar(const TCstChar_st *pCstChar);

// ���ַ����� ���� xyPix, 
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
// * FUNC: // ��ʾ�뺺��ͬ�ߵ�����:
// *   IN:   mPreCnNum = �У�ǰ����mPreCnNum������; ÿ��ռ16��12pix;
// *   IN:   mPreEnNum = �У�ǰ����mPreEnNum���ַ�; ÿ��ռ8 pix;
void showXY_Figure(TYPE_LCD_RL mRow, 
					U8 mPreCnNum, U8 mPreEnNum,
					TShowFigPara_st *pShowFigPara);


// ��ʾǰ���0��
void showLib_Fig_Pre0(U8 mUseLib,
						TYPE_LCD_RL mRow, TYPE_LCD_RL mLine,
						U32 fig, U8 bitTotal
						);
// ����ʾǰ���0 + �Ҷ��룺
void showLib_Fig_RightAllign(emShowUseLib_PIX mUseLib,
						TYPE_LCD_RL mRow, TYPE_LCD_RL mLine,
						U32 fig, U8 bitTotal
						);
// ����ʾǰ���0 + ����룺
void showLib_Fig_LeftAllign(emShowUseLib_PIX mUseLib, 
						TYPE_LCD_RL mRow, TYPE_LCD_RL mLine,
						U32 fig, U8 bitTotal
						);

// 1bit���֣�������ʾ | ���ԣ�
void showLib_1Fig_if_inverse(emShowUseLib_PIX mUseLib, 
						TYPE_LCD_RL mRow, TYPE_LCD_RL mLine,
						U8 fig, BOOL bInverse);
#endif //__lcdSub_ModeTextFig_C__


/*=========== ���к�������-����-�뺺��ͬ�� - pixX����ǰ����ַ��� =============*/
//EX_lcdSub_ModeTextFig 

// ��ʾǰ���0��
extern void ShowXY_Fig_Pre0(TYPE_LCD_RL mRow, U8 mPreCnNum, U8 mPreEnNum,
			 U32 fig, U8 bitTotal
			 );
// ����ʾǰ���0 + �Ҷ��룺
extern void ShowXY_Fig_RightAllign(TYPE_LCD_RL mRow, U8 mPreCnNum, U8 mPreEnNum,
			 U32 fig, U8 bitTotal
			 );
// ����ʾǰ���0 + ����룺
extern void ShowXY_Fig_LeftAllign(TYPE_LCD_RL mRow, U8 mPreCnNum, U8 mPreEnNum,
			 U32 fig, U8 bitTotal
			 );
// 1bit���֣�������ʾ | ���ԣ�
extern void ShowXY_1Fig_if_inverse(TYPE_LCD_RL mRow, U8 mPreCnNum, U8 mPreEnNum,
							U8 fig, BOOL bInverse);
// 1bit���֣�������ʾ��
extern void ShowXY_1Fig_usual(TYPE_LCD_RL mRow, U8 mPreCnNum, U8 mPreEnNum,
							U8 fig );
// 1bit���֣����ԣ�
extern void ShowXY_1Fig_inverse(TYPE_LCD_RL mRow, U8 mPreCnNum, U8 mPreEnNum,
							U8 fig );

/*========== ���к�������-����-�뺺��ͬ�� - pixX ����������λ��  ============*/
//EX_lcdSub_ModeTextFig 

// �뺺��ͬ�� ���� ��ʾ����:
extern void Show_Figure(TYPE_LCD_RL mRow, TYPE_LCD_RL mLine,
					TShowFigPara_st *pShowFigPara);
// ��ʾǰ���0��
extern void Show_Fig_Pre0(TYPE_LCD_RL mRow, TYPE_LCD_RL mLine,
			 U32 fig, U8 bitTotal
			 );
// ����ʾǰ���0 + �Ҷ��룺
extern void Show_Fig_RightAllign(TYPE_LCD_RL mRow, TYPE_LCD_RL mLine,
			 U32 fig, U8 bitTotal
			 );
// ����ʾǰ���0 + ����룺
extern void Show_Fig_LeftAllign(TYPE_LCD_RL mRow, TYPE_LCD_RL mLine,
			 U32 fig, U8 bitTotal
			 );


// 1bit���֣�������ʾ | ���ԣ�
extern void Show_1Fig_if_inverse(TYPE_LCD_RL mRow, TYPE_LCD_RL mLine,
							U8 fig, BOOL bInverse);
// 1bit���֣�������ʾ��
extern void Show_1Fig_usual(TYPE_LCD_RL mRow, TYPE_LCD_RL mLine,
							U8 fig );
// 1bit���֣����ԣ�
extern void Show_1Fig_inverse(TYPE_LCD_RL mRow, TYPE_LCD_RL mLine,
							U8 fig );


/*================= ���к�������-����-8*8 ���� ====================================*/
// 8*8 ������ʾ����:
extern void Show88_Figure(TYPE_LCD_RL mRow, TYPE_LCD_RL mLine,
					TShowFigPara_st *pShowFigPara);
// ��ʾǰ���0��
extern void Show88_Fig_Pre0(TYPE_LCD_RL mRow, TYPE_LCD_RL mLine,
			 U32 fig, U8 bitTotal
			 );
// ����ʾǰ���0 + �Ҷ��룺
extern void Show88_Fig_RightAllign(TYPE_LCD_RL mRow, TYPE_LCD_RL mLine,
			 U32 fig, U8 bitTotal
			 );
// ����ʾǰ���0 + ����룺
extern void Show88_Fig_LeftAllign(TYPE_LCD_RL mRow, TYPE_LCD_RL mLine,
			 U32 fig, U8 bitTotal
			 );

// 8*8 ������ʾ����:
// 1bit���֣�������ʾ | ���ԣ�
extern void Show88_1Fig_if_inverse(TYPE_LCD_RL mRow, TYPE_LCD_RL mLine,
							U8 fig, BOOL bInverse);
// 1bit���֣�������ʾ��
extern void Show88_1Fig_usual(TYPE_LCD_RL mRow, TYPE_LCD_RL mLine,
							U8 fig );
// 1bit���֣����ԣ�
extern void Show88_1Fig_inverse(TYPE_LCD_RL mRow, TYPE_LCD_RL mLine,
							U8 fig );


/*================= ���к�������-�ַ����� ====================================*/
//EX_lcdSub_ModeTextFig 

extern void SetMenuHeadMode(void);
extern void SetMenuMode(U8 bSelect);
extern void SetTextMode(void);

extern void ShowMenu(TYPE_LCD_RL mRow, TYPE_LCD_RL mLine);
extern void ShowMenuHead(void);

extern TYPE_LCD_XY ShowCstCharRL(TYPE_LCD_RL mRow, TYPE_LCD_RL mLine, 
							const TCstChar_st *pCstChar);

// ��ʾ " " �ڵ��ַ���  // ShowCodeCharRL(0, 0, " ", FALSE);
extern void ShowCodeCharRL(TYPE_LCD_RL mRow, TYPE_LCD_RL mLine, 
						const U8 *pCodeChar, BOOL bInverse);
extern void ShowXYCodeCharRL(TYPE_LCD_RL mRow, 
						U8 mPreCnNum, U8 mPreEnNum, 
						const U8 *pCodeChar, BOOL bInverse);
extern void Show88CodeCharRL(TYPE_LCD_RL mRow, TYPE_LCD_RL mLine, 
						const U8 *pCodeChar, BOOL bInverse);


extern void ClrWindow_Page(void);
extern void ClrWindow_Menu(void);

// ����� mRowFrom ~ (mRowEnd-1) // ���1�У�(1,2)
extern void ClrLcdRlRow(TYPE_LCD_RL mRowFrom, TYPE_LCD_RL mRowEnd);



/*================= ���к�������-�ַ����� ����bufһ����ʾ ====================================*/
// EX_lcdSub_ModeTextFig

// ��ʾһ�����ַ�buf
extern void IniTextBuf(emShowUseLib_PIX  mUseLib);
extern BOOL bTextBufEmpty(void);
extern U32 AddToTextBuf(U8 *pChar);
// AddCodeStrToTextBuf("*__*");
extern U32 AddCodeStrToTextBuf(U8 *pChar);
// swTotal += AddCstStrToTextBuf(&cstChar_Total);
extern U32 AddCstStrToTextBuf(const TCstChar_st *pCstChar);

// ��ʾ AddToTextBuf() �� string.
// OUT : �� ���ص�ַ
// (mRow, mLine)
extern TYPE_LCD_XY ShowTextBuf(TYPE_LCD_RL mRow, TYPE_LCD_RL mLine);
extern TYPE_LCD_XY ShowTxtBufPix(TYPE_LCD_XY mPixRow, TYPE_LCD_XY mPixLine);


/******************************************************************************
// END :
******************************************************************************/
#endif // __lcdSub_ModeTextFig_H__

