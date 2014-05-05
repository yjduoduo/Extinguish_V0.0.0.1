#define __flsErase_C__
/******************************************************************************
* @file    flsErase.c
* @author  yx
* @version V1.1
* @date    2013-9-3
* @brief   �������У���ִ��erase.
* @master  Ӧ�ó��� | �޸�ǰ�Ĳ�����
* @master   saveManage.c
*
* V1.1  ����buf[out]�����ݣ�startʱ���浽stEraseTask.nowBuf��ʹ�á� 2013-9-3 
* V1.0  2013-07-23

* ���� mIntegratPart
*	   
* IN: FlsErase_New() ����brother;  
******************************************************************************/
#include  "flsErase.h"

#include  "codeComm.h"		//���ݡ�buf�ȳ������
#include  "codeCrc.h"
#include  "bufCircle.h"

#include  "flsStoreBytesDef.h"
#include  "strFlsAdrDef.h"
#include  "flsItemState.h"
#include  "flsAdrCalculate.h"

#include  "strFlsQue.h"

#include  "fls_Interface.h"


// #include  "flashIdAssign.h"
extern BOOL bIsFinish_FlsExe(U8 flsId, U8 *pRtnSucc);
extern void FlsResultNotificat(U8 taskId, U8 mFlsId, U8 bSucc);
	


/*================= ���� ============================================*/

/*================= �ṹ���� ========================================*/

/*================= ˽�нṹ�������� ================================*/

/*================= ���к������� ====================================*/

/*================= ˽�к������� ====================================*/

/*=================  ================================================*/
		
/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
		
void Init_FlsEraseTask(void)
{
#if U_SYS_IdleBuf_setFF == 1
U32 ii;
#endif //U_SYS_IdleBuf_setFF

	BufCircleIni(U_FlsErase_Item_MAX, &vCircleFlsEraseBuf);
	flsErase_SetIdle();
	
#if U_SYS_IdleBuf_setFF == 1
	for(ii=0; ii<U_FlsErase_Item_MAX; ii++)
	{
		init_FlsEraseOneBuf(&stEraseBuf[ii]);
	}
#endif //U_SYS_IdleBuf_setFF
}


void init_FlsEraseOneBuf(TFlsEraseBuf_st *pOne)
{
U8 byteMax = sizeof(TFlsEraseBuf_st);


	if(pOne == NULL)
	{
		return;
	}
	
	ClrRamIsFF((U8*)(pOne), byteMax); //ȫ��FF
	
}


/******************************************************************************
* FUNC: // add Erase FlsItem.Part.pAdr ���� -> eraseBuf[].
*   IN:
*  OUT: 
******************************************************************************/

BOOL flsErase_entryBuf(U8 mFlsItem, U8 mPart, 
					U8 taskId, U8 flsId, 
					TFlsItemAddr *pAdr,
					U8 percentS, U8 percentE)
{
TFlsEraseBuf_st *pEraseInBuf;
TFlsItemAddr stAdr;

	if(!getFlsItem_Addr(mFlsItem, mPart, &stAdr))
	{
		return FALSE;
	}
	if(  (!bInFlsItemAddr(pAdr->adrS, &stAdr))
	  || (!bInFlsItemAddr(pAdr->adrE, &stAdr))
	  )
	{
		return FALSE;
	}
	
	
	if(bFullBufCircle(&vCircleFlsEraseBuf))
	{
		return FALSE;
	}
	pEraseInBuf = &stEraseBuf[BufCircle_GetIn(&vCircleFlsEraseBuf)];
	
	pEraseInBuf->mFlsItem = mFlsItem;
	pEraseInBuf->mPart = mPart;
	pEraseInBuf->mIntegratPart = FALSE;
	
	if(bEquFlsItemAddr(&stAdr, pAdr)) 
	{
		pEraseInBuf->mIntegratPart = TRUE;
	}
	pEraseInBuf->taskId = taskId;
	pEraseInBuf->flsId = flsId;
	pEraseInBuf->stEraseAdr = *pAdr;
	
	pEraseInBuf->percentS = percentS;
	pEraseInBuf->percentE = percentE;
	BufCircle_InInc(&vCircleFlsEraseBuf);
	
	// stEraseTask.nowSectAdr = pEraseInBuf->stEraseAdr.adrS;
	// stEraseTask.bOpeaIng = TRUE;
	
#if U_FLASH_TASK_WAIT == FALSE
	return TRUE;
#else  // U_FLASH_TASK_WAIT
	return bWaitForFlsOpeaFinish(flsId);
#endif // U_FLASH_TASK_WAIT
	
}

