#ifndef __lcdPg_MainOrEvt_H__
#define __lcdPg_MainOrEvt_H__
/******************************************************************************
* @file    lcdPg_MainOrEvt.h
* @author  yx
* @version V1.0
* @date    2013-09-10
* @brief   MCycleҳ����л����л���˳���� "lcdTsk_PgNum.c" cstPgMCycDef[]
* @in	MCyclePage + keyReturn.
* 
#include  "lcdPg_MainOrEvt.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

/*================= extern ============================================*/
#ifdef  __lcdPg_MainOrEvt_C__
#define EX_lcdPg_MainOrEvt
#else
#define EX_lcdPg_MainOrEvt extern 
#endif
/*================= ���� ============================================*/
//#define 
/*================= �ṹ�嶨�� ======================================*/

/*================= ���нṹ�������� ================================*/

/*================= ˽�к������� ====================================*/
#ifdef  __lcdPg_MainOrEvt_C__

// �������ȼ����͵��¼�ҳ�档
// Pre:  pgEvt_jdgHaveEvent();
// IN: mFromSequ = ��ʼ���ҵ�sequ;
//	  mFromSequ < U_PgMCycDef_Event_MAX�� ���� Default = 0.
// OUT: FALSE = �����ȼ����͵��¼�
BOOL jdgNextEvtCycSequ_defaultPageMain(U8 mFromSequ, 
									 PAGEWORD *pRtnPgNum);


// page Main. next MCycle:
PAGEWORD jdgPageMain_NextMCycle(void);
// page Main��event�����. next MCycle:
PAGEWORD jdgPageMOther_NextMCycle(void);
// page event. next MCycle:
PAGEWORD jdgPageEvent_NextMCycle(void);


#endif  //__lcdPg_MainOrEvt_C__

/*================= ���к������� ====================================*/
//EX_lcdPg_MainOrEvt 

//  ���� next MCycle Page:
extern BOOL JdgNextMCyclePage(PAGEWORD *pRtnPgNum);

// main or �¼� page;
// *  OUT: ��ǰ���ȼ���ߵ��¼�ҳ�档if all total==0, return MAIN.
extern PAGEWORD JdgMainOrEvtHighPriorityPage(void); 


/******************************************************************************
// END :
******************************************************************************/
#endif // __lcdPg_MainOrEvt_H__

