/*****************************************************************************
*author:κ�½�
*time  :2013�� 9.22~10��22��
*****************************************************************************/
#ifndef LCDPG_INITT_H
#define LCDPG_INITT_H
#define __KeyCall_Pg
#define __KeyCall_Pg_EX
#include "lcdPg_KeyCall.h"


#ifdef __KeyCall_INITT_EX
#define KEYCALL_INITT_EX extern
#else
#define KEYCALL_INITT_EX
#endif




extern key_callbackfun *pgCall;
/*****************************************************************************
*FUNC:����ҳ���ʼ����������lcdPg_Page.c��ֱ�ӵ���
*****************************************************************************/

KEYCALL_INITT_EX void p010_initpgentry(void);//�ֶ���ͣ�豸
KEYCALL_INITT_EX void p011_initpgentry(void);// ����
KEYCALL_INITT_EX void p013_initpgentry(void);//ʱ������
KEYCALL_INITT_EX void p016_initpgentry(void);//�Զ��Ǽ�
KEYCALL_INITT_EX void p017_initpgentry(void);//�ֶ��Ǽ�
KEYCALL_INITT_EX void p018_initpgentry(void);//�ֶ�����
KEYCALL_INITT_EX void p060_initpgentry(void);//��·���

KEYCALL_INITT_EX void p030_initpgentry(void);//���������
KEYCALL_INITT_EX void p037_initpgentry(void);//����ѡ��
KEYCALL_INITT_EX void p038_initpgentry(void);//����ģʽ
KEYCALL_INITT_EX void p041_initpgentry(void);//������Ϣ
KEYCALL_INITT_EX void p040_initpgentry(void);//������Ϣ
KEYCALL_INITT_EX void p044_initpgentry(void);//��ѯ����ע��
KEYCALL_INITT_EX void p039_initpgentry(void);//��ѯ����ģʽ
KEYCALL_INITT_EX void p058_initpgentry(void);//��ѯ���ߵǼǵ�ַ
KEYCALL_INITT_EX void p042_initpgentry(void);
KEYCALL_INITT_EX void p047_initpgentry(void);
KEYCALL_INITT_EX void p048_initpgentry(void);
KEYCALL_INITT_EX void p049_initpgentry(void);
KEYCALL_INITT_EX void p024_initpgentry(void);
KEYCALL_INITT_EX void p027_initpgentry(void);
KEYCALL_INITT_EX void p015_initpgentry(void);
KEYCALL_INITT_EX void p019_initpgentry(void);
KEYCALL_INITT_EX void p020_initpgentry(void);
KEYCALL_INITT_EX void p028_initpgentry(void);
KEYCALL_INITT_EX void p080_initpgentry(void);
KEYCALL_INITT_EX void p077_initpgentry(void);
KEYCALL_INITT_EX void p078_initpgentry(void);
KEYCALL_INITT_EX void p081_initpgentry(void);
KEYCALL_INITT_EX void p083_initpgentry(void);
KEYCALL_INITT_EX void p084_initpgentry(void);
KEYCALL_INITT_EX void p061_initpgentry(void);// ��ʾ ģ��������
KEYCALL_INITT_EX void p062_initpgentry(void);
KEYCALL_INITT_EX void p063_initpgentry(void);
KEYCALL_INITT_EX void p064_initpgentry(void);
KEYCALL_INITT_EX void p065_initpgentry(void);
KEYCALL_INITT_EX void p067_initpgentry(void);
KEYCALL_INITT_EX void p072_initpgentry(void);
KEYCALL_INITT_EX void p073_initpgentry(void);
KEYCALL_INITT_EX void p059_initpgentry(void);
KEYCALL_INITT_EX void p052_initpgentry(void);
KEYCALL_INITT_EX void p053_initpgentry(void);
KEYCALL_INITT_EX void p054_initpgentry(void);
KEYCALL_INITT_EX void p055_initpgentry(void);
KEYCALL_INITT_EX void p056_initpgentry(void);
KEYCALL_INITT_EX void p057_initpgentry(void);
#endif // LCDPG_INITT_H
