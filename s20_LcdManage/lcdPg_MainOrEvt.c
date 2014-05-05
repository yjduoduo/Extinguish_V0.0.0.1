#define __lcdPg_MainOrEvt_C__
/******************************************************************************
* @file    lcdPg_MainOrEvt.c
* @author  yx
* @version V1.0
* @date    2013-09-10
* @brief    MCycle页面的切换。切换的顺序在 "lcdTsk_PgNum.c" cstPgMCycDef[]
* @in	MCyclePage + keyReturn.	    
* @ use 	sequ 专指 cstPgMCycDef[]的序号。
* 
******************************************************************************/
#include  "lcdPg_MainOrEvt.h"

#include  "lcdTsk_PgNum.h"

#include  "evt_Buf_incOut.h"
//#include "incFile.h"	

#include  "lcdPg_MainAndEvtChange.h"

/*================= 常数 ============================================*/

/*================= 结构定义 ========================================*/

/*================= 私有结构变量声明 ================================*/

/*================= 公有函数声明 ====================================*/

/*================= 私有函数声明 ====================================*/

/*=================  ================================================*/



/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
// U_SIGN_bHaveTested	2013.10.15 by yx: 
******************************************************************************/

//  查找 next MCycle Page:
BOOL JdgNextMCyclePage(PAGEWORD *pRtnPgNum)
{
PAGEWORD pageIndex;

	*pRtnPgNum = GetPgNum_Main();
	if(!bPageIsMCycle())
	{
		return FALSE;
	}
	pgEvt_jdgHaveEvent();
	GetPageNum(&pageIndex);
	
	if(pageIndex == GetPgNum_Main())
	{
		// page Main. next MCycle:
		*pRtnPgNum = jdgPageMain_NextMCycle();
		return TRUE;
	}
	else if(bPageIsEvent())
	{
		*pRtnPgNum = jdgPageEvent_NextMCycle();
		return TRUE;
	}
	else
	{
		*pRtnPgNum = jdgPageMOther_NextMCycle();
		return TRUE;
	}
	
}

/******************************************************************************
* FUNC: // main or 事件 page;
*   IN:
*  OUT: 当前优先级最高的事件页面。if all total==0, return MAIN.
******************************************************************************/

PAGEWORD JdgMainOrEvtHighPriorityPage(void)
{
PAGEWORD pageIndex;
	
	pgEvt_jdgHaveEvent();
	if(bAllPgCycEvt_NoEvent())
	{
		return GetPgNum_Main();
	}
	else
	{
		if(jdgNextEvtCycSequ_defaultPageMain(
							0, &pageIndex))
		{
			return pageIndex;
		}
		else
		{
			return GetPgNum_Main();
		}
	}
}

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
// U_SIGN_bHaveTested	2013.10.15 by yx: 
******************************************************************************/

// page event. next MCycle:
PAGEWORD jdgPageEvent_NextMCycle(void)
{
PAGEWORD pageIndex;
U8 mSequ;
	if(bAllPgCycEvt_NoEvent()) // master pgEvt_jdgHaveEvent();
	{
		return GetPgNum_Main();
	}
	else
	{
		GetPageNum(&pageIndex);
		
		if(!GetPgCycSequ_FromPage(pageIndex, &mSequ))
		{
			return GetPgNum_Main();
		}
		
		// 找到
		mSequ++;
		if(mSequ < U_PgMCycDef_Event_MAX) //U_PgMCycDef_All_MAX) // 仍是事件
		{
			if(jdgNextEvtCycSequ_defaultPageMain(
							mSequ, &pageIndex))
			{
				return pageIndex; //优先级更低的事件
			}
		}
		// 无优先级更低的事件 +　有事件可以显示：
		
#if (U_PgMCycDef_Event_MAX == U_PgMCycDef_All_MAX)
		// 查找优先级更低的事件页面。
		if(jdgNextEvtCycSequ_defaultPageMain(
							0, &pageIndex))
		{
			return pageIndex;
		}
		else
		{
			return GetPgNum_Main();
		}
#else // if (U_PgMCycDef_Event_MAX != U_PgMCycDef_All_MAX)
		return GetMCycPage_AfterEvtFirst();
#endif // (U_PgMCycDef_Event_MAX == U_PgMCycDef_All_MAX)
		
	
	}
	
}

