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
*		add: LcdShow_Tmr ����
* V1.0 2013-10-08
#include  "LcdLib_Inc_Extern.h"
******************************************************************************/
//
#include  "prjCompileCon.h"
//#include  "hwEx11_lcd_DefPara.h"

/*================= ���� ============================================*/

/*================= �������� ======================================*/

/*================= �ṹ�嶨�� ======================================*/

/*================= ���к������� =====================================*/

/*================= ���к������� =============================================*/
//EX_LcdLib_Inc_Extern

// lcd������һ��ִ��ʱ��ϳ�������һ�Ρ�ԭ�򳬹�10ms�͵���һ�Ρ�
extern void LcdDriver_RunCycle(void);


extern void LcdShow_TmrStart(void);
extern BOOL bLcdShow_TmrWorkIng(void);
extern BOOL bLcdShow_TmrArrived(void);
// * TMR_LcdHardShow ������ʾ��ˢ�����С�
extern U32 GetLcdShow_Refresh_TmrMax(void);

/******************************************************************************
// END :
******************************************************************************/
#endif // __LcdLib_Inc_Extern_H__

