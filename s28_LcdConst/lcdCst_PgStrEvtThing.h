#ifndef __lcdCst_PgStrEvtThing_H__
#define __lcdCst_PgStrEvtThing_H__
/******************************************************************************
* @file    lcdCst_PgStrEvtThing.h
* @author  yx
* @version V1.0
* @date    2013-07-01
* @brief   
* 
#include  "lcdCst_PgStrEvtThing.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

#include  "lcdCst_PgString.h"
/*================= extern ============================================*/

#define EX_lcdCst_PgStrEvtThing extern 

/*================= 常数 ============================================*/
//#define 
/*================= 结构体定义 ======================================*/

/*================= 字符串定义 ======================================*/

/*================= 私有函数声明 ====================================*/
#ifdef __lcdCst_PgStrEvtThing_C__ 

typedef struct{  //U_Language_MAX
	U8 thing;
	TCstChar_st stChar;
}TCstEvtThing_st;

const TCstEvtThing_st cstEvtClsChar[];
const TCstEvtThing_st cstEvtLinkModuChar[];
const TCstEvtThing_st cstEvtExtgChar[];
const TCstEvtThing_st cstEvtAlarmChar[];
const TCstEvtThing_st cstEvtFaultChar[];
const TCstEvtThing_st cstEvtOpeaChar[];
const TCstEvtThing_st cstEvtSuperChar[];

#endif // __lcdCst_PgStrEvtThing_C__
/*================= 公有函数声明 ====================================*/
//EX_lcdCst_PgStrEvtThing 

// bEvtValid(_thing_)

extern BOOL GetCstChar_EvtLinkModu(U8 mThing, const TCstChar_st **pRtnChar);
extern BOOL GetCstChar_EvtExtg(U8 mThing, const TCstChar_st **pRtnChar);
extern BOOL GetCstChar_EvtAlarm(U8 mThing, const TCstChar_st **pRtnChar);
extern BOOL GetCstChar_EvtSpvs(U8 mThing, const TCstChar_st **pRtnChar);
extern BOOL GetCstChar_EvtFault(U8 mThing, const TCstChar_st **pRtnChar);
extern BOOL GetCstChar_EvtOpea(U8 mThing, const TCstChar_st **pRtnChar);

extern BOOL GetCstChar_EvtCls(U8 mEvtCls, const TCstChar_st **pRtnChar);


/******************************************************************************
// END :
******************************************************************************/
#endif // __lcdCst_PgStrEvtThing_H__

