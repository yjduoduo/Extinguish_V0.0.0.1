#define __codeFig_C__
/******************************************************************************
* @file    codeFig.c
* @author  yx
* @version V1.0
* @date    2013-09-05
* @brief   数字 HEX和BCD的转换。
* 
// U_SIGN_bHaveTested	//已经测试 2013.9.6 10:11 , yx.
******************************************************************************/
#include  "codeFig.h"




/*================= 常数 ============================================*/
#define U_BCD_8_Max  (100*100*100*100)
#define U_BCD_7_Max  (100*100*100*10)
#define U_BCD_6_Max  (100*100*100)
#define U_BCD_5_Max  (100*100*10)
#define U_BCD_4_Max  (100*100)
#define U_BCD_3_Max  (100*10)
#define U_BCD_2_Max  (100)
#define U_BCD_1_Max  (10)
#define U_BCD_0_Max  (1)

const U32 figBcdMaxLimitBit[32/4+1] =
{
//   0,  1,   2,    3,               
	U_BCD_0_Max, U_BCD_1_Max, U_BCD_2_Max, U_BCD_3_Max, 
	U_BCD_4_Max, U_BCD_5_Max, U_BCD_6_Max, U_BCD_7_Max,               
	U_BCD_8_Max
};

/*================= 结构定义 ========================================*/

/*================= 私有结构变量声明 ================================*/

#define U_LcdSw_FigBuf_MAX  0x0A
static U8 vFigBytes;
static U8 vFigBuf[U_LcdSw_FigBuf_MAX]; // U32 共8个数字

#ifdef U_SYS_SoftTestState
#if    U_SYS_SoftTestState == 1 
U8 vTestCharNum;  // 应该 == vFigBytes。
U32 vTestBcd;
U8 vTestBcdNum;
U32 vTestLimitBitBcd;
U8 vTestLimitBitBcdNum;
#endif // U_SYS_SoftTestState
#endif // U_SYS_SoftTestState

/*================= 公有函数声明 ====================================*/

/*================= 私有函数声明 ====================================*/

/*=================  ================================================*/


/******************************************************************************
* FUNC: // Hex数字 -> Bcd String .
*   IN:
*  OUT: 字符数，不包括'\0'

// U_SIGN_bHaveTested	//已经测试 2013.9.6 10:11 , yx.  test_FigToStr();
******************************************************************************/

U8 FigToString(U32 fig, U8 bitTotal, BOOL bAllignRight, BOOL bShowPre0, 
							U8 **pRtnFigStr)
{
U32 bcd;
U32 bcdNum;
U8 charNum;
	
#ifdef U_SYS_SoftTestState
#if    U_SYS_SoftTestState == 1 
	for(charNum=0; charNum<U_LcdSw_FigBuf_MAX; charNum++)
	{
		vFigBuf[charNum] = ~0;
	}
#endif // U_SYS_SoftSimulatState
#endif // U_SYS_SoftTestState

	vFigBytes = 0;
	vFigBuf[U_LcdSw_FigBuf_MAX-1] = '\0';
	
	
	// if((bitTotal == 0) || (bitTotal > U_FIG_SHOW_BITS_MAX))
	// {
		// bitTotal = U_FIG_SHOW_BITS_MAX;
	// }
	if(bitTotal == 0)
	{
		bitTotal = (32/4);
	}
	bcdNum = HexToBcd_LimitBcdNum(fig, bitTotal, &bcd);
	
	
	if(bShowPre0) 
	{
		figToStr_Show0(bcd, bitTotal);
		charNum = bitTotal;
	}
	else //"不显示无效的0"
	{
		if(fig == 0)
		{
			// bcd=0 & 不显示前面的0:
			charNum = figToStr_dotShow0_bcd0(bcd, bitTotal, bAllignRight);
		}
		else //"不显示无效的0" + "fig != 0"
		{
			if(bAllignRight)
			{
				// 不显示前面的0  &  !0  & 右对齐，用' '补前:
				figToStr_dotShow0_AllignRight(bcd, bcdNum, bitTotal);
				charNum = bitTotal;
			}
			else
			{
				// 不显示前面的0  &  !0  & 左对齐，显示的都是有效数字:
				figToStr_dotShow0_AllignLeft(bcd, bcdNum);
				charNum = bcdNum;
			}
		}
	}
	
#ifdef U_SYS_SoftTestState
#if    U_SYS_SoftTestState == 1 
	vTestCharNum = charNum;
#endif // U_SYS_SoftTestState
#endif // U_SYS_SoftTestState
	
	*pRtnFigStr = &vFigBuf[0];
	return charNum;
	
}



