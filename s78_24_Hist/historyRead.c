#define __historyRead_C__
/******************************************************************************
* @file    historyRead.c
* @author  yx
* @version V1.0
* @date    2013-07-08
* @brief   读历史记录
* 
******************************************************************************/
#include  "historyRead.h"

#include  "phSaveHist_incIn.h"
#include  "strFlsQue.h"

#include  "strEvtTrans.h"
//#include "incFile.h"	


/*================= 常数 ============================================*/

/*================= 结构定义 ========================================*/
typedef struct{
	U8 mHistCls;
	U8 mPart;
	U32 nowAdr; //以最后一次的读操作为准
	BOOL bReNewHead;
}THistRdAdr_st;

static THistRdAdr_st stHistRdAdr;

/*================= 私有结构变量声明 ================================*/
U8 vHistRdBuf[U_FLS_1HISTORY_BYTE_MAX]; //U_FLS_SectorStart_BYTES

/*================= 公有函数声明 ====================================*/

/*================= 私有函数声明 ====================================*/



/*=================  ================================================*/
	

/******************************************************************************
* FUNC: //
******************************************************************************/

/******************************************************************************
* FUNC: //计算hist的条数：
*   IN:
*  OUT: 
******************************************************************************/
U32 HistRd_CacuItem_HistCls(U8 mHistCls, U8 mPart)
{
U8 mFlsItem;

	if(mHistCls >= U_HIST_CLASS_MAX)
	{
		return 0;
	}
	
	
	// mPart = 0;
	// if(bFlsItem_isState(U_FlsItem_Error_State, getFlsItem_hist(mHistCls), mPart))
	// {
		// mPart = 1;
		// if(bFlsItem_isState(U_FlsItem_Error_State, getFlsItem_hist(mHistCls), mPart))
		// {
			// return 0;
		// }
	// }
	
	mFlsItem = getFlsItem_hist(mHistCls);
	
	return HistRd_CacuItemNum(mHistCls, mPart,
			GetFlsQueHeadAdr(mFlsItem, mPart),	
			GetFlsQueEndAdr(mFlsItem, mPart)	 
			);
	
}


/******************************************************************************
* FUNC: //计算剩余条数
******************************************************************************/
U32 HistRd_CacuItem_Remain(U8 mHistCls, U8 mPart, U32 mRdAdr)
{
U8 mFlsItem;

	if(mHistCls >= U_HIST_CLASS_MAX)
	{
		return 0;
	}
	mFlsItem = getFlsItem_hist(mHistCls);
	
	return HistRd_CacuItemNum(mHistCls, mPart,
			GetFlsQueHeadAdr(mFlsItem, mPart),	
			mRdAdr 
			);
	
}

/******************************************************************************
* FUNC: //计算hist的总条数
******************************************************************************/
U32 HistRd_CacuItemNum(U8 mHistCls, U8 mPart, 
				U32 mAdrHead, U32 mAdrEnd) //计算hist的条数
{
U8 mFlsItem;
U32 histItemNum = 0;
U32 sectorS_adrHead;
U32 sectorS_adrEnd;
U32 adr;
U32 sectorNum = 0;
TFlsItemAddr stAdr;

	mFlsItem = getFlsItem_hist(mHistCls);
	if(!getFlsItem_Addr(mFlsItem, mPart, &stAdr))
	{
		return 0;
	}
	
	sectorS_adrHead = hist_sector_start(mAdrHead);
	sectorS_adrEnd  = hist_sector_start(mAdrEnd);
	histItemNum = ((mAdrEnd - sectorS_adrEnd)/U_FLS_1HISTORY_BYTE_MAX);
	if(histItemNum > 1)
	{
		histItemNum -= 1; //空出sector head;
	}
	
	adr = sectorS_adrEnd;
	sectorNum = 0;
	while(adr != sectorS_adrHead)
	{
		adr = hist_sectorBefore_start(adr, &stAdr);
		histItemNum += ( (U_Hist_1SectorBytes 
						/ U_FLS_1HISTORY_BYTE_MAX) -1
						);
		sectorNum++;
		if(sectorNum >= getFlsItem_SectorMax(mFlsItem)) //查找次数上限
		{
			return 0; // 出错
		}
		
	}

	return histItemNum;
}



