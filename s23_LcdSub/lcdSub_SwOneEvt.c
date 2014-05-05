
#define __lcdSub_SwOneEvt_C__
/******************************************************************************
* @file    lcdSub_SwOneEvt.c
* @author  yx
* @version V1.0
* @date    2013-09-13
* @brief   
* 
	显示一条事件
******************************************************************************/
#include  "lcdSub_SwOneEvt.h"

//#include "..\\s00Prj\\incFile.h"	

#include  "lcdCst_PgStrEvtThing.h"
#include  "lcdCst_PgStrDeteType.h"

//-----------------   --------------------------------// 
#include  "tsk_lcd_incIn.h"
#include  "codeFig.h"



/*================= 常数 ============================================*/
#define U_EVT_SHOW_DEV_LINE_START  5 // 序号后面，开始显示dev

/*================= 结构定义 ========================================*/

/*================= 私有结构变量声明 ================================*/

/*================= 公有函数声明 ====================================*/
// EX_lcdSub_ModeTextFig

extern TYPE_LCD_XY getPixYR_formRow(TYPE_LCD_RL mRow);
/*================= 私有函数声明 ====================================*/

/*=================  ================================================*/
		
/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

void Show_OneSpvs(U8 winItem, EVTWORD sequ,
									TEvtSpvs_st *m_pSpvs)
{
	
U8 swTotal;
	
	swTotal = swTotal;
	
	showOneEvt_Dev(winItem, &m_pSpvs->stPos.unDev);
	showOneEvt_Clock(winItem, &m_pSpvs->evtClock);
	
	showOneEvt_devType(winItem, m_pSpvs->stPos.devType);
	
	
	showOneEvt_Note(winItem, &m_pSpvs->stPos.unDev);
	
	
	showOneEvt_sequNum(winItem, sequ, U_EvtCls_Spvs);
}


/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

void Show_OneAlarm(U8 winItem, EVTWORD sequ,
									TEvtAlarm_st *m_pAlarm)
{
U8 swTotal;
	
	swTotal = swTotal;
	
	
	showOneEvt_Dev(winItem, &m_pAlarm->stPos.unDev);
	showOneEvt_Clock(winItem, &m_pAlarm->evtClock);
	
	showOneEvt_devType(winItem, m_pAlarm->stPos.devType);
	
	
	showOneEvt_Note(winItem, &m_pAlarm->stPos.unDev);
	
	// 首行显示 事件类型；
	// 后续显示 sequ/total:
	// showEvtCls_EvtOrSequ_String(winItem, mRow,
								// sequ, U_EvtCls_Alarm);
	
	showOneEvt_sequNum(winItem, sequ, U_EvtCls_Alarm);
}


/******************************************************************************
* FUNC: //
*   IN:
*  OUT:
******************************************************************************/

void Show_OneLink(U8 winItem, EVTWORD sequ,
							TEvtLink_st *m_pLink)
{
U8 swTotal;
//TYPE_LCD_RL mRow, mLine;
TYPE_LCD_XY mPixLineAfterType;

	
	swTotal = swTotal;
	
	showOneEvt_Dev(winItem, &m_pLink->stPos.unDev);
	mPixLineAfterType = showOneEvt_devType(winItem, 
								m_pLink->stPos.devType);
	
	showOneEvt_Note(winItem, &m_pLink->stPos.unDev);
	
	
	
	// 事件类型：
	if(bEvtValid(m_pLink->thing))
	{
		mPixLineAfterType += 4;
		mPixLineAfterType = showLinkEvt(	
					getEvtPixRow(winItem, 2),
				   mPixLineAfterType,  m_pLink->thing
				   );
		
		if(m_pLink->thing == U_ModuAutoRunDelay_EVT)
		{
			mPixLineAfterType += 4;
			showLinkOrExtgDelaySec(
							getEvtPixRow(winItem, 2),
							mPixLineAfterType, 
							m_pLink->delayActSec
							);
		}
		showOneEvt_Clock(winItem, &m_pLink->evtClock);
	}
	
	
	// 事件类型，序号：
	showOneEvt_sequNum(winItem, sequ, U_EvtCls_Link);
	
}



