#ifndef __prjFosc_H__
#define __prjFosc_H__
/******************************************************************************
* @file    prjFosc.h
* @author  yx
* @version V1.0
* @date    2012-01-05
* @brief   CPU各种晶振、基础时钟、通讯bps。 in "prjCompileCon.h"
* 
#include  "prjFosc.h"
******************************************************************************/
//
/******************************************************************************
//  :
******************************************************************************/
#define U_SysTimer0_TmrMs   5
#define U_SysTimer1_TmrMs   1

//#define U_TIMER2_NUM  1000 //AD采样周期

#define U_MyTickTmrCycle   5 // ms
#define U_MyTickTmrCycleUs   5000 // us


/******************************************************************************
// 晶振 :
******************************************************************************/
#define MHZ           *1000000L
#define KHZ           *1000L
#define HZ            *1L


#define FOSC	(12MHZ)			// Crystal Oscillator Frequency
#define FCCLK	(48MHZ)			// PLL output frequency (also processor clock frequency)
#define FPCLK	(12MHZ)			// Peripheral frequency
#define FPCLK_M	(12)	
#define FPCLK_RTC	(12MHZ)		// RTC
#define FPCLK_SPI	(24MHZ)		// 设置SSP0时钟FCCLK/2
#define FPCLK_SSP0	(24MHZ)		// 设置SSP0时钟FCCLK/2
#define FPCLK_SSP1	(24MHZ)		// 设置SSP0时钟FCCLK/2
#define FI2CLK      (1MHZ)		//  SMBUS总线通讯率为1MBPS
//#define FI2CLK     500000		//500000//SMBUS总线通讯率为500KBPS
				  



/******************************************************************************
// END :
******************************************************************************/
#endif // __prjFosc_H__

