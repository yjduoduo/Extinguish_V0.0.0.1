#define __sim_saveHist_C__
/******************************************************************************
* @file    sim_saveHist.c
* @author  yx
* @version V1.0
* @date    2013-07-09
* @brief   ���ԣ�saveHistPoint.c, historyWrite.c, 2013.7.8
				historyWrBuf.c
		ģ�����¼� -> historyWrBuf.c, ���� historyWrite.c д��ʷ��¼��ָ�롣
* 
******************************************************************************/
#include  "sim_saveHist.h"


#include  "incSysCommon.h"
#include  "evt_Buf_incOut.h"

#include  "strFlsAdrDef.h"
#include  "flsAdrCalculate.h"

#include  "phSaveHist_incIn.h"

//#include "incFile.h"	

#if U_SYS_Test_Flash_Hist == 1
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


static void init_stAdr(void)
{
U8 mFlsItem;
U8 mHistPart;
U8 mPointPart;

	for(mHistPart=0; mHistPart<U_SIM_histPart_MAX; mHistPart++)
	{
		mFlsItem = getFlsItem_hist(U_Sim_FlsHistCls);
		getFlsItem_Addr(mFlsItem, mHistPart, &vSim_HistAdr[mHistPart]);
		
		mFlsItem = getFlsItem_hstPoint(U_Sim_FlsHistCls, mHistPart);
		for(mPointPart=0; mPointPart<U_SIM_pointPart_MAX; mPointPart++)
		{
			getFlsItem_Addr(mFlsItem, mPointPart, 
						   &vSim_PointAdr[mHistPart][mPointPart]
						   );
		}
	}
	
}


/******************************************************************************
* FUNC: //
*   IN:
*  OUT:  
	//����ֵ����ģ��flash��ֵ��
******************************************************************************/
// static void init_HeadEnd(void)
// {
	// init_HeadEnd_sectEndOnly_1_item();
// }

/******************************************************************************
* FUNC: // ��¼��ָ�붼ֻ��1���գ�����sector ĩβ��
*   IN:
*  OUT:  
******************************************************************************/
static void init_HeadEnd_6Cls_sectEndOnly_1_item(void)
{
U8 mHistCls;
U8 mHistPart;

U8 mFlsItem;
U8 mPointPart;
TFlsItemAddr stAdr;

	for(mHistCls=0; mHistCls<U_HIST_CLASS_MAX; mHistCls++)
	{
				//��ʷ��¼
		for(mHistPart=0; mHistPart<U_SIM_histPart_MAX; mHistPart++)
		{
			mFlsItem = getFlsItem_hist(mHistCls);
			getFlsItem_Addr(mFlsItem, mHistPart, &stAdr);
			SetFlsQueHeadAdr(mFlsItem, mHistPart, stAdr.adrS);
			SetFlsQueEndAdr (mFlsItem, mHistPart, stAdr.adrE - U_FLS_1HISTORY_BYTE_MAX);
			
			//ָ�룺
			mFlsItem = getFlsItem_hstPoint(mHistCls, mHistPart);
			for(mPointPart=0; mPointPart<U_SIM_pointPart_MAX; mPointPart++)
			{
				getFlsItem_Addr(mFlsItem, mPointPart, &stAdr);
				SetFlsQueHeadAdr(mFlsItem, mPointPart, stAdr.adrS);
				SetFlsQueEndAdr (mFlsItem, mPointPart, stAdr.adrE - U_FLS_1HistPoint_BYTE_MAX);
			}
		}

	}
	
}

