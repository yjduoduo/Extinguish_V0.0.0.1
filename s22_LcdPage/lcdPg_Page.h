#ifndef __lcdPg_Page_H__
#define __lcdPg_Page_H__
/****************************************************************************** 
* @file    lcdPg_Page.h
* @author  yx
* @version V1.0
* @date    2012-01-05
* @brief   
* 
#include  "lcdPg_Page.h"
******************************************************************************/

#include  "prjCompileCon.h"

#include  "hwEx11_lcd_DefPara.h"
#include "lcdPg_KeyCall.h"
/*================= extern ============================================*/
#ifdef  __lcdPg_Page_C__
#define EX_lcdPg_Page
#else
#define EX_lcdPg_Page extern 
#endif

/*================= ���� ============================================*/
//#define 
/*================= �ṹ�嶨�� ======================================*/

/*================= ���нṹ�������� ================================*/

/*================= ˽�к������� ====================================*/
#ifdef  __lcdPg_Page_C__

static PAGEWORD vThisPageKey;

#endif
/*================= ˽�к������� P060 ��·����� ====================================*/
#ifdef  __lcdPg_Page_C__

#define U_DevScan_AdrMax    64
#define U_DevScan_AdrHalf   32

// һ����ַ��ռ�� x pix :
#define U_DevScan_Pix_X_1Point   5

//����0�����㻭��������ļ�ͷ
#define U_DevScan_Pix_X_Start    13 //the distance from the leftest line

// ���ߵ� Y λ�á� ��Ҫ�������� �ָ���ַ����ʾ���ߡ�
#define U_DevScan_Pix_Y0_Start  ((U_LCD_ROW_PIX_MAX/2)-1)
#define U_DevScan_Pix_Y1_Start  ((U_LCD_ROW_PIX_MAX )-5)
#define U_DevScan_Pix_Y_End  (2)

#define U_DevScan_Pix_X_Start_p061    13+8




// һ����ַ��ռ�� y pix:��Ϊ��ʾ�����ߵ����ֵ
//#define U_DevScan_Pix_Y_1Point   ((U_LCD_ROW_PIX_MAX/4))
#define U_DevScan_Pix_Y_1Point   (24)
// �� ��ʾ���꣺
void dw_devScan_coordinate(void);
// �� ����:
void dw_devScan_current_all(U8 *pCurrent);

// ��ʾ����ֵ-1����ַ��
void dw_devScan_current_one(U32 mAdr, U8 mCurrent);

// ��ַ��λ����ʾ������ַ��λ�ߣ�
void dw_devScan_adrPrompt(void);
    // ����ַ��λ�ߣ��ж��� 8�ı������� 4�ı�����
    void dw_devScan_adrPrpt_one(U32 mAdr);
// ��������X�ĳ��ȣ�
TYPE_LCD_XY cacu_devScan_coordinateX(void);
// �������ַ��x���꣺33=(4+5)+(33*5)=185.
TYPE_LCD_XY cacu_devScan_deteX(U32 mAdr);
TYPE_LCD_XY cacu_devScan_deteY(U32 mAdr);
// �������᣺
void dw_devScan_axis(void);

#endif
/*================= ���к������� ====================================*/
//EX_lcdPg_Page 

// �������ʱ�Ĵ���
extern void KeyCheck_ShowInLcd(U8 mKey);


/******************************************************************************
// END :
******************************************************************************/
#endif // __lcdPg_Page_H__

