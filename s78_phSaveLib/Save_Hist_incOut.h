#ifndef __Save_Hist_incOut_H__
#define __Save_Hist_incOut_H__
/******************************************************************************
* @file    Save_Hist_incOut.h
* @author  yx
* @version V1.3
* @date    2013-09-4
* @brief   
* 
#include  "Save_Hist_incOut.h"
******************************************************************************/
//
#include  "prjCompileCon.h"
#include  "strDevice.h"
#include  "strEvtTrans.h"
#include  "historyClsDef.h"


/*================= ���к�������-lib�ⲿ ====================================*/
// EX_historyWrBuf
// ����ʷ��¼��
extern U8 HistNewEvent(TEvtTrans_st *pEvtTrans);

/*================= ���к�������-lib�ⲿ ====================================*/
//EX_historyRead
//����hist��������
extern U32 HistRd_CacuItem_HistCls(U8 mHistCls, U8 mPart);

//����ʣ������
extern U32 HistRd_CacuItem_Remain(U8 mHistCls, U8 mPart, U32 mRdAdr);

//����hist��������
extern U32 HistRd_CacuItemNum(U8 mHistCls, U8 mPart, 
						U32 mAdrHead, U32 mAdrEnd); 

// ׼����ʼ����¼
// OUT: *pRtnAdrS = �м�¼�ĵ�ַ��
extern BOOL HistRd_Start(U8 mHistCls, U8 *pRtnPart, U32 *pRtnAdrS,
				 U32 *pRtnItemNum);
extern BOOL HistRd_NowAllow(U8 mHistCls, U8 mPart);

// ������ʷ��¼�����ƶ�
extern void HistRd_Item_toNew(U8 mHistCls, U8 mPart,  
					U8 mNextItem, U32 mRdAdr,
					U32 *pRtnAdr, U8 *pRtnIsEnd
					);
// �����ʷ��¼�����ƶ�
extern BOOL HistRd_OneItem(U8 mHistCls, U8 mPart, 
					U32 mRdAdr, 
				   TEvtTrans_st *pRtnEvt, U32 *pRtnAdr,
				   U8 *pRtnHaveArrivedHead);

// TRUE=��ַ����Ч��¼֮��
extern BOOL HistRd_AdrValid(U8 mHistCls, U8 mPart, U32 mAdr);

/******************************************************************************
// END :
******************************************************************************/
#endif // __Save_Hist_incOut_H__

