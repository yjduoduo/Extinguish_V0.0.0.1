#ifndef __ProjectStruct_H__
#define __ProjectStruct_H__
/******************************************************************************
* @file    ProjectStruct.h
* @author  yx
* @brief   工程的文件夹结构说明
******************************************************************************/

/*================= 2013.6.29 ================================================*/
	KEIL编译后的工程，导入TKStudio，.h文件就可以右键打开了，
不受不同文件夹的限制。
	TKStudio导入keil工程时，选择ARM并实际选个CPU型号而不是类别，
下次打开时就不会提示重新选择CPU型号。

/*=================  ================================================*/
工程文件：
<bufCan>文件隐藏了 ICAN ECAN使用哪个 hdCan
flash判断状态的初始化在 Init_SaveTask() 里；

/*================= 2013.6.29 ================================================*/
应用程序只允许用《Periph》。
硬件驱动层可以用"HdInterface.h" "hw00_HdInt.h"隔离。
搜索"THdPinItem_st"结构体，可以找出所有的引脚定义。

《s16_CanBufLib》 CAN的数据和文件存储buf操作。

《s18_PeriphSave》flash数据的存储。带任务号。

《s70_Periph》是控制驱动的处理。
		"HdInterface.h" 不单独分类的，都在里面。
《s81_HardWareEx》是CPU外围器件的驱动。
		只允许调用《s80_HardWareCpu》及CpuDriver驱动。
《s80_HardWareCpu》与CPU有关的驱动。
		只允许调用 《s86_driver》；
		"hw00_CallBack.h" 是回调函数。有些中断需要的接口,《Periph》用；
		"hw00_HdInt.h" 应用程序控制中断，与CPU隔离。
《s86_driver》ARM的驱动。 CPU内的ex的驱动。


.\s01_Inc;.\s01_incAssemble;.\s02_Task;.\s03_Common;.\s09_Board;.\s09_Struct;.\s10_EventBuf;.\s11_canProtocal;.\s15_CanManage;.\s16_CanBufLib;.\s17_SimCanBuf;.\s20_LcdPage;.\s21_LcdSub;.\s22_LcdConst;.\s70_Periph;.\s71_PhInterface;.\s80_HardWareCpu;.\s81_HardWareEx;.\s82_HardWareLcd;.\s85_cpuDef;.\s86_driver;


.\X;.\X;.\X;.\X;.\X;.\X;.\X;.\X;.\X;.\X;.\X;

/******************************************************************************
// Use Lib:
《Extinguish_V0.0.0.1__0.1.20》
"Lpc177xDriverLib_V1.0_2.lib"  CPU驱动
"DriverTmrTick_V0.0.0.1_0.1.2.rar"
"DriverOpeaMenu_V0.0.0.1_0.0.8.rar"
"DriverLcd19264_V0.0.0.1_6.rar"
"DriverKeyBuf_V0.0.0.1_0.0.5.rar"
"DriverFlsSave_V0.0.0.1_0.1.8.rar"
"DriverEventBuf_V0.0.0.1_1.4.rar"
"DriverEventAndWinBuf_V0.0.0.1_1.1.rar"
"DriverCanBuf_V0.0.0.1_0.0.6.rar"



《Extinguish_V0.0.0.1__0.0.19》
"Lpc177xDriverLib_V1.0_2.lib"  CPU驱动
"TmrTick_Driver_V1.1.lib" 			in <s03_Common>        定时; 现在用同样的.c文件。
"EventBuf_Driver_V0.0.0.1_0.1.0.lib"	in <s10_EventBuf> 	   事件队列
	"EventAndWinBuf_Driver_V0.0.0.1_0.0.5.lib"
"CanBuf_Driver_V0.0.0.1_0.0.4.lib"		in <s16_CanBufLib>      CAN数据帧和文件存储
"OpeaMenu_Driver_V0.0.0.1_0.0.3.lib"    in <s29_LcdOpeaMenuLib>  菜单
"DriverFlsSave_V0.0.0.1_0.1.4.lib"      in <s78_phSaveLib>       Flash存储
"KeyBuf_Driver_V0.0.0.1_0.0.3.lib"      in <s70_Periph>          按键处理

******************************************************************************/


/******************************************************************************
* FUNC: //END
******************************************************************************/
#endif // __ProjectStruct_H__

