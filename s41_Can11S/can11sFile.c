#define __can11sFile_C__
/******************************************************************************
* @file    can11sFile.c
* @author  yx
* @version V1.0
* @date    2013-10-10
* @brief   11S的文件帧。
*		发送文件未考虑 应答，只管发送。若定时未收到应答需要重发，则发送完成后不能ClrBuf.
* 
******************************************************************************/
#include  "can11sFile.h"


//#include "incFile.h"	
#include  "sysDef.h"
#include  "codeComm.h"
#include  "canFrame.h"
#include  "canProtocalStr.h"
#include  "CCan_11S_Def.h"
#include  "sysPanel.h"
#include  "CanBufLib_ReDef.h"

#include  "CanBufLib_strFileProp.h"
#include  "CanBufLib_incOut.h"

#include  "can_DataOrFile.h"
#include  "can11sPrtl_iCan.h"
#include  "iCanRxTask.h"
#include  "lcdPg_Page.h"

/*================= 常数 ============================================*/
// 字节数。主要是指示字节用途。
#define U_File11s_ByteNum_FILE_ID   1
#define U_File11s_ByteNum_FILE_LENGTH   1
#define U_File11s_ByteNum_FILE_VERIFY   1
#define U_File11s_ByteNum_FILE_EndFF   1
/*================= 结构定义 ========================================*/

/*================= 私有结构变量声明 ================================*/

THdCanFrame_st  stFrmTxMesgFile; // 待发送的帧
/*================= 公有函数声明 ====================================*/

/*================= 私有函数声明 ====================================*/

// 查找 存储位置，fileHead, 和 buf[0].
BOOL bGet11sFile_RxMesg_StoreLocat(U8 can_id, U8 mFileHeadOrData,
						TCanFile_sId  *pFileSNewId,
						TCanRxFileHead_st  **pRtnHeadNow,
						U8 **pRtnByteBufS,
						U32 *pRtnOneBufMax
						);
BOOL bCan11sRxFile_jdgVerify(TCanRxFileHead_st  *pFileHead, 
					   U8 *pByteStoreS);



// 查找 新的 存储位置，fileHead, 和 buf[0].
BOOL bGet11sFile_TxMesg_NewStoreLocat(U8 can_id,
						TCanTxFileHead_st  **pRtnHeadNow,
						U8 **pRtnByteBufS,
						U32 *pRtnOneBufMax
						);
// 查找 buf 存储位置，fileHead, 和 buf[0].
BOOL bGet11sFile_TxMesg_bufStoreLocat(
						U8 can_id, U8 mBuf,
						TCanTxFileHead_st  **pRtnHeadNow,
						U8 **pRtnByteBufS,
						U32 *pRtnOneBufMax
						);
U8 can11sTxFile_cacuVerify(U8 mFileId, U8 fileLength, 
					   U8 *pFileS, U32 mByteTotal);
void can11sTxMesgFile_iCan_composeOneFrm(
						TCanTxFileHead_st  *pFileHead, 
						U8 *pByteStoreS,
						BOOL *pRtnIsLastFrm);

/*=================  ================================================*/

/******************************************************************************
* 文件帧说明：
每帧开始 [0]fileId, 
		[1]文件长度字节， 从fileHead.[0] 到 校验和，不算最后的FF.
文件最后，(N-2)=校验和， 从fileHead.[2]开始算，
		(N-1)=FF.
******************************************************************************/


/******************************************************************************
* FUNC: //
*   IN:  
*  OUT:  stFrmTxMesgFile
*master: Can11sTxMesgFile_iCan_Follow(); 
******************************************************************************/

