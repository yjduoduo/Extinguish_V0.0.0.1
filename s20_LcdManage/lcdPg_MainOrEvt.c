#define __lcdPg_MainOrEvt_C__
/******************************************************************************
* @file    lcdPg_MainOrEvt.c
* @author  yx
* @version V1.0
* @date    2013-09-10
* @brief    MCycleҳ����л����л���˳���� "lcdTsk_PgNum.c" cstPgMCycDef[]
* @in	MCyclePage + keyReturn.	    
* @ use 	sequ רָ cstPgMCycDef[]����š�
* 
******************************************************************************/
#include  "lcdPg_MainOrEvt.h"

#include  "lcdTsk_PgNum.h"

#include  "evt_Buf_incOut.h"
//#include "incFile.h"	

#include  "lcdPg_MainAndEvtChange.h"

/*================= ���� ============================================*/

/*================= �ṹ���� ========================================*/

/*================= ˽�нṹ�������� ================================*/

/*================= ���к������� ====================================*/

/*================= ˽�к������� ====================================*/

/*=================  ================================================*/



/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
// U_SIGN_bHaveTested	2013.10.15 by yx: 
******************************************************************************/

//  ���� next MCycle Page:
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
* FUNC: // main or �¼� page;
*   IN:
*  OUT: ��ǰ���ȼ���ߵ��¼�ҳ�档if all total==0, return MAIN.
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
		
		// �ҵ�
		mSequ++;
		if(mSequ < U_PgMCycDef_Event_MAX) //U_PgMCycDef_All_MAX) // �����¼�
		{
			if(jdgNextEvtCycSequ_defaultPageMain(
							mSequ, &pageIndex))
			{
				return pageIndex; //���ȼ����͵��¼�
			}
		}
		// �����ȼ����͵��¼� +�����¼�������ʾ��
		
#if (U_PgMCycDef_Event_MAX == U_PgMCycDef_All_MAX)
		// �������ȼ����͵��¼�ҳ�档
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

// page Main��event�����. next MCycle:
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
		
		// �ҵ�
		mSequ++;
		if(mSequ < U_PgMCycDef_All_MAX)
		{
			// get ��ӦMCycle���ڵ� pageNum:
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
				// �������ȼ����͵��¼�ҳ�档
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

// �������ȼ����͵��¼�ҳ�档
// Pre:  pgEvt_jdgHaveEvent();
// IN: mFromSequ = ��ʼ���ҵ�sequ;
//	  mFromSequ < U_PgMCycDef_Event_MAX�� ���� Default = 0.
// OUT: FALSE = �����ȼ����͵��¼�
BOOL jdgNextEvtCycSequ_defaultPageMain(
					U8 mFromSequ, PAGEWORD *pRtnPgNum)
{
U8 mSequ;
	
	*pRtnPgNum = GetPgNum_Main(); // Ĭ�ϣ���ʾ���¼�ʱ��pageNum.
	
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