/******************************************************************************
* FUNC: //
*   IN:
*  OUT:
******************************************************************************/

void Show_OneExtg(U8 winItem, EVTWORD sequ,
							TEvtExtg_st *m_pExtg)
{
U8 swTotal;
//TYPE_LCD_RL mRow, mLine;
TYPE_LCD_XY mPixLineAfterType;
	
	swTotal = swTotal;
	
	
	showOneEvt_Dev(winItem, &m_pExtg->stPos.unDev);
	mPixLineAfterType = showOneEvt_devType(winItem, 
								m_pExtg->stPos.devType);
	
	showOneEvt_Note(winItem, &m_pExtg->stPos.unDev);
	
	
	// 事件类型：
	if(bEvtValid(m_pExtg->thing))
	{
		mPixLineAfterType += 4;
		mPixLineAfterType = showExtgEvt(	
					getEvtPixRow(winItem, 2),
				   mPixLineAfterType,  m_pExtg->thing
				   );
		
		if(m_pExtg->thing == U_ModuAutoRunDelay_EVT)
		{
			mPixLineAfterType += 4;
			showLinkOrExtgDelaySec(
							getEvtPixRow(winItem, 2),
							mPixLineAfterType, 
							m_pExtg->delaySpraySec
							);
		}
		showOneEvt_Clock(winItem, &m_pExtg->evtClock);
	}
	
	
	
	// 事件类型，序号：
	showOneEvt_sequNum(winItem, sequ, U_EvtCls_Extg);
	
}

/******************************************************************************
* FUNC: //
*   IN:
*  OUT:
******************************************************************************/

void Show_OneFault(U8 winItem, EVTWORD sequ,
							TEvtFault_st *m_pFault)
{
U8 swTotal;
	
	swTotal = swTotal;
	
	showOneEvt_Dev(winItem, &m_pFault->stPos.unDev);
	
	if(JdgDevClass(&m_pFault->stPos.unDev) == U_DEV_IS_Dete_TYPE)
	{
		showOneEvt_devType(winItem, m_pFault->stPos.devType);
	}
	
	showOneEvt_Clock(winItem, &m_pFault->evtClock);
	
	if(JdgDevClass(&m_pFault->stPos.unDev) == U_DEV_IS_Dete_TYPE)
	{
		showOneEvt_Note(winItem, &m_pFault->stPos.unDev);
	}
	
	
	showOneEvt_sequNum(winItem, sequ, U_EvtCls_Fault);
		
}


/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

void Show_OneDsab(U8 winItem, EVTWORD sequ,
							TEvtDsab_st *m_pDsab)
{
U8 swTotal;
	
	swTotal = swTotal;
	
	showOneEvt_Dev(winItem, &m_pDsab->stPos.unDev);
	
	if(JdgDevClass(&m_pDsab->stPos.unDev) == U_DEV_IS_Dete_TYPE)
	{
		showOneEvt_devType(winItem, m_pDsab->stPos.devType);
	}
	
	showOneEvt_Clock(winItem, &m_pDsab->evtClock);
	
	if(JdgDevClass(&m_pDsab->stPos.unDev) == U_DEV_IS_Dete_TYPE)
	{
		showOneEvt_Note(winItem, &m_pDsab->stPos.unDev);
	}
	
	showOneEvt_sequNum(winItem, sequ, U_EvtCls_Dsab);
}

/******************************************************************************
* FUNC: //
*   IN:
*  OUT:
******************************************************************************/

