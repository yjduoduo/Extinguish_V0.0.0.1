#ifndef __evtThingDef_H__
#define __evtThingDef_H__
/******************************************************************************
* @file    evtThingDef.h
* @author  yx
* @version V1.1_1
* @date    2013-09-11
* @brief   �¼�thing���Ͷ���
* 
* V1.1_2�� 2013-10-23 
*		add:  U_SpvsRstr_EVT�� U_FaultDeteType_EVT 
*		add:  U_ModuRun_EVT,  U_ModuStop_EVT
* V1.1_1�� 2013-09-13 
		bEvtValid()
* V1.1�� 2013-09-11 �� ������¼���
* V1.0�� 2012-01-05

#include  "evtThingDef.h"
******************************************************************************/

#include  "prjCompileCon.h"
/*================= extern ============================================*/

/*================= ���� ============================================*/
// TEvtTrans_st ->thing: �¼�����

// �Ķ� �漰��EvtThing_toHistClsBits();
 

enum emevtThingDef
{
	U_EVT_MIN,
//----- ���� ------------------------------------
	U_Ala_EVT_Min = 2, // <
	U_Alarm_EVT = 3,
	U_Ala_EVT_Max = 5, // >
//----- ��� ------------------------------------
	U_Spvs_EVT_Min = 5, // <
	U_Spvs_EVT = 6,
	U_SpvsRstr_EVT = 7,
	U_Spvs_EVT_Max = 9, // >
	
//----- ���� ------------------------------------
	U_Fau_EVT_Min = 10, // <
	
	U_Fault_EVT = 11,
	U_FaultRstr_EVT = 12,

	U_FaultDeteType_EVT = 13, // �豸���ʹ���
	U_FaultProtocalVersion_EVT = 14, // Э�鲻ƥ��

	
	U_Fau_EVT_Max = 19, // >
//----- ���� ------------------------------------
	U_Link_EVT_Min = 30, // <
	
	U_ExtgEvt_EVT = 31, 	//������¼�
	U_ExtgEvt_Min = 31, 	//������¼�
	U_ExtgCircleRun_EVT, 	//��� �������� ����, ��������sec��ʱ��
	U_ExtgCircleSec_EVT, 	//��� �������� ʣ������
	U_ExtgCircleStop_EVT, 	//��� �������� ֹͣ
	U_ExtgAnnuRun_EVT, 		//��� ��������
	U_ExtgAnnuStop_EVT, 	//��� ����ֹͣ
	U_ExtgAuxRun_EVT, 		//��� �����豸����
	U_ExtgAuxStop_EVT, 		//��� �����豸ֹͣ
	U_ExtgSprayRun_EVT, 	//��� ��������
	U_ExtgSprayStop_EVT, 	//��� ����ֹͣ
	U_ExtgSprayAck_EVT, 	//��� ��������
	U_ExtgSprayAckRstr_EVT, //��� ������������
	U_ExtgSprayMissAck_EVT, //��� ��������ȱʧ
	U_ExtgEvt_Max = 59, 	//������¼�
	
	U_ModuEvt_EVT = 60,
	U_ModuEvt_Min = 60,
	U_ModuManuRun_EVT,
	U_ModuManuStop_EVT,
	U_ModuAutoRun_EVT,
	U_ModuAutoRunDelay_EVT,		//��ʱ����
	U_ModuRunDelayCancel_EVT,	//��ʱ��������
	U_ModuAutoStop_EVT,	
	U_ModuRun_EVT,
	U_ModuStop_EVT,		//
	
	U_ModuAck_EVT = 80,			//����
	U_ModuAckRstr_EVT,		//��������
	U_ModuMissAck_EVT,		//����ȱʧ
	U_ModuEvt_Max = 99,
	
	U_Link_EVT_Max = 99, // >
	
//----- ���� ------------------------------------
	U_Opea_EVT_Min = 120, // <
	
	U_Reset_EVT,
	U_PwrOff_EVT,
	
