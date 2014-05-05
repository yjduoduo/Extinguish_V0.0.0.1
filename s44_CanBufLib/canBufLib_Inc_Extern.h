#ifndef __canBufLib_Inc_Extern_H__
#define __canBufLib_Inc_Extern_H__
/******************************************************************************
* @file    canBufLib_Inc_Extern.h
* @author  yx
* @version V1.0
* @date    2013-07-23
* @brief   
* 
#include  "canBufLib_Inc_Extern.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

#include  "canProtocalStr.h"
#include  "CanBufLib_strFileProp.h"

/*================= ====================================*/
//#include  "can_DataOrFile.h"

// IN: can_id = U_iCAN_ID, U_eCAN_ID

extern BOOL bCanFrmIsEvtFile(U8 can_id, U32 mCanFrmId);
extern BOOL bCanFrmIsMessageFile(U8 can_id, U32 mCanFrmId);

extern BOOL CanRx_File_CompProp(U8 can_id, 
						THdCanFrame_st *pFrm,
						TCanFile_sId *pRtnFileSId,
						U8 *pRtnFileHeadOrData);

//组成can发送的id.
extern U32 CanTx_File_CompId(U8 can_id,
						TCanFile_sId *pFileSId, 
						emCanFrm11sDataOrFile  mFileHeadOrData);

/*================= 公有函数声明 ====================================*/
//EX_can11sFile 

// CAN帧 组成文件：
extern BOOL CanRxEvtFile_iCan(THdCanFrame_st *pFrm);
extern BOOL CanRxMesgFile_iCan(THdCanFrame_st *pFrm);


// 需要发送的文件 保存，等待发送:
extern BOOL CanTxMesgFile_iCan_New(U8 taskId,
					TCanFile_sId  *pFileSId,
					U8 *pFileS, 
					U32 mByteTotal);
// 实际发送：
extern void CanTxMesgFile_iCan_Start(U8 mBuf);
extern BOOL CanTxMesgFile_iCan_Follow(U8 mBuf, BOOL *bRtnFinish);


/*================= ====================================*/
// #include  "CanIntCouple.h"
/* 2013.7.25 ，yx;
// CAN某一类的读取只在一处出现，所以不必控制。
// 比如urgent类的不可以在 发送成功后自动启动新发送，
	同时main里还要不时检测是否有urgent发送，
	这是禁止的。
// 注意在main里，判断CAN是否busy，最好前面关中断，
	否则有可能读了 notBusy,此时接收中断，
	且在接收中断里启动了新的发送，
	而改变了原来读出的状态。
规定：避免在CAN中断启动新的发送。因为其会改变状态。

// CAN buf添加时，为防止中断和main有代码重用造成指针错位，需要控制中断。
// 用这2个函数时必须成对出现，

U32 mDisableBit;

	mDisableBit = IntDisable_May_iCanAdd();
	// ...
	IntEnable_May_iCanAdd(mDisableBit);
*/

//OUT: 中断的id由 enable变为disable的 bit。
extern U32 IntDisable_May_CanAdd(void);
//IN:  中断的id由 enable变为disable的 bit，现在恢复enable的状态。
extern void IntEnable_May_CanAdd(U32 whichDisable);

extern U32 IntDisable_May_iCanAdd(void);
extern void IntEnable_May_iCanAdd(U32 whichDisable);
extern U32 IntDisable_May_eCanAdd(void);
extern void IntEnable_May_eCanAdd(U32 whichDisable);

/*================= ====================================*/
// #include  "CanWhenTx.h"
extern BOOL bCanTx_Tmr_Arrived(U8 can_id);

    
/******************************************************************************
// END :
******************************************************************************/
#endif // __canBufLib_Inc_Extern_H__