TYPE_LCD_XY showExtgEvt(TYPE_LCD_XY mPixRow, 
							TYPE_LCD_XY mPixLine, U8 thing)
{
const TCstChar_st *pCstChar;
	
	GetCstChar_EvtExtg(thing, &pCstChar);
	IniTextBuf(U_ShowUseLib_88orCn_CN);
	AddCstStrToTextBuf(pCstChar);
	return ShowTxtBufPix(mPixRow, mPixLine);
}

TYPE_LCD_XY showLinkEvt(TYPE_LCD_XY mPixRow, 
							TYPE_LCD_XY mPixLine, U8 thing)
{
const TCstChar_st *pCstChar;
	
	IniTextBuf(U_ShowUseLib_88orCn_CN);
	GetCstChar_EvtLinkModu(thing, &pCstChar);
	AddCstStrToTextBuf(pCstChar);
	return ShowTxtBufPix(mPixRow, mPixLine);
}

void showLinkOrExtgDelaySec(
					TYPE_LCD_XY mPixRow, TYPE_LCD_XY mPixLine, 
					U32 mDelaySec)
{
U8 *pStr;
	
	IniTextBuf(U_ShowUseLib_88orCn_CN);
	AddCstStrToTextBuf(&cstChar_Delay);
	sw_delaySec_Fig(mDelaySec, 4, &pStr);
	AddToTextBuf(pStr);
	AddCstStrToTextBuf(&cstChar_Second);
	
	ShowTxtBufPix(mPixRow, mPixLine);
}


/******************************************************************************
* FUNC: //
*   IN:
*  OUT:
******************************************************************************/

void Show_Note(TYPE_LCD_RL mRow, TYPE_LCD_RL mLine, 
										TDev_un *pDev)
{
	ShowCodeCharRL(mRow, mLine, 
			"注释567890注释567890注释567890注释567890", FALSE);
	
}

/******************************************************************************
* FUNC: // 状态页面: 显示各类事件的总数
*   IN:
*  OUT: 
******************************************************************************/
const  TLcdRL_st mShowAllEvtTotalRow[U_EvtCls_MAX] = 
{
	// U_EvtCls_Alarm  U_EvtCls_Fault  U_EvtCls_Link = 2,
	{1*2, 0},		{2*2, 0},		{1*2, 15},
	// U_EvtCls_Extg   U_EvtCls_Spvs   U_EvtCls_Dsab = 5, //屏蔽
	{  0, 15},		{ ~0, ~0},		{2*2, 15},
};
#define U_PageEvtTotal_LineChar    9


void LcdPageEvtTotal_First(void)
{
U8 mEvtCls;
const TCstChar_st *pCstPromptChar;


	for(mEvtCls=0; mEvtCls<U_EvtCls_MAX; mEvtCls++)
	{
		if(mShowAllEvtTotalRow[mEvtCls].row >= U_LCD_ROW_MAX)
		{
			continue;
		}
		GetCstChar_EvtCls(mEvtCls, &pCstPromptChar);
		
		IniTextBuf(U_ShowUseLib_88orCn_CN);
		AddCstStrToTextBuf(pCstPromptChar);
		AddCstStrToTextBuf(&cstChar_Total);
		AddCodeStrToTextBuf(":   ;");
		ShowTextBuf(mShowAllEvtTotalRow[mEvtCls].row, 
				   mShowAllEvtTotalRow[mEvtCls].line);
		
		LcdPageEvtTotal_Refresh(mEvtCls);
		bEvtBuf_TotalChange_andClr(mEvtCls); // 为了clr sign.
	}
}

void LcdPageEvtTotal_Refresh(U8 mEvtCls)
{
EVTWORD mEvtTotal;

	if( (mEvtCls >= U_EvtCls_MAX)
	  ||(mShowAllEvtTotalRow[mEvtCls].row >= U_LCD_ROW_MAX))
	{
		return;
	}
	
	mEvtTotal = GetEvtTotal(mEvtCls);
	// 不显示前面的0 + 右对齐：
	Show_Fig_RightAllign(mShowAllEvtTotalRow[mEvtCls].row, 
			mShowAllEvtTotalRow[mEvtCls].line + U_PageEvtTotal_LineChar,
			 mEvtTotal, 
			 U_EVT_TOTAL_FIG_BIT_TOTAL
			 );
}

