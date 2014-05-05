#define __lcdCst_PgStrEvtThing_C__
/******************************************************************************
* @file    lcdCst_PgStrEvtThing.c
* @author  yx
* @version V1.0
* @date    2013-07-01
* @brief   
* 
******************************************************************************/
#include  "lcdCst_PgStrEvtThing.h"

#include  "evtThingDef.h"
#include  "evt_Para.h"


/*================= 常数 ============================================*/

/*=================  ================================================*/
/******************************************************************************
* FUNC: //
******************************************************************************/

// 事件类别:
const TCstEvtThing_st cstEvtClsChar[] =
{
	{U_EvtCls_Alarm, {"火警", "alarm", ""}},
	{U_EvtCls_Fault, {"故障", "fault ", ""}},
	{U_EvtCls_Link, {"联动", "link", ""}},
	{U_EvtCls_Extg, {"气灭", "extg", ""}},
	{U_EvtCls_Spvs, {"监管", "spvs", ""}},
	{U_EvtCls_Dsab, {"屏蔽", "dsab", ""}},
	
	// {DDD, {"", "", ""}},
};
/******************************************************************************
* FUNC: //
******************************************************************************/
// 事件：link-modu:
const TCstEvtThing_st cstEvtLinkModuChar[] =
{
	{U_ModuManuRun_EVT, 	{"手动启动", "mRun", ""}},
	{U_ModuManuStop_EVT, 	{"手动停止", "mStop", ""}},
	{U_ModuAutoRun_EVT, 	{"自动启动", "aRun", ""}},
	{U_ModuAutoRunDelay_EVT,{"启动延时", "delay", ""}},
	{U_ModuRunDelayCancel_EVT, {"启动延时撤销", "dlyRs", ""}},
	{U_ModuAutoStop_EVT, 	{"自动停止", "aStop", ""}},
	{U_ModuAck_EVT, 	{"反馈", "ack", ""}},
	{U_ModuAckRstr_EVT, {"反馈撤销", "ackRs", ""}},
	{U_ModuMissAck_EVT, {"反馈缺失", "ackMiss", ""}},
	
	{U_EVT_INVALID, 	{"未识别", "no", ""}} // 最后一条特殊功能，一直放最后。
	// {DDD, {"", "", ""}},
};

/******************************************************************************
* FUNC: //
******************************************************************************/
// 事件：extg:
const TCstEvtThing_st cstEvtExtgChar[] =
{
	{U_ExtgCircleRun_EVT, 	{"流程启动", "run", ""}},
	{U_ExtgCircleSec_EVT, 	{"倒计时", "delay", ""}},
	{U_ExtgCircleStop_EVT, 	{"流程停止", "stop", ""}},
	{U_ExtgAnnuRun_EVT, 	{"声光启动", "hlRun", ""}},
	{U_ExtgAnnuStop_EVT, 	{"声光停止", "hlStop", ""}},
	{U_ExtgAuxRun_EVT, 		{"辅助设备动作", "auxRun", ""}},
	{U_ExtgAuxStop_EVT, 	{"辅助设备停止", "auxStop", ""}},
	{U_ExtgSprayRun_EVT, 	{"喷洒动作", "etRun", ""}},
	{U_ExtgSprayStop_EVT, 	{"喷洒停止", "etStop", ""}},
	{U_ExtgSprayAck_EVT, 	{"喷洒反馈", "", "etAck"}},
	{U_ExtgSprayAckRstr_EVT, {"喷洒反馈撤销", "ackRs", ""}},
	{U_ExtgSprayMissAck_EVT, {"喷洒反馈缺失", "ackMiss", ""}},
	
	{U_EVT_INVALID, 	{"未识别", "no", ""}} // 最后一条特殊功能，一直放最后。
	// {DDD, {"", "", ""}},
};

/******************************************************************************
* FUNC: //
******************************************************************************/
// 事件：alarm:
const TCstEvtThing_st cstEvtAlarmChar[] =
{
	{U_Alarm_EVT, 	{"火警", "", ""}},
	
	{U_EVT_INVALID, 	{"未识别", "", ""}} // 最后一条特殊功能，一直放最后。
	// {DDD, {"", "", ""}},
};


/******************************************************************************
* FUNC: //
******************************************************************************/
// 事件：Fault:
const TCstEvtThing_st cstEvtFaultChar[] =
{
	{U_Fault_EVT, 		{"故障", "", ""}},
	{U_FaultRstr_EVT, 	{"故障撤销", "", ""}},
	
	{U_EVT_INVALID, 	{"未识别", "", ""}} // 最后一条特殊功能，一直放最后。
	// {DDD, {"", "", ""}},
};

/******************************************************************************
* FUNC: //
******************************************************************************/
// 事件：Opea:
const TCstEvtThing_st cstEvtOpeaChar[] =
{
	{U_Reset_EVT, {"复位", "", ""}},
	{U_PwrOff_EVT, {"关机", "", ""}},
	{U_Disable_EVT, {"屏蔽", "", ""}},
	{U_DisableRstr_EVT, {"屏蔽撤销", "", ""}},
	
	{U_EVT_INVALID, 	{"未识别", "", ""}} // 最后一条特殊功能，一直放最后。
	// {DDD, {"", "", ""}},
};


