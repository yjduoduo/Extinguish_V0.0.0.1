#define __sim1_flsInqPoit_C__
/******************************************************************************
* @file    sim1_flsInqPoit.c
* @author  yx
* @version V1.2, 2013-07-07
* @date    2013-07-05
* @brief   测试 flsInqPoint.c 的文件。
*          用特殊用例来测试。准备模拟一条一条存储的情况再测试。
		sector 最少4段。
		测试结果在最后。0x100bytes/sector 是可以的。
******************************************************************************/
#include  "sim1_flsInqPoit.h"

#include  "incSysCommon.h"
#include  "strFlsAdrDef.h"
#include  "flsAdrCalculate.h"
// #include  "strDevice.h"
// #include  "fls_Interface.h"
#include  "flsInqPoint.h"

//#include "incFile.h"	
/*================= 常数 ============================================*/

/******************************************************************************
* FUNC: //
******************************************************************************/


#if U_SYS_Test_Flash_InqPoint == 1
/******************************************************************************
* NAME: U_SYS_Test_Flash_InqPoint
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

static U32 test_result;

//应该每次存储，比较指针。
void sim_FlsInqPoit_Que_Test(void)
{
U32 mIni;
U8 mFlsItem = U_SimFlsPoit_FlsItemCls;
	getFlsItem_Addr(mFlsItem, U_SimFlsPoit_Part, &stSimFlsItemAdr);
	test_result = test_result;
	
	sim_InitPointBuf();
	
	
	for(mIni=1; mIni<19; mIni++)
	{
		mIni = mIni; //方便改数据
		if(!sim_initDat(mIni))
		{
			continue;
		}
		test_result = sim_jdgPoint(mIni);
	}
	for(mIni=30; mIni<37; mIni++)
	{
		mIni = mIni; //方便改数据
		if(!sim_initDat(mIni))
		{
			continue;
		}
		test_result = sim_jdgPoint(mIni);
	}
	
	
	//看数据填充是否正确：1~18,30~36正确。
	for(mIni=0; mIni<50; mIni++)
	{
		sim_initDat(mIni);
	}
	
}


/******************************************************************************
* FUNC: //
******************************************************************************/
static BOOL sim_jdgPoint(U32 mTestNum)
{
U32 bResult;
TFlsQueuePoint_st stHeadEnd;

	bResult = flsInq_1Cls_JdgPoint(U_SimFlsPoit_Part, U_SimFlsPoit_FlsItemCls,
						TFlsQueuePoint_st *pRtnHeadEnd);
	
	if(mTestNum < U_SimFlsPoit_TestNum_MAX)
	{
		if(bResult)
		{
			vSimPoitResult[mTestNum][0] = stHeadEnd.headAdr; 
			vSimPoitResult[mTestNum][1] = stHeadEnd.endAdr;
		}
		else
		{
			vSimPoitResult[mTestNum][0] = ~0;
			vSimPoitResult[mTestNum][1] = ~0;
		}			
	}
	vSimPoitResult[mTestNum][2] = bResult;
	
	if( (vSimPoitResult[mTestNum][0] != vSimPoit_yxFill[mTestNum][0])
	  ||(vSimPoitResult[mTestNum][1] != vSimPoit_yxFill[mTestNum][1])
	  ||(vSimPoitResult[mTestNum][2] != vSimPoit_yxFill[mTestNum][2])
	  )
	{
		test_result = FALSE;
	}
	return bResult;
	
}

/******************************************************************************
* FUNC: //
******************************************************************************/
static void sim_InitPointBuf(void)
{
	U32 ii;
	for (ii=0; ii<U_SimFlsPoit_TestNum_MAX; ii++)
	{
		vSimPoitResult[ii][0] = ~0;
		vSimPoitResult[ii][1] = ~0;
		vSimPoitResult[ii][2] = ~0;

		vSimPoit_yxFill[ii][0] = ~0;
		vSimPoit_yxFill[ii][1] = ~0;
		vSimPoit_yxFill[ii][2] = ~0;
	}
	
	sim_shouldPointBuf_0x20_0x1000();
	for (ii=0; ii<U_SimFlsPoit_TestNum_MAX; ii++)
	{
		if(vSimPoit_yxFill[ii][2] == 1)
		{
			vSimPoit_yxFill[ii][0] += U_SimFlsPoit_AdrS;
			vSimPoit_yxFill[ii][1] += U_SimFlsPoit_AdrS;
		}
	}
}

