#define __CanHd_Interface_C__
/******************************************************************************
* @file    CanHd_Interface.c
* @author  yx
* @version V1.0
* @date    2013-07-24
* @brief   can驱动接口。
		 driver的canStruct 与 应用层的canStruct的接口，在callBack里已隔离。
* @slave:  can driver; callBack.c 
* 
******************************************************************************/
#include  "CanHd_Interface.h"


#include  "hwEx10_PinDef.h"
#include  "hw10_Can.h"

#include  "CanBufLib_ReDef.h"
#include  "CanBufLib_incOut.h"

#include  "canFrame.h"
#include  "hw10_MaskCan.h"

#include  "hw00_HdInt.h"

#include  "Can_Manage.h"
#include  "CanIntRxBuf.h"
//#include "incFile.h"	


/*================= 常数 ============================================*/

typedef struct{
	U8 can_id;
	U8 canPeriId;
	U8 hdPhInt_id;
	U32 baudrate_us;
}TCanProp_st;

// baudrate_us = 5: 可以与watcher iCan 通讯，100K;
// baudrate_us = 37,38：可以与11S小点数 通讯:
//     37，38， 报3反馈；
//     39只收到一条反馈，然后CAN灯常亮。
//     36，40不行。
const TCanProp_st cstCanPeriId[U_CAN_ID_MAX+1] = 
{
	{U_iCAN_ID, U_PERI_CAN1_ID, U_Hd_Int_iCAN, 38}, // 5 = watcher iCan 100K bps.
	{U_eCAN_ID, U_PERI_CAN2_ID, U_Hd_Int_eCAN, 38}, // 75 = 11s
	
	{U_iCAN_ID, U_PERI_CAN1_ID, U_Hd_Int_iCAN, 75}, // default , 参考 U_CAN_ID_Default
};

/*================= 结构定义 ========================================*/

typedef struct{
	THdCanFrame_st txFrm;
	THdCanFrame_st rxFrm;
	
	BOOL bTxIdle;
	
}THdCanTask_st;

/*================= 私有结构变量声明 ================================*/

THdCanTask_st stHdCan[U_CAN_ID_MAX];

/*================= 公有函数声明 ====================================*/

/*================= 私有函数声明 ====================================*/

// 转换CAN帧结构: cpu canLib -> user def;
void CanFrmType_MsgToFrm(CAN_MSG_Type *pMsg, THdCanFrame_st *pFrm);
// 转换CAN帧结构: user def -> cpu canLib;
void CanFrmType_FrmToMsg(THdCanFrame_st *pFrm, CAN_MSG_Type *pMsg);

/*=================  ================================================*/
		
/******************************************************************************
* FUNC: // Init
*   IN:
*  OUT: 
******************************************************************************/

void CanHd_IorE_Hd_Init(U8 can_id)
{
	canHd_IorE_Init(can_id);
}


/******************************************************************************
* FUNC: // Init
******************************************************************************/

// canBuf, canHd, canState:
void CanHd_IorE_HdAndBuf_Init(U8 can_id)
{
	CanTxRxAndFileBuf_OneCls_Init(can_id);
	CanIntBuf_Init(can_id);
	
	CanHdTxState_OneCanId_Init(can_id);
	
	canHd_IorE_Init(can_id);
}

void canHd_All_HdAndBuf_Init(void)
{
U8 can_id;
	
	for(can_id=0; can_id<U_CAN_ID_MAX; can_id++)
	{
		CanHd_IorE_HdAndBuf_Init(can_id);
	}
}

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
void Can_Hd_Close(U8 can_id)
{
U8 hdPhInt_id;
	
	if(can_id >= U_CAN_ID_MAX)
	{
		return;
	}
	hdPhInt_id = cstCanPeriId[can_id].hdPhInt_id;
	if(!bGet_SysInt_Hd_Open(hdPhInt_id))
	{
		return;
	}
	MyInt_Disable(hdPhInt_id);
	
	CanRegi_Close(cstCanPeriId[can_id].canPeriId);
	
	Notify_SysInt_Hd_Close(hdPhInt_id);
	
}

/******************************************************************************
* FUNC: // 硬件Init
*   IN:
*  OUT: 
******************************************************************************/

void canHd_IorE_Init(U8 can_id)
{
U8 hdPhInt_id;
	if(can_id >= U_CAN_ID_MAX)
	{
		return;
	}
	hdPhInt_id = cstCanPeriId[can_id].hdPhInt_id;
	if(bGet_SysInt_Hd_Open(hdPhInt_id))
	{
		Can_Hd_Close(can_id);
	}
	canHd_PinFunc(cstCanPeriId[can_id].canPeriId);
	CanRegi_Init   (cstCanPeriId[can_id].canPeriId, 
				      cstCanPeriId[can_id].baudrate_us);
	
	Notify_SysInt_Hd_Open(hdPhInt_id);
	MyInt_Enable(hdPhInt_id);
	
}

