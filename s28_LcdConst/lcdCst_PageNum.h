#ifndef __lcdCst_PageNum_H__
#define __lcdCst_PageNum_H__
/******************************************************************************
* @file    lcdCst_PageNum.h
* @author  yx
* @version V1.0
* @date    2012-01-05
* @brief   ҳ��� �Ų�
* 
*  Master: lcdCst_Page.c; lcdCst_Menu.c;  lcdTsk_PgNum.c;
		
#include  "lcdCst_PageNum.h" 
******************************************************************************/


#include  "prjCompileCon.h"
/*================= extern ============================================*/
#ifdef  __lcdCst_PageNum_C__
#define EX_lcdCst_PageNum
#else
#define EX_lcdCst_PageNum extern 
#endif


/*================= ҳ�� =======================================*/
#define U_P000_MAIN			0	//
#define U_P001_FireAlarm		1	//��
#define U_P002_Monitor			2	//���
#define U_P003_Disable			3	//����
#define U_P004_Fault			4	//����
#define U_P005_Link				5	//����
#define U_P006_Extg				6	//����

#define U_PageNumEvent_MIN		(U_P001_FireAlarm)
#define U_PageNumEvent_MAX		(U_P006_Extg + 1)
#define U_P007_Status			7	//״̬3t	

#define U_P008_MENU			8	//
#define U_P009_UserLogin	9	//��¼

#define U_P010_ManuActModu 			10 //���� �ֶ�����
#define U_P011_Help			11 //����
#define U_P012_ManuAuto		12 //�ֶ��Զ�	
#define U_P013_SetClock		13 //ʱ��	
#define U_P014_MiniEvent		14 //
#define U_P015_SetDefault		15 //�ָ�Ĭ������	
#define U_P016_AutoRegist		16 //�Զ��Ǽ�	
#define U_P017_ManuRegist		17 //�ֶ��Ǽ�	
#define U_P018_SetDisable		18 //��������	
#define U_P019_SetNote			19 //�ֶ�ע��
	
#define U_P020_SetLinkLogic		20 //�������
#define U_P021_P		21 //
#define U_P022_P		22 //
#define U_P023_P		23 //

#define U_P024_SetMachNet		24 //����
#define U_P025_P		25 //	
#define U_P026_P		26 //			
#define U_P027_SetAddrRelation	27 //������ַ
#define U_P028_QrAddrRelation	28 // ������ַ	
#define U_P029_P				29 //

#define U_P030_SetUnitRegi		30 //��Ԫ����	
#define U_P031_P		31 //
#define U_P032_P		32 //
#define U_P033_P		33 //
#define U_P034_P		34 //
#define U_P035_P		35 //
#define U_P036_P		36 //
#define U_P037_SetLanguage		37 //����		
#define U_P038_SetModeFieldDebug	38 //�ֳ�����ģʽ
#define U_P039_QrModeFieldDebug 	39 //�ֳ�����ģʽ


#define U_P040_QrNowFault		40 //��ǰ����	
#define U_P041_QrNowDisable	41 //��ǰ����	
#define U_P042_QrLoopLinkLgc	42 //��·���������	
#define U_P043_P				43 //
#define U_P044_QrNote			44 //��ѯע��	
#define U_P045_P		45 //
#define U_P046_P		46 //

#define U_P047_QrSoftVer		47 //����汾	
#define U_P048_QrUnitRegi		48 //��Ԫ����	
#define U_P049_QrMachNet		49 //����	
#define U_P050_P				50 //
#define U_P051_P				51 //
#define U_P052_QrHistAll		52 //��ʷ-ȫ��	
#define U_P053_QrHistAlarm		53 //��ʷ-	
#define U_P054_QrHistLink		54 //��ʷ-
#define U_P055_QrHistFault		55 //��ʷ-	
#define U_P056_QrHistOpea		56 //��ʷ-	
#define U_P057_QrHistOthers		57 //��ʷ-		
#define U_P058_QrFieldRegist	58 //��ѯ �Ǽ�
#define U_P059_QrAutoManu		59 //��ѯ �ֶ� �Զ�

#define U_P060_TsLoopDevScan	60 //��·���	
#define U_P061_TsDeteCurve		61 //ģ������	
#define U_P062_TsLoopData		62 //��·������ѯ	
#define U_P063_TsDeteType		63 //�ֳ���������	
#define U_P064_TsDeteData		64 //�ֳ���������	
#define U_P065_TsCSoundAndLed	65 //�����Լ�	
#define U_P066_P			66 //
#define U_P067_TsCKey			67 //�������	
#define U_P068_TsAllHardware	68 //���� ����Ӳ��
#define U_P069_P			69 //
#define U_P070_P			70 //	
#define U_P071_P			71 //
#define U_P072_TsCommUnit		72 //��ʾ��ԪͨѶ���	
#define U_P073_TsCommMach		73 //��ʾ����ͨѶ���		
#define U_P074_P				74 //		
#define U_P075_P				75 //		
#define U_P076_P				76 //

#define U_P077_ClrLinkLogic	77 //���	
#define U_P078_ClrNote			78 //	
#define U_P079_P	79 //	
#define U_P080_ClrLoopRegi		80 //	
#define U_P081_ClrAddrRelation	81 //������ַ		
#define U_P082_P				82 //
	
#define U_P083_Pssw1_Change			83 //�������	
#define U_P084_Pssw2_Change			84 //	
#define U_P085_P		85 //	
#define U_P086_P			86 //	
							
#define U_PXXX			87	//		
//��ֹ�պţ���ֹ�غš����밴˳���š�
			
/*=================  ================================================*/
#define MAX_PAGE        100	 

#define U_PageNum_Default			0	//

/******************************************************************************
// END :
******************************************************************************/
#endif // __lcdCst_PageNum_H__

