#ifndef __sysPanel_H__
#define __sysPanel_H__
/******************************************************************************
* @file    sysPanel.h
* @author  yx
* @version V1.2
* @date    2013.10.24
* @brief   
	   
* 
* V1.2, 2013.10.24
*		修改：TPanelSequ_st 移动到.c文件。
*		去掉： pGetPanelStr(); 
*		去掉: TransDevTo_ICanAdr(); Trans_ICanAdr_ToDev(); 修改 panel_inLine_ResultOk();
*		add: GetPanelUnitMax();  
*		U_PN_TYPE_MAX  防止enum外面
*		add: Panel_Vesion_Rx(); 等有关version的。
* V1.1, 增加函数  TPanelSequ_st *pGetPanelStr(U8 pnType);  2013.8.21
* V1.0, 2013.7.1
* 
#include  "sysPanel.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

#include  "strDevice.h"
#include  "sysDef.h"
/*================= extern ============================================*/
#ifdef  __sysPanel_C__
#define EX_sysPanel
#else
#define EX_sysPanel extern 
#endif
/*================= 常数 ============================================*/

//==== << 设备 单元类型 ======
//==== << 设备 pDev唯一标识 ======
//系统内 单元类型定义：
//类型定义不能用enum, 因为涉及到 "#if"
// emBoardType:
typedef enum {	//pnType
	
	U_PN_Machine_TYPE		= 0x0,  // 0值是禁止的,所以用做machine.
	U_PN_Loop_TYPE		= 0x1,
	U_PN_Opea_TYPE		= 0x2, 
	U_PN_Drt_TYPE		= 0x3,
	U_PN_Bus_TYPE		= 0x4,
	U_PN_Extg_TYPE		= 0x5,
	U_PN_Broad_TYPE		= 0x6,
	U_PN_Power_TYPE		= 0x7,
	U_PN_Other_TYPE		= 0x8,
	
}emPanelType;
	
#define U_PN_TYPE_MAX  		0x09
	
/*================= 常数 ============================================*/

#define U_Board_LOOP_MAX	 0x08
#define U_Board_DRT_MAX	 	0x40
#define U_Board_EXTG_MAX	 0x30

/*================= 结构体定义 ======================================*/

/*================= 公有结构变量声明 ================================*/


/*================= 私有函数声明 ====================================*/
#ifdef  __sysPanel_C__
#define U_PANEL_INLINE_NUM_TOP   200
#define U_PANEL_OutLine_NUM_MIN   1 //如果时间足够，inLine 应 > outLine.
#define U_PANEL_InLine_NUM_MIN   1

#define U_PN_InLine_Interval_OutLine_Second   10
#define U_PN_InLine_Interval_InLine_Second    3


typedef struct 
{
	U32 bRegisted:1;
	U32 bOutLine:1;
	U32 inLineNum:8;
	
	U32 bHaveVersion:1;
	U32 pnVersionMain:4;
	U32 pnVersionAux:8;
}TPanel_st;

static TPanel_st vPanel[U_PANEL_TOTAL_SEQU_MAX]; // U8 pnICanSequ;


// static BOOL getPanelStr(U8 pnType, const TPanelSequ_st **pPnStr);


//  IN: mCanIdSrc: 0~
// OUT: mPnRamSequ: 0 ~ U_PANEL_TOTAL_SEQU_MAX;
BOOL canIdSourse_to_pnRamSequ(U8 mCanIdSrc,
							U8 *pRtnPnRamSequ);


//  IN: mPnRamSequ: 0 ~ U_PANEL_TOTAL_SEQU_MAX;
// OUT: *pRtnType: emPanelType;  *pRtnSequ: 1~
BOOL pnRamSequ_to_pnTypeSequ(U8 mPnRamSequ, 
							U8 *pRtnType, U8 *pRtnSequ);


BOOL panel_inLine_ResultOk(U8 mPnRamSequ, U8 bOk);

#endif  //__sysPanel_C__


/*================= 公有函数声明 ====================================*/
//EX_sysPanel 
extern void Panel_Regist(U8 mPnRamSequ, BOOL bRegisted);
extern void Panel_inLine_Inc(U8 mCanIdSrc);
extern void Panel_inLine_ClrOne(U8 mPnRamSequ);
extern void Panel_inLine_ClrAll(void);
extern void Panel_inLine_Check(void);


extern void Panel_Vesion_Rx(U8 pnType, U8 pnSequ, 
						   U8 versionMain, U8 versionAux);
extern void Panel_Vesion_ClrOne(U8 pnType, U8 pnSequ);
extern void Panel_Vesion_ClrAll(void);
extern BOOL Panel_Vesion_Get(U8 pnType, U8 pnSequ, 
							U8 *pVersionMain, U8 *pVersionAux);

//  IN: pnType: emPanelType;  pnSequ: 1~
// OUT: mPnRamSequ: 0 ~ U_PANEL_TOTAL_SEQU_MAX;
extern BOOL pnTypeSequ_to_pnRamSequ(U8 pnType, U8 pnSequ,
							U8 *pRtnPnRamSequ);

/*================= 公有函数声明 ====================================*/
//EX_sysPanel 

extern U8 GetPanelType_Loop(void);
extern U8 GetPanelType_Extg(void);
extern U8 GetPanelType_Drt(void);

extern BOOL bExtgUnit_Regist(U8 mExtgUnit);
extern BOOL bExtgUnit_Inline(U8 mExtgUnit);
extern U8 GetExtgUnitMax(void);

// MAX = 允许的数字+1；
extern BOOL GetPanelUnitMax(U8 pnType, U8 *pPnMax);

// 判断 单元号是否有效：
// IN: pnType: emPanelType;  
// IN: mSequStart:有关pange的计数，1号panel对应的数；
// IN: mSequNow:  有关pange的计数，当前数；
extern BOOL bSequValid_RelatePanel(U8 pnType, U8 mSequPn1Start, U8 mSequNow);

/*================= 公有函数声明 ====================================*/
//EX_sysPanel 

extern void PanelState_Init(void);


extern  U8 bPnSequIsValid(U8 pnType, U8 pnSequ);
extern  BOOL bPnTypeIsValid(U8 pnType); //emPanelType

/******************************************************************************
// END :
******************************************************************************/
#endif // __sysPanel_H__

