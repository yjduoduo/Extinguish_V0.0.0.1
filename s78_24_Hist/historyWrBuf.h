#ifndef __historyWrBuf_H__
#define __historyWrBuf_H__
/******************************************************************************
* @file    historyWrBuf.h
* @author  yx
* @version V1.0
* @date    2013-07-08
* @brief   
* 
#include  "historyWrBuf.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

#include  "bufCircle.h"
#include  "strEvtTrans.h"
#include  "strFlsItmStruct.h"

/*================= extern ============================================*/
#ifdef  __historyWrBuf_C__
#define EX_historyWrBuf
#else
#define EX_historyWrBuf extern 
#endif
/*================= 常数 ============================================*/

#define U_HIST_BUF_MAX  0x100
#define U_HIST_BUF_NeedSave_NUM  (U_HIST_BUF_MAX / 2)
/*================= 结构体定义 ======================================*/

/*================= 公有结构变量声明 ================================*/


/*================= 公有函数声明-lib内部 ====================================*/
// EX_historyWrBuf
EX_historyWrBuf void Init_HistWrBuf(void);
EX_historyWrBuf U8 HistNewEvent(TEvtTrans_st *pEvtTrans);

//read, 需要按顺序调用
EX_historyWrBuf BOOL bHistBuf_isEmpty(void);
EX_historyWrBuf BOOL bHistBuf_NumNeedSave(void);

EX_historyWrBuf void HistBuf_StartRead(void);
EX_historyWrBuf BOOL HistBuf_Read(U8 mHistCls, U8 mPart, THisory_un *pRtnHist);

EX_historyWrBuf BOOL bHistBuf_readThisCycFinished(void);

/******************************************************************************
// END :
******************************************************************************/
#endif // __historyWrBuf_H__

