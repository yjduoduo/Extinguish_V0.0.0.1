#ifndef __Version_H__
#define __Version_H__
/******************************************************************************
* @file    Version.h
* @author  yx
* @brief   �汾��¼
TmrTick_Driver_V1.1.lib
******************************************************************************/

/******************************************************************************
// �汾��¼��
LoadSoundFuncToHd  δ���
******************************************************************************/

/*=============================================================================



01.��Extinguish_V0.0.0.1__0.1.28��2013.11.02 15:17  Compiled
		����: ��ʷ��¼�ĵ�ַ�Ķ������
		add: bCheckSaveItemConstDef();
01.��Extinguish_V0.0.0.1__0.1.27��2013.11.02 14:20  Compiled
	�Ĵ����� ��Lcd_Driver_V0.0.0.1_10_Cn12En6Asc6.lib��
01.��Extinguish_V0.0.0.1__0.1.26��2013.11.02 12:12  Compiled
	����wxj��LCD V1.2.1.JFB_wxj_time2013��10��22�ա���ҳ�档
01.��Extinguish_V0.0.0.1__0.1.25��2013.10.31 10:24  Compiled
	��reset���ơ� iCan unit inLine ����
01.��Extinguish_V0.0.0.1__0.1.24��2013.10.31 09:47  Compiled
	��Ӳ�����Խ��棬�ܹ���ʱ�շ���iCan��eCan�� ������ԭ�򣬷�eCan��Ϣ�״β����������жϣ���֡�
	��С�����Ļ�·�����յ����������������� ��LCD����ʾ��
01.��Extinguish_V0.0.0.1__0.1.23��2013.10.31 10:47  Compiled
	flsSave.lib �ļ� δ���ԣ���wxj���ԡ�
	��s78_30_SaveSim��������ļ�"sim_saveItem.c"����в��ԡ�
01.��Extinguish_V0.0.0.1__0.1.22��2013.10.29 21:39  Compiled
	�� flsSave.lib �ļ���ӽ�����׼�����ԡ�
01.��Extinguish_V0.0.0.1__0.1.21��2013.10.24 16:31  Compiled
	��Ϊ "strDevice.h" "sysDef.h"U_PANEL_TOTAL_SEQU_MAX�䣬
		�����汾��DriverEventBuf_V0.0.0.1_1.6����DriverFlsSave_V0.0.0.1_0.1.8��
01.��Extinguish_V0.0.0.1__0.1.21��2013.10.24 14:17  Compiled
	flsItem ����U_FlsSave_MachAlarmNote; 
		TFlsRelatAddr_st; TFlsExtgZoneConfig_st;  TFlsLoopAddrRegist_st; �洢δ����
	���� panel.c �� U_PANEL_TOTAL_SEQU_MAX 128->250.
	���11SЭ�飬no test;
	add:  "OpeaAndEvtState"  ������ ״̬
	��ʹ�а������������ȼ����ߵ��¼�ʱ��Ҳ�л�ҳ���ˣ���֪Ϊʲô�� bNewEvtIsHigherThanNow() MCycle->bEvent
	�ڲ鿴all event totalʱ����ϣ�������¼���ϡ�
01.��Extinguish_V0.0.0.1__0.1.20��2013.10.17 14:43   Compiled
	��ʾ�¼� ������ 88�ַ��ֿ⡣
	use : ExecTmrArrivedLcdShow();
01.��Extinguish_V0.0.0.1__0.1.19��2013.10.16 21:39   Compiled
	�¼�ҳ��һ�� �ж��� �Ķ��� cstEvtWindowDef[]
	�¼�ҳ�����л��� 
	�¼�����ʾ����������������2��ʱδ��ʾ��  ���ڶ�ʱ���¼���
01.��Extinguish_V0.0.0.1__0.1.18��2013.10.15 12:03   Compiled
	sim  �¼�ҳ��һ�� ֻһ�� �Ķ��塣 cstEvtWindowDef[]
01.��Extinguish_V0.0.0.1__0.1.17��2013.10.14 22:11   Compiled
	sim_EvtBuf.c  V1.1 mSimCls = U_EvtCls_Link;  U_OneScr_DevBuf_MAX = 1;
	evtBuf code in project.
01.��Extinguish_V0.0.0.1__0.1.16��2013.10.14 15:43   Compiled
	���� evtBuf. ��� "EventAndWinBuf" 
	sim_EvtBuf.c  V1.0  mSimCls = U_EvtCls_Link;  U_OneScr_DevBuf_MAX = 3;
01.��Extinguish_V0.0.0.1__0.1.15��2013.10.11 22:08   Compiled
	�����ļ�����š�
01.��Extinguish_V0.0.0.1__0.1.14��2013.10.11 22:08   Compiled
	can �ļ����շ� �Ѳ��ԡ�
	�й�Э��Ĳ��֣����� lib, ת�Ƶ� can11sFile.c. �й�evtFile�Ĳ���Ϊϸ��ժ����
		��CanID��Ϊ��THdCanFrame_st�����ˣ�����Ҳ������lib�
	use CanBuf_Driver_V0.0.0.1_0.0.6.lib
01.��Extinguish_V0.0.0.1__0.1.13��2013.10.11 00:01   Compiled
	�ļ����͡� �ļ�����δ���ԡ�
01.��Extinguish_V0.0.0.1__0.1.12��2013.10.10 20:58   Compiled
	�����ļ� "can11sFile.c"  "can_DataOrFile.c"
	��ʾ��ִ��ʱ�䳤������ΪLCD�����ſ��� ��Ҫ��ʱ10us��������ʾ��������
01.��Extinguish_V0.0.0.1__0.1.11��2013.10.09 08:37   Compiled
	��ʾ"00001"��Լ����Ҫ20ms, ����̫���ˡ�
	����Ӳ��ҳ��  U_P068_TsAllHardware ���á� 2013.10.08
	��Lcd_Driver_V0.0.0.1_2.lib��		2013.10.08
01.��Extinguish_V0.0.0.1__0.1.10��2013.9.30 11:05   Compiled
	�����˵� �� ҳ�档����Ӧ������
	�������빦�� δ���ԡ�
	ҳ�沿�� ���� Wei.
01.��Extinguish_V0.0.0.1__0.1.9��2013.9.29 12:22   Compiled
	���Բ˵���OK.
01.��Extinguish_V0.0.0.1__0.1.8��2013.9.27 14:01   Compiled
	"lcdSub_ModeTextFig" �� �����Ӻ��� ����pix. 
01.��Extinguish_V0.0.0.1__0.1.7��2013.9.26 23:46   Compiled
	��12*12 �����д���δ����
01.��Extinguish_V0.0.0.1__0.1.6��2013.9.26 19:36   Compiled
	12*12 ���� ���� �� 12*8�ַ� ����ʾ�� �����ڵ����������⡣
	�� CAN bps ; ����5us=watcher iCan 100K bps.
	����δ�漰 ͨѶ �洢���߼���
01.��Extinguish_V0.0.0.1__0.1.5��2013.9.26 16:26   Compiled
	����
	Һ����ʾ����4����ʾ����ȫ����������Ӳ��������������������ˡ�
	���Ź���OK, ���ַ���ʾ������ʱstop.
	ʵʱʱ�ӡ������ʱ��
	iCan�շ��� eCan�շ�����ʾ����֡������ 3s��һ֡�� ����: iCan��eCan���ӣ�
	�����շ�����ʾ���ֽڼ����� 3s��2�ֽڣ� ����:2��3�����ӣ�
	flash ������д��������ȷ��ʾ" V ", ������ʾ" X ".
	����: ���°�������ʾ��
	��Դ״̬����ߣ�3����0���� 1���ϣ�
	��Դ��⿪�أ�AD����ֵ����� AD���ϵĵ�ѹ��

	������ ���� δ���ԣ�
	��ʾ12*12�����ֿ�δ���ԣ�

01.��Extinguish_V0.0.0.1__0.1.4��2013.9.26 14:31   Compiled
	������ʾ��
	uart0 �շ������� δ�� hw11_Uart�� ���� CUart.
	8*8 ������
01.��Extinguish_V0.0.0.1__0.1.3��2013.9.26 00:28   Compiled
	������ʾ���ַ� ���� 8*8 .
01.��Extinguish_V0.0.0.1__0.1.2��2013.9.25 23:56   Compiled
	��⿪�� AD;
	��Դ״̬��
	watchDog ����ʱ�� OK.
	�� 8*8 �����ַ� ����ʾ������
01.��Extinguish_V0.0.0.1__0.1.1��2013.9.25 16:36 
	Һ����ʾ: ʱ�ӣ�����ʱ������
			CAN���մ���( iCan �� eCan ����);
			������
			Flsд����� 
	chip1 �� NorFlash ���ԣ���дʧ�ܣ�
	������ δ����
	����δ����
	USB δ����
01.��Extinguish_V0.0.0.1__0.1.0��2013.9.24 
	��ʼ����; 
	LCD��ʾ 2013.9.24 21:00 
		��ʾ (0,0)(0,1)�� when  U_ShowCharHeight_IsOneRowPage = 1  
		��ʾ (0,0)(0,1)�� when  U_ShowCharHeight_IsOneRowPage = 0 
		12*12 ���ֿ� ��֧�֡�
	CAN ͨѶ�� iCan �� eCan ͨѶ�ɹ����� �ա��� �жϣ� 
		bps δ���ԡ�
	Flash: chip=0 erase,write,read OK; 
		chip=1 failed;
	ʵʱʱ�ӣ�ż��������3s�����¡� ��24V�������ݿ��Ա��ֵ�ѹ����֪��ά�ֶ�á�


01.��Extinguish_V0.0.0.1__0.0.23��2013.9.23 21:50  Compiled
	eventBuf ���� insert;
	flsSave.lib ���޸�;
01.��Extinguish_V0.0.0.1__0.0.22��2013.9.22 22:16  Compiled
	��·��� ����
	��DriverFlsSave_V0.0.0.1_0.1.5.lib��
	lcd������show text��fig, ���� color��para.
01.��Extinguish_V0.0.0.1__0.0.21��2013.9.16 09:10  Compiled
	���ְ�������
	��ʾ���� ��Ҫ����ɫ�ͱ���ɫ��Ϊ�˹��Ĵ���
	swFig.c δ����
01.��Extinguish_V0.0.0.1__0.0.20��2013.9.11 00:54  Compiled
	MCycle ҳ�� ���ȡ�"lcdPg_aSchedu"  "lcdPg_MainOrEvt"
01.��Extinguish_V0.0.0.1__0.0.19��2013.9.10 16:45  Compiled
	"DriverEventBuf_V0.0.0.1_0.1.0"
01.��Extinguish_V0.0.0.1__0.0.18��2013.9.10
	��EventAndWinBuf_Driver_V0.0.0.1_0.0.3.lib��
01.��Extinguish_V0.0.0.1__0.0.17��2013.9.9  23:54 Compiled
	��  EventBuf.lib
01.��Extinguish_V0.0.0.1__0.0.16��2013.9.9  19:59 Compiled
	�� canManage 
01.��Extinguish_V0.0.0.1__0.0.15��2013.9.4  17:57 Compiled
	��menu;
	use "OpeaMenu_Driver_V0.0.0.1_0.0.1.lib"
	"lcdCst_OpaMenuInterface" �ӿ�δ��ɡ�
01.��Extinguish_V0.0.0.1__0.0.14��2013.9.4  12:09 Compiled
	use: .\s78_phSaveLib\DriverFlsSave_V0.0.0.1_0.1.3.lib
01.��Extinguish_V0.0.0.1__0.0.13��2013.8.28 13:51 Compiled
	add: lcdSub_Pssw.c
	use: .\s70_Periph\KeyBuf_Driver_V0.0.0.1_0.0.3.lib
01.��Extinguish_V0.0.0.1__0.0.12��2013.8.27 17:14 Compiled
	led �� keyɨ�� Ӳ���棬��ȷ��
	Key scan ��δ���ó�OD.
01.��Extinguish_V0.0.0.1__0.0.11��2013.8.27 11:00 Compiled
	�����жϺ�����
	sys_Init();
	������ ������
01.��Extinguish_V0.0.0.1__0.0.10��2013.8.26 16:41 Compiled
	add Uart;
	add NorFlash SST39VF800A ������ ��ȱ ������ ������
01.��Extinguish_V0.0.0.1__0.0.9��
	�� keyBufDriver��  �ӵ�Դ��⡣
	δ��: �洢��uart;
01.��Extinguish_V0.0.0.1__0.0.8��
	׼����keyScan �� keyBuf �ֿ�
01.��Extinguish_V0.0.0.1__0.0.7��2013.8.16 16:16
	��can driver.  error�ж���Ҫʵ�⡣
01.��Extinguish_V0.0.0.1__0.0.6��2013.8.15 16:47 Compiled
	�� led, key.  Sound��PWMδ�����
01.��Extinguish_V0.0.0.1__0.0.5��2013.8.15 16:47
	�� timer�� 
01.��Extinguish_V0.0.0.1__0.0.4��2013.8.13 20:35
	���� showBuf.
	pcf8563�ģ�IIC;  phClock.
=============================================================================*/

/******************************************************************************
// Use Lib:  in "ProjectStruct.h"

******************************************************************************/


/******************************************************************************
// ��¼��
******************************************************************************/
/*=============================================================================

=============================================================================*/


/******************************************************************************
* FUNC: //END
******************************************************************************/
#endif // __Version_H__
