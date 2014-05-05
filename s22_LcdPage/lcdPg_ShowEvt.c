
#define __lcdPg_ShowEvt_C__
/******************************************************************************
* @file    lcdPg_ShowEvt.c
* @author  yx
* @version V1.0
* @date    2013-01-04
* @brief   几个事件页面
* 
******************************************************************************/
#include  "lcdPg_ShowEvt.h"

//#include "..\\s00Prj\\incFile.h"	

//-----------------   --------------------------------// 
#include  "tsk_lcd_incIn.h"

#include  "tmrTick.h"
#include  "phIoKeyScan.h"

//----- Me:
#include  "lcdPg_MainAndEvtChange.h"
#include  "lcdSub_SwOneMiniEvt.h"
#include  "LcdLib_incOut.h"

/*================= 常数 ============================================*/

/*================= 结构定义 ========================================*/

/*================= 私有结构变量声明 ================================*/

/*================= 私有结构变量声明 ================================*/
// 每类事件 每屏 显示的条数MAX: 最少1条
#if U_SYS_Test_EvtBuf == 1

	const U8 cstWinSwEventTotal[U_EvtCls_MAX] =  // < U_OneScr_DevBuf_MAX
	   {  	U_OneScr_DevBuf_MAX, U_OneScr_DevBuf_MAX, U_OneScr_DevBuf_MAX, 
			U_OneScr_DevBuf_MAX, U_OneScr_DevBuf_MAX, U_OneScr_DevBuf_MAX
		};

#else  //U_SYS_Test_EvtBuf
	//!!!注意要小于 U_OneScr_DevBuf_MAX。
	const U8 cstWinSwEventTotal[U_EvtCls_MAX] =  // < U_OneScr_DevBuf_MAX
	// U_EvtCls_Alarm, U_EvtCls_Fault, U_EvtCls_Link, 
	// U_EvtCls_Extg, U_EvtCls_Spvs, U_EvtCls_Dsab
	//   {  2,               2,        2,           2,           2,     2       }; 
   {  1,    1,  1,    1,   1,  1   }; 

	const U8 cstWinSwMiniEventTotal[U_EvtCls_MAX] =
	{
		U_SHOW_MINI_EVENT_ITEM_MAX, U_SHOW_MINI_EVENT_ITEM_MAX, 
		U_SHOW_MINI_EVENT_ITEM_MAX, U_SHOW_MINI_EVENT_ITEM_MAX,
		U_SHOW_MINI_EVENT_ITEM_MAX, U_SHOW_MINI_EVENT_ITEM_MAX
	};

#endif //U_SYS_Test_EvtBuf

/*================= 公有函数声明 ====================================*/

/*================= 私有函数声明 ====================================*/

/*=================  ================================================*/




/******************************************************************************
* FUNC: //
*   IN: 
*  OUT: 
******************************************************************************/

void LcdPageEvt_PageBack(void)
{
	Win_EvtBufClr();
	LcdPageEvt_RefreshTmrStop();
	LcdPageEvt_AutoTurn_TmrStop();
}

void LcdPageEvt_PageUsual(void)
{
	LcdPageEvt_Key();
}

void LcdPageEvt_PageUp(U8 mEvtCls)
{
	Win_PageTurnPre(mEvtCls);
	LcdPageEvt_EvtCls_Refresh(mEvtCls);
}

void LcdPageEvt_PageDown(U8 mEvtCls)
{
	Win_PageTurnNext(mEvtCls);
	LcdPageEvt_EvtCls_Refresh(mEvtCls);
}



/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

