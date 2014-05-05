#ifndef __keyBufJdgLib_incOut_H__
#define __keyBufJdgLib_incOut_H__
/******************************************************************************
* @file    keyBufJdgLib_incOut.h
* @author  yx
* @version V1.5
* @date    2013-09-29
* @brief   ����ɨ�����жϡ�
		ֻ�ܴ��� 32�����ڵİ�������Ϊ��ȡ1���ڵ�ɨ��������U32.
*
* V1.5, 2013-09-29  ��KeyBuf_Driver_V0.0.0.1_0.0.5��
*		��keyBufJdgLib_Inc_Extern�������޸İ��º͵ȴ���ʱ�䡣emKeyDownTmr
* V1.3, ������Ĵ��� 
		��������clr.
		2013-08-28
* V1.1, �а���δ����ʱ���������µİ����� 
		�� ClrKeyValue();
		2013-08-27,yx
* V1.0, 2013-07-01
* 
#include  "keyBufJdgLib_incOut.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

/*================= ���� ============================================*/

/*================= ���к������� ====================================*/
//EX_keyBufJdgLib 

extern void InitKeyJudgeTask(void);


// ����keyɨ������
// ɨ������ * bufMax �ڱ���ִ��һ�Ρ�
// ���յ�ɨ�����ݣ�bit=1��ʾ�а�����
extern void Task_ExecKeyTask(void);

// ��ǰ����Ч�İ��������£�
extern BOOL bHaveKeyValidDown(void);

// ��ȡ��Ч������
// OUT:��emKey, �û����ּ����ܼ��Ķ��塣
extern BOOL GetKeyValue(U8 *pGetKey);

// * Ӧ�ó��򣬵�new pageʱ���˳��á�
extern void ClrKeyValue(void);

// master: lcdSub_Pssw.c
// UserGradeȷ����ȷ��set key:
extern void SetKeyValueWhenPsswOk(U8 mKeyValue);


// master: phIoKeyScan.c
//��������ʱ�䡣��ʱ���Զ�clr key.
// ���ú���Ҫ��ʱ���Զ�ֹͣ��
extern void TmrArrived_KeySave(void);


/******************************************************************************
// END :
******************************************************************************/
#endif // __keyBufJdgLib_incOut_H__

