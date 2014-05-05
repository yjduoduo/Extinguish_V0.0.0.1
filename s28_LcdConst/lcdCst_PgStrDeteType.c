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


/*================= 常数 ============================================*/


/*=================  ================================================*/
		
/******************************************************************************
* FUNC: //
******************************************************************************/
// 回路现场部件 设备类型
const TCstDeteType_st cstDeteTypeChar[] =
{
	{DETE_TYPE_Butt, {"手报", "", ""}},
	{DETE_TYPE_XiaoNiu, {"消钮", "", ""}},
	{DETE_TYPE_Wen, {"感温", "", ""}},
	{DETE_TYPE_DianLan, {"电缆", "", ""}},
	{DETE_TYPE_FuHe, {"复合", "", ""}},
	{DETE_TYPE_ShuRu, {"输入", "", ""}},
	{DETE_TYPE_YanLiZi, {"离子", "", ""}},
	{DETE_TYPE_YanGd, {"光电", "", ""}},
	{DETE_TYPE_ZhongJi, {"中继模块", "", ""}},
	{DETE_TYPE_ExtgAutoManu, {"气灭手自动", "", ""}},
	{DETE_TYPE_ExtgForbid, {"气灭禁止模块", "", ""}},
	
	{DETE_TYPE_INVALID, {"未识别", "", ""}} // 最后一条特殊功能，一直放最后。
	// {DDD, {"", "", ""}},
};



/******************************************************************************
* FUNC: //
******************************************************************************/

// 回路现场部件 设备类型
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
