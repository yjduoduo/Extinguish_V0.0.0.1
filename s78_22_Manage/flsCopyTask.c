#define __flsCopyTask_C__
/******************************************************************************
* @file    flsCopyTask.c
* @author  yx
* @version V1.0
* @date    2013-07-23
* @brief   error的mFlsItem, 用another对其覆盖。
		FlsCopy_CheckError();  // 检查出错的flsItem;
* 
// copy开始，Set U_FlsItem_Copyed_State -> Set U_FlsItem_Error_State ; FlsCopy_Start();
// copy结束：Clr U_FlsItem_Copyed_State -> Clr U_FlsItem_Space_State, U_FlsItem_Error_State.
******************************************************************************/
#include  "flsCopyTask.h"

#include  "saveInc_Common.h"
#include  "saveInc_Extern.h"


#include  "historyWrBuf.h"

#include  "flashIdAssign.h"

//#include "incFile.h"	


/*================= 常数 ============================================*/
#define U_FlsErrorToEvt_Erase   0  // U8 bErrType   
#define U_FlsErrorToEvt_CopyReNew   1 
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
		
void Init_FlsCopyTask(void)
{
#if U_SYS_IdleBuf_setFF == 1
U32 ii;
#endif //U_SYS_IdleBuf_setFF

	BufCircleIni(U_FlsCopy_Item_MAX, &vCircleFlsCopyBuf);
	flsCopy_SetIdle();
	
#if U_SYS_IdleBuf_setFF == 1
	for(ii=0; ii<U_FlsCopy_Item_MAX; ii++)
	{
		init_FlsCopyOneBuf(&stCopyBuf[ii]);
	}
#endif //U_SYS_IdleBuf_setFF
}

// clr one buf TFlsCopyBuf_st :
void init_FlsCopyOneBuf(TFlsCopyBuf_st *pOne)
{
U8 byteMax = sizeof(TFlsCopyBuf_st);


	if(pOne == NULL)
	{
		return;
	}
	
	ClrRamIsFF((U8*)(pOne), byteMax); //全清FF
	
}

/******************************************************************************
* FUNC: // -> BUF[]
*   IN:
*  OUT: 
******************************************************************************/
BOOL FlsCopy_New(U8 mFlsItemFrom, U8 mPartFrom, 
					  U8 mFlsItemDest, U8 mPartDest, 
					  U8 taskId, U8 flsId)
{
TFlsCopyBuf_st *pCopyInBuf;

	if(bFullBufCircle(&vCircleFlsCopyBuf))
	{
		return FALSE;
	}
	pCopyInBuf = &stCopyBuf[BufCircle_GetIn(&vCircleFlsCopyBuf)];
	
	pCopyInBuf->taskId = taskId;
	pCopyInBuf->flsId = flsId;
	pCopyInBuf->mFlsItemFrom = mFlsItemFrom;
	pCopyInBuf->mPartFrom    = mPartFrom;
	pCopyInBuf->mFlsItemDest = mFlsItemDest;
	pCopyInBuf->mPartDest    = mPartDest;
	
	BufCircle_InInc(&vCircleFlsCopyBuf);
	
	return TRUE;
}


/******************************************************************************
* FUNC: //整mFlsItem copy.
******************************************************************************/

BOOL FlsCopy_ItemPart_New(U8 mFlsItem, U8 mPartFrom, 
						 U8 mPartDest, U8 taskId, U8 flsId)
{
	return FlsCopy_New(mFlsItem, mPartFrom, 
					  mFlsItem, mPartDest, 
					  taskId, flsId);
}


BOOL FlsCopy_Item_New(U8 mFlsItemFrom, U8 mFlsItemDest, 
					  U8 taskId, U8 flsId)
{

U8 mPart;
	
	for(mPart=0; mPart<FlsItem_PartMax(mFlsItemFrom); mPart++)
	{
		if(!FlsCopy_New(mFlsItemFrom, mPart, 
					  mFlsItemDest, mPart, 
					  taskId, flsId))
		{
			return FALSE;
		}
	}
	return TRUE;
}


