#define __fls_Interface_C__
/******************************************************************************
* @file    fls_Interface.c
* @author  yx
* @version V1.0
* @date    2012-01-05
* @brief   flash接口函数.实际hd flash的接口。
* @slave   "hwEx21_SST39vf800A"   
* 
******************************************************************************/
#include  "fls_Interface.h"

#include  "incSysCommon.h"
#include  "flsStoreBytesDef.h"

#include  "hwEx21_SST39vf800A.h"
#include  "tmrTick.h"

#include  "hw00_CallBack.h"
// extern void CallBack_RunInFlashWait(void);

//#include "incFile.h"	


/*================= 常数 ============================================*/

/*================= 结构定义 ========================================*/

/*================= 私有结构变量声明 ================================*/


typedef struct{
	U8 bOpeaIng;
	U8 opeaType; 	//emFlashOpeaType
}TFlashStatus_st;

TFlashStatus_st stFlashStatus[U_SST39VF900A_CHIP_MAX];


	 
enum emFlashOpeaType{
	U_FLASH_EraseChip_TYPE = 1,
	U_FLASH_EraseBlock_TYPE = 2,
	U_FLASH_EraseSector_TYPE = 3,
	
	U_FLASH_WriteByte_TYPE = 4,
		
	U_FLASH_Invalid_TYPE = 5
};
/*================= 公有函数声明 ====================================*/

/*================= 私有变量声明 ====================================*/
#ifdef  __fls_Interface_C__

static U8 vFlsBuf[U_FLASH_1_SECTOR];
#endif  //__fls_Interface_C__
/*================= 私有函数声明 ====================================*/
#ifdef  __fls_Interface_C__

BOOL flsHd_waitForIdle(U8 chip, U32 waitTimeMs);
// BOOL decompose_w25x80_adr(U32 address, U8 *pRtnBlock, U8 *pRtnSector);

void FlsHd_StopWrite(U8 chip); //防止在上次失败的情况下有新命令


// opeaType = emFlashOpeaType
void Flash_setOpeaIng(U8 chip, U8 opeaType);
void Flash_clrOpeaIng(U8 chip);
U8 bFlash_getOpeaIng(U8 chip);
#endif  //__fls_Interface_C__

/*=================  ================================================*/
		
/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

/******************************************************************************
* FUNC: //若在waitTimeMs期间完成操作，return; 否则等足waitTimeMs返回结论。
******************************************************************************/
BOOL flsHd_waitForIdle(U8 chip, U32 waitTimeMs)
{
	BOOL result = U_FAILED;
	
	SetTmrTickTask(TASK_Flash_Wait + chip, waitTimeMs);
	SetTmrTickTask(TASK_Flash_CheckInterval, TMR_Flash_CheckInterval);
	
	while(1)
	{
		if(GetTickTaskStatus(TASK_Flash_Wait + chip)) // 3
		{
			if(bNorFlash_Busy(chip)){  
				result = U_FAILED;
			}
			else{							//不忙
				result = U_SUCC;
			}
			break;
		}
		else
		{
			if(GetTickTaskStatus(TASK_Flash_CheckInterval)) // 6
			{
				if(bNorFlash_Idle(chip)){  //不忙
					result = U_SUCC;
					break;
				}
				
			}
		}
		CallBack_RunInFlashWait(); //需要按时exec.
	}
	KillTickTask(TASK_Flash_Wait + chip);
	KillTickTask(TASK_Flash_CheckInterval);
	FlsHd_StopWrite(chip);
	return result;
}

/******************************************************************************
* FUNC: // 
*   IN:
*  OUT: 
******************************************************************************/
U8 *pFlsHd_GetBufS(void)
{
	return &vFlsBuf[0];
}


void   FlsHd_All_Init(void)
{
	U8 chip;
	for(chip=0; chip<U_SST39VF900A_CHIP_MAX; chip++)
	{
		FlsHd_Init(chip);
	}
}