/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
watch: 
// U_SIGN_bHaveTested	//已经测试 2013.9.6 10:11 , yx.
******************************************************************************/
#ifdef U_SYS_Test_GeneralCode
#if    U_SYS_Test_GeneralCode == 1 

void test_FigToStr(void)
{
U8 charNum;
U8 *pFigStr;
	
	//U8 FigToString(U32 fig, U8 bitTotal, 
	//						BOOL bAllignRight, BOOL bShowPre0, 
	//						U8 **pRtnFigStr);


	// 测试 只有1位：
	// 右对齐 &   显示0:  // bcd= 0 , 	num= 1; 
	//  1, ['0',0,FF];
	charNum = FigToString(10, 1, FALSE, FALSE, &pFigStr);
	// 右对齐 & 不显示0:  // bcd=  , 	num= ; 
	//  , ['',0,FF]; 同上
	charNum = FigToString(10, 1, FALSE, FALSE, &pFigStr);
	// 左对齐 &   显示0:  // bcd=  , 	num= ; 
	//  , ['',0,FF]; 同上
	charNum = FigToString(10, 1, FALSE, FALSE, &pFigStr);
	// 左对齐 & 不显示0:  // bcd=  , 	num= ; 
	//  , ['',0,FF]; 同上
	charNum = FigToString(10, 1, FALSE, FALSE, &pFigStr);
	
	
	
	// 测试 只有1位：
	// 右对齐 &   显示0:  // bcd= 5 , 	num= 1; 
	//  1, ['5',0,FF];
	charNum = FigToString(5, 1, FALSE, FALSE, &pFigStr);
	// 右对齐 & 不显示0:  // bcd=  , 	num= ; 
	//  , ['',0,FF];
	charNum = FigToString(5, 1, FALSE, FALSE, &pFigStr);
	// 左对齐 &   显示0:  // bcd=  , 	num= ; 
	//  , ['',0,FF];
	charNum = FigToString(5, 1, FALSE, FALSE, &pFigStr);
	// 左对齐 & 不显示0:  // bcd=  , 	num= ; 
	//  , ['',0,FF];
	charNum = FigToString(5, 1, FALSE, FALSE, &pFigStr);
	
	





	// 大于显示位数: 	// bcd=0x10000001, 	num=8; 
	// 8, ['10000001',0,0];
	charNum = FigToString(110000001, 8, TRUE,  TRUE,  &pFigStr);
	// 大于显示位数:		// bcd= , 	num= ; 
	//  , [同上 ];
	charNum = FigToString(110000001, 8, TRUE,  FALSE,  &pFigStr);
	// 大于显示位数:		// bcd=  , 	num= ; 
	//  , [同上 ];
	charNum = FigToString(110000001, 8, FALSE,  FALSE,  &pFigStr);
	
	
	// 最多位数:		// bcd=10000001, 	num=8;  
	// 8, ['10000001',0,0]; 同上
	charNum = FigToString(10000001, 8, TRUE,  TRUE,  &pFigStr);

	
	
	// 7位数:		// bcd=01234567  , 	num= 7; 
	//  8, ['01234567',0,0];
	charNum = FigToString(1234567, 8, TRUE,  TRUE,  &pFigStr);
	// 7位数:		// bcd=01234567  , 	num= 7; 
	//  8, [' 1234567',0,0];
	charNum = FigToString(1234567, 8, TRUE,  FALSE,  &pFigStr);
	// 7位数:		// bcd=01234567  , 	num= 7; 
	//  7, ['1234567',0,FF,0];
	charNum = FigToString(1234567, 8, FALSE,  FALSE,  &pFigStr);
	
	
	
	
	// :	// bcd=0x01  , 	num= 1; 
	//  4, ['0001',0,FF];
	charNum = FigToString(10001, 4, TRUE,  TRUE,  &pFigStr);
	// :	// bcd=0x09999  , 	num= 4; 
	//  4, ['9999',0,FF];
	charNum = FigToString(999999, 4, TRUE,  TRUE,  &pFigStr);
	
	
	// 右对齐 &   显示0: // bcd=0x09999  , 	num= 4; 
	//  4, ['9999',0,FF];
	charNum = FigToString(9999, 4, TRUE,  TRUE,  &pFigStr);
	// 右对齐 & 不显示0: // bcd=0x09999  , 	num= 4;
	//  4, ['9999',0,FF];
	charNum = FigToString(9999, 4, TRUE,  FALSE, &pFigStr);
	// 左对齐 &   显示0: // bcd=0x09999  , 	num= 4;
	//  4, ['9999',0,FF];
	charNum = FigToString(9999, 4, FALSE, TRUE,  &pFigStr);
	// 左对齐 & 不显示0: // bcd=0x09999  , 	num= 4;
	//  4, ['9999',0,FF];
	charNum = FigToString(9999, 4, FALSE, FALSE, &pFigStr);

	

	// 右对齐 &   显示0:  // bcd= 0x0100 , 	num= 3; 
	//  4, ['0100',0,FF];
	charNum = FigToString(100, 4, TRUE,  TRUE,  &pFigStr);
	// 右对齐 & 不显示0:  // bcd=  , 	num= ; 
	//  4, [' 100',0,FF];
	charNum = FigToString(100, 4, TRUE,  FALSE, &pFigStr);
	// 左对齐 &   显示0:  // bcd=  , 	num= ; 
	//  4, ['0100',0,FF];
	charNum = FigToString(100, 4, FALSE, TRUE,  &pFigStr);
	// 左对齐 & 不显示0:  // bcd= 0x010 , 	num= 2; 
	//  2, ['10',0,FF];
	charNum = FigToString(10, 4, FALSE, FALSE, &pFigStr);
	
	

	// 右对齐 &   显示0:  // bcd= 1 , 	num= 1; 
	//  4, ['0001',0,FF];
	charNum = FigToString(1, 4, TRUE,  TRUE,  &pFigStr);
	// 右对齐 & 不显示0:  // bcd= 1 , 	num= 1; 
	//  4, ['   1',0,FF];
	charNum = FigToString(1, 4, TRUE,  FALSE, &pFigStr);
	// 左对齐 &   显示0:  // bcd= 1 , 	num= 1; 
	//  4, ['0001',0,FF];
	charNum = FigToString(1, 4, FALSE, TRUE,  &pFigStr);
	// 左对齐 & 不显示0:  // bcd= 1 , 	num= 1; 
	//  1, ['1',0,FF];
	charNum = FigToString(1, 4, FALSE, FALSE, &pFigStr);

	// 测试 fig 0 的情况：
	// 右对齐 &   显示0:  // bcd= 0 , 	num= 1; 
	//  4, ['0000',0,FF];
	charNum = FigToString(0, 4, TRUE,  TRUE,  &pFigStr);
	// 右对齐 & 不显示0:  // bcd= 0 , 	num= 1; 
	//  4, ['   0',0,FF];
	charNum = FigToString(0, 4, TRUE,  FALSE, &pFigStr);
	// 左对齐 &   显示0:  // bcd= 0 , 	num= 1; 
	//  4, ['0000',0,FF];
	charNum = FigToString(0, 4, FALSE, TRUE,  &pFigStr);
	// 左对齐 & 不显示0:  // bcd= 0 , 	num= 1; 
	//  1, ['0',0,FF];
	charNum = FigToString(0, 4, FALSE, FALSE, &pFigStr);
	
	// END:
	charNum = FigToString(0, 4, TRUE,  TRUE,  &pFigStr);
	charNum = charNum;
}


