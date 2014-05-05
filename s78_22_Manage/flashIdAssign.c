#define __flashIdAssign_C__
/******************************************************************************
* @file    flashIdAssign.c
* @author  yx
* @version V1.0
* @date    2013-01-04
* @brief   // flash id分配。
* 
******************************************************************************/
#include  "flashIdAssign.h"

#include  "codeComm.h"

#include  "saveInc_Extern.h"
// extern U8 GetSysTaskId_FlsVerify(void);


/*================= 常数 ============================================*/

/*================= 私有结构变量声明 ================================*/
//最后一个留给不需要结果的存储
#define U_FLASH_ID_MAX  0xC0 //U8 mFlsId
#define U_FLASH_ID_DefaultAssign   (U_FLASH_ID_MAX - 1)
// flash纠错，不会到页面上实时显示，
// 用flsId,只是用来调用函数时的填充，很有可能不会自动clrAssign,
// 所以单独分配一个。
#define U_FLASH_ID_FlsVerify	   (U_FLASH_ID_MAX - 2)
#define U_FLASH_ID_AutoAssign_MAX  (U_FLASH_ID_MAX - 2)

#define U_FLASH_ID_ResultReserve_100ms  30  

typedef struct{
	BOOL bAssigned;
	U8 FlsIdTmr;
	U8 taskId;
	BOOL bFinished;
	U8 bSucc; //读出比较的结果 // .0=1=part0 Succ; .1=1=part1 Succ
	// U8 flsId;
}TFlsIdAssign_st;

static TFlsIdAssign_st   stFlsIdAssign[U_FLASH_ID_MAX];


static U8 assignBufLast; // 最后一个被分配的位置
/*================= 公有函数声明 ====================================*/

/*================= 私有函数声明 ====================================*/

void flsIdAssign_one_init(TFlsIdAssign_st *pOne);
/*=================  ================================================*/
		
/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

/******************************************************************************
* FUNC: // flash id分配。
*   IN:
*  OUT: 
// 分配存储任务唯一id, Clr:
******************************************************************************/

void FlsIdAssign_Init(void)
{
	U8 mFlsId;
	for(mFlsId=0; mFlsId<U_FLASH_ID_MAX; mFlsId++)
	{
		flsIdAssign_one_init(&stFlsIdAssign[mFlsId]);
	}
	
	assignBufLast = 0;
}

BOOL bFlsId_Valid(U8 mFlsId)
{
	return (mFlsId < U_FLASH_ID_MAX);
}



void flsIdAssign_one_init(TFlsIdAssign_st *pOne)
{
U8 byteMax = sizeof(TFlsIdAssign_st);

	if(pOne == NULL)
	{
		return;
	}
	ClrRamIs00((U8*)(pOne), byteMax); //全清FF
}

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

void FlsIdClrAssign(U8 mFlsId)
{
	if(mFlsId >= U_FLASH_ID_MAX)
	{
		return;
	}
	flsIdAssign_one_init(&stFlsIdAssign[mFlsId]);
	
}


/******************************************************************************
* FUNC: //清除所有taskId所分配的flsId.
*   IN:
*  OUT: 
******************************************************************************/
void FlsIdClr_FromTaskId(U8 mTaskId)
{
	U8 mFlsId;
	for(mFlsId=0; mFlsId<U_FLASH_ID_MAX; mFlsId++)
	{
		if((stFlsIdAssign[mFlsId].bAssigned)
		  &&(stFlsIdAssign[mFlsId].taskId == mTaskId))
		{
			flsIdAssign_one_init(&stFlsIdAssign[mFlsId]);
		}
	}
}

/******************************************************************************
* FUNC: //
******************************************************************************/

BOOL bFlsId_AllFinish_FromTaskId(U8 mTaskId)
{
	U8 mFlsId;
	for(mFlsId=0; mFlsId<U_FLASH_ID_MAX; mFlsId++)
	{
		if((stFlsIdAssign[mFlsId].bAssigned)
		  &&(stFlsIdAssign[mFlsId].taskId == mTaskId))
		{
			if(!stFlsIdAssign[mFlsId].bFinished)
			{
				return FALSE;
			}
		}
	}
	return TRUE;
}


