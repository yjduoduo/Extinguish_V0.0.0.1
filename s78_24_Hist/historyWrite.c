#define __historyWrite_C__
/******************************************************************************
* @file    historyWrite.c
* @author  yx
* @version V1.0
* @date    2013-07-23
* @brief   д��ʷ��¼�Ĺ��̿��ơ���������ָ�롣
		ÿhistClsÿpart������һ�飬���ֻ��ʾ��sectEnd.
* @slave   saveHistPoint.c ��ȫ��������¡�
* @master   saveManage.c
* 
0x1000 -> 0x100���� 
sector���ʼ���ֽ�, �� TFlsSecStart_un ;


д��δ��sectorEnd: ��hist.part0���ݣ� ��hist.part1���ݣ�
д���ѵ�sectorEnd: 
	1. ��hist.part0. point.part0ָ��
	2. hist.part0. SectorNext : erase , hist.head += 1SectorBytes;
	3. ��hist.part0��¼, hist.end = SectorNext;
	4. дSectorNext.head, hist.end = SectorNext + 1��;
	5. ��hist.part0. point.part1ָ��
	6. ͬ������part2.
����nextSectʱ�����޸�end,Ҫд�¼�¼����sectHeadʱ���޸�end.

// U_SIGN_bHaveTested; 2013-07-10
******************************************************************************/
#include  "historyWrite.h"


#include  "phSaveHist_incIn.h"
#include  "flsInqPoint.h"
//#include "incFile.h"	

#if U_SYS_Test_Flash_Hist == 1
	#include  "sim_saveHist.h"
#else // U_SYS_Test_Flash_Hist
#endif // U_SYS_Test_Flash_Hist

/*================= ���� ============================================*/

/*================= �ṹ���� ========================================*/

/*================= �ṹ�嶨�� ======================================*/



typedef struct{
	
	U8 bOpeaIng;
	U8 step;
	U8 bSucc;
	BOOL bNeedEraseNextSector;
	U32 adrSectNext;
	U32 adrNextHead;
	
	TFlsQueuePoint_st   stPt;
	
}THistWr_step_st;


typedef struct{
	
	U8 mHistCls;
	U8 mHistFlsItem;
	U8 mHistPart;
	TFlsItemAddr stAdr;
}THistWr_hist_st;




typedef struct{
	
	U8 mPointFlsItem;
	U8 mPointPart;
	TFlsItemAddr stPointAdr;
	BOOL bHaveOpeaHistPointPart[U_FlsSave_Part_MAX];
}THistWr_point_st;


#define U_HIST_WriteOnce_Item_MAX   0x10 //һ��д�����

typedef struct{
	// U8 task_HistCls;
	THistWr_step_st  wrStep;
	
	
	//��ʷ��¼�ģ�
	THistWr_hist_st  hist;
	//
	TBufCircle    stCircle;
	THisory_un wrBuf[U_HIST_WriteOnce_Item_MAX]; //��д��
	
	//ָ��ģ�
	THistWr_point_st point;
	
	
}THistWr_st;
/*================= ˽�б������� ====================================*/
static THistWr_st   stHstWr;

/*=================  ================================================*/
		
/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

static void set_hist_endAdr(U32 mAdrEnd)
{
	SetFlsQueEndAdr(stHstWr.hist.mHistFlsItem, 
						stHstWr.hist.mHistPart, 
					   mAdrEnd
					   );
}

static void set_hist_headAdr(U32 mAdrHead)
{
	SetFlsQueHeadAdr(stHstWr.hist.mHistFlsItem, 
						stHstWr.hist.mHistPart, 
					   mAdrHead
					   );
}

static U32 get_hist_headAdr(void)
{
	return GetFlsQueHeadAdr(	stHstWr.hist.mHistFlsItem, 
									stHstWr.hist.mHistPart
									);
}

static U32 get_hist_endAdr(void)
{
	return GetFlsQueEndAdr(	stHstWr.hist.mHistFlsItem, 
									stHstWr.hist.mHistPart
									);
}

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

BOOL FlsWr_Hist_Start(void)
{

	if(bHistBuf_isEmpty())
	{
		return FALSE;
	}
	//��ʷ��¼��д��buf���˴ν�ֹ:
	HistBuf_StartRead();
	
	stHstWr.hist.mHistCls = 0;
	stHstWr.hist.mHistPart = 0;
	
	stHstWr.wrStep.bOpeaIng = TRUE;
	stHstWr.wrStep.bSucc = FALSE;
	stHstWr.wrStep.step = U_HistWrStep_01_Start;
	
	return TRUE;
}




