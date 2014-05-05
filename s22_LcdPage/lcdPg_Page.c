
#define __lcdPg_Page_C__
/******************************************************************************
* @file    lcdPg_Page.c
* @author  yx
* @version V1.0
* @date    2012-01-05
* @brief   ���е�ҳ�溯��. ̫�࣬�ɿ��ǰ�����ļ���
* 
*  ÿ��ҳ��� First() ,�Լ������Ƿ��� LcdSw_ClrFullWindow(U_COLOR_BackGroundDefault);
*  ���еı��������Ĭ��enter�����档�����˱���ȷ�ϵ���ʾ�������еı��涼Ӧ����ʾ��
*  �����������ҳ�棬�˳�ǰ��һ������ FigInput_Stop();
*  
*  P016 �Զ��Ǽǣ� P058 ��ѯ�Ǽǵ�ַ��
*  P060  ��·���  
******************************************************************************/
#include  "lcdPg_Page.h"


#include "lcdSub_ModeTextFig.h"
#include "keyBufJdgLib_incOut.h"
//#define __lcdShowTask_C__
#include "lcdShowTask.h"
//#define __lcdSub_InputFig_C__
#include "lcdSub_InputFig.h"
#include "tmrTick.h"


#include "lcdPg_InitT.h"
//#include "..\\s00Prj\\incFile.h"	

//-----------------   --------------------------------// 
#include  "tsk_lcd_incIn.h"

#include  "phIoKeyScan.h"
	// if(bGetPageKey(&vThisPageKey)) 
	// {
		// if(vThisPageKey == emKey )
		// {}
	// }

#include "posText.h"

#include  "opeaMenuLib_incOut.h"

#include  "LcdLib_incOut.h" // LCD��ʾ���� �Ѳ���

#include  "lcdSub_ModeTextFig.h" // ��ʾ �ַ������� �Ѳ���
#include  "lcdSub_InputFig.h" // ҳ�����������ֹ���. �д��룬δ���ԣ�

#include  "lcdPg_Common.h"  // 2��������ҳ������õ����Ӻ���
#include  "lcdPg_pSelfHdChk.h"

//----- Me:
#include  "canPrtl_iTx.h"  // CAN Э��

/*================= ���� ============================================*/

/*================= �ṹ���� ========================================*/

/*================= ˽�нṹ�������� ================================*/

/*================= ���к������� ====================================*/

/*================= ˽�к������� ====================================*/

/*=================  ================================================*/
		
/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

/******************************************************************************
* ҳ��: //
* ������������
* �ֶ�: �Զ���
* ����ʱ�ӣ�
******************************************************************************/
void P000_MAIN_Back(void)	//
{
	
}

void P000_MAIN_First(void)
{

	LcdSw_ClrFullWindow(U_COLOR_BackGroundDefault);
	
	ShowCstCharRL(3, 9, &cstChar_RunUsual);
	ShowCstCharRL(1, 6, &cstChar_ExtgMachineIni);
	
	ShowStr_AutoManuNowState(6, 4);
	
}


void P000_MAIN_Usua(void)
{
	Show_Clock(8, 13);
	ShowStr_AutoManuChangeState(6, 4);
}

/******************************************************************************
* ҳ��: // �𾯽���
* 
******************************************************************************/
void P001_FireAlarm_Back(void)	//
{
	LcdPageEvt_PageBack();
}
void P001_FireAlarm_First(void)
{
	LcdPageEvt_PageFirst();
}
void P001_FireAlarm_Usua(void)
{
	LcdPageEvt_PageUsual();
}
/******************************************************************************
* ҳ��: //����¼�
* 
******************************************************************************/
void P002_Monitor_Back(void)	//
{
	LcdPageEvt_PageBack();
}
void P002_Monitor_First(void)
{
	LcdPageEvt_PageFirst();
}
void P002_Monitor_Usua(void)
{
	LcdPageEvt_PageUsual();
}
/******************************************************************************
* ҳ��: //�����¼�
* 
******************************************************************************/
void P003_Disable_Back(void)	//
{
	LcdPageEvt_PageBack();
}
void P003_Disable_First(void)
{
	LcdPageEvt_PageFirst();
}
void P003_Disable_Usua(void)
{
	LcdPageEvt_PageUsual();
}
/******************************************************************************
* ҳ��: //�����¼�
* 
******************************************************************************/
void P004_Fault_Back(void)	//
{
	LcdPageEvt_PageBack();
}
void P004_Fault_First(void)
{
	LcdPageEvt_PageFirst();
}
void P004_Fault_Usua(void)
{
	LcdPageEvt_PageUsual();
}


/******************************************************************************
* ҳ��: //�����¼�
* 
******************************************************************************/
void P005_Link_Back(void)	//
{
	LcdPageEvt_PageBack();
}
void P005_Link_First(void)
{
	LcdPageEvt_PageFirst();
}
void P005_Link_Usua(void)
{
	LcdPageEvt_PageUsual();
}
/******************************************************************************
* ҳ��: //�����¼�
* 
******************************************************************************/
void P006_Extg_Back(void)	//
{
	LcdPageEvt_PageBack();
}
void P006_Extg_First(void)
{
	LcdPageEvt_PageFirst();
}
void P006_Extg_Usua(void)
{
	LcdPageEvt_PageUsual();
}

/******************************************************************************
* ҳ��: //
* ����ģʽ���ֶ��Զ����¼�������
******************************************************************************/
void P007_Status_Back(void)	//
{
	
}

void P007_Status_First(void)
{
	LcdSw_ClrFullWindow(U_COLOR_BackGroundDefault);
	ShowCstCharRL(0, 0, &cstChar_StatusColon);
	
	LcdPageEvtTotal_First();
	
	ShowStr_AutoManuNowState(3*2, 0);
	
}

