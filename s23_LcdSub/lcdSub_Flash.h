#ifndef __lcdSub_Flash_H__
#define __lcdSub_Flash_H__
/******************************************************************************
* @file    lcdSub_Flash.h
* @author  yx
* @version V1.0
* @date    2012-01-05
* @brief   控制flash写时禁止读
* 
#include  "lcdSub_Flash.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

/*================= extern ============================================*/
#ifdef  __lcdSub_Flash_C__
#define EX_lcdSub_Flash
#else
#define EX_lcdSub_Flash extern 
#endif
/*================= 常数 ============================================*/
//#define 
/*================= 结构体定义 ======================================*/

/*================= 公有结构变量声明 ================================*/

/*================= 公有函数声明 ====================================*/
//EX_lcdSub_Flash 


extern void LcdSubFls_Clr_WaitFor_RdAllow(U8 mFlsItem, U8 mPart);

extern void LcdSubFls_Set_WaitFor_RdAllow(U8 mFlsItem, U8 mPart);

extern BOOL bLcdSubFls_isWaitIng(void);

// if 允许读，waitRd flsItem:
extern BOOL LcdSubFls_RdAllow(void);



/*================= 私有函数声明 ====================================*/
#ifdef  __lcdSub_Flash_C__

#endif  //__lcdSub_Flash_C__
/******************************************************************************
// END :
******************************************************************************/
#endif // __lcdSub_Flash_H__

