#define __flsInqPoint_C__
/******************************************************************************
* @file    flsInqPoint.c    // Inquire.
* @author  yx
* @version V1.1�� 2013-07-07
* @date    2013-07-05
* @brief   flsQueue���͵Ĵ洢������ʵ�ʵ� head & end.
* 
Ҫ��
pProp->itemBytes �� U_FLASH_1_SECTOR ֻ����sector������ʹ�ã�
over sectorͨ�� FlsItm_sector_start()��ʹ�á�

�����ԣ���sim1_flsInqPoit����sim2_flsInqPoit��
U_SectMAX =  2 sector�� OK.
0x100bytes/sector�� OK��
ֻ��2sectorʱ���㷨������

// U_SIGN_bHaveTested; 2013-07-07
******************************************************************************/

/******************************************************************************

һ��һ���洢�����:
��sectorĩβend=0xX FF��ʱ,
	1:����nextSector + Jdg; end ���䣻��head==nextSectorHead,head+=1Sector;
	2:д0xX FF��     + Jdg; end = nextSectorHead;
	3:дhead         + Jdg; end = 0xX 10. 
//��power off + ��1:������δִ��, Jdg end = 0xX FF��head����;
//��power off + ��2:д0xX FF����δִ��, Jdg end = 0xX FF��head = nextSectorHead;
//��power off + ��3:дhead��δִ��, Jdg end = 0xX 00��head = nextSectorHead;

******************************************************************************/
#include  "flsInqPoint.h"

#include  "flsStoreBytesDef.h"
#include  "strFlsItmStrCacu.h"
#include  "strFlsAdrDef.h"
#include  "flsAdrCalculate.h"
#include  "strFlsItmStruct.h"
#include  "strFlsQue.h"
// #include  "strDevice.h"
// #include  "fls_Interface.h"

#if U_SYS_Test_Flash_InqPoint == 1
	#if U_SYS_Test_Flash_InqPoint_SimX == 1
		#include  "sim1_flsInqPoit.h"
	#elif U_SYS_Test_Flash_InqPoint_SimX == 2
		#include  "sim2_flsInqPoit.h"
	#endif // U_SYS_Test_Flash_InqPoint_SimX
#endif // U_SYS_Test_Flash_InqPoint

//#include "incFile.h"	

/*================= �ṹ���� ========================================*/
/*================= ˽�б��� ========================================*/
static TFlsQueueProp stFlsQueueItemProp;
static TFlsQueueProp *pProp = &stFlsQueueItemProp;

/*================= ˽�к��� ========================================*/
static void setFlsQueue_head(U8 mPart, U8 mFlsItem, U32 flsAdr);
static void setFlsQueue_end(U8 mPart, U8 mFlsItem, U32 flsAdr);

/* *****************************************************************************
================= //Pseudocode: Inquire point  ====================================

SectHead ,  SectEnd :  head,end���ڵ�Sector.
Sect# : �м�¼;   Sect^ :�޼�¼��

��Sect0 = Sect# | Sect^;
	1. Sect0 = Sect#:
	   һֱ�ж�Sect#��ֱ��Sect^����Sect^ǰ��Sect# | Sect^��ʼ����SectEnd����Ҫ�ж�pointEnd��λ�á�
		��ֱ��ĩβ��Sect#, ��Error. ���߼����ж�ʱ�����ָ���
		һֱ��ֱ��Sect#����Sect#��SectHead��
		  ��ֱ��ĩβ��Sect^��   ��Sect0 ��SectHead��
	2. Sect0 = Sect^:
	   һֱ�ж�Sect^��ֱ��Sect#����Sect#��SectHead��
		��ֱ��ĩβ��Sect^, pointHead = pointEnd = 0.
		һֱ��Sect#��ֱ��Sect^����Sect# | Sect^��ʼ����SectEnd����Ҫ�ж�pointEnd��λ�á�
		  ��ֱ��ĩβ��Sect#��   ��Sect0 | SectE ��SectEnd��


===========================================================================

дSect�����һ��ǰ����Ҫ��clrNextSector�������������ȫSect#�������
��������2Sector�ǿ�: Ԥд�����1Sector����������EraseNextSector����ʱPowerOff, ����2Sector�ǿա�

===========================================================================

***************************************************************************** */


