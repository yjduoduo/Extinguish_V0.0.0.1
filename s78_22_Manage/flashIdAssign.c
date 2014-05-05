#define __flashIdAssign_C__
/******************************************************************************
* @file    flashIdAssign.c
* @author  yx
* @version V1.0
* @date    2013-01-04
* @brief   // flash id���䡣
* 
******************************************************************************/
#include  "flashIdAssign.h"

#include  "codeComm.h"

#include  "saveInc_Extern.h"
// extern U8 GetSysTaskId_FlsVerify(void);


/*================= ���� ============================================*/

/*================= ˽�нṹ�������� ================================*/
//���һ����������Ҫ����Ĵ洢
#define U_FLASH_ID_MAX  0xC0 //U8 mFlsId
#define U_FLASH_ID_DefaultAssign   (U_FLASH_ID_MAX - 1)
// flash�������ᵽҳ����ʵʱ��ʾ��
// ��flsId,ֻ���������ú���ʱ����䣬���п��ܲ����Զ�clrAssign,
// ���Ե�������һ����
#define U_FLASH_ID_FlsVerify	   (U_FLASH_ID_MAX - 2)
#define U_FLASH_ID_AutoAssign_MAX  (U_FLASH_ID_MAX - 2)

#define U_FLASH_ID_ResultReserve_100ms  30  

typedef struct{
	BOOL bAssigned;
	U8 FlsIdTmr;
	U8 taskId;
	BOOL bFinished;
	U8 bSucc; //�����ȽϵĽ�� // .0=1=part0 Succ; .1=1=part1 Succ
	// U8 flsId;
}TFlsIdAssign_st;

static TFlsIdAssign_st   stFlsIdAssign[U_FLASH_ID_MAX];


static U8 assignBufLast; // ���һ���������λ��
/*================= ���к������� ====================================*/

/*================= ˽�к������� ====================================*/

void flsIdAssign_one_init(TFlsIdAssign_st *pOne);
/*=================  ================================================*/
		
/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

/******************************************************************************
* FUNC: // flash id���䡣
*   IN:
*  OUT: 
// ����洢����Ψһid, Clr:
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
	ClrRamIs00((U8*)(pOne), byteMax); //ȫ��FF
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
* FUNC: //�������taskId�������flsId.
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
*  OUT: BOOL=�Ƿ������ϣ�*pRtnSucc = �洢�����
******************************************************************************/
BOOL bIsFinish_FlsExe(U8 mFlsId, U8 *pRtnSucc)
{
	if(  (mFlsId >= U_FLASH_ID_MAX)
	  || (!stFlsIdAssign[mFlsId].bAssigned) // δ����
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
* FUNC: //Ĭ��ֵ���������Ľ����taskʹ�á�
	��ֵ���ᱻ�Զ������
******************************************************************************/
U8 FlsId_DefaultValue(void)
{
	return U_FLASH_ID_DefaultAssign;
}
/******************************************************************************
* FUNC: //
// �·�������ţ���master�жϴ洢����á�
// master��Ҫ�ȵõ�һ��flsId, Ȼ���ٵ��� FlsSave_PnConfig()�ȡ�
*   IN:
*  OUT: 
��ô����һ���������λ�������䣬���ⳬʱ���flsId����ѯ״̬��
******************************************************************************/

BOOL FlsIdNewAssign(U8 taskId, U8 *pRtnFlsId)
{
	U8 mFlsId;
	U8 findTotal = 0; 
	
	// �ο� U_FLASH_ID_FlsVerify �Ķ���
	if(taskId == GetSysTaskId_FlsVerify())
	{
		*pRtnFlsId = U_FLASH_ID_FlsVerify;
		return TRUE;
	}
	
	// ���� space:
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
* FUNC: //��ʱ�жϽ����ʱ����Ҫmaster��ʱ100msִ��
����ʱ����������
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
*   IN: taskId = emSysTask; mFlsId�Ƿ���ġ�
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
