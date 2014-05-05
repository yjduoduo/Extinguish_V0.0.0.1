#define __iCanRxTask_C__
/******************************************************************************
* @file    iCanRxTask.c
* @author  yx
* @version V1.0
* @date    2013-09-09
* @brief   
* @master  Can_Manage.c
* 
******************************************************************************/
#include  "iCanRxTask.h"


#include  "CanBufLib_ReDef.h"
#include  "CanBufLib_strFileProp.h"
#include  "CanBufLib_incOut.h"
#include  "canFrame.h"

#include  "can11sPrtl_iRx.h"
#include  "can11sFile.h"
//#include "incFile.h"	
#include  "lcdPg_pSelfHdChk.h"


extern BOOL bPageIsInquireRegist(void);  //page=��ѯ�Ǽ�
extern BOOL bPageIsLoopBrowse(void);  //page=��·���

extern BOOL bPageIsGetDeteAnalog(void);  //page=���ԣ�ģ������
extern BOOL bPageIsGetDeteInterData(void);  //page=���ԣ��ڲ�����
extern BOOL bPageIsGetDeteTypeState(void);  //page=���ԣ�����״̬
extern BOOL bPageIsGetDeteCurrent(void);  //page=���ԣ�״̬����+��������
extern BOOL bPageIsGetDeteSensitive(void);  //page=���ԣ�̽����������

/*================= ���� ============================================*/

/*================= �ṹ���� ========================================*/

/*================= ˽�нṹ�������� ================================*/

static TCanFile_sId  vICanRxFileId;
/*================= ���к������� ====================================*/

/*================= ˽�к������� ====================================*/

/*=================  ================================================*/
		
/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

//��������֡��

void iCanRxDataFrm(void)
{
THdCanFrame_st *pRxDataFrm;

	if(!CanBuf_Rx_Read(U_iCAN_ID, &pRxDataFrm))
	{
		return;
	}
	
	// ��֡������
	ICan11s_Rx_One(pRxDataFrm);
	chkHd_Can__CanRx(U_iCAN_ID);
}


/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
//�����ļ����¼�֡
void iCanRxEvtFile(U8 mEvtBuf)
{
TCanFile_sId  mFileId;
U8 *pRxByteS;
U32 byteTotal;
	
	if(!GetCanRxEvtFile(U_iCAN_ID, mEvtBuf,	
				   &mFileId, &pRxByteS, &byteTotal))
	{
		return;
	}
	
	
		// Clr_One_CanRxEvtFile(U_iCAN_ID, mEvtBuf);
}

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
//�����ļ�����Ϣ֡
void iCanRxMesgFile(U8 mMesgBuf)
{
U8 *pRxByteS;
U32 byteTotal;
	
	if(!GetCanRxMesgFile(U_iCAN_ID, mMesgBuf,
					&vICanRxFileId, &pRxByteS, &byteTotal))
	{
		return;
	}
	
	
	ICan11s_FileRx_One(&vICanRxFileId, pRxByteS, byteTotal);
	
	
	Clr_One_CanRxMesgFile(U_iCAN_ID, mMesgBuf);
}


BOOL iCanRxFile_PageIsInquireRegist(void)
{
	return bPageIsInquireRegist();
}

BOOL iCanRxFile_PageIsLoopBrowse(void)
{
	return bPageIsLoopBrowse();
}

/******************************************************************************
* FUNC: // END
*   IN:
*  OUT: 
******************************************************************************/
