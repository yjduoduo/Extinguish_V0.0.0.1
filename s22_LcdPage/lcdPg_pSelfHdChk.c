
#define __lcdPg_pSelfHdChk_C__
/******************************************************************************
* @file    lcdPg_pSelfHdChk.c
* @author  yx
* @version V1.0
* @date    2013-01-04
* @brief   自检：声光、按键、Flash, 时钟，Can, Uart 等。
*  
******************************************************************************/
#include  "lcdPg_pSelfHdChk.h"

//#include "..\\s00Prj\\incFile.h"	

#include "incFile.h"	
#include  "tmrTick.h"
#include  "phIoLed.h"
#include  "LcdLib_incOut.h"
//-----------------   --------------------------------// 
#include  "tsk_lcd_incIn.h"
//----- Me:
#include  "canPrtl_iTx.h"
#include  "canPrtl_eTx.h"
#include  "CanHd_Interface.h"
#include  "CanBufLib_ReDef.h"
extern void canHd_IorE_Init(U8 can_id);
// #include  "hw11_Uart.h"
#include  "CUart.h"
#include  "hwEx03_Pcf8563.h"

#include  "lcdSub_SwOneEvt.h"
#include  "lcdSub_ModeTextFig.h"

extern void CanRegi_AD_Init(void);
extern U32 chkPwrChkSwc_GetAd(void); // AD 采样

#include  "phIoPwrState.h"
#include  "hwEx10_GpioDef.h"
extern U8 chkPwrState_bFault_HdChk(U8 mChnl); //硬件检测

#include  "hwEx21_SST39vf800A.h"
#include  "nandflash_hy27uf081g2a.h"


extern TYPE_LCD_XY getPixYR_formRow(TYPE_LCD_RL mRow);

/*================= 常数 ============================================*/

const TCstSelfHdChkDef cstChkHdTmrMsArrived[emChkHd_ITEM_MAX] =
{
	{emChkHd_Led, (TMR_LedCheck * 100 * 2)},
	{emChkHd_Key, 1000},
	{emChkHd_Fosc, 100},
	{emChkHd_ICanSend, 3000},
	{emChkHd_ECanSend, 3000},
	{emChkHd_CanRx, 1000},
	{emChkHd_UartSend, 3000},
	{emChkHd_UartRx, 1000},
	{emChkHd_PwrChkSwc, 1000},
	{emChkHd_PwrState, 1000},
};
/*================= 结构定义 ========================================*/

/*================= 私有结构变量声明 ================================*/

/*================= 公有函数声明 ====================================*/

/*================= 私有函数声明 ====================================*/

/*=================  ================================================*/
		
/******************************************************************************
* FUNC: // 显示
*   IN:
*  OUT: 
******************************************************************************/
void chkHd_AllHd_Exit(void)
{
	chkHd_Led_Exit();
	KillTickTask(TASK_SelfHdChk);
}
	
void chkHd_AllHd_Ini(void)
{
	ClrRamIs00((U8*)(&stSelfHdChkTask), sizeof(TSelfHdChkTask));
	stSelfHdChkTask.testStep = ~0;
	
	// chkHd_Dog_Ini();
	chkHd_Lcd_Ini();
	chkHd_RealTmrFosc_Ini();
	chkHd_Uart_Ini();
	chkHd_Can_Ini();
	chkHd_PwrState_Ini();
	chkHd_PwrChkSwc_Ini();
	chkHd_Led_Ini();
	chkHd_Key_Ini();
	chkHd_Fls_Ini();
	
	
	chkHd_TmrMs_Clr();
	SetTmrTickTask(TASK_SelfHdChk, TMR_SelfHdChk);
}

/******************************************************************************
* FUNC: //
******************************************************************************/



void chkHd_AllHd_Exec(void)
{
	if(GetTickTaskStatus(TASK_SelfHdChk))
	{
		chkHd_TmrMsAdd(TMR_SelfHdChk);
		// chkHd_AllHd_Exe_TestTick();
	}
	
	
	
	chkHd_Dog_Exec();
	
	chkHd_Lcd_Exec();
	chkHd_RealTmrFosc_Exec();
	chkHd_Uart_Exec();
	chkHd_Can_Exec();
	
	chkHd_PwrChkSwc_Exec();
	chkHd_PwrState_Exec();
	chkHd_Led_Exec();
	chkHd_Key_Exec();
	chkHd_Fls_Exec();
	
}

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

void chkHd_AllHd_Exe_test_tick_show(void)
{
	if(stSelfHdChkTask.tmr0 > stSelfHdChkTask.tmr1)
	{
		return;
	}
	stSelfHdChkTask.tmrDiff = stSelfHdChkTask.tmr1 - stSelfHdChkTask.tmr0;
	
	selfHdChk_Show_Fig_RightAllign(U_ROW__TestFosc, 
					0, U_Line_TestFosc+9,
					stSelfHdChkTask.tmrDiff, 
					5);
	
}

