#define __lcdPg_MainAndEvtChange_C__
/******************************************************************************
* @file    lcdPg_MainAndEvtChange.c
* @author  yx
* @version V1.0
* @date    2013-10-15
* @brief   事件变化 对页面的影响
		 手动和自动翻页控制。
* 
******************************************************************************/
#include  "lcdPg_MainAndEvtChange.h"

#include  "phIoKeyScan.h"
#include  "tmrTick.h"
#include  "sysDef.h"

#include  "lcdPg_Status.h"
#include  "lcdTsk_PgNum.h"
#include  "lcdPg_ShowEvt.h" 
#include  "lcdSub_SwOneEvt.h"
#include  "lcdPg_aSchedu.h"

#include  "evt_Buf_incOut.h"
//#include "incFile.h"	


/*================= 常数 ============================================*/

/*================= 结构定义 ========================================*/

/*================= 私有结构变量声明 ================================*/

// 为了不涉及 pageNum 的定义，
// 事件类型 和 page的对应关系的定义 在 "lcdTsk_PgNum.c"
// const TPgMCycDef_st  cstPgMCycDef[U_PgMCycDef_All_MAX];
// 某页面可能有2 mEvtCls, 所以不用total来计算. 
static BOOL vEvtPgHaveEvent[U_PgMCycDef_Event_MAX];

static BOOL vEvtPgNewEvent[U_PgMCycDef_Event_MAX];
/*================= 公有函数声明 ====================================*/

/*================= 私有函数声明 ====================================*/

/*=================  ================================================*/
		
/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
// 判断 事件页面 有新事件：
static BOOL pgEvt_jdgNewEvent(void)
{
U8 mSequ;
U8 mScreen;
U8 mEvtCls;
BOOL bHaveNewEvent = FALSE;

	for(mSequ=0; mSequ<U_PgMCycDef_Event_MAX; mSequ++)
	{
		vEvtPgNewEvent[mSequ] = FALSE;
		for(mScreen=0; mScreen<U_OneScr_Cls_MAX; mScreen++)
		{
			if(GetEvtCls_FromMCycEvtDefSequ(mSequ, mScreen, &mEvtCls))
			{
				vEvtPgNewEvent[mSequ] |= (bEvtBuf_BufChange(mEvtCls));
			}
		}
		if(vEvtPgNewEvent[mSequ])
		{
			bHaveNewEvent = TRUE;
		}
	}
	return bHaveNewEvent;
}

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

// 判断 有事件：
BOOL pgEvt_jdgHaveEvent(void)
{
U8 mSequ;
U8 mScreen;
U8 mEvtCls;
BOOL bHaveEvent = FALSE;

	for(mSequ=0; mSequ<U_PgMCycDef_Event_MAX; mSequ++)
	{
		vEvtPgHaveEvent[mSequ] = FALSE;
		for(mScreen=0; mScreen<U_OneScr_Cls_MAX; mScreen++)
		{
			if(GetEvtCls_FromMCycEvtDefSequ(mSequ, mScreen, &mEvtCls))
			{
				vEvtPgHaveEvent[mSequ] |= (!bEvtBuf_Empty(mEvtCls));
			}
		}
		if(vEvtPgHaveEvent[mSequ])
		{
			bHaveEvent = TRUE;
		}
	}
	return bHaveEvent;
}


/******************************************************************************
* FUNC: //
// TRUE = mSequ事件页面有需要显示的事件
* 需要预调用 pgEvt_jdgHaveEvent();
******************************************************************************/
BOOL bCycEvtSequ_HaveEvent(U8 mSequ)
{
	if(mSequ < U_PgMCycDef_Event_MAX)
	{
		return vEvtPgHaveEvent[mSequ];
	}
	else
	{
		return FALSE;
	}
}


/******************************************************************************
* FUNC: // TRUE = 所以的事件页面都无可显示的事件
// 需要预先 pgEvt_jdgHaveEvent();
******************************************************************************/
BOOL bAllPgCycEvt_NoEvent(void)
{
U8 mSequ;
	
	for(mSequ=0; mSequ<U_PgMCycDef_Event_MAX; mSequ++)
	{
		if(vEvtPgHaveEvent[mSequ])
		{
			return FALSE;
		}
	}
	
	return TRUE;
}