/******************************************************************************
* FUNC: // 
*   IN:
*  OUT: 
******************************************************************************/
BOOL FlsErase_New(U8 mFlsItem, U8 mPart, U8 taskId, U8 flsId, 
					TFlsItemAddr *pAdr)
{
	return flsErase_entryBuf(mFlsItem, mPart, 
					taskId, flsId, pAdr,
					0, 100);
}

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
// add Erase FlsItem.Part ���� -> eraseBuf[].
******************************************************************************/
BOOL FlsErase_ItemPart_New(U8 mFlsItem, U8 mPart, 
						  U8 taskId, U8 flsId)
{
TFlsItemAddr stAdr;

	if(!getFlsItem_Addr(mFlsItem, mPart, &stAdr))
	{
		return FALSE;
	}
	
	
	return flsErase_entryBuf(mFlsItem, mPart, 
					taskId, flsId, &stAdr,
					0, 100);
	
}

/******************************************************************************
* FUNC: //��mFlsItem���� -> eraseBuf[].
******************************************************************************/

BOOL FlsErase_Item_New(U8 mFlsItem, U8 taskId, U8 flsId)
{
TFlsItemAddr stAdr;
U8 mPart;
U8 mPatMax;
U8 percentS, percentE;
	
	mPatMax = FlsItem_PartMax(mFlsItem);
	
	for(mPart=0; mPart<mPatMax; mPart++)
	{
		if(!getFlsItem_Addr(mFlsItem, mPart, &stAdr))
		{
			return FALSE;
		}
		
		if(mPatMax == 1)
		{
			percentS = 0;
			percentE = 100;
		}
		else
		{
			if(mPart == 0)
			{
				percentS = 0;
				percentE = 50;
			}
			else if(mPart == 1)
			{
				percentS = 50;
				percentE = 100;
			}
		}
		
		if(!flsErase_entryBuf(mFlsItem, mPart, 
						taskId, flsId, &stAdr,
						percentS, percentE))
		{
			return FALSE;
		}
	}
	return TRUE;
}


/******************************************************************************
* FUNC: //
******************************************************************************/
BOOL bFlsEraseBuf_Empty(void)
{
	return bEmptyBufCircle(&vCircleFlsEraseBuf);
}

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
BOOL bFlsErase_isIdle(void)
{
	return LogicInverse((stEraseTask.bOpeaIng));
}

static void flsErase_SetIdle(void)
{
	stEraseTask.bOpeaIng = FALSE;
}

/******************************************************************************
* FUNC: // 
*   IN:
*  OUT: 
******************************************************************************/

BOOL FlsErase_Start(void)
{
U32 mOut;
TFlsEraseBuf_st *pEraseNowBuf;

	if(bFlsEraseBuf_Empty())
	{
		return FALSE;
	}
	
	stEraseTask.bOpeaIng = TRUE;
	mOut = BufCircle_GetOut(&vCircleFlsEraseBuf);
	stEraseTask.nowBuf = stEraseBuf[mOut];
	pEraseNowBuf = &stEraseTask.nowBuf;
	BufCircle_OutInc(&vCircleFlsEraseBuf);
	
	stEraseTask.stEraseAdr = pEraseNowBuf->stEraseAdr; //chip,S,E;
	stEraseTask.nowSectAdr = stEraseTask.stEraseAdr.adrS;
	
	stEraseTask.sectTotal = FlsItm_sector_Total(
								pEraseNowBuf->mFlsItem,
								&pEraseNowBuf->stEraseAdr);
	stEraseTask.sectHaveFinish = 0;
	
	Set_FlsItemState(U_FlsItem_Error_State, 
		pEraseNowBuf->mFlsItem, pEraseNowBuf->mPart);
	
	return TRUE;
}


/******************************************************************************
* FUNC: //������ɵİٷֱ�
*   IN:
*  OUT: 
******************************************************************************/
BOOL FlsErase_WorkIng_MyFlsId(U8 mFlsId) 
{
U32 mOut;
	
	if(bFlsIdIsEraseIng(mFlsId))
	{
		return TRUE;
	}
	else if(bFlsIdIsExistInBuf(mFlsId, &mOut))
	{
		return TRUE;
	}
	else
	{
		return FALSE; 
	}
	
}



