#ifndef __strEvtTrans_H__
#define __strEvtTrans_H__
/******************************************************************************
* @file    strEvtTrans.h
* @author  yx
* @version V1.1
* @date    2013-08-22
* @brief   
* 
* V1.1， add: void GetEvtTransStrAndClock(...);
		2013-08-22
* V1.0， 2013-07-01
*
#include  "strEvtTrans.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

#include  "strDevice.h"
#include  "strClock.h"
/*================= extern ============================================*/
#ifdef  __strEvtTrans_C__
#define EX_strEvtTrans
#else
#define EX_strEvtTrans extern 
#endif
/*================= 常数 ============================================*/
//#define 
/*================= 结构体定义 ======================================*/

/*================= 公有结构变量声明 ================================*/

#define U_EVT_TRANS_BYTE_MAX	0x0F //4+3+6=13

#pragma pack(1)	
typedef struct{
	TDev_un unDev;
	U8 type; //设备类型  //在灭火联动事件里，代表manu/auto/remote.
	U8 thing;
	U8 thiFurther; //灭火有
	
	TEvtClock_st evtClock;
	//U8 hour; //火警用？
	//U8 min;
}TEvtTrans_st; //
#pragma pack()	

/*================= 公有函数声明 ====================================*/
//EX_strEvtTrans 

extern void IniEvtTransStruct(TEvtTrans_st *pEvtTrans);
extern void GetEvtTransStrAndClock(TDev_un *pDev,
							TEvtTrans_st **pEvtTrans);
/*================= 私有函数声明 ====================================*/
#ifdef  __strEvtTrans_C__

#endif  //__strEvtTrans_C__


/******************************************************************************
// END :
******************************************************************************/
#endif // __strEvtTrans_H__

