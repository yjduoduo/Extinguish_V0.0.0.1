#define __lcdCst_OpeaMenu_C__
/******************************************************************************
* @file    lcdCst_OpeaMenu.c
* @author  yx
* @version V1.1
* @date    2013.9.6
* @brief   �˵�����
* @in      ��Ҫ�ǰ���
* 
* V1.1, 2013.9.6
		�˵���ʾ �� PgMenuItem_SelectSign();
* V1.0, 2013-09-04
*
******************************************************************************/
#include  "lcdCst_OpeaMenu.h"

#include  "lcdCst_OpaMenu_Inc_extern.h"

#include  "lcdCst_Menu.h"
//#include "incFile.h"	


/*================= ���� ============================================*/

/*================= �ṹ���� ========================================*/

typedef struct{
	U8 pathMenuId;
	U8 pathMenuSequ;
}TMenuRow_st;

typedef struct    //
{
	U8 				vMnPathDepth;  //vMnPathBuf[vMnPathDepth]�����ݣ��ǵ�ǰ��ʾ�Ĳ˵�ID�͹�������С�
	TMenuRow_st 	vMnPathBuf[U_MENU_GRD_MAX];  //�˵� Ŀ¼  ���á�
	
	U8 				vTotal;
	const TMenu* 	vMnWinBuf[U_MENU_SameGrade_ITEM_MAX];  //��ǰ����ʾ����
	
	BOOL 			v_bMenuError;
	
}TMenuTask_st;	

// vStMn.vMnPathBuf[vStMn.vMnPathDepth].pathMenuSequ
// Ϊ��ǰ���λ�á�

TMenuTask_st   vStMn;
/*================= ˽�нṹ�������� ================================*/

/*================= ���к������� ====================================*/

/*================= ˽�к������� ====================================*/

// �˵��ַ���ȡ:
// char *pGet_Menu_Char(const TMenu *pOneMenu);
/*=================  ================================================*/
		
/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/


#if U_SYS_Test_Menu == U_Yes 

void testMenu(void)
{
	
	MenuFirstEntry();
	
	MenuReturn();
	MenuReturn();
	
	MenuEnter();
	MenuUp();
	MenuUp();
	MenuDown();
	MenuDown();
	
}

#endif // U_SYS_Test_Menu


/******************************************************************************
* FUNC: // ���winBuf[]. //��ǰ����ʾ����
*   IN:
*  OUT: 
******************************************************************************/
void clrMenuWinBuf(void)
{
	int sequ;
	
	for(sequ=0; sequ<U_MENU_SameGrade_ITEM_MAX; sequ++)
	{
		vStMn.vMnWinBuf[sequ] = pGetCstBufFirMenu(U_Menu_Invalid_ID);
	}
	vStMn.vTotal = 0;
}


/******************************************************************************
* FUNC: // mMenuId�Ĳ˵�->winBuf[].
*   IN:
*  OUT: 
******************************************************************************/


BOOL fillMenuWinBuf(U8 mMenuId)
{
	U8 total;
	U8 sequ;
	
	clrMenuWinBuf();
	
	if(!GetMenuBufTotal(mMenuId, &total))
	{
		vStMn.vTotal = 0;
		return FALSE;
	}
	
	for(sequ=0; sequ<total; sequ++)
	{
		vStMn.vMnWinBuf[sequ] = pGetCstMenu(mMenuId, sequ);
	}
	vStMn.vTotal = total;
	
	return TRUE;
}

/******************************************************************************
* FUNC: // ��� �˵�·�� All��
*   IN:
*  OUT: 
******************************************************************************/

void clrMenuPathBuf(void)
{
	int pathId;
	
	for(pathId=0; pathId<U_MENU_GRD_MAX; pathId++)
	{
		clrMenuOnePathBuf(pathId);
	}
	vStMn.vMnPathDepth = 0;
	vStMn.vMnPathBuf[0].pathMenuId = U_Menu_Invalid_ID;
	vStMn.vMnPathBuf[0].pathMenuSequ = 0x0;
	
}

/******************************************************************************
* FUNC: // ��� �˵�·�� pathId��
******************************************************************************/
void clrMenuOnePathBuf(U8 pathId)
{
	vStMn.vMnPathBuf[pathId].pathMenuId = U_Menu_Invalid_ID;
	vStMn.vMnPathBuf[pathId].pathMenuSequ = 0xFF;
}