void P007_Status_Usua(void)
{
U8 mEvtCls;
U8 mKey;
	
	for(mEvtCls=0; mEvtCls<U_EvtCls_MAX; mEvtCls++)
	{
		if(bEvtBuf_TotalChange_andClr(mEvtCls))
		{
			LcdPageEvtTotal_Refresh(mEvtCls);
		}
	}
	
	Show_Clock(8, 13);
	ShowStr_AutoManuChangeState(3*2, 0);
	
	
	if(bGetPageKey(&mKey))
	{
		LcdPageEvt_Key_Fig(mKey);
		return;
	}
}

/******************************************************************************
* ҳ��: //�˵�
* 
******************************************************************************/
void P008_MENU_Back(void)	//
{
	ClrMenuAllBufAndSign();
}
void P008_MENU_First(void)
{
	
	//MenuEntry();
}

void P008_MENU_Usua(void)
{
	if(!bGetPageKey(&vThisPageKey))
	{
		return;
	}
	
	if(vThisPageKey < U_KEY_Fig_Max)
	{
		if(vThisPageKey != 0)
		{
			vThisPageKey--;
		}
		MenuFigEnter(vThisPageKey);
		return;
	}
	
	switch(vThisPageKey)
	{
		case U_KEY_Up:
			MenuUp();
			break;
		case U_KEY_Down:
			MenuDown();
			break;
		case U_KEY_Left:
			MenuReturn();
			break;
		case U_KEY_Right:
		case U_KEY_Enter:
			MenuEnter();
			break;
		default:
			break;
	}
	
	
	
}
/******************************************************************************
* ҳ��: //��������
* 
******************************************************************************/
void P009_UserLogin_Back(void)	//
{
	
}
void P009_UserLogin_First(void)
{
	
}
void P009_UserLogin_Usua(void)
{
	
}
/******************************************************************************
* ҳ��: //�ֶ�����ģ�顣 
* ��ַ��Χ ��
	U_SYS_LOOP_MAX 	��·MAX,0��Ч��
	U_1LOOP_DETE_MAX 	ÿ��·��ַ��Χ��0��Ч��


*      _��·_ _��ַ
*       key:����  key:ֹͣ
*   ��ʾ:��ǰ�ĵ�ַ ������ֹͣ״̬

* �ο� "lcdSub_InputFig.h"
******************************************************************************/

void P010_ManuActModu_Back(void)	//
{
    UNINITENTRY(p010);
}


void P010_ManuActModu_First(void)
{
    INITENTRY(p010);


}

//�ֶ�����ҳ�� ��������
//	BOOL pg_keyDeal();
void P010_ManuActModu_Usua(void)
{
U8 ii;
    KEYCALL(p010);
	
	ii = pgcom_callb.inputFig[0];
	ii = ii;
}


/******************************************************************************
* ҳ��: // ����
* ��ʱ ��ʾ����������
******************************************************************************/
void P011_Help_Back(void)	//
{
    UNINITENTRY(p011);
}
void P011_Help_First(void)
{
    INITENTRY(p011);
   // ShowXYCodeCharRL(1,6,0,"����",FALSE);
}
void P011_Help_Usua(void)
{
    KEYCALL(p011);
}
/******************************************************************************
* ҳ��: // �˹�����ȥ������ʱ����
*
******************************************************************************/
void P012_ManuAuto_Back(void)	//
{

}
void P012_ManuAuto_First(void)
{

}
void P012_ManuAuto_Usua(void)
{

}


/******************************************************************************
* ҳ��: // �������ڡ�ʱ��
* 	key:��������
* ��ʾ��ǰ ���ڡ�ʱ�ӣ�
*  20_ _ ��_ _ �� _ _ ��
*    _ _ ʱ_ _ �� _ _ ��
*   key:��ǰʱ�� ��λ������
******************************************************************************/
void P013_SetClock_Back(void)	//
{
    UNINITENTRY(p013);
}
void P013_SetClock_First(void)
{
    INITENTRY(p013);
}
void P013_SetClock_Usua(void)
{
    KEYCALL(p013);
}

void P013_SetClock_Save(void)
{
    // BOOL SetClock(TEvtClock_st *pClock); // ����ʱ��
}


// BOOL GetClock(TEvtClock_st  *pClock); // ��ȡӲ��ʱ��

	// ��ʾʱ�ӣ��Ѷ�ʱ��ȡʱ�Ӳ��жϣ�����second�仯���� U_SysSta_bClockChanged ��
// TEvtClock_st *pClock;
	// if(GetSysState(U_SysSta_bClockChanged))
	// {
		// ClrSysState(U_SysSta_bClockChanged);
		
		// GetRamTimer(&pClock);
		// ��ʾ����
	// }



/******************************************************************************
* ҳ��: // 
******************************************************************************/
void P014_MiniEvent_Back(void)
{
	LcdPageEvt_MiniBack();
}
void P014_MiniEvent_First(void)
{
	LcdPageEvt_MiniFirst();
}
void P014_MiniEvent_Usua(void)
{
	LcdPageEvt_MiniUsual();
}


/******************************************************************************
* ҳ��: // �ָ�Ĭ������
* 	�ָ�Ĭ�����ã�
*	  key:��   key:�˳�
*	
******************************************************************************/
void P015_SetDefault_Back(void)	//
{
    UNINITENTRY(p015);
}
void P015_SetDefault_First(void)
{
    INITENTRY(p015);
//    ShowXYCodeCharRL(1,6,0,"�ָ�Ĭ������",FALSE);
}
void P015_SetDefault_Usua(void)
{
    KEYCALL(p015);
}
/******************************************************************************
* ҳ��: // �Զ��Ǽ�
* 	���ڵǼǣ��ѽ��� �ٷֱ�
*		key:ֹͣ�Ǽ�
******************************************************************************/
void P016_AutoRegist_Back(void)	//
{
    UNINITENTRY(p016);
}
void P016_AutoRegist_First(void)
{

    INITENTRY(p016);
	
	ICan_Tx_RegistAll(); // �Զ��Ǽ�

}
void P016_AutoRegist_Usua(void)
{

}

