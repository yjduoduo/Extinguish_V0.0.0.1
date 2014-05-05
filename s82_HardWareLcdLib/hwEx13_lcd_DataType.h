#ifndef __hwEx13_lcd_DataType_H__
#define __hwEx13_lcd_DataType_H__
/******************************************************************************
* @file    hwEx13_lcd_DataType.h
* @author  yx
* @version V1.0
* @date    2012-01-05
* @brief   
* 
#include  "hwEx13_lcd_DataType.h"
******************************************************************************/
//
// #include  "prjCompileCon.h"

/*================= ===========================================*/

typedef unsigned char       TYPE_LCD_COLOR;  //256 uchar
typedef unsigned char       TYPE_LCD_RL;  // 字符行列

// typedef unsigned int       TYPE_LCD_XY;  // pix 坐标
typedef unsigned char       TYPE_LCD_XY;  // pix 坐标
#define U_LCD_XY_TYPE_IS_WORD     0  // 1= X,Y 占用双字节


#define U_LCD_Color_Default      0
/******************************************************************************
// END :
******************************************************************************/
#endif // __hwEx13_lcd_DataType_H__

