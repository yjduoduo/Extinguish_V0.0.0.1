#ifndef __sim_saveHist_H__
#define __sim_saveHist_H__
/******************************************************************************
* @file    sim_saveHist.h
* @author  yx
* @version V1.0
* @date    2013-07-09
* @brief   
* 
#include  "sim_saveHist.h"
******************************************************************************/
//
#include  "prjCompileCon.h"
#include  "strFlsAdrDef.h"
#include  "flsBytesDef.h"
#include  "flsStoreBytesDef.h"

/*================= extern ============================================*/
#ifdef  __sim_saveHist_C__
#define EX_sim_saveHist
#else
#define EX_sim_saveHist extern 
#endif

/*================= 私有有函数声明 - 测试 ====================================*/
#if U_SYS_Test_Flash_Hist == 1
#ifdef  __sim_saveHist_C__
//----------------------------------------------------------------------

#define U_SIM_Hist_1SectByteMax   U_FLASH_1_SECTOR //存储历史记录和指针
#define U_SIM_Point_1SectByteMax   U_FLASH_1_SECTOR //存储历史记录和指针
// U32 mOneSectBytes;
//----------------------------------------------------------------------
#define U_SIM_histPart0   0
#define U_SIM_histPart1   1
#define U_SIM_histPart_MAX   2

#define U_SIM_pointPart0  0
#define U_SIM_pointPart1  1
#define U_SIM_pointPart_MAX  2

#define U_SIM_histPart_Invalid  ~0

//重复定义
#define U_1HistCls_SectMAX  0x02  //重复定义
#define U_1HistClsPoint_SectMAX  2  //重复定义

static U8 vSim_PointDat[U_SIM_histPart_MAX][U_SIM_pointPart_MAX][U_1HistClsPoint_SectMAX][U_SIM_Point_1SectByteMax]; //
static U8 vSim_HistData[U_SIM_histPart_MAX][U_1HistCls_SectMAX][U_SIM_Hist_1SectByteMax];

// #define U_SimFls_Part     0
#define U_Sim_FlsHistCls  U_HIST_Alarm_CLASS
static TFlsItemAddr vSim_HistAdr[U_SIM_histPart_MAX];
static TFlsItemAddr vSim_PointAdr[U_SIM_histPart_MAX][U_SIM_pointPart_MAX]; //

#define U_SimFlsPoit_signHave  0x01
#define U_SimFlsPoit_signSpace  0xFF
//----------------------------------------------------------------------

typedef struct{
	U32 head;
	U32 end;
}TSim1HeadEnd_st;

typedef struct{
	TSim1HeadEnd_st  stHist;
	TSim1HeadEnd_st  stPoint[U_SIM_pointPart_MAX]; //对应同个历史记录
}TSimHeadEnd_st;

static TSimHeadEnd_st  vSim_HeadEnd[U_FlsSave_Part_MAX];  // mHistPart

//----------------------------------------------------------------------
enum emSimHist{
	emFlsItemHist,
	emFlsItem_HistPartX_PointPart0,
	emFlsItem_HistPartX_PointPart1,
};
#define U_emFlsItem_MAX  3


typedef struct{
	U32 mFlsItem;
	U32 mPart;
	U8  oneSectBytesMax;
	TFlsItemAddr *pStAdr;
	U8 *pFlash;
	TSim1HeadEnd_st *pHeadEnd;
}TSimHistFlash_st;


