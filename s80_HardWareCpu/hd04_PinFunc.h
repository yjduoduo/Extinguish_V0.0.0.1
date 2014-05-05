#ifndef __hd04_PinFunc_H__
#define __hd04_PinFunc_H__
/******************************************************************************
* @file    hd04_PinFunc.h
* @author  yx
* @version V1.0
* @date    2013-07-01
* @Cpu     LPC177x_8x   
* @brief   
* 
#include  "hd04_PinFunc.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

/*================= extern ============================================*/
#ifdef  __hd04_PinFunc_C__
#define EX_hd04_PinFunc
#else
#define EX_hd04_PinFunc extern 
#endif
/*================= ���� ============================================*/

	
/*================= �ṹ�嶨�� ======================================*/

typedef struct{
	unsigned long pin_PERIPH; //emCpuPeriph ��Χ�豸�ĺţ�CPUָ����
	unsigned long pin_BASE;  //emGpioPeriph 
	unsigned long pin_PORT;
}THdPinFuncItem_st;

/*================= ���нṹ�������� ================================*/
/*
typedef struct{
	U8 sequStart;
}TStruct_st;
TStruct_st stStruct;
*/


/*================= ˽�к������� ====================================*/
#ifdef  __hd04_PinFunc_C__

#endif  //__hd04_PinFunc_C__
/*================= ���к������� ====================================*/
// EX_hd04_PinFunc

extern void hdPinFunc_AD(const THdPinFuncItem_st *pHdPin);
extern void hdPinFunc_CAN(const THdPinFuncItem_st *pHdPin);
extern void hdPinFunc_UART(const THdPinFuncItem_st *pHdPin);
extern void hdPinFunc_USB(const THdPinFuncItem_st *pHdPin);
extern void hdPinFunc_PWM(const THdPinFuncItem_st *pHdPin);
extern void hdPinFunc_IIC(const THdPinFuncItem_st *pHdPin);
extern void hdPinFunc_EMC(const THdPinFuncItem_st *pHdPin);


/******************************************************************************
// END :
******************************************************************************/
#endif // __hd04_PinFunc_H__

