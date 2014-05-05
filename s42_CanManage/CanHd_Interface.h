#ifndef __CanHd_Interface_H__
#define __CanHd_Interface_H__
/******************************************************************************
* @file    CanHd_Interface.h
* @author  yx
* @version V1.0
* @date    2013-07-24
* @brief   can驱动接口。
		 driver的canStruct 与 应用层的canStruct的接口，在callBack里已隔离。
* @slave:  can driver; callBack.c 
* 
#include  "CanHd_Interface.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

#include  "canFrame.h"
/*================= extern ============================================*/
#ifdef  __CanHd_Interface_C__
#define EX_CanHd_Interface
#else
#define EX_CanHd_Interface extern 
#endif
/*================= 常数 ============================================*/
//#define 
/*================= 结构体定义 ======================================*/

/*================= 公有结构变量声明 ================================*/

/*================= 私有函数声明- 测试 ====================================*/
// #ifdef  __CanHd_Interface_C__

	#if U_SYS_Test_CanHw == 1
	extern void testSend_iCan(void);
	extern void testSend_eCan(void);
	#endif // U_SYS_Test_CanHw
// #endif  //__hw10_Can_C__
/*================= 私有函数声明 ====================================*/
#ifdef  __CanHd_Interface_C__

// Init
void canHd_IorE_Init(U8 can_id);

//
void canHd_PinFunc(U8 canPeriId);


#endif  //__CanHd_Interface_C__
/*================= 公有函数声明 ====================================*/
//EX_CanHd_Interface 

// Int:
extern void CanHd_IorE_Hd_Int_Enable(U8 can_id);
extern void CanHd_IorE_Hd_Int_Disable(U8 can_id);

// 转换CAN帧结构: cpu canLib -> user def;
// Master: callBack.c 
// extern void CanFrmType_MsgToFrm(CAN_MSG_Type *pMsg, THdCanFrame_st *pFrm);

// 转换CAN帧结构: user def -> cpu canLib;
// Master: 发送时由lib得到THdCanFrame_st，me.CanHd_IorE_Send() use.
// extern void CanFrmType_FrmToMsg(THdCanFrame_st *pFrm, CAN_MSG_Type *pMsg);

// 应用层 与 硬件 的canId 的对应关系：
extern U8 GetCanPeriId_FromCanId(U8 can_id);
extern U8 GetCanId_FromCanPeriId(U8 canPeriId);

// Init
extern void CanHd_IorE_Hd_Init(U8 can_id);
// Init: canBuf, canHd, canState:
extern void CanHd_IorE_HdAndBuf_Init(U8 can_id);
extern void canHd_All_HdAndBuf_Init(void);

extern void Can_Hd_Close(U8 can_id);

// rx 指针：
extern THdCanFrame_st *pGetCanHd_RxBuf(U8 can_id);

// bus state:
// *Master: // can driver.
extern void CanHd_IorE_setTxIng(U8 can_id);
extern void CanHd_IorE_TxSucc(U8 can_id);
extern void CanHd_IorE_TxFailed(U8 can_id);
extern void CanHd_IorE_NoAck(U8 can_id);
extern void CanHd_IorE_bitError(U8 can_id);
extern void CanHd_IorE_BusOff(U8 can_id);

// Send:
extern BOOL CanHd_IorE_Send(U8 can_id, THdCanFrame_st *pFrm);
extern BOOL iCanHd_Send(THdCanFrame_st *pFrm); //硬件发送
extern BOOL eCanHd_Send(THdCanFrame_st *pFrm); //硬件发送

// rx:
// extern void CanHd_IorE_Rec(U8 can_id, U8 canMaskBuf, CAN_MSG_Type *pFrm);
// extern void iCanHd_Rec(U8 canMaskBuf, CAN_MSG_Type *pMsg); //硬件接收
// extern void eCanHd_Rec(U8 canMaskBuf, CAN_MSG_Type *pMsg); //硬件接收


/******************************************************************************
// END :
******************************************************************************/
#endif // __CanHd_Interface_H__

