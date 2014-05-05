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

/*================= ���к�������-lib�ⲿ ====================================*/
//EX_can12_TxEvtFile 

// �����¼����ļ�֡��ֱ����lib����֯add tx buf;
// *Master: task.
extern BOOL CanTxEvtFile(U8 can_id, 
					TCanFile_sId  *pFileSId,
					U8 *pFileS, U32 mByteTotal);


/*================= ���к�������-lib�ⲿ - ����ļ�֡�� ====================*/
//EX_can13_TxMesgFile 

// Get FileHeadָ�룺
extern BOOL bGetFileHead_CanTxMesgFile(U8 can_id, U8 mBuf, 
							   TCanTxFileHead_st  **pRtnHeadNow);

// Get FileBuf[0] λ�ã�
extern BOOL bGetFileByteBufS_CanTxMesgFile(U8 can_id, U8 mBuf, 
							   U8  **pRtnByteBufS,
							   U32 *pRtnOneBufMax);

extern void SetFile_CanTxMesgFile_Using(U8 can_id,
								TCanTxFileHead_st  *pFileHead);

//����buf���λ�ã�
extern BOOL bFindSpaceBuf_CanTxMesgFile(U8 can_id, U8 *pRtnBuf);

/*================= ���к�������-lib�ⲿ ====================================*/
//EX_can13_TxMesgFile 

//������Ϣ�ļ� ��ʼ��:
extern void CanTxMesgFile_Init(void);
extern void CanTxMesgFile_Cls_Init(U8 can_id);

//�����ѷ�����ɵ�
extern BOOL bFindBuf_bSendFinish_CanTxMesgFile(U8 can_id, U8 *pRtnBuf);


//���
// �����Ͷ����delete ĳ���ļ�id���ļ�֡��
// ����task ����ȡ��ʱ��
extern void Clr_CanTxMesgFile_FromProp(U8 can_id, 
								TCanFile_sId *pFileSId);

extern void Clr_CanTxMesgFile_FromTaskId(U8 can_id, 
								U8 taskId);

// ����ļ��������ѷ�����ɵ�
// ������ɺ���ɾ������������ס�
extern void Clr_CanTxMesgFile_HaveFinished(void);
extern void Clr_CanTxMesgFile_Cls_HaveFinished(U8 can_id);

// �ж�buf���Ƿ����ļ�
extern BOOL bBufHave_TxMesgFile(U8 can_id);

/******************************************************************************
// END :
******************************************************************************/
#endif // __CanBufLib_TxFile_incOut_H__