/******************************************************************************
* FUNC: //
// U_SIGN_bHaveTested	2013.10.15 by yx: 
******************************************************************************/

// page Main和event以外的. next MCycle:
PAGEWORD jdgPageMOther_NextMCycle(void)
{

	#if (U_PgMCycDef_Event_MAX == U_PgMCycDef_All_MAX)
PAGEWORD pageIndex;
	
		if(jdgNextEvtCycSequ_defaultPageMain(0, &pageIndex))
		{
			return pageIndex;
		}
		else
		{
			return GetPgNum_Main();
		}
	#else // if (U_PgMCycDef_Event_MAX != U_PgMCycDef_All_MAX)
PAGEWORD pageIndex;
U8 mSequ;
		GetPageNum(&pageIndex);
		if(!GetPgCycSequ_FromPage(pageIndex, &mSequ))
		{
			return GetPgNum_Main();
		}
		
		// 找到
		mSequ++;
		if(mSequ < U_PgMCycDef_All_MAX)
		{
			// get 相应MCycle窗口的 pageNum:
			// IN: mSequ < U_PgMCycDef_All_MAX
			return GetMCyclePage_FromDefSequ(mSequ);
		}
		else
		{
			if(bAllPgCycEvt_NoEvent()) // master pgEvt_jdgHaveEvent();
			{
				return GetPgNum_Main();
			}
			else
			{
				// 查找优先级更低的事件页面。
				if(jdgNextEvtCycSequ_defaultPageMain(0, 
												&pageIndex))
				{
					return pageIndex;
				}
				else
				{
					return GetPgNum_Main();
				}
			}
		}
		
		
	#endif // (U_PgMCycDef_Event_MAX == U_PgMCycDef_All_MAX)
}

/******************************************************************************
* FUNC: //
// U_SIGN_bHaveTested	2013.10.15 by yx: 
******************************************************************************/

// page Main. next MCycle:
PAGEWORD jdgPageMain_NextMCycle(void)
{
PAGEWORD pageIndex;

	if(!bAllPgCycEvt_NoEvent()) // master pgEvt_jdgHaveEvent();
	{
		if(jdgNextEvtCycSequ_defaultPageMain(0, &pageIndex))
		{
			return pageIndex;
		}
	}
	
	// no event | find event failed:
	#if (U_PgMCycDef_Event_MAX == U_PgMCycDef_All_MAX)
		return GetPgNum_Main();
	#else
		return GetMCycPage_AfterEvtFirst();
	#endif 
	
}


		


/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

// 查找优先级更低的事件页面。
// Pre:  pgEvt_jdgHaveEvent();
// IN: mFromSequ = 开始查找的sequ;
//	  mFromSequ < U_PgMCycDef_Event_MAX， 否则 Default = 0.
// OUT: FALSE = 无优先级更低的事件
BOOL jdgNextEvtCycSequ_defaultPageMain(
					U8 mFromSequ, PAGEWORD *pRtnPgNum)
{
U8 mSequ;
	
	*pRtnPgNum = GetPgNum_Main(); // 默认，表示无事件时的pageNum.
	
	if(mFromSequ >= U_PgMCycDef_Event_MAX)
	{
		mFromSequ = 0;
	}
	
	for(mSequ=mFromSequ; mSequ<U_PgMCycDef_Event_MAX; mSequ++)
	{
		if(bCycEvtSequ_HaveEvent(mSequ))
		{
			*pRtnPgNum = GetMCycEvtPage_FromDefSequ(mSequ);
			return TRUE;
		}
	}
	
	return FALSE;
}



/******************************************************************************
* FUNC: // END
*   IN:
*  OUT: 
******************************************************************************/
