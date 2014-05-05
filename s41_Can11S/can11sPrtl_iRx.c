#define __can11sPrtl_iRx_C__
/******************************************************************************
* @file    can11sPrtl_iRx.c
* @author  yx
* @version V1.0
* @date    2013-07-01
* @brief   
* 
******************************************************************************/
#include  "can11sPrtl_iRx.h"


//#include "incFile.h"	
#include  "strEvtTrans.h"
#include  "sysPanel.h"
#include  "evtThingDef.h"
#include  "evt_Buf_incOut.h"

#include  "can11sPrtl_iCan.h"

/*================= 常数 ============================================*/

/*================= 结构定义 ========================================*/

/*================= 私有结构变量声明 ================================*/
static CanID  vICan11sRxId;
static THdCanFrame_st  *pNowRxFrm;

static TDev_un   vDev;
static TEvtTrans_st *pTransEvt;

static U8 vPnType;
static U8 vPnSequ;
static U8 vLoop;
static U8 vLpInBoard; // 1~
static U8 vAddr;
static U8 vChannel;

/*================= 公有函数声明 ====================================*/

/*================= 私有函数声明 ====================================*/

/*=================  ================================================*/
		
/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

void ICan11s_Rx_One(THdCanFrame_st  *pRxFrm)
{
U8 mCommand;
	
	if(!bICan11sId_Rx_DestIsMe(pRxFrm, &mCommand))
	{
		return;
	}
	pNowRxFrm = pRxFrm;
	
	if(iCan11s_Rx_DeteEvt_0x80_0x8D(mCommand))
	{
		return;
	}
	if(iCan11s_Rx_DeteOpeaResponse_0x92_0x9C(mCommand))
	{
		return;
	}
	
	switch(mCommand)
	{
		case 0x7A: // 发送本板版本号
			iCan11s_Rx_Version();
			break;
		case 0x3B: // 协议版本: length=2: 0x3B, 0X01;
			iCan11s_Rx_Protocal();
			break;
			
		case 0x7B: // 发送本板延时信息
			iCan11s_Rx_LoopHaveModuDelay();
			break;
		case 0x7C: // 启动延时
			iCan11s_Rx_RunDelay();
			break;
		case 0x7F: // 发送本板未收到应答信息
			iCan11s_Rx_LoopNoAck();
			break;
			
		case 0x87: 
		case 0x88: 
			iCan11s_Rx_LoopFault(mCommand);
			break;
			
		case 0x90: 
		case 0x91: 
		case 0xE0: 
			iCan11s_Rx_DeteEvt_0x90_0x91_0xE0(mCommand);
			break;
			
		case 0x9F: 
			iCan11s_Rx_DeteEvt_0x9F(mCommand);
			break;
			
		case 0xA0: 
			iCan11s_Rx_DeteCheckResponse_0xA0(mCommand);
			break;
		case 0xA1: 
			iCan11s_Rx_DeteCheckResponse_0xA1(mCommand);
			break;
			
			
			// 
		default:
			break;
	}
}


/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

// 手动启动、屏蔽的反馈：
void iCan11s_Rx_Response_DeteOpea(U8 mResponseState, 
								 TDev_un stDev, U8 mType)
{
	
}

// 模拟曲线，内部数据，类型状态； 页面决定是哪个。
void iCan11s_Rx_Response_DeteCheck(
							U8 mLoopPnSequ, U8 mResponseData)
{
	
}

// 探测器灵敏度， 状态电流+背景电流； 页面决定是哪个。
// 灵敏度用 mData0: 0/2  2级; 1=1级; 3=3级; 0x80=地址未登记.
// 状态电流： mData0:dete电流，mData1:回路背景电流.
void iCan11s_Rx_Response_DeteSensitiveOrCurrent(
						U8 mLoopPnSequ, U8 mData0, U8 mData1)
{
	
}

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

// OUT: TRUE=是 回路故障消息
// 注意 LoopFault 码包含在 0x80_0x91 里。
BOOL iCan11s_Rx_LoopFault(U8 mCommand)
{
	switch(mCommand)
	{
		case 0x87:
		case 0x88:
			if(!bICan11sId_Rx_Dete_BoardLpFrom1_loopAddr())
			{
				break;
			}
			
			if(BuildToDev_Me_PnModu(vPnType, 
								   vPnSequ, vLpInBoard, &vDev))
			{
				GetEvtTransStrAndClock(&vDev, &pTransEvt);
				if(mCommand == 0x87)
				{
					pTransEvt->thing = U_Fault_EVT;
				}
				else
				{
					pTransEvt->thing = U_FaultRstr_EVT;
				}
				Buf_Fault(pTransEvt);
			}
			break;
			
		default:
			return FALSE;
	}
	return TRUE;
}


