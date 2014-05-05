#ifndef __lcdCst_OpeaMenu_H__
#define __lcdCst_OpeaMenu_H__
/******************************************************************************
* @file    lcdCst_OpeaMenu.h
* @author  yx
* @version V1.6
* @date    2013.10.08 11:50
* @brief   �˵�����
* @in      ��Ҫ�ǰ���
* @  U_SIGN_bHaveTested ; 2013.9.29 10:35
*
* V1.6  2013.10.08 11:50
*		add: MenuFigEnter(); // �˵���ֱ��������ȷ��
* V1.5  2013.9.29 10:35 
		add: �˵�δ��ʾhead��endʱ�����ַ���ʾ��
* V1.4, 2013.9.17 16:17 
		addע�ͣ�������slave
* V1.3, 2013.9.13 09:28
		add: һ��������ʾ���в˵������ MenuDisp();  -> Menu_Part_Disp();
* V1.2, 2013.9.11
* 		add: ClrMenuAllBufAndSign();
* V1.1, 2013.9.6
		�˵���ʾ �� PgMenuItem_SelectSign();
* V1.0, 2013-09-04
* 
#include  "lcdCst_OpeaMenu.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

/*================= extern ============================================*/
#ifdef  __lcdCst_OpeaMenu_C__
#define EX_lcdCst_OpeaMenu
#else
#define EX_lcdCst_OpeaMenu extern 
#endif
/*================= ���� ============================================*/
//#define 
/*================= �ṹ�嶨�� ======================================*/

/*================= ���нṹ�������� ================================*/

/*================= ˽�к������� ====================================*/
#ifdef  __lcdCst_OpeaMenu_C__

// * FUNC: �˵� showBuf[]��
// *   IN:
// *  OUT: 

// ���winBuf[].//��ǰ����ʾ����
void clrMenuWinBuf(void);
// mMenuId�Ĳ˵�->winBuf[].
BOOL fillMenuWinBuf(U8 mMenuId);

// ��� �˵�·�� pathId��
void clrMenuOnePathBuf(U8 pathId);
// ��� �˵�·�� All��
void clrMenuPathBuf(void);





// * FUNC: �˵� next��
// *   IN:
// *  OUT: 

// menu -> ����ҳ�棺
void menuPageEntry(void);
// menu -> ������ڵ�next���˵�������ʾ�˵���
void menuNext(void);



// * FUNC: �˵���ʾ��
// *   IN:
// *  OUT: 

// �Ƿ�����Ϊ��ѡ��״̬
// ���ǵ�ǰ��ѡ��ģʽ���µĲ����������������ģʽ��
BOOL menuSwMode(U8 menuSequ, U8 mMenuRow, BOOL bNowSelect);

// �˵����� ��ʾһ��:
BOOL menu_OneItem_Disp(U8 mMenuSequ, U8 mMenuRow,
						BOOL bNowSelect, BOOL *pRtnMenuValid);
// * FUNC: // ���� �˵���ʼ menuSequ.
BOOL cacuMenuStartSequ(U8 nowCursor, U8 menuTotal, 
										U8 *pRtnSequS);



// ��ʾ �˵�·��
void menuSwHead(void);

// �˵����� ��ʾ:
void MenuDisp(void);
	// һ����ʾͬ�������в˵�
	void Menu_AllItem_Disp(void); 
	// һ��������ʾ���в˵� ��ʾ��
	void Menu_Part_Disp(void);
void menu_Part_Dsp_promptHeadEnd(
					U8 mMenuRow, U8 menuSequ, U8 menuTotal);

#endif  //__lcdCst_OpeaMenu_C__
/*================= ���к������� ====================================*/
//EX_lcdCst_OpeaMenu 

#if U_SYS_Test_Menu == U_Yes 
extern void testMenu(void);
#endif // U_SYS_Test_Menu
/*================= ���к������� ====================================*/
//EX_lcdCst_OpeaMenu 

// ��ҳ�� �״ν���˵�:
// * Slave:  SetPgState_InMenu();  PgMenu_SetPageNum();  MenuEnter();
extern void MenuFirstEntry(void);

//������ڵ�next���˵�������ʾ�˵��������ҳ�档 //U_SYS_bShowNoFinished
// * Slave:  Pssw_MenuNeedPssw();  ��Ҫ�ж� userGrade:
extern void MenuEnter(void);

// userGrade�����㣬ֱ�ӽ���
// * Slave:  PgMenu_SetPageNum(); 
//		menuNext(); 
//		menuPageEntry()  -> PgMenu_toPage(); 
extern void MenuEntr_NextMenuOrPage(void);


// �˵�����������ƶ���ͻ����ʾ���λ��:
extern void MenuUp(void);
extern void MenuDown(void);
extern void MenuFigEnter(U8 mMenuSequ);



// ���ص��ϼ��˵� �� MCycle(�¼���״̬)ҳ��:
// * Slave:  
// 		����˵�.return:  ClrMenuAllBufAndSign() 
//						+ PgMenu_Return_Exit();
extern void MenuReturn(void);

// �˵��˳���MCycle(�¼���״̬)ҳ��:
// slave: ClrMenuAllBufAndSign() + PgMenu_Esc_Exit();
extern void MenuEsc(void);



// ҳ���˳��� �˵�:
// master: ���ȣ�ҳ���˳�;
// slave: PgMenu_SetPageNum(); 
extern void PageRtnToMenu(void);

//Clr�˵�R �� menu.back() ִ�С�
// slave: ClrPgState_InMenu();
extern void ClrMenuAllBufAndSign(void);

/******************************************************************************
// END :
******************************************************************************/
#endif // __lcdCst_OpeaMenu_H__

