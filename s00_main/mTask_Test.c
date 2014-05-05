#define __mTask_Test_C__
/******************************************************************************
* @file    mTask_Test.c
* @author  yx
* @version V1.0
* @date    2013-09-25
* @brief   lcd_disp_pix_1Line();
* 
******************************************************************************/
#include  "mTask_Test.h"


#include "incFile.h"	
// #include  "CanManage.h"
#include  "codeComm.h"
#include  "sysMachine.h"
#include  "sysPanel.h"
#include  "HdInterface.h"
#include  "lcdSub_ModeTextFig.h"
/*================= test ============================================*/
#include  "phIoLed.h"
#include  "LcdLib_incOut.h"
#include  "evt_Buf_incOut.h"
#include  "lcdTsk_PgNum.h"
#include  "lcdPg_aSchedu.h"
extern PAGEWORD pageMCycleReturn(void);
#include  "lcdCst_Page.h"
#include  "lcdPg_MainAndEvtChange.h"
#include  "lcdShowTask.h"
extern void lcdTask_JdgKey(void);

#if U_SYS_Test_Flash_SimTask == U_YES
  #include  "sim_saveItem.h"
#endif // U_SYS_Test_Flash_SimTask

/*=================  ================================================*/
static TEvtTrans_st stSimTrans;
/*=================  ================================================*/


/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
	lcdTask_JdgKey();
******************************************************************************/
void SysTask_Test_Init(void)
{
#if U_SYS_Test_Flash_SimTask == U_YES
	Sim_Init_SaveTask();
#endif // U_SYS_Test_Flash_SimTask
	
#if U_SYS_Test_Lcd == 1
	// TestLcdTmr_Start();
	// test_MCycle_Return();
	// sim_EvtShow();
	// simInit_TimerAddEvt();

#endif // U_SYS_Test_Lcd


}

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
void SysTask_Test_Exec(void)
{
#if U_SYS_Test_Flash_SimTask == U_YES
	Sim_Exec_SaveTask();
#endif // U_SYS_Test_Flash_SimTask


#if U_SYS_Test_Lcd == 1
	// simExec_TimerAddEvt();
	
#endif // U_SYS_Test_Lcd
}


/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

#if U_SYS_Test_Lcd == 1
static U32 vTimerAddNum = 0;

void simInit_TimerAddEvt(void)
{
	vTimerAddNum = 0;
	SetTmrTickTask(TASK_LcdSim100msShow, TMR_LcdSim100msShow);
	
}


#endif // U_SYS_Test_Lcd
/******************************************************************************
* FUNC: //
******************************************************************************/
#if U_SYS_Test_Lcd == 1

#define U_SIM_TimerAddEvt_IntervalSec   5  //  xx s一次。

#define U_SIM_TimerAddEvt_Cycle_Sec     (45)

void simExec_TimerAddEvt(void)
{
U32 mAddEvtNum;

	if(!GetTickTaskStatus(TASK_LcdSim100msShow) == TRUE)
	{
		return;
	}
	if(vTimerAddNum > (U_SIM_TimerAddEvt_Cycle_Sec * (U_SIM_TimerAddEvt_IntervalSec*10)))
	{
		vTimerAddNum = 0;
		return;
	}
	vTimerAddNum++;
	if((vTimerAddNum % (U_SIM_TimerAddEvt_IntervalSec*10)) != 0)
	{
		return;
	}
	mAddEvtNum = vTimerAddNum / (U_SIM_TimerAddEvt_IntervalSec*10);
	
	simAddOne_TimerAddEvt(mAddEvtNum);
	// simAddOne_TimerRectangle(mAddEvtNum);
}


#endif // U_SYS_Test_Lcd
/******************************************************************************
* FUNC: //
******************************************************************************/
#if U_SYS_Test_Lcd == 1

