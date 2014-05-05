#ifndef __HdInterface_H__
#define __HdInterface_H__
/******************************************************************************
* @file    HdInterface.h
* @author  yx
* @version V1.0
* @date    2012-01-05
* @brief   ��ֹӦ�ó������ hw�� hwEx
		���е��ж���ں�����Ӧ �� "hw00_CallBack.c" ����
		�й�cpu�Ĳ��ܹ���module�ļĴ�������CpuReg.c�
* 
#include  "HdInterface.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

/*================= extern ============================================*/
#ifdef  __HdInterface_C__
#define EX_HdInterface
#else
#define EX_HdInterface extern 
#endif
/*================= ���� ============================================*/

enum emTmrLogicId{  // uint8 tmr_id;
	U_Tmr_SysTick_ID = 0, // ���漰Ӳ��
	U_Tmr_NorFlash_ID = 1, // 
};
#define U_TMR_ID_MAX  2

#define U_TMR_ID_Default  U_Tmr_SysTick_ID

/*================= �ṹ�嶨�� ======================================*/

/*================= ���нṹ�������� ================================*/

/*================= ˽�к������� ====================================*/
#ifdef  __HdInterface_C__
extern void MyTickTimer_IntrHander(void); //�ж� Handle
extern void NorFlashTimer_IntrHander(void); //�ж� Handle

#endif //__HdInterface_C__
/*================= ���к�������-WatcherDog ====================================*/
//EX_HdInterface 

extern void MyDog_Init(void);
extern void MyDog_Feed(void);

/*================= ���к�������-Timer ====================================*/
//EX_HdInterface 

// Int:
extern void TimerHd_Int_Enable(U8 tmr_id); // emTmrLogicId
extern void TimerHd_Int_Disable(U8 tmr_id);

// Ӧ�ò� �� Ӳ�� ��uartId �Ķ�Ӧ��ϵ��
// const TTmrProp_st cstTmrPeriId[U_TMR_ID_MAX+1] ;
extern U8 GetTmrDriveId_FromTmrId(U8 tmr_id);
extern U8 GetTmrId_FromTmrPeriId(U8 tmrDriveId);
extern void MyTimer_IntrHander(U8 tmrDriveId); //�ж� Handle

extern void MyTickTimer_Init(void);
extern void TickTimer_HdInt(U8 bAllow);  //�ж� ����/��ֹ
// extern void MyTickTimer_IntrHander(void); //�ж� Handle
extern void MyTickTimer_Close(void);


extern void NorFlashTimer_Init(U32 mTmrUs);
// extern void NorFlashTimer_IntrHander(void); //�ж� Handle
extern BOOL bNorFlashTimer_Arrived(void); //
extern void NorFlashTimer_Close(void);

/******************************************************************************
// END :
******************************************************************************/
#endif // __HdInterface_H__