void P016_AutoRegist_ShowPercent(U8 mPercent)
{

}


/******************************************************************************
* ҳ��: // �ֶ��Ǽ�  �ο�P010
*      _��·_ _��ַ	  _����
*   ��ʾ: �������Ͷ��壬��ʱ��ʾ �ֱ�,���̣����£����ϣ�����˨����������룬���⡣
*       key:�Ǽ�  key:ȡ��
*   ��ʾ:��ǰ�ĵ�ַ �Ǽ�״̬
* 



#define  cNdTy_Hand       1	     //�ֱ�
#define  cNdTy_Hydrant    2	     //����˨��ť
#define  cNdTy_1Out       3	     //��ģ�����
#define  cNdTy_Heat       4	     //���Ӹ���
#define  cNdTy_Inter      5	     //��ʽ�ӿ�	
#define  cNdTy_2Out       6		 //˫������
#define  cNdTy_In_Out     7		 //˫�ر���
#define  cNdTy_Omnis      8		 //���¸���
#define  cNdTy_Input      9		 //����ģ�� 
#define  cNdTy_Display    0x0a	 //����
#define  cNdTy_Smoke      0x0b	 //����
#define  cNdTy_SL         0x0C	 //����
#define  cNdTy_DetInter   0x0d	 //�м�ģ��
#define  cNdTy_4Out       0x0E	 //�Ŀ�����
#define  cNdTy_OnOff      0x0F	 //����
//#include  "CNodeTypeDef.h"
******************************************************************************/
void P017_ManuRegist_Back(void)	//
{
    UNINITENTRY(p017);
}
void P017_ManuRegist_First(void)
{
    INITENTRY(p017);
}
void P017_ManuRegist_Usua(void)
{
    KEYCALL(p017);

}
/******************************************************************************
* ҳ��: // �ֶ����ε�ַ �ο�P010
*      _��·_ _��ַ
*       key:����  key:ȡ��
*   ��ʾ:��ǰ�ĵ�ַ ����״̬
*
******************************************************************************/
void P018_SetDisable_Back(void)	//
{
    UNINITENTRY(p018);
}
void P018_SetDisable_First(void)
{
    INITENTRY(p018);
}
void P018_SetDisable_Usua(void)
{
    KEYCALL(p018);

}
/******************************************************************************
* ҳ��: // �ֶ�ע��
*      _��·_ _��ַ
* 	ע������: ע��������ʱ�Ӻ���
*
******************************************************************************/
void P019_SetNote_Back(void)	//
{
    UNINITENTRY(p019);
}
void P019_SetNote_First(void)
{
    INITENTRY(p019);
}
void P019_SetNote_Usua(void)
{
    KEYCALL(p019);
}
/******************************************************************************
* ҳ��: // �����������
*      _��·_ _��ַ
* 	����:  ��ʱ�Ӻ���
*
******************************************************************************/
void P020_SetLinkLogic_Back(void)	//
{
    UNINITENTRY(p020);
}
void P020_SetLinkLogic_First(void)
{
    INITENTRY(p020);
}
void P020_SetLinkLogic_Usua(void)
{
    KEYCALL(p020);
}



/******************************************************************************
* ҳ��: //��������������
* 	������ַ: _ _ 
*	������ַ: _ _ 
******************************************************************************/
void P024_SetMachNet_Back(void)	//
{
    UNINITENTRY(p024);
}
void P024_SetMachNet_First(void)
{
    INITENTRY(p024);
}
void P024_SetMachNet_Usua(void)
{
    KEYCALL(p024);
}

/******************************************************************************
* ҳ��: //���ñ���������ַ
* 	_ _��_ _��·_ _ _��ַ ~ _ _ _��ַ
*	key: ���  key:ɾ��  key:�鿴���й���
* �鿴���й������� P028_QrAddrRelation ����һ�����棬�����û�Ȩ�޲�ͬ��
* ���Թ����Ӻ�����
******************************************************************************/
void P027_SetAddrRelation_Back(void)	//
{
    UNINITENTRY(p027);
}
void P027_SetAddrRelation_First(void)
{
    INITENTRY(p027);
}
void P027_SetAddrRelation_Usua(void)
{
    KEYCALL(p027);
}

/******************************************************************************
* ҳ��: // ��ѯ������ַ
*
******************************************************************************/
void P028_QrAddrRelation_Back(void)	//
{
    UNINITENTRY(p028);
}
void P028_QrAddrRelation_First(void)
{
    INITENTRY(p028);
//    ShowXYCodeCharRL(1,3,0,"��ѯ������ַ",FALSE);
}
void P028_QrAddrRelation_Usua(void)
{
    KEYCALL(p028);
}


/******************************************************************************
* ҳ��: // ��������
* 	��ʱ����
******************************************************************************/


