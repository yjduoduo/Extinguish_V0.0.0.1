#ifndef __CanIntCouple_H__
#define __CanIntCouple_H__
/******************************************************************************
* @file    CanIntCouple.h
* @author  yx
* @version V1.0
* @date    2013-07-25
* @brief   
* 
#include  "CanIntCouple.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

/*================= extern ============================================*/
#ifdef  __CanIntCouple_C__
#define EX_CanIntCouple
#else
#define EX_CanIntCouple extern 
#endif
/*================= ���� ============================================*/
//#define 
/*================= �ṹ�嶨�� ======================================*/

/*================= ���нṹ�������� ================================*/

/*================= ˽�к������� ====================================*/
#ifdef  __CanIntCouple_C__

#endif  //__CanIntCouple_C__
/*================= ���к������� ====================================*/
//EX_CanIntCouple 

//OUT: �жϵ�id�� enable��Ϊdisable�� bit��
extern U32 IntDisable_May_CanAdd(void);
//IN:  �жϵ�id�� enable��Ϊdisable�� bit�����ڻָ�enable��״̬��
extern void IntEnable_May_CanAdd(U32 whichDisable);

extern U32 IntDisable_May_iCanAdd(void);
extern void IntEnable_May_iCanAdd(U32 whichDisable);
extern U32 IntDisable_May_eCanAdd(void);
extern void IntEnable_May_eCanAdd(U32 whichDisable);


/******************************************************************************
// END :
******************************************************************************/
#endif // __CanIntCouple_H__

