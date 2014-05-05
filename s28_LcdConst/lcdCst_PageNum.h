#ifndef __lcdCst_PageNum_H__
#define __lcdCst_PageNum_H__
/******************************************************************************
* @file    lcdCst_PageNum.h
* @author  yx
* @version V1.0
* @date    2012-01-05
* @brief   页面号 排布
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


/*================= 页面 =======================================*/
#define U_P000_MAIN			0	//
#define U_P001_FireAlarm		1	//火警
#define U_P002_Monitor			2	//监管
#define U_P003_Disable			3	//屏蔽
#define U_P004_Fault			4	//故障
#define U_P005_Link				5	//动作
#define U_P006_Extg				6	//气灭

#define U_PageNumEvent_MIN		(U_P001_FireAlarm)
#define U_PageNumEvent_MAX		(U_P006_Extg + 1)
#define U_P007_Status			7	//状态3t	

#define U_P008_MENU			8	//
#define U_P009_UserLogin	9	//登录

#define U_P010_ManuActModu 			10 //联动 手动启动
#define U_P011_Help			11 //帮助
#define U_P012_ManuAuto		12 //手动自动	
#define U_P013_SetClock		13 //时钟	
#define U_P014_MiniEvent		14 //
#define U_P015_SetDefault		15 //恢复默认设置	
#define U_P016_AutoRegist		16 //自动登记	
#define U_P017_ManuRegist		17 //手动登记	
#define U_P018_SetDisable		18 //设置屏蔽	
#define U_P019_SetNote			19 //手动注释
	
#define U_P020_SetLinkLogic		20 //联动编程
#define U_P021_P		21 //
#define U_P022_P		22 //
#define U_P023_P		23 //

#define U_P024_SetMachNet		24 //联网
#define U_P025_P		25 //	
#define U_P026_P		26 //			
#define U_P027_SetAddrRelation	27 //关联地址
#define U_P028_QrAddrRelation	28 // 关联地址	
#define U_P029_P				29 //

#define U_P030_SetUnitRegi		30 //单元配置	
#define U_P031_P		31 //
#define U_P032_P		32 //
#define U_P033_P		33 //
#define U_P034_P		34 //
#define U_P035_P		35 //
#define U_P036_P		36 //
#define U_P037_SetLanguage		37 //语言		
#define U_P038_SetModeFieldDebug	38 //现场调试模式
#define U_P039_QrModeFieldDebug 	39 //现场调试模式


#define U_P040_QrNowFault		40 //当前故障	
#define U_P041_QrNowDisable	41 //当前屏蔽	
#define U_P042_QrLoopLinkLgc	42 //回路的联动编程	
#define U_P043_P				43 //
#define U_P044_QrNote			44 //查询注释	
#define U_P045_P		45 //
#define U_P046_P		46 //

#define U_P047_QrSoftVer		47 //软件版本	
#define U_P048_QrUnitRegi		48 //单元配置	
#define U_P049_QrMachNet		49 //联网	
#define U_P050_P				50 //
#define U_P051_P				51 //
#define U_P052_QrHistAll		52 //历史-全部	
#define U_P053_QrHistAlarm		53 //历史-	
#define U_P054_QrHistLink		54 //历史-
#define U_P055_QrHistFault		55 //历史-	
#define U_P056_QrHistOpea		56 //历史-	
#define U_P057_QrHistOthers		57 //历史-		
#define U_P058_QrFieldRegist	58 //查询 登记
#define U_P059_QrAutoManu		59 //查询 手动 自动

#define U_P060_TsLoopDevScan	60 //回路浏览	
#define U_P061_TsDeteCurve		61 //模拟曲线	
#define U_P062_TsLoopData		62 //回路参数查询	
#define U_P063_TsDeteType		63 //现场部件类型	
#define U_P064_TsDeteData		64 //现场部件数据	
#define U_P065_TsCSoundAndLed	65 //声光自检	
#define U_P066_P			66 //
#define U_P067_TsCKey			67 //按键检测	
#define U_P068_TsAllHardware	68 //测试 所有硬件
#define U_P069_P			69 //
#define U_P070_P			70 //	
#define U_P071_P			71 //
#define U_P072_TsCommUnit		72 //显示单元通讯情况	
#define U_P073_TsCommMach		73 //显示机器通讯情况		
#define U_P074_P				74 //		
#define U_P075_P				75 //		
#define U_P076_P				76 //

#define U_P077_ClrLinkLogic	77 //清除	
#define U_P078_ClrNote			78 //	
#define U_P079_P	79 //	
#define U_P080_ClrLoopRegi		80 //	
#define U_P081_ClrAddrRelation	81 //关联地址		
#define U_P082_P				82 //
	
#define U_P083_Pssw1_Change			83 //密码管理	
#define U_P084_Pssw2_Change			84 //	
#define U_P085_P		85 //	
#define U_P086_P			86 //	
							
#define U_PXXX			87	//		
//禁止空号，禁止重号。必须按顺序排。
			
/*=================  ================================================*/
#define MAX_PAGE        100	 

#define U_PageNum_Default			0	//

/******************************************************************************
// END :
******************************************************************************/
#endif // __lcdCst_PageNum_H__