void chkHd_AllHd_Exe_test_tick_1_tick(void)
{
	if(stSelfHdChkTask.testStep >= 3)
	{
		return;
	}
	
	switch(stSelfHdChkTask.testStep)
	{
		case 0:
			stSelfHdChkTask.tmr0 = GetTickTmrNowMs();
			break;
		case 1:
			stSelfHdChkTask.tmr1 = GetTickTmrNowMs();
			break;
		case 2:
			chkHd_AllHd_Exe_test_tick_show();
			break;
		default:
			break;
	}
	
}


// 测试 for循环
void chkHd_AllHd_Exe_test_tick_2_for(void)
{
U32 ii,jj;

	if(stSelfHdChkTask.testStep >= 1)
	{
		return;
	}
	
	
	// 清除已有的
	while(1)
	{
		if(bGetTickIntr())
		{
			TickTaskWork();
			break;
		}
	}
	
	// 确保刚刚有中断
	while(1)
	{
		if(bGetTickIntr())
		{
			TickTaskWork();
			break;
		}
	}
	
	stSelfHdChkTask.tmr0 = 0;
	ii = 0;
	while(1)
	{
		for(jj=0; jj<100; jj++);  // keil显示: 19us;
		ii++;
		if(bGetTickIntr())
		{
			TickTaskWork();  // keil显示: 23us;
			break;
		}
	}
	stSelfHdChkTask.tmr1 = ii; // 结果: 1498.
    //timerTickInterrupt(FORBID);
    
	chkHd_AllHd_Exe_test_tick_show();
	ExecLcdShow();
	
    //timerTickInterrupt(ALLOW);
	
	// 5ms 执行了 1500*for100; 1us=30for1;
	
}

/******************************************************************************
* FUNC: //
******************************************************************************/
// 测试指令周期：
void chkHd_AllHd_Exe_TestTick(void)
{
	
	stSelfHdChkTask.testTimes++;
	if(stSelfHdChkTask.testTimes >= 200)
	{
		stSelfHdChkTask.testTimes = 0;
		stSelfHdChkTask.testStep = 0;
	}
	
	chkHd_AllHd_Exe_test_tick_2_for();
	
	if(stSelfHdChkTask.testStep < 100)
	{
		stSelfHdChkTask.testStep++;
	}
}

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

U32 chkHd_getTmrMsMax(U8 mItem)
{
U8 ii;
	if(mItem >= emChkHd_ITEM_MAX)
	{
		return 0;
	}
	for(ii=0; ii<emChkHd_ITEM_MAX; ii++)
	{
		if(cstChkHdTmrMsArrived[ii].item == mItem)
		{
			return cstChkHdTmrMsArrived[ii].tmrMsMax;
		}
	}
	return 0;
}

void chkHd_TmrMs_Clr(void)
{
U8 ii;
	
	for(ii=0; ii<emChkHd_ITEM_MAX; ii++)
	{
		stSelfHdChkTmr[ii].tmr100msNum = 0;
		stSelfHdChkTmr[ii].bTmrArrived = FALSE;
	}
}

void chkHd_TmrMsAdd(U32 mMs)
{
U8 ii;
	
	for(ii=0; ii<emChkHd_ITEM_MAX; ii++)
	{
		stSelfHdChkTmr[ii].tmr100msNum += mMs;
	}
}

