#ifndef __canProtocalStr_H__
#define __canProtocalStr_H__
/******************************************************************************
* @file    canProtocalStr.h
* @author  yx
* @version V1.0
* @date    2013-07-26
* @brief   CANЭ���֡ID����
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


/*================= �ṹ�嶨�� ======================================*/

/*================= ���нṹ�������� ================================*/
//#pragma pack(4)
typedef union
{			
	U32 dWord;
	struct{
		uint32 DataType:5;   // (0x40>>3) = 11s ���ݴ�
		uint32 SourceAddr:8; // Դ��ַ
		uint32 TargetAddr:8; // Ŀ�ĵ�ַ
		uint32 BroadOrPToP:8;  // ֡���Ͷ��� 04H=�ڲ��㲥����  // CFrameType   CBroadOrPToP      		 
		uint32 NoUsed:3;	
	}st11sId;  
}CanID;   // CanID  mID;

//#pragma pack()
/*
"FF RTR X X
DLC3~DLC0"	ͨѶ֡�����ֽ�	CFCtrl	0x80+����	
ID28~ID21	ͨѶ�����ֽ�1	CFComm1		08��Ե�, 04�㲥
ID20~ID13	ͨѶ�����ֽ�2	CFComm2		Ŀ�ĵ�ַ(TargetAddr)
ID12~ID5	ͨѶ�����ֽ�3	CFComm3		Դ��ַ(SourceAddr)
ID4~ID0 X X X	ͨѶ�����ֽ�4	CFComm4	40H,80H

*/  



/*================= ���� ============================================*/   

//#define 
#define U_CAN_BROAD_SEND_AIM_ADR		0x0 //CAN�Ϲ㲥�ĵ�ַ
#define U_ICAN_POT_ADR_MAX  127
/*================= ���� ============================================*/
// CDataType 
typedef enum 
{
	CDType_11s_SData = (0x40>>3),     // 11s ���ݴ�
	CDType_11s_FHead = (0x80>>3),     // 11s �ļ�ͷ
	CDType_11s_FData = (0xA0>>3),     // 11s �ļ�����
	CDType_11s_FEnd  = (0x90>>3),     // 11s �ļ�����
	
}emCanFrm11sDataOrFile;

// CFrameType
#define  CFType_11s_CBoard     0x04    // 11s�ڲ��㲥����
#define  CFType_11s_CPtoP      0x08    // 11s�ڲ�������� // CFType_11s_CDot
#define  CFType_11s_WBoard     0x54    // 11s WCAN�㲥����
#define  CFType_11s_WPtoP      0x58    // 11s WCAN�������  δʹ�� // CFType_11s_WDot


/*================= ���к������� ====================================*/
//EX_canProtocalStr 


/******************************************************************************
// END :
******************************************************************************/
#endif // __canProtocalStr_H__