/******************************************************************************
* FUNC: //
* FALSE = 有copy任务存在。
******************************************************************************/
BOOL bFlsCopyBuf_Empty(void)
{
	return bEmptyBufCircle(&vCircleFlsCopyBuf);
}

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
BOOL bFlsCopy_isIdle(void)
{
	return LogicInverse((stCopyTask.bOpeaIng));
}

static void flsCopy_SetIdle(void)
{
	stCopyTask.bOpeaIng = FALSE;
	stCopyTask.step = ~0;
}

/******************************************************************************
* FUNC: // 
*   IN:
*  OUT: 
******************************************************************************/

BOOL FlsCopy_Start(void)
{
U32 mOut;
TFlsItemAddr stAdr;
TFlsCopyBuf_st *pCopyNowBuf;

	if(bFlsCopyBuf_Empty())
	{
		return FALSE;
	}
	
	mOut = BufCircle_GetOut(&vCircleFlsCopyBuf);
	stCopyTask.nowBuf = stCopyBuf[mOut];
	pCopyNowBuf = &stCopyTask.nowBuf;
	BufCircle_OutInc(&vCircleFlsCopyBuf);
	
	if(!getFlsItem_Addr(pCopyNowBuf->mFlsItemFrom, 
							pCopyNowBuf->mPartFrom, &stAdr))
	{
		return FALSE;
	}
	stCopyTask.stChipAdrSE_From = stAdr;
	stCopyTask.sectAdr_From = stAdr.adrS;
	if(!getFlsItem_Addr(pCopyNowBuf->mFlsItemDest, 
							pCopyNowBuf->mPartDest, &stAdr))
	{
		return FALSE;
	}
	stCopyTask.stChipAdrSE_Dest = stAdr;
	stCopyTask.sectAdr_Dest = stAdr.adrS;
	
	if(!FlsErase_ItemPart_New(pCopyNowBuf->mFlsItemDest, 
								pCopyNowBuf->mPartDest, 
								pCopyNowBuf->taskId,
								pCopyNowBuf->flsId))
	{
		return FALSE;
	}
	
	stCopyTask.bOpeaIng = TRUE;
	stCopyTask.step = U_FlsCopy_step_write;
	
	Set_FlsItemState(	U_FlsItem_Copyed_State, 
						pCopyNowBuf->mFlsItemFrom, 
						pCopyNowBuf->mPartFrom);
	Set_FlsItemState(	U_FlsItem_Error_State,
						pCopyNowBuf->mFlsItemFrom, 
						pCopyNowBuf->mPartFrom);
	return TRUE;
}


/******************************************************************************
* FUNC: // Copy结束
		通知结果没意义，因为不会被显示。
		应该是进历史记录。

*   IN:  pCopyNowBuf->mFlsItemFrom, pCopyNowBuf->mPartFrom
		pCopyNowBuf->mFlsItemDest, pCopyNowBuf->mPartDest
*  OUT: 
saveFlsItm_NotificatResult();
******************************************************************************/
static void flsCopy_NotificatResult(U8 bSucc)
{
TFlsCopyBuf_st *pCopyNowBuf;
	pCopyNowBuf = &stCopyTask.nowBuf;
	
	// taskId = pCopyNowBuf->taskId;
	// mFlsItem = pCopyNowBuf->mFlsItem;
	// 已有 HistNewEvent()
	// FlsIdClrAssign(pCopyNowBuf->flsId);
	
	// FlsResultNotificat(pCopyNowBuf->taskId, 
					  // pCopyNowBuf->flsId,
					  // bSucc);
	
	FlsIdClrAssign(pCopyNowBuf->flsId);
	
	
#if U_SYS_bShowNoFinished == 1 
	U_SYS_bShowNoFinished = 1;
#endif // U_SYS_bShowNoFinished
}


/******************************************************************************
* FUNC: // 当某part错误时，用another覆盖
*   IN:
*  OUT: 
******************************************************************************/
static U8 bAllowCheckError = 0;

void SetAllow_FlsCopy_CheckItemError(void)
{
	bAllowCheckError = 1;
}

