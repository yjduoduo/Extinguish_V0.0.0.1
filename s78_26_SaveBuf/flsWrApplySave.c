#define __flsWrApplySave_C__
/******************************************************************************
* @file    flsWrApplySave.c
* @author  yx
* @version V1.0
* @date    2013-07-23
* @brief   写flash管理。都是定地址存储。
		读在[PeriphSave] saveX.c里。

* 新task -> buf[] ： FlashSaveNew();
* buf[] -> 写flash:  FlsSave_Start();

******************************************************************************/
#include  "flsWrApplySave.h"

#include  "SaveTask_incIn.h"
#include  "flsWrApplyBuf.h"


#include  "saveNote.h"
#include  "saveExtgZoneConfig.h"
#include  "saveLinkProg.h"
#include  "saveHistory.h"
#include  "flsWrite.h"
#include  "saveMeStatus.h"
#include  "savePnConfig.h"
#include  "saveNetMachine.h"
#include  "saveField.h"
#include  "saveRelateAddr.h"
#include  "saveDisable.h"

extern void FlsResultNotificat(U8 taskId, U8 mFlsId, U8 bSucc);

//#include "incFile.h"



/*================= 常数 ============================================*/

/*================= 结构定义 ========================================*/

/*================= 私有结构变量声明 ================================*/
#define U_FlsWr_1Page_BYTE_MAX  (U_FLASH_1_PAGE + U_FLS_SectorStart_BYTES)
static U8 		vFlsWr_1Page[U_FlsWr_1Page_BYTE_MAX];
static U8 		vFlsRd_1Page[U_FlsWr_1Page_BYTE_MAX];
static TFlsAlyOneHead_un  vFileHead; //文件信息

/*================= 公有函数声明 ====================================*/

/*================= 私有函数声明 ====================================*/


/*=================  ================================================*/
		

/******************************************************************************
* FUNC: // "saveManage.c" 里 emSave_Opea_Item类，判断if有任务：
*   IN:
*  OUT: FALSE = 空。
******************************************************************************/
BOOL FlsSave_Start(void)
{

	if(bFlsWr_AlyBuf_Empty())
	{
		return FALSE;
	}
	if(!FlsWr_AlyBuf_Read(
				&vFlsWr_1Page[U_FLS_SectorStart_BYTES], 
				&vFileHead))
	{
		return FALSE;
	}
	
	stSave.PartMax = 1;
	stSave.bHavePart2 = FALSE;
	if(bFlsItem_HaveShare(vFileHead.head.mFlsItem))
	{
		stSave.PartMax = 2;
		stSave.bHavePart2 = TRUE;
	}
	
	stSave.step = U_FlsWrApplyStep_01_Start;
	stSave.mPart = 0;
	
	stSave.bSucc = FALSE;
	
	// FlsSave_Exec(); 等1循环再进行操作，给任务留空。
	return TRUE;
}

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
void FlsSave_Exec(void)
{
	if(bFlsSave_isIdle())
	{
		return;
	}
	
	switch(stSave.step)
	{
		case U_FlsWrApplyStep_01_Start:
			fls_step_Start();
			fls_step_Part();
			break;
			
		case U_FlsWrApplyStep_02_Part0:
			fls_step_Part();
			break;
			
		case U_FlsWrApplyStep_03_Part1:
			fls_step_Part();
			break;
			
		case U_FlsWrApplyStep_04_Read:
			flsSave_flsItem(U_READ);
			stSave.step = U_FlsWrApplyStep_05_Notify;
			fls_step_Notify();
			break;
			
		case U_FlsWrApplyStep_05_Notify:
			fls_step_Notify();
			break;
			
		default:
			flsSave_SetIdle();
			break;
		
	}
	
}

/******************************************************************************
* FUNC: //
******************************************************************************/

static void fls_step_Start(void)
{
TFlsSecStart_un *pFlsSecStart;
if(bFlsItemIs_Disable(vFileHead.head.mFlsItem)){
	pFlsSecStart = (TFlsSecStart_un*)(&vFlsWr_1Page[0]);
		Init_StrFlsSectStart(vFileHead.head.mFlsItem, pFlsSecStart);
		return;

}

	if(!bFlsItemIs_OnePageSave(vFileHead.head.mFlsItem))
	{
		return;
	}
	pFlsSecStart = (TFlsSecStart_un*)(&vFlsWr_1Page[0]);
	Init_StrFlsSectStart(vFileHead.head.mFlsItem, pFlsSecStart);
	// U_FLS_SectorStart_BYTES
	
	stSave.mPart = 0;
	stSave.step = U_FlsWrApplyStep_02_Part0;
}

/******************************************************************************
* FUNC: //
******************************************************************************/

static void fls_step_Part(void)
{
	flsSave_flsItem(U_WRITE);
	
	stSave.mPart++;
	if(stSave.mPart >= stSave.PartMax)
	{
		stSave.step = U_FlsWrApplyStep_04_Read;
	}
	else
	{
		stSave.step = U_FlsWrApplyStep_03_Part1;
		// if(stSave.bHavePart2)
	}
	
}



