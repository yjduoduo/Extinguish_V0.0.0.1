
#define __phClock_C__
/******************************************************************************
* @file    phClock.c
* @author  yx
* @version V1.0
* @date    2012-01-05
* @brief   
* 
*  PCF8563
******************************************************************************/
#include  "phClock.h"

//#include "incFile.h"	

#include  "sysStatus.h"
#include  "codeComm.h"
#include  "tmrTick.h"
#include  "hwEx03_Pcf8563.h"

/*================= 常数 ============================================*/
/*================= 常数 ============================================*/
	
/*================= 结构定义 ========================================*/

/*================= 私有结构变量声明 ================================*/
TEvtClock_st stRamClock;
TEvtClock_st stTempClock;
// BOOL bClockChanged;


/*================= 公有函数声明 ====================================*/

/*================= 私有函数声明 ====================================*/
BOOL bChkClockError(TEvtClock_st *pClock);
U8 getClockItemValue(U8 clockItem, TEvtClock_st *pClock);

BOOL compareClockEqual(TEvtClock_st *pClock1, TEvtClock_st *pClock2);



/*=================  ================================================*/
		
/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

void GetRamTimer(TEvtClock_st **pClock)
{
	*pClock = &stRamClock;
}


void GetRamEvtTimer(TEvtClock_st *pEvtClock)
{
	pEvtClock->year = stRamClock.year;
	pEvtClock->month = stRamClock.month;
	pEvtClock->day = stRamClock.day;
	pEvtClock->hour = stRamClock.hour;
	pEvtClock->min = stRamClock.min;
	pEvtClock->sec = stRamClock.sec;
	
}

/******************************************************************************
* FUNC: //
******************************************************************************/
void InitClock(void)
{
	Init_PCF8563();
	
	if(!GetClock(&stRamClock))
	{
		stRamClock = cstDefaultClock;
		SetClock(&stRamClock);
	}
	SetSysState(U_SysSta_bClockChanged);
	
	SetTmrTickTask(TASK_ReadClock, TMR_ReadClock);
	
}

// stTempClock
void ExecClockTask(void)
{
U8 second;

	if(GetTickTaskStatus(TASK_ReadClock))
	{
		second = stRamClock.sec;
		GetClock(&stRamClock);
		if(second != (stRamClock.sec))
		{
			SetSysState(U_SysSta_bClockChanged);
		}
		
	}
}


/******************************************************************************
* FUNC: //
******************************************************************************/
BOOL GetClock(TEvtClock_st  *pClock)
{
#if U_SYS_ForbidHardWare == U_Yes 
	return FALSE;
#else

#if U_SYS_bShowConduct == 1 
	U_SYS_bShowConduct = 1;
#endif // U_SYS_bShowConduct
	if(!PCF8563_Read(pClock))
	{
		return FALSE;
	}
	
	if(bChkClockError(pClock))
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
#endif // U_SYS_ForbidHardWare
}


/******************************************************************************
* FUNC: //
******************************************************************************/
BOOL SetClock(TEvtClock_st *pClock)
{
#if U_SYS_ForbidHardWare == U_Yes 
	return TRUE;
#else
	if(bChkClockError(pClock))
	{
		return FALSE;
	}
	
	SetPCF8563(pClock);
	return TRUE;
#endif // U_SYS_ForbidHardWare
}

/******************************************************************************
* FUNC: //
*  OUT: TRUE=pClock1更近。
		equal = TRUE.
******************************************************************************/
BOOL bFirClockNearly(TEvtClock_st *pClock1, TEvtClock_st *pClock2)
{

	if                  (pClock1->year  != pClock2->year)
	{
		return bBigger(pClock1->year,    pClock2->year);
	}	
	if                  (pClock1->month != pClock2->month)
	{
		return bBigger(pClock1->month,   pClock2->month);
	}	
	if                  (pClock1->day   != pClock2->day)
	{
		return bBigger(pClock1->day,     pClock2->day);
	}
	
	if                  (pClock1->hour  != pClock2->hour)
	{
		return bBigger(pClock1->hour,    pClock2->hour);
	}
	if                  (pClock1->min   != pClock2->min)
	{
		return bBigger(pClock1->min,     pClock2->min);
	}
	if                  (pClock1->sec   != pClock2->sec)
	{
		return bBigger(pClock1->sec,     pClock2->sec);
	}

	return TRUE;
	
}

/******************************************************************************
* FUNC: //
******************************************************************************/
BOOL compareClockEqual(TEvtClock_st *pClock1, TEvtClock_st *pClock2)
{
	//return bCompareByte((U8*)(pClock1), (U8*)(pClock2), U_SYS_CLOCK_BYTE_MAX);
	
	//不可能 1小时检测一次
	if((pClock1->sec) != (pClock2->sec)){
		return FALSE;
	}
	else if((pClock1->min) != (pClock2->min)){
		return FALSE;
	}
	// else if((pClock1->hour) != (pClock2->hour)){
		// return FALSE;
	// }
	
	return TRUE;
}


/******************************************************************************
* FUNC: //
******************************************************************************/
BOOL bChkClockError(TEvtClock_st *pClock)
{
	U8 item;
	U8 value;
	
	for(item=0; item<U_Clock_Item_MAX; item++)
	{
		value = getClockItemValue(item, pClock);
		
		if((value < cstClockLimit[item][U_MIN]) || (value >= cstClockLimit[item][U_MAX]))
		{
			return TRUE;
		}
	}
	return FALSE;
}

/******************************************************************************
* FUNC: //
******************************************************************************/
U8 getClockItemValue(U8 clockItem, TEvtClock_st *pClock)
{
	if(clockItem >= U_Clock_Item_MAX)
	{
		return ~0;
	}
	
	switch(clockItem)
	{
		case U_Year_Item:
			return pClock->year;
			
		case U_Month_Item:
			return pClock->month;
			
			
		case U_Day_Item:
			return pClock->day;
			
		case U_Hour_Item:
			return pClock->hour;
			
		case U_Min_Item:
			return pClock->min;
			
		case U_Sec_Item:
			return pClock->sec;
			
		default:
			return ~0;
	}
}


/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

