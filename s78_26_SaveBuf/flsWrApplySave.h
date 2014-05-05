#ifndef __flsWrApplySave_H__
#define __flsWrApplySave_H__
/******************************************************************************
* @file    flsWrApplySave.h
* @author  yx
* @version V1.1
* @date    2013.9.22
* @brief   дflash�������Ƕ���ַ�洢��
		����[PeriphSave] saveX.c�
* @slave   "flsWrApplyBuf.h"

* ��task -> buf[] �� FlashSaveNew();
* buf[] -> дflash:  FlsSave_Start();


* @Version history 
* V1.1, 2013.9.22
*	FlsResultNotificat()�Ľ������U8��ʾ��.0��ʾpart0,.1��ʾpart1.
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
/*================= ���� ============================================*/

enum emFlsWrApplyStep{
	U_FlsWrApplyStep_01_Start = 1,
	U_FlsWrApplyStep_02_Part0 = 2, //
	U_FlsWrApplyStep_03_Part1 = 3, //
	U_FlsWrApplyStep_04_Read = 4, //
	U_FlsWrApplyStep_05_Notify = 5, //
	
	U_FlsWrApplyStep_MAX = 6, //
};

/*================= �ṹ�嶨�� ======================================*/

typedef struct{
	U8 step;
	
	U8 mPart;
	U8 PartMax;
	BOOL bHavePart2;
	U8 bSucc; //�����ȽϵĽ�� // .0=1=part0 Succ; .1=1=part1 Succ
}TFlsWrApply_st;


/*================= ˽�к������� ====================================*/
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
static void fls_step_Start(void); //���sectHead��־
static void fls_step_Part(void);
static void fls_step_Notify(void);

static void fls_step_Notif_ReNewRam(void);
static void fls_step_Notif_ReNewState(void);
static void saveFlsItm_NotificatResult(U8 bSucc);

#endif  //__flsWrApplySave_C__
/*================= ���к������� ====================================*/
#if U_SYS_Test_FlsApplyBuf == 1
extern void Sim_FlsApplyBuf(void);
#endif // U_SYS_Test_FlsApplyBuf

/*================= ���к�������-lib�ڲ� ====================================*/
//EX_flsWrApplySave 

// ���flash�洢�Ƿ���ȷ, SectorStart & CRC .
// only  before hist
// OUT: Set_FlsItemState()
extern void FlsSave_CheckFlash(void);
extern void FlsSave_CheckItem(U8 mFlsItem);
extern void flsSave_checkItemPart(U8 mFlsItem, U8 mPart);

// 
extern void FlsSave_Init(void);
extern BOOL bFlsSave_isIdle(void);

// "saveManage.c" �� emSave_Opea_Item�࣬�ж�if������
extern BOOL FlsSave_Start(void); //�������洢�����ݱ���
extern void FlsSave_Exec(void);

/*================= ���к�������-lib�ⲿ ====================================*/
//EX_flsWrApplySave 

//�´洢��
extern BOOL FlashSaveNew(U8 mFlsItem, U8 taskId, U8 flsId, U8 *pSrc); 


/******************************************************************************
// END :
******************************************************************************/
#endif // __flsWrApplySave_H__

