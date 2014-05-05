#ifndef __lcdCst_PageFunction_H__
#define __lcdCst_PageFunction_H__
/******************************************************************************
* @file    lcdCst_PageFunction.h
* @author  yx
* @version V1.0
* @date    2012-01-05
* @brief   是 "lcdPg_Page.c" 里的页面声明
* 
*  

#include  "lcdCst_PageFunction.h"
******************************************************************************/

#include  "prjCompileCon.h"
				
/*================= 公有函数声明 ====================================*/
// EX_lcdCst_PageFunction

//页面 基础函数声明
extern void P000_MAIN_Back(void);	//
extern void P000_MAIN_First(void);
extern void P000_MAIN_Usua(void);
extern void P001_FireAlarm_Back(void);	//
extern void P001_FireAlarm_First(void);
extern void P001_FireAlarm_Usua(void);
extern void P002_Monitor_Back(void);	//
extern void P002_Monitor_First(void);
extern void P002_Monitor_Usua(void);
extern void P003_Disable_Back(void);	//
extern void P003_Disable_First(void);
extern void P003_Disable_Usua(void);
extern void P004_Fault_Back(void);	//
extern void P004_Fault_First(void);
extern void P004_Fault_Usua(void);
extern void P005_Link_Back(void);	//
extern void P005_Link_First(void);
extern void P005_Link_Usua(void);
extern void P006_Extg_Back(void);	//
extern void P006_Extg_First(void);
extern void P006_Extg_Usua(void);

extern void P007_Status_Back(void);	//
extern void P007_Status_First(void);
extern void P007_Status_Usua(void);
extern void P008_MENU_Back(void);	//
extern void P008_MENU_First(void);
extern void P008_MENU_Usua(void);
extern void P009_UserLogin_Back(void);	//
extern void P009_UserLogin_First(void);
extern void P009_UserLogin_Usua(void);
extern void P010_ManuActModu_Back(void);	//
extern void P010_ManuActModu_First(void);
extern void P010_ManuActModu_Usua(void);
extern void P011_Help_Back(void);	//
extern void P011_Help_First(void);
extern void P011_Help_Usua(void);
extern void P012_ManuAuto_Back(void);	//
extern void P012_ManuAuto_First(void);
extern void P012_ManuAuto_Usua(void);
extern void P013_SetClock_Back(void);	//
extern void P013_SetClock_First(void);
extern void P013_SetClock_Usua(void);

extern void P014_MiniEvent_Back(void);	//
extern void P014_MiniEvent_First(void);
extern void P014_MiniEvent_Usua(void);

extern void P015_SetDefault_Back(void);	//
extern void P015_SetDefault_First(void);
extern void P015_SetDefault_Usua(void);
extern void P016_AutoRegist_Back(void);	//
extern void P016_AutoRegist_First(void);
extern void P016_AutoRegist_Usua(void);
extern void P017_ManuRegist_Back(void);	//
extern void P017_ManuRegist_First(void);
extern void P017_ManuRegist_Usua(void);
extern void P018_SetDisable_Back(void);	//
extern void P018_SetDisable_First(void);
extern void P018_SetDisable_Usua(void);
extern void P019_SetNote_Back(void);	//
extern void P019_SetNote_First(void);
extern void P019_SetNote_Usua(void);
extern void P020_SetLinkLogic_Back(void);	//
extern void P020_SetLinkLogic_First(void);
extern void P020_SetLinkLogic_Usua(void);

extern void P024_SetMachNet_Back(void);	//
extern void P024_SetMachNet_First(void);
extern void P024_SetMachNet_Usua(void);

extern void P027_SetAddrRelation_Back(void);	//
extern void P027_SetAddrRelation_First(void);
extern void P027_SetAddrRelation_Usua(void);
extern void P028_QrAddrRelation_Back(void);	//
extern void P028_QrAddrRelation_First(void);
extern void P028_QrAddrRelation_Usua(void);




extern void P030_SetUnitRegi_Back(void);	//
extern void P030_SetUnitRegi_First(void);
extern void P030_SetUnitRegi_Usua(void);

extern void P037_SetLanguage_Back(void);	//
extern void P037_SetLanguage_First(void);
extern void P037_SetLanguage_Usua(void);
extern void P038_SetModeFieldDebug_Back(void);	//
extern void P038_SetModeFieldDebug_First(void);
extern void P038_SetModeFieldDebug_Usua(void);
extern void P039_QrModeFieldDebug_Back(void);	//
extern void P039_QrModeFieldDebug_First(void);
extern void P039_QrModeFieldDebug_Usua(void);



extern void P040_QrNowFault_Back(void);	//
extern void P040_QrNowFault_First(void);
extern void P040_QrNowFault_Usua(void);
extern void P041_QrNowDisable_Back(void);	//
extern void P041_QrNowDisable_First(void);
extern void P041_QrNowDisable_Usua(void);
extern void P042_QrLoopLinkLgc_Back(void);	//
extern void P042_QrLoopLinkLgc_First(void);
extern void P042_QrLoopLinkLgc_Usua(void);

