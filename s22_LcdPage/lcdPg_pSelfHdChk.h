#ifndef __lcdPg_pSelfHdChk_H__
#define __lcdPg_pSelfHdChk_H__
/******************************************************************************
* @file    lcdPg_pSelfHdChk.h
* @author  yx
* @version V1.0
* @date    2013-01-04
* @brief   自检：声光、按键、Flash, 时钟，Can, Uart 等。
* 
#include  "lcdPg_pSelfHdChk.h"
******************************************************************************/

#include  "prjCompileCon.h"
#include  "hwEx13_lcd_DataType.h"
#include  "hwEx11_lcd_DefPara.h"
#include  "strClock.h"
/*================= extern ============================================*/
#ifdef  __lcdPg_pSelfHdChk_C__
#define EX_lcdPg_pSelfHdChk
#else
#define EX_lcdPg_pSelfHdChk extern 
#endif

/*================= 常数 ============================================*/
/*================= 常数-显示位置 ============================================*/
#define U_ShowUseLib_Test_Use   0
	// U_ShowUseLib_88orCn_CN  = 0,
	// U_ShowUseLib_88orCn_88Ascii  = 1,
/*================= 常数-显示位置 ============================================*/

	#define U_Line_TestFosc     18
	#define U_Line_TestRealTmr     0

	#define U_Line_TestICan     0
	#define U_Line_TestECan     8

	#define U_Line_TestUart     16
	#define U_Line_TestUrtFig   (U_Line_TestUart + 5)

	#define U_Line_TestKey     0
	#define U_Line_TstKey_key   (U_Line_TestKey + 4)
	
	#define U_Line_TestFlash     11
	#define U_Line_TestPwrChkSwc     17
	#define U_Line_TestPwrState     0
	
	
#if U_ShowUseLib_Test_Use == 1 // U_ShowUseLib_88orCn_88Ascii

	#if U_SHOW_HalfChar_HEIGHT  == 8
		#define U_ROW__TestFosc      2
		#define U_ROW__TestRealTmr      2

		#define U_ROW__TestCan      3
		#define U_ROW__TestUart      3

		#define U_ROW__TestKey      4
		#define U_ROW__TestFlash      4

		#define U_ROW__TestPwrChkSwc      5
		#define U_ROW__TestPwrState      5
	#else // now : U_SHOW_HalfChar_HEIGHT < 8
		#define U_ROW__TestFosc      2
		#define U_ROW__TestRealTmr      2

		#define U_ROW__TestCan      4
		#define U_ROW__TestUart      4

		#define U_ROW__TestKey      6
		#define U_ROW__TestFlash      6

		#define U_ROW__TestPwrChkSwc      8
		#define U_ROW__TestPwrState      8
	#endif // U_CharLibAscii8_Wide_NOW
	
#else // now  U_ShowUseLib_Test_Use == U_ShowUseLib_88orCn_CN
	#if U_CharLib_NOW == U_CharLib_16
		#define U_ROW__TestFosc      0
		#define U_ROW__TestRealTmr      0
	#else // now U_CharLib_NOW = U_CharLib_12
		#define U_ROW__TestFosc      8
		#define U_ROW__TestRealTmr      8
	#endif // U_CharLib_NOW

	#define U_ROW__TestCan      2

	#define U_ROW__TestUart      2

	#define U_ROW__TestKey      4

	#define U_ROW__TestFlash      4

	#define U_ROW__TestPwrChkSwc      6

	#define U_ROW__TestPwrState      6

#endif // U_ShowUseLib_Test_Use


/*================= 私有结构变量声明 ================================*/
#ifdef  __lcdPg_pSelfHdChk_C__
typedef struct{
	U8 testTimes;
	U8 testStep;
	
	U32 tmr0;
	U32 tmr1;
	U32 tmrDiff;
}TSelfHdChkTask;

TSelfHdChkTask  stSelfHdChkTask;

// 测试指令周期：
void chkHd_AllHd_Exe_TestTick(void); 
// 测试 for循环
void chkHd_AllHd_Exe_test_tick_2_for(void);
void chkHd_AllHd_Exe_test_tick_1_tick(void);
void chkHd_AllHd_Exe_test_tick_show(void);

#endif  //__lcdPg_pSelfHdChk_C__
/*================= 私有结构变量声明 ================================*/
#ifdef  __lcdPg_pSelfHdChk_C__
typedef struct{
	U32 tmr100msNum;
	BOOL bTmrArrived;
}TSelfHdChkOne;

typedef struct{
	U8  item;
	U32 tmrMsMax; //定时到，exec一次。
}TCstSelfHdChkDef;

#define emChkHd_Led  1
#define emChkHd_Key  2
#define emChkHd_Fosc  3
#define emChkHd_ICanTxWait  4
#define emChkHd_ICanSend  5
#define emChkHd_ECanSend  6
#define emChkHd_CanRx  7
#define emChkHd_UartSend  8
#define emChkHd_UartRx  9
#define emChkHd_PwrChkSwc 10
#define emChkHd_PwrState  11

