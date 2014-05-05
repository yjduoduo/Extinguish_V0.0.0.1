
#define __tmrTick_C__
/******************************************************************************
* @file    tmrTick.c
* @author  yx
* @version V1.1
* @date    2013-07-19
* @brief  

* V1.1, 2013-07-19, ��taskId,�����������ʱͳһ���漰����tmr��Kill.
******************************************************************************/
#include  "tmrTick.h"
#include  "prjBool.h"

//#include "..\\s00Prj\\incFile.h"	

/*================= ���� ============================================*/

#define U_TIMERTICK_R_MAX  0x10000 //65536ms=65s //��Ҫ��ֹ�������ͷ�Χ
#define U_TIMERTICK_R_MASK  (U_TIMERTICK_R_MAX - 1) //��Ҫ��ֹ�������ͷ�Χ

//#define U_TIMER_TICK_MS   U_MyTickTmrCycle //ÿ�ζ�ʱ�жϵ�ms

/*================= �ṹ���� ========================================*/

/*================= ˽�нṹ�������� ================================*/
#pragma pack(4)
typedef struct //TTaskTimer_str
{
	U8		IsUsing;	//�ö�ʱ���Ƿ�ʹ�ñ�־
    U8		Sign;	//�������õĶ�ʱ������
	U8 taskId;  //emSysTask
    U32	SetMSec;	//Ҫ��ʱ��ms,��1msΪ��λ		
    U32	OrgMSec;	//��������ʱ��d1msTimer	
}TTaskTimer_st; 
#pragma pack()

static TTaskTimer_st stTaskTimer[MAX_TICK_TASK_NUM]; 

static U32 dIntrAddMs;
static BOOL bHaveIntr;

static U32 d1msTimer;
static U32 d100msTimer;
static U32 dN00msTimer;
static U32 d1sTimer;
static U32 dNsTimer;

static U8 tmr100msLow = TASK_100MS_LOW; //�����ض����Ӱ��
static U8 tmr1sLow = TASK_1S_LOW;
/*================= ���к������� ====================================*/

/*================= ˽�к������� ====================================*/
//void IntTimerInterrupt(BOOL i); //��ʱ�ж� 
void timerTickInterrupt(U8 bAllow);

/*=================  ================================================*/

/******************************************************************************
* NAME: 
* FUNC: //ʱ�������ʼ��
*   IN:
*  OUT:
******************************************************************************/
void InitTmrTickTask (void) //ʱ�������ʼ�� 
{
U8 tmrID;
	
	dIntrAddMs = 0; 
	
	d1msTimer = 0x0;
	d100msTimer = 0x0;
	dN00msTimer = 0x0;
	d1sTimer = 0x0;
	dNsTimer = 0x0;
	
	
	tmr100msLow = Get_TmrId_100msLow(); //�����ض����Ӱ��
	tmr1sLow = Get_TmrId_1sLow();
	
	for(tmrID=0; tmrID<MAX_TICK_TASK_NUM; tmrID++)
	{
		stTaskTimer[tmrID].IsUsing = FALSE;
	}
}

/******************************************************************************
* NAME: 
* FUNC: //
*   IN:
*  OUT:
******************************************************************************/
void timerTickInterrupt(U8 bAllow)
{
	TickTimer_HdInt(bAllow);  //hd
	
}


/******************************************************************************
* NAME: 
* FUNC: //����ʱ�������״̬ ������
*   IN:
*  OUT:
* 
******************************************************************************/
BOOL GetTickTaskStatus (U8 tmrID)
{
BOOL succ;
    if(tmrID >= MAX_TICK_TASK_NUM)
        return FALSE;
    timerTickInterrupt(FORBID);
	succ = stTaskTimer[tmrID].Sign;
    stTaskTimer[tmrID].Sign = 0;
	timerTickInterrupt(ALLOW);
    return succ;
}

BOOL GetTickTaskStaNoClr (U8 tmrID)
{
BOOL succ;
    if(tmrID >= MAX_TICK_TASK_NUM)
        return FALSE;
    timerTickInterrupt(FORBID);
	succ = stTaskTimer[tmrID].Sign;
	timerTickInterrupt(ALLOW);
    return succ;
}
/******************************************************************************
* NAME: 
* FUNC: //�ж��Ƿ�using
*   IN:
*  OUT:
* 
******************************************************************************/
BOOL JudgeTickTaskUsing (U8 tmrID)		
{
    if(tmrID >= MAX_TICK_TASK_NUM)
        return FALSE;
	return stTaskTimer[tmrID].IsUsing;
}

