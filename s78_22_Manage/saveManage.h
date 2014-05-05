#ifndef __saveManage_H__
#define __saveManage_H__
/******************************************************************************
* @file    saveManage.h
* @author  yx
* @version V1.1
* @date    2013.9.23
* @brief   此lib的管理函数入口。
*		写flash管理。
*			恢复机制也要在此控制下进行。
*		读在[PeriphSave] saveX.c里。
* 
为防止某sector未写入的情况，上电后的查找head,end应挨条查找。
* 检查part1的判断: 在 "ProjectStruct.h"
*
*0x100000字节，1us, 0x100000us=1048576us = 1048ms = 1s.
*
* @version history
* V1.1，2013.9.23 
* 		稍改变命名。
* V1.0，2013-07-23
* 
#include  "saveManage.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

#include  "flsStoreBytesDef.h"
#include  "strFlsAdrDef.h"

/*================= extern ============================================*/
#ifdef  __saveManage_C__
#define EX_saveManage
#else
#define EX_saveManage extern 
#endif
/*================= 常数 ============================================*/

typedef enum {
	emSave_Opea_Erase = 1,
	emSave_Opea_PwrOff,
	emSave_Opea_Hist,
	emSave_Opea_Item,
	emSave_Opea_FlsCopy,
	
}emSaveOpeaClass;
/*================= 结构体定义 ======================================*/

/*================= 私有函数声明 ====================================*/
#ifdef  __saveManage_C__

// 判断是否有未完结的任务，若有则需要继续处理。
// TRUE = !Erase & !FlsWr & !WorkHist & !WorkPwrOff & !WorkItem;
// 相对于flsTask_OpeaOne()，二者一致。无 copyTask();
static BOOL bFlsTask_isIdle(void);

// TRUE = flash busy or opeaOne; FALSE=idle;
static BOOL flsTask_OpeaOne(void);

// bStartOpea_...()：
// 开始新任务。按优先级排列。
// master: SaveManage_Exec();
static BOOL bStartOpea_Erase(void);
static BOOL bStartOpea_Item(void);
static BOOL bStartOpea_Hist(void);
static BOOL bStartOpea_PwrOff(void);
static BOOL bStartOpea_FlsCopy(void);
// FlsCopy,中间可以被其他任务打断。
static BOOL bStartOrExec_FlsCopy(void);

// bIfWorkIngExec_...():
//判断若 FALSE=taskIdle; else: exec() next step;
// master: flsTask_OpeaOne().U_FLASH_TASK_WAIT == FALSE;
// master: bStartOrExec_common_exeTillFinish.U_FLASH_TASK_WAIT == TRUE;
static BOOL bIfWorkIngExec_FlsWr(void); // Write Ing, flashIdle->next step;
static BOOL bIfWorkIngExec_Erase(void);
static BOOL bIfWorkIngExec_Item(void);
static BOOL bIfWorkIngExec_Hist(void);
static BOOL bIfWorkIngExec_PwrOff(void);
static BOOL bIfWorkIngExec_FlsCopy(void);


// 任务开始时：
// bStartOpea_...()后，
// U_FLASH_TASK_WAIT == FALSE：在 SaveManage_Exec() 里调度；
// U_FLASH_TASK_WAIT == TRUE:  一直等待完成：
static BOOL bStartOrExec_common_exeTillFinish(
									emSaveOpeaClass mOpeaClass);


#endif  //__saveManage_C__
/*================= 公有函数声明-lib内部 ====================================*/
//EX_saveManage 
#if U_FLASH_TASK_WAIT == TRUE
//直接等待至此task完毕.
// *Master: FlashSaveNew() + U_FLASH_TASK_WAIT=TRUE;
	    // FlsErase_New() + U_FLASH_TASK_WAIT=TRUE;
extern BOOL bWaitForFlsOpeaFinish(U8 mFlsId);
#endif // U_FLASH_TASK_WAIT

/*================= 公有函数声明-lib外部-允许读 ====================================*/
//EX_saveManage 
// 因为flash 写期间 禁止读操作，所以应用层读取前要判断：

//需要的项目允许读
//有1part允许就可以：
extern BOOL FlsRdFlsItem_ChipAllow(U8 mFlsItem);
extern BOOL FlsRdFlsItem_PartN_ChipAllow(U8 mFlsItem, U8 mPart);

/*================= 公有函数声明-lib外部 ====================================*/
//EX_saveManage 

// 检查master和lib定义的一致性
extern BOOL bSave_CheckReDef(void);

extern void Init_SaveManage(void);

// flash 存储管理 exe, 需要main循环调用。
extern void SaveManage_Exec(void);

/******************************************************************************
// END :
******************************************************************************/
#endif // __saveManage_H__

