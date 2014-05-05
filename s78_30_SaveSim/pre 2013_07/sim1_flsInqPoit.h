#ifndef __sim1_flsInqPoit_H__
#define __sim1_flsInqPoit_H__
/******************************************************************************
* @file    sim1_flsInqPoit.h
* @author  yx
* @version V1.0
* @date    2013-01-04
* @brief   
* 
#include  "sim1_flsInqPoit.h"
******************************************************************************/
//
#include  "prjCompileCon.h"
#include  "strFlsAdrDef.h"
#include  "flsBytesDef.h"
#include  "flsStoreBytesDef.h"

/*================= extern ============================================*/
#ifdef  __sim1_flsInqPoit_C__
#define EX_sim1_flsInqPoit
#else
#define EX_sim1_flsInqPoit extern 
#endif
/*================= ���� ============================================*/
//#define 
/*================= �ṹ�嶨�� ======================================*/

/*================= ���нṹ�������� ================================*/

/*================= ˽���к������� - ���� ====================================*/
#if U_SYS_Test_Flash_InqPoint == 1
#ifdef  __sim1_flsInqPoit_C__
//----------------------------------------------------------------------

// Sector��ȫ�ģ�
// ����ļ�¼��ȫ��ֻ�ǿ�ͷ2���ͽ�β2�����������Ե��߼����м���渽���ġ�
#define U_SimFlsPoit_Sector_MAX  U_InqPoint_FlsItem_SectMAX //0x20
#define U_SimFlsPoit_Item_1Sector  8
#define U_SimFlsPoit_Item_Mid      (U_SimFlsPoit_Item_1Sector - 3) //�ж�ʱ������ͷ2����β2�����м�Ķ��������ַ
static U8 vSimFlsData[U_SimFlsPoit_Sector_MAX][U_SimFlsPoit_Item_1Sector];  //1��ʾ�����ݡ�

#define U_SimFlsPoit_Part     0
#define U_SimFlsPoit_FlsItemCls  U_SimFlsPoit_FlsItmCls
static TFlsItemAddr stSimFlsItemAdr;

#define U_SimFlsPoit_signHave  0x01
#define U_SimFlsPoit_signSpace  0xFF

#define U_SimFlsPoit_TestNum_MAX  50
static U32 vSimPoit_yxFill[U_SimFlsPoit_TestNum_MAX][3];
static U32 vSimPoitResult[U_SimFlsPoit_TestNum_MAX][3];


static BOOL sim_initDat(U8 mIni); //ģ��flash����
static void test_initDat_01(void);
static void test_initDat_02(void);
static void test_initDat_03(void);
static void test_initDat_04(void);
static void test_initDat_05(void);
static void test_initDat_06(void);
static void test_initDat_07(void);
static void test_initDat_08(void);
static void test_initDat_09(void);
static void test_initDat_10(void);
static void test_initDat_11(void);
static void test_initDat_12(void);
static void test_initDat_13(void);
static void test_initDat_14(void);
static void test_initDat_15(void);
static void test_initDat_16(void);
static void test_initDat_17(void);
static void test_initDat_18(void);
static void test_initDat_30(void);
static void test_initDat_31(void);
static void test_initDat_32(void);
static void test_initDat_33(void);
static void test_initDat_34(void);
static void test_initDat_35(void);
static void test_initDat_36(void);

//
static void sim_InitPointBuf(void);
static BOOL sim_jdgPoint(U32 mTestNum);
static void sim_shouldPointBuf_0x20_0x1000(void); //0x20 sectors, 0x1000bytes/sector
//
static void test_initDat_head_set1(U32 mSect);
static void test_initDat_head_clr0(U32 mSect);
static BOOL bSim_sectorHead_have(U32 mSect);
static void test_initDat_item_set1(U32 mSect, U32 item);
static void test_initDat_item_clr0(U32 mSect, U32 item);
static BOOL bSim_item_have(U32 mSect, U32 item); //item=0��Ӧ��ַ0
static void test_initDat_AllHave(void);
static void test_initDat_AllSpace(void);
static void test_initDat_sectX_set1(U32 mSect);
static void test_initDat_sectX_clr0(U32 mSect);

static	BOOL sim_cacuSect_fromFlsAdr(U32 mAdr, U32 *pRtnSimSect);

//----------------------------------------------------------------------
#endif //__sim1_flsInqPoit_C__
#endif //U_SYS_Test_Flash_InqPoint

/*================= ���к������� ====================================*/
#if U_SYS_Test_Flash_InqPoint == 1

EX_sim1_flsInqPoit void sim_FlsInqPoit_Que_Test(void); //�������

//�ӿں���������flash�����

EX_sim1_flsInqPoit BOOL sim_FlsInqPoit_bSectHaveRecord(U8 chip, U32 mAdr, U8 mFlsItem);
EX_sim1_flsInqPoit BOOL sim_FlsInqPoit_b_1Item_OK(U8 chip, U32 mAdr);


#endif //U_SYS_Test_Flash_InqPoint
/******************************************************************************
// END :
******************************************************************************/
#endif // __sim1_flsInqPoit_H__

