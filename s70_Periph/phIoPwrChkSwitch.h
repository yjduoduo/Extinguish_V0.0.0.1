#ifndef __phIoPwrChkSwitch_H__
#define __phIoPwrChkSwitch_H__
/******************************************************************************
* @file    phIoPwrChkSwitch.h
* @author  yx
* @version V1.0
* @date    2013-08-22
* @brief   ��Դ���޿���
* 
#include  "phIoPwrChkSwitch.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

/*================= extern ============================================*/
#ifdef  __phIoPwrChkSwitch_C__
#define EX_phIoPwrChkSwitch
#else
#define EX_phIoPwrChkSwitch extern 
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
#ifdef  __phIoPwrChkSwitch_C__

#endif  //__phIoPwrChkSwitch_C__
/*================= ���к������� ====================================*/
//EX_phIoPwrChkSwitch 

extern void InitPwrChkSwcTask(void);
extern void ExecPwrChkSwcTask(void);

/******************************************************************************
// END :
******************************************************************************/
#endif // __phIoPwrChkSwitch_H__

