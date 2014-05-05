#ifndef __meBoard_H__
#define __meBoard_H__
/******************************************************************************
* @file    meBoard.h
* @author  yx
* @version V1.2
* @date    2013.10.24
* @brief   自身硬件、软件定义
* 
* V1.2， 2013.10.24
*		去掉 GetBoardICanStartAddr(); 修改 GetBoardICanAddr();  
*		修改：GetBoardMax(); GetCanBoardSign();   GetCanApSign(); 
* V1.1  增加函数，GetBoardICanStartAddr()等，2013-8-21
* V1.0  2012-01-05
*
#include  "meBoard.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

#include  "sysPanel.h"
/*================= extern ============================================*/
#ifdef  __meBoard_C__
#define EX_meBoard
#else
#define EX_meBoard extern 
#endif
/*================= 常数 ============================================*/

/*================= CPU 厂家，产品系列 ============================================*/

#define cBoardCpu_Company_Serial_LPC_1777   0 

/*================= 系统 协议 版本 ============================================*/
//系统版本：
#define  cCanProt_11S  0               //CAN 协议代码 11S
#define  cCanProtCur  cCanProt_11S     //CAN 协议代码


/*================= 公有函数声明 ====================================*/

extern U8 GetBoardICanAddr(void);

// MAX = 允许的数字+1；
extern U8 GetBoardMax(void);
extern U8 GetCanBoardSign(void);
extern U8 GetCanApSign(void);

/*================= 公有函数声明 ====================================*/
// 软硬件版本：
EX_meBoard   uint8 GetBoardVersion_Hard(void);
EX_meBoard   uint8 GetBoardVersion_Soft(void);
EX_meBoard   uint8 GetBoardVersion_DebugSoft(void);
EX_meBoard   uint8 GetBoardVersion_TempSoft(void);


/******************************************************************************
// END :
******************************************************************************/
#endif // __meBoard_H__

