#ifndef __tmrTick_H__
#define __tmrTick_H__
/******************************************************************************
* @file    tmrTick.h
* @author  yx
* @version V1.2
* @date    2013-10-09
* @brief   系统定时任务
* 注意：定时中断的粒度，要小于任务定时的最小粒度；
		定时的误差，ms级是定时中断的粒度，100ms级是100ms. 
		所以第一次的定时是不准的，若是连续定时执行，则较准确。

* V1.2 2013-10-09 《DriverTmrTick_V0.0.0.1_0.1.2》
* 		add: GetTickIntrAddMs(); 等 
* V1.1 2013-07-19
* V1.0 2010-06-19
#include  "tmrTick.h"
******************************************************************************/
/******************************************************************************
* 使用方法：
1.  InitTmrTickTask();
2.  初始化定时器timer;
3.  定时中断里，IntrAddTickMs();
4.  在main过程中，
	if(bHaveTmrTickIntr())
	{
		TickTaskWork();
	}
******************************************************************************/

//#include  "prjCompileCon.h"

#include  "prjDataType.h"
/*================= extern ============================================*/
#ifdef  __tmrTick_C__
#define EX_tmrTick
#else
#define EX_tmrTick extern 
#endif

/*================= 常数 ============================================*/

/*================= 应用举例 =======================================*/
/*
	SetTmrTickTask(TASK_XXTESTTASKXX, TMR_XXTESTTASKXX);//开始时间任务
	if(GetTickTaskStatus(TASK_XXTESTTASKXX) == TRUE)
	{
	}
	KillTickTask(TASK_XXTESTTASKXX);
	JudgeTickTaskUsing(TASK_XXTESTTASKXX);
*/
/*================= 常数 ============================================*/
/*================= 定时1ms =========================================*/

//以1ms为单位计数
#define TASK_CanTxInterval				0     //
#define TASK_ICanSend				0     //
#define  TMR_ICanSend          			1000 //ms
#define TASK_ECanSend				1     //
#define  TMR_ECanSend          			1000 //ms
#define TASK_CanTxCtrl				2     //

#define TASK_Flash_Wait				3     //U_SST39VF900A_CHIP_MAX
#define  TMR_Flash_Wait          		2 //ms
#define TASK_Flash_CheckInterval	6  
#define  TMR_Flash_CheckInterval   		20 //ms

#define TASK_CanTxSucc				15  //包含can0 can1.
#define  TMR_CanTxSucc					20 //ms 
#define TASK_CanReTx				17  //包含can0 can1.
#define  TMR_CanReTx					100 //ms 

#define TASK_IoTaskRefresh			19 		//Led, Key, Sound.
#define  TMR_IoTaskRefresh				20 //ms 

#define TASK_TestTemp				20 		//测试时用
#define  TMR_TestTemp					20 //ms 
#define TASK_TestClock				21 		//测试时用
#define  TMR_TestClock					200 //ms 
#define TASK_TestFlash				22 		//测试时用
#define  TMR_TestFlash					1000 //ms 
#define TASK_SelfHdChk				23 		//测试时用
#define  TMR_SelfHdChk					20 //ms 

/*================= 定时100ms =======================================*/
#define TASK_100MS_LOW		30 //LOW
//以100ms为单位计数

#define TASK_LedCheck		(TASK_100MS_LOW + 0)    
#define  TMR_LedCheck          		2 //100ms
#define TASK_ReadClock		(TASK_100MS_LOW + 1)    
#define  TMR_ReadClock          	3 //100ms
#define TASK_SaveFlsId		(TASK_100MS_LOW + 2)    	//
#define  TMR_SaveFlsId				1  //100ms
#define TASK_CanFileOverTime	(TASK_100MS_LOW + 3)    	//
#define  TMR_CanFileOverTime			1  //100ms
#define TASK_KeyHold			(TASK_100MS_LOW+4)    	// 按键保持时间
#define  TMR_KeyHold					20  //100ms
#define TASK_PageEvtChkChange	(TASK_100MS_LOW+5) // 事件页面 检查是否需要更新
#define  TMR_PageEvtChkChange			10  //100ms
#define TASK_PageEvtAutoTurn	(TASK_100MS_LOW+6) // 事件页面 自动翻页
#define  TMR_PageEvtAutoTurn			30  //100ms
#define TASK_FigInCursor		(TASK_100MS_LOW+8) // 输入数字的光标
#define  TMR_FigInCursor				 5  //100ms
#define TASK_LedBlink			(TASK_100MS_LOW+9) // 
#define  TMR_LedBlink				 	5  //100ms

#define TASK_LcdHardShow		(TASK_100MS_LOW+10)  
#define  TMR_LcdHardShow          		2 //100ms

#define TASK_CloseHdWhenResetIng (TASK_100MS_LOW+11)  
#define  TMR_CloseHdWhenResetIng 		15 //100ms

