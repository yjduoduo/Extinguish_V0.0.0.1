#ifndef __prjDataType_H__
#define __prjDataType_H__
/******************************************************************************
* @file    prjDataType.h
* @author  yx
* @version V1.0
* @date    2012-01-05
* @brief   数据类型定义。 in "prjCompileCon.h"
* 
#include  "prjDataType.h"
******************************************************************************/
//
/******************************************************************************
// 数据类型 :
******************************************************************************/

typedef unsigned char   BOOL;	  
typedef unsigned short   TMRWORD;	
typedef unsigned short  FIREWORD; //报警事件个数。		   
typedef unsigned char   PAGEWORD;	 

typedef unsigned char  U8; 	//无符号8位整型变量
typedef unsigned short U16;	//无符号16位整型变量
typedef unsigned long  U32;	//无符号32位整型变量

typedef unsigned char  uint8; //无符号8位整型变量
typedef signed   char  int8;  //有符号8位整型变量
typedef unsigned short uint16;//无符号16位整型变量
typedef signed   short int16; //有符号16位整型变量
typedef unsigned long   uint32;//无符号32位整型变量
typedef signed   long   int32; //有符号32位整型变量
typedef float          fp32;  //单精度浮点数（32位长度
typedef double         fp64;  //双精度浮点数（64位长度）

typedef unsigned char  BOOLEAN;	// 1	 
//typedef unsigned char  CHAR;	// 1
typedef unsigned char  BYTE;	// 1
typedef unsigned short WORD;	// 2  +
typedef signed   short SHORT;	// 2  -+	
typedef signed   int   INT;		// 4  -+
typedef unsigned int   UINT;	// 4  +		
typedef signed   int   LONG;	// 4  -+
typedef unsigned int   DWORD; 	// 4  +


#define HH_DWORD32(_wdata)   (uint8)(((_wdata) >> 24) & 0xFF)
#define HL_DWORD32(_wdata)   (uint8)(((_wdata) >> 16) & 0xFF)
#define LH_DWORD32(_wdata)   (uint8)(((_wdata) >> 8 ) & 0xFF)
#define LL_DWORD32(_wdata)   (uint8)(((_wdata)      ) & 0xFF)

/******************************************************************************
// 
******************************************************************************/
#ifndef NULL
#ifdef __cplusplus
#define NULL    0
#else
#define NULL    ((void *)0)
#endif
#endif
//如果在C++里面，NULL就是0，如果在C里面，NULL就是((void *)0)

/******************************************************************************
// 
******************************************************************************/
#define KBytes        (0x400)
#define MBytes        (0x400*0x400)


/******************************************************************************
// END :
******************************************************************************/
#endif // __prjDataType_H__

