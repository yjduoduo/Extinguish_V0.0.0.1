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
/*================= 常数 ============================================*/

/*================= 结构体定义 ======================================*/

/*================= 公有结构变量声明 ================================*/

/*================= 私有函数声明 ====================================*/
#ifdef  __historyRead_C__

// 记录最后一次读历史记录的地址，以免在读期间head已修改。
void rdHist_RecordLastAdr(U8 mHistCls, U8 mPart, U32 mAdr);

#endif // __historyRead_C__
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


/*================= 公有函数声明 ====================================*/


/******************************************************************************
// END :
******************************************************************************/
#endif // __historyRead_H__