void LcdPageEvt_Key(void)
{
U8 mKey;
U8 mScreen;
U8 mEvtCls;
	
	if(!bPageIsEvent())
	{
		return;
	}
	if(!bGetPageKey(&mKey))
	{
		return;
	}
	
	if(mKey < 10)
	{
		LcdPageEvt_Key_Fig(mKey);
		return;
	}
	switch(mKey)
	{
		case U_KEY_Up:
			mScreen = 0;
			if(GetEvtClsFromPageNum(mScreen, &mEvtCls))
			{
				LcdPageEvt_PageUp(mEvtCls);
			}
			break;
			
		case U_KEY_Down:
			mScreen = 0;
			if(GetEvtClsFromPageNum(mScreen, &mEvtCls))
			{
				LcdPageEvt_PageDown(mEvtCls);
			}
			break;
			
			
		case U_KEY_Left:
			break;
			
		case U_KEY_Right:
			break;
			
			
		default:
			break;
	}
}

/******************************************************************************
* FUNC: //
*   IN: 
*  OUT: 
******************************************************************************/

void LcdPageEvt_MiniBack(void)
{
	ClrPgMiniEvent_Class();
	
	Win_EvtBufClr();
	LcdPageEvt_RefreshTmrStop();
}

void LcdPageEvt_MiniUsual(void)
{
U8 mEvtCls = GetPgMiniEvent_Class();

	if(bEvtBuf_Empty(mEvtCls))
	{
		SetChangeFuncKey(U_KEY_Esc);
		return;
	}
	
	
	if(bWin_EvtBuf_Change(mEvtCls))
	{
		LcdPageEvt_EvtCls_Refresh(mEvtCls);
		Win_EvtBuf_Clr_ChangeSign();
	}
	
	if(bEvtBuf_TotalChange_andClr(mEvtCls))
	{
		ShowEvtCls_Total_String(mEvtCls);
	}
	
	LcdPageEvt_Mini_Key(mEvtCls);
}



BOOL LcdPageEvt_MiniFirst(void)
{
U8 mEvtCls = GetPgMiniEvent_Class();

	if(mEvtCls >= U_EvtCls_MAX)
	{
		return FALSE;
	}
	LcdSw_ClrFullWindow(U_COLOR_BackGroundDefault);
	
	EvtBuf_ClrChange();
	Win_EvtBufClr();
	
	SetEvtWin_OneScrItemMax((U8*)(&cstWinSwMiniEventTotal[0]));
	
	if(LcdPageEvt_EvtCls_Ini(mEvtCls, 0))
	{
		LcdPageEvt_EvtCls_Refresh(mEvtCls);
	}
	
	Win_EvtBuf_Clr_ChangeSign();
	LcdPageEvt_RefreshTmrStart();
	return TRUE;
}


/******************************************************************************
* FUNC: //
*   IN: 已设置 mPage.
*  OUT: 
	// 参考 LcdPageEvt_Key(); 
******************************************************************************/
void LcdPageEvt_Mini_Key(U8 mEvtCls)
{
U8 mKey;

	if(!bGetPageKey(&mKey))
	{
		return;
	}
	
	if(mKey < 10)
	{
		LcdPageEvt_Key_Fig(mKey);
		return;
	}
	
	switch(mKey)
	{
		case U_KEY_Up:
			LcdPageEvt_PageUp(mEvtCls);
			break;
			
		case U_KEY_Down:
			LcdPageEvt_PageDown(mEvtCls);
			break;
			
		case 9:
			LcdPageEvt_MiniBack();
			PageEntry(GetPgNum_EvtTotal());
			break;
			
		default:
			break;
	}
}

/******************************************************************************
* FUNC: //
*   IN: 已设置 mPage.
*  OUT: 
******************************************************************************/
// set evtWin[] cls;  首次事件显示。
BOOL LcdPageEvt_PageFirst(void)
{
U8 mScreen;
U8 mEvtCls;

	if(!bPageIsEvent())
	{
		return FALSE;
	}
	LcdSw_ClrFullWindow(U_COLOR_BackGroundDefault);
	
	EvtBuf_ClrChange();
	Win_EvtBufClr();
	
	for(mScreen=0; mScreen<U_OneScr_Cls_MAX; mScreen++)
	{
		if(GetEvtClsFromPageNum(mScreen, &mEvtCls))
		{
			SetEvtWin_OneScrItemMax((U8*)(&cstWinSwEventTotal[0]));
			if(LcdPageEvt_EvtCls_Ini(mEvtCls, mScreen))
			{
				LcdPageEvt_EvtCls_Refresh(mEvtCls);
			}
		}
	}
	
	Win_EvtBuf_Clr_ChangeSign();
	
	LcdPageEvt_RefreshTmrStart();
	
	if(!bLcdPageEvt_ForbidAutoTurn_Ing())
	{
		LcdPageEvt_AutoTurn_TmrStart();
	}
	return TRUE;
	
}

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

