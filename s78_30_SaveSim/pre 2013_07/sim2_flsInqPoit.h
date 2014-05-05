#ifndef __sim2_flsInqPoit_H__
#define __sim2_flsInqPoit_H__
/******************************************************************************
* @file    sim2_flsInqPoit.h
* @author  yx
* @version V1.0
* @date    2013-01-04
* @brief   
* 
#include  "sim2_flsInqPoit.h"
******************************************************************************/
//
#include  "prjCompileCon.h"
#include  "strFlsAdrDef.h"
#include  "flsBytesDef.h"
#include  "flsStoreBytesDef.h"

/*================= extern ============================================*/
#ifdef  __sim2_flsInqPoit_C__
#define EX_sim2_flsInqPoit
#else
#define EX_sim2_flsInqPoit extern 
#endif
/*================= 常数 ============================================*/
//#define 
/*================= 结构体定义 ======================================*/

/*================= 公有结构变量声明 ================================*/

/*================= 私有有函数声明 - 测试 ====================================*/
#if U_SYS_Test_Flash_InqPoint == 1
#ifdef  __sim2_flsInqPoit_C__
//----------------------------------------------------------------------
#define U_SimFlsPoit_flsItem_ByteMax  (U_InqPoint_FlsItem_SectMAX * U_SimFlsPoit_1SectorBytes)

#define U_SimFlsPoit_Item_MAX      (U_SimFlsPoit_flsItem_ByteMax / U_SimFlsPoit_1ItemBytes)
#define U_SimFlsPoit_Sector_MAX        (U_SimFlsPoit_flsItem_ByteMax / U_SimFlsPoit_1SectorBytes)
#define U_SimFlsPoit_Item_1Sector  (U_SimFlsPoit_1SectorBytes          / U_SimFlsPoit_1ItemBytes)
static U8 vSimFlsData[U_SimFlsPoit_Sector_MAX][U_SimFlsPoit_Item_1Sector];  // U_SimFlsPoit_signHave 表示有数据。

#define U_SimFlsPoit_Part     0
#define U_SimFlsPoit_FlsItemCls  U_SimFlsPoit_FlsItmCls
static TFlsItemAddr stSimFlsItemAdr;

#define U_SimFlsPoit_signHave  0x01
#define U_SimFlsPoit_signSpace  0xFF

static void sim_nextAdr(void);
static BOOL sim_jdgPoint(void);
static void sim_erase_next_sector(U32 mNowSect);
static void sim_AddOne(U32 store_sequItm);
static U32 sim_adr_inc(U32 mAdr);
static void sim_endPoint_inc(void);
static BOOL sim_cacuSectItem(U32 mAdr, U32 *pSec, U32 *pItmInSect);



static void test_initDat_AllHave(void);
static void test_initDat_AllSpace(void);
static void test_initDat_sectX_set1(U32 mSect);
static void test_initDat_sectX_clr0(U32 mSect);

static void test_initDat_head_set1(U32 mSect);
static void test_initDat_head_clr0(U32 mSect);
static BOOL bSim_sectorHead_have(U32 mSect);
static void test_initDat_item_set1(U32 mSect, U32 item);
static void test_initDat_item_clr0(U32 mSect, U32 item);
static BOOL bSim_item_have(U32 mSect, U32 item); //item=0对应地址0

static	BOOL sim_cacuSect_fromFlsAdr(U32 mAdr, U32 *pRtnSimSect);
//----------------------------------------------------------------------
#endif //__sim2_flsInqPoit_C__
#endif //U_SYS_Test_Flash_InqPoint


/*================= 公有函数声明 ====================================*/

EX_sim2_flsInqPoit void sim_FlsInqPoit_Que_Test(void); //测试入口

//接口函数，仿真flash读结果

EX_sim2_flsInqPoit BOOL sim_FlsInqPoit_bSectHaveRecord(U8 chip, U32 mAdr, U8 mFlsItem);
EX_sim2_flsInqPoit BOOL sim_FlsInqPoit_b_1Item_OK(U8 chip, U32 mAdr);

/******************************************************************************
// END :
******************************************************************************/
#endif // __sim2_flsInqPoit_H__

