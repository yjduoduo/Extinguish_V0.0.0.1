#ifndef __lcdSub_SwDev_H__
#define __lcdSub_SwDev_H__
/******************************************************************************
* @file    lcdSub_SwDev.h
* @author  yx
* @version V1.1
* @date    2013-09-06
* @brief   ��ʾstDev.
* 
* V1.1��2013-09-06
		�ַ���in textBufһ����ʾ��
* V1.0��2012-01-05
*
#include  "lcdSub_SwDev.h"
******************************************************************************/

#include  "prjCompileCon.h"

#include  "strDevice.h"
#include  "lcd_Para.h"

/*================= extern ============================================*/
#ifdef  __lcdSub_SwDev_C__
#define EX_lcdSub_SwDev
#else
#define EX_lcdSub_SwDev extern 
#endif

/*================= ���� ============================================*/
//#define 
/*================= �ṹ�嶨�� ======================================*/

/*================= ���нṹ�������� ================================*/

/*================= ˽�к������� ====================================*/
#ifdef __lcdSub_SwDev_C__

// OUT: pRtnFigStr-> ����תbcd string.
void sw_dev_Fig(U32 fig, U8 bitTotal, U8 **pRtnFigStr);

#endif //__lcdSub_SwDev_C__
/*================= ˽�к������� ====================================*/
#ifdef __lcdSub_SwDev_C__
// OUT: TextBuf[], �ַ�����

U8 sw_DevPnModu_String(TDev_un *pDev);
U8 sw_DevPanel_String(TDev_un *pDev);
U8 sw_DevMachine_String(TDev_un *pDev);
U8 sw_DevMachinMe_String(void);

// ��ʾ��·�ֳ����� �豸����
// OUT: TextBuf[], �ַ���
U8 sw_DeteType_String(U8 mType);

// �ַ���ʽ ��ʾ ��·�ֳ�����:
//�ַ���= 2+4 +2+6 +3+4 +1+4 = 26.
U8 sw_Dete_String(TDev_un *pDev);

// ������ʽ ��ʾ ��·�ֳ�����:
//�ַ���= 2+1 +2+1 +3 +1+1 = 11;
U8 sw_Dete_Char(TDev_un *pDev);

// ��ʾ ��·�ֳ�����, �޻����ţ�����" ":
// OUT: TextBuf[], �ַ���
//�ַ���= bChar0Cn1=0: 2+1 + 3+1 +1   + 1 = 9;
//�ַ���= bChar0Cn1=1: 2+4 + 3+4 +1+4 + 1 = 19;
U8 sw_Dete_noMachine(TDev_un *pDev, BOOL bChar0Cn1);

#endif //__lcdSub_SwDev_C__
/*================= ���к������� ====================================*/
// EX_lcdSub_SwDev

// �ַ���ʽ ��ʾ ��·�ֳ����� �豸����:
extern TYPE_LCD_XY Show_Dete_Type_String(TYPE_LCD_RL mRow, 
									TYPE_LCD_RL mLine, 
									U8 type);

extern TYPE_LCD_XY Show_Dev_String(TYPE_LCD_RL mRow, 
									TYPE_LCD_RL mLine, 
									TDev_un *pDev);

// �ַ���ʽ ��ʾ ��·�ֳ�����:
extern TYPE_LCD_XY Show_Dete_String(TYPE_LCD_RL mRow, 
									TYPE_LCD_RL mLine, 
									TDev_un *pDev);

//OUT: ��ʾ�ַ�����
// ������ʽ ��ʾ ��·�ֳ�����:
extern TYPE_LCD_XY Show_Dete_Char(TYPE_LCD_RL mRow, 
									TYPE_LCD_RL mLine, 
									TDev_un *pDev);



/******************************************************************************
// END :
******************************************************************************/
#endif // __lcdSub_SwDev_H__

