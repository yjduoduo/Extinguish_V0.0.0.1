#ifndef __strDevMLAT_H__
#define __strDevMLAT_H__
/******************************************************************************
* @file    strDevMLAT.h
* @author  yx
* @version V1.0
* @date    2013-07-01
* @brief   DEV的结构 细节定义。 subject to "strDevice.h";
* 
#include  "strDevMLAT.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

/*================= 常数 ============================================*/

/******************************************************************************
* FUNC: // DEV 结构
******************************************************************************/

enum emEvtSubject{
	U_EVT_SUBJECT_FIELD = 0, // 带回路现场部件的方式。
	U_EVT_SUBJECT_BOARD = 1  //包括分区。尽量只用U_EVT_SUBJECT_FIELD判断。
};

/*================= 公有结构变量声明 ================================*/
//modu, mduLine, 
#pragma pack(1)	
typedef struct{
	
	U32 channel:6; //1~
	U32 field:9;		//1~ //mduLine  //各分类。若不是现场部件,有不同的定义。 
	
	//以下结构不能变,名称可变。
	U32 eventSubject:1; 	// U_EVT_SUBJECT_FIELD, U_EVT_SUBJECT_BOARD 包括分区。
	U32 boardLoop:4;	//1~  //板内回路-num,  //modu
	U32 pnSequ:7;  		//1~ //panel拨码序号-num, 128
	U32 pnType:5;  		//0~ //panel类型  // emPanelSign 
	
	U8  machine;
}TCommonMLAT_st; //machine-loop-addr-channel
#pragma pack()	
//若改变字段，需要改 cstStDevStructProp[];

/*=================  ======================================*/
#pragma pack(1)	
typedef struct{
	
	U32 state:6; 
	U32 mduLine:9;  //  
	
	//以下结构不能变,名称可变。
	U32 eventSubject:1; // U_EVT_SUBJECT_FIELD, U_EVT_SUBJECT_BOARD
	U32 modu:4; //1~ //单元内分区 
	U32 pnSequ:7; //1~ //panel拨码序号-num, 128
	U32 pnType:5; //0~ //panel类型  // emPanelType
	
	U8  machine;
}TModuMLAT_st; //machine-loop-addr-channel
#pragma pack()



/******************************************************************************
* FUNC: // Dev 结构里的item的 max, mask
******************************************************************************/
/*=================Dev 分类 ============================================*/
enum emDevItem{ // U8 mDevItem;
	U_DEV_ITEM_Machine = 0,
	U_DEV_ITEM_pnType = 1,
	U_DEV_ITEM_pnSequ = 2,
	U_DEV_ITEM_modu = 3,
	U_DEV_ITEM_evtSubject = 4,
	U_DEV_ITEM_mduLine = 5,
	U_DEV_ITEM_field = 6,
	U_DEV_ITEM_channel = 7
	
};
#define U_DEV_ITEM_MAX  8  
	
// TDevStructProp  cstStDevStructProp[U_DEV_ITEM_MAX];

/******************************************************************************
* FUNC: // mduLine 线路 和 事件 分类
******************************************************************************/

//==== << pDev->pnModu.mduLine ===========	
//实际的板上分区的线路  //
//U_EVT_SUBJECT_FIELD 相当于现场部件处理。
enum emMduLineFunc{  
	//多线  参考通讯协议
	U_Drt_MduFunc_Action = 0,
	U_Drt_MduFunc_Stop = 1,
	U_Drt_MduFunc_Ack = 2,
	U_Drt_MduFunc_AckRstr = 3, //反馈撤销
	U_Drt_MduFunc_AckMiss = 4, //反馈缺失
	
	U_Drt_MduFunc_MAX = 5,
	
	//气体灭火  参考通讯协议
	U_Extg_MduFunc_Action = 0,
	U_Extg_MduFunc_MAX = 3
	
};
	
//==== << pDev->pnModu.mduLine ===========	
//虚拟的各板上的事件. 注意同板的事件，类型不能相同。
// U_EVT_SUBJECT_BOARD 
enum emMduLineEvtFunc{
	U_MduFunc_BoardNoCommunicate = 0x10,
	
	//电源 mduLine
	U_Power_MduFunc_pwrMain = 0,
	U_Power_MduFunc_pwrBty = 1,
	
	//flsItem
	U_Fls_MduFunc_Config = 0x20,
	
	//显示单元：
	U_MduLine_Print = 0x30,
	
	
	U_MduLine_Invalid = 0x1FF
};

/******************************************************************************
// END :
******************************************************************************/
#endif // __strDevMLAT_H__