/*=================  ================================================*/
/******************************************************************************
* NAME: �� �ⲿ�����ӿڣ��й�flash���ġ�
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/


BOOL flsInq__bFlsRd_Sector_HaveRecord(U8 chip, U32 mAdr, U8 mFlsItem) //Flash Sector Start OK.
{
#if U_SYS_Test_Flash_InqPoint == 1
	return sim_FlsInqPoit_bSectHaveRecord(chip, mAdr, mFlsItem);
#else  // U_SYS_Test_Flash_InqPoint

	return       bFlsSectorStart_isItem(chip, mAdr, mFlsItem);

#endif // U_SYS_Test_Flash_InqPoint
}


BOOL flsInq__bFlsRd_Record_isOk(U8 chip, U32 mAdr, U8 mFlsItem) // one OK 
{
#if U_SYS_Test_Flash_InqPoint == 1
	return sim_FlsInqPoit_b_1Item_OK(chip, mAdr);
#else  // U_SYS_Test_Flash_InqPoint
	return bFlsQueRd_OneItem_isOK(chip, mAdr, mFlsItem);

#endif // U_SYS_Test_Flash_InqPoint
	
}

/******************************************************************************
* NAME: 
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

/******************************************************************************
* FUNC: // ����ĩ��space��sector����sector�� 0~ space��λ�á�
*   IN: 
*  OUT: 
// U_SIGN_bHaveTested; 2013-07-06
******************************************************************************/
BOOL flsInqItm_inSect_EndSpace(
				TFlsItemAddr *pAdr, U32 *pRtnAdr
				)
{
U32 adr_Space = ~0;
	
	if(!flsInqSect_LastItmSpace_EtoS(pAdr, &adr_Space))
	{
		return FALSE;
	}
	else
	{
		return (flsInq_space_inSector_0toH(pAdr->chip, adr_Space, pRtnAdr));
	}

}

/******************************************************************************
* FUNC: // ���� sector �� ĩ�� space �ġ�
*   IN: 
*  OUT: *pRtnAdr = Sect LastItem space 

// U_SIGN_bHaveTested; 2013-07-06
******************************************************************************/

BOOL flsInqSect_LastItmSpace_EtoS(TFlsItemAddr *pAdr, U32 *pRtnAdr)
{
U8 chip = pAdr->chip;
U32 adr_beforeSect = ~0;
U32 adr_inSectLastItem = ~0;
U32 adr_sectStart = ~0;

	adr_sectStart = pAdr->adrE;
	while(adr_sectStart != pAdr->adrS)
	{
		adr_beforeSect     = FlsItm_sectorBefore_start   (adr_sectStart,  pProp->mFlsItem, pAdr);
		adr_inSectLastItem = FlsItm_adr_sector_LastItem(adr_beforeSect, pProp->mFlsItem, pProp->itemBytes);
		if(!flsInq__bFlsRd_Record_isOk(chip, adr_inSectLastItem, pProp->mFlsItem)) //ĩ���޼�¼
		{
			*pRtnAdr = adr_inSectLastItem;
			return TRUE;
		}
		adr_sectStart = FlsItm_sector_start(adr_inSectLastItem, pProp->mFlsItem);
	}
	
	return FALSE;
	
}


/******************************************************************************
* FUNC: // ��󣬲��� bInquireSectorHaveData �� sector. ֻ�ж�sector.head.
*   IN: �� mAdrNow.next sector ��ʼ�� ~ adrE.
*   IN: bInquireSectorHaveData = FALSE: ��sector�޼�¼�ġ�
*  OUT: *pRtnAdr = Sect^|Sect#.start.

* U_SIGN_bHaveTested; 2013-07-05
******************************************************************************/

