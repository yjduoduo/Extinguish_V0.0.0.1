#ifndef __CanBufLib_incOut_H__
#define __CanBufLib_incOut_H__
/******************************************************************************
* @file    CanBufLib_incOut.h
* @author  yx
* @version V1.4
* @date    2013-10-21
* @brief   
*	    
* V1.4�� 2013-10-21  ��CanBuf_Driver_V0.0.0.1_0.0.8��
*	   canIntrBuf_toBuf_Move() �� extern, ����master�Լ������жϽ��ա�
*		U_ICanIntrRx_ID  U_ECanIntrRx_ID �����ˣ���Ϊ���ж�����Ҫ�϶�Ĵ���
* V1.4�� 2013-10-11  ��CanBuf_Driver_V0.0.0.1_0.0.7��
*		�� buf ������
* V1.3�� 2013-10-11  ��CanBuf_Driver_V0.0.0.1_0.0.6��
*	�����ѷ��档 evtFile���շ�δ���ԡ�
*	 add:  CanIntrBuf_Move();
*	�ļ��� �й�Э��Ĳ��֣�����master����libֻ�ṩ λ��ָ�롣
*	fileHead �� struct ��"can05_FileHead.h"�ĵ�   "CanBufLib_strFileProp.h"��
*	ȥ�����жϵĿ��� ��ʹ�á���Ϊ�ж�add() ���߲�����outʱ����in�������쳣��
* 	��������ʼ�����ú����Ĵ��� ���� bufCircle �� inDec���� .Fullδ�жϵĴ���
* V1.2�� 2013-09-09
*	GetCanRxEvtFile() �ӷ���ֵ
*	GetCanRxMesgFile() �ӷ���ֵ
V1.1, 2013-07-23 ע��
* 
#include  "CanBufLib_incOut.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

// #include  "canBufLib_Inc_Extern.h"
// #include  "CanBufLib_ReDef.h"
// #include  "CanBufLib_strFileProp.h"

#include  "CanBufLib_TxRx_Buf.h"
#include  "CanBufLib_TxState.h"
#include  "CanBufLib_TxFile_incOut.h"
#include  "CanBufLib_RxFile_incOut.h"


/******************************************************************************
// lib���漰CANЭ�飺file�� ��ɺͷֽ⣬���Բ��� U_CAN_1Frame_FileByte ��
******************************************************************************/

/******************************************************************************
// main����

void can_manage_task(U8 can_id)
{
	// ��ʼ����
*	CanTxRxAndFileBuf_Init();
*	CanTxRxAndFileBuf_OneCls_Init(U8 can_id);

	//�жϽ��գ�CanBufLib_TxRx_Buf.h
	//����״̬�иı䣺CanBufLib_TxState.h

	// �����ļ���
*	CanTxEvtFile();
*	CanTxMesgFile_iCan_New();
	
	//main�������intr���յ����ļ�֡����֯Ϊ�ļ���
*	void CanFrmRx_toFile(void);

	//�����¼�֡
*	bCanRxEvtFile_HaveFinish();
*	GetCanRxEvtFile();
*	Clr_One_CanRxEvtFile();

	//������Ϣ֡
*	bCanRxMesgFile_HaveFinish();
*	GetCanRxMesgFile();
*	Clr_One_CanRxMesgFile();

	//����֡�Ķ�ȡ����
*	CanBufLib_TxRx_Buf.h ->��CanBuf_Rx_Read();

	//���ͣ�
*	CanTx_txNewFrm();

	//�� ���һ�η��͵�֡���ط��ã�
*	Get_LastOne_Frm_canSend();

	

	// ��ʱ100ms�ж�buf:
*	CanTxRx_File_TmrAdd_JdgOverTime();

	//���iCan or eCan�� taskId��֡
*	CanTxAndFileBuf_IorE_DelTaskId();


}


******************************************************************************/



/*================= ���к�������-lib�ⲿ ====================================*/
//EX_can21_BufInit 

// IN: can_id : emCanLogicId_ICanECan
extern void CanTxRxAndFileBuf_Init(void);
extern void CanTxRxAndFileBuf_OneCls_Init(U8 can_id);

//���iCan or eCan�� taskId��֡
extern void CanTxAndFileBuf_IorE_DelTaskId(U8 can_id, U8 taskId);

/*================= ���к�������-lib�ⲿ ====================================*/
//EX_can05_FileHead 

extern void CanRx_FileHead_SetInvalid(TCanRxFileHead_st  *pFileHead);
extern void CanTx_FileHead_SetInvalid(TCanTxFileHead_st  *pFileHead);

//��ʱ�жϽ����ʱ����Ҫmaster��ʱ100msִ��:
//���� RxEvtFileBuf, RxMesgFileBuf, TxMesgFileBuf
//����ʱ��ɾ�������ⳤ��ռ�пռ�
extern void CanTxRx_File_TmrAdd_JdgOverTime(void);


/*================= ���к�������-lib�ⲿ ====================================*/
//EX_can20_BufManage 

//main�������intr���յ����ļ�֡����֯Ϊ�ļ���
extern void CanFrmRx_toFile(void);

// �жϽ��յ�֡������ת�������У���������������
// ��Ҫ��ʱ����
// ���ʱ��Ϊ  (һ֡����ʱ�� * (CanHd_IntrRxBuf_MAX-2))
extern void CanIntrBuf_ToClsBuf_Move(U8 can_id);

// �жϣ�����ͬ��buf.
extern void canIntrBuf_toBuf_Move(U8 can_id, 
								THdCanFrame_st *pCanFrm);

/*================= ���к�������-lib�ⲿ ====================================*/
//EX_can25_TxNewFrm 


//������һ�η��͵�buf�ļ�¼
extern void Clr_LastOne_BufCls_canSend(U8 can_id);

// ��������͵�һ֡
extern BOOL Get_LastOne_Frm_canSend(U8 can_id, 
							THdCanFrame_st **ppFrm
							);

/*================= ���к�������-lib�ⲿ ====================================*/
//EX_can25_TxNewFrm 

// * FUNC: //�·���һ֡
// *   IN:
// *  OUT: ��TxIng -> ����˳��: urgent > file > ��ʱ��+usual ;
// * NEED: iCanHd_Send(pFrm); //Ӳ������
extern BOOL CanTx_txNewFrm(U8 can_id, THdCanFrame_st **ppFrm);


/******************************************************************************
// END :
******************************************************************************/
#endif // __CanBufLib_incOut_H__

