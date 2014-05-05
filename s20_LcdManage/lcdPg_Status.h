#ifndef __lcdPg_Status_H__
#define __lcdPg_Status_H__
/******************************************************************************
* @file    lcdPg_Status.h
* @author  yx
* @version V1.0
* @date    2013-07-01
* @brief   �Ƿ���ʾ״̬����
* 
#include  "lcdPg_Status.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

/*================= extern ============================================*/
#ifdef  __lcdPg_Status_C__
#define EX_lcdPg_Status
#else
#define EX_lcdPg_Status extern 
#endif
/*================= ���� ============================================*/

typedef enum {
	
	//��ǰ��ʾ�� ״̬��. ��Щҳ����"��·���"���ܲ���ʾWinState.
	U_WIN_ShowState_Sta,
		
	//SubPg.first()ʱ, set(U_WIN_PageSubIng_Sta)״̬��
	//SubPg.back()ʱ�������ص��˵���
	// 	clr(U_WIN_PageSubIng_Sta)״̬ 
	//	+ set parent PageNum 
	//	+ parent.first()��
	U_WIN_PageSubIng_Sta,	
	
	//ҳ���Ǵ�menu����ġ�����ڴ�ҳ��ֱ�ӽ��롣
	// page.returnʱ�����Ǵ�menu����ģ��˳���menuҳ�档
	U_WIN_EntryMenu_Sta,	
	
	// ���� * # ����������һ����������̡�
	// *#�� page δ�õ�������£����� return ���ܣ�
	// ��Ϊ�� key-return�������������ֵ������key-left�����ƶ���ꡣ
	// �������ã��û���ֻ�� key-eseѡ���ˡ�
	U_WIN_NeedKey_StarPound_Sta, 
	
	// ���� <-  ->���ڷ�ҳ
	U_WIN_KeyLR_UseforPageUpDown_Sta, 
	//
	U_WIN_BOOL_Sta_MAX,
	
}emWinBoolState;

	
/*================= �ṹ�嶨�� ======================================*/

/*================= ���нṹ�������� ================================*/

/*================= ˽�к������� ====================================*/
#ifdef  __lcdPg_Status_C__

	BOOL vWinBoolState[U_WIN_BOOL_Sta_MAX];

#endif  //__lcdPg_Status_C__
/*================= ���к������� ====================================*/
//EX_lcdPg_Status 

// ������ҳ���Լ�����İ�����
// �ڶ���key��������Ч����������Ҫҳ���Լ�������set.
// �� LcdPage_function_ ...() ������ clr.
extern void SetPageKey(U8 mKeyValue);
extern void ClrPageKey(void);
extern BOOL bGetPageKey(U8 *pRtnKey);

// ������ �ı���;�İ�����
void SetChangeFuncKey(U8 mKeyValue);
void ClrChangeFuncKey(void);
BOOL bGetChangeFuncKey_andClr(U8 *pRtnKey);

// ҳ�汾������ԡ�
// ���Լ��� first()��set, ��back()��clr.
extern void SetWinBoolState(emWinBoolState mState);
extern void ClrWinBoolState(emWinBoolState mState);
extern BOOL bWinBoolState(emWinBoolState mState);

// ����ʾ״̬�� //����subPage // ���Ǿ���menu�����page
extern void Ini_WinBoolState(void);

/******************************************************************************
// END :
******************************************************************************/
#endif // __lcdPg_Status_H__

