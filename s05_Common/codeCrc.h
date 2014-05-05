#ifndef __codeCrc_H__
#define __codeCrc_H__
/******************************************************************************
* @file    codeCrc.h
* @author  yx
* @version V1.0
* @date    2012-01-05
* @brief   
* 
#include  "codeCrc.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

/*================= extern ============================================*/
#ifdef  __codeCrc_C__
#define EX_codeCrc
#else
#define EX_codeCrc extern 
#endif
/*================= 常数 ============================================*/

/*================= 公有函数声明 ====================================*/
//EX_codeCrc 
EX_codeCrc U8 CacuCrcValue(U8 *pByte, U32 vBytesTotal);
EX_codeCrc BOOL JdgCrcOK(U8 *pByte, U32 vBytesTotal);

/******************************************************************************
// END :
******************************************************************************/
#endif // __codeCrc_H__