BOOL chkHd_bTmrMsMaxArrived(U8 mItem)
{
U32 mMsMax = 0;

	if(mItem >= emChkHd_ITEM_MAX)
	{
		return FALSE;
	}
	mMsMax = chkHd_getTmrMsMax(mItem);
	
	if(stSelfHdChkTmr[mItem].tmr100msNum >= mMsMax)
	{
		stSelfHdChkTmr[mItem].tmr100msNum = 0;
		// stSelfHdChkTmr[mItem].bTmrArrived = TRUE; //直接判断出结果，不必置位。
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/******************************************************************************
* FUNC: // 显示
*   IN:
*  OUT: 
******************************************************************************/


static void selfHdChk_Show_EvtTime_YMDHMS(
						TYPE_LCD_RL mRow, TYPE_LCD_RL mLine, 
						TEvtClock_st *pEvtClock
						)
{
#if U_ShowUseLib_Test_Use == U_ShowUseLib_88orCn_CN
	Show_EvtTime_YMDHMS(mRow, mLine, pEvtClock);	
#else 
	Show88_EvtTime_YMDHMS(mRow, mLine, pEvtClock);	
#endif //U_ShowUseLib_Test_Use
}


/******************************************************************************
* FUNC: // 
******************************************************************************/

static void selfHdChk_Show_cstChar(
						TYPE_LCD_RL mRow, 
						U8 mPreCnNum, U8 mPreEnNum, 
						const U8 *pCodeChar, BOOL bInverse
						)
{
#if U_ShowUseLib_Test_Use == U_ShowUseLib_88orCn_CN
	ShowXYCodeCharRL(mRow, mPreCnNum, mPreEnNum, pCodeChar, bInverse);
#else 
	// Show88CodeCharRL(mRow, mPreEnNum, pCodeChar, bInverse);
	LcdSw_cstAscii88(getPixYR_formRow(mRow), 
				 (mPreEnNum * U_Show_OneAscii88_LinePix), 
									pCodeChar);
#endif //U_ShowUseLib_Test_Use
}

/******************************************************************************
* FUNC: // 
******************************************************************************/

static void selfHdChk_Show_Fig_Pre0(
						TYPE_LCD_RL mRow, 
						U8 mPreCnNum, U8 mPreEnNum,
						U32 fig, U8 bitTotal
						)
{
	
#if U_ShowUseLib_Test_Use == U_ShowUseLib_88orCn_CN
	ShowXY_Fig_Pre0(mRow, mPreCnNum, mPreEnNum, fig, bitTotal);

#else 
	// Show88_Fig_Pre0(mRow, mPreEnNum, fig, bitTotal);
	LcdSw_SetFigMode(U_LcdMode_FigShow0, U_LcdMode_FigAlignRight);
	LcdSw_Ascii88Fig(getPixYR_formRow(mRow), 
				 (mPreEnNum * U_Show_OneAscii88_LinePix), 
									fig, bitTotal);
#endif //U_ShowUseLib_Test_Use
}


/******************************************************************************
* FUNC: // 
******************************************************************************/

static void selfHdChk_Show_Fig_RightAllign(
						TYPE_LCD_RL mRow, 
						U8 mPreCnNum, U8 mPreEnNum,
						U32 fig, U8 bitTotal
						)
{
#if U_ShowUseLib_Test_Use == U_ShowUseLib_88orCn_CN
	ShowXY_Fig_RightAllign(mRow, mPreCnNum, mPreEnNum, fig, bitTotal);	
#else 
	// Show88_Fig_RightAllign(mRow, mPreEnNum, fig, bitTotal);	
	LcdSw_SetFigMode(U_LcdMode_DontFigShow0, U_LcdMode_FigAlignRight);
	LcdSw_Ascii88Fig(getPixYR_formRow(mRow), 
				 (mPreEnNum * U_Show_OneAscii88_LinePix), 
									fig, bitTotal);
#endif //U_ShowUseLib_Test_Use
	
}


/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

void chkHd_Lcd__Ini_drawLine(void)
{
	
	
	// LcdSw_HvLine(	TYPE_LCD_XY mPixRow_S, 
							// TYPE_LCD_XY mPixLine_S,
							// TYPE_LCD_XY mPixRow_E, 
							// TYPE_LCD_XY mPixLine_E);
	LcdSw_HvLine(2,180,   58,180);
	LcdSw_HvLine(2,181,   59,181);
	LcdSw_HvLine(2,182,   60,182);
	LcdSw_ClrHvLine(5,181,   56,181);
	
	// LcdSw_HvLine(8,190,  2,190);
	// LcdSw_ClrRectangle(
							// TYPE_LCD_XY mPixRow_S, 
							// TYPE_LCD_XY mPixLine_S,
							// TYPE_LCD_XY mPixRow_E, 
							// TYPE_LCD_XY mPixLine_E);
	LcdSw_SetRectangle(50,2,   63,178);
	LcdSw_ClrRectangle(60,2,   62,178);
}

void chkHd_Lcd__Ini_ShowTxt(void)
{
	
	ShowXYCodeCharRL(1, 0,U_LCD_LINE_MAX-7,"控制器", FALSE);
	
	ShowXYCodeCharRL(0, 0,U_LCD_LINE_MAX-6,"控制器", FALSE);
	ShowXYCodeCharRL(2, 0,U_LCD_LINE_MAX-6,"控制器", FALSE);
	ShowXYCodeCharRL(4, 0,U_LCD_LINE_MAX-6,"控制器", FALSE);
	ShowXYCodeCharRL(6, 0,U_LCD_LINE_MAX-6,"控制器", FALSE);
	// ShowXYCodeCharRL(8, 0,U_LCD_LINE_MAX-6,"控制器", FALSE);

}

/******************************************************************************
* FUNC: //
******************************************************************************/

void chkHd_Lcd_Ini(void)
{
	if(!bMyHdHaveIniSign(U_SysTask_LcdShow))
	{
		InitLcdShow();
		SetMyHdHaveIniSign(U_SysTask_LcdShow);
	}
	
	LcdSw_ClrFullWindow(U_COLOR_BackGroundDefault);
	
	chkHd_Lcd__Ini_ShowTxt();
	// chkHd_Lcd__Ini_drawLine();
}


void chkHd_Lcd_Exec(void)
{
	// ExecLcdShow();
}


/******************************************************************************
* FUNC: //  chkHd_Fls_Ini();
*   IN:
*  OUT: 
******************************************************************************/


#define U_FLS_TEST_ADR   0x20 // 测试地址要选未实际用到的

#define U_NandFLS_TEST_PAGE   0
#define U_NandFLS_TEST_BLOCK   0

#define U_TEST_FLASH_NUM   0x10
static U8 mTestFlsWr[U_TEST_FLASH_NUM*2+8];
static U8 mTestFlsRd[U_TEST_FLASH_NUM*2+8];

static U8 vTestFlsNum = 0;

/******************************************************************************
* FUNC: //
******************************************************************************/

void chkHd_Fls__WrBufFillData(void)
{
U32 ii;
	for(ii=0; ii<U_TEST_FLASH_NUM; ii++)
	{
		mTestFlsWr[ii] = (vTestFlsNum * 0x20) +ii+1;
	}	
	vTestFlsNum++;
}


/******************************************************************************
* FUNC: //
******************************************************************************/

void chkHd_Fls__SwResultOne(U8 offsetLine, BOOL bOK)
{
	if(bOK)
	{
		selfHdChk_Show_cstChar(U_ROW__TestFlash, 
					0,(U_Line_TestFlash+offsetLine), "V", FALSE);
	}
	else
	{
		selfHdChk_Show_cstChar(U_ROW__TestFlash, 
					0,(U_Line_TestFlash+offsetLine), "X", FALSE);
	}
}

/******************************************************************************
* FUNC: //
******************************************************************************/

void chkHd_Fls__SwResultAll(U8 bNorU7Ok, U8 bNorU8Ok, U8 bNandU9Ok)
{
	selfHdChk_Show_cstChar(U_ROW__TestFlash, 0,U_Line_TestFlash, 
							"Fls:0V,1V,2V", FALSE);
	
	chkHd_Fls__SwResultOne( 5, bNorU7Ok);
	chkHd_Fls__SwResultOne( 8, bNorU8Ok);
	chkHd_Fls__SwResultOne(11, bNandU9Ok);
	
}

BOOL chkHd_Fls__compare_Rd_Wr(void)
{
U32 ii;
BOOL bOk = FALSE;
	
	for(ii=0; ii<U_TEST_FLASH_NUM; ii++)
	{
		if(mTestFlsRd[ii] != mTestFlsWr[ii])
		{
			bOk = FALSE;
			break;
		}
	}	
	if(ii >= U_TEST_FLASH_NUM)
	{
			bOk = TRUE;
	}
	
	
	return bOk;
}


/******************************************************************************
* FUNC: //
******************************************************************************/

void chkHd_Fls__Nor_0_RdEraseRd(void)
{
	FlsHd_Read_nByte(U_SST39VF900A_U7, &mTestFlsRd[0], U_TEST_FLASH_NUM, U_FLS_TEST_ADR);	
	FlsHd_EraseSect_FromAdr(U_SST39VF900A_U7, U_FLS_TEST_ADR, TRUE);	
	FlsHd_Read_nByte(U_SST39VF900A_U7, &mTestFlsRd[0], U_TEST_FLASH_NUM, U_FLS_TEST_ADR);
		
}


BOOL chkHd_Fls__Nor_N(U8 mChip)
{
	FlsHd_EraseSect_FromAdr(mChip, U_FLS_TEST_ADR+0x40, TRUE);	
	
	chkHd_Fls__WrBufFillData();
	
	FlsHd_Write_nByte(mChip, &mTestFlsWr[0], U_TEST_FLASH_NUM, 
					 U_FLS_TEST_ADR+0x40, TRUE);		
	FlsHd_Read_nByte(mChip, &mTestFlsRd[0], U_TEST_FLASH_NUM, 
					U_FLS_TEST_ADR+0x40);
	
	return chkHd_Fls__compare_Rd_Wr();
	
}

BOOL chkHd_Fls__Nand(void)
{
	
	HY271G_BlockErase( U_NandFLS_TEST_BLOCK );
	chkHd_Fls__WrBufFillData();
	HY271G_PageProgramData(U_NandFLS_TEST_BLOCK, U_NandFLS_TEST_PAGE,
				U_FLS_TEST_ADR, &mTestFlsWr[0], U_TEST_FLASH_NUM);
	HY271G_PageReadDataFromAddr(U_NandFLS_TEST_BLOCK, U_NandFLS_TEST_PAGE,
				U_FLS_TEST_ADR, &mTestFlsRd[0], U_TEST_FLASH_NUM);
	return chkHd_Fls__compare_Rd_Wr();
}


/******************************************************************************
* FUNC: //
******************************************************************************/


void chkHd_Fls__Check(void)
{
U8 bChip0Ok = FALSE;
U8 bChip1Ok = FALSE;
U8 bChip2Ok = FALSE;
	
	if(bMyHdHaveIniSign(U_SysTask_HdFlashNorU7_ID))
	{
		chkHd_Fls__Nor_0_RdEraseRd();
	}
	
	if(bMyHdHaveIniSign(U_SysTask_HdFlashNorU7_ID))
	{
		bChip0Ok = chkHd_Fls__Nor_N(U_SST39VF900A_U7);
	}
	if(bMyHdHaveIniSign(U_SysTask_HdFlashNorU8_ID))
	{
		bChip1Ok = chkHd_Fls__Nor_N(U_SST39VF900A_U8);
	}
	
	
	if(bMyHdHaveIniSign(U_SysTask_HdFlashNand_ID))
	{
		bChip2Ok = chkHd_Fls__Nand();
	}
	
	
	chkHd_Fls__SwResultAll(bChip0Ok, bChip1Ok, bChip2Ok);
	
}


/******************************************************************************
* FUNC: //
******************************************************************************/


void chkHd_Fls_Ini(void)
{
	if(!bMyHdHaveIniSign(U_SysTask_HdFlashNorU7_ID))
	{
		FlsHd_Init(U_SST39VF900A_U7);
		SetMyHdHaveIniSign(U_SysTask_HdFlashNorU7_ID);
	}
	
	if(!bMyHdHaveIniSign(U_SysTask_HdFlashNorU8_ID))
	{
		FlsHd_Init(U_SST39VF900A_U8);
		SetMyHdHaveIniSign(U_SysTask_HdFlashNorU8_ID);
	}
	
	if(!bMyHdHaveIniSign(U_SysTask_HdFlashNand_ID))
	{
		HY271G_Init();
		SetMyHdHaveIniSign(U_SysTask_HdFlashNand_ID);
	}
	
	
	chkHd_Fls__Check();
}

/******************************************************************************
* FUNC: //
******************************************************************************/
void chkHd_Fls_Exec(void)
{
	
}


/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

/******************************************************************************
* FUNC: // chkHd_Key_Ini(); 
*   IN:
*  OUT: 
******************************************************************************/


void chkHd_Key__show(U8 mKey)
{
	
const U8 *pCodeChar = "";
	
	selfHdChk_Show_cstChar(U_ROW__TestKey, 0, (U_Line_TstKey_key),
								"      ", FALSE);
	if(mKey < U_KEY_Fig_Max)
	{
		selfHdChk_Show_Fig_RightAllign(U_ROW__TestKey, 0,(U_Line_TstKey_key), 
								mKey, 1);	
		return;
	}
	switch(mKey)
	{
		
		case U_KEY_Star: 	pCodeChar = "*";
			break;
		case U_KEY_Pound: 	pCodeChar = "#";
			break;	
		case U_KEY_Auto:	pCodeChar = "Auto";
			break;	
		
		case U_KEY_Up:		pCodeChar = "Up";
			break;	
		case U_KEY_Down:	pCodeChar = "Down";
			break;	
		case U_KEY_Left:	pCodeChar = "Left";
			break;	
		case U_KEY_Right:	pCodeChar = "Right";
			break;	
		case U_KEY_Enter:	pCodeChar = "Enter";
			break;	
	
		case U_KEY_Return:	pCodeChar = "Return";
			break;	
		case U_KEY_Reset:	pCodeChar = "Reset";
			break;	
		case U_KEY_Silence:	pCodeChar = "Silenc";
			break;	
		
		case U_KEY_Esc:	
		default:
			return;
	}
	
	selfHdChk_Show_cstChar(U_ROW__TestKey, 0,(U_Line_TstKey_key), 
						pCodeChar, FALSE);
}


/******************************************************************************
* FUNC: //
******************************************************************************/
void chkHd_Key_Ini(void)
{
	
	if(!bMyHdHaveIniSign(U_SysTask_Key_ID))
	{
		InitKeyJudgeTask();
		InitKeyScanTask();
		SetMyHdHaveIniSign(U_SysTask_Key_ID);
	}
	
	selfHdChk_Show_cstChar(U_ROW__TestKey, 0,U_Line_TestKey, 
								"key: No", FALSE);
}


/******************************************************************************
* FUNC: //
******************************************************************************/

void chkHd_Key_Exec(void)
{
U8 mKey;

	Task_ExecKeyTask();
	
	if(bGetPageKey(&mKey))
	{	
		chkHd_Key__show(mKey);
	}
	
}



/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

/******************************************************************************
* FUNC: // chkHd_Led_Ini(); 
*   IN:
*  OUT: 
******************************************************************************/
U32 mLedCheckStep;


void chkHd_Led__Start(void)
{
	
	// LedFuncAllOff();	
	LedFuncAllOn();
	LoadLedFuncToHd();
	
	
	LedCheckStart();
	mLedCheckStep = 0;
}

/******************************************************************************
* FUNC: //
******************************************************************************/
void chkHd_Led_Exit(void)
{
	LedCheckStop();
}

void chkHd_Led_Ini(void)
{
	
	//LED:
	if(!bMyHdHaveIniSign(U_SysTask_Led_ID))
	{
		InitLedTask();
		SetMyHdHaveIniSign(U_SysTask_Led_ID);
	}
	
	chkHd_Led__Start();
}


/******************************************************************************
* FUNC: //
******************************************************************************/

void chkHd_Led_Exec(void)
{
	if(!bMyHdHaveIniSign(U_SysTask_Led_ID))
	{
		return;
	}
	
	
	ExecLedTask();
	if(chkHd_bTmrMsMaxArrived(emChkHd_Led))
	{
		LedCheckNewStep(mLedCheckStep);	
		LoadLedFuncToHd();	
		mLedCheckStep++;
	}
}




/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

/******************************************************************************
* FUNC: // chkHd_PwrChkSwc_Ini(); 
*   IN:
*  OUT: 
******************************************************************************/


/******************************************************************************
* FUNC: //
******************************************************************************/

U32  chkHd_PwrChkSwc__CacuVolt(U32 mAdVal)
{
	return (33*mAdVal*10/0x1000);
}

// IN: mVolt= 电压volt*100.
void chkHd_PwrChkSwc__ShowAdResult(U32 mAdVal)
{
U32 mVolt;

	mVolt = chkHd_PwrChkSwc__CacuVolt(mAdVal);
	
	selfHdChk_Show_cstChar		(U_ROW__TestPwrChkSwc, 
					0,(U_Line_TestPwrChkSwc), "AD:", FALSE);
	selfHdChk_Show_Fig_RightAllign(U_ROW__TestPwrChkSwc, 
					0,(U_Line_TestPwrChkSwc+3), mVolt/100, 1);
	selfHdChk_Show_cstChar		(U_ROW__TestPwrChkSwc, 
					0,(U_Line_TestPwrChkSwc+4), ".", FALSE);
	selfHdChk_Show_Fig_Pre0			(U_ROW__TestPwrChkSwc, 
					0,(U_Line_TestPwrChkSwc+5), mVolt%100, 2);
}


/******************************************************************************
* FUNC: //
******************************************************************************/

void chkHd_PwrChkSwc_Ini(void)
{
	if(!bMyHdHaveIniSign(U_SysTask_PwrChkSwc_ID))
	{
		CanRegi_AD_Init();
		SetMyHdHaveIniSign(U_SysTask_PwrChkSwc_ID);
	}
}


/******************************************************************************
* FUNC: //
******************************************************************************/
static U32 vAdVal;

void chkHd_PwrChkSwc_Exec(void)
{
	if(!bMyHdHaveIniSign(U_SysTask_PwrChkSwc_ID))
	{
		return;
	}
		
	if(chkHd_bTmrMsMaxArrived(emChkHd_PwrChkSwc))
	{
		// Exec_IoLedKeyScan(); -> ExecPwrChkSwcTask();
		vAdVal = chkPwrChkSwc_GetAd();
		chkHd_PwrChkSwc__ShowAdResult(vAdVal);
		
		vAdVal = vAdVal;
	}
}




/******************************************************************************
* FUNC: // chkHd_PwrState_Ini(); 
*   IN:
*  OUT: 
******************************************************************************/

void chkHd_PwrState__ShowResultOne(U8 offsetLine, BOOL bFault)
{
	if(bFault)
		selfHdChk_Show_Fig_Pre0		(U_ROW__TestPwrState, 
					0,(U_Line_TestPwrState+offsetLine), 1, 1);
	else
		selfHdChk_Show_Fig_Pre0		(U_ROW__TestPwrState, 
					0,(U_Line_TestPwrState+offsetLine), 0, 1);
	
}

/******************************************************************************
* FUNC: //
******************************************************************************/
void chkHd_PwrState_Ini(void)
{
	if(!bMyHdHaveIniSign(U_SysTask_PwrState_ID))
	{
		InitPwrStateTask();
		SetMyHdHaveIniSign(U_SysTask_PwrState_ID);
	}
	
	selfHdChk_Show_cstChar		(U_ROW__TestPwrState, 
					0,(U_Line_TestPwrState), "Pwr:0=usua:", FALSE);
}

/******************************************************************************
* FUNC: //
******************************************************************************/


void chkHd_PwrState_Exec(void)
{
	if(!bMyHdHaveIniSign(U_SysTask_PwrState_ID))
	{
		return;
	}
		
	if(!chkHd_bTmrMsMaxArrived(emChkHd_PwrState))
	{
		return;
	}
	
	chkHd_PwrState__ShowResultOne(11, 
				chkPwrState_bFault_HdChk(U_Gpio_Pwr_Main_FUNC));
	chkHd_PwrState__ShowResultOne(12, 
				chkPwrState_bFault_HdChk(U_Gpio_Pwr_Baty_FUNC));
	chkHd_PwrState__ShowResultOne(13, 
				chkPwrState_bFault_HdChk(U_Gpio_Pwr_Link_FUNC));
	
}




/******************************************************************************
* FUNC: // chkHd_Can_Ini(); 
*   IN:
*  OUT: 
******************************************************************************/

static U8 bICanRx = FALSE;
static U8 bECanRx = FALSE;

static U8 vICanRxNum = 0;
static U8 vECanRxNum = 0;

void chkHd_Can__CanRx(U8 canPeriId)
{
	switch(canPeriId)
	{
		case U_iCAN_ID:
			bICanRx = TRUE;
			vICanRxNum++;
			break;
		case U_eCAN_ID:
			bECanRx = TRUE;
			vECanRxNum++;
			break;
		
		default:
			break;
	}
}


/******************************************************************************
* FUNC: //
******************************************************************************/
void chkHd_Can__showRxNum(void)
{
	
	if(bICanRx)
	{
		bICanRx = FALSE;
		selfHdChk_Show_Fig_RightAllign(U_ROW__TestCan, 
						0,(U_Line_TestICan+4), vICanRxNum, 3);		
	}
	if(bECanRx)
	{
		bECanRx = FALSE;
		selfHdChk_Show_Fig_RightAllign(U_ROW__TestCan, 
						0,(U_Line_TestECan+4), vECanRxNum, 3);		
	}
}

/******************************************************************************
* FUNC: //
******************************************************************************/
void chkHd_Can_Ini(void)
{
	// Can_Task_Init();
	
	if(!bMyHdHaveIniSign(U_SysTask_iCan_ID))
	{
		canHd_IorE_Init(U_iCAN_ID);
		SetMyHdHaveIniSign(U_SysTask_iCan_ID);
	}
	if(!bMyHdHaveIniSign(U_SysTask_eCan_ID))
	{
		canHd_IorE_Init(U_eCAN_ID);
		SetMyHdHaveIniSign(U_SysTask_eCan_ID);
	}
	
	
	
	selfHdChk_Show_cstChar(U_ROW__TestCan, 0,U_Line_TestICan, 
					"iRx: 0", FALSE);
	selfHdChk_Show_cstChar(U_ROW__TestCan, 0,U_Line_TestECan, 
					"eRx: 0", FALSE);
		
}

/******************************************************************************
* FUNC: //
******************************************************************************/


/******************************************************************************
* FUNC: //
******************************************************************************/


void chkHd_Can_Exec(void)
{
	
	// Can_Task_Exec();
	/*
	CAN 引脚未设置  不发送；
	CanBps  未设置  不发送；
	无  CAN_ModeConfig() 可以发送；
	能产生中断，CAN0: 0x00AB0080， CAN1：0

	奇怪， ICan_Tx_Alarm() : 只要 vICanTxFrm.id.dWord = 0x0A800028;
		&& iCan和eCan的发送间隔 一个是3000ms ,eCan 3000ms 或 3100ms ,
		就发送异常，7s内iCan和eCan都不产生发送中断；
		而发别的码(参考 ICan_Tx_Alarm(); ) 对定时无要求。
	*/
	#if U_SYS_Test_CanHw == 1
	if(bMyHdHaveIniSign(U_SysTask_iCan_ID))
	{
		if(chkHd_bTmrMsMaxArrived(emChkHd_ICanSend))
		{
			// testSend_iCan();
			// ICan_Tx_Clock();
			ICan_Tx_Alarm(2);
		}
	}
	
	if(bMyHdHaveIniSign(U_SysTask_eCan_ID))
	{
		if(chkHd_bTmrMsMaxArrived(emChkHd_ECanSend))
		{
			// testSend_eCan();
			ECan_Tx_HeartBeat();
		}
	}
	#endif // U_SYS_Test_CanHw
		
	if(chkHd_bTmrMsMaxArrived(emChkHd_CanRx))
	{
		chkHd_Can__showRxNum();
	}
}


/******************************************************************************
* FUNC: // chkHd_Uart_Ini(); 
*   IN:
*  OUT: 
******************************************************************************/


/******************************************************************************
* FUNC: //  函数原型，因为 hw_Uart 现在未用。
******************************************************************************/
void Close_CUart(U8 uartPeriId)
{}
//  Int:
void UartRegi_Int_Enable(U8 uartPeriId)
{}
void UartRegi_Int_Disable(U8 uartPeriId)
{}
void HwUart_SendStart(U8 uartPeriId)
{}

/******************************************************************************
* FUNC: //
******************************************************************************/
#if U_SYS_Test_UartHw == 1
static U8 bUartRx = FALSE;

static U8 vUartRxNum = 0;

void chkHd_Uart__UartRx(void)
{
	bUartRx = TRUE;
	vUartRxNum++;
}

#endif // U_SYS_Test_UartHw

/******************************************************************************
* FUNC: //
******************************************************************************/
void chkHd_Uart_Ini(void)
{
	if(!bMyHdHaveIniSign(U_SysTask_Uart_DownLoad))
	{
		Init_CUart();
		SetMyHdHaveIniSign(U_SysTask_Uart_DownLoad);
	}
	
	
	// Uart_HdAndBuf_Init(U_Uart_Download_ID);
	
	selfHdChk_Show_cstChar(U_ROW__TestUart, 0, U_Line_TestUart, 
						"Uart:", FALSE);
	selfHdChk_Show_Fig_Pre0(U_ROW__TestUart, 0, U_Line_TestUrtFig, 
						0, 3);
	
}



/******************************************************************************
* FUNC: //
******************************************************************************/

static U8 vUartTestTxBuf[8];

void chkHd_Uart_Exec(void)
{
	if(!bMyHdHaveIniSign(U_SysTask_Uart_DownLoad))
	{
		return;
	}
	
	if(chkHd_bTmrMsMaxArrived(emChkHd_UartSend))
	{
#if U_SYS_Test_UartHw == 1
		vUartTestTxBuf[0] = ~0;
		vUartTestTxBuf[1]++;
		// UartHd_LoadTxBuf(U_Uart_Download_ID, 
					// &vUartTestTxBuf[0], 2);
		// UartHd_TxByteStart(U_Uart_Download_ID); 
		UARTSend(_LPC_UART, &vUartTestTxBuf[0], 2);
#endif // U_SYS_Test_UartHw
	}
	
	
	if(chkHd_bTmrMsMaxArrived(emChkHd_UartRx))
	{
		if(bUartRx)
		{
			bUartRx = FALSE;
			selfHdChk_Show_Fig_RightAllign(
						U_ROW__TestUart, 0, U_Line_TestUrtFig, 
						vUartRxNum, 3);
		}
	}
}




/******************************************************************************
* FUNC: // chkHd_RealTmrFosc_Ini(); 
*   IN:
*  OUT: 
******************************************************************************/

TEvtClock_st  stTestClock;
TEvtClock_st  stTestClkRd;


static U32 vTestTickMs = 0;  // 计fosc 的定时器 

/******************************************************************************
* FUNC: // 
******************************************************************************/
void chkHd_RealTmrFosc__showFoscSec(void)
{
U32 m100ms;
U32 mSec;
U32 mMin;
	
	vTestTickMs += chkHd_getTmrMsMax(emChkHd_Fosc);
	if(vTestTickMs >= (100*1000))
	{
		vTestTickMs -= (100*1000);
	}
	
	m100ms = vTestTickMs / 100;
	if((m100ms%10) != 0)
	{
		return;
	}
	
	mSec = m100ms / 10;
	mMin = mSec/60;
	mSec = mSec%60;
	
	
	selfHdChk_Show_Fig_RightAllign(U_ROW__TestFosc, 0, U_Line_TestFosc,
						mMin, 3);
	selfHdChk_Show_cstChar(U_ROW__TestFosc, 0, U_Line_TestFosc+3, 
						"'", FALSE);
	selfHdChk_Show_Fig_Pre0(U_ROW__TestFosc, 0, U_Line_TestFosc+4, 
						mSec, 2);
	
	
	
}


/******************************************************************************
* FUNC: // 若读出无效，写入时钟
******************************************************************************/

BOOL chkHd_RealTmrFosc__SetRealTmr(void)
{
BOOL bResult;

	if(!bMyHdHaveIniSign(U_SysTask_RealTime_ID))
	{
		return FALSE;
	}
	
	if(GetClock(&stTestClkRd))
	{
		return TRUE;
	}
		
	stTestClock.year = 13;
	stTestClock.month = 9;
	stTestClock.day = 25;
	stTestClock.hour = 18;
	stTestClock.min = 42;
	stTestClock.sec = 26;	
	SetClock(&stTestClock);
		
	bResult = GetClock(&stTestClkRd);
		
	return bResult;
	
	// bResult = SS_PCF8563(cPCF8563Stop);
}


/******************************************************************************
* FUNC: // 显示时钟
******************************************************************************/

BOOL chkHd_RealTmrFosc__ShowRealTmr(void)
{
TEvtClock_st *pClock;

	if(GetSysState(U_SysSta_bClockChanged))
	{
		ClrSysState(U_SysSta_bClockChanged);
		
		GetRamTimer(&pClock);
		selfHdChk_Show_EvtTime_YMDHMS(U_ROW__TestRealTmr, 
							U_Line_TestRealTmr, pClock);
	}
	return TRUE;
}

/******************************************************************************
* FUNC: // 
******************************************************************************/
void chkHd_RealTmrFosc_Ini(void)
{
	if(!bMyHdHaveIniSign(U_SysTask_RealTime_ID))
	{
		InitClock();
		
		SetMyHdHaveIniSign(U_SysTask_RealTime_ID);
	}
	chkHd_RealTmrFosc__SetRealTmr();
	
	if(!bMyHdHaveIniSign(U_SysTask_Timer_ID))
	{
		InitTmrTickTask(); // clr all task;		
		MyTickTimer_Init(); // 开定时器
		
		SetMyHdHaveIniSign(U_SysTask_Timer_ID);
	}
}



/******************************************************************************
* FUNC: //
******************************************************************************/


void chkHd_RealTmrFosc_Exec(void)
{
	if(bMyHdHaveIniSign(U_SysTask_RealTime_ID))
	{
		ExecClockTask();
		chkHd_RealTmrFosc__ShowRealTmr();
	}
	

	if(bMyHdHaveIniSign(U_SysTask_Timer_ID))
	{
		if(chkHd_bTmrMsMaxArrived(emChkHd_Fosc))
		{
			chkHd_RealTmrFosc__showFoscSec(); // 显示晶振的秒数；
		}
	}
	
	
	
}


/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

void chkHd_Dog_Ini(void)
{
	if(!bMyHdHaveIniSign(U_SysTask_WatchDog_ID))
	{
		MyDog_Init();
		SetMyHdHaveIniSign(U_SysTask_WatchDog_ID);
	}
}

void chkHd_Dog_Exec(void)
{
	if(bMyHdHaveIniSign(U_SysTask_WatchDog_ID))
	{
		Clear_MyWatchDog();
	}
}

/******************************************************************************
* FUNC: // END 
*   IN:
*  OUT: 
******************************************************************************/