/******************************************************************************
* FUNC: //
******************************************************************************/

BOOL iCan11s_Rx_DeteEvt_0x80_0x8D(U8 mCommand)
{
	if((mCommand < 0x80) || (mCommand > 0x8D))
	{
		return FALSE;
	}
	if((mCommand == 0x87) || (mCommand == 0x88)) // 回路故障除外
	{
		return FALSE;
	}
	
	
	if(!bICan11sRx_GetDev_BoardLpFrom1_loopAddr())
	{
		return FALSE;
	}
	
	
	GetEvtTransStrAndClock(&vDev, &pTransEvt);
	switch(mCommand)
	{
		case 0x80: // emDeteAlarmCls
			pTransEvt->type = pNowRxFrm->rtData.rtU8[3];
			pTransEvt->thing = U_Alarm_EVT;
			Buf_Alarm(pTransEvt);
			return TRUE;
			
		case 0x81:  // emDeteFaultClass
		case 0x82:
			pTransEvt->type = pNowRxFrm->rtData.rtU8[3];
			switch(mCommand)
			{
				case 0x81: pTransEvt->thing = U_Fault_EVT;
					break;
				case 0x82: pTransEvt->thing = U_FaultRstr_EVT;
					break;
				default:
					return FALSE;
			}
			Buf_Fault(pTransEvt);
			return TRUE;
			
		case 0x83: // emDeteResponseCls
		case 0x84: 
		case 0x85: 
		case 0x86: 
		case 0x87: 
		case 0x88: 
		case 0x89:
		case 0x8A: 
		case 0x8B: 
			pTransEvt->type = pNowRxFrm->rtData.rtU8[3];
			switch(mCommand)
			{
				case 0x83: pTransEvt->thing = U_ModuRun_EVT;
					break;
				case 0x84: pTransEvt->thing = U_ModuStop_EVT;
					break;
					
				case 0x85: pTransEvt->thing = U_ModuAck_EVT;
					break;
				case 0x86: pTransEvt->thing = U_ModuAckRstr_EVT;
					break;					
				case 0x89: pTransEvt->thing = U_ModuMissAck_EVT;
					pTransEvt->type = ~0;
					break;
					
				case 0x8A: pTransEvt->thing = U_ModuAutoRun_EVT;
					break;
				case 0x8B: pTransEvt->thing = U_ModuManuRun_EVT;
					break;
					
				default:
					return FALSE;
			}
			Buf_Link(pTransEvt);
			return TRUE;
			
		case 0x8C:  // emDeteAlarmCls
		case 0x8D:
			pTransEvt->type = pNowRxFrm->rtData.rtU8[3];
			switch(mCommand)
			{
				case 0x8C: pTransEvt->thing = U_Spvs_EVT;
					break;
				case 0x8D: pTransEvt->thing = U_SpvsRstr_EVT;
					break;
				default:
					return FALSE;
			}
			Buf_Spvs(pTransEvt);
			return TRUE;
			
		default:
			break;
	}
	
	return FALSE;
}


BOOL iCan11s_Rx_DeteEvt_0x9F(U8 mCommand)
{
	if(mCommand != 0x9F) 
	{
		return FALSE;
	}
	
	if(!bICan11sRx_GetDev_AllLpFrom1_loopAddr())
	{
		return FALSE;
	}
	pTransEvt->type = ~0;
	pTransEvt->thing = U_FaultDeteType_EVT;
	Buf_Fault(pTransEvt);
	return TRUE;
}

BOOL iCan11s_Rx_DeteEvt_0x90_0x91_0xE0(U8 mCommand)
{
	if(  (mCommand != 0x90) 
	  && (mCommand != 0x91)
	  && (mCommand != 0xE0) 
	  )
	{
		return FALSE;
	}
	
	if(!bICan11sRx_GetDev_AllLpFrom1_loopAddr())
	{
		return FALSE;
	}
	
	GetEvtTransStrAndClock(&vDev, &pTransEvt);
	
	// emDeteResponseCls
	pTransEvt->type = pNowRxFrm->rtData.rtU8[3];
	switch(mCommand)
	{
		case 0x90: pTransEvt->thing = U_ModuManuRun_EVT;
			break;
		case 0x91: pTransEvt->thing = U_ModuManuStop_EVT;
			break;
		case 0xE0: pTransEvt->thing = U_ModuRunDelayCancel_EVT;
			break;
		default:
			return FALSE;
	}
	Buf_Link(pTransEvt);
	return TRUE;
}


