#ifndef __saveLinkProg_H__
#define __saveLinkProg_H__
/******************************************************************************
* @file    saveLinkProg.h
* @author  yx
* @version V1.1
* @date    2013-09-23
* @brief   本机 联动编程
* 
* V1.1，2013-09-23 
*		计算存储地址，只有本机的。 其他控制器的未做。
* V1.0，2013-01-04
*
* 
#include  "saveLinkProg.h"
******************************************************************************/
//
#include  "prjCompileCon.h"
#include  "strDevice.h"

/*================= extern ============================================*/
#ifdef  __saveLinkProg_C__
#define EX_saveLinkProg
#else
#define EX_saveLinkProg extern 
#endif
/*================= 常数 ============================================*/
//#define 
/*================= 结构体定义 ======================================*/

/*================= 公有结构变量声明 ================================*/

/*================= 私有函数声明 ====================================*/
#ifdef  __saveLinkProg_C__

#endif  //__saveLinkProg_C__

/*================= 公有函数声明-lib内部 ====================================*/
//EX_saveLinkProg 

extern BOOL CacuFlsOffsetAdr_LinkProg(TDev_un *pDev, U32 *pRtnAdr);

// 计算link存储地址，本机：
static BOOL cacuFlsOffsetAdr_Link_machineMe(
								TDev_un *pDev, U32 *pRtnAdr);
// 本机，气灭：
static BOOL cacuFlsOffsetLink_me_extg(
								TDev_un *pDev, U32 *pRtnAdr);
// 本机，回路内地址：
static BOOL cacuFlsOffsetLink_me_dete(
								TDev_un *pDev, U32 *pRtnAdr);



/*================= 公有函数声明-lib外部 ====================================*/
//EX_saveLinkProg 

extern BOOL FlsSave_LinkProg(TDev_un *pDev, U8 *pProgByte, 
							U8 taskId, U8 flsId);
extern BOOL FlsRd_LinkProg(TDev_un *pDev, U8 *pProgByte);

/******************************************************************************
// END :
******************************************************************************/
#endif // __saveLinkProg_H__

