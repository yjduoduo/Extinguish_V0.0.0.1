
#define __lcdCst_Menu_C__
/******************************************************************************
* @file    lcdCst_Menu.c
* @author  yx
* @version V1.0
* @date    2012-01-05
* @brief   
	   
	   
	   
******************************************************************************/

#include  "lcdCst_Menu.h"

#include  "lcdCst_PageNum.h" 
#include  "sysDef.h"   // emUserGrade �Ķ���


// #include  "sysStatus.h"
extern U8 GetLanguage(void);
//#include "..\\s00Prj\\incFile.h"	

//-----------------   --------------------------------// 
// #include  "tsk_lcd_incIn.h"

//----- Me:

/*================= ���� ============================================*/

enum emMenuId{
	U_Menu_Space_ID = U_Menu_Invalid_ID,
	U_Menu_Virtual_ID = U_Menu_SysIni_ID,
	U_Menu_Ini_ID,
	U_Menu_0_UserSet_ID,
	U_Menu_1_Inquire_ID,
	U_Menu_2_Measure_ID,
	U_Menu_3_SystemSet_ID,
	U_Menu_4_FactorySet_ID,
	
	
	
	
	
	U_Menu_1_0_SysState_ID,
	U_Menu_1_1_QrSysInstal_ID,
	U_Menu_1_2_Hist_ID,
	
	
	U_Menu_2_0_Dete_ID,
	U_Menu_2_1_SelfChk_ID,
	U_Menu_2_2_Comm_ID,
	
	U_Menu_3_0_ClrSave_ID,
	U_Menu_3_1_User_ID,
	
	U_Menu_ID_MAX,
};
	


	
/*================= �ṹ���� ========================================*/

/*================= ˽�нṹ�������� ================================*/

/*================= ���к������� ====================================*/

/*================= ˽�к������� ====================================*/

/*=================  ================================================*/
		

