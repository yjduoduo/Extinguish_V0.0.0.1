#define __flsItemState_C__
/******************************************************************************
* @file    flsItemState.c
* @author  yx
* @version V1.0
* @date    2013-07-23
* @brief   
* 
******************************************************************************/
#include  "flsItemState.h"

#include  "flsReDef.h"
#include  "strFlsAdrDef.h"
#include  "flsStoreBytesDef.h"

//#include "incFile.h"	


/*================= ���� ============================================*/

/*================= �ṹ���� ========================================*/

/*================= ˽�нṹ�������� ================================*/
U8 vFlsItemState[U_FlsSave_Item_MAX][U_FlsSave_Part_MAX];
U8 vFlsItemCopyNum[U_FlsSave_Item_MAX][U_FlsSave_Part_MAX];

/*================= ���к������� ====================================*/

/*================= ˽�к������� ====================================*/

/*=================  ================================================*/
		
/******************************************************************************
* FUNC: 
// ���屻���ǵĴ�����
// ����α����帲��������err
*  OUT: 
******************************************************************************/

void FlsItemState_copyNum_Inc(U8 mFlsItem, U8 mPart)
{
	if(vFlsItemCopyNum[mFlsItem][mPart] < 200)
	{
	vFlsItemCopyNum[mFlsItem][mPart]++;
	}
}

void FlsItemState_copyNum_Clr(U8 mFlsItem, U8 mPart)
{
	vFlsItemCopyNum[mFlsItem][mPart] = 0;
}

BOOL bFlsItemState_copyNum_Over(U8 mFlsItem, U8 mPart)
{
	return(vFlsItemCopyNum[mFlsItem][mPart] >= 1);
}

/******************************************************************************
* FUNC: // 
*   IN:
*  OUT: 
******************************************************************************/

void Set_FlsItemState(U8 mState, U8 mFlsItem, U8 mPart)
{
	if((mState>=U_FlsItem_State_MAX) 
	  || (!bSaveItemValid(mFlsItem))
	  || (!bSaveItmPartValid(mPart))
		)
	{
		return;
	}
	
	vFlsItemState[mFlsItem][mPart] |= (1<<mState);
}

void Clr_FlsItemState(U8 mState, U8 mFlsItem, U8 mPart)
{
	if((mState>=U_FlsItem_State_MAX) 
	  || (!bSaveItemValid(mFlsItem))
	  || (!bSaveItmPartValid(mPart))
		)
	{
		return;
	}
	
	vFlsItemState[mFlsItem][mPart] &= ~(1<<mState);
}

BOOL bFlsItem_isState(U8 mState, U8 mFlsItem, U8 mPart)
{
	return (vFlsItemState[mFlsItem][mPart] & (1<<mState));
}


/******************************************************************************
* FUNC: // ״̬����
*   IN:
*  OUT: 
******************************************************************************/
void FlsItem_StateAll_Init(void)
{
U8 mFlsItem;
U8 mPart;
	
	for(mFlsItem=0; mFlsItem<GetSaveItemMax(); mFlsItem++)
	{
		for(mPart=0; mPart<GetSaveItmPartMax(); mPart++)
		{
			vFlsItemState[mFlsItem][mPart] = 0;
		}
	}
}

void FlsItem_State_Init(U8 mState)
{
	U8 mFlsItem;
	U8 mPart;
	if(mState>=U_FlsItem_State_MAX)
	{
		return;
	}
	for(mFlsItem=0; mFlsItem<GetSaveItemMax(); mFlsItem++)
	{
		for(mPart=0; mPart<GetSaveItmPartMax(); mPart++)
		{
			vFlsItemState[mFlsItem][mPart] &= ~(1<<mState);
		}
	}
}


/******************************************************************************
* FUNC: // 
*   IN:
*  OUT: 
******************************************************************************/


/******************************************************************************
* FUNC: // 
*   IN:
*  OUT: 
******************************************************************************/
// ��ǰ�洢��������Ч
BOOL bFlsItem_IsErrorOrSpace(U8 mFlsItem, U8 mPart)
{
	return (  (bFlsItem_isState(U_FlsItem_Error_State, mFlsItem, mPart))
			||(bFlsItem_isState(U_FlsItem_Space_State, mFlsItem, mPart))
			);
}

// ������Ч��
BOOL bFlsItem_IsUsual(U8 mFlsItem, U8 mPart)
{
	return (  (!bFlsItem_isState(U_FlsItem_Error_State, mFlsItem, mPart))
			&&(!bFlsItem_isState(U_FlsItem_Erase_State, mFlsItem, mPart))
			);
}

/******************************************************************************
* FUNC: // TRUE=�����, (!Error + !Erase + !Renew)
*   IN:
*  OUT: 
******************************************************************************/
BOOL bFlsItem_IsReadAllow(U8 mFlsItem, U8 mPart)
{
	return (  (!bFlsItem_isState(U_FlsItem_Error_State, mFlsItem, mPart))
			&&(!bFlsItem_isState(U_FlsItem_Erase_State, mFlsItem, mPart))
			&&(!bFlsItem_isState(U_FlsItem_Renew_State, mFlsItem, mPart))
			);
}

/******************************************************************************
* FUNC: // END
*   IN:
*  OUT: 
******************************************************************************/
