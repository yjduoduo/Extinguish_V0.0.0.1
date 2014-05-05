#ifndef __flsAdrCalculate_H__
#define __flsAdrCalculate_H__
/******************************************************************************
* @file    flsAdrCalculate.h
* @author  yx
* @version V1.1
* @date    2013-07-23
* @brief   
* 
#include  "flsAdrCalculate.h"

V1.1, 增加FlsItm_sector_Total(); 2013.7.23, by yx;
******************************************************************************/
//
#include  "prjCompileCon.h"
#include  "strFlsAdrDef.h"

/*================= extern ============================================*/
#ifdef  __flsAdrCalculate_C__
#define EX_flsAdrCalculate
#else
#define EX_flsAdrCalculate extern 
#endif
/*================= 常数 ============================================*/
//#define 
/*================= 结构体定义 ======================================*/

/*================= 公有结构变量声明 ================================*/




/*================= 公有函数声明 ====================================*/
// EX_flsAdrCalculate 
extern U32 FlsItm_sector_start(U32 mAdr, U8 mFlsItem);
extern U32 FlsItm_sectorBefore_start(U32 mAdr, 
							U8 mFlsItem, TFlsItemAddr *pAdr);
extern U32 FlsItm_sectorNext_start(U32 mAdr, 
							U8 mFlsItem, TFlsItemAddr *pAdr);
extern U32 FlsItm_sector_Total(U8 mFlsItem, 
							TFlsItemAddr *pAdr);
extern U32 FlsItm_adr_sector_firItem(U32 mAdr, 
							U8 mFlsItem, U32 itemByte);
extern U32 FlsItm_adr_sector_LastItem(U32 mAdr, 
							U8 mFlsItem, U32 itemByte);
extern U32 FlsItm_adr_itemMe_start(U32 mAdr, U32 itemByte);
extern U32 FlsItm_adr_itemNext(U32 mAdr, 
							U8 mFlsItem, U32 oneItemBytes, 
							TFlsItemAddr *pAdr);
extern U32 FlsItm_adr_itemBefore(U32 mAdr, 
							U8 mFlsItem, U32 oneItemBytes, 
							TFlsItemAddr *pAdr);

extern U32 FlsItm_adr_inSector(U32 mAdr, U8 mFlsItem);
extern U32 FlsItm_adr_inSect_itmSequ(U32 mAdr, 
							U8 mFlsItem, U32 itemByte);

//剩余的条数
extern U32 FlsItm_adr_inSect_itmSpace(U32 mAdr, 
							U8 mFlsItem, U32 oneItemBytes);

/*================= 公有函数声明 ====================================*/
//EX_flsAdrCalculate 

extern U32 hist_sector_start(U32 mAdr);
extern U32 hist_adr_sector_firItem(U32 mAdr);
extern U32 hist_sector_LastItem_start(U32 mAdr);
extern U32 hist_sectorNext_start(U32 mAdr, TFlsItemAddr *pAdr);
extern U32 hist_sectorBefore_start(U32 mAdr, TFlsItemAddr *pAdr);
extern U32 hist_me_start(U32 mAdr); //一条记录
extern U32 hist_adr_itemNext(U32 mAdr, TFlsItemAddr *pAdr);
extern U32 hist_adr_itemBefore(U32 mAdr, TFlsItemAddr *pAdr);
extern U32 hist_adr_inSector(U32 mAdr);
extern U32 hist_adr_inSect_histSequ(U32 mAdr);

/******************************************************************************
// END :
******************************************************************************/
#endif // __flsAdrCalculate_H__

