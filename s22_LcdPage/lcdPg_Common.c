#define __lcdPg_Common_C__
/******************************************************************************
* @file    lcdPg_Common.c
* @author  yx
* @version V1.0
* @date    2013-07-01
* @brief   
* 
******************************************************************************/
#include  "lcdPg_Common.h"


#include  "tsk_lcd_incIn.h"
#include  "lcdSub_ModeTextFig.h"

#include  "strFlsItmStruct.h"
#include  "Save_Item_incOut.h"
#include  "phClock.h"
//#include "incFile.h"	


/*================= ���� ============================================*/

/*================= �ṹ���� ========================================*/

/*================= ˽�нṹ�������� ================================*/

/*================= ���к������� ====================================*/

/*================= ˽�к������� ====================================*/

/*=================  ================================================*/
		
/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

// ��ʾ �б䶯�� �Զ� �ֶ���
void ShowStr_AutoManuChangeState(
				TYPE_LCD_RL mRow, TYPE_LCD_RL mLine)
{
	if(GetSysState(U_SysSta_bAutoManuChanged))
	{
		ClrSysState(U_SysSta_bAutoManuChanged);
			
		ShowStr_AutoManuNowState(mRow, mLine);
	}
}

// ��ʾ ��ǰ �Զ� �ֶ���
void ShowStr_AutoManuNowState(
				TYPE_LCD_RL mRow, TYPE_LCD_RL mLine)
{
TFlsSysSet_un *pSysSet;

		pSysSet = pGetFlsSysSet();
		
		ShowStr_AutoManuState( mRow, mLine,
					pSysSet->stSet.runAuto, 
					pSysSet->stSet.runManu
					);
}


// ��ʾ para �Զ� �ֶ���
void ShowStr_AutoManuState(
				TYPE_LCD_RL mRow, TYPE_LCD_RL mLine,
				BOOL bAutoAllow, BOOL bManuAllow)
{
	ShowStr_Auto_Manu(mRow, mLine);
	ShowStr_Allow_Forbid(mRow, mLine+5, bAutoAllow);
	ShowStr_Allow_Forbid(mRow, mLine+10+5, bManuAllow);
}



void ShowStr_Auto_Manu(TYPE_LCD_RL mRow, TYPE_LCD_RL mLine)
{
	ShowCstCharRL(mRow, mLine, &cstChar_Auto);
	ShowCstCharRL(mRow, mLine+10, &cstChar_Manu);
}

void ShowStr_Allow_Forbid(TYPE_LCD_RL mRow, TYPE_LCD_RL mLine,
						 BOOL bAllow)
{
	if(bAllow)
	{
		ShowCstCharRL(mRow, mLine, &cstChar_Allow);
	}
	else
	{
		ShowCstCharRL(mRow, mLine, &cstChar_Forbid);
	}
}

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
void Show_Clock(TYPE_LCD_RL mRow, TYPE_LCD_RL mLine)
{
TEvtClock_st *pClock;

	if(GetSysState(U_SysSta_bClockChanged))
	{
		ClrSysState(U_SysSta_bClockChanged);
		
		GetRamTimer(&pClock);
		Show_SysTime_YMDHMS(mRow, mLine, pClock);
	}
}



/******************************************************************************
* FUNC: //
******************************************************************************/



/******************************************************************************
* FUNC: // END
*   IN:
*  OUT: 
******************************************************************************/