/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
static void fls_step_Notify(void)
{
	
	fls_step_Notif_ReNewRam();
	
	fls_step_Notif_ReNewState();
	
	
	
	saveFlsItm_NotificatResult(stSave.bSucc);
	flsSave_SetIdle();
}

/******************************************************************************
* FUNC: //
******************************************************************************/

static void fls_step_Notif_ReNewState(void)
{
U8 mFlsItem;
U8 mPart;

	mFlsItem = vFileHead.head.mFlsItem;
	
	if(stSave.bSucc)
	{
		// emFlsItem :
		if(bFlsItemIs_OnePageSave(mFlsItem))
		{
			for(mPart=0; mPart<FlsItem_PartMax(mFlsItem); mPart++)
			{
				Clr_FlsItemState(U_FlsItem_Space_State,mFlsItem, mPart);
				Clr_FlsItemState(U_FlsItem_Error_State,mFlsItem, mPart);
			}
		}
		else if(  getFlsItem_Disable()
			   || getFlsItem_Field()
			   || getFlsItem_LinkProg()
			   || getFlsItem_ManuProg()
			   || getFlsItem_Note()
			   )
		{
			return;
		}
		
	}
}


/******************************************************************************
* FUNC: //
******************************************************************************/

static void fls_step_Notif_ReNewRam(void)
{
U8 mFlsItem = vFileHead.head.mFlsItem;

	if(stSave.bSucc)
	{
		// emFlsItem :
		if(mFlsItem == getFlsItem_MeStatus())
		{
			FlsRd_MeStatus();
		}
		else if(mFlsItem == getFlsItem_PnConfig())
		{
			FlsRd_PnConfig();
		}
		else if(mFlsItem == getFlsItem_NetMachine())
		{
			FlsRd_NetMachine();
		}
		
		
		else if(mFlsItem == getFlsItem_MachProbat())
		{}
		else if(mFlsItem == getFlsItem_UserLogin())
		{}
		
		else if(mFlsItem == getFlsItem_Disable())
		{}
		else if(mFlsItem == getFlsItem_Field())
		{}
		else if(mFlsItem == getFlsItem_LinkProg())
		{}
		else if(mFlsItem == getFlsItem_ManuProg())
		{}
		else if(mFlsItem == getFlsItem_Note())
		{}
		
		
	}
}


/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
void FlsSave_Init(void)
{
	flsSave_SetIdle();
	Init_FlsApplyBuf();
}

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
BOOL bFlsSave_isIdle(void)
{
	return (stSave.step >= U_FlsWrApplyStep_MAX);
}

static void flsSave_SetIdle(void)
{
	stSave.step = ~0;
	stSave.mPart = 0;
}

/******************************************************************************
* FUNC: //
*   IN: vFileHead, vFlsWr_1Page[] ;
*  OUT: 
******************************************************************************/

static void flsItm_OnePageCls_SaveOrRead(U8 mReadWrite)
{
	if(mReadWrite == U_WRITE)
	{
		saveFlsItm_OnePageCls();
	}
	else //U_READ
	{
		rdFlsItm_OnePageCls();
	}
}

static BOOL saveFlsItm_OnePageCls(void)
{
U8 chip;
U32 mAdrS;
U32 num;
U8 crc;

	// num = sector head + 结构体字节。
	flsItm_onePageCls_cacuAdr(stSave.mPart, &chip, &mAdrS, &num);
	if(num > U_FLASH_1_PAGE)
	{
		return FALSE;
	}
	if(stSave.mPart == 0) // 只计算一次就可以了，part1的计算结果是相同的。
	{
		crc = CacuCrcValue(&vFlsWr_1Page[U_FLS_SectorStart_BYTES], 
						vFileHead.head.strFlsItemBytes - 1);
		vFlsWr_1Page[num-1] = crc;
	}
	
	// write flash:	
	FlsWr_Write_nByte_meIsEnd(chip, &vFlsWr_1Page[0], num, mAdrS);
	return TRUE;
	
}

//OUT: stSave.bSucc
static BOOL rdFlsItm_OnePageCls(void)
{
U8 chip;
U32 mAdrS;
U32 num;
U8 mPart;
U8 bSucc;

	bSucc = 0;
	for(mPart=0; mPart<stSave.PartMax; mPart++)
	{
		flsItm_onePageCls_cacuAdr(mPart, &chip, &mAdrS, &num);	
		FlsHd_Read_nByte(chip, &vFlsRd_1Page[0], num, mAdrS);
		if(bCompareByte(&vFlsWr_1Page[0], &vFlsRd_1Page[0], num))
		{
			bSucc |= (1 << mPart);
		}
	}
	
	stSave.bSucc = bSucc;
	
	return bSucc;
}