BOOL flsInqSect_headSpaOrHave_sectNextToE(
				TFlsItemAddr *pAdr, U32 mAdrNow, U8 mFlsItem, U32 *pRtnAdr,
				BOOL bInquireSectorHaveData
				)
{
U32 adr = ~0;
U8 bFound = ~0;
	
	mAdrNow = FlsItm_sector_start(mAdrNow, pProp->mFlsItem);
	if(mAdrNow == pAdr->adrE)
	{
		return FALSE;
	}
	
	adr = FlsItm_sectorNext_start(mAdrNow, pProp->mFlsItem, pAdr);
	while((adr != pAdr->adrE) && (adr != pAdr->adrS))
	{
		bFound = flsInq__bFlsRd_Sector_HaveRecord(pAdr->chip, adr, mFlsItem);
		if(!bInquireSectorHaveData) 
		{
			bFound = !(bFound);
		}
		
		if(bFound)
		{
			*pRtnAdr = adr;
			return TRUE;
		}
		
		if(adr == pAdr->adrE)
		{
			break;
		}
		adr = FlsItm_sectorNext_start(adr, pProp->mFlsItem, pAdr);
	}
	return FALSE;
}

/******************************************************************************
* FUNC: // ��󣬲��ҿյ�sector. ֻ�ж�sector.head.
		һֱ����Sect#, ֱ��Sect^. �� adrE.
*   IN: �� mAdrNow.next sector ��ʼ�� ~ adrE.
*  OUT: *pRtnAdr = Sect^.start.
******************************************************************************/

BOOL flsInqSect_headSpace_sectNextToE(
				TFlsItemAddr *pAdr, U32 mAdrNow, U8 mFlsItem, U32 *pRtnAdr
				)
{
	return flsInqSect_headSpaOrHave_sectNextToE(pAdr, mAdrNow, mFlsItem, pRtnAdr,
							  FALSE  ); // bInquireSector HaveData
}


/******************************************************************************
* FUNC: // ��󣬲����м�¼��sector. ֻ�ж�sector.head.
		һֱ����Sect^, ֱ��Sect#. �� adrE.
*   IN: �� mAdrNow.next sector ��ʼ�� ~ adrE.
*  OUT: *pRtnAdr = Sect#.start.
******************************************************************************/

BOOL flsInqSect_headHave_sectNextToE(
				TFlsItemAddr *pAdr, U32 mAdrNow, U8 mFlsItem, U32 *pRtnAdr
				)
{
	return flsInqSect_headSpaOrHave_sectNextToE(pAdr, mAdrNow, mFlsItem, pRtnAdr,
							  TRUE  ); // bInquireSector HaveData
	
}

/******************************************************************************
* FUNC: // ���һֱ����Sect^, ֱ��Sect#. 
*   IN:
*  OUT: 
******************************************************************************/
BOOL flsInq_Sector0_Have(TFlsItemAddr *pAdr, U8 mFlsItem)
{
	return flsInq__bFlsRd_Sector_HaveRecord( pAdr->chip, pAdr->adrS, mFlsItem);
}


/******************************************************************************
* FUNC: // ���һֱ����Sect#, ֱ��Sect^. 
*   IN:
*  OUT: sector�� 0 ~H, û�м�¼��adr.
	   FALSE = lastItem�м�¼��

// U_SIGN_bHaveTested; 2013-07-06
******************************************************************************/

BOOL flsInq_space_inSector_0toH(U8 chip, U32 mAdr, U32 *pRtnAdr)
{
U32 adr = ~0;
U32 adr_ItemLast = ~0;

	adr_ItemLast = FlsItm_adr_sector_LastItem(mAdr, pProp->mFlsItem, pProp->itemBytes);
	if(flsInq__bFlsRd_Record_isOk(chip, adr_ItemLast, pProp->mFlsItem)) //ĩ���м�¼
	{
		return FALSE;
	}
	else //ĩ���޼�¼
	{
		adr = FlsItm_adr_sector_firItem(mAdr, pProp->mFlsItem, pProp->itemBytes); //�ճ�������
		while(adr < adr_ItemLast)
		{
			if(!flsInq__bFlsRd_Record_isOk(chip, adr, pProp->mFlsItem)) //�޼�¼
			{
				*pRtnAdr = adr;
				return TRUE;
			}
			adr += pProp->itemBytes;
		}
		
		*pRtnAdr = adr_ItemLast;
		return TRUE;
	}
	
}

