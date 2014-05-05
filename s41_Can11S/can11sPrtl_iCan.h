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
// Can֡��ʽ��	
#include  "canProtocalStr.h"
#include  "canFrame.h"
// 

/*================= extern ============================================*/
#ifdef  __can11sPrtl_iCan_C__
#define EX_can11sPrtl_iCan
#else
#define EX_can11sPrtl_iCan extern 
#endif
/*================= ���� ============================================*/
//#define 
/*================= �ṹ�嶨�� ======================================*/

/*================= ���нṹ�������� ================================*/

/*================= ˽�к������� ====================================*/
#ifdef  __can11sPrtl_iCan_C__

#endif  //__can11sPrtl_iCan_C__
/*================= ���к������� ====================================*/
//EX_can11sPrtl_iCan 

// IN: pnType: emPanelType ;
// ��ʾ��Ԫ ���� canId.Sourse Start:
extern BOOL bGetCan11s_Rx_SrcStart(U8 pnType, U8 *pRtnSrcStart);
// ��ʾ��Ԫ ���� canId.Dest Start:
extern BOOL bGetCan11s_Tx_DestStart(U8 pnType, U8 *pRtnDestStart);
//   ����Ԫ ���� canId.Sourse Start:
extern BOOL bGetCan11s_Tx_SrcStart(U8 pnType, U8 *pRtnDestStart);

// ����Դ��ַ������panel: 
//CAN Aim adr -> .pnType, .pnSequ 
extern BOOL bICan11sIdSourse_ToPnTypeSequ( U8 mCanSrc, 
						U8 *pRtnPnType, U8 *pRtnPnSequ);

/******************************************************************************
// END :
******************************************************************************/
#endif // __can11sPrtl_iCan_H__

