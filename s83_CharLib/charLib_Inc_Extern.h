#ifndef __charLib_Inc_Extern_H__
#define __charLib_Inc_Extern_H__
/******************************************************************************
* @file    charLib_Inc_Extern.h
* @author  yx
* @version V1.0
* @date    2012-02-01
* @brief   
* 
*
*
#include  "charLib_Inc_Extern.h"
******************************************************************************/
//
#include  "prjCompileCon.h"
#include  "hwEx11_lcd_Def_charLib.h"
#include  "hwEx11_lcd_DefPara.h"

/*================= ���� ============================================*/

/*================= �������� ======================================*/

/*================= �ṹ�嶨�� ======================================*/

/*================= ���к������� =====================================*/
//EX_hwEx13_charLib 

extern const BYTE bbit[8];

extern BYTE *pGetLib1CharBuf(void); // ��ȡ1���ֵĵ����bufS
extern BYTE *pGetLib1TransCharBuf(void); // ת��1���ֵĵ����bufS
extern void ClrLib1CharBufEnd2Bytes(void); // ���2���ֽ���0

/******************************************************************************
// END :
******************************************************************************/
#endif // __charLib_Inc_Extern_H__

