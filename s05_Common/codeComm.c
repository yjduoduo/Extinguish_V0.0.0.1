#define __codeComm_C__
/******************************************************************************
* @file    codeComm.c
* @author  yx
* @version V1.1
* @date    2013-09-05
* @brief   
* 
******************************************************************************/
#include  "codeComm.h"

#include  "prjBool.h"
// #include "incFile.h"	

/*================= 常数 ============================================*/

/*=================  ================================================*/
/******************************************************************************
* NAME: 
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

#ifdef U_SYS_Test_codCommon
#if    U_SYS_Test_codCommon == 1 

U32 test_mCodCommon;

void Test_codCommon(void)
{
	
	
}

#endif // U_SYS_Test_codCommon
#endif // U_SYS_Test_codCommon
/******************************************************************************
* NAME: 
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
U8 LogicInverse(U8 bSign)
{
	if(bSign == TRUE)
		return FALSE;
	else
		return TRUE; 
}


/******************************************************************************
* NAME: 
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
U8 CacuMaskBits(U8 mFromBit, U8 bits)
{
U8 ii;
U8 mask = 0;

	if((8-mFromBit) < bits)
	{
		bits = (8-mFromBit);
	}
	
	for(ii=0; ii<bits; ii++)
	{
		mask |= (1 << mFromBit);
		mFromBit++;
	}
	return mask;
}


/******************************************************************************
* FUNC: //
*   IN:
*  OUT:
******************************************************************************/
void ExchangeU8(U8 *p1, U8 *p2)
{
	U8 temp;
	temp = *p1;
	*p1 = *p2;
	*p2 = temp;
}

/******************************************************************************
* FUNC: // copy bytes
* U_SIGN_bHaveTested; 2013-07-04
******************************************************************************/
void CopyNByte(U8 *pFrom, U8 *pTo, U32 byteTotal)
{
U32 byteNum;
	
	for(byteNum=0; byteNum<byteTotal; byteNum++)
	{
		*pTo++ = *pFrom++;
	}
}

/******************************************************************************
* FUNC: // 比较bytes
* U_SIGN_bHaveTested; 2013-07-04
******************************************************************************/
BOOL bCompareByte(U8 *pFrom, U8 *pTo, U32 byteTotal)
{
U32 byteNum;
	
	for(byteNum=0; byteNum<byteTotal; byteNum++)
	{
		if((*pFrom++) != (*pTo++))
		{
			return FALSE;
		}
	}
	return TRUE;
}
/*

	for(ii=0; ii<0x10; ii++)
	{
		test_mCod1[ii] = ii+1;
		test_mCod2[ii] = ii+1;
	}
	bTestCod = bCompareByte(&test_mCod1[0], &test_mCod2[0], 0x10);
	
	for(ii=0; ii<0x10; ii++)
	{
		test_mCod1[ii] = ii+1;
		test_mCod2[ii] = ii+1;
	}
	test_mCod2[0] = ~0;
	bTestCod = bCompareByte(&test_mCod1[0], &test_mCod2[0], 0x10);
	
	for(ii=0; ii<0x10; ii++)
	{
		test_mCod1[ii] = ii+1;
		test_mCod2[ii] = ii+1;
	}
	test_mCod2[0x0F] = ~0;
	bTestCod = bCompareByte(&test_mCod1[0], &test_mCod2[0], 0x10);


*/

/******************************************************************************
* NAME: 
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
void ClrRamIsFF(U8 *pByte, U32 byteMax)
{
U32 byteNum;

	for(byteNum=0; byteNum<byteMax; byteNum++)
	{
		*pByte++ = 0xFF;
	}	
}

void ClrRamIs00(U8 *pByte, U32 byteMax)
{
U32 byteNum;

	for(byteNum=0; byteNum<byteMax; byteNum++)
	{
		*pByte++ = 0x0;
	}	
}

BOOL bAllRamIsFF(U8 *pByte, U32 byteMax)
{
U32 byteNum;

	for(byteNum=0; byteNum<byteMax; byteNum++)
	{
		if(*pByte++ != 0xFF)
		{
			return FALSE;
		}
	}
	return TRUE;
}

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
* U_SIGN_bHaveTested; 2013-07-02
******************************************************************************/
U32 AdrAllign4ToHigh(U32 mAdr)
{
	return ((mAdr + 3) & (~(3)));
}

U32 AdrAllign4ToLow(U32 mAdr)
{
	return (mAdr & (~(3)));
}

