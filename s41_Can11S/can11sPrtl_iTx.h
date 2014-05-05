#ifndef __can11sPrtl_iTx_H__
#define __can11sPrtl_iTx_H__
/******************************************************************************
* @file    can11sPrtl_iTx.h
* @author  yx
* @version V1.0
* @date    2013-07-01
* @brief   
* 
#include  "can11sPrtl_iTx.h"
******************************************************************************/
//
#include  "prjCompileCon.h"
// Can帧格式：	
#include  "canProtocalStr.h"
#include  "canFrame.h"
// 

/*================= extern ============================================*/
#ifdef  __can11sPrtl_iTx_C__
#define EX_can11sPrtl_iTx
#else
#define EX_can11sPrtl_iTx extern 
#endif
/*================= 常数 ============================================*/

/*================= 结构体定义 ======================================*/

/*================= 公有结构变量声明 ================================*/

/*================= 私有函数声明 ====================================*/
#ifdef  __can11sPrtl_iTx_C__


#endif  //__can11sPrtl_iTx_C__
/*================= 公有函数声明 ====================================*/
//EX_can11sPrtl_iTx 

extern U32 GetICan11sId_Broad(void);
extern U32 GetICan11sId_PtoP(U8 mDest);


extern void CompICan11s_tx_1byte_broad(U8 mByte, 
								THdCanFrame_st *pRtnFrm);
extern void CompICan11s_tx_2byte_broad(U8 mByte0, U8 mByte1, 
								THdCanFrame_st *pRtnFrm);
extern void CompICan11s_tx_nbyte_broad(U8 mNum, U8 *pByte, 
								THdCanFrame_st *pRtnFrm);


extern void CompICan11s_tx_1byte_PtoP(U8 mDest, U8 mByte, 
								THdCanFrame_st *pRtnFrm);

/*================= 公有函数声明 ====================================*/
//EX_can11sPrtl_iTx 

// IN:  mPnType: emPanelType
// IN:  mPnSequ: 1~
extern BOOL iCan11s_tx_Dev_PrtlTypePink(U8 pnType, U8 pnSequ, 
							U8 *pRtnCanDest);
// CAN发送的 dest 和 回路号：协议里粉色：
extern BOOL iCan11s_tx_Dete_PrtlTypePink(U8 mLoop, 
							U8 *pRtnCanDest, U8 *pRtnLoop);
// CAN发送的 dest 和 回路号：协议里大红色：
extern BOOL iCan11s_tx_Dete_PrtlTypeRed(U8 mLoop, 
							U8 *pRtnCanDest, U8 *pRtnLoop);
// CAN发送的 dest 和 回路号：协议里棕色：
extern BOOL iCan11s_tx_Dete_PrtlTypeBrown(U8 mLoop, 
							U8 *pRtnCanDest, U8 *pRtnLoop);
// CAN发送的 dest 和 回路号：协议里绿色：
extern BOOL iCan11s_tx_Dete_PrtlTypeGreen(U8 mLoop, 
							U8 *pRtnCanDest, U8 *pRtnLoop);



/******************************************************************************
// END :
******************************************************************************/
#endif // __can11sPrtl_iTx_H__