void SetForbid_FlsCopy_CheckItemError(void)
{
	bAllowCheckError = 0;
	bAllowCheckError = bAllowCheckError;
}

BOOL bFlsCopy_Allow_CheckItemError(void)
{
	return FALSE;
	
	// return bAllowCheckError;

#if U_SYS_bShowNoFinished == 1 
	U_SYS_bShowNoFinished = 1;
#endif // U_SYS_bShowNoFinished
}


/******************************************************************************
* FUNC: // 报错。报故障，进历史记录。
*   IN: 
*  OUT: 
******************************************************************************/
static BOOL flashError_Item_toEvtBuf(U8 flsItem, U8 bErrType)
{
U8 mPart;
	for(mPart=0; mPart<FlsItem_PartMax(flsItem); mPart++)
	{
	flashError_ItemPart_toEvtBuf(flsItem, mPart, bErrType);
	}
	return TRUE;
}

static BOOL flashError_ItemPart_toEvtBuf(U8 flsItem, U8 mPart, U8 bErrType)
{
TEvtTrans_st  stEvt;


	DevSetInvalid(&stEvt.unDev);
	BuildToDev_Me_Flash(flsItem, mPart, &stEvt.unDev);

	GetRamEvtTimer(&stEvt.evtClock);
	stEvt.thing = GetEvtThingDef_Fault();
	// Buf_Fault(&stEvt); 
	
	if(bErrType == U_FlsErrorToEvt_Erase)
		stEvt.thing = GetEvtThingDef_FlsErase();
	else
		stEvt.thing = GetEvtThingDef_FlsCopyRenew();
	HistNewEvent(&stEvt);
	
	return TRUE;
}

/******************************************************************************
* FUNC: // 若是mFlsItem.error, copy
*   IN: 
*  OUT: 
* 应加限制，多次修改失败，不继续修改了。
******************************************************************************/
void FlsCopy_CheckError(void)
{
	// if(flsCopy_checkErr_preHist() != 0)
	// {
		// return;
	// }
	
	// flsCopy_checkErr_hist();
	
	
#if U_SYS_bShowNoFinished == 1 
	U_SYS_bShowNoFinished = 1;
#endif // U_SYS_bShowNoFinished
}


/******************************************************************************
* FUNC: // 判断各flsItem是否有错,有错->buf[]: 
hist前，判断FlsItem_State。
*   IN: 
*  OUT: 

******************************************************************************/

U32 flsCopy_checkErr_preHist(void)
{
U8 mFlsItem;
U8 addNum = 0;

	for(mFlsItem=0; mFlsItem<getFlsItem_BeforeHist(); mFlsItem++)
	{
		if(addNum >= U_FlsCopy_Once_MAX)
		{
			return addNum;
		}
		if(!bFlsItem_HaveShare(mFlsItem))
		{
			if(bFlsItem_isState(U_FlsItem_Error_State, mFlsItem, U_FlsSave_Part0))
			{
				flsCopy_checkErr_ItemPartErase(mFlsItem, U_FlsSave_Part0);
			}
			continue;
		}
		
		if((bFlsItem_isState(U_FlsItem_Error_State, mFlsItem, U_FlsSave_Part0))
		   &&(bFlsItem_isState(U_FlsItem_Error_State, mFlsItem, U_FlsSave_Part1)))
		{
			flsCopy_checkErr_ItemErase(mFlsItem);
		}
		else if(bFlsItem_IsErrorOrSpace(mFlsItem, U_FlsSave_Part0))
		{
			if(!bFlsItem_IsErrorOrSpace(mFlsItem, U_FlsSave_Part1))
			{
				flsCopy_checkErr_ItemCopy(
						mFlsItem, U_FlsSave_Part1,
						mFlsItem, U_FlsSave_Part0);
				addNum++;
			}
		}
		else
		{
			if(bFlsItem_IsErrorOrSpace(mFlsItem, U_FlsSave_Part1))
			{
				flsCopy_checkErr_ItemCopy(
						mFlsItem, U_FlsSave_Part0,
						mFlsItem, U_FlsSave_Part1);
				addNum++;
			}
		}
	}
	return addNum;
}




