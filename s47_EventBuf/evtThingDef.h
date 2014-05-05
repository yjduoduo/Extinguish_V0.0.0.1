#ifndef __evtThingDef_H__
#define __evtThingDef_H__
/******************************************************************************
* @file    evtThingDef.h
* @author  yx
* @version V1.1_1
* @date    2013-09-11
* @brief   事件thing类型定义
* 
* V1.1_2， 2013-10-23 
*		add:  U_SpvsRstr_EVT， U_FaultDeteType_EVT 
*		add:  U_ModuRun_EVT,  U_ModuStop_EVT
* V1.1_1， 2013-09-13 
		bEvtValid()
* V1.1， 2013-09-11 填 灭火类事件。
* V1.0， 2012-01-05

#include  "evtThingDef.h"
******************************************************************************/

#include  "prjCompileCon.h"
/*================= extern ============================================*/

/*================= 常数 ============================================*/
// TEvtTrans_st ->thing: 事件类型

// 改动 涉及：EvtThing_toHistClsBits();
 

enum emevtThingDef
{
	U_EVT_MIN,
//----- 报警 ------------------------------------
	U_Ala_EVT_Min = 2, // <
	U_Alarm_EVT = 3,
	U_Ala_EVT_Max = 5, // >
//----- 监管 ------------------------------------
	U_Spvs_EVT_Min = 5, // <
	U_Spvs_EVT = 6,
	U_SpvsRstr_EVT = 7,
	U_Spvs_EVT_Max = 9, // >
	
//----- 故障 ------------------------------------
	U_Fau_EVT_Min = 10, // <
	
	U_Fault_EVT = 11,
	U_FaultRstr_EVT = 12,

	U_FaultDeteType_EVT = 13, // 设备类型错误
	U_FaultProtocalVersion_EVT = 14, // 协议不匹配

	
	U_Fau_EVT_Max = 19, // >
//----- 联动 ------------------------------------
	U_Link_EVT_Min = 30, // <
	
	U_ExtgEvt_EVT = 31, 	//灭火类事件
	U_ExtgEvt_Min = 31, 	//灭火类事件
	U_ExtgCircleRun_EVT, 	//灭火 序列流程 启动, 启动后有sec计时。
	U_ExtgCircleSec_EVT, 	//灭火 序列流程 剩余秒数
	U_ExtgCircleStop_EVT, 	//灭火 序列流程 停止
	U_ExtgAnnuRun_EVT, 		//灭火 声光启动
	U_ExtgAnnuStop_EVT, 	//灭火 声光停止
	U_ExtgAuxRun_EVT, 		//灭火 辅助设备动作
	U_ExtgAuxStop_EVT, 		//灭火 辅助设备停止
	U_ExtgSprayRun_EVT, 	//灭火 喷洒动作
	U_ExtgSprayStop_EVT, 	//灭火 喷洒停止
	U_ExtgSprayAck_EVT, 	//灭火 喷洒反馈
	U_ExtgSprayAckRstr_EVT, //灭火 喷洒反馈撤销
	U_ExtgSprayMissAck_EVT, //灭火 喷洒反馈缺失
	U_ExtgEvt_Max = 59, 	//灭火类事件
	
	U_ModuEvt_EVT = 60,
	U_ModuEvt_Min = 60,
	U_ModuManuRun_EVT,
	U_ModuManuStop_EVT,
	U_ModuAutoRun_EVT,
	U_ModuAutoRunDelay_EVT,		//延时启动
	U_ModuRunDelayCancel_EVT,	//延时启动撤销
	U_ModuAutoStop_EVT,	
	U_ModuRun_EVT,
	U_ModuStop_EVT,		//
	
	U_ModuAck_EVT = 80,			//反馈
	U_ModuAckRstr_EVT,		//反馈撤销
	U_ModuMissAck_EVT,		//反馈缺失
	U_ModuEvt_Max = 99,
	
	U_Link_EVT_Max = 99, // >
	
//----- 操作 ------------------------------------
	U_Opea_EVT_Min = 120, // <
	
