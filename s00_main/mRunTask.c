#define __mRunTask_C__
/******************************************************************************
* @file    mRunTask.c
* @author  yx
* @version V1.0
* @date    2012-01-05
* @brief   main.c�ĸ��������Ŵ�����taskЭ����
* 
******************************************************************************/
#include  "mRunTask.h"


#include "incFile.h"	
// #include  "CanManage.h"
#include  "sysMachine.h"
#include  "sysPanel.h"
#include  "lcdCst_Page.h"

#include  "mTask_Test.h"



/*================= ���� ============================================*/

/*================= �ṹ���� ========================================*/

/*================= ˽�нṹ�������� ================================*/

/*================= ���к������� ====================================*/

/*================= ˽�к������� ====================================*/

/*=================  ================================================*/
		
/******************************************************************************
* FUNC: // ��ʼ ��ʱ��������Ҫһֱ���еģ�
*   IN:
*  OUT: 
******************************************************************************/

void init_Timer_TaskTmr(void)
{
	SetTmrTickTask(TASK_ICanSend, TMR_ICanSend);
	SetTmrTickTask(TASK_ECanSend, TMR_ECanSend);
	
	SetTmrTickTask(TASK_HeatBeat, TMR_HeatBeat); 
	// SetTmrTickTask(TASK_XXTESTTASKXX, TMR_XXTESTTASKXX); 
	
}


/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
void sys_CloseAllHd_AndIniTimer(void)
{
	
	MyInt_All_Disable();
	Notify_SysInt_Hd_AllClose();
	
	Init_SysStatus();
	InitTmrTickTask(); // clr all task;
	
	MyTickTimer_Init(); // ����ʱ��
	SetMyHdHaveIniSign(U_SysTask_Timer_ID);
}



/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

void sys_init_Part(void)
{
#if U_SYS_ForbidHardWare == U_NO
	
	InitClock();
	SetMyHdHaveIniSign(U_SysTask_RealTime_ID);
	
	// LCD:
	Init_LcdTask();
	SetMyHdHaveIniSign(U_SysTask_LcdShow);
	
	//KEY:
	InitKeyJudgeTask();
	InitKeyScanTask();
	SetMyHdHaveIniSign(U_SysTask_Key_ID);
	
	//LED:
	InitLedTask();
	SetMyHdHaveIniSign(U_SysTask_Led_ID);
	LedFuncBlink(U_LED_pwrMain);
	
	
	Can_Task_Init();
	SetMyHdHaveIniSign(U_SysTask_iCan_ID);
	SetMyHdHaveIniSign(U_SysTask_eCan_ID);
	
#endif
	
	SysTask_Test_Init();
	
}

/******************************************************************************
* FUNC: //
******************************************************************************/
void sys_init_All(void)
{

	
	PanelState_Init();
	MachineState_Init();
			// TickTaskWork();
	
	IniEvtAll();
	LcdCstPage_CheckCst();
	
// Flash:
	FlsHd_All_Init();
	SetMyHdHaveIniSign(U_SysTask_HdFlashNor0_ID);
	SetMyHdHaveIniSign(U_SysTask_HdFlashNor1_ID);
	
	
// I/O
	InitIoScan();
	SetMyHdHaveIniSign(U_SysTask_Led_ID);
	SetMyHdHaveIniSign(U_SysTask_Key_ID);
	SetMyHdHaveIniSign(U_SysTask_Sound_ID);
	SetMyHdHaveIniSign(U_SysTask_PwrChkSwc_ID);
	SetMyHdHaveIniSign(U_SysTask_PwrState_ID);
		// Exec_IoLedKeyScan();
	
	InitClock();
	SetMyHdHaveIniSign(U_SysTask_RealTime_ID);
		// ExecClockTask();
	
// �洢����:
	Init_SaveTask(); // TRUE=OK;
	SetMyHdHaveIniSign(U_SysTask_FlsSave);
	
//��ʾ��
	//LCD Init; Clr show buf.
	Init_LcdTask();
	SetMyHdHaveIniSign(U_SysTask_LcdShow);
		// Exec_LcdTask();
	// InitWindowTask();
	NeedPssw_Init();
	
//ͨѶ��
	//canHd_All_HdAndBuf_Init();
	Can_Task_Init();
	SetMyHdHaveIniSign(U_SysTask_iCan_ID);
	SetMyHdHaveIniSign(U_SysTask_eCan_ID);
	
	Uart_All_HdAndBuf_Init();
	SetMyHdHaveIniSign(U_SysTask_Uart_DownLoad);
	// MyUart_Init();
	// CanTask_Init();
		
//Dog:
	MyDog_Init();
		// checkWatchDog();
		
	MyTickTimer_Init(); // ����ʱ��
	init_Timer_TaskTmr();  // ��ʼ ��ʱ��������Ҫһֱ���еģ�
	
	//flash��أ�
	// Init_SaveTask();  // TRUE=OK;
	// FlsRd_PnConfig();
	// FlsRd_NetMachine();
	
}