#if U_SYS_Test_Flash_SimTask == U_YES
	#define TASK_FlsSim100ms		(TASK_100MS_LOW+18)  
	#define  TMR_FlsSim100ms          		1 //100ms
#endif // U_SYS_Test_Flash_SimTask == 1

#if U_SYS_Test_Lcd == 1
	#define TASK_LcdSim100msShow		(TASK_100MS_LOW+19)  
	#define  TMR_LcdSim100msShow          		1 //100ms
#endif // U_SYS_Test_Lcd == 1

/*================= 定时1s ==========================================*/
#define TASK_1S_LOW			50 //LOW
//以1s为单位计数

#define TASK_HeatBeat			(TASK_1S_LOW+0)    	//
#define  TMR_HeatBeat					9  	//s
#define TASK_SavePowerOff		(TASK_1S_LOW+1)    	//
#define  TMR_SavePowerOff				60  //s
#define TASK_SaveHist			(TASK_1S_LOW+2)    	//
#define  TMR_SaveHist					3  //s

#define TASK_CanTx1FrmMax		(TASK_1S_LOW+3)  
#define  TMR_CanTx1FrmMax          			3 //s
#define TASK_ICanTx1FrmMax		(TASK_CanTx1FrmMax + 0)     //
#define TASK_ECanTx1FrmMax		(TASK_CanTx1FrmMax + 1)     //


#define TASK_CanTxRxCycle		(TASK_1S_LOW+5)  
#define  TMR_CanTxRxCycle          			30 //s
#define TASK_ICanTxRxCycle		(TASK_CanTxRxCycle + 0)     //
#define TASK_ECanTxRxCycle		(TASK_CanTxRxCycle + 1)     //

#define TASK_PageEvtForbidAutoTurn	(TASK_1S_LOW+7) // 事件页面 禁止自动翻页
#define  TMR_PageEvtForbidAutoTurn		10  //s

#define TASK_CheckPanelInLine		(TASK_1S_LOW+8) // unit,machine 在线的检测
#define  TMR_CheckPanelInLine				1  //s
#define TASK_CheckMachineInLine		(TASK_1S_LOW+9) // unit,machine 在线的检测
#define  TMR_CheckMachineInLine				30  //s


/*================= 定时常数END =====================================*/
#define MAX_TICK_TASK_NUM 	 70 //不可改变,在lib决定

/*================= 结构体定义 ======================================*/


/*================= 调用外部函数声明 ====================================*/
extern void TickTimer_HdInt(U8 bAllow);  //中断 允许/禁止

extern U8 Get_TmrId_100msLow(void);
extern U8 Get_TmrId_1sLow(void);
/*================= 公有函数声明 测试用 ====================================*/
//EX_tmrTick 
extern U8 get100msLow(void); //测试用
extern BOOL bGetTickIntr(void);
extern U32 GetTickIntrAddMs(void);
extern U32 GetTickTmrNowMs(void);
extern U32 GetTickTmrNowN00Ms(void);
extern U32 GetTickTmrNowNs(void);
/*================= 公有函数声明 与timer定时相关 ====================================*/
//EX_tmrTick 
extern void InitTmrTickTask(void); //时间任务初始化 TIMER2
extern void TickTaskWork(void);   //系统事件定时

extern void IntrAddTickMs(U32 mMsNum); //定时中断时，调用一次。
extern U8 bHaveTmrTickIntr(void);

/*================= 公有函数声明 use ====================================*/
//EX_tmrTick 
extern void ClearTickTaskTmr(U8 tmrID);   //重新计时tmrID的sign时钟的工作
extern void SetTickTaskSign(U8 tmrID);    //设置计时到标志
extern void ClrTickTaskSign(U8 tmrID);
extern BOOL JudgeTickTaskUsing(U8 tmrID); //判断是否using

extern BOOL GetTickTaskStatus(U8 tmrID); //读出时间任务的状态 并清零标志
extern BOOL GetTickTaskStaNoClr(U8 tmrID); //读出且不清标志
extern BOOL SetTmrTickTask(U8 tmrID, U32 SetMSec);//开始时间任务
extern BOOL SetTmrTickTsk_haveTaskId(U8 tmrID, U32 SetMSec, U8 taskId);
extern BOOL KillTickTask(U8 tmrID);       //取消时间任务 taskId:emSysTask
extern void KillTickTsk_TaskId(U8 taskId); 

/*================= 应用举例 =======================================*/
/*
	SetTmrTickTsk_haveTaskId(TASK_XXTESTTASKXX, TMR_XXTESTTASKXX, U_SysTask_LcdShow);
	SetTmrTickTask(TASK_XXTESTTASKXX, TMR_XXTESTTASKXX);//开始时间任务
	if(GetTickTaskStatus(TASK_XXTESTTASKXX) == TRUE)
	{
	}
	KillTickTask(TASK_XXTESTTASKXX);
	JudgeTickTaskUsing(TASK_XXTESTTASKXX);
*/
/******************************************************************************
// END :
******************************************************************************/
#endif // __tmrTick_H__

