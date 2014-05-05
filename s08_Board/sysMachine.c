#define __sysMachine_C__
/******************************************************************************
* @file    sysMachine.c
* @author  yx
* @version V1.0
* @date    2012-01-05
* @brief   
* 
******************************************************************************/
#include  "sysMachine.h"

#include  "strDevice.h"
#include  "codeComm.h"
#include  "phClock.h"
#include  "tmrTick.h"

#include  "evt_Buf_incOut.h"

//#include "incFile.h"	


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
void Machine_Regist(U8 mMachineSequ, BOOL bRegisted)
{
	if(mMachineSequ < U_MACHINE_MAX)
	{
		vMachine[mMachineSequ].bRegisted = bRegisted;
	}
}


/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

void Machine_inLine_Inc(U8 mMachineSequ)
{
	if(mMachineSequ < U_MACHINE_MAX)
	{
		if(vMachine[mMachineSequ].inLineNum < U_Machine_InLine_NUM_MAX)
		{
			vMachine[mMachineSequ].inLineNum++;
		}
	}
}

void Machine_inLine_Clr(U8 mMachineSequ)
{
	if(mMachineSequ < U_MACHINE_MAX)
	{
		vMachine[mMachineSequ].inLineNum = 0;
	}
}

void Machine_inLine_ClrAll(void)
{
U8 mMachineSequ;

	for(mMachineSequ=0; mMachineSequ<U_MACHINE_MAX; mMachineSequ++)
	{
		vMachine[mMachineSequ].inLineNum = 0;
	}
}


/******************************************************************************
* FUNC: //
******************************************************************************/
void MachineState_Init(void)
{
U32 num = sizeof(vMachine);

	ClrRamIs00((U8*)(&vMachine[0]), num); //全清00
	
	SetTmrTickTask(TASK_CheckMachineInLine, TMR_CheckMachineInLine);
}

/******************************************************************************
* FUNC: //
******************************************************************************/

void Machine_inLine_Check(void)
{
U8 mMachineSequ;

	if(!GetTickTaskStatus(TASK_CheckMachineInLine))
	{
		return;
	}
	
	for(mMachineSequ=0; mMachineSequ<U_MACHINE_MAX; mMachineSequ++)
	{
		if(!vMachine[mMachineSequ].bRegisted)
		{
			continue;
		}
		if((vMachine[mMachineSequ].inLineNum < U_Machine_InLine_NUM_MIN)
		  &&(!vMachine[mMachineSequ].bOutLine) )
		{
			if(machine_inLine_ResultOk(mMachineSequ, FALSE))
			{
				vMachine[mMachineSequ].bOutLine = TRUE;
			}
		}
		else if((vMachine[mMachineSequ].inLineNum >= U_Machine_InLine_NUM_MIN)
		  &&(vMachine[mMachineSequ].bOutLine) )
		{
			if(machine_inLine_ResultOk(mMachineSequ, TRUE))
			{
				vMachine[mMachineSequ].bOutLine = FALSE;
			}
		}
	}
	
}

/******************************************************************************
* FUNC: //
******************************************************************************/

BOOL machine_inLine_ResultOk(U8 mMachineSequ, U8 bOk)
{
TEvtTrans_st  stEvt;

	DevSetInvalid(&stEvt.unDev);
	if(!BuildToDev_Machine(mMachineSequ, &stEvt.unDev))
	{
		return FALSE;
	}
	GetRamEvtTimer(&stEvt.evtClock);
	
	if(bOk)
	{
		stEvt.thing = U_FaultRstr_EVT;
	}
	else
	{
		stEvt.thing = U_Fault_EVT;
	}
	return (Buf_Fault(&stEvt));
}




/******************************************************************************
* FUNC: //
******************************************************************************/
BOOL GetMachine_Regist(U8 mMachineSequ)
{
    if(mMachineSequ < U_MACHINE_MAX)
    {
        return vMachine[mMachineSequ].bRegisted;
    }
		return FALSE;
}



/******************************************************************************
* FUNC: // END
*   IN:
*  OUT: 
******************************************************************************/
