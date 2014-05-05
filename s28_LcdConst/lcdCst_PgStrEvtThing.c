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


/*================= ���� ============================================*/

/*=================  ================================================*/
/******************************************************************************
* FUNC: //
******************************************************************************/

// �¼����:
const TCstEvtThing_st cstEvtClsChar[] =
{
	{U_EvtCls_Alarm, {"��", "alarm", ""}},
	{U_EvtCls_Fault, {"����", "fault ", ""}},
	{U_EvtCls_Link, {"����", "link", ""}},
	{U_EvtCls_Extg, {"����", "extg", ""}},
	{U_EvtCls_Spvs, {"���", "spvs", ""}},
	{U_EvtCls_Dsab, {"����", "dsab", ""}},
	
	// {DDD, {"", "", ""}},
};
/******************************************************************************
* FUNC: //
******************************************************************************/
// �¼���link-modu:
const TCstEvtThing_st cstEvtLinkModuChar[] =
{
	{U_ModuManuRun_EVT, 	{"�ֶ�����", "mRun", ""}},
	{U_ModuManuStop_EVT, 	{"�ֶ�ֹͣ", "mStop", ""}},
	{U_ModuAutoRun_EVT, 	{"�Զ�����", "aRun", ""}},
	{U_ModuAutoRunDelay_EVT,{"������ʱ", "delay", ""}},
	{U_ModuRunDelayCancel_EVT, {"������ʱ����", "dlyRs", ""}},
	{U_ModuAutoStop_EVT, 	{"�Զ�ֹͣ", "aStop", ""}},
	{U_ModuAck_EVT, 	{"����", "ack", ""}},
	{U_ModuAckRstr_EVT, {"��������", "ackRs", ""}},
	{U_ModuMissAck_EVT, {"����ȱʧ", "ackMiss", ""}},
	
	{U_EVT_INVALID, 	{"δʶ��", "no", ""}} // ���һ�����⹦�ܣ�һֱ�����
	// {DDD, {"", "", ""}},
};

/******************************************************************************
* FUNC: //
******************************************************************************/
// �¼���extg:
const TCstEvtThing_st cstEvtExtgChar[] =
{
	{U_ExtgCircleRun_EVT, 	{"��������", "run", ""}},
	{U_ExtgCircleSec_EVT, 	{"����ʱ", "delay", ""}},
	{U_ExtgCircleStop_EVT, 	{"����ֹͣ", "stop", ""}},
	{U_ExtgAnnuRun_EVT, 	{"��������", "hlRun", ""}},
	{U_ExtgAnnuStop_EVT, 	{"����ֹͣ", "hlStop", ""}},
	{U_ExtgAuxRun_EVT, 		{"�����豸����", "auxRun", ""}},
	{U_ExtgAuxStop_EVT, 	{"�����豸ֹͣ", "auxStop", ""}},
	{U_ExtgSprayRun_EVT, 	{"��������", "etRun", ""}},
	{U_ExtgSprayStop_EVT, 	{"����ֹͣ", "etStop", ""}},
	{U_ExtgSprayAck_EVT, 	{"��������", "", "etAck"}},
	{U_ExtgSprayAckRstr_EVT, {"������������", "ackRs", ""}},
	{U_ExtgSprayMissAck_EVT, {"��������ȱʧ", "ackMiss", ""}},
	
	{U_EVT_INVALID, 	{"δʶ��", "no", ""}} // ���һ�����⹦�ܣ�һֱ�����
	// {DDD, {"", "", ""}},
};

/******************************************************************************
* FUNC: //
******************************************************************************/
// �¼���alarm:
const TCstEvtThing_st cstEvtAlarmChar[] =
{
	{U_Alarm_EVT, 	{"��", "", ""}},
	
	{U_EVT_INVALID, 	{"δʶ��", "", ""}} // ���һ�����⹦�ܣ�һֱ�����
	// {DDD, {"", "", ""}},
};


/******************************************************************************
* FUNC: //
******************************************************************************/
// �¼���Fault:
const TCstEvtThing_st cstEvtFaultChar[] =
{
	{U_Fault_EVT, 		{"����", "", ""}},
	{U_FaultRstr_EVT, 	{"���ϳ���", "", ""}},
	
	{U_EVT_INVALID, 	{"δʶ��", "", ""}} // ���һ�����⹦�ܣ�һֱ�����
	// {DDD, {"", "", ""}},
};

/******************************************************************************
* FUNC: //
******************************************************************************/
// �¼���Opea:
const TCstEvtThing_st cstEvtOpeaChar[] =
{
	{U_Reset_EVT, {"��λ", "", ""}},
	{U_PwrOff_EVT, {"�ػ�", "", ""}},
	{U_Disable_EVT, {"����", "", ""}},
	{U_DisableRstr_EVT, {"���γ���", "", ""}},
	
	{U_EVT_INVALID, 	{"δʶ��", "", ""}} // ���һ�����⹦�ܣ�һֱ�����
	// {DDD, {"", "", ""}},
};


/******************************************************************************
* FUNC: //
	U_Super_FlsErase_EVT,
	U_Super_FlsCopyRenew_EVT,
	
******************************************************************************/
// �¼���Super:
const TCstEvtThing_st cstEvtSuperChar[] =
{
	{U_Super_FlsErase_EVT, {"flash����", "", ""}},
	{U_Super_FlsCopyRenew_EVT, {"flash������", "", ""}},
	
	{U_EVT_INVALID, 	{"δʶ��", "", ""}} // ���һ�����⹦�ܣ�һֱ�����
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
* FUNC: // �¼����ͣ�string
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
