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

/*================= ���� ============================================*/


/*================= �ṹ���� ========================================*/

/*================= ˽�нṹ�������� ================================*/

/*================= ���к������� ====================================*/

/*================= ˽�к������� ====================================*/

/*=================  ================================================*/
		

/******************************************************************************
* FUNC: // Watch Dog :
*   IN:
*  OUT:
******************************************************************************/
uint32 bExtraNeedFeedDog;	//U_NEED_FEED_DOG_BITS �������ʱ���ӵ�

void WatchDog_AddSupviseBits(uint32 mDogTaskId)
{
	bExtraNeedFeedDog |= mDogTaskId;
}

void WatchDog_MoveawaySupviseBits(uint32 mDogTaskId)
{
	bExtraNeedFeedDog &= ~mDogTaskId;
}




/******************************************************************************
* FUNC: // Watch Dog : U_NEED_FEED_DOG_BITS ����ļ������
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

void checkWatchDog(void); //��⿴�Ź�

//
void Clear_MyWatchDog(void) //Ӳ���忴�Ź���
{ 
	if(bMyHdHaveIniSign(U_SysTask_WatchDog_ID))
	{
		// һ����dog:
		// bHaveFeedDog = ~0;
		// bExtraNeedFeedDog = 0;
		
		checkWatchDog();
	}
}


/******************************************************************************
* FUNC: //
******************************************************************************/

void checkWatchDog(void) //��⿴�Ź�
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
	
	//�жϣ�
	if((bHaveFeedDog & mNeedBits) == mNeedBits) //��Ҫ��λ��Ϊ1ʱ���Ż��忴�Ź���
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

