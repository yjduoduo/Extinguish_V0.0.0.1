#ifndef __lcdShowTask_H__
#define __lcdShowTask_H__
/******************************************************************************
* @file    lcdShowTask.h
* @author  yx
* @version V1.0
* @date    2013-07-01
* @brief   
* 
#include  "lcdShowTask.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

/*================= extern ============================================*/
#ifdef  __lcdShowTask_C__
#define EX_lcdShowTask
#else
#define EX_lcdShowTask extern 
#endif
/*================= ���� ============================================*/
//#define 
/*================= �ṹ�嶨�� ======================================*/

/*================= ���нṹ�������� ================================*/
/*
typedef struct{
	U8 sequStart;
}TStruct_st;
TStruct_st stStruct;
*/

/*-----------------    ----------------------------------*/

/*================= ˽�к������� ====================================*/
#ifdef  __lcdShowTask_C__

// �жϰ����� emKey 
// ��slave����  OUT: TRUE=�Ѵ���
void lcdTask_JdgKey(void);

//OUT: TRUE=�Ѵ���
BOOL lcdTask_keyCheckIng(U8 mKey); // �������
BOOL lcdTask_keyReset(U8 mKey);
BOOL lcdTask_keySilence(U8 mKey);
BOOL lcdTask_keyReturn(U8 mKey); 
BOOL lcdTask_keyEsc(U8 mKey);
BOOL lcdTask_keyEnter(U8 mKey);
BOOL lcdTask_keyInputFig(U8 mKey); // ���ֺͷ����



#endif  //__lcdShowTask_C__
/*================= ���к������� ====================================*/
//EX_lcdShowTask 

extern void Init_LcdTask(void);
extern void Exec_LcdTask(void);

/******************************************************************************
// END :
******************************************************************************/
#endif // __lcdShowTask_H__