void   FlsHd_Init(U8 chip)
{
	if(chip < U_SST39VF900A_CHIP_MAX)
	{
		NorFlash_Init(chip);
	}
	
}
/******************************************************************************
* FUNC: // 
*   IN:
*  OUT: 
******************************************************************************/
U32 FlsHd_ByteMax_1Chip(U8 chip)
{
	return NOR_FLASH_SIZE;
}

U32 FlsHd_adrInSector(U8 chip, U32 mAdr)
{
	return Flash_adrInSector(mAdr);
}

U32 FlsHd_adrToSectorS(U8 chip, U32 mAdr)
{
	return Flash_adrToSectS(mAdr);
}


/******************************************************************************
* FUNC: //
*  OUT:emFlashOpeaState
******************************************************************************/

U8 FlsHd_NowOpeaState(U8 chip)
{
	if(!bFlash_getOpeaIng(chip))
	{
		return U_FLASH_NoOpea_STA;
	}
	
	if(bFlsHd_bOpeaSucc(chip))
	{
		FlsHd_StopWrite(chip);
		return U_FLASH_OpeaSucc_STA;
		//操作成功
	}
	
	if(bFlsHd_OpeaTimerArrived(chip))
	{
		FlsHd_StopWrite(chip);
		return U_FLASH_TimerOut_STA;
		//超时失败
	}
	else
	{
		return U_FLASH_WaitContinue_STA;
		//继续等待
	}
}


U8 bFlsHd_ReadAllow(U8 chip)
{
	if(chip < U_SST39VF900A_CHIP_MAX)
	{
		return bNorFlash_Idle(chip);
	}
	else
	{
		return FALSE;
	}
}



/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

BOOL bFlsHd_CheckIntervalArrived(void)
{
	return (GetTickTaskStatus(TASK_Flash_CheckInterval));
}


/******************************************************************************
* FUNC: //操作定时 是否arrived.
******************************************************************************/
BOOL bFlsHd_OpeaTimerArrived(U8 chip)
{
	if(chip >= U_SST39VF900A_CHIP_MAX)
	{
		return FALSE;
	}
	
	if(GetTickTaskStatus(TASK_Flash_Wait + chip))
	{
		return U_SUCC;
	}
	else
	{
		return U_FAILED;
	}
}




/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
// opeaType = emFlashOpeaType
void Flash_setOpeaIng(U8 chip, U8 opeaType)
{
	if(chip < U_SST39VF900A_CHIP_MAX)
	{
		stFlashStatus[chip].bOpeaIng = 1;
		stFlashStatus[chip].opeaType = opeaType;
	}
	
}

void Flash_clrOpeaIng(U8 chip)
{
	if(chip < U_SST39VF900A_CHIP_MAX)
	{
		stFlashStatus[chip].bOpeaIng = 0;
		stFlashStatus[chip].opeaType = U_FLASH_Invalid_TYPE;
	}
}


U8 bFlash_getOpeaIng(U8 chip)
{
	if(chip < U_SST39VF900A_CHIP_MAX)
	{
		return stFlashStatus[chip].bOpeaIng;
	}
	else
	{
		return 0;
	}
}


/******************************************************************************
* FUNC: // 
*   IN:
*  OUT: 
******************************************************************************/
BOOL bFlashChip_IsAllIdle(void)
{
	U8 chip;
	BOOL bSucc;
	
	for(chip=0; chip<U_SST39VF900A_CHIP_MAX; chip++)
	{
		if(!bFlash_getOpeaIng(chip))
		{
			continue;
		}
		
		if(!bFlsHd_CheckIntervalArrived())
		{
			return FALSE;
		}
		else
		{
			bSucc = (bFlsHd_bOpeaSucc(chip));
			if(bFlsHd_OpeaTimerArrived(chip))
			{
				FlsHd_StopWrite(chip);
				return bSucc;
			}
			else
			{
				if(bSucc)
				{
					FlsHd_StopWrite(chip);
					return TRUE;
				}
			}
			break;
		}
	}
	
	if(chip >= U_SST39VF900A_CHIP_MAX)
	{
		return TRUE;
	}
	return FALSE;
	
}

