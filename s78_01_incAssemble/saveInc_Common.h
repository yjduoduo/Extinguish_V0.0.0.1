#ifndef __saveInc_Common_H__
#define __saveInc_Common_H__
/******************************************************************************
* @file    saveInc_Common.h
* @author  yx
* @version V1.1
* @date    2013-9-3
* @brief   
*
* V1.0，2013-07-23
*
#include  "saveInc_Common.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

/*================= 公有函数声明 ====================================*/

// 在master里为lib所使用的文件。
// master 和 lib 需要同步。

//s01_inc:
#include  "prjCompileCon.h"
#include  "prjDataType.h"
#include  "prjBool.h"

//s02_incStr:
#include  "strDevice.h"
#include  "strClock.h"
#include  "strEvtTrans.h"

//s03_IncCommon:
#include  "bufCircle.h"
#include  "codeComm.h"
#include  "codeCrc.h"

//s06_IncSaveDef
#include  "flsStoreBytesDef.h"
#include  "historyClsDef.h"
#include  "strFlsAdrDef.h"
#include  "strFlsItmStruct.h"

//s10_FlsInterface
#include  "fls_Interface.h"

/******************************************************************************
// 之上的.h文件若 有变动，需要同步
******************************************************************************/

#include  "flsErase.h"
#include  "flsWrite.h"

//s20_SaveCacu
#include  "flsAdrCalculate.h"
#include  "strFlsItmStrCacu.h"

//
#include  "flsItemState.h"

/******************************************************************************
// END :
******************************************************************************/
#endif // __saveInc_Common_H__

