#define __saveHistPoint_C__
/******************************************************************************
* @file    saveHistPoint.c
* @author  yx
* @version V1.0
* @date    2013-07-08
* @brief   保存历史记录的指针，历史记录每增加1sector保存一次。和powerOff一样处理。
* @master  historyWrite.c
* 
// U_SIGN_bHaveTested; 2013-07-10
******************************************************************************/
#include  "saveHistPoint.h"

#include  "phSaveHist_incIn.h"

//#include "incFile.h"	

#if U_SYS_Test_Flash_Hist == 1
	#include  "sim_saveHist.h"
#else // U_SYS_Test_Flash_Hist
#endif // U_SYS_Test_Flash_Hist


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
void FlsWr_HistPoint_Init(void)
{
	FlsWr_HistPoint_SetFinish();
}

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

BOOL FlsWr_HistPoint_New(U8 mHistCls, U8 mHistPart, 
					U8 mPointPart,
					TFlsQueuePoint_st  mStHistPoint)
{
	stHistPt.mHistCls = mHistCls;
	stHistPt.mFlsItem = getFlsItem_hstPoint(mHistCls, mHistPart);
	stHistPt.mPart = mPointPart;
	if(!getFlsItem_Addr(stHistPt.mFlsItem, mPointPart, &stHistPt.stAdr))
	{
		return FALSE;
	}
	
	
	ClrRamIsFF(&stHistPt.unNewAdr.byte[0], U_FLS_1HistPoint_BYTE_MAX); //全清FF
	
	stHistPt.unNewAdr.stPoint = mStHistPoint;
	
	stHistPt.unNewAdr.byte[U_FLS_1HistPoint_BYTE_MAX-1] = 
						(U8)(CacuCrcValue(&stHistPt.unNewAdr.byte[0], 
							(U_FLS_1HistPoint_BYTE_MAX-1)));
	
	
	stHistPt.bOpeaIng = TRUE;
	stHistPt.step = U_SaveHistPointStep_01_Start;
	return TRUE;
}



/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
BOOL bFlsWr_HistPoint_Finished(void)
{
	return LogicInverse(stHistPt.bOpeaIng);
}
BOOL bFlsWr_HistPoint_isIdle(void)
{
	return LogicInverse(stHistPt.bOpeaIng);
}

/******************************************************************************
* FUNC: //
******************************************************************************/

void FlsWr_HistPoint_SetFinish(void)
{
	stHistPt.bOpeaIng = FALSE;
	stHistPt.step = ~0;
}

/******************************************************************************
* FUNC: //写 sectorNext.head
******************************************************************************/
void flsWr_histPoint_SectorHead(void)
{
TFlsSecStart_un stSectHead;
U32 mAdrEnd;
U32 adr_sectS;
	
	ClrRamIsFF((U8 *)(&stSectHead), U_FLS_SectorStart_BYTES); //全清FF
	stSectHead.detail.byte_55 = 0x55;
	stSectHead.detail.mFlsItem = stHistPt.mFlsItem;
	
	stSectHead.byte[U_FLS_SectorStart_BYTES-1] = 
						(U8)(CacuCrcValue(&stSectHead.byte[0], 
							(U_FLS_SectorStart_BYTES-1)));
	
	
	mAdrEnd = GetFlsQueEndAdr(stHistPt.mFlsItem, stHistPt.mPart);
	adr_sectS = FlsItm_sector_start(mAdrEnd, stHistPt.mFlsItem);
	if(mAdrEnd != adr_sectS)
	{
		return;
	}
#if U_SYS_Test_Flash_Hist == 1
	sim_flash_Write_nByte(stHistPt.stAdr.chip, 
				&stSectHead.byte[0], U_FLS_SectorStart_BYTES, 
				mAdrEnd, 
				U_SYS_FLASH_OPEA_WAIT);
#else // U_SYS_Test_Flash_Hist
	FlsWr_Write_nByte_meIsEnd(stHistPt.stAdr.chip, 
				&stSectHead.byte[0], U_FLS_SectorStart_BYTES, 
				mAdrEnd
				);
#endif // U_SYS_Test_Flash_Hist

	mAdrEnd = FlsItm_adr_itemNext(
				mAdrEnd, stHistPt.mFlsItem, 
				U_FLS_1HistPoint_BYTE_MAX, 
				&stHistPt.stAdr
				);
	SetFlsQueEndAdr(stHistPt.mFlsItem, stHistPt.mPart, mAdrEnd);
}


/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

static void wrHp_Step_01_Start(void)
{
U32 adr_SectLastItem;
U32 adr_SectS;
U32 mAdrEnd;

    if(!getFlsItem_Addr(stHistPt.mFlsItem, stHistPt.mPart, &stHistPt.stAdr))
    {
        return;
    }
	stHistPt.bNeedEraseNextSector = FALSE;
	mAdrEnd = GetFlsQueEndAdr(stHistPt.mFlsItem, stHistPt.mPart);
	adr_SectLastItem = FlsItm_adr_sector_LastItem(
							mAdrEnd, stHistPt.mFlsItem, U_FLS_1HistPoint_BYTE_MAX);
	adr_SectS = FlsItm_sector_start(mAdrEnd, stHistPt.mFlsItem);
	
	
	if(mAdrEnd == adr_SectLastItem)
	{
		stHistPt.step = U_SaveHistPointStep_02_EraseNextSector;
		stHistPt.bNeedEraseNextSector = TRUE;
	}
	else if(mAdrEnd == adr_SectS)
	{
		stHistPt.step = U_SaveHistPointStep_03_WriteSectorHead;
	}
	else
	{
		stHistPt.step = U_SaveHistPointStep_04_WriteNew;
	}
	
}


