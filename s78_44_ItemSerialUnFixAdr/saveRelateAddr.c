#define __saveRelateAddr_C__
/******************************************************************************
* @file    saveRelateAddr.c
* @author  yx
* @version V1.0
* @date    2013-10-24
* @brief   ���������� ��ص�ַ
* 
******************************************************************************/
#include  "saveRelateAddr.h"


#include  "saveItem_incIn.h"
//#include "incFile.h"	


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
// read sector firstOne:
// out: pBuf
void readOne_relateDete_SecFirstOne(
							U8 mChip, U32 mFromAdr, U8 *pBuf)
{
U32 mAdrFrom;
	
	mAdrFrom = FlsItm_sector_start(mFromAdr, 
								  getFlsItem_RelateDete());
	mAdrFrom += U_FLS_RelateDete_One_BYTE_MAX;
	
	FlsHd_Read_nByte(mChip, pBuf, 
						U_FLS_RelateDete_One_BYTE_MAX, mFromAdr);
}

/******************************************************************************
* FUNC: // 
******************************************************************************/

// this sector stored is :
BOOL bSectorFir_IsThisMachineLoop(TDev_un *pDev, 
							U8 mChip, U32 mFromAdr)
{
U8 *pBufS;
TFlsRelateDeteOne_st *pRelatDete;
	
	pBufS = pFlsHd_GetBufS();
	readOne_relateDete_SecFirstOne(mChip, mFromAdr, pBufS);
	
	pRelatDete = (TFlsRelateDeteOne_st*)(pBufS);
	
	return bEquLoop_RelatDeteAndDev(pRelatDete, pDev);
	
}

/******************************************************************************
* FUNC: // 
******************************************************************************/

BOOL bEquLoop_RelatDeteAndDev( 
					TFlsRelateDeteOne_st *pRelatDete, TDev_un *pDev)
{
	
	if(  (pRelatDete->stDev.stDete.machine   == pDev->stDete.machine)
	  || (pRelatDete->stDev.stDete.pnType    == pDev->stDete.pnType)
	  || (pRelatDete->stDev.stDete.pnSequ    == pDev->stDete.pnSequ)
	  || (pRelatDete->stDev.stDete.boardLoop == pDev->stDete.boardLoop)
	  )
	{
		return TRUE;
	}
	{
		return FALSE;
	}
}

/******************************************************************************
* FUNC: // 
******************************************************************************/

// ��RAM����� ��ͬ��loop:
BOOL bFoundInRam_EquMachineLoop(TDev_un *pDev, 
							  U8 *pBufS, U32 mAdrOffset,
							  U32 *pRtnOffset)
{
TFlsRelateDeteOne_st *pRelatDete;
U32 mOffstAdr;
U8 mFlsItem = getFlsItem_RelateDete();
U32 mOffsetMax = getFlsItem_1SectorBytes(mFlsItem);
U8 *pBufNow;
	
	mOffstAdr = mAdrOffset;
	if(mAdrOffset < U_FLS_RelateDete_One_BYTE_MAX)
	{
		mOffstAdr = U_FLS_RelateDete_One_BYTE_MAX;
	}
	// ��֤һ���ռ�:
	while((mOffstAdr + U_FLS_RelateDete_One_BYTE_MAX) <= mOffsetMax)
	{
		pBufNow = pBufS + mOffstAdr;
		pRelatDete = (TFlsRelateDeteOne_st*)(pBufNow);
		if(!bDevOk(&pRelatDete->stDev))
		{
			break; // is Buf END
		}
		if(bEquLoop_RelatDeteAndDev(pRelatDete, pDev))
		{
			*pRtnOffset = mOffstAdr;
			return TRUE;
		}
		mOffstAdr += U_FLS_RelateDete_One_BYTE_MAX;
	}
	
	return FALSE;
}