void can11sTxMesgFile_iCan_composeOneFrm(
									TCanTxFileHead_st  *pFileHead, 
									U8 *pByteStoreS,
									BOOL *pRtnIsLastFrm)
{
U8 can_id = U_iCAN_ID;
U8 *pByteStoreNow;
U32 mLaveByte;
U8 mFileHeadOrData;
U8 mThisFrmSendByte; // 不算前2字节 
	
	*pRtnIsLastFrm = FALSE;
	mLaveByte =   pFileHead->txFileProp.needSendTotal 
				- pFileHead->txFileProp.haveSendByte;
	if(pFileHead->txFileProp.haveSendByte == 0)
	{
		mFileHeadOrData = CDType_11s_FHead;
		mThisFrmSendByte = (8-2);
	}
	else if(mLaveByte <= (8-2))
	{
		mFileHeadOrData = CDType_11s_FEnd;
		mThisFrmSendByte = (mLaveByte);
		*pRtnIsLastFrm = TRUE;
	}
	else
	{
		mFileHeadOrData = CDType_11s_FData;
		mThisFrmSendByte = (8-2);
	}
	stFrmTxMesgFile.id.dWord = CanTx_File_CompId(can_id,
					&pFileHead->fileSId, mFileHeadOrData);
	
	stFrmTxMesgFile.length = mThisFrmSendByte + 2;
	stFrmTxMesgFile.taskId = pFileHead->txFileProp.taskId;
	stFrmTxMesgFile.rtData.rtU8[0] = pFileHead->fileSId.frmId;
	stFrmTxMesgFile.rtData.rtU8[1] = pFileHead->txFileProp.fileLength;
		
	pByteStoreNow = pByteStoreS + pFileHead->txFileProp.haveSendByte;
	// CopyNByte(U8 *pFrom, U8 *pTo, U32 byteTotal);
	CopyNByte(pByteStoreNow, &stFrmTxMesgFile.rtData.rtU8[2], 
								mThisFrmSendByte);
	pFileHead->txFileProp.haveSendByte += mThisFrmSendByte;
	
	if(mFileHeadOrData == CDType_11s_FEnd)
	{
		pFileHead->txFileProp.bSendFinish = TRUE;
	}
}


/******************************************************************************
* FUNC: // 实际发送：开始 
*		若是load后首次发送，不调用也可以。若是重新发送，需要调用。
*   IN:  
*  OUT:  
// master: can file tx buf -> can hard tx;
******************************************************************************/

void Can11sTxMesgFile_iCan_Start(U8 mBuf)
{
U8 can_id = U_iCAN_ID;
TCanTxFileHead_st  *pFileHead;
	

	if(!bGetFileHead_CanTxMesgFile(can_id, mBuf, &pFileHead))
	{
		return;
	}
	
	pFileHead->txFileProp.bSendFinish = FALSE;
	pFileHead->txFileProp.bSendIng = TRUE;
	pFileHead->txFileProp.haveSendByte = 0;
	
	pFileHead->tmr.loadStart_100msNum = 0;
	pFileHead->tmr.sendFinish_100msNum = 0;
	
}

/******************************************************************************
* FUNC: // 实际发送：文件组成其中一帧，进frmBuf, 等待发送。
*   IN:  
*  OUT:  MesgFile_ID.buf 
// master: can file tx buf -> can hard tx;
*  若bRtnFinish=TRUE, 且无应答机制，需要master执行Clr_CanTxMesgFile_FromBuf();

// U_SIGN_bHaveTested  2013.10.11 21:21  "sim_CanBuf.c"
******************************************************************************/

BOOL Can11sTxMesgFile_iCan_Follow(U8 mBuf, BOOL *bRtnFinish)
{
U8 can_id = U_iCAN_ID;
TCanTxFileHead_st  *pFileHead;
U8 *pByteStoreS;
U32 vBufMax; // 一个文件字节MAX 

	if(!bGet11sFile_TxMesg_bufStoreLocat(can_id, mBuf,
						&pFileHead,
						&pByteStoreS,
						&vBufMax)
						)
	{
		return FALSE;
	}
	
	if(		(!pFileHead->txFileProp.bHaveFile)
	  ||	( pFileHead->txFileProp.bSendFinish)
	  )
	{
		return FALSE;
	}
	
	
	can11sTxMesgFile_iCan_composeOneFrm(pFileHead, pByteStoreS,
									bRtnFinish);
	
	return CanBuf_mesgFile_Tx_Add(can_id, &stFrmTxMesgFile);
	
}


/******************************************************************************
* FUNC: //
*   IN:  
*  OUT: 
******************************************************************************/

