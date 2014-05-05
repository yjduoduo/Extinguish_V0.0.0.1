#define __hw00_HdInt_C__
/******************************************************************************
* @file    hw00_HdInt.c
* @author  yx
* @version V1.0
* @date    2012-01-05
* @brief   Ӧ�ò���ã������жϡ�
		��Ӳ����ʼʹ�ã���Ҫ���� Notify_SysInt_Hd_Open();
* 
******************************************************************************/
#include  "hw00_HdInt.h"

#include  "HdInterface.h"
#include  "UartHd_Interface.h"
#include  "CanHd_Interface.h"
#include  "CanBufLib_ReDef.h"

// #include  "hw01_Timer.h"
// #include  "hw10_Can.h"
// #include  "hw11_Uart.h"

/*================= ���� ============================================*/

/*=================  ================================================*/
		
/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

void MyInt_Status_Init(void)
{
	U32 ulInterrupt;
	
	MyInt_All_Disable();
	
	for(ulInterrupt=0; ulInterrupt<U_Hd_Int_MAX; ulInterrupt++)
	{
		bSysIntDisable[ulInterrupt] = 0;
		// bSysIntHdOpen[ulInterrupt] = FALSE;
	}
	Notify_SysInt_Hd_AllClose();
}

/******************************************************************************
* FUNC: // 
*   IN:    ulInterrupt = emMySysIntId
*  OUT:  1=״̬�иı䡣 �޸ı�ʱע�⣬����������Ҫ���жϡ�
* Ӧ�ã�
	bCan0IntChange = MyInt_Disable(INT_CAN_iCan);
	if(bCan0IntChange)
	{
		MyInt_Enable(INT_CAN_iCan);
	}
******************************************************************************/
U8 MyInt_Disable(unsigned int ulInterrupt)
{
#if U_SYS_ForbidHardWare == U_Yes 
	return 1;
#else
	U8 nowNeedState;
	U8 bChanged = 0;
	
	if(ulInterrupt >= U_Hd_Int_MAX)
	{
		return bChanged;
	}
	else if(!bGet_SysInt_Hd_Open(ulInterrupt))
	{
		return bChanged;
	}
	
	switch(ulInterrupt)
	{
		case U_Hd_Int_iCAN:
			CanHd_IorE_Hd_Int_Disable(U_iCAN_ID);
			break;
			
		case U_Hd_Int_eCAN:
			CanHd_IorE_Hd_Int_Disable(U_eCAN_ID);
			break;
			
		case U_Hd_Int_UART_DownLoad:
			UartHd_Int_Disable(U_Uart_Download_ID);
			break;
			
			
		case U_Hd_Int_TIMER_SysTick:
			TimerHd_Int_Disable(U_Tmr_SysTick_ID);
			break;
			
		case U_Hd_Int_TIMER_NorFlash:
			TimerHd_Int_Disable(U_Tmr_NorFlash_ID);
			break;			
		
			
		default:
			break;
	}
	
	nowNeedState = 1;
	bChanged = ( (bSysIntDisable[ulInterrupt] == nowNeedState)? (0):(1) );
	bSysIntDisable[ulInterrupt] = nowNeedState;
	return bChanged;
#endif // U_SYS_ForbidHardWare
}



U8 MyInt_Enable(unsigned int ulInterrupt)
{
#if U_SYS_ForbidHardWare == U_Yes 
	return 1;
#else
	U8 nowNeedState;
	U8 bChanged = 0;
	
	if(ulInterrupt >= U_Hd_Int_MAX)
	{
		return bChanged;
	}
	else if(!bGet_SysInt_Hd_Open(ulInterrupt))
	{
		return bChanged;
	}
	
	switch(ulInterrupt)
	{
		case U_Hd_Int_iCAN:
			CanHd_IorE_Hd_Int_Enable(U_iCAN_ID);
			break;
			
		case U_Hd_Int_eCAN:
			CanHd_IorE_Hd_Int_Enable(U_eCAN_ID);
			break;
			
		case U_Hd_Int_UART_DownLoad:
			UartHd_Int_Enable(U_Uart_Download_ID);
			break;
			
			
		case U_Hd_Int_TIMER_SysTick:
			TimerHd_Int_Enable(U_Tmr_SysTick_ID);
			break;
			
		case U_Hd_Int_TIMER_NorFlash:
			TimerHd_Int_Enable(U_Tmr_NorFlash_ID);
			break;
			
			
		default:
			break;
	}
	
	nowNeedState = 0;
	bChanged = ( (bSysIntDisable[ulInterrupt] == nowNeedState)? (0):(1) );
	bSysIntDisable[ulInterrupt] = nowNeedState;
	return bChanged;
	
#endif // U_SYS_ForbidHardWare
}

/******************************************************************************
* FUNC: // 
******************************************************************************/

void MyInt_All_Enable(void)
{
#if U_SYS_ForbidHardWare == U_Yes 
#else
	U32 ulInterrupt;
	
	// IntMasterEnable();
	
	for(ulInterrupt=0; ulInterrupt<U_Hd_Int_MAX; ulInterrupt++)
	{
		// MyInt_Enable(ulInterrupt);
		if(bGet_SysInt_Hd_Open(ulInterrupt))
		{
			bSysIntDisable[ulInterrupt] = 0;
		}
	}
	
#endif // U_SYS_ForbidHardWare
}



