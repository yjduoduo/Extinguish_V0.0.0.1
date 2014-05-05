#ifndef __canPrtl_iTx_H__
#define __canPrtl_iTx_H__
/******************************************************************************
* @file    canPrtl_iTx.h
* @author  yx
* @version V1.0
* @date    2013-10-22
* @brief   ��Э����֯CAN֡��������;
*		Ӧ�ð��й�11sЭ��ģ�������"can11sPrtl_iTx"�����Щ���������11s�ģ�����Ϊʡ�£���д�������ˡ�
* 
#include  "canPrtl_iTx.h"
******************************************************************************/
//
#include  "prjCompileCon.h"
// Can֡��ʽ��	
#include  "canProtocalStr.h"
#include  "canFrame.h"
// 

/*================= extern ============================================*/
#ifdef  __canPrtl_iTx_C__
#define EX_canPrtl_iTx
#else
#define EX_canPrtl_iTx extern 
#endif
/*================= ���� ============================================*/
//#define 
/*================= �ṹ�嶨�� ======================================*/

/*================= ���нṹ�������� ================================*/

/*================= ˽�к������� ====================================*/
#ifdef  __canPrtl_iTx_C__

// ���ͣ�ID, command, loop, addr:
BOOL iCan11s_tx_DetePrtlPink_InByte1(U8 mCommand,
							U8 mLoop, U8 mAddr);

#endif  //__canPrtl_iTx_C__

/*================= ���к������� ====================================*/
//EX_canPrtl_iTx 
extern void iCan_txNewFrm_ToTxBuf(void);
/*================= ���к������� ====================================*/
//EX_canPrtl_iTx // ���Է����¼���
extern void ICan_Tx_Alarm(U8 mAddr);
/*================= ���к������� ====================================*/
//EX_canPrtl_iTx 
extern void ICan_Tx_Reset(void); // ��λ
extern void ICan_Tx_RegistAll(void); // �Զ��Ǽ�
extern void ICan_Tx_HornLedCheck(void); // �Ƽ�
extern void ICan_Tx_Clock(void); // ʱ��
extern void ICan_Tx_ClrRegist(void); // ����Ǽ�
extern void ICan_Tx_Inquire_Regist(U8 mLoop); // ��ѯ�Ǽ� ?
extern void ICan_Tx_ClrLinkProg(void); // ������
extern void ICan_Tx_PcLoadIng(void); // ��������
extern void ICan_Tx_MachMaster_EnAuto(void); // ���������ӻ� �Զ�����
extern void ICan_Tx_Silence(void); // ����
extern void ICan_Tx_HornStrobe_On(void); // ���� ON
extern void ICan_Tx_HornStrobe_Off(void); // ���� ON
extern void ICan_Tx_WorkMode_Debug_On(void); // ����ģʽ
extern void ICan_Tx_WorkMode_Debug_Off(void);
extern void ICan_Tx_AutoManu(void); // �ֶ��Զ�

// IN: pnType: emPanelType ;
// IN: pnSequ: ��ţ�1~ ;
extern void ICan_Tx_InqireCommand_Stop(U8 mLoop, U8 mAddr); // ��������
extern void ICan_Tx_InqireCommand_Analog_Start(
					U8 mLoop, U8 mAddr); // ��������-ģ������
extern void ICan_Tx_InqireCommand_Analog_Stop(
					U8 mLoop, U8 mAddr);
extern void ICan_Tx_InqireCommand_DeteData_Start(
					U8 mLoop, U8 mAddr); // ��������-̽�����ڲ�����
extern void ICan_Tx_InqireCommand_DeteData_Stop(
					U8 mLoop, U8 mAddr);

// IN: mModuType:  emModuRunAuMaRemote
extern void ICan_Tx_DevRunMess_Run(U8 mLoop, U8 mAddr, 
								U8 mModuType); // ģ������
extern void ICan_Tx_DevRunMess_Stop(U8 mLoop, U8 mAddr, 
								U8 mModuType); // ģ��ֹͣ
								
								
// IN:   mDeteClass: emDeteCanClass ;
extern void ICan_Tx_OpeaDete_Disable(BOOL bDisable, 
				U8 mLoop, U8 mAddr, U8 mDeteClass); // ����������
extern void ICan_Tx_OpeaDete_ManuRunOrStop(
				BOOL bRun, 
				U8 mLoop, U8 mAddr, U8 mChannel); // ������ģ������/ֹͣ
extern void ICan_Tx_OpeaDete_SignalRegist(BOOL bRegist, 
				U8 mLoop, U8 mAddr, U8 mDeteClass); // �����������Ǽ�
extern void ICan_Tx_OpeaDete_InquireStateAndType(
						U8 mLoop, U8 mAddr); // ��������ѯ״̬������


extern void ICan_Tx_Inquire_DeteInline(U8 mLoop); // ��ѯ����
extern void ICan_Tx_Set_LoopDisable(U8 mLoop); // ���� ��·����
extern void ICan_Tx_Inquire_Regist(U8 mLoop); // ��ѯ��·�Ǽ� ?
extern void ICan_Tx_Inquire_DeteRegist(U8 mLoop); // ��ѯ��·�ֳ������Ǽ�



// ȡ�� ��ѯ�ֳ����� ���ԣ�״̬�����ߣ��ڲ����ݣ�
static void ICan_Tx_InquireCheck_Dete_Stop(U8 mCommand, U8 mLoop, U8 mAddr);
// ��ѯ�ֳ����� ״̬��
extern void ICan_Tx_Inquire_DeteState(U8 mLoop, U8 mAddr); 
extern void ICan_Tx_Inquire_DeteStaStop(U8 mLoop, U8 mAddr);
// ��ѯ�ֳ����� ģ�����ߣ�
extern void ICan_Tx_Inquire_DeteCurv(U8 mLoop, U8 mAddr); 
extern void ICan_Tx_Inquire_DeteCuvStop(U8 mLoop, U8 mAddr);
// ��ѯ�ֳ����� �ڲ����ݣ�
extern void ICan_Tx_Inquire_DeteInterData(U8 mLoop, U8 mAddr); 
extern void ICan_Tx_Inquire_DeteInterDatStop(U8 mLoop, U8 mAddr);
// ��ѯ�ֳ����� ��·��� ��·������
extern void ICan_Tx_Inquire_LoopBrowse(U8 mLoop); 
extern void ICan_Tx_Inquire_LoopBrowsStop(U8 mLoop);


extern void ICan_Tx_Inquire_SoftVersion(U8 mLoop);






/******************************************************************************
// END :
******************************************************************************/
#endif // __canPrtl_iTx_H__

