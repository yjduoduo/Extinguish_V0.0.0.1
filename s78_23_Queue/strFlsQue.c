#define __strFlsQue_C__
/******************************************************************************
* @file    strFlsQue.c
* @author  yx
* @version V1.0
* @date    2013-07-23
* @brief   
* 
******************************************************************************/
#include  "strFlsQue.h"


#include  "flsStoreBytesDef.h"
#include "codeCrc.h"

#include  "strFlsAdrDef.h"
#include  "strFlsItmStruct.h"
#include  "flsAdrCalculate.h"
#include  "strFlsItmStrCacu.h"
#include  "flsItemState.h"

#include  "flsInqPoint.h"
#include  "fls_Interface.h"
//#include "incFile.h"	


/*================= 常数 ============================================*/
/*================= 队列存储的指针 ======================================*/
//队列类型的 mFlsItem 最多有：
#define U_FlsQueue_PointId_MAX  (U_HIST_CLASS_MAX*3 + 4) 

/*================= 结构定义 ========================================*/

/*================= 私有结构变量声明 ================================*/
// 最多的一个：
// #define U_FLS_1HISTORY_BYTE_MAX   0x10
// #define U_FLS_1HistPoint_BYTE_MAX   0x08
// #define U_FLS_1PowerOff_BYTE_MAX   0x10

static U8 vRdBuf[U_FLS_1HISTORY_BYTE_MAX]; //

/*================= 公有函数声明 ====================================*/

/*================= 私有函数声明 ====================================*/

/*=================  ================================================*/
		
/******************************************************************************
* FUNC: //队列属性 TFlsQueueProp :
*   IN:
*  OUT: 
//U_FlsQueue_PointId_MAX
******************************************************************************/
BOOL FlsQueue_Prop(U8 mFlsItem, U8 mFlsPart, TFlsQueueProp *pProp)
{
U32 mId;

	pProp->itemBytes = ~0;
	pProp->mFlsItem = mFlsItem;
	pProp->bIsQueue = FALSE;
	pProp->pointId = ~0;
	pProp->sectBytes = U_FLASH_1_SECTOR;
	
	if(mFlsPart != 0)
	{
		if(!bFlsItem_HaveShare(mFlsItem))
		{
			return FALSE;
		}
	}
	if(!getFlsItem_Addr(mFlsItem, mFlsPart, &pProp->stAdr))
	{
		return FALSE;
	}
	
	
	
	
	pProp->bIsQueue = TRUE;
	// U_FlsQueue_PointId_MAX 
	
	if(mFlsItem == getFlsItem_PowerOff())
	{
		pProp->pointId   = U_HIST_CLASS_MAX*3;
		pProp->itemBytes = U_FLS_1PowerOff_BYTE_MAX;
	}
#if U_SYS_Test_Flash_InqPoint == 1
	else if(mFlsItem == U_SimFlsPoit_FlsItmCls)
	{
		pProp->pointId   = U_HIST_CLASS_MAX*3+1;
		pProp->itemBytes = U_SimFlsPoit_1ItemBytes;
		pProp->sectBytes = U_SimFlsPoit_1SectorBytes;
	}
#endif 

	else if(bFlsItemIs_hstPart0Point(mFlsItem))
	{
		pProp->pointId   = mFlsItem - getFlsItem_hstPart0Point(0);
		pProp->itemBytes = U_FLS_1HistPoint_BYTE_MAX;
	}
	else if(bFlsItemIs_hstPart1Point(mFlsItem))
	{
		mId          = mFlsItem - getFlsItem_hstPart1Point(0);
		pProp->pointId   = U_HIST_CLASS_MAX + mId;
		pProp->itemBytes = U_FLS_1HistPoint_BYTE_MAX;
	}
	else if(bFlsItemIsHist(mFlsItem))
	{
		mId          = mFlsItem - getFlsItem_hist(0);
		pProp->pointId   = U_HIST_CLASS_MAX*2 + mId;
		pProp->itemBytes = U_FLS_1HistPoint_BYTE_MAX;
		return TRUE;
	}
	else
	{
		pProp->bIsQueue = FALSE;
	}
	
	return pProp->bIsQueue;
}


/******************************************************************************
* FUNC: // if 是 Queue类型存储：
*   IN:
*  OUT: 
******************************************************************************/
BOOL bFlsItem_isQueue(U8 mFlsItem)
{
U8 mFlsPart = 0;
TFlsQueueProp stProp;

	if(FlsQueue_Prop(mFlsItem, mFlsPart, &stProp))
	{
	}
	return stProp.bIsQueue;
}

