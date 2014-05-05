#ifndef __lcdPg_Page_H__
#define __lcdPg_Page_H__
/****************************************************************************** 
* @file    lcdPg_Page.h
* @author  yx
* @version V1.0
* @date    2012-01-05
* @brief   
* 
#include  "lcdPg_Page.h"
******************************************************************************/

#include  "prjCompileCon.h"

#include  "hwEx11_lcd_DefPara.h"
#include "lcdPg_KeyCall.h"
/*================= extern ============================================*/
#ifdef  __lcdPg_Page_C__
#define EX_lcdPg_Page
#else
#define EX_lcdPg_Page extern 
#endif

/*================= 常数 ============================================*/
//#define 
/*================= 结构体定义 ======================================*/

/*================= 公有结构变量声明 ================================*/

/*================= 私有函数声明 ====================================*/
#ifdef  __lcdPg_Page_C__

static PAGEWORD vThisPageKey;

#endif
/*================= 私有函数声明 P060 回路浏览： ====================================*/
#ifdef  __lcdPg_Page_C__

#define U_DevScan_AdrMax    64
#define U_DevScan_AdrHalf   32

// 一个地址点占的 x pix :
#define U_DevScan_Pix_X_1Point   5

//不是0，方便画竖线上面的箭头
#define U_DevScan_Pix_X_Start    13 //the distance from the leftest line

// 横线的 Y 位置。 需要在线下留 分隔地址的提示短线。
#define U_DevScan_Pix_Y0_Start  ((U_LCD_ROW_PIX_MAX/2)-1)
#define U_DevScan_Pix_Y1_Start  ((U_LCD_ROW_PIX_MAX )-5)
#define U_DevScan_Pix_Y_End  (2)

#define U_DevScan_Pix_X_Start_p061    13+8




// 一个地址点占的 y pix:此为显示的竖线的最大值
//#define U_DevScan_Pix_Y_1Point   ((U_LCD_ROW_PIX_MAX/4))
#define U_DevScan_Pix_Y_1Point   (24)
// 画 提示坐标：
void dw_devScan_coordinate(void);
// 画 电流:
void dw_devScan_current_all(U8 *pCurrent);

// 显示电流值-1个地址：
void dw_devScan_current_one(U32 mAdr, U8 mCurrent);

// 地址的位置提示：画地址定位线：
void dw_devScan_adrPrompt(void);
    // 画地址定位线：判断是 8的倍数，或 4的倍数。
    void dw_devScan_adrPrpt_one(U32 mAdr);
// 计算坐标X的长度：
TYPE_LCD_XY cacu_devScan_coordinateX(void);
// 计算各地址的x坐标：33=(4+5)+(33*5)=185.
TYPE_LCD_XY cacu_devScan_deteX(U32 mAdr);
TYPE_LCD_XY cacu_devScan_deteY(U32 mAdr);
// 画坐标轴：
void dw_devScan_axis(void);

#endif
/*================= 公有函数声明 ====================================*/
//EX_lcdPg_Page 

// 按键检测时的处理：
extern void KeyCheck_ShowInLcd(U8 mKey);


/******************************************************************************
// END :
******************************************************************************/
#endif // __lcdPg_Page_H__

