#define __can11sPrtl_eTx_C__
/******************************************************************************
* @file    can11sPrtl_eTx.c
* @author  yx
* @version V1.0
* @date    2013-07-01
* @brief   
* 
******************************************************************************/
#include  "can11sPrtl_eTx.h"


//#include "incFile.h"	
#include  "canProtocalStr.h"
#include  "can11sPrtl_eCan.h"


/*================= 常数 ============================================*/

/*================= 结构定义 ========================================*/

/*================= 私有结构变量声明 ================================*/

static CanID  vECan11sTxId;

/*================= 公有函数声明 ====================================*/

/*================= 私有函数声明 ====================================*/

/*=================  ================================================*/
		
/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

U32 GetECan11sId_Broad(void)
{
	vECan11sTxId.dWord = 0;
	vECan11sTxId.st11sId.DataType = CDType_11s_SData;
	vECan11sTxId.st11sId.BroadOrPToP = CFType_11s_WBoard;
	vECan11sTxId.st11sId.SourceAddr = GetECan_MeAdr();
	return vECan11sTxId.dWord;
}

U32 GetECan11sId_PtoP(U8 mDest)
{
	vECan11sTxId.dWord = 0;
	vECan11sTxId.st11sId.DataType = CDType_11s_SData;
	vECan11sTxId.st11sId.BroadOrPToP = CFType_11s_WPtoP;
	vECan11sTxId.st11sId.SourceAddr = GetECan_MeAdr();
	vECan11sTxId.st11sId.TargetAddr = mDest;
	return vECan11sTxId.dWord;
}



/******************************************************************************
* FUNC: //
******************************************************************************/



/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

void CompECan11s_tx_1byte_broad(U8 mByte, 
							THdCanFrame_st *pRtnFrm)
{
	pRtnFrm->id.dWord = GetECan11sId_Broad();
	pRtnFrm->length = 1;
	pRtnFrm->rtData.rtU8[0] = mByte;
	pRtnFrm->taskId = ~0;
}


void CompECan11s_tx_2byte_broad(U8 mByte0, U8 mByte1, 
							  THdCanFrame_st *pRtnFrm)
{
	pRtnFrm->id.dWord = GetECan11sId_Broad();
	pRtnFrm->length = 2;
	pRtnFrm->rtData.rtU8[0] = mByte0;
	pRtnFrm->rtData.rtU8[1] = mByte1;
	pRtnFrm->taskId = ~0;
}


void CompECan11s_tx_nbyte_broad(U8 mNum, U8 *pByte, 
							  THdCanFrame_st *pRtnFrm)
{
U8 ii;
	if(mNum > U_CAN_HARDFRAME_U8_MAX)
	{
		mNum = U_CAN_HARDFRAME_U8_MAX;
	}
	pRtnFrm->id.dWord = GetECan11sId_Broad();
	pRtnFrm->length = mNum;
	for(ii=0; ii<mNum; ii++)
	{
		pRtnFrm->rtData.rtU8[ii] = *pByte++;
	}
	pRtnFrm->taskId = ~0;
}

/******************************************************************************
* FUNC: // 
*   IN:
*  OUT: 
******************************************************************************/

void CompECan11s_tx_1byte_PtoP(U8 mDest, U8 mByte, 
							THdCanFrame_st *pRtnFrm)
{
	pRtnFrm->id.dWord = GetECan11sId_PtoP(mDest);
	pRtnFrm->length = 1;
	pRtnFrm->rtData.rtU8[0] = mByte;
	pRtnFrm->taskId = ~0;
}

/******************************************************************************
* FUNC: // END 
*   IN:
*  OUT: 
******************************************************************************/

