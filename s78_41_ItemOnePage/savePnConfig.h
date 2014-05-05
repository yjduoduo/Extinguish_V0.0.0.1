#ifndef __savePnConfig_H__
#define __savePnConfig_H__
/******************************************************************************
* @file    savePnConfig.h
* @author  yx
* @version V1.0
* @date    2013-01-04
* @brief   ϵͳ��Ԫ����
* 
#include  "savePnConfig.h"
******************************************************************************/

#include  "prjCompileCon.h"

/*================= extern ============================================*/
#ifdef  __savePnConfig_C__
#define EX_savePnConfig
#else
#define EX_savePnConfig extern 
#endif

/*================= ���� ============================================*/
//#define 
/*================= �ṹ�嶨�� ======================================*/

/*================= ˽�нṹ�������� ================================*/
#ifdef  __savePnConfig_C__

// OUT: pRtnBuf ���������� pnConfig �����ݣ�
BOOL flsRd_PnConf_toBuf(U8 mPart, U8 *pBufS);

BOOL flsSave_pnConf_change(U8 pnType, 
						  U8 mSequS, U8 mSequE, BOOL bAdd,
							U8 taskId, U8 flsId);
#endif
/*================= ���к�������-lib�ⲿ ====================================*/
//EX_savePnConfig 

// *  OUT:  pFlsHd_GetBufS();
extern BOOL FlsRd_PnConfig(void);

extern BOOL FlsSave_PnConfig_Add(U8 pnType, U8 mSequS, U8 mSequE, 
							U8 taskId, U8 flsId);
extern BOOL FlsSave_PnConfig_Delete(U8 pnType, U8 mSequS, U8 mSequE, 
							U8 taskId, U8 flsId);


/******************************************************************************
// END :
******************************************************************************/
#endif // __savePnConfig_H__

