#ifndef __iCanRxTask_H__
#define __iCanRxTask_H__
/******************************************************************************
* @file    iCanRxTask.h
* @author  yx
* @version V1.0
* @date    2013-09-09
* @brief   
* 
#include  "iCanRxTask.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

/*================= extern ============================================*/
#ifdef  __iCanRxTask_C__
#define EX_iCanRxTask
#else
#define EX_iCanRxTask extern 
#endif
/*================= 常数 ============================================*/
//#define 
/*================= 结构体定义 ======================================*/

/*================= 公有结构变量声明 ================================*/
/*
typedef struct{
	U8 sequStart;
}TStruct_st;
TStruct_st stStruct;
*/

/*-----------------    ----------------------------------*/

/*================= 私有函数声明 ====================================*/
#ifdef  __iCanRxTask_C__

#endif  //__iCanRxTask_C__
/*================= 公有函数声明 ====================================*/
//EX_iCanRxTask 

//接收数据帧：
extern void iCanRxDataFrm(void);

//接收文件：事件帧
extern void iCanRxEvtFile(U8 mEvtBuf);
//接收文件：信息帧
extern void iCanRxMesgFile(U8 mMesgBuf);

extern BOOL iCanRxFile_PageIsInquireRegist(void);
extern BOOL iCanRxFile_PageIsLoopBrowse(void);




/******************************************************************************
// END :
******************************************************************************/
#endif // __iCanRxTask_H__