/******************************************************************************
* FUNC: //fls��¼ָ�� init.
*   IN:
*  OUT: 
U_HistWrStep_02_PointPart0 �� U_HistWrStep_07_PointPart1 ǰ��Ҫ���á�
******************************************************************************/
static void flsWr_hstPoint_init(U8 mHistCls, U8 mHistPart, U8 mPointPart)
{
	stHstWr.point.mPointFlsItem = getFlsItem_hstPoint(mHistCls, mHistPart);
	stHstWr.point.mPointPart = mPointPart;
	getFlsItem_Addr(stHstWr.point.mPointFlsItem, 
				mPointPart, &stHstWr.point.stPointAdr
				);
}


/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 	mHistCls, mHistFlsItem, mHistPart, stAdr;
		stHstWr.wrBuf
		bNeedEraseNextSector, adrSectNext;
******************************************************************************/
static BOOL flsWr_hist_1Cls1Part_init(U8 mHistCls, U8 mHistPart)
{
U32 mAdrEnd; //��¼��endָ��
U32 itmSectRemain;
U32 itmRdMax;
U32 itmHaveRd;

	stHstWr.hist.mHistCls = mHistCls;
	stHstWr.hist.mHistFlsItem = getFlsItem_hist(mHistCls);
	stHstWr.hist.mHistPart = mHistPart;
	if(!getFlsItem_Addr(stHstWr.hist.mHistFlsItem, mHistPart, &stHstWr.hist.stAdr))
	{
		return FALSE;
	}
	
	stHstWr.point.bHaveOpeaHistPointPart[0] = FALSE;
	stHstWr.point.bHaveOpeaHistPointPart[FlsHistPointPartMax()-1] = FALSE;
	
	
	//��ȡ��¼�����ݣ�
	BufCircleIni(U_HIST_WriteOnce_Item_MAX, &stHstWr.stCircle);
	
	mAdrEnd = get_hist_endAdr();
	itmSectRemain = FlsItm_adr_inSect_itmSpace(
						mAdrEnd, stHstWr.hist.mHistFlsItem, U_FLS_1HISTORY_BYTE_MAX
						);
	//ע���Ƿ���sector head:
	if(mAdrEnd == FlsItm_sector_start(mAdrEnd, stHstWr.hist.mHistFlsItem))
	{
		itmSectRemain -= 1;
	}
	
	itmRdMax = itmSectRemain;
	if(itmSectRemain >= U_HIST_WriteOnce_Item_MAX)
	{
		itmRdMax = U_HIST_WriteOnce_Item_MAX;
	}
	
	itmHaveRd = 0;
	while(itmHaveRd < itmRdMax)
	{
		if(HistBuf_Read(mHistCls, mHistPart, 
					&stHstWr.wrBuf[BufCircle_GetIn(&stHstWr.stCircle)]))
		{
			itmHaveRd++;
			BufCircle_InInc(&stHstWr.stCircle);
		}
		else
		{
			break;
		}
	}
	
	if(itmHaveRd == 0)
	{
		return FALSE;
	}
	else
	{
		stHstWr.wrStep.bNeedEraseNextSector = FALSE;
		if(itmHaveRd == itmSectRemain) //sector����д��
		{
			flsWr_hist_1Cls1Part_sectWillFull();
		}
		return TRUE;
	}
	
}




void flsWr_hist_1Cls1Part_sectWillFull(void)
{
U32 mAdrHead;
U32 mAdrEnd; //��¼��endָ��

	mAdrHead = get_hist_headAdr();
	mAdrEnd = get_hist_endAdr();
	
	stHstWr.wrStep.bNeedEraseNextSector = TRUE;
	stHstWr.wrStep.adrSectNext =  FlsItm_sectorNext_start(
				mAdrEnd, stHstWr.hist.mHistFlsItem, &stHstWr.hist.stAdr
				);
	
	//Ԥ�� histHead. ���ܳɹ�д,�����µ�head;�����磬RAMû���ˡ�
	//ҲΪд histPoint��׼����
	//ʵ����wrHist_Step_03_EraseNextSector()����Ч��
	if(mAdrHead == stHstWr.wrStep.adrSectNext)
	{
		mAdrHead = FlsItm_sectorNext_start(
					stHstWr.wrStep.adrSectNext, stHstWr.hist.mHistFlsItem, 
					&stHstWr.hist.stAdr
					);
		set_hist_headAdr(mAdrHead);
		
		
	}
	
	//��д���histָ�룺
	stHstWr.wrStep.stPt.headAdr = get_hist_headAdr();
	stHstWr.wrStep.stPt.endAdr = stHstWr.wrStep.adrSectNext;
	
}

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/