/******************************************************************************
* FUNC: // 
*   IN:
*  OUT: sector�� H ~0, �м�¼��adr.

// U_SIGN_bHaveTested; 2013-07-06
******************************************************************************/

BOOL flsInq_have_inSector_Hto0(U8 chip, U32 mAdr, U32 *pRtnAdr)
{
U32 adr = ~0;
U32 adr_ItemS = ~0;
	
	adr_ItemS = FlsItm_sector_start(mAdr, pProp->mFlsItem);
	adr = FlsItm_adr_sector_LastItem(mAdr, pProp->mFlsItem, pProp->itemBytes);
	
	while(adr != adr_ItemS)
	{
		if(flsInq__bFlsRd_Record_isOk(chip, adr, pProp->mFlsItem))
		{
			*pRtnAdr = adr;
			return TRUE;
		}
		adr -= pProp->itemBytes;
	}
	
	if(flsInq__bFlsRd_Record_isOk(chip, adr_ItemS, pProp->mFlsItem))
	{
		*pRtnAdr = adr_ItemS;
		return TRUE;
	}
	else //ȫ��
	{
		return FALSE;
	}
	
}




/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

/******************************************************************************
* FUNC: // sector 0 �м�¼:
// U_SIGN_bHaveTested; 2013-07-06
******************************************************************************/

BOOL flsInq_1Cls_JdgPoint_Sector0_haveData(U8 mPart, U8 mFlsItem, TFlsItemAddr *pAdr)
{
U32 adr = ~0;
U32 adr_FirstSpaceSect = ~0;
U32 adr_FirstSpaceAdr = ~0;
U32 adr_HaveSect = ~0;
U8 bFound = ~0;
	
	bFound = flsInqSect_headSpace_sectNextToE(
				pAdr, pAdr->adrS, mFlsItem, &adr_FirstSpaceSect
				);
	if(!bFound)
	{
		//all Sector �м�¼, 
		//���������һ��û�е� :
		if(!flsInqItm_inSect_EndSpace(
						pAdr, &adr_FirstSpaceAdr
						))
		{
			return FALSE;
		}
		else
		{
			setFlsQueue_end(mPart, mFlsItem, adr_FirstSpaceAdr);
			adr_HaveSect = FlsItm_sectorNext_start(
						adr_FirstSpaceAdr, pProp->mFlsItem, pAdr);
			
			setFlsQueue_head(mPart, mFlsItem, adr_HaveSect);
			return TRUE;
		}
	}
	else
	{
		adr = FlsItm_sectorBefore_start(adr_FirstSpaceSect, pProp->mFlsItem, pAdr);
		bFound = flsInq_space_inSector_0toH(pAdr->chip, adr, &adr_FirstSpaceAdr);
		if(bFound)
		{
			setFlsQueue_end(mPart, mFlsItem, adr_FirstSpaceAdr);
		}
		else
		{
			setFlsQueue_end(mPart, mFlsItem, adr_FirstSpaceSect);
			//setFlsQueue_end(mPart, mFlsItem, *****
			//			FlsItm_adr_itemNext(adr_FirstSpaceSect, pProp->mFlsItem, pProp->itemBytes, pAdr)
			//			);
		}
		
		//������head:
		bFound = flsInqSect_headHave_sectNextToE(
								pAdr, adr_FirstSpaceSect, mFlsItem, 
								&adr_HaveSect
								);
		if(!bFound)
		{
			setFlsQueue_head(mPart, mFlsItem, pAdr->adrS);
		}
		else
		{
			setFlsQueue_head(mPart, mFlsItem, adr_HaveSect);
		}
		return TRUE;
	}
}


/******************************************************************************
* FUNC: // sector 0 �޼�¼:
// U_SIGN_bHaveTested; 2013-07-06
******************************************************************************/

