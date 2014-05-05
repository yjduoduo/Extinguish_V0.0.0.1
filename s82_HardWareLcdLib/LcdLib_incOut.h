#ifndef __LcdLib_incOut_H__
#define __LcdLib_incOut_H__
/******************************************************************************
* @file    LcdLib_incOut.h
* @author  yx
* @version V1.2
* @date    2013.10.09 16:04
* @brief   
*
* 
*	《Lcd_Driver_V0.0.0.1_8.lib》
* V1.4  2013.10.17 14:10 《Lcd_Driver_V0.0.0.1_6.lib》
*	add: ExecAllToLcdRam();
*	改正 dealLcdSwBuf() 加参数， 以用于ExecTmrArrivedLcdShow() 和 ExecLcdShow() 共用。
*	Lcd_disp_Rectangle() 里加 LcdDriver_RunCycle();
*	"hwEx12_lcd_control"  先显示下行，后显示上行时，上行显示了 linePix16.
*		lcd_disp_pix_1Line() 加 mNowPixMax 变量
* V1.2, 2013.10.09 16:04 《Lcd_Driver_V0.0.0.1_3.lib》
*	"hwEx12_lcd_control"
*		修改 lcd_disp_Style_pix() 函数。
*		“_2”显示 需要19340.6us，改后16802.7us，节省2.5ms.
*		其中送lcd用10ms. 引脚需要的延时需要约10us，应该有问题。
*	"hwEx15_lcd_swBuf"
*		add: ExecTmrArrivedLcdShow();   //定时一起送上LCD显示。 带定时刷新。
* V1.1, 2013.10.08 22:07 《Lcd_Driver_V0.0.0.1_2.lib》
*	驱动比较耗时。显示"0001" 需要40ms. 改后20ms.
*		"hwEx11_lcd_cmd"
*			lcd_w_data() 前面去掉 判断 bWaitForLcdIdle(); 
*			lcd_w_data() lcd_w_command() 去掉 delay(2);
*		"hwEx12_lcd_control"
*			lcd_buf_save() 以8字节为单位刷新。 bLcdRowPageChange[].
*	引入LcdDriver_RunCycle(); 
*	
* V1.0, 2012-02-01
#include  "LcdLib_incOut.h"
******************************************************************************/
//
#include  "prjCompileCon.h"
#include  "hwEx11_lcd_DefPara.h"


#include  "hwEx16_charLibAscii08.h"

// #include  "hwEx15_lcd_swBuf.h"
#include  "Lcd_swBuf_Graph.h"
#include  "Lcd_swBuf_Fig88.h"
#include  "Lcd_swBuf_Figure.h"
#include  "Lcd_swBuf_Ascii.h"
#include  "Lcd_swBuf_Text.h"
#include  "Lcd_swBuf_Task.h"

/*================= 常数 ============================================*/

/*================= 公有函数声明 ====================================*/

/*================= 公有函数声明-Ext. ====================================*/
//EX_hwEx14_lcd_swChar 

extern void Lcd_pix_selfCheck_Step(U8 mStep);
extern void Lcd_pix_selfCheck_Finish(void);


/******************************************************************************
// END :
******************************************************************************/
#endif // __LcdLib_incOut_H__

