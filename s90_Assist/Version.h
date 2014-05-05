#ifndef __Version_H__
#define __Version_H__
/******************************************************************************
* @file    Version.h
* @author  yx
* @brief   版本记录
TmrTick_Driver_V1.1.lib
******************************************************************************/

/******************************************************************************
// 版本记录：
LoadSoundFuncToHd  未输出
******************************************************************************/

/*=============================================================================



01.《Extinguish_V0.0.0.1__0.1.28》2013.11.02 15:17  Compiled
		改正: 历史记录的地址的定义错误。
		add: bCheckSaveItemConstDef();
01.《Extinguish_V0.0.0.1__0.1.27》2013.11.02 14:20  Compiled
	改错升级 《Lcd_Driver_V0.0.0.1_10_Cn12En6Asc6.lib》
01.《Extinguish_V0.0.0.1__0.1.26》2013.11.02 12:12  Compiled
	加入wxj《LCD V1.2.1.JFB_wxj_time2013年10月22日》的页面。
01.《Extinguish_V0.0.0.1__0.1.25》2013.10.31 10:24  Compiled
	加reset机制。 iCan unit inLine 做。
01.《Extinguish_V0.0.0.1__0.1.24》2013.10.31 09:47  Compiled
	在硬件测试界面，能够定时收发。iCan连eCan。 但不明原因，发eCan消息首次不产生发送中断，奇怪。
	连小点数的回路板能收到反馈、反馈撤销， 在LCD上显示。
01.《Extinguish_V0.0.0.1__0.1.23》2013.10.31 10:47  Compiled
	flsSave.lib 文件 未测试，交wxj测试。
	《s78_30_SaveSim》在这个文件"sim_saveItem.c"里进行测试。
01.《Extinguish_V0.0.0.1__0.1.22》2013.10.29 21:39  Compiled
	把 flsSave.lib 文件添加进来，准备测试。
01.《Extinguish_V0.0.0.1__0.1.21》2013.10.24 16:31  Compiled
	因为 "strDevice.h" "sysDef.h"U_PANEL_TOTAL_SEQU_MAX变，
		升级版本《DriverEventBuf_V0.0.0.1_1.6》《DriverFlsSave_V0.0.0.1_0.1.8》
01.《Extinguish_V0.0.0.1__0.1.21》2013.10.24 14:17  Compiled
	flsItem 增加U_FlsSave_MachAlarmNote; 
		TFlsRelatAddr_st; TFlsExtgZoneConfig_st;  TFlsLoopAddrRegist_st; 存储未做。
	整理 panel.c ， U_PANEL_TOTAL_SEQU_MAX 128->250.
	添加11S协议，no test;
	add:  "OpeaAndEvtState"  声、光 状态
	即使有按键，在有优先级更高的事件时，也切换页面了，不知为什么？ bNewEvtIsHigherThanNow() MCycle->bEvent
	在查看all event total时，不希望被新事件打断。
01.《Extinguish_V0.0.0.1__0.1.20》2013.10.17 14:43   Compiled
	显示事件 调整。 88字符字库。
	use : ExecTmrArrivedLcdShow();
01.《Extinguish_V0.0.0.1__0.1.19》2013.10.16 21:39   Compiled
	事件页面一屏 有二种 的定义 cstEvtWindowDef[]
	事件页面能切换。 
	事件能显示，但不完整，屏蔽2条时未显示。  现在定时加事件。
01.《Extinguish_V0.0.0.1__0.1.18》2013.10.15 12:03   Compiled
	sim  事件页面一屏 只一种 的定义。 cstEvtWindowDef[]
01.《Extinguish_V0.0.0.1__0.1.17》2013.10.14 22:11   Compiled
	sim_EvtBuf.c  V1.1 mSimCls = U_EvtCls_Link;  U_OneScr_DevBuf_MAX = 1;
	evtBuf code in project.
01.《Extinguish_V0.0.0.1__0.1.16》2013.10.14 15:43   Compiled
	测试 evtBuf. 针对 "EventAndWinBuf" 
	sim_EvtBuf.c  V1.0  mSimCls = U_EvtCls_Link;  U_OneScr_DevBuf_MAX = 3;
01.《Extinguish_V0.0.0.1__0.1.15》2013.10.11 22:08   Compiled
	调整文件夹序号。
01.《Extinguish_V0.0.0.1__0.1.14》2013.10.11 22:08   Compiled
	can 文件的收发 已测试。
	有关协议的部分，脱离 lib, 转移到 can11sFile.c. 有关evtFile的部分为细心摘除。
		但CanID因为和THdCanFrame_st捆绑了，所以也带到了lib里。
	use CanBuf_Driver_V0.0.0.1_0.0.6.lib
01.《Extinguish_V0.0.0.1__0.1.13》2013.10.11 00:01   Compiled
	文件发送。 文件部分未测试。
01.《Extinguish_V0.0.0.1__0.1.12》2013.10.10 20:58   Compiled
	接收文件 "can11sFile.c"  "can_DataOrFile.c"
	显示的执行时间长，是因为LCD的引脚控制 需要延时10us，否则显示不正常。
01.《Extinguish_V0.0.0.1__0.1.11》2013.10.09 08:37   Compiled
	显示"00001"大约共需要20ms, 还是太长了。
	测试硬件页面  U_P068_TsAllHardware 能用。 2013.10.08
	《Lcd_Driver_V0.0.0.1_2.lib》		2013.10.08
01.《Extinguish_V0.0.0.1__0.1.10》2013.9.30 11:05   Compiled
	调整菜单 和 页面。能响应按键。
	数字输入功能 未调试。
	页面部分 交给 Wei.
01.《Extinguish_V0.0.0.1__0.1.9》2013.9.29 12:22   Compiled
	调试菜单，OK.
01.《Extinguish_V0.0.0.1__0.1.8》2013.9.27 14:01   Compiled
	"lcdSub_ModeTextFig" 改 调用子函数 都以pix. 
01.《Extinguish_V0.0.0.1__0.1.7》2013.9.26 23:46   Compiled
	把12*12 的行列处理。未测试
01.《Extinguish_V0.0.0.1__0.1.6》2013.9.26 19:36   Compiled
	12*12 点阵 汉字 和 12*8字符 能显示； 但现在的行列有问题。
	调 CAN bps ; 设置5us=watcher iCan 100K bps.
	现在未涉及 通讯 存储的逻辑。
01.《Extinguish_V0.0.0.1__0.1.5》2013.9.26 16:26   Compiled
	检测项：
	液晶显示；若4行显示不完全，则是其他硬件驱动卡在哪里出不来了。
	看门狗。OK, 无字符显示。仿真时stop.
	实时时钟、晶振计时；
	iCan收发， eCan收发，显示接收帧计数； 3s发一帧； 接线: iCan与eCan连接；
	串口收发，显示接字节计数； 3s发2字节； 接线:2和3脚连接；
	flash 擦除、写、读；正确显示" V ", 错误显示" X ".
	按键: 按下按键有提示。
	电源状态检测线：3条，0正常 1故障；
	电源检测开关：AD采样值计算的 AD脚上的电压。

	扬声器 驱动 未测试；
	显示12*12点阵字库未测试；

01.《Extinguish_V0.0.0.1__0.1.4》2013.9.26 14:31   Compiled
	调整显示。
	uart0 收发正常； 未用 hw11_Uart， 仍用 CUart.
	8*8 正常。
01.《Extinguish_V0.0.0.1__0.1.3》2013.9.26 00:28   Compiled
	测试显示的字符 都用 8*8 .
01.《Extinguish_V0.0.0.1__0.1.2》2013.9.25 23:56   Compiled
	检测开关 AD;
	电源状态；
	watchDog 设置时间 OK.
	加 8*8 点阵字符 的显示驱动。
01.《Extinguish_V0.0.0.1__0.1.1》2013.9.25 16:36 
	液晶显示: 时钟，晶振定时秒数；
			CAN接收次数( iCan 和 eCan 连接);
			按键；
			Fls写结果； 
	chip1 的 NorFlash 测试，读写失败；
	扬声器 未做；
	串口未做。
	USB 未做。
01.《Extinguish_V0.0.0.1__0.1.0》2013.9.24 
	开始测试; 
	LCD显示 2013.9.24 21:00 
		显示 (0,0)(0,1)； when  U_ShowCharHeight_IsOneRowPage = 1  
		显示 (0,0)(0,1)； when  U_ShowCharHeight_IsOneRowPage = 0 
		12*12 汉字库 不支持。
	CAN 通讯： iCan 和 eCan 通讯成功，有 收、发 中断； 
		bps 未测试。
	Flash: chip=0 erase,write,read OK; 
		chip=1 failed;
	实时时钟：偶尔有连续3s不更新。 断24V后法拉电容可以保持电压，不知能维持多久。


01.《Extinguish_V0.0.0.1__0.0.23》2013.9.23 21:50  Compiled
	eventBuf 增加 insert;
	flsSave.lib 有修改;
01.《Extinguish_V0.0.0.1__0.0.22》2013.9.22 22:16  Compiled
	回路浏览 曲线
	《DriverFlsSave_V0.0.0.1_0.1.5.lib》
	lcd驱动：show text和fig, 增加 color的para.
01.《Extinguish_V0.0.0.1__0.0.21》2013.9.16 09:10  Compiled
	部分按键处理。
	显示驱动 需要加颜色和背景色；为了光标的处理；
	swFig.c 未做。
01.《Extinguish_V0.0.0.1__0.0.20》2013.9.11 00:54  Compiled
	MCycle 页面 调度。"lcdPg_aSchedu"  "lcdPg_MainOrEvt"
01.《Extinguish_V0.0.0.1__0.0.19》2013.9.10 16:45  Compiled
	"DriverEventBuf_V0.0.0.1_0.1.0"
01.《Extinguish_V0.0.0.1__0.0.18》2013.9.10
	“EventAndWinBuf_Driver_V0.0.0.1_0.0.3.lib”
01.《Extinguish_V0.0.0.1__0.0.17》2013.9.9  23:54 Compiled
	用  EventBuf.lib
01.《Extinguish_V0.0.0.1__0.0.16》2013.9.9  19:59 Compiled
	加 canManage 
01.《Extinguish_V0.0.0.1__0.0.15》2013.9.4  17:57 Compiled
	加menu;
	use "OpeaMenu_Driver_V0.0.0.1_0.0.1.lib"
	"lcdCst_OpaMenuInterface" 接口未完成。
01.《Extinguish_V0.0.0.1__0.0.14》2013.9.4  12:09 Compiled
	use: .\s78_phSaveLib\DriverFlsSave_V0.0.0.1_0.1.3.lib
01.《Extinguish_V0.0.0.1__0.0.13》2013.8.28 13:51 Compiled
	add: lcdSub_Pssw.c
	use: .\s70_Periph\KeyBuf_Driver_V0.0.0.1_0.0.3.lib
01.《Extinguish_V0.0.0.1__0.0.12》2013.8.27 17:14 Compiled
	led 和 key扫描 硬仿真，正确。
	Key scan 线未设置成OD.
01.《Extinguish_V0.0.0.1__0.0.11》2013.8.27 11:00 Compiled
	整理中断函数。
	sys_Init();
	灯运行 不亮。
01.《Extinguish_V0.0.0.1__0.0.10》2013.8.26 16:41 Compiled
	add Uart;
	add NorFlash SST39VF800A 驱动。 还缺 扬声器 驱动。
01.《Extinguish_V0.0.0.1__0.0.9》
	用 keyBufDriver；  加电源检测。
	未做: 存储，uart;
01.《Extinguish_V0.0.0.1__0.0.8》
	准备把keyScan 和 keyBuf 分开
01.《Extinguish_V0.0.0.1__0.0.7》2013.8.16 16:16
	加can driver.  error中断需要实测。
01.《Extinguish_V0.0.0.1__0.0.6》2013.8.15 16:47 Compiled
	加 led, key.  Sound的PWM未输出。
01.《Extinguish_V0.0.0.1__0.0.5》2013.8.15 16:47
	加 timer， 
01.《Extinguish_V0.0.0.1__0.0.4》2013.8.13 20:35
	加了 showBuf.
	pcf8563的，IIC;  phClock.
=============================================================================*/

/******************************************************************************
// Use Lib:  in "ProjectStruct.h"

******************************************************************************/


/******************************************************************************
// 记录：
******************************************************************************/
/*=============================================================================

=============================================================================*/


/******************************************************************************
* FUNC: //END
******************************************************************************/
#endif // __Version_H__
