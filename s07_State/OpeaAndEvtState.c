#define __OpeaAndEvtState_C__
/******************************************************************************
* @file    OpeaAndEvtState.c
* @author  yx
* @version V1.0
* @date    2013-10-17 23:23 
* @brief   ϵͳ�������¼�������״̬����Ҫ�漰LED��Sound.
* @brief   
* 
******************************************************************************/
#include  "OpeaAndEvtState.h"

#include  "sysStatus.h"
#include  "phIoLed.h"
#include  "phIoSound.h"

//#include "incFile.h"	


/*================= ���� ============================================*/
// ���������ȼ���
const U8 cstSoundPriority[] = 
{
	U_SOUND_Alarm_FUNC, 
	U_SOUND_Action_FUNC, U_SOUND_Ack_FUNC,
	U_SOUND_Fault_FUNC,
	
	U_SOUND_Key_FUNC,
	U_SOUND_Silence_FUNC
};
/*================= �ṹ���� ========================================*/

/*================= ˽�нṹ�������� ================================*/

/*================= ���ú������� ====================================*/
// EX_lcdPg_MainAndEvtChange

// �ж� ���¼���
extern BOOL pgEvt_jdgHaveEvent(void);

/*================= ���к������� ====================================*/

/*================= ˽�к������� ====================================*/

/*=================  ================================================*/
		

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/


BOOL getSoundSequ(U8 mSound, U8 *pRtnSequ)
{
U8 sequ;
U8 mMax = sizeof(cstSoundPriority);

	for(sequ=0; sequ<mMax; sequ++)
	{
		if(mSound == cstSoundPriority[sequ])
		{
			*pRtnSequ = sequ;
			return TRUE;
		}
	}
	return FALSE;
}

BOOL bSysStaNowSoundHighThanMe(U8 mSoundNew)
{
U8 mSequNow;
U8 mSequNew;
	
	if(!getSoundSequ(GetNowSound(), &mSequNow))
	{
		return FALSE;
	}
	if(!getSoundSequ(mSoundNew, &mSequNew))
	{
		return FALSE;
	}
	
	return (mSequNow < mSequNew);
}

void sysStaMeSound(U8 mSoundNew)
{
	if(!bSysStaNowSoundHighThanMe(mSoundNew))
	{
		SoundNewSet(mSoundNew);
	}
}


// �жϵ�ǰ�Ƿ������¼������ޣ�to silence״̬��
void sysSta_JdgNowNoEvent_toSilence(void)
{
	
	if(pgEvt_jdgHaveEvent())
	{
		if(bSysStaNowSoundHighThanMe(U_SOUND_Key_FUNC))
		{
			SoundNewSet(U_SOUND_Silence_FUNC);
		}
		LedFuncOff(U_LED_silence);
	}
}



/******************************************************************************
* NAME: 
* FUNC: // ���¼���������״̬: //���⡢��ʾ
*   IN: ���¼�buf�б�ʱ���á�
*  OUT: 
******************************************************************************/

void SysStaNewEvent(emStateOaeClass mCls)
{

	switch(mCls)
	{
		case U_StateOaeCls_Alarm:
			LedFuncOn(U_LED_Alarm);
			LedFuncOff(U_LED_silence);
			sysStaMeSound(U_SOUND_Alarm_FUNC);
			break;
		case U_StateOaeCls_Fault:
			LedFuncOff(U_LED_silence);
			sysStaMeSound(U_SOUND_Fault_FUNC);
			break;
		case U_StateOaeCls_Link:
			break;
		case U_StateOaeCls_Extg:
			break;
		case U_StateOaeCls_Spvs:
			break;
		case U_StateOaeCls_Dsab:
			break;
			
		case U_StateOaeCls_Action:
			LedFuncOff(U_LED_silence);
			sysStaMeSound(U_SOUND_Action_FUNC);
			break;
		case U_StateOaeCls_Ack:
			LedFuncOff(U_LED_silence);
			sysStaMeSound(U_SOUND_Ack_FUNC);
			break;
		case U_StateOaeCls_Key:
			sysStaMeSound(U_SOUND_Key_FUNC);
			break;
			
		case U_StateOaeCls_Silence:
			SoundNewSet(U_SOUND_Silence_FUNC);
			if(pgEvt_jdgHaveEvent())
			{
				LedFuncOn(U_LED_silence);
			}
			break;
			
		case U_StateOaeCls_PowerMain:
			LedFuncOn(U_LED_pwrMain);
			break;
		case U_StateOaeCls_PowerBty:
			LedFuncOn(U_LED_pwrBty);
			break;
			
		case U_StateOaeCls_Reset:
			break;
	
		case U_StateOaeCls_ActionAutoAllow:
		case U_StateOaeCls_ActionAutoForbid:
		case U_StateOaeCls_ActionManuAllow:
		case U_StateOaeCls_ActionManuForbid:
			SetSysState(U_SysSta_bAutoManuChanged);
			break;
		default:
			break;
	}
}

/******************************************************************************
* NAME: 
* FUNC: // �����¼�����error״̬�� //���⡢��ʾ
*   IN: ���¼�buf�б�ʱ���á�
*  OUT: 
******************************************************************************/

void SysStaEventRstrSpace(emStateOaeClass mCls)
{
	
	switch(mCls)
	{
		case U_StateOaeCls_Alarm:
			LedFuncOff(U_LED_Alarm);
			sysSta_JdgNowNoEvent_toSilence();
			break;
		case U_StateOaeCls_Fault:
			sysSta_JdgNowNoEvent_toSilence();
			break;
		case U_StateOaeCls_Link:
			break;
		case U_StateOaeCls_Extg:
			break;
		case U_StateOaeCls_Spvs:
			break;
		case U_StateOaeCls_Dsab:
			break;
			
		case U_StateOaeCls_Action:
			sysSta_JdgNowNoEvent_toSilence();
			break;
		case U_StateOaeCls_Ack:
			sysSta_JdgNowNoEvent_toSilence();
			break;
			
		case U_StateOaeCls_PowerMain:
			LedFuncOff(U_LED_pwrMain);
			break;
		case U_StateOaeCls_PowerBty:
			LedFuncOff(U_LED_pwrBty);
			break;
			
		default:
			break;
	}
}




/******************************************************************************
* FUNC: //
******************************************************************************/



/******************************************************************************
* FUNC: // END
*   IN:
*  OUT: 
******************************************************************************/
