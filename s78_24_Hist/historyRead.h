#ifndef __historyRead_H__
#define __historyRead_H__
/******************************************************************************
* @file    historyRead.h
* @author  yx
* @version V1.0
* @date    2013-07-08
* @brief   
* 
#include  "historyRead.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

#include  "strEvtTrans.h"
/*================= extern ============================================*/
#ifdef  __historyRead_C__
#define EX_historyRead
#else
#define EX_historyRead extern 
#endif
/*================= ���� ============================================*/

/*================= �ṹ�嶨�� ======================================*/

/*================= ���нṹ�������� ================================*/

/*================= ˽�к������� ====================================*/
#ifdef  __historyRead_C__

// ��¼���һ�ζ���ʷ��¼�ĵ�ַ�������ڶ��ڼ�head���޸ġ�
void rdHist_RecordLastAdr(U8 mHistCls, U8 mPart, U32 mAdr);

#endif // __historyRead_C__
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


/*================= ���к������� ====================================*/


/******************************************************************************
// END :
******************************************************************************/
#endif // __historyRead_H__

