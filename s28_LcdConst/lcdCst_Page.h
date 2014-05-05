#ifndef __lcdCst_Page_H__
#define __lcdCst_Page_H__
/******************************************************************************
* @file    lcdCst_Page.h
* @author  yx
* @version V1.0
* @date    2012-01-05
* @brief   各页面的 _Back, _First, _Usua 函数 const.
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

/*================= 常数 ============================================*/


/*================= 结构体定义 ======================================*/

/*================= 公有结构变量声明 ================================*/

// extern const TPage stPage[MAX_PAGE]; 

/*================= 公有函数声明 ====================================*/

/*================= 公有函数声明 ====================================*/
// EX_lcdCst_Page

// 检查 stPage[]的定义是否有误。
// * Master: "lcdTsk_PgNum"  "lcdShowTask"
extern PAGEWORD GetCstPageDef_PractMax(void);
extern BOOL bPageNumFewThanPractMax(PAGEWORD mPage);
extern BOOL LcdCstPage_CheckCst(void);


// * Master: lcdPg_aSchedu.c
extern void LcdCstPage_Back(PAGEWORD mPageNum);
extern void LcdCstPage_First(PAGEWORD mPageNum);
extern void LcdCstPage_Usual(PAGEWORD mPageNum);


// 返回的 back PageNum:
extern PAGEWORD LcdCstPage_GetBackPgNum(PAGEWORD mPageNum);


/******************************************************************************
// END :
******************************************************************************/
#endif // __lcdCst_Page_H__