static void init_HeadEnd_sectEndOnly_1_item(void)
{
U8 mFlsItem;
U8 mHistPart;
U8 mPointPart;
TSimHistFlash_st  *pStr;

	//��ʷ��¼
	for(mHistPart=0; mHistPart<U_SIM_histPart_MAX; mHistPart++)
	{
		mFlsItem = getFlsItem_hist(U_Sim_FlsHistCls);
		sim_cacuStr_fromItem(mFlsItem, mHistPart, &pStr);
		SetFlsQueHeadAdr(mFlsItem, mHistPart, pStr->pStAdr->adrS);
		SetFlsQueEndAdr (mFlsItem, mHistPart, pStr->pStAdr->adrE - U_FLS_1HISTORY_BYTE_MAX);
		
		//ָ�룺
		mFlsItem = getFlsItem_hstPoint(U_Sim_FlsHistCls, mHistPart);
		for(mPointPart=0; mPointPart<U_SIM_pointPart_MAX; mPointPart++)
		{
			sim_cacuStr_fromItem(mFlsItem, mPointPart, &pStr);
			SetFlsQueHeadAdr(mFlsItem, mPointPart, pStr->pStAdr->adrS);
			SetFlsQueEndAdr (mFlsItem, mPointPart, pStr->pStAdr->adrE - U_FLS_1HistPoint_BYTE_MAX);
		}
	}
	
}



static void sim_rd_head_end(void)
{
U8 mFlsItem;
U8 mHistPart;
U8 mPointPart;

	//��ʷ��¼
	for(mHistPart=0; mHistPart<U_SIM_histPart_MAX; mHistPart++)
	{
		mFlsItem = getFlsItem_hist(U_Sim_FlsHistCls);
		vSim_HeadEnd[mHistPart].stHist.head = 
				GetFlsQueHeadAdr(mFlsItem, mHistPart);
		vSim_HeadEnd[mHistPart].stHist.end  = 
				GetFlsQueEndAdr(mFlsItem, mHistPart);
		
		//ָ�룺
		mFlsItem = getFlsItem_hstPoint(U_Sim_FlsHistCls, mHistPart);
		for(mPointPart=0; mPointPart<U_SIM_pointPart_MAX; mPointPart++)
		{
			vSim_HeadEnd[mHistPart].stPoint[mPointPart].head = 
				GetFlsQueHeadAdr(mFlsItem, mPointPart);
			vSim_HeadEnd[mHistPart].stPoint[mPointPart].end = 
				GetFlsQueEndAdr(mFlsItem, mPointPart);
			
		}
	}
	
}



/******************************************************************************
* FUNC: //
*   IN:
*  OUT:  
******************************************************************************/
static void init_task(void)
{

	init_stAdr();
	
	//ֻ��Ϊ�˲���warning, static����δ���õ���
	addHistPoint(U_SIM_histPart_Invalid, U_SIM_histPart_Invalid, ~0, ~0); //mAdr�ǵ�ַ������ָ�롣
	clrHistPoint(U_SIM_histPart_Invalid, U_SIM_histPart_Invalid, ~0, ~0);
	addHistData(U_SIM_histPart_Invalid, ~0, ~0);
	clrHistData(U_SIM_histPart_Invalid, ~0, ~0);
	
	//ȫ���ø��������㿴buf�Ƿ��޸Ĺ����޸ĺ�Ĳ�����ô���롣
	init_histPointBuf(1);
	init_histDataBuf(1);
	
	
	
}

/******************************************************************************
* FUNC: //
******************************************************************************/
static void init_histPointBuf(BOOL bFillData)
{
U8 mHistPart;
U8 mPointPart;
U32 mSect;
	
	for(mHistPart=0; mHistPart<U_SIM_histPart_MAX; mHistPart++)
	{
		for(mPointPart=0; mPointPart<U_SIM_pointPart_MAX; mPointPart++)
		{
			for(mSect=0; 
			   mSect<getFlsItem_SectorMax(getFlsItem_hstPoint(0,0)); 
			   mSect++)
			{
				init_histPointBuf_1Sect(mHistPart, mPointPart, mSect, bFillData);
			}
		}
		
	}
	
}

static void init_histDataBuf(BOOL bFillData)
{
U32 mPart;
U32 mSect;
U8 mFlsItem;
	mFlsItem = getFlsItem_hist(U_Sim_FlsHistCls);

	for(mPart=0; mPart<U_SIM_histPart_MAX; mPart++)
	{
		for(mSect=0; mSect<getFlsItem_SectorMax(mFlsItem); mSect++)
		{
			init_histDataBuf_1Sect(mPart, mSect, bFillData);
		}
	}
}

