/*
;*********************************************************************************************************
;*                                                
;*                            ¶ÔÏó: hw01_Timer
;*
;*                        (c) Copyright 2010-2018, ½¯Ñ©Ã·
;*                              All Rights Reserved
;*                                    Ver1.0
;* File : hw01_Timer.h
* @Cpu     LPC177x_8x   
;* By   : ½¯Ñ©Ã·
;* Ê±¼ä : 2010-10-11
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
/******************       È«¾Ö³£Á¿¶¨Òåý     *********************/
/*******************************************************************/

enum emTmrDriveId{  // uint8 tmrDriveId;
	U_TmrDrive_0 = 0, //¶ÔÓ¦Ó²¼þ
	U_TmrDrive_1 = 1, //
};
#define U_TMR_Drive_ID_MAX  2
 
#define U_TMR_Drive_Default_ID  U_TmrDrive_0
/*******************************************************************/
/******************       Êý¾Ý½á¹¹¶¨Òåý     *********************/
/*******************************************************************/
 


/*******************************************************************/
/********************* Ë½ÓÐ³ÉÔ±±äÁ¿,º¯Êý¼°³£Á¿    *******************/
/*******************************************************************/
//Private:
#ifdef  hw01_Timer_C


uint8  m_Time1Run;

uint8  m_Time2Run;
void Init_CTimeN(LPC_TIM_TypeDef *TIMx, IRQn_Type IRQn, U32 mTmrUs);

#endif  // hw01_Timer_C
/*******************************************************************/
/****************     ¹«ÓÐ³ÉÔ±±äÁ¿,º¯Êý¼°³£Á¿     ******************/
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