#endif // U_SYS_Test_GeneralCode
#endif // U_SYS_Test_GeneralCode

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
// U_SIGN_bHaveTested	//已经测试 2013.9.6 10:11 , yx.
******************************************************************************/

// 不显示前面的0  &  !0  & 右对齐，用' '补前:
static void figToStr_dotShow0_AllignRight(
							U32 bcd, U8 bcdNum, U8 bitTotal)
{
U8 ii;
	
	if(bcdNum == bitTotal)
	{
		// 不显示前面的0  &  !0  & 左对齐，显示的都是有效数字:
		figToStr_dotShow0_AllignLeft(bcd, bcdNum);
		return;
	}
	
	for(ii=bitTotal; ii>bcdNum; ii--)
	{
		vFigBuf[vFigBytes] = ' ';
		vFigBytes++;
	}
	figToStr_dotShow0_AllignLeft(bcd, bcdNum);
}


/******************************************************************************
* FUNC: //
// U_SIGN_bHaveTested	//已经测试 2013.9.6 10:11 , yx.
******************************************************************************/
// 不显示前面的0  &  !0  & 左对齐，显示的都是有效数字:
static void figToStr_dotShow0_AllignLeft(U32 bcd, U8 bcdNum)
{
U8 ii;
U8 nowFig;

	for(ii=bcdNum; ii!=0; ii--)
	{
		nowFig = (bcd >> ((ii-1)*4)) & 0x0F;
		vFigBuf[vFigBytes] = nowFig +  '0';
		vFigBytes++;
	}
	vFigBuf[vFigBytes] = '\0';
}


