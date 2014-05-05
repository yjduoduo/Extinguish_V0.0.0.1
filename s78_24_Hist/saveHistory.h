#ifndef __saveHistory_H__
#define __saveHistory_H__
/******************************************************************************
* @file    saveHistory.h
* @author  yx
* @version V1.0
* @date    2013-07-23
* @brief   add 一条历史记录；
		// 比较指针和记录是否相符:
		
* 
#include  "saveHistory.h"
******************************************************************************/

#include  "prjCompileCon.h"

#include  "historyClsDef.h"
#include  "strEvtTrans.h"

/*================= extern ============================================*/
#ifdef  __saveHistory_C__
#define EX_saveHistory
#else
#define EX_saveHistory extern 
#endif

/*================= 常数 ============================================*/

/*================= 结构体定义 ======================================*/

/*================= 公有结构变量声明 ================================*/



/*================= 私有函数声明 ====================================*/
#ifdef  __saveHistory_C__

// 比较指针和记录是否相符:
// *  OUT: FlsItemState.bError
void histPoint_1Cls1Part_Init(U8 mHistCls, U8 mHistPart);

#endif

/*================= 公有函数声明-lib内部 ====================================*/
// EX_historyWrBuf

// clr buf;
// 比较指针和记录是否相符:
// * 需要预先执行 InitAll_FlsQueHeadEnd(); 
extern void SaveHist_Init(void);

/*================= 公有函数声明-lib外部 ====================================*/
// EX_historyWrBuf

// 新历史记录：
extern U8 HistNewEvent(TEvtTrans_st *pEvtTrans);

/******************************************************************************
// END :
******************************************************************************/
#endif // __saveHistory_H__

