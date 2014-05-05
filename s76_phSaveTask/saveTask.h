#ifndef __saveTask_H__
#define __saveTask_H__
/******************************************************************************
* @file    saveTask.h
* @author  yx
* @version V1.0
* @date    2013-07-23
* @brief   配合 "FlsSave_Driver" 的接口。
* 
#include  "saveTask.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

/*================= extern ============================================*/
#ifdef  __saveTask_C__
#define EX_saveTask
#else
#define EX_saveTask extern 
#endif
/*================= 常数 ============================================*/
//#define 
/*================= 结构体定义 ======================================*/

/*================= 公有结构变量声明 ================================*/

/*================= 私有函数声明 ====================================*/
#ifdef  __saveTask_C__

#endif  //__saveTask_C__
/*================= 公有函数声明 ====================================*/
//EX_saveTask 

EX_saveTask BOOL Init_SaveTask(void);
EX_saveTask void SaveTask_Exec(void);

/******************************************************************************
// END :
******************************************************************************/
#endif // __saveTask_H__

