#define __lcdSub_Pssw_C__
/******************************************************************************
* @file    lcdSub_Pssw.c
* @author  yx
* @version V1.0
* @date    2013-08-28
* @brief   ��������menu����ҪȨ��ʱ���жϡ�
		 ��������Ȩ�ޣ���Ҫ���������
		 �������Ȩ�����㣬����ִ���û�Ҫ�����Ĺ��ܡ�
* 
******************************************************************************/
#include  "lcdSub_Pssw.h"

#include  "sysDef.h"

#include  "keyBufJdgLib_incOut.h"
// master: lcdSub_Pssw.c
// UserGradeȷ����ȷ��set key:
// extern void SetKeyValueWhenPsswOk(U8 mKeyValue);

#include  "lcdCst_OpaMenuInterface.h"
#include  "opeaMenuLib_incOut.h"
// userGrade�����㣬ֱ�ӽ���
// extern void MenuEntr_NextMenuOrPage(void);


#include  "lcdTsk_PgNum.h"
#include  "lcdPg_aSchedu.h"



//#include "incFile.h"	


/*================= ���� ============================================*/

/*================= �ṹ���� ========================================*/
typedef struct{
	U8 nowUserGrade;
}TNeedPssw_st;

TNeedPssw_st stNeedPssw;
/*================= ˽�нṹ�������� ================================*/

/*================= ���к������� ====================================*/

/*================= ˽�к������� ====================================*/

/*=================  ================================================*/


/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
void NeedPssw_Init(void)
{
	Clr_UserGrade();
}

/******************************************************************************
* FUNC: // ��ǰ userGrade;
*   IN:
*  OUT: 
******************************************************************************/
void set_UserGrade(U8 userGrade)
{
	stNeedPssw.nowUserGrade = userGrade;
}

void Clr_UserGrade(void)
{
	stNeedPssw.nowUserGrade = U_UserGrd_Min;
}

U8 Get_UserGrade(void)
{
	return stNeedPssw.nowUserGrade;
}

/******************************************************************************
* FUNC: // to��¼����
*   IN:
*  OUT: 
******************************************************************************/

#if U_SYS_bShowNoFinished == 1 
	U_SYS_bShowNoFinished = 1;
#endif // U_SYS_bShowNoFinished

//�����¼���棺 
// ע��menu ��ִ�� back();
void needPssw_toLoginPage(U8 needUserGrade)
{
	if(bPageIsMCycle())
	{
		PageEntry(GetPgNum_UserLogin());
	}
	else if(bPageIsMenu())
	{
		PgMenu_toPage(GetPgNum_UserLogin());
	}
	else
	{
		PgExitToMain_NoFirstFuncExc();
		PageEntry(GetPgNum_UserLogin());
	}
}

// Key����ĵ�¼���˳���¼����:
void needPsswKey_outLoginPage(void)
{
	//PgExitToMain_NoFirstFuncExc();
	
	// �������ⰴ�����ǲ�Ӱ���������ģ�
	// ��ʱ����Ҫ�˳��� ��¼ǰ�Ľ��棬���߸ɴ������ж� EventPage.	
	PageRtnTo_MainOrEvent();
}

// Menu����ĵ�¼���˳���¼����:
void needPsswMenu_outLoginPage(void)
{
	// ��Ϊ�� �˳���menu | ����nextMenu or page,
	// ����ûʲô�������ġ�
}

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/


// ���� ��Ҫ�ж�userGrade
// Master: keyBufJdg.c
void Pssw_KeyNeedPssw(U8 mKeyValue, U8 needUserGrade)
{
	// bUserGradeOk(U8 nowGrade, U8 mNeedGrade);
	if(bUserGradeOk(Get_UserGrade(), needUserGrade))
	{
		// Ϊ��ֹkey��Ч�����ҳ�棬��ǰҳ�����˳�
		PageRtnTo_MainOrEvent();
		// master: lcdSub_Pssw.c
		// UserGradeȷ����ȷ��set key:
		SetKeyValueWhenPsswOk(mKeyValue);
	}
	else
	{
		// Ϊ��ֹkey��Ч�����ҳ�棬��ǰҳ�����˳�
		PageRtnTo_MainOrEvent();
		
		stNeedPsswKey.bNeedPssw = TRUE;
		stNeedPsswKey.keyValue  = mKeyValue;
		stNeedPsswKey.needUserGrade = needUserGrade;
		
		// ��ʾ���û���������
		needPssw_toLoginPage(needUserGrade);
	}
	
}