/******************************************************************************
* NAME: 
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/


//   *xscn[16];      *xsen[5];  userGrd,        preItemMenuBuf,   nextItemMenuBuf,   page

const TMenu CstMenu_Space =  {{"", "", "",}, U_UserGrd_INVALID, U_MENU_IdInvalid, U_MENU_IdInvalid, 0};  //��

const TMenu CstMenu_Virtual = 
	{{"�˵�:", 		"menu:", ""}, 	U_UserGrd_GUEST, U_Menu_Space_ID, 	U_Menu_Ini_ID, 		U_MENU_NEXT}; 

	
const TMenu CstMenu_Ini[]=
{
//   *xscn[16];      *xsen[5];  userGrd,        preItemMenuBuf,   nextItemMenuBuf,   page
	//�ײ˵���
	{{"����Ӳ������",		"x", ""}, U_UserGrd_GUEST, U_Menu_Virtual_ID, U_MENU_TO_PAGE, U_P068_TsAllHardware}, 
	
	{{"�����ֶ�����",	"x", ""},  U_UserGrd_GUEST, U_Menu_Virtual_ID, U_MENU_TO_PAGE, 		U_P010_ManuActModu},
	{{"������ѯ",	"a", ""},  U_UserGrd_GUEST, U_Menu_Virtual_ID, U_Menu_1_Inquire_ID, 	U_MENU_NEXT},
	{{"�����û�����",	"c", ""},  U_UserGrd_GUEST, U_Menu_Virtual_ID, U_Menu_0_UserSet_ID, 	U_MENU_NEXT}, 
	{{"��������",	"y", ""},  U_UserGrd_GUEST, U_Menu_Virtual_ID, U_Menu_2_Measure_ID, 	U_MENU_NEXT},
	{{"����ϵͳ����",	"c", ""},  U_UserGrd_GUEST, U_Menu_Virtual_ID, U_Menu_3_SystemSet_ID, 	U_MENU_NEXT}, 
	{{"������������",	"y", ""},  U_UserGrd_GUEST, U_Menu_Virtual_ID, U_Menu_4_FactorySet_ID,U_MENU_NEXT},
	{{"��������",	"x", ""},  U_UserGrd_GUEST, U_Menu_Virtual_ID, U_MENU_TO_PAGE,        U_P011_Help},
	
};



const TMenu CstMenu_0_UserSet[]=
{
//   *xscn[16];      *xsen[5];  userGrd,        preItemMenuBuf,   nextItemMenuBuf,   page
	//�û����ã�
	
	{{"�����Զ��Ǽ�",	"x", ""}, U_UserGrd_GUEST, U_Menu_Ini_ID, U_MENU_TO_PAGE, U_P016_AutoRegist}, 
	{{"�����ֶ��Ǽ�",	"x", ""}, U_UserGrd_GUEST, U_Menu_Ini_ID, U_MENU_TO_PAGE, U_P017_ManuRegist}, 
	{{"�����ֶ�����",	"x", ""}, U_UserGrd_GUEST, U_Menu_Ini_ID, U_MENU_TO_PAGE, U_P018_SetDisable},//��ʾ�����β��������κͽ����������
		
	{{"�������ں�ʱ��","x", ""}, U_UserGrd_GUEST, U_Menu_Ini_ID, U_MENU_TO_PAGE, 			U_P013_SetClock},
	
};





const TMenu CstMenu_1_Inquire[]=
{
//   *xscn[16];      *xsen[5];  userGrd,        preItemMenuBuf,   nextItemMenuBuf,   page
	//��ѯ��
	{{"������ѯ�ֶ��Զ�״̬",	"x", ""}, U_UserGrd_GUEST, U_Menu_Ini_ID, U_MENU_TO_PAGE, U_P059_QrAutoManu},  	
	
	{{"������ǰ����",	"x", ""},         U_UserGrd_GUEST, U_Menu_Ini_ID, U_MENU_TO_PAGE, U_P040_QrNowFault}, 
	{{"������ǰ����",	"x", ""},         U_UserGrd_GUEST, U_Menu_Ini_ID, U_MENU_TO_PAGE, U_P041_QrNowDisable},  	
	
	//�Ǽǣ�������̣�ע�ͣ�ר�߹��ϼ��λ��
	{{"������ѯ��װ����",	"x", ""}, U_UserGrd_GUEST, U_Menu_Ini_ID, U_Menu_1_1_QrSysInstal_ID, 	U_MENU_NEXT},  //��Ԫ�����������������ӡ,ͨѶ����
	// ������Ԫ����汾��
	{{"������ѯϵͳ״̬",	"x", ""}, U_UserGrd_GUEST, U_Menu_Ini_ID, U_Menu_1_0_SysState_ID, 		U_MENU_NEXT},  
	{{"������ѯ��ʷ��¼",	"x", ""}, U_UserGrd_GUEST, U_Menu_Ini_ID, U_Menu_1_2_Hist_ID, 		U_MENU_NEXT}, 
	 
	
};


const TMenu CstMenu_1_0_SysState[]=
{
//   *xscn[16];      *xsen[5];  userGrd,        preItemMenuBuf,   nextItemMenuBuf,   page
	//3.��ѯ //3.����Ԫ������������
	{{"������ѯ����ģʽ",		"x", ""}, U_UserGrd_GUEST, U_Menu_1_Inquire_ID, U_MENU_TO_PAGE, U_P039_QrModeFieldDebug},  //
	{{"������ѯ�������",		"x", ""}, U_UserGrd_GUEST, U_Menu_1_Inquire_ID, U_MENU_TO_PAGE, U_P049_QrMachNet}, 
	
	
	{{"��������Ԫ����汾",	"x", ""}, U_UserGrd_GUEST, U_Menu_1_Inquire_ID, U_MENU_TO_PAGE, U_P047_QrSoftVer},
	 
};

const TMenu CstMenu_1_1_QrSysInstal[]=
{
//   *xscn[16];      *xsen[5];  userGrd,        preItemMenuBuf,   nextItemMenuBuf,   page
	//3.��ѯ //4.ϵͳ����
	{{"������ѯ���ߵǼǵ�ַ",	"x", ""}, U_UserGrd_GUEST, U_Menu_1_Inquire_ID, U_MENU_TO_PAGE, U_P058_QrFieldRegist},  //
	{{"������ѯ�������",		"x", ""}, U_UserGrd_GUEST, U_Menu_1_Inquire_ID, U_MENU_TO_PAGE, U_P042_QrLoopLinkLgc}, 
	{{"������ѯ����ע��",		"x", ""}, U_UserGrd_GUEST, U_Menu_1_Inquire_ID, U_MENU_TO_PAGE, U_P044_QrNote}, 
	
	{{"������ѯ���������",	"x", ""}, U_UserGrd_GUEST, U_Menu_1_Inquire_ID, U_MENU_TO_PAGE, U_P048_QrUnitRegi}, 
	{{"������ѯ������ַ",		"x", ""}, U_UserGrd_GUEST, U_Menu_1_Inquire_ID, U_MENU_TO_PAGE, U_P028_QrAddrRelation},  //
	 
	
};

const TMenu CstMenu_1_2_Hist[]=
{
//   *xscn[16];      *xsen[5];  userGrd,        preItemMenuBuf,   nextItemMenuBuf,   page
	//3.��ѯ //5.��ʷ��¼
	{{"����ȫ����ʷ",		"x", ""}, U_UserGrd_GUEST, U_Menu_1_Inquire_ID, U_MENU_TO_PAGE, U_P052_QrHistAll}, 
	{{"��������ʷ",		"x", ""}, U_UserGrd_GUEST, U_Menu_1_Inquire_ID, U_MENU_TO_PAGE, U_P053_QrHistAlarm}, 
	{{"����������ʷ",		"x", ""}, U_UserGrd_GUEST, U_Menu_1_Inquire_ID, U_MENU_TO_PAGE, U_P054_QrHistLink}, 
	{{"����������ʷ",		"x", ""}, U_UserGrd_GUEST, U_Menu_1_Inquire_ID, U_MENU_TO_PAGE, U_P055_QrHistFault}, 
	{{"����������ʷ",		"x", ""}, U_UserGrd_GUEST, U_Menu_1_Inquire_ID, U_MENU_TO_PAGE, U_P056_QrHistOpea}, 
	{{"����������ʷ",		"x", ""}, U_UserGrd_GUEST, U_Menu_1_Inquire_ID, U_MENU_TO_PAGE, U_P057_QrHistOthers}, //��洢������ȣ����ز˵���������ȫ����ʷ
	 
};



const TMenu CstMenu_2_Measure[]=
{
//   *xscn[16];      *xsen[5];  userGrd,        preItemMenuBuf,   nextItemMenuBuf,   page
	//4. ����
    
	{{"������·���",			"x", ""}, U_UserGrd_GUEST, U_Menu_Ini_ID, U_MENU_TO_PAGE, U_P060_TsLoopDevScan}, 
	//ģ�����ߣ���·�����������ͣ����ݲ�ѯ��
	{{"������·�ֳ���������",	"x", ""}, U_UserGrd_GUEST, U_Menu_Ini_ID, U_Menu_2_0_Dete_ID, U_MENU_NEXT}, 
	{{"��������ָʾ�Ƽ������Լ�","x", ""}, U_UserGrd_GUEST, U_Menu_Ini_ID, U_Menu_2_1_SelfChk_ID, U_MENU_NEXT},  //�����Լ� ����
	{{"������Ԫ�ͻ���ͨѶ���","x", ""}, U_UserGrd_GUEST, U_Menu_Ini_ID, U_Menu_2_2_Comm_ID, U_MENU_NEXT},   
	 
	
};


const TMenu CstMenu_2_0_Dete[]=
{
//   *xscn[16];      *xsen[5];  userGrd,        preItemMenuBuf,   nextItemMenuBuf,   page
	//3.���� //2.��·�ֳ���������	
	{{"����ģ������",			"x", ""}, U_UserGrd_GUEST, U_Menu_2_Measure_ID, U_MENU_TO_PAGE, U_P061_TsDeteCurve}, 
	{{"������·����",			"x", ""}, U_UserGrd_GUEST, U_Menu_2_Measure_ID, U_MENU_TO_PAGE, U_P062_TsLoopData}, 
	{{"������·�ֳ���������",		"x", ""}, U_UserGrd_GUEST, U_Menu_2_Measure_ID, U_MENU_TO_PAGE, U_P063_TsDeteType}, 
	{{"������·�ֳ��������ݲ�ѯ",	"x", ""}, U_UserGrd_GUEST, U_Menu_2_Measure_ID, U_MENU_TO_PAGE, U_P064_TsDeteData}, 	
	 
};

const TMenu CstMenu_2_1_SelfChk[]=
{
//   *xscn[16];      *xsen[5];  userGrd,        preItemMenuBuf,   nextItemMenuBuf,   page
	//3.���� //3.���⼰�����Լ�
	
	{{"��������ָʾ�Ƽ��","x", ""}, U_UserGrd_GUEST, U_Menu_2_Measure_ID, U_MENU_TO_PAGE, U_P065_TsCSoundAndLed}, 
	{{"�����������",		"x", ""}, U_UserGrd_GUEST, U_Menu_2_Measure_ID, U_MENU_TO_PAGE, U_P067_TsCKey}, 
	{{"����Ӳ������",		"x", ""}, U_UserGrd_GUEST, U_Menu_2_Measure_ID, U_MENU_TO_PAGE, U_P068_TsAllHardware}, 
	
};

const TMenu CstMenu_2_2_Comm[]=
{
//   *xscn[16];      *xsen[5];  userGrd,        preItemMenuBuf,   nextItemMenuBuf,   page
	//3.���� //4.��Ԫ�ͻ���ͨѶ���
	
	{{"�������Ե�ԪͨѶ",	"x", ""}, U_UserGrd_GUEST, U_Menu_2_Measure_ID, U_MENU_TO_PAGE, U_P072_TsCommUnit}, //10*10=100.
	{{"�������Ի���ͨѶ",	"x", ""}, U_UserGrd_GUEST, U_Menu_2_Measure_ID, U_MENU_TO_PAGE, U_P073_TsCommMach}, 
	
};



const TMenu CstMenu_3_SystemSet[]=
{
//   *xscn[16];      *xsen[5];  userGrd,        preItemMenuBuf,   nextItemMenuBuf,   page
	//5.ϵͳ����   
	{{"�����������",		"x", ""}, U_UserGrd_GUEST, U_Menu_Ini_ID, U_MENU_TO_PAGE, U_P020_SetLinkLogic}, 
	{{"�������������",	"z", ""}, U_UserGrd_GUEST, U_Menu_Ini_ID, U_MENU_TO_PAGE, U_P030_SetUnitRegi}, //
	{{"�����ֶ�ע��",		"x", ""}, U_UserGrd_GUEST, U_Menu_Ini_ID, U_MENU_TO_PAGE, U_P019_SetNote},  //
	{{"����������ַ",		"x", ""}, U_UserGrd_GUEST, U_Menu_Ini_ID, U_MENU_TO_PAGE, U_P027_SetAddrRelation},  //
	{{"������������",		"x", ""}, U_UserGrd_GUEST, U_Menu_Ini_ID, U_MENU_TO_PAGE, U_P024_SetMachNet},  //������ַ������ģʽ
	{{"��������ѡ��",		"x", ""}, U_UserGrd_GUEST, U_Menu_Ini_ID, U_MENU_TO_PAGE, U_P037_SetLanguage},  //
	{{"��������ģʽѡ��",		"x", ""}, U_UserGrd_GUEST, U_Menu_Ini_ID, U_MENU_TO_PAGE, U_P038_SetModeFieldDebug},  //
	
	
};


const TMenu CstMenu_4_FactorySet[]=
{
//   *xscn[16];      *xsen[5];  userGrd,        preItemMenuBuf,   nextItemMenuBuf,   page
	//6.��������   
	{{"��������洢����",	"z", ""}, U_UserGrd_GUEST, U_Menu_Ini_ID, U_Menu_3_0_ClrSave_ID, U_MENU_NEXT}, //��Ǽ� ������� ���߶�Ӧ ע��  
	{{"�����ָ�Ĭ������",	"z", ""}, U_UserGrd_GUEST, U_Menu_Ini_ID, U_MENU_TO_PAGE, 			U_P015_SetDefault}, //��ҳ�棺��������1�ŵ�ַ��ϵͳ��1��·1ר�ߣ��Զ���ֹ�ֶ�������ӡȫ����Ϣ��   
	{{"�����������",		"z", ""}, U_UserGrd_GUEST, U_Menu_Ini_ID, U_Menu_3_1_User_ID, 	U_MENU_NEXT}, //��ӣ�ɾ�����޸ġ�     
	
	
};


const TMenu CstMenu_3_0_ClrSave[]=
{
//   *xscn[16];      *xsen[5];  userGrd,        preItemMenuBuf,   nextItemMenuBuf,   page
	//4.�������� //2.����洢����
	{{"������Ǽ�",		"x", ""}, U_UserGrd_GUEST, U_Menu_4_FactorySet_ID, U_MENU_TO_PAGE, U_P080_ClrLoopRegi},
	{{"�������������",	"x", ""}, U_UserGrd_GUEST, U_Menu_4_FactorySet_ID, U_MENU_TO_PAGE, U_P077_ClrLinkLogic},
	{{"������ע��",		"x", ""}, U_UserGrd_GUEST, U_Menu_4_FactorySet_ID, U_MENU_TO_PAGE, U_P078_ClrNote},
	{{"�����������ַ",	"x", ""}, U_UserGrd_GUEST, U_Menu_4_FactorySet_ID, U_MENU_TO_PAGE, U_P081_ClrAddrRelation},
	 
};

const TMenu CstMenu_3_1_User[]=
{
//   *xscn[16];      *xsen[5];  userGrd,        preItemMenuBuf,   nextItemMenuBuf,   page
	//4.�������� //4.�û�����
	{{"�����޸�1������",		"x", ""}, U_UserGrd_GUEST, U_Menu_4_FactorySet_ID, U_MENU_TO_PAGE, U_P083_Pssw1_Change},
	{{"�����޸�2������",		"x", ""}, U_UserGrd_GUEST, U_Menu_4_FactorySet_ID, U_MENU_TO_PAGE, U_P084_Pssw2_Change},
	 
};




/******************************************************************************
* NAME: 
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
/*


const TMenu Cst [U_MENU_SameGrade_ITEM_MAX]=
{
//   *xscn[16];      *xsen[5];  userGrd,        preItemMenuBuf,   nextItemMenuBuf,   page
	
};

*/


