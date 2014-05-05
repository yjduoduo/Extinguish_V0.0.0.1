#define __historyWrBuf_C__
/******************************************************************************
* @file    historyWrBuf.c
* @author  yx
* @version V1.0
* @date    2013-07-08
* @brief   写历史记录的RAM缓冲区。
* 		
* IN: U8 HistNewEvent(TEvtTrans_st *pEvtTrans)

// U_SIGN_bHaveTested; 2013-07-10
******************************************************************************/
#include  "historyWrBuf.h"


#include  "phSaveHist_incIn.h"
//#include  "evt_Buf_incOut.h"
//#include "incFile.h"	


/*================= 常数 ============================================*/

/*================= 结构定义 ========================================*/


typedef struct{ //stHistWriBuf
	TBufCircle    stCircle;
	TEvtTrans_st  buf[U_HIST_BUF_MAX];
	U32 thisCycOut; //此次处理周期的截止out.
	
	//有U_FlsSave_Part_MAX，是方便写后清零。
	U32 histClsBits[U_FlsSave_Part_MAX][U_HIST_BUF_MAX]; //需要保存到哪种，哪位置1
	
	
}THistWriBuf_st; //历史记录RAM buf

THistWriBuf_st   stHistWriBuf; //新事件buf

/*================= 私有结构变量声明 ================================*/

/*================= 公有函数声明 ====================================*/

/*================= 私有函数声明 ====================================*/

void histBuf_check_clsBits(U32 mNowOut);

/*=================  ================================================*/

/******************************************************************************
* NAME: 
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

void Init_HistWrBuf(void)
{
	ClrRamIs00((U8 *)(&stHistWriBuf), sizeof(THistWriBuf_st));
	
	BufCircleIni(U_HIST_BUF_MAX, &stHistWriBuf.stCircle);
}


/******************************************************************************
* NAME: 
* FUNC: // 新事件，存历史记录
*   IN:
*  OUT: 
******************************************************************************/

U8 HistNewEvent(TEvtTrans_st *pEvtTrans)
{
U32 mIn;
U32 mClsBits; 
//U8 *pByteS;
//U8 *pByteCrc;

	if(bFullBufCircle(&stHistWriBuf.stCircle))
	{
		return FALSE;
	}
		
	mIn = BufCircle_GetIn(&stHistWriBuf.stCircle);
	stHistWriBuf.buf[mIn] = *pEvtTrans;
	
	
	// pByteS = (U8*)(&stHistWriBuf.buf[mIn]);
	// pByteCrc = pByteS + (U_FLS_1HISTORY_BYTE_MAX - 1);
	// *pByteCrc = CacuCrcValue(pByteS, (U_FLS_1HISTORY_BYTE_MAX - 1));
	
	
	
	mClsBits= EvtThing_toHistClsBits(pEvtTrans);
	if(mClsBits == 0)
	{
		return FALSE;
	}
	//用 FlsHistPartMax()-1 是不必判断是否有part2
	stHistWriBuf.histClsBits[0][mIn] = mClsBits;
	stHistWriBuf.histClsBits[FlsHistPartMax()-1][mIn] = mClsBits; 
	
	BufCircle_InInc(&stHistWriBuf.stCircle);
	
	return TRUE;
}


/******************************************************************************
* FUNC: // 读取
*   IN:
*  OUT: 
******************************************************************************/

BOOL bHistBuf_isEmpty(void)
{
	return bEmptyBufCircle(&stHistWriBuf.stCircle);
}

BOOL bHistBuf_NumNeedSave(void)
{
	return (CircleFillBytes(&stHistWriBuf.stCircle) >= U_HIST_BUF_NeedSave_NUM);
}

BOOL bHistBuf_readThisCycFinished(void)
{
	if(BufCircle_GetOut(&stHistWriBuf.stCircle)
	  == (stHistWriBuf.thisCycOut))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/******************************************************************************
* FUNC: //历史记录待写入buf，此次截止:
******************************************************************************/
void HistBuf_StartRead(void)
{
	stHistWriBuf.thisCycOut = BufCircle_GetIn(&stHistWriBuf.stCircle);
}


/******************************************************************************
* FUNC: // 读一类， 一次读一条。
*  OUT: TRUE 表示 out ~ thisCycOut 有此类事件。
* 		
*		读后清除标志。
******************************************************************************/
BOOL HistBuf_Read(U8 mHistCls, U8 mPart, THisory_un *pRtnHist)
{
U32 mOutS;
U32 mOutE;
U32 mOut;
U32 needBit;
TEvtTrans_st *pEvt;
U8 *pByteS;
U8 *pByteCrc;

	if((mHistCls>=U_HIST_CLASS_MAX) || (mPart >= FlsHistPartMax()))
		return FALSE;
	if(bEmptyBufCircle(&stHistWriBuf.stCircle))
	{
		return FALSE;
	}
	
	needBit = (1 << mHistCls);
	
	mOutS = BufCircle_GetOut(&stHistWriBuf.stCircle);
	mOutE = stHistWriBuf.thisCycOut;
	
	mOut = mOutS;

	while(mOut != mOutE)
	{
		if(stHistWriBuf.histClsBits[mPart][mOut] & needBit)
		{
			pEvt = &stHistWriBuf.buf[mOut];
			pRtnHist->stHist.unDev = pEvt->unDev;
			pRtnHist->stHist.type  = pEvt->type ;
			pRtnHist->stHist.thingFir  = pEvt->thing ;
			pRtnHist->stHist.thingSec  = pEvt->thiFurther ;
			pRtnHist->stHist.stClock  = pEvt->evtClock ;
				
	pByteS = (U8*)(pRtnHist);
	pByteCrc = pByteS + (U_FLS_1HISTORY_BYTE_MAX - 1);
	*pByteCrc = CacuCrcValue(pByteS, (U_FLS_1HISTORY_BYTE_MAX - 1));
	
			// clr bit:
			stHistWriBuf.histClsBits[mPart][mOut] &= (~needBit);
			histBuf_check_clsBits(mOut);
			return TRUE;
		}
		
		histBuf_check_clsBits(mOut);
		mOut = CircleAdd(mOut, 1, stHistWriBuf.stCircle.max);
	}
	return FALSE;
}


/******************************************************************************
* FUNC: //
******************************************************************************/

void histBuf_check_clsBits(U32 mNowOut)
{
	
	if(mNowOut == BufCircle_GetOut(&stHistWriBuf.stCircle))
	{
		if( (stHistWriBuf.histClsBits[0][mNowOut] == 0)
		  &&(stHistWriBuf.histClsBits[FlsHistPartMax()-1][mNowOut] == 0))
		{
			BufCircle_OutInc(&stHistWriBuf.stCircle);
		}
	}
}


/******************************************************************************
* FUNC: // END
*   IN:
*  OUT: 
******************************************************************************/
