#define __lcdSub_Flash_C__
/******************************************************************************
* @file    lcdSub_Flash.c
* @author  yx
* @version V1.0

* @date    2012-01-05
* @brief   控制flash写时禁止读
* 
******************************************************************************/
#include  "lcdSub_Flash.h"
#include  "prjBool.h"

#include  "Save_Manage_incOut.h"

//#include "incFile.h"	


/*================= 常数 ============================================*/

/*================= 结构定义 ========================================*/

/*================= 私有结构变量声明 ================================*/
typedef struct{
	BOOL bWaitIng;
	U8 mFlsItem;
	U8 mPart;
}TWaitForRd_st;
static TWaitForRd_st stWaitForRd;

/*================= 公有函数声明 ====================================*/

/*================= 私有函数声明 ====================================*/

/*=================  ================================================*/
		
/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

void LcdSubFls_Clr_WaitFor_RdAllow(U8 mFlsItem, U8 mPart)
{
	stWaitForRd.bWaitIng = FALSE;
	stWaitForRd.mFlsItem = ~0;
	stWaitForRd.mPart = ~0;
}

void LcdSubFls_Set_WaitFor_RdAllow(U8 mFlsItem, U8 mPart)
{
	stWaitForRd.bWaitIng = TRUE;
	stWaitForRd.mFlsItem = mFlsItem;
	stWaitForRd.mPart = mPart;
}

BOOL bLcdSubFls_isWaitIng(void)
{
	return stWaitForRd.bWaitIng;
}


// if 允许读，waitRd flsItem:
BOOL LcdSubFls_RdAllow(void)
{
	return FlsRdFlsItem_PartN_ChipAllow(
			stWaitForRd.mFlsItem, 
			stWaitForRd.mPart
			);
}

/******************************************************************************
* FUNC: //
******************************************************************************/



/******************************************************************************
* FUNC: // END
*   IN:
*  OUT: 
******************************************************************************/
