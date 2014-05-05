#ifndef __saveField_H__
#define __saveField_H__
/******************************************************************************
* @file    saveField.h
* @author  yx
* @version V1.0
* @date    2013-01-04
* @brief   ��·�ֳ������Ǽ�
* 
#include  "saveField.h"
******************************************************************************/

#include  "prjCompileCon.h"
#include  "strFlsItmStruct.h"

/*================= extern ============================================*/
#ifdef  __saveField_C__
#define EX_saveField
#else
#define EX_saveField extern 
#endif

/*================= ���� ============================================*/
//#define 
/*================= �ṹ�嶨�� ======================================*/

/*================= ���нṹ�������� ================================*/


/*================= ˽�к������� ================================*/
#ifdef  __saveField_C__
BOOL bCorrespDisable_one_fieldAndBuf(
							U8 mLoop, U8 mAddr, TDev_un *pDev);
#endif // __saveField_C__
/*================= ���к�������-lib�ڲ� ====================================*/
//EX_saveField 

// ���field�Ķ��� �� disable buf �Ƿ��Ӧ��
extern BOOL bCorrespDisable_FieldAndBuf(void);

//�����ֳ������Ǽǵ�ƫ�Ƶ�ַ:
extern BOOL GetFlsOffsetAdr_Field(U8 mLoop, U8 mAddr, 
										U32 *pRtnAdr);

//��ѯfield�Ƿ�����:
//use: ���� public buf;
extern BOOL bFlsField_beDisabled(U8 mLoop, U8 mAddr);

/*================= ���к�������-lib�ⲿ ====================================*/
//EX_saveField 

extern BOOL FlsRd_Field(TFlsFieldHead_st *pHead, U8 *pRtnRegistByte);

// TFlsFieldOne_st
extern BOOL FlsSave_Field(TFlsFieldHead_st *pHead, 
						 U8 *pRegistByte, 
						U8 taskId, U8 flsId);

extern BOOL FlsClr_Field(TFlsFieldHead_st *pHead,
						U8 taskId, U8 flsId);


/******************************************************************************
// END :
******************************************************************************/
#endif // __saveField_H__

