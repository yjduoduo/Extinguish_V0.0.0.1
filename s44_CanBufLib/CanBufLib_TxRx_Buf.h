#ifndef __CanBufLib_TxRx_Buf_H__
#define __CanBufLib_TxRx_Buf_H__

/******************************************************************************
* @file    CanBufLib_TxRx_Buf.h  // #include  "can02_TxRx_Buf.h"
* @author  yx
* @version V1.0
* @date    2013-07-24 
* @brief   
*  IN: ������can�жϣ�������task;
* OUT: ������֡buf����Ҫ�� CanBuf_X_Read()������ȡ��
* OUT: �ļ�֡��-> CanBuf_file_iCanRx_Add();  
				  CanBuf_file_eCanRx_Add();
urgent tx buf�Ǹ���ʾ����������׼���ġ����˳�һ�����棬Ӧinit urgent tx buf.
* 
#include  "CanBufLib_TxRx_Buf.h"
******************************************************************************/
//
#include  "prjCompileCon.h"
#include  "canFrame.h"


/*=================  ============================================*/

/*================= ���к�������-lib�ⲿ ====================================*/
//EX_can01_TxRx_CommonBuf 

//��ʼ��CAN֡�շ�buf:
//���� "can02_TxRx_Buf"��init, ���ж����ļ�֮֡һ���buf��init:
extern void CanTrBuf_All_Init(void);

/*============== ���к�������-lib�ⲿ-CAN�ж�load ============================*/
//EX_can02_TxRx_Buf - iCanIntrRx:

extern void CanBuf_iCanIntrRx_Init(void);
extern BOOL CanBuf_iCanIntrRx_Add(THdCanFrame_st *pCanFrm);
extern BOOL CanBuf_iCanIntrRx_Read(THdCanFrame_st **ppCanFrm);
extern BOOL CanBuf_iCanIntrRx_IsFull(void);
extern BOOL CanBuf_iCanIntrRx_IsEmpty(void);

//EX_can02_TxRx_Buf - eCanIntrRx:
extern void CanBuf_eCanIntrRx_Init(void);
extern BOOL CanBuf_eCanIntrRx_Add(THdCanFrame_st *pCanFrm);
extern BOOL CanBuf_eCanIntrRx_Read(THdCanFrame_st **ppCanFrm);
extern BOOL CanBuf_eCanIntrRx_IsFull(void);
extern BOOL CanBuf_eCanIntrRx_IsEmpty(void);

/*================= ���к�������-lib�ⲿ ====================================*/
//EX_can02_TxRx_Buf - iCanRx: iCan����; add:����or�ļ�; read:����.

extern void CanBuf_iCanRx_Init(void);
extern BOOL CanBuf_iCanRx_Add(THdCanFrame_st *pCanFrm);
extern BOOL CanBuf_iCanRx_IsFull(void);
extern BOOL CanBuf_iCanRx_IsEmpty(void);

//��ȡbufһ����
// THdCanFrame_st  *pFrm;
// 	CanBuf_iCanRx_Read(&pFrm);
extern BOOL CanBuf_iCanRx_Read(THdCanFrame_st **ppCanFrm);

//��ȡ�ϴ� buf����������ݣ�
extern BOOL CanBuf_iCanRx_RdNow(THdCanFrame_st **ppCanFrm);

/*================= ���к�������-lib�ⲿ ====================================*/
//EX_can02_TxRx_Buf - eCanRx: eCan����; add:����or�ļ�; read:����.

extern void CanBuf_eCanRx_Init(void);
extern BOOL CanBuf_eCanRx_Add(THdCanFrame_st *pCanFrm);
extern BOOL CanBuf_eCanRx_IsFull(void);
extern BOOL CanBuf_eCanRx_IsEmpty(void);
extern BOOL CanBuf_eCanRx_Read(THdCanFrame_st **ppCanFrm);
extern BOOL CanBuf_eCanRx_RdNow(THdCanFrame_st **ppCanFrm);

/*================= ���к�������-lib�ⲿ ====================================*/
//EX_can02_TxRx_Buf - iCanTx: iCan����֡����.

extern void CanBuf_iCanTx_Init(void);
extern BOOL CanBuf_iCanTx_Add(THdCanFrame_st *pCanFrm);
extern BOOL CanBuf_iCanTx_IsFull(void);
extern BOOL CanBuf_iCanTx_IsEmpty(void);
extern BOOL CanBuf_iCanTx_Read(THdCanFrame_st **ppCanFrm);
extern BOOL CanBuf_iCanTx_RdNow(THdCanFrame_st **ppCanFrm);

// ɾ����ʧЧ��taskId��֡���������ڷ��͵ġ�
extern void CanBuf_iCanTx_DelTaskId(U8 taskId);

/*================= ���к�������-lib�ⲿ ====================================*/
//EX_can02_TxRx_Buf - eCanTx: eCan����֡����.

extern void CanBuf_eCanTx_Init(void);
extern BOOL CanBuf_eCanTx_Add(THdCanFrame_st *pCanFrm);
extern BOOL CanBuf_eCanTx_IsFull(void);
extern BOOL CanBuf_eCanTx_IsEmpty(void);
extern BOOL CanBuf_eCanTx_Read(THdCanFrame_st **ppCanFrm);
extern BOOL CanBuf_eCanTx_RdNow(THdCanFrame_st **ppCanFrm);
extern void CanBuf_eCanTx_DelTaskId(U8 taskId);