static void sim_shouldPointBuf_0x20_0x1000(void) //0x20 sectors, 0x1000bytes/sector
{
	// 1: FALSE
	vSimPoit_yxFill[1][0] = ~0;
	vSimPoit_yxFill[1][1] = ~0;
	vSimPoit_yxFill[1][2] = 0;
	
	// 2: head= 0,  	end= 0x   20 //
	vSimPoit_yxFill[2][0] = 0;
	vSimPoit_yxFill[2][1] = U_SimFlsPoit_1ItemBytes * 2;
	vSimPoit_yxFill[2][2] = 1;
	
	// 3: head= 0,  	end= 0x  FF0 //
	vSimPoit_yxFill[3][0] = 0;
	vSimPoit_yxFill[3][1] = U_SimFlsPoit_1SectorBytes - U_SimFlsPoit_1ItemBytes;
	vSimPoit_yxFill[3][2] = 1;
	
	// 4: head= 0,  	end= 0x 1 000 //
	vSimPoit_yxFill[4][0] = 0;
	vSimPoit_yxFill[4][1] = U_SimFlsPoit_1SectorBytes;
	vSimPoit_yxFill[4][2] = 1;
	
	// 5: head= 0,  	end= 0x 1 FF0 //
	vSimPoit_yxFill[5][0] = 0;
	vSimPoit_yxFill[5][1] = U_SimFlsPoit_1SectorBytes*2 - U_SimFlsPoit_1ItemBytes;
	vSimPoit_yxFill[5][2] = 1;
	
	// 6: head= 0,  		end= 0x 2 000 //
	vSimPoit_yxFill[6][0] = 0;
	vSimPoit_yxFill[6][1] = U_SimFlsPoit_1SectorBytes*2;
	vSimPoit_yxFill[6][2] = 1;
	
	// 7: head=  0,  		end= 0x 1F 000 //
	vSimPoit_yxFill[7][0] = 0;
	vSimPoit_yxFill[7][1] = (U_InqPoint_FlsItem_SectMAX-1) * U_SimFlsPoit_1SectorBytes; 
	vSimPoit_yxFill[7][2] = 1;      //0x1F000;
	
	// 8: head= 0,  		end= 0x 1F 020 //
	vSimPoit_yxFill[8][0] = 0;
	vSimPoit_yxFill[8][1] = (U_InqPoint_FlsItem_SectMAX-1) * U_SimFlsPoit_1SectorBytes
							+ U_SimFlsPoit_1ItemBytes*2; 
	vSimPoit_yxFill[8][2] = 1;		//0x1F020;
	
	// 9: head=  0,  		end= 0x 1F FF0 //
	vSimPoit_yxFill[9][0] = 0;
	vSimPoit_yxFill[9][1] = (U_InqPoint_FlsItem_SectMAX) * U_SimFlsPoit_1SectorBytes
							- U_SimFlsPoit_1ItemBytes; 
	vSimPoit_yxFill[9][2] = 1;		//0x1FFF0;
	
	//10: head= 0x 1 000,  end= 0x 1F FF0 //
	vSimPoit_yxFill[10][0] = U_SimFlsPoit_1SectorBytes;
	vSimPoit_yxFill[10][1] = (U_InqPoint_FlsItem_SectMAX) * U_SimFlsPoit_1SectorBytes
							- U_SimFlsPoit_1ItemBytes; 
	vSimPoit_yxFill[10][2] = 1;		//0x1FFF0;
	
	//11: head= 0x 1 000,  end= 0x 0 //
	vSimPoit_yxFill[11][0] = U_SimFlsPoit_1SectorBytes;
	vSimPoit_yxFill[11][1] = 0;
	vSimPoit_yxFill[11][2] = 1;
	
	//12: head= 0x 1 000,  end= 0x 20 //
	vSimPoit_yxFill[12][0] = U_SimFlsPoit_1SectorBytes;
	vSimPoit_yxFill[12][1] = U_SimFlsPoit_1ItemBytes*2;
	vSimPoit_yxFill[12][2] = 1;
	
	//13: head= 0x 1 000,  end= 0x  FF0 //
	vSimPoit_yxFill[13][0] = U_SimFlsPoit_1SectorBytes;
	vSimPoit_yxFill[13][1] = U_SimFlsPoit_1SectorBytes - U_SimFlsPoit_1ItemBytes;
	vSimPoit_yxFill[13][2] = 1;
	
	//14: head= 0x 1E 000,  end= 0x  FF0 //
	vSimPoit_yxFill[14][0] = (U_InqPoint_FlsItem_SectMAX-2) * U_SimFlsPoit_1SectorBytes; 
	vSimPoit_yxFill[14][1] = U_SimFlsPoit_1SectorBytes - U_SimFlsPoit_1ItemBytes;
	vSimPoit_yxFill[14][2] = 1;
	
	//15: head= 0x 1E 000,  end= 0x 1 000 //
	vSimPoit_yxFill[15][0] = (U_InqPoint_FlsItem_SectMAX-2) * U_SimFlsPoit_1SectorBytes; 
	vSimPoit_yxFill[15][1] = U_SimFlsPoit_1SectorBytes;
	vSimPoit_yxFill[15][2] = 1;
	
	//16: head= 0x 1E 000,  end= 0x 1 020 //
	vSimPoit_yxFill[16][0] = (U_InqPoint_FlsItem_SectMAX-2) * U_SimFlsPoit_1SectorBytes; 
	vSimPoit_yxFill[16][1] = U_SimFlsPoit_1SectorBytes + U_SimFlsPoit_1ItemBytes*2;
	vSimPoit_yxFill[16][2] = 1;
	
	//17: head= 0x 1F 000,  end= 0x 1 FF0 //
	vSimPoit_yxFill[17][0] = (U_InqPoint_FlsItem_SectMAX-1) * U_SimFlsPoit_1SectorBytes; 
	vSimPoit_yxFill[17][1] = U_SimFlsPoit_1SectorBytes*2 - U_SimFlsPoit_1ItemBytes;
	vSimPoit_yxFill[17][2] = 1;
	
	//18: FALSE //
	vSimPoit_yxFill[18][0] = ~0;
	vSimPoit_yxFill[18][1] = ~0;
	vSimPoit_yxFill[18][2] = 0;
	
	//30: head= 0x  1 000,  	end= 0x    10 //
	vSimPoit_yxFill[30][0] = U_SimFlsPoit_1SectorBytes;
	vSimPoit_yxFill[30][1] = U_SimFlsPoit_1ItemBytes;
	vSimPoit_yxFill[30][2] = 1;
	//31: head= 0x 1E 000,  	end= 0x    10 //
	vSimPoit_yxFill[31][0] = (U_InqPoint_FlsItem_SectMAX-2) * U_SimFlsPoit_1SectorBytes; 
	vSimPoit_yxFill[31][1] = U_SimFlsPoit_1ItemBytes;
	vSimPoit_yxFill[31][2] = 1;
	//32: head= 0x 1E 000,  	end= 0x  1 010 //
	vSimPoit_yxFill[32][0] = (U_InqPoint_FlsItem_SectMAX-2) * U_SimFlsPoit_1SectorBytes; 
	vSimPoit_yxFill[32][1] = U_SimFlsPoit_1SectorBytes + U_SimFlsPoit_1ItemBytes;
	vSimPoit_yxFill[32][2] = 1;
	//33: head= 0x 1F 000,		end= 0x 1E 010 //
	vSimPoit_yxFill[33][0] = (U_InqPoint_FlsItem_SectMAX-1) * U_SimFlsPoit_1SectorBytes; 
	vSimPoit_yxFill[33][1] = (U_InqPoint_FlsItem_SectMAX-2) * U_SimFlsPoit_1SectorBytes
								+ U_SimFlsPoit_1ItemBytes;  
	vSimPoit_yxFill[33][2] = 1;  //
	
	//34: head=   0,  		end= 0x 1E 010 //
	vSimPoit_yxFill[34][0] = 0;
	vSimPoit_yxFill[34][1] = (U_InqPoint_FlsItem_SectMAX-2) * U_SimFlsPoit_1SectorBytes
								+ U_SimFlsPoit_1ItemBytes;  
	vSimPoit_yxFill[34][2] = 1;
	//35: head=   0,  		end= 0x 1F 010 //
	vSimPoit_yxFill[35][0] = 0;
	vSimPoit_yxFill[35][1] = (U_InqPoint_FlsItem_SectMAX-1) * U_SimFlsPoit_1SectorBytes
								+ U_SimFlsPoit_1ItemBytes;  
	vSimPoit_yxFill[35][2] = 1;
	//36: head= 0x  1 000,  	end= 0x 1F 010 //
	vSimPoit_yxFill[36][0] = U_SimFlsPoit_1SectorBytes;
	vSimPoit_yxFill[36][1] = (U_InqPoint_FlsItem_SectMAX-1) * U_SimFlsPoit_1SectorBytes
								+ U_SimFlsPoit_1ItemBytes;  
	vSimPoit_yxFill[36][2] = 1;
	
}

