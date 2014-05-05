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


extern BOOL bPageIsInquireRegist(void);  //page=查询登记
extern BOOL bPageIsLoopBrowse(void);  //page=回路浏览

extern BOOL bPageIsGetDeteAnalog(void);  //page=测试：模拟曲线
extern BOOL bPageIsGetDeteInterData(void);  //page=测试：内部数据
extern BOOL bPageIsGetDeteTypeState(void);  //page=测试：类型状态
extern BOOL bPageIsGetDeteCurrent(void);  //page=测试：状态电流+背景电流
extern BOOL bPageIsGetDeteSensitive(void);  //page=测试：探测器灵敏度

/*================= 常数 ============================================*/

/*================= 结构定义 ========================================*/

/*================= 私有结构变量声明 ================================*/

static TCanFile_sId  vICanRxFileId;
/*================= 公有函数声明 ====================================*/

/*================= 私有函数声明 ====================================*/

/*=================  ================================================*/
		
/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

//接收数据帧：

void iCanRxDataFrm(void)
{
THdCanFrame_st *pRxDataFrm;

	if(!CanBuf_Rx_Read(U_iCAN_ID, &pRxDataFrm))
	{
		return;
	}
	
	// 各帧分析：
	ICan11s_Rx_One(pRxDataFrm);
	chkHd_Can__CanRx(U_iCAN_ID);
}


/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
//接收文件：事件帧
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
//接收文件：信息帧
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
