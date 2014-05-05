#ifndef __hw10_MaskCan_H__
#define __hw10_MaskCan_H__
/******************************************************************************
* @file    hw10_MaskCan.h
* @author  yx
* @version V1.0
* @date    2013-08-21
* @brief   
* 
#include  "hw10_MaskCan.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

#include  "lpc177x_8x_can.h" 
/*================= extern ============================================*/
#ifdef  __hw10_MaskCan_C__
#define EX_hw10_MaskCan
#else
#define EX_hw10_MaskCan extern 
#endif
/*================= 常数 ============================================*/
#if U_SYS_SoftSimulatState == 1 
	#define U_CanMask_TestIng   U_NO
#endif // U_SYS_SoftSimulatState

//#define U_USE_CAN_MASK   //define=用CAN设置屏蔽，not=全部接收，接收后代码判断分类。

/*================= 常数 ============================================*/

//参考 emCanFrmMaskBits 

enum emCanFrmRxMaskBuf{   // U8 canMaskBuf; 
	//iCan:
	U_iCanRxMaskBuf_IapFile = 0, // 
	U_iCanRxMaskBuf_IapData = 1, // 
	U_iCanRxMaskBuf_Reset = 2, // 
	U_iCanRxMaskBuf_Alarm = 3, // 
	
	U_iCanRxMaskBuf_PtoP = 4, // ALL
	U_iCanRxMaskBuf_Broad = 5, // ALL
	// iCan Max:
	U_iCanRxMaskBuf_Error = 6,
	
	//--------------------------------
	U_eCanRxMaskBuf_Reset = 0, //  
	U_eCanRxMaskBuf_Alarm = 1, //
	
	U_eCanRxMaskBuf_PtoP = 4, // ALL
	U_eCanRxMaskBuf_Broad = 5, // ALL
	// eCan Max:
	U_eCanRxMaskBuf_Error = 6,
	//--------------------------------
	U_CanRxMaskBuf_Error = 10,
	
	
	U_canTxBuf_Usual = 0,
};


/*******************************************************************/
/******************       屏蔽: iCan    **************************/
/*******************************************************************/
//IAP:
#define  U_iCanMaskData_IapData_ID 	 	(0) 
#define  U_iCanMaskBits_IapData 	 	(0) 
		
#define  U_iCanMaskData_IapFile_ID 	 	(0) 
#define  U_iCanMaskBits_IapFile 	 	(0)
	

//PtoP_Broad：
#define  U_iCanMaskData_Broad_ID 	 	(0)
#define  U_iCanMaskBits_Broad 			(0)

#define  U_iCanMaskData_PtoP_ID			(0)
#define  U_iCanMaskBits_PtoP 			(0)
		
#define  U_iCanMaskBits_DestAdr				(0) // 目标地址
#define  U_iCanMaskBitRightShift_DestAdr	(0)
	
/*******************************************************************/
/******************       屏蔽: eCan    **************************/
/*******************************************************************/


/*******************************************************************/
/******************       屏蔽: iCan + eCan    **************************/
/*******************************************************************/

//Reset:
#define  U_CanMaskData_Reset_ID 	(0) 
#define  U_CanMaskBits_Reset 	 	(0)  

#define  U_iCanMaskData_Reset_ID 	(U_CanMaskData_Reset_ID) 
#define  U_iCanMaskBits_Reset 	 	(U_CanMaskBits_Reset) 
#define  U_eCanMaskData_Reset_ID 	(U_CanMaskData_Reset_ID) 
#define  U_eCanMaskBits_Reset 	 	(U_CanMaskBits_Reset)   
		
//Alarm
#define  U_CanMaskData_Alarm_ID 	(0) 
#define  U_CanMaskBits_Alarm 	 	(0)  

#define  U_iCanMaskData_Alarm_ID 	(U_CanMaskData_Reset_ID) 
#define  U_iCanMaskBits_Alarm 	 	(U_CanMaskBits_Reset)  
#define  U_eCanMaskData_Alarm_ID 	(U_CanMaskData_Reset_ID) 
#define  U_eCanMaskBits_Alarm 	 	(U_CanMaskBits_Reset)  


/*================= 私有函数声明 ====================================*/
#ifdef  __hw10_MaskCan_C__
BOOL jdgFrmMask_eCan_FromFrm(CAN_MSG_Type *pReciveCan, U8 *pRtnMaskBuf);
BOOL jdgFrmMask_iCan_FromFrm(CAN_MSG_Type *pReciveCan, U8 *pRtnMaskBuf);

BOOL jdgFrmMask_FromFrm(U8 canPeriId, CAN_MSG_Type *pReciveCan, 
					  U8 *pRtnMaskBuf);
#endif  //__hw10_MaskCan_C__
/*================= 公有函数声明 ====================================*/
//EX_hw10_MaskCan 


// *   IN: iMB 是 CAN硬件屏蔽机制屏蔽后的结果， emCanFrmRxMaskBuf  内。
// *  OUT:  emCanFrmRxMaskBuf
extern BOOL JdgCanFrmMaskBuf(U8 canPeriId, U8 iMB, CAN_MSG_Type *pReciveCan,
							U8 *pRtnMaskBuf);
/******************************************************************************
// END :
******************************************************************************/
#endif // __hw10_MaskCan_H__

