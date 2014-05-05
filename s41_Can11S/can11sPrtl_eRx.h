#ifndef __can11sPrtl_eRx_H__
#define __can11sPrtl_eRx_H__
/******************************************************************************
* @file    can11sPrtl_eRx.h
* @author  yx
* @version V1.0
* @date    2013-07-01
* @brief   
* 
#include  "can11sPrtl_eRx.h"
******************************************************************************/
//
#include  "prjCompileCon.h"
// Can帧格式：	
#include  "canProtocalStr.h"
#include  "canFrame.h"
// 

/*================= extern ============================================*/
#ifdef  __can11sPrtl_eRx_C__
#define EX_can11sPrtl_eRx
#else
#define EX_can11sPrtl_eRx extern 
#endif
/*================= 常数 ============================================*/
//#define 
/*================= 结构体定义 ======================================*/

/*================= 公有结构变量声明 ================================*/

/*================= 私有函数声明 ====================================*/
#ifdef  __can11sPrtl_eRx_C__
// can.dest OK:
BOOL bECan11sId_Rx_DestIsMe(THdCanFrame_st  *pRxFrm,
						   U8 *pRtnMachine, U8 *pRtnCommand);

#endif  //__can11sPrtl_eRx_C__
/*================= 公有函数声明 ====================================*/
//EX_can11sPrtl_eRx 

extern void ECan11s_Rx_One(THdCanFrame_st  *pRxFrm);

/******************************************************************************
// END :
******************************************************************************/
#endif // __can11sPrtl_eRx_H__

