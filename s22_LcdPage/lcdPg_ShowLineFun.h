#ifndef LCDPG_SHOWLINEFUN_H
#define LCDPG_SHOWLINEFUN_H


#include  "hwEx13_lcd_DataType.h"
#include "prjDataType.h"
#include "lcdPg_KeyCall.h"



#define SHOWLINE_FUN_EXT extern




/*
两个光标函数需要定义到#include  "lcdSub_InputFig.h"
*/
//extern  BOOL FigInput_AddIniFig_WithCurHide(TYPE_LCD_RL mRow, TYPE_LCD_RL mLine,
//                        U8 mFig, U8 mMax,BOOL CurSorHide);
//extern  void FigInput_CursorRight_withRowCol(U8 Row,U8 Col);

//extern BOOL figInput_addIniOne_withHide(TYPE_LCD_RL mRow, TYPE_LCD_RL mLine,
//                        U8 mFig, U8 mMax, BOOL bHideShow);
/*
显示相关部分的内容
包括界面P060,模拟曲线
*/

//2013/11/01 11:08:26
/*****************************************************************************
*author:
*time  :
*****************************************************************************/
/*****************************************************************************
*FUNC:
*IN:
*OUT:
*****************************************************************************/
// 画 提示坐标：
SHOWLINE_FUN_EXT void dw_devScan_coordinate_new(void);
/*****************************************************************************
*FUNC:
*IN:
*OUT:
*****************************************************************************/
// 画 提示坐标：
SHOWLINE_FUN_EXT void dw_devScan_coordinate_p061(void);
/*****************************************************************************
*FUNC:
*IN:
*OUT:
*****************************************************************************/
// 计算坐标X的长度：
//SHOWLINE_FUN_EXT TYPE_LCD_XY cacu_devScan_coordinateX(void);
/*****************************************************************************
*FUNC:
*IN:
*OUT:
*****************************************************************************/
SHOWLINE_FUN_EXT TYPE_LCD_XY cacu_devScan_coordinateX_p061(void);
/*****************************************************************************
*FUNC:
*IN:
*OUT:
*****************************************************************************/
//SHOWLINE_FUN_EXT TYPE_LCD_XY cacu_devScan_deteX(U32 mAdr);
/*****************************************************************************
*FUNC:
*IN:
*OUT:
*****************************************************************************/
SHOWLINE_FUN_EXT TYPE_LCD_XY cacu_devScan_deteX_p061(U32 mAdr);
/*****************************************************************************
*FUNC:
*IN:
*OUT:
*****************************************************************************/
//SHOWLINE_FUN_EXT TYPE_LCD_XY cacu_devScan_deteY(U32 mAdr);
/*****************************************************************************
*FUNC:
*IN:
*OUT:
*****************************************************************************/
SHOWLINE_FUN_EXT void dw_info_text_axis(void);
/*****************************************************************************
*FUNC:
*IN:
*OUT:
*****************************************************************************/
SHOWLINE_FUN_EXT void dw_devScan_axis_new(void);
/*****************************************************************************
*FUNC:
*IN:
*OUT:
*****************************************************************************/
//p061的坐标设置
SHOWLINE_FUN_EXT void dw_devScan_axis_p061(void);
/*****************************************************************************
*FUNC:
*IN:
*OUT:
*****************************************************************************/
SHOWLINE_FUN_EXT void dw_devScan_adrPrompt_new(void);
/*****************************************************************************
*FUNC:
*IN:
*OUT:
*****************************************************************************/
SHOWLINE_FUN_EXT void dw_devScan_adrPrompt_half(void);
/*****************************************************************************
*FUNC:
*IN:
*OUT:
*****************************************************************************/
SHOWLINE_FUN_EXT void add_digital_num_at_axis(void);
/*****************************************************************************
*FUNC:
*IN:
*OUT:
*****************************************************************************/
SHOWLINE_FUN_EXT void show_currentresult_p061(funpara* para);
/*****************************************************************************
*FUNC:
*IN:
*OUT:
*****************************************************************************/
SHOWLINE_FUN_EXT void show_currentresult_p061(funpara* para);
/*****************************************************************************
*FUNC:
*IN:
*OUT:
*****************************************************************************/
SHOWLINE_FUN_EXT void showConsequentAddr(U8 mRow, U8 mLineS, U8 mAddrNum, U8 *pAddr,U8 size);
/*****************************************************************************
*FUNC:
*IN:
*OUT:
*****************************************************************************/
SHOWLINE_FUN_EXT void showConsequentAddrTest(void);


SHOWLINE_FUN_EXT void dw_devScan_adrPrpt_one(U32 mAdr);


SHOWLINE_FUN_EXT void dw_devScan_adrPrpt_one_p061(U32 mAdr);


SHOWLINE_FUN_EXT void dw_devScan_coordinate_p061(void);

SHOWLINE_FUN_EXT void dw_devScan_current_all_p061(U8 *pCurrent,U8 ShowNums,void (*dw_devScan_current)(U32 mAdr, U8 mCurrent));

SHOWLINE_FUN_EXT void show_currentresult_p061(funpara* para);
SHOWLINE_FUN_EXT void dw_devScan_current_one_p061(U32 mAdr, U8 mCurrent);


SHOWLINE_FUN_EXT void show_Simulated_curves(funpara* para);


SHOWLINE_FUN_EXT void show_currentresult(funpara* para);

SHOWLINE_FUN_EXT void showHLine(U8 row,U8 firstcol,U8 endcol);








#endif // LCDPG_SHOWLINEFUN_H

