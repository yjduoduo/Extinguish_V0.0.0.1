#ifndef __saveLinkProg_H__
#define __saveLinkProg_H__
/******************************************************************************
* @file    saveLinkProg.h
* @author  yx
* @version V1.1
* @date    2013-09-23
* @brief   ���� �������
* 
* V1.1��2013-09-23 
*		����洢��ַ��ֻ�б����ġ� ������������δ����
* V1.0��2013-01-04
*
* 
#include  "saveLinkProg.h"
******************************************************************************/
//
#include  "prjCompileCon.h"
#include  "strDevice.h"

/*================= extern ============================================*/
#ifdef  __saveLinkProg_C__
#define EX_saveLinkProg
#else
#define EX_saveLinkProg extern 
#endif
/*================= ���� ============================================*/
//#define 
/*================= �ṹ�嶨�� ======================================*/

/*================= ���нṹ�������� ================================*/

/*================= ˽�к������� ====================================*/
#ifdef  __saveLinkProg_C__

#endif  //__saveLinkProg_C__

/*================= ���к�������-lib�ڲ� ====================================*/
//EX_saveLinkProg 

extern BOOL CacuFlsOffsetAdr_LinkProg(TDev_un *pDev, U32 *pRtnAdr);

// ����link�洢��ַ��������
static BOOL cacuFlsOffsetAdr_Link_machineMe(
								TDev_un *pDev, U32 *pRtnAdr);
// ����������
static BOOL cacuFlsOffsetLink_me_extg(
								TDev_un *pDev, U32 *pRtnAdr);
// ��������·�ڵ�ַ��
static BOOL cacuFlsOffsetLink_me_dete(
								TDev_un *pDev, U32 *pRtnAdr);



/*================= ���к�������-lib�ⲿ ====================================*/
//EX_saveLinkProg 

extern BOOL FlsSave_LinkProg(TDev_un *pDev, U8 *pProgByte, 
							U8 taskId, U8 flsId);
extern BOOL FlsRd_LinkProg(TDev_un *pDev, U8 *pProgByte);

/******************************************************************************
// END :
******************************************************************************/
#endif // __saveLinkProg_H__

