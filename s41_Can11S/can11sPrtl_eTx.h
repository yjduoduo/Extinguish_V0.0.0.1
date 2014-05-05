#ifndef __can11sPrtl_eTx_H__
#define __can11sPrtl_eTx_H__
/******************************************************************************
* @file    can11sPrtl_eTx.h
* @author  yx
* @version V1.0
* @date    2013-07-01
* @brief   
* 
#include  "can11sPrtl_eTx.h"
******************************************************************************/
//
#include  "prjCompileCon.h"
// Can֡��ʽ��	
#include  "canProtocalStr.h"
#include  "canFrame.h"
// 

/*================= extern ============================================*/
#ifdef  __can11sPrtl_eTx_C__
#define EX_can11sPrtl_eTx
#else
#define EX_can11sPrtl_eTx extern 
#endif
/*================= ���� ============================================*/
//#define 
/*================= �ṹ�嶨�� ======================================*/

/*================= ���нṹ�������� ================================*/
/*
typedef struct{
	U8 sequStart;
}TStruct_st;
TStruct_st stStruct;
*/

/*-----------------    ----------------------------------*/

/*================= ˽�к������� ====================================*/
#ifdef  __can11sPrtl_eTx_C__
U8 getECan_MeAdr(void);

#endif  //__can11sPrtl_eTx_C__
/*================= ���к������� ====================================*/
//EX_can11sPrtl_eTx 
extern U32 GetECan11sId_Broad(void);
extern U32 GetECan11sId_PtoP(U8 mDest);


extern void CompECan11s_tx_1byte_broad(U8 mByte, 
								THdCanFrame_st *pRtnFrm);
extern void CompECan11s_tx_2byte_broad(U8 mByte0, U8 mByte1, 
								THdCanFrame_st *pRtnFrm);
extern void CompECan11s_tx_nbyte_broad(U8 mNum, U8 *pByte, 
								THdCanFrame_st *pRtnFrm);


extern void CompECan11s_tx_1byte_PtoP(U8 mDest, U8 mByte, 
								THdCanFrame_st *pRtnFrm);

/******************************************************************************
// END :
******************************************************************************/
#endif // __can11sPrtl_eTx_H__

