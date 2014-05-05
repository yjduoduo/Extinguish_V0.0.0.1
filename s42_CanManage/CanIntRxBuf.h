#ifndef __CanIntRxBuf_H__
#define __CanIntRxBuf_H__
/******************************************************************************
* @file    CanIntRxBuf.h
* @author  yx
* @version V1.0
* @date    2013-07-01
* @brief   
* 
#include  "CanIntRxBuf.h"
******************************************************************************/
//
#include  "prjCompileCon.h"
#include  "lpc177x_8x_can.h"
#include  "canFrame.h"

/*================= extern ============================================*/
#ifdef  __CanIntRxBuf_C__
#define EX_CanIntRxBuf
#else
#define EX_CanIntRxBuf extern 
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
#ifdef  __CanIntRxBuf_C__

#if U_SYS_IdleBuf_setFF == 1
// һ��buf��FF
void canIntBuf_SetOneIni(CAN_MSG_Type *pMsg);
#endif // U_SYS_IdleBuf_setFF

#endif  //__CanIntRxBuf_C__
/*================= ���к������� ====================================*/
//EX_CanIntRxBuf 

void CanIntBuf_Init(U8 can_id);
BOOL CanIntBuf_Add(U8 can_id, U8 canMaskChannel, CAN_MSG_Type *pMsg);
BOOL CanIntBuf_Read(U8 can_id, U8 *pRtnMaskChannel, 
							THdCanFrame_st **ppRtnCanFrm);

/******************************************************************************
// END :
******************************************************************************/
#endif // __CanIntRxBuf_H__

