#ifndef __strFlsItmStruct_H__
#define __strFlsItmStruct_H__
/******************************************************************************
* @file    strFlsItmStruct.h // WrFlsApply 写fls task分配空间
* @author  yx
* @version V1.1
* @date    2013-10-24
* @brief   
*
* V1.1 2013-10-24
*		add: TFlsRelateDete_st; TFlsExtgZoneConfig_st;  TFlsField_st;
* V1.0 2013-07-22
*
#include  "strFlsItmStruct.h"
******************************************************************************/
//
#include  "prjCompileCon.h"
//#include  "sysDef.h"
#include  "flsReDef.h"

#include  "strDevice.h"
#include  "strClock.h"

#include  "strFlsAdrDef.h"
#include  "strFlsQue.h"
#include  "flsStoreBytesDef.h"

/*================= extern ============================================*/
#ifdef  __strFlsItmStruct_C__
#define EX_strFlsItmStruct
#else
#define EX_strFlsItmStruct extern 
#endif

/*================= 每sector, 在开始的0x10字节，存属性。 ======================================*/
#define U_FLS_SectorStart_BYTES   0x04
typedef union
{
	U32 dword[U_FLS_SectorStart_BYTES/4];
	U8  byte[U_FLS_SectorStart_BYTES];
	struct{
		U8 byte_55;
		U8 mFlsItem;
		// U8 crc;		//仅单页一次全存储的有用。
	}detail;
}TFlsSecStart_un; //TFlsSecStart_un *pFlsSecStart;



/*================= TFlsSysSet_un ======================================*/

/*================= TFlsSysSet_un ======================================*/
#define U_PRINT_ALARM_BIT			0x01
#define U_PRINT_LINK_BIT			0x02
#define U_PRINT_FAULT_BIT			0x04
#define U_PRINT_SUPERVISION_BIT		0x08
#define U_PRINT_OPEA_BIT			0x10

#define U_PSSW1_BYTE_MAX	3
#define U_PSSW2_BYTE_MAX	6
#define U_SOFT_VERSION_BYTE_MAX		8


#define U_SYSSET_BYTE_MAX		0x40

typedef union
{
	U8 byte[U_SYSSET_BYTE_MAX];
	struct{
		
		U8 runAuto;
		U8 runManu;
		// U8 showMachProbat; //试用期是否显示
		
		// U8 printSwitch; //打印机开关
		// U8 prtZfOneRow; //打印机一行的字符数
		// U8 prtClassBit; //打印的事件类型 U_PRINT_ALARM_BIT
		U8 pssw1[U_PSSW1_BYTE_MAX];
		U8 pssw2[U_PSSW2_BYTE_MAX];
		// U8 rowOneScreen; //故障、屏蔽消息 每屏显示的条数
		// U8 rowOneTurn; //故障、屏蔽消息 每次翻页的条数
		//U8 softVersion[U_SOFT_VERSION_BYTE_MAX];
		
		// U8 autoCancelLoginSecond; //user login，无操作自动取消登录的时间
		
		U8 machAdr;
		U8 machMasterOrSlave; //U_MACHINE_MASTER, U_MACHINE_SLAVE
		// U8 machRecClass;
		
		U8 language; //emLanguage
		
		//本机权限：消音，复位，查询，用户设置，全部设置。
		U16 verify;
	}stSet;
	
}TFlsSysSet_un;

/*================= TFlsLinkProg_st ======================================*/

typedef struct
{
	TDev_un stDev;
	U8 byte[U_FLS_LINK_PROG_BYTE_MAX];
}TFlsLinkProg_st;

/*================= TFlsRelateDete_st ======================================*/

#define U_FLS_RelateDete_One_BYTE_MAX  0x28
typedef struct
{
	TDev_un stDev;
	U8 mType;
	BOOL bRelated;
	U8 note[U_FLS_NOTE_BYTE_MAX];
}TFlsRelateDeteOne_st;

typedef enum {
	emFlsRelatDeteOpea_ChangeRelate = 1,
	emFlsRelatDeteOpea_ChangeNote = 2,
	emFlsRelatDeteOpea_ChangeAll = 3,
	emFlsRelatDeteOpea_ClrOne = 8,
	emFlsRelatDeteOpea_Clr1Loop = 9,
}emFlsRelateDeteOpeaCls;
	
#define U_FLS_RelateDete_Head_BYTE_MAX  0x04

typedef struct
{
	// TFlsRelateDeteOne_st 是参数；
	U8 mOpeaCls; // emFlsRelateDeteOpeaCls
	U8 mAddrS;
	U8 mAddrE;
	
}TFlsRelateDeteHead_st; // 几者必占其一

// 0x1000 / 8 = 0x200地址；

/*================= TFlsField_st ======================================*/
#define U_FLS_Field_Once_Addr_MAX  0x20
#define U_FLS_Field_Head_BYTE_MAX  0x04
typedef struct
{
	U8 mLoop;
	U8 mAddrS; // 
	U8 mAddrE; // valid+1;
}TFlsFieldHead_st;

#define U_FLS_Field_1Addr_BYTE_MAX  0x04
typedef struct
{
	U32 mType:8;
	U32 mExtgType:4;
	U32 bRegist:1;
	U32 bDisable:1;
}TFlsFieldOne_st;