/******************************************************************************
* NAME: 
* FUNC: //��ʼʱ������
*   IN: taskId:emSysTask
*  OUT:
* 
******************************************************************************/
BOOL SetTmrTickTsk_haveTaskId(U8 tmrID, U32 SetMSec, U8 taskId)/*����ţ���ʱ�����ƣ���ʱʱ��*/
{
	if(SetTmrTickTask(tmrID, SetMSec))
	{
		stTaskTimer[tmrID].taskId = taskId; 
		return TRUE;
	}
	return FALSE;
}

void KillTickTsk_TaskId(U8 taskId)
{
U8 tmrID;
	for(tmrID=0; tmrID<MAX_TICK_TASK_NUM; tmrID++)
	{
		if(stTaskTimer[tmrID].taskId == taskId)
		{
			KillTickTask(tmrID);       //ȡ��ʱ������
		}
	}
}


/******************************************************************************
* NAME: 
* FUNC: //��ʼʱ������
*   IN: 
*  OUT:
* 
******************************************************************************/
BOOL SetTmrTickTask (U8 tmrID, U32 SetMSec)/*����ţ���ʱ�����ƣ���ʱʱ��*/
{
    if(tmrID >= MAX_TICK_TASK_NUM)
	{
        return FALSE;
	}
    timerTickInterrupt(FORBID);
	if(stTaskTimer[tmrID].IsUsing == TRUE)
		KillTickTask(tmrID);
	
	stTaskTimer[tmrID].SetMSec = SetMSec; 
	if(tmrID < tmr100msLow)
		stTaskTimer[tmrID].OrgMSec = d1msTimer; 
	else if(tmrID < tmr1sLow)
		stTaskTimer[tmrID].OrgMSec = dN00msTimer;
	else
		stTaskTimer[tmrID].OrgMSec = dNsTimer; 
    stTaskTimer[tmrID].Sign = FALSE;
    stTaskTimer[tmrID].IsUsing = TRUE;
	stTaskTimer[tmrID].taskId = ~0; 
	timerTickInterrupt(ALLOW);
    return TRUE;
    
}


/******************************************************************************
* NAME: 
* FUNC: ���ü�ʱ����־
*   IN: 
*  OUT:
* 
******************************************************************************/
void SetTickTaskSign (U8 tmrID)
{
    if(tmrID >= MAX_TICK_TASK_NUM)
        return;
    timerTickInterrupt(FORBID);
    stTaskTimer[tmrID].Sign = TRUE;
	timerTickInterrupt(ALLOW);
}
void ClrTickTaskSign (U8 tmrID)
{
    if(tmrID >= MAX_TICK_TASK_NUM)
        return;
    timerTickInterrupt(FORBID);
    stTaskTimer[tmrID].Sign = 0;
	timerTickInterrupt(ALLOW);
}
/******************************************************************************
* NAME: 
* FUNC: ���¼�ʱtmrID��signʱ�ӵĹ���
*   IN:
*  OUT:
******************************************************************************/
void ClearTickTaskTmr (U8 tmrID)
{
    if(tmrID >= MAX_TICK_TASK_NUM)
        return;
    timerTickInterrupt(FORBID);
	if(tmrID < tmr100msLow)
		stTaskTimer[tmrID].OrgMSec = d1msTimer; 
	else if(tmrID < tmr1sLow)
		stTaskTimer[tmrID].OrgMSec = dN00msTimer;
	else
		stTaskTimer[tmrID].OrgMSec = dNsTimer; 
	
	stTaskTimer[tmrID].Sign = FALSE;
	timerTickInterrupt(ALLOW);
}

/******************************************************************************
* NAME: 
* FUNC: //ֹͣtmrID��signʱ�ӵĹ���
*   IN:
*  OUT:
* 
******************************************************************************/

BOOL KillTickTask (U8 tmrID)
{
    if(tmrID >= MAX_TICK_TASK_NUM)
        return FALSE;
    timerTickInterrupt(FORBID);
    stTaskTimer[tmrID].IsUsing  = FALSE; 
    stTaskTimer[tmrID].Sign  = FALSE; 
	timerTickInterrupt(ALLOW);
    return TRUE;
}

/******************************************************************************
* FUNC: ��ʱ�ж�. ��
*   IN:
*  OUT:
******************************************************************************/

