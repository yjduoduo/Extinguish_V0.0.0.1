#ifndef __prjCompileCon_H__
#define __prjCompileCon_H__
/******************************************************************************
* @file    prjCompileCon.h
* @author  yx
* @version V1.0
* @date    2012-01-05
* @brief   �������,���������е�.h��include.
* 
#include  "prjCompileCon.h"
******************************************************************************/
#include <assert.h>  //	ASSERT(1);  //����,���Ʊ���ʱ�ĺ����������������

#include  "prjDataType.h"
#include  "prjFosc.h"
#include  "prjBool.h"
/*================= ���� ============================================*/

//#define Pseudocode //α����
//#define Code No Finished  //��־δ��ɵĴ���
//#define conduct    //����

/******************************************************************************
// ϵͳ���� :
// �������� #ifdef ,��Ϊ���ļ�δ include me.h, ���岻������Ҳ��֪����
******************************************************************************/
#define U_Yes   1
#define U_YES   1
#define U_No    0
#define U_NO    0

/******************************************************************************
// �ֿ� :
******************************************************************************/
// yes = �ֿ���code��, cpu�״���¼Ӧ�����������
//  no = �ֿ�����code������ٱ����ֿ⡣
// #define U_Include_CharLib  U_NO  ȥ "hwEx11_lcd_Def_charLib.h" ����

// �ֿ����ѡ�� U_CharLib_NOW , �� "hwEx11_lcd_Def_charLib.h" ��
// �ֿ�ĵ����ֽ� �� "hwEx11_lcd_Def_charLib.h"
// ��ʾ�ַ��ĵ��� �� "hwEx11_lcd_Def_charLib.h"

/******************************************************************************
// ����� :
******************************************************************************/

#define U_SYS_SoftSimulatState     U_NO


#if U_SYS_SoftSimulatState == 1 
	#define U_SYS_ForbidHardWare  U_YES  //������ڼ��ֹӲ��	
#endif // U_SYS_SoftSimulatState

#if U_SYS_ForbidHardWare == U_Yes 
#else
#endif // U_SYS_ForbidHardWare

#if U_SYS_SoftSimulatState == 1 
#endif // U_SYS_SoftSimulatState


//----- ����״̬ ----------------------------------------------------------------

#define U_SYS_SoftTestState     1  //�ܿ��ء� // 1=�������״̬����ֻ������档

#if U_SYS_SoftTestState == 1 
	#define U_SYS_IdleBuf_setFF    0 //���õ�buf��FF, ����ʱ��������R.
	
	#define U_SYS_Test_GeneralCode   0
	#define U_SYS_Test_Menu    0
	#define U_SYS_Test_EvtBuf    0
	#define U_SYS_Test_strDevice    0
	#define U_SYS_Test_codCommon    0
	#define U_SYS_Test_Flash_SimTask    1
	#define U_SYS_Test_Flash_InqPoint    0
		#define U_SYS_Test_Flash_InqPoint_SimX    0
	#define U_SYS_Test_Flash_Hist    0
	#define U_SYS_Test_FlsApplyBuf    0
	#define U_SYS_Test_FlsAdrDef    0
	#define U_SYS_Test_CanBuf    0
	
	#define U_SYS_Test_Lcd    1
	#define U_SYS_Test_CanHw    1
	#define U_SYS_Test_UartHw    1
	
#endif // U_SYS_SoftSimulatState

//----- ������Ҫ���� -----------------------------------------------------------------

#define U_SYS_KeyNowNeedPassword   U_NO 


/******************************************************************************
// ����״̬��
******************************************************************************/
#define U_SYS_bShowPseudocode  0  //α����
#define U_SYS_bShowNoFinished  0  //��־δ��ɵĴ���
#define U_SYS_bShowConduct     0  //��Ҫ�ٴ���
// U_SIGN_bHaveTested			 //�Ѿ�����

#if U_SYS_bShowPseudocode == 1 
	//U_SYS_bShowPseudocode = 1;
#endif // U_SYS_bShowPseudocode

#if U_SYS_bShowNoFinished == 1 
	//U_SYS_bShowNoFinished = 1;
#endif // U_SYS_bShowNoFinished

#if U_SYS_bShowConduct == 1 
	//U_SYS_bShowConduct = 1;
#endif // U_SYS_bShowConduct


/******************************************************************************
// С��ģʽ��
******************************************************************************/
#define U_Sys_Big_Endian  1
#define U_Sys_Little_Endian  0
#define U_Sys_Endian  U_Sys_Little_Endian
//Big-Endian��Little-Endian

/******************************************************************************
// ���ԣ�
******************************************************************************/
#define myAssert(expr)    if(expr) {};// assert(expr)

/******************************************************************************
// ���� :
******************************************************************************/
#ifndef __CAN_BUF_LIB__
#define __CAN_BUF_LIB__
#endif 
/******************************************************************************
// END :
******************************************************************************/
#endif // __prjCompileCon_H__

