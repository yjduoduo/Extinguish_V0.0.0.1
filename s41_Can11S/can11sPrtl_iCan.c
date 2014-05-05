#define __can11sPrtl_iCan_C__
/******************************************************************************
* @file    can11sPrtl_iCan.c
* @author  yx
* @version V1.0
* @date    2013-07-01
* @brief   
* 
******************************************************************************/
#include  "can11sPrtl_iCan.h"


//#include "incFile.h"	
#include  "sysPanel.h"


/*================= ���� ============================================*/\
// rx:
// ��·��=��·���
// ר����=ר���̺�+9
// ������=�����̺�+28
// ������=������+52


// tx:
// ��·��=����·��-1��/8,   1~
// ר�߰�=����·��-65��+8,  9~
// �����=����·��-85��+60, 61~ 

typedef struct{
	U8 opeaTx_dest;
	U8 opeaRx_src;
	U8 opeaTx_meSrc;
}TICan11sIdUnique;

#define U_ICan11sIdUnique_UnKnown   (0xFF)
#define U_ICan11sIdUnique_FF   (0xFF) // ��Ч
const TICan11sIdUnique  cstICan11sIdUniqu[U_PN_TYPE_MAX] =
{
	// opeaTx_dest,  opeaRx_src�� opeaTx_meSrc
	{ U_ICan11sIdUnique_FF, U_ICan11sIdUnique_FF, U_ICan11sIdUnique_FF}, // U_PN_Machine_TYPE = 0x0,  // 0ֵ�ǽ�ֹ��,��������machine.
	{  1,  1, 1}, // U_PN_Loop_TYPE = 0x1,
	{  0,  0, 0}, // U_PN_Opea_TYPE = 0x2, 
	{  9,  9, 9}, // U_PN_Drt_TYPE = 0x3,
	{ U_ICan11sIdUnique_UnKnown, 28, U_ICan11sIdUnique_UnKnown}, // U_PN_Bus_TYPE = 0x4,
	{ 61, 52, U_ICan11sIdUnique_UnKnown}, // U_PN_Extg_TYPE = 0x5,
	{ U_ICan11sIdUnique_UnKnown, U_ICan11sIdUnique_UnKnown, U_ICan11sIdUnique_UnKnown}, // U_PN_Broad_TYPE = 0x6,
	{ U_ICan11sIdUnique_FF, U_ICan11sIdUnique_FF, U_ICan11sIdUnique_FF}, // U_PN_Power_TYPE = 0x7,
	{ U_ICan11sIdUnique_FF, U_ICan11sIdUnique_FF, U_ICan11sIdUnique_FF}, // U_PN_Other_TYPE = 0x8,
};

/*================= �ṹ���� ========================================*/

/*================= ˽�нṹ�������� ================================*/

/*================= ���к������� ====================================*/

/*================= ˽�к������� ====================================*/

/*=================  ================================================*/
		
/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

// IN: pnType: emPanelType ;
// ��ʾ��Ԫ ���� canId.Sourse Start:
BOOL bGetCan11s_Rx_SrcStart(U8 pnType, U8 *pRtnSrcStart)
{
	if(pnType >= U_PN_TYPE_MAX)
	{
		return FALSE;
	}
	
	*pRtnSrcStart = cstICan11sIdUniqu[pnType].opeaRx_src;
	return (*pRtnSrcStart < U_ICan11sIdUnique_FF);
}


// ��ʾ��Ԫ ���� canId.Dest Start:
BOOL bGetCan11s_Tx_DestStart(U8 pnType, U8 *pRtnDestStart)
{
	if(pnType >= U_PN_TYPE_MAX)
	{
		return FALSE;
	}
	
	*pRtnDestStart = cstICan11sIdUniqu[pnType].opeaTx_dest;
	return (*pRtnDestStart < U_ICan11sIdUnique_FF);
}


//   ����Ԫ ���� canId.Sourse Start:
BOOL bGetCan11s_Tx_SrcStart(U8 pnType, U8 *pRtnSrcStart)
{
	if(pnType >= U_PN_TYPE_MAX)
	{
		return FALSE;
	}
	
	*pRtnSrcStart = cstICan11sIdUniqu[pnType].opeaTx_meSrc;
	return (*pRtnSrcStart < U_ICan11sIdUnique_FF);
	
}

/******************************************************************************
* FUNC: // ����Դ��ַ������panel:
******************************************************************************/

//CAN Aim adr -> .pnType, .pnSequ 
BOOL bICan11sIdSourse_ToPnTypeSequ( U8 mCanSrc, 
							  U8 *pRtnPnType, U8 *pRtnPnSequ)
{
U8 pnType; // emPanelType
U8 mCanSrcStart;

	
	*pRtnPnType = 0;
	*pRtnPnSequ = 0;
	for(pnType=0; pnType<U_PN_TYPE_MAX; pnType++)
	{
		if(!bGetCan11s_Rx_SrcStart(pnType, &mCanSrcStart))
		{
			continue;
		}
		
		// bSequValid_RelatePanel(U8 pnType, U8 mSequPn1Start, U8 mSequNow)
		if(bSequValid_RelatePanel(pnType, mCanSrcStart, mCanSrc))
		{
			*pRtnPnType = pnType;
			*pRtnPnSequ = (mCanSrc - mCanSrcStart) + 1;
			return TRUE;
		}
	}
	
	return FALSE;
}


/******************************************************************************
* FUNC: // END
*   IN:
*  OUT: 
******************************************************************************/
