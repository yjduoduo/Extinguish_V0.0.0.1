#ifndef __hwAndLib__H__
#define __hwAndLib__H__
/******************************************************************************
* @file    hwAndLib.h
* @author  yx
* @version V1.0
* @date    2012-01-05
* @brief   驱动集合，lib 或 CPU-serial.inc； periph用。
* 
#include  "hwAndLib.h"  // 驱动集合，lib 或 CPU-serial.inc； periph用。
******************************************************************************/
//


/*================= CPU LM3S2793 =======================================*/
//#include  <string.h>
/*=================  ================================================*/

// inc 
#include "hw_ints.h"
#include "hw_memmap.h"
#include "hw_types.h"
#include "hw_can.h"
#include "hw_gpio.h"

// s50_DriverLib
#include "uart.h"
#include "debug.h"
#include "gpio.h"
#include "interrupt.h"
#include "systick.h"
#include "sysctl.h"  //有 SYSCTL_PERIPH_GPIOB 的定义。
#include "can.h"
#include "timer.h"
#include "adc.h"
#include "watchdog.h"
#include "ssi.h"
#include "i2c.h"


/*=================  ================================================*/


/*=================  ================================================*/


#endif //__hwAndLib__H__

