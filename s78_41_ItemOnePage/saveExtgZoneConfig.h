#ifndef __saveExtgZoneConfig_H__
#define __saveExtgZoneConfig_H__
/******************************************************************************
* @file    saveExtgZoneConfig.h
* @author  yx
* @version V1.0
* @date    2013-01-04
* @brief   ������ ��������
* 
#include  "saveExtgZoneConfig.h"
******************************************************************************/
//
#include  "prjCompileCon.h"
#include  "strFlsItmStruct.h"

/*================= extern ============================================*/
#ifdef  __saveExtgZoneConfig_C__
#define EX_saveExtgZoneConfig
#else
#define EX_saveExtgZoneConfig extern 
#endif
/*================= ���� ============================================*/
//#define 
/*================= �ṹ�嶨�� ======================================*/

/*================= ���нṹ�������� ================================*/

/*================= ˽�к������� ====================================*/
#ifdef  __saveExtgZoneConfig_C__

// OUT: pRtnBuf ���������� ExtgZoneConfig �����ݣ�
BOOL flsRd_ExtgZoneConf_toBuf(U8 mPart, U8 *pBufS);

// IN: *pRtnConfigByte�ĸ���: U_FLS_ExtgZoneConfig_One_BYTE_MAX;
BOOL flsSave_ExtgZoneConf_change(U8 mExtgZone, 
						U8 *pRtnConfigByte,
						BOOL bAdd,
						U8 taskId, U8 flsId);

#endif  //__saveExtgZoneConfig_C__
/*================= ���к�������-lib�ڲ� ====================================*/
//EX_saveExtgZoneConfig 

//������������õ�ƫ�Ƶ�ַ:
extern BOOL GetFlsOffsetAdr_ExtgConfig(
							U8 mExtgZone, U32 *pRtnAdr);


/*================= ���к�������-lib�ⲿ ====================================*/
//EX_saveExtgZoneConfig 

extern BOOL FlsRd_ExtgZoneConfig(U8 mExtgZone, U8 *pRtnConfigByte);

// TFlsExtgZoneConfig_st
extern BOOL FlsSave_ExtgZoneConfig(U8 mExtgZone, U8 *pConfigByte, 
						U8 taskId, U8 flsId);
extern BOOL FlsClr_ExtgZoneConfig(U8 mExtgZone, U8 taskId, U8 flsId);



/******************************************************************************
// END :
******************************************************************************/
#endif // __saveExtgZoneConfig_H__