static void init_histPointBuf_1Sect(U8 mHistPart, U8 mPointPart, U8 mSect, BOOL bFillData)
{
	if((mHistPart>=U_SIM_histPart_MAX) 
	  || (mPointPart>=U_SIM_pointPart_MAX) 
	  || (mSect>=getFlsItem_SectorMax(getFlsItem_hstPoint(0,0))))
	{
		return;
	}

	if(bFillData)
	{
		set_Data_OneSector(&vSim_PointDat[mHistPart][mPointPart][mSect][0],
					U_SIM_Point_1SectByteMax);
	}
	else
	{
		clr_Data_OneSector(&vSim_PointDat[mHistPart][mPointPart][mSect][0],
					U_SIM_Point_1SectByteMax);
	}
}


static void init_histDataBuf_1Sect(U8 mPart, U8 mSect, BOOL bFillData)
{
U8 mFlsItem;
	mFlsItem = getFlsItem_hist(U_Sim_FlsHistCls);

	if((mPart>=U_SIM_histPart_MAX) 
	  || (mSect>=getFlsItem_SectorMax(mFlsItem)))
	{
		return;
	}
	
	if(bFillData)
	{
		set_Data_OneSector(&vSim_HistData[mPart][mSect][0],
					U_SIM_Hist_1SectByteMax );
	}
	else
	{
		clr_Data_OneSector(&vSim_HistData[mPart][mSect][0],
					U_SIM_Hist_1SectByteMax);
	}
	
}


/******************************************************************************
* FUNC: // 
******************************************************************************/
static void clr_Data_OneSector(U8 *pByte, U32 mOneSectBytes)
{
U32 ii;
	
	for(ii=0; ii<mOneSectBytes; ii++)
	{
		*pByte = U_SimFlsPoit_signSpace;
		pByte++;
	}
}

static void set_Data_OneSector(U8 *pByte, U32 mOneSectBytes)
{
U32 ii;
	
	for(ii=0; ii<mOneSectBytes; ii++)
	{
		*pByte = U_SimFlsPoit_signHave;
		pByte++;
	}
}


/******************************************************************************
* FUNC: // 
*   IN:
*  OUT: 
******************************************************************************/
static void addHistPoint(U8 mHistPart, U8 mPoitPart, U32 mSect, U32 mAdrInSect)//mAdr�ǵ�ַ������ָ�롣
{
U8 *pByte;
U32 ii;
U8 mFlsItem;

	mFlsItem = getFlsItem_hstPart0Point(U_Sim_FlsHistCls);
	if(mHistPart != 0)
	{
		mFlsItem = getFlsItem_hstPart1Point(U_Sim_FlsHistCls);
	}
	
	if(!sim_cacuBuf_formItmSect(mFlsItem, mPoitPart, mSect, mAdrInSect, &pByte))
	{
		return;
	}
	for(ii=0; ii<U_FLS_1HistPoint_BYTE_MAX; ii++)
	{
		*pByte = U_SimFlsPoit_signHave;
		pByte++;
	}
		
	
}

static void clrHistPoint(U8 mHistPart, U8 mPoitPart, U32 mSect, U32 mAdrInSect)
{
U8 *pByte;
U32 ii;
U8 mFlsItem;

	mFlsItem = getFlsItem_hstPart0Point(U_Sim_FlsHistCls);
	if(mHistPart != 0)
	{
		mFlsItem = getFlsItem_hstPart1Point(U_Sim_FlsHistCls);
	}
	
	if(!sim_cacuBuf_formItmSect(mFlsItem, mPoitPart, mSect, mAdrInSect, &pByte))
	{
		return;
	}
	for(ii=0; ii<U_FLS_1HistPoint_BYTE_MAX; ii++)
	{
		*pByte = U_SimFlsPoit_signSpace;
		pByte++;
	}
		
	
}

static void addHistData(U8 mPart, U32 mSect, U32 mAdrInSect)
{
U8 *pByte;
U32 ii;
U8 mFlsItem = getFlsItem_hist(U_Sim_FlsHistCls);
	
	if(!sim_cacuBuf_formItmSect(mFlsItem, mPart, mSect, mAdrInSect, &pByte))
	{
		return;
	}
	for(ii=0; ii<U_FLS_1HISTORY_BYTE_MAX; ii++)
	{
		*pByte = U_SimFlsPoit_signHave;
		pByte++;
	}
		
}

