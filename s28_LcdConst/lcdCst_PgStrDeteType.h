#ifndef __lcdCst_PgStrDeteType_H__
#define __lcdCst_PgStrDeteType_H__
/******************************************************************************
* @file    lcdCst_PgStrDeteType.h
* @author  yx
* @version V1.0
* @date    2013-07-01
* @brief   
* 
#include  "lcdCst_PgStrDeteType.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

#include  "lcdCst_PgString.h"
/*================= extern ============================================*/

#define EX_lcdCst_PgStrDeteType extern 

/*================= ���� ============================================*/
//#define 
/*================= �ṹ�嶨�� ======================================*/

/*================= �ַ������� ======================================*/

/*================= ˽�к������� ====================================*/
#ifdef __lcdCst_PgStrDeteType_C__ 

typedef struct{  //U_Language_MAX
	U8 type;
	TCstChar_st stChar;
}TCstDeteType_st;

const TCstDeteType_st cstDeteTypeChar[];

#endif // __lcdCst_PgStrDeteType_C__
/*================= ���к������� ====================================*/
//EX_lcdCst_PgStrDeteType 

// ��·�ֳ����� �豸����
extern BOOL GetCstChar_DeteType(U8 mType, 
						const TCstChar_st **pRtnChar);

/******************************************************************************
// END :
******************************************************************************/
#endif // __lcdCst_PgStrDeteType_H__

