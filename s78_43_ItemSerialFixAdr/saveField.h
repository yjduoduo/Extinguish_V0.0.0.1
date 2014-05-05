#ifndef __saveField_H__
#define __saveField_H__
/******************************************************************************
* @file    saveField.h
* @author  yx
* @version V1.0
* @date    2013-01-04
* @brief   回路现场部件登记
* 
#include  "saveField.h"
******************************************************************************/

#include  "prjCompileCon.h"
#include  "strFlsItmStruct.h"

/*================= extern ============================================*/
#ifdef  __saveField_C__
#define EX_saveField
#else
#define EX_saveField extern 
#endif

/*================= 常数 ============================================*/
//#define 
/*================= 结构体定义 ======================================*/

/*================= 公有结构变量声明 ================================*/


/*================= 私有函数声明 ================================*/
#ifdef  __saveField_C__
BOOL bCorrespDisable_one_fieldAndBuf(
							U8 mLoop, U8 mAddr, TDev_un *pDev);
#endif // __saveField_C__
/*================= 公有函数声明-lib内部 ====================================*/
//EX_saveField 

// 检查field的定义 与 disable buf 是否对应：
extern BOOL bCorrespDisable_FieldAndBuf(void);

//计算现场部件登记的偏移地址:
extern BOOL GetFlsOffsetAdr_Field(U8 mLoop, U8 mAddr, 
										U32 *pRtnAdr);

//查询field是否屏蔽:
//use: 不用 public buf;
extern BOOL bFlsField_beDisabled(U8 mLoop, U8 mAddr);

/*================= 公有函数声明-lib外部 ====================================*/
//EX_saveField 

extern BOOL FlsRd_Field(TFlsFieldHead_st *pHead, U8 *pRtnRegistByte);

// TFlsFieldOne_st
extern BOOL FlsSave_Field(TFlsFieldHead_st *pHead, 
						 U8 *pRegistByte, 
						U8 taskId, U8 flsId);

extern BOOL FlsClr_Field(TFlsFieldHead_st *pHead,
						U8 taskId, U8 flsId);


/******************************************************************************
// END :
******************************************************************************/
#endif // __saveField_H__

