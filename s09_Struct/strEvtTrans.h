#ifndef __strEvtTrans_H__
#define __strEvtTrans_H__
/******************************************************************************
* @file    strEvtTrans.h
* @author  yx
* @version V1.1
* @date    2013-08-22
* @brief   
* 
* V1.1�� add: void GetEvtTransStrAndClock(...);
		2013-08-22
* V1.0�� 2013-07-01
*
#include  "strEvtTrans.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

#include  "strDevice.h"
#include  "strClock.h"
/*================= extern ============================================*/
#ifdef  __strEvtTrans_C__
#define EX_strEvtTrans
#else
#define EX_strEvtTrans extern 
#endif
/*================= ���� ============================================*/
//#define 
/*================= �ṹ�嶨�� ======================================*/

/*================= ���нṹ�������� ================================*/

#define U_EVT_TRANS_BYTE_MAX	0x0F //4+3+6=13

#pragma pack(1)	
typedef struct{
	TDev_un unDev;
	U8 type; //�豸����  //����������¼������manu/auto/remote.
	U8 thing;
	U8 thiFurther; //�����
	
	TEvtClock_st evtClock;
	//U8 hour; //���ã�
	//U8 min;
}TEvtTrans_st; //
#pragma pack()	

/*================= ���к������� ====================================*/
//EX_strEvtTrans 

extern void IniEvtTransStruct(TEvtTrans_st *pEvtTrans);
extern void GetEvtTransStrAndClock(TDev_un *pDev,
							TEvtTrans_st **pEvtTrans);
/*================= ˽�к������� ====================================*/
#ifdef  __strEvtTrans_C__

#endif  //__strEvtTrans_C__


/******************************************************************************
// END :
******************************************************************************/
#endif // __strEvtTrans_H__

