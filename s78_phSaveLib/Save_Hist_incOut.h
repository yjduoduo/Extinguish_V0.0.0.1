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


/*================= 公有函数声明-lib外部 ====================================*/
// EX_historyWrBuf
// 新历史记录：
extern U8 HistNewEvent(TEvtTrans_st *pEvtTrans);

/*================= 公有函数声明-lib外部 ====================================*/
//EX_historyRead
//计算hist的条数：
extern U32 HistRd_CacuItem_HistCls(U8 mHistCls, U8 mPart);

//计算剩余条数
extern U32 HistRd_CacuItem_Remain(U8 mHistCls, U8 mPart, U32 mRdAdr);

//计算hist的总条数
extern U32 HistRd_CacuItemNum(U8 mHistCls, U8 mPart, 
						U32 mAdrHead, U32 mAdrEnd); 

// 准备开始读记录
// OUT: *pRtnAdrS = 有记录的地址。
extern BOOL HistRd_Start(U8 mHistCls, U8 *pRtnPart, U32 *pRtnAdrS,
				 U32 *pRtnItemNum);
extern BOOL HistRd_NowAllow(U8 mHistCls, U8 mPart);

// 向新历史记录方向移动
extern void HistRd_Item_toNew(U8 mHistCls, U8 mPart,  
					U8 mNextItem, U32 mRdAdr,
					U32 *pRtnAdr, U8 *pRtnIsEnd
					);
// 向旧历史记录方向移动
extern BOOL HistRd_OneItem(U8 mHistCls, U8 mPart, 
					U32 mRdAdr, 
				   TEvtTrans_st *pRtnEvt, U32 *pRtnAdr,
				   U8 *pRtnHaveArrivedHead);

// TRUE=地址在有效记录之外
extern BOOL HistRd_AdrValid(U8 mHistCls, U8 mPart, U32 mAdr);

/******************************************************************************
// END :
******************************************************************************/
#endif // __Save_Hist_incOut_H__