/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
// 查找mNowPage 在 MCycleDef 的序号：
BOOL GetPgCycSequ_FromPage(PAGEWORD mNowPage, U8 *pRtnSequ)
{
U8 mSequ;
	
	*pRtnSequ = 0; 
	for(mSequ=0; mSequ<U_PgMCycDef_All_MAX; mSequ++)
	{
		if(mNowPage == GetMCyclePage_FromDefSequ(mSequ))
		{
			*pRtnSequ = mSequ;
			return TRUE;
		}
	}
	return FALSE;
}

/******************************************************************************
* FUNC: //
*   IN: 
*  OUT: 
******************************************************************************/
// TRUE = 事件页面 仍有事件。
BOOL jdgNowEvtPage_EvtHave(U8 mSequ)
{
U8 mScreen; // 事件分屏
U8 mEvtCls;

	if(mSequ >= U_PgMCycDef_Event_MAX)
	{
		return FALSE;
	}
	
	for(mScreen=0; mScreen<U_OneScr_Cls_MAX; mScreen++)
	{
		if(GetEvtClsFromPageNum(mScreen, &mEvtCls))
		{
			if(GetEvtTotal(mEvtCls) != 0)
			{
				return TRUE;
			}
		}
	}
	return FALSE;
}

/******************************************************************************
* FUNC: //
******************************************************************************/

/******************************************************************************
* FUNC: // 
	// page main, 当前有事件：
	// TRUE = 是 pageMain,  有事件:key esc; 无事件:不必判断其他事件页面了。
******************************************************************************/
BOOL pageMain_JdgHaveEvent(void)
{
	if(bPageIsMain())
	{
		if(pgEvt_jdgHaveEvent())
		{
			SetChangeFuncKey(U_KEY_Esc);
		}
		return TRUE;
	}
	else
	{
		return FALSE;
	}
	
}

/******************************************************************************
* FUNC: // 显示 事件总数
*   IN:  
*  OUT:  
******************************************************************************/

void LcdPageEvt_evtTotalChange(void)
{
U8 mEvtCls;
U8 mScreen; // 事件分屏

	if(!bPageIsEvent())
	{
		return;
	}
	
	for(mScreen=0; mScreen<U_OneScr_Cls_MAX; mScreen++)
	{
		if(!GetEvtClsFromPageNum(mScreen, &mEvtCls))
		{
			continue;
		}
		if(bEvtBuf_TotalChange_andClr(mEvtCls))
		{
			ShowEvtCls_Total_String(mEvtCls);
			
			// 防止不满页时，总数>显示条数的情况
			if(	GetEvtHaveShowItemNum(mEvtCls) 
			  < GetEvtWin_OneScrItemMax(mEvtCls))
			{
				LcdPageEvt_Refresh_SetArrived();
			}
			if(GetEvtTotal(mEvtCls) < GetEvtHaveShowItemNum(mEvtCls))
			{
				LcdPageEvt_Refresh_SetArrived();
			}
		}
		
	}
	
	
}


/******************************************************************************
* FUNC: // 判断 事件页面的事件total 是否 =0
*   IN:  
*  OUT:  
******************************************************************************/

BOOL LcdPageEvt_jdgTotal0_Esc(void)
{
U8 mSequ;
PAGEWORD pageIndex;

	if(!bPageIsEvent())
	{
		return FALSE;
	}
	
	GetPageNum(&pageIndex);
	if(!GetPgCycSequ_FromPage(pageIndex, &mSequ))
	{
		return FALSE;
	}
	if(!jdgNowEvtPage_EvtHave(mSequ)) // 已无事件
	{
		return TRUE;
	}
	return FALSE;
}

/******************************************************************************
* FUNC: // 
	// page event 最高优先级, 有新事件：
	// TRUE = 有新事件。  不是最高优先级page:key esc; 是:显示更新，不必判断其他事件页面了。
******************************************************************************/


