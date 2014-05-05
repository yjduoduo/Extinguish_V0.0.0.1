#define __can11sPrtl_iTx_C__
/******************************************************************************
* @file    can11sPrtl_iTx.c
* @author  yx
* @version V1.0
* @date    2013-07-01
* @brief   发送的can帧基本配置。
*		发送的命令和事件， 暂时都在 "canPrtl_iTx.h" 里。  
	
* 
******************************************************************************/
#include  "can11sPrtl_iTx.h"

//
#include  "strDevice.h"
#include  "sysPanel.h"
#include  "can11sPrtl_iCan.h"


/*================= 常数 ============================================*/

/*================= 结构定义 ========================================*/

/*================= 私有结构变量声明 ================================*/
static CanID  vICan11sTxId;
THdCanFrame_st  vICan11sTxFrm;
/*================= 公有函数声明 ====================================*/

/*================= 私有函数声明 ====================================*/

/*=================  ================================================*/
		
/******************************************************************************
* FUNC: // 
*   IN:
*  OUT: 
******************************************************************************/

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

U32 GetICan11sId_Broad(void)
{
	vICan11sTxId.dWord = 0;
	vICan11sTxId.st11sId.DataType = CDType_11s_SData;
	vICan11sTxId.st11sId.BroadOrPToP = CFType_11s_CBoard;
	return vICan11sTxId.dWord;
}

U32 GetICan11sId_PtoP(U8 mDest)
{
	vICan11sTxId.dWord = 0;
	vICan11sTxId.st11sId.DataType = CDType_11s_SData;
	vICan11sTxId.st11sId.BroadOrPToP = CFType_11s_CPtoP;
	vICan11sTxId.st11sId.TargetAddr = mDest;
	return vICan11sTxId.dWord;
}

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

void CompICan11s_tx_1byte_broad(U8 mByte, 
							THdCanFrame_st *pRtnFrm)
{
	pRtnFrm->id.dWord = GetICan11sId_Broad();
	pRtnFrm->length = 1;
	pRtnFrm->rtData.rtU8[0] = mByte;
	pRtnFrm->taskId = ~0;
}


void CompICan11s_tx_2byte_broad(U8 mByte0, U8 mByte1, 
							  THdCanFrame_st *pRtnFrm)
{
	pRtnFrm->id.dWord = GetICan11sId_Broad();
	pRtnFrm->length = 2;
	pRtnFrm->rtData.rtU8[0] = mByte0;
	pRtnFrm->rtData.rtU8[1] = mByte1;
	pRtnFrm->taskId = ~0;
}


void CompICan11s_tx_nbyte_broad(U8 mNum, U8 *pByte, 
							  THdCanFrame_st *pRtnFrm)
{
U8 ii;
	if(mNum > U_CAN_HARDFRAME_U8_MAX)
	{
		mNum = U_CAN_HARDFRAME_U8_MAX;
	}
	pRtnFrm->id.dWord = GetICan11sId_Broad();
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

void CompICan11s_tx_1byte_PtoP(U8 mDest, U8 mByte, 
							THdCanFrame_st *pRtnFrm)
{
	pRtnFrm->id.dWord = GetICan11sId_PtoP(mDest);
	pRtnFrm->length = 1;
	pRtnFrm->rtData.rtU8[0] = mByte;
	pRtnFrm->taskId = ~0;
}


/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

BOOL iCan11s_tx_Dev_PrtlTypePink(U8 pnType, U8 pnSequ, 
							U8 *pRtnCanDest)
{
U8 mDestS;
U8 mCanDest;

	// 显示单元 发送 canId.Dest Start:
	if(!bGetCan11s_Tx_DestStart(pnType, &mDestS))
	{
		return FALSE;
	}
	
	mCanDest = (mDestS + (pnSequ - 1));
	
	// bSequValid_RelatePanel(U8 pnType, U8 mSequPn1Start, U8 mSequNow)
	if(bSequValid_RelatePanel(pnType, mDestS, mCanDest))
	{
		*pRtnCanDest = mCanDest;
		return TRUE;
	}
	else
	{
		*pRtnCanDest = mDestS;
		return FALSE;
	}
	
}


/******************************************************************************
* FUNC: //
******************************************************************************/
// CAN发送的 dest 和 回路号：协议里粉色：
// IN:  mPnType: emPanelType
// IN:  mPnSequ: 1~
BOOL iCan11s_tx_Dete_PrtlTypePink(U8 mLoop, 
							U8 *pRtnCanDest, U8 *pRtnLoop)
{
	if((mLoop == 0) || (mLoop > U_SYS_LOOP_MAX))
	{
		return FALSE;
	}
	
	*pRtnCanDest = ((mLoop-1)/U_OneBoard_LOOP_MAX + 1);
	*pRtnLoop = mLoop;
	return TRUE;
}


// CAN发送的 dest 和 回路号：协议里大红色：
// IN:  mPnType: emPanelType
// IN:  mPnSequ: 1~
BOOL iCan11s_tx_Dete_PrtlTypeRed(U8 mLoop, 
							U8 *pRtnCanDest, U8 *pRtnLoop)
{
	if((mLoop == 0) || (mLoop > U_SYS_LOOP_MAX))
	{
		return FALSE;
	}
	
	*pRtnCanDest = ((mLoop-1)/U_OneBoard_LOOP_MAX + 1) - 1;
	*pRtnLoop = mLoop;
	return TRUE;
}


// CAN发送的 dest 和 回路号：协议里棕色：
// IN:  mPnType: emPanelType
// IN:  mPnSequ: 1~
BOOL iCan11s_tx_Dete_PrtlTypeBrown(U8 mLoop, 
							U8 *pRtnCanDest, U8 *pRtnLoop)
{
	if((mLoop == 0) || (mLoop > U_SYS_LOOP_MAX))
	{
		return FALSE;
	}
	
	*pRtnCanDest = mLoop/8;
	*pRtnLoop = mLoop-1;
	return TRUE;
}


// CAN发送的 dest 和 回路号：协议里绿色：
// IN:  mPnType: emPanelType
// IN:  mPnSequ: 1~
BOOL iCan11s_tx_Dete_PrtlTypeGreen(U8 mLoop, 
							U8 *pRtnCanDest, U8 *pRtnLoop)
{
	if((mLoop == 0) || (mLoop > U_SYS_LOOP_MAX))
	{
		return FALSE;
	}
	
	*pRtnCanDest = ((mLoop-1)/U_OneBoard_LOOP_MAX + 1);
	*pRtnLoop = mLoop;
	return TRUE;
}


/******************************************************************************
* FUNC: // END
*   IN:
*  OUT: 
******************************************************************************/
