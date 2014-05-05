#define __HdInterface_C__
/******************************************************************************
* @file    HdInterface.c
* @author  yx
* @version V1.0
* @date    2012-01-05
* @brief   ��ֹӦ�ó������ hw ��hwEx
		���е��ж���ں�����Ӧ �� "hw00_CallBack.c" ����
		�й�cpu�Ĳ��ܹ���module�ļĴ�������CpuReg.c�
* 
******************************************************************************/
#include  "HdInterface.h"


//#include "..\\s00Prj\\incFile.h"	
#include  "hw00_HdInt.h"
#include  "hw01_Timer.h"
#include "lpc177x_8x_wwdt.h" 

#include  "tmrTick.h"

// #include  "phIoScan.h"
extern void ExeInInt_IoLedKeyScan(void);


#include  "phWatchDogTask.h"
// extern  void SetWatchDogBits(uint32 mDogTaskId);
// #define U_Dog_SysTimer_tick_Bit  1

/*================= ���� ============================================*/

/*================= �ṹ���� ========================================*/

/*================= ˽�нṹ�������� ================================*/

/*================= ���к������� ====================================*/

/*================= ˽�к������� ====================================*/

/*=================  ================================================*/
		
/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

typedef struct{
	U8 tmr_id;
	U8 hdPhInt_id;  // hw00_hdInt.h
	U8 tmrDriveId;  // hw01_timer
}TTmrProp_st;

const TTmrProp_st cstTmrPeriId[U_TMR_ID_MAX+1] = 
{
	{U_Tmr_SysTick_ID,  U_Hd_Int_TIMER_SysTick, U_TmrDrive_1}, // 
		
	{U_Tmr_NorFlash_ID, U_Hd_Int_TIMER_NorFlash, U_TmrDrive_0},  // TIM_Waitmsʱ�á�
	
	// default , �ο� U_TMR_ID_Default
	{U_Tmr_SysTick_ID,  U_Hd_Int_TIMER_SysTick, U_TmrDrive_1}
};
	
	
	
// Ӧ�ò� �� Ӳ�� ��uartId �Ķ�Ӧ��ϵ��
U8 GetTmrDriveId_FromTmrId(U8 tmr_id)
{
	if(tmr_id >= U_TMR_ID_MAX)
	{
		return cstTmrPeriId[U_TMR_ID_MAX].tmrDriveId;
	}
	return cstTmrPeriId[tmr_id].tmrDriveId;
	
}
U8 GetTmrId_FromTmrPeriId(U8 tmrDriveId)
{
U8 tmr_id;

	for(tmr_id=0; tmr_id<U_TMR_ID_MAX; tmr_id++)
	{
		if(cstTmrPeriId[tmr_id].tmrDriveId == tmrDriveId)
		{
			break;
		}
	}
	if(tmr_id >= U_TMR_ID_MAX)
	{
		return cstTmrPeriId[U_TMR_ID_Default].tmr_id;
	}
	return tmr_id;
	
}

void MyTimer_IntrHander(U8 tmrDriveId) //�ж� Handle
{
U8 tmr_id;
	tmr_id = GetTmrId_FromTmrPeriId(tmrDriveId);
	switch(tmr_id)
	{
		case U_Tmr_SysTick_ID:
			MyTickTimer_IntrHander();
			break;
			
		case U_Tmr_NorFlash_ID:
			NorFlashTimer_IntrHander();
			break;
			
		default:
			break;
	}
}


/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

// Int:
void TimerHd_Int_Enable(U8 tmr_id) // emTmrLogicId
{
	TimerRegi_Int_Enable(cstTmrPeriId[tmr_id].tmrDriveId);
}

void TimerHd_Int_Disable(U8 tmr_id)
{
	TimerRegi_Int_Disable(cstTmrPeriId[tmr_id].tmrDriveId);
}

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

void MyTickTimer_Init(void)
{
U8 hdPhInt_id;

	hdPhInt_id = cstTmrPeriId[U_Tmr_SysTick_ID].hdPhInt_id;
	if(bGet_SysInt_Hd_Open(hdPhInt_id))
	{
		MyTickTimer_Close();
	}
	//hdInit
	Init_CTimeDrive(cstTmrPeriId[U_Tmr_SysTick_ID].tmrDriveId,
				   U_MyTickTmrCycleUs);
	
	//
	Notify_SysInt_Hd_Open(hdPhInt_id);
	MyInt_Enable(hdPhInt_id);
}