/******************************************************************************
* FUNC: // 显示事件类型，总数:
*   IN:
*  OUT:
******************************************************************************/

void ShowEvtCls_Total_String(U8 mEvtCls)
{
const TCstChar_st *pCstPromptChar = &cstChar_Default;
U8 bitTotal = U_EVT_TOTAL_FIG_BIT_TOTAL;
EVTWORD total;

	if(mEvtCls >= U_EvtCls_MAX)
	{
		return;
	}
	total = GetEvtTotal(mEvtCls);
	
	GetCstChar_EvtCls(mEvtCls, &pCstPromptChar);
	
	showEvt_TotalNum(0, 0, bitTotal, total, pCstPromptChar);
}

/******************************************************************************
* FUNC: // 显示事件类型，总数:
******************************************************************************/

// evtClsString: total
void showEvt_TotalNum(TYPE_LCD_RL mRow, TYPE_LCD_RL mLine, 
							U8 bitTotal, EVTWORD total,
							const TCstChar_st *pCstPromptChar)
{
U8 swTotal = 0;
U8 *pStr;
	
	IniTextBuf(U_ShowUseLib_88orCn_CN);
	
	swTotal += AddCstStrToTextBuf(pCstPromptChar);
	swTotal += AddCstStrToTextBuf(&cstChar_Total);
	swTotal += AddCodeStrToTextBuf(":");
	
	sw_sequTotal_Fig(total, bitTotal, &pStr);
	swTotal += AddToTextBuf(pStr);
	
	ShowTextBuf(mRow, mLine);
	
}

/******************************************************************************
* FUNC: // 显示事件类型，总数:
******************************************************************************/
// 首行显示 事件类型；
// 后续显示 sequ/total:
void showEvtCls_EvtOrSequ_String(U8 winItem, TYPE_LCD_RL mRow,
							U8 sequ, U8 mEvtCls)
{
const TCstChar_st *pCstPromptChar = &cstChar_Default;
EVTWORD total;
	
	if(mEvtCls >= U_EvtCls_MAX)
	{
		return;
	}
	
	if(winItem == 0)
	{
		GetCstChar_EvtCls(mEvtCls, &pCstPromptChar);
		ShowCstCharRL(mRow, 0, pCstPromptChar);
	}
	else
	{
		total = GetEvtTotal(mEvtCls);
		showEvt_sequTotal(mRow, 0, 
					U_EVT_TOTAL_FIG_BIT_TOTAL, sequ, total);
	}
}

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
static TYPE_LCD_RL getEvtRow(U8 winItem)
{
	if(winItem == 0)
	{
		return 3;
	}
	else
	{
		return (3+ 2*2);
	}
	// return (1+ winItem * 2);
}


static TYPE_LCD_XY getEvtPixRow(U8 winItem, TYPE_LCD_RL mOffsetRow)
{
TYPE_LCD_RL mRow;

	mRow = getEvtRow(winItem);
	mRow += mOffsetRow;
	return getPixYR_formRow(mRow);
}

/******************************************************************************
* FUNC: // 显示事件的 序号/总数:
*   IN:
*  OUT:
******************************************************************************/
// sequ:
void showEvt_SequNum(TYPE_LCD_RL mRow, TYPE_LCD_RL mLine, 
							U8 bitTotal, EVTWORD sequ)
{
U8 swTotal = 0;
U8 *pStr;
	
	IniTextBuf(U_ShowUseLib_88orCn_CN);
	
	sw_sequTotal_Fig(sequ, bitTotal, &pStr);
	swTotal += AddToTextBuf(pStr);
	swTotal += AddCodeStrToTextBuf(":");
	
	ShowTextBuf(mRow, mLine);
	
}

