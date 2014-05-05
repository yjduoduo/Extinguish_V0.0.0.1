#define __lcdPg_MainAndEvtChange_C__
/******************************************************************************
* @file    lcdPg_MainAndEvtChange.c
* @author  yx
* @version V1.0
* @date    2013-10-15
* @brief   �¼��仯 ��ҳ���Ӱ��
		 �ֶ����Զ���ҳ���ơ�
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


/*================= ���� ============================================*/

/*================= �ṹ���� ========================================*/

/*================= ˽�нṹ�������� ================================*/

// Ϊ�˲��漰 pageNum �Ķ��壬
// �¼����� �� page�Ķ�Ӧ��ϵ�Ķ��� �� "lcdTsk_PgNum.c"
// const TPgMCycDef_st  cstPgMCycDef[U_PgMCycDef_All_MAX];
// ĳҳ�������2 mEvtCls, ���Բ���total������. 
static BOOL vEvtPgHaveEvent[U_PgMCycDef_Event_MAX];

static BOOL vEvtPgNewEvent[U_PgMCycDef_Event_MAX];
/*================= ���к������� ====================================*/

/*================= ˽�к������� ====================================*/

/*=================  ================================================*/
		
/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
// �ж� �¼�ҳ�� �����¼���
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

// �ж� ���¼���
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
// TRUE = mSequ�¼�ҳ������Ҫ��ʾ���¼�
* ��ҪԤ���� pgEvt_jdgHaveEvent();
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
* FUNC: // TRUE = ���Ե��¼�ҳ�涼�޿���ʾ���¼�
// ��ҪԤ�� pgEvt_jdgHaveEvent();
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
// ����mNowPage �� MCycleDef ����ţ�
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
// TRUE = �¼�ҳ�� �����¼���
BOOL jdgNowEvtPage_EvtHave(U8 mSequ)
{
U8 mScreen; // �¼�����
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
	// page main, ��ǰ���¼���
	// TRUE = �� pageMain,  ���¼�:key esc; ���¼�:�����ж������¼�ҳ���ˡ�
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
* FUNC: // ��ʾ �¼�����
*   IN:  
*  OUT:  
******************************************************************************/

void LcdPageEvt_evtTotalChange(void)
{
U8 mEvtCls;
U8 mScreen; // �¼�����

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
			
			// ��ֹ����ҳʱ������>��ʾ���������
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
* FUNC: // �ж� �¼�ҳ����¼�total �Ƿ� =0
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
	if(!jdgNowEvtPage_EvtHave(mSequ)) // �����¼�
	{
		return TRUE;
	}
	return FALSE;
}

/******************************************************************************
* FUNC: // 
	// page event ������ȼ�, �����¼���
	// TRUE = �����¼���  ����������ȼ�page:key esc; ��:��ʾ���£������ж������¼�ҳ���ˡ�
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
* FUNC: // ���ұ�now���ȼ����ߵ����¼���page
*   IN: // PageMain �Ѵ��� + �����¼���
	// page event �������ȼ�, �����¼���
	// TRUE = ���¼��Ǹ������ȼ��ġ�
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
* FUNC: // �����¼����ж��Ƿ���Ҫ��ʾ���ȼ����ߵģ�
*   IN: sign: buf change.
*  OUT: 
* After: �����Ҫ: EvtBuf_ClrChange(); ����Ӱ����һ�ε��жϡ�
* 
******************************************************************************/

// �¼�ҳ��� �䶯
// �����¼����ж��Ƿ���Ҫ��ʾ���ȼ����ߵģ�
// �����Ҫ: EvtBuf_ClrChange();
BOOL bNewEvtSoToNewPage(PAGEWORD *pRtnPgNum)
{
PAGEWORD pageIndex;
PAGEWORD mPageNew;
BOOL bNeedNewPageFirst = FALSE;

	GetPageNum(&pageIndex);
	
	
	// page event ������ȼ�, �����¼���
	// TRUE = �����¼���  ����������ȼ�page:key esc; ��:��ʾ���£������ж������¼�ҳ���ˡ�
	if(bNewEvtIsHighestPriority(pageIndex))
	{
		bNeedNewPageFirst = FALSE;
	}
	
	// ���ұ�now���ȼ����ߵ����¼���page
	else if(bNewEvtIsHigherThanNow(pageIndex, &mPageNew))
	{
		*pRtnPgNum = mPageNew;
		bNeedNewPageFirst = TRUE;
	}
	
	EvtBuf_ClrChange();
	return bNeedNewPageFirst;
}


/******************************************************************************
* FUNC: // �¼�ҳ��ˢ�¡� ����ǰҳ����¼�total=0, esc.
*   IN:
*  OUT: 
* slave: LcdPageEvt_EvtCls_Refresh();
******************************************************************************/
// �ж� �¼�ҳ�� ��ʾ�Ƿ��б仯Ҫ�� 
// refresh:
BOOL LcdPageEvt_Refresh(void)
{
U8 mEvtCls;
U8 mScreen; // �¼�����

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
* FUNC: // �¼�ˢ�¶�ʱ
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

void LcdPageEvt_RefreshReTmr(void) // �����ض�ʱ
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
* FUNC: // �Զ���ҳ��ʱ
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
			LcdPageEvt_RefreshReTmr(); // �����ض�ʱ
			return TRUE;
		}
	}
	return FALSE;
}



/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
���ж� ���¼�������change page;  
	pageFirstʱ ��һ��buf change, win[]������ʱ��Ȼ��.
�жϷ�ҳ
��ʱ�ж�refresh; ֻ�� win[]��־��

******************************************************************************/


void Exec_MainOrEvtWindow(void)
{
PAGEWORD mNewPage;

	pgEvt_jdgNewEvent();
	pgEvt_jdgHaveEvent();
	
	// �ж� �¼�ҳ����¼�total �Ƿ� =0
	if(LcdPageEvt_jdgTotal0_Esc())
	{
		SetChangeFuncKey(U_KEY_Esc);
		return;
	}
	
	// page main, ��ǰ���¼���
	// TRUE = �� pageMain,  ���¼�:key esc; ���¼�:�����ж������¼�ҳ���ˡ�
	if(pageMain_JdgHaveEvent())
	{
		return;
	}
	
	// �ж����¼���ҳ���MCycleҲ�漰
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
	
	// �¼�ҳ�� �Զ���ҳ
	if(lcdPageEvt_jdgAutoTurn())
	{
		SetChangeFuncKey(U_KEY_Down);
		SetChangeFuncKey(U_KEY_Right);
		return;
	}
	
	// �¼�ҳ�� ����Ƿ���Ҫ����
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
