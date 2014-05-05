/**********************************************************************
* $Id$		system_LPC177x_8x.h			2011-06-02
*//**
* @file		system_LPC177x_8x.h
* @brief	CMSIS Cortex-M3 Device Peripheral Access Layer Source File
*			for the NXP LPC177x_8x Device Series
* @version	1.0
* @date		02. June. 2011
* @author	NXP MCU SW Application Team
* 
* Copyright(C) 2011, NXP Semiconductor
* All rights reserved.
*
***********************************************************************
* Software that is described herein is for illustrative purposes only
* which provides customers with programming information regarding the
* products. This software is supplied "AS IS" without any warranties.
* NXP Semiconductors assumes no responsibility or liability for the
* use of the software, conveys no license or title under any patent,
* copyright, or mask work right to the product. NXP Semiconductors
* reserves the right to make changes in the software without
* notification. NXP Semiconductors also make no representation or
* warranty that such application will be suitable for the specified
* use without further testing or modification.
**********************************************************************/

#ifndef __SYSTEM_LPC177x_8x_H
#define __SYSTEM_LPC177x_8x_H

#ifdef __cplusplus
extern "C" {
#endif


//#include  "CBoardDef.h"	  
#include <stdint.h>

extern uint32_t SystemCoreClock;      /*!< System Clock Frequency (Core Clock)  	*/
extern uint32_t PeripheralClock;	    /*!< Peripheral Clock Frequency (Pclk) 	    */
extern uint32_t EMCClock;			        /*!< EMC Clock                              */
extern uint32_t USBClock;			        /*!< USB Frequency 						              */


/**
 * Initialize the system
 *
 * @param  none
 * @return none
 *
 * @brief  Setup the microcontroller system.
 *         Initialize the System and update the SystemCoreClock variable.
 */
extern void SystemInit (void);

/**
 * Update SystemCoreClock variable
 *
 * @param  none
 * @return none
 *
 * @brief  Updates the SystemCoreClock with current core Clock
 *         retrieved from cpu registers.
 */
extern void SystemCoreClockUpdate (void);

/*----------------------------------------------------------------------------
  Define clocks
 *----------------------------------------------------------------------------*/
 
//#define XTAL        (12000000UL)        /* Oscillator frequency               */  
#if _Board_DOMM == 0 
#define XTAL        (24000000UL)        /* Oscillator frequency               */
#else
#define XTAL        (12000000UL)        /* Oscillator frequency               */ 
#endif 



#define OSC_CLK     (      XTAL)        /* Main oscillator frequency          */
#define RTC_CLK     (   32768UL)        /* RTC oscillator frequency           */
#define IRC_OSC     (12000000UL)        /* Internal RC oscillator frequency   */   
#define WDT_OSC		  (  500000UL)		/* Internal WDT oscillator frequency  */



/*
//-------- <<< end of configuration section >>> ------------------------------
*/

#ifdef __cplusplus
}
#endif

#endif /* __SYSTEM_LPC177x_8x_H */

/******************************************************************************
当前配置： 2013.8.8 yx；
晶振  XTAL = 12M 
系统时钟 SystemCoreClock ：//PllOut= 12M晶振* 10 = 120M 	//PLL0CFG_Val
外围时钟 PeripheralClock ：// APB时钟是120M/4=30M    	//PCLKSEL_Val
外设功率控制寄存器  PCONP_Val
******************************************************************************/
