#define __lcdCst_OpaMenuInterface_C__
/******************************************************************************
* @file    lcdCst_OpaMenuInterface.c
* @author  yx
* @version V1.1
* @date    2013.9.6
* @brief   OpeaMenuLib�Ľӿڡ�
* 
******************************************************************************/
#include  "lcdCst_OpaMenuInterface.h"

#include  "lcdPg_Status.h"

//#include "incFile.h"	

#include  "lcdSub_ModeTextFig.h"
// extern 
// extern void IniTextBuf(emShowUseLib_PIX  mUseLib);
// extern void AddToTextBuf(U8 *pChar);

#include  "lcdTsk_PgNum.h"
#include  "lcdPg_aSchedu.h"

/*================= ���� ============================================*/

/******************************************************************************
�ɲ˵�����ҳ��ʱ�� ���ܵ��� menu.back(), ��Ҫ������ǰ�˵��Ĳ�Ρ�
	-> PgMenu_toPage();
�������U_WIN_PageSubIng_Sta���͵�ҳ�棬
	�˳�ʱ���� bWinBoolState(U_WIN_EntryMenu_Sta)
	���ǣ��˳����˵������򣬵� MCycle;
******************************************************************************/
/*=================  ================================================*/

//
/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
// Master:  menuOpea lib ;
void SetPgState_InMenu(void)
{
	SetWinBoolState(U_WIN_EntryMenu_Sta);
}

// �� PgMenu_Exit()ǰ�ã���־���˳��˵�״̬��
void ClrPgState_InMenu(void)
{
	ClrWinBoolState(U_WIN_EntryMenu_Sta);
}

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

// �˵��˳��� MCycle(�¼���״̬)ҳ�档
// menu.return, menu.esc;
// if ��Ҫ�ж���ʾҳ�棬�� Schedu.c ������ô����
// Master: MenuReturn(): ����˵�.return
// Master: MenuEsc(): use.

void PgMenu_Return_Exit(void)
{
	PageMainOrEventFirst();
	
}
void PgMenu_Esc_Exit(void)
{
	PageMainOrEventFirst();
}

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
// �˵� �����Իָ����˳���
void PgMenu_Error(void)
{
	PageRtnTo_MainOrEvent();
}

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

// �˵�����page:
// ע�ⲻ�� menu.back()����Ҫ������ǰ�˵��Ĳ�Ρ�
void PgMenu_toPage(PAGEWORD mPage)
{
	// clr screen, newPage first();
	PageEntry(mPage);
}

/******************************************************************************
* FUNC: //
******************************************************************************/
void PgMenu_SetPageNum(void) //pageNum = �˵���
{
	SetPageNum(GetPgNum_Menu());
}


/******************************************************************************
* FUNC: //
******************************************************************************/
// �˵�ҳ�� ����:
void PgMenu_ClrScreen(void)
{
	ClrWindow_Menu();
}


/******************************************************************************
* FUNC: // 
*   IN:
*  OUT: 
******************************************************************************/

// �˵���ʾһ�У�clr all:
void PgMenuItem_ClrTextBuf(void)
{
	IniTextBuf(U_ShowUseLib_88orCn_CN);
}

// �˵���ѡ�б�־:
// �� PgMenuItem_ClrTextBuf()��add �˵��ַ�ǰ�� ���á�
// Ҳ�������ɼ�¼bSelect״̬����PgMenuItem_show()ʱ��ӱ�־�������С�
void PgMenuItem_SelectSign(U8 mMenuRow, BOOL bSelect)
{
	if(bSelect)
	{
		AddCodeStrToTextBuf(">>");
	}
	else
	{
		AddCodeStrToTextBuf("  ");
	}
}

// �˵���ʾһ�У�add char:
void PgMenuItem_AddText(U8 *pChar)
{
	AddToTextBuf(pChar);
}

// �˵���ʾһ�У�add char, ��ʾ���¼��˵�:
void PgMenuItem_AddTxt_HaveNextMenu(void)
{
	AddToTextBuf("->");
}

// �˵���ʾһ�У�add char, ��ʾ ��ǰ�б�ѡ��:
void PgMenuItem_AddTxt_bSelect(void)
{
	AddToTextBuf(". Select");
}

// ��ʾһ���˵��ַ�:
void PgMenuItem_show(U8 mMenuRow)
{
	ShowTextBuf(mMenuRow*2+1, 1);  // (mRow, mLine)
}

/******************************************************************************
* FUNC: // 
* ��ǰ menuHead ����ʾ��
******************************************************************************/

// �˵�head��ʾһ�У�clr all:
void PgMenuHead_ClrTextBuf(void)
{
	IniTextBuf(U_ShowUseLib_88orCn_CN);
}

// �˵�head��ʾһ�У�add char, ��ʾ ���ӷ�:
void PgMenuHead_AddTxt_Join(void)
{
	// AddToTextBuf("-");
}

// �˵���ʾһ�У�add char:
void PgMenuHead_AddText(U8 *pChar)
{
	// AddToTextBuf(pChar);
}


// ��ʾ�˵�Head�ַ�:
void PgMenuHead_show(void)
{
	// ShowTextBuf(0, 0);  // (mRow, mLine)
}


/******************************************************************************
* FUNC: // 
******************************************************************************/


// �˵���ʾģʽ: �Ƿ��������С� ����ʾһ�в˵�ǰ���á�
// �������óɷ�ѡģʽ��
void PgMenuShowMode_Cursor(U8 mMenuRow, U8 bCursorAt)
{
	
}


// �˵���ʾģʽ: menuHead
void PgMenuShowMode_MenuHead(void)
{
	
}

// ��һ����ʾ�Ĳ��������˵���
void PgMenuShowMode_PrePgHaveMenu(void)
{
	ShowCodeCharRL(0, U_LCD_LINE_MAX-5, 
							"..<<", FALSE);
}
//   ĩ����ʾ�Ĳ���ĩ���˵���
void PgMenuShowMode_NextPgHaveMenu(void)
{
	ShowCodeCharRL((U_LCD_ROW_MAX-2), U_LCD_LINE_MAX-5, 
							">>..", FALSE);
	
}
U8 GetMenu1PageItemMax(void)
{
	return U_OneScreen_Menu_MAX;
}


/******************************************************************************
* FUNC: // END
*   IN:
*  OUT: 
******************************************************************************/
