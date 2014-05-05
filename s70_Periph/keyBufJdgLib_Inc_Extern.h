#ifndef __keyBufJdgLib_Inc_Extern_H__
#define __keyBufJdgLib_Inc_Extern_H__
/******************************************************************************
* @file    keyBufJdgLib_Inc_Extern.h
* @author  yx
* @version V1.4
* @date    2013-09-29
* @brief   keyBufJdgLib �� head�ļ���
* 
* V1.4, 2013-09-29
*		�����޸İ��º͵ȴ���ʱ�䡣emKeyDownTmr
* V1.3,2013-08-28
*
*
#include  "keyBufJdgLib_Inc_Extern.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

/*================= ���� ============================================*/
#define U_KEY_JUDGE_MAX    32 // lib����ж�32������


#define U_KEY_BOARD_MAX  		U_KEY_JUDGE_MAX // ������
#define U_KEY_FUNCTION_MAX		(U_KEY_BOARD_MAX + U_KEY_JUDGE_MAX) // ������

/*================= ���� ============================================*/

// ��Ҫ����ɨ��һ�ܵ�ʱ�������
//5ms*7��ɨ�裬35ms���
enum emKeyDownTmr{
	U_KeyEnter_Tmr_MAX	= 200,  //�������µ��ʱ��,�ż������.��DITHER~LONG֮���ʾ��LONG.
	U_KeyEnter_TmrDither = 3, //2  //����   2*35ms=70ms
	U_KeyEnter_TmrContinueSound = 3,//�ǳ�������ȥ����buzzer���ʱ�䡣U_KeyEnter_TmrDither+1
	U_KeyEnter_TmrContinueMax = 20, //5 //�ǳ����������µ��޷�Ӧ��ʱ�䡣 8*35ms=280ms, �޳������ܣ���������ʱ�ƶ��������
	
	// ����������̰���ͬ�İ�������ʱ�䰴�£�
	U_KeyEnter_TmrLongKey = 60, //28    //28*35ms=980ms
	
};
	
/*================= �ṹ�嶨�� ======================================*/

// ��Ӧ�ó����keyScan.c�ﶨ�塣
// �������Զ��壺
// ��ɨ����صİ����š����ܶ��壺
typedef struct TConstEveryKey_st{
	U8 have_long;     //1=��Ҫ������
	U8 KeySchId;      //ɨ��İ���˳��ź�ԭ��ͼ�Ķ�Ӧ��ϵ
	U8 NeedPassWord;  // emUserGrade
	U8 KeyNumber;     // emKey
}TConstEveryKey;

/*================= ���к������� phIoKeyBufJudge �� =================*/
// EX_phIoKeyScan

// ɨ�谴���ĸ�����
extern U8 GetScanKeyNum(void);

// TConstEveryKey �Ķ���
extern BOOL GetConstEveryKey(U8 mScanKey, TConstEveryKey **pEveryKey);

// ��ȡ�������ɨ�� 1 cycle ���
extern BOOL GetKeyScanBuf(U32 *pRtnScanValue);

//��������ʱ�䡣��ʱ���Զ�clr.
extern void TmrStart_KeySave(void);
extern void TmrStop_KeySave(void);
extern void TmrJudge_KeySave(void);

/*================= ���к������� phIoKeyBufJudge �� =================*/
// EX_lcdSub_Pssw

// ���� ��Ҫ�ж�userGrade
extern void Pssw_KeyNeedPssw(U8 mKeyValue, U8 needUserGrade);

/******************************************************************************
// END :
******************************************************************************/
#endif // __keyBufJdgLib_Inc_Extern_H__

