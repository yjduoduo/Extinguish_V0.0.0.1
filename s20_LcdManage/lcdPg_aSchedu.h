#ifndef __lcdPg_aSchedu_H__
#define __lcdPg_aSchedu_H__
/******************************************************************************
* @file    lcdPg_aSchedu.h
* @author  yx
* @version V1.0
* @date    2012-01-05
* @brief   ҳ�����
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

/*================= ���� ============================================*/
	
/*================= �ṹ�嶨�� ======================================*/

/*================= ���нṹ�������� ================================*/

/*================= ˽�к������� ====================================*/
#ifdef  __lcdPg_aSchedu_C__

void execPageError(void);

// ��ҳ�� �л�:
PAGEWORD pageMCycleReturn(void);

// back() ֱ�� PageMain.back()ִ��һ��;
// ������ҳ�治ִ�� first();
// OUT: pageNum = GetPgNum_Main();
void pageExit_tillPageMain(void);

void pageExitToMain_EntryMCycleWin(void);

#endif  // __lcdPg_aSchedu_C__
/*================= ���к������� ====================================*/
//EX_lcdPg_aSchedu 

// clr screen, newPage first();
extern void PageEntry(PAGEWORD mPage);

extern void PageReturn(void);

//nowPageExit & ��back��ֱ���ж��¼�ҳ��:
extern void PageEsc(void);


extern  void IniPageSchedu(void);

extern  void PageMainOrEventFirst(void);

// ��һҳ������Ѵ�����ϣ�ֱ��ȥ�ж��¼�ҳ��:
extern void PageRtnTo_MainOrEvent(void);

//exit from now & enter menu page
extern void PgExit_andMenuEntry(void);

//exit to P000, no first().
extern void PgExitToMain_NoFirstFuncExc(void);

// ԭexit & ��first
extern void PageExit_andNewPageFirst (PAGEWORD pageNew);


extern void execPageBack(void);
extern void LcdPage_function_Back(PAGEWORD mPageNum);
extern void LcdPage_function_First(PAGEWORD mPageNum);
extern void LcdPage_function_Usual(PAGEWORD mPageNum);

/******************************************************************************
// END :
******************************************************************************/
#endif // __lcdPg_aSchedu_H__

