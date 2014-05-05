#ifndef __phIoKeyScan_H__
#define __phIoKeyScan_H__
/******************************************************************************
* @file    phIoKeyScan.h
* @author  yx
* @version V1.1
* @date    2013.8.21
* @brief   
* 
#include  "phIoKeyScan.h"
******************************************************************************/

#include  "prjCompileCon.h"
#include  "keyBufJdgLib_Inc_Extern.h"
/*================= extern ============================================*/
#ifdef  __phIoKeyScan_C__
#define EX_phIoKeyScan
#else
#define EX_phIoKeyScan extern 
#endif

/*================= ���� ============================================*/
// �û����ּ����ܼ��Ķ���:
typedef enum { 
	
	U_KEY_Fig_Max = 10,
		
	U_KEY_Star = 10,
	U_KEY_Pound, // # 	//11
	U_KEY_Auto, 
		
	U_KEY_Up,
	U_KEY_Down,
	U_KEY_Left,
	U_KEY_Right,
	U_KEY_Enter,
	
	U_KEY_Return, // 18
	U_KEY_Reset,
	U_KEY_Silence,
	
	U_KEY_MAX,  // < U_HD_KEY_BIT_MAX
	
	U_KEY_Esc = (U_KEY_BOARD_MAX + U_KEY_Return),
	
	// �� U_KEY_BOARD_MAX ��ʼ�����峤�����Ĺ��ܡ�
	// �޳������ܵģ���ַ���ܱ�ռ�á�
	
}emKey;
	
#define  bKeyValueValid(__mKeyVal__)   \
				((__mKeyVal__) < (U_KEY_FUNCTION_MAX))
	
	
/*================= ���� ============================================*/
// ��ɨ����صĶ��� �����



/*================= �ṹ�嶨�� ======================================*/



/*================= ˽�нṹ�������� ================================*/
#ifdef __phIoKeyScan_C__

void KeyNewScanResult(U32 scanBits); //ɨ����

#endif // __phIoKeyScan_C__

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


/*================= ���к������� ====================================*/
// EX_phIoKeyScan

extern void InitKeyScanTask(void);


extern BOOL bNeedKeySound(void);

// �ж�����߱�֤һ��ʱ����һ��ִ��һ��
extern void Key_Read_And_ScanOut(void);

/******************************************************************************
// END :
******************************************************************************/
#endif // __phIoKeyScan_H__