/******************************************************************************
* FUNC: // 
*   IN:
*  OUT: 
******************************************************************************/
BOOL HistRd_NowAllow(U8 mHistCls, U8 mPart)
{
U8 mFlsItem;
	mFlsItem = getFlsItem_hist(mHistCls);
	return bFlsItem_IsReadAllow(mFlsItem, mPart);
}


/******************************************************************************
* FUNC: // 向新历史记录方向移动
*   IN: mRdAdr 是有记录的位置。若是翻屏，应是最上面的一条的地址
*  OUT: *pRtnAdr 是有记录的位置。
******************************************************************************/
void HistRd_Item_toNew(U8 mHistCls, U8 mPart, 
					U8 mNextItem, U32 mRdAdr,
					U32 *pRtnAdr, U8 *pRtnIsEnd
					)
{
U8 mFlsItem;
TFlsItemAddr stAdr;
U32 adr_queEnd;
U32 adr_sectorHead;
U32 adr;
U32 adr_next;
U8 moveNum;

	*pRtnIsEnd = FALSE;
	*pRtnAdr = mRdAdr;
	
	mFlsItem = getFlsItem_hist(mHistCls);
	getFlsItem_Addr(mFlsItem, mPart, &stAdr);
	adr_queEnd = GetFlsQueEndAdr(mFlsItem, mPart);
	adr = mRdAdr;
	
	if(!HistRd_AdrValid(mHistCls, mPart, mRdAdr))
	{
		*pRtnAdr = adr;
		*pRtnIsEnd = TRUE;
		rdHist_RecordLastAdr(mHistCls,mPart, adr);
		return;
	}
	
	for(moveNum=0; moveNum<mNextItem; moveNum++)
	{
		adr_next = hist_adr_itemNext(adr, &stAdr);
		if(adr_next == adr_queEnd)
		{
			*pRtnIsEnd = TRUE;
			*pRtnAdr = adr;
			rdHist_RecordLastAdr(mHistCls,mPart, adr);
			return;
		}
		adr_sectorHead = hist_sector_start(adr_next);
		if(adr_next == adr_sectorHead)
		{
			adr_next = hist_adr_itemNext(adr_next, &stAdr);
			if(adr_next == adr_queEnd)
			{
				*pRtnIsEnd = TRUE;
				*pRtnAdr = adr;
				rdHist_RecordLastAdr(mHistCls, mPart, adr);
				return;
			}
		}
		adr = adr_next;
	}
	*pRtnIsEnd = FALSE;
	*pRtnAdr = adr;
	rdHist_RecordLastAdr(mHistCls, mPart, adr);
}

/******************************************************************************
* FUNC: // 准备开始读记录
*   IN:
*  OUT: *pRtnAdrS = 有记录的地址。
******************************************************************************/
BOOL HistRd_Start(U8 mHistCls, U8 *pRtnPart, U32 *pRtnAdrS,
				 U32 *pRtnItemNum)
{
U8 mFlsItem;
TFlsItemAddr stAdr;
U32 adr_queEnd;
U32 adr_sectorHead;
U8 mPart;
U32 adr;

	mFlsItem = getFlsItem_hist(mHistCls);
	for(mPart=0; mPart<FlsHistPartMax(); mPart++)
	{
		if(getFlsItem_Addr(mFlsItem, mPart, &stAdr))
		{
			if(bFlsItem_IsUsual(mFlsItem, mPart))
			{
				break;
			}
		}
	}
	rdHist_RecordLastAdr(mHistCls,mPart, stAdr.adrS);
	
	if(mPart<FlsHistPartMax())
	{
		*pRtnPart = mPart;
		*pRtnItemNum = HistRd_CacuItem_HistCls(mHistCls, mPart);
		if(*pRtnItemNum == 0)
		{
			return TRUE;
		}
			
		adr_queEnd = GetFlsQueEndAdr(mFlsItem, mPart);
		adr = hist_adr_itemBefore(adr_queEnd, &stAdr);
		adr_sectorHead = hist_sector_start(adr);
		if(adr == adr_sectorHead)
		{
			adr = hist_adr_itemBefore(adr, &stAdr);
		}
		*pRtnAdrS = adr;
		rdHist_RecordLastAdr(mHistCls,mPart, adr);
		return TRUE;
		
	}
	return FALSE;
}

