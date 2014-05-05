#ifndef __lcdPg_MainAndEvtChange_H__
#define __lcdPg_MainAndEvtChange_H__
/******************************************************************************
* @file    lcdPg_MainAndEvtChange.h
* @author  yx
* @version V1.0
* @date    2013-10-15
* @brief   事件变化 对页面的影响. 
		 手动和自动翻页控制。
* 
#include  "lcdPg_MainAndEvtChange.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

/*================= extern ============================================*/
#ifdef  __lcdPg_MainAndEvtChange_C__
#define EX_lcdPg_MainAndEvtChange
#else
#define EX_lcdPg_MainAndEvtChange extern 
#endif
/*================= 常数 ============================================*/
//#define 
/*================= 结构体定义 ======================================*/

/*================= 公有结构变量声明 ================================*/

/*================= 私有函数声明 ====================================*/
#ifdef  __lcdPg_MainAndEvtChange_C__

// 判断 事件页面 有新事件：
static BOOL pgEvt_jdgNewEvent(void);

// TRUE = 事件页面 仍有事件。
BOOL jdgNowEvtPage_EvtHave(U8 mSequ);



// 无原型
// static BOOL pgEvt_jdgHaveEvtOneSequ(U8 mSequ);

#endif  //__lcdPg_MainAndEvtChange_C__
/*================= 私有函数声明 ====================================*/
#ifdef  __lcdPg_MainAndEvtChange_C__

void LcdPageEvt_Refresh_SetArrived(void);
BOOL lcdPageEvt_jdgRereshTmr(void);

// 事件页面刷新。 若当前页面的事件total=0, esc.
// refresh:
extern BOOL LcdPageEvt_Refresh(void);

// 判断 事件页面的事件total 是否 =0
extern BOOL LcdPageEvt_jdgTotal0_Esc(void);

// 显示 事件总数
void LcdPageEvt_evtTotalChange(void);


// page main, 当前有事件：
// TRUE = 是 pageMain,  有事件:key esc; 无事件:不必判断其他事件页面了。
BOOL pageMain_JdgHaveEvent(void);

// page event 最高优先级, 有新事件：
// TRUE = 有新事件。  不是最高优先级page:key esc; 是:显示更新，不必判断其他事件页面了。
BOOL bNewEvtIsHighestPriority(PAGEWORD mNowPage);


// * FUNC: // 查找比now优先级更高的新事件的page
// *   IN: // PageMain 已处理 + 有新事件。
// page event 更高优先级, 有新事件：
// TRUE = 新事件是更高优先级的。
BOOL bNewEvtIsHigherThanNow(
						PAGEWORD mNowPage, PAGEWORD *pRtnPgNum);



// 有新事件，判断是否需要显示优先级更高的：
// 调用后，需要master: EvtBuf_ClrChange();
extern BOOL bNewEvtSoToNewPage(PAGEWORD *pRtnPgNum);


#endif  //__lcdPg_MainAndEvtChange_C__

/*================= 公有函数声明 ====================================*/
//EX_lcdPg_MainAndEvtChange 

// 事件定时刷新
extern void LcdPageEvt_RefreshTmrStart(void);
extern void LcdPageEvt_RefreshTmrStop(void);
extern void LcdPageEvt_RefreshReTmr(void); // 更新重定时

// 自动翻页定时
extern void LcdPageEvt_AutoTurn_TmrStart(void);
extern void LcdPageEvt_AutoTurn_TmrStop(void);
extern void LcdPageEvt_HaveUserKey_ForbidAutoTurn(void);
static BOOL lcdPageEvt_jdgAutoTurn(void);
extern BOOL bLcdPageEvt_ForbidAutoTurn_Ing(void);

/*======= 公有函数声明-模块内 "lcdPg_MainOrEvt.c" use =================*/
//EX_lcdPg_MainAndEvtChange 

// 判断 有事件：
extern BOOL pgEvt_jdgHaveEvent(void);

// TRUE = 所以的事件页面都无可显示的事件
// 需要预先 pgEvt_jdgHaveEvent();
extern BOOL bAllPgCycEvt_NoEvent(void);

// TRUE = mSequ事件页面有需要显示的事件
// * 需要预调用 pgEvt_jdgHaveEvent();
extern BOOL bCycEvtSequ_HaveEvent(U8 mSequ);


// 查找mNowPage 在 MCycleDef 的序号：
extern BOOL GetPgCycSequ_FromPage(PAGEWORD mNowPage, U8 *pRtnSequ);



/*================= 公有函数声明 ====================================*/
//EX_lcdPg_MainAndEvtChange 
//


extern void Exec_MainOrEvtWindow(void);

/******************************************************************************
// END :
******************************************************************************/
#endif // __lcdPg_MainAndEvtChange_H__

