#define __CanTxTask_C__
/******************************************************************************
* @file    CanTxTask.c
* @author  yx
* @version V1.0
* @date    2013-09-09
* @brief   
* @master  Can_Manage.c, CanBufLib .
* 
******************************************************************************/
#include  "CanTxTask.h"


#include  "CanBufLib_ReDef.h"
#include  "tmrTick.h"
#include  "CanBufLib_incOut.h"
#include  "Can_Manage.h"
#include  "CanHd_Interface.h"
//#include "incFile.h"	


/*================= 常数 ============================================*/
#define U_CAN_TX_FAILED_MAX   5 
 
/*================= 结构定义 ========================================*/

/*================= 私有结构变量声明 ================================*/

/*================= 公有函数声明 ====================================*/

/*================= 私有函数声明 ====================================*/

/*=================  ================================================*/
		
/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
void Init_Can_TxTask(void)
{
	U8 can_id;
	
	SetTmrTickTask(TASK_ICanSend, TMR_ICanSend);
	SetTmrTickTask(TASK_ECanSend, TMR_ECanSend);
	
	for(can_id=0; can_id<U_CAN_ID_MAX; can_id++)
	{
		tmr_CanTxStop(can_id);
		canTxFailed_clr(can_id);
	}
}



/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
// can发送~ 发送有结果的定时：
void tmr_CanTxStart(U8 can_id)
{
	if(!bCanHdIdValid(can_id))
	{
		return;
	}
	SetTmrTickTask((TASK_CanTx1FrmMax + can_id), TMR_CanTx1FrmMax);
}

void tmr_CanTxStop(U8 can_id)
{
	if(!bCanHdIdValid(can_id))
	{
		return;
	}
	KillTickTask(TASK_CanTx1FrmMax + can_id);
}

BOOL bTmr_CanTxArrived(U8 can_id)
{
	if(!bCanHdIdValid(can_id))
	{
		return FALSE;
	}
	return GetTickTaskStatus(TASK_CanTx1FrmMax + can_id);
}

/******************************************************************************
* FUNC: // 发送失败的次数：
******************************************************************************/
static U8  canTxFailed[U_CAN_ID_MAX];
void canTxFailed_inc(U8 can_id)
{
	if(canTxFailed[can_id] < U_CAN_TX_FAILED_MAX)
	{
		canTxFailed[can_id]++;
	}
}
void canTxFailed_clr(U8 can_id)
{
	canTxFailed[can_id] = 0;
}

BOOL bCanTxFailed_Max(U8 can_id)
{
	return (canTxFailed[can_id] >= U_CAN_TX_FAILED_MAX);
}


/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
// 检测发送结果的状态：
// TRUE=未到判定出错，但上一帧未发送成功。
BOOL checkNowTxFailed(U8 can_id)
{
BOOL bTxResultSucc;
	
	if(bTmr_CanTxArrived(can_id))
	{
		tmr_CanTxStop(can_id);
		Set_CanHdTxState_Failed(can_id);
	}
	if(bCanHdTxState_HaveResult(can_id, &bTxResultSucc))
	{
		tmr_CanTxStop(can_id);
		if(bTxResultSucc)
		{
			canTxFailed_clr(can_id);
		}
		else
		{
			canTxFailed_inc(can_id);
			
			if(bCanTxFailed_Max(can_id))
			{
				canTxFailed_clr(can_id);
				SetCanError(can_id);
			}
			else
			{
				// TRUE=未到判定出错，但上一帧未发送成功。
				return TRUE;
			}
		}
	}
	return FALSE;
}


/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
// static THdCanFrame_st stTxFrm;
void Exec_Can_TxTask(U8 can_id)
{
THdCanFrame_st *pTxFrm;
	
	//发送：
// * FUNC: //新发送一帧
// *   IN:
// *  OUT: 判TxIng -> 发送顺序: urgent > file > 定时到+usual ;
// * NEED: iCanHd_Send(pFrm); //硬件发送
// 不用这个函数，也可以应用层控制发送帧的顺序。

	// if(bCanTx_Tmr_Arrived(can_id))
	{
		if(CanTx_txNewFrm(can_id, &pTxFrm))
		{
	#if U_SYS_Test_CanHw == 1
			
			if(can_id == U_iCAN_ID)
			{
				can_id = can_id;
			}
	#endif // U_SYS_Test_CanHw
			
			
			if(CanHd_IorE_Send(can_id, pTxFrm))
			{
				tmr_CanTxStart(can_id);
			}
		}
		
	}
	
	
	if(checkNowTxFailed(can_id))
	{
		//读 最后一次发送的帧，重发用：
		// Get_LastOne_Frm_canSend();
	}
}

/******************************************************************************
* FUNC: // 清除taskId未发送的帧：
*   IN:
*  OUT: 
******************************************************************************/
void CanMange_ClrTaskIdTx(U8 can_id, U8 taskId)
{
	CanTxAndFileBuf_IorE_DelTaskId(can_id, taskId);
}


/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
*Master: CanBufLib 
******************************************************************************/
BOOL bCanTx_Tmr_Arrived(U8 can_id)
{
	switch(can_id)
	{
		case U_iCAN_ID:
			return GetTickTaskStatus(TASK_ICanSend);
			
		case U_eCAN_ID:
			return GetTickTaskStatus(TASK_ECanSend);
			
		default:
			return FALSE;
	}
	
}


/******************************************************************************
* FUNC: // can 发送到 buf[] 准备：
*   IN:
*  OUT: 


******************************************************************************/


// extern BOOL CanBuf_Tx_Add(U8 can_id, THdCanFrame_st *pCanFrm);
// extern BOOL CanBuf_urgent_Tx_Add(U8 can_id, THdCanFrame_st *pCanFrm);

// CanTxMesgFile_iCan_New(); 
// extern BOOL CanTxEvtFile(U8 can_id, 
					// TCanFile_sId  *pFileSId,
					// U8 *pFileS, U32 mByteTotal);


/******************************************************************************
* FUNC: // END
*   IN:
*  OUT: 
******************************************************************************/
