#ifndef __saveManage_H__
#define __saveManage_H__
/******************************************************************************
* @file    saveManage.h
* @author  yx
* @version V1.1
* @date    2013.9.23
* @brief   ��lib�Ĺ�������ڡ�
*		дflash����
*			�ָ�����ҲҪ�ڴ˿����½��С�
*		����[PeriphSave] saveX.c�
* 
Ϊ��ֹĳsectorδд���������ϵ��Ĳ���head,endӦ�������ҡ�
* ���part1���ж�: �� "ProjectStruct.h"
*
*0x100000�ֽڣ�1us, 0x100000us=1048576us = 1048ms = 1s.
*
* @version history
* V1.1��2013.9.23 
* 		�Ըı�������
* V1.0��2013-07-23
* 
#include  "saveManage.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

#include  "flsStoreBytesDef.h"
#include  "strFlsAdrDef.h"

/*================= extern ============================================*/
#ifdef  __saveManage_C__
#define EX_saveManage
#else
#define EX_saveManage extern 
#endif
/*================= ���� ============================================*/

typedef enum {
	emSave_Opea_Erase = 1,
	emSave_Opea_PwrOff,
	emSave_Opea_Hist,
	emSave_Opea_Item,
	emSave_Opea_FlsCopy,
	
}emSaveOpeaClass;
/*================= �ṹ�嶨�� ======================================*/

/*================= ˽�к������� ====================================*/
#ifdef  __saveManage_C__

// �ж��Ƿ���δ����������������Ҫ��������
// TRUE = !Erase & !FlsWr & !WorkHist & !WorkPwrOff & !WorkItem;
// �����flsTask_OpeaOne()������һ�¡��� copyTask();
static BOOL bFlsTask_isIdle(void);

// TRUE = flash busy or opeaOne; FALSE=idle;
static BOOL flsTask_OpeaOne(void);

// bStartOpea_...()��
// ��ʼ�����񡣰����ȼ����С�
// master: SaveManage_Exec();
static BOOL bStartOpea_Erase(void);
static BOOL bStartOpea_Item(void);
static BOOL bStartOpea_Hist(void);
static BOOL bStartOpea_PwrOff(void);
static BOOL bStartOpea_FlsCopy(void);
// FlsCopy,�м���Ա����������ϡ�
static BOOL bStartOrExec_FlsCopy(void);

// bIfWorkIngExec_...():
//�ж��� FALSE=taskIdle; else: exec() next step;
// master: flsTask_OpeaOne().U_FLASH_TASK_WAIT == FALSE;
// master: bStartOrExec_common_exeTillFinish.U_FLASH_TASK_WAIT == TRUE;
static BOOL bIfWorkIngExec_FlsWr(void); // Write Ing, flashIdle->next step;
static BOOL bIfWorkIngExec_Erase(void);
static BOOL bIfWorkIngExec_Item(void);
static BOOL bIfWorkIngExec_Hist(void);
static BOOL bIfWorkIngExec_PwrOff(void);
static BOOL bIfWorkIngExec_FlsCopy(void);


// ����ʼʱ��
// bStartOpea_...()��
// U_FLASH_TASK_WAIT == FALSE���� SaveManage_Exec() ����ȣ�
// U_FLASH_TASK_WAIT == TRUE:  һֱ�ȴ���ɣ�
static BOOL bStartOrExec_common_exeTillFinish(
									emSaveOpeaClass mOpeaClass);


#endif  //__saveManage_C__
/*================= ���к�������-lib�ڲ� ====================================*/
//EX_saveManage 
#if U_FLASH_TASK_WAIT == TRUE
//ֱ�ӵȴ�����task���.
// *Master: FlashSaveNew() + U_FLASH_TASK_WAIT=TRUE;
	    // FlsErase_New() + U_FLASH_TASK_WAIT=TRUE;
extern BOOL bWaitForFlsOpeaFinish(U8 mFlsId);
#endif // U_FLASH_TASK_WAIT

/*================= ���к�������-lib�ⲿ-����� ====================================*/
//EX_saveManage 
// ��Ϊflash д�ڼ� ��ֹ������������Ӧ�ò��ȡǰҪ�жϣ�

//��Ҫ����Ŀ�����
//��1part����Ϳ��ԣ�
extern BOOL FlsRdFlsItem_ChipAllow(U8 mFlsItem);
extern BOOL FlsRdFlsItem_PartN_ChipAllow(U8 mFlsItem, U8 mPart);

/*================= ���к�������-lib�ⲿ ====================================*/
//EX_saveManage 

// ���master��lib�����һ����
extern BOOL bSave_CheckReDef(void);

extern void Init_SaveManage(void);

// flash �洢���� exe, ��Ҫmainѭ�����á�
extern void SaveManage_Exec(void);

/******************************************************************************
// END :
******************************************************************************/
#endif // __saveManage_H__

