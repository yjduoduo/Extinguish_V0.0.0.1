#ifndef __canBufLib_Inc_Extern_H__
#define __canBufLib_Inc_Extern_H__
/******************************************************************************
* @file    canBufLib_Inc_Extern.h
* @author  yx
* @version V1.0
* @date    2013-07-23
* @brief   
* 
#include  "canBufLib_Inc_Extern.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

#include  "canProtocalStr.h"
#include  "CanBufLib_strFileProp.h"

/*================= ====================================*/
//#include  "can_DataOrFile.h"

// IN: can_id = U_iCAN_ID, U_eCAN_ID

extern BOOL bCanFrmIsEvtFile(U8 can_id, U32 mCanFrmId);
extern BOOL bCanFrmIsMessageFile(U8 can_id, U32 mCanFrmId);

extern BOOL CanRx_File_CompProp(U8 can_id, 
						THdCanFrame_st *pFrm,
						TCanFile_sId *pRtnFileSId,
						U8 *pRtnFileHeadOrData);

//���can���͵�id.
extern U32 CanTx_File_CompId(U8 can_id,
						TCanFile_sId *pFileSId, 
						emCanFrm11sDataOrFile  mFileHeadOrData);

/*================= ���к������� ====================================*/
//EX_can11sFile 

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


/*================= ====================================*/
// #include  "CanIntCouple.h"
/* 2013.7.25 ��yx;
// CANĳһ��Ķ�ȡֻ��һ�����֣����Բ��ؿ��ơ�
// ����urgent��Ĳ������� ���ͳɹ����Զ������·��ͣ�
	ͬʱmain�ﻹҪ��ʱ����Ƿ���urgent���ͣ�
	���ǽ�ֹ�ġ�
// ע����main��ж�CAN�Ƿ�busy�����ǰ����жϣ�
	�����п��ܶ��� notBusy,��ʱ�����жϣ�
	���ڽ����ж����������µķ��ͣ�
	���ı���ԭ��������״̬��
�涨��������CAN�ж������µķ��͡���Ϊ���ı�״̬��

// CAN buf���ʱ��Ϊ��ֹ�жϺ�main�д����������ָ���λ����Ҫ�����жϡ�
// ����2������ʱ����ɶԳ��֣�

U32 mDisableBit;

	mDisableBit = IntDisable_May_iCanAdd();
	// ...
	IntEnable_May_iCanAdd(mDisableBit);
*/

//OUT: �жϵ�id�� enable��Ϊdisable�� bit��
extern U32 IntDisable_May_CanAdd(void);
//IN:  �жϵ�id�� enable��Ϊdisable�� bit�����ڻָ�enable��״̬��
extern void IntEnable_May_CanAdd(U32 whichDisable);

extern U32 IntDisable_May_iCanAdd(void);
extern void IntEnable_May_iCanAdd(U32 whichDisable);
extern U32 IntDisable_May_eCanAdd(void);
extern void IntEnable_May_eCanAdd(U32 whichDisable);

/*================= ====================================*/
// #include  "CanWhenTx.h"
extern BOOL bCanTx_Tmr_Arrived(U8 can_id);

    
/******************************************************************************
// END :
******************************************************************************/
#endif // __canBufLib_Inc_Extern_H__