// num = sector head + 结构体字节。
static void flsItm_onePageCls_cacuAdr(U8 mPart, U8 *pChip, U32 *pAdr, U32 *pNum)
{
U8 mFlsItem; 
	
	mFlsItem = vFileHead.head.mFlsItem;
	*pChip = getFlsItem_Chip(mFlsItem, mPart);
	*pAdr =getFlsItem_AdrS(mFlsItem, mPart);
	
	*pNum = vFileHead.head.strFlsItemBytes;
	*pNum += U_FLS_SectorStart_BYTES;
}

/******************************************************************************
* FUNC: // 写注释
*   IN: vFileHead, vFlsWr_1Page[] ;
*  OUT: 
******************************************************************************/

static void flsItm_Note_SaveOrRead(U8 mReadWrite)
{
	if(mReadWrite == U_WRITE)
	{
		saveFlsItm_Note();
	}
	else //U_READ
	{
		rdFlsItm_Note();
	}
}

static BOOL saveFlsItm_Note(void)
{
TFlsNote_st *pNote;
U8 chip;
U32 mAdrS;
	
	pNote = (TFlsNote_st*)(&vFlsWr_1Page[U_FLS_SectorStart_BYTES]);
	if(!flsItm_Note_cacuAdr(stSave.mPart, &chip, &mAdrS))
	{
		return FALSE;
	}
	
	FlsWr_Write_nByte(chip,&pNote->note[0], 
					U_FLS_NOTE_BYTE_MAX, mAdrS);
	return TRUE;
}

static BOOL rdFlsItm_Note(void)
{
TFlsNote_st *pNote0;
TFlsNote_st *pNote1;
U8 chip;
U32 mAdrS;
U8 mPart;
BOOL bSucc;


	pNote0 = (TFlsNote_st*)(&vFlsWr_1Page[U_FLS_SectorStart_BYTES]);
	pNote1 = (TFlsNote_st*)(&vFlsRd_1Page[U_FLS_SectorStart_BYTES \
							+ U_FLS_NOTE_BYTE_MAX]);
	
	bSucc = 0;
	for(mPart=0; mPart<stSave.PartMax; mPart++)
	{
		if(!flsItm_Note_cacuAdr(mPart, &chip, &mAdrS))
		{
			continue;
		}
		FlsHd_Read_nByte(chip, &pNote1->note[0], 
							U_FLS_NOTE_BYTE_MAX, mAdrS);
		if(bCompareByte(&pNote0->note[0], &pNote1->note[0], 
							U_FLS_NOTE_BYTE_MAX))
		{
			bSucc |= (1 << mPart);
		}
	}
	
	stSave.bSucc = bSucc;
	
	return bSucc;
}

static BOOL flsItm_Note_cacuAdr(U8 mPart, U8 *pChip, U32 *pAdr)
{
U32 mOffset;
TFlsNote_st *pNote;
TFlsItemAddr stAdr;
U32 adr;
	
	pNote = (TFlsNote_st*)(&vFlsWr_1Page[U_FLS_SectorStart_BYTES]);
	
	if(!GetFlsOffsetAdr_Note_Wr(&pNote->stDev, &mOffset))
	{
		return FALSE;
	}
	
	if(!getFlsItem_Addr(getFlsItem_Note(), mPart, &stAdr))
	{
		return FALSE;
	}
	adr = stAdr.adrS + mOffset;
	if(adr >= stAdr.adrE)
	{
		return FALSE;
	}
	*pChip = stAdr.chip;
	*pAdr = stAdr.adrS + mOffset;
	
	return TRUE;
}




/******************************************************************************
* FUNC: // 写联动编程
*   IN: vFileHead, vFlsWr_1Page[] ;
*  OUT: 
******************************************************************************/

static void flsItm_LinkProg_SaveOrRead(U8 mReadWrite)
{
	if(mReadWrite == U_WRITE)
	{
		saveFlsItm_LinkProg();
	}
	else //U_READ
	{
		rdFlsItm_LinkProg();
	}
}

static BOOL saveFlsItm_LinkProg(void)
{
TFlsLinkProg_st *pProg;
U8 chip;
U32 mAdrS;
	
	pProg = (TFlsLinkProg_st*)(&vFlsWr_1Page[U_FLS_SectorStart_BYTES]);
	if(!flsItm_LinkProg_cacuAdr(stSave.mPart, &chip, &mAdrS))
	{
		return FALSE;
	}
	
	FlsWr_Write_nByte(chip,&pProg->byte[0], 
					U_FLS_LINK_PROG_BYTE_MAX, mAdrS);
	return TRUE;
}



