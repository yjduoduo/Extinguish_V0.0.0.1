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
/*================= ���� ============================================*/

/*================= ҳ�� ���� =======================================*/
//ҳ�� ����	  
typedef enum {
	
	U_PageType_MAIN 		= 0,	
	U_PageType_EVENT 		= 1,  	
	U_PageType_MENU 		= 2,
	U_PageType_PASSWORD		= 4, 		
	U_PageType_KEYENTER		= 5, 

	U_PageType_USUA 		= 3,			
	U_PageType_INVALID		= 7,

}emPageType;

/*================= �ṹ�嶨�� ======================================*/


typedef struct{
	U8 evtCls[U_OneScr_Cls_MAX]; // U8 mScreen;
	U8 page;
}TPgMCycDef_st;


#define U_PgMCycDef_Event_MAX   5 // U_EvtCls_MAX
#define U_PgMCycDef_All_MAX   (U_PgMCycDef_Event_MAX + 1)

// MCycle����(���� �¼�����) �Ķ���
// �����ȼ�����:
// const TPgMCycDef_st  cstPgMCycDef[U_PgMCycDef_All_MAX]; 

/*================= ���нṹ�������� ================================*/
/*================= ˽�к������� ====================================*/
#ifdef  __lcdTsk_PgNum_C__



#endif  //__lcdTsk_PgNum_C__
/*====== ���к������� - MCycle����(���� �¼�����) �Ķ���=============*/
//EX_lcdTsk_PgNum 

// �����ȼ�����:
// const TPgMCycDef_st  cstPgMCycDef[U_PgMCycDef_All_MAX];



// pageNum -> emEvtClass
extern BOOL GetEvtClsFromPageNum(U8 mScreen, U8 *pRtnEvtCls);

// get ��Ӧevt���� �� evtCls:
// IN: mDefSequ < U_PgMCycDef_Event_MAX
extern BOOL GetEvtCls_FromMCycEvtDefSequ(
				U8 mDefSequ, U8 mScreen, U8 *pRtnEvtCls);


// �¼�ҳ�����һ��
extern PAGEWORD GetMCycPage_AfterEvtFirst(void);

// get ��Ӧevt���ڵ� pageNum:
// IN: mDefSequ < U_PgMCycDef_Event_MAX
extern PAGEWORD GetMCycEvtPage_FromDefSequ(U8 mDefSequ);

// get ��ӦMCycle���ڵ� pageNum:
// IN: mDefSequ < U_PgMCycDef_All_MAX
extern PAGEWORD GetMCyclePage_FromDefSequ(U8 mDefSequ);


/*================= ���к������� ====================================*/
//EX_lcdTsk_PgNum 


extern void IniPageNum(void);
extern BOOL SetPageNum(PAGEWORD mPage);
extern BOOL GetPageNum(PAGEWORD *pRtnPage);
//page=��Ч
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


extern BOOL bPageIsMCycle(void);  //page=�¼����� | main | Status.
extern BOOL bPageIsEvent(void);
extern BOOL bPageIsUserLogin(void);  //page=�û���¼����
extern BOOL bPageIsMenu(void);  //page=�˵�����
extern BOOL bPageIsMain(void);  //page=������
extern BOOL bPageIsCheckKey(void);  //page=���԰�������

extern BOOL bPageIsInquireRegist(void);  //page=��ѯ�Ǽ�
extern BOOL bPageIsLoopBrowse(void);  //page=��·���

extern BOOL bPageIsGetDeteAnalog(void);  //page=���ԣ�ģ������
extern BOOL bPageIsGetDeteInterData(void);  //page=���ԣ��ڲ�����
extern BOOL bPageIsGetDeteTypeState(void);  //page=���ԣ�����״̬
extern BOOL bPageIsGetDeteCurrent(void);  //page=���ԣ�״̬����+��������
extern BOOL bPageIsGetDeteSensitive(void);  //page=���ԣ�̽����������


extern void SetPgMiniEvent_Class(U8 mCls);
extern void ClrPgMiniEvent_Class(void);
extern U8 GetPgMiniEvent_Class(void);


/******************************************************************************
// END :
******************************************************************************/
#endif // __lcdTsk_PgNum_H__

