#ifndef __strClock_H__
#define __strClock_H__
/******************************************************************************
* @file    strClock.h
* @author  yx
* @version V1.0
* @date    2012-01-05
* @brief   
* 
#include  "strClock.h"
******************************************************************************/

#include  "prjCompileCon.h"
/*================= extern ============================================*/
#ifdef  __strClock_C__
#define EX_strClock
#else
#define EX_strClock extern 
#endif

/*================= 常数 ============================================*/
//#define 
/*================= 结构体定义 ======================================*/

/*================= 公有结构变量声明 ================================*/
#define U_SYS_CLOCK_BYTE_MAX	7
typedef struct{
	U8 year;
	U8 month;
	U8 day;
	U8 week;
	U8 hour;
	U8 min;
	U8 sec;
}TClockYmdhms_st;

#define U_EVT_CLOCK_BYTE_MAX	6
#pragma pack(1)	
typedef struct{
	U8 year;
	U8 month;
	U8 day;
	U8 hour;
	U8 min;
	U8 sec;
}TEvtClock_st;
#pragma pack()	

/*================= 公有函数声明 ====================================*/
//EX_strClock 

EX_strClock void Clock_all_FF(TEvtClock_st *pClock);
EX_strClock void Clock_all_00(TEvtClock_st *pClock);
EX_strClock void Clock_all_test12345(U8 mIniVal, TEvtClock_st *pClock);


/******************************************************************************
// END :
******************************************************************************/
#endif // __strClock_H__

