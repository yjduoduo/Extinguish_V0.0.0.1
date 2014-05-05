#ifndef __saveInc_Extern_H__
#define __saveInc_Extern_H__
/******************************************************************************
* @file    saveInc_Extern.h
* @author  yx
* @version V1.5
* @date    2013-09-23
* @brief   需要master定义的函数
* 
* V1.5, 2013-09-23
* 		add:  FlsMeStatus_Default();
		add:  GetPanelType_...();
* V1.4, 2013-09-10 
		修改注释，函数来源。
* V1.3, 2013-09-4
*
#include  "saveInc_Extern.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

#include  "strEvtTrans.h"
#include  "strFlsItmStruct.h"

/*================= 事件类型 ====================================*/
// EX_evt_Class

// 历史记录保存 归类
// *  OUT: bits: (1 << U_HIST_CLASS_MAX)
extern U32 EvtThing_toHistClsBits(TEvtTrans_st *pEvtTrans); 


// *  OUT: 事件 emevtThingDef;
extern U8 GetEvtThingDef_Fault(void);
extern U8 GetEvtThingDef_FlsErase(void);
extern U8 GetEvtThingDef_FlsCopyRenew(void);

extern U8 GetEvtThingDef_PwrOff(void);
/*================= ====================================*/
// EX_sysDef 

// *  OUT: flash修正的taskId. [emSysTask]
extern U8 GetSysTaskId_FlsVerify(void);

/*================= 公有函数声明 ====================================*/
//EX_sysPanel 

// Panel登记的标志字 = bRegisted.
extern void Panel_Regist(U8 pnICanSequ, BOOL bRegisted);

//单元类型 in emPanelType
extern BOOL bPnTypeIsValid(U8 pnType);

/*================= 公有函数声明 ====================================*/
//EX_sysMachine 

// Machine登记的标志字 = bRegisted.
extern void Machine_Regist(U8 mMachineSequ, BOOL bRegisted);

/*================= 公有函数声明-lib用 ====================================*/
//EX_saveItemAux 

extern void FlsMeStatus_Default(TFlsSysSet_un *pSet);

/*================= 公有函数声明 ====================================*/
//EX_sysPanel 

extern U8 GetPanelType_Loop(void);
extern U8 GetPanelType_Extg(void);
extern U8 GetPanelType_Drt(void);

/*================= 单元，控制器====================================*/
// EX_sysDef 

extern BOOL bMachineIdIsMe(U8 mMachine);
extern U8 GetMachineMaster(void);
extern U8 GetLanguageChinese(void);

// 控制器号：
extern U8 GetMachineMax(void);
extern BOOL bMachineValid(U8 mMachine);

// Panel的顺序号：
extern U8 GetPanelTotalSequMax(void);
extern BOOL bPanelTotalSequValid(U8 mPnSequ);

/*================= 公有函数声明-master ====================================*/
//EX_saveTmrPwroffAndHist 

//保存关机时间的定时：
extern void SavePwrOff_Tmr_Init(void);
extern BOOL bSavePwrOff_Arrived(void);
extern void FlsWr_pwrOff_Start(void); //-> FlsWr_pwrOff_New(&stClock);


//保存历史记录的时间间隔：
extern void SaveHist_Tmr_Init(void);
extern BOOL bSaveHist_Arrived(void);

// save任务，定时删除的定时：
extern void SaveFlsId_Tmr_Init(void);
extern BOOL bSaveFlsId_Arrived(void);


/*================= 公有函数声明 ====================================*/
// EX_phClock
extern void GetRamEvtTimer(TEvtClock_st *pEvtClock);

//EX_mRunTask 
// 需要严格定时执行的task. 在系统长时间执行某task的间隙insert.
extern void RunCycle_OnTime(void);
/******************************************************************************
// END :
******************************************************************************/
#endif // __saveInc_Extern_H__

