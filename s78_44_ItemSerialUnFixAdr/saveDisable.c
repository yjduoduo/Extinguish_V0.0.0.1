#define __saveDisable_C__
/******************************************************************************
* @file    saveDisable.c
* @author  yx
* @version V1.0
* @date    2013-01-04
* @brief   
* 
******************************************************************************/
#include  "saveDisable.h"

#include  "saveItem_incIn.h"

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

// 在RAM里查找 相同的 dete:
BOOL bFoundInRam_Dsab_EquDete(TDev_un *pDev, 
							  U8 *pBufS, U32 mAdrOffset,
							  U32 *pRtnOffset)
{
U32 mOffstAdr;
U8 mFlsItem = getFlsItem_Disable();
U32 mOffsetMax = getFlsItem_1SectorBytes(mFlsItem);
U8 *pBufNow;
TFlsDisable_un *pDsabOne;
	
	mOffstAdr = mAdrOffset;
	if(mAdrOffset < U_FLS_DISABLE_BYTE_MAX)
	{
		mOffstAdr = U_FLS_DISABLE_BYTE_MAX;
	}
	
	// 保证一条空间:
	while((mOffstAdr + U_FLS_DISABLE_BYTE_MAX) <= mOffsetMax)
	{
		pBufNow = pBufS + mOffstAdr;
		pDsabOne = (TFlsDisable_un*)(pBufNow);
		
		if(bDevCompMask(U_DEV_ITEM_channel, 
					   &pDsabOne->stDisable.stDev, pDev))
		{
			*pRtnOffset = mOffstAdr;
			return TRUE;
		}
		
		mOffstAdr += U_FLS_DISABLE_BYTE_MAX;
	}
	
	return FALSE;
}


/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
// 在RAM里delete:
static BOOL bDeleteInRam_dsab(U8 *pBufS, U32 mAdrOffset)
{
U32 mOffstAdr;
U8 mFlsItem = getFlsItem_Disable();
U32 mOffsetMax = getFlsItem_1SectorBytes(mFlsItem);
U8 *pBufNow;
TFlsDisable_un *pDsabNow;
TFlsDisable_un *pDsabNext;
	
	mOffstAdr = U_FLS_DISABLE_BYTE_MAX;
	
	// 保证一条空间:
	while((mOffstAdr + (2*U_FLS_DISABLE_BYTE_MAX)) <= mOffsetMax)
	{
		pBufNow  = pBufS + mOffstAdr;
		pDsabNow = (TFlsDisable_un*)(pBufNow);
		pBufNow += U_FLS_DISABLE_BYTE_MAX;
		pDsabNext = (TFlsDisable_un*)(pBufNow);
		
		*pDsabNow = *pDsabNext;
		
		if(!bDevOk(&pDsabNow->stDisable.stDev))
		{
			pBufNow  = pBufS + mOffstAdr;
			ClrRamIsFF(pBufNow, (mOffsetMax - mOffstAdr));
			return TRUE;
		}
		else
		{
			mOffstAdr += U_FLS_DISABLE_BYTE_MAX;
			continue;
		}
		
	}
	
	if((mOffstAdr + (1*U_FLS_DISABLE_BYTE_MAX)) <= mOffsetMax)
	{
		pBufNow  = pBufS + mOffstAdr;
		ClrRamIsFF(pBufNow, (mOffsetMax - mOffstAdr));
	}
	return TRUE;
}

/******************************************************************************
* FUNC: //
******************************************************************************/
#include "lcdSub_ModeTextFig.h"
#include "codeFig.h"

