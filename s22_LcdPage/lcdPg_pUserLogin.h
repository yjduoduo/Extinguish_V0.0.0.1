#ifndef __lcdPg_pUserLogin_H__
#define __lcdPg_pUserLogin_H__
/******************************************************************************
* @file    lcdPg_pUserLogin.h
* @author  yx
* @version V1.0
* @date    2013-09-05
* @brief   page: �û���¼���� ��������
* @slave   lcdSub_Pssw.c
* 
#include  "lcdPg_pUserLogin.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

/*================= extern ============================================*/
#ifdef  __lcdPg_pUserLogin_C__
#define EX_lcdPg_pUserLogin
#else
#define EX_lcdPg_pUserLogin extern 
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
#ifdef  __lcdPg_pUserLogin_C__


// �û���¼ �� ��Ч��userGrade:
// ��Ϊ�漰�� pageEsc, ��Ҫ�� pgPssw_Exit() ������ ���ִ�С�
void pgUserLogin_Result(U8 mLoginUserGrade);



#endif  //__lcdPg_pUserLogin_C__
/*================= ���к������� ====================================*/
//EX_lcdPg_pUserLogin 

// �û���¼ �˳���
extern void pgUserLogin_userExit(void);

/******************************************************************************
// END :
******************************************************************************/
#endif // __lcdPg_pUserLogin_H__