BOOL flsInq_1Cls_JdgPoint_Sector0_space(U8 mPart, U8 mFlsItem, TFlsItemAddr *pAdr)
{
U32 adr = ~0;
U32 adr_SectFirst_Have = ~0;
U32 adr_EndHaveData = ~0;
U32 adr_SpaceSect = ~0;
BOOL bFound = ~0;
	

		bFound = flsInqSect_headHave_sectNextToE(
								pAdr, pAdr->adrS, mFlsItem, 
								&adr_SectFirst_Have
								);
		if(!bFound)
		{
			//all space
			setFlsQueue_head(mPart, mFlsItem, pAdr->adrS);
			setFlsQueue_end (mPart, mFlsItem, pAdr->adrS);
			return TRUE; 
		}
		else //���ҵ� adr_SectFirst_Have
		{
			setFlsQueue_head(mPart, mFlsItem, adr_SectFirst_Have);
			//������end:
			bFound = flsInqSect_headSpace_sectNextToE(
									pAdr, adr_SectFirst_Have, mFlsItem, 
									&adr_SpaceSect
									);
			if(!bFound)
			{
				adr_SpaceSect = pAdr->adrS;
			}
			
			adr = FlsItm_sectorBefore_start(adr_SpaceSect, pProp->mFlsItem, pAdr);
			bFound = flsInq_have_inSector_Hto0(pAdr->chip, adr, &adr_EndHaveData);	
			if(!bFound)
			{
				if(flsInq__bFlsRd_Sector_HaveRecord(pAdr->chip, adr, mFlsItem))
				{
					setFlsQueue_end(mPart, mFlsItem, 
							FlsItm_adr_sector_firItem(adr, pProp->mFlsItem, pProp->itemBytes));
				}
				else
				{
					setFlsQueue_end(mPart, mFlsItem, adr_SpaceSect);
				}
			}
			else
			{
				adr = FlsItm_adr_itemNext(adr_EndHaveData, pProp->mFlsItem, pProp->itemBytes, pAdr);
				setFlsQueue_end(mPart, mFlsItem, adr);
			}
			return TRUE;
				
		}
		

}


/******************************************************************************
* FUNC: // 
*   IN:
*  OUT: 
******************************************************************************/
U32 vInqPointHead;
U32 vInqPointEnd;
static void setFlsQueue_head(U8 mPart, U8 mFlsItem, U32 flsAdr)
{
	vInqPointHead = flsAdr;
}
static void setFlsQueue_end(U8 mPart, U8 mFlsItem, U32 flsAdr)
{
	vInqPointEnd = flsAdr;
}


/******************************************************************************
* FUNC: // ����.c��ĺ�������Ҫ�ȳ�ʼ��������
*   IN:
*  OUT: 
******************************************************************************/
BOOL flsInq_SetQueueProp(U8 mFlsItem, U8 mPart)
{
	return FlsQueue_Prop(mFlsItem, mPart, &stFlsQueueItemProp);
}

/******************************************************************************
* FUNC: // 
*   IN:
*  OUT: 
* �жϵ�end�п����� sector.0��ַ��
******************************************************************************/

BOOL flsInq_1Cls_JdgPoint(U8 mFlsItem, U8 mPart, TFlsQueuePoint_st *pRtnHeadEnd)
{
TFlsItemAddr stAdr;
BOOL bResult;


	
	if(!FlsQueue_Prop(mFlsItem, mPart, &stFlsQueueItemProp))
	{
		return FALSE;
	}
	stAdr = stFlsQueueItemProp.stAdr;

 	pRtnHeadEnd->headAdr = stFlsQueueItemProp.stAdr.adrS;
	pRtnHeadEnd->endAdr  = pRtnHeadEnd->headAdr;
	
	if(flsInq_Sector0_Have(&stAdr, mFlsItem))
	{
		bResult = flsInq_1Cls_JdgPoint_Sector0_haveData(
					mPart, mFlsItem, &stAdr);
	}
	else // sector0 space
	{
		bResult = flsInq_1Cls_JdgPoint_Sector0_space(
					mPart, mFlsItem, &stAdr);
	}
	
	if(bResult)
	{
		pRtnHeadEnd->headAdr = vInqPointHead;
		pRtnHeadEnd->endAdr  = vInqPointEnd;
	}
	return bResult;
}


/******************************************************************************
* FUNC: // END
*   IN:  
*  OUT: 
******************************************************************************/