/******************************************************************************

* FUNC: // 判断各flsItem是否有错,有错->buf[]: 
hist，判断FlsItem_State。
*   IN: 
*  OUT: 
******************************************************************************/

void flsCopy_checkErr_hist(void)
{
U8 mFlsItem;
U8 mFlsPt0Item;
U8 mFlsPt1Item;
U8 mHistCls;
	
	for(mHistCls=0; mHistCls<U_HIST_CLASS_MAX; mHistCls++)
	{
		mFlsItem = getFlsItem_hist(mHistCls);
		mFlsPt0Item = getFlsItem_hstPart0Point(mHistCls);
		mFlsPt1Item = getFlsItem_hstPart1Point(mHistCls);
		
		if((bFlsItem_isState(U_FlsItem_Error_State, mFlsItem, U_FlsSave_Part0))
		   &&(bFlsItem_isState(U_FlsItem_Error_State, mFlsItem, U_FlsSave_Part1)))
		{
			flsCopy_checkErr_ItemErase(mFlsItem);			
			flsCopy_checkErr_ItemErase(mFlsPt0Item);			
			flsCopy_checkErr_ItemErase(mFlsPt1Item);
			return;
		}
		
		
		//先检查单一指针错误
		if(!bFlsItem_isState(U_FlsItem_Error_State, mFlsItem, U_FlsSave_Part0))
		{
			if(!flsCopy_checkErr_hstPt(mHistCls, U_FlsSave_Part0))
			{
				return;
			}
		}
		if(!bFlsItem_isState(U_FlsItem_Error_State, mFlsItem, U_FlsSave_Part1))
		{
			if(!flsCopy_checkErr_hstPt(mHistCls, U_FlsSave_Part1))
			{
				return;
			}
		}
		
		//一个记录错误的情况：
		if((  bFlsItem_IsErrorOrSpace(mFlsItem, U_FlsSave_Part0))
		  &&(!bFlsItem_IsErrorOrSpace(mFlsItem, U_FlsSave_Part1)))
		{
			// U_FlsSave_Part1 -> U_FlsSave_Part0
			flsCopy_checkErr_ItemCopy(
					mFlsItem, U_FlsSave_Part1,
					mFlsItem, U_FlsSave_Part0);
			// addNum++;
			
			flsCopy_checkErr_ItemCopy(
					mFlsPt1Item, U_FlsSave_Part0,
					mFlsPt0Item, U_FlsSave_Part0);
			// addNum++;
			
			flsCopy_checkErr_ItemCopy(
					mFlsPt1Item, U_FlsSave_Part1,
					mFlsPt0Item, U_FlsSave_Part1);
			// addNum++;
			
			return;
		}
		
		
		if((  bFlsItem_IsErrorOrSpace(mFlsItem, U_FlsSave_Part1))
		  &&(!bFlsItem_IsErrorOrSpace(mFlsItem, U_FlsSave_Part0)))
		{
			// U_FlsSave_Part0 -> U_FlsSave_Part1
			flsCopy_checkErr_ItemCopy(
					mFlsItem, U_FlsSave_Part0,
					mFlsItem, U_FlsSave_Part1);
			// addNum++;
			
			flsCopy_checkErr_ItemCopy(
					mFlsPt0Item, U_FlsSave_Part0,
					mFlsPt1Item, U_FlsSave_Part0);
			// addNum++;
			
			flsCopy_checkErr_ItemCopy(
					mFlsPt0Item, U_FlsSave_Part1,
					mFlsPt1Item, U_FlsSave_Part1);
			// addNum++;
			
			return;
			
		}
		
	}
	
	
}


