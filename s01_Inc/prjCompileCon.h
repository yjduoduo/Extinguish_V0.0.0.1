#ifndef __prjCompileCon_H__
#define __prjCompileCon_H__
/******************************************************************************
* @file    prjCompileCon.h
* @author  yx
* @version V1.0
* @date    2012-01-05
* @brief   编译控制,工程里所有的.h都include.
* 
#include  "prjCompileCon.h"
******************************************************************************/
#include <assert.h>  //	ASSERT(1);  //断言,控制编译时的函数的输入参数报错。

#include  "prjDataType.h"
#include  "prjFosc.h"
#include  "prjBool.h"
/*================= 常数 ============================================*/

//#define Pseudocode //伪代码
//#define Code No Finished  //标志未完成的代码
//#define conduct    //处理

/******************************************************************************
// 系统定义 :
// 尽量不用 #ifdef ,因为若文件未 include me.h, 则定义不起作用也不知道。
******************************************************************************/
#define U_Yes   1
#define U_YES   1
#define U_No    0
#define U_NO    0

/******************************************************************************
// 字库 :
******************************************************************************/
// yes = 字库在code里, cpu首次烧录应该用这个定义
//  no = 字库已在code里，不必再编译字库。
// #define U_Include_CharLib  U_NO  去 "hwEx11_lcd_Def_charLib.h" 定义

// 字库点阵选择： U_CharLib_NOW , 在 "hwEx11_lcd_Def_charLib.h" ，
// 字库的点阵字节 在 "hwEx11_lcd_Def_charLib.h"
// 显示字符的点阵 在 "hwEx11_lcd_Def_charLib.h"

/******************************************************************************
// 软仿真 :
******************************************************************************/

#define U_SYS_SoftSimulatState     U_NO


#if U_SYS_SoftSimulatState == 1 
	#define U_SYS_ForbidHardWare  U_YES  //软仿真期间禁止硬件	
#endif // U_SYS_SoftSimulatState

#if U_SYS_ForbidHardWare == U_Yes 
#else
#endif // U_SYS_ForbidHardWare

#if U_SYS_SoftSimulatState == 1 
#endif // U_SYS_SoftSimulatState


//----- 测试状态 ----------------------------------------------------------------

#define U_SYS_SoftTestState     1  //总开关。 // 1=软件测试状态。不只是软仿真。

#if U_SYS_SoftTestState == 1 
	#define U_SYS_IdleBuf_setFF    0 //不用的buf置FF, 仿真时有助分析R.
	
	#define U_SYS_Test_GeneralCode   0
	#define U_SYS_Test_Menu    0
	#define U_SYS_Test_EvtBuf    0
	#define U_SYS_Test_strDevice    0
	#define U_SYS_Test_codCommon    0
	#define U_SYS_Test_Flash_SimTask    1
	#define U_SYS_Test_Flash_InqPoint    0
		#define U_SYS_Test_Flash_InqPoint_SimX    0
	#define U_SYS_Test_Flash_Hist    0
	#define U_SYS_Test_FlsApplyBuf    0
	#define U_SYS_Test_FlsAdrDef    0
	#define U_SYS_Test_CanBuf    0
	
	#define U_SYS_Test_Lcd    1
	#define U_SYS_Test_CanHw    1
	#define U_SYS_Test_UartHw    1
	
#endif // U_SYS_SoftSimulatState

//----- 按键需要密码 -----------------------------------------------------------------

#define U_SYS_KeyNowNeedPassword   U_NO 


/******************************************************************************
// 代码状态：
******************************************************************************/
#define U_SYS_bShowPseudocode  0  //伪代码
#define U_SYS_bShowNoFinished  0  //标志未完成的代码
#define U_SYS_bShowConduct     0  //需要再处理
// U_SIGN_bHaveTested			 //已经测试

#if U_SYS_bShowPseudocode == 1 
	//U_SYS_bShowPseudocode = 1;
#endif // U_SYS_bShowPseudocode

#if U_SYS_bShowNoFinished == 1 
	//U_SYS_bShowNoFinished = 1;
#endif // U_SYS_bShowNoFinished

#if U_SYS_bShowConduct == 1 
	//U_SYS_bShowConduct = 1;
#endif // U_SYS_bShowConduct


/******************************************************************************
// 小端模式：
******************************************************************************/
#define U_Sys_Big_Endian  1
#define U_Sys_Little_Endian  0
#define U_Sys_Endian  U_Sys_Little_Endian
//Big-Endian和Little-Endian

/******************************************************************************
// 断言：
******************************************************************************/
#define myAssert(expr)    if(expr) {};// assert(expr)

/******************************************************************************
// 其他 :
******************************************************************************/
#ifndef __CAN_BUF_LIB__
#define __CAN_BUF_LIB__
#endif 
/******************************************************************************
// END :
******************************************************************************/
#endif // __prjCompileCon_H__

