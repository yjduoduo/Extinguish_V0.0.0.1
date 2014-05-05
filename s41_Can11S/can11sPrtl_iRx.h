#ifndef __can11sPrtl_iRx_H__
#define __can11sPrtl_iRx_H__
/******************************************************************************
* @file    can11sPrtl_iRx.h
* @author  yx
* @version V1.0
* @date    2013-07-01
* @brief   
* 
#include  "can11sPrtl_iRx.h"
******************************************************************************/
//
#include  "prjCompileCon.h"
// Can帧格式：	
#include  "canProtocalStr.h"
#include  "canFrame.h"
#include  "strDevice.h"
// 

/*================= extern ============================================*/
#ifdef  __can11sPrtl_iRx_C__
#define EX_can11sPrtl_iRx
#else
#define EX_can11sPrtl_iRx extern 
#endif
/*================= 常数 ============================================*/
//#define 
/*================= 结构体定义 ======================================*/

/*================= 公有结构变量声明 ================================*/

/*================= 私有函数声明 ====================================*/
#ifdef  __can11sPrtl_iRx_C__


//  IN: pNowRxFrm ;
// OUT: vLoop 等；
// get 回路[1]，地址[2]：
BOOL bICan11sId_Rx_Dete_AllLpFrom1_loopAddr(void);
// get 回路[1]，地址[2], 通道[3]：
BOOL bICan11sId_Rx_Dete_AllLpFrom1_lpAddrChnl(void);
// get 回路[1]，地址[2]：
BOOL bICan11sId_Rx_Dete_BoardLpFrom1_loopAddr(void);



// 通过CAN帧取得 vDev
BOOL bICan11sRx_GetDev_BoardLpFrom1_loopAddr(void);
BOOL bICan11sRx_GetDev_AllLpFrom1_loopAddr(void);
BOOL bICan11sRx_GetDev_AllLpFrom1_lpAddrChnl(void);

#endif  //__can11sPrtl_iRx_C__
/*================= 私有函数声明 ====================================*/
#ifdef  __can11sPrtl_iRx_C__

void iCan11s_Rx_Version(void);
void iCan11s_Rx_Protocal(void);
void iCan11s_Rx_LoopHaveModuDelay(void); // ？
void iCan11s_Rx_RunDelay(void);  // ？
void iCan11s_Rx_LoopNoAck(void); // ？

// OUT: TRUE=是 回路故障消息
// 注意 LoopFault 码包含在 0x80_0x91 里。
BOOL iCan11s_Rx_LoopFault(U8 mCommand);
BOOL iCan11s_Rx_DeteEvt_0x80_0x8D(U8 mCommand);
BOOL iCan11s_Rx_DeteEvt_0x90_0x91_0xE0(U8 mCommand);
BOOL iCan11s_Rx_DeteEvt_0x9F(U8 mCommand);
BOOL iCan11s_Rx_DeteOpeaResponse_0x92_0x9C(U8 mCommand);

BOOL iCan11s_Rx_DeteCheckResponse_0xA0(U8 mCommand);
BOOL iCan11s_Rx_DeteCheckResponse_0xA1(U8 mCommand);



#endif  //__can11sPrtl_iRx_C__
/*================= 私有函数声明 ====================================*/
#ifdef  __can11sPrtl_iRx_C__

// 手动启动、屏蔽的反馈：
void iCan11s_Rx_Response_DeteOpea(U8 mResponseState, 
								 TDev_un stDev, U8 mType);
// 模拟曲线，内部数据，类型状态； 页面决定是哪个。
void iCan11s_Rx_Response_DeteCheck(U8 mLoopPnSequ, 
								  U8 mResponseData);
// 探测器灵敏度， 状态电流+背景电流； 页面决定是哪个。
// 灵敏度用 mData0: 0/2  2级; 1=1级; 3=3级; 0x80=地址未登记.
// 状态电流： mData0:dete电流，mData1:回路背景电流.
void iCan11s_Rx_Response_DeteSensitiveOrCurrent(
						U8 mLoopPnSequ, U8 mData0, U8 mData1);

#endif  //__can11sPrtl_iRx_C__
/*================= 公有函数声明 ====================================*/
//EX_can11sPrtl_iRx 

// CAN接收，判断sourse的 回路板 和回路数：
// OUT:  *pRtnPnType= U_PN_Loop_TYPE
// OUT:  *pRtnPnSequ: 单元号：1~
// OUT:  *pRtnLoop:   回路数：1~
// [1]回路号是整机排序：
extern BOOL bICan11sId_Rx_Dete_AllLoopFrom1( 
					THdCanFrame_st  *pRxFrm, 
					U8 *pRtnPnSequ, U8 *pRtnLoop);
// [1]回路号是板上排序：
extern BOOL bICan11sId_Rx_Dete_BoardLoopFrom1(
					THdCanFrame_st  *pRxFrm, 
					U8 *pRtnPnSequ, U8 *pRtnLoop);



// CAN接收，判断sourse的板卡：
//  IN:  CAN id.st11sId.SourceAddr
// OUT:  *pRtnPnType: emPanelType
// OUT:  *pRtnPnSequ: 1~
extern BOOL bICan11sId_Rx_Dev_PrtlTypePink( 
					THdCanFrame_st  *pRxFrm, 
					U8 *pRtnCanSrc, U8 *pRtnPnType, U8 *pRtnPnSequ);


// can.dest OK:
extern BOOL bICan11sId_Rx_DestIsMe(
					THdCanFrame_st  *pRxFrm, U8 *pRtnCommand);

/*================= 公有函数声明 ====================================*/
//EX_can11sPrtl_iRx 



extern void ICan11s_Rx_One(THdCanFrame_st  *pRxFrm);


/******************************************************************************
// END :
******************************************************************************/
#endif // __can11sPrtl_iRx_H__