BOOL iCan11s_Rx_DeteOpeaResponse_0x92_0x9C(U8 mCommand)
{
	
	if(  (mCommand < 0x92) || (mCommand > 0x9C) )
	{
		return FALSE;
	}
	
	switch(mCommand)
	{
		case 0x92:
		case 0x96:
		case 0x99:
		case 0x9A:
		case 0x9B:
			if(!bICan11sRx_GetDev_AllLpFrom1_loopAddr())
			{
				return FALSE;
			}
			iCan11s_Rx_Response_DeteOpea(mCommand, vDev, ~0);
			return TRUE;
			
			
		case 0x93: // emDeteFaultClass
		case 0x97:
		case 0x98:
		case 0x9C:
			if(!bICan11sRx_GetDev_AllLpFrom1_loopAddr())
			{
				return FALSE;
			}
			iCan11s_Rx_Response_DeteOpea(mCommand, vDev, 
										pNowRxFrm->rtData.rtU8[3]);
			return TRUE;
			
		case 0x94:
		case 0x95:
			if(!bICan11sRx_GetDev_AllLpFrom1_lpAddrChnl())
			{
				return FALSE;
			}
			iCan11s_Rx_Response_DeteOpea(mCommand, vDev, ~0);
			return TRUE;
		
		default:
			break;
	}
	
	return FALSE;
	
}

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
BOOL iCan11s_Rx_DeteCheckResponse_0xA0(U8 mCommand)
{
U8 mSourse;
U8 pnType;
U8 pnSequ;
	
	if(mCommand != 0xA0)
	{
		return FALSE;
	}
	if(!bICan11sId_Rx_Dev_PrtlTypePink(pNowRxFrm, 
						&mSourse, &pnType, &pnSequ))
	{
		return FALSE;
	}
	if(pnType != U_PN_Loop_TYPE)
	{
		return FALSE;
	}
	
	if(pNowRxFrm->rtData.rtU8[2] != 0x80) // 0x80表示数据有效
	{
		return FALSE;
	}
	
	// 模拟曲线，内部数据，类型状态
	iCan11s_Rx_Response_DeteCheck(vPnSequ, 
								 pNowRxFrm->rtData.rtU8[1]);
	
	return TRUE;
}


BOOL iCan11s_Rx_DeteCheckResponse_0xA1(U8 mCommand)
{
U8 mSourse;
U8 pnType;
U8 pnSequ;
	
	if(mCommand != 0xA1)
	{
		return FALSE;
	}
	if(!bICan11sId_Rx_Dev_PrtlTypePink(pNowRxFrm, 
						&mSourse, &pnType, &pnSequ))
	{
		return FALSE;
	}
	if(pnType != U_PN_Loop_TYPE)
	{
		return FALSE;
	}
	
	
	// 模拟曲线，内部数据，类型状态
	iCan11s_Rx_Response_DeteSensitiveOrCurrent( 
				vPnSequ, pNowRxFrm->rtData.rtU8[1], 
						 pNowRxFrm->rtData.rtU8[2]);
	
	return TRUE;
}

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

// can.dest OK:
BOOL bICan11sId_Rx_DestIsMe(THdCanFrame_st  *pRxFrm, U8 *pRtnCommand)
{

	vICan11sRxId.dWord = pRxFrm->id.dWord;
	
	if(  (vICan11sRxId.st11sId.TargetAddr != 0)
	  || (vICan11sRxId.st11sId.DataType != CDType_11s_SData)
	  )
	{
		return FALSE;
	}
	
	*pRtnCommand = pRxFrm->rtData.rtU8[0];
	Panel_inLine_Inc(vICan11sRxId.st11sId.SourceAddr);
	
	return TRUE;
}

/******************************************************************************
* FUNC: // 
//  IN: pNowRxFrm ;
// OUT: vLoop 等；
******************************************************************************/

// get 回路[1]，地址[2]：
// OUT: vLoop 等；
BOOL bICan11sId_Rx_Dete_AllLpFrom1_loopAddr(void)
{
	
	if(!bICan11sId_Rx_Dete_AllLoopFrom1(pNowRxFrm, 
							&vPnSequ, &vLoop))
	{
		return FALSE;
	}
	vPnType = U_PN_Loop_TYPE;
	// 1->1; 8->8; 9->1;
	vLpInBoard = ((vLoop - 1) % 8) + 1;
	vAddr   = pNowRxFrm->rtData.rtU8[2];
	vChannel = ~0;
	return TRUE;
}