//detect whether disabOne exist in the flash,exist return true
static BOOL DetectDsabOneInFlash(U8 *pBufS, TFlsDisable_un *pDsabOne)
{
    U32 mOffstAdr;
    U8 mFlsItem = getFlsItem_Disable();
    U32 mOffsetMax = getFlsItem_1SectorBytes(mFlsItem);
    U8 *pBufNow;
    TFlsDisable_un *pDsabNow;

    mOffstAdr = U_FLS_DISABLE_BYTE_MAX;
    //查看保存的内容是否存在,if same return
    while((mOffstAdr + (U_FLS_DISABLE_BYTE_MAX)) <= mOffsetMax)
    {
        pBufNow  = pBufS + mOffstAdr;
        pDsabNow = (TFlsDisable_un*)(pBufNow);
        //things is the same,so continue it
        //so if machine,addr,and loop are the same ,so don't save it
        if(U_FLS_DISABLE_BYTE_MAX == mOffstAdr){
            if(!bDevOk(&pDsabNow->stDisable.stDev)){
                break;
            }
        }
        if((pDsabNow->stDisable.stDev.stDete.field == pDsabOne->stDisable.stDev.stDete.field)
                &&(pDsabNow->stDisable.stDev.stDete.machine == pDsabOne->stDisable.stDev.stDete.machine)
                &&(pDsabNow->stDisable.stDev.stDete.boardLoop == pDsabOne->stDisable.stDev.stDete.boardLoop))
            return TRUE;
        if(bDevOk(&pDsabNow->stDisable.stDev))
        {
            mOffstAdr += U_FLS_DISABLE_BYTE_MAX;
            continue;
        }
        else
        {
            break;
        }
    }
    return FALSE;
}

static BOOL bAddInRam_dsab(U8 *pBufS, TFlsDisable_un *pDsabOne)
{
U32 mOffstAdr;
U8 mFlsItem = getFlsItem_Disable();
U32 mOffsetMax = getFlsItem_1SectorBytes(mFlsItem);
U8 *pBufNow;
TFlsDisable_un *pDsabNow;
	
    if(DetectDsabOneInFlash(pBufS,pDsabOne))//如果存在相同内容，返回
        return FALSE;
	mOffstAdr = U_FLS_DISABLE_BYTE_MAX;
	
	// 保证一条空间:
	while((mOffstAdr + (U_FLS_DISABLE_BYTE_MAX)) <= mOffsetMax)
	{
		pBufNow  = pBufS + mOffstAdr;
		pDsabNow = (TFlsDisable_un*)(pBufNow);
        //第一条读取的machine为FF，须对第一条进行处理
        if(U_FLS_DISABLE_BYTE_MAX == mOffstAdr){
            if(!bDevOk(&pDsabNow->stDisable.stDev)){
                *pDsabNow = *pDsabOne;
                return TRUE;
            }
        }
		
		if(bDevOk(&pDsabNow->stDisable.stDev))
		{
			mOffstAdr += U_FLS_DISABLE_BYTE_MAX;
			continue;
		}
		else 
		{
			*pDsabNow = *pDsabOne;
			return TRUE;
		}
	}
	return FALSE;

}



/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/


