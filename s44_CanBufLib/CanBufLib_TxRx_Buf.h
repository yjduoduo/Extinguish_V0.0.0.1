#ifndef __CanBufLib_TxRx_Buf_H__
#define __CanBufLib_TxRx_Buf_H__

/******************************************************************************
* @file    CanBufLib_TxRx_Buf.h  // #include  "can02_TxRx_Buf.h"
* @author  yx
* @version V1.0
* @date    2013-07-24 
* @brief   
*  IN: 接收是can中断，发送是task;
* OUT: 各数据帧buf，需要用 CanBuf_X_Read()函数读取；
* OUT: 文件帧：-> CanBuf_file_iCanRx_Add();  
				  CanBuf_file_eCanRx_Add();
urgent tx buf是给显示任务发送命令准备的。若退出一个界面，应init urgent tx buf.
* 
#include  "CanBufLib_TxRx_Buf.h"
******************************************************************************/
//
#include  "prjCompileCon.h"
#include  "canFrame.h"


/*=================  ============================================*/

/*================= 公有函数声明-lib外部 ====================================*/
//EX_can01_TxRx_CommonBuf 

//初始化CAN帧收发buf:
//包含 "can02_TxRx_Buf"的init, 和判断是文件帧之一后的buf的init:
extern void CanTrBuf_All_Init(void);

/*============== 公有函数声明-lib外部-CAN中断load ============================*/
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

/*================= 公有函数声明-lib外部 ====================================*/
//EX_can02_TxRx_Buf - iCanRx: iCan接收; add:数据or文件; read:数据.

extern void CanBuf_iCanRx_Init(void);
extern BOOL CanBuf_iCanRx_Add(THdCanFrame_st *pCanFrm);
extern BOOL CanBuf_iCanRx_IsFull(void);
extern BOOL CanBuf_iCanRx_IsEmpty(void);

//读取buf一条：
// THdCanFrame_st  *pFrm;
// 	CanBuf_iCanRx_Read(&pFrm);
extern BOOL CanBuf_iCanRx_Read(THdCanFrame_st **ppCanFrm);

//读取上次 buf里读出的数据：
extern BOOL CanBuf_iCanRx_RdNow(THdCanFrame_st **ppCanFrm);

/*================= 公有函数声明-lib外部 ====================================*/
//EX_can02_TxRx_Buf - eCanRx: eCan接收; add:数据or文件; read:数据.

extern void CanBuf_eCanRx_Init(void);
extern BOOL CanBuf_eCanRx_Add(THdCanFrame_st *pCanFrm);
extern BOOL CanBuf_eCanRx_IsFull(void);
extern BOOL CanBuf_eCanRx_IsEmpty(void);
extern BOOL CanBuf_eCanRx_Read(THdCanFrame_st **ppCanFrm);
extern BOOL CanBuf_eCanRx_RdNow(THdCanFrame_st **ppCanFrm);

/*================= 公有函数声明-lib外部 ====================================*/
//EX_can02_TxRx_Buf - iCanTx: iCan数据帧发送.

extern void CanBuf_iCanTx_Init(void);
extern BOOL CanBuf_iCanTx_Add(THdCanFrame_st *pCanFrm);
extern BOOL CanBuf_iCanTx_IsFull(void);
extern BOOL CanBuf_iCanTx_IsEmpty(void);
extern BOOL CanBuf_iCanTx_Read(THdCanFrame_st **ppCanFrm);
extern BOOL CanBuf_iCanTx_RdNow(THdCanFrame_st **ppCanFrm);

// 删除已失效的taskId的帧，包括正在发送的。
extern void CanBuf_iCanTx_DelTaskId(U8 taskId);

/*================= 公有函数声明-lib外部 ====================================*/
//EX_can02_TxRx_Buf - eCanTx: eCan数据帧发送.

extern void CanBuf_eCanTx_Init(void);
extern BOOL CanBuf_eCanTx_Add(THdCanFrame_st *pCanFrm);
extern BOOL CanBuf_eCanTx_IsFull(void);
extern BOOL CanBuf_eCanTx_IsEmpty(void);
extern BOOL CanBuf_eCanTx_Read(THdCanFrame_st **ppCanFrm);
extern BOOL CanBuf_eCanTx_RdNow(THdCanFrame_st **ppCanFrm);
extern void CanBuf_eCanTx_DelTaskId(U8 taskId);

/*================= 公有函数声明-lib外部 ====================================*/
//EX_can02_TxRx_Buf - urgent_iCanTx: iCan数据帧紧急发送.

extern void CanBuf_urgent_iCanTx_Init(void);
extern BOOL CanBuf_urgent_iCanTx_Add(THdCanFrame_st *pCanFrm);
extern BOOL CanBuf_urgent_iCanTx_IsFull(void);
extern BOOL CanBuf_urgent_iCanTx_IsEmpty(void);
extern BOOL CanBuf_urgent_iCanTx_Read(THdCanFrame_st **ppCanFrm);
extern BOOL CanBuf_urgent_iCanTx_RdNow(THdCanFrame_st **ppCanFrm);
extern void CanBuf_urgent_iCanTx_DelTaskId(U8 taskId);

/*================= 公有函数声明-lib外部 ====================================*/
//EX_can02_TxRx_Buf - urgent_eCanTx: eCan数据帧紧急发送.

extern void CanBuf_urgent_eCanTx_Init(void);
extern BOOL CanBuf_urgent_eCanTx_Add(THdCanFrame_st *pCanFrm);
extern BOOL CanBuf_urgent_eCanTx_IsFull(void);
extern BOOL CanBuf_urgent_eCanTx_IsEmpty(void);
extern BOOL CanBuf_urgent_eCanTx_Read(THdCanFrame_st **ppCanFrm);
extern BOOL CanBuf_urgent_eCanTx_RdNow(THdCanFrame_st **ppCanFrm);
extern void CanBuf_urgent_eCanTx_DelTaskId(U8 taskId);


/*================= 公有函数声明-lib外部 ====================================*/
//EX_can02_TxRx_Buf - mesgFile_iCanTx: iCan文件的一帧发送.
extern BOOL CanBuf_mesgFile_iCanTx_IsEmpty(void);
extern BOOL CanBuf_mesgFile_iCanTx_Read(THdCanFrame_st **ppCanFrm);
extern BOOL CanBuf_mesgFile_iCanTx_RdNow(THdCanFrame_st **ppCanFrm);
extern void CanBuf_mesgFile_iCanTx_DelTaskId(U8 taskId);

//EX_can02_TxRx_Buf - mesgFile_eCanTx: eCan消息文件的一帧发送.
extern BOOL CanBuf_mesgFile_eCanTx_IsEmpty(void);
extern BOOL CanBuf_mesgFile_eCanTx_Read(THdCanFrame_st **ppCanFrm);
extern BOOL CanBuf_mesgFile_eCanTx_RdNow(THdCanFrame_st **ppCanFrm);
extern void CanBuf_mesgFile_eCanTx_DelTaskId(U8 taskId);


/*================= 公有函数声明-lib外部 ====================================*/
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

