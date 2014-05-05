#ifndef __phIoPwrChkSwitch_H__
#define __phIoPwrChkSwitch_H__
/******************************************************************************
* @file    phIoPwrChkSwitch.h
* @author  yx
* @version V1.0
* @date    2013-08-22
* @brief   电源检修开关
* 
#include  "phIoPwrChkSwitch.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

/*================= extern ============================================*/
#ifdef  __phIoPwrChkSwitch_C__
#define EX_phIoPwrChkSwitch
#else
#define EX_phIoPwrChkSwitch extern 
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
#ifdef  __phIoPwrChkSwitch_C__

#endif  //__phIoPwrChkSwitch_C__
/*================= 公有函数声明 ====================================*/
//EX_phIoPwrChkSwitch 

extern void InitPwrChkSwcTask(void);
extern void ExecPwrChkSwcTask(void);

/******************************************************************************
// END :
******************************************************************************/
#endif // __phIoPwrChkSwitch_H__

