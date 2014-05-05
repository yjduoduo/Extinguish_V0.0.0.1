#ifndef __evt_Buf_incOut_H__
#define __evt_Buf_incOut_H__
/******************************************************************************
* @file    evt_Buf_incOut.h
* @author  yx
* @version V1.10
* @date    2013.10.17 15:47 
* @brief   事件队列的接口函数
*
*		
*		
* V1.10, 2013.10.17  15:47 《DriverEventBuf_V0.0.0.1_1.5》
*		一页显示事件的数量在master里设置。add: SetEvtWin_OneScrItemMax();  一屏的事件总数默认 U_OneScr_DevBuf_MAX。
*		U_OneScr_DevBuf_MAX 3-> 10
*		去掉 Get_WinEvtBuf_Max();
* V1.9, 2013.10.17  09:19 《DriverEventBuf_V0.0.0.1_1.4》
*		"evtStruct" V1.5   add : GetEvtWin_OneScrItemMax();
* V1.8, 2013-10-15 14:29 《DriverEventBuf_V0.0.0.1_1.2》
*		add: Win_EvtBufClr();
*		add: Win_EvtBuf_Clr_ChangeSign();
*		add: EvtBuf_ClrChange();   bEvtBuf_BufChange()读出后不清。
*		bEvtBuf_TotalChange();  ->  bEvtBuf_TotalChange_Clr(); 
*		U_OneScr_Cls_MAX 的定义 由 evtStruct.h 改到 evt_Para.h.
*		改注释：IniEvtAll();
* V1.7, 2013-10-15 11:28 《DriverEventBuf_V0.0.0.1_1.1》
*		改变 队列数量。
*		add:  bEvtBuf_BufChange();  bEvtBuf_TotalChange(); 
* V1.6, 2013-10-14 22:29 《DriverEventBuf_V0.0.0.1_1.0》
*		soft simulate
* V1.5，2013-09-23 21:33 《DriverEventBuf_V0.0.0.1_0.1.3》
*		add文件："evtCommonLinkExtg" "evtCommonThing"
*		"EventAndWinBuf" 增加 insert 操作。
* V1.4，2013-09-13 14:06
		bWin_EvtBuf_Total();
		《EventAndWinBuf_Driver_V0.0.0.1_0.0.7.lib》
* V1.3, 2013.9.12
		add:　Buf_Extg(); 
		"evtStrDef.h" 升级 V1.1 
		"evtThingDef.h" 升级 V1.1
* V1.2, 2013.9.10 09:38, yx  《DriverEventBuf_V0.0.0.1_0.0.1》
		加返回值 ： IniEvtAll()
* V1.1, 2013.9.9 23:30, yx 
		整理incOut函数，添加注释。
* 		改变： win_EvtCopy()
		add: bWin_EvtBuf_Total();
		add: bWinRead_EvtBuf_One();
		add: bReadOne...() 
* V1.0, 2012-01-05
* 
#include  "evt_Buf_incOut.h"
******************************************************************************/

#include  "prjCompileCon.h"
#include  "strDevice.h"
#include  "strEvtTrans.h"

#include  "evt_Para.h"
#include  "evtThingDef.h"

#include  "evtStrDef.h"
/*================= extern ============================================*/
#ifdef  __evt_Buf_incOut_C__
#define EX_evt_Buf_incOut
#else
#define EX_evt_Buf_incOut extern 
#endif
/*================= 常数 ============================================*/
/*
事件队列的长度，在 evtStruct.c 里定义。 stEvtPoint[U_EvtCls_MAX];


*/
/*================= EventBuf 初始化 ====================================*/
// EX_evtStruct 

// 初始化:
// 判断const定义是否正确，并 初始化。
extern BOOL IniEvtAll(void); //ALL 

// IN: mCls = emEvtClass;
extern void IniEvtPointAndBuf(U8 mCls);