void P037_SetLanguage_Back(void)	//
{
    UNINITENTRY(p037);
}
void P037_SetLanguage_First(void)
{
    INITENTRY(p037);
}
void P037_SetLanguage_Usua(void)
{
    KEYCALL(p037);
}
/******************************************************************************
* ҳ��: // ���� �ֳ�����ģʽ
* 	key:����ģʽ key:��������
*	��ʾ: ��ǰģʽ״̬
******************************************************************************/
void P038_SetModeFieldDebug_Back(void)	//
{
    UNINITENTRY(p038);
}
void P038_SetModeFieldDebug_First(void)
{
    INITENTRY(p038);
}
void P038_SetModeFieldDebug_Usua(void)
{
    KEYCALL(p038);
}
/******************************************************************************
* ҳ��: // ��ѯ �Ƿ��ֳ�����ģʽ
*
******************************************************************************/
void P039_QrModeFieldDebug_Back(void)	//
{
    UNINITENTRY(p039);

}
void P039_QrModeFieldDebug_First(void)
{
    INITENTRY(p039);

}
void P039_QrModeFieldDebug_Usua(void)
{
    KEYCALL(p039);

}




/******************************************************************************
* ҳ��: // ���������
* 			1     2    3   4 
*״̬: ��/��   _    _    _    _
*��ʱʱ��(s)  _ _  _ _  _ _  _ _  
*    key: ��   key:�� 
******************************************************************************/
void P030_SetUnitRegi_Back(void)	//
{
    UNINITENTRY(p030);

}
void P030_SetUnitRegi_First(void)
{
    INITENTRY(p030);

}
void P030_SetUnitRegi_Usua(void)
{
    KEYCALL(p030);

}


/******************************************************************************
* ҳ��: // ��ѯ��ǰ����
* �� P004_Fault ���ơ�
******************************************************************************/
void P040_QrNowFault_Back(void)	//
{
    UNINITENTRY(p041);
}
void P040_QrNowFault_First(void)
{
    INITENTRY(p040);
}
void P040_QrNowFault_Usua(void)
{
    KEYCALL(p040);
}
/******************************************************************************
* ҳ��: //// ��ѯ��ǰ����
* �� P003_Disable ���ơ�
*
******************************************************************************/
void P041_QrNowDisable_Back(void)	//
{
    UNINITENTRY(p041);
}
void P041_QrNowDisable_First(void)
{
    INITENTRY(p041);
}
void P041_QrNowDisable_Usua(void)
{
    KEYCALL(p041);
}
/******************************************************************************
* ҳ��: // ��ѯ�������
*  ��ʱ����
******************************************************************************/
void P042_QrLoopLinkLgc_Back(void)	//
{
    UNINITENTRY(p042);
//    ClrWinBoolState(U_WIN_NeedKey_StarPound_Sta);
}

void P042_QrLoopLinkLgc_First(void)
{
    INITENTRY(p042);
//    SetWinBoolState(U_WIN_NeedKey_StarPound_Sta);
//    ShowXYCodeCharRL(1,3,0,"��ѯ�������",FALSE);

}
void P042_QrLoopLinkLgc_Usua(void)
{
    KEYCALL(p042);
}

/******************************************************************************
* ҳ��: //��ѯע��
* ��ʱ����
******************************************************************************/
void P044_QrNote_Back(void)	//
{
    UNINITENTRY(p044);
}
void P044_QrNote_First(void)
{
    INITENTRY(p044);
//    ShowXYCodeCharRL(1,3,0,"��ѯ����ע��",FALSE);
}
void P044_QrNote_Usua(void)
{
    KEYCALL(p044);
}


/******************************************************************************
* ҳ��: //��ѯ����汾
*
******************************************************************************/
void P047_QrSoftVer_Back(void)	//
{
    UNINITENTRY(p047);
}
void P047_QrSoftVer_First(void)
{
    INITENTRY(p047);
//    ShowXYCodeCharRL(1,3,0,"��ѯ����汾",FALSE);
}
void P047_QrSoftVer_Usua(void)
{
    KEYCALL(p047);
}
/******************************************************************************
* ҳ��: // ��ѯ��������� �ο� P030_SetUnitRegi
*
******************************************************************************/
void P048_QrUnitRegi_Back(void)	//
{
    UNINITENTRY(p048);
}
void P048_QrUnitRegi_First(void)
{
    INITENTRY(p048);
//    ShowXYCodeCharRL(1,3,0,"��ѯ���������",FALSE);
}
void P048_QrUnitRegi_Usua(void)
{
    KEYCALL(p048);
}
/******************************************************************************
* ҳ��: //��ѯ���������� �ο� P024_SetMachNet
*
******************************************************************************/
void P049_QrMachNet_Back(void)	//
{
    UNINITENTRY(p049);
}
void P049_QrMachNet_First(void)
{
    INITENTRY(p049);
}
void P049_QrMachNet_Usua(void)
{
    KEYCALL(p049);
}


/******************************************************************************
* ҳ��: // ��ѯ��ʷ��¼-����
* 
******************************************************************************/
void P052_QrHistAll_Back(void)	//
{
    UNINITENTRY(p052);
}
void P052_QrHistAll_First(void)
{
    INITENTRY(p052);
}
void P052_QrHistAll_Usua(void)
{
    KEYCALL(p052);
}
/******************************************************************************
* ҳ��: // ��ѯ��ʷ��¼-��
*
******************************************************************************/
void P053_QrHistAlarm_Back(void)	//
{
    UNINITENTRY(p053);
}
void P053_QrHistAlarm_First(void)
{
    INITENTRY(p053);
}
void P053_QrHistAlarm_Usua(void)
{
    KEYCALL(p053);
}
/******************************************************************************
* ҳ��: // ��ѯ��ʷ��¼-����
*
******************************************************************************/
void P054_QrHistLink_Back(void)	//
{
    UNINITENTRY(p054);
}
void P054_QrHistLink_First(void)
{
    INITENTRY(p054);
}
void P054_QrHistLink_Usua(void)
{
    KEYCALL(p054);
}
/******************************************************************************
* ҳ��: // ��ѯ��ʷ��¼-����
*
******************************************************************************/
void P055_QrHistFault_Back(void)	//
{
    UNINITENTRY(p055);
}
void P055_QrHistFault_First(void)
{
    INITENTRY(p055);
}
void P055_QrHistFault_Usua(void)
{
    KEYCALL(055);
}
/******************************************************************************
* ҳ��: // ��ѯ��ʷ��¼-����
*
******************************************************************************/
void P056_QrHistOpea_Back(void)	//
{
    UNINITENTRY(p056);
}
void P056_QrHistOpea_First(void)
{
    INITENTRY(p056);
}
void P056_QrHistOpea_Usua(void)
{
    KEYCALL(056);
}
/******************************************************************************
* ҳ��: // ��ѯ��ʷ��¼-����
*
******************************************************************************/
void P057_QrHistOthers_Back(void)	//
{
    UNINITENTRY(p057);
}
void P057_QrHistOthers_First(void)
{
    INITENTRY(p057);
}
void P057_QrHistOthers_Usua(void)
{
    KEYCALL(p057);
}