/******************************************************************************
* FUNC: //
******************************************************************************/
static BOOL sim_initDat(U8 mIni) //模拟flash数据
{
	switch(mIni)
	{
		case 1:
			test_initDat_01(); //datOK // test_result = FALSE;
			return TRUE;
		case 2:
			test_initDat_02(); //datOK // 
			return TRUE;
		case 3:
			test_initDat_03(); //datOK // 
			return TRUE;
		case 4:
			test_initDat_04(); //datOK // 
			return TRUE;
		case 5:
			test_initDat_05(); //datOK // 
			return TRUE;
		case 6:
			test_initDat_06(); //datOK // 
			return TRUE;
		case 7:
			test_initDat_07(); //datOK // 
			return TRUE;
		case 8:
			test_initDat_08(); //datOK // 
			return TRUE;
		case 9:
			test_initDat_09(); //datOK // 
			return TRUE;
		case 10:
			test_initDat_10(); //datOK // 
			return TRUE;
		case 11:
			test_initDat_11(); //datOK // test_result = FALSE;
			return TRUE;
		case 12:
			test_initDat_12(); //datOK // 
			return TRUE;
		case 13:
			test_initDat_13(); //datOK // 
			return TRUE;
		case 14:
			test_initDat_14(); //datOK // 
			return TRUE;
		case 15:
			test_initDat_15(); //datOK // 
			return TRUE;
		case 16:
			test_initDat_16(); //datOK // 
			return TRUE;
		case 17:
			test_initDat_17(); //datOK // 
			return TRUE;
		case 18:
			test_initDat_18(); //datOK // 
			return TRUE;
			
			
		case 30:
			test_initDat_30(); //datOK // 
			return TRUE;
		case 31:
			test_initDat_31(); //datOK // test_result = FALSE;
			return TRUE;
		case 32:
			test_initDat_32(); //datOK // 
			return TRUE;
		case 33:
			test_initDat_33(); //datOK // 
			return TRUE;
		case 34:
			test_initDat_34(); //datOK // 
			return TRUE;
		case 35:
			test_initDat_35(); //datOK // 
			return TRUE;
		case 36:
			test_initDat_36(); //datOK // 
			return TRUE;
			
		default:
			break;
	}
	return FALSE;
}

