
#define __lcdPg_Page_C__
/******************************************************************************
* @file    lcdPg_Page.c
* @author  yx
* @version V1.0
* @date    2012-01-05
* @brief   所有的页面函数. 太多，可考虑按类分文件。
* 
*  每个页面的 First() ,自己决定是否用 LcdSw_ClrFullWindow(U_COLOR_BackGroundDefault);
*  所有的保存操作，默认enter键保存。若做了保存确认的提示，则所有的保存都应有提示。
*  有数字输入的页面，退出前，一定调用 FigInput_Stop();
*  
*  P016 自动登记； P058 查询登记地址；
*  P060  回路浏览  
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

#include  "LcdLib_incOut.h" // LCD显示驱动 已测试

#include  "lcdSub_ModeTextFig.h" // 显示 字符或数字 已测试
#include  "lcdSub_InputFig.h" // 页面上输入数字管理. 有代码，未测试；

#include  "lcdPg_Common.h"  // 2个或以上页面可能用到的子函数
#include  "lcdPg_pSelfHdChk.h"

//----- Me:
#include  "canPrtl_iTx.h"  // CAN 协议

/*================= 常数 ============================================*/

/*================= 结构定义 ========================================*/

/*================= 私有结构变量声明 ================================*/

/*================= 公有函数声明 ====================================*/

/*================= 私有函数声明 ====================================*/

/*=================  ================================================*/
		
/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

/******************************************************************************
* 页面: //
* 气体灭火控制器
* 手动: 自动：
* 日期时钟：
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
* 页面: // 火警界面
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
* 页面: //监管事件
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
* 页面: //屏蔽事件
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
* 页面: //故障事件
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
* 页面: //联动事件
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
* 页面: //气灭事件
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
* 页面: //
* 调试模式，手动自动；事件总数；
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
* 页面: //菜单
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
* 页面: //输入密码
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
* 页面: //手动启动模块。 
* 地址范围 ：
	U_SYS_LOOP_MAX 	回路MAX,0无效；
	U_1LOOP_DETE_MAX 	每回路地址范围，0无效；


*      _回路_ _地址
*       key:动作  key:停止
*   提示:当前的地址 动作或停止状态

* 参考 "lcdSub_InputFig.h"
******************************************************************************/

void P010_ManuActModu_Back(void)	//
{
    UNINITENTRY(p010);
}


void P010_ManuActModu_First(void)
{
    INITENTRY(p010);


}

//手动启动页面 按键输入
//	BOOL pg_keyDeal();
void P010_ManuActModu_Usua(void)
{
U8 ii;
    KEYCALL(p010);
	
	ii = pgcom_callb.inputFig[0];
	ii = ii;
}


/******************************************************************************
* 页面: // 帮助
* 暂时 显示生产厂名称
******************************************************************************/
void P011_Help_Back(void)	//
{
    UNINITENTRY(p011);
}
void P011_Help_First(void)
{
    INITENTRY(p011);
   // ShowXYCodeCharRL(1,6,0,"帮助",FALSE);
}
void P011_Help_Usua(void)
{
    KEYCALL(p011);
}
/******************************************************************************
* 页面: // 此功能已去掉，暂时不用
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
* 页面: // 设置日期、时钟
* 	key:输入数字
* 显示当前 日期、时钟：
*  20_ _ 年_ _ 月 _ _ 日
*    _ _ 时_ _ 分 _ _ 秒
*   key:当前时钟 进位到整分
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
    // BOOL SetClock(TEvtClock_st *pClock); // 设置时钟
}


// BOOL GetClock(TEvtClock_st  *pClock); // 读取硬件时钟

	// 显示时钟：已定时读取时钟并判断，若有second变化，置 U_SysSta_bClockChanged 。
// TEvtClock_st *pClock;
	// if(GetSysState(U_SysSta_bClockChanged))
	// {
		// ClrSysState(U_SysSta_bClockChanged);
		
		// GetRamTimer(&pClock);
		// 显示代码
	// }



/******************************************************************************
* 页面: // 
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
* 页面: // 恢复默认设置
* 	恢复默认设置？
*	  key:是   key:退出
*	
******************************************************************************/
void P015_SetDefault_Back(void)	//
{
    UNINITENTRY(p015);
}
void P015_SetDefault_First(void)
{
    INITENTRY(p015);
//    ShowXYCodeCharRL(1,6,0,"恢复默认设置",FALSE);
}
void P015_SetDefault_Usua(void)
{
    KEYCALL(p015);
}
/******************************************************************************
* 页面: // 自动登记
* 	正在登记，已进行 百分比
*		key:停止登记
******************************************************************************/
void P016_AutoRegist_Back(void)	//
{
    UNINITENTRY(p016);
}
void P016_AutoRegist_First(void)
{

    INITENTRY(p016);
	
	ICan_Tx_RegistAll(); // 自动登记

}
void P016_AutoRegist_Usua(void)
{

}