/******************************************************************************
* NAME: 
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
	
/******************************************************************************
* FUNC: //�жϲ˵��Ƿ���Ч
*	   //private
*   IN: 
*  OUT: 
******************************************************************************/
BOOL bValidCstMenu (const TMenu *m_pMenu)
{
	if((m_pMenu->nextItemMenuBuf == 0) || (m_pMenu->nextItemMenuBuf == (0xFF)))
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}

BOOL bMenuIdError(U8 mMenuId)
{
	U8 total;
	if(GetMenuBufTotal(mMenuId, &total)){
		return FALSE;
	}
	else{
		return TRUE;
	}
		
	/*
	if((mMenuId == 0)||(mMenuId == U_Menu_Space_ID) || (mMenuId >= U_Menu_ID_MAX))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
	*/
}
	

/******************************************************************************
* FUNC: // �˵��ַ���ȡ:
*   IN:
*  OUT: 
******************************************************************************/

char *pGetMenuChar(const TMenu *pOneMenu)
{
	U8 language;
	language= GetLanguage();
	switch(language)
	{
		case U_Complex_LANGUAGE:
			return (char*)(pOneMenu->stLanguage.sComplex);
			
		case U_English_LANGUAGE:
			return (char*)(pOneMenu->stLanguage.sEn);
			
		case U_Chinese_LANGUAGE:
		default:
			return (char*)(pOneMenu->stLanguage.sCn);
	}
}



