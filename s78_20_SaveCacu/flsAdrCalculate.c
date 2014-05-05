#define __flsAdrCalculate_C__
/******************************************************************************
* @file    flsAdrCalculate.c
* @author  yx
* @version V1.1
* @date    2013-07-23
* @brief   
* 
V1.1, 增加FlsItm_sector_Total(); 2013.7.23, by yx;
******************************************************************************/
#include  "flsAdrCalculate.h"

#include  "flsStoreBytesDef.h"
#include  "codeComm.h"

//#include "incFile.h"	


/*================= 常数 ============================================*/

/*=================  ================================================*/

/******************************************************************************
* FUNC: // 
*   IN:
*  OUT: 
//防止 各mFlsItem 的sector不同。
******************************************************************************/

U32 FlsItm_sector_start(U32 mAdr, U8 mFlsItem)
{
U32 oneSector_ByteMax = getFlsItem_1SectorBytes(mFlsItem);
	return AdrAllignArea_ToLow(mAdr, oneSector_ByteMax);
	
}

U32 FlsItm_sectorBefore_start(U32 mAdr, U8 mFlsItem, TFlsItemAddr *pAdr)
{
U32 adr;
U32 oneSector_ByteMax = getFlsItem_1SectorBytes(mFlsItem);
	

	adr = AdrAllignArea_ToLow(mAdr, oneSector_ByteMax);
	
	if(adr == pAdr->adrS)
	{
		return (pAdr->adrE - oneSector_ByteMax);
	}
	else
	{
		if(adr >= oneSector_ByteMax)
		{
			return (adr - oneSector_ByteMax);
		}
		else
		{
			return (pAdr->adrE - oneSector_ByteMax);
		}
		
	}
	
}

U32 FlsItm_sectorNext_start(U32 mAdr, U8 mFlsItem, TFlsItemAddr *pAdr)
{
U32 adr;
U32 oneSector_ByteMax = getFlsItem_1SectorBytes(mFlsItem);
	
	adr = AdrAllignArea_ToHigh(mAdr, oneSector_ByteMax);
	if(adr == pAdr->adrE)
	{
		adr = pAdr->adrS;
	}
	return adr;
	
}

U32 FlsItm_sector_Total(U8 mFlsItem, TFlsItemAddr *pAdr)
{
	U32 nowAdr;
	U32 sectTotal = 0;
	
	nowAdr = pAdr->adrS;
	while(1)
	{
		if(nowAdr == pAdr->adrE)
		{
			break;
		}
		nowAdr = FlsItm_sectorNext_start(nowAdr, mFlsItem, pAdr);
		sectTotal++;
	}
	return sectTotal;
}


U32 FlsItm_adr_sector_firItem(U32 mAdr, U8 mFlsItem, U32 oneItemBytes)
{
	mAdr = FlsItm_sector_start(mAdr, mFlsItem);
	return (mAdr + oneItemBytes);
}

U32 FlsItm_adr_sector_LastItem(U32 mAdr, U8 mFlsItem, U32 oneItemBytes)
{
U32 adr;
U32 oneSector_ByteMax = getFlsItem_1SectorBytes(mFlsItem);


	adr = AdrAllignArea_ToLow(mAdr, oneSector_ByteMax);
	adr += oneSector_ByteMax;
	adr -= oneItemBytes;
	return adr;
}


U32 FlsItm_adr_itemMe_start(U32 mAdr, U32 oneItemBytes)
{
	return AdrAllignArea_ToLow(mAdr, oneItemBytes);
}

//Tested 2013.7.7
U32 FlsItm_adr_itemNext(U32 mAdr, U8 mFlsItem, U32 oneItemBytes, TFlsItemAddr *pAdr)
{
U32 adr;
U32 oneSector_ByteMax = getFlsItem_1SectorBytes(mFlsItem);

	adr  = AdrAllignArea_ToLow(mAdr, oneItemBytes);
	adr += oneItemBytes; //注意 new sector
	if((adr & (oneSector_ByteMax-1)) == 0)
	{
		return FlsItm_sectorNext_start(mAdr, mFlsItem, pAdr);
	}
	else
	{
		return adr;
	}
}