// 01.  ____,  ____, ...,  ____,  ____.
//      start = end = 0 
static void test_initDat_01(void) //FALSE
{
	test_initDat_AllSpace();
}

// 02.  #___,  ____, ...,  ____,  ____.
//      start end 
static void test_initDat_02(void) // 
{
	test_initDat_AllSpace();
	test_initDat_head_set1(0);
	test_initDat_item_set1(0, 0);
}

// 03.  ###_,  ____, ...,  ____,  ____.
//      start end 
static void test_initDat_03(void)
{
	test_initDat_AllSpace();
	test_initDat_sectX_set1(0);
	test_initDat_item_clr0(0, U_SimFlsPoit_Item_1Sector-1);
}

// 04.  ####,  ____, ...,  ____,  ____.
//      start end 
static void test_initDat_04(void)
{
	test_initDat_AllSpace();
	test_initDat_sectX_set1(0);	
}

// 05.  ####,  ###_, ...,  ____,  ____.
//      start     end 
static void test_initDat_05(void)
{
	test_initDat_AllSpace();
	test_initDat_sectX_set1(0);	
	
	test_initDat_sectX_set1(1);
	test_initDat_item_clr0(1, U_SimFlsPoit_Item_1Sector-1);
}

// 06.  ####,  ####, ...,  ____,  ____.
//      start              end 
static void test_initDat_06(void)
{
	
	test_initDat_AllSpace();
	test_initDat_sectX_set1(0);		
	test_initDat_sectX_set1(1);
}

// 07.  ####,  ####, ...,  ####,  ____.
//      start                     end 
static void test_initDat_07(void)
{
	test_initDat_AllHave();
	test_initDat_sectX_clr0(U_SimFlsPoit_Sector_MAX-1);
}

// 08.  ####,  ####, ...,  ####,  #___.
//      start                      end 
static void test_initDat_08(void)
{
	test_initDat_AllHave();
	test_initDat_sectX_clr0(U_SimFlsPoit_Sector_MAX-1);
	test_initDat_head_set1(U_SimFlsPoit_Sector_MAX-1);
	test_initDat_item_set1(U_SimFlsPoit_Sector_MAX-1, 0);
	
}

// 09.  ####,  ####, ...,  ####,  ###_.
//      start                        end 
static void test_initDat_09(void)
{
	test_initDat_AllHave();
	test_initDat_item_clr0(U_SimFlsPoit_Sector_MAX-1, U_SimFlsPoit_Item_1Sector-1);
}

// 10.  ____,  ####, ...,  ####,  ###_.
//             start                 end 
static void test_initDat_10(void)
{
	test_initDat_AllHave();
	test_initDat_item_clr0(U_SimFlsPoit_Sector_MAX-1, U_SimFlsPoit_Item_1Sector-1);
	test_initDat_sectX_clr0(0);
	
}

// 11.  ____,  ####, ...,  ####,  ####.
//      end    start             
static void test_initDat_11(void)
{
	test_initDat_AllHave();
	test_initDat_sectX_clr0(0);
	
}

