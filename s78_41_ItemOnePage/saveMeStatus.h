#ifndef __saveMeStatus_H__
#define __saveMeStatus_H__
/******************************************************************************
* @file    saveMeStatus.h
* @author  yx
* @version V1.1
* @date    2013-09-23 
* @brief   系统配置
* 
* V1.1, 2013-09-23 
		去掉对 unSet的控制，以免在master里修改相对位置的定义，造成影响。
* V1.0, 2013-01-04
*
#include  "saveMeStatus.h"
******************************************************************************/
//
#include  "prjCompileCon.h"
#include  "strFlsItmStruct.h"

/*================= extern ============================================*/
#ifdef  __saveMeStatus_C__
#define EX_saveMeStatus
#else
#define EX_saveMeStatus extern 
#endif
/*================= 常数 ============================================*/
//#define 
/*================= 结构体定义 ======================================*/

/*================= 公有结构变量声明 ================================*/

/*================= 私有函数声明 ====================================*/
#ifdef  __saveMeStatus_C__
static TFlsSysSet_un  unSysSet; // 不涉及 unSet字段，只保证留够总字节数。

#endif  //__saveMeStatus_C__


/*================= 公有函数声明-lib外部 ====================================*/
//EX_saveMeStatus 

// 保存
extern BOOL FlsSysSetMeStatus_Save(U8 taskId, U8 flsId);

// 读flash内容
extern BOOL FlsRd_MeStatus(void);

// 读出，且可能被改变内容。
extern TFlsSysSet_un *pGetFlsSysSet(void);



/******************************************************************************
// END :
******************************************************************************/
#endif // __saveMeStatus_H__