// get 回路[1]，地址[2], 通道[3]：
BOOL bICan11sId_Rx_Dete_AllLpFrom1_lpAddrChnl(void)
{
	if(!bICan11sId_Rx_Dete_AllLoopFrom1(pNowRxFrm, 
							&vPnSequ, &vLoop))
	{
		return FALSE;
	}
	vPnType  = U_PN_Loop_TYPE;
	// 1->1; 8->8; 9->1;
	vLpInBoard = ((vLoop - 1) % 8) + 1;
	vAddr    = pNowRxFrm->rtData.rtU8[2];
	vChannel = pNowRxFrm->rtData.rtU8[3];
	return TRUE;
	
}



/******************************************************************************
* FUNC: // 
******************************************************************************/
// get 回路[1]，地址[2]：
// OUT: vLoop 等；
BOOL bICan11sId_Rx_Dete_BoardLpFrom1_loopAddr(void)
{
	
	if(!bICan11sId_Rx_Dete_BoardLoopFrom1(pNowRxFrm, 
							&vPnSequ, &vLoop))
	{
		return FALSE;
	}
	vPnType = U_PN_Loop_TYPE;
	vLpInBoard = pNowRxFrm->rtData.rtU8[1];
	vAddr   = pNowRxFrm->rtData.rtU8[2];
	vChannel = ~0;
	return TRUE;
}


/******************************************************************************
* FUNC: // 
*   IN:
*  OUT: 
******************************************************************************/

// 通过CAN帧取得 vDev
BOOL bICan11sRx_GetDev_BoardLpFrom1_loopAddr(void)
{
	
	if(!bICan11sId_Rx_Dete_BoardLpFrom1_loopAddr())
	{
		return FALSE;
	}
	
	return BuildToDev_Me_DeteMLA(vLoop, vAddr, &vDev);
	
}


BOOL bICan11sRx_GetDev_AllLpFrom1_loopAddr(void)
{
	
	if(!bICan11sId_Rx_Dete_AllLpFrom1_loopAddr())
	{
		return FALSE;
	}
	
	return BuildToDev_Me_DeteMLA(vLoop, vAddr, &vDev);
	
}


BOOL bICan11sRx_GetDev_AllLpFrom1_lpAddrChnl(void)
{
	
	if(!bICan11sId_Rx_Dete_AllLpFrom1_lpAddrChnl())
	{
		return FALSE;
	}
	
	return BuildToDev_Me_DeteMLAC(
						vLoop, vAddr, vChannel, &vDev);
	
}


/******************************************************************************
* FUNC: // 
*   IN:
*  OUT: 
******************************************************************************/



// CAN接收，判断sourse的 回路板 和回路数：
// OUT:  *pRtnPnType= U_PN_Loop_TYPE
// OUT:  *pRtnPnSequ: 单元号：1~
// OUT:  *pRtnLoop:   回路数：1~
// [1]回路号是整机排序：
BOOL bICan11sId_Rx_Dete_AllLoopFrom1( 
					THdCanFrame_st  *pRxFrm, 
					U8 *pRtnPnSequ, U8 *pRtnLoop)
{
U8 mCanSrc = pRxFrm->id.st11sId.SourceAddr;
U8 mSrcStart;

	
	*pRtnPnSequ = 0;
	*pRtnLoop = 0;
	if(!bGetCan11s_Rx_SrcStart(U_PN_Loop_TYPE, &mSrcStart))
	{
		return FALSE;
	}
	// bSequValid_RelatePanel(U8 pnType, U8 mSequPn1Start, U8 mSequNow)
	if(bSequValid_RelatePanel(U_PN_Loop_TYPE, mSrcStart, mCanSrc))
	{
		return FALSE;
	}
	
	*pRtnPnSequ = (mCanSrc - mSrcStart) + 1;
	*pRtnLoop = pRxFrm->rtData.rtU8[1];
	return TRUE;
}


// 回路板=回路板号
// 专线盘=专线盘号+9
// 总线盘=总线盘号+28
// 气体盘=气体盘+52

// CAN接收，判断sourse的板卡：
//  IN:  CAN id.st11sId.SourceAddr
// OUT:  *pRtnPnType: emPanelType
// OUT:  *pRtnPnSequ: 1~
BOOL bICan11sId_Rx_Dev_PrtlTypePink( 
					THdCanFrame_st  *pRxFrm, 
					U8 *pRtnCanSrc, U8 *pRtnPnType, U8 *pRtnPnSequ)
{
U8 mCanSrc = pRxFrm->id.st11sId.SourceAddr;

	*pRtnCanSrc = mCanSrc;
	
	return bICan11sIdSourse_ToPnTypeSequ(mCanSrc, 
						pRtnPnType, pRtnPnSequ);
	
}

