#ifndef __saveDisable_H__
#define __saveDisable_H__
/******************************************************************************
* @file    saveDisable.h
* @author  yx
* @version V1.0
* @date    2013-01-04
* @brief   ����
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
/*================= ���� ============================================*/
//#define 
/*================= �ṹ�嶨�� ======================================*/

/*================= ���нṹ�������� ================================*/

/*================= ���к�������-lib�ⲿ ====================================*/
//EX_saveDisable 

/*================= ˽�к������� ====================================*/
#ifdef  __saveDisable_C__


// ��RAM��delete:
static BOOL bDeleteInRam_dsab(U8 *pBufS, U32 mAdrOffset);

// ��RAM�� add:
static BOOL bAddInRam_dsab(U8 *pBufS, TFlsDisable_un *pFlsDsabOne);

#endif  //__saveDisable_C__



/*================= ���к�������-lib�ڲ� ====================================*/
//EX_saveDisable 

// RAM ���޸����ݡ�
// IN: Ҫ��: pSecBufS.max = getFlsItem_1SectorBytes(mFlsItem);
extern BOOL FlsDisable_RamChange(U8 *pSecBufS, 
						 TFlsDisable_un *pDsabOne);

extern BOOL bFoundInRam_Dsab_EquDete(TDev_un *pDev, 
							  U8 *pBufS, U32 mAdrOffset,
							  U32 *pRtnOffset);

/*================= ���к�������-lib�ⲿ ====================================*/
//EX_saveDisable 

// if dete �Ƿ���buf�ڣ�
// use: ��ռ��public buf.
extern BOOL FlsJdg_bDisableInBuf(TDev_un *pDev);

// buf item:
// use: ��ռ��public buf.
extern U32 FlsGet_DisableBufItemNum(void);

// TRUE = ����� �н����
// FALSE = ������󣬻��ֹ����
// use: ��ռ��public buf.
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

