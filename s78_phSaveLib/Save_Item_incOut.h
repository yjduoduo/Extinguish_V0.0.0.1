#ifndef __Save_Item_incOut_H__
#define __Save_Item_incOut_H__
/******************************************************************************
* @file    Save_Item_incOut.h
* @author  yx
* @version V1.5
* @date    2013-09-23 
* @brief   
	   
* @version history 
* V1.5, 2013-09-23 
		ȥ���� unSet�Ŀ��ƣ�������master���޸����λ�õĶ��壬���Ӱ�졣
*		FlsSetMeStatus_...()
* V1.4��2013.9.22 ��DriverFlsSave_V0.0.0.1_0.1.5��
*		�޸�FlsErase_WorkIng_MyFlsId(); FlsErase_HaveFinishPercent();
* V1.3��2013-09-4
* V1.0  2013-07-23
* 
#include  "Save_Item_incOut.h"
******************************************************************************/
//
#include  "prjCompileCon.h"
#include  "strDevice.h"
#include  "strEvtTrans.h"

#include  "strFlsItmStruct.h"

/*================= ���к�������-lib�ⲿ ====================================*/
//EX_flsErase 

// add Erase FlsItem.Part.pAdr ���� -> eraseBuf[].
extern BOOL FlsErase_New(U8 mFlsItem, U8 mPart, U8 taskId, U8 flsId,
						TFlsItemAddr *pAdr);
// add Erase FlsItem.Part ���� -> eraseBuf[].
extern BOOL FlsErase_ItemPart_New(U8 mFlsItem, U8 mPart, 
						U8 taskId, U8 flsId);
//��mFlsItem���� -> eraseBuf[].
extern BOOL FlsErase_Item_New(U8 mFlsItem, U8 taskId, U8 flsId); 

//�Ƿ�Erase FlsId, ������erase�������:
extern BOOL FlsErase_WorkIng_MyFlsId(U8 mFlsId);
//������ɵİٷֱ�
extern U8 FlsErase_HaveFinishPercent(U8 mFlsId); 


/*================= ���к�������-lib�ⲿ ====================================*/
//EX_saveNetMachine 
extern BOOL FlsRd_NetMachine(void); //OUT: Machine_Regist();
extern BOOL FlsSave_NetMachine_Add(U8 mMachS, U8 mMachE, 
							  U8 taskId, U8 flsId);
extern BOOL FlsSave_NetMachine_Delete(U8 mMachS, U8 mMachE, 
							  U8 taskId, U8 flsId);

/*================= ���к�������-lib�ⲿ ====================================*/
//EX_saveExtgZoneConfig 

extern BOOL FlsRd_ExtgZoneConfig(U8 mExtgZone, U8 *pRtnConfigByte);

// TFlsExtgZoneConfig_st
extern BOOL FlsSave_ExtgZoneConfig(U8 mExtgZone, U8 *pConfigByte, 
						U8 taskId, U8 flsId);
extern BOOL FlsClr_ExtgZoneConfig(U8 mExtgZone, U8 taskId, U8 flsId);

/*================= ���к�������-lib�ⲿ ====================================*/
//EX_saveMeStatus 

// ����
extern BOOL FlsSysSetMeStatus_Save(U8 taskId, U8 flsId);

// ��flash����
extern BOOL FlsRd_MeStatus(void);

// �������ҿ��ܱ��ı����ݡ�
extern TFlsSysSet_un *pGetFlsSysSet(void);

/*================= ���к�������-lib�ⲿ ====================================*/
//EX_saveNote 
extern BOOL FlsRd_Note(TDev_un *pDev, U8 *pRtnNote);
extern BOOL FlsSave_Note(TDev_un *pDev, U8 *pNoteByte, 
						U8 taskId, U8 flsId);

/*================= ���к�������-lib�ⲿ ====================================*/
//EX_saveDisable 

extern BOOL FlsRd_bDisable(TDev_un *pDev);

extern BOOL FlsAdd_Disable(TDev_un *pDev, BOOL bDisable,
								U8 taskId, U8 flsId);
/*================= ���к�������-lib�ⲿ ====================================*/
//EX_saveUserLogin 


/*================= ���к�������-lib�ⲿ ====================================*/
// EX_savePowerOff
extern BOOL FlsRd_PwrOff(TEvtClock_st  *pRtnClock);
extern BOOL FlsWr_pwrOff_New(TEvtClock_st  *pStClock);

/*================= ���к�������-lib�ⲿ ====================================*/
//EX_saveMachProbat 

/*================= ���к�������-lib�ⲿ ====================================*/
//EX_savePnConfig 

// *  OUT:  pFlsHd_GetBufS();
extern BOOL FlsRd_PnConfig(void);

extern BOOL FlsSave_PnConfig_Add(U8 pnType, U8 mSequS, U8 mSequE, 
							U8 taskId, U8 flsId);
extern BOOL FlsSave_PnConfig_Delete(U8 pnType, U8 mSequS, U8 mSequE, 
							U8 taskId, U8 flsId);

/*================= ���к�������-lib�ⲿ ====================================*/
//EX_saveField 

extern BOOL FlsRd_Field(TFlsFieldHead_st *pHead, U8 *pRtnRegistByte);

// TFlsFieldOne_st
extern BOOL FlsSave_Field(TFlsFieldHead_st *pHead, 
						 U8 *pRegistByte, 
						U8 taskId, U8 flsId);

extern BOOL FlsClr_Field(TFlsFieldHead_st *pHead,
						U8 taskId, U8 flsId);


/*================= ���к�������-lib�ⲿ ====================================*/
//EX_saveLinkProg 
extern BOOL FlsSave_LinkProg(TDev_un *pDev, U8 *pProgByte, 
							U8 taskId, U8 flsId);
extern BOOL FlsRd_LinkProg(TDev_un *pDev, U8 *pProgByte);

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
EX_flsErase
EX_saveNetMachine 	EX_savePnConfig 	EX_saveExtgZoneConfig
EX_saveMeStatus
EX_saveNote 		EX_saveField 		EX_saveLinkProg
EX_saveDisable 	EX_saveRelateAddr
EX_savePowerOff

EX_saveUserLogin
EX_saveMachProbat

******************************************************************************/
#endif // __Save_Item_incOut_H__

