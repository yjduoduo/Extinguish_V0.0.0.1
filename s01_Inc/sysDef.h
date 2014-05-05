#ifndef __sysDef_H__
#define __sysDef_H__
/******************************************************************************
* @file    sysDef.h
* @author  yx
* @version V1.1
* @date    2013-10-24
* @brief   Ӧ�ò��á�Use in ".c"
* 
* V1.1, 2013-10-24
* 		U_PANEL_TOTAL_SEQU_MAX: 128->250
* V1.0, 2012-01-05
*
#include  "sysDef.h"
******************************************************************************/

#include  "prjCompileCon.h"
#include  "prjBool.h"
/*================= extern ============================================*/
#ifdef  __sysDef_C__
#define EX_sysDef
#else
#define EX_sysDef extern 
#endif
/*================= ���� ============================================*/


/*================= taskID ====================================*/
enum emSysTask{   // U8 taskId;
	U_SysTask_LcdShow = 1,
	U_SysTask_History = 2,
	U_SysTask_Uart_DownLoad = 3,
	U_SysTask_FlsSave = 4,
	U_SysTask_FlsVerify = 5,
	
	
	U_SysTask_Led_ID,
	U_SysTask_Key_ID,
	U_SysTask_Sound_ID,
	U_SysTask_HdFlashNor0_ID,
	U_SysTask_HdFlashNorU7_ID = U_SysTask_HdFlashNor0_ID,
	U_SysTask_HdFlashNor1_ID,
	U_SysTask_HdFlashNorU8_ID = U_SysTask_HdFlashNor1_ID,
	U_SysTask_HdFlashNand_ID,
	U_SysTask_iCan_ID,
	U_SysTask_eCan_ID,
	U_SysTask_RealTime_ID,
	U_SysTask_Timer_ID,
	U_SysTask_PwrChkSwc_ID,
	U_SysTask_PwrState_ID,
	U_SysTask_WatchDog_ID,
	
	
	
};
#define U_SYS_TASK_ID_MAX   26
#define U_SYS_TASK_ID_Invalid   0xFF

/*================= ���� ============================================*/
/*================= ������ԪID ======================================*/

#define U_UNIT_OPERATOR	0x0 //��ʾ��Ԫ�ĵ�Ԫid
#define U_MACHINE_SELF		0x80 //������־
#define U_MACHINE_MAX		0x30 //

#define U_MACHINE_MASTER	0 //����
#define U_MACHINE_SLAVE		1 //�ӻ�


#define U_PANEL_TOTAL_SEQU_MAX      250

/*================= TASK ID =========================================*/

#define U_SOFT_TASK_UNIT_VERFIRY_ID 	0x00 //����Ԫflash�洢У�顣
#define U_SOFT_TASK_FLASH_VERFIRY_ID 	0x01 //����ԪflashУ�顣
#define U_SOFT_TASK_ID_MAX 			0xFF //

/*================= ���ֿ���ص� ====================================*/
//

#define U_CHARPIX_DISP_HalfLeft		0 //һ��������Ҫ�������Ұ���ʾ
#define U_CHARPIX_DISP_HalfRight	1 //
#define U_CHARPIX_DISP_Half_MAX		2

/*================= ��Һ����ص� ====================================*/

#define U_CHAR_IS_EN		0  //�ַ� EN 
#define U_CHAR_IS_CN			1  //���� CN

/*=================  ======================================*/

enum emUserGrade{  // U8 userGrade;
	
	U_UserGrd_INVALID	= 0x0,
	U_UserGrd_Min  	= 0x10,    //����Ȩ�����
	U_UserGrd_0    	= 0x10,    //ֻ�ܲ�������
	U_UserGrd_1    	= 0x11,    //
	U_UserGrd_2    	= 0x12,    //
	U_UserGrd_3    	= 0x13,    //
	U_UserGrd_Max  	= 0x14,    //����Ȩ�����
	U_UserGrd_GUEST   = U_UserGrd_0,    //
	U_UserGrd_SUPER   = U_UserGrd_3,    //
};

enum emLanguage{
	U_Chinese_LANGUAGE,
	U_English_LANGUAGE,
	U_Complex_LANGUAGE, //���� cmpl
	U_Language_MAX,
};

/*================= ���к������� ====================================*/
// EX_sysDef 
extern U8 Get_TmrId_100msLow(void);
extern U8 Get_TmrId_1sLow(void);

extern U8 GetSysTaskId_FlsVerify(void);

/*================= ���к������� ====================================*/
// EX_sysDef 
extern void InitAll_MyHdHaveIniSign(void);
extern void SetMyHdHaveIniSign(U8 mTaskId);
extern void ClrMyHdHaveIniSign(U8 mTaskId);
extern BOOL bMyHdHaveIniSign(U8 mTaskId);
/*================= ��Ԫ��������====================================*/
extern BOOL bMachineIdIsMe(U8 mMachine);
extern U8 GetMachineMaster(void);
extern U8 GetLanguageChinese(void);

extern U8 GetMachineMax(void);
extern BOOL bMachineValid(U8 mMachine);
extern U8 GetPanelTotalSequMax(void);
extern BOOL bPanelTotalSequValid(U8 mPnSequ);

/*=================  ====================================*/
// �Ƿ� ��ǰ���û��������Ȩ��
// *  OUT: TRUE=���㡣
extern BOOL bUserGradeOk(U8 nowGrade, U8 mNeedGrade);

/******************************************************************************
// END :
******************************************************************************/
#endif // __sysDef_H__