void simAddOne_TimerAddEvt(U32 mVal)
{
	if(bInDomain(mVal, 1, 3))
	{
		sim_LoadNewEvent(U_EvtCls_Dsab, mVal, U_Disable_EVT, 0);
	} 
	
	// 事件撤销：
	else if(bInDomain(mVal, 3, 5))
	{
		sim_LoadNewEvent(U_EvtCls_Dsab, mVal-2, U_DisableRstr_EVT, 0);
	}
	
	
	// 故障，仅此一条：
	else if(bInDomain(mVal, 5, 6))
	{
		sim_LoadNewEvent(U_EvtCls_Fault, mVal, U_Fault_EVT, 0);
	}
	
	// 高优先级
	else if(bInDomain(mVal, 6, 7))
	{
		sim_LoadNewEvent(U_EvtCls_Link, mVal, U_ModuAutoRunDelay_EVT, 9);
	}
	
	
	// 高优先级
	else if(bInDomain(mVal, 7, 8))
	{
		sim_LoadNewEvent(U_EvtCls_Alarm, mVal, U_Alarm_EVT, 0);
	}
	
	// 最高优先级
	else if(bInDomain(mVal, 8, 9))
	{
		sim_LoadNewEvent(U_EvtCls_Extg, mVal, U_ExtgAnnuRun_EVT, 0);
	}
	
	
	// 最高优先级 又一条，观察 应reFresh, 不应first.
	else if(bInDomain(mVal, 9, 10))
	{
		sim_LoadNewEvent(U_EvtCls_Extg, mVal, U_ExtgAnnuRun_EVT, 0);
	}
	
	
	// 新的优先级更低的事件：
	else if(bInDomain(mVal, 10, 11))
	{
		sim_LoadNewEvent(U_EvtCls_Link, mVal, U_ModuManuRun_EVT, 0);
	}
	
	
	// 翻页 到 非事件页面
	else if(bInDomain(mVal, 11, 20))
	{
		if(bPageIsEvent())
		{
			SetKeyValueWhenPsswOk(U_KEY_Return);
		}
	}
	
	
	// 非最高优先级事件，在MCycle里，退出
	else if(bInDomain(mVal, 20, 21))
	{
		sim_LoadNewEvent(U_EvtCls_Link, mVal, U_ModuManuRun_EVT, 0);
	}
	
	
	// 最高优先级事件，首次换页面，后续只更新。
	else if(bInDomain(mVal, 22, 30))
	{
		sim_LoadNewEvent(U_EvtCls_Extg, mVal, U_ExtgAnnuRun_EVT, 0);
	}
	
	
	else if(bInDomain(mVal, 30, 40))
	{
	}
	
	else if(bInDomain(mVal, 40, 42))
	{
		IniEvtAll();
	}
}

#endif // U_SYS_Test_Lcd
/******************************************************************************
* FUNC: //
******************************************************************************/
#if U_SYS_Test_Lcd == 1

extern TYPE_LCD_XY getPixYR_formRow(TYPE_LCD_RL mRow);

void simAddOne_TimerRectangle(U32 mVal)
{
	if(mVal == 1)
	{
		LcdSw_ClrFullWindow(0);
		return;
	}
	if(bInDomain(mVal, 2, 20))
	{
		LcdSw_ClrRectangle( 
				getPixYR_formRow(mVal-2), (mVal-2)*3, 
				getPixYR_formRow(mVal-1), (mVal-2)*3+2);
		ExecLcdShow();
		return;
	}
	
	
	if(mVal == 0)
	{
	}
	else if(bInDomain(mVal, 1, 2))
	{
		LcdSw_ClrFullWindow(~0);
		// 5行7列 方块
		LcdSw_SetRectangle( 60, 128+60, 66, 128+65);
		LcdSw_HvLine(       60, 128+60, 66, 128+65);
	}
	else if(bInDomain(mVal, 2, 3))
	{
		LcdSw_SetRectangle( 6*5, 60, 6*5+ 5, 65);
		LcdSw_HvLine(     6*5+10, 60, 6*5+10, 65);
	}
	else if(bInDomain(mVal, 3, 4))
	{
		LcdSw_SetRectangle( 6*5, 64+60, 6*5+ 5, 64+65);
		LcdSw_HvLine(     6*5+10, 64+60, 6*5+10, 64+65);
	}
	else if(bInDomain(mVal, 4, 5))
	{
		LcdSw_SetRectangle( 6*5, 128+60, 6*5+ 5, 128+65);
		LcdSw_HvLine(     6*5+10, 128+60, 6*5+10, 128+65);
	}
	else if(bInDomain(mVal, 5, 6))
	{
		LcdSw_ClrFullWindow(0);
	}
	
	
}