/*
	2013-07-02

	test_mCodCommon = AdrAllign4ToHigh(0); //0
	test_mCodCommon = AdrAllign4ToHigh(4); //4
	test_mCodCommon = AdrAllign4ToHigh(5); //8
	test_mCodCommon = AdrAllign4ToHigh(7); //8
	test_mCodCommon = AdrAllign4ToHigh(8); //8
	test_mCodCommon = AdrAllign4ToHigh(0xFFFFFFFB); //0xFFFFFFFC
	test_mCodCommon = AdrAllign4ToHigh(0xFFFFFFFC); //0xFFFFFFFC
	test_mCodCommon = AdrAllign4ToHigh(0xFFFFFFFD); //0x0
	test_mCodCommon = AdrAllign4ToHigh(0xFFFFFFFE); //0x0
	test_mCodCommon = AdrAllign4ToHigh(0xFFFFFFFF); //0x0
	test_mCodCommon = AdrAllign4ToHigh(~0); //0x0
	
	test_mCodCommon = AdrAllign4ToHigh(0); //0x0
	//
	
	test_mCodCommon = AdrAllign4ToLow(0); //0
	test_mCodCommon = AdrAllign4ToLow(1); //0
	test_mCodCommon = AdrAllign4ToLow(2); //0
	test_mCodCommon = AdrAllign4ToLow(3); //0
	test_mCodCommon = AdrAllign4ToLow(4); //4
	test_mCodCommon = AdrAllign4ToLow(0xFFFFFFFB); // ..F8
	test_mCodCommon = AdrAllign4ToLow(0xFFFFFFFC); // ..FC
	test_mCodCommon = AdrAllign4ToLow(0xFFFFFFFD); // ..FC
	test_mCodCommon = AdrAllign4ToLow(0xFFFFFFFE); // ..FC
	test_mCodCommon = AdrAllign4ToLow(0xFFFFFFFF); // ..FC
*/

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
* U_SIGN_bHaveTested; 2013-07-04
******************************************************************************/

U32 AdrAllignArea_ToHigh(U32 mAdr, U32 mAreaByteMax) // ->nextArea
{
	return AdrAllignArea_ToLow(mAdr + mAreaByteMax, mAreaByteMax);
	
	// 在输入0x5000,0x1000 时输出 0x5000, error.
	// U32 mask = mAreaByteMax - 1;
	// return ((mAdr + mask) & (~(mask)));
}

U32 AdrAllignArea_ToLow(U32 mAdr, U32 mAreaByteMax)
{
	U32 mask = mAreaByteMax - 1;
	return (mAdr & (~(mask)));
}

/*

	//2013-07-04
	test_mCodCommon = AdrAllignArea_ToHigh(0x4FFF, 0x1000); // 0x5000
	test_mCodCommon = AdrAllignArea_ToHigh(0x5000, 0x1000); // 0x6000 
	test_mCodCommon = AdrAllignArea_ToHigh(0x5001, 0x1000); // 0x6000
	test_mCodCommon = AdrAllignArea_ToLow(0x4FFF, 0x1000); // 0x4000
	test_mCodCommon = AdrAllignArea_ToLow(0x5000, 0x1000); // 0x5000
	test_mCodCommon = AdrAllignArea_ToLow(0x5001, 0x1000); // 0x5000

*/

/******************************************************************************
* FUNC: //
*   IN:
*  OUT:  0x100 -> 0xFFFFFF00 
******************************************************************************/
U32 GetAdrMask(U32 oneItemMax_HexOneBit1)
{
	return ~(oneItemMax_HexOneBit1-1);
}

/******************************************************************************
* FUNC: //
*   IN: 
*  OUT: 0x08 -> 3
* U_SIGN_bHaveTested; 2013-07-04
******************************************************************************/

U32 GetLowBit1_RShift(U32 mNum)
{
U32 shiftNum;

	if(mNum == 0)
	{
		return 0;
	}
	for(shiftNum=0; shiftNum<32; shiftNum++)
	{
		if(mNum & 1)
		{
			return shiftNum;
		}
		mNum >>= 1;
	}
	return 32;
}

/*

	test_mCodCommon = GetLowBit1_RShift(0); // 0
	test_mCodCommon = GetLowBit1_RShift(1); // 0
	test_mCodCommon = GetLowBit1_RShift(2); // 1
	test_mCodCommon = GetLowBit1_RShift(0x1000); //0x0C
	test_mCodCommon = GetLowBit1_RShift(0x1010); //0x04

*/
		
/******************************************************************************
* FUNC: //
*   IN:
*  OUT:
******************************************************************************/
void FoscDelayXXus (U32 delayUs)
{
U32 delayTemp;

	for(delayTemp=2*delayUs; delayTemp!=0; delayTemp--);
}

void FoscDelayXXms (U32 delayMs)
{
U32 delayTemp;

	if(delayMs > 1000)
	{
		delayMs = 1000;
	}
	for(delayTemp=2*delayMs*1000; delayTemp!=0; delayTemp--);
}

/******************************************************************************
* FUNC: //延时。为防止扫描任务不能及时执行，集中在此处理。
*   IN:
*  OUT:
******************************************************************************/
void FoscDelay15msForEe () //EE需要延时最少15ms
{
U32 delay1msNum;

	for(delay1msNum=0; delay1msNum<15; delay1msNum++)
	{
		FoscDelayXXms(1);
	}
}

void FoscDelay10usForSPI1Byte () //用SPI写1Byte后，等待数据实际发出
{
U32 delayTemp;

	for(delayTemp=5; delayTemp!=0; delayTemp--);
}



/******************************************************************************
* NAME: 
* FUNC: // END
*   IN:
*  OUT: 
******************************************************************************/
