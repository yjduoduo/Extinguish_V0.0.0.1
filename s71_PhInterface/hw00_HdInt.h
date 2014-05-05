#ifndef __hw00_HdInt_H__
#define __hw00_HdInt_H__
/******************************************************************************
* @file    hw00_HdInt.h
* @author  yx
* @version V1.0
* @date    2012-01-05
* @brief   
* 
#include  "hw00_HdInt.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

/*================= extern ============================================*/
#ifdef  __hw00_HdInt_C__
#define EX_hw00_HdInt
#else
#define EX_hw00_HdInt extern 
#endif
/*================= 常数 ============================================*/

enum emHardWarePeriph{
	U_Hd_Int_iCAN,
	U_Hd_Int_eCAN,
	U_Hd_Int_UART_DownLoad,
	U_Hd_Int_TIMER_SysTick,
	U_Hd_Int_TIMER_NorFlash,
		
	U_Hd_Int_MAX,
};
	



/*================= 结构体定义 ======================================*/

/*================= 公有结构变量声明 ================================*/

/*================= 私有函数声明 ====================================*/
#ifdef  __hw00_HdInt_C__
U8 bSysIntDisable[U_Hd_Int_MAX]; //中断禁止
U8 bSysIntHdOpen[U_Hd_Int_MAX];  //硬件已开

#endif  //__hw00_HdInt_C__
/*================= 公有函数声明 ====================================*/
//EX_hw00_HdInt 

EX_hw00_HdInt   void MyInt_Status_Init(void);

EX_hw00_HdInt   U8 MyInt_Disable(unsigned int ulInterrupt); //emMySysIntId
EX_hw00_HdInt   U8 MyInt_Enable(unsigned int ulInterrupt);

EX_hw00_HdInt   void MyInt_All_Enable(void);
EX_hw00_HdInt   void MyInt_All_Disable(void);

EX_hw00_HdInt   U32 MyInt_AllDisable_RtnBits(void);
EX_hw00_HdInt   void MyInt_AllEnable_FromBits(U32 mOpeaIntBits);

EX_hw00_HdInt   U32 MyInt_N_Disable_RtnBits(U32 mOpeaIntBits);
EX_hw00_HdInt   void MyInt_N_Enable_FromBits(U32 mOpeaIntBits);

EX_hw00_HdInt   void Notify_SysInt_Hd_Open(unsigned int ulInterrupt);
EX_hw00_HdInt   void Notify_SysInt_Hd_Close(unsigned int ulInterrupt);
EX_hw00_HdInt   void Notify_SysInt_Hd_AllClose(void);
EX_hw00_HdInt   U8 bGet_SysInt_Hd_Open(unsigned int ulInterrupt);




/******************************************************************************
// END :
******************************************************************************/
#endif // __hw00_HdInt_H__