// ��RAM����� ��ͬ�� dete:
static BOOL bFoundInRam_EquDete(TDev_un *pDev, 
							  U8 *pBufS, U32 mAdrOffset,
							  U32 *pRtnOffset)
{
TFlsRelateDeteOne_st *pRelatDete;
U32 mOffstAdr;
U8 mFlsItem = getFlsItem_RelateDete();
U32 mOffsetMax = getFlsItem_1SectorBytes(mFlsItem);
U8 *pBufNow;
	
	mOffstAdr = mAdrOffset;
	if(mAdrOffset < U_FLS_RelateDete_One_BYTE_MAX)
	{
		mOffstAdr = U_FLS_RelateDete_One_BYTE_MAX;
	}
	// ��֤һ���ռ�:
	while((mOffstAdr + U_FLS_RelateDete_One_BYTE_MAX) <= mOffsetMax)
	{
		pBufNow = pBufS + mOffstAdr;
		pRelatDete = (TFlsRelateDeteOne_st*)(pBufNow);
		if(!bDevOk(&pRelatDete->stDev))
		{
			break; // is Buf END
		}
		if(bEquLoop_RelatDeteAndDev(pRelatDete, pDev))
		{
			if(pRelatDete->stDev.stDete.field == pDev->stDete.field)
			{
				*pRtnOffset = mOffstAdr;
				return TRUE;
			}
		}
		mOffstAdr += U_FLS_RelateDete_One_BYTE_MAX;
	}
	
	return FALSE;
}

/******************************************************************************
* FUNC: // 
******************************************************************************/

// ��RAM����� space:
static BOOL bFoundInRam_Space(U8 *pBufS, U32 mAdrOffset,
							  U32 *pRtnOffset)
{
TFlsRelateDeteOne_st *pRelatDete;
U32 mOffstAdr;
U8 mFlsItem = getFlsItem_RelateDete();
U32 mOffsetMax = getFlsItem_1SectorBytes(mFlsItem);
U8 *pBufNow;
	
	mOffstAdr = mAdrOffset;
	if(mAdrOffset < U_FLS_RelateDete_One_BYTE_MAX)
	{
		mOffstAdr = U_FLS_RelateDete_One_BYTE_MAX;
	}
	// ��֤һ���ռ�:
	while((mOffstAdr + U_FLS_RelateDete_One_BYTE_MAX) <= mOffsetMax)
	{
		pBufNow = pBufS + mOffstAdr;
		pRelatDete = (TFlsRelateDeteOne_st*)(pBufNow);
		if(!bDevOk(&pRelatDete->stDev))
		{
			*pRtnOffset = mOffstAdr;
			return TRUE; // is Buf END
		}
		
		mOffstAdr += U_FLS_RelateDete_One_BYTE_MAX;
	}
	
	return FALSE;
}


/******************************************************************************
* FUNC: // 
******************************************************************************/

// ��RAM���жϣ���mAdrOffset֮��ȫ��Space:
static BOOL bJdgInRam_AllSpace(U8 *pBufS, U32 mAdrOffset)
{
TFlsRelateDeteOne_st *pRelatDete;
U32 mOffstAdr;
U8 mFlsItem = getFlsItem_RelateDete();
U32 mOffsetMax = getFlsItem_1SectorBytes(mFlsItem);
U8 *pBufNow;
	
	mOffstAdr = mAdrOffset;
	if(mAdrOffset < U_FLS_RelateDete_One_BYTE_MAX)
	{
		mOffstAdr = U_FLS_RelateDete_One_BYTE_MAX;
	}
	// ��֤һ���ռ�:
	while((mOffstAdr + U_FLS_RelateDete_One_BYTE_MAX) <= mOffsetMax)
	{
		pBufNow = pBufS + mOffstAdr;
		pRelatDete = (TFlsRelateDeteOne_st*)(pBufNow);
		if(bDevOk(&pRelatDete->stDev))
		{
			return FALSE; // ��dev���ǿ�
		}
		
		mOffstAdr += U_FLS_RelateDete_One_BYTE_MAX;
	}
	
	return TRUE;
}

/******************************************************************************
* FUNC: // 
******************************************************************************/
// sector isSpace:
BOOL bSectorFir_IsRelatDeteSpace(U8 mChip, U32 mFromAdr)
{
U8 *pBufS;
TFlsRelateDeteOne_st *pRelatDete;
	
	pBufS = pFlsHd_GetBufS();
	readOne_relateDete_SecFirstOne(mChip, mFromAdr, pBufS);
	
	pRelatDete = (TFlsRelateDeteOne_st*)(pBufS);
	
	if(bDevOk(&pRelatDete->stDev))
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}

