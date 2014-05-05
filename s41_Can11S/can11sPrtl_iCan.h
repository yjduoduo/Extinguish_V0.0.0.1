#ifndef __can11sPrtl_iCan_H__
#define __can11sPrtl_iCan_H__
/******************************************************************************
* @file    can11sPrtl_iCan.h
* @author  yx
* @version V1.0
* @date    2013-07-01
* @brief   
* 
#include  "can11sPrtl_iCan.h"
******************************************************************************/
//
#include  "prjCompileCon.h"
// Can帧格式：	
#include  "canProtocalStr.h"
#include  "canFrame.h"
// 

/*================= extern ============================================*/
#ifdef  __can11sPrtl_iCan_C__
#define EX_can11sPrtl_iCan
#else
#define EX_can11sPrtl_iCan extern 
#endif
/*================= 常数 ============================================*/
//#define 
/*================= 结构体定义 ======================================*/

/*================= 公有结构变量声明 ================================*/

/*================= 私有函数声明 ====================================*/
#ifdef  __can11sPrtl_iCan_C__

#endif  //__can11sPrtl_iCan_C__
/*================= 公有函数声明 ====================================*/
//EX_can11sPrtl_iCan 

// IN: pnType: emPanelType ;
// 显示单元 接收 canId.Sourse Start:
extern BOOL bGetCan11s_Rx_SrcStart(U8 pnType, U8 *pRtnSrcStart);
// 显示单元 发送 canId.Dest Start:
extern BOOL bGetCan11s_Tx_DestStart(U8 pnType, U8 *pRtnDestStart);
//   本单元 发送 canId.Sourse Start:
extern BOOL bGetCan11s_Tx_SrcStart(U8 pnType, U8 *pRtnDestStart);

// 根据源地址，计算panel: 
//CAN Aim adr -> .pnType, .pnSequ 
extern BOOL bICan11sIdSourse_ToPnTypeSequ( U8 mCanSrc, 
						U8 *pRtnPnType, U8 *pRtnPnSequ);

/******************************************************************************
// END :
******************************************************************************/
#endif // __can11sPrtl_iCan_H__

