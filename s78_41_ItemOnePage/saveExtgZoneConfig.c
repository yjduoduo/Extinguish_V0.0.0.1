#define __saveExtgZoneConfig_C__
/******************************************************************************
* @file    saveExtgZoneConfig.c
* @author  yx
* @version V1.0
* @date    2013-10-24
* @brief   ������ ��������
* 
******************************************************************************/
#include  "saveExtgZoneConfig.h"

#include  "saveItem_incIn.h"

//#include "incFile.h"	


/*================= ���� ============================================*/
#define U_FLS_EXTG_ZONE_MAX   (U_SYS_LOOP_MAX)

/*================= �ṹ���� ========================================*/

/*================= ˽�нṹ�������� ================================*/

/*================= ���к������� ====================================*/

/*================= ˽�к������� ====================================*/

/*=================  ================================================*/
		
/******************************************************************************
* FUNC: //
//  IN: *pRtnConfigByte�ĸ���: U_FLS_ExtgZoneConfig_One_BYTE_MAX;
*  OUT: 
// ��bAdd=FALSEʱ��pConfigByte��Ч��
******************************************************************************/

BOOL flsSave_ExtgZoneConf_change(U8 mExtgZone, 
						U8 *pConfigByte,
						BOOL bAdd,
						U8 taskId, U8 flsId)
{
U8 *pNowZoneConf;
U32 mOffsetAdr;
U8 *pBufS;

	if((mExtgZone==0) || (mExtgZone > U_FLS_EXTG_ZONE_MAX))
	{
		return FALSE;
	}
	mExtgZone--;
	
	mOffsetAdr = (mExtgZone * U_FLS_ExtgZoneConfig_One_BYTE_MAX);
	if(mOffsetAdr >= U_FLS_ExtgZoneConfig_All_BYTE_MAX)
	{
		return FALSE;
	}
	pBufS = pFlsHd_GetBufS();
	pNowZoneConf = (pBufS + mOffsetAdr);
	
	if(bAdd)
	{
		// CopyNByte(U8 *pFrom, U8 *pTo, U32 byteTotal);
		CopyNByte(pConfigByte, pNowZoneConf, 
							U_FLS_ExtgZoneConfig_One_BYTE_MAX);
	}
	else
	{
		// ClrRamIsFF(U8 *pByte, U32 byteMax); //ȫ��FF
		ClrRamIsFF(pNowZoneConf, U_FLS_ExtgZoneConfig_One_BYTE_MAX);
	}
	
	
	return FlashSaveNew(getFlsItem_ExtgZoneConfig(), 
						taskId, flsId,pBufS);
	
}


/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
// OUT: pRtnBuf ���������� ExtgZoneConfig �����ݣ�
BOOL flsRd_ExtgZoneConf_toBuf(U8 mPart, U8 *pBufS)
{
TFlsItemAddr stAdr;
U32 adr;
U8 mFlsItem = getFlsItem_ExtgZoneConfig();
	
	if(!getFlsItem_Addr(mFlsItem, mPart, &stAdr))
	{
		return FALSE;
	}
	if(!bFlsItem_IsReadAllow(mFlsItem, mPart))
	{
		return FALSE;
	}
	if(!bFlsSectorStart_isItem(stAdr.chip, stAdr.adrS, mFlsItem))
	{
		Set_FlsItemState(U_FlsItem_Error_State, mFlsItem, mPart);
		return FALSE;
	}
	adr = stAdr.adrS + U_FLS_SectorStart_BYTES;
	
	FlsHd_Read_nByte(stAdr.chip, pBufS, 
					U_FLS_ExtgZoneConfig_All_BYTE_MAX, adr);
	
	if(JdgCrcOK(pBufS, U_FLS_ExtgZoneConfig_All_BYTE_MAX))
	{
		return TRUE;
	}
	else
	{
		Set_FlsItemState(U_FlsItem_Error_State, mFlsItem, mPart);
		return FALSE;
	}
}

/******************************************************************************
* FUNC: //����ע�͵�ƫ�Ƶ�ַ
*   IN:
*  OUT: 
******************************************************************************/

//������������õ�ƫ�Ƶ�ַ:
BOOL GetFlsOffsetAdr_ExtgConfig(
							U8 mExtgZone, U32 *pRtnAdr)
{
	
	if((mExtgZone == 0) || (mExtgZone > U_FLS_EXTG_ZONE_MAX))
	{
		return FALSE;
	}
    mExtgZone--;
	
	// 0��ַ�ճ�
	*pRtnAdr = ((mExtgZone) * U_FLS_ExtgZoneConfig_One_BYTE_MAX);
	
	return TRUE;
}

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/


BOOL FlsRd_ExtgZoneConfig(U8 mExtgZone, U8 *pRtnConfigByte)
{
U8 mPart;
TFlsItemAddr stAdr;
U8 *pBufS;
U32 adr;
U32 mOffset;
    U8 HeadSize=0;
U8 mFlsItem = getFlsItem_ExtgZoneConfig();

    if(bFlsItemIs_OnePageSave(mFlsItem))
    {
        HeadSize=U_FLS_SectorStart_BYTES;
    }
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
		if(!GetFlsOffsetAdr_ExtgConfig(mExtgZone, &mOffset))
		{
			continue;
		}
        adr = stAdr.adrS + mOffset+HeadSize;//��ͷ����
		pBufS = pRtnConfigByte;  //pFlsHd_GetBufS();
		FlsHd_Read_nByte(stAdr.chip, pBufS, 
						U_FLS_ExtgZoneConfig_One_BYTE_MAX, adr);
		
		return TRUE;
		
	}
	return FALSE;
	
}

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

// TFlsExtgZoneConfig_st
BOOL FlsSave_ExtgZoneConfig(U8 mExtgZone, U8 *pConfigByte, 
						U8 taskId, U8 flsId)
{
	return flsSave_ExtgZoneConf_change(mExtgZone, 
						pConfigByte,
						TRUE,
						taskId, flsId);
}

BOOL FlsClr_ExtgZoneConfig(U8 mExtgZone, U8 taskId, U8 flsId)
{
U8 stConf[2]; // temp, �Ӻ������ò���

	return flsSave_ExtgZoneConf_change(mExtgZone, 
						&stConf[0],
						FALSE,
						taskId, flsId);
}

/******************************************************************************
* FUNC: // END
*   IN:
*  OUT: 
******************************************************************************/