/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
void FlsWr_Hist_Init(void)
{
	FlsWr_Hist_SetFinish();
}

/******************************************************************************
* FUNC: //
******************************************************************************/
BOOL bFlsWr_Hist_Finished(void)
{
	return LogicInverse(stHstWr.wrStep.bOpeaIng);
}

BOOL bFlsWr_Hist_isIdle(void)
{
	return bFlsWr_Hist_Finished();
}


/******************************************************************************
* FUNC: //
******************************************************************************/

void FlsWr_Hist_SetFinish(void)
{
	stHstWr.wrStep.bOpeaIng = FALSE;
	stHstWr.wrStep.step = ~0;
}

/******************************************************************************
* FUNC: //
******************************************************************************/



/******************************************************************************
* FUNC: // step
*   IN:
*  OUT: 
******************************************************************************/

static BOOL wrHist_Step_01_Start(void)
{
U8 mHistCls;
U8 mHistPart;
U8 mFlsItem;

	mHistCls=stHstWr.hist.mHistCls;
	mHistPart=stHstWr.hist.mHistPart;
	
	while((mHistCls < U_HIST_CLASS_MAX))
	{
		if(flsWr_hist_1Cls1Part_init(mHistCls, mHistPart))
		{
			wrHist_Step_01_Start__newStep();
			return TRUE;
		}
		else
		{
			mHistPart++;
			if(mHistPart >= FlsHistPartMax())
			{
				mHistPart = 0;
				mHistCls++;
			}
			else if(mHistPart == 1)
			{
				mFlsItem = getFlsItem_hist(mHistCls);
				if(!bFlsItem_HaveShare(mFlsItem))
				{
					mHistPart = 0;
					mHistCls++;
				}
			}
		}
	}
	
	return FALSE;
}


//
static void wrHist_Step_01_Start__newStep(void)
{
	if(stHstWr.wrStep.bNeedEraseNextSector)
	{
		flsWr_hstPoint_init(stHstWr.hist.mHistCls, stHstWr.hist.mHistPart, 0);
		stHstWr.wrStep.step = U_HistWrStep_02_PointPart0;
	}
	else
	{
		wrHist_Step__wrSectHead_orHist();
	}
}

/******************************************************************************
* FUNC: //step=��histEnd=sectorHead,��Ҫдhead.
*master: 	wrHist_Step_01_Start__newStep()
*master: 	wrHist_Step_03_EraseNextSector()
******************************************************************************/
static void wrHist_Step__wrSectHead_orHist(void) 
{
U32 mAdrEnd;
	
	mAdrEnd = get_hist_endAdr();
	
	if(mAdrEnd == (hist_sector_start(mAdrEnd)))
	{
		stHstWr.wrStep.step = U_HistWrStep_04_WriteSectorHead;
	}
	else
	{
		stHstWr.wrStep.step = U_HistWrStep_05_WriteNew;
	}
}



/******************************************************************************
* FUNC: //д sectorNext.head
******************************************************************************/
/******************************************************************************
* FUNC: // 
******************************************************************************/
static void wrHist_Step_02_PointPart0(void)
{
	
	if(!stHstWr.point.bHaveOpeaHistPointPart[U_FlsSave_Part0])
	{
		stHstWr.point.bHaveOpeaHistPointPart[U_FlsSave_Part0] = TRUE;
		
		
		FlsWr_HistPoint_New(stHstWr.hist.mHistCls, stHstWr.hist.mHistPart,
						   U_FlsSave_Part0, stHstWr.wrStep.stPt);
	}
	else if(bFlsWr_HistPoint_Finished())
	{
		stHstWr.wrStep.step = U_HistWrStep_03_EraseNextSector;
	}
	else
	{
		FlsWr_HistPoint_Exec();
	}
}

/******************************************************************************
* FUNC: // 
******************************************************************************/
static void wrHist_Step_07_PointPart1(void)
{
	
	if(!stHstWr.point.bHaveOpeaHistPointPart[U_FlsSave_Part1])
	{
		stHstWr.point.bHaveOpeaHistPointPart[U_FlsSave_Part1] = TRUE;
		if(!bFlsItem_HaveShare(stHstWr.point.mPointFlsItem))
		{
			stHstWr.wrStep.step = U_HistWrStep_10_NextPart;
			return;
		}
		FlsWr_HistPoint_New(stHstWr.hist.mHistCls, stHstWr.hist.mHistPart,
						   U_FlsSave_Part1, stHstWr.wrStep.stPt);
	}
	else if(bFlsWr_HistPoint_Finished())
	{
		stHstWr.wrStep.step = U_HistWrStep_10_NextPart;
	}
	else
	{
		FlsWr_HistPoint_Exec();
	}
}


