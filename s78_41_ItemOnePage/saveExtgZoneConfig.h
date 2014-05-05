#ifndef __saveExtgZoneConfig_H__
#define __saveExtgZoneConfig_H__
/******************************************************************************
* @file    saveExtgZoneConfig.h
* @author  yx
* @version V1.0
* @date    2013-01-04
* @brief   气灭区 属性配置
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
/*================= 常数 ============================================*/
//#define 
/*================= 结构体定义 ======================================*/

/*================= 公有结构变量声明 ================================*/

/*================= 私有函数声明 ====================================*/
#ifdef  __saveExtgZoneConfig_C__

// OUT: pRtnBuf 读出的所有 ExtgZoneConfig 的数据：
BOOL flsRd_ExtgZoneConf_toBuf(U8 mPart, U8 *pBufS);

// IN: *pRtnConfigByte的个数: U_FLS_ExtgZoneConfig_One_BYTE_MAX;
BOOL flsSave_ExtgZoneConf_change(U8 mExtgZone, 
						U8 *pRtnConfigByte,
						BOOL bAdd,
						U8 taskId, U8 flsId);

#endif  //__saveExtgZoneConfig_C__
/*================= 公有函数声明-lib内部 ====================================*/
//EX_saveExtgZoneConfig 

//计算灭火区配置的偏移地址:
extern BOOL GetFlsOffsetAdr_ExtgConfig(
							U8 mExtgZone, U32 *pRtnAdr);


/*================= 公有函数声明-lib外部 ====================================*/
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