/******************************************************************************
* FUNC: //
*   IN: 
*  OUT: FALSE = 有错误
******************************************************************************/
// 历史记录正确，判断其指针error：
static BOOL flsCopy_checkErr_hstPt(U8 mHistCls, U8 mHistPart)
{
U8 mFlsItem;
U8 mFlsPtItem;
	
	mFlsItem = getFlsItem_hist(mHistCls);
	mFlsPtItem = getFlsItem_hstPoint(mHistCls, mHistPart);
	
	if(( bFlsItem_IsErrorOrSpace(mFlsPtItem, U_FlsSave_Part1))
	  &&(bFlsItem_IsErrorOrSpace(mFlsPtItem, U_FlsSave_Part0)))
	{
		Set_FlsItemState(U_FlsItem_Error_State, mFlsItem, mHistPart);
		Set_FlsItemState(U_FlsItem_Error_State, mFlsPtItem, U_FlsSave_Part0);
		Set_FlsItemState(U_FlsItem_Error_State, mFlsPtItem, U_FlsSave_Part1);
		flsCopy_checkErr_ItemErase(mFlsPtItem);
		return FALSE;
	}
	else if((bFlsItem_IsErrorOrSpace(mFlsPtItem, U_FlsSave_Part1))
		 &&(!bFlsItem_IsErrorOrSpace(mFlsPtItem, U_FlsSave_Part0)))
	{
		// U_FlsSave_Part0 -> U_FlsSave_Part1
		flsCopy_checkErr_ItemCopy(
				mFlsPtItem, U_FlsSave_Part0,
				mFlsPtItem, U_FlsSave_Part1);
		return FALSE;
		
	}
	else if((bFlsItem_IsErrorOrSpace(mFlsPtItem, U_FlsSave_Part0))
		 &&(!bFlsItem_IsErrorOrSpace(mFlsPtItem, U_FlsSave_Part1)))
	{
		// U_FlsSave_Part1 -> U_FlsSave_Part0
		flsCopy_checkErr_ItemCopy(
				mFlsPtItem, U_FlsSave_Part1,
				mFlsPtItem, U_FlsSave_Part0);
		return FALSE;
		
	}

	return TRUE;

}


/******************************************************************************
* FUNC: // 出错处理方法：Copy.
*   IN: 
*  OUT: 
******************************************************************************/
static void flsCopy_checkErr_ItemCopy(
						U8 mFlsItemFrom, U8 mPartFrom,
						U8 mFlsItemDest, U8 mPartDest)
{
U8 flsId;
	
	if((bFlsItemState_copyNum_Over(mFlsItemDest, mPartDest)))
	{
	}
	else
	{
		if(!FlsIdNewAssign(GetSysTaskId_FlsVerify(), &flsId))
		{
			return;
		}
		FlsCopy_New(mFlsItemFrom, mPartFrom, 
					mFlsItemDest, mPartDest, GetSysTaskId_FlsVerify(), flsId);
		flashError_ItemPart_toEvtBuf(mFlsItemDest, mPartDest,
					U_FlsErrorToEvt_CopyReNew);
	}
}

/******************************************************************************
* FUNC: // 出错处理方法：Erase.
******************************************************************************/
static void flsCopy_checkErr_ItemErase(U8 flsItem)
{
U8 flsId;
	
	if((bFlsItemState_copyNum_Over(flsItem, U_FlsSave_Part0))
	  ||(bFlsItemState_copyNum_Over(flsItem, U_FlsSave_Part1)))
	{
	}
	else
	{
		if(!FlsIdNewAssign(GetSysTaskId_FlsVerify(), &flsId))
		{
			return;
		}
		FlsErase_Item_New(flsItem, GetSysTaskId_FlsVerify(), flsId);
		
		FlsItemState_copyNum_Inc(flsItem, U_FlsSave_Part0);
		FlsItemState_copyNum_Inc(flsItem, U_FlsSave_Part1);
		
		flashError_Item_toEvtBuf(flsItem, U_FlsErrorToEvt_Erase);
	}
}

/******************************************************************************
* FUNC: // 
******************************************************************************/

static void flsCopy_checkErr_ItemPartErase(U8 flsItem, U8 mPart)
{
U8 flsId;
	
	if(bFlsItemState_copyNum_Over(flsItem, mPart))
	{
	}
	else
	{
		if(!FlsIdNewAssign(GetSysTaskId_FlsVerify(), &flsId))
		{
			return;
		}
		FlsErase_ItemPart_New(flsItem, mPart, 
						  GetSysTaskId_FlsVerify(), flsId);
		
		FlsItemState_copyNum_Inc(flsItem, mPart);
		
		flashError_ItemPart_toEvtBuf(flsItem, mPart, U_FlsErrorToEvt_Erase);
		
	}
}

