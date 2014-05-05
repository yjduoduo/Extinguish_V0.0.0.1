#define __can_DataOrFile_C__
/******************************************************************************
* @file    can_DataOrFile.c
* @author  yx
* @version V1.0
* @date    2013-07-24
* @brief   
void  File_CCanRcv(uint8 vFileType,uint8 *pBuff,uint8 vBuffLen)
//第一字节,目标板地址,第2字节数据长度
void  Send_CPro11sBuff(void)
* 
******************************************************************************/
#include  "can_DataOrFile.h"

//#include "incFile.h"	
#include  "sysDef.h"
#include  "canFrame.h"
#include  "canProtocalStr.h"
#include  "CanBufLib_ReDef.h"


/*================= 常数 ============================================*/

/*================= 结构定义 ========================================*/

/*================= 私有结构变量声明 ================================*/
THdCanFrame_st  vCanFrm_HeartBeat;
/*================= 公有函数声明 ====================================*/

/*================= 私有函数声明 ====================================*/

/*=================  ================================================*/
		
/******************************************************************************
* FUNC: // 组织心跳帧
*   IN:
*  OUT: 
******************************************************************************/
void Get_MeHeartBeat(U8 can_id, THdCanFrame_st **ppFrm)
{
	*ppFrm = &vCanFrm_HeartBeat;
}

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
#include  "canBufLib_Inc_Extern.h"
******************************************************************************/
//是文件(事件)：
BOOL bCanFrmIsEvtFile(U8 canId, U32 mCanFrmId)
{
	return FALSE;
}

//是文件(信息类)：
BOOL bCanFrmIsMessageFile(U8 canId, U32 mCanFrmId)
{
CanID  mID;
U8 mDataType;

	mID.dWord = mCanFrmId;
	
	// return (CDType_11s_SData != (mID.stId.CDataType));
	
	mDataType = (mID.st11sId.DataType);
	
	if(	(mDataType == CDType_11s_FHead)
	  ||(mDataType == CDType_11s_FData)
	  ||(mDataType == CDType_11s_FEnd)
	  )
	{
		return TRUE;
	}
	return FALSE;
}

/******************************************************************************
* FUNC: // 
*   IN:
*  OUT: 
******************************************************************************/
//分解29bits canId to fileProp:
BOOL CanRx_File_CompProp(U8 can_id, 
						THdCanFrame_st *pFrm,
						TCanFile_sId *pRtnFileSId,
						U8 *pRtnFileHeadOrData)
{
CanID  mID;
U8 mDataType;

	mID.dWord = pFrm->id.dWord;
	
	pRtnFileSId->src = mID.st11sId.SourceAddr;
	pRtnFileSId->dest = mID.st11sId.TargetAddr;
	
	pRtnFileSId->frmId = pFrm->rtData.rtU8[0];
	
	
	mDataType = (mID.st11sId.DataType);
	if(	(mDataType == CDType_11s_FHead)
	  ||(mDataType == CDType_11s_FData)
	  ||(mDataType == CDType_11s_FEnd)
	  )
	{
		*pRtnFileHeadOrData = mID.st11sId.DataType;
		return TRUE;
	}
	return FALSE;
}


/******************************************************************************
* FUNC: // 
*   IN:  mFileHeadOrData = emCanFrm11sDataOrFile;
*  OUT: 
******************************************************************************/
//组成can发送的id:
U32 CanTx_File_CompId(U8 can_id,
						TCanFile_sId *pFileSId, 
						U8  mFileHeadOrData)
{
CanID  mID;

	mID.dWord = 0;
	mID.st11sId.SourceAddr = pFileSId->src;
	mID.st11sId.TargetAddr = pFileSId->dest;
	mID.st11sId.DataType = mFileHeadOrData; // 
	if(can_id == U_iCAN_ID)
	{
		mID.st11sId.BroadOrPToP = CFType_11s_CPtoP; // iCan的
	}
	else // if(can_id == U_eCAN_ID)
	{
		mID.st11sId.BroadOrPToP = CFType_11s_WPtoP; // eCan的
	}
	
	return mID.dWord;
}

/******************************************************************************
* FUNC: //
******************************************************************************/



/******************************************************************************
* FUNC: // END
*   IN:
*  OUT: 
******************************************************************************/
