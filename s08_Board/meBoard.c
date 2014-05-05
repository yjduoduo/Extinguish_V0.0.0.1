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

/*================= ���� ============================================*/

 
//���Ӳ���汾����Ϊ������䣬������.c�

#define CBoardHardVer    1
#define CBoardSoftVer    10     //�û���ʾ����汾
#define CBoardDSoftVer   10     //�ڲ�������������汾
#define CBoardTempSoftVer   11     //��ʱ�汾

/*================= ���� ============================================*/
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
	return mSrcStart; // ���е�Ԫ��ַ����Ҫ+��Ԫ��ַ��
}


/******************************************************************************
* FUNC: // 
*   IN:
*  OUT:
******************************************************************************/

U8 GetBoardMax(void)
{
U8 mPnMax;
	// MAX = ���������+1��
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
