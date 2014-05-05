#ifndef __sysStatus_H__
#define __sysStatus_H__
/******************************************************************************
* @file    sysStatus.c
* @author  yx
* @version V1.1
* @date    2013.9.10 
* @brief   
*
* V1.1, 2013.9.10 
* 	add: bSysStatus_TurnPageSerial(); 
* V1.0, 2012-01-05
* 
#include  "sysStatus.h"
******************************************************************************/
// 

#include  "prjCompileCon.h"
/*================= extern ============================================*/
#ifdef  __sysStatus_C__
#define EX_sysStatus
#else
#define EX_sysStatus extern 
#endif

/*================= ���� ============================================*/
enum emSysBoolStatus{
	U_SysSta_bNeedReset, //��Ҫ��λ
	U_SysSta_bResetIng,  //��λ��
	
	//���ϴθ�λ��
	U_SysSta_bHaveAlarm,
	U_SysSta_bHaveLink,
	U_SysSta_bHaveRun,
	U_SysSta_bHaveAck,
	U_SysSta_bHaveFault,
	U_SysSta_bHaveDisable,
	
	//״̬��
	U_SysSta_bSilence,
	U_SysSta_bClockChanged, //ʱ������仯
	U_SysSta_bAutoManuChanged, //
	
	U_SysSta_bTurnPageSerial,
	
	U_SysSta_,
	/*
	U_SysSta_,
	U_SysSta_,
	U_SysSta_,
	U_SysSta_,
	U_SysSta_,
	U_SysSta_,
	U_SysSta_,
	U_SysSta_,
	*/
	
	
	U_SysBoolSta_MAX,
};

	
//#define 
/*================= �ṹ�嶨�� ======================================*/

/*================= ���нṹ�������� ================================*/

typedef struct{
	U8 machineAddr;
	
	
	
}TSysConfig_st;

//TStruct_st stStruct;


/*================= ���к������� ====================================*/

EX_sysStatus void Init_SysStatus(void);
EX_sysStatus void SetSysState(U32 sysBoolStateItem);
EX_sysStatus void ClrSysState(U32 sysBoolStateItem);
EX_sysStatus U8 GetSysState(U32 sysBoolStateItem);
extern BOOL bSysStatus_TurnPageSerial(void);

/*================= ���к������� ===============================*/
//
EX_sysStatus U8 getMachineMeAddr(void);
EX_sysStatus U8 GetLanguage(void);



/*
EX_sysStatus void SysStaSetReset(void);
EX_sysStatus void SysStaResetFinish(void);
EX_sysStatus U8 bSysStaReseting(void);
*/



EX_sysStatus U8 bSysStaReseting(void);


/******************************************************************************
// END :
******************************************************************************/
#endif // __sysStatus_H__

