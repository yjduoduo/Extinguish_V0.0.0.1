#ifndef __saveHistory_H__
#define __saveHistory_H__
/******************************************************************************
* @file    saveHistory.h
* @author  yx
* @version V1.0
* @date    2013-07-23
* @brief   add һ����ʷ��¼��
		// �Ƚ�ָ��ͼ�¼�Ƿ����:
		
* 
#include  "saveHistory.h"
******************************************************************************/

#include  "prjCompileCon.h"

#include  "historyClsDef.h"
#include  "strEvtTrans.h"

/*================= extern ============================================*/
#ifdef  __saveHistory_C__
#define EX_saveHistory
#else
#define EX_saveHistory extern 
#endif

/*================= ���� ============================================*/

/*================= �ṹ�嶨�� ======================================*/

/*================= ���нṹ�������� ================================*/



/*================= ˽�к������� ====================================*/
#ifdef  __saveHistory_C__

// �Ƚ�ָ��ͼ�¼�Ƿ����:
// *  OUT: FlsItemState.bError
void histPoint_1Cls1Part_Init(U8 mHistCls, U8 mHistPart);

#endif

/*================= ���к�������-lib�ڲ� ====================================*/
// EX_historyWrBuf

// clr buf;
// �Ƚ�ָ��ͼ�¼�Ƿ����:
// * ��ҪԤ��ִ�� InitAll_FlsQueHeadEnd(); 
extern void SaveHist_Init(void);

/*================= ���к�������-lib�ⲿ ====================================*/
// EX_historyWrBuf

// ����ʷ��¼��
extern U8 HistNewEvent(TEvtTrans_st *pEvtTrans);

/******************************************************************************
// END :
******************************************************************************/
#endif // __saveHistory_H__

