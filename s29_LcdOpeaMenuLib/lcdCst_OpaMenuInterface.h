#ifndef __lcdCst_OpaMenuInterface_H__
#define __lcdCst_OpaMenuInterface_H__
/******************************************************************************
* @file    lcdCst_OpaMenuInterface.h
* @author  yx
* @version V1.3
* @date    2013.9.17 16:17
* @brief   OpeaMenuLib�Ľӿڡ�
* 

* V1.4, 2013.9.29 10:10 
*		add:�� GetMenu1PageItemMax();
*			PgMenuShowMode_PrePgHaveMenu();  PgMenuShowMode_NextPgHaveMenu();
* V1.3, 2013.9.17 16:17 
		�� PgMenu_Esc_Exit();
* V1.2, 2013.9.11 00:19
		add: PgMenu_Error();
		��:  PgMenu_Exit() �Ĵ���ʽ��
* V1.1, 2013.9.6
		add : PgMenuItem_SelectSign();
* V1.0, 2013-09-04
*
*
#include  "lcdCst_OpaMenuInterface.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

/*================= extern ============================================*/
#ifdef  __lcdCst_OpaMenuInterface_C__
#define EX_lcdCst_OpaMenuInterface
#else
#define EX_lcdCst_OpaMenuInterface extern 
#endif
/*================= ���� ============================================*/

#if U_CharLib_NOW==U_CharLib_12
	#define U_OneScreen_Menu_MAX    4   
#else
	#define U_OneScreen_Menu_MAX    3   
#endif
/*================= �ṹ�嶨�� ======================================*/

/*================= ���нṹ�������� ================================*/

/*================= ˽�к������� ====================================*/
#ifdef  __lcdCst_OpaMenuInterface_C__

#endif  //__lcdCst_OpaMenuInterface_C__

/*================= ���к�������-�ַ���ʾ ====================================*/
//EX_lcdCst_OpaMenuInterface 


/*-----------------  һ��menu:  ----------------------------------*/
// �˵���ʾһ�У�clr all:
extern void PgMenuItem_ClrTextBuf(void);

// �˵���ѡ�б�־:
// �� PgMenuItem_ClrTextBuf()��add �˵��ַ�ǰ�� ���á�
// Ҳ�������ɼ�¼bSelect״̬����PgMenuItem_show()ʱ��ӱ�־�������С�
extern void PgMenuItem_SelectSign(U8 mMenuRow, BOOL bSelect);

// �˵���ʾһ�У�add char:
extern void PgMenuItem_AddText(U8 *pChar);

// �˵���ʾһ�У�add char, ��ʾ���¼��˵�:
extern void PgMenuItem_AddTxt_HaveNextMenu(void);

// �˵���ʾһ�У�add char, ��ʾ ��ǰ�б�ѡ��:
extern void PgMenuItem_AddTxt_bSelect(void);

// ��ʾһ���˵��ַ�:
extern void PgMenuItem_show(U8 mMenuRow);


/*-----------------  menuHead:  ----------------------------------*/
// �˵�head��ʾһ�У�clr all:
extern void PgMenuHead_ClrTextBuf(void);

// �˵�head��ʾһ�У�add char, ��ʾ ���ӷ�:
extern void PgMenuHead_AddTxt_Join(void);

// �˵���ʾһ�У�add char:
extern void PgMenuHead_AddText(U8 *pChar);

// ��ʾ�˵�Head�ַ�:
extern void PgMenuHead_show(void);

/*-----------------  showMode:  ----------------------------------*/
// �˵���ʾģʽ: menuHead
extern void PgMenuShowMode_MenuHead(void);

// �˵���ʾģʽ: �Ƿ��������С� ����ʾһ�в˵�ǰ���á�
extern void PgMenuShowMode_Cursor(U8 mMenuRow, U8 bCursorAt);

// ��һ����ʾ�Ĳ��������˵���
extern void PgMenuShowMode_PrePgHaveMenu(void);
//   ĩ����ʾ�Ĳ���ĩ���˵���
extern void PgMenuShowMode_NextPgHaveMenu(void);

extern U8 GetMenu1PageItemMax(void);

/*================= ���к������� ====================================*/
//EX_lcdCst_OpaMenuInterface 

extern void SetPgState_InMenu(void);
// �� PgMenu_Exit()ǰ�ã���־���˳��˵�״̬��
extern void ClrPgState_InMenu(void);


// �˵��˳��� MCycle(�¼���״̬)ҳ�档
// menu.return, menu.esc;
// if ��Ҫ�ж���ʾҳ�棬�� Schedu.c ������ô����
// Master: MenuReturn(): ����˵�.return
// Master: MenuEsc(): use.
extern void PgMenu_Return_Exit(void);
extern void PgMenu_Esc_Exit(void);

// �˵� �����Իָ����˳���
extern void PgMenu_Error(void);

// �˵�����page:
extern void PgMenu_toPage(PAGEWORD mPage);

//pageNum = �˵���
extern void PgMenu_SetPageNum(void);

// �˵�ҳ�� ����:
extern void PgMenu_ClrScreen(void);

/******************************************************************************
// END :
******************************************************************************/
#endif // __lcdCst_OpaMenuInterface_H__

