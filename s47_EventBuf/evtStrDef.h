#ifndef __evtStrDef_H__
#define __evtStrDef_H__
/******************************************************************************
* @file    evtStrDef.h
* @author  yx
* @version V1.2
* @date    2013-09-23
* @brief   TEvtBufWho_st; 
*  		 �����¼��Ķ��� �ṹ;


* @Versin history:
* V1.2, 2013-09-23 
*		�ı䣺TEvtLink_st�� TEvtExtg_st  Ϊ����ģʽ
*		���� "TEvtBufWho_st", "TEvtPos_st" -> "evtStrCommon"
* V1.1, 2013-09-11
*		�ı䣺TEvtLink_st�� TEvtExtg_st
* V1.0, 2012-09-09
* 
#include  "evtStrDef.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

#include  "strDevice.h"
#include  "strClock.h"

#include  "evt_Para.h"
#include  "evtStrCommon.h"
/*=================  ============================================*/


/*================= �¼����� �����ṹ ================================*/
#pragma pack(1)	
typedef struct{
	TEvtPos_st  stPos;
	U8 thing;
	TEvtClock_st evtClock;
}TEvtAlarm_st; //

typedef struct{
	TEvtPos_st  stPos;
	U8 thing;
	TEvtClock_st evtClock;
}TEvtFault_st; //


// typedef struct{
	// TEvtPos_st  stPos;
	// U8 thingAction; //����״̬
	// U8 delayActSec; // ������ʱ ʣ��s:
	// U8 thingAck;    //����״̬
	// TEvtClock_st evtClockAction;
	// TEvtClock_st evtClockAck;
// }TEvtLink_st; // U_ModuEvt_EVT

typedef struct{
	TEvtPos_st  stPos;
	U8 thing; //���������� ״̬
	U8 delayActSec; // ������ʱ ʣ��s:
	TEvtClock_st evtClock;
}TEvtLink_st; // U_ModuEvt_EVT

// typedef struct{
	// TEvtPos_st  stPos;
	// U8 thingCircuit; 	 // ��������: ���⶯���������豸����������������
	// U8 thingAnnunciator; // ���� ���Ե������� 
	// U8 thingSpray;   	 // ��������������ֹͣ��
	// U8 thgSprayAck;   	 // ��������
	// U8 delaySpraySec; 	 // ������ʱ ʣ��s:
	// TEvtClock_st evtClockAnnu; // 
	// TEvtClock_st evtClockSpray; // ����;
	// TEvtClock_st evtClockSpryAck; // ��������;
// }TEvtExtg_st; // U_ExtgEvt_EVT

typedef struct{
	TEvtPos_st  stPos;
	U8 thing; 	 // ��������: ���⶯���������豸����������������
	U8 delaySpraySec; 	 // ������ʱ ʣ��s:
	TEvtClock_st evtClock; //
}TEvtExtg_st; // U_ExtgEvt_EVT


typedef struct{
	TEvtPos_st  stPos;
	U8 thing;
	TEvtClock_st evtClock;
}TEvtSpvs_st; //

typedef struct{
	TEvtPos_st  stPos;
	U8 thing;
	TEvtClock_st evtClock;
}TEvtDsab_st; //
#pragma pack()





/******************************************************************************
// END :
******************************************************************************/
#endif // __evtStrDef_H__