void P016_AutoRegist_ShowPercent(U8 mPercent)
{

}


/******************************************************************************
* 页面: // 手动登记  参考P010
*      _回路_ _地址	  _类型
*   提示: 各种类型定义，暂时提示 手报,感烟，感温，复合，消火栓，输出，输入，声光。
*       key:登记  key:取消
*   提示:当前的地址 登记状态
* 



#define  cNdTy_Hand       1	     //手报
#define  cNdTy_Hydrant    2	     //消火栓按钮
#define  cNdTy_1Out       3	     //单模块输出
#define  cNdTy_Heat       4	     //电子感温
#define  cNdTy_Inter      5	     //缆式接口	
#define  cNdTy_2Out       6		 //双控联动
#define  cNdTy_In_Out     7		 //双控报警
#define  cNdTy_Omnis      8		 //烟温复合
#define  cNdTy_Input      9		 //输入模块 
#define  cNdTy_Display    0x0a	 //层显
#define  cNdTy_Smoke      0x0b	 //感烟
#define  cNdTy_SL         0x0C	 //声光
#define  cNdTy_DetInter   0x0d	 //中继模块
#define  cNdTy_4Out       0x0E	 //四控联动
#define  cNdTy_OnOff      0x0F	 //开关
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
* 页面: // 手动屏蔽地址 参考P010
*      _回路_ _地址
*       key:屏蔽  key:取消
*   提示:当前的地址 屏蔽状态
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
* 页面: // 手动注释
*      _回路_ _地址
* 	注释内容: 注释输入暂时延后做
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
* 页面: // 设置联动编程
*      _回路_ _地址
* 	内容:  暂时延后做
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
* 页面: //设置联网控制器
* 	本机地址: _ _ 
*	主机地址: _ _ 
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
* 页面: //设置本机关联地址
* 	_ _机_ _回路_ _ _地址 ~ _ _ _地址
*	key: 添加  key:删除  key:查看现有关联
* 查看现有关联，与 P028_QrAddrRelation 不是一个界面，二者用户权限不同。
* 可以共用子函数。
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
* 页面: // 查询关联地址
*
******************************************************************************/
void P028_QrAddrRelation_Back(void)	//
{
    UNINITENTRY(p028);
}
void P028_QrAddrRelation_First(void)
{
    INITENTRY(p028);
//    ShowXYCodeCharRL(1,3,0,"查询关联地址",FALSE);
}
void P028_QrAddrRelation_Usua(void)
{
    KEYCALL(p028);
}


/******************************************************************************
* 页面: // 设置语言
* 	暂时不做
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
* 页面: // 设置 现场调试模式
* 	key:调试模式 key:正常工作
*	提示: 当前模式状态
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
* 页面: // 查询 是否现场调试模式
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
* 页面: // 灭火区配置
* 			1     2    3   4 
*状态: 开/关   _    _    _    _
*延时时间(s)  _ _  _ _  _ _  _ _  
*    key: 开   key:关 
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
* 页面: // 查询当前故障
* 与 P004_Fault 类似。
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
* 页面: //// 查询当前屏蔽
* 与 P003_Disable 类似。
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
* 页面: // 查询联动编程
*  暂时不做
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
//    ShowXYCodeCharRL(1,3,0,"查询联动编程",FALSE);

}
void P042_QrLoopLinkLgc_Usua(void)
{
    KEYCALL(p042);
}

/******************************************************************************
* 页面: //查询注释
* 暂时不做
******************************************************************************/
void P044_QrNote_Back(void)	//
{
    UNINITENTRY(p044);
}
void P044_QrNote_First(void)
{
    INITENTRY(p044);
//    ShowXYCodeCharRL(1,3,0,"查询汉字注释",FALSE);
}
void P044_QrNote_Usua(void)
{
    KEYCALL(p044);
}


