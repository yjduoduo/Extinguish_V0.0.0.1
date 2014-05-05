#define __sysPanel_C__
/******************************************************************************
* @file    sysPanel.c
* @author  yx
* @version V1.2
* @date    2013.10.24
* @brief   系统内的unit定义
* 
* V1.1, 增加函数  TPanelSequ_st *pGetPanelStr(U8 pnType);  2013.8.21
* V1.0, 2013.7.1
******************************************************************************/
#include  "sysPanel.h"

#include  "canFrame.h"
#include  "sysDef.h"
#include  "codeComm.h"
#include  "phClock.h"
#include  "tmrTick.h"

#include  "can11sPrtl_iCan.h"
#include  "evt_Buf_incOut.h"

//#include "incFile.h"	


/*================= 常数 ============================================*/

/*================= 结构定义 ========================================*/

typedef struct{
	// inLine等排序, 只要不重复就可以;  // U8 mPnRamSequ;
	U8 sequStart;  // 1号存在这里
	U8 sequEnd;		//本身是MAX, 是next的sequStart。
	
	U8 pnMax;
	U8 pnCanSign;  // 板卡类型, can协议里定义的。
}TPanelSequ_st;

/*================= 私有结构变量声明 ================================*/
static U8 vInLineS;
static U8 vOutLineS;
/*================= 私有结构变量声明 ================================*/
#define U_RAM_SEQU_DEFAULT   (U_PANEL_TOTAL_SEQU_MAX - 1)

const TPanelSequ_st cPanelSequ[U_PN_TYPE_MAX] = 
{
//	sequStart	sequEnd		pnMax		,      pnCanSign
	{0x00,		0x00,		U_MACHINE_MAX, U_PN_Machine_TYPE 	}, //U_PN_Machine_TYPE
		
	{0x01,		0x09,		(0x04+1), U_PN_Loop_TYPE 	}, //U_PN_Loop_TYPE
	{0x11,		0x21,		(0x10+1), U_PN_Opea_TYPE 	}, //U_PN_Opea_TYPE
	{0x21,		0x61,		(0x40+1), U_PN_Drt_TYPE	}, //U_PN_Drt_TYPE
	{0x61,		0xA1,		(0x40+1), U_PN_Bus_TYPE	}, //U_PN_Bus_TYPE
	{0xA1,		0xD1,		(0x04+1), U_PN_Extg_TYPE	}, //U_PN_Extg_TYPE
	{0xD1,		0xD9,		(0x08+1), U_PN_Broad_TYPE	}, //U_PN_Broad_TYPE
	{0xD9,		0xE1,		(0x08+1), U_PN_Power_TYPE	}, //U_PN_Power_TYPE
	{0xE1,		0xE9,		(0x08+1), U_PN_Other_TYPE  	}, //U_PN_Other_TYPE
};
	
/*================= 公有函数声明 ====================================*/

/*================= 私有函数声明 ====================================*/
static BOOL getPanelStr(U8 pnType, const TPanelSequ_st **pPnStr);

/*=================  ================================================*/
		
/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

static BOOL getPanelStr(U8 pnType, const TPanelSequ_st **pPnStr)
{
U8 ii;

	for(ii=0; ii<U_PN_TYPE_MAX; ii++)
	{
		if(cPanelSequ[ii].pnCanSign == pnType)
		{
			break;
		}
	}
	if(ii >= U_PN_TYPE_MAX)
	{
		return FALSE;
	}
	else
	{
		*pPnStr = &cPanelSequ[ii];
		return TRUE;
	}
	
}

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