//一屏每类的事件总数:
// 默认 U_OneScr_DevBuf_MAX，在 Win_EvtBufShowIni() 之前需要确定。
extern void SetEvtWin_OneScrItemMax(U8 *pItemNum);
extern U8 GetEvtWin_OneScrItemMax(U8 mCls);

/*================= EventBuf buf属性 ====================================*/
// EX_evtStruct 

extern U32 GetEvtTotal(U8 mCls);
extern BOOL bEvtBuf_Empty(U8 mCls);
extern BOOL bEvtBuf_Full(U8 mCls);

extern BOOL bEvtBuf_BufChange(U8 mCls);
extern void EvtBuf_ClrChange(void);
extern BOOL bEvtBuf_TotalChange_andClr(U8 mCls);

/*================= EventBuf 读取事件buf[] ====================================*/
// EX_evtStruct 


extern EVTWORD  GetEvtHeadLocat(U8 mCls);
extern EVTWORD  GetEvtEndLocat(U8 mCls);

// 物理位置.next :
// OUT: FALSE = mLocatNow Invalid | Now is end.
extern BOOL  GetEvtLocatNext(U8 mCls, EVTWORD mLocatNow, 
										EVTWORD *pRtnLocatNext);
// 物理位置.pre :
// OUT: FALSE = mLocatNow Invalid | Now is head.
extern BOOL  GetEvtLocatPre(U8 mCls, EVTWORD mLocatNow, 
										EVTWORD *pRtnLocatPre);

/*================= Event Win[] ====================================*/
// EX_EventAndWinBuf 

//win[] 初始化, 
extern void Win_EvtBufClr(void); 

// IN: mCls = emEvtClass;
// IN: mScreen=窗口显示分屏的屏号, < U_OneScr_Cls_MAX, 
//		一屏显示的事件类别MAX. 火警/联动。
extern void Win_EvtBufShowIni(U8 mCls, U8 mScreen); 

//win[] 是否有变化：and clr
extern BOOL bWin_EvtBuf_Change(U8 mCls); 
//win[] 清除变化
extern void Win_EvtBuf_Clr_ChangeSign(void);
//win[] 的当前事件总数
// TRUE= win[]里有mCls。
extern BOOL bWin_EvtBuf_Total(U8 mCls, U8 *pRtnTotal);
//读取win[] 一条的locat:
// 配合 bReadOne...() 使用
extern BOOL bWinRead_EvtBuf_One(U8 mCls, U8 mWinBuf, 
								TEvtBufWho_st *pRtnWho);

extern void Win_PageTurnPre(U8 mCls); //前翻页
extern void Win_PageTurnNext(U8 mCls); //后翻页


/*================= 各buf 新事件 ====================================*/
// EX_evt_x_Buf 

extern BOOL Buf_Alarm(TEvtTrans_st *m_pTrans);

extern BOOL Buf_Extg(TEvtTrans_st *m_pTrans);
extern BOOL Buf_Link(TEvtTrans_st *m_pTrans);
extern BOOL Buf_Fault(TEvtTrans_st *m_pTrans);
extern BOOL Buf_Disable(TEvtTrans_st *m_pTrans);
extern BOOL Buf_Spvs(TEvtTrans_st *m_pTrans);


extern BOOL bReadOneAlarmEvent(EVTWORD mLocat, 
									TEvtAlarm_st **pRtnAlarm);
extern BOOL bReadOneSpvsEvent(EVTWORD mLocat, 
									TEvtSpvs_st **pRtnSpvs);
extern BOOL bReadOneLinkEvent(EVTWORD mLocat, 
									TEvtLink_st **pRtnLink);
extern BOOL bReadOneExtgEvent(EVTWORD mLocat, 
									TEvtExtg_st **pRtnExtg);
extern BOOL bReadOneFaultEvent(EVTWORD mLocat, 
									TEvtFault_st **pRtnFault);
extern BOOL bReadOneDsabEvent(EVTWORD mLocat, 
									TEvtDsab_st **pRtnDsab);


/******************************************************************************
// END :
******************************************************************************/
#endif // __evt_Buf_incOut_H__

