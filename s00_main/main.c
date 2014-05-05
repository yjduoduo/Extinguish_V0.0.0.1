#define __main_C__
/******************************************************************************
* @file    main.c
* @author  yx
* @version V1.0
* @date    2012-01-05
* @brief   
* 
******************************************************************************/


//#include "incFile.h"	
#include  "mRunTask.h"

#include  "tmrTick.h"
#include  "sysStatus.h"
#include  "LcdLib_incOut.h"
#include  "Can_Manage.h"
#include  "canPrtl_iTx.h"
/*================= 常数 ============================================*/

/*================= 结构定义 ========================================*/

/*================= 私有结构变量声明 ================================*/

/*================= 公有函数声明 ====================================*/

/*================= 私有函数声明 ====================================*/

/*=================  ================================================*/
		
/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
void Sys_Reset(void)
{
	if(GetSysState(U_SysSta_bNeedReset))
	{
		SetSysState(U_SysSta_bResetIng);
		ClrSysState(U_SysSta_bNeedReset);
		
		SetTmrTickTask(TASK_CloseHdWhenResetIng, 
							TMR_CloseHdWhenResetIng);
		
		ICan_Tx_Reset();
	}
	
	if(GetSysState(U_SysSta_bResetIng))
	{
		if(GetTickTaskStatus(TASK_CloseHdWhenResetIng))
		{
			ClrSysState(U_SysSta_bResetIng);
			KillTickTask(TASK_CloseHdWhenResetIng);
			SysInit_WhenReset();
		}
	}
	
}

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

int main(void)
{
	SysInit_WhenPowerOn();
	while(1)
	{
		if(bHaveTmrTickIntr())
		{
			TickTaskWork();
		}
		// Clear_MyWatchDog();
		CanIntrBuf_Move();
		
		
		Sys_Exec(); 
		
		if(bSysStaReseting())
		{
			Sys_Reset();
		}
	}
}


/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/



/******************************************************************************
* FUNC: // END
*   IN:
*  OUT: 
******************************************************************************/