// 12.  #___,  ####, ...,  ####,  ####.
//       end   start             
static void test_initDat_12(void)
{
	test_initDat_AllHave();
	test_initDat_sectX_clr0(0);
	test_initDat_head_set1(0);
	test_initDat_item_set1(0,0);
}

// 13.  ###_,  ####, ...,  ####,  ####.
//         end start             
static void test_initDat_13(void)
{
	test_initDat_AllHave();
	test_initDat_item_clr0(0, U_SimFlsPoit_Item_1Sector-1);
	
}

// 14.  ###_,  ____, ...,  ####,  ####.
//         end             start  
static void test_initDat_14(void)
{
	test_initDat_AllSpace();
	test_initDat_sectX_set1(0);
	test_initDat_item_clr0(0, U_SimFlsPoit_Item_1Sector-1);
	test_initDat_sectX_set1(U_SimFlsPoit_Sector_MAX - 1);
	test_initDat_sectX_set1(U_SimFlsPoit_Sector_MAX - 2);
}

// 15.  ####,  ____, ...,  ####,  ####.
//             end         start  
static void test_initDat_15(void)
{
	test_initDat_AllSpace();
	test_initDat_sectX_set1(0);
	test_initDat_sectX_set1(U_SimFlsPoit_Sector_MAX - 1);
	test_initDat_sectX_set1(U_SimFlsPoit_Sector_MAX - 2);
	
}

// 16.  ####,  #___, ...,  ####,  ####.
//              end        start  
static void test_initDat_16(void)
{
	test_initDat_AllSpace();
	test_initDat_sectX_set1(0);
	test_initDat_head_set1(1);
	test_initDat_item_set1(1, 0);
	test_initDat_sectX_set1(U_SimFlsPoit_Sector_MAX - 1);
	test_initDat_sectX_set1(U_SimFlsPoit_Sector_MAX - 2);
	
}

// 17.  ####,  ###_, ...,  ____,  ####.
//                end             start  
static void test_initDat_17(void)
{
	test_initDat_AllSpace();
	test_initDat_sectX_set1(0);
	test_initDat_sectX_set1(1);
	test_initDat_item_clr0(1, U_SimFlsPoit_Item_1Sector - 1);
	test_initDat_sectX_set1(U_SimFlsPoit_Sector_MAX - 1);
	
}

// 18.  ####,  ####, ...,  ####,  ####.
//      start = end = 0        
static void test_initDat_18(void)
{
	test_initDat_AllHave();
	
}


//只有head, 没有实际记录的sector:



// 30.  |____,  ####, ...,  ####,  ####.
//      end     start 
static void test_initDat_30(void)
{
	test_initDat_AllHave();
	test_initDat_sectX_clr0(0);
	test_initDat_head_set1(0);
	
}

// 31.  |____,  ____, ...,  ####,  ####.
//      end                 start 
static void test_initDat_31(void) 
{
	test_initDat_AllSpace();
	test_initDat_head_set1(0);
	test_initDat_sectX_set1(U_SimFlsPoit_Sector_MAX-1);
	test_initDat_sectX_set1(U_SimFlsPoit_Sector_MAX-2);
	
}

// 32.  ####,  |____, ...,  ####,  ####.
//             end          start 
static void test_initDat_32(void)
{
	test_initDat_AllSpace();
	test_initDat_sectX_set1(0);
	test_initDat_head_set1(1);
	test_initDat_sectX_set1(U_SimFlsPoit_Sector_MAX-1);
	test_initDat_sectX_set1(U_SimFlsPoit_Sector_MAX-2);
	
	
	//test_initDat_AllHave();
	//test_initDat_sectX_clr0(1);
	//test_initDat_head_set1(1);
	
}

// 33.  ####,  ####, ...,  |____,  ####.
//                         end     start 
static void test_initDat_33(void)
{
	test_initDat_AllHave();
	test_initDat_sectX_clr0(U_SimFlsPoit_Sector_MAX-2);
	test_initDat_head_set1(U_SimFlsPoit_Sector_MAX-2);
	
}

// 34.  ####,  ####, ...,  |____,  ____.
//      start              end     
static void test_initDat_34(void)
{
	test_initDat_AllHave();
	test_initDat_sectX_clr0(U_SimFlsPoit_Sector_MAX-2);
	test_initDat_head_set1(U_SimFlsPoit_Sector_MAX-2);
	test_initDat_sectX_clr0(U_SimFlsPoit_Sector_MAX-1);
	
}

// 35.  ####,  ####, ...,  ####,  |____.
//      start                     end    
static void test_initDat_35(void)
{
	test_initDat_AllHave();
	test_initDat_sectX_clr0(U_SimFlsPoit_Sector_MAX-1);
	test_initDat_head_set1(U_SimFlsPoit_Sector_MAX-1);
	
}

