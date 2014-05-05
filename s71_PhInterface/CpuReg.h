#ifndef __CpuReg_H__
#define __CpuReg_H__
/******************************************************************************
* @file    CpuReg.h
* @author  yx
* @version V1.0
* @date    2013-07-01
* @brief   HdInterface以外，不能归入一个module的，有关CPU的寄存器的设置
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
/*================= 常数 ============================================*/
enum emCpuPeriph{
	U_Periph_P0_PH,
	U_Periph_P1_PH,
	U_Periph_P2_PH,
	U_Periph_P3_PH,
	U_Periph_P4_PH,
	U_Periph_P5_PH,
	U_Periph_PH_MAX,
};
/*================= 结构体定义 ======================================*/


/*================= 公有结构变量声明 ================================*/
/*
typedef struct{
	U8 sequStart;
}TStruct_st;
TStruct_st stStruct;
*/


/*================= 私有函数声明 ====================================*/
#ifdef  __CpuReg_C__

#endif  //__CpuReg_C__
/*================= 公有函数声明 ====================================*/
//EX_CpuReg 
EX_CpuReg void Periph_ModulePower(unsigned int mPeriph, unsigned int bOn);


/******************************************************************************
// END :
******************************************************************************/
#endif // __CpuReg_H__