static BOOL rdFlsItm_LinkProg(void)
{
TFlsLinkProg_st *pProg0;
TFlsLinkProg_st *pProg1;
U8 chip;
U32 mAdrS;
U8 mPart;
BOOL bSucc;


	pProg0 = (TFlsLinkProg_st*)(&vFlsWr_1Page[U_FLS_SectorStart_BYTES]);
	pProg1 = (TFlsLinkProg_st*)(&vFlsRd_1Page[U_FLS_SectorStart_BYTES]);
	
	bSucc = 0;
	for(mPart=0; mPart<stSave.PartMax; mPart++)
	{
		if(!flsItm_LinkProg_cacuAdr(mPart, &chip, &mAdrS))
		{
			continue;
		}
		FlsHd_Read_nByte(chip, &pProg1->byte[0], U_FLS_LINK_PROG_BYTE_MAX, mAdrS);
		if(bCompareByte(&pProg0->byte[0], &pProg1->byte[0], U_FLS_LINK_PROG_BYTE_MAX))
		{
			bSucc |= (1 << mPart);
		}
	}
	
	stSave.bSucc = bSucc;
	
	return bSucc;

}

static BOOL flsItm_LinkProg_cacuAdr(U8 mPart, U8 *pChip, U32 *pAdr)
{
U32 mOffset;
TFlsLinkProg_st *pProg;
TFlsItemAddr stAdr;
U32 adr;
	
	pProg = (TFlsLinkProg_st*)(&vFlsWr_1Page[U_FLS_SectorStart_BYTES]);
	
	if(!CacuFlsOffsetAdr_LinkProg(&pProg->stDev, &mOffset))
	{
		return FALSE;
	}
	
	if(!getFlsItem_Addr(getFlsItem_LinkProg(), mPart, &stAdr))
	{
		return FALSE;
	}
	adr = stAdr.adrS + mOffset;
	if(adr >= stAdr.adrE)
	{
		return FALSE;
	}
	*pChip = stAdr.chip;
	*pAdr = stAdr.adrS + mOffset;
	
	return TRUE;
}

/******************************************************************************
* FUNC: // 回路现场部件
*   IN: vFileHead, vFlsWr_1Page[] ;
*  OUT: 
******************************************************************************/

static void flsItm_Field_SaveOrRead(U8 mReadWrite)
{
	if(mReadWrite == U_WRITE)
	{
		saveFlsItm_Field();
	}
	else //U_READ
	{
		rdFlsItm_Field();
	}
	
}

static BOOL saveFlsItm_Field(void)
{
U8 chip;
U32 mAdrS;
U32 mRamOffset;
U8 mNeedGetAddrNum;
U32 mRegiByteMax;
TFlsFieldHead_st *pFieldHead;
	
	if(!flsItm_Field_cacuAdr(stSave.mPart, &chip, &mAdrS))
	{
		return FALSE;
	}

	pFieldHead = (TFlsFieldHead_st*)(&vFlsWr_1Page[U_FLS_SectorStart_BYTES]);
	
	mRamOffset = U_FLS_SectorStart_BYTES + U_FLS_Field_Head_BYTE_MAX;
	
	mNeedGetAddrNum = (pFieldHead->mAddrE - pFieldHead->mAddrS);
	mRegiByteMax = (mNeedGetAddrNum * U_FLS_Field_1Addr_BYTE_MAX);
	
	FlsWr_Write_nByte(chip,
					&vFlsWr_1Page[mRamOffset], 
					mRegiByteMax, 
					mAdrS);
	return TRUE;
	
}

static BOOL rdFlsItm_Field(void)
{
U8 chip;
U32 mAdrS;
U8 mPart;
BOOL bSucc;
U8 *pByteWr;
U8 *pByteRd;
U32 mRamOffset;
U8 mNeedGetAddrNum;
U32 mRegiByteMax;
TFlsFieldHead_st *pFieldHead;
	
	mRamOffset = U_FLS_SectorStart_BYTES + U_FLS_Field_Head_BYTE_MAX;
	pByteWr = (&vFlsWr_1Page[mRamOffset]);
	pByteRd = (&vFlsRd_1Page[mRamOffset]);
	
	pFieldHead = (TFlsFieldHead_st*)(&vFlsWr_1Page[U_FLS_SectorStart_BYTES]);
	
	mNeedGetAddrNum = (pFieldHead->mAddrE - pFieldHead->mAddrS);
	mRegiByteMax = (mNeedGetAddrNum * U_FLS_Field_1Addr_BYTE_MAX);
	
	
	bSucc = 0;
	for(mPart=0; mPart<stSave.PartMax; mPart++)
	{
		if(!flsItm_Field_cacuAdr(mPart, &chip, &mAdrS))
		{
			continue;
		}
		FlsHd_Read_nByte(chip, pByteRd, mRegiByteMax, mAdrS);
		if(bCompareByte(pByteRd, pByteWr, mRegiByteMax))
		{
			bSucc |= (1 << mPart);
		}
	}
	
	stSave.bSucc = bSucc;
	
	return bSucc;
	
}

