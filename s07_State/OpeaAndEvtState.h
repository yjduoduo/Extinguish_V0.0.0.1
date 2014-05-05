#ifndef __OpeaAndEvtState_H__
#define __OpeaAndEvtState_H__
/******************************************************************************
* @file    OpeaAndEvtState.h
* @author  yx
* @version V1.0
* @date    2013-10-17 23:23 
* @brief   系统操作和事件引发的状态，主要涉及LED和Sound.
* 
#include  "OpeaAndEvtState.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

/*================= extern ============================================*/
#ifdef  __OpeaAndEvtState_C__
#define EX_OpeaAndEvtState
#else
#define EX_OpeaAndEvtState extern 
#endif
/*================= 常数 ============================================*/

typedef enum { // 前几个保持 与事件队列  emEvtClass 一致
	U_StateOaeCls_Alarm = 0,
	U_StateOaeCls_Fault = 1,
	U_StateOaeCls_Link = 2,
	U_StateOaeCls_Extg = 3,
	U_StateOaeCls_Spvs = 4, //监管
	U_StateOaeCls_Dsab = 5, //屏蔽
	
	U_StateOaeCls_Action = 7,
	U_StateOaeCls_Ack = 8,
	
	U_StateOaeCls_PowerMain,
	U_StateOaeCls_PowerBty,
	
	// 以下没有恢复状态
	
	U_StateOaeCls_Key,
	U_StateOaeCls_Silence,
	
	U_StateOaeCls_Reset,
	
	U_StateOaeCls_ActionAutoAllow,
	U_StateOaeCls_ActionAutoForbid,
	U_StateOaeCls_ActionManuAllow,
	U_StateOaeCls_ActionManuForbid,
	
	
}emStateOaeClass;	
	
/*================= 结构体定义 ======================================*/

/*================= 公有结构变量声明 ================================*/

/*================= 私有函数声明 ====================================*/
#ifdef  __OpeaAndEvtState_C__

BOOL getSoundSequ(U8 mSound, U8 *pRtnSequ);
BOOL bSysStaNowSoundHighThanMe(U8 mSoundNew);
void sysStaMeSound(U8 mSoundNew);

// 判断当前是否已无事件，若无，to silence状态。
void sysSta_JdgNowNoEvent_toSilence(void);

#endif  //__OpeaAndEvtState_C__
/*================= 公有函数声明 ====================================*/
//EX_OpeaAndEvtState 

// 新事件，或正常状态:
extern void SysStaNewEvent(emStateOaeClass mCls); 
// 撤销事件，或error状态：
extern void SysStaEventRstrSpace(emStateOaeClass mCls); 

/******************************************************************************
// END :
******************************************************************************/
#endif // __OpeaAndEvtState_H__

