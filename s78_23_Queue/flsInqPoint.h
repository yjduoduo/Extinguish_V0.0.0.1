#ifndef __flsInqPoint_H__
#define __flsInqPoint_H__
/******************************************************************************
* @file    flsInqPoint.h
* @author  yx
* @version V1.0
* @date    2013-07-05
* @brief   队列类型的存储，查找指针。
* @Master  strFlsQue.c    
* 
#include  "flsInqPoint.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

#include  "strFlsAdrDef.h"
#include  "strFlsQue.h"
/*================= extern ============================================*/
#ifdef  __flsInqPoint_C__
#define EX_flsInqPoint
#else
#define EX_flsInqPoint extern 
#endif
/*================= 常数 ============================================*/

/*================= 私有函数声明 ====================================*/
#ifdef  __flsInqPoint_C__


// 查找指针：
BOOL flsInq_1Cls_JdgPoint_Sector0_haveData(
			U8 mPart, U8 mFlsItem, TFlsItemAddr *pAdr
			);
BOOL flsInq_1Cls_JdgPoint_Sector0_space(
			U8 mPart, U8 mFlsItem, TFlsItemAddr *pAdr
			);


// 查找 sector head:
BOOL flsInqSect_headSpace_sectNextToE(
			TFlsItemAddr *pAdr, U32 mAdrNow, U8 mFlsItem, U32 *pRtnAdr
			);
BOOL flsInqSect_headHave_sectNextToE(
			TFlsItemAddr *pAdr, U32 mAdrNow, U8 mFlsItem, U32 *pRtnAdr
			);

	BOOL flsInqSect_headSpaOrHave_sectNextToE(
			TFlsItemAddr *pAdr, U32 mAdrNow, U8 mFlsItem, U32 *pRtnAdr,
			BOOL bInquireSectorHaveData
			);
	
// 查找末条space的sector，找sector内 0~ space的位置。
BOOL flsInqItm_inSect_EndSpace(
			TFlsItemAddr *pAdr, U32 *pRtnAdr
			);
// 查找 sector 末条 space :
BOOL flsInqSect_LastItmSpace_EtoS(TFlsItemAddr *pAdr, U32 *pRtnAdr);
	
//Sector 0:
BOOL flsInq_Sector0_Have(TFlsItemAddr *pAdr, U8 mFlsItem);

BOOL flsInq_have_inSector_Hto0(U8 chip, U32 mAdr, U32 *pRtnAdr);


#endif //__flsInqPoint_C__
/*================= 公有函数声明 ====================================*/


/*================= 公有函数声明-lib内部 ====================================*/
//sector内查找：
EX_flsInqPoint BOOL flsInq_space_inSector_0toH(U8 chip, U32 mAdr, U32 *pRtnAdr);

// 若用.c里的函数，需要先初始化参数：
EX_flsInqPoint BOOL flsInq_SetQueueProp(U8 mFlsItem, U8 mPart);

EX_flsInqPoint BOOL flsInq_1Cls_JdgPoint(
			U8 mFlsItem, U8 mPart, TFlsQueuePoint_st *pRtnHeadEnd
			);

/******************************************************************************
// END :
******************************************************************************/
#endif // __flsInqPoint_H__

