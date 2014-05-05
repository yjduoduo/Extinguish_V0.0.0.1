#ifndef __saveRelateAddr_H__
#define __saveRelateAddr_H__
/******************************************************************************
* @file    saveRelateAddr.h
* @author  yx
* @version V1.0
* @date    2013-10-24
* @brief   其他控制器 相关地址
* 
#include  "saveRelateAddr.h"
******************************************************************************/
//
#include  "prjCompileCon.h"
#include  "strFlsItmStruct.h"

/*================= extern ============================================*/
#ifdef  __saveRelateAddr_C__
#define EX_saveRelateAddr
#else
#define EX_saveRelateAddr extern 
#endif
/*================= 常数 ============================================*/
//#define 
/*================= 结构体定义 ======================================*/

/*================= 公有结构变量声明 ================================*/

/*================= 私有函数声明 ====================================*/
#ifdef  __saveRelateAddr_C__

BOOL bEquLoop_RelatDeteAndDev( 
					TFlsRelateDeteOne_st *pRelatDete, TDev_un *pDev);

// read sector firstOne:
// out: pBuf
static void readOne_relateDete_SecFirstOne(
							U8 mChip, U32 mFromAdr, U8 *pBuf);

// this sector stored is :
static BOOL bSectorFir_IsThisMachineLoop(TDev_un *pDev, 
							U8 mChip, U32 mFromAdr);

// sector isSpace:
static BOOL bSectorFir_IsRelatDeteSpace(U8 mChip, U32 mFromAdr);

// 在RAM里查找 相同的loop:
static BOOL bFoundInRam_EquMachineLoop(TDev_un *pDev, 
							  U8 *pBufS, U32 mAdrOffset,
							  U32 *pRtnOffset);
// 在RAM里查找 相同的 dete:
static BOOL bFoundInRam_EquDete(TDev_un *pDev, 
							  U8 *pBufS, U32 mAdrOffset,
							  U32 *pRtnOffset);
// 在RAM里查找 space:
static BOOL bFoundInRam_Space(U8 *pBufS, U32 mAdrOffset,
							  U32 *pRtnOffset);
// 在RAM里判断，从mAdrOffset之后，全部Space:
static BOOL bJdgInRam_AllSpace(U8 *pBufS, U32 mAdrOffset);

// 判断buf内，同地址dete, 设置equal:
// 不包括 emFlsRelatDeteOpea_ClrOne;
BOOL flsRelateDete_OneDeteEquSet(U8 *pSecBufS, 
						 U8 mOpeaCls, 
						 TFlsRelateDeteOne_st *pOne);
						 
// 判断 1sector 正确。
// OUT: TRUE = !FULL & EquLoop;
BOOL bFlsRelateDete_OneLoopRight(U8 mChip, U32 mFromAdr);

static void relateDete_change(U8 mOpeaCls, 
						TFlsRelateDeteOne_st *pInFlash,
						TFlsRelateDeteOne_st *pNew);
static BOOL relateDete_add(U8 mOpeaCls, 
						TFlsRelateDeteOne_st *pInFlash,
						TFlsRelateDeteOne_st *pNew);
static void relateDete_clrOne(TFlsRelateDeteOne_st *pInFlash);

// RAM里，找到空位置，并添加：
static BOOL relateDete_findSpaceAndNew(U8 mOpeaCls,
						U8 *pSectBufS, U32 mAdrOffsetJdgStart, 
						TFlsRelateDeteOne_st *pOne);

// RAM 里修改数据。
// IN: 要求: pSecBufS.max = getFlsItem_1SectorBytes(mFlsItem);
// 若删除，找到一个以后要继续找；若buf已空，allSetFF;
// 若添加，注意sectorHead;
BOOL flsRelateDete_OneRamChange(U8 *pSecBufS, 
						 TFlsRelateDeteHead_st *pHead, 
						 TFlsRelateDeteOne_st *pOne);


#endif  //__saveRelateAddr_C__

/*================= 公有函数声明-lib内部 ====================================*/
//EX_saveRelateAddr 

// 查找空的 sector, 以存储新回路
extern BOOL bFlsRelateDete_FoundSpaceSector(U8 mPart, 
										U32 *pRtnSecFirAdr);
// 查找 相同回路的sector：
extern BOOL bFlsRelateDete_FoundEquMachineLoopSector( 
				TDev_un *pDev, U8 mPart, U32 *pRtnSecFirAdr);

// 检查 flash 每回路里，是否地址已满 0x1000/U_FLS_RelateDete_One_BYTE_MAX:
extern BOOL bFlsRelateDete_LoopFull(void);

// 在RAM里判断，判断某地址的配置与其一致：
extern BOOL bJdgInRam_FlsRelateDete_EquSet(U8 *pSecBufS, 
						 TFlsRelateDeteHead_st *pHead, 
						 TFlsRelateDeteOne_st *pOne);
// 在RAM里判断，判断某dete已删除：
extern BOOL bJdgInRam_FlsRelateDete_HaveClr(U8 *pSecBufS,
						 TFlsRelateDeteOne_st *pOne);

// RAM 里修改数据。
// IN: 要求: pSecBufS.max = getFlsItem_1SectorBytes(mFlsItem);
// 有连续地址的参数，在pHead里。
extern BOOL FlsRelateDete_RamChange(U8 *pSecBufS, 
						 TFlsRelateDeteHead_st *pHead, 
						 TFlsRelateDeteOne_st *pOne);

/*================= 公有函数声明-lib外部 ====================================*/
//EX_saveRelateAddr 

extern BOOL FlsRd_isRelateDete(TDev_un *pDev);
extern BOOL FlsRd_RelateDete_Note(TDev_un *pDev, U8 *pRtnNote);

// IN: mOpeaCls: emFlsRelateDeteOpeaCls 其一:
// IN: mOpeaCls = emFlsRelatDeteOpea_Clr1Loop;
extern BOOL FlsSave_RelateDete_ClrOneLoop(
						TDev_un *pDev,
						U8 taskId, U8 flsId);
// IN: mOpeaCls = emFlsRelatDeteOpea_ClrOne, 
//				emFlsRelatDeteOpea_ChangeRelate;
extern BOOL FlsSave_RelateDete_RelateOne(U8 mOpeaCls,
						TDev_un *pDev, BOOL bRelate,
						U8 taskId, U8 flsId);
// IN: mOpeaCls = emFlsRelatDeteOpea_ChangeRelate;
extern BOOL FlsSave_RelateDete_RelateSerial(
						TFlsRelateDeteHead_st *pRelateHead,
						TDev_un *pDev,  BOOL bRelate,
						U8 taskId, U8 flsId);
// IN: mOpeaCls = emFlsRelatDeteOpea_ChangeNote, 
//				emFlsRelatDeteOpea_ChangeRelate;
//				emFlsRelatDeteOpea_ChangeAll ;
extern BOOL FlsSave_RelateDete_One(U8 mOpeaCls,
						TDev_un *pDev, 
						 BOOL bRelate, U8 *pNote,
						U8 taskId, U8 flsId);






/******************************************************************************
// END :
TFlsRelateDeteOne_st    相关地址
emFlsRelateDeteOpeaCls    TFlsRelateDeteHead_st
******************************************************************************/
#endif // __saveRelateAddr_H__