/******************************************************************************
* FUNC: // ��ҳ�� �״ν���˵�:
*   IN:
*  OUT: 
* Slave:  SetPgState_InMenu();  PgMenu_SetPageNum();  MenuEnter();
******************************************************************************/

void MenuFirstEntry(void)
{
	ClrMenuAllBufAndSign();
	
	SetPgState_InMenu();
	PgMenu_SetPageNum(); //pageNum = �˵���
	
	vStMn.vMnPathBuf[0].pathMenuId = U_Menu_SysIni_ID;
	vStMn.vMnPathBuf[0].pathMenuSequ = 0;
	
	vStMn.vMnWinBuf[0] = pGetCstMenu(U_Menu_SysIni_ID, 0);
	
	MenuEnter();
	

}

/******************************************************************************
* FUNC: // 
*   IN:
*  OUT: 
******************************************************************************/
//Clr�˵�R �� menu.back() ִ�С�
void ClrMenuAllBufAndSign(void)
{
	clrMenuPathBuf();
	
	clrMenuWinBuf();
	
	ClrPgState_InMenu();
	
	vStMn.vMnWinBuf[0] = pGetCstMenu(U_Menu_SysIni_ID, 0);
}

/******************************************************************************
* FUNC: // �˵��˳�����ҳ��:
*   IN:
*  OUT: 
// slave: PgMenu_Exit();
******************************************************************************/

void MenuEsc(void)
{
	ClrMenuAllBufAndSign();
	PgMenu_Esc_Exit();
}

/******************************************************************************
* FUNC: // ���ص��ϼ��˵�:
*   IN:
*  OUT: 
// ����˵�.return: PgMenu_Exit();
******************************************************************************/

void MenuReturn(void)
{
	U8 preMenuId;
	
	if(vStMn.vMnPathDepth == 0) //U_Menu_SysIni_ID, ��
	{
		ClrMenuAllBufAndSign();
		
		PgMenu_Return_Exit();
		return;
	}
	
	clrMenuOnePathBuf(vStMn.vMnPathDepth);
	vStMn.vMnPathDepth--;
	
	preMenuId = vStMn.vMnWinBuf[0]->preItemMenuBuf;
	if(preMenuId == U_Menu_SysIni_ID)
	{
		ClrMenuAllBufAndSign();
		
		PgMenu_Return_Exit();
		return;
	}
	
	fillMenuWinBuf(preMenuId);
	MenuDisp();
}

/******************************************************************************
* FUNC: // �˵�����������ƶ���ͻ����ʾ���λ��:
*   IN:
*  OUT: 
******************************************************************************/

void MenuUp(void)
{
	U8 *pCursor;
	pCursor = &vStMn.vMnPathBuf[vStMn.vMnPathDepth].pathMenuSequ;
	if(*pCursor == 0)
	{
		*pCursor = vStMn.vTotal-1;
	}
	else
	{
		*pCursor = *pCursor - 1;
	}
	MenuDisp();
}


void MenuDown(void)
{
	U8 *pCursor;
	pCursor = &vStMn.vMnPathBuf[vStMn.vMnPathDepth].pathMenuSequ;
	if(*pCursor == (vStMn.vTotal-1))
	{
		*pCursor = 0;
	}
	else
	{
		*pCursor = *pCursor + 1;
	}
	MenuDisp();
}



/******************************************************************************
* FUNC: // �˵���ֱ��������ȷ��
*   IN:
*  OUT: 
******************************************************************************/

void MenuFigEnter(U8 mMenuSequ)
{
U8 *pCursor;
	if(mMenuSequ >= vStMn.vTotal)
	{
		return;
	}
	
	pCursor = &vStMn.vMnPathBuf[vStMn.vMnPathDepth].pathMenuSequ;
	*pCursor = mMenuSequ;
	
	MenuEnter();
}


/******************************************************************************
* FUNC: // ҳ���˳��� �˵�:
*       // ֱ����ʾwin[]�Ϳ��ԡ�
*   IN:
*  OUT: 
// master: ���ȣ�ҳ���˳�;
******************************************************************************/

void PageRtnToMenu(void)
{
	if(vStMn.vMnPathDepth == 0)
	{
		ClrMenuAllBufAndSign();
		PgMenu_Error();
	}
	else
	{
		PgMenu_SetPageNum(); //pageNum = �˵���
	
		MenuDisp();
	}
	
}

