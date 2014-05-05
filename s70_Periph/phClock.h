#ifndef __phClock_H__
#define __phClock_H__
/******************************************************************************
* @file    phClock.h
* @author  yx
* @version V1.0
* @date    2012-01-05
* @brief   
* 
#include  "phClock.h"
******************************************************************************/

#include  "prjCompileCon.h"

#include  "strClock.h"

/*================= extern ============================================*/
#ifdef  __phClock_C__
#define EX_phClock
#else
#define EX_phClock extern 
#endif

/*================= 常数 ============================================*/

enum emClockWeek{
	U_WEEK_Sunday = 0, //星期日
	U_WEEK_Monday = 1,
	U_WEEK_Tuesday = 2,
	U_WEEK_Wednesday = 3,
	U_WEEK_Thursday = 4,
	U_WEEK_Friday = 5,
	U_WEEK_Saturday = 6,
};
	
	
/*================= 私有定义 ======================================*/
#ifdef __phClock_C__


enum emClockItem{
	U_Sec_Item 		= 0,
	U_Min_Item 		= 1,
	U_Hour_Item 	= 2,
	U_Day_Item 		= 3,
	U_Month_Item 	= 4,
	U_Year_Item 	= 5,	
	U_Clock_Item_MAX = 6
};

const U8 cstClockLimit[U_Clock_Item_MAX][2] = {
//	U_Sec_Item, U_Min_Item, U_Hour_Item
	{0, 60},  {0, 60},   {0, 24}, 
//   U_Day_Item, U_Month_Item, U_Year_Item
    {1, 32},  {1, 13},    {0, 100},
};

	
const TEvtClock_st cstDefaultClock = {13, 1, 1,   9, 0, 0}; //年月日  时分秒

#endif //__phClock_C__
/*================= 结构体定义 ======================================*/

/*================= 公有结构变量声明 ================================*/

/*================= 公有函数声明 ====================================*/

EX_phClock void InitClock(void);
EX_phClock void ExecClockTask(void);

EX_phClock BOOL compareClockEqual(TEvtClock_st *pClock1, TEvtClock_st *pClock2);
EX_phClock BOOL bFirClockNearly(TEvtClock_st *pClock1, TEvtClock_st *pClock2);
EX_phClock BOOL bChkClockError(TEvtClock_st *pClock);


EX_phClock BOOL SetClock(TEvtClock_st *pClock);
EX_phClock BOOL GetClock(TEvtClock_st  *pClock);
EX_phClock void GetRamTimer(TEvtClock_st **pClock);
EX_phClock void GetRamEvtTimer(TEvtClock_st *pEvtClock);


/******************************************************************************
// END :
******************************************************************************/
#endif // __phClock_H__

