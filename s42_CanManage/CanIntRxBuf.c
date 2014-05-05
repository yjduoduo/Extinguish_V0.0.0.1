#define __CanIntRxBuf_C__
/******************************************************************************
* @file    CanIntRxBuf.c
* @author  yx
* @version V1.0
* @date    2013-07-01
* @brief   
* 
******************************************************************************/
#include  "CanIntRxBuf.h"


//#include "incFile.h"	
#include  "CanBufLib_ReDef.h"
#include  "bufCircle.h"

//EX_CanHd_Interface 
extern void CanFrmType_MsgToFrm(CAN_MSG_Type *pMsg, 
						THdCanFrame_st *pFrm);

/*================= 常数 ============================================*/

#define U_ICanIntRx_Buf_MAX		0x10 // 内CAN 数据帧 中断 rx buf
#define U_ECanIntRx_Buf_MAX		0x10 // 内CAN 数据帧 中断 rx buf


/*================= 结构定义 ========================================*/

typedef struct{
	CAN_MSG_Type *pBufS;
	U32 max;
}TCanIntBufProp_st;
/*================= 私有结构变量声明 ================================*/

static TBufCircle  stCanIntCircle[U_CAN_ID_MAX];

static CAN_MSG_Type  stICanIntRx_Buf[U_ICanIntRx_Buf_MAX];
static CAN_MSG_Type  stECanIntRx_Buf[U_ECanIntRx_Buf_MAX];


const TCanIntBufProp_st  cstCanIntBufProp[U_CAN_ID_MAX]=
{
	{&stICanIntRx_Buf[0], U_ICanIntRx_Buf_MAX}, //U_iCAN_ID,
	{&stECanIntRx_Buf[0], U_ECanIntRx_Buf_MAX}, //U_eCAN_ID,
	
};
	
// 最后一个读出的，临时保存。
static THdCanFrame_st  stCanIntBuf_Now[U_CAN_ID_MAX];
/*================= 公有函数声明 ====================================*/

/*================= 私有函数声明 ====================================*/

/*=================  ================================================*/
		
/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

void CanIntBuf_Init(U8 can_id)
{
#if U_SYS_IdleBuf_setFF == 1
U32 bufNum;
U32 bufMax;
CAN_MSG_Type  *pMsgS;
CAN_MSG_Type  *pMsgNow;
#endif //U_SYS_IdleBuf_setFF

	if(!bCanHdIdValid(can_id))
	{
		return;
	}

#if U_SYS_IdleBuf_setFF == 1
	pMsgS = cstCanIntBufProp[can_id].pBufS;
	for(bufNum=0; bufNum<cstCanIntBufProp[can_id].max; bufNum++)
	{
		pMsgNow = pMsgS + bufNum;
		canIntBuf_SetOneIni(pMsgNow);
	}
#endif //U_SYS_IdleBuf_setFF

	BufCircleIni(cstCanIntBufProp[can_id].max, 
				  &stCanIntCircle[can_id]);
}


/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
*  // U_SIGN_bHaveTested  2013.10.10
******************************************************************************/

BOOL CanIntBuf_Add(U8 can_id, U8 canMaskChannel, CAN_MSG_Type *pMsg)
{
CAN_MSG_Type  *pMsgS;
CAN_MSG_Type  *pMsgNow;

	#if U_SYS_Test_CanHw == 1
	if(can_id == U_eCAN_ID)
	{
		can_id = can_id;
	}

	#endif // U_SYS_Test_CanHw

	if(!bCanHdIdValid(can_id))
	{
		return FALSE;
	}
	if(bFullBufCircle(&stCanIntCircle[can_id]))
	{
		return FALSE;
	}
	pMsg->type = canMaskChannel; // 借用位置
	
	pMsgS = cstCanIntBufProp[can_id].pBufS;
	pMsgNow = pMsgS + BufCircle_GetIn(&stCanIntCircle[can_id]);
	
	*pMsgNow = *pMsg;
	BufCircle_InInc(&stCanIntCircle[can_id]);
	
	return TRUE;
}


/******************************************************************************
* FUNC: // 读取 buf
*   IN:
* SAVE:  stCanIntBuf_Now[can_id];  
*  OUT: 
*  // U_SIGN_bHaveTested  2013.10.10

void read(void)
{
THdCanFrame_st  *pFrm;
	if(CanIntBuf_Read(can_id, &pFrm))
	{
	}
}
******************************************************************************/

BOOL CanIntBuf_Read(U8 can_id, U8 *pRtnMaskChannel, 
							THdCanFrame_st **ppRtnCanFrm)
{
CAN_MSG_Type  *pMsgS;
CAN_MSG_Type  *pMsgNow;

	if(!bCanHdIdValid(can_id))
	{
		return FALSE;
	}
	if(bEmptyBufCircle(&stCanIntCircle[can_id]))
	{
		return FALSE;
	}
	

	pMsgS = cstCanIntBufProp[can_id].pBufS;
	pMsgNow = pMsgS + BufCircle_GetOut(&stCanIntCircle[can_id]);
	CanFrmType_MsgToFrm(pMsgNow, &stCanIntBuf_Now[can_id]);
	
	*pRtnMaskChannel = pMsgNow->type;
	
#if U_SYS_IdleBuf_setFF == 1
	canIntBuf_SetOneIni(pMsgNow);
#endif // U_SYS_IdleBuf_setFF

	BufCircle_OutInc(&stCanIntCircle[can_id]);
	
	*ppRtnCanFrm = &stCanIntBuf_Now[can_id];
	
	return TRUE;
}


/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

#if U_SYS_IdleBuf_setFF == 1
// 一个buf置FF
void canIntBuf_SetOneIni(CAN_MSG_Type *pMsg)  
{
	pMsg->id = ~0;
	pMsg->format = ~0;
	pMsg->len = ~0;
	pMsg->type = ~0;
}
#endif //U_SYS_IdleBuf_setFF


/******************************************************************************
* FUNC: //
******************************************************************************/



/******************************************************************************
* FUNC: // END
*   IN:
*  OUT: 
******************************************************************************/