extern void P044_QrNote_Back(void);	//
extern void P044_QrNote_First(void);
extern void P044_QrNote_Usua(void);

extern void P047_QrSoftVer_Back(void);	//
extern void P047_QrSoftVer_First(void);
extern void P047_QrSoftVer_Usua(void);
extern void P048_QrUnitRegi_Back(void);	//
extern void P048_QrUnitRegi_First(void);
extern void P048_QrUnitRegi_Usua(void);
extern void P049_QrMachNet_Back(void);	//
extern void P049_QrMachNet_First(void);
extern void P049_QrMachNet_Usua(void);

extern void P052_QrHistAll_Back(void);	//
extern void P052_QrHistAll_First(void);
extern void P052_QrHistAll_Usua(void);
extern void P053_QrHistAlarm_Back(void);	//
extern void P053_QrHistAlarm_First(void);
extern void P053_QrHistAlarm_Usua(void);
extern void P054_QrHistLink_Back(void);	//
extern void P054_QrHistLink_First(void);
extern void P054_QrHistLink_Usua(void);
extern void P055_QrHistFault_Back(void);	//
extern void P055_QrHistFault_First(void);
extern void P055_QrHistFault_Usua(void);
extern void P056_QrHistOpea_Back(void);	//
extern void P056_QrHistOpea_First(void);
extern void P056_QrHistOpea_Usua(void);
extern void P057_QrHistOthers_Back(void);	//
extern void P057_QrHistOthers_First(void);
extern void P057_QrHistOthers_Usua(void);
extern void P058_QrFieldRegist_Back(void);	//
extern void P058_QrFieldRegist_First(void);
extern void P058_QrFieldRegist_Usua(void);
extern void P059_QrAutoManu_Back(void);	//
extern void P059_QrAutoManu_First(void);
extern void P059_QrAutoManu_Usua(void);


extern void P060_TsLoopDevScan_Back(void);	//
extern void P060_TsLoopDevScan_First(void);
extern void P060_TsLoopDevScan_Usua(void);
extern void P061_TsDeteCurve_Back(void);	//
extern void P061_TsDeteCurve_First(void);
extern void P061_TsDeteCurve_Usua(void);
extern void P062_TsLoopData_Back(void);	//
extern void P062_TsLoopData_First(void);
extern void P062_TsLoopData_Usua(void);
extern void P063_TsDeteType_Back(void);	//
extern void P063_TsDeteType_First(void);
extern void P063_TsDeteType_Usua(void);
extern void P064_TsDeteData_Back(void);	//
extern void P064_TsDeteData_First(void);
extern void P064_TsDeteData_Usua(void);
extern void P065_TsCSoundAndLed_Back(void);	//
extern void P065_TsCSoundAndLed_First(void);
extern void P065_TsCSoundAndLed_Usua(void);

extern void P067_TsCKey_Back(void);	//
extern void P067_TsCKey_First(void);
extern void P067_TsCKey_Usua(void);

extern void P068_TsAllHardware_Back(void);	//
extern void P068_TsAllHardware_First(void);
extern void P068_TsAllHardware_Usua(void);

extern void P072_TsCommUnit_Back(void);	//
extern void P072_TsCommUnit_First(void);
extern void P072_TsCommUnit_Usua(void);
extern void P073_TsCommMach_Back(void);	//
extern void P073_TsCommMach_First(void);
extern void P073_TsCommMach_Usua(void);
extern void P077_ClrLinkLogic_Back(void);	//
extern void P077_ClrLinkLogic_First(void);
extern void P077_ClrLinkLogic_Usua(void);
extern void P078_ClrNote_Back(void);	//
extern void P078_ClrNote_First(void);
extern void P078_ClrNote_Usua(void);

extern void P080_ClrLoopRegi_Back(void);	//
extern void P080_ClrLoopRegi_First(void);
extern void P080_ClrLoopRegi_Usua(void);
extern void P081_ClrAddrRelation_Back(void);	//
extern void P081_ClrAddrRelation_First(void);
extern void P081_ClrAddrRelation_Usua(void);

extern void P083_Pssw1_Change_Back(void);	//
extern void P083_Pssw1_Change_First(void);
extern void P083_Pssw1_Change_Usua(void);
extern void P084_Pssw2_Change_Back(void);	//
extern void P084_Pssw2_Change_First(void);
extern void P084_Pssw2_Change_Usua(void);

/*

extern void PXXX_Back(void);	//
extern void PXXX_First(void);
extern void PXXX_Usua(void);

*/



/*=================  ================================================*/


/******************************************************************************
// END :
******************************************************************************/
#endif // __lcdCst_PageFunction_H__

