#ifndef __codeFig_H__
#define __codeFig_H__
/******************************************************************************
* @file    codeFig.h
* @author  yx
* @version V1.0
* @date    2013-09-05
* @brief   ���� HEX��BCD��ת����
* 
// U_SIGN_bHaveTested	//�Ѿ����� 2013.9.6 10:11 , yx.
* 
#include  "codeFig.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

/*================= extern ============================================*/
#ifdef  __codeFig_C__
#define EX_codeFig
#else
#define EX_codeFig extern 
#endif
/*================= ���� ============================================*/
//#define 
/*================= �ṹ�嶨�� ======================================*/

/*================= ���нṹ�������� ================================*/


/*================= ˽�к������� ====================================*/
#ifdef  __codeFig_C__

// ����ʾǰ���0  &  !0  & �Ҷ��룬��' '��ǰ:
static void figToStr_dotShow0_AllignRight(
						U32 bcd, U8 bcdNum, U8 bitTotal);

// ����ʾǰ���0  &  !0  & ����룬��ʾ�Ķ�����Ч����:
static void figToStr_dotShow0_AllignLeft(U32 bcd, U8 bcdNum);

// ����ʾǰ���0  & bcd=0:
static U8 figToStr_dotShow0_bcd0(
					U32 bcd, U8 bitTotal, BOOL bAllignRight);

// ��ʾǰ���0. ��ʱ���뷽ʽ������
static void figToStr_Show0(U32 bcd, U8 bitTotal);


#endif  //__codeFig_C__

/*================= ���к������� ====================================*/
//EX_codeFig 
#ifdef U_SYS_Test_GeneralCode
#if    U_SYS_Test_GeneralCode == 1 

	void test_FigToStr(void);  // ����
#endif // U_SYS_Test_GeneralCode
#endif // U_SYS_Test_GeneralCode
/*================= ���к������� ====================================*/
//EX_codeFig 

// * FUNC: // Hex���� -> Bcd String .
// *  OUT: �ַ�����������'\0'
// charNum  = FigToString(fig, bitTotal,  b�Ҷ���, b��ʾ0, **pRtnStr);
extern U8 FigToString(U32 fig, U8 bitTotal, 
							BOOL bAllignRight, BOOL bShowPre0, 
							U8 **pRtnFigStr);

// * FUNC: // HEX to BCD:
// *  OUT:  ��Чbcd�ĸ���
extern U8 HexToBcdU32(U32 hexFigure, U32 *pRtnBcd);
// ���� bcd �ĸ�����
extern U8 HexToBcd_LimitBcdNum(U32 hexFigure, U8 bcdNumMax, 
										U32 *pRtnBcd);
extern U32 HexToBcd(U8 hexFigure);



extern U8 BcdToHexU8(U8 bcdFigure);
extern U32 BcdToHexU32(U32 bcdFigure);

extern void BcdDecToHex(U32 num,U8* str);


/******************************************************************************
// END :
******************************************************************************/
#endif // __codeFig_H__