// 36.  ___,  ####, ...,  ####,  |____.
//            start              end    
static void test_initDat_36(void)
{
	test_initDat_AllHave();
	test_initDat_sectX_clr0(0);
	
	test_initDat_sectX_clr0(U_SimFlsPoit_Sector_MAX-1);
	test_initDat_head_set1(U_SimFlsPoit_Sector_MAX-1);
}


//----------------------------------------------------------------------


BOOL sim_FlsInqPoit_b_1Item_OK(U8 chip, U32 mAdr)
{
U32 mSimSect;
U32 item;
U32 flsItemMax;
chip = chip;

	
	if(sim_cacuSect_fromFlsAdr(mAdr, &mSimSect))
	{
		item = FlsItm_adr_inSect_itmSequ(mAdr, U_SimFlsPoit_FlsItemCls, U_SimFlsPoit_1ItemBytes);
		flsItemMax = U_SimFlsPoit_1SectorBytes / U_SimFlsPoit_1ItemBytes;
		if(item == 0)
		{
			//不应有的
			return bSim_item_have(mSimSect, 1);
		}
		else if(item == 1)
		{
			return bSim_item_have(mSimSect, 1);
		}
		else if(item == (flsItemMax - 1))
		{
			return bSim_item_have(mSimSect, U_SimFlsPoit_Item_1Sector - 1);			
		}
		else if(item == (flsItemMax - 2))
		{
			return bSim_item_have(mSimSect, U_SimFlsPoit_Item_1Sector - 2);	
		}
		else
		{
			return bSim_item_have(mSimSect, U_SimFlsPoit_Item_Mid);	
		}
	}
	else
	{
		return FALSE;
	}
}

BOOL sim_FlsInqPoit_bSectHaveRecord(U8 chip, U32 mAdr, U8 mFlsItem)
{
U32 mSimSect;
chip = chip;
mFlsItem = mFlsItem;

	if(sim_cacuSect_fromFlsAdr(mAdr, &mSimSect))
	{
		return (bSim_sectorHead_have(mSimSect));
	}
	else
	{
		return FALSE;
	}
}


static BOOL sim_cacuSect_fromFlsAdr(U32 mAdr, U32 *pRtnSimSect)
{
U32 mSimSect;
	
	mAdr = mAdr - stSimFlsItemAdr.adrS;
	mSimSect = mAdr / U_SimFlsPoit_1SectorBytes;
	*pRtnSimSect = mSimSect;
	return (mSimSect < U_SimFlsPoit_Sector_MAX);
}

//----------------------------------------------------------------------
static void test_initDat_AllHave(void)
{
	U32 mSect;
	U32 item;
	
	for(mSect=0; mSect<U_SimFlsPoit_Sector_MAX; mSect++)
	{
		test_initDat_head_set1(mSect);
		for(item=0; item<U_SimFlsPoit_Item_1Sector; item++)
		{
			test_initDat_item_set1(mSect, item);
		}
	}
}

static void test_initDat_AllSpace(void)
{
	U32 mSect;
	U32 item;
	
	for(mSect=0; mSect<U_SimFlsPoit_Sector_MAX; mSect++)
	{
		test_initDat_head_clr0(mSect);
		for(item=0; item<U_SimFlsPoit_Item_1Sector; item++)
		{
			test_initDat_item_clr0(mSect, item);
		}
	}
}

static void test_initDat_head_set1(U32 mSect)
{
	if(mSect >= U_SimFlsPoit_Sector_MAX)
		return;
	vSimFlsData[mSect][0] = U_SimFlsPoit_signHave;
}
static void test_initDat_head_clr0(U32 mSect)
{
	if(mSect >= U_SimFlsPoit_Sector_MAX)
		return;
	vSimFlsData[mSect][0] = U_SimFlsPoit_signSpace;
}
static BOOL bSim_sectorHead_have(U32 mSect)
{
	if(mSect >= U_SimFlsPoit_Sector_MAX)
		return FALSE;
	return (vSimFlsData[mSect][0] == U_SimFlsPoit_signHave);
}