/******************************************************************************
* FUNC: // 历史记录指针，要修改sectorHead.
*   IN: 
*  OUT: 
******************************************************************************/

static void flsCopy_sect_head(void)
{
U8 mFlsItemFrom;
U8 mFlsItemDest;
TFlsCopyBuf_st *pCopyNowBuf;
U8 *pBufS;
TFlsSecStart_un *pSectStart;

	
	pCopyNowBuf = &stCopyTask.nowBuf;
	pBufS = pFlsHd_GetBufS();
	mFlsItemFrom = pCopyNowBuf->mFlsItemFrom;
	mFlsItemDest = pCopyNowBuf->mFlsItemDest;
	if(mFlsItemDest == mFlsItemFrom)
	{
		return;
	}
	
	if(bFlsItemIs_hstPoint(mFlsItemFrom))
	{
		pSectStart = (TFlsSecStart_un*)(pBufS);
		Init_StrFlsSectStart(mFlsItemDest, pSectStart);
	}
	
	
}


/******************************************************************************
* FUNC: // 
*   IN:
*  OUT: 
******************************************************************************/

void FlsCopy_Exec(void)
{
U8 *pBufS;
U32 byte_1Sect;
TFlsCopyBuf_st *pCopyNowBuf;

	pCopyNowBuf = &stCopyTask.nowBuf;
	
	switch(stCopyTask.step)
	{
		case U_FlsCopy_step_write:
			
			pBufS = pFlsHd_GetBufS();
			
			if(stCopyTask.sectAdr_From == stCopyTask.stChipAdrSE_From.adrE)
			{
				stCopyTask.step = U_FlsCopy_step_finish;
				return;
			}
			byte_1Sect = getFlsItem_1SectorBytes(
							pCopyNowBuf->mFlsItemDest);
			FlsHd_Read_1Sec(stCopyTask.stChipAdrSE_From.chip, 
							pBufS, stCopyTask.sectAdr_From);
			//sectorHead:
			flsCopy_sect_head();
			FlsWr_Write_nByte(stCopyTask.stChipAdrSE_Dest.chip, 
							pBufS, byte_1Sect, stCopyTask.sectAdr_Dest);
			
			stCopyTask.step = U_FlsCopy_step_sectNext;
			break;
			
			
		case U_FlsCopy_step_sectNext: //主要是为了给task的read留空。
			stCopyTask.sectAdr_From = hist_sectorNext_start(
										stCopyTask.sectAdr_From, 
										&stCopyTask.stChipAdrSE_From);
			stCopyTask.sectAdr_Dest = hist_sectorNext_start(
										stCopyTask.sectAdr_Dest, 
										&stCopyTask.stChipAdrSE_Dest);
			stCopyTask.step = U_FlsCopy_step_write;
			break;
			
			
		case U_FlsCopy_step_finish:
			// 考虑比较数据
			Clr_FlsItemState(	U_FlsItem_Copyed_State,
								pCopyNowBuf->mFlsItemFrom, 
								pCopyNowBuf->mPartFrom);
			Clr_FlsItemState(	U_FlsItem_Space_State, 
								pCopyNowBuf->mFlsItemDest, 
								pCopyNowBuf->mPartDest);
			Clr_FlsItemState(	U_FlsItem_Error_State, 
								pCopyNowBuf->mFlsItemDest, 
								pCopyNowBuf->mPartDest);
			FlsItemState_copyNum_Inc(
								pCopyNowBuf->mFlsItemDest,
								pCopyNowBuf->mPartDest);
			
			flsCopy_NotificatResult(U_SUCC);
			flsCopy_SetIdle();
			break;
		
		default:
			flsCopy_SetIdle();
			break;
	}
	
	
}



/******************************************************************************
* FUNC: // END
*   IN:
*  OUT: 
******************************************************************************/
