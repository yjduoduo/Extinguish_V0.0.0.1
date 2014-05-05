#ifndef __loopFieldTypeState_H__
#define __loopFieldTypeState_H__
/******************************************************************************
* @file    loopFieldTypeState.h
* @author  yx
* @version V1.0
* @date    2013-07-01
* @brief   
* 
#include  "loopFieldTypeState.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

/*================= 常数 ============================================*/
//==== << 设备类型 ======高四位是类型码

enum emDeteType{
	
	DETE_TYPE_Butt   		= 0x010, //手报
	DETE_TYPE_XiaoNiu		= 0x020, //消钮
	DETE_TYPE_Wen    		= 0x030, //感温
	DETE_TYPE_DianLan		= 0x050, //电缆
	DETE_TYPE_FuHe   		= 0x080, //复合
	DETE_TYPE_ShuRu  		= 0x090, //输入模块
	DETE_TYPE_YanLiZi   	= 0x0A0, //感烟
	DETE_TYPE_YanGd    		= 0x0B0, //感烟
	DETE_TYPE_ZhongJi		= 0x0D0, //中继模块
	DETE_TYPE_ExtgAutoManu	= 0x0D1, //气灭手自动
	DETE_TYPE_ExtgForbid	= 0x0D2, //气灭禁止模块

	DETE_TYPE_INVALID      		= 0x0FF, //

};
	
// enum emDeteType{
	// DETE_TYPE_00_OldButt		= 0x00, //手报
	// DETE_TYPE_10_Butt   		= 0x010, //手报
	// DETE_TYPE_20_XiaoNiu		= 0x020, //消钮
	// DETE_TYPE_40_Wen    		= 0x030, //感温
	// DETE_TYPE_50_DianLan		= 0x050, //电缆
	// DETE_TYPE_80_FuHe   		= 0x080, //复合
	// DETE_TYPE_90_ShuRu  		= 0x090, //输入模块
	// DETE_TYPE_A0_YanT   		= 0x0A0, //感烟
	// DETE_TYPE_B0_Yan    		= 0x0B0, //感烟
	// DETE_TYPE_D0_ZhongJi		= 0x0D0, //中继模块
	// DETE_TYPE_F0_T      		= 0x0F0, //手报
// };
	
enum emDeteSta{
	
	//设备状态
	DETE_00_STA_USUAL 		= 0x00, //正常
	DETE_20_STA_FAULT 		= 0x20, //故障
	DETE_40_STA_FAULT 		= 0x40, //故障
	DETE_80_STA_FAULT 		= 0x80, //故障
	DETE_C0_STA_FAULT 		= 0x0C0, //故障
	DETE_A0_STA 			= 0x0A0, //
	DETE_90_STA 			= 0x090, //一级
	DETE_B0_STA 			= 0x0B0, //一级
	DETE_D0_STA 			= 0x0D0, //一级
	DETE_30_STA 			= 0x030, //二级
	DETE_50_STA 			= 0x050, //二级
	DETE_10_STA 			= 0x010, //三级
	DETE_60_STA 			= 0x060, //三级
	DETE_70_STA 			= 0x070, //三级
	DETE_E0_STA 			= 0x0E0, //三级
	DETE_FF_STA_INVALID 	= 0x0FF, //
};

/******************************************************************************
// END :
******************************************************************************/
#endif // __loopFieldTypeState_H__

