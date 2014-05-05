#define __sim_saveItem_C__
/******************************************************************************
* @file    sim_saveItem.c
* @author  yx
* @version V1.0
* @date    2013-10-30
* @brief   ��ʵ�ʴ洢����;
* @brief   

******************************************************************************/
#include  "sim_saveItem.h"

#include  "sysDef.h"
#include  "tmrTick.h"
#include  "codeComm.h"

#include  "saveInc_Extern.h"
#include  "flsReDef.h"

#include  "saveTask.h"
#include  "Save_Manage_incOut.h"
#include  "Save_Item_incOut.h"
#include  "Save_Hist_incOut.h"

//#include "incFile.h"	

/******************************************************************************
* ˵����
* ��s78_phSaveLib��~ ��s78_44_ItemSerialUnFixAdr������������ļ������Ĳ��֣�
*  ��Ҫ������¼��Ľṹ����s77_phSaveDef��"strFlsItmStruct.h"
*  ��Ҫ������ļ��ĵ�ַ����s77_phSaveDef��"strFlsAdrDef"
*  ��Ҫ������ļ������ࣺ��s78_40_ItemM��~ ��s78_44_ItemSerialUnFixAdr����
*  ��ʷ��¼�ı��棺��s78_24_Hist��"saveHistory"
* save����init: 	Init_SaveTask();
* save��������ִ��: SaveTask_Exec();
* 
* ������ڣ�"Save_Manage_incOut.h"  "Save_Item_incOut.h"   "Save_Hist_incOut.h"

* 
******************************************************************************/


#if U_SYS_Test_Flash_SimTask == U_YES
/*================= ���� ============================================*/

/*================= �ṹ���� ========================================*/

/*================= ˽�нṹ�������� ================================*/
typedef struct{
	U8 step;
	
	U8 mFlsId;
}TSimSaveTask;

static TSimSaveTask stSimTask;
/*================= ���к������� ====================================*/

/*================= ˽�к������� ====================================*/

/*=================  ================================================*/
		
/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

void Sim_Init_SaveTask(void)
{
	ClrRamIs00((U8 *)(&stSimTask), sizeof(stSimTask)); 
	Init_SaveTask(); // TRUE=OK;
	SetTmrTickTask(TASK_FlsSim100ms, TMR_FlsSim100ms);
}


/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

void Sim_Exec_SaveTask(void)
{
	SaveTask_Exec();
	
//	simSave_SysSet_task();
}


/******************************************************************************
* FUNC: // 
*   IN:
*  OUT: 
******************************************************************************/

void simSave_PnConfig_task(void)
{
	
}



void simSave_PnConfig_Get(void)
{
BOOL bSucc;

	bSucc = FlsRd_PnConfig();
	
	bSucc = bSucc;
}

/******************************************************************************
* FUNC: // 
*   IN:
*  OUT: 
******************************************************************************/

void simSave_SysSet_task(void)
{
	switch(stSimTask.step)
	{
		case emSimSv_SysSet_Read: // = 0,
			simSave_SysSet_Get();
			stSimTask.step = emSimSv_SysSet_Save;
			break;
		case emSimSv_SysSet_Save: // = 1,
			simSave_SysSet_Set();
			break;
		case emSimSv_SysSet_SavIng: // = 2,
			simSave_SysSet_waitSaveFinish();
			break;
		case emSimSv_SysSet_HaveResult: // = 3,
		case emSimSv_SysSet_SavOverTime: // = 4,
			stSimTask.step = emSimSv_SysSet_ReadAfterSv;
			break;
		case emSimSv_SysSet_ReadAfterSv: // = 5,
			simSave_SysSet_Get();
			break;
			
		case emSimSv_SysSet_Idle: // = 6,
		default:
			break;
	}
}




void simSave_SysSet_waitSaveFinish(void)
{
BOOL bSucc;

	if(!(stSimTask.step == emSimSv_SysSet_SavIng))
	{
		return;
	}
	
	if(GetTickTaskStatus(TASK_FlsSim100ms) == TRUE)
	{
		stSimTask.step = emSimSv_SysSet_SavOverTime;
	}
	else
	{
		if(bIsFinish_FlsExe(stSimTask.mFlsId, &bSucc))
		{
			FlsIdClrAssign(stSimTask.mFlsId);
			stSimTask.step = emSimSv_SysSet_HaveResult;
		}
	}
	bSucc = bSucc;
}

void simSave_SysSet_Set(void)
{
TFlsSysSet_un *pSysSet;
BOOL bSucc;

	stSimTask.step = emSimSv_SysSet_Save;
	pSysSet = pGetFlsSysSet();
	pSysSet->stSet.language = U_Chinese_LANGUAGE;
	pSysSet->stSet.machAdr = 2;
	pSysSet->stSet.machMasterOrSlave = U_MACHINE_MASTER;
	
	if(FlsIdNewAssign(U_SysTask_LcdShow, &stSimTask.mFlsId))
	{
		bSucc = FlsSysSetMeStatus_Save(
						U_SysTask_LcdShow, stSimTask.mFlsId);
		SetTmrTickTask(TASK_FlsSim100ms, 10);
		stSimTask.step = emSimSv_SysSet_SavIng;
	}
	bSucc = bSucc;
}

void simSave_SysSet_Get(void)
{
BOOL bSucc;
TFlsSysSet_un *pSysSet;

	bSucc = FlsRd_MeStatus();
	pSysSet = pGetFlsSysSet();
	
	bSucc = pSysSet->stSet.verify;
	bSucc = bSucc;
}


/******************************************************************************
* FUNC: // END
*   IN:
*  OUT: 
******************************************************************************/
#endif // U_SYS_Test_Flash_SimTask
