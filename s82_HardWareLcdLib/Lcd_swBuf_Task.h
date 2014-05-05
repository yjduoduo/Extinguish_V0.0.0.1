#ifndef __Lcd_swBuf_Task_H__
#define __Lcd_swBuf_Task_H__
/******************************************************************************
* @file    Lcd_swBuf_Task.h
* @author  yx
* @version V1.9
* @date     2013.10.17 14:22 
* @brief   
*
* 
* 
#include  "Lcd_swBuf_Task.h"
******************************************************************************/
//
#include  "prjCompileCon.h"
#include  "hwEx11_lcd_DefPara.h"

/*================= ���� ============================================*/

/*================= ���к������� ====================================*/

/*================= ���к������� ====================================*/
//EX_hwEx15_lcd_swBuf 


//�´��ڣ�buf[]δ������ϵģ�����Ҫ���������ˡ�
extern void NewWindows(TYPE_LCD_COLOR emColor);

//��ʼ�� ����
extern void LcdSw_Page_Ini(void);

extern void LcdSw_ClrFullWindow(TYPE_LCD_COLOR emColor);

// ͬҳ����ʾ���ݷǳ���ʱ�ã�һ��ˢ�£�����̫��ʱ��
extern void ExecAllToLcdRam(void);

//LCD Init; Clr show buf.
extern void InitLcdShow(void);

//�пվ�exec, ��buf��������lcd.
extern void ExecLcdShow(void);

//��ʱһ������LCD��ʾ�� ����ʱˢ�¡�
// ������ʾʱ�����Ա���ĳblock�ظ���ʾ������
extern void ExecTmrArrivedLcdShow(void);

/******************************************************************************
// END :
******************************************************************************/
#endif // __Lcd_swBuf_Task_H__