// 每条的字节数:
U32 FlsItemQue_itemBytes(U8 mFlsItem)
{
U8 mFlsPart = 0;
TFlsQueueProp stProp;

	if(FlsQueue_Prop(mFlsItem, mFlsPart, &stProp))
	{
	}
	return stProp.itemBytes;
}

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
// flsItem的存储，队列类型的，排号:
BOOL getFlsQueue_pointId(U8 mFlsItem, U32 *pRtnPointId)
{
TFlsQueueProp stProp;
U8 mFlsPart = 0;

	FlsQueue_Prop(mFlsItem, mFlsPart, &stProp);
	*pRtnPointId = stProp.pointId;
	return stProp.bIsQueue;
}



/******************************************************************************
* NAME: 
* FUNC: // 读取&设置： head,end：
*   IN:
*  OUT: 
******************************************************************************/

TFlsQueuePoint_st stFlsQueuePoint[U_FlsQueue_PointId_MAX][U_FlsSave_Part_MAX];

// 读取 head,end; 
U32 GetFlsQueHeadAdr(U8 mFlsItem, U8 mFlsPart)
{
	U32 quePointId;
	if(!getFlsQueue_pointId(mFlsItem, &quePointId))
	{
		return ~0;
	}
	return stFlsQueuePoint[quePointId][mFlsPart].headAdr;
}

U32 GetFlsQueEndAdr(U8 mFlsItem, U8 mFlsPart)
{
	U32 quePointId;
	if(!getFlsQueue_pointId(mFlsItem, &quePointId))
	{
		return ~0;
	}
	return stFlsQueuePoint[quePointId][mFlsPart].endAdr;
}

BOOL GetFlsQueHeadEndAdr(U8 mFlsItem, U8 mFlsPart,
				TFlsQueuePoint_st *pRtnHeadEnd)
{
	U32 quePointId;
	if(!getFlsQueue_pointId(mFlsItem, &quePointId))
	{
		return FALSE;
	}
	*pRtnHeadEnd = stFlsQueuePoint[quePointId][mFlsPart];
	return TRUE;
}



// 设置 head,end; 
void SetFlsQueHeadAdr(U8 mFlsItem, U8 mFlsPart, U32 flsAdr)
{
	U32 quePointId;
	if(!getFlsQueue_pointId(mFlsItem, &quePointId))
	{
		return;
	}
	stFlsQueuePoint[quePointId][mFlsPart].headAdr = flsAdr;
}

void SetFlsQueEndAdr(U8 mFlsItem, U8 mFlsPart, U32 flsAdr)
{
	U32 quePointId;
	if(!getFlsQueue_pointId(mFlsItem, &quePointId))
	{
		return;
	}
	stFlsQueuePoint[quePointId][mFlsPart].endAdr = flsAdr;
}


/******************************************************************************
* FUNC: // 1条的校验正确, crc;
*   IN:
*  OUT: 
******************************************************************************/
BOOL bFlsQueRd_OneItem_isOK(U8 chip, U32 mAdr, U8 mFlsItem)
{
U32 adr_meS;
U32 mStrByte = GetFlsItemBufBytes(mFlsItem); //计算各写buf的需求bytes

	if(!bFlsItem_isQueue(mFlsItem))
	{
		return FALSE;
	}
	adr_meS = FlsItm_adr_itemMe_start(mAdr, mStrByte); //一条的首地址

	FlsHd_Read_nByte(chip, &vRdBuf[0], mStrByte, adr_meS);
	return (JdgCrcOK(&vRdBuf[0], mStrByte));
	
}

/******************************************************************************
* FUNC: // 判断mAdr所在sector存储的情况。
*  OUT:  emFlsQueSectorState
******************************************************************************/

U8 FlsQueRd_JdgFlsSect(U8 chip, U32 mAdr, U8 mFlsItem)
{
U32 adr_ItemLast;

	mAdr = FlsItm_sector_start(mAdr, mFlsItem);

	if(!bFlsSectorStart_isItem(chip, mAdr, mFlsItem))
	{
		return U_FlsQueSectorSta_NotMe;
	}

	adr_ItemLast = FlsItm_adr_sector_LastItem(
				mAdr, mFlsItem, FlsItemQue_itemBytes(mFlsItem)); //last one

	
	
	
	if(bFlsQueRd_OneItem_isOK(chip, adr_ItemLast, mFlsItem))
	{
		return U_FlsQueSectorSta_SectIsFull;
	}
	else
	{
		return U_FlsQueSectorSta_SectNotFull;
	}
}

