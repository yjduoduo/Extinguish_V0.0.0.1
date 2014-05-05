#ifndef __lcdCst_Page_H__
#define __lcdCst_Page_H__
/******************************************************************************
* @file    lcdCst_Page.h
* @author  yx
* @version V1.0
* @date    2012-01-05
* @brief   ��ҳ��� _Back, _First, _Usua ���� const.
* 
#include  "lcdCst_Page.h"
******************************************************************************/

#include  "prjCompileCon.h"

/*================= extern ============================================*/
#ifdef  __lcdCst_Page_C__
#define EX_lcdCst_Page
#else
#define EX_lcdCst_Page extern 
#endif

/*================= ���� ============================================*/


/*================= �ṹ�嶨�� ======================================*/

/*================= ���нṹ�������� ================================*/

// extern const TPage stPage[MAX_PAGE]; 

/*================= ���к������� ====================================*/

/*================= ���к������� ====================================*/
// EX_lcdCst_Page

// ��� stPage[]�Ķ����Ƿ�����
// * Master: "lcdTsk_PgNum"  "lcdShowTask"
extern PAGEWORD GetCstPageDef_PractMax(void);
extern BOOL bPageNumFewThanPractMax(PAGEWORD mPage);
extern BOOL LcdCstPage_CheckCst(void);


// * Master: lcdPg_aSchedu.c
extern void LcdCstPage_Back(PAGEWORD mPageNum);
extern void LcdCstPage_First(PAGEWORD mPageNum);
extern void LcdCstPage_Usual(PAGEWORD mPageNum);


// ���ص� back PageNum:
extern PAGEWORD LcdCstPage_GetBackPgNum(PAGEWORD mPageNum);


/******************************************************************************
// END :
******************************************************************************/
#endif // __lcdCst_Page_H__

