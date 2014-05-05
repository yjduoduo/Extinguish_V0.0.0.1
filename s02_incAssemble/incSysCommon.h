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
#include  "sysDef.h"		//Һ�����ء������š���Ԫ�� ��ϵͳ����
#include  "sysStatus.h"	//RAM-Status, ROM-Config

#include  "codeComm.h"		//���ݡ�buf�ȳ������
#include  "codeCrc.h"
#include  "bufCircle.h"
#include  "cstBits.h"


/*================= ���к������� ====================================*/

extern  void RunCycle_OnTime(void); //��Ҫ��ʱexec. //"mRunTask.h"

/******************************************************************************
// END :
******************************************************************************/
#endif // __incSysCommon_H__