// 查找 buf 存储位置，fileHead, 和 buf[0].
BOOL bGet11sFile_TxMesg_bufStoreLocat(U8 can_id, U8 mBuf,
						TCanTxFileHead_st  **pRtnHeadNow,
						U8 **pRtnByteBufS,
						U32 *pRtnOneBufMax
						)
{
	
	if(!bGetFileHead_CanTxMesgFile(can_id, mBuf, pRtnHeadNow))
	{
		return FALSE;
	}
		
	if(!bGetFileByteBufS_CanTxMesgFile(can_id, mBuf, 
							   pRtnByteBufS,
							   pRtnOneBufMax))
	{
		return FALSE;
	}			   
	
	return TRUE;
	
}


// 查找 新的 存储位置，fileHead, 和 buf[0].
BOOL bGet11sFile_TxMesg_NewStoreLocat(U8 can_id,
						TCanTxFileHead_st  **pRtnHeadNow,
						U8 **pRtnByteBufS,
						U32 *pRtnOneBufMax
						)
{
U8 mBuf;
	
	if(!bFindSpaceBuf_CanTxMesgFile(can_id, &mBuf))
	{
		return FALSE;
	}
	
	return bGet11sFile_TxMesg_bufStoreLocat(can_id, mBuf,
						pRtnHeadNow,
						pRtnByteBufS,
						pRtnOneBufMax
						);
}


/******************************************************************************
* FUNC: // 需要发送的文件 保存，等待发送:
// 		实际发送： Can11sTxMesgFile_iCan_Start();  Can11sTxMesgFile_iCan_Follow(); 
*   IN:  pFileS字节里， 不带  fileID和 文件字节长度；
*		fileID 在 pFileSId.frmId;
*		mByteTotal  不带  fileID和 文件字节长度 和 校验，只是pFileS文件本身。
*  发送到CAN帧上，每帧[2]~[7]的总数，= (mByteTotal+2)
*  OUT: 
// *Master: task.

// U_SIGN_bHaveTested  2013.10.11 21:21  "sim_CanBuf.c"
******************************************************************************/

BOOL Can11sTxMesgFile_iCan_New(U8 taskId,
					TCanFile_sId  *pFileSId,
					U8 *pFileS, 
					U32 mByteTotal)
{
U8 can_id = U_iCAN_ID;
TCanTxFileHead_st  *pFileHead;
U8 *pByteStoreS;
U8 *pFileByte;
U32 vBufMax; // 一个文件字节MAX 
U8 mVerifyVal = 0;
U32 mThisSendByteNum;

	if(!bGet11sFile_TxMesg_NewStoreLocat(can_id,
						&pFileHead,
						&pByteStoreS,
						&vBufMax)
						)
	{
		return FALSE;
	}
	
	mThisSendByteNum = mByteTotal;
	mThisSendByteNum += 
				(U_File11s_ByteNum_FILE_ID + U_File11s_ByteNum_FILE_LENGTH
			   + U_File11s_ByteNum_FILE_VERIFY + U_File11s_ByteNum_FILE_EndFF
			   );
	if(mThisSendByteNum >= vBufMax)
	{
		return FALSE;
	}
	
	CanTx_FileHead_SetInvalid(pFileHead);
	
	pFileHead->fileSId = *pFileSId;
	
	SetFile_CanTxMesgFile_Using(can_id, pFileHead);
	
	pFileHead->txFileProp.taskId = taskId;
	pFileHead->txFileProp.fileLength = mByteTotal 					
					+(U_File11s_ByteNum_FILE_ID 
					+ U_File11s_ByteNum_FILE_LENGTH
					+ U_File11s_ByteNum_FILE_VERIFY);
	pFileHead->txFileProp.haveSendByte = 0;
	
	mVerifyVal = can11sTxFile_cacuVerify(
				pFileSId->frmId, pFileHead->txFileProp.fileLength,
				pFileS, mByteTotal);
	pFileHead->txFileProp.verifyVal = mVerifyVal;
	
	pFileByte = pFileS + mByteTotal;
	*pFileByte = mVerifyVal;
	pFileByte++;
	*pFileByte = 0xFF;
	mByteTotal += (U_File11s_ByteNum_FILE_VERIFY + U_File11s_ByteNum_FILE_EndFF);
	pFileHead->txFileProp.needSendTotal = mByteTotal;
	
	// CopyNByte(U8 *pFrom, U8 *pTo, U32 byteTotal);
	CopyNByte(pFileS, pByteStoreS, mByteTotal);
	
	return TRUE;
	
}


/******************************************************************************
* FUNC: // 
******************************************************************************/

