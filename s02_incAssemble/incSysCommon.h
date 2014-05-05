#ifndef __incSysCommon_H__
#define __incSysCommon_H__
/******************************************************************************
* @file    incSysCommon.h
* @author  yx
* @version V1.0
* @date    2012-01-05
* @brief   
* 
#include  "incSysCommon.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

/*=================  ============================================*/
#include  "sysDef.h"		//液晶像素、机器号、单元号 等系统定义
#include  "sysStatus.h"	//RAM-Status, ROM-Config

#include  "codeComm.h"		//数据、buf等常规操作
#include  "codeCrc.h"
#include  "bufCircle.h"
#include  "cstBits.h"


/*================= 公有函数声明 ====================================*/

extern  void RunCycle_OnTime(void); //需要按时exec. //"mRunTask.h"

/******************************************************************************
// END :
******************************************************************************/
#endif // __incSysCommon_H__

