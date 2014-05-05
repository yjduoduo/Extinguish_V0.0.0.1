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

/*================= 常数 ============================================*/
enum emSysBoolStatus{
	U_SysSta_bNeedReset, //需要复位
	U_SysSta_bResetIng,  //复位中
	
	//自上次复位后：
	U_SysSta_bHaveAlarm,
	U_SysSta_bHaveLink,
	U_SysSta_bHaveRun,
	U_SysSta_bHaveAck,
	U_SysSta_bHaveFault,
	U_SysSta_bHaveDisable,
	
	//状态：
	U_SysSta_bSilence,
	U_SysSta_bClockChanged, //时钟有秒变化
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
/*================= 结构体定义 ======================================*/

/*================= 公有结构变量声明 ================================*/

typedef struct{
	U8 machineAddr;
	
	
	
}TSysConfig_st;

//TStruct_st stStruct;


/*================= 公有函数声明 ====================================*/

EX_sysStatus void Init_SysStatus(void);
EX_sysStatus void SetSysState(U32 sysBoolStateItem);
EX_sysStatus void ClrSysState(U32 sysBoolStateItem);
EX_sysStatus U8 GetSysState(U32 sysBoolStateItem);
extern BOOL bSysStatus_TurnPageSerial(void);

/*================= 公有函数声明 ===============================*/
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

