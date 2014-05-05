#ifndef __bufCircle_H__
#define __bufCircle_H__
/******************************************************************************
* @file    bufCircle.h
* @author  yx
* @version V1.2
* @date    2013.10.11
* @brief   
*
* V1.2 2013.10.11
* 	BufCircle_InDec();  BufCircle_OutDec(); �ж� bFull.
*	CircleSpaceBytes();  result= (... - 1)
*	CircleFillBytes(); 
* V1.1, 2013.7.26, yx;
*	add: BufCircle_InDec();  
* 
#include  "bufCircle.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

/*================= extern ============================================*/
#ifdef  __bufCircle_C__
#define EX_bufCircle
#else
#define EX_bufCircle extern 
#endif
/*================= ���� ============================================*/
//#define 
/*================= �ṹ�嶨�� ======================================*/

/*================= ���нṹ�������� ================================*/
typedef struct{
	U32 in;  //����invalid
	U32 out; //����valid
	U32 max;
	BOOL bFull;
}TBufCircle;

/*================= ���к������� ====================================*/
//EX_bufCircle 

EX_bufCircle void BufCircleIni(U32 max, TBufCircle *pBufCircle);
EX_bufCircle BOOL bFullBufCircle(TBufCircle *pBufCircle);
EX_bufCircle BOOL bEmptyBufCircle(TBufCircle *pBufCircle);

EX_bufCircle U32 BufCircle_GetIn(TBufCircle *pBufCircle); // in
EX_bufCircle void BufCircle_InInc(TBufCircle *pBufCircle);
EX_bufCircle void BufCircle_InDec(TBufCircle *pBufCircle);
EX_bufCircle U32 BufCircle_GetOut(TBufCircle *pBufCircle); //out
EX_bufCircle void BufCircle_OutInc(TBufCircle *pBufCircle);
EX_bufCircle void BufCircle_OutDec(TBufCircle *pBufCircle);

EX_bufCircle U32 CircleAdd(U32 now, U32 vary, U32 max);
EX_bufCircle U32 CircleSub(U32 now, U32 vary, U32 max);
EX_bufCircle U32 CircleDiffValue(U32 in, U32 out, U32 max);

EX_bufCircle BOOL BufCircle_In_Add(U32 vary, TBufCircle *pBufCircle);
EX_bufCircle BOOL BufCircle_Out_Add(U32 vary, TBufCircle *pBufCircle);

EX_bufCircle U32 CircleSpaceBytes(TBufCircle *pBufCircle); //������ֽ���
EX_bufCircle U32 CircleFillBytes(TBufCircle *pBufCircle);  // �Ѵ洢���ֽڸ���

EX_bufCircle void CircleCopyBytAllign4(U8 *pBufS, U8 *pCopySrc, U32 copyMax, TBufCircle *pBufCircle);
EX_bufCircle U32 CircleCopyByte(U8 *pBufS, U8 *pCopySrc, U32 copyMax, TBufCircle *pBufCircle);

EX_bufCircle void ByteCopyFromCircle(U8 *pBufS, U8 *pCopyDest, U32 copyMax, TBufCircle *pBufCircle);


/******************************************************************************
// END :
******************************************************************************/
#endif // __bufCircle_H__