static BOOL flsItm_Field_cacuAdr(U8 mPart, U8 *pChip, U32 *pAdr)
{
U32 mOffset;
TFlsFieldHead_st *pFieldHead;
TFlsItemAddr stAdr;
U32 adr;

	pFieldHead = (TFlsFieldHead_st*)(&vFlsWr_1Page[U_FLS_SectorStart_BYTES]);
	
	if(!GetFlsOffsetAdr_Field(pFieldHead->mLoop, pFieldHead->mAddrS, 
										&mOffset))
	{
		return FALSE;
	}
	
	if(!getFlsItem_Addr(getFlsItem_Field(), mPart, &stAdr))
	{
		return FALSE;
	}
	adr = stAdr.adrS + mOffset;
	if(adr >= stAdr.adrE)
	{
		return FALSE;
	}
	*pChip = stAdr.chip;
	*pAdr = stAdr.adrS + mOffset;
	
	return TRUE;
}


/******************************************************************************
* FUNC: // 相关地址
*   IN: vFileHead, vFlsWr_1Page[] ;
*  OUT: 
******************************************************************************/

static void flsItm_RelateAddr_SaveOrRead(U8 mReadWrite)
{
	if(mReadWrite == U_WRITE)
	{
		saveFlsItm_RelateAddr();
	}
	else //U_READ
	{
		rdFlsItm_RelateAddr();
	}
	
}

static BOOL saveFlsItm_RelateAddr(void)
{
TFlsItemAddr stAdr;
TFlsRelateDeteHead_st *pRelateHead;
TFlsRelateDeteOne_st *pOne;
U32 mFlsAdr;
U8 mFlsItem = vFileHead.head.mFlsItem;
U8 *pBufS;
U32 m1SectorByte = getFlsItem_1SectorBytes(mFlsItem);


	pRelateHead = (TFlsRelateDeteHead_st*) \
				(&vFlsWr_1Page[U_FLS_SectorStart_BYTES]);
	pOne = (TFlsRelateDeteOne_st*) \
				(&vFlsWr_1Page[U_FLS_SectorStart_BYTES \
							+ U_FLS_RelateDete_Head_BYTE_MAX]);
	
	if(!getFlsItem_Addr(mFlsItem, stSave.mPart, &stAdr))
	{
		return FALSE;
	}

	if(bFlsRelateDete_FoundEquMachineLoopSector( 
				&pOne->stDev, stSave.mPart, &mFlsAdr))
	{
	}
	else
	{
		if((pRelateHead->mOpeaCls == emFlsRelatDeteOpea_ClrOne)
		  ||(pRelateHead->mOpeaCls == emFlsRelatDeteOpea_Clr1Loop))
		{
			return TRUE;
		}
		if(!bFlsRelateDete_FoundSpaceSector(
							stSave.mPart, &mFlsAdr))
		{
			return FALSE;
		}
	}
	mFlsAdr = FlsItm_sector_start(mFlsAdr, mFlsItem);
	pBufS = pFlsHd_GetBufS();
	FlsHd_Read_nByte(stAdr.chip, pBufS, 
					m1SectorByte, mFlsAdr);
	
	FlsRelateDete_RamChange(pBufS, pRelateHead, pOne);
		
	FlsWr_Write_nByte(stAdr.chip, pBufS,
					m1SectorByte, mFlsAdr);
	
	return TRUE;
}

static BOOL rdFlsItm_RelateAddr(void)
{
	
TFlsItemAddr stAdr;
TFlsRelateDeteHead_st *pRelateHead;
TFlsRelateDeteOne_st *pOne;
U32 mFlsAdr;
U8 mFlsItem = vFileHead.head.mFlsItem;
U8 *pBufS;
U32 m1SectorByte = getFlsItem_1SectorBytes(mFlsItem);
U8 bSucc;
U8 mPart;


	pRelateHead = (TFlsRelateDeteHead_st*) \
				(&vFlsWr_1Page[U_FLS_SectorStart_BYTES]);
	pOne = (TFlsRelateDeteOne_st*) \
				(&vFlsWr_1Page[U_FLS_SectorStart_BYTES \
							+ U_FLS_RelateDete_Head_BYTE_MAX]);
	
	bSucc = 0;
	for(mPart=0; mPart<stSave.PartMax; mPart++)
	{
		if(!getFlsItem_Addr(mFlsItem, mPart, &stAdr))
		{
			return FALSE;
		}
		
		switch(pRelateHead->mOpeaCls)
		{
		case emFlsRelatDeteOpea_Clr1Loop:
			if(!bFlsRelateDete_FoundEquMachineLoopSector( 
					&pOne->stDev, stSave.mPart, &mFlsAdr))
			{
				bSucc |= (1 << mPart);
			}
			break;
			
		case emFlsRelatDeteOpea_ClrOne:
			if(bFlsRelateDete_FoundEquMachineLoopSector( 
					&pOne->stDev, stSave.mPart, &mFlsAdr))
			{
				mFlsAdr = FlsItm_sector_start(mFlsAdr, mFlsItem);
				pBufS = pFlsHd_GetBufS();
				FlsHd_Read_nByte(stAdr.chip, pBufS, 
								getFlsItem_1SectorBytes(mFlsItem), 
								mFlsAdr);
				// 在RAM里判断，判断某dete已删除：
				if(bJdgInRam_FlsRelateDete_HaveClr(pBufS, pOne))
				{
					bSucc |= (1 << mPart);
				}
			}
			else
			{
				bSucc |= (1 << mPart);
			}
			break;

		case emFlsRelatDeteOpea_ChangeRelate:
		case emFlsRelatDeteOpea_ChangeNote:
		case emFlsRelatDeteOpea_ChangeAll:
			if(bFlsRelateDete_FoundEquMachineLoopSector( 
					&pOne->stDev, stSave.mPart, &mFlsAdr))
			{
				mFlsAdr = FlsItm_sector_start(mFlsAdr, mFlsItem);
				pBufS = pFlsHd_GetBufS();
				FlsHd_Read_nByte(stAdr.chip, pBufS, 
								getFlsItem_1SectorBytes(mFlsItem), 
								mFlsAdr);
				
				if(bJdgInRam_FlsRelateDete_EquSet(pBufS, 
								pRelateHead, pOne))
				{
					bSucc |= (1 << mPart);
				}
			}
			break;
			
		default:
			break;
			
		}
	}

	
	stSave.bSucc = bSucc;
	
	return bSucc;
}



