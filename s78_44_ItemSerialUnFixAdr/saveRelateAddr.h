#ifndef __saveRelateAddr_H__
#define __saveRelateAddr_H__
/******************************************************************************
* @file    saveRelateAddr.h
* @author  yx
* @version V1.0
* @date    2013-10-24
* @brief   ���������� ��ص�ַ
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
/*================= ���� ============================================*/
//#define 
/*================= �ṹ�嶨�� ======================================*/

/*================= ���нṹ�������� ================================*/

/*================= ˽�к������� ====================================*/
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

// ��RAM����� ��ͬ��loop:
static BOOL bFoundInRam_EquMachineLoop(TDev_un *pDev, 
							  U8 *pBufS, U32 mAdrOffset,
							  U32 *pRtnOffset);
// ��RAM����� ��ͬ�� dete:
static BOOL bFoundInRam_EquDete(TDev_un *pDev, 
							  U8 *pBufS, U32 mAdrOffset,
							  U32 *pRtnOffset);
// ��RAM����� space:
static BOOL bFoundInRam_Space(U8 *pBufS, U32 mAdrOffset,
							  U32 *pRtnOffset);
// ��RAM���жϣ���mAdrOffset֮��ȫ��Space:
static BOOL bJdgInRam_AllSpace(U8 *pBufS, U32 mAdrOffset);

// �ж�buf�ڣ�ͬ��ַdete, ����equal:
// ������ emFlsRelatDeteOpea_ClrOne;
BOOL flsRelateDete_OneDeteEquSet(U8 *pSecBufS, 
						 U8 mOpeaCls, 
						 TFlsRelateDeteOne_st *pOne);
						 
// �ж� 1sector ��ȷ��
// OUT: TRUE = !FULL & EquLoop;
BOOL bFlsRelateDete_OneLoopRight(U8 mChip, U32 mFromAdr);

static void relateDete_change(U8 mOpeaCls, 
						TFlsRelateDeteOne_st *pInFlash,
						TFlsRelateDeteOne_st *pNew);
static BOOL relateDete_add(U8 mOpeaCls, 
						TFlsRelateDeteOne_st *pInFlash,
						TFlsRelateDeteOne_st *pNew);
static void relateDete_clrOne(TFlsRelateDeteOne_st *pInFlash);

// RAM��ҵ���λ�ã�����ӣ�
static BOOL relateDete_findSpaceAndNew(U8 mOpeaCls,
						U8 *pSectBufS, U32 mAdrOffsetJdgStart, 
						TFlsRelateDeteOne_st *pOne);

// RAM ���޸����ݡ�
// IN: Ҫ��: pSecBufS.max = getFlsItem_1SectorBytes(mFlsItem);
// ��ɾ�����ҵ�һ���Ժ�Ҫ�����ң���buf�ѿգ�allSetFF;
// ����ӣ�ע��sectorHead;
BOOL flsRelateDete_OneRamChange(U8 *pSecBufS, 
						 TFlsRelateDeteHead_st *pHead, 
						 TFlsRelateDeteOne_st *pOne);


#endif  //__saveRelateAddr_C__

/*================= ���к�������-lib�ڲ� ====================================*/
//EX_saveRelateAddr 

// ���ҿյ� sector, �Դ洢�»�·
extern BOOL bFlsRelateDete_FoundSpaceSector(U8 mPart, 
										U32 *pRtnSecFirAdr);
// ���� ��ͬ��·��sector��
extern BOOL bFlsRelateDete_FoundEquMachineLoopSector( 
				TDev_un *pDev, U8 mPart, U32 *pRtnSecFirAdr);

// ��� flash ÿ��·��Ƿ��ַ���� 0x1000/U_FLS_RelateDete_One_BYTE_MAX:
extern BOOL bFlsRelateDete_LoopFull(void);

// ��RAM���жϣ��ж�ĳ��ַ����������һ�£�
extern BOOL bJdgInRam_FlsRelateDete_EquSet(U8 *pSecBufS, 
						 TFlsRelateDeteHead_st *pHead, 
						 TFlsRelateDeteOne_st *pOne);
// ��RAM���жϣ��ж�ĳdete��ɾ����
extern BOOL bJdgInRam_FlsRelateDete_HaveClr(U8 *pSecBufS,
						 TFlsRelateDeteOne_st *pOne);

// RAM ���޸����ݡ�
// IN: Ҫ��: pSecBufS.max = getFlsItem_1SectorBytes(mFlsItem);
// ��������ַ�Ĳ�������pHead�
extern BOOL FlsRelateDete_RamChange(U8 *pSecBufS, 
						 TFlsRelateDeteHead_st *pHead, 
						 TFlsRelateDeteOne_st *pOne);

/*================= ���к�������-lib�ⲿ ====================================*/
//EX_saveRelateAddr 

extern BOOL FlsRd_isRelateDete(TDev_un *pDev);
extern BOOL FlsRd_RelateDete_Note(TDev_un *pDev, U8 *pRtnNote);

// IN: mOpeaCls: emFlsRelateDeteOpeaCls ��һ:
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
TFlsRelateDeteOne_st    ��ص�ַ
emFlsRelateDeteOpeaCls    TFlsRelateDeteHead_st
******************************************************************************/
#endif // __saveRelateAddr_H__