/******************************************************************************
* FUNC: //
******************************************************************************/
// if Key��ҪuserGrade:
BOOL bNeedPsswKey_nowNeed(void)
{
	return stNeedPsswKey.bNeedPssw;
}


/******************************************************************************
* FUNC: //
******************************************************************************/
// if ��ǰUserGrade �Ƿ����� key Ҫ���grade:
BOOL bNeedPsswKey_meetGrade(U8 mLoginUserGrade)
{
	// BOOL bUserGradeOk(U8 nowGrade, U8 mNeedGrade);
	return (bUserGradeOk(mLoginUserGrade, 
						stNeedPsswKey.needUserGrade));	
}

/******************************************************************************
* FUNC: //
******************************************************************************/
// ������ҪuserGrade�İ���:
// ��Ϊ�漰�� pageEsc, ��Ҫ�� pgPssw_Exit() ������ ���ִ�С�
void NeedPsswKey_result_giveupKey(void)
{
	needPsswKey_outLoginPage();
	
	stNeedPsswKey.bNeedPssw = FALSE;
}

/******************************************************************************
* FUNC: //
******************************************************************************/
// ʹ����ҪuserGrade�İ���:
// ��Ϊ�漰�� pageEsc, ��Ҫ�� pgPssw_Exit() ������ ���ִ�С�
void NeedPsswKey_result_useKey(void)
{
	needPsswKey_outLoginPage();
	
	// UserGradeȷ����ȷ��set key:
	SetKeyValueWhenPsswOk(stNeedPsswKey.keyValue);
	
	stNeedPsswKey.bNeedPssw = FALSE;
}

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
// �˵� ��Ҫ�ж�userGrade
// Master: lcdCst_OpaMenu.c
void Pssw_MenuNeedPssw(U8 needUserGrade)
{
	// bUserGradeOk(U8 nowGrade, U8 mNeedGrade);
	if(bUserGradeOk(Get_UserGrade(), needUserGrade))
	{
		// master: lcdCst_OpaMenu.c
		// userGrade�����㣬ֱ�ӽ���
		MenuEntr_NextMenuOrPage();
	}
	else
	{
		stNeedPsswMenu.bNeedPssw = TRUE;
		stNeedPsswMenu.needUserGrade = needUserGrade;
		
		// ��ʾ���û���������
		needPssw_toLoginPage(needUserGrade);
	}
	
}

/******************************************************************************
* FUNC: //
******************************************************************************/

// if Menu��ҪuserGrade:
BOOL bNeedPsswMenu_nowNeed(void)
{
	return stNeedPsswMenu.bNeedPssw;
}



/******************************************************************************
* FUNC: //
******************************************************************************/

// if ��ǰUserGrade �Ƿ����� menu Ҫ���grade:
BOOL bNeedPsswMenu_meetGrade(U8 mLoginUserGrade)
{
	// BOOL bUserGradeOk(U8 nowGrade, U8 mNeedGrade);
	return (bUserGradeOk(mLoginUserGrade, 
						stNeedPsswMenu.needUserGrade));	
}



/******************************************************************************
* FUNC: //
******************************************************************************/

// ������ҪuserGrade�� menu :
// ��Ϊ�漰�� pageEsc, ��Ҫ�� pgPssw_Exit() ������ ���ִ�С�
void NeedPsswMenu_result_giveupNextMenu(void)
{
	needPsswMenu_outLoginPage();
	
	// ҳ���˳��� �˵�:
	PageRtnToMenu();
	
	stNeedPsswMenu.bNeedPssw = FALSE;
}



/******************************************************************************
* FUNC: //
******************************************************************************/


// ������ҪuserGrade��menu:
// ��Ϊ�漰�� pageEsc, ��Ҫ�� pgPssw_Exit() ������ ���ִ�С�
void NeedPsswMenu_result_entryMenuNext(void)
{
	needPsswMenu_outLoginPage();
	
	// master: lcdCst_OpaMenu.c
	// userGrade�����㣬ֱ�ӽ���
	MenuEntr_NextMenuOrPage();
	
	stNeedPsswMenu.bNeedPssw = FALSE;
}



/******************************************************************************
* FUNC: // END
*   IN:
*  OUT: 
******************************************************************************/
