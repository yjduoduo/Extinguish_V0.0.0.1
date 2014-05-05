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
/*================= ���� ============================================*/
//#define 
/*================= �ṹ�嶨�� ======================================*/

/*================= ���нṹ�������� ================================*/

/*================= ˽�к������� ====================================*/
#ifdef  __canPrtl_File_C__

#endif  //__canPrtl_File_C__
/*================= ���к������� ====================================*/
//EX_canPrtl_File 

// CAN֡ ����ļ���
extern BOOL CanRxEvtFile_iCan(THdCanFrame_st *pFrm);
extern BOOL CanRxMesgFile_iCan(THdCanFrame_st *pFrm);


// ��Ҫ���͵��ļ� ���棬�ȴ�����:
extern BOOL CanTxMesgFile_iCan_New(U8 taskId,
					TCanFile_sId  *pFileSId,
					U8 *pFileS, 
					U32 mByteTotal);
// ʵ�ʷ��ͣ�
extern void CanTxMesgFile_iCan_Start(U8 mBuf);
extern BOOL CanTxMesgFile_iCan_Follow(U8 mBuf, BOOL *bRtnFinish);

/******************************************************************************
// END :
******************************************************************************/
#endif // __canPrtl_File_H__