static void wrHp_Step_02_EraseNextSector(void)
{
U32 mAdrHead;
U32 mAdrEnd;
U8 mFlsItem = stHistPt.mFlsItem;
	
	mAdrHead = GetFlsQueHeadAdr(mFlsItem, stHistPt.mPart);
	mAdrEnd = GetFlsQueEndAdr(mFlsItem, stHistPt.mPart);
	
	
	stHistPt.adrSectNext = FlsItm_sectorNext_start(
					mAdrEnd, mFlsItem, &stHistPt.stAdr
					);
#if U_SYS_Test_Flash_Hist == 1
	sim_flash_EraseSect_FromAdr(stHistPt.stAdr.chip, 
				stHistPt.adrSectNext, 
				U_SYS_FLASH_OPEA_WAIT);
#else // U_SYS_Test_Flash_Hist
	FlsHd_EraseSect_FromAdr(stHistPt.stAdr.chip, 
				stHistPt.adrSectNext, 
				U_SYS_FLASH_OPEA_WAIT);
#endif // U_SYS_Test_Flash_Hist
	
	if(mAdrHead == stHistPt.adrSectNext)
	{
		mAdrHead = FlsItm_sectorNext_start(
					stHistPt.adrSectNext, mFlsItem, &stHistPt.stAdr
					);
		SetFlsQueHeadAdr(mFlsItem, stHistPt.mPart, mAdrHead);
	}
	
	stHistPt.step = U_SaveHistPointStep_04_WriteNew;
}


static void wrHp_Step_04_WriteNew(void)
{
U32 mAdrEnd;
	
	mAdrEnd = GetFlsQueEndAdr(stHistPt.mFlsItem, stHistPt.mPart);

#if U_SYS_Test_Flash_Hist == 1
	sim_flash_Write_nByte(stHistPt.stAdr.chip, 
				&stHistPt.unNewAdr.byte[0], 
				U_FLS_1HistPoint_BYTE_MAX, 
				mAdrEnd, 
				U_SYS_FLASH_OPEA_WAIT
				);
#else // U_SYS_Test_Flash_Hist
	FlsWr_Write_nByte_meIsEnd(stHistPt.stAdr.chip, 
				&stHistPt.unNewAdr.byte[0], 
				U_FLS_1HistPoint_BYTE_MAX, 
				mAdrEnd
				);
#endif // U_SYS_Test_Flash_Hist
	mAdrEnd = FlsItm_adr_itemNext(
				mAdrEnd, stHistPt.mFlsItem, U_FLS_1HistPoint_BYTE_MAX, 
				&stHistPt.stAdr
				);
	SetFlsQueEndAdr(stHistPt.mFlsItem, stHistPt.mPart, mAdrEnd);
	
	if(stHistPt.bNeedEraseNextSector)
	{
		stHistPt.step = U_SaveHistPointStep_05_NextSectorHead;
	}
	else
	{
		stHistPt.step = U_SaveHistPointStep_06_Finish;
	}
}

static void wrHp_Step_03_WriteSectorHead(void)
{
	flsWr_histPoint_SectorHead();
	stHistPt.step = U_SaveHistPointStep_04_WriteNew;
}

static void wrHp_Step_05_NextSectorHead(void)
{
	flsWr_histPoint_SectorHead();
	stHistPt.step = U_SaveHistPointStep_06_Finish;
	
}



/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

void FlsWr_HistPoint_Exec(void)
{


	if(!stHistPt.bOpeaIng)
	{
		return;
	}
	
	switch(stHistPt.step)
	{
		case U_SaveHistPointStep_01_Start:
			wrHp_Step_01_Start();
			break;
			
			
		case U_SaveHistPointStep_02_EraseNextSector:
			wrHp_Step_02_EraseNextSector();
			break;
			
		case U_SaveHistPointStep_03_WriteSectorHead:
			wrHp_Step_03_WriteSectorHead();
			break;
			
		case U_SaveHistPointStep_04_WriteNew:
			wrHp_Step_04_WriteNew();
			break;
			
		case U_SaveHistPointStep_05_NextSectorHead:
			wrHp_Step_05_NextSectorHead();
			break;
			
		case U_SaveHistPointStep_06_Finish:
			Clr_FlsItemState(U_FlsItem_Space_State,
					stHistPt.mFlsItem, stHistPt.mPart);
			FlsWr_HistPoint_SetFinish();
			break;
			
		default:
			FlsWr_HistPoint_SetFinish();
			break;
			
	}
}


/******************************************************************************
* FUNC: // END
*   IN:
*  OUT: 
******************************************************************************/