void MyInt_All_Disable(void)
{
#if U_SYS_ForbidHardWare == U_Yes 
#else
	U32 ulInterrupt;
	
	// IntMasterDisable();
	
	for(ulInterrupt=0; ulInterrupt<U_Hd_Int_MAX; ulInterrupt++)
	{
		// MyInt_Disable(ulInterrupt);
		if(bGet_SysInt_Hd_Open(ulInterrupt))
		{
			bSysIntDisable[ulInterrupt] = 1;
		}
	}

#endif // U_SYS_ForbidHardWare
}



/******************************************************************************
* FUNC: // ����ɶ�ʹ�á�
	   //  ����Ƕ��ʹ�á�Ƕ��ʱע�Ᵽ���� mOpeaIntBits ���ô�
//ʾ��:

	U32 mOpeaIntBits;
	mOpeaIntBits = MyInt_AllDisable_RtnBits();
	//exec 
	MyInt_AllEnable_FromBits(mOpeaIntBits);
******************************************************************************/
U32 MyInt_AllDisable_RtnBits(void)
{
	U32 ulInterrupt;
	U32 mOpeaIntBits = 0;
	
	for(ulInterrupt=0; ulInterrupt<U_Hd_Int_MAX; ulInterrupt++)
	{
		if(!bGet_SysInt_Hd_Open(ulInterrupt))
		{
			continue;
		}
		if(bSysIntDisable[ulInterrupt])
		{
			continue;
		}
		
		MyInt_Disable(ulInterrupt);
		mOpeaIntBits |= (1 << ulInterrupt);
	}
	return mOpeaIntBits;
}

void MyInt_AllEnable_FromBits(U32 mOpeaIntBits)
{
	U32 ulInterrupt;
	U32 intBits = mOpeaIntBits;
	
	for(ulInterrupt=0; ulInterrupt<U_Hd_Int_MAX; ulInterrupt++)
	{
		if((intBits & (1 << ulInterrupt)) == 0)
		{
			continue;
		}
		
		MyInt_Enable(ulInterrupt);
	}
}

/******************************************************************************
* FUNC: // ����ɶ�ʹ�á�
	   //  ����Ƕ��ʹ�á�Ƕ��ʱע�Ᵽ���� mOpeaIntBits ���ô�
*   IN:
*  OUT:
* 2013.7.25�����䣬yx;
******************************************************************************/


U32 MyInt_N_Disable_RtnBits(U32 mOpeaIntBits)
{
	U32 ulInterrupt;
	U32 mRtnOpeaIntBits = 0;
	
	for(ulInterrupt=0; ulInterrupt<U_Hd_Int_MAX; ulInterrupt++)
	{
		if(!bGet_SysInt_Hd_Open(ulInterrupt))
			continue;
		if((mOpeaIntBits & (1 << ulInterrupt)) == 0) //��bit������
			continue;
		if(bSysIntDisable[ulInterrupt]) //�ѽ�ֹ�ж�
			continue;
		
		MyInt_Disable(ulInterrupt);
		mRtnOpeaIntBits |= (1 << ulInterrupt);
	}
	return mRtnOpeaIntBits;
}

void MyInt_N_Enable_FromBits(U32 mOpeaIntBits)
{
	U32 ulInterrupt;
	
	for(ulInterrupt=0; ulInterrupt<U_Hd_Int_MAX; ulInterrupt++)
	{
		if((mOpeaIntBits & (1 << ulInterrupt)) == 0)
		{
			continue;
		}
		
		MyInt_Enable(ulInterrupt);
	}
}


/******************************************************************************
* FUNC: // Ӳ��close״̬��������Ĵ������ᵼ��������(��freeScale K60оƬ��)
*   IN:
*  OUT:
******************************************************************************/
void Notify_SysInt_Hd_Open(unsigned int ulInterrupt)
{
	if(ulInterrupt >= U_Hd_Int_MAX)
	{
		return;
	}
	bSysIntHdOpen[ulInterrupt] = 1;
}

void Notify_SysInt_Hd_Close(unsigned int ulInterrupt)
{
	if(ulInterrupt >= U_Hd_Int_MAX)
	{
		return;
	}
	bSysIntHdOpen[ulInterrupt] = 0;
}

void Notify_SysInt_Hd_AllClose(void)
{
	U32 ulInterrupt;
	for(ulInterrupt=0; ulInterrupt<U_Hd_Int_MAX; ulInterrupt++)
	{
		bSysIntHdOpen[ulInterrupt] = 0;		
	}
}

U8 bGet_SysInt_Hd_Open(unsigned int ulInterrupt)
{
	if(ulInterrupt >= U_Hd_Int_MAX)
	{
		return 0;
	}
	return bSysIntHdOpen[ulInterrupt];
}


/******************************************************************************
* FUNC: //
******************************************************************************/



/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