/******************************************************************************
* FUNC: // 
*   IN:
*  OUT: 
******************************************************************************/
// ���ҿյ� sector, �Դ洢�»�·
BOOL bFlsRelateDete_FoundSpaceSector(U8 mPart, 
										U32 *pRtnSecFirAdr)
{
TFlsItemAddr stAdr;
U8 mFlsItem = getFlsItem_RelateDete();
U32 mAdr;
	
	if(!getFlsItem_Addr(mFlsItem, mPart, &stAdr))
	{
		return FALSE;
	}
	
	mAdr = stAdr.adrS;
	while(mAdr != stAdr.adrE)
	{
		if(bSectorFir_IsRelatDeteSpace(stAdr.chip, mAdr))
		{
			*pRtnSecFirAdr = mAdr;
			return TRUE;
		}
		mAdr = FlsItm_sectorNext_start(mAdr, mFlsItem, &stAdr);
	}
	
	return FALSE;
}



/******************************************************************************
* FUNC: // 
******************************************************************************/
// ���� ��ͬ��·��sector��
BOOL bFlsRelateDete_FoundEquMachineLoopSector( 
				TDev_un *pDev, U8 mPart, U32 *pRtnSecFirAdr)
{
TFlsItemAddr stAdr;
U8 mFlsItem = getFlsItem_RelateDete();
U32 mAdr;
	
	if(!getFlsItem_Addr(mFlsItem, mPart, &stAdr))
	{
		return FALSE;
	}
	
	mAdr = stAdr.adrS;
	while(mAdr != stAdr.adrE)
	{
		if(bSectorFir_IsThisMachineLoop(pDev, stAdr.chip, mAdr))
		{
			*pRtnSecFirAdr = mAdr;
			return TRUE;
		}
		mAdr = FlsItm_sectorNext_start(mAdr, mFlsItem, &stAdr);
	}
	
	return FALSE;
}
/******************************************************************************
* FUNC: // 
*   IN:
*  OUT: 
******************************************************************************/
static void relateDete_change(U8 mOpeaCls, 
						TFlsRelateDeteOne_st *pInFlash,
						TFlsRelateDeteOne_st *pNew)
{
U8 ii;

	switch(mOpeaCls)
	{
		case emFlsRelatDeteOpea_ChangeRelate:
			pInFlash->bRelated = pNew->bRelated;
			break;
			
		case emFlsRelatDeteOpea_ChangeNote:
			for(ii=0; ii<U_FLS_NOTE_BYTE_MAX; ii++)
			{
				pInFlash->note[ii] = pNew->note[ii];
			}
			break;
			
		case emFlsRelatDeteOpea_ChangeAll:
			pInFlash->bRelated = pNew->bRelated;
			for(ii=0; ii<U_FLS_NOTE_BYTE_MAX; ii++)
			{
				pInFlash->note[ii] = pNew->note[ii];
			}
			break;
			
		case emFlsRelatDeteOpea_ClrOne:
			relateDete_clrOne(pInFlash);
			break;
		// case emFlsRelatDeteOpea_Clr1Loop:
			// break;
			
		default:
			break;
	}
}


static void relateDete_clrOne(TFlsRelateDeteOne_st *pInFlash)
{
U8 *pBuf;

	pBuf = (U8*)(pInFlash);
	ClrRamIsFF(pBuf, U_FLS_RelateDete_One_BYTE_MAX);
}


