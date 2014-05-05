#ifndef __lcdPg_MainAndEvtChange_H__
#define __lcdPg_MainAndEvtChange_H__
/******************************************************************************
* @file    lcdPg_MainAndEvtChange.h
* @author  yx
* @version V1.0
* @date    2013-10-15
* @brief   �¼��仯 ��ҳ���Ӱ��. 
		 �ֶ����Զ���ҳ���ơ�
* 
#include  "lcdPg_MainAndEvtChange.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

/*================= extern ============================================*/
#ifdef  __lcdPg_MainAndEvtChange_C__
#define EX_lcdPg_MainAndEvtChange
#else
#define EX_lcdPg_MainAndEvtChange extern 
#endif
/*================= ���� ============================================*/
//#define 
/*================= �ṹ�嶨�� ======================================*/

/*================= ���нṹ�������� ================================*/

/*================= ˽�к������� ====================================*/
#ifdef  __lcdPg_MainAndEvtChange_C__

// �ж� �¼�ҳ�� �����¼���
static BOOL pgEvt_jdgNewEvent(void);

// TRUE = �¼�ҳ�� �����¼���
BOOL jdgNowEvtPage_EvtHave(U8 mSequ);



// ��ԭ��
// static BOOL pgEvt_jdgHaveEvtOneSequ(U8 mSequ);

#endif  //__lcdPg_MainAndEvtChange_C__
/*================= ˽�к������� ====================================*/
#ifdef  __lcdPg_MainAndEvtChange_C__

void LcdPageEvt_Refresh_SetArrived(void);
BOOL lcdPageEvt_jdgRereshTmr(void);

// �¼�ҳ��ˢ�¡� ����ǰҳ����¼�total=0, esc.
// refresh:
extern BOOL LcdPageEvt_Refresh(void);

// �ж� �¼�ҳ����¼�total �Ƿ� =0
extern BOOL LcdPageEvt_jdgTotal0_Esc(void);

// ��ʾ �¼�����
void LcdPageEvt_evtTotalChange(void);


// page main, ��ǰ���¼���
// TRUE = �� pageMain,  ���¼�:key esc; ���¼�:�����ж������¼�ҳ���ˡ�
BOOL pageMain_JdgHaveEvent(void);

// page event ������ȼ�, �����¼���
// TRUE = �����¼���  ����������ȼ�page:key esc; ��:��ʾ���£������ж������¼�ҳ���ˡ�
BOOL bNewEvtIsHighestPriority(PAGEWORD mNowPage);


// * FUNC: // ���ұ�now���ȼ����ߵ����¼���page
// *   IN: // PageMain �Ѵ��� + �����¼���
// page event �������ȼ�, �����¼���
// TRUE = ���¼��Ǹ������ȼ��ġ�
BOOL bNewEvtIsHigherThanNow(
						PAGEWORD mNowPage, PAGEWORD *pRtnPgNum);



// �����¼����ж��Ƿ���Ҫ��ʾ���ȼ����ߵģ�
// ���ú���Ҫmaster: EvtBuf_ClrChange();
extern BOOL bNewEvtSoToNewPage(PAGEWORD *pRtnPgNum);


#endif  //__lcdPg_MainAndEvtChange_C__

/*================= ���к������� ====================================*/
//EX_lcdPg_MainAndEvtChange 

// �¼���ʱˢ��
extern void LcdPageEvt_RefreshTmrStart(void);
extern void LcdPageEvt_RefreshTmrStop(void);
extern void LcdPageEvt_RefreshReTmr(void); // �����ض�ʱ

// �Զ���ҳ��ʱ
extern void LcdPageEvt_AutoTurn_TmrStart(void);
extern void LcdPageEvt_AutoTurn_TmrStop(void);
extern void LcdPageEvt_HaveUserKey_ForbidAutoTurn(void);
static BOOL lcdPageEvt_jdgAutoTurn(void);
extern BOOL bLcdPageEvt_ForbidAutoTurn_Ing(void);

/*======= ���к�������-ģ���� "lcdPg_MainOrEvt.c" use =================*/
//EX_lcdPg_MainAndEvtChange 

// �ж� ���¼���
extern BOOL pgEvt_jdgHaveEvent(void);

// TRUE = ���Ե��¼�ҳ�涼�޿���ʾ���¼�
// ��ҪԤ�� pgEvt_jdgHaveEvent();
extern BOOL bAllPgCycEvt_NoEvent(void);

// TRUE = mSequ�¼�ҳ������Ҫ��ʾ���¼�
// * ��ҪԤ���� pgEvt_jdgHaveEvent();
extern BOOL bCycEvtSequ_HaveEvent(U8 mSequ);


// ����mNowPage �� MCycleDef ����ţ�
extern BOOL GetPgCycSequ_FromPage(PAGEWORD mNowPage, U8 *pRtnSequ);



/*================= ���к������� ====================================*/
//EX_lcdPg_MainAndEvtChange 
//


extern void Exec_MainOrEvtWindow(void);

/******************************************************************************
// END :
******************************************************************************/
#endif // __lcdPg_MainAndEvtChange_H__

