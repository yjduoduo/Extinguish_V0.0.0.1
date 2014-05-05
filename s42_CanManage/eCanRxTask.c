#define __eCanRxTask_C__
/******************************************************************************
* @file    eCanRxTask.c
* @author  yx
* @version V1.0
* @date    2013-09-09
* @brief   
* @master  Can_Manage.c
* 
******************************************************************************/
#include  "eCanRxTask.h"

#include  "CanBufLib_ReDef.h"
#include  "CanBufLib_strFileProp.h"
#include  "CanBufLib_incOut.h"
#include  "canFrame.h"

#include  "can11sFile.h"
#include  "can11sPrtl_eRx.h"
//#include "incFile.h"	

#include  "lcdPg_pSelfHdChk.h"

/*================= ���� ============================================*/

/*================= �ṹ���� ========================================*/

/*================= ˽�нṹ�������� ================================*/
TCanFile_sId  vICanRxFileId;

/*================= ���к������� ====================================*/

/*================= ˽�к������� ====================================*/

/*=================  ================================================*/
		
/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

//��������֡��

void eCanRxDataFrm(void)
{
THdCanFrame_st *pRxDataFrm;

	
	if(!CanBuf_Rx_Read(U_eCAN_ID, &pRxDataFrm))
	{
		return;
	}
	
	// ��֡������
	ECan11s_Rx_One(pRxDataFrm);
	chkHd_Can__CanRx(U_eCAN_ID);
	
}


/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
//�����ļ����¼�֡
void eCanRxEvtFile(U8 mEvtBuf)
{
TCanFile_sId  mFileId;
U8 *pRxByteS;
U32 byteTotal;
	
	if(!GetCanRxEvtFile(U_eCAN_ID, mEvtBuf,
					&mFileId, &pRxByteS, &byteTotal))
	{
		return;
	}
	
		// Clr_One_CanRxEvtFile(U_eCAN_ID, mEvtBuf);
	
}


/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
//�����ļ�����Ϣ֡
void eCanRxMesgFile(U8 mMesgBuf)
{
U8 *pRxByteS;
U32 byteTotal;
	
	if(!GetCanRxMesgFile(U_eCAN_ID, mMesgBuf,
					&vICanRxFileId, &pRxByteS, &byteTotal))
	{
		return;
	}
	
	ICan11s_FileRx_One(&vICanRxFileId, pRxByteS, byteTotal);
	
	Clr_One_CanRxMesgFile(U_eCAN_ID, mMesgBuf);
	
}


/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/



/******************************************************************************
* FUNC: //
******************************************************************************/



/******************************************************************************
* FUNC: // END
*   IN:
*  OUT: 
******************************************************************************/
