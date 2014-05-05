#ifndef __prjDataType_H__
#define __prjDataType_H__
/******************************************************************************
* @file    prjDataType.h
* @author  yx
* @version V1.0
* @date    2012-01-05
* @brief   �������Ͷ��塣 in "prjCompileCon.h"
* 
#include  "prjDataType.h"
******************************************************************************/
//
/******************************************************************************
// �������� :
******************************************************************************/

typedef unsigned char   BOOL;	  
typedef unsigned short   TMRWORD;	
typedef unsigned short  FIREWORD; //�����¼�������		   
typedef unsigned char   PAGEWORD;	 

typedef unsigned char  U8; 	//�޷���8λ���ͱ���
typedef unsigned short U16;	//�޷���16λ���ͱ���
typedef unsigned long  U32;	//�޷���32λ���ͱ���

typedef unsigned char  uint8; //�޷���8λ���ͱ���
typedef signed   char  int8;  //�з���8λ���ͱ���
typedef unsigned short uint16;//�޷���16λ���ͱ���
typedef signed   short int16; //�з���16λ���ͱ���
typedef unsigned long   uint32;//�޷���32λ���ͱ���
typedef signed   long   int32; //�з���32λ���ͱ���
typedef float          fp32;  //�����ȸ�������32λ����
typedef double         fp64;  //˫���ȸ�������64λ���ȣ�

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
//�����C++���棬NULL����0�������C���棬NULL����((void *)0)

/******************************************************************************
// 
******************************************************************************/
#define KBytes        (0x400)
#define MBytes        (0x400*0x400)


/******************************************************************************
// END :
******************************************************************************/
#endif // __prjDataType_H__