/******************************************************************************
* ҳ��: // ��ѯ �Ǽ�
* 		_ _ ��·   key: ȷ��
* ��ʾ�Ǽǵ�ַ

* 88 CFireCtrl C11S
* ��101 CWndCtrlCheck��"CCheckAddr.C"void   DisLpReg_CCheckAddr(void)
******************************************************************************/
void P058_QrFieldRegist_Back(void)	//
{
    UNINITENTRY(p058);
}
void P058_QrFieldRegist_First(void)
{
    INITENTRY(p058);
//    ShowXYCodeCharRL(1,3,0,"��ѯ���ߵǼǵ�ַ",FALSE);
}
void P058_QrFieldRegist_Usua(void)
{
    KEYCALL(p058);
}


// * ͨѶ�����ļ���ʽ�ݲ�ȷ�������:
// �ļ�����,��̽����,��������,¥������, ̽�����ַ...,�������ַ...,¥�����ַ...;
// ��������¥�ԡ�
// �ѵǼǵĵ�ַ��˳���С������С�

// ��ʾ��ʽΪ:
// ̽��012: 1~5,7,9~15;
// ����000;
// ��ַMAX: U_1LOOP_DETE_MAX
void P058_QrFieldRegist_Rx_Detector(U8 mAdrNum, U8 *pAddrS)
{
	
}
void P058_QrFieldRegist_Rx_Modu(U8 mAdrNum, U8 *pAddrS)
{
	
}
void P058_QrFieldRegist_Rx_HornStrobe(U8 mAdrNum, U8 *pAddrS)
{
	
}
void P058_QrFieldRegist_Rx_Broad(U8 mAdrNum, U8 *pAddrS)
{
	
}
void P058_QrFieldRegist_Rx_FloorPanel(U8 mAdrNum, U8 *pAddrS)
{
	
}


/******************************************************************************
* ҳ��: //��ѯ�ֶ��Զ�
* ��ʾ�ѵǼǵ������ֶ��Զ�  �ο� ShowStr_AutoManuNowState();
* һ��:
* ����:
* ����:
* ����:
******************************************************************************/
void P059_QrAutoManu_Back(void)	//
{
    UNINITENTRY(p059);
}
void P059_QrAutoManu_First(void)
{
    INITENTRY(p059);
//    ShowXYCodeCharRL(3,3,0,"��ѯ�ֶ��Զ�״̬��",FALSE);
//    ShowStr_AutoManuChangeState(6, 4);
//    ShowCstCharRL(1, 6, &cstChar_ExtgMachineIni);
//    ShowCstCharRL(3, 9, &cstChar_RunUsual);
//    ShowStr_AutoManuNowState(4, 4);
}
void P059_QrAutoManu_Usua(void)
{
    KEYCALL(p059);

}

BOOL P059_QrAutoState_OneExtgUnit(U8 mExtgUnit)
{
    return U_ALLOW;
}
BOOL P059_QrManuState_OneExtgUnit(U8 mExtgUnit)
{
    return U_ALLOW;
}


// extern BOOL bExtgUnit_Regist(U8 mExtgUnit);
// extern BOOL bExtgUnit_Inline(U8 mExtgUnit);
void P059_QrAutoManu_show(void)
{
    U8 mExtgUnit;
    for(mExtgUnit=0; mExtgUnit<GetExtgUnitMax(); mExtgUnit++)
    {

    }
}


/******************************************************************************
* ҳ��: // ��·���  P060_TsLoopDevScan_
* ����;
*  _ ��·:
* |_________________________> 32   
* |_________________________> 64
* ����ַ��λ�ߣ���ַÿ8���������ں�������4����������ʾ��ÿ4�ı�����2���ء�

��64��ַ����2�У�
���ÿ��ַռ 192 / 32 = 6 pix. ��5pix�㣬32*5=160����192-160=32 2�����ֵ�λ�á�
******************************************************************************/

// ��������X�ĳ��ȣ�
TYPE_LCD_XY cacu_devScan_coordinateX(void)
{
    return cacu_devScan_deteX(U_DevScan_AdrHalf-1)
            + U_DevScan_Pix_X_1Point;
}


