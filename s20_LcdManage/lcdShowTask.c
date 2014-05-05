#define __lcdShowTask_C__
/******************************************************************************
* @file    lcdShowTask.c
* @author  yx
* @version V1.0
* @date    2013-07-01
* @brief   
* 
******************************************************************************/
#include  "lcdShowTask.h"

#include  "LcdLib_incOut.h"

#include  "tsk_lcd_incIn.h"
#include  "lcdCst_Page.h"
#include  "lcdPg_MainOrEvt.h"
#include  "lcdPg_MainAndEvtChange.h"

#include  "keyBufJdgLib_incOut.h"

#include  "lcdPg_aSchedu.h"

#include  "phIoKeyScan.h"  // key def
#include  "phIoSound.h"
#include  "lcdSub_InputFig.h"
//#include "incFile.h"	


/*================= 常数 ============================================*/

/*================= 结构定义 ========================================*/

/*================= 私有结构变量声明 ================================*/

/*================= 公有函数声明 ====================================*/

/*================= 私有函数声明 ====================================*/

/*=================  ================================================*/
		
/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

void Init_LcdTask(void)
{
	InitLcdShow();
	LcdSw_ClrFullWindow(U_COLOR_BackGroundDefault);
	
	if(!LcdCstPage_CheckCst())
	{
		ShowCstCharRL(0, 0, &cstChar_PageDefError);
		return;
	}
	
	//Page初始化:
	IniPageNum();
	
	// 不显示状态栏 //不是subPage // 不是经由menu进入的page
	Ini_WinBoolState();
	
	ClrPageKey();
	ClrChangeFuncKey();
	
	IniPageSchedu();
}


/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

void Exec_LcdTask(void)
{
PAGEWORD mPageIndex;
	
	if(!GetPageNum(&mPageIndex))
	{
		IniPageSchedu();
	}
	
	
	Exec_MainOrEvtWindow();
	
	lcdTask_JdgKey();
	
	
	// 将buf数据送上lcd.
	// ExecLcdShow();
	ExecTmrArrivedLcdShow();
}


/******************************************************************************
* FUNC: //
******************************************************************************/
BOOL lcdTask_keySilence(U8 mKey)
{
	if(mKey == U_KEY_Silence)
	{
		SoundSetSilence();
		return TRUE;
	}
	else
	{
		return FALSE;
	}
	
}

/******************************************************************************
* FUNC: //
******************************************************************************/
BOOL lcdTask_keyReset(U8 mKey)
{
	if(mKey == U_KEY_Reset)
	{
		SetSysState(U_SysSta_bNeedReset);
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}


/******************************************************************************
* FUNC: //
******************************************************************************/

BOOL lcdTask_keyCheckIng(U8 mKey) // 按键检测
{
	if(bPageIsCheckKey())
	{
		if(mKey < U_KEY_BOARD_MAX)
		{
			KeyCheck_ShowInLcd(mKey);
			SetPageKey(mKey);
			return TRUE;
		}
	}
	return FALSE;
}

/******************************************************************************
* FUNC: //
******************************************************************************/
// 数字和方向键
BOOL lcdTask_keyInputFig(U8 mKey)
{
	
	if(!bFigInputNeed())
	{
		return FALSE;
	}
	
	if(mKey < U_KEY_Fig_Max)
	{
		FigInput_newFig(mKey);
		return TRUE;
	}
	else
	{
		switch(mKey)
		{
			case U_KEY_Up:
				FigInput_newUp();
				return TRUE;
			
			case U_KEY_Down:
				FigInput_newDown();
				return TRUE;
			
			case U_KEY_Left:
				FigInput_CursorLeft();
				return TRUE;
			
			case U_KEY_Right:
				FigInput_CursorRight();
				return TRUE;
								
			default:
				break;
		}
	}
		
	return FALSE;
		
}


/******************************************************************************
* FUNC: //
******************************************************************************/

BOOL lcdTask_keyEsc(U8 mKey)
{
	if((mKey == U_KEY_Esc))
	{
		PageEsc();
		return TRUE;
	}
	
	else
	{
		return FALSE;
	}
	
}


/******************************************************************************
* FUNC: //
******************************************************************************/
BOOL lcdTask_keyEnter(U8 mKey)
{
	if(mKey == U_KEY_Enter)
	{
		if(bPageIsMCycle())
		{
			PgExit_andMenuEntry();
			return TRUE;
		}
	}
	return FALSE;
}

/******************************************************************************
* FUNC: //
******************************************************************************/

BOOL lcdTask_keyReturn(U8 mKey)
{
	if((mKey == U_KEY_Star) || (mKey == U_KEY_Pound))
	{
		if(bWinBoolState(U_WIN_NeedKey_StarPound_Sta))
		{
			return FALSE;
		}
		else
		{
			mKey = U_KEY_Return;
		}
	}
	else if(mKey == U_KEY_Left)
	{
		if(!bFigInputNeed())
		{
			if(!bWinBoolState(U_WIN_KeyLR_UseforPageUpDown_Sta))  
			{
				mKey = U_KEY_Return;
			}
		}
	}
	
	if(mKey == U_KEY_Return)
	{
		PageReturn();
		return TRUE;
	}	
	else
	{
		return FALSE;
	}
}

/******************************************************************************
* FUNC: // 判断按键。 emKey 
*   IN:
*  OUT: 
* 其slave函数  OUT: TRUE=已处理。
******************************************************************************/

void lcdTask_JdgKey(void)
{
U8 key;
PAGEWORD mPageIndex;
	
	if(GetKeyValue(&key))
	{
		LcdPageEvt_HaveUserKey_ForbidAutoTurn();
	}
	else
	{
		if(!bGetChangeFuncKey_andClr(&key))
		{
			GetPageNum(&mPageIndex);
			LcdPage_function_Usual(mPageIndex);
			return;
		}
	}
	
	
	// 有效按键：
	if(lcdTask_keyCheckIng(key)) // 按键检测
	{
		return;
	}
	if(lcdTask_keyReset(key))
	{
		return;
	}
	if(lcdTask_keySilence(key))
	{
		return;
	}
	if(lcdTask_keyEsc(key))
	{
		return;
	}
	if(lcdTask_keyReturn(key))
	{
		return;
	}
	if(lcdTask_keyEnter(key))
	{
		return;
	}
	
	if(lcdTask_keyInputFig(key)) // 数字和方向键
	{
		SetPageKey(key);
		GetPageNum(&mPageIndex);
		LcdPage_function_Usual(mPageIndex);	
		
		return;
	}
	
	SetPageKey(key);
	GetPageNum(&mPageIndex);
	LcdPage_function_Usual(mPageIndex);	
	
}

/******************************************************************************
* FUNC: // END
*   IN:
*  OUT: 
******************************************************************************/
