#define __Can_Manage_C__
/******************************************************************************
* @file    Can_Manage.c
* @author  yx
* @version V1.0
* @date    2013-09-09
* @brief   
* 
******************************************************************************/
#include  "Can_Manage.h"

#include  "CanBufLib_ReDef.h"
#include  "CanBufLib_incOut.h"
#include  "CanIntRxBuf.h"

#include  "tmrTick.h"
#include  "CanHd_Interface.h"
#include  "CanTxTask.h"
#include  "iCanRxTask.h"
#include  "eCanRxTask.h"

//#include "incFile.h"	


/*================= 常数 ============================================*/

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

void Can_Task_Init(void)
{
U8 can_id;

	for(can_id=0; can_id<U_CAN_ID_MAX; can_id++)
	{
		can_IorE_task_init(can_id);
	}
	
	SetTmrTickTask(TASK_CanFileOverTime, TMR_CanFileOverTime);
}


void Can_Task_Exec(void)
{
U8 can_id;


	CanIntrBuf_Move();
	CanFrmRx_toFile();

	for(can_id=0; can_id<U_CAN_ID_MAX; can_id++)
	{
		canCheckError(can_id);
		if(!bCanError(can_id))
		{
			Exec_Can_TxTask(can_id);
			Exec_Can_RxTask(can_id);
		}
	}
	
	if(GetTickTaskStatus(TASK_CanFileOverTime))
	{
		CanTxRx_File_TmrAdd_JdgOverTime();
	}
}

// 中断接收的帧，快速转入分类队列，不对内容作处理。
// 需要随时调用
// 最大时间为  (一帧传输时间 * (CanHd_IntrRxBuf_MAX-2))
void CanIntrBuf_Move(void)
{
U8 can_id; 
U32 mMoveNum;
THdCanFrame_st *pCanFrm;
U8 mMaskChannel;

	for(can_id=0; can_id<U_CAN_ID_MAX; can_id++)
	{
		// CanIntrBuf_ToClsBuf_Move(can_id);
		for(mMoveNum=0; mMoveNum<100; mMoveNum++)
		{
			if(CanIntBuf_Read(can_id, &mMaskChannel, &pCanFrm))
			{
				if(can_id == U_iCAN_ID)
				{
					canIntrBuf_toBuf_Move(can_id, pCanFrm); 
				}
				else
				{
					canIntrBuf_toBuf_Move(can_id, pCanFrm); 
				}
					
			}
			else
			{
				break;
			}
		}
		
	}
}

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

void can_IorE_task_init(U8 can_id)
{
	if(!bCanHdIdValid(can_id))
	{
		return;
	}
	
	// Init: canBuf, canHd, canState:
	CanHd_IorE_HdAndBuf_Init(can_id);
	ClrCanError(can_id);
	ClrCanReInit(can_id);
	canTxRxSucc_Clr(can_id);
	
	SetTmrTickTask(TASK_CanTxRxCycle + can_id, TMR_CanTxRxCycle);
	
	
	Init_Can_TxTask();
	
}

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

void canCheckError(U8 can_id)
{
	
	if(bCanError(can_id))
	{
		if(bCanReInitIng(can_id))
		{
			ClrCanError(can_id);
		}
		else
		{
			Can_Hd_Close(can_id);
			CanHd_IorE_Hd_Init(can_id);
			SetCanReInit(can_id);
			return; // 等一周期，就算延时。
		}
	}
	
	if(GetTickTaskStatus(TASK_CanTxRxCycle + can_id))
	{
		if(bCanTxRxZero(can_id))
		{
			SetCanError(can_id);
		}
		else
		{
			canTxRxSucc_Clr(can_id);
		}
	}
	
	
}


/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

void Exec_Can_RxTask(U8 can_id)
{

	can_rx_EvtFile(can_id);
	
	can_rx_MesgFile(can_id);
	
	can_rx_DataFrm(can_id);
	
}

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
void can_rx_EvtFile(U8 can_id)
{
U8 mEvtBuf;
	
	//接收文件：事件帧
	if(bCanRxEvtFile_HaveFinish(can_id, &mEvtBuf))
	{
		switch(can_id)
		{
			case U_iCAN_ID:
				iCanRxEvtFile(mEvtBuf);
				break;
			case U_eCAN_ID:
				eCanRxEvtFile(mEvtBuf);
				break;
			default:
				break;
		}
		// Clr_One_CanRxEvtFile(can_id, mEvtBuf);
	}
}


void can_rx_MesgFile(U8 can_id)
{
U8 mMesgBuf;
	
	//接收文件：信息帧
	if(bCanRxMesgFile_HaveFinish(can_id, &mMesgBuf))
	{
		switch(can_id)
		{
			case U_iCAN_ID:
				iCanRxMesgFile(mMesgBuf);
				break;
			case U_eCAN_ID:
				eCanRxMesgFile(mMesgBuf);
				break;
			default:
				break;
		}
		// Clr_One_CanRxMesgFile(can_id, mMesgBuf);
	}
}


void can_rx_DataFrm(U8 can_id)
{
	
	//接收数据帧：
	if(!CanBuf_Rx_IsEmpty(can_id))
	{
		switch(can_id)
		{
			case U_iCAN_ID:
				iCanRxDataFrm();
				break;
			case U_eCAN_ID:
				eCanRxDataFrm();
				break;
			default:
				break;
		}
	}
}

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
static U8  vCanError[U_CAN_ID_MAX];
void SetCanError(U8 can_id)
{
	vCanError[can_id] = TRUE;
}

void ClrCanError(U8 can_id)
{
	vCanError[can_id] = FALSE;
}

BOOL bCanError(U8 can_id)
{
	return vCanError[can_id];
}


/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
static U8  vCanReInit[U_CAN_ID_MAX];
void SetCanReInit(U8 can_id)
{
	vCanReInit[can_id] = TRUE;
}

void ClrCanReInit(U8 can_id)
{
	vCanReInit[can_id] = FALSE;
}

BOOL bCanReInitIng(U8 can_id)
{
	return vCanReInit[can_id];
}


/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
static U8  vCanTxSuccNum[U_CAN_ID_MAX];
static U8  vCanRxSuccNum[U_CAN_ID_MAX];
void CanTxSuccInc(U8 can_id)
{
	if(vCanTxSuccNum[can_id] < 200)
	{
		vCanTxSuccNum[can_id]++;
	}
}
void CanRxSuccInc(U8 can_id)
{
	if(vCanRxSuccNum[can_id] < 200)
	{
		vCanRxSuccNum[can_id]++;
	}
	
}
void canTxRxSucc_Clr(U8 can_id)
{
	vCanTxSuccNum[can_id] = 0;
	vCanRxSuccNum[can_id] = 0;
}

BOOL bCanTxRxZero(U8 can_id)
{
	return ( (vCanTxSuccNum[can_id] == 0)
		   ||(vCanRxSuccNum[can_id] == 0)
		   );
}



/******************************************************************************
* FUNC: //
******************************************************************************/



/******************************************************************************
* FUNC: // END
*   IN:
*  OUT: 
******************************************************************************/
