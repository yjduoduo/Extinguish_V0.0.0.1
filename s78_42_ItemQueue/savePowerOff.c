#define __savePowerOff_C__
/******************************************************************************
* @file    savePowerOff.c
* @author  yx
* @version V1.0
* @date    2013-07-08
* @brief   保存关机指针。
* @master  
* 
******************************************************************************/
#include  "savePowerOff.h"

#include  "saveItem_incIn.h"



#include  "historyWrBuf.h"
//#include "incFile.h"	



/*================= 常数 ============================================*/

/*================= 结构定义 ========================================*/

/*================= 私有结构变量声明 ================================*/

/*================= 公有函数声明 ====================================*/
/*================= 私有函数声明 ====================================*/

/*=================  ================================================*/


/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

BOOL FlsRd_PwrOff(TEvtClock_st  *pRtnClock)
{
TFlsQueuePoint_st stHeadEnd;
TFlsItemAddr stAdr;
U32 adr_sectorHead;
U32 adr;
U8 mPart;
TFlsPwrOff_un  *pPwrOff;
U8 *pBufS;
U8 mFlsItem = getFlsItem_PowerOff();
	
	for(mPart=0; mPart<FlsItem_PartMax(mFlsItem); mPart++)
	{
		if(!getFlsItem_Addr(mFlsItem, mPart, &stAdr))
		{
			continue;
		}
		if(!bFlsItem_IsReadAllow(mFlsItem, mPart))
		{
			continue;
		}
		
		GetFlsQueHeadEndAdr(mFlsItem, mPart, &stHeadEnd);
		if(stHeadEnd.headAdr == stHeadEnd.endAdr)
		{
			continue;
		}
		adr = stHeadEnd.endAdr;
		adr = FlsItm_adr_itemBefore(adr, mFlsItem, 
						U_FLS_1PowerOff_BYTE_MAX, &stAdr
						);
		adr_sectorHead = hist_sector_start(adr);
		if(adr == adr_sectorHead)
		{
			if(adr == stHeadEnd.headAdr)
			{
				continue;
			}
			adr = FlsItm_adr_itemBefore(adr, mFlsItem, 
						U_FLS_1PowerOff_BYTE_MAX, &stAdr
						);
		}
		pBufS = pFlsHd_GetBufS();
		FlsHd_Read_nByte(stAdr.chip, pBufS, 
					U_FLS_1PowerOff_BYTE_MAX, adr);
		if(!JdgCrcOK(pBufS, U_FLS_1PowerOff_BYTE_MAX))
		{
			continue;
		}
		
		pPwrOff = (TFlsPwrOff_un*)(pBufS);
		*pRtnClock = pPwrOff->stPwrOff.stClock;
		return TRUE;
	}
	
	return FALSE;
}

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
void FlsWr_pwrOff_Init(void)
{
	FlsWr_pwrOff_SetFinish();
	SavePwrOff_Tmr_Init();
}



/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
BOOL FlsWr_pwrOff_New(TEvtClock_st  *pStClock)
{
	stPwrOff.mFlsItem = getFlsItem_PowerOff();
	stPwrOff.mPart = U_FlsSave_Part0;
	if(!getFlsItem_Addr(stPwrOff.mFlsItem, stPwrOff.mPart, &stPwrOff.stAdr))
	{
		return FALSE;
	}
	
	
	ClrRamIsFF(&stPwrOff.unNewClock.byte[0], U_FLS_1PowerOff_BYTE_MAX); //全清FF
	
	stPwrOff.unNewClock.stPwrOff.stClock = *pStClock;
	
	stPwrOff.unNewClock.byte[U_FLS_1PowerOff_BYTE_MAX-1] = 
						(U8)(CacuCrcValue(&stPwrOff.unNewClock.byte[0], 
							(U_FLS_1PowerOff_BYTE_MAX-1)));
	
	
	stPwrOff.bOpeaIng = TRUE;
	stPwrOff.step = U_savePowerOffStep_01_Start;
	return TRUE;
}



