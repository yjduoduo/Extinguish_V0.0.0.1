#define __meBoard_C__
/******************************************************************************
* @file    meBoard.c
* @author  yx
* @version V1.2
* @date    2013.10.24
* @brief   
* 
******************************************************************************/
#include  "meBoard.h"

//#include "incFile.h"	
#include  "can11sPrtl_iCan.h"  // bGetCan11s_Tx_SrcStart();

/*================= 常数 ============================================*/

 
//软件硬件版本：因为经常会变，所以在.c里。

#define CBoardHardVer    1
#define CBoardSoftVer    10     //用户显示软件版本
#define CBoardDSoftVer   10     //内部开发调试软件版本
#define CBoardTempSoftVer   11     //临时版本

/*================= 常数 ============================================*/
#define CBoardType      	 U_PN_Opea_TYPE  //

/******************************************************************************
* FUNC: // 
*   IN:
*  OUT:
******************************************************************************/
U8 GetBoardICanAddr(void)
{
U8 mSrcStart;
	if(!bGetCan11s_Tx_SrcStart(CBoardType, &mSrcStart))
	{
		return 0;
	}
	return mSrcStart; // 若有单元地址，需要+单元地址；
}


/******************************************************************************
* FUNC: // 
*   IN:
*  OUT:
******************************************************************************/

U8 GetBoardMax(void)
{
U8 mPnMax;
	// MAX = 允许的数字+1；
	GetPanelUnitMax(CBoardType, &mPnMax);
	return mPnMax;
}

U8 GetCanBoardSign(void)
{
	return CBoardType;
}

U8 GetCanApSign(void)
{
	return U_PN_Opea_TYPE;
}

	
		
/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

U8 GetBoardVersion_Hard(void)
{
	return CBoardHardVer;
}

U8 GetBoardVersion_Soft(void)
{
	return CBoardSoftVer;
}
U8 GetBoardVersion_DebugSoft(void)
{
	return CBoardDSoftVer;
}
U8 GetBoardVersion_TempSoft(void)
{
	return CBoardTempSoftVer;
}


/******************************************************************************
* FUNC: //
******************************************************************************/



/******************************************************************************
* FUNC: // END
*   IN:
*  OUT: 
******************************************************************************/
