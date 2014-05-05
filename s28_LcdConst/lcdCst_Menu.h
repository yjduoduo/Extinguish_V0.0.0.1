#ifndef __lcdCst_Menu_H__
#define __lcdCst_Menu_H__
/******************************************************************************
* @file    lcdCst_Menu.h
* @author  yx
* @version V1.1
* @date    2013-09-13
* @brief   �˵�����
*
* V1.1��2013-09-13
* 		U_MENU_1SCR_SEQU_MAX  ���� U_MENU_SameGrade_ITEM_MAX��
		add: def:��U_OneScreen_Menu_MAX
* V1.0��2012-01-05
* 
#include  "lcdCst_Menu.h"
******************************************************************************/
//#include  "lcdCst_Menu.h"
				   

#include  "prjCompileCon.h"
/*================= extern ============================================*/
#ifdef  __lcdCst_Menu_C__
#define EX_lcdCst_Menu
#else
#define EX_lcdCst_Menu extern 
#endif

/*================= ���� ============================================*/
 enum emMenuNum{
	 U_MENU_NEXT		= 0x0FC,  //Menu.page=���¼��˵�ʱ��ȡֵ��Ҫ����PAGE_MAX
	 U_MENU_TO_PAGE	= 0x0FA,  //Menu.nextItemMenuBuf=���¼��˵�ʱ��ȡֵ��Ҫ����U_MENU_XXth_MAX
	 U_MENU_IdMax	= 0x0F0,  // U_Menu_ID_MAX
	 U_MENU_IdInvalid  = 0x0,
 };


#define U_Menu_Invalid_ID   0xFF
#define U_Menu_SysIni_ID   0x02

//��N���˵���0-N-1. M0 M1 MN-1����Чʱ��ʾ����N-1���˵�ȫ��
#define U_MENU_GRD_MAX  6 

// ͬ���˵������
#define U_MENU_SameGrade_ITEM_MAX  10 
// һ�������ʾ�Ĳ˵����� 


// emUserGrade �û�����
	


/*================= �ṹ�嶨�� ======================================*/

/*================= ���нṹ�������� ================================*/

typedef struct{
	const char *sCn;  //����
	const char *sEn;  //Ӣ��
	const char *sComplex;
}TMenuLanguage_st;


typedef struct TMenu_st //�˵���
{
	TMenuLanguage_st  stLanguage;
	U8  userGrd;          //��Ҫ�û��ȼ��� ͬʱ��������δ����Ĳ˵���δ����ʱ�ֶ�ΪFF��00.
	U8  preItemMenuBuf;   //
	U8  nextItemMenuBuf;  //�����¼��˵�,0~�� 		//û���¼�=U_MENU_TO_PAGE
	
	PAGEWORD page;	      //U_MENU_NEXT��ʾ���¼��˵���//��Ҫ�����ҳ�棻
}TMenu;



/*================= ˽�к������� ====================================*/
#ifdef  __lcdCst_Menu_C__

// *   IN: emMenuId
// *  OUT: TMenu[]����������������ָ�롣
const TMenu *pGetMenuBufFirAndTotal(U8 mMenuId, U8 *m_pRtnTotal);

#endif //  __lcdCst_Menu_C__
/*================= ���к������� ====================================*/
// EX_lcdCst_Menu

extern BOOL GetCstMenu(U8 mMenuId, U8 mSequ, TMenu *pRtnMenu);
extern const TMenu *pGetCstMenu(U8 mMenuId, U8 mSequ);

extern const TMenu *pGetCstBufFirMenu(U8 mMenuId);
extern BOOL GetMenuBufTotal(U8 mMenuId, U8 *m_pRtnTotal);

extern BOOL bValidCstMenu (const TMenu *m_pMenu);
extern BOOL bMenuIdError(U8 mMenuId);

// �˵��ַ���ȡ:
extern char *pGetMenuChar(const TMenu *pOneMenu);


/******************************************************************************
// END :
******************************************************************************/
#endif // __lcdCst_Menu_H__