static BOOL relateDete_add(U8 mOpeaCls, 
						TFlsRelateDeteOne_st *pInFlash,
						TFlsRelateDeteOne_st *pNew)
{
U8 ii;
BOOL bChanged = FALSE;

	switch(mOpeaCls)
	{
		case emFlsRelatDeteOpea_ChangeRelate:
			pInFlash->bRelated = pNew->bRelated;
			bChanged = TRUE;
			break;
			
		case emFlsRelatDeteOpea_ChangeNote:
			for(ii=0; ii<U_FLS_NOTE_BYTE_MAX; ii++)
			{
				pInFlash->note[ii] = pNew->note[ii];
			}
			bChanged = TRUE;
			break;
			
		case emFlsRelatDeteOpea_ChangeAll:
			pInFlash->bRelated = pNew->bRelated;
			for(ii=0; ii<U_FLS_NOTE_BYTE_MAX; ii++)
			{
				pInFlash->note[ii] = pNew->note[ii];
			}
			bChanged = TRUE;
			break;
			
		case emFlsRelatDeteOpea_ClrOne:
		default:
			break;
	}
	
	if(bChanged)
	{
		pInFlash->stDev = pNew->stDev;
		pInFlash->mType = pNew->mType;
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/******************************************************************************
* FUNC: // RAM��ҵ���λ�ã�����ӣ�
*   IN:
*  OUT: 
******************************************************************************/

static BOOL relateDete_findSpaceAndNew(U8 mOpeaCls, 
									  U8 *pSectBufS, U32 mAdrOffsetJdgStart, 
									  TFlsRelateDeteOne_st *pOne)
{
U32 mOffstAdr;
TFlsRelateDeteOne_st *pRelatDete;

	if((mOpeaCls) == emFlsRelatDeteOpea_ClrOne)
	{
		return TRUE; // �������δ�ҵ���ַ��Ҳ��ɹ���
	}
	else // add �ࣺ
	{
		if(bFoundInRam_Space(pSectBufS, mAdrOffsetJdgStart, &mOffstAdr))
		{
			pRelatDete = (TFlsRelateDeteOne_st*)(pSectBufS + mOffstAdr);
			relateDete_clrOne(pRelatDete);
			relateDete_add(mOpeaCls, pRelatDete, pOne);
			return TRUE;
		}
		return FALSE; // δ�ҵ��յĴ洢�ռ�
	}
	
}

/******************************************************************************
* FUNC: // 
*   IN:
*  OUT: 
******************************************************************************/
// �ж�buf�ڣ�ͬ��ַdete, ����equal:
// ������ emFlsRelatDeteOpea_ClrOne;
BOOL flsRelateDete_OneDeteEquSet(U8 *pSecBufS, 
						 U8 mOpeaCls, 
						 TFlsRelateDeteOne_st *pOne)
{
U32 mOffstAdr;
U8 ii;
TFlsRelateDeteOne_st *pRelatDete;
U8 mFlsItem = getFlsItem_RelateDete();
U32 mOffsetMax = getFlsItem_1SectorBytes(mFlsItem);
	
	mOffstAdr = U_FLS_RelateDete_One_BYTE_MAX;
	// ��֤һ���ռ�:
	while((mOffstAdr + U_FLS_RelateDete_One_BYTE_MAX) <= mOffsetMax)
	{
		pRelatDete = (TFlsRelateDeteOne_st*)(pSecBufS + mOffstAdr);
		if(bEquLoop_RelatDeteAndDev(pRelatDete, &pOne->stDev))
		{
			break;
		}
		mOffstAdr += U_FLS_RelateDete_One_BYTE_MAX;
	}
	
	if(((mOffstAdr + U_FLS_RelateDete_One_BYTE_MAX) >= mOffsetMax))
	{
		return FALSE;
	}
	else
	{
		switch(mOpeaCls)
		{
		case emFlsRelatDeteOpea_ChangeRelate:
			return ((pRelatDete->bRelated) == (pOne->bRelated));

		case emFlsRelatDeteOpea_ChangeAll:
			if (!((pRelatDete->bRelated) == (pOne->bRelated)))
			{
				return FALSE;
			}
			// �� break;
		case emFlsRelatDeteOpea_ChangeNote:
			for (ii=0; ii<U_FLS_NOTE_BYTE_MAX; ii++)
			{
				if (!((pRelatDete->note[ii]) == (pOne->note[ii])))
				{
					return FALSE;
				}
			}
			return TRUE;

		default:
			break;
		}
	}
	return FALSE;
}

/******************************************************************************
* FUNC: // 
*   IN:
*  OUT: 
******************************************************************************/
// RAM ���޸����ݡ�
// IN: Ҫ��: pSecBufS.max = getFlsItem_1SectorBytes(mFlsItem);
// ��ɾ�����ҵ�һ���Ժ�Ҫ�����ң���buf�ѿգ�allSetFF;
// Ҫ��master: ����ӣ�ע��sectorHead;
BOOL flsRelateDete_OneRamChange(U8 *pSecBufS, 
						 TFlsRelateDeteHead_st *pHead, 
						 TFlsRelateDeteOne_st *pOne)
{
U8 mFlsItem = getFlsItem_RelateDete();
U32 mOffsetMax = getFlsItem_1SectorBytes(mFlsItem);
U32 mOffstAdr;
TFlsRelateDeteOne_st *pRelatDete;
BOOL bFound = FALSE;

	if(pHead->mOpeaCls == emFlsRelatDeteOpea_ClrOne)
	{
		ClrRamIsFF(pSecBufS, mOffsetMax);
		return TRUE;
	}
	
	mOffstAdr = U_FLS_RelateDete_One_BYTE_MAX;
	// ��֤һ���ռ�:
	while((mOffstAdr + U_FLS_RelateDete_One_BYTE_MAX) <= mOffsetMax)
	{
		if(bFoundInRam_EquMachineLoop(&pOne->stDev, 
							  pSecBufS, mOffstAdr,
							  &mOffstAdr))
		{
			pRelatDete = (TFlsRelateDeteOne_st*)(pSecBufS + mOffstAdr);
			pRelatDete = (TFlsRelateDeteOne_st*)(pSecBufS + mOffstAdr);
			relateDete_change(pHead->mOpeaCls, 
						pRelatDete, pOne);
			bFound = TRUE;
			mOffstAdr += U_FLS_RelateDete_One_BYTE_MAX;
			break;
		}
		else
		{
			mOffstAdr += U_FLS_RelateDete_One_BYTE_MAX;
			continue;
		}
	}

	if(bFound == FALSE)
	{
		return relateDete_findSpaceAndNew(pHead->mOpeaCls, 
									pSecBufS, mOffstAdr, pOne);
	}
	else // ���ҵ��������� �ص�ַ�ģ�
	{
		// ������Ķ�ɾ��
		pHead->mOpeaCls = emFlsRelatDeteOpea_ClrOne; 
		
		while((mOffstAdr + U_FLS_RelateDete_One_BYTE_MAX) <= mOffsetMax)
		{
			if(bFoundInRam_EquMachineLoop(&pOne->stDev, 
								  pSecBufS, mOffstAdr,
								  &mOffstAdr))
			{
				pRelatDete = (TFlsRelateDeteOne_st*)(pSecBufS + mOffstAdr);
				relateDete_clrOne(pRelatDete);
			}
			mOffstAdr += U_FLS_RelateDete_One_BYTE_MAX;
		}
		return TRUE; 
	}
	
}

/******************************************************************************
* FUNC: //
*   IN: use pDev.machine,loop;
*  OUT: 
******************************************************************************/

// ��� flash ÿ��·��Ƿ��ַ���� 0x1000/U_FLS_RelateDete_One_BYTE_MAX:
BOOL bFlsRelateDete_LoopFull(void)
{
U8 mPart;
TFlsItemAddr stAdr;
BOOL bError = FALSE;
U32 mFlsAdr;
U8 mFlsItem = getFlsItem_RelateDete();
U32 m1SectorByte = getFlsItem_1SectorBytes(mFlsItem);
	
	for(mPart=0; mPart<FlsItem_PartMax(mFlsItem); mPart++)
	{
		if(!getFlsItem_Addr(mFlsItem, mPart, &stAdr))
		{
			continue;
		}
		if(!bFlsItem_IsReadAllow(mFlsItem, mPart))
		{
			bError = TRUE;
			Set_FlsItemState(U_FlsItem_Error_State, mFlsItem, mPart);
			continue;
		}
		
		for(mFlsAdr=stAdr.adrS; mFlsAdr<stAdr.adrE; mFlsAdr+=m1SectorByte)
		{
			if(!bFlsRelateDete_OneLoopRight(stAdr.chip, mFlsAdr))
			{
				bError = TRUE;
				Set_FlsItemState(U_FlsItem_Error_State, mFlsItem, mPart);
			}
		}
		
	}
	return bError;
}


// �ж� 1sector ��ȷ��
// OUT: TRUE = !FULL & EquLoop;
BOOL bFlsRelateDete_OneLoopRight(U8 mChip, U32 mFromAdr)
{
U8 *pBufS;
U32 mOffstAdr;
TFlsRelateDeteOne_st *pRelatDete;
U8 *pBufNow;
TDev_un stDev;
U8 mFlsItem = getFlsItem_RelateDete();
U32 mOffsetMax = getFlsItem_1SectorBytes(mFlsItem);

	pBufS = pFlsHd_GetBufS();
	FlsHd_Read_nByte(mChip, pBufS, 
					getFlsItem_1SectorBytes(mFlsItem), mFromAdr);
	
	// first item:
	mOffstAdr = U_FLS_RelateDete_One_BYTE_MAX;
	pBufNow = pBufS + mOffstAdr;
	pRelatDete = (TFlsRelateDeteOne_st*)(pBufNow);
	// first is space:
	if(!bDevOk(&pRelatDete->stDev)) 
	{
		mOffstAdr += U_FLS_RelateDete_One_BYTE_MAX;
		return bJdgInRam_AllSpace(pBufS, mOffstAdr);
		
	}
	else // first valid:
	{
		mOffstAdr += U_FLS_RelateDete_One_BYTE_MAX;
		stDev = pRelatDete->stDev;
		
		while((mOffstAdr + U_FLS_RelateDete_One_BYTE_MAX) <= mOffsetMax)
		{
			pBufNow = pBufS + mOffstAdr;
			pRelatDete = (TFlsRelateDeteOne_st*)(pBufNow);
			if(bDevOk(&pRelatDete->stDev))
			{
				if(bEquLoop_RelatDeteAndDev(pRelatDete, &stDev))
				{
					mOffstAdr += U_FLS_RelateDete_One_BYTE_MAX;
					continue;
				}
				else
				{
					return FALSE; // �в�ͬ��·��dev����
				}
			}
			else //֮���ж�space;
			{
				break;
			}
			
		}
		
		// !FULL:
		// TRUE=֮����space;
		if((mOffstAdr + U_FLS_RelateDete_One_BYTE_MAX) <= mOffsetMax)
		{
			return bJdgInRam_AllSpace(pBufS, mOffstAdr);
		}
		else // ����
		{
			return FALSE;
		}
		
	}
	
}

/******************************************************************************
* FUNC: // 
*   IN:
*  OUT: 
******************************************************************************/
// ��RAM���жϣ��ж�ĳdete��ɾ����
BOOL bJdgInRam_FlsRelateDete_HaveClr(U8 *pSecBufS,
						 TFlsRelateDeteOne_st *pOne)
{
U32 mAdrOffset;

	// ��RAM����� ��ͬ�� dete:
	if(bFoundInRam_EquDete(&pOne->stDev, 
							  pSecBufS, 
							  U_FLS_RelateDete_One_BYTE_MAX,
							  &mAdrOffset))
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
							  
}

/******************************************************************************
* FUNC: // 
*   IN:
*  OUT: 
******************************************************************************/
// ��RAM���жϣ��ж�ĳ��ַ����������һ�£�
BOOL bJdgInRam_FlsRelateDete_EquSet(U8 *pSecBufS, 
						 TFlsRelateDeteHead_st *pHead, 
						 TFlsRelateDeteOne_st *pOne)
{
	
U8 mAddr;

	if(pHead->mAddrS == pHead->mAddrE)
	{
		pHead->mAddrE = pHead->mAddrS + 1;
	}
	
	for(mAddr=pHead->mAddrS; mAddr!=pHead->mAddrE; mAddr++)
	{
		pOne->stDev.stDete.field = mAddr;
		
		// �ж�buf�ڣ�ͬ��ַdete, ����equal:
		// ������ emFlsRelatDeteOpea_ClrOne;
		flsRelateDete_OneDeteEquSet(pSecBufS, 
					pHead->mOpeaCls, pOne);
	}
	return TRUE;
}


/******************************************************************************
* FUNC: // 
*   IN:
*  OUT: 
******************************************************************************/

// RAM ���޸����ݡ�
// IN: Ҫ��: pSecBufS.max = getFlsItem_1SectorBytes(mFlsItem);
// ��������ַ�Ĳ�������pHead�
BOOL FlsRelateDete_RamChange(U8 *pSecBufS, 
						 TFlsRelateDeteHead_st *pHead, 
						 TFlsRelateDeteOne_st *pOne)
{
U8 mAddr;

	if(pHead->mAddrS == pHead->mAddrE)
	{
		return flsRelateDete_OneRamChange(pSecBufS, 
						 pHead, pOne);
	}
	else
	{
		for(mAddr=pHead->mAddrS; mAddr!=pHead->mAddrE; mAddr++)
		{
			pOne->stDev.stDete.field = mAddr;
			flsRelateDete_OneRamChange(pSecBufS, 
						 pHead, pOne);
		}
		return TRUE;
	}
	
}
					
/******************************************************************************
* FUNC: // 
*   IN:
*  OUT: 
******************************************************************************/	

BOOL FlsRd_isRelateDete(TDev_un *pDev)
{
U8 mFlsItem = getFlsItem_RelateDete();
U32 m1SectorByte = getFlsItem_1SectorBytes(mFlsItem);
U8 mPart;
U32 mFlsAdr;
U32 mOffsetAdr;
U8 *pBufS;
TFlsItemAddr stAdr;
TFlsRelateDeteOne_st *pRelatDete;

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
		// ���� ��ͬ��·��sector��
		if(!bFlsRelateDete_FoundEquMachineLoopSector( 
				pDev, mPart, &mFlsAdr))
		{
			return FALSE;
		}
		mFlsAdr = FlsItm_sector_start(mFlsAdr, mFlsItem);
				
		pBufS = pFlsHd_GetBufS();
		FlsHd_Read_nByte(stAdr.chip, pBufS, m1SectorByte, mFlsAdr);
		
		// ��RAM����� ��ͬ�� dete:
		if(bFoundInRam_EquDete(pDev, pBufS, 0,
							  &mOffsetAdr))
		{
			pRelatDete = (TFlsRelateDeteOne_st*)(pBufS + mOffsetAdr);
			return (pRelatDete->bRelated);
		}
		return FALSE;
		
	}
	return FALSE;
}


/******************************************************************************
* FUNC: //
******************************************************************************/
BOOL FlsRd_RelateDete_Note(TDev_un *pDev, U8 *pRtnNote)
{
U8 mFlsItem = getFlsItem_RelateDete();
U32 m1SectorByte = getFlsItem_1SectorBytes(mFlsItem);
U8 mPart;
U32 mFlsAdr;
U32 mOffsetAdr;
U8 *pBufS;
TFlsItemAddr stAdr;
TFlsRelateDeteOne_st *pRelatDete;

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
		// ���� ��ͬ��·��sector��
		if(!bFlsRelateDete_FoundEquMachineLoopSector( 
				pDev, mPart, &mFlsAdr))
		{
			return FALSE;
		}
		mFlsAdr = FlsItm_sector_start(mFlsAdr, mFlsItem);
				
		pBufS = pFlsHd_GetBufS();
		FlsHd_Read_nByte(stAdr.chip, pBufS, m1SectorByte, mFlsAdr);
		
		// ��RAM����� ��ͬ�� dete:
		if(bFoundInRam_EquDete(pDev, pBufS, 0,
							  &mOffsetAdr))
		{
			pRelatDete = (TFlsRelateDeteOne_st*)(pBufS + mOffsetAdr);
			
			// CopyNByte(U8 *pFrom, U8 *pTo, U32 byteTotal);
			CopyNByte(&pRelatDete->note[0], pRtnNote, U_FLS_NOTE_BYTE_MAX);
			
			pBufS = pRtnNote;
			for(mOffsetAdr=0; mOffsetAdr<U_FLS_NOTE_BYTE_MAX; mOffsetAdr++)
			{
				if(*pBufS == 0xFF)
				{
					*pBufS = 0;
					break; // 0xFF Ҳ����һ�� '/0'
				}
				pBufS++;
			}
			return TRUE;
		}
		return FALSE;		
	}
	return FALSE;
	
}



