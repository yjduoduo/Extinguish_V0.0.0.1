#define __lcdTsk_PgNum_C__
/******************************************************************************
* @file    lcdTsk_PgNum.c
* @author  yx
* @version V1.0
* @date    2013-07-01
* @brief   
* 
******************************************************************************/
#include  "lcdTsk_PgNum.h"


#include  "tsk_lcd_incIn.h"
//#include "incFile.h"	

#include  "lcdCst_PageNum.h" 
#include  "lcdCst_Page.h"
#include  "evt_Para.h"

/*================= ���� ============================================*/

/*================= �ṹ���� ========================================*/
typedef struct{
	
	PAGEWORD vPage;
	
}TMyPage_st;

static TMyPage_st vMyPg;
/*================= ˽�нṹ�������� ================================*/

/*================= ���к������� ====================================*/

/*================= ˽�к������� ====================================*/

/*=================  ================================================*/






/*=================  ================================================*/

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

void IniPageNum(void)
{
	vMyPg.vPage = GetPgNum_Main();
}

BOOL SetPageNum(PAGEWORD mPage)
{
	if(mPage < GetCstPageDef_PractMax())
	{
		vMyPg.vPage = mPage;
		return TRUE;
	}
	return FALSE;
}

BOOL GetPageNum(PAGEWORD *pRtnPage)
{
	if(vMyPg.vPage < GetCstPageDef_PractMax())
	{
		*pRtnPage = vMyPg.vPage;
		return TRUE;
	}
	else
	{
		*pRtnPage = U_PageNum_Default;
		return FALSE;
	}
}



/******************************************************************************
* FUNC: //
******************************************************************************/

//page=��Ч
BOOL bPageNumValid(PAGEWORD mPage)
{
	return (bPageNumFewThanPractMax(mPage));
}





/******************************************************************************
* FUNC: // MCycle����(���� �¼�����) �Ķ���
*   IN: //
*  OUT:	
// Master: lcdPg_MainOrEvt.c;
******************************************************************************/

// MCycle����(���� �¼�����) �Ķ���
// �����ȼ�����:
const TPgMCycDef_st  cstPgMCycDef[U_PgMCycDef_All_MAX] =
{
	{{U_EvtCls_Extg,  U_EvtCls_MAX}, 	U_P006_Extg},
	{{U_EvtCls_Alarm, U_EvtCls_MAX}, 	U_P001_FireAlarm},
	{{U_EvtCls_Link,  U_EvtCls_MAX}, 	U_P005_Link},
	{{U_EvtCls_Fault, U_EvtCls_MAX}, 	U_P004_Fault},
	{{U_EvtCls_Dsab,  U_EvtCls_MAX}, 	U_P003_Disable},
	
	{{U_EvtCls_MAX,   U_EvtCls_MAX}, 	U_P007_Status},
	// {{U_EvtCls_MAX,   U_EvtCls_MAX}, 	U_P011_Help},
};


/******************************************************************************
* FUNC: //
*   IN: //
*  OUT:	
******************************************************************************/

// pageNum -> emEvtClass
BOOL GetEvtClsFromPageNum(U8 mScreen, U8 *pRtnEvtCls)
{
PAGEWORD mPageIndex;
U8 mSequ;
U8 mEvtCls;

	*pRtnEvtCls = U_EvtCls_MAX;
	if(mScreen >= U_OneScr_Cls_MAX)
	{
		return FALSE;
	}
	
	GetPageNum(&mPageIndex);
	
	for(mSequ=0; mSequ<U_PgMCycDef_Event_MAX; mSequ++)
	{
		if(mPageIndex == cstPgMCycDef[mSequ].page)
		{
			mEvtCls = cstPgMCycDef[mSequ].evtCls[mScreen];
			if(mEvtCls < U_EvtCls_MAX)
			{
				*pRtnEvtCls = mEvtCls;
				return TRUE;
			}
		}
	}
	
	return FALSE;
	
}


/******************************************************************************
* FUNC: // 
******************************************************************************/
// �¼�ҳ�����һ��
PAGEWORD GetMCycPage_AfterEvtFirst(void)
{
	#if (U_PgMCycDef_Event_MAX == U_PgMCycDef_All_MAX)
	return cstPgMCycDef[0].page;
	#else // if (U_PgMCycDef_Event_MAX != U_PgMCycDef_All_MAX)
	return cstPgMCycDef[U_PgMCycDef_Event_MAX].page;
	#endif // (U_PgMCycDef_Event_MAX == U_PgMCycDef_All_MAX)
}


