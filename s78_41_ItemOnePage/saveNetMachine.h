#ifndef __saveNetMachine_H__
#define __saveNetMachine_H__
/******************************************************************************
* @file    saveNetMachine.h
* @author  yx
* @version V1.0
* @date    2013-01-04
* @brief   联网机器配置；
* 
#include  "saveNetMachine.h"
******************************************************************************/
//
#include  "prjCompileCon.h"
#include  "flsStoreBytesDef.h"

/*================= extern ============================================*/
#ifdef  __saveNetMachine_C__
#define EX_saveNetMachine
#else
#define EX_saveNetMachine extern 
#endif
/*================= 常数 ============================================*/
//#define 
/*================= 结构体定义 ======================================*/

/*================= 公有结构变量声明 ================================*/

/*================= 私有函数声明 ====================================*/
#ifdef  __saveNetMachine_C__

// OUT: pRtnBuf 读出的所有 netMachine的数据：
BOOL flsRd_NetMach_toBuf(U8 mPart, U8 *pBufS);

BOOL flsSave_NetMachine_change(U8 mMachS, U8 mMachE, 
						BOOL bAdd,
						U8 taskId, U8 flsId);

#endif  //__saveNetMachine_C__

/*================= 公有函数声明-lib外部 ====================================*/
//EX_saveNetMachine 
extern BOOL FlsRd_NetMachine(void);

extern BOOL FlsSave_NetMachine_Add(U8 mMachS, U8 mMachE, 
							  U8 taskId, U8 flsId);
extern BOOL FlsSave_NetMachine_Delete(U8 mMachS, U8 mMachE, 
							  U8 taskId, U8 flsId);


/******************************************************************************
// END :
******************************************************************************/
#endif // __saveNetMachine_H__