void canHd_PinFunc(U8 canPeriId)
{
	if(canPeriId == U_PERI_CAN1_ID)
	{
		IniPinFunc_Can1();
	}
	else if(canPeriId == U_PERI_CAN2_ID)
	{
		IniPinFunc_Can2();
	}
}

/******************************************************************************
* FUNC: // Int:
*   IN:
*  OUT: 
******************************************************************************/
void CanHd_IorE_Hd_Int_Enable(U8 can_id)
{
	if(can_id >= U_CAN_ID_MAX)
	{
		return;
	}
	CanRegi_Int_Enable(cstCanPeriId[can_id].canPeriId);
}

void CanHd_IorE_Hd_Int_Disable(U8 can_id)
{
	if(can_id >= U_CAN_ID_MAX)
	{
		return;
	}
	CanRegi_Int_Disable(cstCanPeriId[can_id].canPeriId);
}


/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
#if U_SYS_Test_CanHw == 1
void testSend_iCan(void)
{
THdCanFrame_st stFrm;
	stFrm.id.dWord = 1;
	stFrm.length = 1;
	stFrm.taskId = 0;
	stFrm.rtData.rtU8[0] = 0x10;
	
	iCanHd_Send(&stFrm);
}
void testSend_eCan(void)
{
THdCanFrame_st stFrm;
	stFrm.id.dWord = 2;
	stFrm.length = 2;
	stFrm.taskId = 0;
	stFrm.rtData.rtU8[0] = 0x11;
	stFrm.rtData.rtU8[1] = 0x12;
	
	eCanHd_Send(&stFrm);
	
}
#endif // U_SYS_Test_CanHw
/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
BOOL iCanHd_Send(THdCanFrame_st *pFrm)
{
	return CanHd_IorE_Send(U_iCAN_ID, pFrm);
}

BOOL eCanHd_Send(THdCanFrame_st *pFrm)
{
	return CanHd_IorE_Send(U_eCAN_ID, pFrm);
}

/******************************************************************************
* FUNC: //
******************************************************************************/

BOOL CanHd_IorE_Send(U8 can_id, THdCanFrame_st *pFrm)
{
CAN_MSG_Type *pMsg;
U8 canPeriId;
BOOL bTxSucc;

	if(can_id >= U_CAN_ID_MAX)
	{
		return FALSE;
	}
	canPeriId = cstCanPeriId[can_id].canPeriId;
	
	pMsg = pGetCanRegi_TxBuf(canPeriId);
	
	CanFrmType_FrmToMsg(pFrm, pMsg);
	
	// 发送: 判断 can的Tx状态寄存器：
	bTxSucc = CanRegi_Send(canPeriId, pMsg); // 硬件发送
	
	stHdCan[can_id].txFrm = *pFrm;
	
	return bTxSucc;
}

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

// 转换CAN帧结构: cpu canLib -> user def;
// Master: callBack.c 
void CanFrmType_MsgToFrm(CAN_MSG_Type *pMsg, THdCanFrame_st *pFrm)
{
	
	U8 dataNum;
	unsigned char *pData;
	
	pFrm->id.dWord     = pMsg->id;
	pFrm->length = pMsg->len;
	
	
	pData = pMsg->dataA;
	if(pMsg->len < 4)
	{
		for(dataNum=0; dataNum<pMsg->len; dataNum++)
		{
			pFrm->rtData.rtU8[dataNum] = *pData;
			pData++;
		}
	}
	else
	{
		for(dataNum=0; dataNum<4; dataNum++)
		{
			pFrm->rtData.rtU8[dataNum] = *pData;
			pData++;
		}
		pData = pMsg->dataB;
		for(dataNum=4; dataNum<pMsg->len; dataNum++)
		{
			pFrm->rtData.rtU8[dataNum] = *pData;
			pData++;
		}
	}
	for(; dataNum<U_CAN_HARDFRAME_U8_MAX; dataNum++)
	{
		pFrm->rtData.rtU8[dataNum] = ~0;
	}
}

// 转换CAN帧结构: user def -> cpu canLib;
// Master: 发送时由lib得到THdCanFrame_st，me.CanHd_IorE_Send() use.
void CanFrmType_FrmToMsg(THdCanFrame_st *pFrm, CAN_MSG_Type *pMsg)
{
U8 dataNum;
unsigned char *pData;

	pMsg->id = (pFrm->id.dWord & (0x1FFFFFFF));
	
	if(pFrm->length >= 8)
	{
		pFrm->length = 8;
	}
	pMsg->len = pFrm->length;
	
	
	pData = pMsg->dataA;
	for(dataNum=0; dataNum<4; dataNum++)
	{
		*pData = pFrm->rtData.rtU8[dataNum];
		pData++;
	}
	if(pMsg->len >= 4)
	{
		pData = pMsg->dataB;
		for(dataNum=4; dataNum<8; dataNum++)
		{
			*pData = pFrm->rtData.rtU8[dataNum];
			pData++;
		}
	}
	
	pMsg->format = EXT_ID_FORMAT; // 29bit  // STD_ID_FORMAT=11bit.
	pMsg->type = DATA_FRAME;  // REMOTE_FRAME = Remote Frame is sent
}


