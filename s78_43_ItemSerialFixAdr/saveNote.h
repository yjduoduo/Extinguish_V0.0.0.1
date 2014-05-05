#ifndef __saveNote_H__
#define __saveNote_H__
/******************************************************************************
* @file    saveNote.h
* @author  yx
* @version V1.1
* @date    2013-09-23
* @brief   本机注释
* 
* V1.1，2013-09-23 
*		计算存储地址，只有本机的。 其他控制器的未做。
* V1.0，2013-01-04
*
#include  "saveNote.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

#include  "strDevice.h"
/*================= extern ============================================*/
#ifdef  __saveNote_C__
#define EX_saveNote
#else
#define EX_saveNote extern 
#endif
/*================= 常数 ============================================*/
//#define 
/*================= 结构体定义 ======================================*/

/*================= 公有结构变量声明 ================================*/

/*================= 私有函数声明 ====================================*/
#ifdef  __saveNote_C__

// 计算note存储地址，本机：
static BOOL cacuFlsOffsetAdr_Note_machineMe(
								TDev_un *pDev, U32 *pRtnAdr);
// 本机，回路内地址：
static BOOL cacuFlsOffsetNote_me_dete(
								TDev_un *pDev, U32 *pRtnAdr);
// 本机，气灭：
static BOOL cacuFlsOffsetNote_me_extg(
								TDev_un *pDev, U32 *pRtnAdr);

#endif  //__saveNote_C__

/*================= 公有函数声明-lib内部 ====================================*/
//EX_saveNote 
//计算注释的偏移地址:
extern BOOL GetFlsOffsetAdr_Note_Wr(TDev_un *pDev, U32 *pRtnAdr);
extern BOOL GetFlsOffsetAdr_Note_Rd(TDev_un *pDev, U32 *pRtnAdr);

/*================= 公有函数声明-lib外部 ====================================*/
//EX_saveNote 

extern BOOL FlsRd_Note(TDev_un *pDev, U8 *pRtnNote);

extern BOOL FlsSave_Note(TDev_un *pDev, U8 *pNoteByte, 
						U8 taskId, U8 flsId);

/******************************************************************************
// END :
******************************************************************************/
#endif // __saveNote_H__