#endif // U_SYS_Test_Lcd
/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

#if U_SYS_Test_Lcd == 1
void sim_EvtShow(void)
{	
U32 mVal;
U32 mIniAdr;

	IniEvtAll();
	LcdCstPage_CheckCst();
	IniPageNum();
	
	for(mVal=0; mVal<400; mVal++)
	{
		if((mVal%4) == 0)
		{
			mIniAdr = mVal/4;
			sim_evt_show_one(mIniAdr);
		}
		Exec_MainOrEvtWindow();	
		lcdTask_JdgKey();
		sim_evt_show_SetTmrArrivedRefresh(0);
	}
	// 在page_main, 只要有事件total!=0 则进优先级最高的页面。
	
}

#endif // U_SYS_Test_Lcd



#if U_SYS_Test_Lcd == 1
void sim_evt_show_SetTmrArrivedRefresh(BOOL bArrived)
{
	bArrived = bArrived;
	if(bArrived)
	{
		SetTickTaskSign(TASK_PageEvtChkChange);
	}
}
#endif // U_SYS_Test_Lcd



#if U_SYS_Test_Lcd == 1
// 参考 test_MCycle_Return();
void sim_evt_show_one(U32 mVal)
{
	if(bInDomain(mVal, 1, 3))
	{
		sim_LoadNewEvent(U_EvtCls_Dsab, mVal, U_Disable_EVT, 0);
	} 
	//page=3, evtCls=5
	// 第2次， change show total.
	
	// 事件撤销：
	else if(bInDomain(mVal, 3, 5))
	{
		sim_LoadNewEvent(U_EvtCls_Dsab, mVal-2, U_DisableRstr_EVT, 0);
	}
	
	
	
	// 故障，仅此一条：
	else if(bInDomain(mVal, 5, 6))
	{
		sim_LoadNewEvent(U_EvtCls_Fault, mVal, U_Fault_EVT, 0);
	}
	
	
	
	// 高优先级
	else if(bInDomain(mVal, 6, 7))
	{
		sim_LoadNewEvent(U_EvtCls_Link, mVal, U_ModuManuRun_EVT, 0);
	}
	
	
	// 高优先级
	else if(bInDomain(mVal, 7, 8))
	{
		sim_LoadNewEvent(U_EvtCls_Alarm, mVal, U_Alarm_EVT, 0);
	}
	
	
	// 最高优先级
	else if(bInDomain(mVal, 8, 9))
	{
		sim_LoadNewEvent(U_EvtCls_Extg, mVal, U_ExtgAnnuRun_EVT, 0);
	}
	
	// 最高优先级 又一条，观察 应reFresh, 不应first.
	else if(bInDomain(mVal, 9, 10))
	{
		sim_LoadNewEvent(U_EvtCls_Extg, mVal, U_ExtgAnnuRun_EVT, 0);
	}
	
	
	// 新的优先级更低的事件：
	else if(bInDomain(mVal, 10, 11))
	{
		sim_LoadNewEvent(U_EvtCls_Link, mVal, U_ModuManuRun_EVT, 0);
	}
	
	
	// 翻页 到 非事件页面
	else if(bInDomain(mVal, 11, 20))
	{
		if(bPageIsEvent())
		{
			SetKeyValueWhenPsswOk(U_KEY_Return);
		}
	}
	//6,1,5,4 fault, 7 
	
	
	// 非最高优先级事件，在MCycle里，退出
	else if(bInDomain(mVal, 20, 21))
	{
		sim_LoadNewEvent(U_EvtCls_Link, mVal, U_ModuManuRun_EVT, 0);
	}
	
	// 最高优先级事件，首次换页面，后续只更新。
	else if(bInDomain(mVal, 22, 30))
	{
		sim_LoadNewEvent(U_EvtCls_Extg, mVal, U_ExtgAnnuRun_EVT, 0);
	}
	
	
	
}