/*================= TFlsExtgZoneConfig_st 气灭区配置 ===========================*/
#define U_FLS_ExtgZoneConfig_One_BYTE_MAX  0x10

#define U_FLS_ExtgZoneConfig_All_BYTE_MAX  \
			((U_FLS_ExtgZoneConfig_One_BYTE_MAX * U_SYS_LOOP_MAX) + 1)
			
typedef struct
{
	U8 mExtgZone; // 1~4
	
	U8 mData[U_FLS_ExtgZoneConfig_One_BYTE_MAX];
	
}TFlsExtgZoneConfig_st;

/*================= TFlsNote_st ======================================*/
typedef struct
{
	TDev_un stDev;
	U8 note[U_FLS_NOTE_BYTE_MAX];
}TFlsNote_st;


/*================= TFlsDisable_un ======================================*/
#define U_FLS_DISABLE_BYTE_MAX		0x10

typedef union
{
	U8 byte[U_FLS_DISABLE_BYTE_MAX];
	struct{
		TDev_un stDev;
		U8 bAdd;
	}stDisable;
}TFlsDisable_un;

/*================= TFlsUnitConfig_un ======================================*/
#define U_FLS_PanelConfig_BYTE_MAX		(U_PANEL_TOTAL_SEQU_MAX+1)
typedef union
{
	U8 byte[U_FLS_PanelConfig_BYTE_MAX];
	struct{
		
		U8 pnNum[U_PANEL_TOTAL_SEQU_MAX];
		//u16 verify;
	}stSet;
	
}TFlsUnitConfig_un; //本机单元配置
/*================= TFlsMachineConfig_un ======================================*/
#define U_FLS_MachineConfig_BYTE_MAX		(U_MACHINE_MAX+1)
typedef union
{
	U8 byte[U_FLS_MachineConfig_BYTE_MAX];
	struct{
		
		U8 machNum[U_MACHINE_MAX];
		//u16 verify;
	}stSet;
	
}TFlsMachineConfig_un; //本机控制器配置

/*================= TFlsPwrOff_st ======================================*/

typedef union{ 
	U8 byte[U_FLS_1PowerOff_BYTE_MAX];
	struct{
		TEvtClock_st stClock;		
	}stPwrOff;
}TFlsPwrOff_un; // 关机时间

/*================= TUserLogin_un ======================================*/
#define U_FLS_UserLogin_BYTE_MAX		(0xF0+1)

typedef union{
	U8 byte[U_FLS_UserLogin_BYTE_MAX];
	struct{
		
		U8 bProbatIng;
		U8 bHaveArrived;
		U32 daysBeforehandShow; //剩余天数提前显示的天数
		TEvtClock_st stClkWhenSet; //设置时的日期
		U32 setDays; //试用天数
		U32 remainingDays; //剩余天数。不根据当前日期计算，防止user修改时钟达到继续使用的目的。
		U32 delayDays; //实际存储时无用，
		
		U8 setTimes; //已设置次数
		U32 idShow; //设置时生成的序列号
		
	}stSet;
	
}TUserLogin_un;

/*================= TFlsProbat_un ======================================*/
#define U_FLS_Probat_BYTE_MAX		(0x20+1)

typedef union{
	U8 byte[U_FLS_Probat_BYTE_MAX];
	struct{
		
		U8 bProbatIng;
		U8 bHaveArrived;
		U32 daysBeforehandShow; //剩余天数提前显示的天数
		TEvtClock_st stClkWhenSet; //设置时的日期
		U32 setDays; //试用天数
		U32 remainingDays; //剩余天数。不根据当前日期计算，防止user修改时钟达到继续使用的目的。
		U32 delayDays; //实际存储时无用，
		
		U8 setTimes; //已设置次数
		U32 idShow; //设置时生成的序列号
		
	}stSet;
	
}TFlsProbat_un;



/*================= THisory_un  ======================================*/

// typedef struct{ 
		// TDev_un unDev; 
		// U8 type; //设备类型
		// U8 thingFir;
		// U8 thingSec;
		// TEvtClock_st stClock;	
// }THisory_st; //需要存历史的struct.

typedef union{ 
	U8 byte[U_FLS_1HISTORY_BYTE_MAX];
	struct{
		TDev_un unDev; 
		U8 type; //设备类型
		U8 thingFir;
		U8 thingSec;
		TEvtClock_st stClock;		
	}stHist;
}THisory_un; //需要存历史的struct.

typedef union{ 
	U8 byte[U_FLS_1HistPoint_BYTE_MAX];
	
	TFlsQueuePoint_st   stPoint;
	
}THistPoint_un; //历史记录.end 地址

/*=================   ======================================*/


/******************************************************************************
// 
TFlsSecStart_un

TFlsSysSet_un		系统配置
TFlsLinkProg_st	联动编程
TFlsRelateDete_st    相关地址
TFlsFieldHead_st  TFlsFieldOne_st 回路现场部件
TFlsExtgZoneConfig_st 气灭区配置
TFlsNote_st		注释
TFlsDisable_un		屏蔽
TFlsUnitConfig_un	单元
TFlsMachineConfig_un	控制器
TFlsPwrOff_un		关机时间
TFlsProbat_un		试用期
THisory_un		历史记录
THistPoint_un		历史记录指针

******************************************************************************/

/******************************************************************************
// END :
******************************************************************************/
#endif // __strFlsItmStruct_H__

