#ifndef __ProjectStruct_H__
#define __ProjectStruct_H__
/******************************************************************************
* @file    ProjectStruct.h
* @author  yx
* @brief   ���̵��ļ��нṹ˵��
******************************************************************************/

/*================= 2013.6.29 ================================================*/
	KEIL�����Ĺ��̣�����TKStudio��.h�ļ��Ϳ����Ҽ����ˣ�
���ܲ�ͬ�ļ��е����ơ�
	TKStudio����keil����ʱ��ѡ��ARM��ʵ��ѡ��CPU�ͺŶ��������
�´δ�ʱ�Ͳ�����ʾ����ѡ��CPU�ͺš�

/*=================  ================================================*/
�����ļ���
<bufCan>�ļ������� ICAN ECANʹ���ĸ� hdCan
flash�ж�״̬�ĳ�ʼ���� Init_SaveTask() �

/*================= 2013.6.29 ================================================*/
Ӧ�ó���ֻ�����á�Periph����
Ӳ�������������"HdInterface.h" "hw00_HdInt.h"���롣
����"THdPinItem_st"�ṹ�壬�����ҳ����е����Ŷ��塣

��s16_CanBufLib�� CAN�����ݺ��ļ��洢buf������

��s18_PeriphSave��flash���ݵĴ洢��������š�

��s70_Periph���ǿ��������Ĵ���
		"HdInterface.h" ����������ģ��������档
��s81_HardWareEx����CPU��Χ������������
		ֻ������á�s80_HardWareCpu����CpuDriver������
��s80_HardWareCpu����CPU�йص�������
		ֻ������� ��s86_driver����
		"hw00_CallBack.h" �ǻص���������Щ�ж���Ҫ�Ľӿ�,��Periph���ã�
		"hw00_HdInt.h" Ӧ�ó�������жϣ���CPU���롣
��s86_driver��ARM�������� CPU�ڵ�ex��������


.\s01_Inc;.\s01_incAssemble;.\s02_Task;.\s03_Common;.\s09_Board;.\s09_Struct;.\s10_EventBuf;.\s11_canProtocal;.\s15_CanManage;.\s16_CanBufLib;.\s17_SimCanBuf;.\s20_LcdPage;.\s21_LcdSub;.\s22_LcdConst;.\s70_Periph;.\s71_PhInterface;.\s80_HardWareCpu;.\s81_HardWareEx;.\s82_HardWareLcd;.\s85_cpuDef;.\s86_driver;


.\X;.\X;.\X;.\X;.\X;.\X;.\X;.\X;.\X;.\X;.\X;

/******************************************************************************
// Use Lib:
��Extinguish_V0.0.0.1__0.1.20��
"Lpc177xDriverLib_V1.0_2.lib"  CPU����
"DriverTmrTick_V0.0.0.1_0.1.2.rar"
"DriverOpeaMenu_V0.0.0.1_0.0.8.rar"
"DriverLcd19264_V0.0.0.1_6.rar"
"DriverKeyBuf_V0.0.0.1_0.0.5.rar"
"DriverFlsSave_V0.0.0.1_0.1.8.rar"
"DriverEventBuf_V0.0.0.1_1.4.rar"
"DriverEventAndWinBuf_V0.0.0.1_1.1.rar"
"DriverCanBuf_V0.0.0.1_0.0.6.rar"



��Extinguish_V0.0.0.1__0.0.19��
"Lpc177xDriverLib_V1.0_2.lib"  CPU����
"TmrTick_Driver_V1.1.lib" 			in <s03_Common>        ��ʱ; ������ͬ����.c�ļ���
"EventBuf_Driver_V0.0.0.1_0.1.0.lib"	in <s10_EventBuf> 	   �¼�����
	"EventAndWinBuf_Driver_V0.0.0.1_0.0.5.lib"
"CanBuf_Driver_V0.0.0.1_0.0.4.lib"		in <s16_CanBufLib>      CAN����֡���ļ��洢
"OpeaMenu_Driver_V0.0.0.1_0.0.3.lib"    in <s29_LcdOpeaMenuLib>  �˵�
"DriverFlsSave_V0.0.0.1_0.1.4.lib"      in <s78_phSaveLib>       Flash�洢
"KeyBuf_Driver_V0.0.0.1_0.0.3.lib"      in <s70_Periph>          ��������

******************************************************************************/


/******************************************************************************
* FUNC: //END
******************************************************************************/
#endif // __ProjectStruct_H__

