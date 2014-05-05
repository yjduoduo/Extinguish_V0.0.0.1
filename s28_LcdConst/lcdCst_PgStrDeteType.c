#define __lcdCst_PgStrDeteType_C__
/******************************************************************************
* @file    lcdCst_PgStrDeteType.c
* @author  yx
* @version V1.0
* @date    2013-07-01
* @brief   
* 
******************************************************************************/
#include  "lcdCst_PgStrDeteType.h"

#include  "loopFieldTypeState.h"


/*================= ���� ============================================*/


/*=================  ================================================*/
		
/******************************************************************************
* FUNC: //
******************************************************************************/
// ��·�ֳ����� �豸����
const TCstDeteType_st cstDeteTypeChar[] =
{
	{DETE_TYPE_Butt, {"�ֱ�", "", ""}},
	{DETE_TYPE_XiaoNiu, {"��ť", "", ""}},
	{DETE_TYPE_Wen, {"����", "", ""}},
	{DETE_TYPE_DianLan, {"����", "", ""}},
	{DETE_TYPE_FuHe, {"����", "", ""}},
	{DETE_TYPE_ShuRu, {"����", "", ""}},
	{DETE_TYPE_YanLiZi, {"����", "", ""}},
	{DETE_TYPE_YanGd, {"���", "", ""}},
	{DETE_TYPE_ZhongJi, {"�м�ģ��", "", ""}},
	{DETE_TYPE_ExtgAutoManu, {"�������Զ�", "", ""}},
	{DETE_TYPE_ExtgForbid, {"�����ֹģ��", "", ""}},
	
	{DETE_TYPE_INVALID, {"δʶ��", "", ""}} // ���һ�����⹦�ܣ�һֱ�����
	// {DDD, {"", "", ""}},
};



/******************************************************************************
* FUNC: //
******************************************************************************/

// ��·�ֳ����� �豸����
BOOL GetCstChar_DeteType(U8 mType, const TCstChar_st **pRtnChar)
{
U8 charDefMax;
U8 ii;

	charDefMax = sizeof(cstDeteTypeChar) / sizeof(TCstDeteType_st);
	for(ii=0; ii<charDefMax; ii++)
	{
		if(cstDeteTypeChar[ii].type == mType)
		{
			*pRtnChar = &cstDeteTypeChar[ii].stChar;
			return TRUE;
		}
	}
	
	*pRtnChar = &cstDeteTypeChar[charDefMax-1].stChar;
	return FALSE;
}



/******************************************************************************
* FUNC: // END
*   IN:
*  OUT: 
******************************************************************************/