/******************************************************************************
* FUNC: //读hdStatus, 是否BUSY.
******************************************************************************/
BOOL bFlsHd_bOpeaSucc(U8 chip)
{
#if U_SYS_ForbidHardWare == U_Yes
	return TRUE;
#else
	if(chip >= U_SST39VF900A_CHIP_MAX)
	{
		return FALSE;
	}
	
	if(bNorFlash_Busy(chip))  //忙
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
#endif // U_SYS_ForbidHardWare
}



/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

 
/******************************************************************************
* FUNC: //防止在上次失败的情况下有新命令
******************************************************************************/
void FlsHd_StopWrite(U8 chip)
{
	if(chip >= U_SST39VF900A_CHIP_MAX)
	{
		return;
	}
	KillTickTask(TASK_Flash_Wait + chip);
	KillTickTask(TASK_Flash_CheckInterval);
	
	Flash_clrOpeaIng(chip);
}


/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/


/******************************************************************************
* FUNC: //
******************************************************************************/

BOOL FlsHd_EraseSect_FromAdr(U8 chip, U32 address, U8 bWaitForFinish)
{
	return FlsHd_EraseSector(chip, Flash_adrToSector(address), 
										bWaitForFinish);
}









/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
BOOL FlsHd_EraseChip(U8 chip, U8 bWaitForFinish)
{
	U8 result;
	
	if(chip >= U_SST39VF900A_CHIP_MAX)
	{
		return FALSE;
	}
	
	if(bFlash_getOpeaIng(chip))
	{
		FlsHd_StopWrite(chip);
	}
	
	Flash_setOpeaIng(chip, U_FLASH_EraseChip_TYPE);
	
	//----------------------------------<
	result = NorFlash_EraseChip(chip, bWaitForFinish); // erase 
	//---------------------------------->
	
	
	
	if(bWaitForFinish)
	{
		// result = flsHd_waitForIdle(chip, U_EE_WaitTimeMs_EraseChip);
		Flash_clrOpeaIng(chip);
		return result;
	}
	else
	{
		SetTmrTickTask(TASK_Flash_Wait + chip, 
					  U_Delay_Flash_WAIT_EraseChip_us/1000 + U_MyTickTmrCycle);
		SetTmrTickTask(TASK_Flash_CheckInterval, TMR_Flash_CheckInterval);
		return TRUE;
	}
}

/******************************************************************************
* FUNC: // 
*   IN:
*  OUT: 
******************************************************************************/
BOOL FlsHd_EraseBlock(U8 chip, U8 block, U8 bWaitForFinish)
{
	U8 result;
	
	if(chip >= U_SST39VF900A_CHIP_MAX)
	{
		return FALSE;
	}
	
	if(bFlash_getOpeaIng(chip))
	{
		FlsHd_StopWrite(chip);
	}
	
	Flash_setOpeaIng(chip, U_FLASH_EraseBlock_TYPE);
	
	//----------------------------------<
	result = NorFlash_EraseBlock(chip, block, bWaitForFinish);
	//---------------------------------->
	
	if(bWaitForFinish)
	{
		// result = flsHd_waitForIdle(chip, U_EE_WaitTimeMs_EraseBlock);
		
		Flash_clrOpeaIng(chip);
		return result;
	}
	else
	{
		SetTmrTickTask(TASK_Flash_Wait + chip, 
					  U_Delay_Flash_WAIT_EraseBlock_us/1000 + U_MyTickTmrCycle);
		SetTmrTickTask(TASK_Flash_CheckInterval, TMR_Flash_CheckInterval);
		return TRUE;
	}
	
	
}