static void test_initDat_item_set1(U32 mSect, U32 item)
{
	if(mSect >= U_SimFlsPoit_Sector_MAX)
		return;
	
	//最后的2个，对应flash段内的最后2个。
	if( (item == U_SimFlsPoit_Item_1Sector-1)   
	  ||(item == U_SimFlsPoit_Item_1Sector-2))  
	{   
		vSimFlsData[mSect][item] = U_SimFlsPoit_signHave;
	}
	//除了0,1, 其余位置都是整sector一起置位。
	else if(item < (U_SimFlsPoit_Item_1Sector-2))
	{
		vSimFlsData[mSect][item+1] = U_SimFlsPoit_signHave;
	}
}
static void test_initDat_item_clr0(U32 mSect, U32 item)
{
	if(mSect >= U_SimFlsPoit_Sector_MAX)
		return;
	
	//最后的2个，对应flash段内的最后2个。
	if( (item == U_SimFlsPoit_Item_1Sector-1)   
	  ||(item == U_SimFlsPoit_Item_1Sector-2))  
	{   
		vSimFlsData[mSect][item] = U_SimFlsPoit_signSpace;
	}
	//除了0,1, 其余位置都是整sector一起置位。
	else if(item < (U_SimFlsPoit_Item_1Sector-2))
	{
		vSimFlsData[mSect][item+1] = U_SimFlsPoit_signSpace;
	}
}
static BOOL bSim_item_have(U32 mSect, U32 item) //item=0对应地址0
{
	if(mSect >= U_SimFlsPoit_Sector_MAX)
		return FALSE;
	if(item >= U_SimFlsPoit_Item_1Sector)
		return FALSE;
	return (vSimFlsData[mSect][item] == U_SimFlsPoit_signHave);
}


static void test_initDat_sectX_set1(U32 mSect)
{
U32 item;

	if(mSect >= U_SimFlsPoit_Sector_MAX)
		return;
	test_initDat_head_set1(mSect);
	for(item=0; item<U_SimFlsPoit_Item_1Sector; item++)
	{
		test_initDat_item_set1(mSect, item);
	}
}

static void test_initDat_sectX_clr0(U32 mSect)
{
U32 item;

	if(mSect >= U_SimFlsPoit_Sector_MAX)
		return;
	test_initDat_head_clr0(mSect);
	for(item=0; item<U_SimFlsPoit_Item_1Sector; item++)
	{
		test_initDat_item_clr0(mSect, item);
	}
}

/******************************************************************************
* FUNC: // 
*   IN:
*  OUT: 
******************************************************************************/


/******************************************************************************
测试：0x20 sector, 0x1000bytes/Sector.  2013.7.5

// 01.  ____,  ____, ...,  ____,  ____. 	// 1: FALSE
//      start = end = 0 

// 02.  #___,  ____, ...,  ____,  ____. 	// 2: head= 0,  	end= 0x   20 //
//      start end 

// 03.  ###_,  ____, ...,  ____,  ____. 	// 3: head= 0,  	end= 0x  FF0 //
//      start end 	

// 04.  ####,  ____, ...,  ____,  ____. 	// 4: head= 0,  	end= 0x 1 000 //
//      start end 

// 05.  ####,  ###_, ...,  ____,  ____. 	// 5: head= 0,  	end= 0x 1 FF0 //
//      start     end 

// 06.  ####,  ####, ...,  ____,  ____. 	// 6: head= 0,  		end= 0x 2 000 //
//      start              end 

// 07.  ####,  ####, ...,  ####,  ____. 	// 7: head=  0,  		end= 0x 1F 000 //
//      start                     end 

// 08.  ####,  ####, ...,  ####,  #___. 	// 8: head= 0,  		end= 0x 1F 020 //
//      start                      end 

// 09.  ####,  ####, ...,  ####,  ###_. 	// 9: head=  0,  		end= 0x 1F FF0 //
//      start                        end 

// 10.  ____,  ####, ...,  ####,  ###_. 	//10: head= 0x 1 000,  end= 0x 1F FF0 //
//             start                 end 

// 11.  ____,  ####, ...,  ####,  ####. 	//11: head= 0x 1 000,  end= 0x 0 //
//      end    start             

// 12.  #___,  ####, ...,  ####,  ####. 	//12: head= 0x 1 000,  end= 0x 20 //
//       end   start             

// 13.  ###_,  ####, ...,  ####,  ####. 	//13: head= 0x 1 000,  end= 0x  FF0 //
//         end start             

// 14.  ###_,  ____, ...,  ####,  ####. 	//14: head= 0x 1E 000,  end= 0x  FF0 //
//         end             start  

// 15.  ####,  ____, ...,  ####,  ####. 	//15: head= 0x 1E 000,  end= 0x 1 000 //
//             end         start  

// 16.  ####,  #___, ...,  ####,  ####. 	//16: head= 0x 1E 000,  end= 0x 1 020 //
//              end        start  

// 17.  ####,  ###_, ...,  ____,  ####. 	//17: head= 0x 1F 000,  end= 0x 1 FF0 //
//                end             start  

// 18.  ####,  ####, ...,  ####,  ####. 	//18: FALSE //
//      start = end = 0        

//只有head, 没有实际记录的sector:

// 30.  |____,  ####, ...,  ####,  ####.	//30: head= 0x  1 000,  	end= 0x    10 //
//      end     start 

// 31.  |____,  ____, ...,  ####,  ####. 	//31: head= 0x 1E 000,  	end= 0x    10 //
//      end                 start 

// 32.  ####,  |____, ...,  ####,  ####. 	//32: head= 0x 1E 000,  	end= 0x  1 010 //
//             end          start 

// 33.  ####,  ####, ...,  |____,  ####. 	//33: head= 0x 1F 000,		end= 0x 1E 010 //
//                         end     start 

// 34.  ####,  ####, ...,  |____,  ____. 	//34: head=   0,  		end= 0x 1E 010 //
//      start              end     

// 35.  ####,  ####, ...,  ####,  |____. 	//35: head=   0,  		end= 0x 1F 010 //
//      start                     end    

// 36.  ___,  ####, ...,  ####,  |____. 	//36: head= 0x  1 000,  	end= 0x 1F 010 //
//            start              end    

 
******************************************************************************/