/******************************************************************************
* FUNC: //
*   IN: emMenuId
*  OUT: TMenu[]����������������ָ�롣
* 	U_SIGN_bHaveTested
******************************************************************************/
	
const TMenu *pGetMenuBufFirAndTotal(U8 mMenuId, U8 *m_pRtnTotal)
{
	if(mMenuId >= U_Menu_ID_MAX) 
	{
		*m_pRtnTotal = 0;
		return &CstMenu_Space;
	}
	switch(mMenuId)
	{
		case U_Menu_Virtual_ID:
			*m_pRtnTotal = sizeof(CstMenu_Virtual) / sizeof(TMenu);
			return &CstMenu_Virtual;
			
		case U_Menu_Ini_ID:
			*m_pRtnTotal = sizeof(CstMenu_Ini) / sizeof(TMenu);
			return &CstMenu_Ini[0];
			
		case U_Menu_0_UserSet_ID:
			*m_pRtnTotal = sizeof(CstMenu_0_UserSet) / sizeof(TMenu);
			return &CstMenu_0_UserSet[0];
			
		case U_Menu_1_Inquire_ID:
			*m_pRtnTotal = sizeof(CstMenu_1_Inquire) / sizeof(TMenu);
			return &CstMenu_1_Inquire[0];
			
		case U_Menu_2_Measure_ID:
			*m_pRtnTotal = sizeof(CstMenu_2_Measure) / sizeof(TMenu);
			return &CstMenu_2_Measure[0];
			
		case U_Menu_3_SystemSet_ID:
			*m_pRtnTotal = sizeof(CstMenu_3_SystemSet) / sizeof(TMenu);
			return &CstMenu_3_SystemSet[0];
			
		case U_Menu_4_FactorySet_ID:
			*m_pRtnTotal = sizeof(CstMenu_4_FactorySet) / sizeof(TMenu);
			return &CstMenu_4_FactorySet[0];
	
	
			
	
	
		case U_Menu_1_0_SysState_ID:
			*m_pRtnTotal = sizeof(CstMenu_1_0_SysState) / sizeof(TMenu);
			return &CstMenu_1_0_SysState[0];
			
		case U_Menu_1_1_QrSysInstal_ID:
			*m_pRtnTotal = sizeof(CstMenu_1_1_QrSysInstal) / sizeof(TMenu);
			return &CstMenu_1_1_QrSysInstal[0];
			
		case U_Menu_1_2_Hist_ID:
			*m_pRtnTotal = sizeof(CstMenu_1_2_Hist) / sizeof(TMenu);
			return &CstMenu_1_2_Hist[0];
	
	
		case U_Menu_2_0_Dete_ID:
			*m_pRtnTotal = sizeof(CstMenu_2_0_Dete) / sizeof(TMenu);
			return &CstMenu_2_0_Dete[0];
			
		case U_Menu_2_1_SelfChk_ID:
			*m_pRtnTotal = sizeof(CstMenu_2_1_SelfChk) / sizeof(TMenu);
			return &CstMenu_2_1_SelfChk[0];
			
		case U_Menu_2_2_Comm_ID:
			*m_pRtnTotal = sizeof(CstMenu_2_2_Comm) / sizeof(TMenu);
			return &CstMenu_2_2_Comm[0];
	
		case U_Menu_3_0_ClrSave_ID:
			*m_pRtnTotal = sizeof(CstMenu_3_0_ClrSave) / sizeof(TMenu);
			return &CstMenu_3_0_ClrSave[0];
			
		case U_Menu_3_1_User_ID:
			*m_pRtnTotal = sizeof(CstMenu_3_1_User) / sizeof(TMenu);
			return &CstMenu_3_1_User[0];
			
	
		case U_Menu_Space_ID:
		default:
			*m_pRtnTotal = 0;
			return &CstMenu_Space;
	}
	
}


