#ifndef __saveDisable_H__
#define __saveDisable_H__
/******************************************************************************
* @file    saveDisable.h
* @author  yx
* @version V1.0
* @date    2013-01-04
* @brief   屏蔽
* 
#include  "saveDisable.h"
******************************************************************************/
//
#include  "prjCompileCon.h"
#include  "strFlsItmStruct.h"

/*================= extern ============================================*/
#ifdef  __saveDisable_C__
#define EX_saveDisable
#else
#define EX_saveDisable extern 
#endif
/*================= 常数 ============================================*/
//#define 
/*================= 结构体定义 ======================================*/

/*================= 公有结构变量声明 ================================*/

/*================= 公有函数声明-lib外部 ====================================*/
//EX_saveDisable 

/*================= 私有函数声明 ====================================*/
#ifdef  __saveDisable_C__


// 在RAM里delete:
static BOOL bDeleteInRam_dsab(U8 *pBufS, U32 mAdrOffset);

// 在RAM里 add:
static BOOL bAddInRam_dsab(U8 *pBufS, TFlsDisable_un *pFlsDsabOne);

#endif  //__saveDisable_C__



/*================= 公有函数声明-lib内部 ====================================*/
//EX_saveDisable 

// RAM 里修改数据。
// IN: 要求: pSecBufS.max = getFlsItem_1SectorBytes(mFlsItem);
extern BOOL FlsDisable_RamChange(U8 *pSecBufS, 
						 TFlsDisable_un *pDsabOne);

extern BOOL bFoundInRam_Dsab_EquDete(TDev_un *pDev, 
							  U8 *pBufS, U32 mAdrOffset,
							  U32 *pRtnOffset);

/*================= 公有函数声明-lib外部 ====================================*/
//EX_saveDisable 

// if dete 是否在buf内：
// use: 不占用public buf.
extern BOOL FlsJdg_bDisableInBuf(TDev_un *pDev);

// buf item:
// use: 不占用public buf.
extern U32 FlsGet_DisableBufItemNum(void);

// TRUE = 允许读 有结果；
// FALSE = 定义错误，或禁止读。
// use: 不占用public buf.
extern BOOL FlsRd_DisableInBuf(U32 mSequ, BOOL *bRtnDevValid, 
								TFlsDisable_un *pRtnDsabOne);

extern BOOL FlsAdd_Disable(TDev_un *pDev, BOOL bDisable,
								U8 taskId, U8 flsId);


/******************************************************************************
// END :
TFlsDisable_un
U8 mFlsItem = getFlsItem_Disable();
U32 mOffsetMax = getFlsItem_1SectorBytes(mFlsItem);
******************************************************************************/
#endif // __saveDisable_H__

