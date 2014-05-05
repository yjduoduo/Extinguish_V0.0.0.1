#ifndef __sim_saveItem_H__
#define __sim_saveItem_H__
/******************************************************************************
* @file    sim_saveItem.h
* @author  yx
* @version V1.0
* @date    2013-10-30
* @brief   ��ʵ�ʴ洢����;
* 
#include  "sim_saveItem.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

/*================= extern ============================================*/
#ifdef  __sim_saveItem_C__
#define EX_sim_saveItem
#else
#define EX_sim_saveItem extern 
#endif

#if U_SYS_Test_Flash_SimTask == U_YES
/*================= ���� ============================================*/
typedef enum{
	emSimSv_SysSet_Read = 0,
	emSimSv_SysSet_Save = 1,
	emSimSv_SysSet_SavIng = 2,
	emSimSv_SysSet_HaveResult = 3,
	emSimSv_SysSet_SavOverTime = 4,
	emSimSv_SysSet_ReadAfterSv = 5,
	emSimSv_SysSet_Idle = 6,
}emSimSave_SysSet;
/*================= �ṹ�嶨�� ======================================*/

/*================= ���нṹ�������� ================================*/

/*================= ˽�к������� ====================================*/
#ifdef  __sim_saveItem_C__


void simSave_PnConfig_task(void);
void simSave_PnConfig_Get(void);


void simSave_SysSet_task(void);
void simSave_SysSet_Get(void);
void simSave_SysSet_Set(void);
void simSave_SysSet_waitSaveFinish(void);

#endif  //__sim_saveItem_C__
/*================= ���к������� ====================================*/
//EX_sim_saveItem 

extern void Sim_Init_SaveTask(void);
extern void Sim_Exec_SaveTask(void);

/******************************************************************************
// END :
******************************************************************************/
#endif // U_SYS_Test_Flash_SimTask
#endif // __sim_saveItem_H__