BOOL bFlsId_AllSucc_FromTaskId(U8 mTaskId)
{
	U8 mFlsId;
	for(mFlsId=0; mFlsId<U_FLASH_ID_MAX; mFlsId++)
	{
		if((stFlsIdAssign[mFlsId].bAssigned)
		  &&(stFlsIdAssign[mFlsId].taskId == mTaskId))
		{
			if( (!stFlsIdAssign[mFlsId].bFinished)
			  ||(!stFlsIdAssign[mFlsId].bSucc))
			{
				return FALSE;
			}
		}
	}
	return TRUE;
	
}

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: BOOL=是否操作完毕；*pRtnSucc = 存储结果；
******************************************************************************/
BOOL bIsFinish_FlsExe(U8 mFlsId, U8 *pRtnSucc)
{
	if(  (mFlsId >= U_FLASH_ID_MAX)
	  || (!stFlsIdAssign[mFlsId].bAssigned) // 未分配
	  )
	{
		*pRtnSucc = FALSE;
		return TRUE;
	}
	
	if(stFlsIdAssign[mFlsId].bFinished)
	{
		*pRtnSucc = stFlsIdAssign[mFlsId].bSucc;
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/******************************************************************************
* FUNC: //默认值，给不关心结果的task使用。
	此值不会被自动分配掉
******************************************************************************/
U8 FlsId_DefaultValue(void)
{
	return U_FLASH_ID_DefaultAssign;
}
/******************************************************************************
* FUNC: //
// 新分配任务号，给master判断存储结果用。
// master需要先得到一个flsId, 然后再调用 FlsSave_PnConfig()等。
*   IN:
*  OUT: 
最好从最后一个分配过的位置向后分配，避免超时后的flsId被查询状态。
******************************************************************************/

BOOL FlsIdNewAssign(U8 taskId, U8 *pRtnFlsId)
{
	U8 mFlsId;
	U8 findTotal = 0; 
	
	// 参考 U_FLASH_ID_FlsVerify 的定义
	if(taskId == GetSysTaskId_FlsVerify())
	{
		*pRtnFlsId = U_FLASH_ID_FlsVerify;
		return TRUE;
	}
	
	// 查找 space:
	mFlsId = assignBufLast+1;
	for(findTotal=0; findTotal<U_FLASH_ID_AutoAssign_MAX; findTotal++)
	{
		if(mFlsId >= U_FLASH_ID_AutoAssign_MAX)
		{
			mFlsId = 0;
		}
		
		if(!stFlsIdAssign[mFlsId].bAssigned)
		{
			flsIdAssign_one_init(&stFlsIdAssign[mFlsId]);
			stFlsIdAssign[mFlsId].bAssigned = 1;
			stFlsIdAssign[mFlsId].taskId  = taskId;
			
			*pRtnFlsId = mFlsId;
			
			assignBufLast = mFlsId;
			return TRUE;
		}
		
		mFlsId++;
	}
	return FALSE;
	
}




/******************************************************************************
* FUNC: //定时判断结果超时，需要master定时100ms执行
若超时，清除结果。
*   IN:
*  OUT: 
******************************************************************************/

void FlsIdAssign_TmrAdd(void)
{
	U8 mFlsId;
	for(mFlsId=0; mFlsId<U_FLASH_ID_MAX; mFlsId++)
	{
		if(!stFlsIdAssign[mFlsId].bAssigned)
		{
			continue;
		}
		if(!stFlsIdAssign[mFlsId].bFinished)
		{
			continue;
		}
		
		stFlsIdAssign[mFlsId].FlsIdTmr++;
		if(stFlsIdAssign[mFlsId].FlsIdTmr >= U_FLASH_ID_ResultReserve_100ms)
		{
			FlsIdClrAssign(mFlsId);
		}
	}
	
}


/******************************************************************************
* FUNC: // 
*   IN: taskId = emSysTask; mFlsId是分配的。
*  OUT: 
******************************************************************************/
void FlsResultNotificat(U8 taskId, U8 mFlsId, U8 bSucc)
{
	if(mFlsId >= U_FLASH_ID_MAX)
	{
		return;
	}
	if(stFlsIdAssign[mFlsId].bAssigned)
	{
		stFlsIdAssign[mFlsId].bFinished = TRUE;
		stFlsIdAssign[mFlsId].bSucc = bSucc;
	}
	
}


/******************************************************************************
* FUNC: // END
*   IN:
*  OUT: 
******************************************************************************/
