#ifndef __lcdSub_Pssw_H__
#define __lcdSub_Pssw_H__
/******************************************************************************
* @file    lcdSub_Pssw.h
* @author  yx
* @version V1.0
* @date    2013-08-28
* @brief   ��������menu����ҪȨ��ʱ���жϡ�
		 ��������Ȩ�ޣ���Ҫ���������
		 �������Ȩ�����㣬����ִ���û�Ҫ�����Ĺ��ܡ�
* @master  ������lcdSub_Pssw.c; opeaMenu;
* @master  ����lcdPg_pUserLogin.c;
* 
#include  "lcdSub_Pssw.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

/*================= extern ============================================*/
#ifdef  __lcdSub_Pssw_C__
#define EX_lcdSub_Pssw
#else
#define EX_lcdSub_Pssw extern 
#endif
/*================= ���� ============================================*/
//#define 
/*================= �ṹ�嶨�� ======================================*/

typedef struct{
	BOOL bNeedPssw;
	U8   keyValue;
	U8	 needUserGrade;
}TNeedPsswKey_st;

typedef struct{
	BOOL bNeedPssw;
	U8	 needUserGrade;
}TNeedPsswMenu_st;

/*================= ���нṹ�������� ================================*/

/*================= ˽�к������� ====================================*/
#ifdef  __lcdSub_Pssw_C__

TNeedPsswKey_st   stNeedPsswKey;
TNeedPsswMenu_st  stNeedPsswMenu;


void set_UserGrade(U8 userGrade);

//�����¼���棺 
void needPssw_toLoginPage(U8 needUserGrade); 
// Key����ĵ�¼���˳���¼����:
void needPsswKey_outLoginPage(void);
// Menu����ĵ�¼���˳���¼����:
void needPsswMenu_outLoginPage(void);

#endif  //__lcdSub_Pssw_C__
/*================= ���к�������-extern  ====================================*/
//EX_lcdCst_OpeaMenu 


/*================= ���к������� ====================================*/
//EX_lcdSub_Pssw 


extern void NeedPssw_Init(void);

extern void Clr_UserGrade(void);
extern U8 Get_UserGrade(void);

/*-----------------    ----------------------------------*/
// ���� ��Ҫ�ж�userGrade
// Master: keyBufJdg.c
extern void Pssw_KeyNeedPssw(U8 mKeyValue, U8 needUserGrade);

// if Key��ҪuserGrade:
extern BOOL bNeedPsswKey_nowNeed(void);

// if ��ǰUserGrade �Ƿ����� key Ҫ���grade:
extern BOOL bNeedPsswKey_meetGrade(U8 mLoginUserGrade);

// ʹ����ҪuserGrade�İ���:
// ��Ϊ�漰�� pageEsc, ��Ҫ�� pgPssw_Exit() ������ ���ִ�С�
extern void NeedPsswKey_result_useKey(void);

// ������ҪuserGrade�İ���:
// ��Ϊ�漰�� pageEsc, ��Ҫ�� pgPssw_Exit() ������ ���ִ�С�
extern void NeedPsswKey_result_giveupKey(void);

/*-----------------    ----------------------------------*/
// �˵� ��Ҫ�ж�userGrade
// Master: lcdCst_OpaMenu.c
extern void Pssw_MenuNeedPssw(U8 needUserGrade);

// if Menu��ҪuserGrade:
extern BOOL bNeedPsswMenu_nowNeed(void);

// if ��ǰUserGrade �Ƿ����� menu Ҫ���grade:
extern BOOL bNeedPsswMenu_meetGrade(U8 mLoginUserGrade);

// ������ҪuserGrade�� menu :
// ��Ϊ�漰�� pageEsc, ��Ҫ�� pgPssw_Exit() ������ ���ִ�С�
extern void NeedPsswMenu_result_giveupNextMenu(void);

// ������ҪuserGrade��menu:
// ��Ϊ�漰�� pageEsc, ��Ҫ�� pgPssw_Exit() ������ ���ִ�С�
extern void NeedPsswMenu_result_entryMenuNext(void);


/******************************************************************************
// END :
******************************************************************************/
#endif // __lcdSub_Pssw_H__