// 显示事件的 序号/总数:
// sequ/total:
void showEvt_sequTotal(TYPE_LCD_RL mRow, TYPE_LCD_RL mLine, 
							U8 bitTotal, EVTWORD sequ, EVTWORD total)
{
U8 swTotal = 0;
U8 *pStr;
	
	IniTextBuf(U_ShowUseLib_88orCn_CN);
	
	sw_sequTotal_Fig(sequ, bitTotal, &pStr);
	swTotal += AddToTextBuf(pStr);
	swTotal += AddCodeStrToTextBuf("/");
	sw_sequTotal_Fig(total, bitTotal, &pStr);
	swTotal += AddToTextBuf(pStr);
	swTotal += AddCodeStrToTextBuf(":");
	
	ShowTextBuf(mRow, mLine);
	
}


/******************************************************************************
* FUNC: //显示时间
*   IN:
*  OUT:
******************************************************************************/
void Show_SysTime_YMDHMS(TYPE_LCD_RL mRow, TYPE_LCD_RL mLine, 
						TEvtClock_st *pClock)
{
// U8 swTotal = 0;
U8 *pStr;

	IniTextBuf(U_ShowUseLib_88orCn_CN);
	// IniTextBuf(U_ShowUseLib_88orCn_88Ascii);

	sw_time_Fig(20, 2, &pStr);
	AddToTextBuf(pStr);
	sw_Time_YMD(pClock->year, pClock->month, pClock->day);
	AddCodeStrToTextBuf(" ");
	sw_Time_HMS(pClock->hour, pClock->min, pClock->sec);
	
	ShowTextBuf(mRow, mLine);
	
}


/******************************************************************************
* FUNC: //
******************************************************************************/

void showLib_EvtTime_YMDHMS(emShowUseLib_PIX  mUseLib,
						TYPE_LCD_RL mRow, TYPE_LCD_RL mLine, 
						TEvtClock_st *pEvtClock)
{
// U8 swTotal = 0;

	IniTextBuf(mUseLib);

	sw_Time_MD(pEvtClock->month, pEvtClock->day);
	AddCodeStrToTextBuf(" ");
	sw_Time_HMS(pEvtClock->hour, pEvtClock->min, pEvtClock->sec);
	
	ShowTextBuf(mRow, mLine);

}
//

void Show88_EvtTime_YMDHMS(
						TYPE_LCD_RL mRow, TYPE_LCD_RL mLine, 
						TEvtClock_st *pEvtClock)
{
	showLib_EvtTime_YMDHMS(U_ShowUseLib_88orCn_88Ascii,
						mRow, mLine, pEvtClock);	
}

void Show_EvtTime_YMDHMS(
						TYPE_LCD_RL mRow, TYPE_LCD_RL mLine, 
						TEvtClock_st *pEvtClock)
{
	showLib_EvtTime_YMDHMS(U_ShowUseLib_88orCn_CN,
						mRow, mLine, pEvtClock);
}



/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
// OUT: pRtnFigStr-> 数字转bcd string.
void sw_time_Fig(U32 fig, U8 bitTotal, U8 **pRtnFigStr)
{
// charNum  = FigToString(fig, bitTotal,  b右对齐, b显示0, **pRtnStr);
	FigToString(fig, bitTotal, TRUE,TRUE, pRtnFigStr);
}


void sw_delaySec_Fig(U32 fig, U8 bitTotal, U8 **pRtnFigStr)
{
// charNum  = FigToString(fig, bitTotal,  b右对齐, b显示0, **pRtnStr);
	FigToString(fig, bitTotal, FALSE,FALSE, pRtnFigStr);
}

void sw_sequTotal_Fig(U32 fig, U8 bitTotal, U8 **pRtnFigStr)
{
// charNum  = FigToString(fig, bitTotal,  b右对齐, b显示0, **pRtnStr);
	FigToString(fig, bitTotal, TRUE,FALSE, pRtnFigStr);
}

