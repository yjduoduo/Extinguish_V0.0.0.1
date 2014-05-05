
#define __lcdCst_Page_C__
/******************************************************************************
* @file    lcdCst_Page.c
* @author  yx
* @version V1.0
* @date    2012-01-05
* @brief   各页面的 _Back, _First, _Usua 函数 const.
* 

******************************************************************************/
#include  "lcdCst_Page.h"

//#include "..\\s00Prj\\incFile.h"	

//-----------------   --------------------------------// 
// #include  "tsk_lcd_incIn.h"


#include  "lcdCst_PageFunction.h"
#include  "lcdCst_PageNum.h" 
//----- Me:

/*================= 常数 ============================================*/

/*================= 结构体定义 ======================================*/

//#pragma pack(4)
typedef struct TPage_st //页面事件
{
	PAGEWORD index;  //页面号
	PAGEWORD backto;  //返回的页面  //MAX_PAGE表示返回菜单; 在返回的是页面时用。U_P008_MENU表示返回到菜单。
	void (*PageBack)(void);	//退出页面前的处理
    void (*PageFirst)(void);
	void (*PageUsua)(void);
}TPage;
//#pragma pack()

/*================= 公有结构变量声明 ================================*/
const TPage stPage[MAX_PAGE];

/*================= 私有结构变量声明 ================================*/
//static PAGEWORD  pageIndex = 0;
static PAGEWORD  vPagePractMax = 0;  // 实际定义的 pageMax.

/*================= 公有函数声明 ====================================*/
//void (const *CurrPage)(void);
void (*CurrPage)(void);
/*
    PageIndex = stPage[PageIndex].PageBack;
    CurrPage = stPage[PageIndex].PageFirst;    
    (*CurrPage)();
*/				  


/*================= 私有函数声明 ====================================*/

/*=================  ================================================*/

/*=================  ================================================*/

/******************************************************************************
* FUNC: // 检查 stPage[]的定义是否有误。
*   IN:
*  OUT: vPagePractMax
******************************************************************************/
PAGEWORD GetCstPageDef_PractMax(void)
{
	return vPagePractMax;
}

BOOL bPageNumFewThanPractMax(PAGEWORD mPage)
{
	return (mPage < vPagePractMax);
}

BOOL LcdCstPage_CheckCst(void)
{
PAGEWORD mPageNum;

	for(mPageNum=0; mPageNum<MAX_PAGE; mPageNum++)
	{
		if(stPage[mPageNum].index != mPageNum)
		{
			break;
		}
	}
	
	vPagePractMax = mPageNum;
	
	if(mPageNum >= MAX_PAGE)
	{
		vPagePractMax = MAX_PAGE;
		return TRUE;
	}
	else
	{
		for(; mPageNum<MAX_PAGE; mPageNum++)
		{
			if( (stPage[mPageNum].index > 0)
			  &&(stPage[mPageNum].index < MAX_PAGE))
			{
				// 之后的都应是无效页面。若定义有1~(max-1),是错的。
				return FALSE; 
			}
		}
		return TRUE;
	}
}




/******************************************************************************
* FUNC: //
*   IN:
*  OUT:
* Master: lcdPg_aSchedu.c
******************************************************************************/

void LcdCstPage_Back(PAGEWORD mPageNum)
{
	if(bPageNumFewThanPractMax(mPageNum))
	{
		CurrPage = stPage[mPageNum].PageBack;    
		(*CurrPage)();	
	}	
}

void LcdCstPage_First(PAGEWORD mPageNum)
{
	if(bPageNumFewThanPractMax(mPageNum))
	{
		CurrPage = stPage[mPageNum].PageFirst;    
		(*CurrPage)();	
	}	
}

void LcdCstPage_Usual(PAGEWORD mPageNum)
{
	if(bPageNumFewThanPractMax(mPageNum))
	{
		CurrPage = stPage[mPageNum].PageUsua;    
		(*CurrPage)();	
	}	
}

/******************************************************************************
* FUNC: //
*   IN:
*  OUT:
******************************************************************************/
// 返回的 back PageNum:
PAGEWORD LcdCstPage_GetBackPgNum(PAGEWORD mPageNum)
{
	if(bPageNumFewThanPractMax(mPageNum))
	{
		return stPage[mPageNum].backto;
	}	
	else
	{
		return U_PageNum_Default;
	}
}