BOOL LcdPageEvt_EvtCls_Ini(U8 mEvtCls, U8 mScreen)
{
EVTWORD mEvtTotal;

	if((mEvtCls >= U_EvtCls_MAX) || (mScreen >= U_OneScr_Cls_MAX))
	{
		return FALSE;
	}
	mEvtTotal = GetEvtTotal(mEvtCls);
	if(mEvtTotal == 0)
	{
		return FALSE;
	}
	Win_EvtBufShowIni(mEvtCls, mScreen);
	return TRUE;
}


/******************************************************************************
* FUNC: // 更新显示：
*   IN:
*  OUT: 
* master: LcdPageEvt_Refresh();
******************************************************************************/

BOOL LcdPageEvt_EvtCls_Refresh(U8 mEvtCls)
{
U8 mShowItem;

	
	ClrLcdRlRow(2, U_LCD_ROW_MAX);
		ExecAllToLcdRam();
		ExecLcdShow();
	
	ShowEvtCls_Total_String(mEvtCls);
	bEvtBuf_TotalChange_andClr(mEvtCls); // 为了clr sign.
	
	switch(mEvtCls)
	{
		case U_EvtCls_Alarm:
			mShowItem = LcdPageEvt_Alarm_refresh();
			break;
		case U_EvtCls_Fault:
			mShowItem = LcdPageEvt_Fault_refresh();
			break;
		case U_EvtCls_Link:
			mShowItem = LcdPageEvt_Link_refresh();
			break;
		case U_EvtCls_Extg:
			mShowItem = LcdPageEvt_Extg_refresh();
			break;
		case U_EvtCls_Spvs:
			mShowItem = LcdPageEvt_Spvs_refresh();
			break;
		case U_EvtCls_Dsab:
			mShowItem = LcdPageEvt_Dsab_refresh();
			break;
		default:
			return FALSE;
	}
	setEvtHaveShowItemNum(mEvtCls, mShowItem); // 当前屏 显示的事件条数
	
	//win[] 是否有变化：and clr
	bWin_EvtBuf_Change(mEvtCls); 
	
	ExecAllToLcdRam();
	
	return (mShowItem != 0);
}


/******************************************************************************
* FUNC: // 当前屏 显示的事件条数
*   IN:
*  OUT: 
******************************************************************************/
static U8 vNowShowItemNum[U_EvtCls_MAX];

static void setEvtHaveShowItemNum(U8 mEvtCls, U8 mNum)
{
	if(mEvtCls < U_EvtCls_MAX)
	{
		vNowShowItemNum[mEvtCls] = mNum;
	}
}

U8 GetEvtHaveShowItemNum(U8 mEvtCls) // 当前屏 显示的事件条数
{
	if(mEvtCls < U_EvtCls_MAX)
	{
		return vNowShowItemNum[mEvtCls];
	}
	else
	{
		return 0;
	}
}


/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

static BOOL bPgEvtIsMiniShow(void)
{
PAGEWORD mPage;

	GetPageNum(&mPage);
	return (mPage == GetPgNum_MiniEvent());
}

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 显示条数
******************************************************************************/