/******************************************************************************
* FUNC: // CLR: head & end = stAdr.adrS
*   IN:
*  OUT: 
******************************************************************************/
void ClrAll_FlsQueHeadEnd(void)
{
	U8 mFlsItem;
	U8 mPart;
	for(mFlsItem=0; mFlsItem<GetSaveItemMax(); mFlsItem++)
	{
		if(!bFlsItem_isQueue(mFlsItem))
		{
			continue;
		}
		for(mPart=0; mPart<FlsItem_PartMax(mFlsItem); mPart++)
		{
			ClrOneItem_FlsQueHeadEnd(mFlsItem, mPart);
		}
	}
	
}

/******************************************************************************
* FUNC: // CLR: head & end = stAdr.adrS
******************************************************************************/

void ClrOneItem_FlsQueHeadEnd(U8 mFlsItem, U8 mPart)
{
TFlsItemAddr stAdr;

	if(getFlsItem_Addr(mFlsItem, mPart, &stAdr))
	{
		SetFlsQueHeadAdr(mFlsItem, mPart, stAdr.adrS);
		SetFlsQueEndAdr (mFlsItem, mPart, stAdr.adrS);
	}
}

/******************************************************************************
* FUNC: // 读取flash，判断queue.head & end.
*   IN:
*  OUT: SetFlsQueHeadAdr();  SetFlsQueEndAdr();
******************************************************************************/
void InitAll_FlsQueHeadEnd(void)
{
	U8 mFlsItem;
	U8 mPart;
	for(mFlsItem=0; mFlsItem<GetSaveItemMax(); mFlsItem++)
	{
		if(!bFlsItem_isQueue(mFlsItem))
		{
			continue;
		}
		
		for(mPart=0; mPart<FlsItem_PartMax(mFlsItem); mPart++)
		{
			InitOneItem_FlsQueHeadEnd(mFlsItem, mPart);
		}
	}
	
}

/******************************************************************************
* FUNC: // 读取flash，判断queue.head & end.
*   IN:
*  OUT: SetFlsQueHeadAdr();  SetFlsQueEndAdr();
*Slave: flsInqPoint.c
******************************************************************************/

void InitOneItem_FlsQueHeadEnd(U8 mFlsItem, U8 mPart)
{
TFlsQueuePoint_st  stHeadEnd;

	if(!bFlsItem_isQueue(mFlsItem))
	{
		return;
	}
	
	if(flsInq_1Cls_JdgPoint(mFlsItem, mPart, &stHeadEnd))
	{
		SetFlsQueHeadAdr(mFlsItem, mPart, stHeadEnd.headAdr);
		SetFlsQueEndAdr (mFlsItem, mPart, stHeadEnd.endAdr);
		if(stHeadEnd.headAdr == stHeadEnd.endAdr)
		{
			Set_FlsItemState(U_FlsItem_Space_State, mFlsItem, mPart);
		}
	}
	else
	{
		ClrOneItem_FlsQueHeadEnd(mFlsItem, mPart);
		
		Set_FlsItemState(U_FlsItem_Error_State, mFlsItem, mPart);
	}
}


/******************************************************************************
* FUNC: // if 地址在 head,end之间:
*   IN:
*  OUT: 
******************************************************************************/

BOOL bAdr_Mid_QueHeadEnd(U8 mFlsItem, U8 mPart, U32 flsAdr)
{
TFlsQueuePoint_st  stHeadEnd;
		
	if(!GetFlsQueHeadEndAdr(mFlsItem, mPart, &stHeadEnd))
	{
		return FALSE;
	}
	if(stHeadEnd.headAdr == stHeadEnd.endAdr)
	{
		return FALSE;
	}
	else if(stHeadEnd.headAdr < stHeadEnd.endAdr)
	{
		return ((flsAdr >= stHeadEnd.headAdr)
				&&(flsAdr < stHeadEnd.endAdr));
	}
	else
	{
		if(flsAdr >= stHeadEnd.headAdr)
			return TRUE;
		else if(flsAdr < stHeadEnd.endAdr)
			return TRUE;
		else
			return FALSE;
	}
}


/******************************************************************************
* FUNC: // 比较2组 head & end 是否equal:
*   IN:
*  OUT: 
******************************************************************************/

BOOL bEqu_FlsQueHeadEnd(TFlsQueuePoint_st *p1, 
					           TFlsQueuePoint_st *p2
							   )
{
	return (   (p1->headAdr == p2->headAdr)
			&& (p1->endAdr  == p2->endAdr));
}

/******************************************************************************
* FUNC: // END
*   IN:
*  OUT: 
******************************************************************************/
