#ifndef __flashIdAssign_H__
#define __flashIdAssign_H__
/******************************************************************************
* @file    flashIdAssign.h
* @author  yx
* @version V1.1
* @date    2013.9.22
* @brief   
//����ID�ţ�flash�洢 ��Ψһ��id��(�ػ�ʱ�����ʷ��¼����)
// master��Ҫ�ȵõ�һ��flsId, Ȼ���ٵ��� FlsSave_PnConfig()�ȡ�
//��������洢�����������Ĭ�ϵ�flsId: FlsId_DefaultValue();
*
*
* @Version history 
* V1.1, 2013.9.22
*	FlsResultNotificat()�Ľ������U8��ʾ��.0��ʾpart0,.1��ʾpart1.
* V1.0, 2013-07-23
* 
#include  "flashIdAssign.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

/*================= extern ============================================*/
#ifdef  __flashIdAssign_C__
#define EX_flashIdAssign
#else
#define EX_flashIdAssign extern 
#endif
/*================= ���� ============================================*/
//#define 
/*================= �ṹ�嶨�� ======================================*/

/*================= ���нṹ�������� ================================*/

/*================= ˽�к������� ====================================*/
#ifdef  __flashIdAssign_C__

#endif  //__flashIdAssign_C__
/*================= ���к�������-lib�ڲ� ====================================*/
//EX_flashIdAssign 

// �洢���
extern void FlsResultNotificat(U8 taskId, U8 mFlsId, U8 bSucc);

/*================= ���к�������-lib�ⲿ ====================================*/
//EX_flashIdAssign 

//����ID�ţ�flash�洢 ��Ψһ��id��(�ػ�ʱ�����ʷ��¼����)
// master��Ҫ�ȵõ�һ��flsId, Ȼ���ٵ��� FlsSave_PnConfig()�ȡ�
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


/******************************************************************************
// END :
******************************************************************************/
#endif // __flashIdAssign_H__