/******************************************************************************
* FUNC: //
******************************************************************************/
// OUT: TextBuf[], 字符数：
U8 sw_Time_YMD(U8 mYear, U8 mMonth, U8 mDay)
{
U8 swTotal = 0;
U8 *pStr;

	//sw_time_Fig(20, 2, &pStr);
	//swTotal += AddToTextBuf(pStr);
	sw_time_Fig(mYear, 2, &pStr);
	swTotal += AddToTextBuf(pStr);
	swTotal += AddCodeStrToTextBuf("/");
	
	
	sw_time_Fig(mMonth, 2, &pStr);
	swTotal += AddToTextBuf(pStr);
	swTotal += AddCodeStrToTextBuf("/");
	
	
	sw_time_Fig(mDay, 2, &pStr);
	swTotal += AddToTextBuf(pStr);
	// swTotal += AddCodeStrToTextBuf("/");
	
	return swTotal;
}


/******************************************************************************
* FUNC: //
******************************************************************************/
// OUT: TextBuf[], 字符数：
U8 sw_Time_MD(U8 mMonth, U8 mDay)
{
U8 swTotal = 0;
U8 *pStr;

	// sw_time_Fig(mYear, 2, &pStr);
	// swTotal += AddToTextBuf(pStr);
	// swTotal += AddCodeStrToTextBuf("/");
	
	
	sw_time_Fig(mMonth, 2, &pStr);
	swTotal += AddToTextBuf(pStr);
	swTotal += AddCodeStrToTextBuf("-");
	
	
	sw_time_Fig(mDay, 2, &pStr);
	swTotal += AddToTextBuf(pStr);
	// swTotal += AddCodeStrToTextBuf("/");
	
	return swTotal;
}

/******************************************************************************
* FUNC: //
******************************************************************************/
// OUT: TextBuf[], 字符数：
U8 sw_Time_HMS(U8 mHour, U8 mMin, U8 mSec)
{
U8 swTotal = 0;
U8 *pStr;

	sw_time_Fig(mHour, 2, &pStr);
	swTotal += AddToTextBuf(pStr);
	swTotal += AddCodeStrToTextBuf(":");
	
	sw_time_Fig(mMin, 2, &pStr);
	swTotal += AddToTextBuf(pStr);
	swTotal += AddCodeStrToTextBuf(":");
	
	sw_time_Fig(mSec, 2, &pStr);
	swTotal += AddToTextBuf(pStr);
	// swTotal += AddCodeStrToTextBuf(":");
	
	return swTotal;
}


/******************************************************************************
* FUNC: //
******************************************************************************/

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
void showOneEvt_sequNum(U8 winItem, EVTWORD sequ, U8 mEvtCls)
{
	showEvt_SequNum(getEvtRow(winItem), 0,
					U_EVT_TOTAL_FIG_BIT_TOTAL, sequ);
	
}

void showOneEvt_Note(U8 winItem, TDev_un *pDev)
{
	Show_Note(	getEvtRow(winItem)+4, 0,  pDev);
}


void showOneEvt_Clock(U8 winItem, TEvtClock_st *pEvtClock)
{
	// Show_EvtTime_YMDHMS(
	Show88_EvtTime_YMDHMS( getEvtRow(winItem), 18,  
						 pEvtClock);
}

TYPE_LCD_XY showOneEvt_devType(U8 winItem, U8 mDevType)
{
	return Show_Dete_Type_String(
					getEvtRow(winItem)+2, 
					U_EVT_SHOW_DEV_LINE_START, 
					mDevType);
}

void showOneEvt_Dev(U8 winItem, TDev_un *pDev)
{
	// Show_Dete_Char(	getEvtRow(winItem), 
						// U_EVT_SHOW_DEV_LINE_START, 
						// pDev);
	Show_Dev_String(	getEvtRow(winItem), 
						U_EVT_SHOW_DEV_LINE_START, 
						pDev);
}

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