/******************************************************************************
* 页面: //查询软件版本
*
******************************************************************************/
void P047_QrSoftVer_Back(void)	//
{
    UNINITENTRY(p047);
}
void P047_QrSoftVer_First(void)
{
    INITENTRY(p047);
//    ShowXYCodeCharRL(1,3,0,"查询软件版本",FALSE);
}
void P047_QrSoftVer_Usua(void)
{
    KEYCALL(p047);
}
/******************************************************************************
* 页面: // 查询灭火区设置 参考 P030_SetUnitRegi
*
******************************************************************************/
void P048_QrUnitRegi_Back(void)	//
{
    UNINITENTRY(p048);
}
void P048_QrUnitRegi_First(void)
{
    INITENTRY(p048);
//    ShowXYCodeCharRL(1,3,0,"查询灭火区设置",FALSE);
}
void P048_QrUnitRegi_Usua(void)
{
    KEYCALL(p048);
}
/******************************************************************************
* 页面: //查询联网控制器 参考 P024_SetMachNet
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
* 页面: // 查询历史记录-所有
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
* 页面: // 查询历史记录-火警
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
* 页面: // 查询历史记录-联动
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
* 页面: // 查询历史记录-故障
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
* 页面: // 查询历史记录-操作
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
* 页面: // 查询历史记录-其它
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
* 页面: // 查询 登记
* 		_ _ 回路   key: 确定
* 显示登记地址

* 88 CFireCtrl C11S
* 《101 CWndCtrlCheck》"CCheckAddr.C"void   DisLpReg_CCheckAddr(void)
******************************************************************************/
void P058_QrFieldRegist_Back(void)	//
{
    UNINITENTRY(p058);
}
void P058_QrFieldRegist_First(void)
{
    INITENTRY(p058);
//    ShowXYCodeCharRL(1,3,0,"查询总线登记地址",FALSE);
}
void P058_QrFieldRegist_Usua(void)
{
    KEYCALL(p058);
}


// * 通讯来的文件格式暂不确定，大概:
// 文件长度,总探测数,联动总数,楼显总数, 探测类地址...,联动类地址...,楼显类地址...;
// 气灭里无楼显。
// 已登记的地址按顺序从小大大排列。