U8 can11sTxFile_cacuVerify(U8 mFileId, U8 fileLength, 
							U8 *pFileS, U32 mByteTotal)
{
U8 mVerifyVal = 0;
U32 mByteNum;
U8 *pFileByte;

	mVerifyVal = mFileId;
	mVerifyVal += (fileLength); // 文件，长度，..., 校验，FF.
	
	pFileByte = pFileS;
	for(mByteNum=0; mByteNum<mByteTotal; mByteNum++)
	{
		mVerifyVal += (*pFileByte);
		pFileByte++;
	}
	return mVerifyVal;
}


/******************************************************************************
* FUNC: // CAN帧 组成文件：
*   IN:
*  OUT: 
*Master:  main流程处理：“can20_BufManage” : CanFrmRx_toFile();
// master: can intr rx buf read;
******************************************************************************/

BOOL Can11sRxEvtFile_iCan(THdCanFrame_st *pFrm)
{
	return FALSE;
}

/******************************************************************************
* FUNC: // CAN帧 组成文件：
*   IN:
*  OUT: pByteStoreS开始的文件，不包括fileId 和 length.
*Master:  main流程处理：“can20_BufManage” : CanFrmRx_toFile();
// master: can intr rx buf read;

// U_SIGN_bHaveTested  2013.10.11 21:21  "sim_CanBuf.c"
******************************************************************************/

BOOL Can11sRxMesgFile_iCan(THdCanFrame_st *pFrm)
{
U8 can_id = U_iCAN_ID;
U8 mFileHeadOrData; // CDType_11s_FHead, CDType_11s_FData, CDType_11s_FEnd;
TCanFile_sId  stFileSNewId;
TCanRxFileHead_st  *pFileHead;
U8 *pByteStoreS;
U8 *pByteStoreNow;
U32 vBufMax; // 一个文件字节MAX 

	
	//分解29bits canId to fileProp:
	if(!CanRx_File_CompProp(can_id, pFrm, 
							&stFileSNewId, &mFileHeadOrData))
	{
		return FALSE;
	}
	
	// 查找 存储位置，fileHead, 和 buf[0].
	// mFileHeadOrData=head时，stFileSNewId 用不到。
	if(!bGet11sFile_RxMesg_StoreLocat(can_id, 
						mFileHeadOrData, &stFileSNewId,
						&pFileHead, &pByteStoreS, &vBufMax
						))
	{
		return FALSE;
	}
	if(mFileHeadOrData != CDType_11s_FHead)
	{
		if((pFileHead->rxFileProp.haveRecLength + 8) >= vBufMax)
		{
			return FALSE; // 超长
		}		
	}
	
	//  
	switch(mFileHeadOrData)
	{
		
	case CDType_11s_FHead:	// 11s 文件头
		// 存储的属性位置： pFileHead
		CanRx_FileHead_SetInvalid(pFileHead);
		pFileHead->fileSId = stFileSNewId;
		pFileHead->rxFileProp.bUsIng = TRUE;
		
		// 存储字节位置：pByteStoreNow
		pByteStoreNow = pByteStoreS + 0;
		// CopyNByte(U8 *pFrom, U8 *pTo, U32 byteTotal);
		CopyNByte(&pFrm->rtData.rtU8[2], pByteStoreNow, (8-2));
		
		pFileHead->rxFileProp.fileLength = pFrm->rtData.rtU8[1]; //文件字节总长度
		pFileHead->rxFileProp.haveRecLength = (8-2);		
		break;
		
	case CDType_11s_FData:	// 11s 文件数据
		pByteStoreNow = pByteStoreS + pFileHead->rxFileProp.haveRecLength;
		CopyNByte(&pFrm->rtData.rtU8[2], pByteStoreNow, (8-2));
		pFileHead->rxFileProp.haveRecLength += (8-2);		
		break;
		
	case CDType_11s_FEnd:	// 11s 文件结束
		if(pFrm->length < 2)
		{
			return FALSE;
		}
		pByteStoreNow = pByteStoreS + pFileHead->rxFileProp.haveRecLength;
		CopyNByte(&pFrm->rtData.rtU8[2], pByteStoreNow, (pFrm->length-2));
		pFileHead->rxFileProp.haveRecLength += (pFrm->length-2); // 去掉[0][1].
		
		// 校验：
		// 登记文件 带校验
		// 回路浏览，不带校验。
		if(pFileHead->fileSId.frmId == c11s_FI_LpReg) 
		{
			if(!bCan11sRxFile_jdgVerify(pFileHead, pByteStoreS))
			{
				return FALSE;
			}
		}
		pFileHead->rxFileProp.bRecFinish = TRUE;
		break;
		
	default:
		return FALSE;
		
	}
	return TRUE;
}



