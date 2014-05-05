#ifndef __lcdPg_aSchedu_H__
#define __lcdPg_aSchedu_H__
/******************************************************************************
* @file    lcdPg_aSchedu.h
* @author  yx
* @version V1.0
* @date    2012-01-05
* @brief   页面调度
* 
#include  "lcdPg_aSchedu.h"
******************************************************************************/

#include  "prjCompileCon.h"
/*================= extern ============================================*/
#ifdef  __lcdPg_aSchedu_C__
#define EX_lcdPg_aSchedu
#else
#define EX_lcdPg_aSchedu extern 
#endif

/*================= 常数 ============================================*/
	
/*================= 结构体定义 ======================================*/

/*================= 公有结构变量声明 ================================*/

/*================= 私有函数声明 ====================================*/
#ifdef  __lcdPg_aSchedu_C__

void execPageError(void);

// 主页面 切换:
PAGEWORD pageMCycleReturn(void);

// back() 直至 PageMain.back()执行一次;
// 但最后的页面不执行 first();
// OUT: pageNum = GetPgNum_Main();
void pageExit_tillPageMain(void);

void pageExitToMain_EntryMCycleWin(void);

#endif  // __lcdPg_aSchedu_C__
/*================= 公有函数声明 ====================================*/
//EX_lcdPg_aSchedu 

// clr screen, newPage first();
extern void PageEntry(PAGEWORD mPage);

extern void PageReturn(void);

//nowPageExit & 逐级back，直至判断事件页面:
extern void PageEsc(void);


extern  void IniPageSchedu(void);

extern  void PageMainOrEventFirst(void);

// 上一页面的事已处理完毕，直接去判断事件页面:
extern void PageRtnTo_MainOrEvent(void);

//exit from now & enter menu page
extern void PgExit_andMenuEntry(void);

//exit to P000, no first().
extern void PgExitToMain_NoFirstFuncExc(void);

// 原exit & 新first
extern void PageExit_andNewPageFirst (PAGEWORD pageNew);


extern void execPageBack(void);
extern void LcdPage_function_Back(PAGEWORD mPageNum);
extern void LcdPage_function_First(PAGEWORD mPageNum);
extern void LcdPage_function_Usual(PAGEWORD mPageNum);

/******************************************************************************
// END :
******************************************************************************/
#endif // __lcdPg_aSchedu_H__