// �������ַ��x���꣺
// ���ӣ�(32+1)=(4+5)+(33*5)=185.
/*****************************************************************************
*FUNC:return a value that between [0,191]
*IN:mAdr from [0,63]
*OUT:
*****************************************************************************/
TYPE_LCD_XY cacu_devScan_deteX(U32 mAdr)
{
    U32 mPoint;
    TYPE_LCD_XY  dwX;

    if(mAdr < U_DevScan_AdrHalf){//the addr between 0~31
        mPoint = mAdr;//31
        dwX =  U_DevScan_Pix_X_Start;
        dwX += (mPoint) *  U_DevScan_Pix_X_1Point;
        dwX += U_DevScan_Pix_X_1Point; // �����һ����ַ��λ��

    }else{//the addr between 32~63
        mPoint = mAdr%U_DevScan_AdrHalf;//31
        dwX =  U_DevScan_Pix_X_Start;
        dwX += (mPoint) *  U_DevScan_Pix_X_1Point;
        dwX += U_DevScan_Pix_X_1Point; // �����һ����ַ��λ��
    }

    //  if(  (mAdr+1 == U_DevScan_AdrHalf)
    //       || (mAdr+1 == U_DevScan_AdrMax)
    //       )
    //    {//if addr is 31 or 63,as half and whole

    //    }
    //  else
    //    {
    //      mPoint =  mAdr % U_DevScan_AdrHalf;
    //      mPoint += 1;   // (63-32)+1 =32
    //    }

    //  dwX =  U_DevScan_Pix_X_Start;
    //  dwX += (mPoint) *  U_DevScan_Pix_X_1Point;
    //  dwX += U_DevScan_Pix_X_1Point; // �����һ����ַ��λ��

    return dwX;
}

TYPE_LCD_XY cacu_devScan_deteY(U32 mAdr)
{
    if(mAdr < U_DevScan_AdrHalf)
    {
        return U_DevScan_Pix_Y0_Start;//31
    }
    else
    {
        return U_DevScan_Pix_Y1_Start;//57
    }
}

void dw_devScan_axis(void)
{

    U8 iiy;
  //  ShowCodeCharRL(0, 1, "^", FALSE);//��
    ShowCodeCharRL(0, 0, "mA", FALSE);

    // LcdSw_HvLine(mPixRow_S,mPixLine_S, mPixRow_E,mPixLine_E)
    // ���ߣ�
    LcdSw_HvLine(
                U_DevScan_Pix_Y1_Start,
                U_DevScan_Pix_X_Start, 
                U_DevScan_Pix_Y_End,
                U_DevScan_Pix_X_Start);//the second column at x,the y to the y1 as top to bottom

	
    LcdSw_ClrHvLine(
                34,
                U_DevScan_Pix_X_Start,
                32,
                U_DevScan_Pix_X_Start);



    // show > sign��
  //  ShowCodeCharRL(4, (U_LCD_LINE_MAX - 1), ">", FALSE);
    //��ʾ����0����U_DevScan_Pix_X_Start��
    LcdSw_HvLine(
                U_DevScan_Pix_Y0_Start,
                U_DevScan_Pix_X_Start,
                U_DevScan_Pix_Y0_Start,
                (U_DevScan_Pix_X_Start
                 + cacu_devScan_coordinateX())//y0 as row at horital,x from  x and x+cal
                );
	
    //��ʾ����32
    LcdSw_Fig(U_LCD_AXIX_MUM_POS_X_32, (U_LCD_AXIX_NUM_POS_Y), U_DevScan_AdrHalf, 2);


//    ShowCodeCharRL(8, (U_LCD_LINE_MAX - 1), ">", FALSE);
    // ����2��
    LcdSw_HvLine(
                U_DevScan_Pix_Y1_Start,
                U_DevScan_Pix_X_Start,
                U_DevScan_Pix_Y1_Start,
                (U_DevScan_Pix_X_Start
                 + cacu_devScan_coordinateX())
                );
    //��ʾ����64
    LcdSw_Fig(U_LCD_AXIX_MUM_POS_X_64, (U_LCD_AXIX_NUM_POS_Y), U_DevScan_AdrMax, 2);

    for(iiy=0;iiy<6;iiy++){
        //��ʾ�����꣬��ȡ6�����꼴��
        LcdSw_HvLine(
                    yval[iiy],
                U_DevScan_Pix_X_Start,
                yval[iiy],
                U_DevScan_Pix_X_Start-2
                );
        if(0==iiy%3)
            LcdSw_Ascii88Fig(yval[iiy]-3,0,30,2);
        else if(1==iiy%3)
            LcdSw_Ascii88Fig(yval[iiy]-3,0,20,2);
        if(2==iiy%3)
            LcdSw_Ascii88Fig(yval[iiy]-3,0,10,2);
    }


	ExecAllToLcdRam();

}

// ��ַ��λ����ʾ������ַ��λ�ߣ�
/*****************************************************************************
*FUNC:paint the locate line at the horictal line��the first and the end must be careful
*IN:
*OUT:
*****************************************************************************/
void dw_devScan_adrPrompt(void)
{
    U32 mAdr;
    //from 0-64,need to paint total 18 lines

    for(mAdr=0; mAdr<U_DevScan_AdrMax; mAdr++)//0~31//32~63
    {
        if((mAdr % 4) == 0||31==mAdr||63==mAdr)
        {
            dw_devScan_adrPrpt_one(mAdr);
        }
    }

    //  add_digital_num_at_axis();

}




// ����ַ��λ�ߣ��ж��� 8�ı������� 4�ı�����
/*****************************************************************************
*FUNC:to draw the address line at the horitical line
*IN:
*OUT:
*****************************************************************************/
void dw_devScan_adrPrpt_one(U32 mAdr)
{
    TYPE_LCD_XY  dwX;
    TYPE_LCD_XY  dwY;

    dwX = cacu_devScan_deteX(mAdr);
    dwY = cacu_devScan_deteY(mAdr);

    if((mAdr % 8) == 0)
    {
        LcdSw_HvLine(dwY,dwX, (dwY+4),dwX);
    }
    else if((mAdr % 4) == 0)
    {
        LcdSw_HvLine(dwY,dwX, (dwY+2),dwX);
    }
    else
    {
        LcdSw_HvLine(dwY,dwX, (dwY+4),dwX);

    }
}




// ��ʾ����ֵ-1����ַ��

