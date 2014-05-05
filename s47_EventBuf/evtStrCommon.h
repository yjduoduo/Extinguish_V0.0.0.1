#ifndef __evtStrCommon_H__
#define __evtStrCommon_H__
/******************************************************************************
* @file    evtStrCommon.h
* @author  yx
* @version V1.0
* @date    2013-09-23
* @brief   �����¼����õĽṹ;
*
* @Versin history:
* V1.0, 2013-09-23
* 
#include  "evtStrCommon.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

#include  "strDevice.h"

#include  "evt_Para.h"
/*=================  ============================================*/

/*================= һ���¼� ��ʶ ================================*/

typedef struct{
	EVTWORD sequ;  //���  0~
	EVTWORD locat; //����ƫ��
}TEvtBufWho_st; //һ���¼���


/*================= Commmon �洢 ================================*/

#pragma pack(1)	
typedef struct{ //ÿ���¼����еġ�
	EVTWORD pre;
	EVTWORD next;
	
	TDev_un  unDev;   //���ж�buf[N]�Ƿ������ݵ��о�
	U8     devType; //�豸�������ͣ����û�����
}TEvtPos_st; //
#pragma pack()


/*================= �¼��������� ================================*/
	
//total = 0: head = end;  every.pre = next = MAX;
//total = 1: head = end;  every.pre = next = MAX;
//total = 2: head != end; every.pre != next

typedef struct{
	EVTWORD total;  
	EVTWORD head;
	EVTWORD end;  //��Ч����
	U8 bFull;
	
	BOOL bVaryTotal;	//������ 
	BOOL bVaryBuf;	   //buf�б� 
}TPointEvt_st;

/******************************************************************************
// END :
******************************************************************************/
#endif // __evtStrCommon_H__