/******************************************************************************
* FUNC: //
******************************************************************************/

BOOL bCan11sRxFile_jdgVerify(TCanRxFileHead_st  *pFileHead, 
					   U8 *pByteStoreS)
{
U8 mVerifyVal = 0;
U32 mByteNum;
U32 mByteBeforeVerify;
U8 *pByteStoreNow;

// 接收时， lenTotal = 接收文件的[1]，包括head帧的[0][1],mid帧的6字节，校验，不包括字节FF.
//		lenNow = 存储到buf的字节 + 字节FF 的 in指针；
// 		判断接收正确结束，lenNow+1 = lenTotal。 1差距为文件id,总数 - 字节FF.
	if(		(pFileHead->rxFileProp.haveRecLength 
				+ (U_File11s_ByteNum_FILE_ID + U_File11s_ByteNum_FILE_LENGTH)
			)
	    !=	(pFileHead->rxFileProp.fileLength    
				+ (U_File11s_ByteNum_FILE_EndFF)
			)
		)
	{
		return FALSE;
	}
	
	pByteStoreNow = pByteStoreS + pFileHead->rxFileProp.haveRecLength; 
	//文件倒数第2个字节 是校验字，最后一个是FF。
	pByteStoreNow -= (U_File11s_ByteNum_FILE_VERIFY + U_File11s_ByteNum_FILE_EndFF); 
	pFileHead->rxFileProp.verifyVal = *pByteStoreNow; 
	
	
	mByteBeforeVerify = pFileHead->rxFileProp.haveRecLength;
	mByteBeforeVerify -= (U_File11s_ByteNum_FILE_VERIFY + U_File11s_ByteNum_FILE_EndFF);
	pByteStoreNow = pByteStoreS;
	
	mVerifyVal = pFileHead->fileSId.frmId;
	mVerifyVal += pFileHead->rxFileProp.fileLength;
	for(mByteNum=0; mByteNum<mByteBeforeVerify; mByteNum++)
	{
		mVerifyVal += (*pByteStoreNow);
		pByteStoreNow++;
	}
	return (mVerifyVal == (pFileHead->rxFileProp.verifyVal));
}

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
// 查找 存储位置，fileHead, 和 buf[0].
// mFileHeadOrData=head时，stFileSNewId 用不到。
BOOL bGet11sFile_RxMesg_StoreLocat(U8 can_id, U8 mFileHeadOrData,
						TCanFile_sId  *pFileSNewId,
						TCanRxFileHead_st  **pRtnHeadNow,
						U8 **pRtnByteBufS,
						U32 *pRtnOneBufMax
						)
{
U8 mBuf;
	
	// 初始化 存储位置，fileHead, 和 buf[0].
	if(mFileHeadOrData == CDType_11s_FHead)
	{
		//查找buf里空位置：
		if(!bFindSpaceBuf_CanRxMesgFile(can_id, &mBuf))
		{
			return FALSE;
		}
	}
	else // CDType_11s_FData, CDType_11s_FEnd
	{
		//查找buf里相同的文件:
		if(!bFindEquBuf_CanRxMesgFile(can_id, pFileSNewId, &mBuf))
		{
			return FALSE;
		}
	}
	// 存储的属性位置： pFileHead
	bGetFileHead_CanRxMesgFile(can_id, mBuf, pRtnHeadNow);
	
	
	// 存储字节位置：pByteStoreNow
	bGetFileByteBufS_CanRxMesgFile(can_id, mBuf, 
						   pRtnByteBufS, pRtnOneBufMax);
	
	return TRUE;
	
}




/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 

