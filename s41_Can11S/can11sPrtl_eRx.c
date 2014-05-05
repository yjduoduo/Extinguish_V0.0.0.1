#define __can11sPrtl_eRx_C__
/******************************************************************************
* @file    can11sPrtl_eRx.c
* @author  yx
* @version V1.0
* @date    2013-07-01
* @brief   
* 
******************************************************************************/
#include  "can11sPrtl_eRx.h"


#include  "strEvtTrans.h"
#include  "sysPanel.h"
#include  "sysMachine.h"
#include  "evtThingDef.h"
#include  "evt_Buf_incOut.h"

#include  "can11sPrtl_eCan.h"
//#include "incFile.h"	


/*================= 常数 ============================================*/

/*================= 结构定义 ========================================*/

/*================= 私有结构变量声明 ================================*/

static CanID  vECan11sRxId;
static THdCanFrame_st  *pNowRxFrm;

static TDev_un   vDev;
static TEvtTrans_st *pTransEvt;

static U8 vMachine;
static U8 vPnType;
static U8 vPnSequ;
static U8 vLoop;
static U8 vLpInBoard; // 1~
static U8 vAddr;
static U8 vChannel;

/*================= 公有函数声明 ====================================*/

/*================= 私有函数声明 ====================================*/

/*=================  ================================================*/
		
/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
void ECan11s_Rx_One(THdCanFrame_st  *pRxFrm)
{
	U8 mCommand;

	if (!bECan11sId_Rx_DestIsMe(pRxFrm, &vMachine, &mCommand))
	{
		return;
	}
	pNowRxFrm = pRxFrm;
	
	switch(mCommand)
	{
		case 0x80:
			vLoop = pNowRxFrm->rtData.rtU8[1];
			vAddr = pNowRxFrm->rtData.rtU8[2];
			if(!BuildToDev_DeteMLA(vMachine, vLoop, vAddr, &vDev))
			{
				return;
			}
			
			GetEvtTransStrAndClock(&vDev, &pTransEvt);
			pTransEvt->type = pNowRxFrm->rtData.rtU8[3];
			pTransEvt->thing = U_Alarm_EVT;
			Buf_Alarm(pTransEvt);
			break;
			
		default:
			break;
	}
	
	pNowRxFrm = pNowRxFrm;
}


/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

// can.dest OK:
BOOL bECan11sId_Rx_DestIsMe(THdCanFrame_st  *pRxFrm, 
						   U8 *pRtnMachine, U8 *pRtnCommand)
{
	vECan11sRxId.dWord = pRxFrm->id.dWord;
	
	if((vECan11sRxId.st11sId.TargetAddr == 0)
	  || (vECan11sRxId.st11sId.TargetAddr == GetECan_MeAdr()))
	{
		if(vECan11sRxId.st11sId.DataType != CDType_11s_SData)
		{
			return FALSE;
		}
		
		*pRtnMachine = vECan11sRxId.st11sId.SourceAddr;
		if((*pRtnMachine == 0) || (*pRtnMachine > U_MACHINE_MAX))
		{
			return FALSE;
		}
		
		*pRtnCommand = pRxFrm->rtData.rtU8[0];
		Machine_inLine_Inc(*pRtnMachine);
		
		return TRUE;
	}
	
	
	return FALSE;
}


/******************************************************************************
* FUNC: //
******************************************************************************/



/******************************************************************************
* FUNC: // END
*   IN:
*  OUT: 
******************************************************************************/