U32 FlsItm_adr_itemBefore(U32 mAdr, U8 mFlsItem, U32 oneItemBytes, TFlsItemAddr *pAdr)
{
U32 adr;
U32 adr_sectHead;

	adr  = AdrAllignArea_ToLow(mAdr, oneItemBytes);
	adr_sectHead = FlsItm_sector_start(mAdr, mFlsItem);
	if(adr == adr_sectHead)
	{
		adr_sectHead = FlsItm_sectorBefore_start(adr, mFlsItem, pAdr);
		return FlsItm_adr_sector_LastItem(adr_sectHead, mFlsItem, oneItemBytes);
	}
	else
	{
		return (adr - oneItemBytes);
	}
	
}


U32 FlsItm_adr_inSector(U32 mAdr, U8 mFlsItem)
{
U32 oneSector_ByteMax = getFlsItem_1SectorBytes(mFlsItem);
	
	return ((mAdr) & (oneSector_ByteMax-1));
}


U32 FlsItm_adr_inSect_itmSequ(U32 mAdr, U8 mFlsItem, U32 oneItemBytes)
{
	U32 adr_inSect;
	adr_inSect = FlsItm_adr_inSector(mAdr, mFlsItem);
	return adr_inSect / oneItemBytes;
}

//剩余的条数
U32 FlsItm_adr_inSect_itmSpace(U32 mAdr, U8 mFlsItem, U32 oneItemBytes)
{
U32 adr_inSect;
U32 inSect_ItmMax;
U32 inSect_ItmMe;
U32 oneSector_ByteMax = getFlsItem_1SectorBytes(mFlsItem);

	adr_inSect = ((mAdr) & (oneSector_ByteMax-1));
	inSect_ItmMax = oneSector_ByteMax / oneItemBytes;
	inSect_ItmMe  = adr_inSect        / oneItemBytes;
	return inSect_ItmMax - inSect_ItmMe;
}






/******************************************************************************
* FUNC: // 
*   IN:
*  OUT: 
******************************************************************************/

U32 hist_sector_start(U32 mAdr)
{
	return FlsItm_sector_start(mAdr, getFlsItem_hist(0));
}


U32 hist_me_start(U32 mAdr)
{
	return FlsItm_adr_itemMe_start(mAdr, U_FLS_1HISTORY_BYTE_MAX);
}

U32 hist_adr_itemNext(U32 mAdr, TFlsItemAddr *pAdr)
{
	return FlsItm_adr_itemNext(mAdr, getFlsItem_hist(0), 
					U_FLS_1HISTORY_BYTE_MAX, pAdr);
}

U32 hist_adr_itemBefore(U32 mAdr, TFlsItemAddr *pAdr)
{
	return FlsItm_adr_itemBefore(mAdr, getFlsItem_hist(0), 
					U_FLS_1HISTORY_BYTE_MAX, pAdr);
}

U32 hist_adr_inSector(U32 mAdr)
{
	return FlsItm_adr_inSector(mAdr, getFlsItem_hist(0));
}

U32 hist_adr_inSect_histSequ(U32 mAdr)
{
	return FlsItm_adr_inSect_itmSequ(
				mAdr, getFlsItem_hist(0), U_FLS_1HISTORY_BYTE_MAX);
}

U32 hist_sector_LastItem_start(U32 mAdr)
{
	return FlsItm_adr_sector_LastItem(
				mAdr, getFlsItem_hist(0), U_FLS_1HISTORY_BYTE_MAX);
}

U32 hist_adr_sector_firItem(U32 mAdr)
{
	return FlsItm_adr_sector_firItem(
				mAdr, getFlsItem_hist(0), U_FLS_1HISTORY_BYTE_MAX);
	
}

U32 hist_sectorNext_start(U32 mAdr, TFlsItemAddr *pAdr)
{
	return FlsItm_sectorNext_start(
				mAdr, getFlsItem_hist(0), pAdr);
}

U32 hist_sectorBefore_start(U32 mAdr, TFlsItemAddr *pAdr)
{
	return FlsItm_sectorBefore_start(
				mAdr, getFlsItem_hist(0), pAdr);
}


/******************************************************************************
* FUNC: //
******************************************************************************/



/******************************************************************************
* FUNC: // END
*   IN:
*  OUT: 
******************************************************************************/