/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
// IN: mOpeaCls: emFlsRelateDeteOpeaCls ��һ:
// IN: mOpeaCls = emFlsRelatDeteOpea_Clr1Loop;
BOOL FlsSave_RelateDete_ClrOneLoop(
						TDev_un *pDev,
						U8 taskId, U8 flsId)
{
U8 *pBufS;
TFlsRelateDeteHead_st *pHead;
TFlsRelateDeteOne_st *pRelatDete;
	
	pBufS = pFlsHd_GetBufS();
	pHead = (TFlsRelateDeteHead_st*)(pBufS);
	pRelatDete = (TFlsRelateDeteOne_st*)(pBufS + U_FLS_RelateDete_Head_BYTE_MAX);
	
	pHead->mOpeaCls = emFlsRelatDeteOpea_Clr1Loop;
	pHead->mAddrS = pDev->stDete.field;
	pHead->mAddrE = pDev->stDete.field;
	pRelatDete->stDev = *pDev;
	pRelatDete->bRelated = FALSE;
	
	return FlashSaveNew(getFlsItem_RelateDete(), taskId, flsId, pBufS);
}


/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
// IN: mOpeaCls = emFlsRelatDeteOpea_ClrOne, 
//				emFlsRelatDeteOpea_ChangeRelate;
BOOL FlsSave_RelateDete_RelateOne(U8 mOpeaCls,
						TDev_un *pDev, BOOL bRelate,
						U8 taskId, U8 flsId)
{
U8 *pBufS;
TFlsRelateDeteHead_st *pHead;
TFlsRelateDeteOne_st *pRelatDete;
	
	switch(mOpeaCls)
	{
		case emFlsRelatDeteOpea_ClrOne:
		case emFlsRelatDeteOpea_ChangeRelate:
			break; // ����
			
		case emFlsRelatDeteOpea_ChangeNote:
		case emFlsRelatDeteOpea_ChangeAll:
		case emFlsRelatDeteOpea_Clr1Loop:
		default:
			return FALSE;
	}
	pBufS = pFlsHd_GetBufS();
	pHead = (TFlsRelateDeteHead_st*)(pBufS);
	pRelatDete = (TFlsRelateDeteOne_st*)(pBufS + U_FLS_RelateDete_Head_BYTE_MAX);
	
	pHead->mOpeaCls = mOpeaCls;
	pHead->mAddrS = pDev->stDete.field;
	pHead->mAddrE = pDev->stDete.field;
	pRelatDete->stDev = *pDev;
	pRelatDete->bRelated = bRelate;
	
	return FlashSaveNew(getFlsItem_RelateDete(), taskId, flsId, pBufS);
}


