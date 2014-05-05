#ifndef __CanBufLib_RxFile_incOut_H__
#define __CanBufLib_RxFile_incOut_H__
/******************************************************************************
* @file    CanBufLib_RxFile_incOut.h
* @author  yx
* @version V1.1
* @date    2013-09-09
* @brief   
	   
V1.1， 2013-09-09
	GetCanRxEvtFile() 加返回值
	GetCanRxMesgFile() 加返回值
V1.0， 2013-07-24
* 
#include  "CanBufLib_RxFile_incOut.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

#include  "canFrame.h"
#include  "CanBufLib_strFileProp.h"
/*=================   ============================================*/

/*================= 公有函数声明-lib外部 ====================================*/
//EX_can04_RxFile_Buf - file_eCanRx:

extern void CanBuf_file_eCanRx_Init(void);
extern BOOL CanBuf_file_eCanRx_Add(THdCanFrame_st *pCanFrm);

/*================= 公有函数声明-lib外部 ====================================*/
//EX_can04_RxFile_Buf - file_iCanRx:

extern void CanBuf_file_iCanRx_Init(void);
extern BOOL CanBuf_file_iCanRx_Add(THdCanFrame_st *pCanFrm);


/*================= 公有函数声明-lib外部 - 组成文件帧用 ====================*/
//EX_can06_RxEvtFile 

// Get FileHead指针：
extern BOOL bGetFileHead_CanRxEvtFile(U8 can_id, U8 mBuf, 
							   TCanRxFileHead_st  **pRtnHeadNow);
// Get FileBuf[0] 位置：
extern BOOL bGetFileByteBufS_CanRxEvtFile(U8 can_id, U8 mBuf, 
							   U8  **pRtnByteBufS,
							   U32 *pRtnOneBufMax);

//查找buf里相同的文件:
BOOL bFindEquBuf_CanRxEvtFile(U8 can_id, 
						TCanFile_sId *pFileSId,
						U8 *pRtnBuf
						);

//查找buf里空位置：
BOOL bFindSpaceBuf_CanRxEvtFile(U8 can_id, U8 *pRtnBuf);

/*================= 公有函数声明-lib外部 ====================================*/
//EX_can06_RxEvtFile 事件文件:


//接收事件类的文件帧:
extern void CanRxEvtFile_Init(void);
extern void CanRxEvtFile_Cls_Init(U8 can_id);

//有已接收完毕的帧：
extern BOOL bCanRxEvtFile_HaveFinish(U8 can_id, U8 *pRtnBuf);
extern void Clr_One_CanRxEvtFile(U8 can_id, U8 mBuf);

// * FUNC: // 读出接收到的完整的事件文件。
// *   IN:  
// *  OUT:  pRtnFileSId: 文件id, 
		// pRtnStoreByteS: 文件字节的起始指针，
		// pRtnByteTotal:  文件字节长度。
// *  USE: 	bCanRxEvtFile_HaveFinish()=TRUE;
		// -> GetCanRxEvtFile();
		// -> Clr_One_CanRxEvtFile(); 
extern BOOL GetCanRxEvtFile(U8 can_id, U8 mBuf,
						TCanFile_sId  *pRtnFileSId,
						U8 **pRtnStoreByteS,
						U32 *pRtnByteTotal);



/*================= 公有函数声明-lib外部 - 组成文件帧用 ====================*/
//EX_can07_RxMesgFile 

// Get FileHead指针：
extern BOOL bGetFileHead_CanRxMesgFile(U8 can_id, U8 mBuf, 
							   TCanRxFileHead_st  **pRtnHeadNow);
// Get FileBuf[0] 位置：
extern BOOL bGetFileByteBufS_CanRxMesgFile(U8 can_id, U8 mBuf, 
							   U8  **pRtnByteBufS,
							   U32 *pRtnOneBufMax);
//查找buf里相同的文件:
extern BOOL bFindEquBuf_CanRxMesgFile(U8 can_id, 
						TCanFile_sId *pFileSId,
						U8 *pRtnBuf
						);
//查找buf里空位置：
extern BOOL bFindSpaceBuf_CanRxMesgFile(U8 can_id, U8 *pRtnBuf);


/*================= 公有函数声明-lib外部 ====================================*/
//EX_can07_RxMesgFile  信息文件:

//接收信息类的文件帧:
extern void CanRxMesgFile_Init(void);
extern void CanRxMesgFile_Cls_Init(U8 can_id);

//有已接收完毕的帧：
extern BOOL bCanRxMesgFile_HaveFinish(U8 can_id, U8 *pRtnBuf);
extern void Clr_One_CanRxMesgFile(U8 can_id, U8 mBuf);

// * FUNC: // 读出接收到的完整的事件文件。
// *   IN:  
// *  OUT:  pRtnFileSId: 文件id, 
		// pRtnStoreByteS: 文件字节的起始指针，
		// pRtnByteTotal:  文件字节长度。
// *  USE: 	bCanRxMesgFile_HaveFinish()=TRUE;
		// -> GetCanRxMesgFile();
		// -> Clr_One_CanRxMesgFile(); 
extern BOOL GetCanRxMesgFile(U8 can_id, U8 mBuf,
						TCanFile_sId  *pRtnFileSId,
						U8 **pRtnStoreByteS,
						U32 *pRtnByteTotal);


/******************************************************************************
// END :
******************************************************************************/
#endif // __CanBufLib_RxFile_incOut_H__

