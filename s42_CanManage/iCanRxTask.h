#ifndef __iCanRxTask_H__
#define __iCanRxTask_H__
/******************************************************************************
* @file    iCanRxTask.h
* @author  yx
* @version V1.0
* @date    2013-09-09
* @brief   
* 
#include  "iCanRxTask.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

/*================= extern ============================================*/
#ifdef  __iCanRxTask_C__
#define EX_iCanRxTask
#else
#define EX_iCanRxTask extern 
#endif
/*================= ���� ============================================*/
//#define 
/*================= �ṹ�嶨�� ======================================*/

/*================= ���нṹ�������� ================================*/
/*
typedef struct{
	U8 sequStart;
}TStruct_st;
TStruct_st stStruct;
*/

/*-----------------    ----------------------------------*/

/*================= ˽�к������� ====================================*/
#ifdef  __iCanRxTask_C__

#endif  //__iCanRxTask_C__
/*================= ���к������� ====================================*/
//EX_iCanRxTask 

//��������֡��
extern void iCanRxDataFrm(void);

//�����ļ����¼�֡
extern void iCanRxEvtFile(U8 mEvtBuf);
//�����ļ�����Ϣ֡
extern void iCanRxMesgFile(U8 mMesgBuf);

extern BOOL iCanRxFile_PageIsInquireRegist(void);
extern BOOL iCanRxFile_PageIsLoopBrowse(void);




/******************************************************************************
// END :
******************************************************************************/
#endif // __iCanRxTask_H__