// get ��Ӧevt���� �� evtCls:
// IN: mDefSequ < U_PgMCycDef_Event_MAX
BOOL GetEvtCls_FromMCycEvtDefSequ(
				U8 mDefSequ, U8 mScreen, U8 *pRtnEvtCls)
{
U8 mEvtCls;

	*pRtnEvtCls = U_EvtCls_MAX;
	
	if(	 (mDefSequ < U_PgMCycDef_Event_MAX) 
	  && (mScreen < U_OneScr_Cls_MAX)
	  )
	{
		mEvtCls = cstPgMCycDef[mDefSequ].evtCls[mScreen];
		if(mEvtCls < U_EvtCls_MAX)
		{
			*pRtnEvtCls = mEvtCls;
			return TRUE;
		}
		return FALSE;
	}
	else
	{
		return FALSE;
	}
}

// get ��Ӧevt���ڵ� pageNum:
// IN: mDefSequ < U_PgMCycDef_Event_MAX
PAGEWORD GetMCycEvtPage_FromDefSequ(U8 mDefSequ)
{
	if(mDefSequ < U_PgMCycDef_Event_MAX)
	{
		return cstPgMCycDef[mDefSequ].page;
	}
	else
	{
		return U_PageNum_Default;
	}
}

// get ��ӦMCycle���ڵ� pageNum:
// IN: mDefSequ < U_PgMCycDef_All_MAX
PAGEWORD GetMCyclePage_FromDefSequ(U8 mDefSequ)
{
	if(mDefSequ < U_PgMCycDef_All_MAX)
	{
		return cstPgMCycDef[mDefSequ].page;
	}
	else
	{
		return U_PageNum_Default;
	}
}

/******************************************************************************
* FUNC: //
*   IN: //
*  OUT:	
******************************************************************************/
PAGEWORD GetPgNum_Main(void)
{
	return U_P000_MAIN;
}
PAGEWORD GetPgNum_EvtTotal(void)
{
	return U_P007_Status;
}

PAGEWORD GetPgNum_EvtAlarm(void)
{
	return U_P001_FireAlarm;
}
PAGEWORD GetPgNum_EvtExtg(void)
{
	return U_P006_Extg;
}
PAGEWORD GetPgNum_EvtLink(void)
{
	return U_P005_Link;
}

PAGEWORD GetPgNum_Default(void)
{
	return U_PageNum_Default;
}

PAGEWORD GetPgNum_Menu(void)
{
	return U_P008_MENU;
}
PAGEWORD GetPgNum_UserLogin(void)
{
	return U_P009_UserLogin;
}



/******************************************************************************
* NAME: 
* FUNC: //
*   IN: 
*  OUT:	
******************************************************************************/

PAGEWORD GetPgNum_MiniEvent(void)
{
	return U_P014_MiniEvent;
}

static U8 mPgMiniEventClass = ~0;
void SetPgMiniEvent_Class(U8 mCls)
{
	if(mCls < U_EvtCls_MAX)
	{
		mPgMiniEventClass = mCls;
	}
}

void ClrPgMiniEvent_Class(void)
{
	mPgMiniEventClass = ~0;
}

U8 GetPgMiniEvent_Class(void)
{
	return mPgMiniEventClass;
}

/******************************************************************************
* NAME: 
* FUNC: //�ж��Ƿ��¼���ʾ����
*   IN: //
*  OUT:	emPageType
******************************************************************************/
U8 LcdJdg_PageType (void)
{
PAGEWORD pageIndex;
	
	if(!GetPageNum(&pageIndex))
	{
		return U_PageType_INVALID;
	}
								   
	if(pageIndex == U_P000_MAIN) 
	{
		return U_PageType_MAIN;	
	}
	else if((pageIndex >= U_PageNumEvent_MIN) 
		 && (pageIndex < U_PageNumEvent_MAX))
	{
		return U_PageType_EVENT;
	}
	// else if(pageIndex == U_P014_MiniEvent) 
	// {
		// return U_PageType_EVENT;	
	// }
	
	else if(pageIndex == U_P008_MENU) 
	{
		return U_PageType_MENU;	
	}
	else if(pageIndex == U_P009_UserLogin) 
	{
		return U_PageType_PASSWORD;	
	}
	else if((pageIndex == U_P067_TsCKey))
	{
		return U_PageType_KEYENTER;
	}
	
	else if(pageIndex < MAX_PAGE)				
		return U_PageType_USUA;
	else							
		return U_PageType_INVALID;
}