/******************************************************************************
* FUNC: //
// U_SIGN_bHaveTested	//已经测试 2013.9.6 10:11 , yx.
******************************************************************************/
// 不显示前面的0  & bcd=0:
static U8 figToStr_dotShow0_bcd0(
					U32 bcd, U8 bitTotal, BOOL bAllignRight)
{

	if(bAllignRight)  // 右对齐：
	{
		for(vFigBytes=0; vFigBytes<bitTotal; vFigBytes++)
		{
			vFigBuf[vFigBytes] = ' ';
		}
		vFigBuf[bitTotal-1] = '0';
		vFigBuf[bitTotal] = '\0';
		return bitTotal;
	}
	else
	{
		vFigBuf[0] = '0';
		vFigBuf[1] = '\0';
		vFigBytes = 1;
		return 1;
	}
}

/******************************************************************************
* FUNC: //
// U_SIGN_bHaveTested	//已经测试 2013.9.6 10:11 , yx.
******************************************************************************/
// 显示前面的0. 此时对齐方式无意义
static void figToStr_Show0(U32 bcd, U8 bitTotal)
{
U32 shiftBits;
		
	for(vFigBytes=0; vFigBytes<bitTotal;vFigBytes++)
	{
		shiftBits = ((bitTotal - vFigBytes - 1)*4);
		vFigBuf[vFigBytes] = (((bcd >> shiftBits) & 0x0F) + ('0'));
	}
	vFigBuf[vFigBytes] = '\0'; 
}



/******************************************************************************
* NAME: 
* FUNC: //
*   IN:
*  OUT:  有效bcd的个数

// U_SIGN_bHaveTested	//已经测试 2013.9.6 10:11 , yx.
******************************************************************************/

