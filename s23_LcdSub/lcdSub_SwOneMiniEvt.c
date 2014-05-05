#define __lcdSub_SwOneMiniEvt_C__
/******************************************************************************
* @file    lcdSub_SwOneMiniEvt.c
* @author  yx
* @version V1.0
* @date    2013-10-18
* @brief   
* 
******************************************************************************/
#include  "lcdSub_SwOneMiniEvt.h"

#include  "lcdSub_ModeTextFig.h"

#include  "lcdCst_PgStrEvtThing.h"

// #include  "lcdSub_SwDev.h"
extern U8 sw_Dete_Char(TDev_un *pDev);
// #include  "lcdSub_SwOneEvt.h"
extern void sw_sequTotal_Fig(U32 fig, U8 bitTotal, U8 **pRtnFigStr);


/*================= 常数 ============================================*/

/*================= 结构定义 ========================================*/

/*================= 私有结构变量声明 ================================*/
static TYPE_LCD_XY  vPixRow;
static TYPE_LCD_XY  vPixLine;

/*================= 公有函数声明 ====================================*/

/*================= 私有函数声明 ====================================*/

/*=================  ================================================*/
		
/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

void Show_OneMiniAlarm(U8 winItem, EVTWORD sequ,
									TEvtAlarm_st *m_pAlarm)
{
	get_pix_x_y_mini(winItem);
	
	IniTextBuf(U_ShowUseLib_88orCn_88Ascii);
	sw_sequ_mini(sequ);
	sw_dev_mini(&m_pAlarm->stPos.unDev);
	ShowTxtBufPix(vPixRow, vPixLine);
}


void Show_OneMiniSpvs(U8 winItem, EVTWORD sequ,
							TEvtSpvs_st *m_pSpvs)
{
	get_pix_x_y_mini(winItem);
	
	IniTextBuf(U_ShowUseLib_88orCn_88Ascii);
	sw_sequ_mini(sequ);
	sw_dev_mini(&m_pSpvs->stPos.unDev);
	ShowTxtBufPix(vPixRow, vPixLine);
}


void Show_OneMiniLink(U8 winItem, EVTWORD sequ,
							TEvtLink_st *m_pLink)
{
	get_pix_x_y_mini(winItem);
	
	IniTextBuf(U_ShowUseLib_88orCn_88Ascii);
	sw_sequ_mini(sequ);
	sw_dev_mini(&m_pLink->stPos.unDev);
	sw_LinkEvt_mini(m_pLink->thing);
	ShowTxtBufPix(vPixRow, vPixLine);

}

void Show_OneMiniExtg(U8 winItem, EVTWORD sequ,
							TEvtExtg_st *m_pExtg)
{
	get_pix_x_y_mini(winItem);
	
	IniTextBuf(U_ShowUseLib_88orCn_88Ascii);
	
	sw_sequ_mini(sequ);
	sw_dev_mini(&m_pExtg->stPos.unDev);
	sw_ExtgEvt_mini(m_pExtg->thing);
	
	ShowTxtBufPix(vPixRow, vPixLine);

}

void Show_OneMiniFault(U8 winItem, EVTWORD sequ,
							TEvtFault_st *m_pFault)
{
	get_pix_x_y_mini(winItem);
	
	IniTextBuf(U_ShowUseLib_88orCn_88Ascii);
	sw_sequ_mini(sequ);
	sw_dev_mini(&m_pFault->stPos.unDev);
	ShowTxtBufPix(vPixRow, vPixLine);
}

void Show_OneMiniDsab(U8 winItem, EVTWORD sequ,
							TEvtDsab_st *m_pDsab)
{
	get_pix_x_y_mini(winItem);
	
	IniTextBuf(U_ShowUseLib_88orCn_88Ascii);
	sw_sequ_mini(sequ);
	sw_dev_mini(&m_pDsab->stPos.unDev);
	ShowTxtBufPix(vPixRow, vPixLine);
}


/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 

64-12=52;  52/8=6;    
需要 < U_OneScr_DevBuf_MAX , def in lib = 10.
******************************************************************************/

static void get_pix_x_y_mini(U8 winItem)
{
U8 mRow;
	if(winItem >= U_SHOW_MINI_EVENT_ITEM_MAX)
	{
		vPixRow = ~0; vPixLine = ~0;
		return;
	}
	
	mRow = (winItem % 5);
	vPixRow = 16+ (mRow*9);
	
	if(winItem < 5)
	{
		vPixLine = 0;
	}
	else
	{
		vPixLine = (192/2);
	}
}

//OUT: 显示字符总数
// 符号形式 显示 回路现场部件:
static void sw_dev_mini(TDev_un *pDev)
{
	sw_Dete_Char(pDev);
	AddCodeStrToTextBuf(" ");
}

static void sw_sequ_mini(EVTWORD sequ)
{
U8 *pFigStr;
	
	sw_sequTotal_Fig(sequ, U_EvtMini_TOTAL_FIG_BIT_TOTAL, &pFigStr);
	AddToTextBuf(pFigStr);
	AddCodeStrToTextBuf(":");
}




static void sw_LinkEvt_mini(U8 thing)
{
const TCstChar_st *pCstChar;
	
	GetCstChar_EvtLinkModu(thing, &pCstChar);
	AddToTextBuf((U8*)(pCstChar->pEn));
	
}

static void sw_ExtgEvt_mini(U8 thing)
{
const TCstChar_st *pCstChar;
	
	GetCstChar_EvtExtg(thing, &pCstChar);
	AddToTextBuf((U8*)(pCstChar->pEn));
	
}

/******************************************************************************
* FUNC: // END
*   IN:
*  OUT: 
******************************************************************************/