/******************************************************************************
* FUNC: //������ڵ�next���˵�������ʾ�˵��������ҳ�档 //U_SYS_bShowNoFinished
*   IN: 
*  OUT: 
******************************************************************************/
// ��Ҫ�ж� userGrade:
void MenuEnter(void)
{
const TMenu *pOneMenu;

	if(vStMn.vMnPathDepth >= U_MENU_GRD_MAX)
	{
		return;
	}
	pOneMenu = vStMn.vMnWinBuf[vStMn.vMnPathBuf[vStMn.vMnPathDepth].pathMenuSequ];
	if(!bValidCstMenu(pOneMenu))
	{
		vStMn.v_bMenuError = TRUE;
		return;
	}
	
	// ��userGrade�����㣬��callBack  MenuEntr_NextMenuOrPage(); 
	Pssw_MenuNeedPssw(pOneMenu->userGrd);
	
}

/******************************************************************************
* FUNC: //������ڵ�next���˵�������ʾ�˵��������ҳ�档
******************************************************************************/

// userGrade�����㣬ֱ�ӽ���
void MenuEntr_NextMenuOrPage(void)
{	

const TMenu *pOneMenu;

	// �п��ܴ� psswPage����������������һ�¡�
	PgMenu_SetPageNum(); //pageNum = �˵���

	
	if(vStMn.vMnPathDepth >= U_MENU_GRD_MAX)
	{
		return;
	}
	pOneMenu = vStMn.vMnWinBuf[vStMn.vMnPathBuf[vStMn.vMnPathDepth].pathMenuSequ];
	if(!bValidCstMenu(pOneMenu))
	{
		vStMn.v_bMenuError = TRUE;
		return;
	}
	
	
	if(pOneMenu->nextItemMenuBuf < U_MENU_IdMax)
	{
		menuNext();
	}
	else
	{
		menuPageEntry();
	}

}


/******************************************************************************
* FUNC: // menu -> ����ҳ�棺
*   IN:
*  OUT: 
******************************************************************************/
void menuPageEntry(void)
{
	const TMenu *pOneMenu;
	
	pOneMenu = vStMn.vMnWinBuf[vStMn.vMnPathBuf[vStMn.vMnPathDepth].pathMenuSequ];	
	
	if(pOneMenu->nextItemMenuBuf == U_MENU_TO_PAGE)
	{
		PgMenu_toPage(pOneMenu->page);
	}
}


/******************************************************************************
* FUNC: // menu -> ������ڵ�next���˵�������ʾ�˵���
*   IN:
*  OUT: 
******************************************************************************/
void menuNext(void)
{
	const TMenu *pOneMenu;
	
	pOneMenu = vStMn.vMnWinBuf[vStMn.vMnPathBuf[vStMn.vMnPathDepth].pathMenuSequ];
	
	if(pOneMenu->nextItemMenuBuf < U_MENU_IdMax)
	{
		vStMn.vMnPathDepth++;
		vStMn.vMnPathBuf[vStMn.vMnPathDepth].pathMenuId = pOneMenu->nextItemMenuBuf;
		vStMn.vMnPathBuf[vStMn.vMnPathDepth].pathMenuSequ = 0;
		
		fillMenuWinBuf(pOneMenu->nextItemMenuBuf);
		MenuDisp();
	}
}

/******************************************************************************
* FUNC: // �˵����� ��ʾ:
*   IN:
*  OUT: 
******************************************************************************/

void MenuDisp(void)
{
#if U_MENU_SameGrade_ITEM_MAX <= U_OneScreen_Menu_MAX
	Menu_AllItem_Disp();
#else 
	Menu_Part_Disp();
#endif // U_MENU_SameGrade_ITEM_MAX <= U_OneScreen_Menu_MAX
}

/******************************************************************************
* FUNC: // �˵����� ��ʾ:
******************************************************************************/