/******************************************************************************
* FUNC: //
******************************************************************************/
// IN: mOpeaCls = emFlsRelatDeteOpea_ChangeRelate;
BOOL FlsSave_RelateDete_RelateSerial(
						TFlsRelateDeteHead_st *pRelateHead,
						TDev_un *pDev, BOOL bRelate,
						U8 taskId, U8 flsId)
{
U8 *pBufS;
TFlsRelateDeteHead_st *pHead;
TFlsRelateDeteOne_st *pRelatDete;
	
	pBufS = pFlsHd_GetBufS();
	pHead = (TFlsRelateDeteHead_st*)(pBufS);
	pRelatDete = (TFlsRelateDeteOne_st*)(pBufS + U_FLS_RelateDete_Head_BYTE_MAX);
	
	*pHead = *pRelateHead;
	pRelatDete->stDev = *pDev;
	
	pRelatDete->bRelated = bRelate;
	
	return FlashSaveNew(getFlsItem_RelateDete(), taskId, flsId, pBufS);

}



/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
// IN: mOpeaCls = emFlsRelatDeteOpea_ChangeNote, 
//				emFlsRelatDeteOpea_ChangeRelate;
//				emFlsRelatDeteOpea_ChangeAll ;
BOOL FlsSave_RelateDete_One(U8 mOpeaCls,
						TDev_un *pDev, 
						 BOOL bRelate, U8 *pNote,
						U8 taskId, U8 flsId)
{
U8 *pBufS;
TFlsRelateDeteHead_st *pHead;
TFlsRelateDeteOne_st *pRelatDete;
	
	pBufS = pFlsHd_GetBufS();
	pHead = (TFlsRelateDeteHead_st*)(pBufS);
	pRelatDete = (TFlsRelateDeteOne_st*)(pBufS + U_FLS_RelateDete_Head_BYTE_MAX);
	
	pRelatDete->stDev = *pDev;
	
	switch(mOpeaCls)
	{
			
		case emFlsRelatDeteOpea_ChangeAll:
			pRelatDete->bRelated = bRelate;
			// ����next, ����break;
		case emFlsRelatDeteOpea_ChangeNote:
			// CopyNByte(U8 *pFrom, U8 *pTo, U32 byteTotal);
			CopyNByte(pNote, &pRelatDete->note[0], U_FLS_NOTE_BYTE_MAX);
			break;
			
		case emFlsRelatDeteOpea_ChangeRelate:
			pRelatDete->bRelated = bRelate;
			break; // ����
			
		case emFlsRelatDeteOpea_ClrOne:
		case emFlsRelatDeteOpea_Clr1Loop:
			break; // ���� // ��2��Ҳ˳����Ӧ 
			
		default:
			return FALSE;
	}
	pHead->mOpeaCls = mOpeaCls;
	pHead->mAddrS = pDev->stDete.field;
	pHead->mAddrE = pDev->stDete.field;
	
	return FlashSaveNew(getFlsItem_RelateDete(), taskId, flsId, pBufS);

}




/******************************************************************************
* FUNC: // END
*   IN:
*  OUT: 
******************************************************************************/
