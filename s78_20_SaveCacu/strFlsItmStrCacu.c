#define __strFlsItmStrCacu_C__
/******************************************************************************
* @file    strFlsItmStrCacu.c
* @author  yx
* @version V1.0
* @date    2013-07-23
* @brief   写flash，空间申请。
* 
******************************************************************************/
#include  "strFlsItmStrCacu.h"

#include <absacc.h>  // __at()

#include  "strFlsAdrDef.h"
#include  "strFlsItmStruct.h"
#include  "flsAdrCalculate.h"

#include  "fls_Interface.h"
#include  "codeComm.h"
#include  "codeCrc.h"

//#include "incFile.h"	

/*================= 常数 ============================================*/

/*================= 私有函数声明====================================*/
#ifdef  __strFlsItmStruct_C__

// 最多的一个：
// #define U_FLS_1HISTORY_BYTE_MAX   0x10
// #define U_FLS_1HistPoint_BYTE_MAX   0x08
// #define U_FLS_1PowerOff_BYTE_MAX   0x10

static U8 vRdBuf[U_FLS_1HISTORY_BYTE_MAX]; //

#endif // __strFlsItmStruct_C__
/*=================  ================================================*/
		
/******************************************************************************
* FUNC: //计算各写buf的需求bytes
*   IN:
*  OUT: 结构体所占字节数
U32 mStrByte;
******************************************************************************/
U32 GetFlsItemBufBytes(U8 mFlsItem)
{

	if(!bSaveItemValid(mFlsItem))
	{
		return 0;
	}
	
	if(bFlsItemIsHist(mFlsItem))
	{
		return U_FLS_1HISTORY_BYTE_MAX;
	}
	
	else if(bFlsItemIs_hstPart0Point(mFlsItem))
	{
		return sizeof(THistPoint_un);
	}
	else if(bFlsItemIs_hstPart1Point(mFlsItem))
	{
		return sizeof(THistPoint_un);
	}
	
	
	
	// emFlsItem :
	if(mFlsItem == getFlsItem_PnConfig())
	{
		return sizeof(TFlsUnitConfig_un);
	}
	else if(mFlsItem == getFlsItem_MeStatus())
	{
		return sizeof(TFlsSysSet_un);
	}
	else if(mFlsItem == getFlsItem_NetMachine())
	{
		return sizeof(TFlsMachineConfig_un);
	}
	else if(mFlsItem == getFlsItem_MachProbat())
	{
		return sizeof(TFlsProbat_un);
	}
	else if(mFlsItem == getFlsItem_UserLogin())
	{
		return sizeof(TUserLogin_un);
	}
	else if(mFlsItem == getFlsItem_Disable())
	{
		return sizeof(TFlsDisable_un);
	}
	else if(mFlsItem == getFlsItem_Note())
	{
		return sizeof(TFlsNote_st);
	}
	else if(mFlsItem == getFlsItem_LinkProg())
	{
		return sizeof(TFlsLinkProg_st);
	}
	else if(mFlsItem == getFlsItem_ManuProg())
	{
		return sizeof(TFlsLinkProg_st);
	}
	else if(mFlsItem == getFlsItem_PowerOff())
	{
		return sizeof(TFlsPwrOff_un);
	}
	else if(mFlsItem == getFlsItem_Field())
	{
		return U_FLASH_1_PAGE;
	}
	
	else if(mFlsItem == getFlsItem_MachAlarmNote())
	{
		return sizeof(TFlsNote_st);
	}
	else if(mFlsItem == getFlsItem_RelateDete())
	{
		//return (U_FLS_RelateDete_Head_BYTE_MAX + );
		// return U_FLS_RelateDete_One_BYTE_MAX;
		// return U_FLASH_1_PAGE;
		
		return (U_FLS_RelateDete_Head_BYTE_MAX \
			   + U_FLS_RelateDete_One_BYTE_MAX);
	}
	else if(mFlsItem == getFlsItem_ExtgZoneConfig())
	{
		// return sizeof(TFlsExtgZoneConfig_st);
		return U_FLS_ExtgZoneConfig_All_BYTE_MAX;
	}
	else
	{
		return 0;
	}
	
}

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
U8 vFlsJdgSectorRdBuf[U_FLS_SectorStart_BYTES]; 

BOOL bFlsSectorStart_isItem(U8 chip, U32 mAdr, U8 mFlsItem) 
{
TFlsSecStart_un *pFlsSecStart;
U32 oneSector_ByteMax = getFlsItem_1SectorBytes(mFlsItem);

	mAdr = AdrAllignArea_ToLow(mAdr, oneSector_ByteMax);
	FlsHd_Read_nByte(chip, &vFlsJdgSectorRdBuf[0], U_FLS_SectorStart_BYTES, mAdr);
	pFlsSecStart = (TFlsSecStart_un*)(&vFlsJdgSectorRdBuf[0]);
	
	return ( (pFlsSecStart->detail.byte_55 == 0x55)
		   &&(pFlsSecStart->detail.mFlsItem == mFlsItem)
		   );

}

void Init_StrFlsSectStart(U8 mFlsItem, 
							TFlsSecStart_un *pRtnSecStart
							)
{
U8 *pByteS;
	
	pByteS = &pRtnSecStart->byte[0];
	ClrRamIsFF(pByteS, U_FLS_SectorStart_BYTES); //全清FF
	pRtnSecStart->detail.byte_55 = 0x55;
	pRtnSecStart->detail.mFlsItem = mFlsItem;
	
	pRtnSecStart->byte[U_FLS_SectorStart_BYTES-1] = 
						CacuCrcValue(pByteS, 
							(U_FLS_SectorStart_BYTES-1)
							);
	
}

/******************************************************************************
* FUNC: // END
*   IN:
*  OUT: 
******************************************************************************/
