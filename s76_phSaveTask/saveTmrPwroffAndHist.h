#ifndef __saveTmrPwroffAndHist_H__
#define __saveTmrPwroffAndHist_H__
/******************************************************************************
* @file    saveTmrPwroffAndHist.h
* @author  yx
* @version V1.1
* @date    2013-9-04
* @brief   
*
* V1.0  2012-01-05
* 
#include  "saveTmrPwroffAndHist.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

/*================= extern ============================================*/
#ifdef  __saveTmrPwroffAndHist_C__
#define EX_saveTmrPwroffAndHist
#else
#define EX_saveTmrPwroffAndHist extern 
#endif
/*================= ���� ============================================*/
//#define 
/*================= �ṹ�嶨�� ======================================*/

/*================= ���нṹ�������� ================================*/

/*================= ˽�к������� ====================================*/
#ifdef  __saveTmrPwroffAndHist_C__

#endif  //__saveTmrPwroffAndHist_C__

/*================= ���к�������-master�� ====================================*/
//EX_saveTmrPwroffAndHist 
// saveTask.c 

//��ʷ��¼����ػ�ʱ��
extern BOOL PwrOff_toHist(void);


/*================= ���к�������-lib�� ====================================*/
//EX_saveTmrPwroffAndHist 

//����ػ�ʱ��Ķ�ʱ��
extern void SavePwrOff_Tmr_Init(void);
extern BOOL bSavePwrOff_Arrived(void);
extern void FlsWr_pwrOff_Start(void); //-> FlsWr_pwrOff_New(&stClock);


//������ʷ��¼��ʱ������
extern void SaveHist_Tmr_Init(void);
extern BOOL bSaveHist_Arrived(void);

// save���񣬶�ʱɾ���Ķ�ʱ��
extern void SaveFlsId_Tmr_Init(void);
extern BOOL bSaveFlsId_Arrived(void);



/******************************************************************************
// END :
******************************************************************************/
#endif // __saveTmrPwroffAndHist_H__

