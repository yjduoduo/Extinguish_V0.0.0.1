
#define __saveHistory_C__
/******************************************************************************
* @file    saveHistory.c
* @author  yx
* @version V1.0
* @date    2013-07-23
* @brief   ��ʷ��¼�Ľӿں���
* 


******************************************************************************/
#include  "saveHistory.h"

#include  "phSaveHist_incIn.h"
#include  "flsInqPoint.h"

//#include "incFile.h"	

/*================= ���� ============================================*/

/*================= �ṹ���� ========================================*/


/*================= ˽�нṹ�������� ================================*/

/*================= ���к������� ====================================*/

/*================= ˽�к������� ====================================*/






/*=================  ================================================*/

/******************************************************************************
* FUNC: //
clr buf;
�Ƚ�ָ��ͼ�¼�Ƿ����
*   IN:
*  OUT: 
* ��ҪԤ��ִ�� InitAll_FlsQueHeadEnd(); 
******************************************************************************/

void SaveHist_Init(void)
{
U8 mHistCls;
U8 mHistPart;
	
	Init_HistWrBuf();
	FlsWr_Hist_Init();
	
	for(mHistCls=0; mHistCls<FlsHistPartMax(); mHistCls++)
	{
		for(mHistPart=0; mHistPart<FlsHistPartMax(); mHistPart++)
		{
			histPoint_1Cls1Part_Init(mHistCls, mHistPart);
		}
	}
}



/******************************************************************************
* FUNC: // �Ƚ�ָ��ͼ�¼�Ƿ����:
*  OUT: FlsItemState.bError

	//���У���һ�£����ݲ��ã� ���඼��error��

******************************************************************************/

void histPoint_1Cls1Part_Init(U8 mHistCls, U8 mHistPart)
{
TFlsQueuePoint_st  mHeadEnd_PointPart0;
TFlsQueuePoint_st  mHeadEnd_PointPart1;
TFlsQueuePoint_st  mHeadEnd_Hist;
TFlsQueuePoint_st  mHeadEnd_cacu;
U8 mFlsItem_hist;
U8 mFlsItem_point;
	
	mFlsItem_hist = getFlsItem_hist(mHistCls);
	mFlsItem_point = getFlsItem_hstPoint(mHistCls,mHistPart);
	
	GetFlsQueHeadEndAdr(mFlsItem_hist, mHistPart,
				&mHeadEnd_Hist);
	GetFlsQueHeadEndAdr(mFlsItem_point, U_FlsSave_Part0,
				&mHeadEnd_PointPart0);
	GetFlsQueHeadEndAdr(mFlsItem_point, U_FlsSave_Part1,
				&mHeadEnd_PointPart1);
	
	mHeadEnd_cacu.headAdr = hist_sector_start(mHeadEnd_Hist.headAdr);
	mHeadEnd_cacu.endAdr  = hist_sector_start(mHeadEnd_Hist.endAdr);
	
	if(!bFlsItem_HaveShare(mFlsItem_point)) // ��part1
	{
		if(bEqu_FlsQueHeadEnd(&mHeadEnd_cacu, &mHeadEnd_PointPart0))
		{
			Clr_FlsItemState(U_FlsItem_Error_State, mFlsItem_hist, mHistPart);
			Clr_FlsItemState(U_FlsItem_Error_State, mFlsItem_point, U_FlsSave_Part0);
		}
		else
		{
			Set_FlsItemState(U_FlsItem_Error_State, mFlsItem_hist, mHistPart);
			Set_FlsItemState(U_FlsItem_Error_State, mFlsItem_point, U_FlsSave_Part0);
		}
		return;
	}
	
	if(bEqu_FlsQueHeadEnd(&mHeadEnd_PointPart0, &mHeadEnd_PointPart1))
	{
		if(bEqu_FlsQueHeadEnd(&mHeadEnd_cacu, &mHeadEnd_PointPart0))
		{
			Clr_FlsItemState(U_FlsItem_Error_State, mFlsItem_hist, mHistPart);
			Clr_FlsItemState(U_FlsItem_Error_State, mFlsItem_point, U_FlsSave_Part1);
			Clr_FlsItemState(U_FlsItem_Error_State, mFlsItem_point, U_FlsSave_Part0);
		}
		else
		{
			Set_FlsItemState(U_FlsItem_Error_State, mFlsItem_hist, mHistPart);
			Set_FlsItemState(U_FlsItem_Error_State, mFlsItem_point, U_FlsSave_Part1);
			Set_FlsItemState(U_FlsItem_Error_State, mFlsItem_point, U_FlsSave_Part0);
		}
	}
	else
	{
		if(bEqu_FlsQueHeadEnd(&mHeadEnd_cacu, &mHeadEnd_PointPart0))
		{
			Set_FlsItemState(U_FlsItem_Error_State, mFlsItem_point, U_FlsSave_Part1);
		}
		else if(bEqu_FlsQueHeadEnd(&mHeadEnd_cacu, &mHeadEnd_PointPart1))
		{
			Set_FlsItemState(U_FlsItem_Error_State, mFlsItem_point, U_FlsSave_Part0);
		}
		else
		{
			Set_FlsItemState(U_FlsItem_Error_State, mFlsItem_hist, mHistPart);
			Set_FlsItemState(U_FlsItem_Error_State, mFlsItem_point, U_FlsSave_Part1);
			Set_FlsItemState(U_FlsItem_Error_State, mFlsItem_point, U_FlsSave_Part0);			
		}
	}
}








/******************************************************************************
* FUNC: // END
*   IN:
*  OUT: 
******************************************************************************/
