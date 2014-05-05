#ifndef __flsWrApplySave_H__
#define __flsWrApplySave_H__
/******************************************************************************
* @file    flsWrApplySave.h
* @author  yx
* @version V1.1
* @date    2013.9.22
* @brief   写flash管理。都是定地址存储。
		读在[PeriphSave] saveX.c里。
* @slave   "flsWrApplyBuf.h"

* 新task -> buf[] ： FlashSaveNew();
* buf[] -> 写flash:  FlsSave_Start();


* @Version history 
* V1.1, 2013.9.22
*	FlsResultNotificat()的结果，用U8表示，.0表示part0,.1表示part1.
* V1.0, 2013-07-23
* 
#include  "flsWrApplySave.h"
******************************************************************************/
//
#include  "prjCompileCon.h"
#include  "flsStoreBytesDef.h"
#include  "strFlsAdrDef.h"

/*================= extern ============================================*/
#ifdef  __flsWrApplySave_C__
#define EX_flsWrApplySave
#else
#define EX_flsWrApplySave extern 
#endif
/*================= 常数 ============================================*/

enum emFlsWrApplyStep{
	U_FlsWrApplyStep_01_Start = 1,
	U_FlsWrApplyStep_02_Part0 = 2, //
	U_FlsWrApplyStep_03_Part1 = 3, //
	U_FlsWrApplyStep_04_Read = 4, //
	U_FlsWrApplyStep_05_Notify = 5, //
	
	U_FlsWrApplyStep_MAX = 6, //
};

/*================= 结构体定义 ======================================*/

typedef struct{
	U8 step;
	
	U8 mPart;
	U8 PartMax;
	BOOL bHavePart2;
	U8 bSucc; //读出比较的结果 // .0=1=part0 Succ; .1=1=part1 Succ
}TFlsWrApply_st;


/*================= 私有函数声明 ====================================*/
#ifdef  __flsWrApplySave_C__

static TFlsWrApply_st  stSave;

static void flsSave_SetIdle(void);
static void flsSave_flsItem(U8 mReadWrite);

static void flsItm_OnePageCls_SaveOrRead(U8 mReadWrite);
static BOOL saveFlsItm_OnePageCls(void);
static BOOL rdFlsItm_OnePageCls(void);
static void flsItm_onePageCls_cacuAdr(U8 mPart, U8 *pChip, U32 *pAdr, U32 *pNum);

static void flsItm_Note_SaveOrRead(U8 mReadWrite);
static BOOL saveFlsItm_Note(void);
static BOOL rdFlsItm_Note(void);
static BOOL flsItm_Note_cacuAdr(U8 mPart, U8 *pChip, U32 *pAdr);


static void flsItm_LinkProg_SaveOrRead(U8 mReadWrite);
static BOOL saveFlsItm_LinkProg(void);
static BOOL rdFlsItm_LinkProg(void);
static BOOL flsItm_LinkProg_cacuAdr(U8 mPart, U8 *pChip, U32 *pAdr);


static void flsItm_Field_SaveOrRead(U8 mReadWrite);
static BOOL saveFlsItm_Field(void);
static BOOL rdFlsItm_Field(void);
static BOOL flsItm_Field_cacuAdr(U8 mPart, U8 *pChip, U32 *pAdr);

static void flsItm_RelateAddr_SaveOrRead(U8 mReadWrite);
static BOOL saveFlsItm_RelateAddr(void);
static BOOL rdFlsItm_RelateAddr(void);

static void flsItm_Disable_SaveOrRead(U8 mReadWrite);
static BOOL saveFlsItm_Disable(void);
static BOOL rdFlsItm_Disable(void);


//----------------------------------------------------
static void fls_step_Start(void); //添加sectHead标志
static void fls_step_Part(void);
static void fls_step_Notify(void);

static void fls_step_Notif_ReNewRam(void);
static void fls_step_Notif_ReNewState(void);
static void saveFlsItm_NotificatResult(U8 bSucc);

#endif  //__flsWrApplySave_C__
/*================= 公有函数声明 ====================================*/
#if U_SYS_Test_FlsApplyBuf == 1
extern void Sim_FlsApplyBuf(void);
#endif // U_SYS_Test_FlsApplyBuf

/*================= 公有函数声明-lib内部 ====================================*/
//EX_flsWrApplySave 

// 检查flash存储是否正确, SectorStart & CRC .
// only  before hist
// OUT: Set_FlsItemState()
extern void FlsSave_CheckFlash(void);
extern void FlsSave_CheckItem(U8 mFlsItem);
extern void flsSave_checkItemPart(U8 mFlsItem, U8 mPart);

// 
extern void FlsSave_Init(void);
extern BOOL bFlsSave_isIdle(void);

// "saveManage.c" 里 emSave_Opea_Item类，判断if有任务：
extern BOOL FlsSave_Start(void); //读出待存储的数据本身
extern void FlsSave_Exec(void);

/*================= 公有函数声明-lib外部 ====================================*/
//EX_flsWrApplySave 

//新存储项
extern BOOL FlashSaveNew(U8 mFlsItem, U8 taskId, U8 flsId, U8 *pSrc); 


/******************************************************************************
// END :
******************************************************************************/
#endif // __flsWrApplySave_H__