// 显示方式为:
// 探测012: 1~5,7,9~15;
// 联动000;
// 地址MAX: U_1LOOP_DETE_MAX
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
* 页面: //查询手动自动
* 显示已登记的区的手动自动  参考 ShowStr_AutoManuNowState();
* 一区:
* 二区:
* 三区:
* 四区:
******************************************************************************/
void P059_QrAutoManu_Back(void)	//
{
    UNINITENTRY(p059);
}
void P059_QrAutoManu_First(void)
{
    INITENTRY(p059);
//    ShowXYCodeCharRL(3,3,0,"查询手动自动状态？",FALSE);
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
* 页面: // 回路浏览  P060_TsLoopDevScan_
* 先做;
*  _ 回路:
* |_________________________> 32   
* |_________________________> 64
* 画地址定位线：地址每8的整数倍在横线下用4像素竖线提示；每4的倍数用2像素。

共64地址，分2行，
最多每地址占 192 / 32 = 6 pix. 按5pix算，32*5=160，余192-160=32 2个汉字的位置。
******************************************************************************/

// 计算坐标X的长度：
TYPE_LCD_XY cacu_devScan_coordinateX(void)
{
    return cacu_devScan_deteX(U_DevScan_AdrHalf-1)
            + U_DevScan_Pix_X_1Point;
}


// 计算各地址的x坐标：
// 例子：(32+1)=(4+5)+(33*5)=185.
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
        dwX += U_DevScan_Pix_X_1Point; // 后面空一个地址的位置

    }else{//the addr between 32~63
        mPoint = mAdr%U_DevScan_AdrHalf;//31
        dwX =  U_DevScan_Pix_X_Start;
        dwX += (mPoint) *  U_DevScan_Pix_X_1Point;
        dwX += U_DevScan_Pix_X_1Point; // 后面空一个地址的位置
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
    //  dwX += U_DevScan_Pix_X_1Point; // 后面空一个地址的位置

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
  //  ShowCodeCharRL(0, 1, "^", FALSE);//∧
    ShowCodeCharRL(0, 0, "mA", FALSE);

    // LcdSw_HvLine(mPixRow_S,mPixLine_S, mPixRow_E,mPixLine_E)
    // 竖线：
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



    // show > sign：
  //  ShowCodeCharRL(4, (U_LCD_LINE_MAX - 1), ">", FALSE);
    //显示横线0，从U_DevScan_Pix_X_Start到
    LcdSw_HvLine(
                U_DevScan_Pix_Y0_Start,
                U_DevScan_Pix_X_Start,
                U_DevScan_Pix_Y0_Start,
                (U_DevScan_Pix_X_Start
                 + cacu_devScan_coordinateX())//y0 as row at horital,x from  x and x+cal
                );
	
    //显示汉字32
    LcdSw_Fig(U_LCD_AXIX_MUM_POS_X_32, (U_LCD_AXIX_NUM_POS_Y), U_DevScan_AdrHalf, 2);


//    ShowCodeCharRL(8, (U_LCD_LINE_MAX - 1), ">", FALSE);
    // 横线2：
    LcdSw_HvLine(
                U_DevScan_Pix_Y1_Start,
                U_DevScan_Pix_X_Start,
                U_DevScan_Pix_Y1_Start,
                (U_DevScan_Pix_X_Start
                 + cacu_devScan_coordinateX())
                );
    //显示汉字64
    LcdSw_Fig(U_LCD_AXIX_MUM_POS_X_64, (U_LCD_AXIX_NUM_POS_Y), U_DevScan_AdrMax, 2);

    for(iiy=0;iiy<6;iiy++){
        //显示纵坐标，获取6个坐标即可
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

// 地址的位置提示：画地址定位线：
/*****************************************************************************
*FUNC:paint the locate line at the horictal line，the first and the end must be careful
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




// 画地址定位线：判断是 8的倍数，或 4的倍数。
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




// 显示电流值-1个地址：

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
* 页面: // P060
******************************************************************************/


// 画 电流:
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
* 页面: // 回路浏览
******************************************************************************/


// 显示电流值-1个地址：
void dw_devScan_current_one(U32 mAdr, U8 mCurrent);
// 地址的位置提示：画地址定位线：
void dw_devScan_adrPrompt(void);

// 画地址定位线：判断是 8的倍数，或 4的倍数。
void dw_devScan_adrPrpt_one(U32 mAdr);
// 计算坐标X的长度：
TYPE_LCD_XY cacu_devScan_coordinateX(void);
// 计算各地址的x坐标：33=(4+5)+(33*5)=185.
TYPE_LCD_XY cacu_devScan_deteX(U32 mAdr);


TYPE_LCD_XY cacu_devScan_deteY(U32 mAdr);
// 画坐标轴：
void dw_devScan_axis(void);


// 画 提示坐标：
void dw_devScan_coordinate(void);
// 画 电流:
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
* 页面: // 显示 模拟量曲线
*  _回路_ _ _地址: _ _ _ (显示当前值)
* |
* |_________________________>
* 把当前值用一个点显示，高度对应值的大小，最大128.
* 每得到一个新的值，X轴向上右移一个显示位置；若满，从左侧开始刷新，同时把其右侧16个像素清掉；
* 看效果，视觉上不舒服可以改，比如每次得到值，用横向2个像素表示；
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
* 页面: // 回路参数查询
*  	_回路:
*   回路背景电流:
*  回路24V时电流:
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
* 页面: // 现场设备类型状态
*  	_回路_ _ _地址:
*   部件类型:
*   部件状态:
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
* 页面: //
*  _回路_ _ _地址
*  十六进制数据，顺序显示； 若满，回头刷新显示，并清除其后的2个字节。
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
* 页面: // 自检；液晶扫屏；跑马灯；扬声器按顺序几种音调。
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
* 页面: // 测试按键。
* 在屏幕上按照实际键盘顺序画标志；若某按键按下，则变色；
* 界面6秒无按键输入，则自动退出到菜单
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

// 按键检测时的处理：
void KeyCheck_ShowInLcd(U8 mKey)
{

}


/******************************************************************************
* 页面: // 所有硬件的能检测的状态，在LCD上显示
* 杨旭 做
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
* 页面: // 测试 通讯-iCan;
* 接收1区帧数:
* 接收2区帧数:
* 接收3区帧数:
* 接收4区帧数:
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
* 页面: // 测试 通讯-eCan;
* 接收主机帧数:
* 其他控制器若在线，显示接收帧数；
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
* 页面: //清除联动编程
*
******************************************************************************/
void P077_ClrLinkLogic_Back(void)	//
{
    UNINITENTRY(p077);
}
void P077_ClrLinkLogic_First(void)
{
    INITENTRY(p077);
//    ShowCodeCharRL(3,5,"清联动编程",FALSE);
}
void P077_ClrLinkLogic_Usua(void)
{
    KEYCALL(p077);
}

void P077_ClrLinkLogic_showPercent(U8 mPercent)
{

}

/******************************************************************************
* 页面: //清除注释
*
******************************************************************************/
void P078_ClrNote_Back(void)	//
{
    UNINITENTRY(p078);
}
void P078_ClrNote_First(void)
{
    INITENTRY(p078);
//    ShowCodeCharRL(3,5,"清注释",FALSE);
}
void P078_ClrNote_Usua(void)
{
    KEYCALL(p078);
}
void P078_ClrNote_showPercent(U8 mPercent)
{

}


/******************************************************************************
* 页面: //清除回路登记
*
******************************************************************************/
void P080_ClrLoopRegi_Back(void)	//
{
    UNINITENTRY(p080);
}
void P080_ClrLoopRegi_First(void)
{
    INITENTRY(p080);
//    ShowCodeCharRL(4,5,"清除回路登记",FALSE);
}
void P080_ClrLoopRegi_Usua(void)
{
    KEYCALL(p080);
}
void P080_ClrLoopRegi_showPercent(U8 mPercent)
{

}

/******************************************************************************
* 页面: //清除关联地址
*
******************************************************************************/
void P081_ClrAddrRelation_Back(void)	//
{
    UNINITENTRY(p081);
}
void P081_ClrAddrRelation_First(void)
{
    INITENTRY(p081);
//    ShowCodeCharRL(4,5,"清除关联地址",FALSE);
}
void P081_ClrAddrRelation_Usua(void)
{
    KEYCALL(p081);
}

void P081_ClrAddrRelation_showPercent(U8 mPercent)
{

}

/******************************************************************************
* 页面: // 修改1级密码
* 输入的密码用 * 显示；

* 原有密码: _ _ _
* 新设密码: _ _ _
* 再次确认: _ _ _
******************************************************************************/
void P083_Pssw1_Change_Back(void)	//
{
    UNINITENTRY(p083);
}
void P083_Pssw1_Change_First(void)
{
    INITENTRY(p083);
//    ShowCodeCharRL(4,5,"修改1级密码",FALSE);
}
void P083_Pssw1_Change_Usua(void)
{
    KEYCALL(p083);
}
/******************************************************************************
* 页面: // 修改2级密码
* 输入的密码用 * 显示；

* 原有密码: _ _ _ _ _ _
* 新设密码: _ _ _ _ _ _
* 再次确认: _ _ _ _ _ _
*
******************************************************************************/
void P084_Pssw2_Change_Back(void)	//
{
    UNINITENTRY(p084);
}
void P084_Pssw2_Change_First(void)
{
    INITENTRY(p084);
//    ShowCodeCharRL(4,5,"修改2级密码",FALSE);
}
void P084_Pssw2_Change_Usua(void)
{
    KEYCALL(p084);
}

/******************************************************************************
* 页面: //
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

