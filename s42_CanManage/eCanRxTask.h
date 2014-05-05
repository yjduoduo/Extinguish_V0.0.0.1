#ifndef __eCanRxTask_H__
#define __eCanRxTask_H__
/******************************************************************************
* @file    eCanRxTask.h
* @author  yx
* @version V1.0
* @date    2013-09-09
* @brief   
* 
#include  "eCanRxTask.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

/*================= extern ============================================*/
#ifdef  __eCanRxTask_C__
#define EX_eCanRxTask
#else
#define EX_eCanRxTask extern 
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
#ifdef  __eCanRxTask_C__

#endif  //__eCanRxTask_C__
/*================= 公有函数声明 ====================================*/
//EX_eCanRxTask 

//接收数据帧：
extern void eCanRxDataFrm(void);

//接收文件：事件帧
extern void eCanRxEvtFile(U8 mEvtBuf);
//接收文件：信息帧
extern void eCanRxMesgFile(U8 mMesgBuf);


/******************************************************************************
// END :
******************************************************************************/
#endif // __eCanRxTask_H__

