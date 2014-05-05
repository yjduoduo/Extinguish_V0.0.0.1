#define __sim2_flsInqPoit_C__
/******************************************************************************
* @file    sim2_flsInqPoit.c
* @author  yx
* @version V1.2, 2013-07-07
* @date    2013-01-04
* @brief   测试 flsInqPoint.c 的文件。
*          模拟一条一条存储的情况。
		到sector末尾end=0xX FF条时, (以下3条在代码里有 同字符标注)
			1:擦除nextSector + Jdg; end 不变；若head==nextSectorHead,head+=1Sector;
			2:写0xX FF条     + Jdg; end = nextSectorHead;
			3:写head         + Jdg; end = 0xX 10. 
		//若power off + “1:擦除”未执行, Jdg end = 0xX FF，head不变;
		//若power off + “2:写0xX FF条”未执行, Jdg end = 0xX FF，head = nextSectorHead;
		//若power off + “3:写head”未执行, Jdg end = 0xX 00，head = nextSectorHead;

* 	已测试，4sector OK. 2013.7.6
* 	已测试，2sector OK. 2013.7.6
*    已测试，2sector, 1Sector= 0x100.  OK. 2013.7.6
******************************************************************************/
#include  "sim2_flsInqPoit.h"

#include  "incSysCommon.h"
#include  "strFlsAdrDef.h"
#include  "flsAdrCalculate.h"
// #include  "strDevice.h"
// #include  "fls_Interface.h"
#include  "flsInqPoint.h"
//#include "incFile.h"	

/*=================  ================================================*/

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

#if U_SYS_Test_Flash_InqPoint == 1
		
/******************************************************************************
* FUNC: //
******************************************************************************/
U32 test_sim_fls_ByteMax = U_SimFlsPoit_flsItem_ByteMax;
U32 test_sim_Sector_MAX      = U_SimFlsPoit_Sector_MAX;
U32 test_sim_Item_1Sector    = U_SimFlsPoit_Item_1Sector;
U32 test_sim_Item_MAX        = U_SimFlsPoit_Item_MAX;


/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

U32 test_Head; //按条数算
U32 test_End;

U32 test_pointHead; // test_Head*U_SimFlsPoit_1ItemBytes
U32 test_pointEnd;
U32 rdHead;
U32 rdEnd;
BOOL test_bResult;

U32 test_sequItem; //条数,指向next空地址。
U32 test_sequItm_Stop = ~0; //仿真断点 着重条数N 。
U32 test_bPointError;
U32 test_bAdrEqual;

U8 test_bSecEndDisp;
U8 test_step;


//应该每次存储，比较指针。
void sim_FlsInqPoit_Que_Test(void)
{

U8 mFlsItem = U_SimFlsPoit_FlsItemCls;

	getFlsItem_Addr(mFlsItem, U_SimFlsPoit_Part, &stSimFlsItemAdr);
	
	//---------------
	test_bPointError = FALSE; 
	test_initDat_AllHave();
	if(!sim_jdgPoint())
	{
		test_bPointError = TRUE; //ERROR 一直设断点。
	}
	
	//---------------
	test_bSecEndDisp = FALSE;
	test_step = ~0;

	test_Head = 0;
	test_End = 0;
	test_pointHead = 0;
	test_pointEnd = 0;
	test_initDat_AllSpace();	
	test_sequItem = 0;	
	
	test_bPointError = FALSE;
	test_bAdrEqual = FALSE;
	test_sequItm_Stop = test_sim_Item_MAX -1;
	while(1)
	{
		//断点的地址：
		if(test_sequItem == test_sequItm_Stop)
		{
			test_bAdrEqual = TRUE; //条数断点
		}
		
		//判断指针
		if(!sim_jdgPoint())
		{
			test_bPointError = TRUE; //ERROR 一直设断点。
		}
		sim_nextAdr();
	}
}


/******************************************************************************
* FUNC: //
******************************************************************************/
static void sim_nextAdr(void)
{
U32 mSect;
U32 mItmInSect;
	
		sim_cacuSectItem(test_sequItem, &mSect, &mItmInSect);
		//判断 地址接近sector end:
		if(test_bSecEndDisp)
		{
			// 2:写0xX FF条     + Jdg; end = nextSectorHead;
			if(test_step == 1)
			{
				sim_AddOne(test_sequItem); //sector 最后一条
				//adr++:
				test_sequItem = sim_adr_inc(test_sequItem);
				sim_endPoint_inc();
				
				test_step++;
			}
			// 3:写head         + Jdg; end = 0xX 10. 
			else if(test_step == 2)
			{
				test_initDat_head_set1(mSect);
				//adr++:
				test_sequItem = sim_adr_inc(test_sequItem);
				sim_endPoint_inc();
				
				test_bSecEndDisp = FALSE;
				test_step = ~0;
			}
		}
		else
		{
			// 1:擦除nextSector + Jdg; end 不变；若head==nextSectorHead,head+=1Sector;
			if(mItmInSect == (U_SimFlsPoit_Item_1Sector - 1))
			{
				test_bSecEndDisp = TRUE;
				test_step = 0;
				sim_erase_next_sector(mSect);
				//可以试着再erase next.next sector.
				
				//不加 sim_endPoint_inc();
				
				test_step++;
			}
			else
			{
				sim_AddOne(test_sequItem);
				//adr++:
				test_sequItem = sim_adr_inc(test_sequItem);
				sim_endPoint_inc();
			}
			
		}
}
/******************************************************************************
* FUNC: //
******************************************************************************/
static BOOL sim_jdgPoint(void)
{
TFlsQueuePoint_st stHeadEnd;
	
	test_bResult = flsInq_1Cls_JdgPoint(U_SimFlsPoit_Part, U_SimFlsPoit_FlsItemCls,
						&stHeadEnd);
	
	rdHead = stHeadEnd.headAdr;
	rdEnd  = stHeadEnd.endAdr;
	
	test_pointHead = U_SimFlsPoit_AdrS + test_Head * U_SimFlsPoit_1ItemBytes;
	test_pointEnd  = U_SimFlsPoit_AdrS + test_End  * U_SimFlsPoit_1ItemBytes;
	
	return ((rdHead == test_pointHead) && (rdEnd == test_pointEnd));
}