登记文件: 02H	文件长度(含文件头及校验和)	报警总数	联动总数	声光总数	广播总数	楼显总数	登记地址	
纵览文件: 08H  文件长度(无校验位)=219  发送0-216个地址对应的当前状态电流值，无校验位
查询回路灵敏度文件: 09H	文件长度	查询回路	版本特征	
			1级报警地址罗列+0xf2结束标志	2级报警地址罗列+0xf3结束标志	
			3级报警地址罗列+0xf4结束标志	4级报警地址罗列+0xff结束标志



******************************************************************************/

// 处理一条收到的文件：
void ICan11s_FileRx_One(TCanFile_sId  *pFileSId,
						U8 *pStoreByteS, U32 mByteTotal)
{
U8 pnType; // emPanelType
U8 pnSequ;

	if(!bICan11sIdSourse_ToPnTypeSequ(pFileSId->src, 
						&pnType, &pnSequ))
	{
		return;
	}
	
	switch(pFileSId->frmId)
	{
		case c11s_FI_LpReg: // 2
			if(!iCanRxFile_PageIsInquireRegist())
			{
				return;
			}
			if(pnType != U_PN_Loop_TYPE)
			{
				return;
			}
			ICan11s_FileRx_InquireRegist(pnSequ,
								pStoreByteS, mByteTotal);
			break;
			
		case c11s_FI_LpScan: // 8
			if(!iCanRxFile_PageIsLoopBrowse())
			{
				return;
			}
			if(pnType != U_PN_Loop_TYPE)
			{
				return;
			}
			ICan11s_FileRx_LoopBrowse(pnSequ,
								pStoreByteS, mByteTotal);
			break;
			
		default:
			break;
	}
}


void ICan11s_FileRx_LoopBrowse(U8 pnLoopSequ,
						U8 *pStoreByteS, U32 mByteTotal)
{

}



#define U_ICan11sFileRx_InqRegist_AddrS   6 
void ICan11s_FileRx_InquireRegist(U8 pnLoopSequ,
						U8 *pStoreByteS, U32 mByteTotal)
{
U32 mItem = 0;
U8 *pTotal = pStoreByteS;
U8 *pAddrS = pStoreByteS;
U8 *pAddrNow = pStoreByteS;
	
	pTotal = pStoreByteS;
	pAddrS = (pStoreByteS + U_ICan11sFileRx_InqRegist_AddrS);
	pAddrNow = pAddrS;
	
	while(1)
	{
		switch(mItem)
		{
			case 0:
	ICan11s_FileRx_InqRegist_Detector(*pTotal, pAddrNow);
				break;
			case 1:
	ICan11s_FileRx_InqRegist_Modu(*pTotal, pAddrNow);
				break;
			case 2:
	ICan11s_FileRx_InqRegist_HornStrobe(*pTotal, pAddrNow);
				break;
			case 3:
	ICan11s_FileRx_InqRegist_Broad(*pTotal, pAddrNow);
				break;
			case 4:
	ICan11s_FileRx_InqRegist_FloorPanel(*pTotal, pAddrNow);
				return; // last one 
				
			default:
				return;
		}
		pAddrNow += *pTotal;
		pTotal++;
		mItem++;
	}

}



void ICan11s_FileRx_InqRegist_Detector(U8 mAdrNum, U8 *pAddrS)
{
	P058_QrFieldRegist_Rx_Detector(mAdrNum, pAddrS);
}
void ICan11s_FileRx_InqRegist_Modu(U8 mAdrNum, U8 *pAddrS)
{
	P058_QrFieldRegist_Rx_Modu(mAdrNum, pAddrS);
}
void ICan11s_FileRx_InqRegist_HornStrobe(U8 mAdrNum, U8 *pAddrS)
{
	P058_QrFieldRegist_Rx_HornStrobe(mAdrNum, pAddrS);
}
void ICan11s_FileRx_InqRegist_Broad(U8 mAdrNum, U8 *pAddrS)
{
	P058_QrFieldRegist_Rx_Broad(mAdrNum, pAddrS);
}
void ICan11s_FileRx_InqRegist_FloorPanel(U8 mAdrNum, U8 *pAddrS)
{
	P058_QrFieldRegist_Rx_FloorPanel(mAdrNum, pAddrS);
}