//  IN: mCanIdSrc: 0~
// OUT: mPnRamSequ: 0 ~ U_PANEL_TOTAL_SEQU_MAX;
BOOL canIdSourse_to_pnRamSequ(U8 mCanIdSrc,
							U8 *pRtnPnRamSequ)
{
U8 pnType;
U8 pnSequ;
	
	// 根据源地址，计算panel:
	if(!bICan11sIdSourse_ToPnTypeSequ(mCanIdSrc, &pnType, &pnSequ))
	{
		*pRtnPnRamSequ = U_RAM_SEQU_DEFAULT;
		return FALSE;
	}
	
	//  IN: *pRtnType: emPanelType;  *pRtnSequ: 1~
	// OUT: mPnRamSequ: 0 ~ U_PANEL_TOTAL_SEQU_MAX;
	return pnTypeSequ_to_pnRamSequ(
							pnType, pnSequ,
							pRtnPnRamSequ);
	
}

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
//  IN: pnType: emPanelType;  pnSequ: 1~
// OUT: mPnRamSequ: 0 ~ U_PANEL_TOTAL_SEQU_MAX;
BOOL pnTypeSequ_to_pnRamSequ(U8 pnType, U8 pnSequ,
							U8 *pRtnPnRamSequ)
{
const TPanelSequ_st *pPnStr;

	if(!getPanelStr(pnType, &pPnStr))
	{
		*pRtnPnRamSequ = U_RAM_SEQU_DEFAULT;
		return FALSE;
	}
	
	if(pnSequ == 0)
	{
		pnSequ = 1;
	}
	if(pnSequ >= pPnStr->pnMax)
	{
		*pRtnPnRamSequ = U_RAM_SEQU_DEFAULT;
		return FALSE;
	}
	else
	{
		*pRtnPnRamSequ = pPnStr->sequStart + (pnSequ - 1);
		return TRUE;
	}
}


//  IN: mPnRamSequ: 0 ~ U_PANEL_TOTAL_SEQU_MAX;
// OUT: *pRtnType: emPanelType;  *pRtnSequ: 1~
BOOL pnRamSequ_to_pnTypeSequ(U8 mPnRamSequ, 
							U8 *pRtnType, U8 *pRtnSequ)
{
U8 pnType;
U8 ii;
U8 pnSequ;

	for(ii=0; ii<U_PN_TYPE_MAX; ii++)
	{
		if( (mPnRamSequ >= cPanelSequ[ii].sequStart)
		  &&(mPnRamSequ <  cPanelSequ[ii].sequEnd)
		  )
		{
			break;
		}
	}
	if(ii < U_PN_TYPE_MAX)
	{
		pnType = cPanelSequ[ii].pnCanSign;
		
		*pRtnType = pnType;
		pnSequ = (mPnRamSequ - cPanelSequ[ii].sequStart) + 1;
		if(pnSequ >= cPanelSequ[ii].pnMax)
		{
			pnSequ = cPanelSequ[ii].pnMax;
		}
		*pRtnSequ = pnSequ;
		return TRUE;
	}
	
	return FALSE;
}




/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

BOOL bExtgUnit_Regist(U8 mExtgUnit) //已登记
{
U8 mPnRamSequ;

	//  IN: *pRtnType: emPanelType;  *pRtnSequ: 1~
	// OUT: mPnRamSequ: 0 ~ U_PANEL_TOTAL_SEQU_MAX;
	if(!pnTypeSequ_to_pnRamSequ(U_PN_Extg_TYPE, mExtgUnit,
								&mPnRamSequ))
	{
		return FALSE;
	}
	return vPanel[mPnRamSequ].bRegisted;
}

BOOL bExtgUnit_Inline(U8 mExtgUnit) // 在线
{
U8 mPnRamSequ;

	//  IN: *pRtnType: emPanelType;  *pRtnSequ: 1~
	// OUT: mPnRamSequ: 0 ~ U_PANEL_TOTAL_SEQU_MAX;
	if(!pnTypeSequ_to_pnRamSequ(U_PN_Extg_TYPE, mExtgUnit,
								&mPnRamSequ))
	{
		return FALSE;
	}
	return (!vPanel[mPnRamSequ].bOutLine);
}