void IntrAddTickMs(U32 mMsNum)
{
	dIntrAddMs += mMsNum;
	bHaveIntr = TRUE;
	
}

U8 bHaveTmrTickIntr(void)
{
	return bHaveIntr;
}


/******************************************************************************
* NAME: 
* FUNC: 
*   IN:
*  OUT:
******************************************************************************/

U8 GetTick100msLow(void)
{
	return tmr100msLow;
}

BOOL bGetTickIntr(void)
{
	return bHaveIntr;
}

U32 GetTickIntrAddMs(void)
{
	return dIntrAddMs;
}

U32 GetTickTmrNowMs(void)
{
	return d1msTimer;
}

U32 GetTickTmrNowN00Ms(void)
{
	return dN00msTimer;
}

U32 GetTickTmrNowNs(void)
{
	return dNsTimer;
}


/******************************************************************************
* NAME: 
* FUNC: ��ʱ�ж�
*   IN:
*  OUT:
******************************************************************************/

void TickTaskWork (void)   //ϵͳ�¼���ʱ
{
U8 tmrID;
U32 mDiff;
U32 mTickMs = 0;
	
	if(!bHaveIntr)
	{
		return;
	}
    timerTickInterrupt(FORBID);
	bHaveIntr = FALSE;
	mTickMs = dIntrAddMs;
	dIntrAddMs = 0;
    timerTickInterrupt(ALLOW);
	
	d1msTimer += mTickMs;
	if(d1msTimer >= U_TIMERTICK_R_MAX)
	{
		d1msTimer -= U_TIMERTICK_R_MAX;
	}
	//if(d1msTimer<10)
	//	d1msTimer = 0;
	for(tmrID=0; tmrID<tmr100msLow; tmrID++)
	{
		if(stTaskTimer[tmrID].IsUsing == FALSE)
			continue;
		if(d1msTimer >= stTaskTimer[tmrID].OrgMSec)
			mDiff = d1msTimer-stTaskTimer[tmrID].OrgMSec;
		else
			mDiff = U_TIMERTICK_R_MASK - stTaskTimer[tmrID].OrgMSec + 1 + d1msTimer;
		
		if(mDiff >= stTaskTimer[tmrID].SetMSec)
		{
			stTaskTimer[tmrID].OrgMSec = d1msTimer;
			stTaskTimer[tmrID].Sign = TRUE;
		}
	}
	
	d100msTimer += mTickMs;
	if(d100msTimer >= 100)
	{
		d100msTimer -= 100;
		dN00msTimer++;
		if(dN00msTimer >= U_TIMERTICK_R_MAX)
		{
			dN00msTimer -= U_TIMERTICK_R_MAX;
		}
		
		for(tmrID=tmr100msLow; tmrID<tmr1sLow; tmrID++)
		{
			if(stTaskTimer[tmrID].IsUsing == FALSE)
				continue;
			if(dN00msTimer >= stTaskTimer[tmrID].OrgMSec)
				mDiff = dN00msTimer - stTaskTimer[tmrID].OrgMSec;
			else
				mDiff = U_TIMERTICK_R_MASK - stTaskTimer[tmrID].OrgMSec + 1 + dN00msTimer;
			if(mDiff >= stTaskTimer[tmrID].SetMSec)
			{
				stTaskTimer[tmrID].OrgMSec = dN00msTimer;
				stTaskTimer[tmrID].Sign = TRUE;
			}
		}	
	}
	
	d1sTimer += mTickMs;
	if(d1sTimer >= 1000)
	{
		d1sTimer -= 1000;
		dNsTimer++;		
		if(dNsTimer >= U_TIMERTICK_R_MAX)
		{
			dNsTimer -= U_TIMERTICK_R_MAX;
		}
		
		for(tmrID=tmr1sLow; tmrID<MAX_TICK_TASK_NUM; tmrID++)
		{
			if(stTaskTimer[tmrID].IsUsing == FALSE)
				continue;
			if(dNsTimer >= stTaskTimer[tmrID].OrgMSec)
				mDiff = dNsTimer - stTaskTimer[tmrID].OrgMSec;
			else
				mDiff = U_TIMERTICK_R_MASK - stTaskTimer[tmrID].OrgMSec + 1 + dNsTimer;
			if(mDiff >= stTaskTimer[tmrID].SetMSec)
			{
				stTaskTimer[tmrID].OrgMSec = dNsTimer;
				stTaskTimer[tmrID].Sign = TRUE;
			}
		}	
	}
}


/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

