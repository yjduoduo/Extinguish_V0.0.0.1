#ifndef __CanBufLib_incOut_H__
#define __CanBufLib_incOut_H__
/******************************************************************************
* @file    CanBufLib_incOut.h
* @author  yx
* @version V1.4
* @date    2013-10-21
* @brief   
*	    
* V1.4， 2013-10-21  《CanBuf_Driver_V0.0.0.1_0.0.8》
*	   canIntrBuf_toBuf_Move() 加 extern, 方便master自己管理中断接收。
*		U_ICanIntrRx_ID  U_ECanIntrRx_ID 不用了，因为在中断里需要较多的处理。
* V1.4， 2013-10-11  《CanBuf_Driver_V0.0.0.1_0.0.7》
*		改 buf 数量。
* V1.3， 2013-10-11  《CanBuf_Driver_V0.0.0.1_0.0.6》
*	代码已仿真。 evtFile的收发未测试。
*	 add:  CanIntrBuf_Move();
*	文件的 有关协议的部分，改在master处理，lib只提供 位置指针。
*	fileHead 的 struct 由"can05_FileHead.h"改到   "CanBufLib_strFileProp.h"里
*	去掉对中断的控制 的使用。因为中断add() 单线操作，out时操作in不引发异常。
* 	改正：初始化调用函数的错误。 发现 bufCircle 里 inDec函数 .Full未判断的错误。
* V1.2， 2013-09-09
*	GetCanRxEvtFile() 加返回值
*	GetCanRxMesgFile() 加返回值
V1.1, 2013-07-23 注释
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
// lib里涉及CAN协议：file的 组成和分解，可以查找 U_CAN_1Frame_FileByte 。
******************************************************************************/

/******************************************************************************
// main处理：

void can_manage_task(U8 can_id)
{
	// 初始化：
*	CanTxRxAndFileBuf_Init();
*	CanTxRxAndFileBuf_OneCls_Init(U8 can_id);

	//中断接收：CanBufLib_TxRx_Buf.h
	//发送状态有改变：CanBufLib_TxState.h

	// 发送文件：
*	CanTxEvtFile();
*	CanTxMesgFile_iCan_New();
	
	//main流程里，将intr里收到的文件帧，组织为文件：
*	void CanFrmRx_toFile(void);

	//接收事件帧
*	bCanRxEvtFile_HaveFinish();
*	GetCanRxEvtFile();
*	Clr_One_CanRxEvtFile();

	//接收信息帧
*	bCanRxMesgFile_HaveFinish();
*	GetCanRxMesgFile();
*	Clr_One_CanRxMesgFile();

	//数据帧的读取处理：
*	CanBufLib_TxRx_Buf.h ->　CanBuf_Rx_Read();

	//发送：
*	CanTx_txNewFrm();

	//读 最后一次发送的帧，重发用：
*	Get_LastOne_Frm_canSend();

	

	// 定时100ms判断buf:
*	CanTxRx_File_TmrAdd_JdgOverTime();

	//清除iCan or eCan里 taskId的帧
*	CanTxAndFileBuf_IorE_DelTaskId();


}


******************************************************************************/



/*================= 公有函数声明-lib外部 ====================================*/
//EX_can21_BufInit 

// IN: can_id : emCanLogicId_ICanECan
extern void CanTxRxAndFileBuf_Init(void);
extern void CanTxRxAndFileBuf_OneCls_Init(U8 can_id);

//清除iCan or eCan里 taskId的帧
extern void CanTxAndFileBuf_IorE_DelTaskId(U8 can_id, U8 taskId);

/*================= 公有函数声明-lib外部 ====================================*/
//EX_can05_FileHead 

extern void CanRx_FileHead_SetInvalid(TCanRxFileHead_st  *pFileHead);
extern void CanTx_FileHead_SetInvalid(TCanTxFileHead_st  *pFileHead);

//定时判断结果超时，需要master定时100ms执行:
//包括 RxEvtFileBuf, RxMesgFileBuf, TxMesgFileBuf
//若超时，删除，以免长期占有空间
extern void CanTxRx_File_TmrAdd_JdgOverTime(void);


/*================= 公有函数声明-lib外部 ====================================*/
//EX_can20_BufManage 

//main流程里，将intr里收到的文件帧，组织为文件：
extern void CanFrmRx_toFile(void);

// 中断接收的帧，快速转入分类队列，不对内容作处理。
// 需要随时调用
// 最大时间为  (一帧传输时间 * (CanHd_IntrRxBuf_MAX-2))
extern void CanIntrBuf_ToClsBuf_Move(U8 can_id);

// 判断，进不同的buf.
extern void canIntrBuf_toBuf_Move(U8 can_id, 
								THdCanFrame_st *pCanFrm);

/*================= 公有函数声明-lib外部 ====================================*/
//EX_can25_TxNewFrm 


//清除最后一次发送的buf的记录
extern void Clr_LastOne_BufCls_canSend(U8 can_id);

// 读出最后发送的一帧
extern BOOL Get_LastOne_Frm_canSend(U8 can_id, 
							THdCanFrame_st **ppFrm
							);

/*================= 公有函数声明-lib外部 ====================================*/
//EX_can25_TxNewFrm 

// * FUNC: //新发送一帧
// *   IN:
// *  OUT: 判TxIng -> 发送顺序: urgent > file > 定时到+usual ;
// * NEED: iCanHd_Send(pFrm); //硬件发送
extern BOOL CanTx_txNewFrm(U8 can_id, THdCanFrame_st **ppFrm);


/******************************************************************************
// END :
******************************************************************************/
#endif // __CanBufLib_incOut_H__