U8 GetExtgUnitMax(void)
{
U8 mPnMax;

	if(!GetPanelUnitMax(U_PN_Extg_TYPE, &mPnMax))
	{
		return 0;
	}
	return mPnMax;
	
}



/******************************************************************************
* NAME: 
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
// MAX = 允许的数字+1；
BOOL GetPanelUnitMax(U8 pnType, U8 *pPnMax)
{
const TPanelSequ_st *pPnStr;
	
	if(!getPanelStr(pnType, &pPnStr))
	{
		return FALSE;
	}
	*pPnMax = pPnStr->pnMax;
	return TRUE;
}


// 判断 单元号是否有效：
// IN: pnType: emPanelType;  
// IN: mSequStart:有关pange的计数，1号panel对应的数；
// IN: mSequNow:  有关pange的计数，当前数；
BOOL bSequValid_RelatePanel(U8 pnType, U8 mSequPn1Start, U8 mSequNow)
{
U8 mPnMax;
U8 pnSequ;

	// MAX = 允许的数字+1；
	if(!GetPanelUnitMax(pnType, &mPnMax))
	{
		return FALSE;
	}
	if(mSequNow < mSequPn1Start)
	{
		return FALSE;
	}
	
	pnSequ = (mSequNow - mSequPn1Start) + 1;
	
	return (pnSequ < mPnMax);
}

/******************************************************************************
* NAME: 
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
U8 bPnSequIsValid(U8 pnType, U8 pnSequ)
{
	if(pnType >= U_PN_TYPE_MAX)
	{
		return FALSE;
	}
	
	if( (pnSequ >= cPanelSequ[pnType].pnMax)
	  ||(pnSequ == 0)
	  )
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}


BOOL bPnTypeIsValid(U8 pnType) //emPanelType
{
	if(pnType < U_PN_TYPE_MAX)
	{
		return TRUE;
	}
	return FALSE;
}


/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
U8 GetPanelType_Loop(void)
{
	return U_PN_Loop_TYPE;
}
U8 GetPanelType_Extg(void)
{
	return U_PN_Extg_TYPE;
}
U8 GetPanelType_Drt(void)
{
	return U_PN_Drt_TYPE;
}
/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
void Panel_Regist(U8 mPnRamSequ, BOOL bRegisted)
{
	if(mPnRamSequ < U_PANEL_TOTAL_SEQU_MAX)
	{
		vPanel[mPnRamSequ].bRegisted = bRegisted;
	}
}


/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

void Panel_inLine_Inc(U8 mCanIdSrc)
{
U8 mPnRamSequ;

	if(!canIdSourse_to_pnRamSequ(mCanIdSrc, &mPnRamSequ))
	{
		return;
	}
	
	if(mPnRamSequ < U_PANEL_TOTAL_SEQU_MAX)
	{
		if(vPanel[mPnRamSequ].inLineNum < U_PANEL_INLINE_NUM_TOP)
		{
			vPanel[mPnRamSequ].inLineNum++;
		}
	}
}

void Panel_inLine_ClrOne(U8 mPnRamSequ)
{
	if(mPnRamSequ < U_PANEL_TOTAL_SEQU_MAX)
	{
		vPanel[mPnRamSequ].inLineNum = 0;
	}
}

void Panel_inLine_ClrAll(void)
{
U8 mPnRamSequ;

	for(mPnRamSequ=0; mPnRamSequ<U_PANEL_TOTAL_SEQU_MAX; mPnRamSequ++)
	{
		vPanel[mPnRamSequ].inLineNum = 0;
	}
}


/******************************************************************************
* FUNC: //
******************************************************************************/

