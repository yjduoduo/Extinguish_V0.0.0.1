#ifndef __can11sFile_H__
#define __can11sFile_H__
/******************************************************************************
* @file    can11sFile.h
* @author  yx
* @version V1.0
* @date    2013-10-10
* @brief   
* 
#include  "can11sFile.h"
******************************************************************************/
//
#include  "prjCompileCon.h"
#include  "canFrame.h"
#include  "CanBufLib_strFileProp.h"

/*================= extern ============================================*/
#ifdef  __can11sFile_C__
#define EX_can11sFile
#else
#define EX_can11sFile extern 
#endif
/*================= ���� ============================================*/
//#define 
/*================= �ṹ�嶨�� ======================================*/

/*================= ���нṹ�������� ================================*/

/*================= ˽�к������� ====================================*/
#ifdef  __can11sFile_C__

// ���� �洢λ�ã�fileHead, �� buf[0].
// BOOL bGet11sFile_RxMesg_StoreLocat();
// BOOL bCan11sRxFile_jdgVerify();

// ���� �洢λ�ã�fileHead, �� buf[0].
// BOOL bGet11sFile_TxMesg_NewStoreLocat();
// BOOL bGet11sFile_TxMesg_bufStoreLocat();
// U8 can11sTxFile_cacuVerify();
// void can11sTxMesgFile_iCan_composeOneFrm();


extern void ICan11s_FileRx_LoopBrowse(U8 pnLoopSequ,
						U8 *pStoreByteS, U32 mByteTotal);
extern void ICan11s_FileRx_InquireRegist(U8 pnLoopSequ,
						U8 *pStoreByteS, U32 mByteTotal);

void ICan11s_FileRx_InqRegist_Detector(U8 mAdrNum, U8 *pAddrS);
void ICan11s_FileRx_InqRegist_Modu(U8 mAdrNum, U8 *pAddrS);
void ICan11s_FileRx_InqRegist_HornStrobe(U8 mAdrNum, U8 *pAddrS);
void ICan11s_FileRx_InqRegist_Broad(U8 mAdrNum, U8 *pAddrS);
void ICan11s_FileRx_InqRegist_FloorPanel(U8 mAdrNum, U8 *pAddrS);

#endif  //__can11sFile_C__
/*================= ���к������� ====================================*/
//EX_can11sFile 

// CAN֡ ����ļ���
// master: can intr rx buf read;
extern BOOL Can11sRxEvtFile_iCan(THdCanFrame_st *pFrm);
extern BOOL Can11sRxMesgFile_iCan(THdCanFrame_st *pFrm);


// ��Ҫ���͵��ļ� ���棬�ȴ�����:
extern BOOL Can11sTxMesgFile_iCan_New(U8 taskId,
					TCanFile_sId  *pFileSId,
					U8 *pFileS, 
					U32 mByteTotal);
// ʵ�ʷ��ͣ�
// master: can file tx buf -> can hard tx;
extern void Can11sTxMesgFile_iCan_Start(U8 mBuf);
extern BOOL Can11sTxMesgFile_iCan_Follow(U8 mBuf, BOOL *bRtnFinish);



/*================= ���к������� ====================================*/
//EX_can11sFile 


// ����һ���յ����ļ���
extern void ICan11s_FileRx_One(TCanFile_sId  *pFileSId,
						U8 *pStoreByteS, U32 mByteTotal);

/******************************************************************************
// END :
******************************************************************************/
#endif // __can11sFile_H__

