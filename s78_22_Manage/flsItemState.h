#ifndef __flsItemState_H__
#define __flsItemState_H__
/******************************************************************************
* @file    flsItemState.h
* @author  yx
* @version V1.0
* @date    2013-07-23
* @brief   �洢��״̬ emFlsItemState ��
* 
#include  "flsItemState.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

/*================= extern ============================================*/
#ifdef  __flsItemState_C__
#define EX_flsItemState
#else
#define EX_flsItemState extern 
#endif
/*================= ���� ============================================*/

enum emFlsItemState{
	U_FlsItem_Error_State,  // CRC����head != mFlsItem;
	U_FlsItem_Space_State,  // ȫFF״̬
	U_FlsItem_Erase_State,  // ���ڱ�erase
	U_FlsItem_Copyed_State, // ���ڱ�copy, ��ʱ���ܱ��ı�
	U_FlsItem_Renew_State,  // ����д��
	U_FlsItem_State_MAX,
};
	
/*================= �ṹ�嶨�� ======================================*/

/*================= ���нṹ�������� ================================*/

/*================= ˽�к������� ====================================*/
#ifdef  __flsItemState_C__

#endif  //__flsItemState_C__

/*================= ���к�������-lib�ڲ� ====================================*/
//EX_flsItemState 

// TRUE=�����, (!Error + !Erase + !Renew)
extern BOOL bFlsItem_IsReadAllow(U8 mFlsItem, U8 mPart);

/*================= ���к�������-lib�ڲ� ====================================*/
//EX_flsItemState 
	
extern void Set_FlsItemState(U8 mState, U8 mFlsItem, U8 mPart);
extern void Clr_FlsItemState(U8 mState, U8 mFlsItem, U8 mPart);
extern BOOL bFlsItem_isState(U8 mState, U8 mFlsItem, U8 mPart);

// ״̬����
extern void FlsItem_StateAll_Init(void);
extern void FlsItem_State_Init(U8 mState);

// ���屻���ǵĴ�����
// ����α����帲��������error��˵��flashӲ������
extern void FlsItemState_copyNum_Inc(U8 mFlsItem, U8 mPart);
extern void FlsItemState_copyNum_Clr(U8 mFlsItem, U8 mPart);
extern BOOL bFlsItemState_copyNum_Over(U8 mFlsItem, U8 mPart);
	
// ��ǰ�洢��������Ч
extern BOOL bFlsItem_IsErrorOrSpace(U8 mFlsItem, U8 mPart);

// ������Ч��
extern BOOL bFlsItem_IsUsual(U8 mFlsItem, U8 mPart);



/******************************************************************************
// END :
******************************************************************************/
#endif // __flsItemState_H__