static void clrHistData(U8 mPart, U32 mSect, U32 mAdrInSect)
{
U8 *pByte;
U32 ii;
U8 mFlsItem = getFlsItem_hist(U_Sim_FlsHistCls);
	
	if(!sim_cacuBuf_formItmSect(mFlsItem, mPart, mSect, mAdrInSect, &pByte))
	{
		return;
	}
	for(ii=0; ii<U_FLS_1HISTORY_BYTE_MAX; ii++)
	{
		*pByte = U_SimFlsPoit_signSpace;
		pByte++;
	}
		
	
}


/******************************************************************************
* FUNC: // 
******************************************************************************/
static BOOL sim_cacuBuf_formItmSect(U8 mFlsItem, U8 mPart, 
								   U32 mSect, U32 mAdrInSect,
								   U8 **pRtnByte)
{
TSimHistFlash_st  *pStr;
U8 *pByte;
	
	if(!sim_cacuStr_fromItem(mFlsItem, mPart, &pStr))
	{
		return FALSE;
	}
	pByte = pStr->pFlash;
	
	pByte += mSect * pStr->oneSectBytesMax;
	
	pByte += mAdrInSect;
	return TRUE;
}

/******************************************************************************
* FUNC: // 
******************************************************************************/
static BOOL sim_cacuAdr_toBuf(U8 chip, U32 mAdr, 
						U8 **pRtnByte)
{
TSimHistFlash_st  *pStr;
TFlsItemAddr *pAdr;
U32 adrDiff;

	if(!sim_cacuStr_fromAdr(chip, mAdr, &pStr))
	{
		return FALSE;
	}
	pAdr = pStr->pStAdr;
	adrDiff = mAdr - pAdr->adrS;
	*pRtnByte = pStr->pFlash + adrDiff;
	
	*pRtn1SectBytes = pStr->oneSectBytesMax;
	return TRUE;
}


/******************************************************************************
* FUNC: // 
*   IN:
*  OUT: 
******************************************************************************/

static BOOL sim_cacuStr_fromAdr(U8 chip, U32 mAdr, 
								TSimHistFlash_st **pRtnStr
								)
{
U8 mEmFlsItem;
U8 mHistPart;
TSimHistFlash_st  *pStr;
TFlsItemAddr *pAdr;

	for(mHistPart=0; mHistPart<U_SIM_histPart_MAX; mHistPart++)
	{
		for(mEmFlsItem=0; mEmFlsItem<U_emFlsItem_MAX; mEmFlsItem++)
		{
			pStr = (TSimHistFlash_st*)(&vSim_cstHistFlash[mHistPart][mEmFlsItem]);
			pAdr = pStr->pStAdr;
			
			if((chip == pAdr->chip) && (mAdr >= pAdr->adrS)&&(mAdr <  pAdr->adrE))
			{
				*pRtnStr = pStr;
				return TRUE;
			}
		}
		
	}
	return FALSE; 
}



static BOOL sim_cacuStr_fromItem(U8 mFlsItem, U8 mFlsPart, 
								TSimHistFlash_st **pRtnStr
								)
{
U8 mEmFlsItem;
U8 mHistPart;
TSimHistFlash_st  *pStr;

	if(mFlsPart >= 2)
	{
		return FALSE;
	}
	
	for(mHistPart=0; mHistPart<U_SIM_histPart_MAX; mHistPart++)
	{
		for(mEmFlsItem=0; mEmFlsItem<U_emFlsItem_MAX; mEmFlsItem++)
		{
			pStr = (TSimHistFlash_st*)(&vSim_cstHistFlash[mHistPart][mEmFlsItem]);
			if((pStr->mFlsItem == mFlsItem)&&(pStr->mPart == mFlsPart))
			{
				*pRtnStr = pStr;
				return TRUE;
			}
		}
	}
	return FALSE; 
}


