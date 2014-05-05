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
// Can֡��ʽ��	
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
/*================= ���� ============================================*/
//#define 
/*================= �ṹ�嶨�� ======================================*/

/*================= ���нṹ�������� ================================*/

/*================= ˽�к������� ====================================*/
#ifdef  __can11sPrtl_iRx_C__


//  IN: pNowRxFrm ;
// OUT: vLoop �ȣ�
// get ��·[1]����ַ[2]��
BOOL bICan11sId_Rx_Dete_AllLpFrom1_loopAddr(void);
// get ��·[1]����ַ[2], ͨ��[3]��
BOOL bICan11sId_Rx_Dete_AllLpFrom1_lpAddrChnl(void);
// get ��·[1]����ַ[2]��
BOOL bICan11sId_Rx_Dete_BoardLpFrom1_loopAddr(void);



// ͨ��CAN֡ȡ�� vDev
BOOL bICan11sRx_GetDev_BoardLpFrom1_loopAddr(void);
BOOL bICan11sRx_GetDev_AllLpFrom1_loopAddr(void);
BOOL bICan11sRx_GetDev_AllLpFrom1_lpAddrChnl(void);

#endif  //__can11sPrtl_iRx_C__
/*================= ˽�к������� ====================================*/
#ifdef  __can11sPrtl_iRx_C__

void iCan11s_Rx_Version(void);
void iCan11s_Rx_Protocal(void);
void iCan11s_Rx_LoopHaveModuDelay(void); // ��
void iCan11s_Rx_RunDelay(void);  // ��
void iCan11s_Rx_LoopNoAck(void); // ��

// OUT: TRUE=�� ��·������Ϣ
// ע�� LoopFault ������� 0x80_0x91 �
BOOL iCan11s_Rx_LoopFault(U8 mCommand);
BOOL iCan11s_Rx_DeteEvt_0x80_0x8D(U8 mCommand);
BOOL iCan11s_Rx_DeteEvt_0x90_0x91_0xE0(U8 mCommand);
BOOL iCan11s_Rx_DeteEvt_0x9F(U8 mCommand);
BOOL iCan11s_Rx_DeteOpeaResponse_0x92_0x9C(U8 mCommand);

BOOL iCan11s_Rx_DeteCheckResponse_0xA0(U8 mCommand);
BOOL iCan11s_Rx_DeteCheckResponse_0xA1(U8 mCommand);



#endif  //__can11sPrtl_iRx_C__
/*================= ˽�к������� ====================================*/
#ifdef  __can11sPrtl_iRx_C__

// �ֶ����������εķ�����
void iCan11s_Rx_Response_DeteOpea(U8 mResponseState, 
								 TDev_un stDev, U8 mType);
// ģ�����ߣ��ڲ����ݣ�����״̬�� ҳ��������ĸ���
void iCan11s_Rx_Response_DeteCheck(U8 mLoopPnSequ, 
								  U8 mResponseData);
// ̽���������ȣ� ״̬����+���������� ҳ��������ĸ���
// �������� mData0: 0/2  2��; 1=1��; 3=3��; 0x80=��ַδ�Ǽ�.
// ״̬������ mData0:dete������mData1:��·��������.
void iCan11s_Rx_Response_DeteSensitiveOrCurrent(
						U8 mLoopPnSequ, U8 mData0, U8 mData1);

#endif  //__can11sPrtl_iRx_C__
/*================= ���к������� ====================================*/
//EX_can11sPrtl_iRx 

// CAN���գ��ж�sourse�� ��·�� �ͻ�·����
// OUT:  *pRtnPnType= U_PN_Loop_TYPE
// OUT:  *pRtnPnSequ: ��Ԫ�ţ�1~
// OUT:  *pRtnLoop:   ��·����1~
// [1]��·������������
extern BOOL bICan11sId_Rx_Dete_AllLoopFrom1( 
					THdCanFrame_st  *pRxFrm, 
					U8 *pRtnPnSequ, U8 *pRtnLoop);
// [1]��·���ǰ�������
extern BOOL bICan11sId_Rx_Dete_BoardLoopFrom1(
					THdCanFrame_st  *pRxFrm, 
					U8 *pRtnPnSequ, U8 *pRtnLoop);



// CAN���գ��ж�sourse�İ忨��
//  IN:  CAN id.st11sId.SourceAddr
// OUT:  *pRtnPnType: emPanelType
// OUT:  *pRtnPnSequ: 1~
extern BOOL bICan11sId_Rx_Dev_PrtlTypePink( 
					THdCanFrame_st  *pRxFrm, 
					U8 *pRtnCanSrc, U8 *pRtnPnType, U8 *pRtnPnSequ);


// can.dest OK:
extern BOOL bICan11sId_Rx_DestIsMe(
					THdCanFrame_st  *pRxFrm, U8 *pRtnCommand);

/*================= ���к������� ====================================*/
//EX_can11sPrtl_iRx 



extern void ICan11s_Rx_One(THdCanFrame_st  *pRxFrm);


/******************************************************************************
// END :
******************************************************************************/
#endif // __can11sPrtl_iRx_H__