/******************************************************************************
测试：0x20 sector, 0x100bytes/Sector.  2013.7.6

// 01.  ____,  ____, ...,  ____,  ____. 	//FALSE
//      start = end = 0 

// 02.  #___,  ____, ...,  ____,  ____. 	// head= 0,  	end= 0x   20
//      start end 

// 03.  ###_,  ____, ...,  ____,  ____. 	// head= 0,  	end= 0x  F0
//      start end 	

// 04.  ####,  ____, ...,  ____,  ____. 	// head= 0,  	end= 0x 1 00
//      start end 

// 05.  ####,  ###_, ...,  ____,  ____. 	// head= 0,  	end= 0x 1 F0
//      start     end 

// 06.  ####,  ####, ...,  ____,  ____. 	// head= 0,  		end= 0x 2 00
//      start              end 

// 07.  ####,  ####, ...,  ####,  ____. 	// head=  0,  		end= 0x 1F 00
//      start                     end 

// 08.  ####,  ####, ...,  ####,  #___. 	// head= 0,  		end= 0x 1F 20
//      start                      end 

// 09.  ####,  ####, ...,  ####,  ###_. 	// head=  0,  		end= 0x 1F F0
//      start                        end 

// 10.  ____,  ####, ...,  ####,  ###_. 	// head= 0x 1 00,  end= 0x 1F F0
//             start                 end 

// 11.  ____,  ####, ...,  ####,  ####. 	// head= 0x 1 00,  end= 0x 0
//      end    start             

// 12.  #___,  ####, ...,  ####,  ####. 	// head= 0x 1 00,  end= 0x 20
//       end   start             

// 13.  ###_,  ####, ...,  ####,  ####. 	// head= 0x 1 00,  end= 0x  F0
//         end start             

// 14.  ###_,  ____, ...,  ####,  ####. 	// head= 0x 1E 00,  end= 0x  F0
//         end             start  

// 15.  ####,  ____, ...,  ####,  ####. 	// head= 0x 1E 00,  end= 0x 1 00
//             end         start  

// 16.  ####,  #___, ...,  ####,  ####. 	// head= 0x 1E 00,  end= 0x 1 20
//              end        start  

// 17.  ####,  ###_, ...,  ____,  ####. 	// head= 0x 1F 00,  end= 0x 1 F0
//                end             start  

// 18.  ####,  ####, ...,  ####,  ####. 	//FALSE
//      start = end = 0        

//只有head, 没有实际记录的sector:

// 30.  |____,  ####, ...,  ####,  ####.	// head= 0x  1 00,  	end= 0x    10
//      end     start 

// 31.  |____,  ____, ...,  ####,  ####. 	// head= 0x 1E 00,  	end= 0x    10
//      end                 start 

// 32.  ####,  |____, ...,  ####,  ####. 	// head= 0x 1E 00,  	end= 0x  1 10
//             end          start 

// 33.  ####,  ####, ...,  |____,  ####. 	// head= 0x 1F 00,		end= 0x 1E 10
//                         end     start 

// 34.  ####,  ####, ...,  |____,  ____. 	// head=   0,  		end= 0x 1E 10
//      start              end     

// 35.  ####,  ####, ...,  ####,  |____. 	// head=   0,  		end= 0x 1F 10
//      start                     end    

// 36.  ___,  ####, ...,  ####,  |____. 	// head= 0x  1 00,  	end= 0x 1F 10
//            start              end    

 
******************************************************************************/




/******************************************************************************
* FUNC: // END
*   IN:
*  OUT: 
******************************************************************************/
#endif //U_SYS_Test_Flash_InqPoint