/******************************************************************************
* FUNC: //
******************************************************************************/
BOOL bPageIsEvent(void)
{
	return (LcdJdg_PageType() == U_PageType_EVENT);
}
/******************************************************************************
* FUNC: //
******************************************************************************/

BOOL bPageIsMCycle(void)  //page=�¼�����  �� main.
{
PAGEWORD pageIndex;
U8 mDefNum;

	GetPageNum(&pageIndex);
	if(pageIndex == U_P000_MAIN)
	{
		return TRUE;
	}
	
	for(mDefNum=0; mDefNum<U_PgMCycDef_All_MAX; mDefNum++)
	{
		if(cstPgMCycDef[mDefNum].page == pageIndex)
		{
			return TRUE;
		}
	}
	return FALSE;

// U8 mPageType;
	// GetPageNum(&pageIndex);
	// mPageType = LcdJdg_PageType();
	
	// return (  (mPageType == U_PageType_MAIN)
		   // || (mPageType == U_PageType_EVENT)
		   
		   // || (pageIndex == U_P007_Status)
		   // || (pageIndex == U_P011_Help)
		   // );
}

BOOL bPageIsUserLogin (void)  //page=�û���¼����
{
	return (LcdJdg_PageType() == U_PageType_PASSWORD);
}		
		  	 
BOOL bPageIsMenu (void)  //page=�˵�����
{
	return (LcdJdg_PageType() == U_PageType_MENU);
}	   			
  	 
BOOL bPageIsMain (void)  //page=������
{
	return (LcdJdg_PageType() == U_PageType_MAIN);
}
	
BOOL bPageIsCheckKey(void)  //page=���԰�������
{
PAGEWORD mPageIndex;
	GetPageNum(&mPageIndex);
	return ((mPageIndex == U_P067_TsCKey)
		   ||(mPageIndex == U_P068_TsAllHardware)
		   );
}		 


BOOL bPageIsInquireRegist(void)  //page=��ѯ�Ǽ�
{
PAGEWORD mPageIndex;
	GetPageNum(&mPageIndex);
	return (mPageIndex == U_P058_QrFieldRegist);
}

BOOL bPageIsLoopBrowse(void)  //page=��·���
{
PAGEWORD mPageIndex;
	GetPageNum(&mPageIndex);
	return (mPageIndex == U_P060_TsLoopDevScan);
}


BOOL bPageIsGetDeteAnalog(void)  //page=���ԣ�ģ������
{
PAGEWORD mPageIndex;
	GetPageNum(&mPageIndex);
	return (mPageIndex == U_P061_TsDeteCurve);
}
BOOL bPageIsGetDeteInterData(void)  //page=���ԣ��ڲ�����
{
PAGEWORD mPageIndex;
	GetPageNum(&mPageIndex);
	return (mPageIndex == U_P064_TsDeteData);
}
BOOL bPageIsGetDeteTypeState(void)  //page=���ԣ�����״̬
{
PAGEWORD mPageIndex;
	GetPageNum(&mPageIndex);
	return (mPageIndex == U_P063_TsDeteType);
}
BOOL bPageIsGetDeteCurrent(void)  //page=���ԣ�״̬����+��������
{
PAGEWORD mPageIndex;
	GetPageNum(&mPageIndex);
	return (mPageIndex == U_P062_TsLoopData);
}
BOOL bPageIsGetDeteSensitive(void)  //page=���ԣ�̽����������
{
PAGEWORD mPageIndex;
	GetPageNum(&mPageIndex);
	return FALSE; // (mPageIndex == );
}


  /*
		  
BOOL bPageIsCheckLed()  //page=����LED����
{
	if((GetLcdPageIndex() == U_P032_CheckLcd)||(GetLcdPageIndex() == U_P031_CheckAll))
		return TRUE;
	return FALSE;
}		  
BOOL bPageIsSelfCheck()  //page=ϵͳ�Լ����
{
	if((GetLcdPageIndex() >= U_P031_CheckAll)&&(GetLcdPageIndex() <= U_P036_CheckSD))
		return TRUE;
	return FALSE;
}			  	 
*/

/******************************************************************************
* FUNC: // END
*   IN:
*  OUT: 
******************************************************************************/
