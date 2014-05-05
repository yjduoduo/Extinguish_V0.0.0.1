#ifndef __CanBufLib_strFileProp_H__
#define __CanBufLib_strFileProp_H__
/******************************************************************************
* @file    CanBufLib_strFileProp.h
* @author  yx
* @version V1.0
* @date    2013-07-24
* @brief   文件帧在can的id里的标志.
* 
#include  "CanBufLib_strFileProp.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

/*================= 常数 ============================================*/
//#define 
/*================= 结构体定义 ======================================*/

// 每帧都有的，能唯一标识不同的文件
typedef struct{  
	
		U8 src;  	//源地址
		U8 dest; 	//目的地址
		U8 frmId;	//can协议里的消息id.
		//U8 taskId;  // 收发共用，带上。
}TCanFile_sId; 


/*================= 结构体定义 CanRx: 一条接收文件帧的head和manage ==========*/
typedef struct{  // file 属性
	
		BOOL bUsIng;
		BOOL bRecFinish;
		
		
		// 发送时， lenTotal = 在发送buf中的字节数。
		//		lenNow = 已发送的buf中的字节字节数，是out指针。
		// 		发送 fileHead[1]= (lenTotal+3).
		U32 haveRecLength;
		U32 fileLength;
		
		U8 verifyVal;
}TCanFile_RxN_Prop;


typedef struct{
	TCanFile_RxN_Prop	rxFileProp; //fileProp;
	TCanFile_sId  		fileSId;  //src,dest,id.
	struct{
		U8 recStart_100msNum;
		U8 recFinish_100msNum;
	}tmr;
}TCanRxFileHead_st;

/*================= 结构体定义 CanRx: 一条发送文件帧的head和manage ==========*/


typedef struct{  // file 属性
	
		BOOL bHaveFile;
		BOOL bSendIng;
		BOOL bSendFinish;
		
				U8 fileId;
		U8 taskId;  // main任务号
		U32 haveSendByte;
		U32 needSendTotal; // 与 fileLength 少1个字节。 ... verify, FF;
		U32 fileLength;		// file, length, ... , verify;
		U8 verifyVal;
}TCanFile_TxN_Prop;

typedef struct{  // buf 分配管理
	
	TCanFile_TxN_Prop	txFileProp; //buf;  
	TCanFile_sId 		fileSId;
	
	struct{
		U8 loadStart_100msNum;
		U8 sendFinish_100msNum;
	}tmr;
	
}TCanTxFileHead_st;

/*================= 公有函数声明 ====================================*/
//EX_CanBufLib_strFileProp 


/******************************************************************************
// END :
******************************************************************************/
#endif // __CanBufLib_strFileProp_H__

