#ifndef __Save_Manage_incOut_H__
#define __Save_Manage_incOut_H__
/******************************************************************************
* @file    Save_Manage_incOut.h
* @author  yx
* @version V1.4
* @date    2013.9.22
* @brief   
	   
* @Version history 
* V1.4, 2013.9.22  ��DriverFlsSave_V0.0.0.1_0.1.5��
*	FlsResultNotificat()�Ľ������U8��ʾ��.0��ʾpart0,.1��ʾpart1.
* V1.3, 2013-09-4
* V1.0, 2013-07-23
* 
#include  "Save_Manage_incOut.h"
******************************************************************************/
//
#include  "prjCompileCon.h"
#include  "strDevice.h"
#include  "strEvtTrans.h"

/******************************************************************************
//����ID�ţ�flash�洢 ��Ψһ��id��(�ػ�ʱ�����ʷ��¼����)
//��������洢�����������Ĭ�ϵ�flsId: FlsId_DefaultValue();

// ʹ��ʾ����
void store(void) // ���棺
{
static U8 mFlsId;
U8 bSucc;
	if(FlsIdNewAssign(taskId, &mFlsId))
	{
		//�洢(���ݣ� taskId, mFlsId);  //FlsSave_PnConfig(taskId); ��
	}
}

void saveResult(void) // ��ȡ��������
{
	if(bIsFinish_FlsExe(mFlsId, &bSucc))  //�鿴�����
	{
		//���ݴ洢�������
		// ������䣺FlsIdClrAssign();
	}
}


void read(void)  //��ȡ
{
	if(FlsRdFlsItem_ChipAllow(mFlsItem))
	{
		// ��
	}
}


* FUNC: //lib �÷���
// *****************************************************************************   *  /
1. �洢��
	�õ�flsId: FlsIdNewAssign(U8 taskId, U8 *pRtnFlsId);
	FlsSave_PnConfig(taskId); ��
	�鿴�����bIsFinish_FlsExe();
	������䣺FlsIdClrAssign();
	
2. ����
	�ж� FlsRdFlsItem_ChipAllow();

3. ����
	��ʱ100ms, ���� FlsIdAssign_TmrAdd(); ����ʱ�������flsId.
	��ʷ��¼�洢����ʱ��|��¼��buf������buf��Ķ�д�롣

******************************************************************************/


/*================= ���к�������-lib�ⲿ ====================================*/
//EX_flashIdAssign 

//����ID�ţ�flash�洢 ��Ψһ��id��(�ػ�ʱ�����ʷ��¼����)
//��������洢�����������Ĭ�ϵ�flsId: FlsId_DefaultValue();

// ����洢����Ψһid, Clr:
extern void FlsIdAssign_Init(void);

extern BOOL bFlsId_Valid(U8 mFlsId);

//��ʱ�жϽ����ʱ����Ҫmaster��ʱ100msִ��:
// ����ʱ����������
extern void FlsIdAssign_TmrAdd(void);

//Ĭ��ֵ���������Ľ����taskʹ�á�
extern U8 FlsId_DefaultValue(void);


// �·�������ţ���master�жϴ洢����á�
// master��Ҫ�ȵõ�һ��flsId, Ȼ���ٵ��� FlsSave_PnConfig()�ȡ�
extern BOOL FlsIdNewAssign(U8 taskId, U8 *pRtnFlsId);

extern void FlsIdClrAssign(U8 mFlsId);

//�������taskId�������flsId.
extern void FlsIdClr_FromTaskId(U8 mTaskId);

//�����ȡ��
// *  OUT: BOOL=�Ƿ������ϣ�
// *pRtnSucc = �����ȽϵĽ�� // .0=1=part0 Succ; .1=1=part1 Succ
extern BOOL bIsFinish_FlsExe(U8 flsId, U8 *pRtnSucc);

extern BOOL bFlsId_AllFinish_FromTaskId(U8 mTaskId);
extern BOOL bFlsId_AllSucc_FromTaskId(U8 mTaskId);



/*================= ���к�������-lib�ⲿ ====================================*/
//EX_flsCopyTask 
//���������ֹ��
//δ��ɡ�׼��������onePart  cover another.
extern void SetAllow_FlsCopy_CheckItemError(void);
extern void SetForbid_FlsCopy_CheckItemError(void);
extern BOOL bFlsCopy_Allow_CheckItemError(void);

/*================= ���к�������-lib�ⲿ ====================================*/
//EX_flsItemState 

// TRUE=�����, (!Error + !Erase + !Renew)
// extern BOOL bFlsItem_IsReadAllow(U8 mFlsItem, U8 mPart);

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
#endif // __Save_Manage_incOut_H__

