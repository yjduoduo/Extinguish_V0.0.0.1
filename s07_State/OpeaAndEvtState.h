#ifndef __OpeaAndEvtState_H__
#define __OpeaAndEvtState_H__
/******************************************************************************
* @file    OpeaAndEvtState.h
* @author  yx
* @version V1.0
* @date    2013-10-17 23:23 
* @brief   ϵͳ�������¼�������״̬����Ҫ�漰LED��Sound.
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
/*================= ���� ============================================*/

typedef enum { // ǰ�������� ���¼�����  emEvtClass һ��
	U_StateOaeCls_Alarm = 0,
	U_StateOaeCls_Fault = 1,
	U_StateOaeCls_Link = 2,
	U_StateOaeCls_Extg = 3,
	U_StateOaeCls_Spvs = 4, //���
	U_StateOaeCls_Dsab = 5, //����
	
	U_StateOaeCls_Action = 7,
	U_StateOaeCls_Ack = 8,
	
	U_StateOaeCls_PowerMain,
	U_StateOaeCls_PowerBty,
	
	// ����û�лָ�״̬
	
	U_StateOaeCls_Key,
	U_StateOaeCls_Silence,
	
	U_StateOaeCls_Reset,
	
	U_StateOaeCls_ActionAutoAllow,
	U_StateOaeCls_ActionAutoForbid,
	U_StateOaeCls_ActionManuAllow,
	U_StateOaeCls_ActionManuForbid,
	
	
}emStateOaeClass;	
	
/*================= �ṹ�嶨�� ======================================*/

/*================= ���нṹ�������� ================================*/

/*================= ˽�к������� ====================================*/
#ifdef  __OpeaAndEvtState_C__

BOOL getSoundSequ(U8 mSound, U8 *pRtnSequ);
BOOL bSysStaNowSoundHighThanMe(U8 mSoundNew);
void sysStaMeSound(U8 mSoundNew);

// �жϵ�ǰ�Ƿ������¼������ޣ�to silence״̬��
void sysSta_JdgNowNoEvent_toSilence(void);

#endif  //__OpeaAndEvtState_C__
/*================= ���к������� ====================================*/
//EX_OpeaAndEvtState 

// ���¼���������״̬:
extern void SysStaNewEvent(emStateOaeClass mCls); 
// �����¼�����error״̬��
extern void SysStaEventRstrSpace(emStateOaeClass mCls); 

/******************************************************************************
// END :
******************************************************************************/
#endif // __OpeaAndEvtState_H__

