#ifndef __meBoard_H__
#define __meBoard_H__
/******************************************************************************
* @file    meBoard.h
* @author  yx
* @version V1.2
* @date    2013.10.24
* @brief   ����Ӳ�����������
* 
* V1.2�� 2013.10.24
*		ȥ�� GetBoardICanStartAddr(); �޸� GetBoardICanAddr();  
*		�޸ģ�GetBoardMax(); GetCanBoardSign();   GetCanApSign(); 
* V1.1  ���Ӻ�����GetBoardICanStartAddr()�ȣ�2013-8-21
* V1.0  2012-01-05
*
#include  "meBoard.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

#include  "sysPanel.h"
/*================= extern ============================================*/
#ifdef  __meBoard_C__
#define EX_meBoard
#else
#define EX_meBoard extern 
#endif
/*================= ���� ============================================*/

/*================= CPU ���ң���Ʒϵ�� ============================================*/

#define cBoardCpu_Company_Serial_LPC_1777   0 

/*================= ϵͳ Э�� �汾 ============================================*/
//ϵͳ�汾��
#define  cCanProt_11S  0               //CAN Э����� 11S
#define  cCanProtCur  cCanProt_11S     //CAN Э�����


/*================= ���к������� ====================================*/

extern U8 GetBoardICanAddr(void);

// MAX = ���������+1��
extern U8 GetBoardMax(void);
extern U8 GetCanBoardSign(void);
extern U8 GetCanApSign(void);

/*================= ���к������� ====================================*/
// ��Ӳ���汾��
EX_meBoard   uint8 GetBoardVersion_Hard(void);
EX_meBoard   uint8 GetBoardVersion_Soft(void);
EX_meBoard   uint8 GetBoardVersion_DebugSoft(void);
EX_meBoard   uint8 GetBoardVersion_TempSoft(void);


/******************************************************************************
// END :
******************************************************************************/
#endif // __meBoard_H__

