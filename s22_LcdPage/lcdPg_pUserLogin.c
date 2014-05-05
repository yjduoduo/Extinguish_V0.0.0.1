#define __lcdPg_pUserLogin_C__
/******************************************************************************
* @file    lcdPg_pUserLogin.c
* @author  yx
* @version V1.0
* @date    2013-09-05
* @brief   page: �û���¼���� ��������
* 
******************************************************************************/
#include  "lcdPg_pUserLogin.h"


#include  "lcdSub_Pssw.h" 
//#include "incFile.h"	


/*================= ���� ============================================*/

/*================= �ṹ���� ========================================*/

/*================= ˽�нṹ�������� ================================*/

/*================= ���к������� ====================================*/

/*================= ˽�к������� ====================================*/

/*=================  ================================================*/
		

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/


// �û���¼ �˳���
void pgUserLogin_userExit(void)
{
	if(bNeedPsswKey_nowNeed())
	{
		NeedPsswKey_result_giveupKey();
	}
	else if(bNeedPsswMenu_nowNeed()) // if Menu��ҪuserGrade:
	{
		NeedPsswMenu_result_giveupNextMenu();
	}
	
}


/******************************************************************************
* FUNC: //
******************************************************************************/

// �û���¼ �� ��Ч��userGrade:
// ��Ϊ�漰�� pageEsc, ��Ҫ�� pgPssw_Exit() ������ ���ִ�С�
void pgUserLogin_Result(U8 mLoginUserGrade)
{
	if(bNeedPsswKey_nowNeed())
	{
		if(bNeedPsswKey_meetGrade(mLoginUserGrade))
		{
			NeedPsswKey_result_useKey();
		}
		else
		{
			NeedPsswKey_result_giveupKey();
		}
	}
	else if(bNeedPsswMenu_nowNeed()) // if Menu��ҪuserGrade:
	{
		if(bNeedPsswMenu_meetGrade(mLoginUserGrade))
		{
			NeedPsswMenu_result_entryMenuNext();
		}
		else
		{
			NeedPsswMenu_result_giveupNextMenu();
		}
		
	}
	
}

/******************************************************************************
* FUNC: // END
*   IN:
*  OUT: 
******************************************************************************/
