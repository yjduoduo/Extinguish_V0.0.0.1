#ifndef __tmrTick_H__
#define __tmrTick_H__
/******************************************************************************
* @file    tmrTick.h
* @author  yx
* @version V1.2
* @date    2013-10-09
* @brief   ϵͳ��ʱ����
* ע�⣺��ʱ�жϵ����ȣ�ҪС������ʱ����С���ȣ�
		��ʱ����ms���Ƕ�ʱ�жϵ����ȣ�100ms����100ms. 
		���Ե�һ�εĶ�ʱ�ǲ�׼�ģ�����������ʱִ�У����׼ȷ��

* V1.2 2013-10-09 ��DriverTmrTick_V0.0.0.1_0.1.2��
* 		add: GetTickIntrAddMs(); �� 
* V1.1 2013-07-19
* V1.0 2010-06-19
#include  "tmrTick.h"
******************************************************************************/
/******************************************************************************
* ʹ�÷�����
1.  InitTmrTickTask();
2.  ��ʼ����ʱ��timer;
3.  ��ʱ�ж��IntrAddTickMs();
4.  ��main�����У�
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

/*================= ���� ============================================*/

/*================= Ӧ�þ��� =======================================*/
/*
	SetTmrTickTask(TASK_XXTESTTASKXX, TMR_XXTESTTASKXX);//��ʼʱ������
	if(GetTickTaskStatus(TASK_XXTESTTASKXX) == TRUE)
	{
	}
	KillTickTask(TASK_XXTESTTASKXX);
	JudgeTickTaskUsing(TASK_XXTESTTASKXX);
*/
/*================= ���� ============================================*/
/*================= ��ʱ1ms =========================================*/

//��1msΪ��λ����
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

#define TASK_CanTxSucc				15  //����can0 can1.
#define  TMR_CanTxSucc					20 //ms 
#define TASK_CanReTx				17  //����can0 can1.
#define  TMR_CanReTx					100 //ms 

#define TASK_IoTaskRefresh			19 		//Led, Key, Sound.
#define  TMR_IoTaskRefresh				20 //ms 

#define TASK_TestTemp				20 		//����ʱ��
#define  TMR_TestTemp					20 //ms 
#define TASK_TestClock				21 		//����ʱ��
#define  TMR_TestClock					200 //ms 
#define TASK_TestFlash				22 		//����ʱ��
#define  TMR_TestFlash					1000 //ms 
#define TASK_SelfHdChk				23 		//����ʱ��
#define  TMR_SelfHdChk					20 //ms 

/*================= ��ʱ100ms =======================================*/
#define TASK_100MS_LOW		30 //LOW
//��100msΪ��λ����

#define TASK_LedCheck		(TASK_100MS_LOW + 0)    
#define  TMR_LedCheck          		2 //100ms
#define TASK_ReadClock		(TASK_100MS_LOW + 1)    
#define  TMR_ReadClock          	3 //100ms
#define TASK_SaveFlsId		(TASK_100MS_LOW + 2)    	//
#define  TMR_SaveFlsId				1  //100ms
#define TASK_CanFileOverTime	(TASK_100MS_LOW + 3)    	//
#define  TMR_CanFileOverTime			1  //100ms
#define TASK_KeyHold			(TASK_100MS_LOW+4)    	// ��������ʱ��
#define  TMR_KeyHold					20  //100ms
#define TASK_PageEvtChkChange	(TASK_100MS_LOW+5) // �¼�ҳ�� ����Ƿ���Ҫ����
#define  TMR_PageEvtChkChange			10  //100ms
#define TASK_PageEvtAutoTurn	(TASK_100MS_LOW+6) // �¼�ҳ�� �Զ���ҳ
#define  TMR_PageEvtAutoTurn			30  //100ms
#define TASK_FigInCursor		(TASK_100MS_LOW+8) // �������ֵĹ��
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

/*================= ��ʱ1s ==========================================*/
#define TASK_1S_LOW			50 //LOW
//��1sΪ��λ����

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

#define TASK_PageEvtForbidAutoTurn	(TASK_1S_LOW+7) // �¼�ҳ�� ��ֹ�Զ���ҳ
#define  TMR_PageEvtForbidAutoTurn		10  //s

#define TASK_CheckPanelInLine		(TASK_1S_LOW+8) // unit,machine ���ߵļ��
#define  TMR_CheckPanelInLine				1  //s
#define TASK_CheckMachineInLine		(TASK_1S_LOW+9) // unit,machine ���ߵļ��
#define  TMR_CheckMachineInLine				30  //s


/*================= ��ʱ����END =====================================*/
#define MAX_TICK_TASK_NUM 	 70 //���ɸı�,��lib����

/*================= �ṹ�嶨�� ======================================*/


/*================= �����ⲿ�������� ====================================*/
extern void TickTimer_HdInt(U8 bAllow);  //�ж� ����/��ֹ

extern U8 Get_TmrId_100msLow(void);
extern U8 Get_TmrId_1sLow(void);
/*================= ���к������� ������ ====================================*/
//EX_tmrTick 
extern U8 get100msLow(void); //������
extern BOOL bGetTickIntr(void);
extern U32 GetTickIntrAddMs(void);
extern U32 GetTickTmrNowMs(void);
extern U32 GetTickTmrNowN00Ms(void);
extern U32 GetTickTmrNowNs(void);
/*================= ���к������� ��timer��ʱ��� ====================================*/
//EX_tmrTick 
extern void InitTmrTickTask(void); //ʱ�������ʼ�� TIMER2
extern void TickTaskWork(void);   //ϵͳ�¼���ʱ

extern void IntrAddTickMs(U32 mMsNum); //��ʱ�ж�ʱ������һ�Ρ�
extern U8 bHaveTmrTickIntr(void);

/*================= ���к������� use ====================================*/
//EX_tmrTick 
extern void ClearTickTaskTmr(U8 tmrID);   //���¼�ʱtmrID��signʱ�ӵĹ���
extern void SetTickTaskSign(U8 tmrID);    //���ü�ʱ����־
extern void ClrTickTaskSign(U8 tmrID);
extern BOOL JudgeTickTaskUsing(U8 tmrID); //�ж��Ƿ�using

extern BOOL GetTickTaskStatus(U8 tmrID); //����ʱ�������״̬ �������־
extern BOOL GetTickTaskStaNoClr(U8 tmrID); //�����Ҳ����־
extern BOOL SetTmrTickTask(U8 tmrID, U32 SetMSec);//��ʼʱ������
extern BOOL SetTmrTickTsk_haveTaskId(U8 tmrID, U32 SetMSec, U8 taskId);
extern BOOL KillTickTask(U8 tmrID);       //ȡ��ʱ������ taskId:emSysTask
extern void KillTickTsk_TaskId(U8 taskId); 

/*================= Ӧ�þ��� =======================================*/
/*
	SetTmrTickTsk_haveTaskId(TASK_XXTESTTASKXX, TMR_XXTESTTASKXX, U_SysTask_LcdShow);
	SetTmrTickTask(TASK_XXTESTTASKXX, TMR_XXTESTTASKXX);//��ʼʱ������
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