void PanelState_Init(void)
{
U32 num = sizeof(vPanel);
U8 mPnRamSequ;

	vInLineS = 0;
	vOutLineS = 0;
	ClrRamIs00((U8*)(&vPanel[0]), num); //全清00 
	
	SetTmrTickTask(TASK_CheckPanelInLine, TMR_CheckPanelInLine);
	
	pnTypeSequ_to_pnRamSequ(U_PN_Loop_TYPE, 1,
							&mPnRamSequ);
	Panel_Regist(mPnRamSequ, TRUE);
	
	pnTypeSequ_to_pnRamSequ(U_PN_Loop_TYPE, 2,
							&mPnRamSequ);
	Panel_Regist(mPnRamSequ, TRUE);
}

/******************************************************************************
* FUNC: //
******************************************************************************/

void Panel_inLine_Check(void)
{
U8 mPnRamSequ;

	if(!GetTickTaskStatus(TASK_CheckPanelInLine))
	{
		return;
	}
	vInLineS++;
	vOutLineS++;
	
	// 检查恢复：
	if(vInLineS >= U_PN_InLine_Interval_InLine_Second)
	{
		vInLineS = 0;
		for(mPnRamSequ=0; mPnRamSequ<U_PANEL_TOTAL_SEQU_MAX; mPnRamSequ++)
		{
			if(!vPanel[mPnRamSequ].bOutLine)
			{
				continue;
			}
			
			if(vPanel[mPnRamSequ].inLineNum >= U_PANEL_InLine_NUM_MIN)
			{
				if(panel_inLine_ResultOk(mPnRamSequ, TRUE))
				{
					vPanel[mPnRamSequ].bOutLine = FALSE;
				}
			}
			// 不清数
		}
	}
	
	
	// 检查断线：
	if(vOutLineS < U_PN_InLine_Interval_OutLine_Second)
	{
		return;
	}
	
	vOutLineS = 0;
	vInLineS = 0;
	
	for(mPnRamSequ=0; mPnRamSequ<U_PANEL_TOTAL_SEQU_MAX; mPnRamSequ++)
	{
		if(!vPanel[mPnRamSequ].bRegisted)
		{
			continue;
		}
		
		  
		if( (!vPanel[mPnRamSequ].bOutLine) // current: 正常
		  &&(vPanel[mPnRamSequ].inLineNum < U_PANEL_OutLine_NUM_MIN))
		{
			if(panel_inLine_ResultOk(mPnRamSequ, FALSE))
			{
				vPanel[mPnRamSequ].bOutLine = TRUE;
			}
		}
		else if( (vPanel[mPnRamSequ].bOutLine) // current: 掉线
		  &&(vPanel[mPnRamSequ].inLineNum >= U_PANEL_InLine_NUM_MIN))
		{
			if(panel_inLine_ResultOk(mPnRamSequ, TRUE))
			{
				vPanel[mPnRamSequ].bOutLine = FALSE;
			}
		}
		
		vPanel[mPnRamSequ].inLineNum = 0;
		
	}
	
}




void Panel_inLine_Check1(void)
{
U8 mPnRamSequ;

	if(!GetTickTaskStatus(TASK_CheckPanelInLine))
	{
		return;
	}
	vInLineS++;
	vOutLineS++;
	
	for(mPnRamSequ=0; mPnRamSequ<U_PANEL_TOTAL_SEQU_MAX; mPnRamSequ++)
	{
		if(!vPanel[mPnRamSequ].bRegisted)
		{
			continue;
		}
		if((vPanel[mPnRamSequ].inLineNum < U_PANEL_OutLine_NUM_MIN)
		  &&(!vPanel[mPnRamSequ].bOutLine) )
		{
			if(panel_inLine_ResultOk(mPnRamSequ, FALSE))
			{
				vPanel[mPnRamSequ].bOutLine = TRUE;
			}
		}
		else if((vPanel[mPnRamSequ].inLineNum >= U_PANEL_OutLine_NUM_MIN)
		  &&(vPanel[mPnRamSequ].bOutLine) )
		{
			if(panel_inLine_ResultOk(mPnRamSequ, TRUE))
			{
				vPanel[mPnRamSequ].bOutLine = FALSE;
			}
		}
		
		vPanel[mPnRamSequ].inLineNum = 0;
	}
	
}

