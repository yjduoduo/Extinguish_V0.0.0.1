#ifndef __saveHistPoint_H__
#define __saveHistPoint_H__
/******************************************************************************
* @file    saveHistPoint.h
* @author  yx
* @version V1.0
* @date    2013-07-08
* @brief   保存历史记录的指针，历史记录每增加1sector保存一次。和powerOff一样处理。
* @master  historyWrite.c
* 
#include  "saveHistPoint.h"
******************************************************************************/
//
#include  "prjCompileCon.h"
#include  "strFlsAdrDef.h"
#include  "strFlsItmStruct.h"

/*================= extern ============================================*/
#ifdef  __saveHistPoint_C__
#define EX_saveHistPoint
#else
#define EX_saveHistPoint extern 
#endif
/*================= 常数 ============================================*/
enum emSaveHistPointStep{
	U_SaveHistPointStep_01_Start = 1,
	U_SaveHistPointStep_02_EraseNextSector = 2,
	U_SaveHistPointStep_03_WriteSectorHead = 3,
	U_SaveHistPointStep_04_WriteNew = 4,
	U_SaveHistPointStep_05_NextSectorHead = 5,
	U_SaveHistPointStep_06_Finish = 6,
};
/*================= 结构体定义 ======================================*/

/*================= 公有结构变量声明 ================================*/

typedef struct{
	U8 bOpeaIng;
	U8 step;
	BOOL bNeedEraseNextSector;
	U32 adrSectNext;
	
	U8 mHistCls;
	U8 mFlsItem;
	U8 mPart;  //指针的part
	TFlsItemAddr stAdr;
	
	//新写入的地址
	THistPoint_un unNewAdr; //U_FLS_1HistPoint_BYTE_MAX
	
}TSaveHistPoint_st;


/*================= 私有函数声明 ====================================*/
#ifdef  __saveHistPoint_C__

static TSaveHistPoint_st  stHistPt;

void flsWr_histPoint_SectorHead(void); //写 sectorNext.head

static void wrHp_Step_01_Start(void);
static void wrHp_Step_02_EraseNextSector(void);
static void wrHp_Step_03_WriteSectorHead(void);
static void wrHp_Step_04_WriteNew(void);
static void wrHp_Step_05_NextSectorHead(void);

#endif  //__saveHistPoint_C__

/*================= 公有函数声明-lib内部 ====================================*/

EX_saveHistPoint void FlsWr_HistPoint_Init(void);
EX_saveHistPoint BOOL FlsWr_HistPoint_New(U8 mHistCls,  
						U8 mHistPart, U8 mPointPart,
						TFlsQueuePoint_st  mStHistPoint);
EX_saveHistPoint void FlsWr_HistPoint_Exec(void);

EX_saveHistPoint void FlsWr_HistPoint_SetFinish(void);
EX_saveHistPoint BOOL bFlsWr_HistPoint_Finished(void);
EX_saveHistPoint BOOL bFlsWr_HistPoint_isIdle(void);


/******************************************************************************
// END :
******************************************************************************/
#endif // __saveHistPoint_H__

