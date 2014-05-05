#ifndef __saveNetMachine_H__
#define __saveNetMachine_H__
/******************************************************************************
* @file    saveNetMachine.h
* @author  yx
* @version V1.0
* @date    2013-01-04
* @brief   �����������ã�
* 
#include  "saveNetMachine.h"
******************************************************************************/
//
#include  "prjCompileCon.h"
#include  "flsStoreBytesDef.h"

/*================= extern ============================================*/
#ifdef  __saveNetMachine_C__
#define EX_saveNetMachine
#else
#define EX_saveNetMachine extern 
#endif
/*================= ���� ============================================*/
//#define 
/*================= �ṹ�嶨�� ======================================*/

/*================= ���нṹ�������� ================================*/

/*================= ˽�к������� ====================================*/
#ifdef  __saveNetMachine_C__

// OUT: pRtnBuf ���������� netMachine�����ݣ�
BOOL flsRd_NetMach_toBuf(U8 mPart, U8 *pBufS);

BOOL flsSave_NetMachine_change(U8 mMachS, U8 mMachE, 
						BOOL bAdd,
						U8 taskId, U8 flsId);

#endif  //__saveNetMachine_C__

/*================= ���к�������-lib�ⲿ ====================================*/
//EX_saveNetMachine 
extern BOOL FlsRd_NetMachine(void);

extern BOOL FlsSave_NetMachine_Add(U8 mMachS, U8 mMachE, 
							  U8 taskId, U8 flsId);
extern BOOL FlsSave_NetMachine_Delete(U8 mMachS, U8 mMachE, 
							  U8 taskId, U8 flsId);


/******************************************************************************
// END :
******************************************************************************/
#endif // __saveNetMachine_H__

