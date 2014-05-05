#define __phWatchDogTask_C__
/******************************************************************************
* @file    phWatchDogTask.c
* @author  yx
* @version V1.0
* @date    2012-01-05
* @brief   
* 
******************************************************************************/
#include  "phWatchDogTask.h"


//#include "..\\s00Prj\\incFile.h"	

#include  "sysStatus.h"
#include  "sysDef.h"

#include  "HdInterface.h"
// extern void MyDog_Init(void);
// extern void MyDog_Feed(void);

/*================= 常数 ============================================*/


/*================= 结构定义 ========================================*/

/*================= 私有结构变量声明 ================================*/

/*================= 公有函数声明 ====================================*/

/*================= 私有函数声明 ====================================*/

/*=================  ================================================*/
		

/******************************************************************************
* FUNC: // Watch Dog :
*   IN:
*  OUT:
******************************************************************************/
uint32 bExtraNeedFeedDog;	//U_NEED_FEED_DOG_BITS 以外的临时监视点

void WatchDog_AddSupviseBits(uint32 mDogTaskId)
{
	bExtraNeedFeedDog |= mDogTaskId;
}

void WatchDog_MoveawaySupviseBits(uint32 mDogTaskId)
{
	bExtraNeedFeedDog &= ~mDogTaskId;
}




/******************************************************************************
* FUNC: // Watch Dog : U_NEED_FEED_DOG_BITS 以外的检测任务。
*   IN:
*  OUT:
******************************************************************************/


void SetWatchDogBits(uint32 mDogTaskId)
{
	bHaveFeedDog |= mDogTaskId;
}

/******************************************************************************
* FUNC: // 
*   IN:
*  OUT:
******************************************************************************/

void checkWatchDog(void); //检测看门狗

//
void Clear_MyWatchDog(void) //硬件清看门狗。
{ 
	if(bMyHdHaveIniSign(U_SysTask_WatchDog_ID))
	{
		// 一定清dog:
		// bHaveFeedDog = ~0;
		// bExtraNeedFeedDog = 0;
		
		checkWatchDog();
	}
}


/******************************************************************************
* FUNC: //
******************************************************************************/

void checkWatchDog(void) //检测看门狗
{
	uint32 mNeedBits = U_NEED_FEED_DOG_BITS;
	
	// if(Get_Iap_OtherBoardIapIng())
	// {
		// mNeedBits = U_Dog_SysTimer_tick_Bit | U_Dog_CanBuf_Rcv_Bit;
	// }
	if(bSysStaReseting())
	{
		mNeedBits = U_Dog_SysTimer_tick_Bit;
	}
	else
	{
		mNeedBits = U_NEED_FEED_DOG_BITS | bExtraNeedFeedDog;
	}
	
	//判断：
	if((bHaveFeedDog & mNeedBits) == mNeedBits) //需要的位都为1时，才会清看门狗。
	{
		MyDog_Feed();
					
		bHaveFeedDog = 0;
	}
}
	

/******************************************************************************
* FUNC: //
******************************************************************************/



/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

