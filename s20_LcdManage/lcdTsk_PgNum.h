#ifndef __lcdTsk_PgNum_H__
#define __lcdTsk_PgNum_H__
/******************************************************************************
* @file    lcdTsk_PgNum.h
* @author  yx
* @version V1.0
* @date    2013-07-01
* @brief   
* 
#include  "lcdTsk_PgNum.h"
******************************************************************************/
//
#include  "prjCompileCon.h"
#include  "evt_Para.h"  // use  U_OneScr_Cls_MAX 

/*================= extern ============================================*/
#ifdef  __lcdTsk_PgNum_C__
#define EX_lcdTsk_PgNum
#else
#define EX_lcdTsk_PgNum extern 
#endif
/*================= 常数 ============================================*/

/*================= 页面 分类 =======================================*/
//页面 分类	  
typedef enum {
	
	U_PageType_MAIN 		= 0,	
	U_PageType_EVENT 		= 1,  	
	U_PageType_MENU 		= 2,
	U_PageType_PASSWORD		= 4, 		
	U_PageType_KEYENTER		= 5, 

	U_PageType_USUA 		= 3,			
	U_PageType_INVALID		= 7,

}emPageType;

/*================= 结构体定义 ======================================*/


typedef struct{
	U8 evtCls[U_OneScr_Cls_MAX]; // U8 mScreen;
	U8 page;
}TPgMCycDef_st;


#define U_PgMCycDef_Event_MAX   5 // U_EvtCls_MAX
#define U_PgMCycDef_All_MAX   (U_PgMCycDef_Event_MAX + 1)

// MCycle窗口(包括 事件窗口) 的定义
// 按优先级排列:
// const TPgMCycDef_st  cstPgMCycDef[U_PgMCycDef_All_MAX]; 

/*================= 公有结构变量声明 ================================*/
/*================= 私有函数声明 ====================================*/
#ifdef  __lcdTsk_PgNum_C__



#endif  //__lcdTsk_PgNum_C__
/*====== 公有函数声明 - MCycle窗口(包括 事件窗口) 的定义=============*/
//EX_lcdTsk_PgNum 

// 按优先级排列:
// const TPgMCycDef_st  cstPgMCycDef[U_PgMCycDef_All_MAX];



// pageNum -> emEvtClass
extern BOOL GetEvtClsFromPageNum(U8 mScreen, U8 *pRtnEvtCls);

// get 相应evt窗口 的 evtCls:
// IN: mDefSequ < U_PgMCycDef_Event_MAX
extern BOOL GetEvtCls_FromMCycEvtDefSequ(
				U8 mDefSequ, U8 mScreen, U8 *pRtnEvtCls);


// 事件页面的下一个
extern PAGEWORD GetMCycPage_AfterEvtFirst(void);

// get 相应evt窗口的 pageNum:
// IN: mDefSequ < U_PgMCycDef_Event_MAX
extern PAGEWORD GetMCycEvtPage_FromDefSequ(U8 mDefSequ);

// get 相应MCycle窗口的 pageNum:
// IN: mDefSequ < U_PgMCycDef_All_MAX
extern PAGEWORD GetMCyclePage_FromDefSequ(U8 mDefSequ);


/*================= 公有函数声明 ====================================*/
//EX_lcdTsk_PgNum 


extern void IniPageNum(void);
extern BOOL SetPageNum(PAGEWORD mPage);
extern BOOL GetPageNum(PAGEWORD *pRtnPage);
//page=有效
extern BOOL bPageNumValid(PAGEWORD mPage);


extern PAGEWORD GetPgNum_Main(void);
extern PAGEWORD GetPgNum_EvtTotal(void);
extern PAGEWORD GetPgNum_EvtAlarm(void);
extern PAGEWORD GetPgNum_EvtExtg(void);
extern PAGEWORD GetPgNum_EvtLink(void);

extern PAGEWORD GetPgNum_Menu(void);
extern PAGEWORD GetPgNum_UserLogin(void);
extern PAGEWORD GetPgNum_MiniEvent(void);
extern PAGEWORD GetPgNum_Default(void);

// *  OUT:	emPageType
extern U8 LcdJdg_PageType(void);


extern BOOL bPageIsMCycle(void);  //page=事件界面 | main | Status.
extern BOOL bPageIsEvent(void);
extern BOOL bPageIsUserLogin(void);  //page=用户登录界面
extern BOOL bPageIsMenu(void);  //page=菜单界面
extern BOOL bPageIsMain(void);  //page=主界面
extern BOOL bPageIsCheckKey(void);  //page=测试按键界面

extern BOOL bPageIsInquireRegist(void);  //page=查询登记
extern BOOL bPageIsLoopBrowse(void);  //page=回路浏览

extern BOOL bPageIsGetDeteAnalog(void);  //page=测试：模拟曲线
extern BOOL bPageIsGetDeteInterData(void);  //page=测试：内部数据
extern BOOL bPageIsGetDeteTypeState(void);  //page=测试：类型状态
extern BOOL bPageIsGetDeteCurrent(void);  //page=测试：状态电流+背景电流
extern BOOL bPageIsGetDeteSensitive(void);  //page=测试：探测器灵敏度


extern void SetPgMiniEvent_Class(U8 mCls);
extern void ClrPgMiniEvent_Class(void);
extern U8 GetPgMiniEvent_Class(void);


/******************************************************************************
// END :
******************************************************************************/
#endif // __lcdTsk_PgNum_H__