/*****************************************************************************
*FUNC: paint hortical or vertical line from input parameter
*IN:
*OUT:
*****************************************************************************/
void dw_devScan_current_one(U32 mAdr, U8 mCurrent)
{

    TYPE_LCD_XY  dwX;
    TYPE_LCD_XY  dwY;
    U8  lvLineY;

    dwX = cacu_devScan_deteX(mAdr);//mAdr from 0 to 63
    lvLineY = (mCurrent / 2);//the current value as theput value
    if(lvLineY >= U_DevScan_Pix_Y_1Point)//out of range
    {
        lvLineY = (U_DevScan_Pix_Y_1Point - 1);
    }

    dwY = cacu_devScan_deteY(mAdr);

    LcdSw_HvLine(dwY - lvLineY, dwX,
                 dwY,           dwX);
    ExecLcdShow();//the lcd buffer maybe full if called many times,so deal

}


/******************************************************************************
* ҳ��: // P060
******************************************************************************/


// �� ����:
void dw_devScan_current_all(U8 *pCurrent)
{
    U32 mAdr;
    for(mAdr=0; mAdr<U_DevScan_AdrMax; mAdr++)//loop for 64 times
    {
        dw_devScan_current_one(mAdr, *pCurrent);//first time,
        pCurrent++;//auto incresement
    }
}

/******************************************************************************
* ҳ��: // ��·���
******************************************************************************/


// ��ʾ����ֵ-1����ַ��
void dw_devScan_current_one(U32 mAdr, U8 mCurrent);
// ��ַ��λ����ʾ������ַ��λ�ߣ�
void dw_devScan_adrPrompt(void);

// ����ַ��λ�ߣ��ж��� 8�ı������� 4�ı�����
void dw_devScan_adrPrpt_one(U32 mAdr);
// ��������X�ĳ��ȣ�
TYPE_LCD_XY cacu_devScan_coordinateX(void);
// �������ַ��x���꣺33=(4+5)+(33*5)=185.
TYPE_LCD_XY cacu_devScan_deteX(U32 mAdr);


TYPE_LCD_XY cacu_devScan_deteY(U32 mAdr);
// �������᣺
void dw_devScan_axis(void);


// �� ��ʾ���꣺
void dw_devScan_coordinate(void);
// �� ����:
void dw_devScan_current_all(U8 *pCurrent);




static U8 mNowLoopDevScan_Loop;
void P060_TsLoopDevScan_Back(void)	//
{

    UNINITENTRY(p060);
	
	if((mNowLoopDevScan_Loop == 0) 
	  || (mNowLoopDevScan_Loop > U_SYS_LOOP_MAX))
	{
		ICan_Tx_Inquire_LoopBrowsStop(mNowLoopDevScan_Loop);
	}
}

void P060_TsLoopDevScan_First(void)
{
	mNowLoopDevScan_Loop = ~0;
    INITENTRY(p060);
	
}

void P060_TsLoopDevScan_Usua(void)
{
    KEYCALL(p060);
	
	if(bGetPageKey(&vThisPageKey))
	{
		if((vThisPageKey == 0) || (vThisPageKey > U_SYS_LOOP_MAX))
		{
			return;
		}
		mNowLoopDevScan_Loop = vThisPageKey;
		ICan_Tx_Inquire_LoopBrowse(mNowLoopDevScan_Loop);
	}
}

/******************************************************************************
* ҳ��: // ��ʾ ģ��������
*  _��·_ _ _��ַ: _ _ _ (��ʾ��ǰֵ)
* |
* |_________________________>
* �ѵ�ǰֵ��һ������ʾ���߶ȶ�Ӧֵ�Ĵ�С�����128.
* ÿ�õ�һ���µ�ֵ��X����������һ����ʾλ�ã�����������࿪ʼˢ�£�ͬʱ�����Ҳ�16�����������
* ��Ч�����Ӿ��ϲ�������Ըģ�����ÿ�εõ�ֵ���ú���2�����ر�ʾ��
******************************************************************************/
void P061_TsDeteCurve_Back(void)	//
{
    UNINITENTRY(p061);
}
void P061_TsDeteCurve_First(void)
{
    INITENTRY(p061);
}
void P061_TsDeteCurve_Usua(void)
{
    KEYCALL(p061);
}

/******************************************************************************
* ҳ��: // ��·������ѯ
*  	_��·:
*   ��·��������:
*  ��·24Vʱ����:
******************************************************************************/
void P062_TsLoopData_Back(void)	//
{
    UNINITENTRY(p062);
}
void P062_TsLoopData_First(void)
{
    INITENTRY(p062);
}
void P062_TsLoopData_Usua(void)
{
    KEYCALL(p062);
}
/******************************************************************************
* ҳ��: // �ֳ��豸����״̬
*  	_��·_ _ _��ַ:
*   ��������:
*   ����״̬:
******************************************************************************/
void P063_TsDeteType_Back(void)	//
{
    UNINITENTRY(p063);
}
void P063_TsDeteType_First(void)
{
    INITENTRY(p063);
}
void P063_TsDeteType_Usua(void)
{
    KEYCALL(p063);
}
/******************************************************************************
* ҳ��: //
*  _��·_ _ _��ַ
*  ʮ���������ݣ�˳����ʾ�� ��������ͷˢ����ʾ�����������2���ֽڡ�
*
******************************************************************************/
void P064_TsDeteData_Back(void)	//
{
    UNINITENTRY(p064);
}
void P064_TsDeteData_First(void)
{
    INITENTRY(p064);
}
void P064_TsDeteData_Usua(void)
{
    KEYCALL(p064);
}
/******************************************************************************
* ҳ��: // �Լ죻Һ��ɨ��������ƣ���������˳����������
*
******************************************************************************/
void P065_TsCSoundAndLed_Back(void)	//
{
    UNINITENTRY(p065);
}
void P065_TsCSoundAndLed_First(void)
{
    INITENTRY(p065);
}
void P065_TsCSoundAndLed_Usua(void)
{
    KEYCALL(p065);
}

