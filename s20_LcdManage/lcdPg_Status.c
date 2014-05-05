#define __lcdPg_Status_C__
/******************************************************************************
* @file    lcdPg_Status.c
* @author  yx
* @version V1.0
* @date    2013-07-01
* @brief   
* 
******************************************************************************/
#include  "lcdPg_Status.h"


//#include "incFile.h"	
#include  "phIoKeyScan.h"


/*================= ���� ============================================*/

/*================= �ṹ���� ========================================*/

/*================= ˽�нṹ�������� ================================*/

/*================= ���к������� ====================================*/

/*================= ˽�к������� ====================================*/

/*=================  ================================================*/
		
/******************************************************************************
* FUNC: //
*   IN: emWinBoolState
*  OUT: 
******************************************************************************/
// ����ʾ״̬�� //����subPage // ���Ǿ���menu�����page
void Ini_WinBoolState(void)
{
U8 mState;

	for(mState=0; mState<U_WIN_BOOL_Sta_MAX; mState++)
	{
		vWinBoolState[mState] = 0;
	}
	
	ClrWinBoolState(U_WIN_ShowState_Sta); // ����ʾ״̬��
	ClrWinBoolState(U_WIN_PageSubIng_Sta); //����subPage
	ClrWinBoolState(U_WIN_EntryMenu_Sta); // ���Ǿ���menu�����page
	
	
	ClrPageKey();
	ClrChangeFuncKey();
}

/******************************************************************************
* FUNC: //
// ҳ�汾������ԡ�
// ���Լ��� first()��set, ��back()��clr.
*   IN: emWinBoolState
*  OUT: 
******************************************************************************/


void SetWinBoolState(emWinBoolState mState)
{
	if(mState < U_WIN_BOOL_Sta_MAX)
	{
		vWinBoolState[mState] = TRUE;
	}
}

void ClrWinBoolState(emWinBoolState mState)
{
	if(mState < U_WIN_BOOL_Sta_MAX)
	{
		vWinBoolState[mState] = FALSE;
	}
}

BOOL bWinBoolState(emWinBoolState mState)
{
	
	if(mState < U_WIN_BOOL_Sta_MAX)
	{
		return vWinBoolState[mState];
	}
	else
	{
		return FALSE;
	}
}

/******************************************************************************
* FUNC: 
// ������ҳ���Լ�����İ�����
// �ڶ���key��������Ч����������Ҫҳ���Լ�������set.
// �� LcdPage_function_ ...() ������ clr.
*   IN:
*  OUT: 
******************************************************************************/
static BOOL bPageKeyNew = FALSE;
static U8   vPageKeyVaule = ~0;

void SetPageKey(U8 mKeyValue)
{
	if(bKeyValueValid(mKeyValue))
	{
		bPageKeyNew = TRUE;
		vPageKeyVaule = mKeyValue;
	}
}

void ClrPageKey(void)
{
	bPageKeyNew = FALSE;
	vPageKeyVaule = ~0;
}

BOOL bGetPageKey(U8 *pRtnKey)
{
	if(bPageKeyNew)
	{
		*pRtnKey = vPageKeyVaule;
		return TRUE;
	}
	else
	{
		*pRtnKey = ~0;
		return FALSE;
	}
}

/******************************************************************************
* FUNC: 
// // ������ �ı���;�İ�����
// 		�� �жϰ���ʱ����ͬ�� user ��������
*   IN:
*  OUT: 
******************************************************************************/
static BOOL bChangeFuncKeyNew = FALSE;
static U8   vChangeFuncKeyVaule = ~0;

void SetChangeFuncKey(U8 mKeyValue)
{
	if(bKeyValueValid(mKeyValue))
	{
		bChangeFuncKeyNew = TRUE;
		vChangeFuncKeyVaule = mKeyValue;
	}
}

void ClrChangeFuncKey(void)
{
	bChangeFuncKeyNew = FALSE;
	vChangeFuncKeyVaule = ~0;
}

BOOL bGetChangeFuncKey_andClr(U8 *pRtnKey)
{
	if(bChangeFuncKeyNew)
	{
		*pRtnKey = vChangeFuncKeyVaule;
		bChangeFuncKeyNew = FALSE;
		return TRUE;
	}
	else
	{
		*pRtnKey = ~0;
		return FALSE;
	}
}

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/


/******************************************************************************
* FUNC: // END
*   IN:
*  OUT: 
******************************************************************************/
