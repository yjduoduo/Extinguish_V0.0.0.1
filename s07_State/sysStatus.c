#define __sysStatus_C__
/******************************************************************************
* @file    sysStatus.c
* @author  yx
* @version V1.0
* @date    2012-01-05
* @brief   
* 
*  
*  //系统处于复位状态的时间。       按键检测是否有长按下的；
******************************************************************************/
#include  "sysStatus.h"

#include  "cstBits.h"
#include  "sysDef.h"
#include  "codeComm.h"
//#include "incFile.h"

/*================= 常数 ============================================*/

/*================= 结构定义 ========================================*/
typedef struct{
	U8 sound;
	
	
	
}TSysState_st;

TSysState_st stSysState;
TSysConfig_st stSysConfig;

#define U_SYS_BOOL_STATE_BUF_MAX  (U_SysBoolSta_MAX/32+1)
U32 aSysBoolState[U_SYS_BOOL_STATE_BUF_MAX];

/*================= 私有结构变量声明 ================================*/

/*================= 公有函数声明 ====================================*/



/*================= 私有函数声明 ====================================*/

/*=================  ================================================*/

/******************************************************************************
* FUNC: //
*   IN: 
*  OUT: 
******************************************************************************/
void Init_SysStatus(void)
{
	U32 bufItem;
	for(bufItem=0; bufItem<U_SYS_BOOL_STATE_BUF_MAX; bufItem++)
	{
		aSysBoolState[bufItem] = 0;
	}
	
	bufItem = sizeof(TSysConfig_st);
	ClrRamIs00((U8*)(&stSysConfig), bufItem); //全清00
#if U_SYS_bShowNoFinished == 1 
	U_SYS_bShowNoFinished = 1;
#endif // U_SYS_bShowNoFinished
	
	bufItem = sizeof(TSysState_st);
	ClrRamIs00((U8*)(&stSysState), bufItem); //全清00
	
	
	
	SetSysState(U_SysSta_bAutoManuChanged);
	
}

/******************************************************************************
* FUNC: //
*   IN: emSysBoolStatus
*  OUT: 
******************************************************************************/
void SetSysState(U32 sysBoolStateItem)
{
	U8 bufItem;
	U32 bitLocation;
	
	bufItem = sysBoolStateItem >> 5;   //sysBoolStateItem/32;
	bitLocation = sysBoolStateItem & 0x1F;  //sysBoolStateItem%32;
	
	if(bufItem < U_SYS_BOOL_STATE_BUF_MAX)
	{
		aSysBoolState[bufItem] |= cBit32LowToHigh[bitLocation];
	}
}

void ClrSysState(U32 sysBoolStateItem)
{
	U8 bufItem;
	U32 bitLocation;
	
	bufItem = sysBoolStateItem >> 5;   //sysBoolStateItem/32;
	bitLocation = sysBoolStateItem & 0x1F;  //sysBoolStateItem%32;
	
	if(bufItem < U_SYS_BOOL_STATE_BUF_MAX)
	{
		aSysBoolState[bufItem] &= ~cBit32LowToHigh[bitLocation];
	}
	
}

BOOL GetSysState(U32 sysBoolStateItem)
{
	U8 bufItem;
	U32 bitLocation;
	
	if(sysBoolStateItem == U_SysSta_bTurnPageSerial)
	{
		return TRUE;
	}
	
	bufItem = sysBoolStateItem >> 5;   //sysBoolStateItem/32;
	bitLocation = sysBoolStateItem & 0x1F;  //sysBoolStateItem%32;
	
	if(bufItem < U_SYS_BOOL_STATE_BUF_MAX)
	{
		if((aSysBoolState[bufItem] & cBit32LowToHigh[bitLocation]) == 0)
		{
			return FALSE;
		}
		else
		{
			return TRUE;
		}
	}
	else
	{
		return FALSE;
	}
	
}

/******************************************************************************
* FUNC: //
******************************************************************************/

BOOL bSysStatus_TurnPageSerial(void)
{
	return TRUE;
	// return GetSysState(U_SysSta_bTurnPageSerial);
}

/******************************************************************************
* NAME: 
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
U8 getMachineMeAddr(void)
{
	return stSysConfig.machineAddr;
}

/******************************************************************************
* FUNC: //
******************************************************************************/
U8 GetLanguage(void)
{
	return U_Chinese_LANGUAGE;
}

/******************************************************************************
* NAME: 
* FUNC: //系统处于复位状态的时间。       按键检测是否有长按下的；
*   IN:
*  OUT: 
******************************************************************************/
void SysStaSetReset(void)
{
	
}

void SysStaResetFinish(void)
{
	
}

U8 bSysStaReseting(void)
{
	return (  (GetSysState(U_SysSta_bNeedReset)) 
		   || (GetSysState(U_SysSta_bResetIng)));
}

/******************************************************************************
* NAME: 
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