/******************************************************************************
* FUNC: //
******************************************************************************/


/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
void Sys_Exec(void)
{
	sys_exec_Part();
//	SysTask_Test_Exec();
	// sys_exec_All();
}
/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

void sys_exec_Part(void)
{
	Panel_inLine_Check();
	Machine_inLine_Check();
	
	Task_ExecKeyTask();
	Exec_LcdTask();
	
	ExecClockTask();
	
	ExecLedTask();
	
	
	Can_Task_Exec();
	
	SysTask_Test_Exec();
}

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
void sys_exec_All(void)
{
	
	Clear_MyWatchDog();
	// MyDog_Feed();
	
	ExecClockTask();
	
	
	if(bHaveTmrTickIntr())
	{
		TickTaskWork();
	}
	
	// SaveTask_Exec();
	RunCycle_OnTime();
	
	Exec_IoLedKeyScan();
	
	
	Exec_LcdTask();
	
	SaveTask_Exec();
	
	Can_Task_Exec();
	
	// ExecCanBufTask();
	
	// ExecWindowTask();
}




/******************************************************************************
* FUNC: //
******************************************************************************/


/******************************************************************************
* FUNC: //
******************************************************************************/


/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
void SysInit_WhenPowerOn(void)
{
	InitAll_MyHdHaveIniSign();
	sys_CloseAllHd_AndIniTimer();
	
	IniEvtAll();
	LcdCstPage_CheckCst();
	
	PanelState_Init();
	MachineState_Init();
	


//	// Flash:initial,must have
    FlsHd_All_Init();
    SetMyHdHaveIniSign(U_SysTask_HdFlashNor0_ID);
    SetMyHdHaveIniSign(U_SysTask_HdFlashNor1_ID);

    // sys_init_All();
    sys_init_Part();

	
}

void SysInit_WhenReset(void)
{
	InitAll_MyHdHaveIniSign();
	sys_CloseAllHd_AndIniTimer();
	IniEvtAll();
	PanelState_Init();
	MachineState_Init();
	
	// sys_init_All();
	sys_init_Part();
}


/******************************************************************************
* FUNC: // ��Ҫ�ϸ�ʱִ�е�task. ��ϵͳ��ʱ��ִ��ĳtask�ļ�϶insert.
*   IN:
*  OUT: 
* �����ڲ��ܶ�д flash, ���ܵ���LCD LIB, ���ܵȴ��жϡ�
******************************************************************************/
void RunCycle_OnTime(void)
{
	if(bHaveTmrTickIntr())
	{
		TickTaskWork();
	}
	Clear_MyWatchDog();
	
	
	CanIntrBuf_Move();
	
}

void RunCycle_WhenFlashWaitIng(void)
{
	RunCycle_OnTime();
}


/******************************************************************************
* FUNC: //
******************************************************************************/



/******************************************************************************
* FUNC: // END
*   IN:
*  OUT: 
******************************************************************************/