/******************************************************************************
* FUNC: // 屏蔽
*   IN: vFileHead, vFlsWr_1Page[] ;
*  OUT: 
******************************************************************************/

static void flsItm_Disable_SaveOrRead(U8 mReadWrite)
{
	if(mReadWrite == U_WRITE)
	{
		saveFlsItm_Disable();
	}
	else //U_READ
	{
		rdFlsItm_Disable();
	}
	
}

static BOOL saveFlsItm_Disable(void)
{
TFlsItemAddr stAdr;
U8 mFlsItem = vFileHead.head.mFlsItem;
U32 m1SectorByte = getFlsItem_1SectorBytes(mFlsItem);
U8 *pBufS;
TFlsDisable_un *pDsabOne;
	
	pDsabOne = (TFlsDisable_un*)(&vFlsWr_1Page[U_FLS_SectorStart_BYTES]);
	
	if(!getFlsItem_Addr(mFlsItem, stSave.mPart, &stAdr))
	{
		return FALSE;
	}
	pBufS = pFlsHd_GetBufS();
	FlsHd_Read_nByte(stAdr.chip, pBufS, 
					m1SectorByte, stAdr.adrS);
	
	if(!FlsDisable_RamChange(pBufS, pDsabOne))
	{
		return FALSE;
	}
	FlsWr_Write_nByte(stAdr.chip, pBufS,
					m1SectorByte, 
					stAdr.adrS);
	return TRUE;
}

static BOOL rdFlsItm_Disable(void)
{
TFlsItemAddr stAdr;
U8 mFlsItem = vFileHead.head.mFlsItem;
U32 m1SectorByte = getFlsItem_1SectorBytes(mFlsItem);
U8 *pBufS;
TFlsDisable_un *pDsabOne;
U32 mOffsetAdr;
U8 bSucc;
U8 mPart;
	
	pDsabOne = (TFlsDisable_un*)(&vFlsWr_1Page[U_FLS_SectorStart_BYTES]);
	
	bSucc = 0;
	for(mPart=0; mPart<stSave.PartMax; mPart++)
	{
		if(!getFlsItem_Addr(mFlsItem, mPart, &stAdr))
		{
			return FALSE;
		}
		pBufS = pFlsHd_GetBufS();
		FlsHd_Read_nByte(stAdr.chip, pBufS, 
						m1SectorByte, stAdr.adrS);
		
		if(pDsabOne->stDisable.bAdd)
		{
			if(bFoundInRam_Dsab_EquDete(
							&pDsabOne->stDisable.stDev, 
							pBufS, 0, &mOffsetAdr))
			{
				bSucc |= (1 << mPart);
			}
		}
		else
		{
			if(!bFoundInRam_Dsab_EquDete(
							&pDsabOne->stDisable.stDev, 
							pBufS, 0, &mOffsetAdr))
			{
				bSucc |= (1 << mPart);
			}
		}
	}
	
	stSave.bSucc = bSucc;
	
	return bSucc;
}


/******************************************************************************
* FUNC: // 通知各task
*   IN: vFileHead
*  OUT: 
flsErase_NotificatResult();
******************************************************************************/

static void saveFlsItm_NotificatResult(U8 bSucc)
{
	FlsResultNotificat(vFileHead.head.taskId, 
					  vFileHead.head.flsId,
					  bSucc);
	
}