// һ��������ʾ���в˵� ��ʾ��
void Menu_Part_Disp(void)
{
#if U_MENU_SameGrade_ITEM_MAX <= U_OneScreen_Menu_MAX
#else 

BOOL bNowSelect;
U8 nowCursor;
U8 menuTotal;
U8 menuSequ;
U8 mnSequS;
U8 mMenuRow;
BOOL bMenuIsValid;
	
	nowCursor = vStMn.vMnPathBuf[vStMn.vMnPathDepth].pathMenuSequ;
	menuTotal = vStMn.vTotal;
	
	PgMenu_ClrScreen();
	
	PgMenuShowMode_MenuHead();
	menuSwHead();
	
	if(!cacuMenuStartSequ(nowCursor, menuTotal, &mnSequS))
	{
		return;
	}
	
	mMenuRow = 0;
	for(menuSequ=mnSequS; menuSequ<menuTotal; menuSequ++)
	{
		bNowSelect = menuSwMode(menuSequ, mMenuRow, bNowSelect);
		
		// �˵����� ��ʾһ��:
		if(menu_OneItem_Disp(menuSequ, mMenuRow,
						bNowSelect, &bMenuIsValid))
		{
		}
		
		menu_Part_Dsp_promptHeadEnd(
						mMenuRow, menuSequ, menuTotal);
		
		mMenuRow++;
		if(mMenuRow >= GetMenu1PageItemMax())
		{
			break;
		}
		
	}
	
#endif // U_MENU_SameGrade_ITEM_MAX <= U_OneScreen_Menu_MAX
}


void menu_Part_Dsp_promptHeadEnd(
					U8 mMenuRow, U8 menuSequ, U8 menuTotal)
{
	
		if(mMenuRow == 0)
		{
			if(menuSequ != 0)
			{
				// ��һ����ʾ�Ĳ��������˵���
				PgMenuShowMode_PrePgHaveMenu();
			}
		}
		else if(mMenuRow == (GetMenu1PageItemMax()-1))
		{
			if(menuSequ != (menuTotal-1))
			{
				//   ĩ����ʾ�Ĳ���ĩ���˵���
				PgMenuShowMode_NextPgHaveMenu();
			}
			
		}
}

/******************************************************************************
* FUNC: // ���� �˵���ʼ menuSequ.
******************************************************************************/

BOOL cacuMenuStartSequ(U8 nowCursor, U8 menuTotal, U8 *pRtnSequS)
{
U8 mnSequS;

	if(menuTotal < GetMenu1PageItemMax())
	{
		mnSequS = 0;
	}
	else if(nowCursor < (GetMenu1PageItemMax()-1))
	{
		mnSequS = 0;
	}
	// if: total=10, max=4, ��ô��6,7,8,9 �������һҳ��
	// if: total= 5, max=4, ��ô��1,2,3,4 �������һҳ��
	else if(nowCursor >= (menuTotal - GetMenu1PageItemMax() + 1))
	{
		mnSequS = menuTotal - GetMenu1PageItemMax();
	}
	else 
	{
		mnSequS = nowCursor - 1;
	}
	
	*pRtnSequS = mnSequS;
	return (mnSequS < menuTotal);
}

/******************************************************************************
* FUNC: // �˵����� ��ʾһ��:
******************************************************************************/
BOOL menu_OneItem_Disp(U8 mMenuSequ, U8 mMenuRow,
						BOOL bNowSelect, BOOL *pRtnMenuValid)
{
const TMenu *pOneMenu;
char *pChar;
	
	if(  (mMenuRow >= GetMenu1PageItemMax())
	  || (mMenuSequ >= U_MENU_SameGrade_ITEM_MAX)
	  )
	{
		*pRtnMenuValid = FALSE;
		return FALSE;
	}
	*pRtnMenuValid = TRUE;
	pOneMenu = vStMn.vMnWinBuf[mMenuSequ];
	
	if(bValidCstMenu(pOneMenu))
	{
		PgMenuItem_ClrTextBuf();
		
		// if(bNowSelect)
		{
			PgMenuItem_SelectSign(mMenuRow, bNowSelect);
		}
		
		pChar = pGetMenuChar(pOneMenu);
		PgMenuItem_AddText((U8 *)(pChar));
		
		if(pOneMenu->nextItemMenuBuf < U_MENU_IdMax) //to next menu
		{
			PgMenuItem_AddTxt_HaveNextMenu();
		}
#if U_SYS_Test_Menu == U_Yes 
		if(bNowSelect)
		{
			PgMenuItem_AddTxt_bSelect();
		}
#endif // U_SYS_Test_Menu
		PgMenuItem_show(mMenuRow);

		*pRtnMenuValid = TRUE;
		return TRUE;
	}
	else
	{
		*pRtnMenuValid = FALSE;
		return FALSE;
	}
}