/*================= ���к�������-lib�ⲿ ====================================*/
//EX_can02_TxRx_Buf - urgent_iCanTx: iCan����֡��������.

extern void CanBuf_urgent_iCanTx_Init(void);
extern BOOL CanBuf_urgent_iCanTx_Add(THdCanFrame_st *pCanFrm);
extern BOOL CanBuf_urgent_iCanTx_IsFull(void);
extern BOOL CanBuf_urgent_iCanTx_IsEmpty(void);
extern BOOL CanBuf_urgent_iCanTx_Read(THdCanFrame_st **ppCanFrm);
extern BOOL CanBuf_urgent_iCanTx_RdNow(THdCanFrame_st **ppCanFrm);
extern void CanBuf_urgent_iCanTx_DelTaskId(U8 taskId);

/*================= ���к�������-lib�ⲿ ====================================*/
//EX_can02_TxRx_Buf - urgent_eCanTx: eCan����֡��������.

extern void CanBuf_urgent_eCanTx_Init(void);
extern BOOL CanBuf_urgent_eCanTx_Add(THdCanFrame_st *pCanFrm);
extern BOOL CanBuf_urgent_eCanTx_IsFull(void);
extern BOOL CanBuf_urgent_eCanTx_IsEmpty(void);
extern BOOL CanBuf_urgent_eCanTx_Read(THdCanFrame_st **ppCanFrm);
extern BOOL CanBuf_urgent_eCanTx_RdNow(THdCanFrame_st **ppCanFrm);
extern void CanBuf_urgent_eCanTx_DelTaskId(U8 taskId);


/*================= ���к�������-lib�ⲿ ====================================*/
//EX_can02_TxRx_Buf - mesgFile_iCanTx: iCan�ļ���һ֡����.
extern BOOL CanBuf_mesgFile_iCanTx_IsEmpty(void);
extern BOOL CanBuf_mesgFile_iCanTx_Read(THdCanFrame_st **ppCanFrm);
extern BOOL CanBuf_mesgFile_iCanTx_RdNow(THdCanFrame_st **ppCanFrm);
extern void CanBuf_mesgFile_iCanTx_DelTaskId(U8 taskId);

//EX_can02_TxRx_Buf - mesgFile_eCanTx: eCan��Ϣ�ļ���һ֡����.
extern BOOL CanBuf_mesgFile_eCanTx_IsEmpty(void);
extern BOOL CanBuf_mesgFile_eCanTx_Read(THdCanFrame_st **ppCanFrm);
extern BOOL CanBuf_mesgFile_eCanTx_RdNow(THdCanFrame_st **ppCanFrm);
extern void CanBuf_mesgFile_eCanTx_DelTaskId(U8 taskId);


/*================= ���к�������-lib�ⲿ ====================================*/
//EX_can02_TxRx_Buf 

extern void CanBuf_Rx_Init(U8 can_id);
extern BOOL CanBuf_Rx_Add(U8 can_id, THdCanFrame_st *pCanFrm);
extern BOOL CanBuf_Rx_IsFull(U8 can_id);
extern BOOL CanBuf_Rx_IsEmpty(U8 can_id);
extern BOOL CanBuf_Rx_Read(U8 can_id, THdCanFrame_st **ppCanFrm);
extern BOOL CanBuf_Rx_RdNow(U8 can_id, THdCanFrame_st **ppCanFrm);


extern void CanBuf_Tx_Init(U8 can_id);
extern BOOL CanBuf_Tx_Add(U8 can_id, THdCanFrame_st *pCanFrm);
extern BOOL CanBuf_Tx_IsFull(U8 can_id);
extern BOOL CanBuf_Tx_IsEmpty(U8 can_id);
extern BOOL CanBuf_Tx_Read(U8 can_id, THdCanFrame_st **ppCanFrm);
extern BOOL CanBuf_Tx_RdNow(U8 can_id, THdCanFrame_st **ppCanFrm);
extern void CanBuf_Tx_DelTaskId(U8 can_id, U8 taskId);



extern void CanBuf_urgent_Tx_Init(U8 can_id);
extern BOOL CanBuf_urgent_Tx_Add(U8 can_id, THdCanFrame_st *pCanFrm);
extern BOOL CanBuf_urgent_Tx_IsFull(U8 can_id);
extern BOOL CanBuf_urgent_Tx_IsEmpty(U8 can_id);
extern BOOL CanBuf_urgent_Tx_Read(U8 can_id, THdCanFrame_st **ppCanFrm);
extern BOOL CanBuf_urgent_Tx_RdNow(U8 can_id, THdCanFrame_st **ppCanFrm);
extern void CanBuf_urgent_Tx_DelTaskId(U8 can_id, U8 taskId);

extern void CanBuf_mesgFile_Tx_Init(U8 can_id);
extern BOOL CanBuf_mesgFile_Tx_Add(U8 can_id, THdCanFrame_st *pCanFrm);
extern BOOL CanBuf_mesgFile_Tx_IsEmpty(U8 can_id);
extern BOOL CanBuf_mesgFile_Tx_Read(U8 can_id, THdCanFrame_st **ppCanFrm);
extern BOOL CanBuf_mesgFile_Tx_RdNow(U8 can_id, THdCanFrame_st **ppCanFrm);
extern void CanBuf_mesgFile_Tx_DelTaskId(U8 can_id, U8 taskId);


/******************************************************************************
// END :
******************************************************************************/
#endif // __CanBufLib_TxRx_Buf_H__

