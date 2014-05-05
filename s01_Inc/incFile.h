#ifndef __incFile__H__
#define __incFile__H__
/******************************************************************************
* @file    incFile.h
* @author  yx
* @version V1.0
* @date    2012-01-05
* @brief   应用层的所有.h
* 
#include  "incFile.h"
******************************************************************************/

//  "Version.h"
/*================= CPU  =======================================*/
// #include  <string.h>
/*=================  ================================================*/

// #include  "incCommonHwCpu.h" //《s14_HardWareCpu》.h 用。
// #include  "incCommonHwEx.h" // 《s15_HardWareEx》.c 用。
// #include  "incCommonPeriph.h" //《Periph》.c 用

/*=================  ================================================*/
//----------------- Main --------------------------------// 
// #include  "codeTest.h"
// #include  "mRunTask.h"
// #include  "CpuReg.h"

//-----------------   --------------------------------// 
#include  "prjCompileCon.h" // 编译控制 数据类型等。每个文件都需要包含。

// #include  "prjDataType.h"
// #include  "prjFosc.h"
//----------------- Common --------------------------------//
#include  "incSysCommon.h"
// #include  "sysDef.h"		//液晶像素、机器号、单元号 等系统定义
// #include  "prjBool.h"
// #include  "codeComm.h"		//数据、buf等常规操作
// #include  "sysStatus.h"	//RAM-Status, ROM-Config

#include  "codeCrc.h"
#include  "cstBits.h"
#include  "bufCircle.h"


#include  "sysStatus.h"
#include  "tmrTick.h"

//----------------- Struct --------------------------------//
#include  "strClock.h"
#include  "strDevice.h"
#include  "strEvtTrans.h"
#include  "canFrame.h"

// #include  "strDevMLAT.h"  // TCommonMLAT_st  // TModuMLAT_st
// #include  "loopFieldTypeState.h"

//----------------- Board --------------------------------//
#include  "sysPanel.h" // 系统单元
#include  "sysMachine.h"
#include  "meBoard.h"  // 软硬件版本

//----------------- EvtBuf --------------------------------//

#include  "evtStrDef.h"
#include  "evt_Buf_incOut.h"

//#include  "evtInterface.h"


//----------------- HardWareCpu --------------------------------//


//----------------- HardWareEx --------------------------------//
//----------------- HardWareLcd --------------------------------//
// #include  "LcdLib_incOut.h"
// #include  "hwEx15_lcd_swBuf.h"

//----------------- PhInterface --------------------------------//
#include  "hw00_CallBack.h"
#include  "hw00_HdInt.h"
#include  "HdInterface.h" //不易归类的 periph.
#include  "CpuReg.h"

#include  "CanHd_Interface.h"
#include  "fls_Interface.h"
#include  "UartHd_Interface.h"
//----------------- Periph --------------------------------//

#include  "phClock.h"
#include  "phWatchDogTask.h"

#include  "phIoScan.h"
#include  "phIoKeyScan.h"
#include  "keyBufJdgLib_incOut.h"
#include  "phIoLed.h"
#include  "phIoSound.h"
// #include  "phPowerCheck.h"

// #include  "bufUart.h"

// #include  "fls_Interface.h"  //被PeriphSave 等调用 
			//读可以直接对其调用，
			//write和erase要通过"flsWrite.c"　 "flsErase.c"


//----------------- Periph - Can --------------------------------//
// #include  "bufCan.h"
#include  "Can_Manage.h"

//----------------- Periph - Save --------------------------------//
// #include  "FlsTask.h" //接口函数

#include  "saveTask.h"

// 《PhSaveDef》
// #include  "flsInqPoint.h"
// #include  "flsAdrCalculate.h"
// #include  "strFlsItmStruct.h"
// #include  "strFlsAdrDef.h"
// #include  "strFlsQue.h"

// 《PhSaveManage》
// #include  "saveManage.h"
// #include  "flsWrApplySave.h"
// #include  "flsWrApplyBuf.h"
// #include  "flsCopyTask.h"
// #include  "FlsTask.h"

// #include  "flsWrite.h"
// #include  "flsErase.h"


// 《PerighSaveHist》
// #include  "historyClsDef.h"

// #include  "saveHistory.h"
// #include  "historyWrite.h"
// #include  "saveHistPoint.h"
// #include  "historyWrBuf.h"
// #include  "historyRead.h"
// #include  "histCopy.h"   // 还未做；
// #include  "hist_Inc.h"

// 《PerighSave》
// #include  "saveOthers.h"
// #include  "saveLinkProg.h"
// #include  "saveField.h"
// #include  "savePnConfig.h"
// #include  "saveMachProbat.h"
// #include  "savePowerOff.h"
// #include  "saveUserLogin.h"
// #include  "saveDisable.h"
// #include  "saveNote.h"
// #include  "saveMeStatus.h"
// #include  "saveNetMachine.h"
// #include  "saveOthers.h"
// #include  "save_inc.h"  // 《PeriphSave》的 include

// 《PhSaveSim》
// #include  "sim_flsInqDef.h"
// #include  "sim2_flsInqPoit.h"
// #include  "sim1_flsInqPoit.h"
// #include  "sim_saveHist.h"


//----------------- LcdPage --------------------------------//

// #include  "lcd_Interface.h"

#include  "lcdShowTask.h"

#include  "lcdSub_Pssw.h"
//----------------- LcdSub --------------------------------// 


//----------------- LcdConst --------------------------------//


//----------------- CanProtocal --------------------------------//

//----------------- EventStr --------------------------------// 
//----------------- EventBuf --------------------------------// 

#include  "evt_Buf_incOut.h"


//----------------- UserLogin --------------------------------//



//----------------- MachProbat --------------------------------//


//----------------- Other --------------------------------//

//----------------- Test --------------------------------//

/*================= 常数 ============================================*/


/*=================  ================================================*/


#endif //__incFile__H__

