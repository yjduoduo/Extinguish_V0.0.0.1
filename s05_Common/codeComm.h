#ifndef __codeComm_H__
#define __codeComm_H__
/******************************************************************************
* @file    codeComm.h
* @author  yx
* @version V1.1
* @date    2013-09-05
* @brief   
	   
* V1.1, 2013-09-05
* 		add 	   CacuMaskBits();
		去掉 hex 和 bcd 转换 -> codeFig.c ;
* V1.0, 2012-01-05
* 
#include  "codeComm.h"
******************************************************************************/

#include  "prjCompileCon.h"

/*================= extern ============================================*/
#ifdef  __codeComm_C__
#define EX_codeComm
#else
#define EX_codeComm extern 
#endif

/*================= 常数 ============================================*/
//#define 
/*================= 结构体定义 ======================================*/

/*================= 公有结构变量声明 ================================*/

/*=================  ====================================*/

#if U_SYS_Test_codCommon == 1 

EX_codeComm void Test_codCommon(void);

#endif // U_SYS_Test_codCommon

/*================= 公有函数声明 ====================================*/
//EX_codeComm 
		
							  
EX_codeComm void FoscDelayXXus (U32 delayUs);
EX_codeComm void FoscDelayXXms (U32 delayMs);
EX_codeComm void FoscDelay15msForEe (void); //EE需要延时最少15ms
EX_codeComm void FoscDelay10usForSPI1Byte (void); //用SPI写1Byte后，等待数据实际发出


/*================= 公有函数声明 ====================================*/

#define Max(_a, _b) 		(((_a) > (_b)) ? (_a) : (_b))
#define Min(_a, _b) 		(((_a) < (_b)) ? (_a) : (_b))
#define bInDomain(_a, _min, _max) 			(( ((_a)>=(_min)) && ((_a)<(_max)) ) ? (1) : (0))  //在区间内？
#define bBigger(_a, _other) 				((  (_a)> (_other)                 ) ? (1) : (0)) 
#define bItemIsValid(_nowItem,_itemMax) (((_nowItem)< (_itemMax)               ) ? (1) : (0))
  

/*================= 公有函数声明 ====================================*/
//EX_codeComm 
EX_codeComm U8 LogicInverse(U8 bSign);

EX_codeComm U8 CacuMaskBits(U8 mFromBit, U8 bits);



EX_codeComm void ExchangeU8(U8 *p1, U8 *p2);

EX_codeComm void CopyNByte(U8 *pFrom, U8 *pTo, U32 byteTotal); // copy bytes
EX_codeComm BOOL bCompareByte(U8 *pFrom, U8 *pTo, U32 byteTotal); // 比较bytes

EX_codeComm void ClrRamIs00(U8 *pByte, U32 byteMax); //全清00
EX_codeComm void ClrRamIsFF(U8 *pByte, U32 byteMax); //全清FF
EX_codeComm BOOL bAllRamIsFF(U8 *pByte, U32 byteMax);

EX_codeComm U32 GetAdrMask(U32 oneItemMax_HexOneBit1);
EX_codeComm U32 GetLowBit1_RShift(U32 mNum);

//Allign:
EX_codeComm U32 AdrAllign4ToHigh(U32 mAdr);
EX_codeComm U32 AdrAllign4ToLow(U32 mAdr);
EX_codeComm U32 AdrAllignArea_ToHigh(U32 mAdr, U32 mAreaByteMax); // ->nextArea
EX_codeComm U32 AdrAllignArea_ToLow(U32 mAdr, U32 mAreaByteMax);

/******************************************************************************
// END :
******************************************************************************/
#endif // __codeComm_H__