/******************************************************************************
* FUNC: // �˵����� ��ʾ:
******************************************************************************/
// ���в˵� ͬʱ������һ����ʾ��
// һ����ʾͬ�������в˵�
void Menu_AllItem_Disp(void)
{
#if U_MENU_SameGrade_ITEM_MAX <= U_OneScreen_Menu_MAX
U8 sequ;
BOOL bNowSelect;
BOOL bMenuIsValid;
	
	PgMenu_ClrScreen();
	
	PgMenuShowMode_MenuHead();
	menuSwHead();
	
	
	for(sequ=0; sequ<vStMn.vTotal; sequ++)
	{
		bNowSelect = menuSwMode(sequ, sequ,bNowSelect);
		
		// �˵����� ��ʾһ��:
		if(menu_OneItem_Disp(sequ, sequ,
						bNowSelect, &bMenuIsValid))
		{
			continue;
		}
		else
		{
			break;
		}
		
	}
	
#else 
#endif // U_MENU_SameGrade_ITEM_MAX <= U_OneScreen_Menu_MAX
}


/******************************************************************************
* FUNC: // �˵��ַ���ȡ:
*   IN:
*  OUT: 
******************************************************************************/

//�ο� U8 ShowCstChar(U8 row, U8 line, const TCstChar_st *pCstChar)
// char *pGet_Menu_Char(const TMenu *pOneMenu)
// {
	// U8 language;
	// language= GetLanguage();
	// switch(language)
	// {
		// case U_Complex_LANGUAGE:
			// return (char*)(pOneMenu->stLanguage.sComplex);
			
		// case U_English_LANGUAGE:
			// return (char*)(pOneMenu->stLanguage.sEn);
			
		// case U_Chinese_LANGUAGE:
		// default:
			// return (char*)(pOneMenu->stLanguage.sCn);
	// }
// }


/******************************************************************************
* FUNC: // �Ƿ�����Ϊ��ѡ��״̬
���ǵ�ǰ��ѡ��ģʽ���µĲ����������������ģʽ��
*   IN:
*  OUT: 
******************************************************************************/

BOOL menuSwMode(U8 menuSequ, U8 mMenuRow, BOOL bNowSelect) 
{
	BOOL bNeedSelect;
	
	if(menuSequ == vStMn.vMnPathBuf[vStMn.vMnPathDepth].pathMenuSequ){
		bNeedSelect = TRUE;
	}
	else{
		bNeedSelect = FALSE;
	}
	
	//����һ��Ԥ��
	if((mMenuRow == 0) || (bNowSelect != bNeedSelect))
	{
		if(bNeedSelect == TRUE){
			// �˵���ʾģʽ: �Ƿ���������
			PgMenuShowMode_Cursor(mMenuRow, TRUE);
			bNowSelect = TRUE;
		}
		else{
			PgMenuShowMode_Cursor(mMenuRow, FALSE);
			bNowSelect = FALSE;
		}
	}
	return bNowSelect;
}

/******************************************************************************
* FUNC: // ��ʾ �˵�·��
*   IN:
*  OUT: 
******************************************************************************/


void menuSwHead(void) 
{
	const TMenu *pOneMenu;
	U8 depth;
	char *pChar;
	
	PgMenuHead_ClrTextBuf();
	for(depth=0; depth<vStMn.vMnPathDepth; depth++)
	{
		pOneMenu = pGetCstMenu(vStMn.vMnPathBuf[depth].pathMenuId, vStMn.vMnPathBuf[depth].pathMenuSequ);
		if(bValidCstMenu(pOneMenu))
		{
			pChar = pGetMenuChar(pOneMenu);
			if(depth != 0)
			{
				PgMenuHead_AddTxt_Join();
			}
			PgMenuHead_AddText((U8 *)(pChar));
		}
		else
		{
			vStMn.v_bMenuError = TRUE;
			break;
		}
		
	}
	PgMenuHead_show();
}


/******************************************************************************
* FUNC: // 
*   IN:
*  OUT: 
******************************************************************************/



/******************************************************************************
* FUNC: // 
*   IN:
*  OUT: 
******************************************************************************/


/******************************************************************************
* FUNC: // 
*   IN:
*  OUT: 
******************************************************************************/



/******************************************************************************
* FUNC: //
******************************************************************************/



/******************************************************************************
* FUNC: // END
*   IN:
*  OUT: 
******************************************************************************/
