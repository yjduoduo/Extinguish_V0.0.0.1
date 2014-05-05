#ifndef __strFlsItmStrCacu_H__
#define __strFlsItmStrCacu_H__
/******************************************************************************
* @file    strFlsItmStrCacu.h // WrFlsApply 写fls task分配空间
* @author  yx
* @version V1.0
* @date    2013-07-23
* @brief   
* 
#include  "strFlsItmStrCacu.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

#include  "strDevice.h"
#include  "strClock.h"
#include  "flsStoreBytesDef.h"
#include  "strFlsAdrDef.h"

#include  "strFlsItmStruct.h"
/*================= extern ============================================*/
#ifdef  __strFlsItmStrCacu_C__
#define EX_strFlsItmStrCacu
#else
#define EX_strFlsItmStrCacu extern 
#endif

/*================= 公有函数声明 ====================================*/
extern U32 GetFlsItemBufBytes(U8 mFlsItem);

extern BOOL bFlsSectorStart_isItem(U8 chip, U32 mAdr, U8 mFlsItem);
extern void Init_StrFlsSectStart(U8 mFlsItem, 
									TFlsSecStart_un *pRtnSecStart
									);


/******************************************************************************
// END :
******************************************************************************/
#endif // __strFlsItmStrCacu_H__

