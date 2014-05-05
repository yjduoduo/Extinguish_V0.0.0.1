/*
*********************************************************************************************************
*                                                
*                               对象: hw01_Timer
*                        (c) Copyright 2010-2018, jxm
*                              All Rights Reserved
*                                    Ver1.0
* File : hw01_Timer.C
* @Cpu     LPC177x_8x   
* By   : jxm
* Date : 2011-11-06
*********************************************************************************************************
*/ 
#define   hw01_Timer_C   
#include  "hw01_Timer.h" 

#include  "hw00_CallBack.h"

// #include  "CSysTimeCtrl.h" 
// #include  "CTab.h" 
// #include  "CAutoCtrl.h" 
// #include  "CSysGasTime.h"
/*================= 常数 ============================================*/

/*================= 结构定义 ============================================*/
typedef struct{
	U8 tmrDriveId;
	LPC_TIM_TypeDef *pTim;
	IRQn_Type  IRQn;
}TTimerPeriDef_st;

// 只表明对应关系。变timer时，还是要注意，尤其是中断。
const TTimerPeriDef_st cstTimerPeriDef[U_TMR_Drive_ID_MAX+1] = 
{
	{U_TmrDrive_0, (LPC_TIM_TypeDef *)LPC_TIM0, TIMER0_IRQn}, // 
	{U_TmrDrive_1, (LPC_TIM_TypeDef *)LPC_TIM1, TIMER1_IRQn}, // 
		
	// default , 参考 U_TMR_Drive_Default_ID
	{U_TmrDrive_0, (LPC_TIM_TypeDef *)LPC_TIM0, TIMER0_IRQn}, // 
};
/*=================  ================================================*/
		
/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
void Init_CTimeDrive(U8 tmrDriveId, U32 mTmrUs)
{
	if(tmrDriveId >= U_TMR_Drive_ID_MAX)
	{
		return;
	}
	
	mTmrUs /= 2;
	
	Init_CTimeN(cstTimerPeriDef[tmrDriveId].pTim, 
			   cstTimerPeriDef[tmrDriveId].IRQn, mTmrUs);
	
}


void Close_CTimeDrive(U8 tmrDriveId)
{
	if(tmrDriveId >= U_TMR_Drive_ID_MAX)
	{
		return;
	}
	TimerRegi_Int_Disable(tmrDriveId);
	TIM_Cmd(cstTimerPeriDef[tmrDriveId].pTim, DISABLE);
	
}



/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
#define U_Timer_PrescaleValue    100   // 100us 为单位


void Init_CTimeN(LPC_TIM_TypeDef *TIMx, IRQn_Type IRQn, U32 mTmrUs)
{
	TIM_TIMERCFG_Type TIM_ConfigStruct;
	TIM_MATCHCFG_Type TIM_MatchConfigStruct ; 

	TIM_ConfigStruct.PrescaleOption = TIM_PRESCALE_USVAL;
	TIM_ConfigStruct.PrescaleValue	= U_Timer_PrescaleValue;
	
		TIM_Init(TIMx, TIM_TIMER_MODE,&TIM_ConfigStruct); 
 	 
 		// use channel 0, MR0
		TIM_MatchConfigStruct.MatchChannel = 0;
		// Enable interrupt when MR0 matches the value in TC register
		TIM_MatchConfigStruct.IntOnMatch   = TRUE;
		//Enable reset on MR0: TIMER will reset if MR0 matches it
		TIM_MatchConfigStruct.ResetOnMatch = TRUE;
		//Stop on MR0 if MR0 matches it
		TIM_MatchConfigStruct.StopOnMatch  = FALSE;
		//Toggle MR0.0 pin if MR0 matches it
		TIM_MatchConfigStruct.ExtMatchOutputType =TIM_EXTMATCH_TOGGLE;
		// Set Match value, count value of 10000 (10000 * 100uS = 1000000us = 1s --> 1 Hz)
		TIM_MatchConfigStruct.MatchValue   = (mTmrUs / U_Timer_PrescaleValue); //mTmrUs中断1次  
		
 		TIM_ConfigMatch(TIMx, &TIM_MatchConfigStruct);

		//preemption = 1, sub-priority = 1 //
		NVIC_SetPriority(IRQn, ((0x01<<3)|0x01));

		// Enable interrupt for timer 0 //
		NVIC_EnableIRQ(IRQn);

		// To start timer
		TIM_Cmd(TIMx, ENABLE);
		
	
}

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
// Int:
void TimerRegi_Int_Enable(U8 tmrDriveId)
{
	if(tmrDriveId >= U_TMR_Drive_ID_MAX)
	{
		return;
	}
	NVIC_EnableIRQ(cstTimerPeriDef[tmrDriveId].IRQn);
}

void TimerRegi_Int_Disable(U8 tmrDriveId)
{
	if(tmrDriveId >= U_TMR_Drive_ID_MAX)
	{
		return;
	}
	NVIC_DisableIRQ(cstTimerPeriDef[tmrDriveId].IRQn);
	
}

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
void  TIMER0_IRQHandler(void)
{    
	if(TIM_GetIntStatus(LPC_TIM0, TIM_MR0_INT)== SET)
	{			   
		CallBack_Tmr_Intr(U_TmrDrive_0);
	}
	TIM_ClearIntPending(LPC_TIM0, TIM_MR0_INT);
}

void  TIMER1_IRQHandler(void)
{    
	if(TIM_GetIntStatus(LPC_TIM1, TIM_MR0_INT)== SET)
	{		
		CallBack_Tmr_Intr(U_TmrDrive_1);
	}		
	TIM_ClearIntPending(LPC_TIM1, TIM_MR0_INT);
}


/******************************************************************************
* FUNC: // END
*   IN:
*  OUT: 
******************************************************************************/
