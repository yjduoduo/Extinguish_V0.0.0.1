#ifndef __CanBufLib_TxFile_incOut_H__
#define __CanBufLib_TxFile_incOut_H__
/******************************************************************************
* @file    CanBufLib_TxFile_incOut.h
* @author  yx
* @version V1.0
* @date    2013-07-24
* @brief   
* 
#include  "CanBufLib_TxFile_incOut.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

#include  "canFrame.h"
#include  "CanBufLib_strFileProp.h"
/*=================   ============================================*/

/*================= 公有函数声明-lib外部 ====================================*/
//EX_can12_TxEvtFile 

// 发送事件的文件帧，直接在lib里组织add tx buf;
// *Master: task.
extern BOOL CanTxEvtFile(U8 can_id, 
					TCanFile_sId  *pFileSId,
					U8 *pFileS, U32 mByteTotal);


/*================= 公有函数声明-lib外部 - 组成文件帧用 ====================*/
//EX_can13_TxMesgFile 

// Get FileHead指针：
extern BOOL bGetFileHead_CanTxMesgFile(U8 can_id, U8 mBuf, 
							   TCanTxFileHead_st  **pRtnHeadNow);

// Get FileBuf[0] 位置：
extern BOOL bGetFileByteBufS_CanTxMesgFile(U8 can_id, U8 mBuf, 
							   U8  **pRtnByteBufS,
							   U32 *pRtnOneBufMax);

extern void SetFile_CanTxMesgFile_Using(U8 can_id,
								TCanTxFileHead_st  *pFileHead);

//查找buf里空位置：
extern BOOL bFindSpaceBuf_CanTxMesgFile(U8 can_id, U8 *pRtnBuf);

/*================= 公有函数声明-lib外部 ====================================*/
//EX_can13_TxMesgFile 

//发送信息文件 初始化:
extern void CanTxMesgFile_Init(void);
extern void CanTxMesgFile_Cls_Init(U8 can_id);

//查找已发送完成的
extern BOOL bFindBuf_bSendFinish_CanTxMesgFile(U8 can_id, U8 *pRtnBuf);


//清除
// 待发送队列里，delete 某个文件id的文件帧。
// 用于task 操作取消时。
extern void Clr_CanTxMesgFile_FromProp(U8 can_id, 
								TCanFile_sId *pFileSId);

extern void Clr_CanTxMesgFile_FromTaskId(U8 can_id, 
								U8 taskId);

// 清除文件队列里已发送完成的
// 发送完成后已删除，这个做保底。
extern void Clr_CanTxMesgFile_HaveFinished(void);
extern void Clr_CanTxMesgFile_Cls_HaveFinished(U8 can_id);

// 判断buf里是否有文件
extern BOOL bBufHave_TxMesgFile(U8 can_id);

/******************************************************************************
// END :
******************************************************************************/
#endif // __CanBufLib_TxFile_incOut_H__

