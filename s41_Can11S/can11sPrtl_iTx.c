#define __can11sPrtl_iTx_C__
/******************************************************************************
* @file    can11sPrtl_iTx.c
* @author  yx
* @version V1.0
* @date    2013-07-01
* @brief   ���͵�can֡�������á�
*		���͵�������¼��� ��ʱ���� "canPrtl_iTx.h" �  
	
* 
******************************************************************************/
#include  "can11sPrtl_iTx.h"

//
#include  "strDevice.h"
#include  "sysPanel.h"
#include  "can11sPrtl_iCan.h"


/*================= ���� ============================================*/

/*================= �ṹ���� ========================================*/

/*================= ˽�нṹ�������� ================================*/
static CanID  vICan11sTxId;
THdCanFrame_st  vICan11sTxFrm;
/*================= ���к������� ====================================*/

/*================= ˽�к������� ====================================*/

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

	// ��ʾ��Ԫ ���� canId.Dest Start:
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
// CAN���͵� dest �� ��·�ţ�Э�����ɫ��
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


// CAN���͵� dest �� ��·�ţ�Э������ɫ��
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


// CAN���͵� dest �� ��·�ţ�Э������ɫ��
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


// CAN���͵� dest �� ��·�ţ�Э������ɫ��
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