/******************************************************************************
* FUNC: // 
*   IN:
*  OUT: 
******************************************************************************/



// CAN接收，判断sourse的 回路板 和回路数：
// OUT:  *pRtnPnType= U_PN_Loop_TYPE
// OUT:  *pRtnPnSequ: 单元号：1~
// OUT:  *pRtnLoop:   回路数：1~
// [1]回路号是板上排序：1~
BOOL bICan11sId_Rx_Dete_BoardLoopFrom1(
					THdCanFrame_st  *pRxFrm, 
					U8 *pRtnPnSequ, U8 *pRtnLoop)
{

U8 mCanSrc = pRxFrm->id.st11sId.SourceAddr;
U8 mSrcStart;
U8 pnSequ;

	*pRtnPnSequ = 0;
	*pRtnLoop = 0;
	if(!bGetCan11s_Rx_SrcStart(U_PN_Loop_TYPE, &mSrcStart))
	{
		return FALSE;
	}
	// bSequValid_RelatePanel(U8 pnType, U8 mSequPn1Start, U8 mSequNow)
	if(bSequValid_RelatePanel(U_PN_Loop_TYPE, mSrcStart, mCanSrc))
	{
		pnSequ = (mCanSrc - mSrcStart) + 1;
		*pRtnPnSequ = pnSequ;
		*pRtnLoop = ((pnSequ - 1) * U_OneBoard_LOOP_MAX)
					+ pRxFrm->rtData.rtU8[1];
		return TRUE;
	}
	else
	{
		return FALSE;
	}
	
}



/******************************************************************************
* FUNC: // 
*   IN:
*  OUT: 
******************************************************************************/

void iCan11s_Rx_Version(void)
{
U8 mSourse;
U8 pnType;
U8 pnSequ;
	
	if(!bICan11sId_Rx_Dev_PrtlTypePink(pNowRxFrm, 
						&mSourse, &pnType, &pnSequ))
	{
		return;
	}
	
	Panel_Vesion_Rx(pnType, pnSequ, 
						pNowRxFrm->rtData.rtU8[2] & 0x0F, 
						pNowRxFrm->rtData.rtU8[3]
						);
}


void iCan11s_Rx_Protocal(void)
{
	// 2013.11.1 抓取 小点数
	// 协议版本: length=2: 0x3B, 0X01;
}

void iCan11s_Rx_Protocal1(void)
{
U8 mSourse;
U8 pnType;
U8 pnSequ;
	
	// 0－－青鸟协议
	// 1－－51s协议
	if(pNowRxFrm->rtData.rtU8[2] == 0)
	{
		return; // 正确
	}
	
	// 错误，存故障消息：
	if(!bICan11sId_Rx_Dev_PrtlTypePink(pNowRxFrm, 
						&mSourse, &pnType, &pnSequ))
	{
		return;
	}
	
	if(!BuildToDev_Me_Panel(vPnType, vPnSequ, &vDev))
	{
		return;
	}
	
	GetEvtTransStrAndClock(&vDev, &pTransEvt);
	pTransEvt->thing = U_FaultProtocalVersion_EVT;
	Buf_Fault(pTransEvt);
	
	//  
}



void iCan11s_Rx_RunDelay(void) // ？
{
	if(!bICan11sId_Rx_Dete_AllLpFrom1_lpAddrChnl())
	{
		return;
	}
	
	
}

// 0--无缺失应答信息
// 80H--有未收到应答
// 本板状态有变化时发送
void iCan11s_Rx_LoopNoAck(void) // ？
{
U8 mSourse;
U8 pnType;
U8 pnSequ;
U8 ackMissState;   // emAckMissState 

	if(!bICan11sId_Rx_Dev_PrtlTypePink(pNowRxFrm, 
						&mSourse, &pnType, &pnSequ))
	{
		return;
	}
	ackMissState = pNowRxFrm->rtData.rtU8[2];
	
	ackMissState = ackMissState;
}



void iCan11s_Rx_LoopHaveModuDelay(void) // ？
{
U8 mSourse;
U8 pnType;
U8 pnSequ;
U8 moduRunDelayState;  // emModuRunDelayState

	if(!bICan11sId_Rx_Dev_PrtlTypePink(pNowRxFrm, 
						&mSourse, &pnType, &pnSequ))
	{
		return;
	}
	moduRunDelayState = pNowRxFrm->rtData.rtU8[2];
	
	moduRunDelayState = moduRunDelayState;
}




/******************************************************************************
* FUNC: // END
*   IN:
*  OUT: 
******************************************************************************/
