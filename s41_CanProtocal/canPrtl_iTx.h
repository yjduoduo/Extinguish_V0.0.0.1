#ifndef __canPrtl_iTx_H__
#define __canPrtl_iTx_H__
/******************************************************************************
* @file    canPrtl_iTx.h
* @author  yx
* @version V1.0
* @date    2013-10-22
* @brief   按协议组织CAN帧，并发送;
*		应该把有关11s协议的，都放在"can11sPrtl_iTx"里，但有些命令是针对11s的，现在为省事，都写在这里了。
* 
#include  "canPrtl_iTx.h"
******************************************************************************/
//
#include  "prjCompileCon.h"
// Can帧格式：	
#include  "canProtocalStr.h"
#include  "canFrame.h"
// 

/*================= extern ============================================*/
#ifdef  __canPrtl_iTx_C__
#define EX_canPrtl_iTx
#else
#define EX_canPrtl_iTx extern 
#endif
/*================= 常数 ============================================*/
//#define 
/*================= 结构体定义 ======================================*/

/*================= 公有结构变量声明 ================================*/

/*================= 私有函数声明 ====================================*/
#ifdef  __canPrtl_iTx_C__

// 发送：ID, command, loop, addr:
BOOL iCan11s_tx_DetePrtlPink_InByte1(U8 mCommand,
							U8 mLoop, U8 mAddr);

#endif  //__canPrtl_iTx_C__

/*================= 公有函数声明 ====================================*/
//EX_canPrtl_iTx 
extern void iCan_txNewFrm_ToTxBuf(void);
/*================= 公有函数声明 ====================================*/
//EX_canPrtl_iTx // 测试发送事件：
extern void ICan_Tx_Alarm(U8 mAddr);
/*================= 公有函数声明 ====================================*/
//EX_canPrtl_iTx 
extern void ICan_Tx_Reset(void); // 复位
extern void ICan_Tx_RegistAll(void); // 自动登记
extern void ICan_Tx_HornLedCheck(void); // 灯检
extern void ICan_Tx_Clock(void); // 时钟
extern void ICan_Tx_ClrRegist(void); // 清除登记
extern void ICan_Tx_Inquire_Regist(U8 mLoop); // 查询登记 ?
extern void ICan_Tx_ClrLinkProg(void); // 清除编程
extern void ICan_Tx_PcLoadIng(void); // 计算机编程
extern void ICan_Tx_MachMaster_EnAuto(void); // 主机开启从机 自动允许
extern void ICan_Tx_Silence(void); // 消音
extern void ICan_Tx_HornStrobe_On(void); // 声光 ON
extern void ICan_Tx_HornStrobe_Off(void); // 声光 ON
extern void ICan_Tx_WorkMode_Debug_On(void); // 调试模式
extern void ICan_Tx_WorkMode_Debug_Off(void);
extern void ICan_Tx_AutoManu(void); // 手动自动

// IN: pnType: emPanelType ;
// IN: pnSequ: 板号，1~ ;
extern void ICan_Tx_InqireCommand_Stop(U8 mLoop, U8 mAddr); // 测试命令
extern void ICan_Tx_InqireCommand_Analog_Start(
					U8 mLoop, U8 mAddr); // 测试命令-模拟曲线
extern void ICan_Tx_InqireCommand_Analog_Stop(
					U8 mLoop, U8 mAddr);
extern void ICan_Tx_InqireCommand_DeteData_Start(
					U8 mLoop, U8 mAddr); // 测试命令-探测器内部数据
extern void ICan_Tx_InqireCommand_DeteData_Stop(
					U8 mLoop, U8 mAddr);

// IN: mModuType:  emModuRunAuMaRemote
extern void ICan_Tx_DevRunMess_Run(U8 mLoop, U8 mAddr, 
								U8 mModuType); // 模块启动
extern void ICan_Tx_DevRunMess_Stop(U8 mLoop, U8 mAddr, 
								U8 mModuType); // 模块停止
								
								
// IN:   mDeteClass: emDeteCanClass ;
extern void ICan_Tx_OpeaDete_Disable(BOOL bDisable, 
				U8 mLoop, U8 mAddr, U8 mDeteClass); // 操作：屏蔽
extern void ICan_Tx_OpeaDete_ManuRunOrStop(
				BOOL bRun, 
				U8 mLoop, U8 mAddr, U8 mChannel); // 操作：模块启动/停止
extern void ICan_Tx_OpeaDete_SignalRegist(BOOL bRegist, 
				U8 mLoop, U8 mAddr, U8 mDeteClass); // 操作：单个登记
extern void ICan_Tx_OpeaDete_InquireStateAndType(
						U8 mLoop, U8 mAddr); // 操作：查询状态、种类


extern void ICan_Tx_Inquire_DeteInline(U8 mLoop); // 查询上线
extern void ICan_Tx_Set_LoopDisable(U8 mLoop); // 设置 回路屏蔽
extern void ICan_Tx_Inquire_Regist(U8 mLoop); // 查询回路登记 ?
extern void ICan_Tx_Inquire_DeteRegist(U8 mLoop); // 查询回路现场部件登记



// 取消 查询现场部件 测试：状态，曲线，内部数据：
static void ICan_Tx_InquireCheck_Dete_Stop(U8 mCommand, U8 mLoop, U8 mAddr);
// 查询现场部件 状态：
extern void ICan_Tx_Inquire_DeteState(U8 mLoop, U8 mAddr); 
extern void ICan_Tx_Inquire_DeteStaStop(U8 mLoop, U8 mAddr);
// 查询现场部件 模拟曲线：
extern void ICan_Tx_Inquire_DeteCurv(U8 mLoop, U8 mAddr); 
extern void ICan_Tx_Inquire_DeteCuvStop(U8 mLoop, U8 mAddr);
// 查询现场部件 内部数据：
extern void ICan_Tx_Inquire_DeteInterData(U8 mLoop, U8 mAddr); 
extern void ICan_Tx_Inquire_DeteInterDatStop(U8 mLoop, U8 mAddr);
// 查询现场部件 回路浏览 回路纵览：
extern void ICan_Tx_Inquire_LoopBrowse(U8 mLoop); 
extern void ICan_Tx_Inquire_LoopBrowsStop(U8 mLoop);


extern void ICan_Tx_Inquire_SoftVersion(U8 mLoop);






/******************************************************************************
// END :
******************************************************************************/
#endif // __canPrtl_iTx_H__

