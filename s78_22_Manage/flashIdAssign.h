#ifndef __flashIdAssign_H__
#define __flashIdAssign_H__
/******************************************************************************
* @file    flashIdAssign.h
* @author  yx
* @version V1.1
* @date    2013.9.22
* @brief   
//分配ID号：flash存储 有唯一的id号(关机时间和历史记录除外)
// master需要先得到一个flsId, 然后再调用 FlsSave_PnConfig()等。
//若不在意存储结果，可以用默认的flsId: FlsId_DefaultValue();
*
*
* @Version history 
* V1.1, 2013.9.22
*	FlsResultNotificat()的结果，用U8表示，.0表示part0,.1表示part1.
* V1.0, 2013-07-23
* 
#include  "flashIdAssign.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

/*================= extern ============================================*/
#ifdef  __flashIdAssign_C__
#define EX_flashIdAssign
#else
#define EX_flashIdAssign extern 
#endif
/*================= 常数 ============================================*/
//#define 
/*================= 结构体定义 ======================================*/

/*================= 公有结构变量声明 ================================*/

/*================= 私有函数声明 ====================================*/
#ifdef  __flashIdAssign_C__

#endif  //__flashIdAssign_C__
/*================= 公有函数声明-lib内部 ====================================*/
//EX_flashIdAssign 

// 存储结果
extern void FlsResultNotificat(U8 taskId, U8 mFlsId, U8 bSucc);

/*================= 公有函数声明-lib外部 ====================================*/
//EX_flashIdAssign 

//分配ID号：flash存储 有唯一的id号(关机时间和历史记录除外)
// master需要先得到一个flsId, 然后再调用 FlsSave_PnConfig()等。
//若不在意存储结果，可以用默认的flsId: FlsId_DefaultValue();

// 分配存储任务唯一id, Clr:
extern void FlsIdAssign_Init(void);

extern BOOL bFlsId_Valid(U8 mFlsId);

//定时判断结果超时，需要master定时100ms执行:
// 若超时，清除结果。
extern void FlsIdAssign_TmrAdd(void);

//默认值，给不关心结果的task使用。
extern U8 FlsId_DefaultValue(void);


// 新分配任务号，给master判断存储结果用。
// master需要先得到一个flsId, 然后再调用 FlsSave_PnConfig()等。
extern BOOL FlsIdNewAssign(U8 taskId, U8 *pRtnFlsId);

extern void FlsIdClrAssign(U8 mFlsId);

//清除所有taskId所分配的flsId.
extern void FlsIdClr_FromTaskId(U8 mTaskId);

//结果读取：
// *  OUT: BOOL=是否操作完毕；
// *pRtnSucc = 读出比较的结果 // .0=1=part0 Succ; .1=1=part1 Succ
extern BOOL bIsFinish_FlsExe(U8 flsId, U8 *pRtnSucc);

extern BOOL bFlsId_AllFinish_FromTaskId(U8 mTaskId);
extern BOOL bFlsId_AllSucc_FromTaskId(U8 mTaskId);


/******************************************************************************
// END :
******************************************************************************/
#endif // __flashIdAssign_H__