#define emChkHd_ITEM_MAX  12

static TSelfHdChkOne  stSelfHdChkTmr[emChkHd_ITEM_MAX];
const TCstSelfHdChkDef cstChkHdTmrMsArrived[emChkHd_ITEM_MAX];

#endif  //__lcdPg_pSelfHdChk_C__
/*=================  ================================================*/
//#define 
/*================= 结构体定义 ======================================*/

/*================= 公有结构变量声明 ================================*/

/*================= 私有函数声明 ====================================*/
#ifdef  __lcdPg_pSelfHdChk_C__

static void selfHdChk_Show_EvtTime_YMDHMS(
						TYPE_LCD_RL mRow, TYPE_LCD_RL mLine, 
						TEvtClock_st *pEvtClock
						);

static void selfHdChk_Show_cstChar(
						TYPE_LCD_RL mRow, 
						U8 mPreCnNum, U8 mPreEnNum, 
						const U8 *pCodeChar, BOOL bInverse
						);
static void selfHdChk_Show_Fig_Pre0(
						TYPE_LCD_RL mRow, 
						U8 mPreCnNum, U8 mPreEnNum,
						U32 fig, U8 bitTotal
						);
static void selfHdChk_Show_Fig_RightAllign(
						TYPE_LCD_RL mRow, 
						U8 mPreCnNum, U8 mPreEnNum,
						U32 fig, U8 bitTotal
						);


U32 chkHd_getTmrMsMax(U8 mItem);
void chkHd_TmrMs_Clr(void);
void chkHd_TmrMsAdd(U32 mMs);
BOOL chkHd_bTmrMsMaxArrived(U8 mItem);


void chkHd_Lcd__Ini_drawLine(void);
void chkHd_Lcd__Ini_ShowTxt(void);
void chkHd_Lcd_Ini(void);
void chkHd_Lcd_Exec(void);

void chkHd_Fls__WrBufFillData(void);
void chkHd_Fls__SwResultOne(U8 offsetLine, BOOL bOK);
void chkHd_Fls__SwResultAll(U8 bNorU7Ok, U8 bNorU8Ok, U8 bNandU9Ok);
BOOL chkHd_Fls__compare_Rd_Wr(void);
void chkHd_Fls__Nor_0_RdEraseRd(void);
BOOL chkHd_Fls__Nor_N(U8 mChip);
BOOL chkHd_Fls__Nand(void);
void chkHd_Fls__Check(void);
void chkHd_Fls_Ini(void);
void chkHd_Fls_Exec(void);

void chkHd_Key__show(U8 mKey);
void chkHd_Key_Ini(void);
void chkHd_Key_Exec(void);

void chkHd_Led__Start(void);
void chkHd_Led_Ini(void);
void chkHd_Led_Exec(void);
void chkHd_Led_Exit(void);

U32  chkHd_PwrChkSwc__CacuVolt(U32 mAdVal);
void chkHd_PwrChkSwc__ShowAdResult(U32 mAdVal);
void chkHd_PwrChkSwc_Ini(void);
void chkHd_PwrChkSwc_Exec(void);

void chkHd_PwrState__ShowResultOne(U8 offsetLine, BOOL bFault);
void chkHd_PwrState_Ini(void);
void chkHd_PwrState_Exec(void);

void chkHd_Can__CanRx(U8 canPeriId);
void chkHd_Can__showRxNum(void);
void chkHd_Can_Ini(void);
void chkHd_Can_Exec(void);

//  函数原型，因为 hw_Uart 现在未用。
void Close_CUart(U8 uartPeriId);
void UartRegi_Int_Enable(U8 uartPeriId);
void UartRegi_Int_Disable(U8 uartPeriId);
void HwUart_SendStart(U8 uartPeriId);

void chkHd_Uart__UartRx(void);
void chkHd_Uart_Ini(void);
void chkHd_Uart_Exec(void);

void chkHd_RealTmrFosc__showFoscSec(void);
BOOL chkHd_RealTmrFosc__SetRealTmr(void);
BOOL chkHd_RealTmrFosc__ShowRealTmr(void);
void chkHd_RealTmrFosc_Ini(void);
void chkHd_RealTmrFosc_Exec(void);

void chkHd_Dog_Ini(void);
void chkHd_Dog_Exec(void);



#endif // __lcdPg_pSelfHdChk_C__
/*================= 公有函数声明 ====================================*/
//EX_lcdPg_pSelfHdChk 

extern void chkHd_Can__CanRx(U8 canPeriId);

extern void chkHd_AllHd_Ini(void);
extern void chkHd_AllHd_Exec(void);
extern void chkHd_AllHd_Exit(void);


/******************************************************************************
// END :
******************************************************************************/
#endif // __lcdPg_pSelfHdChk_H__