/******************************************************************************
* ҳ��: // ���԰�����
* ����Ļ�ϰ���ʵ�ʼ���˳�򻭱�־����ĳ�������£����ɫ��
* ����6���ް������룬���Զ��˳����˵�
******************************************************************************/
void P067_TsCKey_Back(void)	//
{
    UNINITENTRY(p067);
}
void P067_TsCKey_First(void)
{
    INITENTRY(p067);
}
void P067_TsCKey_Usua(void)
{
    KEYCALL(p067);
}

// �������ʱ�Ĵ���
void KeyCheck_ShowInLcd(U8 mKey)
{

}


/******************************************************************************
* ҳ��: // ����Ӳ�����ܼ���״̬����LCD����ʾ
* ���� ��
******************************************************************************/

void P068_TsAllHardware_Back(void)	//
{
	chkHd_AllHd_Exit();
}
void P068_TsAllHardware_First(void)
{
	chkHd_AllHd_Ini();
}
void P068_TsAllHardware_Usua(void)
{
	chkHd_AllHd_Exec();
}



/******************************************************************************
* ҳ��: // ���� ͨѶ-iCan;
* ����1��֡��:
* ����2��֡��:
* ����3��֡��:
* ����4��֡��:
******************************************************************************/
void P072_TsCommUnit_Back(void)	//
{
    UNINITENTRY(p072);
}
void P072_TsCommUnit_First(void)
{
    INITENTRY(p072);
}
void P072_TsCommUnit_Usua(void)
{
    KEYCALL(p072);
}
/******************************************************************************
* ҳ��: // ���� ͨѶ-eCan;
* ��������֡��:
* ���������������ߣ���ʾ����֡����
******************************************************************************/
void P073_TsCommMach_Back(void)	//
{
    UNINITENTRY(p073);
}
void P073_TsCommMach_First(void)
{
    INITENTRY(p073);
}
void P073_TsCommMach_Usua(void)
{
    KEYCALL(p073);
}
/******************************************************************************
* ҳ��: //����������
*
******************************************************************************/
void P077_ClrLinkLogic_Back(void)	//
{
    UNINITENTRY(p077);
}
void P077_ClrLinkLogic_First(void)
{
    INITENTRY(p077);
//    ShowCodeCharRL(3,5,"���������",FALSE);
}
void P077_ClrLinkLogic_Usua(void)
{
    KEYCALL(p077);
}

void P077_ClrLinkLogic_showPercent(U8 mPercent)
{

}

/******************************************************************************
* ҳ��: //���ע��
*
******************************************************************************/
void P078_ClrNote_Back(void)	//
{
    UNINITENTRY(p078);
}
void P078_ClrNote_First(void)
{
    INITENTRY(p078);
//    ShowCodeCharRL(3,5,"��ע��",FALSE);
}
void P078_ClrNote_Usua(void)
{
    KEYCALL(p078);
}
void P078_ClrNote_showPercent(U8 mPercent)
{

}


/******************************************************************************
* ҳ��: //�����·�Ǽ�
*
******************************************************************************/
void P080_ClrLoopRegi_Back(void)	//
{
    UNINITENTRY(p080);
}
void P080_ClrLoopRegi_First(void)
{
    INITENTRY(p080);
//    ShowCodeCharRL(4,5,"�����·�Ǽ�",FALSE);
}
void P080_ClrLoopRegi_Usua(void)
{
    KEYCALL(p080);
}
void P080_ClrLoopRegi_showPercent(U8 mPercent)
{

}

/******************************************************************************
* ҳ��: //���������ַ
*
******************************************************************************/
void P081_ClrAddrRelation_Back(void)	//
{
    UNINITENTRY(p081);
}
void P081_ClrAddrRelation_First(void)
{
    INITENTRY(p081);
//    ShowCodeCharRL(4,5,"���������ַ",FALSE);
}
void P081_ClrAddrRelation_Usua(void)
{
    KEYCALL(p081);
}

void P081_ClrAddrRelation_showPercent(U8 mPercent)
{

}

/******************************************************************************
* ҳ��: // �޸�1������
* ����������� * ��ʾ��

* ԭ������: _ _ _
* ��������: _ _ _
* �ٴ�ȷ��: _ _ _
******************************************************************************/
void P083_Pssw1_Change_Back(void)	//
{
    UNINITENTRY(p083);
}
void P083_Pssw1_Change_First(void)
{
    INITENTRY(p083);
//    ShowCodeCharRL(4,5,"�޸�1������",FALSE);
}
void P083_Pssw1_Change_Usua(void)
{
    KEYCALL(p083);
}
/******************************************************************************
* ҳ��: // �޸�2������
* ����������� * ��ʾ��

* ԭ������: _ _ _ _ _ _
* ��������: _ _ _ _ _ _
* �ٴ�ȷ��: _ _ _ _ _ _
*
******************************************************************************/
void P084_Pssw2_Change_Back(void)	//
{
    UNINITENTRY(p084);
}
void P084_Pssw2_Change_First(void)
{
    INITENTRY(p084);
//    ShowCodeCharRL(4,5,"�޸�2������",FALSE);
}
void P084_Pssw2_Change_Usua(void)
{
    KEYCALL(p084);
}

/******************************************************************************
* ҳ��: //
* 
******************************************************************************/
/*

void PXXX_Back(void)	//
{
	
}
void PXXX_First(void)
{
	
}
void PXXX_Usua(void)
{
	
}

*/
/******************************************************************************
* NAME: 
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

