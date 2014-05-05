#ifndef __lcdSub_SwOneEvt_H__
#define __lcdSub_SwOneEvt_H__
/******************************************************************************
* @file    lcdSub_SwOneEvt.h
* @author  yx
* @version V1.0
* @date    2013-09-13
* @brief   显示一条事件
* 		
#include  "lcdSub_SwOneEvt.h"
******************************************************************************/

#include  "prjCompileCon.h"
#include  "evtStrDef.h"
#include  "strClock.h"
#include  "strDevice.h"
#include  "lcd_Para.h"

#include  "lcdCst_PgString.h"

/*================= extern ============================================*/
#ifdef  __lcdSub_SwOneEvt_C__
#define EX_lcdSub_SwOneEvt
#else
#define EX_lcdSub_SwOneEvt extern 
#endif

/*================= 常数 ============================================*/

#define U_EVT_TOTAL_FIG_BIT_TOTAL   3  // 总数和序号的 位数
/*================= 结构体定义 ======================================*/

/*================= 公有结构变量声明 ================================*/

/*================= 私有函数声明 ====================================*/
#ifdef __lcdSub_SwOneEvt_C__
// OUT: pRtnFigStr-> 数字转bcd string.
void sw_time_Fig(U32 fig, U8 bitTotal, U8 **pRtnFigStr);
void sw_delaySec_Fig(U32 fig, U8 bitTotal, U8 **pRtnFigStr);
void sw_sequTotal_Fig(U32 fig, U8 bitTotal, U8 **pRtnFigStr);

// OUT: TextBuf[], 字符数：
U8 sw_Time_MD(U8 mMonth, U8 mDay);
U8 sw_Time_YMD(U8 mYear, U8 mMonth, U8 mDay);
U8 sw_Time_HMS(U8 mHour, U8 mMin, U8 mSec);




// 首行显示 事件类型；
// 后续显示 sequ/total:
void showEvtCls_EvtOrSequ_String(U8 winItem, 
							TYPE_LCD_RL mRow,
							U8 sequ, U8 mEvtCls);
// 显示事件的 序号/总数:
// sequ/total:
void showEvt_sequTotal(TYPE_LCD_RL mRow, TYPE_LCD_RL mLine, 
						U8 bitTotal, EVTWORD sequ, EVTWORD total);



// evtClsString: total
void showEvt_TotalNum(TYPE_LCD_RL mRow, TYPE_LCD_RL mLine, 
							U8 bitTotal, EVTWORD total,
							const TCstChar_st *pCstPromptChar);
// sequ:
void showEvt_SequNum(TYPE_LCD_RL mRow, TYPE_LCD_RL mLine, 
							U8 bitTotal, EVTWORD sequ);


TYPE_LCD_XY showExtgEvt(TYPE_LCD_XY mPixRow, TYPE_LCD_XY mPixLine, U8 thing);
TYPE_LCD_XY showLinkEvt(TYPE_LCD_XY mPixRow, TYPE_LCD_XY mPixLine, U8 thing);
void showLinkOrExtgDelaySec(TYPE_LCD_XY mPixRow, TYPE_LCD_XY mPixLine, 
						   U32 mDelaySec);

static TYPE_LCD_RL getEvtRow(U8 winItem);
static TYPE_LCD_XY getEvtPixRow(U8 winItem, TYPE_LCD_RL mOffsetRow);

void showOneEvt_sequNum(U8 winItem, EVTWORD sequ, U8 mEvtCls);
void showOneEvt_Note(U8 winItem, TDev_un *pDev);
void showOneEvt_Clock(U8 winItem, TEvtClock_st *pEvtClock);
TYPE_LCD_XY showOneEvt_devType(U8 winItem, U8 mDevType);
void showOneEvt_Dev(U8 winItem, TDev_un *pDev);

#endif // __lcdSub_SwOneEvt_C__

/*================= 公有函数声明 ====================================*/
// EX_lcdSub_SwOneEvt

// 状态页面: 显示各类事件的总数
void LcdPageEvtTotal_First(void);
void LcdPageEvtTotal_Refresh(U8 mEvtCls);

/*================= 公有函数声明 ====================================*/
// EX_lcdSub_SwOneEvt


/*================= 公有函数声明 ====================================*/
// EX_lcdSub_SwOneEvt

extern void Show_SysTime_YMDHMS(
								TYPE_LCD_RL mRow, TYPE_LCD_RL mLine, 
								TEvtClock_st *pClock);
extern void Show_EvtTime_YMDHMS(
								TYPE_LCD_RL mRow,TYPE_LCD_RL mLine, 
								TEvtClock_st *pEvtClock);
extern void Show88_EvtTime_YMDHMS(
								TYPE_LCD_RL mRow,TYPE_LCD_RL mLine, 
								TEvtClock_st *pEvtClock);
extern void Show_Note( 		TYPE_LCD_RL mRow, TYPE_LCD_RL mLine, 
								TDev_un *pDev);

// 显示事件类型，总数:
extern void ShowEvtCls_Total_String(U8 mEvtCls);

// 各类事件：
extern void Show_OneAlarm(U8 winItem, EVTWORD sequ,
							TEvtAlarm_st *m_pAlarm);
extern void Show_OneSpvs(U8 winItem, EVTWORD sequ,
							TEvtSpvs_st *m_pSpvs);

extern void Show_OneLink(U8 winItem, EVTWORD sequ,
							TEvtLink_st *m_pLink);
extern void Show_OneExtg(U8 winItem, EVTWORD sequ,
							TEvtExtg_st *m_pExtg);
extern void Show_OneFault(U8 winItem, EVTWORD sequ,
							TEvtFault_st *m_pFault);
extern void Show_OneDsab(U8 winItem, EVTWORD sequ,
							TEvtDsab_st *m_pDsab);

/******************************************************************************
// END :
******************************************************************************/
#endif // __lcdSub_SwOneEvt_H__