/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
BOOL bFlsWr_pwrOff_Finished(void)
{
	return LogicInverse(stPwrOff.bOpeaIng);
}
BOOL bFlsWr_pwrOff_isIdle(void)
{
	return LogicInverse(stPwrOff.bOpeaIng);
}

/******************************************************************************
* FUNC: //
******************************************************************************/

void FlsWr_pwrOff_SetFinish(void)
{
	stPwrOff.bOpeaIng = FALSE;
	stPwrOff.step = ~0;
}

/******************************************************************************
* FUNC: //写 sectorNext.head
******************************************************************************/
static void flsWr_pwrOff_SectorHead(void)
{
TFlsSecStart_un stSectHead;
U32 mAdrEnd;
U32 adr_sectS;
	
	ClrRamIsFF((U8 *)(&stSectHead), U_FLS_SectorStart_BYTES); //全清FF
	stSectHead.detail.byte_55 = 0x55;
	stSectHead.detail.mFlsItem = stPwrOff.mFlsItem;
	
	stSectHead.byte[U_FLS_SectorStart_BYTES-1] = 
						(U8)(CacuCrcValue(&stSectHead.byte[0], 
							(U_FLS_SectorStart_BYTES-1)));
	
	
	mAdrEnd = GetFlsQueEndAdr(stPwrOff.mFlsItem, stPwrOff.mPart);
	adr_sectS = FlsItm_sector_start(mAdrEnd, stPwrOff.mFlsItem);
	if(mAdrEnd != adr_sectS)
	{
		return;
	}
	
	FlsWr_Write_nByte_meIsEnd(stPwrOff.stAdr.chip, 
				&stSectHead.byte[0], U_FLS_SectorStart_BYTES, 
				mAdrEnd
				);

	mAdrEnd = FlsItm_adr_itemNext(
				mAdrEnd, stPwrOff.mFlsItem, 
				U_FLS_1PowerOff_BYTE_MAX, 
				&stPwrOff.stAdr
				);
	SetFlsQueEndAdr(stPwrOff.mFlsItem, stPwrOff.mPart, mAdrEnd);
}


/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

static void wr_Step_01_Start(void)
{
U32 adr_SectLastItem;
U32 adr_SectS;
U32 mAdrEnd;

        //添加对两片芯片的操作，不然就对一个芯片进行操作了，针对有两份存储的内容
    if(!getFlsItem_Addr(stPwrOff.mFlsItem, stPwrOff.mPart, &stPwrOff.stAdr))
    {
        return;
    }

	stPwrOff.bNeedEraseNextSector = FALSE;
	mAdrEnd = GetFlsQueEndAdr(stPwrOff.mFlsItem, stPwrOff.mPart);
	adr_SectLastItem = FlsItm_adr_sector_LastItem(
							mAdrEnd, stPwrOff.mFlsItem, U_FLS_1PowerOff_BYTE_MAX);
	adr_SectS = FlsItm_sector_start(mAdrEnd, stPwrOff.mFlsItem);
	
	
	if(mAdrEnd == adr_SectLastItem)
	{
		stPwrOff.step = U_savePowerOffStep_02_EraseNextSector;
		stPwrOff.bNeedEraseNextSector = TRUE;
	}
	else if(mAdrEnd == adr_SectS)
	{
		stPwrOff.step = U_savePowerOffStep_03_WriteSectorHead;
	}
	else
	{
		stPwrOff.step = U_savePowerOffStep_04_WriteNew;
	}
	
}


