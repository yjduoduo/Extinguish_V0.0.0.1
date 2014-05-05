/*
;*********************************************************************************************************
;*                                                
;*                            ����: hw01_Timer
;*
;*                        (c) Copyright 2010-2018, ��ѩ÷
;*                              All Rights Reserved
;*                                    Ver1.0
;* File : hw01_Timer.h
* @Cpu     LPC177x_8x   
;* By   : ��ѩ÷
;* ʱ�� : 2010-10-11
;*********************************************************************************************************
;*/
//#include  "hw01_Timer.h"

#ifndef hw01_Timer_H
#define hw01_Timer_H	  

#include <prjCompileCon.h> 
#include "lpc177x_8x_timer.h" 


#ifdef  hw01_Timer_C
#define EX_hw01_Timer
#else
#define EX_hw01_Timer extern 
#endif

/*******************************************************************/
/******************       ȫ�ֳ��������     *********************/
/*******************************************************************/

enum emTmrDriveId{  // uint8 tmrDriveId;
	U_TmrDrive_0 = 0, //��ӦӲ��
	U_TmrDrive_1 = 1, //
};
#define U_TMR_Drive_ID_MAX  2
 
#define U_TMR_Drive_Default_ID  U_TmrDrive_0
/*******************************************************************/
/******************       ���ݽṹ�����     *********************/
/*******************************************************************/
 


/*******************************************************************/
/********************* ˽�г�Ա����,����������    *******************/
/*******************************************************************/
//Private:
#ifdef  hw01_Timer_C


uint8  m_Time1Run;

uint8  m_Time2Run;
void Init_CTimeN(LPC_TIM_TypeDef *TIMx, IRQn_Type IRQn, U32 mTmrUs);

#endif  // hw01_Timer_C
/*******************************************************************/
/****************     ���г�Ա����,����������     ******************/
/*******************************************************************/
//EX_hw01_Timer:

extern void Init_CTimeDrive(U8 tmrDriveId, U32 mTmrUs);
extern void Close_CTimeDrive(U8 tmrDriveId);


// Int:
extern void TimerRegi_Int_Enable(U8 tmrDriveId);
extern void TimerRegi_Int_Disable(U8 tmrDriveId);

extern   void   TIMER0_IRQHandler(void);  
 
extern   void   TIMER1_IRQHandler(void);   
/******************************************************************************
// END :
******************************************************************************/
#endif  // hw01_Timer_H