/******************************************************************************
* FUNC: //
* 	U_SIGN_bHaveTested
	pMenu = pGetCstBufFirMenu(U_Menu_Invalid_ID); // ""
	pMenu = pGetCstBufFirMenu(U_Menu_SysIni_ID); //�˵�
	pMenu = pGetCstBufFirMenu(3); //1. ����
	pMenu = pGetCstBufFirMenu(4); //1. ��·����
******************************************************************************/
const TMenu *pGetCstBufFirMenu(U8 mMenuId)
{
	U8 total;
	return pGetMenuBufFirAndTotal(mMenuId, &total);
}

/******************************************************************************
* FUNC: //
* 	U_SIGN_bHaveTested
	GetMenuBufTotal(U_Menu_Invalid_ID, &total); //0
	GetMenuBufTotal(U_Menu_SysIni_ID, &total); //1
	GetMenuBufTotal(3, &total); //6
	GetMenuBufTotal(4, &total); //6
******************************************************************************/
BOOL GetMenuBufTotal(U8 mMenuId, U8 *m_pRtnTotal)
{
	U8 total;
	pGetMenuBufFirAndTotal(mMenuId, &total);
	
	if(total >= U_MENU_SameGrade_ITEM_MAX)
	{
		total = 0;
	}
	*m_pRtnTotal = total;
	
	if(total == 0)
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
	
	
	/*
	for(menuNum=0; menuNum<U_MENU_SameGrade_ITEM_MAX; menuNum++)
	{
		if(!bValidCstMenu(pMenu))
		{
			break;
		}
		pMenu++;
	}
	if(menuNum < U_MENU_SameGrade_ITEM_MAX)
	{
		return TRUE;
	}
	*/
}



