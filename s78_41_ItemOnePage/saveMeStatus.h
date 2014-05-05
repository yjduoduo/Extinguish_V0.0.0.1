#ifndef __saveMeStatus_H__
#define __saveMeStatus_H__
/******************************************************************************
* @file    saveMeStatus.h
* @author  yx
* @version V1.1
* @date    2013-09-23 
* @brief   ϵͳ����
* 
* V1.1, 2013-09-23 
		ȥ���� unSet�Ŀ��ƣ�������master���޸����λ�õĶ��壬���Ӱ�졣
* V1.0, 2013-01-04
*
#include  "saveMeStatus.h"
******************************************************************************/
//
#include  "prjCompileCon.h"
#include  "strFlsItmStruct.h"

/*================= extern ============================================*/
#ifdef  __saveMeStatus_C__
#define EX_saveMeStatus
#else
#define EX_saveMeStatus extern 
#endif
/*================= ���� ============================================*/
//#define 
/*================= �ṹ�嶨�� ======================================*/

/*================= ���нṹ�������� ================================*/

/*================= ˽�к������� ====================================*/
#ifdef  __saveMeStatus_C__
static TFlsSysSet_un  unSysSet; // ���漰 unSet�ֶΣ�ֻ��֤�������ֽ�����

#endif  //__saveMeStatus_C__


/*================= ���к�������-lib�ⲿ ====================================*/
//EX_saveMeStatus 

// ����
extern BOOL FlsSysSetMeStatus_Save(U8 taskId, U8 flsId);

// ��flash����
extern BOOL FlsRd_MeStatus(void);

// �������ҿ��ܱ��ı����ݡ�
extern TFlsSysSet_un *pGetFlsSysSet(void);



/******************************************************************************
// END :
******************************************************************************/
#endif // __saveMeStatus_H__