/******************************************************************************
* FUNC: // 
//����nextSectʱ�����޸�end,Ҫд�¼�¼����sectHeadʱ���޸�end.
******************************************************************************/
static void wrHist_Step_03_EraseNextSector(void)
{
#if U_SYS_Test_Flash_Hist == 1
	sim_flash_EraseSect_FromAdr(stHstWr.hist.stAdr.chip, 
						stHstWr.wrStep.adrSectNext, 
						U_SYS_FLASH_OPEA_WAIT);
#else // U_SYS_Test_Flash_Hist
	FlsHd_EraseSect_FromAdr(stHstWr.hist.stAdr.chip, 
						stHstWr.wrStep.adrSectNext, 
						U_SYS_FLASH_OPEA_WAIT);
#endif // U_SYS_Test_Flash_Hist
	
	
	wrHist_Step__wrSectHead_orHist(); //��histEnd=sectorHead,��Ҫдhead.
	
}


/******************************************************************************
* FUNC: // 
******************************************************************************/
static void wrHist_Step_04_WriteSectorHead(void)
{
	wrHist_Step__jdgSectorHead_andWrHead();
	stHstWr.wrStep.step = U_HistWrStep_05_WriteNew;
}


/******************************************************************************
* FUNC: // 
******************************************************************************/
static void wrHist_Step_06_NextSectorHead(void)
{
	wrHist_Step__jdgSectorHead_andWrHead();
	
	if(bFlsItem_HaveShare(stHstWr.point.mPointFlsItem))
	{
		stHstWr.wrStep.step = U_HistWrStep_07_PointPart1;
	}
	else
	{
		stHstWr.wrStep.step = U_HistWrStep_10_NextPart;
	}
}
/******************************************************************************
* FUNC: // 
//master: wrHist_Step_04_WriteSectorHead(); 
//master: wrHist_Step_06_NextSectorHead();
******************************************************************************/

static void wrHist_Step__jdgSectorHead_andWrHead(void) //����sectorHead,д&�޸�end.
{
U32 mAdrEnd;
	
	mAdrEnd = get_hist_endAdr();
	
	if(mAdrEnd == (hist_sector_start(mAdrEnd)))
	{
		stHstWr.wrStep.adrSectNext=mAdrEnd;
		wrHist_Step__wrSectorHead();
		mAdrEnd = FlsItm_adr_itemNext(
					mAdrEnd, stHstWr.hist.mHistFlsItem, 
					U_FLS_1HISTORY_BYTE_MAX, 
					&stHstWr.hist.stAdr
					);
		set_hist_endAdr(mAdrEnd);
	}
}

//master: wrHist_Step__jdgSectorHead_andWrHead();
static void wrHist_Step__wrSectorHead(void) //д sector.head
{
TFlsSecStart_un stSectHead;

	Init_StrFlsSectStart(stHstWr.hist.mHistFlsItem, 
							&stSectHead
							);
		
#if U_SYS_Test_Flash_Hist == 1
	sim_flash_Write_nByte(stHstWr.hist.stAdr.chip, 
				&stSectHead.byte[0], U_FLS_SectorStart_BYTES, 
				stHstWr.wrStep.adrSectNext, 
				U_SYS_FLASH_OPEA_WAIT);
#else // U_SYS_Test_Flash_Hist
	FlsWr_Write_nByte_meIsEnd(stHstWr.hist.stAdr.chip, 
				&stSectHead.byte[0], U_FLS_SectorStart_BYTES, 
				stHstWr.wrStep.adrSectNext
				);
#endif // U_SYS_Test_Flash_Hist

}

