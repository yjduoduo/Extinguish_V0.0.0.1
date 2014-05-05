#ifndef __CanHd_Interface_H__
#define __CanHd_Interface_H__
/******************************************************************************
* @file    CanHd_Interface.h
* @author  yx
* @version V1.0
* @date    2013-07-24
* @brief   can�����ӿڡ�
		 driver��canStruct �� Ӧ�ò��canStruct�Ľӿڣ���callBack���Ѹ��롣
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
/*================= ���� ============================================*/
//#define 
/*================= �ṹ�嶨�� ======================================*/

/*================= ���нṹ�������� ================================*/

/*================= ˽�к�������- ���� ====================================*/
// #ifdef  __CanHd_Interface_C__

	#if U_SYS_Test_CanHw == 1
	extern void testSend_iCan(void);
	extern void testSend_eCan(void);
	#endif // U_SYS_Test_CanHw
// #endif  //__hw10_Can_C__
/*================= ˽�к������� ====================================*/
#ifdef  __CanHd_Interface_C__

// Init
void canHd_IorE_Init(U8 can_id);

//
void canHd_PinFunc(U8 canPeriId);


#endif  //__CanHd_Interface_C__
/*================= ���к������� ====================================*/
//EX_CanHd_Interface 

// Int:
extern void CanHd_IorE_Hd_Int_Enable(U8 can_id);
extern void CanHd_IorE_Hd_Int_Disable(U8 can_id);

// ת��CAN֡�ṹ: cpu canLib -> user def;
// Master: callBack.c 
// extern void CanFrmType_MsgToFrm(CAN_MSG_Type *pMsg, THdCanFrame_st *pFrm);

// ת��CAN֡�ṹ: user def -> cpu canLib;
// Master: ����ʱ��lib�õ�THdCanFrame_st��me.CanHd_IorE_Send() use.
// extern void CanFrmType_FrmToMsg(THdCanFrame_st *pFrm, CAN_MSG_Type *pMsg);

// Ӧ�ò� �� Ӳ�� ��canId �Ķ�Ӧ��ϵ��
extern U8 GetCanPeriId_FromCanId(U8 can_id);
extern U8 GetCanId_FromCanPeriId(U8 canPeriId);

// Init
extern void CanHd_IorE_Hd_Init(U8 can_id);
// Init: canBuf, canHd, canState:
extern void CanHd_IorE_HdAndBuf_Init(U8 can_id);
extern void canHd_All_HdAndBuf_Init(void);

extern void Can_Hd_Close(U8 can_id);

// rx ָ�룺
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
extern BOOL iCanHd_Send(THdCanFrame_st *pFrm); //Ӳ������
extern BOOL eCanHd_Send(THdCanFrame_st *pFrm); //Ӳ������

// rx:
// extern void CanHd_IorE_Rec(U8 can_id, U8 canMaskBuf, CAN_MSG_Type *pFrm);
// extern void iCanHd_Rec(U8 canMaskBuf, CAN_MSG_Type *pMsg); //Ӳ������
// extern void eCanHd_Rec(U8 canMaskBuf, CAN_MSG_Type *pMsg); //Ӳ������


/******************************************************************************
// END :
******************************************************************************/
#endif // __CanHd_Interface_H__