/******************************************************************************
* FUNC: //
	U_Super_FlsErase_EVT,
	U_Super_FlsCopyRenew_EVT,
	
******************************************************************************/
// 事件：Super:
const TCstEvtThing_st cstEvtSuperChar[] =
{
	{U_Super_FlsErase_EVT, {"flash擦除", "", ""}},
	{U_Super_FlsCopyRenew_EVT, {"flash被更新", "", ""}},
	
	{U_EVT_INVALID, 	{"未识别", "", ""}} // 最后一条特殊功能，一直放最后。
	// {DDD, {"", "", ""}},
};



/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

/******************************************************************************
* FUNC: //
******************************************************************************/

BOOL GetCstChar_EvtLinkModu(U8 mThing, const TCstChar_st **pRtnChar)
{
U8 charDefMax;
U8 ii;

	charDefMax = sizeof(cstEvtLinkModuChar) / sizeof(TCstEvtThing_st);
	for(ii=0; ii<charDefMax; ii++)
	{
		if(cstEvtLinkModuChar[ii].thing == mThing)
		{
			*pRtnChar = &cstEvtLinkModuChar[ii].stChar;
			return TRUE;
		}
	}
	
	*pRtnChar = &cstEvtLinkModuChar[charDefMax-1].stChar;
	return FALSE;
}


/******************************************************************************
* FUNC: //
******************************************************************************/

BOOL GetCstChar_EvtExtg(U8 mThing, const TCstChar_st **pRtnChar)
{
U8 charDefMax;
U8 ii;

	charDefMax = sizeof(cstEvtExtgChar) / sizeof(TCstEvtThing_st);
	for(ii=0; ii<charDefMax; ii++)
	{
		if(cstEvtExtgChar[ii].thing == mThing)
		{
			*pRtnChar = &cstEvtExtgChar[ii].stChar;
			return TRUE;
		}
	}
	
	*pRtnChar = &cstEvtExtgChar[charDefMax-1].stChar;
	return FALSE;
}


/******************************************************************************
* FUNC: //
******************************************************************************/

BOOL GetCstChar_EvtAlarm(U8 mThing, const TCstChar_st **pRtnChar)
{
U8 charDefMax;
U8 ii;

	charDefMax = sizeof(cstEvtAlarmChar) / sizeof(TCstEvtThing_st);
	for(ii=0; ii<charDefMax; ii++)
	{
		if(cstEvtAlarmChar[ii].thing == mThing)
		{
			*pRtnChar = &cstEvtAlarmChar[ii].stChar;
			return TRUE;
		}
	}
	
	*pRtnChar = &cstEvtAlarmChar[charDefMax-1].stChar;
	return FALSE;
}


/******************************************************************************
* FUNC: //
******************************************************************************/

BOOL GetCstChar_EvtSpvs(U8 mThing, const TCstChar_st **pRtnChar)
{
	return GetCstChar_EvtAlarm(mThing, pRtnChar);
}

/******************************************************************************
* FUNC: //
******************************************************************************/

BOOL GetCstChar_EvtFault(U8 mThing, const TCstChar_st **pRtnChar)
{
U8 charDefMax;
U8 ii;

	charDefMax = sizeof(cstEvtFaultChar) / sizeof(TCstEvtThing_st);
	for(ii=0; ii<charDefMax; ii++)
	{
		if(cstEvtFaultChar[ii].thing == mThing)
		{
			*pRtnChar = &cstEvtFaultChar[ii].stChar;
			return TRUE;
		}
	}
	
	*pRtnChar = &cstEvtFaultChar[charDefMax-1].stChar;
	return FALSE;
}


/******************************************************************************
* FUNC: //
******************************************************************************/

BOOL GetCstChar_EvtOpea(U8 mThing, const TCstChar_st **pRtnChar)
{
U8 charDefMax;
U8 ii;

	charDefMax = sizeof(cstEvtOpeaChar) / sizeof(TCstEvtThing_st);
	for(ii=0; ii<charDefMax; ii++)
	{
		if(cstEvtOpeaChar[ii].thing == mThing)
		{
			*pRtnChar = &cstEvtOpeaChar[ii].stChar;
			return TRUE;
		}
	}
	
	*pRtnChar = &cstEvtOpeaChar[charDefMax-1].stChar;
	return FALSE;
}



/******************************************************************************
* FUNC: //
******************************************************************************/

BOOL GetCstChar_EvtSuper(U8 mThing, const TCstChar_st **pRtnChar)
{
U8 charDefMax;
U8 ii;

	charDefMax = sizeof(cstEvtSuperChar) / sizeof(TCstEvtThing_st);
	for(ii=0; ii<charDefMax; ii++)
	{
		if(cstEvtSuperChar[ii].thing == mThing)
		{
			*pRtnChar = &cstEvtSuperChar[ii].stChar;
			return TRUE;
		}
	}
	
	*pRtnChar = &cstEvtSuperChar[charDefMax-1].stChar;
	return FALSE;
}



/******************************************************************************
* FUNC: // 事件类型，string
*   IN:
*  OUT:
******************************************************************************/

BOOL GetCstChar_EvtCls(U8 mEvtCls, const TCstChar_st **pRtnChar)
{
U8 charDefMax;
U8 ii;

	charDefMax = sizeof(cstEvtClsChar) / sizeof(TCstEvtThing_st);
	for(ii=0; ii<charDefMax; ii++)
	{
		if(cstEvtClsChar[ii].thing == mEvtCls)
		{
			*pRtnChar = &cstEvtClsChar[ii].stChar;
			return TRUE;
		}
	}
	
	*pRtnChar = &cstEvtClsChar[charDefMax-1].stChar;
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
