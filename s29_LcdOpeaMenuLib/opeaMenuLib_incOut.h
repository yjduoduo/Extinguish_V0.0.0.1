#ifndef __opeaMenuLib_incOut_H__
#define __opeaMenuLib_incOut_H__
/******************************************************************************
* @file    opeaMenuLib_incOut.h
* @author  yx
* @version V1.6
* @date    2013.10.08 11:50
* @brief   �˵�����
* @in      ��Ҫ�ǰ���
*
* V1.6  2013.10.08 11:50  ��OpeaMenu_Driver_V0.0.0.1_0.0.8��
*		add: MenuFigEnter(); // �˵���ֱ��������ȷ��
* V1.5  2013.9.29 10:35   ��OpeaMenu_Driver_V0.0.0.1_0.0.7��
		add: �˵�δ��ʾhead��endʱ�����ַ���ʾ��
* V1.4, 2013.9.17 16:17   ��OpeaMenu_Driver_V0.0.0.1_0.0.6��
		addע�ͣ�������slave
* V1.3, 2013.9.13 09:28
		add: һ��������ʾ���в˵������ MenuDisp();  -> Menu_Part_Disp();
* V1.2, 2013.9.11
* 		add: ClrMenuAllBufAndSign();
* V1.1��2013-09-09  ��ע�͡�
* V1.0��2013-09-04
* 
#include  "opeaMenuLib_incOut.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

/*================= ���� ============================================*/

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
#endif // __opeaMenuLib_incOut_H__

