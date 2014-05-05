#ifndef __lcdPg_ShowEvt_H__
#define __lcdPg_ShowEvt_H__
/******************************************************************************
* @file    lcdPg_ShowEvt.h
* @author  yx
* @version V1.0
* @date    2013-01-04
* @brief   �����¼�ҳ��
* 
#include  "lcdPg_ShowEvt.h" 
******************************************************************************/

#include  "prjCompileCon.h"
/*================= extern ============================================*/
#ifdef  __lcdPg_ShowEvt_C__
#define EX_lcdPg_ShowEvt
#else
#define EX_lcdPg_ShowEvt extern 
#endif

/*================= ���� ============================================*/
//#define 
/*================= �ṹ�嶨�� ======================================*/

/*================= ���нṹ�������� ================================*/

/*================= ˽�к������� ====================================*/
#ifdef  __lcdPg_ShowEvt_C__


static BOOL bPgEvtIsMiniShow(void);

U8 LcdPageEvt_Alarm_refresh(void);
U8 LcdPageEvt_Spvs_refresh(void);
U8 LcdPageEvt_Link_refresh(void);
U8 LcdPageEvt_Extg_refresh(void);
U8 LcdPageEvt_Fault_refresh(void);
U8 LcdPageEvt_Dsab_refresh(void);

extern BOOL LcdPageEvt_EvtCls_Ini(U8 mEvtCls, U8 mScreen);

extern void LcdPageEvt_Key(void);
extern void LcdPageEvt_Mini_Key(U8 mEvtCls);

#endif  //  __lcdPg_ShowEvt_C__
/*================= ���к������� ====================================*/
//EX_lcdPg_ShowEvt 



static void setEvtHaveShowItemNum(U8 mEvtCls, U8 mNum);
extern U8 GetEvtHaveShowItemNum(U8 mEvtCls); // ��ǰ�� ��ʾ���¼�����

extern BOOL LcdPageEvt_EvtCls_Refresh(U8 mEvtCls);
extern void LcdPageEvt_Key_Fig(U8 mFig);


extern void LcdPageEvt_MiniBack(void);
extern void LcdPageEvt_MiniUsual(void);
extern BOOL LcdPageEvt_MiniFirst(void);

extern void LcdPageEvt_PageBack(void);
extern void LcdPageEvt_PageUsual(void);
extern BOOL LcdPageEvt_PageFirst(void);

extern void LcdPageEvt_PageUp(U8 mEvtCls);
extern void LcdPageEvt_PageDown(U8 mEvtCls);


/******************************************************************************
// END :
******************************************************************************/
#endif // __lcdPg_ShowEvt_H__

