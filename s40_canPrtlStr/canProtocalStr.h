#ifndef __canProtocalStr_H__
#define __canProtocalStr_H__
/******************************************************************************
* @file    canProtocalStr.h
* @author  yx
* @version V1.0
* @date    2013-07-26
* @brief   CAN协议的帧ID定义
* 
V1.0, 2013-07-26

#include  "canProtocalStr.h"
******************************************************************************/

#include  "prjCompileCon.h"
// #include  "canFrame.h"
/*================= extern ============================================*/
#ifdef  __canProtocalStr_C__
#define EX_canProtocalStr
#else
#define EX_canProtocalStr extern 
#endif


/*================= 结构体定义 ======================================*/

/*================= 公有结构变量声明 ================================*/
//#pragma pack(4)
typedef union
{			
	U32 dWord;
	struct{
		uint32 DataType:5;   // (0x40>>3) = 11s 数据串
		uint32 SourceAddr:8; // 源地址
		uint32 TargetAddr:8; // 目的地址
		uint32 BroadOrPToP:8;  // 帧类型定义 04H=内部广播数据  // CFrameType   CBroadOrPToP      		 
		uint32 NoUsed:3;	
	}st11sId;  
}CanID;   // CanID  mID;

//#pragma pack()
/*
"FF RTR X X
DLC3~DLC0"	通讯帧控制字节	CFCtrl	0x80+长度	
ID28~ID21	通讯命令字节1	CFComm1		08点对点, 04广播
ID20~ID13	通讯命令字节2	CFComm2		目的地址(TargetAddr)
ID12~ID5	通讯命令字节3	CFComm3		源地址(SourceAddr)
ID4~ID0 X X X	通讯命令字节4	CFComm4	40H,80H

*/  



/*================= 常数 ============================================*/   

//#define 
#define U_CAN_BROAD_SEND_AIM_ADR		0x0 //CAN上广播的地址
#define U_ICAN_POT_ADR_MAX  127
/*================= 常数 ============================================*/
// CDataType 
typedef enum 
{
	CDType_11s_SData = (0x40>>3),     // 11s 数据串
	CDType_11s_FHead = (0x80>>3),     // 11s 文件头
	CDType_11s_FData = (0xA0>>3),     // 11s 文件数据
	CDType_11s_FEnd  = (0x90>>3),     // 11s 文件结束
	
}emCanFrm11sDataOrFile;

// CFrameType
#define  CFType_11s_CBoard     0x04    // 11s内部广播数据
#define  CFType_11s_CPtoP      0x08    // 11s内部点点数据 // CFType_11s_CDot
#define  CFType_11s_WBoard     0x54    // 11s WCAN广播数据
#define  CFType_11s_WPtoP      0x58    // 11s WCAN点点数据  未使用 // CFType_11s_WDot


/*================= 公有函数声明 ====================================*/
//EX_canProtocalStr 


/******************************************************************************
// END :
******************************************************************************/
#endif // __canProtocalStr_H__