U8 LcdPageEvt_Alarm_refresh(void)
{
U8 mWinBuf;
U8 mWinTotal;
U8 mShowItem = 0; // 显示的条数
TEvtBufWho_st stWho;
U8 mEvtCls = U_EvtCls_Alarm;
TEvtAlarm_st *pEvtAlarm;
BOOL bMiniEvt;

	if(!bWin_EvtBuf_Total(mEvtCls, &mWinTotal))
	{
		return 0;
	}
	
	bMiniEvt = bPgEvtIsMiniShow();
	
	for(mWinBuf=0; mWinBuf<mWinTotal; mWinBuf++)
	{
		if(bWinRead_EvtBuf_One(mEvtCls, mWinBuf, &stWho))
		{
			bReadOneAlarmEvent(stWho.locat, &pEvtAlarm);
			{
				if(bMiniEvt)
				{
					Show_OneMiniAlarm(mShowItem, stWho.sequ+1, pEvtAlarm);
				}
				else
				{
					Show_OneAlarm(mShowItem, stWho.sequ+1, pEvtAlarm);
				}
				mShowItem++;
			}
		}
	}
	
	return mShowItem;
}


/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

U8 LcdPageEvt_Spvs_refresh(void)
{
U8 mWinBuf;
U8 mWinTotal;
U8 mShowItem = 0; // 显示的条数
TEvtBufWho_st stWho;
U8 mEvtCls = U_EvtCls_Spvs;
TEvtSpvs_st *pEvtSpvs;
BOOL bMiniEvt;

	if(!bWin_EvtBuf_Total(mEvtCls, &mWinTotal))
	{
		return 0;
	}
	bMiniEvt = bPgEvtIsMiniShow();
	
	for(mWinBuf=0; mWinBuf<mWinTotal; mWinBuf++)
	{
		if(bWinRead_EvtBuf_One(mEvtCls, mWinBuf, &stWho))
		{
			bReadOneSpvsEvent(stWho.locat, &pEvtSpvs);
			{
				if(bMiniEvt)
				{
					Show_OneMiniSpvs(mShowItem, stWho.sequ+1, pEvtSpvs);
				}
				else
				{
					Show_OneSpvs(mShowItem, stWho.sequ+1, pEvtSpvs);
				}
				
				mShowItem++;
			}
		}
	}
	return mShowItem;
}



/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

U8 LcdPageEvt_Link_refresh(void)
{
U8 mWinBuf;
U8 mWinTotal;
U8 mShowItem = 0; // 显示的条数
TEvtBufWho_st stWho;
U8 mEvtCls = U_EvtCls_Link;
TEvtLink_st *pEvtLink;
BOOL bMiniEvt;

	if(!bWin_EvtBuf_Total(mEvtCls, &mWinTotal))
	{
		return 0;
	}
	bMiniEvt = bPgEvtIsMiniShow();
	
	for(mWinBuf=0; mWinBuf<mWinTotal; mWinBuf++)
	{
		if(bWinRead_EvtBuf_One(mEvtCls, mWinBuf, &stWho))
		{
			bReadOneLinkEvent(stWho.locat, &pEvtLink);
			{
				if(bMiniEvt)
				{
					Show_OneMiniLink(mShowItem, stWho.sequ+1, pEvtLink);
				}
				else
				{
					Show_OneLink(mShowItem, stWho.sequ+1, pEvtLink);
				}
				
				mShowItem++;
			}
		}
	}
	return mShowItem;
}

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

U8 LcdPageEvt_Extg_refresh(void)
{
U8 mWinBuf;
U8 mWinTotal;
U8 mShowItem = 0; // 显示的条数
TEvtBufWho_st stWho;
U8 mEvtCls = U_EvtCls_Extg;
TEvtExtg_st *pEvtExtg;
BOOL bMiniEvt;

	if(!bWin_EvtBuf_Total(mEvtCls, &mWinTotal))
	{
		return 0;
	}
	bMiniEvt = bPgEvtIsMiniShow();
	
	for(mWinBuf=0; mWinBuf<mWinTotal; mWinBuf++)
	{
		if(bWinRead_EvtBuf_One(mEvtCls, mWinBuf, &stWho))
		{
			bReadOneExtgEvent(stWho.locat, &pEvtExtg);
			{
				if(bMiniEvt)
				{
					Show_OneMiniExtg(mShowItem, stWho.sequ+1, pEvtExtg);
				}
				else
				{
					Show_OneExtg(mShowItem, stWho.sequ+1, pEvtExtg);
				}
				
				mShowItem++;
			}
		}
	}
	return mShowItem;
}



