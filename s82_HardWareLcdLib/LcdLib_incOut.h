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
*	��Lcd_Driver_V0.0.0.1_8.lib��
* V1.4  2013.10.17 14:10 ��Lcd_Driver_V0.0.0.1_6.lib��
*	add: ExecAllToLcdRam();
*	���� dealLcdSwBuf() �Ӳ����� ������ExecTmrArrivedLcdShow() �� ExecLcdShow() ���á�
*	Lcd_disp_Rectangle() ��� LcdDriver_RunCycle();
*	"hwEx12_lcd_control"  ����ʾ���У�����ʾ����ʱ��������ʾ�� linePix16.
*		lcd_disp_pix_1Line() �� mNowPixMax ����
* V1.2, 2013.10.09 16:04 ��Lcd_Driver_V0.0.0.1_3.lib��
*	"hwEx12_lcd_control"
*		�޸� lcd_disp_Style_pix() ������
*		��_2����ʾ ��Ҫ19340.6us���ĺ�16802.7us����ʡ2.5ms.
*		������lcd��10ms. ������Ҫ����ʱ��ҪԼ10us��Ӧ�������⡣
*	"hwEx15_lcd_swBuf"
*		add: ExecTmrArrivedLcdShow();   //��ʱһ������LCD��ʾ�� ����ʱˢ�¡�
* V1.1, 2013.10.08 22:07 ��Lcd_Driver_V0.0.0.1_2.lib��
*	�����ȽϺ�ʱ����ʾ"0001" ��Ҫ40ms. �ĺ�20ms.
*		"hwEx11_lcd_cmd"
*			lcd_w_data() ǰ��ȥ�� �ж� bWaitForLcdIdle(); 
*			lcd_w_data() lcd_w_command() ȥ�� delay(2);
*		"hwEx12_lcd_control"
*			lcd_buf_save() ��8�ֽ�Ϊ��λˢ�¡� bLcdRowPageChange[].
*	����LcdDriver_RunCycle(); 
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

/*================= ���� ============================================*/

/*================= ���к������� ====================================*/

/*================= ���к�������-Ext. ====================================*/
//EX_hwEx14_lcd_swChar 

extern void Lcd_pix_selfCheck_Step(U8 mStep);
extern void Lcd_pix_selfCheck_Finish(void);


/******************************************************************************
// END :
******************************************************************************/
#endif // __LcdLib_incOut_H__

