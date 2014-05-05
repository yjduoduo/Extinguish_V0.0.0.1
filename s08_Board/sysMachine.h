#ifndef __sysMachine_H__
#define __sysMachine_H__
/******************************************************************************
* @file    sysMachine.h
* @author  yx
* @version V1.0
* @date    2012-01-05
* @brief   
* 
#include  "sysMachine.h"
******************************************************************************/
//
#include  "prjCompileCon.h"
#include  "sysDef.h"

/*================= extern ============================================*/
#ifdef  __sysMachine_C__
#define EX_sysMachine
#else
#define EX_sysMachine extern 
#endif
/*================= 常数 ============================================*/
//#define 
/*================= 结构体定义 ======================================*/

/*================= 公有结构变量声明 ================================*/

/*================= 私有函数声明 ====================================*/
#ifdef  __sysMachine_C__
#define U_Machine_InLine_NUM_MAX   200
#define U_Machine_InLine_NUM_MIN   1
typedef struct 
{
	U32 bRegisted:1;
	U32 bOutLine:1;
	U32 inLineNum:8;
}TMachine_st;

static TMachine_st vMachine[U_MACHINE_MAX]; // U8 mMachineSequ;

BOOL machine_inLine_ResultOk(U8 mMachineSequ, U8 bOk);
#endif  //__sysMachine_C__
/*================= 公有函数声明 ====================================*/
//EX_sysMachine 

extern void Machine_Regist(U8 mMachineSequ, BOOL bRegisted);
extern void Machine_inLine_Inc(U8 mMachineSequ);
extern void Machine_inLine_Clr(U8 mMachineSequ);
extern void Machine_inLine_ClrAll(void);
extern void Machine_inLine_Check(void);

extern void MachineState_Init(void);

extern BOOL GetMachine_Regist(U8 mMachineSequ);

/******************************************************************************
// END :
******************************************************************************/
#endif // __sysMachine_H__