/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

U8 LcdPageEvt_Fault_refresh(void)
{
U8 mWinBuf;
U8 mWinTotal;
U8 mShowItem = 0; // 显示的条数
TEvtBufWho_st stWho;
U8 mEvtCls = U_EvtCls_Fault;
TEvtFault_st *pEvtFault;
BOOL bMiniEvt;

	if(!bWin_EvtBuf_Total(mEvtCls, &mWinTotal))
	{
		return 0;
	}
	bMiniEvt = bPgEvtIsMiniShow();
	
	for(mWinBuf=0; mWinBuf<mWinTotal; mWinBuf++)
	{
		if(bWinRead_EvtBuf_One(mEvtCls, mWinBuf, &stWho))
		{
			bReadOneFaultEvent(stWho.locat, &pEvtFault);
			{
				if(bMiniEvt)
				{
					Show_OneMiniFault(mShowItem, stWho.sequ+1, pEvtFault);
				}
				else
				{
					Show_OneFault(mShowItem, stWho.sequ+1, pEvtFault);
				}
				
				mShowItem++;
			}
		}
	}
	return mShowItem;
}


/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

U8 LcdPageEvt_Dsab_refresh(void)
{
U8 mWinBuf;
U8 mWinTotal;
U8 mShowItem = 0; // 显示的条数
TEvtBufWho_st stWho;
U8 mEvtCls = U_EvtCls_Dsab;
TEvtDsab_st *pEvtDsab;
BOOL bMiniEvt;

	if(!bWin_EvtBuf_Total(mEvtCls, &mWinTotal))
	{
		return 0;
	}
	bMiniEvt = bPgEvtIsMiniShow();
	
	for(mWinBuf=0; mWinBuf<mWinTotal; mWinBuf++)
	{
		if(bWinRead_EvtBuf_One(mEvtCls, mWinBuf, &stWho))
		{
			bReadOneDsabEvent(stWho.locat, &pEvtDsab);
			{
				if(bMiniEvt)
				{
					Show_OneMiniDsab(mShowItem, stWho.sequ+1, pEvtDsab);
				}
				else
				{
					Show_OneDsab(mShowItem, stWho.sequ+1, pEvtDsab);
				}
				
				mShowItem++;
			}
		}
	}
	return mShowItem;
}





/******************************************************************************
* FUNC: //
*   IN: 
*  OUT: 
******************************************************************************/

void LcdPageEvt_Key_Fig(U8 mFig)
{
U8 mEvtCls = ~0;

	if(mFig >= 10)
	{
		return;
	}
	switch(mFig)
	{
		case 1:
			mEvtCls = U_EvtCls_Extg;
			break;
		case 2:
			mEvtCls = U_EvtCls_Alarm;
			break;
		case 3:
			mEvtCls = U_EvtCls_Link;
			break;
		case 4:
			mEvtCls = U_EvtCls_Fault;
			break;
		case 5:
			mEvtCls = U_EvtCls_Dsab;
			break;
			
		case 9:
			execPageBack();
			PageEntry(GetPgNum_EvtTotal());
			return;
			
		default:
			break;
	}
	
	if(mEvtCls < U_EvtCls_MAX)
	{
		if(GetEvtTotal(mEvtCls) != 0)
		{
			execPageBack();
			SetPgMiniEvent_Class(mEvtCls);
			PageEntry(GetPgNum_MiniEvent());
		}
	}
	
}

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

