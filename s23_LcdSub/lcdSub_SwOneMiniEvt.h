#ifndef __lcdSub_SwOneMiniEvt_H__
#define __lcdSub_SwOneMiniEvt_H__
/******************************************************************************
* @file    lcdSub_SwOneMiniEvt.h
* @author  yx
* @version V1.0
* @date    2013-10-18
* @brief   
* 
#include  "lcdSub_SwOneMiniEvt.h"
******************************************************************************/
//
#include  "prjCompileCon.h"
#include  "strDevice.h"
#include  "evt_Para.h"
#include  "evtStrDef.h"

/*================= extern ============================================*/
#ifdef  __lcdSub_SwOneMiniEvt_C__
#define EX_lcdSub_SwOneMiniEvt
#else
#define EX_lcdSub_SwOneMiniEvt extern 
#endif
/*================= 常数 ============================================*/
#define U_SHOW_MINI_EVENT_ITEM_MAX  10

// U_EVT_TOTAL_FIG_BIT_TOTAL 
#define U_EvtMini_TOTAL_FIG_BIT_TOTAL   3  // 总数和序号的 位数
/*================= 结构体定义 ======================================*/

/*================= 公有结构变量声明 ================================*/

/*================= 私有函数声明 ====================================*/
#ifdef  __lcdSub_SwOneMiniEvt_C__


static void get_pix_x_y_mini(U8 winItem);
static void sw_dev_mini(TDev_un *pDev);
static void sw_sequ_mini(EVTWORD sequ);

static void sw_LinkEvt_mini(U8 thing);
static void sw_ExtgEvt_mini(U8 thing);
#endif  //__lcdSub_SwOneMiniEvt_C__
/*================= 公有函数声明 ====================================*/
//EX_lcdSub_SwOneMiniEvt 

// 各类事件：
extern void Show_OneMiniAlarm(U8 winItem, EVTWORD sequ,
							TEvtAlarm_st *m_pAlarm);
extern void Show_OneMiniSpvs(U8 winItem, EVTWORD sequ,
							TEvtSpvs_st *m_pSpvs);

extern void Show_OneMiniLink(U8 winItem, EVTWORD sequ,
							TEvtLink_st *m_pLink);
extern void Show_OneMiniExtg(U8 winItem, EVTWORD sequ,
							TEvtExtg_st *m_pExtg);
extern void Show_OneMiniFault(U8 winItem, EVTWORD sequ,
							TEvtFault_st *m_pFault);
extern void Show_OneMiniDsab(U8 winItem, EVTWORD sequ,
							TEvtDsab_st *m_pDsab);

/******************************************************************************
// END :
******************************************************************************/
#endif // __lcdSub_SwOneMiniEvt_H__

