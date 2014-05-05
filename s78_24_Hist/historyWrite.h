#ifndef __historyWrite_H__
#define __historyWrite_H__
/******************************************************************************
* @file    historyWrite.h
* @author  yx
* @version V1.0
* @date    2013-07-23
* @brief   д��ʷ��¼�Ĺ��̿��ơ���������ָ�롣
		ÿhistClsÿpart������һ�飬���ֻ��ʾ��sectEnd.  
		����part1: wrHist_Step_10_NextPart(); wrHist_Step_06_NextSectorHead();
* @slave   saveHistPoint.c ��ȫ��������¡�
* @master   saveManage.c
* 
#include  "historyWrite.h"
******************************************************************************/
//
#include  "prjCompileCon.h"
#include  "strFlsAdrDef.h"
#include  "strFlsItmStruct.h"
#include  "bufCircle.h"

/*================= extern ============================================*/
#ifdef  __historyWrite_C__
#define EX_historyWrite
#else
#define EX_historyWrite extern 
#endif
/*================= ���� ============================================*/

enum emHistWrStep{
	U_HistWrStep_01_Start = 1,
	U_HistWrStep_02_PointPart0 = 2, //  ��hist.part0. point.part0ָ��
	U_HistWrStep_03_EraseNextSector = 3,
	U_HistWrStep_04_WriteSectorHead = 4,
	U_HistWrStep_05_WriteNew = 5,
	U_HistWrStep_06_NextSectorHead = 6,
	U_HistWrStep_07_PointPart1 = 7, //  ��hist.part0. point.part1ָ��
	
	U_HistWrStep_10_NextPart = 10,
	U_HistWrStep_11_NextHistCls = 11,
	U_HistWrStep_12_Finish = 12,
};
	
/*================= ���нṹ�������� ================================*/

/*================= ˽�к������� ====================================*/
#ifdef  __historyWrite_C__



static BOOL wrHist_Step_01_Start(void);
static void wrHist_Step_01_Start__newStep(void);
static void wrHist_Step_02_PointPart0(void);

static void wrHist_Step_03_EraseNextSector(void);
static void wrHist_Step_04_WriteSectorHead(void);
static void wrHist_Step_05_WriteNew(void);
static void wrHist_Step_06_NextSectorHead(void);
static void wrHist_Step_07_PointPart1(void);
static void wrHist_Step_10_NextPart(void);
static void wrHist_Step_11_NextHistCls(void);

// *master: 	wrHist_Step_01_Start__newStep()
// *master: 	wrHist_Step_03_EraseNextSector()
static void wrHist_Step__wrSectHead_orHist(void); //step=��histEnd=sectorHead,��Ҫдhead.

//master: wrHist_Step_04_WriteSectorHead(); 
//master: wrHist_Step_06_NextSectorHead();
static void wrHist_Step__jdgSectorHead_andWrHead(void); //����sectorHead,д&�޸�end.
//master: wrHist_Step__jdgSectorHead_andWrHead();
static void wrHist_Step__wrSectorHead(void); //д sector.head


static void set_hist_endAdr(U32 mAdrEnd);
static void set_hist_headAdr(U32 mAdrHead);
static U32 get_hist_headAdr(void);
static U32 get_hist_endAdr(void);

static void flsWr_hstPoint_init(U8 mHistCls, U8 mHistPart, U8 mPointPart);
static BOOL flsWr_hist_1Cls1Part_init(U8 mHistCls, U8 mHistPart);

void flsWr_hist_1Cls1Part_sectWillFull(void);


#endif  //__historyWrite_C__

/*================= ���к�������-lib�ڲ� ====================================*/
EX_historyWrite BOOL FlsWr_Hist_Start(void);
EX_historyWrite void FlsWr_Hist_Exec(void);

// 
EX_historyWrite void FlsWr_Hist_Init(void);
EX_historyWrite BOOL bFlsWr_Hist_Finished(void);
EX_historyWrite BOOL bFlsWr_Hist_isIdle(void);
EX_historyWrite void FlsWr_Hist_SetFinish(void);


/******************************************************************************
// END :
******************************************************************************/
#endif // __historyWrite_H__