// RAM 里修改数据。
// IN: 要求: pSecBufS.max = getFlsItem_1SectorBytes(mFlsItem);
BOOL FlsDisable_RamChange(U8 *pSecBufS, 
						 TFlsDisable_un *pDsabOne)
{
U32 mAdrOffset;

	if(pDsabOne->stDisable.bAdd == TRUE)
	{
		return bAddInRam_dsab(pSecBufS, pDsabOne);
	}
	else
	{
		if(bFoundInRam_Dsab_EquDete(&pDsabOne->stDisable.stDev, 
							  pSecBufS, 0, &mAdrOffset))
		{
			return bDeleteInRam_dsab(pSecBufS, mAdrOffset);
		}
		else
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

BOOL FlsAdd_Disable(TDev_un *pDev, BOOL bDisable, 
								U8 taskId, U8 flsId)
{
U8 *pBufS;
TFlsDisable_un *pDsabOne;
	
	pBufS = pFlsHd_GetBufS();
	pDsabOne = (TFlsDisable_un*)(pBufS);
	
	pDsabOne->stDisable.stDev = *pDev;
	if(bDisable)
	{
		pDsabOne->stDisable.bAdd = TRUE;
	}
	else
	{
		pDsabOne->stDisable.bAdd = FALSE;
	}
	
	return FlashSaveNew(getFlsItem_Disable(), taskId, flsId, pBufS);
}

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
// if dete 是否在buf内：
// use: 不占用public buf.
BOOL FlsJdg_bDisableInBuf(TDev_un *pDev)
{
U8 mPart;
TFlsItemAddr stAdr;
U8 mBuf[U_FLS_DISABLE_BYTE_MAX]; // U_FLS_DISABLE_BYTE_MAX要求是2的倍数，以免read溢出
TFlsDisable_un *pDsabNow;
U32 mOffset;
U8 mFlsItem = getFlsItem_Disable();
U32 mOneSectorByteMax = getFlsItem_1SectorBytes(mFlsItem);
	

	
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
		break;
	}
	if(mPart >= FlsItem_PartMax(mFlsItem))
	{
		return FALSE;
	}
	
	
	mOffset = U_FLS_DISABLE_BYTE_MAX;
	while((mOffset + U_FLS_DISABLE_BYTE_MAX) <= mOneSectorByteMax)
	{
		FlsHd_Read_nByte(stAdr.chip, &mBuf[0], 
						U_FLS_DISABLE_BYTE_MAX, stAdr.adrS + mOffset);
		pDsabNow = (TFlsDisable_un*)(&mBuf[0]);
		if(bDevOk(&pDsabNow->stDisable.stDev))
		{
			if(bDevCompMask(U_DEV_ITEM_channel, 
					   &pDsabNow->stDisable.stDev, pDev))
			{
				return TRUE;
			}
		}
		else
		{
			break; // Buf end;
		}
		mOffset += U_FLS_DISABLE_BYTE_MAX;
	}

	return FALSE;
	
}



/******************************************************************************
* FUNC: // 
*   IN:
*  OUT: 
******************************************************************************/
// buf item:
// use: 不占用public buf.
U32 FlsGet_DisableBufItemNum(void)
{
U8 mPart;
TFlsItemAddr stAdr;
U8 mBuf[U_FLS_DISABLE_BYTE_MAX]; // U_FLS_DISABLE_BYTE_MAX要求是2的倍数，以免read溢出
TFlsDisable_un *pDsabNow;
U32 mOffset;
U8 mFlsItem = getFlsItem_Disable();
U32 mOneSectorByteMax = getFlsItem_1SectorBytes(mFlsItem);
	
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
		break;
	}
	if(mPart >= FlsItem_PartMax(mFlsItem))
	{
		return FALSE;
	}

	mOffset = U_FLS_DISABLE_BYTE_MAX;
	while((mOffset + U_FLS_DISABLE_BYTE_MAX) <= mOneSectorByteMax)
	{
		FlsHd_Read_nByte(stAdr.chip, &mBuf[0], 
						U_FLS_DISABLE_BYTE_MAX, stAdr.adrS + mOffset);
		pDsabNow = (TFlsDisable_un*)(&mBuf[0]);
		if(bDevOk(&pDsabNow->stDisable.stDev))
		{
			mOffset += U_FLS_DISABLE_BYTE_MAX;
			continue;
		}
		else
		{
			break;
		}
	}

	return ((mOffset / U_FLS_DISABLE_BYTE_MAX) - 1);
}


// TRUE = 允许读 有结果；
// FALSE = 定义错误，或禁止读。
// use: 不占用public buf.
BOOL FlsRd_DisableInBuf(U32 mSequ, BOOL *bRtnDevValid, 
								TFlsDisable_un *pRtnDsabOne)
{
U8 mPart;
TFlsItemAddr stAdr;
U8 mBuf[U_FLS_DISABLE_BYTE_MAX]; // U_FLS_DISABLE_BYTE_MAX要求是2的倍数，以免read溢出
TFlsDisable_un *pDsabNow;
U32 mOffset;
U8 mFlsItem = getFlsItem_Disable();
U32 mOneSectorByteMax = getFlsItem_1SectorBytes(mFlsItem);
	

	*bRtnDevValid = FALSE;
	
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
		break;
	}
	if(mPart >= FlsItem_PartMax(mFlsItem))
	{
		return FALSE;
	}
	
	
	
	// +1是 sectorHead.
	mOffset = (mSequ+1) * U_FLS_DISABLE_BYTE_MAX;
	if((mOffset + U_FLS_DISABLE_BYTE_MAX) > mOneSectorByteMax)
	{
		*bRtnDevValid = FALSE;
        return FALSE;
	}
	
	FlsHd_Read_nByte(stAdr.chip, &mBuf[0], 
					U_FLS_DISABLE_BYTE_MAX, stAdr.adrS + mOffset);
	pDsabNow = (TFlsDisable_un*)(&mBuf[0]);
	if(bDevOk(&pDsabNow->stDisable.stDev))
	{
		*pRtnDsabOne = *pDsabNow;
		*bRtnDevValid = TRUE;
	}
	else
	{
		*bRtnDevValid = FALSE;
	}
	return TRUE;
	
}


/******************************************************************************
* FUNC: // END
*   IN:
*  OUT: 
******************************************************************************/