	U_Reset_EVT,
	U_PwrOff_EVT,
	
	U_Disable_Min = 146,
	U_Disable_EVT = 146,
	U_DisableRstr_EVT,
	U_Disable_Max = 149,
	U_Opea_EVT_Max = 149, // >
//----- 超级记录 ------------------------------------
	U_Super_EVT_Min = 150, // <
	
	U_Super_FlsErase_EVT,
	U_Super_FlsCopyRenew_EVT,
	
	U_Super_EVT_Max = 179, // >
//-----   ------------------------------------
	
	U_EVT_INVALID = 255,
//-----------------------------------------
};
	
	
#define bEvtValid(_thing_)   ((_thing_ > U_EVT_MIN) \
							&&(_thing_ < U_EVT_INVALID))

/*
#define U_Alarm_EVT 			0x0  //
#define U_DeteFault_EVT 		0x1  //
#define U_DeteFaultRstr_EVT	0x2  //
#define U_BoardModuFault_EVT 		0x059  //回路故障，多线/灭火路故障
#define U_BoardModuFaultRstr_EVT		0x05A  //
#define U_PnFault_EVT 		0x1  //盘故障
#define U_PnFaultRstr_EVT	0x2  //


*/




/*
//灭火类事件 进一步分类
#define U_ExtgFur_Fault_EVT		0x01 //线路故障	//有继续分故障类型
#define U_ExtgFur_FaultRstr_EVT		0x02 //线路故障恢复	//有继续分故障类型
#define U_ExtgFur_SprayFeed_EVT		0x03 //喷洒回答
#define U_ExtgFur_SprayFeedRstr_EVT	0x04 //喷洒回答撤消
#define U_ExtgFur_AnnuRun_EVT		0x05 //声光启动
#define U_ExtgFur_AnnuStop_EVT		0x06 //声光停止
#define U_ExtgFur_DevRun_EVT		0x07 //相关设备动作
#define U_ExtgFur_DevStop_EVT		0x08 //相关设备停止
#define U_ExtgFur_ZoneRun_EVT		0x09 //防火区动作
#define U_ExtgFur_ZoneStop_EVT		0x0A //防火区停止
#define U_ExtgFur_SprayRun_EVT		0x0B //喷洒动作
#define U_ExtgFur_SprayDelayTmr_EVT	0x0C //延迟时间，本机的不显示
									//0D 空
#define U_ExtgFur_RemoteStopRstr_EVT 0x0E //远程停止动作撤销

//灭火类事件 故障分类
#define U_ExtgFault_Modu_EVT		0x80 //模块故障
#define U_ExtgFault_Annu_EVT		0x40 //声光故障
#define U_ExtgFault_Delay_EVT		0x20 //延迟故障
#define U_ExtgFault_Dev_EVT		0x10 //辅助设备故障
#define U_ExtgFault_SprayRun_EVT		0x08 //喷洒输出故障
#define U_ExtgFault_SprayFeed_EVT		0x04 //喷洒回答故障
#define U_ExtgFault_RemoteRun_EVT		0x02 //远程启动故障
#define U_ExtgFault_RemoteStop_EVT		0x01 //远程停止故障
//灭火类事件 联动事件操作类型
#define U_Extg_Auto_Operate		0x01 //自动
#define U_Extg_Manu_Operate		0x02 //手动
#define U_Extg_Remote_Operate		0x03 //远程
#define U_Extg_Operate_MAX		0x04 //
*/


/*
EVT=RUN,STOP,FEED,FEEDRSTR
RUN + STOP = STOP
RUN + NOFEED = RUN_NO_FEED
RUN + FEED = RUN_AND_FEED
RUN + FEED_RSTR = RUN


*/
	
/*

#define U_DRT_MODU_FAULT_EVT 		0x059  //多线路故障
#define U_DRT_MODU_FAU_RSTR_EVT		0x05A  //
#define U_LOOP_FAULT_EVT 		0x087  //
#define U_LOOP_FAU_RSTR_EVT 		0x088  //
*/



/******************************************************************************
// END :
******************************************************************************/
#endif // __evtThingDef_H__

