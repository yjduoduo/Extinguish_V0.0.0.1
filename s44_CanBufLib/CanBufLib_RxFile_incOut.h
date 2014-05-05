#ifndef __CanBufLib_RxFile_incOut_H__
#define __CanBufLib_RxFile_incOut_H__
/******************************************************************************
* @file    CanBufLib_RxFile_incOut.h
* @author  yx
* @version V1.1
* @date    2013-09-09
* @brief   
	   
V1.1�� 2013-09-09
	GetCanRxEvtFile() �ӷ���ֵ
	GetCanRxMesgFile() �ӷ���ֵ
V1.0�� 2013-07-24
* 
#include  "CanBufLib_RxFile_incOut.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

#include  "canFrame.h"
#include  "CanBufLib_strFileProp.h"
/*=================   ============================================*/

/*================= ���к�������-lib�ⲿ ====================================*/
//EX_can04_RxFile_Buf - file_eCanRx:

extern void CanBuf_file_eCanRx_Init(void);
extern BOOL CanBuf_file_eCanRx_Add(THdCanFrame_st *pCanFrm);

/*================= ���к�������-lib�ⲿ ====================================*/
//EX_can04_RxFile_Buf - file_iCanRx:

extern void CanBuf_file_iCanRx_Init(void);
extern BOOL CanBuf_file_iCanRx_Add(THdCanFrame_st *pCanFrm);


/*================= ���к�������-lib�ⲿ - ����ļ�֡�� ====================*/
//EX_can06_RxEvtFile 

// Get FileHeadָ�룺
extern BOOL bGetFileHead_CanRxEvtFile(U8 can_id, U8 mBuf, 
							   TCanRxFileHead_st  **pRtnHeadNow);
// Get FileBuf[0] λ�ã�
extern BOOL bGetFileByteBufS_CanRxEvtFile(U8 can_id, U8 mBuf, 
							   U8  **pRtnByteBufS,
							   U32 *pRtnOneBufMax);

//����buf����ͬ���ļ�:
BOOL bFindEquBuf_CanRxEvtFile(U8 can_id, 
						TCanFile_sId *pFileSId,
						U8 *pRtnBuf
						);

//����buf���λ�ã�
BOOL bFindSpaceBuf_CanRxEvtFile(U8 can_id, U8 *pRtnBuf);

/*================= ���к�������-lib�ⲿ ====================================*/
//EX_can06_RxEvtFile �¼��ļ�:


//�����¼�����ļ�֡:
extern void CanRxEvtFile_Init(void);
extern void CanRxEvtFile_Cls_Init(U8 can_id);

//���ѽ�����ϵ�֡��
extern BOOL bCanRxEvtFile_HaveFinish(U8 can_id, U8 *pRtnBuf);
extern void Clr_One_CanRxEvtFile(U8 can_id, U8 mBuf);

// * FUNC: // �������յ����������¼��ļ���
// *   IN:  
// *  OUT:  pRtnFileSId: �ļ�id, 
		// pRtnStoreByteS: �ļ��ֽڵ���ʼָ�룬
		// pRtnByteTotal:  �ļ��ֽڳ��ȡ�
// *  USE: 	bCanRxEvtFile_HaveFinish()=TRUE;
		// -> GetCanRxEvtFile();
		// -> Clr_One_CanRxEvtFile(); 
extern BOOL GetCanRxEvtFile(U8 can_id, U8 mBuf,
						TCanFile_sId  *pRtnFileSId,
						U8 **pRtnStoreByteS,
						U32 *pRtnByteTotal);



/*================= ���к�������-lib�ⲿ - ����ļ�֡�� ====================*/
//EX_can07_RxMesgFile 

// Get FileHeadָ�룺
extern BOOL bGetFileHead_CanRxMesgFile(U8 can_id, U8 mBuf, 
							   TCanRxFileHead_st  **pRtnHeadNow);
// Get FileBuf[0] λ�ã�
extern BOOL bGetFileByteBufS_CanRxMesgFile(U8 can_id, U8 mBuf, 
							   U8  **pRtnByteBufS,
							   U32 *pRtnOneBufMax);
//����buf����ͬ���ļ�:
extern BOOL bFindEquBuf_CanRxMesgFile(U8 can_id, 
						TCanFile_sId *pFileSId,
						U8 *pRtnBuf
						);
//����buf���λ�ã�
extern BOOL bFindSpaceBuf_CanRxMesgFile(U8 can_id, U8 *pRtnBuf);


/*================= ���к�������-lib�ⲿ ====================================*/
//EX_can07_RxMesgFile  ��Ϣ�ļ�:

//������Ϣ����ļ�֡:
extern void CanRxMesgFile_Init(void);
extern void CanRxMesgFile_Cls_Init(U8 can_id);

//���ѽ�����ϵ�֡��
extern BOOL bCanRxMesgFile_HaveFinish(U8 can_id, U8 *pRtnBuf);
extern void Clr_One_CanRxMesgFile(U8 can_id, U8 mBuf);

// * FUNC: // �������յ����������¼��ļ���
// *   IN:  
// *  OUT:  pRtnFileSId: �ļ�id, 
		// pRtnStoreByteS: �ļ��ֽڵ���ʼָ�룬
		// pRtnByteTotal:  �ļ��ֽڳ��ȡ�
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