BOOL bNewEvtIsHighestPriority(PAGEWORD mNowPage)
{
U8 mHighestSequ = 0;

	if(	 (vEvtPgNewEvent[mHighestSequ]) 
	  && (vEvtPgHaveEvent[mHighestSequ])
	  )
	{
		if(mNowPage != GetMCycEvtPage_FromDefSequ(mHighestSequ)
		  && (mNowPage != GetPgNum_MiniEvent())
		  )
		{
			SetChangeFuncKey(U_KEY_Esc);
		}
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}



/******************************************************************************
* FUNC: // 查找比now优先级更高的新事件的page
*   IN: // PageMain 已处理 + 有新事件。
	// page event 更高优先级, 有新事件：
	// TRUE = 新事件是更高优先级的。
******************************************************************************/

BOOL bNewEvtIsHigherThanNow(
						PAGEWORD mNowPage, PAGEWORD *pRtnPgNum)
{
U8 mNowSequ;
U8 mSequ;
	
	*pRtnPgNum = mNowPage;
	
	//if(!bPageIsMCycle())
	if(!bPageIsEvent())
	{
		return FALSE;
	}
	if(bLcdPageEvt_ForbidAutoTurn_Ing())
	{
		return FALSE;
	}
	
	if(bPageIsEvent())
	{
		if(!GetPgCycSequ_FromPage(mNowPage, &mNowSequ))
		{
			return FALSE;
		}
	}
	else
	{
		mNowSequ = U_PgMCycDef_Event_MAX;
	}
	
	
	for(mSequ=0; mSequ<mNowSequ; mSequ++)
	{
		if((vEvtPgNewEvent[mSequ])&&(vEvtPgHaveEvent[mSequ]))
		{
			*pRtnPgNum = GetMCycEvtPage_FromDefSequ(mSequ);
			return TRUE;
		}
	}
	
	return FALSE;
}

/******************************************************************************
* FUNC: // 有新事件，判断是否需要显示优先级更高的：
*   IN: sign: buf change.
*  OUT: 
* After: 最后需要: EvtBuf_ClrChange(); 否则影响下一次的判断。
* 
******************************************************************************/

// 事件页面的 变动
// 有新事件，判断是否需要显示优先级更高的：
// 最后需要: EvtBuf_ClrChange();
BOOL bNewEvtSoToNewPage(PAGEWORD *pRtnPgNum)
{
PAGEWORD pageIndex;
PAGEWORD mPageNew;
BOOL bNeedNewPageFirst = FALSE;

	GetPageNum(&pageIndex);
	
	
	// page event 最高优先级, 有新事件：
	// TRUE = 有新事件。  不是最高优先级page:key esc; 是:显示更新，不必判断其他事件页面了。
	if(bNewEvtIsHighestPriority(pageIndex))
	{
		bNeedNewPageFirst = FALSE;
	}
	
	// 查找比now优先级更高的新事件的page
	else if(bNewEvtIsHigherThanNow(pageIndex, &mPageNew))
	{
		*pRtnPgNum = mPageNew;
		bNeedNewPageFirst = TRUE;
	}
	
	EvtBuf_ClrChange();
	return bNeedNewPageFirst;
}


/******************************************************************************
* FUNC: // 事件页面刷新。 若当前页面的事件total=0, esc.
*   IN:
*  OUT: 
* slave: LcdPageEvt_EvtCls_Refresh();
******************************************************************************/
// 判断 事件页面 显示是否有变化要求； 
// refresh:
BOOL LcdPageEvt_Refresh(void)
{
U8 mEvtCls;
U8 mScreen; // 事件分屏

	if(!bPageIsEvent())
	{
		return FALSE;
	}
	
	
	for(mScreen=0; mScreen<U_OneScr_Cls_MAX; mScreen++)
	{
		if(GetEvtClsFromPageNum(mScreen, &mEvtCls))
		{
			if(bWin_EvtBuf_Change(mEvtCls))
			{
				LcdPageEvt_EvtCls_Refresh(mEvtCls);
			}
		}
		
	}
	
	
	return TRUE;
}



/******************************************************************************
* FUNC: // 事件刷新定时
*   IN:
*  OUT: 
******************************************************************************/


void LcdPageEvt_RefreshTmrStart(void)
{
	if(!bPageIsEvent())
	{
		return;
	}
	SetTmrTickTsk_haveTaskId(TASK_PageEvtChkChange, 
							TMR_PageEvtChkChange, 
							U_SysTask_LcdShow);
}

void LcdPageEvt_RefreshTmrStop(void)
{
	KillTickTask(TASK_PageEvtChkChange); 
}

void LcdPageEvt_RefreshReTmr(void) // 更新重定时
{
	ClearTickTaskTmr(TASK_PageEvtChkChange); 
}
static void LcdPageEvt_Refresh_SetArrived(void)
{
	SetTickTaskSign(TASK_PageEvtChkChange); 
}


BOOL lcdPageEvt_jdgRereshTmr(void)
{
	if(!bPageIsEvent())
	{
		return FALSE;
	}
	
	return (GetTickTaskStatus(TASK_PageEvtChkChange));
}


/******************************************************************************
* FUNC: // 自动翻页定时
*   IN:
*  OUT: 
******************************************************************************/

void LcdPageEvt_HaveUserKey_ForbidAutoTurn(void)
{
	if(!bPageIsEvent())
	{
		return;
	}
	SetTmrTickTsk_haveTaskId(
							TASK_PageEvtForbidAutoTurn, 
							 TMR_PageEvtForbidAutoTurn, 
							U_SysTask_LcdShow);
	KillTickTask(TASK_PageEvtAutoTurn); 
}

void LcdPageEvt_AutoTurn_TmrStart(void)
{
	if(!bPageIsEvent())
	{
		return;
	}
	KillTickTask(TASK_PageEvtForbidAutoTurn); 
	SetTmrTickTsk_haveTaskId(
							TASK_PageEvtAutoTurn, 
							 TMR_PageEvtAutoTurn, 
							U_SysTask_LcdShow);
}


void LcdPageEvt_AutoTurn_TmrStop(void)
{
	KillTickTask(TASK_PageEvtForbidAutoTurn); 
	KillTickTask(TASK_PageEvtAutoTurn); 
}


BOOL bLcdPageEvt_ForbidAutoTurn_Ing(void)
{
	return (JudgeTickTaskUsing(TASK_PageEvtForbidAutoTurn));
}

/******************************************************************************
* FUNC: // 
*   IN:
*  OUT: 
******************************************************************************/
BOOL lcdPageEvt_jdgAutoTurn(void)
{
	if(!bPageIsEvent())
	{
		return FALSE;
	}
	
	if(JudgeTickTaskUsing(TASK_PageEvtForbidAutoTurn))
	{
		if(GetTickTaskStatus(TASK_PageEvtForbidAutoTurn))
		{
			LcdPageEvt_AutoTurn_TmrStart();
		}
	}
	else
	{
		if(GetTickTaskStatus(TASK_PageEvtAutoTurn))
		{
			LcdPageEvt_RefreshReTmr(); // 更新重定时
			return TRUE;
		}
	}
	return FALSE;
}



/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
先判断 新事件，可能change page;  
	pageFirst时 清一次buf change, win[]在设置时自然清.
判断翻页
定时判断refresh; 只管 win[]标志。

******************************************************************************/


void Exec_MainOrEvtWindow(void)
{
PAGEWORD mNewPage;

	pgEvt_jdgNewEvent();
	pgEvt_jdgHaveEvent();
	
	// 判断 事件页面的事件total 是否 =0
	if(LcdPageEvt_jdgTotal0_Esc())
	{
		SetChangeFuncKey(U_KEY_Esc);
		return;
	}
	
	// page main, 当前有事件：
	// TRUE = 是 pageMain,  有事件:key esc; 无事件:不必判断其他事件页面了。
	if(pageMain_JdgHaveEvent())
	{
		return;
	}
	
	// 判断新事件，页面非MCycle也涉及
	//  IN:     sign: buf change.
	// OUT: Clr sign: buf change.
	if(bNewEvtSoToNewPage(&mNewPage))
	{
		SetPageNum(mNewPage);
		LcdPageEvt_PageFirst();
		return;
	}
	
	if(!bPageIsMCycle())
	{
		return;
	}
	
	// 事件页面 自动翻页
	if(lcdPageEvt_jdgAutoTurn())
	{
		SetChangeFuncKey(U_KEY_Down);
		SetChangeFuncKey(U_KEY_Right);
		return;
	}
	
	// 事件页面 检查是否需要更新
	// if(lcdPageEvt_jdgRereshTmr())
	{
		LcdPageEvt_Refresh();
		Win_EvtBuf_Clr_ChangeSign();
	}
	
	LcdPageEvt_evtTotalChange();
}


/******************************************************************************
* FUNC: // END
*   IN:
*  OUT: 
******************************************************************************/
