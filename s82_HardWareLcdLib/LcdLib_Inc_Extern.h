#ifndef __LcdLib_Inc_Extern_H__
#define __LcdLib_Inc_Extern_H__
/******************************************************************************
* @file    LcdLib_Inc_Extern.h
* @author  yx
* @version V1.1
* @date    2013-10-09
* @brief   
* 
* V1.1 2013-10-09
*		add: LcdShow_Tmr 函数
* V1.0 2013-10-08
#include  "LcdLib_Inc_Extern.h"
******************************************************************************/
//
#include  "prjCompileCon.h"
//#include  "hwEx11_lcd_DefPara.h"

/*================= 常数 ============================================*/

/*================= 变量定义 ======================================*/

/*================= 结构体定义 ======================================*/

/*================= 公有函数声明 =====================================*/

/*================= 公有函数声明 =============================================*/
//EX_LcdLib_Inc_Extern

// lcd驱动若一次执行时间较长，调用一次。原则超过10ms就调用一次。
extern void LcdDriver_RunCycle(void);


extern void LcdShow_TmrStart(void);
extern BOOL bLcdShow_TmrWorkIng(void);
extern BOOL bLcdShow_TmrArrived(void);
// * TMR_LcdHardShow 无新显示，刷新所有。
extern U32 GetLcdShow_Refresh_TmrMax(void);

/******************************************************************************
// END :
******************************************************************************/
#endif // __LcdLib_Inc_Extern_H__

