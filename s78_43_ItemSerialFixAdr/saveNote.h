#ifndef __saveNote_H__
#define __saveNote_H__
/******************************************************************************
* @file    saveNote.h
* @author  yx
* @version V1.1
* @date    2013-09-23
* @brief   ����ע��
* 
* V1.1��2013-09-23 
*		����洢��ַ��ֻ�б����ġ� ������������δ����
* V1.0��2013-01-04
*
#include  "saveNote.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

#include  "strDevice.h"
/*================= extern ============================================*/
#ifdef  __saveNote_C__
#define EX_saveNote
#else
#define EX_saveNote extern 
#endif
/*================= ���� ============================================*/
//#define 
/*================= �ṹ�嶨�� ======================================*/

/*================= ���нṹ�������� ================================*/

/*================= ˽�к������� ====================================*/
#ifdef  __saveNote_C__

// ����note�洢��ַ��������
static BOOL cacuFlsOffsetAdr_Note_machineMe(
								TDev_un *pDev, U32 *pRtnAdr);
// ��������·�ڵ�ַ��
static BOOL cacuFlsOffsetNote_me_dete(
								TDev_un *pDev, U32 *pRtnAdr);
// ����������
static BOOL cacuFlsOffsetNote_me_extg(
								TDev_un *pDev, U32 *pRtnAdr);

#endif  //__saveNote_C__

/*================= ���к�������-lib�ڲ� ====================================*/
//EX_saveNote 
//����ע�͵�ƫ�Ƶ�ַ:
extern BOOL GetFlsOffsetAdr_Note_Wr(TDev_un *pDev, U32 *pRtnAdr);
extern BOOL GetFlsOffsetAdr_Note_Rd(TDev_un *pDev, U32 *pRtnAdr);

/*================= ���к�������-lib�ⲿ ====================================*/
//EX_saveNote 

extern BOOL FlsRd_Note(TDev_un *pDev, U8 *pRtnNote);

extern BOOL FlsSave_Note(TDev_un *pDev, U8 *pNoteByte, 
						U8 taskId, U8 flsId);

/******************************************************************************
// END :
******************************************************************************/
#endif // __saveNote_H__