/******************************************************************************
* FUNC: //
每帧开始 [0]fileId, 
		[1]文件长度字节， 从fileHead.[0] 到 校验和，不算最后的FF.
文件最后，(N-2)=校验和， 从fileHead.[2]开始算，
		(N-1)=FF.

75 CCanCtrl
******************************************************************************/
/*
void  File_CCanRcv(uint8 vFileType,uint8 *pBuff,uint8 vBuffLen);
void  Send_CPro11sBuff(void);
void  Load_CPro11sBuff(void);
void  SetFile_CCanSend(uint8 vCommValue,uint8 *pBuff) ;

//发送文件  第一个字节－－目标板地址   第2个字节 文件长度
void  SetFile_CCanSend(uint8 vCommValue,uint8 *pBuff) 
{
	  uint8 i=0;  
	  vCanFileSendLen=0;
	  vCanSendInfo.tCanID.Word = 0;	 
	  vCanSendInfo.tCanID.CanID.CFrameType = CFType_11s_CDot;  
	  vCanSendInfo.tCanID.CanID.CSourceAddr = 0; 
	  vCanSendInfo.tCanID.CanID.CTargetAddr = *pBuff++;  
	  vCanSendInfo.Byte[0]= vCommValue; 
		vCanSendInfo.Byte[1]= *pBuff++; 
	  vCanSendInfo.DateNum =8;	 
	  while(vCanFileSendLen < vCanSendInfo.Byte[1])
		{ 
				if(vCanFileSendLen==0)
				{
						vCanSendInfo.tCanID.CanID.CDataType = CDType_11s_FHead;  
            vCanFileSendLen++;  
					  vCanFileSendLen++;  
				}
				else
				{
					  vCanSendInfo.tCanID.CanID.CDataType = CDType_11s_FData;  
				} 
				for(i=2;i<8;i++)
				{
					 vCanSendInfo.Byte[i]=*pBuff++; 
					 vCanFileSendLen++;	 
				}
				if(vCanFileSendLen >= vCanSendInfo.Byte[1])
			  {
					 vCanSendInfo.tCanID.CanID.CDataType = CDType_11s_FEnd;    
			  }	 
	      Add_CCanSendBuff(&vCanSendInfo);	
	  }
} 


void  Load_CPro11sBuff(void)
{
	  uint8 i=0; 
	  uint8   vCanPro11sLen=0; 	 
    tCanInfoDef  vCanPro11s;   
		 
    //计算累加和	
	  for(i=0;i<vPro11sBuffCtrl.In;i++)
		{
			  vCanPro11sLen+=vPro11sBuff[i];
		}
	  vPro11sBuff[GetInPosi_CRec(&vPro11sBuffCtrl)]=vCanPro11sLen;   
		vPro11sBuff[GetInPosi_CRec(&vPro11sBuffCtrl)]=0xff; 
		
	  vCanPro11sLen=0;  
		
	  vCanPro11s.tCanID.Word = 0;	 
	  vCanPro11s.tCanID.CanID.CFrameType = CFType_11s_CDot;  
	  vCanPro11s.tCanID.CanID.CSourceAddr = 0; 
	  vCanPro11s.tCanID.CanID.CTargetAddr = CanTarget_CPhysicalAddr(vPro11sBuff[0]);    
	  vCanPro11s.Byte[0]= c11s_FC_Pro; 
		vCanPro11s.Byte[1]= vPro11sBuffCtrl.In+1; 
	  vCanPro11s.DateNum =8;	 
	  while(vCanPro11sLen < vPro11sBuffCtrl.In)
		{ 
				if(vCanPro11sLen==0)
				{
						vCanPro11s.tCanID.CanID.CDataType = CDType_11s_FHead;   
				}
				else
				{
					  vCanPro11s.tCanID.CanID.CDataType = CDType_11s_FData;  
				} 
				for(i=2;i<8;i++)
				{
					 vCanPro11s.Byte[i]=vPro11sBuff[vCanPro11sLen++];  
				}
				if(vCanPro11sLen > vPro11sBuffCtrl.In)
				{
					 vCanPro11s.tCanID.CanID.CDataType = CDType_11s_FEnd;    
			  }	 
				
	      Add_CCanSendBuff(&vCanPro11s);	
	  }  
}


//第一字节,目标板地址,第2字节数据长度
void  Send_CPro11sBuff(void)
{   
	  uint8 i=0; 
	  uint8   vCanPro11sLen=0; 	 
    tCanInfoDef  vCanPro11s;
	  vPro11sBuff[GetInPosi_CRec(&vPro11sBuffCtrl)]=0xff;
//计算累加和	
	  for(i=0;i<vPro11sBuffCtrl.In;i++)
		{
			  vCanPro11sLen+=vPro11sBuff[i];
		}
	  vPro11sBuff[GetInPosi_CRec(&vPro11sBuffCtrl)]=vCanPro11sLen;   
		vPro11sBuff[GetInPosi_CRec(&vPro11sBuffCtrl)]=0xff; 
		
	  vCanPro11sLen=0;  
		
	  vCanPro11s.tCanID.Word = 0;	 
	  vCanPro11s.tCanID.CanID.CFrameType = CFType_11s_CDot;  
	  vCanPro11s.tCanID.CanID.CSourceAddr = 0; 
	  vCanPro11s.tCanID.CanID.CTargetAddr = CanTarget_CPhysicalAddr(vPro11sBuff[0]);    
	  vCanPro11s.Byte[0]= c11s_FC_Pro; 
		vCanPro11s.Byte[1]= vPro11sBuffCtrl.In+1; 
	  vCanPro11s.DateNum =8;	 
	  while(vCanPro11sLen < vPro11sBuffCtrl.In)
		{ 
				if(vCanPro11sLen==0)
				{
						vCanPro11s.tCanID.CanID.CDataType = CDType_11s_FHead;   
				}
				else
				{
					  vCanPro11s.tCanID.CanID.CDataType = CDType_11s_FData;  
				} 
				for(i=2;i<8;i++)
				{
					 vCanPro11s.Byte[i]=vPro11sBuff[vCanPro11sLen++];  
				}
				if(vCanPro11sLen > vPro11sBuffCtrl.In)
				{
					 vCanPro11s.tCanID.CanID.CDataType = CDType_11s_FEnd;    
			  }	 
				
	      Add_CCanSendBuff(&vCanPro11s);	
	  }  
}     


File_CCanRcv(pCANMessage->tCanID.CanID.CDataType,
			&pCANMessage->Byte[0],
			pCANMessage->DateNum); 

void  File_CCanRcv(uint8 vFileType,uint8 *pBuff,uint8 vBuffLen)
{
	  if(GetCanChkRec_CSysRunFlag()||GetUCanChkRec_CSysRunFlag())//有反馈信息需要显示
		{ 
			  uint8 i; 
				if(vFileType == CDType_11s_FHead)
				{
						InitRcvFileBuff_CCanRcv();
						for(i=0;i<vBuffLen;i++)
						{
							 m_CanRcvFileBuff[m_CanRcvFileBuffCtrl++]=*pBuff++;
						}
				}
				else if(vFileType == CDType_11s_FData)
				{
						if(m_CanRcvFileBuff[0]==*pBuff++)
						{
								if(m_CanRcvFileBuff[1]==*pBuff++)
								{
									 for(i=2;i<vBuffLen;i++)
									 {
											 m_CanRcvFileBuff[m_CanRcvFileBuffCtrl++]=*pBuff++;
									 } 	
								} 
						} 
				}
				else if(vFileType == CDType_11s_FEnd)
				{
						if(m_CanRcvFileBuff[0]==*pBuff++)
						{
								*pBuff++;        //灭火盘最后1帧没有发数据长度
							  //if(m_CanRcvFileBuff[1]==*pBuff++)
								{
									 for(i=2;i<vBuffLen;i++)
									 {
											 m_CanRcvFileBuff[m_CanRcvFileBuffCtrl++]=*pBuff++;
									 } 	
									 SetWndMessFlag(cWM_CheckRecFlag);
				           OSSemPost(pGUIDispSem); 
								} 
						} 
				}
				else if((vFileType == c11s_DBI_AnsPro)&&(GetUCanChkRec_CSysRunFlag()))
				{
					  InitRcvFileBuff_CCanRcv();
						for(i=0;i<vBuffLen;i++)
						{
								m_CanRcvFileBuff[m_CanRcvFileBuffCtrl++]=*pBuff++;
						}
					  SetWndMessFlag(cWM_CheckRecFlag);
				    OSSemPost(pGUIDispSem); 
				}
	  }
}

 
*/

/******************************************************************************
* FUNC: // END
*   IN:
*  OUT: 
******************************************************************************/