#endif // U_SYS_Test_Lcd
/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

#if U_SYS_Test_Lcd == 1
// 测试LCD LIB的执行时间
void TestLcdTmr_Ing(void)
{
U32 ii;

	for(ii=0; ii<10; ii++)
	{
		MyTimer_IntrHander(1); // U_TmrDrive_1 //useLib:125.9 us; 自己做55.6 us;
	}
	
	// 《Lcd_Driver_V0.0.0.1_3.lib》
	for(ii=0; ii<10; ii++)
	{
		Show_Fig_RightAllign(2, 20, 555, 5); // 300.7	us
		ExecLcdShow(); 		// 17 070.3	us
	}
	
	LcdSw_cstText(2, 20, "测试显示"); // 250.2	us
	ExecLcdShow(); 			// 29 908.1	us
	LcdSw_cstText(2, 20, "测试显示");
	ExecLcdShow();
	
	LcdSw_ClrFullWindow(~0); //55.3	us
	ExecLcdShow(); 			// 210 964.5	us
	LcdSw_ClrFullWindow(~0);
	ExecLcdShow();
	
	LcdSw_HvLine(0, 0, 63, 0); // 116.3	us
	ExecLcdShow(); 			// 10 696.8	us
	LcdSw_HvLine(0, 0, 63, 0);
	ExecLcdShow();
	
	
	LcdSw_SetRectangle(0, 0, 63, 63); // 117	us
	ExecLcdShow(); 			// 126 812.9	us
	LcdSw_SetRectangle(0, 0, 63, 63);
	ExecLcdShow();
	
}
#endif // U_SYS_Test_Lcd


/******************************************************************************
* FUNC: //
******************************************************************************/

#if U_SYS_Test_Lcd == 1
void TestLcdTmr_Start(void)
{
U32 ii;

   	ExecAllToLcdRam();
	for(ii=0; ii<20; ii++)
	{
		LcdSw_HvLine(
					2,   1+ii,
					59,  1+ii);
   		ExecAllToLcdRam();
        ExecLcdShow();
	}




	MyInt_Disable(U_Hd_Int_TIMER_SysTick);
	for(ii=0; ii<20; ii++)
	{
		ExecLcdShow();
	}
	
	
	TestLcdTmr_Ing();
	
	
	MyInt_Enable(U_Hd_Int_TIMER_SysTick);
}
#endif // U_SYS_Test_Lcd







/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
			// page = pageMCycleReturn();
			// PageEntry(page);
******************************************************************************/