/******************************************************************************
* FUNC: // 
*   IN:
*  OUT: 
******************************************************************************/
BOOL FlsHd_EraseSector(U8 chip, U8 sector, U8 bWaitForFinish)
{
	U8 result;
	
	
	if(chip >= U_SST39VF900A_CHIP_MAX)
	{
		return FALSE;
	}
	
	if(bFlash_getOpeaIng(chip))
	{
		FlsHd_StopWrite(chip);
	}
	
	Flash_setOpeaIng(chip, U_FLASH_EraseSector_TYPE);
	
	//----------------------------------<
	result = NorFlash_EraseSector(chip, sector, bWaitForFinish);
	//---------------------------------->
	
	if(bWaitForFinish)
	{
		// result = flsHd_waitForIdle(chip, U_EE_WaitTimeMs_EraseSector);
		
		Flash_clrOpeaIng(chip);
		return result;
	}
	else
	{
		SetTmrTickTask(TASK_Flash_Wait + chip, 
					  U_Delay_Flash_WAIT_EraseSector_us/1000 + U_MyTickTmrCycle);
		SetTmrTickTask(TASK_Flash_CheckInterval, TMR_Flash_CheckInterval);
		return TRUE;
	}
	
	
}

/******************************************************************************
* FUNC: //读n字节
*   IN: 存起始位置,接收个数(不包括地址),地址(3Bytes)
*  OUT: 
******************************************************************************/

void FlsHd_Read_1Sec(U8 chip, U8 *pStart, U32 address)
{
	address = FlsHd_adrToSectorS(chip, address);
	
	FlsHd_Read_nByte(chip, pStart, 
					 SECTOR_SIZE, 
					 address);
}

/******************************************************************************
* FUNC: // 
*   IN:
*  OUT: 
******************************************************************************/
void FlsHd_Read_nByte(U8 chip, U8 *pStart, U32 num, U32 address)
{
	NorFlash_ReadNBytes(chip, address, num, pStart);
}


/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

void FlsHd_Write_1Sec(U8 chip, U8 *pStart, U32 address,
					 U8 bWaitForFinish)
{
	address = Flash_adrToSectS(address);
	
	FlsHd_Write_nByte(chip, pStart, 
					 SECTOR_SIZE, 
					 address, 
					 bWaitForFinish);
}

/******************************************************************************
* FUNC: // 
*   IN:
*  OUT: 
******************************************************************************/

BOOL FlsHd_Write_nByte(U8 chip, U8 *pStart, U32 num, U32 address, 
					  U8 bWaitForFinish)
{
U32 delayUs;
U32 delayMs;
U8 result = U_FAILED;


	if(num > SECTOR_SIZE)
	{
		num = SECTOR_SIZE;
	}
	if(chip >= U_SST39VF900A_CHIP_MAX)
	{
		return FALSE;
	}
	
	if(bFlash_getOpeaIng(chip))
	{
		FlsHd_StopWrite(chip);
	}
	Flash_setOpeaIng(chip, U_FLASH_WriteByte_TYPE);
	
	//----------------------------------<
	
	result = NorFlash_WriteNBytes(chip, address, num, pStart);
	
	//---------------------------------->
	
	delayUs = U_Delay_Flash_WAIT_WriteWord_us;
	delayMs = delayUs / 1000;
	if(delayMs < U_MyTickTmrCycle)
	{
		delayMs = U_MyTickTmrCycle;
	}
	delayMs += U_MyTickTmrCycle; //加最小粒度
	
	
	delayMs += U_MyTickTmrCycle;
	delayMs += U_MyTickTmrCycle;
	
	if(bWaitForFinish)
	{
		result = flsHd_waitForIdle(chip, delayMs);
		
		Flash_clrOpeaIng(chip);
		return result;
	}
	else
	{
		SetTmrTickTask(TASK_Flash_Wait + chip, delayMs);
		SetTmrTickTask(TASK_Flash_CheckInterval, TMR_Flash_CheckInterval);
		result = U_SUCC;
	}
	
	return result;
	
}




/******************************************************************************
* FUNC: // END
*   IN:
*  OUT: 
******************************************************************************/