U8 FlsErase_HaveFinishPercent(U8 mFlsId) 
{
U8 bSucc;
U32 mOut;
U32 nowStepPercent;
U32 nowPercent;
TFlsEraseBuf_st *pEraseNowBuf;

	if(bIsFinish_FlsExe(mFlsId, &bSucc))
	{
		return 100;
	}
	else
	{
		if(bFlsIdIsEraseIng(mFlsId))
		{
			pEraseNowBuf = &stEraseTask.nowBuf;
			nowStepPercent = ((stEraseTask.sectHaveFinish *100)
							/ stEraseTask.sectTotal) ;
			nowPercent = nowStepPercent 
						* ((pEraseNowBuf->percentE) - (pEraseNowBuf->percentS)) 
						/ 100;
			return ((pEraseNowBuf->percentS) + nowPercent);
			
		}
		else if(bFlsIdIsExistInBuf(mFlsId, &mOut))
		{
			pEraseNowBuf = &stEraseBuf[mOut];
			return (pEraseNowBuf->percentS);
		}
		else
		{
			return 0;
		}
		
	}
}


/******************************************************************************
* FUNC: //
******************************************************************************/
static BOOL bFlsIdIsExistInBuf(U8 mFlsId, U32 *pRtnBuf)
{
U32 mOut;
TFlsEraseBuf_st *pEraseNowBuf;
	

	if(bEmptyBufCircle(&vCircleFlsEraseBuf))
	{
		return FALSE;
	}
	else
	{
		mOut = BufCircle_GetOut(&vCircleFlsEraseBuf);
		while(mOut != BufCircle_GetIn(&vCircleFlsEraseBuf))
		{
			pEraseNowBuf = &stEraseBuf[mOut];
			if(pEraseNowBuf->flsId == mFlsId)
			{
				*pRtnBuf = mOut;
				return TRUE;
			}
			mOut = CircleAdd(mOut, 1, vCircleFlsEraseBuf.max);
		}
	}
	return FALSE;
}

static BOOL bFlsIdIsEraseIng(U8 mFlsId)
{
TFlsEraseBuf_st *pEraseNowBuf;

	if(bFlsErase_isIdle())
	{
		return FALSE;
	}
	else
	{
		pEraseNowBuf = &stEraseTask.nowBuf;
		return (pEraseNowBuf->flsId == mFlsId);
	}
}


/******************************************************************************
* FUNC: // ������ϣ��޸�state �� queue.point.
*   IN:
*  OUT: 
******************************************************************************/

static void flsErase_Finish(U8 bSucc)
{
TFlsEraseBuf_st *pEraseNowBuf;	
	pEraseNowBuf = &stEraseTask.nowBuf;
	
	Clr_FlsItemState(U_FlsItem_Error_State, 
					pEraseNowBuf->mFlsItem, 
					pEraseNowBuf->mPart);
	Set_FlsItemState(U_FlsItem_Space_State, 
					pEraseNowBuf->mFlsItem, 
					pEraseNowBuf->mPart);
	
	if(bFlsItem_isQueue(pEraseNowBuf->mFlsItem))
	{
		ClrOneItem_FlsQueHeadEnd(
					pEraseNowBuf->mFlsItem, 
					pEraseNowBuf->mPart);
	}
}


/******************************************************************************
* FUNC: // 
*   IN:
*  OUT: 
saveFlsItm_NotificatResult();
******************************************************************************/
static void flsErase_NotificatResult(U8 bSucc)
{
TFlsEraseBuf_st *pEraseNowBuf;	
	pEraseNowBuf = &stEraseTask.nowBuf;
	
	FlsResultNotificat(pEraseNowBuf->taskId, 
					pEraseNowBuf->flsId,
					bSucc);
	

}

/******************************************************************************
* FUNC: // 
*   IN:
*  OUT: 
******************************************************************************/

void FlsErase_Exec(void)
{
TFlsEraseBuf_st *pEraseNowBuf;
	pEraseNowBuf = &stEraseTask.nowBuf;

	if(stEraseTask.nowSectAdr == stEraseTask.stEraseAdr.adrE)
	{
		flsErase_Finish(U_SUCC);
		if(pEraseNowBuf->percentE == 100)
		{
			flsErase_NotificatResult(U_SUCC);
		}
		stEraseTask.sectHaveFinish = stEraseTask.sectTotal;
		flsErase_SetIdle();
		return;
	}
	FlsHd_EraseSect_FromAdr(stEraseTask.stEraseAdr.chip, 
				stEraseTask.nowSectAdr, U_SYS_FLASH_OPEA_WAIT
				);
	
	stEraseTask.nowSectAdr = FlsItm_sectorNext_start(
					stEraseTask.nowSectAdr, 
					pEraseNowBuf->mFlsItem, 
					&pEraseNowBuf->stEraseAdr
					);
	stEraseTask.sectHaveFinish++;
}

/******************************************************************************
* FUNC: // END
*   IN:
*  OUT: 
******************************************************************************/