/******************************************************************************
* NAME: 
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

const TPage stPage[MAX_PAGE] =  //注意index要与实际地址对应
{	 
    {U_P000_MAIN, 		U_P000_MAIN,(*P000_MAIN_Back),(*P000_MAIN_First),(*P000_MAIN_Usua)},	//主页面
	{U_P001_FireAlarm,	U_P000_MAIN,(*P001_FireAlarm_Back),(*P001_FireAlarm_First),(*P001_FireAlarm_Usua)},   
	
	
	{U_P002_Monitor,	U_P000_MAIN,(*P002_Monitor_Back),(*P002_Monitor_First),(*P002_Monitor_Usua)},	  // 
	{U_P003_Disable,	U_P000_MAIN,(*P003_Disable_Back),(*P003_Disable_First),(*P003_Disable_Usua)},	  // 
	{U_P004_Fault,		U_P000_MAIN,(*P004_Fault_Back),  (*P004_Fault_First),  (*P004_Fault_Usua)},	  // 
	{U_P005_Link,		U_P000_MAIN,(*P005_Link_Back),   (*P005_Link_First),   (*P005_Link_Usua)},	  //
	{U_P006_Extg,		U_P000_MAIN,(*P006_Extg_Back),   (*P006_Extg_First),   (*P006_Extg_Usua)},	  //
	{U_P007_Status,		U_P000_MAIN,(*P007_Status_Back), (*P007_Status_First), (*P007_Status_Usua)},	  // 
	
	{U_P008_MENU,		U_P000_MAIN,(*P008_MENU_Back),		(*P008_MENU_First),		(*P008_MENU_Usua)},	  // 
	{U_P009_UserLogin,	U_P008_MENU,(*P009_UserLogin_Back),	(*P009_UserLogin_First),(*P009_UserLogin_Usua)},	  // 
	
	{U_P010_ManuActModu,	U_P008_MENU,(*P010_ManuActModu_Back),(*P010_ManuActModu_First),(*P010_ManuActModu_Usua)},	  // 
	{U_P011_Help,			U_P000_MAIN,(*P011_Help_Back),		(*P011_Help_First),			(*P011_Help_Usua)},	  // 
	{U_P012_ManuAuto,		U_P008_MENU,(*P012_ManuAuto_Back),	(*P012_ManuAuto_First),		(*P012_ManuAuto_Usua)},	  // 
	{U_P013_SetClock,		U_P008_MENU,(*P013_SetClock_Back),	(*P013_SetClock_First),		(*P013_SetClock_Usua)},	  // 
	{U_P014_MiniEvent,	U_P000_MAIN,(*P014_MiniEvent_Back),   (*P014_MiniEvent_First),   (*P014_MiniEvent_Usua)},	  //
	{U_P015_SetDefault,		U_P008_MENU,(*P015_SetDefault_Back),(*P015_SetDefault_First),	(*P015_SetDefault_Usua)},	  // 
	{U_P016_AutoRegist,		U_P008_MENU,(*P016_AutoRegist_Back),(*P016_AutoRegist_First),	(*P016_AutoRegist_Usua)},	  // 
	{U_P017_ManuRegist,		U_P008_MENU,(*P017_ManuRegist_Back),(*P017_ManuRegist_First),	(*P017_ManuRegist_Usua)},	  // 
	{U_P018_SetDisable,		U_P008_MENU,(*P018_SetDisable_Back),(*P018_SetDisable_First),	(*P018_SetDisable_Usua)},	  // 
	{U_P019_SetNote,		U_P008_MENU,(*P019_SetNote_Back),	(*P019_SetNote_First),		(*P019_SetNote_Usua)},	  // 
	{U_P020_SetLinkLogic,	U_P008_MENU,(*P020_SetLinkLogic_Back),(*P020_SetLinkLogic_First),(*P020_SetLinkLogic_Usua)},	  // 
	{U_P021_P,	},	  // 
	{U_P022_P,	},	  // 
	{U_P023_P,},	  // 
	{U_P024_SetMachNet,		U_P008_MENU,(*P024_SetMachNet_Back),(*P024_SetMachNet_First),	(*P024_SetMachNet_Usua)},	  // 
	{U_P025_P,},	  // 
	{U_P026_P,},
	{U_P027_SetAddrRelation,U_P008_MENU,(*P027_SetAddrRelation_Back),(*P027_SetAddrRelation_First),	(*P027_SetAddrRelation_Usua)},
	{U_P028_QrAddrRelation, U_P008_MENU,(*P028_QrAddrRelation_Back),(*P028_QrAddrRelation_First),	(*P028_QrAddrRelation_Usua)},
	{U_P029_P,},	  // 
	{U_P030_SetUnitRegi,	U_P008_MENU,(*P030_SetUnitRegi_Back),	(*P030_SetUnitRegi_First),	(*P030_SetUnitRegi_Usua)},	  // 
	
	{U_P031_P,},	  //
	{U_P032_P,},	  //
	{U_P033_P,},	  //
	{U_P034_P,},	  //
	{U_P035_P,},	  //
	{U_P036_P,},	  //
	
	{U_P037_SetLanguage,	U_P008_MENU,(*P037_SetLanguage_Back),	(*P037_SetLanguage_First),(*P037_SetLanguage_Usua)},
	{U_P038_SetModeFieldDebug,	U_P008_MENU,(*P038_SetModeFieldDebug_Back),	(*P038_SetModeFieldDebug_First),(*P038_SetModeFieldDebug_Usua)},
	{U_P039_QrModeFieldDebug,	U_P008_MENU,(*P039_QrModeFieldDebug_Back),	(*P039_QrModeFieldDebug_First),(*P039_QrModeFieldDebug_Usua)},
	{U_P040_QrNowFault,		U_P008_MENU,(*P040_QrNowFault_Back),	(*P040_QrNowFault_First),	(*P040_QrNowFault_Usua)},	  // 
	{U_P041_QrNowDisable,	U_P008_MENU,(*P041_QrNowDisable_Back),	(*P041_QrNowDisable_First),	(*P041_QrNowDisable_Usua)},	  // 
	{U_P042_QrLoopLinkLgc,	U_P008_MENU,(*P042_QrLoopLinkLgc_Back),	(*P042_QrLoopLinkLgc_First),(*P042_QrLoopLinkLgc_Usua)},	  // 
	{U_P043_P,},	  // 
	{U_P044_QrNote,			U_P008_MENU,(*P044_QrNote_Back),		(*P044_QrNote_First),		(*P044_QrNote_Usua)},	  // 
	{U_P045_P,},	  // 
	{U_P046_P,},	  // 
	{U_P047_QrSoftVer,		U_P008_MENU,(*P047_QrSoftVer_Back),		(*P047_QrSoftVer_First),	(*P047_QrSoftVer_Usua)},	  // 
	{U_P048_QrUnitRegi,		U_P008_MENU,(*P048_QrUnitRegi_Back),	(*P048_QrUnitRegi_First),	(*P048_QrUnitRegi_Usua)},	  // 
	{U_P049_QrMachNet,		U_P008_MENU,(*P049_QrMachNet_Back),		(*P049_QrMachNet_First),	(*P049_QrMachNet_Usua)},	  // 
	{U_P050_P,},	  // 
	{U_P051_P,},	  // 
	{U_P052_QrHistAll,		U_P008_MENU,(*P052_QrHistAll_Back),		(*P052_QrHistAll_First),	(*P052_QrHistAll_Usua)},	  // 
	{U_P053_QrHistAlarm,	U_P008_MENU,(*P053_QrHistAlarm_Back),	(*P053_QrHistAlarm_First),	(*P053_QrHistAlarm_Usua)},	  // 
	{U_P054_QrHistLink,		U_P008_MENU,(*P054_QrHistLink_Back),	(*P054_QrHistLink_First),	(*P054_QrHistLink_Usua)},	  // 
	{U_P055_QrHistFault,	U_P008_MENU,(*P055_QrHistFault_Back),	(*P055_QrHistFault_First),	(*P055_QrHistFault_Usua)},	  // 
	{U_P056_QrHistOpea,		U_P008_MENU,(*P056_QrHistOpea_Back),	(*P056_QrHistOpea_First),	(*P056_QrHistOpea_Usua)},	  //
	{U_P057_QrHistOthers,	U_P008_MENU,(*P057_QrHistOthers_Back),	(*P057_QrHistOthers_First),	(*P057_QrHistOthers_Usua)},	  // 
	{U_P058_QrFieldRegist,	U_P008_MENU,(*P058_QrFieldRegist_Back),	(*P058_QrFieldRegist_First),	(*P058_QrFieldRegist_Usua)},	  // 
	{U_P059_QrAutoManu,		U_P008_MENU,(*P059_QrAutoManu_Back),	(*P059_QrAutoManu_First),	(*P059_QrAutoManu_Usua)},	  // 
	{U_P060_TsLoopDevScan,	U_P008_MENU,(*P060_TsLoopDevScan_Back),	(*P060_TsLoopDevScan_First),	(*P060_TsLoopDevScan_Usua)},	  // 
	{U_P061_TsDeteCurve,	U_P008_MENU,(*P061_TsDeteCurve_Back),	(*P061_TsDeteCurve_First),		(*P061_TsDeteCurve_Usua)},	  // 
	{U_P062_TsLoopData,		U_P008_MENU,(*P062_TsLoopData_Back),	(*P062_TsLoopData_First),		(*P062_TsLoopData_Usua)},	  // 
	{U_P063_TsDeteType,		U_P008_MENU,(*P063_TsDeteType_Back),	(*P063_TsDeteType_First),		(*P063_TsDeteType_Usua)},	  // 
	{U_P064_TsDeteData,		U_P008_MENU,(*P064_TsDeteData_Back),	(*P064_TsDeteData_First),		(*P064_TsDeteData_Usua)},	  // 
	{U_P065_TsCSoundAndLed,	U_P008_MENU,(*P065_TsCSoundAndLed_Back),(*P065_TsCSoundAndLed_First),	(*P065_TsCSoundAndLed_Usua)},	  // 
	{U_P066_P,},	  //
	{U_P067_TsCKey,			U_P008_MENU,(*P067_TsCKey_Back),		(*P067_TsCKey_First),			(*P067_TsCKey_Usua)},	  // 
	{U_P068_TsAllHardware,	U_P008_MENU,(*P068_TsAllHardware_Back),	(*P068_TsAllHardware_First),	(*P068_TsAllHardware_Usua)},
	{U_P069_P,},	  //
	{U_P070_P,},	  //
	{U_P071_P,},	  //
	{U_P072_TsCommUnit,		U_P008_MENU,(*P072_TsCommUnit_Back),	(*P072_TsCommUnit_First),		(*P072_TsCommUnit_Usua)},	  // 
	{U_P073_TsCommMach,		U_P008_MENU,(*P073_TsCommMach_Back),	(*P073_TsCommMach_First),		(*P073_TsCommMach_Usua)},	  // 
	{U_P074_P,},	  // 
	{U_P075_P,},	  // 
	{U_P076_P,},	  // 
	{U_P077_ClrLinkLogic,	U_P008_MENU,(*P077_ClrLinkLogic_Back),	(*P077_ClrLinkLogic_First),		(*P077_ClrLinkLogic_Usua)},	  // 
	{U_P078_ClrNote,		U_P008_MENU,(*P078_ClrNote_Back),		(*P078_ClrNote_First),			(*P078_ClrNote_Usua)},	  // 
	{U_P079_P, },	  // 
	{U_P080_ClrLoopRegi,	U_P008_MENU,(*P080_ClrLoopRegi_Back),	(*P080_ClrLoopRegi_First),		(*P080_ClrLoopRegi_Usua)},
	{U_P081_ClrAddrRelation,	U_P008_MENU,(*P081_ClrAddrRelation_Back),	(*P081_ClrAddrRelation_First),		(*P081_ClrAddrRelation_Usua)},
	{U_P082_P,},	  // 
	{U_P083_Pssw1_Change,		U_P008_MENU,(*P083_Pssw1_Change_Back),		(*P083_Pssw1_Change_First),		(*P083_Pssw1_Change_Usua)},	  // 
	{U_P084_Pssw2_Change,		U_P008_MENU,(*P084_Pssw2_Change_Back),	(*P084_Pssw2_Change_First),		(*P084_Pssw2_Change_Usua)},	  // 
	{U_P085_P,},	// 
	{U_P086_P,	},	  // 
	
	/*
	{U_PXXX,		U_P008_MENU,(*PXXX_Back),(*PXXX_First),(*PXXX_Usua)},
	*/
	//禁止空号，禁止重号。必须按顺序排。
	
	// lastOne:
	{MAX_PAGE, 		U_P000_MAIN,(*P000_MAIN_Back),(*P000_MAIN_First),(*P000_MAIN_Usua)},	//主页面
	
};

/******************************************************************************
* NAME: 
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/


/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

