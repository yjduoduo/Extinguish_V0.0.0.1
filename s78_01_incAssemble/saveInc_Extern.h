#ifndef __saveInc_Extern_H__
#define __saveInc_Extern_H__
/******************************************************************************
* @file    saveInc_Extern.h
* @author  yx
* @version V1.5
* @date    2013-09-23
* @brief   ��Ҫmaster����ĺ���
* 
* V1.5, 2013-09-23
* 		add:  FlsMeStatus_Default();
		add:  GetPanelType_...();
* V1.4, 2013-09-10 
		�޸�ע�ͣ�������Դ��
* V1.3, 2013-09-4
*
#include  "saveInc_Extern.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

#include  "strEvtTrans.h"
#include  "strFlsItmStruct.h"

/*================= �¼����� ====================================*/
// EX_evt_Class

// ��ʷ��¼���� ����
// *  OUT: bits: (1 << U_HIST_CLASS_MAX)
extern U32 EvtThing_toHistClsBits(TEvtTrans_st *pEvtTrans); 


// *  OUT: �¼� emevtThingDef;
extern U8 GetEvtThingDef_Fault(void);
extern U8 GetEvtThingDef_FlsErase(void);
extern U8 GetEvtThingDef_FlsCopyRenew(void);

extern U8 GetEvtThingDef_PwrOff(void);
/*================= ====================================*/
// EX_sysDef 

// *  OUT: flash������taskId. [emSysTask]
extern U8 GetSysTaskId_FlsVerify(void);

/*================= ���к������� ====================================*/
//EX_sysPanel 

// Panel�Ǽǵı�־�� = bRegisted.
extern void Panel_Regist(U8 pnICanSequ, BOOL bRegisted);

//��Ԫ���� in emPanelType
extern BOOL bPnTypeIsValid(U8 pnType);

/*================= ���к������� ====================================*/
//EX_sysMachine 

// Machine�Ǽǵı�־�� = bRegisted.
extern void Machine_Regist(U8 mMachineSequ, BOOL bRegisted);

/*================= ���к�������-lib�� ====================================*/
//EX_saveItemAux 

extern void FlsMeStatus_Default(TFlsSysSet_un *pSet);

/*================= ���к������� ====================================*/
//EX_sysPanel 

extern U8 GetPanelType_Loop(void);
extern U8 GetPanelType_Extg(void);
extern U8 GetPanelType_Drt(void);

/*================= ��Ԫ��������====================================*/
// EX_sysDef 

extern BOOL bMachineIdIsMe(U8 mMachine);
extern U8 GetMachineMaster(void);
extern U8 GetLanguageChinese(void);

// �������ţ�
extern U8 GetMachineMax(void);
extern BOOL bMachineValid(U8 mMachine);

// Panel��˳��ţ�
extern U8 GetPanelTotalSequMax(void);
extern BOOL bPanelTotalSequValid(U8 mPnSequ);

/*================= ���к�������-master ====================================*/
//EX_saveTmrPwroffAndHist 

//����ػ�ʱ��Ķ�ʱ��
extern void SavePwrOff_Tmr_Init(void);
extern BOOL bSavePwrOff_Arrived(void);
extern void FlsWr_pwrOff_Start(void); //-> FlsWr_pwrOff_New(&stClock);


//������ʷ��¼��ʱ������
extern void SaveHist_Tmr_Init(void);
extern BOOL bSaveHist_Arrived(void);

// save���񣬶�ʱɾ���Ķ�ʱ��
extern void SaveFlsId_Tmr_Init(void);
extern BOOL bSaveFlsId_Arrived(void);


/*================= ���к������� ====================================*/
// EX_phClock
extern void GetRamEvtTimer(TEvtClock_st *pEvtClock);

//EX_mRunTask 
// ��Ҫ�ϸ�ʱִ�е�task. ��ϵͳ��ʱ��ִ��ĳtask�ļ�϶insert.
extern void RunCycle_OnTime(void);
/******************************************************************************
// END :
******************************************************************************/
#endif // __saveInc_Extern_H__