#define U_FlsSave_HistPart0Point_Start  0x10 // 6*2=12种，每种2sector, = 24*4K=48K
#define U_FlsSave_HistPart1Point_Start  0x18
#define U_FlsSave_Hist_Start  0x20
const TSimHistFlash_st vSim_cstHistFlash[U_SIM_histPart_MAX][U_emFlsItem_MAX] =
{
	//hist part0:
	{
		// emFlsItemHist,
		{
			U_FlsSave_Hist_Start+U_Sim_FlsHistCls,	//mFlsItem
			U_SIM_histPart0, 						//mPart
			U_SIM_Hist_1SectByteMax,
			&vSim_HistAdr[U_SIM_histPart0], 		//*pStAdr
			&vSim_HistData[U_SIM_histPart0][0][0], 			//*pFlash
			&vSim_HeadEnd[U_SIM_histPart0].stHist 	//*pHeadEnd
		},
		// emFlsItem_HistPartX_PointPart0,
		{
			U_FlsSave_HistPart0Point_Start+U_Sim_FlsHistCls,	//mFlsItem
			U_SIM_pointPart0, 									//mPart
			U_SIM_Point_1SectByteMax,
			&vSim_PointAdr[U_SIM_histPart0][U_SIM_pointPart0], 	//*pStAdr
			&vSim_PointDat[U_SIM_histPart0][U_SIM_pointPart0][0][0], 		//*pFlash
			&vSim_HeadEnd[U_SIM_histPart0].stPoint[U_SIM_pointPart0] 	//*pHeadEnd
		},
		// emFlsItem_HistPartX_PointPart1,
		{
			U_FlsSave_HistPart0Point_Start+U_Sim_FlsHistCls,	//mFlsItem
			U_SIM_pointPart1, 									//mPart
			U_SIM_Point_1SectByteMax,
			&vSim_PointAdr[U_SIM_histPart0][U_SIM_pointPart1], 	//*pStAdr
			&vSim_PointDat[U_SIM_histPart0][U_SIM_pointPart1][0][0], 		//*pFlash
			&vSim_HeadEnd[U_SIM_histPart0].stPoint[U_SIM_pointPart1] 	//*pHeadEnd
		}
	},
	//hist part1:
	{
		// emFlsItemHist,
		{
			U_FlsSave_Hist_Start+U_Sim_FlsHistCls,	//mFlsItem
			U_SIM_histPart1, 						//mPart
			U_SIM_Hist_1SectByteMax,
			&vSim_HistAdr[U_SIM_histPart1], 		//*pStAdr
			&vSim_HistData[U_SIM_histPart1][0][0], 			//*pFlash
			&vSim_HeadEnd[U_SIM_histPart1].stHist 	//*pHeadEnd
		},
		// emFlsItem_HistPartX_PointPart0,
		{
			U_FlsSave_HistPart1Point_Start+U_Sim_FlsHistCls,	//mFlsItem
			U_SIM_pointPart0, 									//mPart
			U_SIM_Point_1SectByteMax,
			&vSim_PointAdr[U_SIM_histPart1][U_SIM_pointPart0], 	//*pStAdr
			&vSim_PointDat[U_SIM_histPart1][U_SIM_pointPart0][0][0], 		//*pFlash
			&vSim_HeadEnd[U_SIM_histPart1].stPoint[U_SIM_pointPart0] 	//*pHeadEnd
		},
		// emFlsItem_HistPartX_PointPart1,
		{
			U_FlsSave_HistPart1Point_Start+U_Sim_FlsHistCls,	//mFlsItem
			U_SIM_pointPart1, 									//mPart
			U_SIM_Point_1SectByteMax,
			&vSim_PointAdr[U_SIM_histPart1][U_SIM_pointPart1], 	//*pStAdr
			&vSim_PointDat[U_SIM_histPart1][U_SIM_pointPart1][0][0], 		//*pFlash
			&vSim_HeadEnd[U_SIM_histPart1].stPoint[U_SIM_pointPart1] 	//*pHeadEnd
		}
		
	}
	
	
};

//----------------------------------------------------------------------
static void init_task(void); //
static void init_stAdr(void);  //

static void init_histPointBuf(BOOL bFillData); //
static void init_histDataBuf(BOOL bFillData); //
static void init_histPointBuf_1Sect(U8 mHistPart, U8 mPointPart, 
							U8 mSect, BOOL bFillData); //
static void init_histDataBuf_1Sect(U8 mPart, U8 mSect, BOOL bFillData); //

static void clr_Data_OneSector(U8 *pByte, U32 mOneSectBytes); //
static void set_Data_OneSector(U8 *pByte, U32 mOneSectBytes); //

static void addHistPoint(U8 mHistPart, U8 mPoitPart, U32 mSect, U32 mAdrInSect); //mAdr是地址，不是指针。
static void clrHistPoint(U8 mHistPart, U8 mPoitPart, U32 mSect, U32 mAdrInSect); //
static void addHistData(U8 mPart, U32 mSect, U32 mAdrInSect); //
static void clrHistData(U8 mPart, U32 mSect, U32 mAdrInSect); //

static BOOL sim_cacuBuf_formItmSect(U8 mFlsItem, U8 mPart, 
								   U32 mSect, U32 mAdrInSect,
								   U8 **pRtnByte); //

static BOOL sim_cacuAdr_toBuf(U8 chip, U32 mAdr, 
						U8 **pRtnByte
						);


static BOOL sim_cacuStr_fromAdr(U8 chip, U32 mAdr, 
								TSimHistFlash_st **pRtnStr
								); //
static BOOL sim_cacuStr_fromItem(U8 mFlsItem, U8 mFlsPart, 
								TSimHistFlash_st **pRtnStr
								); //

// static void init_HeadEnd(void); //
static void init_HeadEnd_sectEndOnly_1_item(void);

static void sim_rd_head_end(void); //
static void sim_add_oneHist(void);
//----------------------------------------------------------------------
#endif //__sim_saveHist_C__
#endif //U_SYS_Test_Flash_Hist
/*================= 公有函数声明 ====================================*/

/*================= 公有函数声明 ====================================*/
//EX_sim_saveHist 

extern void sim_flash_EraseSect_FromAdr(U8 chip, U32 address, U8 bWaitForFinish);
extern void sim_flash_Write_nByte(U8 chip, U8 *pStart, U32 num, U32 address, U8 bWaitForFinish);


extern void Sim_SaveHistTask(void);

/******************************************************************************
// END :
******************************************************************************/
#endif // __sim_saveHist_H__