static void wr_Step_02_EraseNextSector(void)
{
U32 mAdrHead;
U32 mAdrEnd;
U8 mFlsItem = stPwrOff.mFlsItem;
	
	mAdrHead = GetFlsQueHeadAdr(mFlsItem, stPwrOff.mPart);
	mAdrEnd = GetFlsQueEndAdr(mFlsItem, stPwrOff.mPart);
	
	
	stPwrOff.adrSectNext = FlsItm_sectorNext_start(
					mAdrEnd, mFlsItem, &stPwrOff.stAdr
					);
	
	FlsHd_EraseSect_FromAdr(stPwrOff.stAdr.chip, 
				stPwrOff.adrSectNext, 
				U_SYS_FLASH_OPEA_WAIT);
	
	if(mAdrHead == stPwrOff.adrSectNext)
	{
		mAdrHead = FlsItm_sectorNext_start(
					stPwrOff.adrSectNext, mFlsItem, &stPwrOff.stAdr
					);
		SetFlsQueHeadAdr(mFlsItem, stPwrOff.mPart, mAdrHead);
	}
	
	stPwrOff.step = U_savePowerOffStep_04_WriteNew;
}


static void wr_Step_04_WriteNew(void)
{
U32 mAdrEnd;
	
	mAdrEnd = GetFlsQueEndAdr(stPwrOff.mFlsItem, stPwrOff.mPart);

	FlsWr_Write_nByte_meIsEnd(stPwrOff.stAdr.chip, 
				&stPwrOff.unNewClock.byte[0], 
				U_FLS_1PowerOff_BYTE_MAX, 
				mAdrEnd
				);
	
	mAdrEnd = FlsItm_adr_itemNext(
				mAdrEnd, stPwrOff.mFlsItem, U_FLS_1PowerOff_BYTE_MAX, 
				&stPwrOff.stAdr
				);
	SetFlsQueEndAdr(stPwrOff.mFlsItem, stPwrOff.mPart, mAdrEnd);
	
	if(stPwrOff.bNeedEraseNextSector)
	{
		stPwrOff.step = U_savePowerOffStep_05_NextSectorHead;
	}
	else
	{
		stPwrOff.step = U_savePowerOffStep_06_PartNext;
	}
}

static void wr_Step_03_WriteSectorHead(void)
{
	flsWr_pwrOff_SectorHead();
	stPwrOff.step = U_savePowerOffStep_04_WriteNew;
}

static void wr_Step_05_NextSectorHead(void)
{
	flsWr_pwrOff_SectorHead();
	stPwrOff.step = U_savePowerOffStep_06_PartNext;
	
}

static void wr_Step_06_PartNext(void)
{
U8 mPartMax = 1;

	if(bFlsItem_HaveShare(getFlsItem_PowerOff()))
	{
		mPartMax = 2;
	}

	stPwrOff.mPart++;
	if(stPwrOff.mPart >= mPartMax)
	{
		stPwrOff.step = U_savePowerOffStep_07_Finish;
	}
	else
	{
		stPwrOff.step = U_savePowerOffStep_01_Start;
	}
	
	
}

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

void FlsWr_pwrOff_Exec(void)
{


	if(!stPwrOff.bOpeaIng)
	{
		return;
	}
	
	switch(stPwrOff.step)
	{
		case U_savePowerOffStep_01_Start:
			wr_Step_01_Start();
			break;
			
			
		case U_savePowerOffStep_02_EraseNextSector:
			wr_Step_02_EraseNextSector();
			break;
			
		case U_savePowerOffStep_03_WriteSectorHead:
			wr_Step_03_WriteSectorHead();
			break;
			
		case U_savePowerOffStep_04_WriteNew:
			wr_Step_04_WriteNew();
			break;
			
		case U_savePowerOffStep_05_NextSectorHead:
			wr_Step_05_NextSectorHead();
			break;
			
		case U_savePowerOffStep_06_PartNext:
			wr_Step_06_PartNext();
			break;
			
		case U_savePowerOffStep_07_Finish:
			Clr_FlsItemState(U_FlsItem_Space_State,
					getFlsItem_PowerOff(), U_FlsSave_Part0);
			Clr_FlsItemState(U_FlsItem_Space_State,
					getFlsItem_PowerOff(), FlsItem_PartMax(getFlsItem_PowerOff())-1);
			FlsWr_pwrOff_SetFinish();
			break;
			
		default:
			FlsWr_pwrOff_SetFinish();
			break;
			
	}
}


/******************************************************************************
* FUNC: // END
*   IN:
*  OUT: 
******************************************************************************/