/******************************************************************************
* FUNC: // 
*   IN:
*  OUT: 
******************************************************************************/
BOOL HistRd_OneItem(U8 mHistCls, U8 mPart, U32 mRdAdr, 
				   TEvtTrans_st *pRtnEvt, U32 *pRtnAdr,
				   U8 *pRtnHaveArrivedHead)
{
U8 mFlsItem;
THisory_un *pHist;
TFlsItemAddr stAdr;
U32 adr;
U32 adr_sectorHead;
U32 adr_queHead;
BOOL bOk;

	*pRtnHaveArrivedHead = FALSE;
	mFlsItem = getFlsItem_hist(mHistCls);
	if(!getFlsItem_Addr(mFlsItem, mPart, &stAdr))
	{
		return FALSE;
	}
	
	if(!HistRd_AdrValid(mHistCls, mPart, mRdAdr))
	{
		*pRtnAdr = mRdAdr;
		*pRtnHaveArrivedHead = TRUE;
		rdHist_RecordLastAdr(mHistCls,mPart, mRdAdr);
		return FALSE;
	}
	
	bOk = FALSE;
	if(bFlsQueRd_OneItem_isOK(stAdr.chip, mRdAdr, 
						mFlsItem))
	{
		pHist = (THisory_un *)(&vHistRdBuf[0]);
		
		pRtnEvt->unDev = pHist->stHist.unDev;
		pRtnEvt->type = pHist->stHist.type;
		pRtnEvt->thing = pHist->stHist.thingFir;
		pRtnEvt->thiFurther = pHist->stHist.thingSec;
		pRtnEvt->evtClock = pHist->stHist.stClock;
			
		bOk = TRUE;
	}
	else
	{
		// 即使不对，也继续进行
	}
	
	adr = hist_adr_itemBefore(mRdAdr, &stAdr);
	adr_sectorHead = hist_sector_start(adr);
	if(adr == adr_sectorHead)
	{
		adr_queHead = GetFlsQueHeadAdr(mFlsItem, mPart);
		if(adr == adr_queHead)
		{
			*pRtnHaveArrivedHead = TRUE;
		}
		adr = hist_adr_itemBefore(adr, &stAdr);
	}
	*pRtnAdr = adr;
	rdHist_RecordLastAdr(mHistCls, mPart, adr);
	return bOk;
	
	
}

/******************************************************************************
* FUNC: // 记录最后一次读历史记录的地址，以免在读期间head已修改。
*   IN:
*  OUT: 
* 当前未起作用。本来计划是，读地址若是被新记录排出有效地址之外，通知。
******************************************************************************/
void rdHist_RecordLastAdr(U8 mHistCls, U8 mPart, U32 mAdr)
{
	stHistRdAdr.mHistCls = mHistCls;
	stHistRdAdr.mPart = mPart;
	stHistRdAdr.nowAdr = mAdr;
	stHistRdAdr.bReNewHead = FALSE;
	
	stHistRdAdr = stHistRdAdr; 
	
#if U_SYS_bShowNoFinished == 1 
	U_SYS_bShowNoFinished = 1;
#endif // U_SYS_bShowNoFinished

}

/******************************************************************************
* FUNC: // TRUE=地址在有效记录之外
*   IN:
*  OUT: 
******************************************************************************/
BOOL HistRd_AdrValid(U8 mHistCls, U8 mPart, U32 mAdr)
{
	return bAdr_Mid_QueHeadEnd(getFlsItem_hist(mHistCls), 
							mPart, mAdr);
}

/******************************************************************************
* FUNC: // END
*   IN:
*  OUT: 
******************************************************************************/
