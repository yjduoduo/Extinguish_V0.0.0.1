#ifndef __saveTmrPwroffAndHist_H__
#define __saveTmrPwroffAndHist_H__
/******************************************************************************
* @file    saveTmrPwroffAndHist.h
* @author  yx
* @version V1.1
* @date    2013-9-04
* @brief   
*
* V1.0  2012-01-05
* 
#include  "saveTmrPwroffAndHist.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

/*================= extern ============================================*/
#ifdef  __saveTmrPwroffAndHist_C__
#define EX_saveTmrPwroffAndHist
#else
#define EX_saveTmrPwroffAndHist extern 
#endif
/*================= 常数 ============================================*/
//#define 
/*================= 结构体定义 ======================================*/

/*================= 公有结构变量声明 ================================*/

/*================= 私有函数声明 ====================================*/
#ifdef  __saveTmrPwroffAndHist_C__

#endif  //__saveTmrPwroffAndHist_C__

/*================= 公有函数声明-master用 ====================================*/
//EX_saveTmrPwroffAndHist 
// saveTask.c 

//历史记录，存关机时间
extern BOOL PwrOff_toHist(void);


/*================= 公有函数声明-lib用 ====================================*/
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



/******************************************************************************
// END :
******************************************************************************/
#endif // __saveTmrPwroffAndHist_H__