/******************************************************************************
* FUNC: //
******************************************************************************/

BOOL panel_inLine_ResultOk(U8 mPnRamSequ, U8 bOk)
{
U8 pnType;
U8 pnSequ;
TEvtTrans_st  stEvt;

	DevSetInvalid(&stEvt.unDev);
	
	
	//  IN: mPnRamSequ: 0 ~ U_PANEL_TOTAL_SEQU_MAX;
	// OUT: *pRtnType: emPanelType;  *pRtnSequ: 1~
	if(!pnRamSequ_to_pnTypeSequ(mPnRamSequ, 
								&pnType, &pnSequ))
	{
		return FALSE;
	}
	
	if(!BuildToDev_Me_Panel(pnType, pnSequ, &stEvt.unDev))
	{
		return FALSE;
	}
	stEvt.type = ~0;
	
	GetRamEvtTimer(&stEvt.evtClock);
	
	if(bOk)
	{
		stEvt.thing = U_FaultRstr_EVT;
	}
	else
	{
		stEvt.thing = U_Fault_EVT;
	}
	
	return (Buf_Fault(&stEvt));
}


/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

void Panel_Vesion_Rx(U8 pnType, U8 pnSequ, 
					U8 versionMain, U8 versionAux)
{
U8 mPnRamSequ;

	//  IN: *pRtnType: emPanelType;  *pRtnSequ: 1~
	// OUT: mPnRamSequ: 0 ~ U_PANEL_TOTAL_SEQU_MAX;
	if(!pnTypeSequ_to_pnRamSequ(pnType, pnSequ,
								&mPnRamSequ))
	{
		return;
	}
	
	vPanel[mPnRamSequ].bHaveVersion = TRUE;
	vPanel[mPnRamSequ].pnVersionMain = versionMain;
	vPanel[mPnRamSequ].pnVersionAux = versionAux;
		
}


BOOL Panel_Vesion_Get(U8 pnType, U8 pnSequ, 
					U8 *pVersionMain, U8 *pVersionAux)
{
U8 mPnRamSequ;

	//  IN: *pRtnType: emPanelType;  *pRtnSequ: 1~
	// OUT: mPnRamSequ: 0 ~ U_PANEL_TOTAL_SEQU_MAX;
	if(!pnTypeSequ_to_pnRamSequ(pnType, pnSequ,
								&mPnRamSequ))
	{
		return FALSE;
	}
	
	if(!vPanel[mPnRamSequ].bHaveVersion)
	{
		return FALSE;
	}
	
	*pVersionMain = vPanel[mPnRamSequ].pnVersionMain;
	*pVersionAux  = vPanel[mPnRamSequ].pnVersionAux;
	return TRUE;
}


void Panel_Vesion_ClrOne(U8 pnType, U8 pnSequ)
{
U8 mPnRamSequ;

	//  IN: *pRtnType: emPanelType;  *pRtnSequ: 1~
	// OUT: mPnRamSequ: 0 ~ U_PANEL_TOTAL_SEQU_MAX;
	if(!pnTypeSequ_to_pnRamSequ(pnType, pnSequ,
								&mPnRamSequ))
	{
		return;
	}
	
	vPanel[mPnRamSequ].bHaveVersion = FALSE;
}

void Panel_Vesion_ClrAll(void)
{
U8 mPnRamSequ;

	for(mPnRamSequ=0; mPnRamSequ<U_PANEL_TOTAL_SEQU_MAX; mPnRamSequ++)
	{
		vPanel[mPnRamSequ].bHaveVersion = FALSE;
	}
	
}

/******************************************************************************
* FUNC: // END 
*   IN:
*  OUT: 
******************************************************************************/