/******************************************************************************
* FUNC: // flash写的任务。
		注意flash一个命令执行完毕直至 BUSY=0才退出。
*   IN:  	(bSaveItemValid(mFlsItem))
		taskId < U_SYS_TASK_ID_MAX
		flsId
		pSrc ->  TFlsSysSet_un ...
*  OUT: U_SUCC

历史记录因数据量大，且优先级低，不在这里处理。 historyWrBuf

******************************************************************************/

BOOL FlashSaveNew(U8 mFlsItem, U8 taskId, U8 flsId, U8 *pSrc)
{
#if U_FLASH_TASK_WAIT == FALSE
	return FlsWr_AlyBuf_NewApply(mFlsItem, taskId, flsId, pSrc);

#else  // U_FLASH_TASK_WAIT

	if(!FlsWr_AlyBuf_NewApply(mFlsItem, taskId, flsId, pSrc))
		return FALSE;

	return bWaitForFlsOpeaFinish(flsId);
	
#endif // U_FLASH_TASK_WAIT
}

/******************************************************************************
* FUNC: //
******************************************************************************/


/******************************************************************************
* FUNC: // 
*   IN:
*  OUT: 

typedef union{ 
	U8 byte[U_FLS_1HISTORY_BYTE_MAX];
	struct{
		TDev_un unDev; 
		U8 type; //设备类型
		U8 thingFir;
		U8 thingSec;
		TEvtClock_st stClock;		
	}stHist;
}THisory_un; //需要存历史的struct.


typedef union{ 
	U8 byte[U_FLS_1PowerOff_BYTE_MAX];
	struct{
		TEvtClock_st stClock;		
	}stPwrOff;
}TFlsPwrOff_un; //

DevSet_all_test1234567(1, &stTestEvtWin.stAlarm[1].stPos.unDev);

	Clock_all_test12345(0x10, &stTestEvtWin.stAlarm[1].evtClock);

******************************************************************************/
#if U_SYS_Test_FlsApplyBuf == 1
static THisory_un  		unHist;
static TFlsPwrOff_un  unPwrOff;
static TFlsSecStart_un *pFlsSecStart;
static THisory_un  	*pHist;
static TFlsPwrOff_un   *pPwrOff;


void Sim_FlsApplyBuf(void)
{
U8 ii;
U8 addNum = 1;

	
	Init_FlsApplyBuf();
	for(ii=0; ii<10; ii++)
	{
		DevSet_all_test1234567(addNum, &unHist.stHist.unDev);
		unHist.stHist.type = addNum;
		unHist.stHist.thingFir = addNum;
		unHist.stHist.thingSec = addNum;
		Clock_all_test12345(addNum, &unHist.stHist.stClock);
		
		FlashSaveNew(getFlsItem_hist(0), 
					addNum, (U8*)(&unHist));
		addNum++;
		
		
		Clock_all_test12345(addNum, &unPwrOff.stPwrOff.stClock);
		FlashSaveNew(getFlsItem_PowerOff(), 
					addNum, (U8*)(&unPwrOff));
		addNum++;
		
	}
	
	for(ii=0; ii<10; ii++)
	{
		FlsSave_Start();
		pFlsSecStart = (TFlsSecStart_un*)(&vFlsWr_1Page[0]);
		
		if(vFileHead.head.mFlsItem == getFlsItem_hist(0))
		{
			pHist = (THisory_un*)(&vFlsWr_1Page[U_FLS_SectorStart_BYTES]);
		}
		else if(vFileHead.head.mFlsItem == getFlsItem_PowerOff())
		{
			pPwrOff = (TFlsPwrOff_un*)(&vFlsWr_1Page[U_FLS_SectorStart_BYTES]);
			
		}
	}
	
	
	
	
	for(ii=0; ii<10; ii++)
	{
		DevSet_all_test1234567(addNum, &unHist.stHist.unDev);
		unHist.stHist.type = addNum;
		unHist.stHist.thingFir = addNum;
		unHist.stHist.thingSec = addNum;
		Clock_all_test12345(addNum, &unHist.stHist.stClock);
		
		FlashSaveNew(getFlsItem_hist(0), 
					addNum, (U8*)(&unHist));
		addNum++;
		
		
		Clock_all_test12345(addNum, &unPwrOff.stPwrOff.stClock);
		FlashSaveNew(getFlsItem_PowerOff(), 
					addNum, (U8*)(&unPwrOff));
		addNum++;
		
	}
	for(ii=0; ii<10; ii++)
	{
		FlsSave_Start();
		pFlsSecStart = (TFlsSecStart_un*)(&vFlsWr_1Page[0]);
		
		if(vFileHead.head.mFlsItem == getFlsItem_hist(0))
		{
			pHist = (THisory_un*)(&vFlsWr_1Page[U_FLS_SectorStart_BYTES]);
		}
		else if(vFileHead.head.mFlsItem == getFlsItem_PowerOff())
		{
			pPwrOff = (TFlsPwrOff_un*)(&vFlsWr_1Page[U_FLS_SectorStart_BYTES]);
			
		}
		
	}
}

