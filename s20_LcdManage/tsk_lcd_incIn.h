#ifndef __tsk_lcd_incIn_H__
#define __tsk_lcd_incIn_H__
/******************************************************************************
* @file    tsk_lcd_incIn.h
* @author  yx
* @version V1.0
* @date    2012-01-05
* @brief   
* 
#include  "tsk_lcd_incIn.h"
******************************************************************************/

#include  "prjCompileCon.h"

//----------------- Main --------------------------------// 
#include  "incSysCommon.h"

//-----------------   --------------------------------// 

#include  "evtStrDef.h"
#include  "evt_Buf_incOut.h"
#include  "strDevice.h"
#include  "strClock.h"

#include  "sysPanel.h" 
//-----------------   --------------------------------// 
#include  "lcd_Para.h"
// #include  "lcd_Interface.h" //显示buf task.

// 应用程序调用的接口。命令发到这里存buf，慢慢向屏上显示。
//#include  "hwEx15_lcd_swBuf.h"   
//-----------------   --------------------------------// 

// #include  "lcdCst_PageNum.h"
// #include  "lcdCst_PageFunction.h"

// #include  "lcdCst_Menu.h"
// #include  "lcdCst_Page.h"
#include  "lcdCst_PgString.h"

// #include  "lcdTask.h"
#include  "lcdShowTask.h"
#include  "lcdTsk_PgNum.h"
#include  "lcdPg_aSchedu.h"
#include  "lcdPg_Status.h"


#include  "lcdPg_Page.h"
#include  "lcdPg_pUserLogin.h"
// #include  "lcdPg_MainAct.h"
#include  "lcdPg_ShowEvt.h"
// #include  "lcdPg_ShowState.h"
// #include  "lcdPg_Menu.h"
// #include  "lcdPg_pPsw.h"
#include  "lcdPg_pSelfChk.h"

#include  "lcdSub_ModeTextFig.h"
#include  "lcdSub_SwDev.h"
#include  "lcdSub_SwOneEvt.h"



/******************************************************************************
// END :
******************************************************************************/
#endif // __tsk_lcd_incIn_H__