/******************************************************************************
* FUNC: //
* 	U_SIGN_bHaveTested

	bSucc = GetCstMenu(3, 0, &stMenu);
	pStMenu = &stMenu;
	bSucc = GetCstMenu(3, 0, pStMenu);
******************************************************************************/
BOOL GetCstMenu(U8 mMenuId, U8 mSequ, TMenu *pRtnMenu)
{
	const TMenu *pMenu;
	U8 menuTotal;
	
	pMenu = pGetMenuBufFirAndTotal(mMenuId, &menuTotal);
	
	if(mSequ >= menuTotal)  //���� (menuTotal == 0) �����
	{
		return FALSE;
	}
	else
	{
		pMenu += mSequ;
		*pRtnMenu = *pMenu;
		return TRUE;
	}
	
	//ע����������ֻ���˾ֲ�����pRtnMenu��ֵ���Ե��ô˺�����ָ����Ӱ�졣
	//pRtnMenu = (TMenu*)(pMenu);
}


/******************************************************************************
* FUNC: //
* 	U_SIGN_bHaveTested

	pMenu = pGetCstMenu(U_Menu_Invalid_ID, 0); // ""	
	pMenu = pGetCstMenu(U_Menu_SysIni_ID, 0); //�˵�
	pMenu = pGetCstMenu(U_Menu_SysIni_ID, 1); // ""
	pMenu = pGetCstMenu(3, 0); //1. ����
	pMenu = pGetCstMenu(3, 1); //2. �û�����
	pMenu = pGetCstMenu(3, 5); //6. ����
	pMenu = pGetCstMenu(3, 6); // ""
******************************************************************************/
const TMenu *pGetCstMenu(U8 mMenuId, U8 mSequ)
{
	
	const TMenu *pMenu;
	U8 menuTotal;
	
	pMenu = pGetMenuBufFirAndTotal(mMenuId, &menuTotal);
	
	if(mSequ < menuTotal)
	{
		pMenu += mSequ;
		
		return pMenu;
	}
	else
	{
		return &CstMenu_Space;
	}
	
}

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