/******************************************************************************
* FUNC: // 
*   IN:
*  OUT: 
******************************************************************************/
void sim_flash_EraseSect_FromAdr(U8 chip, U32 address, U8 bWaitForFinish)
{
U8 *pByte;
U32 mOneSectBytes;
TSimHistFlash_st  *pStr;

	if(!sim_cacuStr_fromAdr(chip, address, &pStr))
	{
		return FALSE;
	}
	mOneSectBytes = pStr->oneSectBytesMax;
	
	address &= (~(mOneSectBytes));
	if(!sim_cacuAdr_toBuf(chip, address, &pByte))
	{
		return;
	}
	clr_Data_OneSector(pByte, mOneSectBytes);
}


void sim_flash_Write_nByte(U8 chip, U8 *pStart, U32 num, U32 address, U8 bWaitForFinish)
{
U8 *pByte;
U32 ii;

	if(!sim_cacuAdr_toBuf(chip, address, &pByte))
	{
		return;
	}
	
	for(ii=0; ii<num; ii++)
	{
		*pByte++ = *pStart++;
	}
	
}

/******************************************************************************
* FUNC: // TASK
*   IN:
*  OUT: 
******************************************************************************/
static U8 mAdr = 1;
static TEvtTrans_st  stTrans;

/*

typedef struct{
	
	U32 channel:6; //1~
	U32 field:9;		//1~ //mduLine  //�����ࡣ�������ֳ�����,�в�ͬ�Ķ��塣 
	
	//���½ṹ���ܱ�,���ƿɱ䡣
	U32 eventSubject:1; 	// U_EVT_SUBJECT_FIELD, U_EVT_SUBJECT_BOARD ����������
	U32 boardLoop:4;	//1~  //���ڻ�·-num,  //modu
	U32 pnSequ:7;  		//1~ //panel�������-num, 128
	U32 pnType:5;  		//0~ //panel����  // emPanelSign
	
	U8  machine;
}TCommonMLAT_st; //machine-loop-addr-channel
*/
static void sim_add_oneHist(void)
{
	IniEvtTransStruct(&stTrans);
	
	stTrans.type = mAdr;
	stTrans.thing = U_Ala_EVT_Min;
	stTrans.thiFurther = mAdr+2;
	
	stTrans.unDev.stDete.machine = mAdr + 3;
	stTrans.unDev.stDete.pnType = mAdr + 4;
	stTrans.unDev.stDete.pnSequ = mAdr + 5;
	stTrans.unDev.stDete.boardLoop = mAdr + 6;
	stTrans.unDev.stDete.eventSubject = mAdr + 7;
	stTrans.unDev.stDete.field = mAdr + 8;
	stTrans.unDev.stDete.channel = mAdr + 9;
		
	stTrans.evtClock.year = mAdr + 0x10;
	stTrans.evtClock.month = mAdr + 0x11;
	stTrans.evtClock.day = mAdr + 0x12;
	stTrans.evtClock.hour = mAdr + 0x13;
	stTrans.evtClock.min = mAdr + 0x14;
	stTrans.evtClock.sec = mAdr + 0x15;
		
		
	mAdr++;
	HistNewEvent(&stTrans);
}

static void sim_add_Hist(U8 mNum)
{
	U8 ii;
	
	
	for(ii=0; ii<mNum; ii++)
	{
		sim_add_oneHist();
	}
	
}

/******************************************************************************
* FUNC: // 
*   IN:
*  OUT:  
******************************************************************************/

/******************************************************************************
* FUNC: // TASK
*   IN:
*  OUT:  
д histPart0�� pointPart1��λ�ú�����ˡ�
******************************************************************************/
void Sim_SaveHistTask(void)
{
U32 ii;

	init_task();
	//����ֵ����ģ��flash��ֵ��
	init_HeadEnd_sectEndOnly_1_item(); // init_HeadEnd();
	init_HeadEnd_6Cls_sectEndOnly_1_item();
	
	Init_HistWrBuf();
	FlsWr_Hist_Init();
	
	for(ii=0; ii<10000; ii++) 
	{
		if(!bFlsWr_Hist_Finished())
		{
			FlsWr_Hist_Exec();
		}
		else
		{
			sim_add_Hist(0x10);
			FlsWr_Hist_Start();
		}
		sim_rd_head_end();
	}
	
	
	
}


/******************************************************************************
* FUNC: // END
*   IN:
*  OUT: 
******************************************************************************/
#endif //U_SYS_Test_Flash_Hist
