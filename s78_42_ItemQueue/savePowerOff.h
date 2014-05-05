#ifndef __savePowerOff_H__
#define __savePowerOff_H__
/******************************************************************************
* @file    savePowerOff.h
* @author  yx
* @version V1.0
* @date    2013-01-04
* @brief   关机时间
* 
#include  "savePowerOff.h"
******************************************************************************/
//
#include  "prjCompileCon.h"
#include  "strFlsAdrDef.h"
#include  "strFlsItmStruct.h"

/*================= extern ============================================*/
#ifdef  __savePowerOff_C__
#define EX_savePowerOff
#else
#define EX_savePowerOff extern 
#endif
/*================= 常数 ============================================*/
enum emsavePowerOffStep{
	U_savePowerOffStep_01_Start = 1,
	U_savePowerOffStep_02_EraseNextSector = 2,
	U_savePowerOffStep_03_WriteSectorHead = 3,
	U_savePowerOffStep_04_WriteNew = 4,
	U_savePowerOffStep_05_NextSectorHead = 5,
	U_savePowerOffStep_06_PartNext = 6,
	U_savePowerOffStep_07_Finish = 7,
};
/*================= 结构体定义 ======================================*/

/*================= 公有结构变量声明 ================================*/

typedef struct{
	U8 bOpeaIng;
	U8 step;
	BOOL bNeedEraseNextSector;
	U32 adrSectNext;
	
	U8 mFlsItem;
	U8 mPart;  //指针的part
	TFlsItemAddr stAdr;
	
	//新写入的地址
	TFlsPwrOff_un unNewClock; // U_FLS_1PowerOff_BYTE_MAX
	
}TSavePowerOff_st;


/*================= 私有函数声明 ====================================*/
#ifdef  __savePowerOff_C__

static TSavePowerOff_st  stPwrOff;
static U8 vRdBuf[U_FLS_1PowerOff_BYTE_MAX];

static void flsWr_pwrOff_SectorHead(void); //写 sectorNext.head

static void wr_Step_01_Start(void);
static void wr_Step_02_EraseNextSector(void);
static void wr_Step_03_WriteSectorHead(void);
static void wr_Step_04_WriteNew(void);
static void wr_Step_05_NextSectorHead(void);

#endif  //__savePowerOff_C__


/*================= 公有函数声明-lib外部 ====================================*/
// EX_savePowerOff
extern BOOL FlsRd_PwrOff(TEvtClock_st  *pRtnClock);
extern BOOL FlsWr_pwrOff_New(TEvtClock_st  *pStClock);

/*================= 公有函数声明-lib内部 ====================================*/
// EX_savePowerOff

extern void FlsWr_pwrOff_Init(void);

extern void FlsWr_pwrOff_Exec(void);

extern void FlsWr_pwrOff_SetFinish(void);
extern BOOL bFlsWr_pwrOff_Finished(void);
extern BOOL bFlsWr_pwrOff_isIdle(void);


/******************************************************************************
// END :
******************************************************************************/
#endif // __savePowerOff_H__