	U_Disable_Min = 146,
	U_Disable_EVT = 146,
	U_DisableRstr_EVT,
	U_Disable_Max = 149,
	U_Opea_EVT_Max = 149, // >
//----- ������¼ ------------------------------------
	U_Super_EVT_Min = 150, // <
	
	U_Super_FlsErase_EVT,
	U_Super_FlsCopyRenew_EVT,
	
	U_Super_EVT_Max = 179, // >
//-----   ------------------------------------
	
	U_EVT_INVALID = 255,
//-----------------------------------------
};
	
	
#define bEvtValid(_thing_)   ((_thing_ > U_EVT_MIN) \
							&&(_thing_ < U_EVT_INVALID))

/*
#define U_Alarm_EVT 			0x0  //
#define U_DeteFault_EVT 		0x1  //
#define U_DeteFaultRstr_EVT	0x2  //
#define U_BoardModuFault_EVT 		0x059  //��·���ϣ�����/���·����
#define U_BoardModuFaultRstr_EVT		0x05A  //
#define U_PnFault_EVT 		0x1  //�̹���
#define U_PnFaultRstr_EVT	0x2  //


*/




/*
//������¼� ��һ������
#define U_ExtgFur_Fault_EVT		0x01 //��·����	//�м����ֹ�������
#define U_ExtgFur_FaultRstr_EVT		0x02 //��·���ϻָ�	//�м����ֹ�������
#define U_ExtgFur_SprayFeed_EVT		0x03 //�����ش�
#define U_ExtgFur_SprayFeedRstr_EVT	0x04 //�����ش���
#define U_ExtgFur_AnnuRun_EVT		0x05 //��������
#define U_ExtgFur_AnnuStop_EVT		0x06 //����ֹͣ
#define U_ExtgFur_DevRun_EVT		0x07 //����豸����
#define U_ExtgFur_DevStop_EVT		0x08 //����豸ֹͣ
#define U_ExtgFur_ZoneRun_EVT		0x09 //����������
#define U_ExtgFur_ZoneStop_EVT		0x0A //������ֹͣ
#define U_ExtgFur_SprayRun_EVT		0x0B //��������
#define U_ExtgFur_SprayDelayTmr_EVT	0x0C //�ӳ�ʱ�䣬�����Ĳ���ʾ
									//0D ��
#define U_ExtgFur_RemoteStopRstr_EVT 0x0E //Զ��ֹͣ��������

//������¼� ���Ϸ���
#define U_ExtgFault_Modu_EVT		0x80 //ģ�����
#define U_ExtgFault_Annu_EVT		0x40 //�������
#define U_ExtgFault_Delay_EVT		0x20 //�ӳٹ���
#define U_ExtgFault_Dev_EVT		0x10 //�����豸����
#define U_ExtgFault_SprayRun_EVT		0x08 //�����������
#define U_ExtgFault_SprayFeed_EVT		0x04 //�����ش����
#define U_ExtgFault_RemoteRun_EVT		0x02 //Զ����������
#define U_ExtgFault_RemoteStop_EVT		0x01 //Զ��ֹͣ����
//������¼� �����¼���������
#define U_Extg_Auto_Operate		0x01 //�Զ�
#define U_Extg_Manu_Operate		0x02 //�ֶ�
#define U_Extg_Remote_Operate		0x03 //Զ��
#define U_Extg_Operate_MAX		0x04 //
*/


/*
EVT=RUN,STOP,FEED,FEEDRSTR
RUN + STOP = STOP
RUN + NOFEED = RUN_NO_FEED
RUN + FEED = RUN_AND_FEED
RUN + FEED_RSTR = RUN


*/
	
/*

#define U_DRT_MODU_FAULT_EVT 		0x059  //����·����
#define U_DRT_MODU_FAU_RSTR_EVT		0x05A  //
#define U_LOOP_FAULT_EVT 		0x087  //
#define U_LOOP_FAU_RSTR_EVT 		0x088  //
*/



/******************************************************************************
// END :
******************************************************************************/
#endif // __evtThingDef_H__

