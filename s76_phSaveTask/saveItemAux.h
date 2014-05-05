#ifndef __saveItemAux_H__
#define __saveItemAux_H__
/******************************************************************************
* @file    saveItemAux.h
* @author  yx
* @version V1.0
* @date    2013-07-01
* @brief   
* 
#include  "saveItemAux.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

#include  "strFlsItmStruct.h"

/*================= extern ============================================*/
#ifdef  __saveItemAux_C__
#define EX_saveItemAux
#else
#define EX_saveItemAux extern 
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
#ifdef  __saveItemAux_C__

#endif  //__saveItemAux_C__
/*================= 公有函数声明 ====================================*/
//EX_saveItemAux 

/*================= 公有函数声明-lib用 ====================================*/
//EX_saveItemAux 

extern void FlsMeStatus_Default(TFlsSysSet_un *pSet);

/*================= 公有函数声明-lib外部 ====================================*/
//EX_saveItemAux 

extern BOOL FlsSetMeStatus_runAuto(U8 mSet, U8 taskId, U8 flsId);
extern BOOL FlsSetMeStatus_runManu(U8 mSet, U8 taskId, U8 flsId);
extern BOOL FlsSetMeStatus_machAdr(U8 mSet, U8 taskId, U8 flsId);
extern BOOL FlsSetMeStatus_machMasterOrSlave(
									U8 mSet, U8 taskId, U8 flsId);
extern BOOL FlsSetMeStatus_language(U8 mSet, U8 taskId, U8 flsId);
extern BOOL FlsSetMeStatus_pssw1(U8 *pByte, U8 taskId, U8 flsId);
extern BOOL FlsSetMeStatus_pssw2(U8 *pByte, U8 taskId, U8 flsId);

/******************************************************************************
// END :
******************************************************************************/
#endif // __saveItemAux_H__