#if U_SYS_Test_Lcd == 1
void test_MCycle_Return(void)
{
PAGEWORD mNowPage;

	IniEvtAll();
	LcdCstPage_CheckCst();
	mNowPage = GetPgNum_Main();
	SetPageNum(mNowPage);	
	test_MCycle_KeyReturn();
	//带状态page: P000, 007, 011.
	//  不带状态: P000 .
	
	// 新事件
	sim_LoadNewEvent(U_EvtCls_Alarm, 1, U_Alarm_EVT, 0);
	test_MCycle_KeyReturn();
	//带状态page: P001, 007, 011.
	//  不带状态: P001
	
	sim_LoadNewEvent(U_EvtCls_Fault, 1, U_Fault_EVT, 0); // 7.53us
	test_MCycle_KeyReturn();
	//带状态page: P001, 004, 007, 011.
	//  不带状态: P001, 004.
	
	sim_LoadNewEvent(U_EvtCls_Link, 1, U_ModuAck_EVT, 0);
	test_MCycle_KeyReturn();
	//带状态page: P001, 005, 004, 007, 011.
	//  不带状态: P001, 005, 004.
	
	sim_LoadNewEvent(U_EvtCls_Extg, 1, U_ExtgSprayAck_EVT, 0);
	test_MCycle_KeyReturn();
	//带状态page: P006, 001, 005, 004, 007, 011.
	//  不带状态: P006, 001, 005, 004.
	
	sim_LoadNewEvent(U_EvtCls_Spvs, 1, U_Spvs_EVT, 0);
	test_MCycle_KeyReturn();
	//带状态page: P006, 001, 005, 004, 007, 011.
	//  不带状态: P006, 001, 005, 004.
	
	sim_LoadNewEvent(U_EvtCls_Dsab, 1, U_Disable_EVT, 0);
	test_MCycle_KeyReturn();
	//带状态page: P006, 001, 005, 004, 003, 007, 011.
	//  不带状态: P006, 001, 005, 004, 003.
	
	// 事件撤销：
	sim_LoadNewEvent(U_EvtCls_Fault, 1, U_FaultRstr_EVT, 0);
	test_MCycle_KeyReturn();
	//带状态page: P006, 001, 005, 003, 007, 011.
	//  不带状态: P006, 001, 005, 003.
	
	sim_LoadNewEvent(U_EvtCls_Link, 1, U_ModuAckRstr_EVT, 0);
	test_MCycle_KeyReturn();
	//带状态page: P006, 001, 003, 007, 011.
	//  不带状态: P006, 001, 003.
	
	sim_LoadNewEvent(U_EvtCls_Extg, 1, U_ExtgSprayAckRstr_EVT, 0);
	test_MCycle_KeyReturn();
	//带状态page: 001, 003, 007, 011.
	//  不带状态: 001, 003.
	
	sim_LoadNewEvent(U_EvtCls_Dsab, 1, U_DisableRstr_EVT, 0);
	test_MCycle_KeyReturn();
	//带状态page: P001, 007, 011.
	//  不带状态: P001.
	
}
#endif // U_SYS_Test_Lcd



#if U_SYS_Test_Lcd == 1
void test_MCycle_KeyReturn(void)
{
U8 ii;
	
	for(ii=0; ii<20; ii++)
	{
		SetPageNum(pageMCycleReturn());
	}
}

#endif // U_SYS_Test_Lcd
/******************************************************************************
* FUNC: // load 事件
*   IN:
*  OUT: 
******************************************************************************/

BOOL sim_LoadNewEvent(U8 mCls, U8 mAdrIni, U8 mThing, U8 auxDelayS)
{
	DevSet_SimAdr(mAdrIni, &stSimTrans.unDev);
	stSimTrans.type = mAdrIni;
	stSimTrans.thing = mThing;
	stSimTrans.thiFurther = auxDelayS;
#if U_SYS_ForbidHardWare == U_NO 
	GetRamEvtTimer(&stSimTrans.evtClock);
#endif // U_SYS_ForbidHardWare
	
	switch(mCls)
	{
		case U_EvtCls_Alarm:
			stSimTrans.type = DETE_TYPE_Butt;
			return Buf_Alarm(&stSimTrans);
		case U_EvtCls_Fault:
			stSimTrans.type = DETE_TYPE_Wen;
			return Buf_Fault(&stSimTrans);
		case U_EvtCls_Link:
			stSimTrans.type = DETE_TYPE_ShuRu;
			return Buf_Link(&stSimTrans);
		case U_EvtCls_Extg:
			stSimTrans.type = DETE_TYPE_ShuRu;
			return Buf_Extg(&stSimTrans);
		case U_EvtCls_Spvs:
			stSimTrans.type = ~0;
			return Buf_Spvs(&stSimTrans);
		case U_EvtCls_Dsab:
			stSimTrans.type = DETE_TYPE_XiaoNiu;
			return Buf_Disable(&stSimTrans);
			
		default:
			break;
	}
	return FALSE;
}

/******************************************************************************
* FUNC: //
******************************************************************************/

/******************************************************************************
* FUNC: // END
*   IN:
*  OUT: 
******************************************************************************/
