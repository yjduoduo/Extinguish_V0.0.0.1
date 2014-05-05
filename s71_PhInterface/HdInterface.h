#ifndef __HdInterface_H__
#define __HdInterface_H__
/******************************************************************************
* @file    HdInterface.h
* @author  yx
* @version V1.0
* @date    2012-01-05
* @brief   防止应用程序调用 hw， hwEx
		其中的中断入口函数，应 被 "hw00_CallBack.c" 调用
		有关cpu的不能归入module的寄存器，在CpuReg.c里。
* 
#include  "HdInterface.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

/*================= extern ============================================*/
#ifdef  __HdInterface_C__
#define EX_HdInterface
#else
#define EX_HdInterface extern 
#endif
/*================= 常数 ============================================*/

enum emTmrLogicId{  // uint8 tmr_id;
	U_Tmr_SysTick_ID = 0, // 不涉及硬件
	U_Tmr_NorFlash_ID = 1, // 
};
#define U_TMR_ID_MAX  2

#define U_TMR_ID_Default  U_Tmr_SysTick_ID

/*================= 结构体定义 ======================================*/

/*================= 公有结构变量声明 ================================*/

/*================= 私有函数声明 ====================================*/
#ifdef  __HdInterface_C__
extern void MyTickTimer_IntrHander(void); //中断 Handle
extern void NorFlashTimer_IntrHander(void); //中断 Handle

#endif //__HdInterface_C__
/*================= 公有函数声明-WatcherDog ====================================*/
//EX_HdInterface 

extern void MyDog_Init(void);
extern void MyDog_Feed(void);

/*================= 公有函数声明-Timer ====================================*/
//EX_HdInterface 

// Int:
extern void TimerHd_Int_Enable(U8 tmr_id); // emTmrLogicId
extern void TimerHd_Int_Disable(U8 tmr_id);

// 应用层 与 硬件 的uartId 的对应关系：
// const TTmrProp_st cstTmrPeriId[U_TMR_ID_MAX+1] ;
extern U8 GetTmrDriveId_FromTmrId(U8 tmr_id);
extern U8 GetTmrId_FromTmrPeriId(U8 tmrDriveId);
extern void MyTimer_IntrHander(U8 tmrDriveId); //中断 Handle

extern void MyTickTimer_Init(void);
extern void TickTimer_HdInt(U8 bAllow);  //中断 允许/禁止
// extern void MyTickTimer_IntrHander(void); //中断 Handle
extern void MyTickTimer_Close(void);


extern void NorFlashTimer_Init(U32 mTmrUs);
// extern void NorFlashTimer_IntrHander(void); //中断 Handle
extern BOOL bNorFlashTimer_Arrived(void); //
extern void NorFlashTimer_Close(void);

/******************************************************************************
// END :
******************************************************************************/
#endif // __HdInterface_H__

