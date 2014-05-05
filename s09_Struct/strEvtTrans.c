#define __strEvtTrans_C__
/******************************************************************************
* @file    strEvtTrans.c
* @author  yx
* @version V1.1
* @date    2013-08-22
* @brief   
* 
******************************************************************************/
#include  "strEvtTrans.h"

#include  "phClock.h"

//#include "incFile.h"	


/*================= 常数 ============================================*/

/*================= 结构定义 ========================================*/

/*================= 私有结构变量声明 ================================*/
TEvtTrans_st  stEvtTrans;
/*================= 公有函数声明 ====================================*/

/*================= 私有函数声明 ====================================*/

/*=================  ================================================*/



/******************************************************************************
* FUNC: // 
*   IN:
*  OUT: 
******************************************************************************/
void Clock_all_FF(TEvtClock_st *pClock)
{
U8 *pByte = (U8 *)(pClock);
U8 ii;
	
	for(ii=0; ii<sizeof(TEvtClock_st); ii++)
	{
		*pByte = ~0;
		pByte++;
	}
	
}

void Clock_all_00(TEvtClock_st *pClock)
{
U8 *pByte = (U8 *)(pClock);
U8 ii;
	
	for(ii=0; ii<sizeof(TEvtClock_st); ii++)
	{
		*pByte = 0;
		pByte++;
	}
	
	
}

void Clock_all_test12345(U8 mIniVal, TEvtClock_st *pClock)
{
	pClock->year 	= mIniVal+1;
	pClock->month 	= mIniVal+2;
	pClock->day 	= mIniVal+3;
	pClock->hour 	= mIniVal+4;
	pClock->min 	= mIniVal+5;
	pClock->sec 	= mIniVal+6;
}


/******************************************************************************
* NAME: 
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
void IniEvtTransStruct (TEvtTrans_st *pEvtTrans)
{
	GetRamEvtTimer(&pEvtTrans->evtClock);
	pEvtTrans->thing = ~0;
	pEvtTrans->thiFurther = ~0;
}

void GetEvtTransStrAndClock(TDev_un *pDev, 
						   TEvtTrans_st **pEvtTrans)
{
	IniEvtTransStruct (&stEvtTrans);
	stEvtTrans.unDev = *pDev;
	*pEvtTrans = &stEvtTrans;
}

/******************************************************************************
* FUNC: // END
*   IN:
*  OUT: 
******************************************************************************/
