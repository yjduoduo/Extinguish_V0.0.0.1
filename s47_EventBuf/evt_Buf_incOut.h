#ifndef __evt_Buf_incOut_H__
#define __evt_Buf_incOut_H__
/******************************************************************************
* @file    evt_Buf_incOut.h
* @author  yx
* @version V1.10
* @date    2013.10.17 15:47 
* @brief   �¼����еĽӿں���
*
*		
*		
* V1.10, 2013.10.17  15:47 ��DriverEventBuf_V0.0.0.1_1.5��
*		һҳ��ʾ�¼���������master�����á�add: SetEvtWin_OneScrItemMax();  һ�����¼�����Ĭ�� U_OneScr_DevBuf_MAX��
*		U_OneScr_DevBuf_MAX 3-> 10
*		ȥ�� Get_WinEvtBuf_Max();
* V1.9, 2013.10.17  09:19 ��DriverEventBuf_V0.0.0.1_1.4��
*		"evtStruct" V1.5   add : GetEvtWin_OneScrItemMax();
* V1.8, 2013-10-15 14:29 ��DriverEventBuf_V0.0.0.1_1.2��
*		add: Win_EvtBufClr();
*		add: Win_EvtBuf_Clr_ChangeSign();
*		add: EvtBuf_ClrChange();   bEvtBuf_BufChange()�������塣
*		bEvtBuf_TotalChange();  ->  bEvtBuf_TotalChange_Clr(); 
*		U_OneScr_Cls_MAX �Ķ��� �� evtStruct.h �ĵ� evt_Para.h.
*		��ע�ͣ�IniEvtAll();
* V1.7, 2013-10-15 11:28 ��DriverEventBuf_V0.0.0.1_1.1��
*		�ı� ����������
*		add:  bEvtBuf_BufChange();  bEvtBuf_TotalChange(); 
* V1.6, 2013-10-14 22:29 ��DriverEventBuf_V0.0.0.1_1.0��
*		soft simulate
* V1.5��2013-09-23 21:33 ��DriverEventBuf_V0.0.0.1_0.1.3��
*		add�ļ���"evtCommonLinkExtg" "evtCommonThing"
*		"EventAndWinBuf" ���� insert ������
* V1.4��2013-09-13 14:06
		bWin_EvtBuf_Total();
		��EventAndWinBuf_Driver_V0.0.0.1_0.0.7.lib��
* V1.3, 2013.9.12
		add:��Buf_Extg(); 
		"evtStrDef.h" ���� V1.1 
		"evtThingDef.h" ���� V1.1
* V1.2, 2013.9.10 09:38, yx  ��DriverEventBuf_V0.0.0.1_0.0.1��
		�ӷ���ֵ �� IniEvtAll()
* V1.1, 2013.9.9 23:30, yx 
		����incOut���������ע�͡�
* 		�ı䣺 win_EvtCopy()
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
/*================= ���� ============================================*/
/*
�¼����еĳ��ȣ��� evtStruct.c �ﶨ�塣 stEvtPoint[U_EvtCls_MAX];


*/
/*================= EventBuf ��ʼ�� ====================================*/
// EX_evtStruct 

// ��ʼ��:
// �ж�const�����Ƿ���ȷ���� ��ʼ����
extern BOOL IniEvtAll(void); //ALL 

// IN: mCls = emEvtClass;
extern void IniEvtPointAndBuf(U8 mCls);

//һ��ÿ����¼�����:
// Ĭ�� U_OneScr_DevBuf_MAX���� Win_EvtBufShowIni() ֮ǰ��Ҫȷ����
extern void SetEvtWin_OneScrItemMax(U8 *pItemNum);
extern U8 GetEvtWin_OneScrItemMax(U8 mCls);

/*================= EventBuf buf���� ====================================*/
// EX_evtStruct 

extern U32 GetEvtTotal(U8 mCls);
extern BOOL bEvtBuf_Empty(U8 mCls);
extern BOOL bEvtBuf_Full(U8 mCls);

extern BOOL bEvtBuf_BufChange(U8 mCls);
extern void EvtBuf_ClrChange(void);
extern BOOL bEvtBuf_TotalChange_andClr(U8 mCls);

/*================= EventBuf ��ȡ�¼�buf[] ====================================*/
// EX_evtStruct 


extern EVTWORD  GetEvtHeadLocat(U8 mCls);
extern EVTWORD  GetEvtEndLocat(U8 mCls);

// ����λ��.next :
// OUT: FALSE = mLocatNow Invalid | Now is end.
extern BOOL  GetEvtLocatNext(U8 mCls, EVTWORD mLocatNow, 
										EVTWORD *pRtnLocatNext);
// ����λ��.pre :
// OUT: FALSE = mLocatNow Invalid | Now is head.
extern BOOL  GetEvtLocatPre(U8 mCls, EVTWORD mLocatNow, 
										EVTWORD *pRtnLocatPre);

/*================= Event Win[] ====================================*/
// EX_EventAndWinBuf 

//win[] ��ʼ��, 
extern void Win_EvtBufClr(void); 

// IN: mCls = emEvtClass;
// IN: mScreen=������ʾ����������, < U_OneScr_Cls_MAX, 
//		һ����ʾ���¼����MAX. ��/������
extern void Win_EvtBufShowIni(U8 mCls, U8 mScreen); 

//win[] �Ƿ��б仯��and clr
extern BOOL bWin_EvtBuf_Change(U8 mCls); 
//win[] ����仯
extern void Win_EvtBuf_Clr_ChangeSign(void);
//win[] �ĵ�ǰ�¼�����
// TRUE= win[]����mCls��
extern BOOL bWin_EvtBuf_Total(U8 mCls, U8 *pRtnTotal);
//��ȡwin[] һ����locat:
// ��� bReadOne...() ʹ��
extern BOOL bWinRead_EvtBuf_One(U8 mCls, U8 mWinBuf, 
								TEvtBufWho_st *pRtnWho);

extern void Win_PageTurnPre(U8 mCls); //ǰ��ҳ
extern void Win_PageTurnNext(U8 mCls); //��ҳ


/*================= ��buf ���¼� ====================================*/
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

