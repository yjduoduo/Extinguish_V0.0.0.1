#ifndef __can_DataOrFile_H__
#define __can_DataOrFile_H__
/******************************************************************************
* @file    can_DataOrFile.h
* @author  yx
* @version V1.0
* @date    2013-07-24
* @brief   判断 数据帧 或 文件帧
* 
#include  "can_DataOrFile.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

#include  "canFrame.h"
#include  "CanBufLib_strFileProp.h"
#include  "canProtocalStr.h"

/*================= extern ============================================*/
#ifdef  __can_DataOrFile_C__
#define EX_can_DataOrFile
#else
#define EX_can_DataOrFile extern 
#endif
/*================= 常数 ============================================*/
//#define 
/*================= 结构体定义 ======================================*/

/*================= 公有结构变量声明 ================================*/

/*================= 私有函数声明 ====================================*/
#ifdef  __can_DataOrFile_C__

#endif  //__can_DataOrFile_C__
/*================= 公有函数声明 ====================================*/
//EX_can_DataOrFile 

extern void Get_MeHeartBeat(U8 can_id, THdCanFrame_st **ppFrm);

//是文件(事件)：
BOOL bCanFrmIsEvtFile(U8 canId, U32 mCanFrmId);
//是文件(信息类)：
BOOL bCanFrmIsMessageFile(U8 canId, U32 mCanFrmId);


//分解29bits canId to fileProp:
BOOL CanRx_File_CompProp(U8 can_id, 
						THdCanFrame_st *pFrm,
						TCanFile_sId *pRtnFileSId,
						U8 *pRtnFileHeadOrData);
//组成can发送的id:
// *   IN:  mFileHeadOrData = emCanFrm11sDataOrFile;
U32 CanTx_File_CompId(U8 can_id,
						TCanFile_sId *pFileSId, 
						U8  mFileHeadOrData);


/******************************************************************************
// END :
******************************************************************************/
#endif // __can_DataOrFile_H__