/******************************************************************************
* FUNC: // 
******************************************************************************/
static void wrHist_Step_05_WriteNew(void)
{
U32 mAdrEnd;
U32 wrBytes;

	mAdrEnd = get_hist_endAdr();
	
	wrBytes = BufCircle_GetIn(&stHstWr.stCircle) * U_FLS_1HISTORY_BYTE_MAX;
#if U_SYS_Test_Flash_Hist == 1
	sim_flash_Write_nByte(stHstWr.hist.stAdr.chip, 
				(U8 *)(&stHstWr.wrBuf[0]),
				wrBytes,
				mAdrEnd, 
				U_SYS_FLASH_OPEA_WAIT);
#else // U_SYS_Test_Flash_Hist
	FlsWr_Write_nByte_meIsEnd(stHstWr.hist.stAdr.chip, 
				(U8 *)(&stHstWr.wrBuf[0]),
				wrBytes,
				mAdrEnd
				);
#endif // U_SYS_Test_Flash_Hist

	while(wrBytes != 0)
	{
		mAdrEnd = FlsItm_adr_itemNext(
					mAdrEnd, stHstWr.hist.mHistFlsItem, 
					U_FLS_1HISTORY_BYTE_MAX, 
					&stHstWr.hist.stAdr
					);
		wrBytes -= U_FLS_1HISTORY_BYTE_MAX;
	}
	set_hist_endAdr(mAdrEnd);
	
	
	if(stHstWr.wrStep.bNeedEraseNextSector)
	{
		stHstWr.wrStep.step = U_HistWrStep_06_NextSectorHead;
	}
	else
	{
		stHstWr.wrStep.step = U_HistWrStep_10_NextPart;
	}
}


/******************************************************************************
* FUNC: // 
******************************************************************************/
static void wrHist_Step_10_NextPart(void)
{
	Clr_FlsItemState(U_FlsItem_Space_State,
			stHstWr.hist.mHistFlsItem, stHstWr.hist.mHistPart);
	
	stHstWr.hist.mHistPart++;
	if(stHstWr.hist.mHistPart >= FlsHistPartMax())
	{ stHstWr.hist.mHistPart = 0;
		stHstWr.wrStep.step = U_HistWrStep_11_NextHistCls;
	}
	else
	{
		if(bFlsItem_HaveShare(stHstWr.hist.mHistFlsItem))
		{
			stHstWr.wrStep.step = U_HistWrStep_01_Start;
		}
		else
		{
			stHstWr.wrStep.step = U_HistWrStep_11_NextHistCls;
		}
	}
	
}

/******************************************************************************
* FUNC: // 
******************************************************************************/
static void wrHist_Step_11_NextHistCls(void)
{
	stHstWr.hist.mHistCls++;
	stHstWr.hist.mHistPart = 0;
	
	if(stHstWr.hist.mHistCls >= U_HIST_CLASS_MAX)
	{
		stHstWr.hist.mHistCls = 0;
		stHstWr.wrStep.step = U_HistWrStep_12_Finish;
		return;
	}
	
	stHstWr.wrStep.step = U_HistWrStep_01_Start;
}



/******************************************************************************
* FUNC: // 
*   IN:
*  OUT: 
******************************************************************************/

void FlsWr_Hist_Exec(void)
{
// U32 mAdrHead;
// U32 mAdrEnd;
// U8 mHistFlsItem = stHstWr.hist.mHistFlsItem;

	if(!stHstWr.wrStep.bOpeaIng)
	{
		return;
	}
	// mAdrHead = get_hist_headAdr();
	// mAdrEnd = get_hist_endAdr(); 
	
	switch(stHstWr.wrStep.step)
	{
		case U_HistWrStep_01_Start:
			if(!wrHist_Step_01_Start())
			{
				stHstWr.wrStep.step = U_HistWrStep_12_Finish;
			}
			break;
			
		case U_HistWrStep_02_PointPart0: //1. ��hist.part0. point.part0ָ��
			wrHist_Step_02_PointPart0();
			break;
			
		case U_HistWrStep_03_EraseNextSector:
			wrHist_Step_03_EraseNextSector();
			break;
			
		case U_HistWrStep_04_WriteSectorHead:
			wrHist_Step_04_WriteSectorHead();
			break;
			
		case U_HistWrStep_05_WriteNew:
			wrHist_Step_05_WriteNew();
			break;
			
		case U_HistWrStep_06_NextSectorHead:
			wrHist_Step_06_NextSectorHead();
			break;
			
		case U_HistWrStep_07_PointPart1: //5. ��hist.part0. point.part1ָ��
			wrHist_Step_07_PointPart1();
			break;
			
	
		case U_HistWrStep_10_NextPart:
			wrHist_Step_10_NextPart();
			break;
			
		case U_HistWrStep_11_NextHistCls:
			wrHist_Step_11_NextHistCls();
			break;
			
		case U_HistWrStep_12_Finish:
			FlsWr_Hist_SetFinish();
			break;
			
		default:
			FlsWr_Hist_SetFinish();
			break;
			
		
	}
	
}

/******************************************************************************
* FUNC: // END
*   IN:
*  OUT: 
******************************************************************************/