/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

/******************************************************************************
*Master: // can driver.
*Master: // driver有发送时
*   Use: CanBufLib
******************************************************************************/
void CanHd_IorE_setTxIng(U8 can_id)
{
	Set_CanHdTxState_Start(can_id);
}


/******************************************************************************
*Master: // driver发送成功
*   Use: CanBufLib
* 		bCanHdTxState_HaveResult(U8 can_id, U8 *pRtnSucceed);
******************************************************************************/
void CanHd_IorE_TxSucc(U8 can_id)
{
	Set_CanHdTxState_Succeed(can_id);
	CanTxSuccInc(can_id);
}


/******************************************************************************
*Master: // driver发送失败标志；或应用层计算，发送超过定时未产生中断
*   Use: CanBufLib
* 		bCanHdTxState_HaveResult(U8 can_id, U8 *pRtnSucceed);
******************************************************************************/
void CanHd_IorE_TxFailed(U8 can_id)
{
	Set_CanHdTxState_Failed(can_id);
}

/******************************************************************************
* FUNC: // 出错标志
*   IN:
*  OUT:  出错处理
*Master: // driver, error int;
******************************************************************************/

void CanHd_IorE_NoAck(U8 can_id)
{
	Set_CanHdTxState_Failed(can_id);
}


void CanHd_IorE_bitError(U8 can_id)
{
	
	Set_CanHdTxState_Failed(can_id);
}


void CanHd_IorE_BusOff(U8 can_id)
{
	
	Set_CanHdTxState_Failed(can_id);
}

/******************************************************************************
* FUNC: // 应用层 与 硬件 的canId 的对应关系：
*   IN:
*  OUT: 
******************************************************************************/

U8 GetCanPeriId_FromCanId(U8 can_id)
{
	if(can_id >= U_CAN_ID_MAX)
	{
		return cstCanPeriId[U_CAN_ID_MAX].canPeriId;
	}
	return cstCanPeriId[can_id].canPeriId;
}

U8 GetCanId_FromCanPeriId(U8 canPeriId)
{
U8 can_id;

	for(can_id=0; can_id<U_CAN_ID_MAX; can_id++)
	{
		if(cstCanPeriId[can_id].canPeriId == canPeriId)
		{
			break;
		}
	}
	if(can_id >= U_CAN_ID_MAX)
	{
		return cstCanPeriId[U_CAN_ID_Default].can_id;
	}
	return can_id;
}


/******************************************************************************
* FUNC: // 收到的帧，直接保存在这里。
		CanHd_Rec()使用的pFrm的实际存储地址就是这里。
		// rx 指针：
* Master: can driver. rx;
*   IN:
*  OUT: 
******************************************************************************/
THdCanFrame_st *pGetCanHd_RxBuf(U8 can_id)
{
	if(can_id >= U_CAN_ID_MAX)
	{
		can_id = U_CAN_ID_Default;
	}
	return &stHdCan[can_id].rxFrm;
}

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
void CanHd_IorE_Rec(U8 can_id, U8 canMaskBuf, CAN_MSG_Type *pMsg)
{
	CanIntBuf_Add(can_id, canMaskBuf, pMsg);
	
	CanRxSuccInc(can_id);
}


/******************************************************************************
* FUNC: // 
******************************************************************************/

void eCanHd_Rec(U8 canMaskBuf, CAN_MSG_Type *pMsg) //硬件接收
{
	switch(canMaskBuf)
	{
		case U_eCanRxMaskBuf_Reset:
		case U_eCanRxMaskBuf_Alarm:
		
		case U_eCanRxMaskBuf_PtoP:
		case U_eCanRxMaskBuf_Broad:
			CanIntBuf_Add(U_eCAN_ID, canMaskBuf, pMsg);			
			CanRxSuccInc(U_eCAN_ID);
			break;
			
		default:
			break;
	}
}

/******************************************************************************
* FUNC: // 
******************************************************************************/
void iCanHd_Rec(U8 canMaskBuf, CAN_MSG_Type *pMsg) //硬件接收
{
	switch(canMaskBuf)
	{
		case U_iCanRxMaskBuf_IapFile:
		case U_iCanRxMaskBuf_IapData:
			break;
			
		case U_iCanRxMaskBuf_Reset:
		case U_iCanRxMaskBuf_Alarm:
	
		case U_iCanRxMaskBuf_PtoP:
		case U_iCanRxMaskBuf_Broad:
			CanIntBuf_Add(U_iCAN_ID, canMaskBuf, pMsg);			
			CanRxSuccInc(U_iCAN_ID);
			break;
			
		default:
			break;
	}
}


/******************************************************************************
* FUNC: // END
*   IN:
*  OUT: 
******************************************************************************/
