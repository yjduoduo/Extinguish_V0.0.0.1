
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
#include  "sysDef.h"   // emUserGrade 的定义


// #include  "sysStatus.h"
extern U8 GetLanguage(void);
//#include "..\\s00Prj\\incFile.h"	

//-----------------   --------------------------------// 
// #include  "tsk_lcd_incIn.h"

//----- Me:

/*================= 常数 ============================================*/

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
	


	
/*================= 结构定义 ========================================*/

/*================= 私有结构变量声明 ================================*/

/*================= 公有函数声明 ====================================*/

/*================= 私有函数声明 ====================================*/

/*=================  ================================================*/
		

/******************************************************************************
* NAME: 
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/


//   *xscn[16];      *xsen[5];  userGrd,        preItemMenuBuf,   nextItemMenuBuf,   page

const TMenu CstMenu_Space =  {{"", "", "",}, U_UserGrd_INVALID, U_MENU_IdInvalid, U_MENU_IdInvalid, 0};  //空

const TMenu CstMenu_Virtual = 
	{{"菜单:", 		"menu:", ""}, 	U_UserGrd_GUEST, U_Menu_Space_ID, 	U_Menu_Ini_ID, 		U_MENU_NEXT}; 

	
const TMenu CstMenu_Ini[]=
{
//   *xscn[16];      *xsen[5];  userGrd,        preItemMenuBuf,   nextItemMenuBuf,   page
	//首菜单：
	{{"３．硬件测试",		"x", ""}, U_UserGrd_GUEST, U_Menu_Virtual_ID, U_MENU_TO_PAGE, U_P068_TsAllHardware}, 
	
	{{"１．手动启动",	"x", ""},  U_UserGrd_GUEST, U_Menu_Virtual_ID, U_MENU_TO_PAGE, 		U_P010_ManuActModu},
	{{"２．查询",	"a", ""},  U_UserGrd_GUEST, U_Menu_Virtual_ID, U_Menu_1_Inquire_ID, 	U_MENU_NEXT},
	{{"３．用户设置",	"c", ""},  U_UserGrd_GUEST, U_Menu_Virtual_ID, U_Menu_0_UserSet_ID, 	U_MENU_NEXT}, 
	{{"４．测试",	"y", ""},  U_UserGrd_GUEST, U_Menu_Virtual_ID, U_Menu_2_Measure_ID, 	U_MENU_NEXT},
	{{"５．系统设置",	"c", ""},  U_UserGrd_GUEST, U_Menu_Virtual_ID, U_Menu_3_SystemSet_ID, 	U_MENU_NEXT}, 
	{{"６．出厂设置",	"y", ""},  U_UserGrd_GUEST, U_Menu_Virtual_ID, U_Menu_4_FactorySet_ID,U_MENU_NEXT},
	{{"７．帮助",	"x", ""},  U_UserGrd_GUEST, U_Menu_Virtual_ID, U_MENU_TO_PAGE,        U_P011_Help},
	
};



const TMenu CstMenu_0_UserSet[]=
{
//   *xscn[16];      *xsen[5];  userGrd,        preItemMenuBuf,   nextItemMenuBuf,   page
	//用户设置：
	
	{{"１．自动登记",	"x", ""}, U_UserGrd_GUEST, U_Menu_Ini_ID, U_MENU_TO_PAGE, U_P016_AutoRegist}, 
	{{"２．手动登记",	"x", ""}, U_UserGrd_GUEST, U_Menu_Ini_ID, U_MENU_TO_PAGE, U_P017_ManuRegist}, 
	{{"３．手动屏蔽",	"x", ""}, U_UserGrd_GUEST, U_Menu_Ini_ID, U_MENU_TO_PAGE, U_P018_SetDisable},//提示已屏蔽部件，屏蔽和解除都在里面
		
	{{"４．日期和时钟","x", ""}, U_UserGrd_GUEST, U_Menu_Ini_ID, U_MENU_TO_PAGE, 			U_P013_SetClock},
	
};





const TMenu CstMenu_1_Inquire[]=
{
//   *xscn[16];      *xsen[5];  userGrd,        preItemMenuBuf,   nextItemMenuBuf,   page
	//查询：
	{{"１．查询手动自动状态",	"x", ""}, U_UserGrd_GUEST, U_Menu_Ini_ID, U_MENU_TO_PAGE, U_P059_QrAutoManu},  	
	
	{{"２．当前故障",	"x", ""},         U_UserGrd_GUEST, U_Menu_Ini_ID, U_MENU_TO_PAGE, U_P040_QrNowFault}, 
	{{"３．当前屏蔽",	"x", ""},         U_UserGrd_GUEST, U_Menu_Ini_ID, U_MENU_TO_PAGE, U_P041_QrNowDisable},  	
	
	//登记；联动编程；注释；专线故障检测位；
	{{"４．查询安装配置",	"x", ""}, U_UserGrd_GUEST, U_Menu_Ini_ID, U_Menu_1_1_QrSysInstal_ID, 	U_MENU_NEXT},  //单元个数，组网情况，打印,通讯速率
	// ；各单元软件版本：
	{{"５．查询系统状态",	"x", ""}, U_UserGrd_GUEST, U_Menu_Ini_ID, U_Menu_1_0_SysState_ID, 		U_MENU_NEXT},  
	{{"６．查询历史记录",	"x", ""}, U_UserGrd_GUEST, U_Menu_Ini_ID, U_Menu_1_2_Hist_ID, 		U_MENU_NEXT}, 
	 
	
};


const TMenu CstMenu_1_0_SysState[]=
{
//   *xscn[16];      *xsen[5];  userGrd,        preItemMenuBuf,   nextItemMenuBuf,   page
	//3.查询 //3.各单元及部件的设置
	{{"１．查询调试模式",		"x", ""}, U_UserGrd_GUEST, U_Menu_1_Inquire_ID, U_MENU_TO_PAGE, U_P039_QrModeFieldDebug},  //
	{{"２．查询组网情况",		"x", ""}, U_UserGrd_GUEST, U_Menu_1_Inquire_ID, U_MENU_TO_PAGE, U_P049_QrMachNet}, 
	
	
	{{"３．各单元软件版本",	"x", ""}, U_UserGrd_GUEST, U_Menu_1_Inquire_ID, U_MENU_TO_PAGE, U_P047_QrSoftVer},
	 
};

const TMenu CstMenu_1_1_QrSysInstal[]=
{
//   *xscn[16];      *xsen[5];  userGrd,        preItemMenuBuf,   nextItemMenuBuf,   page
	//3.查询 //4.系统配置
	{{"１．查询总线登记地址",	"x", ""}, U_UserGrd_GUEST, U_Menu_1_Inquire_ID, U_MENU_TO_PAGE, U_P058_QrFieldRegist},  //
	{{"２．查询联动编程",		"x", ""}, U_UserGrd_GUEST, U_Menu_1_Inquire_ID, U_MENU_TO_PAGE, U_P042_QrLoopLinkLgc}, 
	{{"３．查询汉字注释",		"x", ""}, U_UserGrd_GUEST, U_Menu_1_Inquire_ID, U_MENU_TO_PAGE, U_P044_QrNote}, 
	
	{{"４．查询灭火区配置",	"x", ""}, U_UserGrd_GUEST, U_Menu_1_Inquire_ID, U_MENU_TO_PAGE, U_P048_QrUnitRegi}, 
	{{"５．查询关联地址",		"x", ""}, U_UserGrd_GUEST, U_Menu_1_Inquire_ID, U_MENU_TO_PAGE, U_P028_QrAddrRelation},  //
	 
	
};

const TMenu CstMenu_1_2_Hist[]=
{
//   *xscn[16];      *xsen[5];  userGrd,        preItemMenuBuf,   nextItemMenuBuf,   page
	//3.查询 //5.历史记录
	{{"１．全部历史",		"x", ""}, U_UserGrd_GUEST, U_Menu_1_Inquire_ID, U_MENU_TO_PAGE, U_P052_QrHistAll}, 
	{{"２．火警历史",		"x", ""}, U_UserGrd_GUEST, U_Menu_1_Inquire_ID, U_MENU_TO_PAGE, U_P053_QrHistAlarm}, 
	{{"３．联动历史",		"x", ""}, U_UserGrd_GUEST, U_Menu_1_Inquire_ID, U_MENU_TO_PAGE, U_P054_QrHistLink}, 
	{{"４．故障历史",		"x", ""}, U_UserGrd_GUEST, U_Menu_1_Inquire_ID, U_MENU_TO_PAGE, U_P055_QrHistFault}, 
	{{"５．操作历史",		"x", ""}, U_UserGrd_GUEST, U_Menu_1_Inquire_ID, U_MENU_TO_PAGE, U_P056_QrHistOpea}, 
	{{"６．其它历史",		"x", ""}, U_UserGrd_GUEST, U_Menu_1_Inquire_ID, U_MENU_TO_PAGE, U_P057_QrHistOthers}, //如存储器出错等，隐藏菜单，不计入全部历史
	 
};



const TMenu CstMenu_2_Measure[]=
{
//   *xscn[16];      *xsen[5];  userGrd,        preItemMenuBuf,   nextItemMenuBuf,   page
	//4. 测试
    
	{{"１．回路浏览",			"x", ""}, U_UserGrd_GUEST, U_Menu_Ini_ID, U_MENU_TO_PAGE, U_P060_TsLoopDevScan}, 
	//模拟曲线，回路电流部件类型，数据查询：
	{{"２．回路现场部件测试",	"x", ""}, U_UserGrd_GUEST, U_Menu_Ini_ID, U_Menu_2_0_Dete_ID, U_MENU_NEXT}, 
	{{"３．声、指示灯及按键自检","x", ""}, U_UserGrd_GUEST, U_Menu_Ini_ID, U_Menu_2_1_SelfChk_ID, U_MENU_NEXT},  //声光自检 按键
	{{"４．单元和机器通讯情况","x", ""}, U_UserGrd_GUEST, U_Menu_Ini_ID, U_Menu_2_2_Comm_ID, U_MENU_NEXT},   
	 
	
};


const TMenu CstMenu_2_0_Dete[]=
{
//   *xscn[16];      *xsen[5];  userGrd,        preItemMenuBuf,   nextItemMenuBuf,   page
	//3.测试 //2.回路现场部件测试	
	{{"１．模拟曲线",			"x", ""}, U_UserGrd_GUEST, U_Menu_2_Measure_ID, U_MENU_TO_PAGE, U_P061_TsDeteCurve}, 
	{{"２．回路电流",			"x", ""}, U_UserGrd_GUEST, U_Menu_2_Measure_ID, U_MENU_TO_PAGE, U_P062_TsLoopData}, 
	{{"３．回路现场部件类型",		"x", ""}, U_UserGrd_GUEST, U_Menu_2_Measure_ID, U_MENU_TO_PAGE, U_P063_TsDeteType}, 
	{{"４．回路现场部件数据查询",	"x", ""}, U_UserGrd_GUEST, U_Menu_2_Measure_ID, U_MENU_TO_PAGE, U_P064_TsDeteData}, 	
	 
};

const TMenu CstMenu_2_1_SelfChk[]=
{
//   *xscn[16];      *xsen[5];  userGrd,        preItemMenuBuf,   nextItemMenuBuf,   page
	//3.测试 //3.声光及按键自检
	
	{{"１．声、指示灯检测","x", ""}, U_UserGrd_GUEST, U_Menu_2_Measure_ID, U_MENU_TO_PAGE, U_P065_TsCSoundAndLed}, 
	{{"２．按键检测",		"x", ""}, U_UserGrd_GUEST, U_Menu_2_Measure_ID, U_MENU_TO_PAGE, U_P067_TsCKey}, 
	{{"３．硬件测试",		"x", ""}, U_UserGrd_GUEST, U_Menu_2_Measure_ID, U_MENU_TO_PAGE, U_P068_TsAllHardware}, 
	
};

const TMenu CstMenu_2_2_Comm[]=
{
//   *xscn[16];      *xsen[5];  userGrd,        preItemMenuBuf,   nextItemMenuBuf,   page
	//3.测试 //4.单元和机器通讯情况
	
	{{"１．测试单元通讯",	"x", ""}, U_UserGrd_GUEST, U_Menu_2_Measure_ID, U_MENU_TO_PAGE, U_P072_TsCommUnit}, //10*10=100.
	{{"２．测试机器通讯",	"x", ""}, U_UserGrd_GUEST, U_Menu_2_Measure_ID, U_MENU_TO_PAGE, U_P073_TsCommMach}, 
	
};



const TMenu CstMenu_3_SystemSet[]=
{
//   *xscn[16];      *xsen[5];  userGrd,        preItemMenuBuf,   nextItemMenuBuf,   page
	//5.系统设置   
	{{"１．联动编程",		"x", ""}, U_UserGrd_GUEST, U_Menu_Ini_ID, U_MENU_TO_PAGE, U_P020_SetLinkLogic}, 
	{{"２．灭火区配置",	"z", ""}, U_UserGrd_GUEST, U_Menu_Ini_ID, U_MENU_TO_PAGE, U_P030_SetUnitRegi}, //
	{{"３．手动注释",		"x", ""}, U_UserGrd_GUEST, U_Menu_Ini_ID, U_MENU_TO_PAGE, U_P019_SetNote},  //
	{{"４．关联地址",		"x", ""}, U_UserGrd_GUEST, U_Menu_Ini_ID, U_MENU_TO_PAGE, U_P027_SetAddrRelation},  //
	{{"５．组网设置",		"x", ""}, U_UserGrd_GUEST, U_Menu_Ini_ID, U_MENU_TO_PAGE, U_P024_SetMachNet},  //本机地址和组网模式
	{{"６．语言选择",		"x", ""}, U_UserGrd_GUEST, U_Menu_Ini_ID, U_MENU_TO_PAGE, U_P037_SetLanguage},  //
	{{"７．调试模式选择",		"x", ""}, U_UserGrd_GUEST, U_Menu_Ini_ID, U_MENU_TO_PAGE, U_P038_SetModeFieldDebug},  //
	
	
};


const TMenu CstMenu_4_FactorySet[]=
{
//   *xscn[16];      *xsen[5];  userGrd,        preItemMenuBuf,   nextItemMenuBuf,   page
	//6.出厂设置   
	{{"１．清除存储数据",	"z", ""}, U_UserGrd_GUEST, U_Menu_Ini_ID, U_Menu_3_0_ClrSave_ID, U_MENU_NEXT}, //清登记 联动编程 总线对应 注释  
	{{"２．恢复默认设置",	"z", ""}, U_UserGrd_GUEST, U_Menu_Ini_ID, U_MENU_TO_PAGE, 			U_P015_SetDefault}, //用页面：非联网，1号地址；系统配1回路1专线；自动禁止手动允许；打印全部消息；   
	{{"３．密码管理",		"z", ""}, U_UserGrd_GUEST, U_Menu_Ini_ID, U_Menu_3_1_User_ID, 	U_MENU_NEXT}, //添加，删除，修改。     
	
	
};


const TMenu CstMenu_3_0_ClrSave[]=
{
//   *xscn[16];      *xsen[5];  userGrd,        preItemMenuBuf,   nextItemMenuBuf,   page
	//4.出厂设置 //2.清除存储数据
	{{"１．清登记",		"x", ""}, U_UserGrd_GUEST, U_Menu_4_FactorySet_ID, U_MENU_TO_PAGE, U_P080_ClrLoopRegi},
	{{"２．清联动编程",	"x", ""}, U_UserGrd_GUEST, U_Menu_4_FactorySet_ID, U_MENU_TO_PAGE, U_P077_ClrLinkLogic},
	{{"３．清注释",		"x", ""}, U_UserGrd_GUEST, U_Menu_4_FactorySet_ID, U_MENU_TO_PAGE, U_P078_ClrNote},
	{{"４．清关联地址",	"x", ""}, U_UserGrd_GUEST, U_Menu_4_FactorySet_ID, U_MENU_TO_PAGE, U_P081_ClrAddrRelation},
	 
};

const TMenu CstMenu_3_1_User[]=
{
//   *xscn[16];      *xsen[5];  userGrd,        preItemMenuBuf,   nextItemMenuBuf,   page
	//4.出厂设置 //4.用户管理
	{{"１．修改1级密码",		"x", ""}, U_UserGrd_GUEST, U_Menu_4_FactorySet_ID, U_MENU_TO_PAGE, U_P083_Pssw1_Change},
	{{"２．修改2级密码",		"x", ""}, U_UserGrd_GUEST, U_Menu_4_FactorySet_ID, U_MENU_TO_PAGE, U_P084_Pssw2_Change},
	 
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
* FUNC: //判断菜单是否有效
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
* FUNC: // 菜单字符获取:
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
*  OUT: TMenu[]的条数，和首条的指针。
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
	pMenu = pGetCstBufFirMenu(U_Menu_SysIni_ID); //菜单
	pMenu = pGetCstBufFirMenu(3); //1. 联动
	pMenu = pGetCstBufFirMenu(4); //1. 回路部件
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
	
	if(mSequ >= menuTotal)  //包含 (menuTotal == 0) 的情况
	{
		return FALSE;
	}
	else
	{
		pMenu += mSequ;
		*pRtnMenu = *pMenu;
		return TRUE;
	}
	
	//注：下面的语句只改了局部变量pRtnMenu的值，对调用此函数的指针无影响。
	//pRtnMenu = (TMenu*)(pMenu);
}


/******************************************************************************
* FUNC: //
* 	U_SIGN_bHaveTested

	pMenu = pGetCstMenu(U_Menu_Invalid_ID, 0); // ""	
	pMenu = pGetCstMenu(U_Menu_SysIni_ID, 0); //菜单
	pMenu = pGetCstMenu(U_Menu_SysIni_ID, 1); // ""
	pMenu = pGetCstMenu(3, 0); //1. 联动
	pMenu = pGetCstMenu(3, 1); //2. 用户设置
	pMenu = pGetCstMenu(3, 5); //6. 帮助
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
