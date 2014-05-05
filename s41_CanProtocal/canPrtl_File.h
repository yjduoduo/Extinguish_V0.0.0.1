#ifndef __canPrtl_File_H__
#define __canPrtl_File_H__
/******************************************************************************
* @file    canPrtl_File.h
* @author  yx
* @version V1.0
* @date    2013-10-10
* @brief   
* 
#include  "canPrtl_File.h"
******************************************************************************/
//
#include  "prjCompileCon.h"
#include  "canFrame.h"
#include  "CanBufLib_strFileProp.h"

/*================= extern ============================================*/
#ifdef  __canPrtl_File_C__
#define EX_canPrtl_File
#else
#define EX_canPrtl_File extern 
#endif
/*================= 常数 ============================================*/
//#define 
/*================= 结构体定义 ======================================*/

/*================= 公有结构变量声明 ================================*/

/*================= 私有函数声明 ====================================*/
#ifdef  __canPrtl_File_C__

#endif  //__canPrtl_File_C__
/*================= 公有函数声明 ====================================*/
//EX_canPrtl_File 

// CAN帧 组成文件：
extern BOOL CanRxEvtFile_iCan(THdCanFrame_st *pFrm);
extern BOOL CanRxMesgFile_iCan(THdCanFrame_st *pFrm);


// 需要发送的文件 保存，等待发送:
extern BOOL CanTxMesgFile_iCan_New(U8 taskId,
					TCanFile_sId  *pFileSId,
					U8 *pFileS, 
					U32 mByteTotal);
// 实际发送：
extern void CanTxMesgFile_iCan_Start(U8 mBuf);
extern BOOL CanTxMesgFile_iCan_Follow(U8 mBuf, BOOL *bRtnFinish);

/******************************************************************************
// END :
******************************************************************************/
#endif // __canPrtl_File_H__