/******************************************************************************
* FUNC: //
******************************************************************************/
void TickTimer_HdInt(U8 bAllow)  //�ж� ����/��ֹ
{
U8 hdPhInt_id;

	hdPhInt_id = cstTmrPeriId[U_Tmr_SysTick_ID].hdPhInt_id;
	if(bAllow == TRUE)
	{
		MyInt_Enable(hdPhInt_id);
	}
	else
	{
		MyInt_Disable(hdPhInt_id);
	}
}

/******************************************************************************
* FUNC: //
// IO useLib:125.9 us; IO�Լ���55.6 us;
******************************************************************************/
void MyTickTimer_IntrHander(void) //�ж� Handle
{
	SetWatchDogBits(U_Dog_SysTimer_tick_Bit);
	
	IntrAddTickMs(U_MyTickTmrCycle);
	
	ExeInInt_IoLedKeyScan();
}

/******************************************************************************
* FUNC: //
******************************************************************************/
void MyTickTimer_Close(void)
{
U8 hdPhInt_id;
	
	hdPhInt_id = cstTmrPeriId[U_Tmr_SysTick_ID].hdPhInt_id;
	if(!bGet_SysInt_Hd_Open(hdPhInt_id))
	{
		return;
	}
	MyInt_Disable(hdPhInt_id);
	
	Close_CTimeDrive(cstTmrPeriId[U_Tmr_SysTick_ID].tmrDriveId);
	
	Notify_SysInt_Hd_Close(hdPhInt_id);
}

/******************************************************************************
* FUNC: // 
*   IN:
*  OUT: 
******************************************************************************/

static U8 mNorFlashTmrArrived;

void NorFlashTimer_Init(U32 mTmrUs)
{
U8 hdPhInt_id;

	hdPhInt_id = cstTmrPeriId[U_Tmr_NorFlash_ID].hdPhInt_id;
	if(bGet_SysInt_Hd_Open(hdPhInt_id))
	{
		NorFlashTimer_Close();
	}
	//hdInit
	Init_CTimeDrive(cstTmrPeriId[U_Tmr_NorFlash_ID].tmrDriveId,
				   mTmrUs);
	
	//
	Notify_SysInt_Hd_Open(hdPhInt_id);
	MyInt_Enable(hdPhInt_id);
	
	mNorFlashTmrArrived = FALSE;
}


/******************************************************************************
* FUNC: //
******************************************************************************/

void NorFlashTimer_IntrHander(void) //�ж� Handle
{
	mNorFlashTmrArrived = TRUE;
}

BOOL bNorFlashTimer_Arrived(void) //
{
	return mNorFlashTmrArrived;
}
/******************************************************************************
* FUNC: //
******************************************************************************/
void NorFlashTimer_Close(void)
{
U8 hdPhInt_id;
	
	hdPhInt_id = cstTmrPeriId[U_Tmr_NorFlash_ID].hdPhInt_id;
	if(!bGet_SysInt_Hd_Open(hdPhInt_id))
	{
		return;
	}
	MyInt_Disable(hdPhInt_id);
	
	Close_CTimeDrive(cstTmrPeriId[U_Tmr_NorFlash_ID].tmrDriveId);
	
	Notify_SysInt_Hd_Close(hdPhInt_id);
	
}



/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
/*  WDTCװ��3�볬ʱֵ           */
#define WDT_TIMEOUT     (3000000UL)   // ��λ��us

void MyDog_Init(void)
{
	//LPC177x_8x: �̶�500K ʱ�ӣ�
	  WWDT_Init(WDT_TIMEOUT);         /* ��ʼ��WDT                    */

    WWDT_Enable(ENABLE);

    WWDT_SetMode(WWDT_RESET_MODE, ENABLE);
    
    WWDT_Start(WDT_TIMEOUT);

    WWDT_Feed();  
	
}


void MyDog_Feed(void)
{
	  WWDT_Feed();  
}

/******************************************************************************
* FUNC: // END
*   IN:
*  OUT: 
******************************************************************************/