U8 HexToBcdU32(U32 hexFigure, U32 *pRtnBcd)
{
U32 bcd = 0;
U8 bcdNum = 0;

	if(hexFigure >= U_BCD_8_Max)
	{
		hexFigure = (hexFigure% U_BCD_8_Max);
	}
	
	if(hexFigure >= U_BCD_7_Max)
	{
		bcd |= ((hexFigure / U_BCD_7_Max) << (4*7));
		hexFigure %= (U_BCD_7_Max);
		if(bcdNum == 0)
		{
			bcdNum = 8;
		}
	}
	if(hexFigure >= U_BCD_6_Max)
	{
		bcd |= ((hexFigure / U_BCD_6_Max) << (4*6));
		hexFigure %= U_BCD_6_Max;
		if(bcdNum == 0)
		{
			bcdNum = 7;
		}
	}	
	if(hexFigure >= U_BCD_5_Max)
	{
		bcd |= ((hexFigure / U_BCD_5_Max) << (4*5));
		hexFigure %= U_BCD_5_Max;
		if(bcdNum == 0)
		{
			bcdNum = 6;
		}
	}
	if(hexFigure >= U_BCD_4_Max)
	{
		bcd |= ((hexFigure / U_BCD_4_Max) << (4*4));
		hexFigure %= U_BCD_4_Max;
		if(bcdNum == 0)
		{
			bcdNum = 5;
		}
	}
	if(hexFigure >= U_BCD_3_Max)
	{
		bcd |= ((hexFigure / U_BCD_3_Max) << (4*3));
		hexFigure %= U_BCD_3_Max;
		if(bcdNum == 0)
		{
			bcdNum = 4;
		}
	}
	if(hexFigure >= U_BCD_2_Max)
	{
		bcd |= ((hexFigure / U_BCD_2_Max) << (4*2));
		hexFigure %= U_BCD_2_Max;
		if(bcdNum == 0)
		{
			bcdNum = 3;
		}
	}
	if(hexFigure >= U_BCD_1_Max)
	{
		bcd |= ((hexFigure / U_BCD_1_Max) << (4*1));
		hexFigure %= U_BCD_1_Max;
		if(bcdNum == 0)
		{
			bcdNum = 2;
		}
	}
	bcd |= (hexFigure);
	if(bcdNum == 0)
	{
		bcdNum = 1;
	}
	
#ifdef U_SYS_SoftTestState
#if    U_SYS_SoftTestState == 1 
	vTestBcd = bcd;
	vTestBcdNum = bcdNum;
#endif // U_SYS_SoftTestState
#endif // U_SYS_SoftTestState
	
	*pRtnBcd = bcd;
	return bcdNum;
}



/******************************************************************************
* NAME: 
* FUNC: // 限制 bcd 的个数：
*   IN:
*  OUT:  有效bcd的个数

// U_SIGN_bHaveTested	//已经测试 2013.9.6 10:11 , yx.
******************************************************************************/

U8 HexToBcd_LimitBcdNum(U32 hexFigure, U8 bcdNumMax, U32 *pRtnBcd)
{
U8 bcdNum;
U32 bcd;
//U32 bcdMask;
//U8 maskNum;
	
	if(bcdNumMax > (32/4))
	{
		bcdNumMax = (32/4);
	}
	if(hexFigure >= figBcdMaxLimitBit[bcdNumMax])
	{
		hexFigure %= (figBcdMaxLimitBit[bcdNumMax]);
	}
	bcdNum = HexToBcdU32(hexFigure, &bcd);
	// if(bcdNum > bcdNumMax)
	// {
		// bcdMask = 0;
		// for(maskNum=0; maskNum<bcdNumMax; maskNum++)
		// {
			// bcdMask |= (0x0F << (maskNum*4));
		// }
		// bcd &= bcdMask;
		// bcdNum = bcdNumMax;
	// }
	
#ifdef U_SYS_SoftTestState
#if    U_SYS_SoftTestState == 1 
	vTestLimitBitBcd = bcd;
	vTestLimitBitBcdNum = bcdNum;
#endif // U_SYS_SoftTestState
#endif // U_SYS_SoftTestState
	
	*pRtnBcd = bcd;
	return bcdNum;
}


