#ifndef __flsItemState_H__
#define __flsItemState_H__
/******************************************************************************
* @file    flsItemState.h
* @author  yx
* @version V1.0
* @date    2013-07-23
* @brief   存储的状态 emFlsItemState 。
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
/*================= 常数 ============================================*/

enum emFlsItemState{
	U_FlsItem_Error_State,  // CRC错，或head != mFlsItem;
	U_FlsItem_Space_State,  // 全FF状态
	U_FlsItem_Erase_State,  // 正在被erase
	U_FlsItem_Copyed_State, // 正在被copy, 此时不能被改变
	U_FlsItem_Renew_State,  // 正在写入
	U_FlsItem_State_MAX,
};
	
/*================= 结构体定义 ======================================*/

/*================= 公有结构变量声明 ================================*/

/*================= 私有函数声明 ====================================*/
#ifdef  __flsItemState_C__

#endif  //__flsItemState_C__

/*================= 公有函数声明-lib内部 ====================================*/
//EX_flsItemState 

// TRUE=允许读, (!Error + !Erase + !Renew)
extern BOOL bFlsItem_IsReadAllow(U8 mFlsItem, U8 mPart);

/*================= 公有函数声明-lib内部 ====================================*/
//EX_flsItemState 
	
extern void Set_FlsItemState(U8 mState, U8 mFlsItem, U8 mPart);
extern void Clr_FlsItemState(U8 mState, U8 mFlsItem, U8 mPart);
extern BOOL bFlsItem_isState(U8 mState, U8 mFlsItem, U8 mPart);

// 状态清零
extern void FlsItem_StateAll_Init(void);
extern void FlsItem_State_Init(U8 mState);

// 整体被覆盖的次数。
// 若多次被整体覆盖数据仍error，说明flash硬件出错。
extern void FlsItemState_copyNum_Inc(U8 mFlsItem, U8 mPart);
extern void FlsItemState_copyNum_Clr(U8 mFlsItem, U8 mPart);
extern BOOL bFlsItemState_copyNum_Over(U8 mFlsItem, U8 mPart);
	
// 当前存储的数据无效
extern BOOL bFlsItem_IsErrorOrSpace(U8 mFlsItem, U8 mPart);

// 数据有效：
extern BOOL bFlsItem_IsUsual(U8 mFlsItem, U8 mPart);



/******************************************************************************
// END :
******************************************************************************/
#endif // __flsItemState_H__