/******************************************************************************
* FUNC: //
******************************************************************************/
static U32 sim_adr_inc(U32 mAdr)
{
	mAdr++;
	if(mAdr >= U_SimFlsPoit_Item_MAX)
	{
		mAdr = 0;
	}
	return mAdr;
}

static void sim_endPoint_inc(void)
{
	
	test_End += 1;
	if(test_End >= U_SimFlsPoit_Item_MAX)
	{
		test_End = 0;
	}
}


static BOOL sim_cacuSectItem(U32 mAdr, U32 *pSec, U32 *pItmInSect)
{
	if(mAdr >= U_SimFlsPoit_Item_MAX)
	{
		return FALSE;
	}
	
	*pSec       = mAdr / U_SimFlsPoit_Item_1Sector;
	*pItmInSect = mAdr % U_SimFlsPoit_Item_1Sector;
	return TRUE;
}

/******************************************************************************
* FUNC: //
******************************************************************************/
static void sim_AddOne(U32 store_sequItm)
{
U32 mSect;
U32 mItmInSect;

	if(!sim_cacuSectItem(store_sequItm, &mSect, &mItmInSect))
	{
		return;
	}
	
	vSimFlsData[mSect][mItmInSect] = 1;  //1表示有数据。
	
}

static void sim_erase_next_sector(U32 mNowSect)
{
U32 mNextSect;

	mNextSect = mNowSect + 1;
	if(mNextSect >= U_SimFlsPoit_Sector_MAX)
	{
		mNextSect = 0;
	}
	test_initDat_sectX_clr0(mNextSect);
	
	if(test_Head == (mNextSect * U_SimFlsPoit_Item_1Sector))
	{
		test_Head += U_SimFlsPoit_Item_1Sector;
		if(test_Head >= U_SimFlsPoit_Item_MAX)
		{
			test_Head = 0;
		}
	}
}


/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
//----------------------------------------------------------------------


BOOL sim_FlsInqPoit_b_1Item_OK(U8 chip, U32 mAdr)
{
U32 mSimSect;
U32 item;
chip = chip;

	
	if(sim_cacuSect_fromFlsAdr(mAdr, &mSimSect))
	{
		item = FlsItm_adr_inSect_itmSequ(mAdr, U_SimFlsPoit_FlsItemCls, U_SimFlsPoit_1ItemBytes);
		return bSim_item_have(mSimSect, item);
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

/******************************************************************************
* FUNC: //
*   IN:
*  OUT:
******************************************************************************/



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


/******************************************************************************
* FUNC: //
******************************************************************************/
static void test_initDat_sectX_set1(U32 mSect)
{
U32 item;

	if(mSect >= U_SimFlsPoit_Sector_MAX)
		return;
	test_initDat_head_set1(mSect);
	for(item=1; item<U_SimFlsPoit_Item_1Sector; item++)
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
	for(item=1; item<U_SimFlsPoit_Item_1Sector; item++)
	{
		test_initDat_item_clr0(mSect, item);
	}
}
/******************************************************************************
* FUNC: //
******************************************************************************/


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


//-----------------------------------------
static void test_initDat_item_set1(U32 mSect, U32 item)
{
	if(mSect >= U_SimFlsPoit_Sector_MAX)
		return;
	vSimFlsData[mSect][item] = U_SimFlsPoit_signHave;
	
}
static void test_initDat_item_clr0(U32 mSect, U32 item)
{
	if(mSect >= U_SimFlsPoit_Sector_MAX)
		return;
	vSimFlsData[mSect][item] = U_SimFlsPoit_signSpace;
}
static BOOL bSim_item_have(U32 mSect, U32 item) //item=0对应地址0
{
	if(mSect >= U_SimFlsPoit_Sector_MAX)
		return FALSE;
	if(item >= U_SimFlsPoit_Item_1Sector)
		return FALSE;
	return (vSimFlsData[mSect][item] == U_SimFlsPoit_signHave);
}


/******************************************************************************
* FUNC: // END
*   IN:
*  OUT: 
******************************************************************************/
#endif //U_SYS_Test_Flash_InqPoint