// * U_SIGN_bHaveTested; 2013-07-04, 
/*
U32 HexToBcdU32(U32 hexFigure)
{
	U32 bcd = 0;
	if(hexFigure >= 10000)
	{
		hexFigure = hexFigure%10000;
	}
	
	if(hexFigure >= 1000)
	{
		bcd |= (hexFigure / 1000) << (4*3);
		hexFigure %= 1000;
	}
	if(hexFigure >= 100)
	{
		bcd |= (hexFigure / 100) << (4*2);
		hexFigure %= 100;
	}
	if(hexFigure >= 10)
	{
		bcd |= (hexFigure / 10) << (4*1);
		hexFigure %= 10;
	}
	bcd |= hexFigure;
	
	return bcd;
}
*/
U32 HexToBcd(U8 hexFigure)
{
U32 bcd;
	HexToBcdU32(hexFigure, &bcd);
	return bcd;
}

/*

	test_mCodCommon = HexToBcdU32(0); //0
	test_mCodCommon = HexToBcdU32(9); //9
	test_mCodCommon = HexToBcdU32(10); //0x10
	test_mCodCommon = HexToBcdU32(11); //0x11
	test_mCodCommon = HexToBcdU32(99); //0x99
	test_mCodCommon = HexToBcdU32(100); //0x100
	test_mCodCommon = HexToBcdU32(101); //0x101
	test_mCodCommon = HexToBcdU32(999); //0x999
	test_mCodCommon = HexToBcdU32(1000); //0x1000
	test_mCodCommon = HexToBcdU32(1001); //0x1001
	test_mCodCommon = HexToBcdU32(1111); //0x1111
	test_mCodCommon = HexToBcdU32(9000); //0x9000
	test_mCodCommon = HexToBcdU32(9999); //0x9999
	test_mCodCommon = HexToBcdU32(10000); // 0
	test_mCodCommon = HexToBcdU32(10001); // 1
	

*/

/******************************************************************************
* FUNC: //显示有问题，比如输入参数0x17bf0
******************************************************************************/
U32 BcdToHexU32(U32 bcdFigure)
{
U8 num;
U32 multiplier = 0;
U32 hexFig = 0;
	
	multiplier = 1;
	for(num=0; num<(32/4); num++)
	{
		if((bcdFigure & 0x0F) != 0)
		{
			hexFig += ((bcdFigure & 0x0F) * multiplier);
		}
		
		multiplier *= 10;
		bcdFigure >>= 4;
	}
	return hexFig;
}

/******************************************************************************
* FUNC: //十进制转换为十六进制显示
******************************************************************************/
void BcdDecToHex(U32 num,U8* str)
{
    U8 i = 0;
    U8 actnum=0;
    U8  numres[8];
    while (num!=0)
    {
        if(num%16<10)
            numres[i]=num%16+'0';
        else
            numres[i] = num%16+'97';
        num=num/16;
        i++;
        actnum++; 
    }
    i=0;
    while(i<=actnum){
        str[i]=numres[actnum-i-1];
        i++;
    }
    for(i=actnum;i<sizeof(numres);i++){
        str[i]=0;
    }

}




/******************************************************************************
* FUNC: //
* U_SIGN_bHaveTested; 2013-07-04
******************************************************************************/
U8 BcdToHexU8(U8 bcdFigure)
{
	U8 hh = (bcdFigure >> 4);
	U8 ll = (bcdFigure & 0x0F);
	
	if((hh >= 10) || (ll >= 10))
	{
		return 0;
	}
	
	return (hh * 10) + ll;
}

/*

	test_mCodCommon = BcdToHexU8(0); //0
	test_mCodCommon = BcdToHexU8(1); //1
	test_mCodCommon = BcdToHexU8(99); //0x3F = 63
	test_mCodCommon = BcdToHexU8(0x63); //0x3F
	test_mCodCommon = BcdToHexU8(0xFF); //0
*/


/******************************************************************************
* FUNC: // END
*   IN:
*  OUT: 
******************************************************************************/