#endif // U_SYS_Test_FlsApplyBuf


/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 

* 已做成在等待BUSY=0期间，允许其他task exec.
******************************************************************************/

static void flsSave_flsItem(U8 mReadWrite)
{
U8 mFlsItem;
	
// emFlsItem :
	mFlsItem = vFileHead.head.mFlsItem;
	
	if(bFlsItemIs_OnePageSave(mFlsItem))
	{
		flsItm_OnePageCls_SaveOrRead(mReadWrite);
	}
	
	else if(mFlsItem == getFlsItem_Field())
	{
		flsItm_Field_SaveOrRead(mReadWrite);
	}
	
	else if(mFlsItem == getFlsItem_LinkProg())
	{
		flsItm_LinkProg_SaveOrRead(mReadWrite);
	}
	else if(mFlsItem == getFlsItem_ManuProg())
	{}
	else if(mFlsItem == getFlsItem_Note())
	{
		flsItm_Note_SaveOrRead(mReadWrite);
	}
	else if(mFlsItem == getFlsItem_RelateDete())
	{
		flsItm_RelateAddr_SaveOrRead(mReadWrite);
	}
	else if(mFlsItem == getFlsItem_Disable())
	{
		flsItm_Disable_SaveOrRead(mReadWrite);
	}
	
	
	
	
	
	if(mReadWrite == U_WRITE)
	{
		if(stSave.mPart == 1)
		{
			Clr_FlsItemState(U_FlsItem_Renew_State, mFlsItem, U_FlsSave_Part0);
		}
		Set_FlsItemState(U_FlsItem_Renew_State, mFlsItem, stSave.mPart);
		
	}
	else if(mReadWrite == U_READ)
	{
		Clr_FlsItemState(U_FlsItem_Renew_State, mFlsItem, U_FlsSave_Part0);
		Clr_FlsItemState(U_FlsItem_Renew_State, mFlsItem, U_FlsSave_Part1);
	}
}

/******************************************************************************
* FUNC: // 检查flash存储是否正确, SectorStart & CRC .
// only  before hist
*   IN:
*  OUT: Set_FlsItemState()
******************************************************************************/
void FlsSave_CheckFlash(void)
{
	U8 mFlsItem;
	
	for(mFlsItem=0; mFlsItem<getFlsItem_BeforeHist(); mFlsItem++)
	{
		FlsSave_CheckItem(mFlsItem);
	}
}

void FlsSave_CheckItem(U8 mFlsItem)
{
	U8 mPart;
	for(mPart=0; mPart<FlsItem_PartMax(mFlsItem); mPart++)
	{
		flsSave_checkItemPart(mFlsItem, mPart);
	}
}

// 检查 SectorStart & CRC .
void flsSave_checkItemPart(U8 mFlsItem, U8 mPart)
{
U32 strFlsItemBytes; //不包括head自身,不对齐
TFlsItemAddr stAdr;
U32 num;

	// emFlsItem :
	if(bFlsItemIs_OnePageSave(mFlsItem))
	{
		
		if(!getFlsItem_Addr(mFlsItem, mPart, &stAdr))
		{
			Set_FlsItemState(U_FlsItem_Error_State, mFlsItem, mPart);
			return;
		}
		if(!bFlsSectorStart_isItem(stAdr.chip, stAdr.adrS, mFlsItem))
		{
			Set_FlsItemState(U_FlsItem_Space_State, mFlsItem, mPart);
			return;
		}
		strFlsItemBytes = GetFlsItemBufBytes(mFlsItem);
		num = U_FLS_SectorStart_BYTES + strFlsItemBytes;
		FlsHd_Read_nByte(stAdr.chip, &vFlsRd_1Page[0], num, stAdr.adrS);
		if(!JdgCrcOK(&vFlsRd_1Page[U_FLS_SectorStart_BYTES], strFlsItemBytes))
		{
			Set_FlsItemState(U_FlsItem_Error_State, mFlsItem, mPart);
			return;
		}
	}
	
	else if(mFlsItem == getFlsItem_Disable())
	{}
	else if(mFlsItem == getFlsItem_Field())
	{}
	else if(mFlsItem == getFlsItem_Note())
	{}
#if U_SYS_Test_Flash_InqPoint == 1
	else if(mFlsItem == getFlsItem_Sim())
	{}
#endif
	else if(mFlsItem == getFlsItem_LinkProg())
	{}
	else if(mFlsItem == getFlsItem_ManuProg())
	{}
	else if(mFlsItem == getFlsItem_PowerOff())
	{}
	
#if U_SYS_bShowNoFinished == 1 
	U_SYS_bShowNoFinished = 1;
#endif // U_SYS_bShowNoFinished
}

/******************************************************************************
* FUNC: // END
*   IN:
*  OUT: 
******************************************************************************/
