#ifndef __CpuReg_H__
#define __CpuReg_H__
/******************************************************************************
* @file    CpuReg.h
* @author  yx
* @version V1.0
* @date    2013-07-01
* @brief   HdInterface���⣬���ܹ���һ��module�ģ��й�CPU�ļĴ���������
* 
#include  "CpuReg.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

/*================= extern ============================================*/
#ifdef  __CpuReg_C__
#define EX_CpuReg
#else
#define EX_CpuReg extern 
#endif
/*================= ���� ============================================*/
enum emCpuPeriph{
	U_Periph_P0_PH,
	U_Periph_P1_PH,
	U_Periph_P2_PH,
	U_Periph_P3_PH,
	U_Periph_P4_PH,
	U_Periph_P5_PH,
	U_Periph_PH_MAX,
};
/*================= �ṹ�嶨�� ======================================*/


/*================= ���нṹ�������� ================================*/
/*
typedef struct{
	U8 sequStart;
}TStruct_st;
TStruct_st stStruct;
*/


/*================= ˽�к������� ====================================*/
#ifdef  __CpuReg_C__

#endif  //__CpuReg_C__
/*================= ���к������� ====================================*/
//EX_CpuReg 
EX_CpuReg void Periph_ModulePower(unsigned int mPeriph, unsigned int bOn);


/******************************************************************************
// END :
******************************************************************************/
#endif // __CpuReg_H__

