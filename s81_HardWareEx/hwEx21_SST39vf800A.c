#define __hwEx21_SST39vf800A_C__

/**********************************************************************
* $Id$		norflash_sst39vf800A.c			2011-06-02
*//**
* @file		norflash_sst39vf800A.c
* @brief	Contains all functions support for NOR Flash SamSung
*			SST39VF3201
* @version	1.0
* @date		02. June. 2011
* @author	NXP MCU SW Application Team
* 
* Copyright(C) 2011, NXP Semiconductor
* All rights reserved.
*
***********************************************************************/
#include "lpc177x_8x_emc.h"
// #include "lpc177x_8x_clkpwr.h"
// #include "lpc177x_8x_pinsel.h"
// #include "lpc177x_8x_timer.h"


/******************************************************************************
* @file    hwEx21_SST39vf800A.c
* @author  yx
* @version V1.0
* @date    2013-08-26 
* @brief   NorFlash SST39vf800A 驱动	
* @master   "fls_Interface"   
* 
******************************************************************************/
#include  "hwEx21_SST39vf800A.h"

#include  "hwEx10_PinDef.h"

#include  "HdInterface.h"
// extern void NorFlashTimer_Init(U32 mTmrUs);
// extern BOOL bNorFlashTimer_Arrived(void); //
// extern void NorFlashTimer_Close(void);

#include  "hw00_CallBack.h"
// extern void CallBack_RunInFlashWait(void);

//#include "incFile.h"	

/******************************************************************************
SST39VF:

写：地址总线上的地址在WE#或CE#的下降沿(无论哪一个后产生下降沿)被锁存;
写：数据总线上的数据在WE#或CE#的上升沿(无论哪一个先产生上升沿)被锁存.
读操作由CE#和OE#控制只有两者都为低电平时系统才能从器件的输出管脚获得数据

SST39LF/VF160以字形式进行编程编程前包含字的扇区必须完全擦除编程操作分为三步：
第一步执行三字节装载时序.用于软件数据保护；
第二步装载字地址和字数据.在字编程操作中,地址在CE#或WE#的下降沿(不论哪一个后产生下降沿)锁存. 
	数据在CE#或WE#的上升沿(不论哪一个先产生上升沿)锁存.
第三步执行内部编程操作,该操作在第4个WE#或CE#的上升沿出现，
	(不论哪一个先产生上升沿)之后启动.编程操作一旦启动,将在20us内完成.
	见图4和5的WE#和CE#控制的编程操作时序图以及图16的流程图.
	在编程操作过程中,只有数据#查询位和触发位的读操作有效.
	在内部编程操作过程中,主机可以自由执行其它任务.该过程中发送的任何命令都被忽略.
即：写期间不支持读数据操作。

写操作状态检测：
	软件检测包括2个状态位：数据#查询位(DQ7)和触发位(DQ6).
	写结束检测模式在WE#的上升沿后使能,
	WE#的上升沿用来启动内部的编程或擦除操作.

命令时序		第1个总线		第2个总线		第2个总线		第2个总线		第2个总线			第2个总线	
			写周期		写周期		写周期		写周期		写周期			写周期
			地址	数据		地址	数据		地址	数据		地址	数据		地址	数据			地址	数据
字编程		5555H	AAH	2AAAH	55H	5555H	A0H	地址	数据				
扇区擦除		5555H	AAH	2AAAH	55H	5555H	80H	5555H	AAH	2AAAH	55H		扇区(Ams~A11)	30H
块擦除		5555H	AAH	2AAAH	55H	5555H	80H	5555H	AAH	2AAAH	55H		块(Ams~A15)	50H
芯片擦除		5555H	AAH	2AAAH	55H	5555H	80H	5555H	AAH	2AAAH	55H		5555H	10H
软件ID入口	5555H	AAH	2AAAH	55H	5555H	90H						
CFI查询入口	5555H	AAH	2AAAH	55H	5555H	98H						
软件ID/CFI退出	5555H	AAH	2AAAH	55H	5555H	F0H						

SST39LF/VF800A Device ID = 2781H, is read with A0 = 1.
******************************************************************************/


/*================= 常数 ============================================*/

/*================= 结构定义 ========================================*/

/*================= 私有结构变量声明 ================================*/

int32_t volatile timerdev = 0;
/*================= 公有函数声明 ====================================*/

/*================= 私有函数声明 ====================================*/

// adr 包含 CS信息:
#define M8(adr)  (*((volatile unsigned char  *) (adr)))
#define M16(adr) (*((volatile unsigned short *) (adr)))
#define M32(adr) (*((volatile unsigned long  *) (adr)))  
/*=================  ================================================*/
		

/*********************************************************************//**
 * @brief 		Delay
 * @param[in]	delayCnt Delay value
 * @return 		None
 **********************************************************************/

static void delayCnt(uint32_t delayCnt)
{
	uint32_t i;

	for ( i = 0; i < delayCnt; i++ );
	return;
}

static void delayUs_tillFinish(uint32_t mUs)
{
	NorFlashTimer_Init(mUs); //us 
	while(!bNorFlashTimer_Arrived())
	{}
	NorFlashTimer_Close();
}

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

void EMCInit( void )
{
	LPC_SC->PCONP      |= 0x00000800;

	LPC_EMC->Control = 0x00000001;

	LPC_EMC->Config  = 0x00000000;

	IniPinFunc_EMC_Data();
	IniPinFunc_EMC_Addr();
	// IniPinFunc_EMC_CtrlLine();


	LPC_EMC->StaticConfig0   = 0x00000081;
	LPC_EMC->StaticConfig1   = 0x00000081;
	LPC_EMC->StaticConfig2   = 0x00000081;
	LPC_EMC->StaticConfig3   = 0x00000081;

	LPC_EMC->StaticWaitWen0  = 0x00000000; /* ( n + 1 ) -> 1 clock cycles */
	LPC_EMC->StaticWaitOen0  = 0x00000000; /* ( n ) -> 0 clock cycles */
	LPC_EMC->StaticWaitRd0   = 0x00000006; /* ( n + 1 ) -> 7 clock cycles */
	LPC_EMC->StaticWaitPage0 = 0x00000000; /* ( n + 1 ) -> 1 clock cycles */
	LPC_EMC->StaticWaitWr0   = 0x00000005; /* ( n + 2 ) -> 7 clock cycles */
	LPC_EMC->StaticWaitTurn0 = 0x00000000; /* ( n + 1 ) -> 1 clock cycles */

	LPC_EMC->StaticWaitWen1  = 0x00000000; /* ( n + 1 ) -> 1 clock cycles */
	LPC_EMC->StaticWaitOen1  = 0x00000000; /* ( n ) -> 0 clock cycles */
	LPC_EMC->StaticWaitRd1   = 0x00000006; /* ( n + 1 ) -> 7 clock cycles */
	LPC_EMC->StaticWaitPage1 = 0x00000000; /* ( n + 1 ) -> 1 clock cycles */
	LPC_EMC->StaticWaitWr1   = 0x00000005; /* ( n + 2 ) -> 7 clock cycles */
	LPC_EMC->StaticWaitTurn1 = 0x00000000; /* ( n + 1 ) -> 1 clock cycles */

	LPC_EMC->StaticWaitWen2  = 0x00000000; /* ( n + 1 ) -> 1 clock cycles */
	LPC_EMC->StaticWaitOen2  = 0x00000000; /* ( n ) -> 0 clock cycles */
	LPC_EMC->StaticWaitRd2   = 0x00000006; /* ( n + 1 ) -> 7 clock cycles */
	LPC_EMC->StaticWaitPage2 = 0x00000000; /* ( n + 1 ) -> 1 clock cycles */
	LPC_EMC->StaticWaitWr2   = 0x00000005; /* ( n + 2 ) -> 7 clock cycles */
	LPC_EMC->StaticWaitTurn2 = 0x00000000; /* ( n + 1 ) -> 1 clock cycles */

	LPC_EMC->StaticWaitWen3  = 0x00000000; /* ( n + 1 ) -> 1 clock cycles */
	LPC_EMC->StaticWaitOen3  = 0x00000000; /* ( n ) -> 0 clock cycles */
	LPC_EMC->StaticWaitRd3   = 0x00000006; /* ( n + 1 ) -> 7 clock cycles */
	LPC_EMC->StaticWaitPage3 = 0x00000000; /* ( n + 1 ) -> 1 clock cycles */
	LPC_EMC->StaticWaitWr3   = 0x00000005; /* ( n + 2 ) -> 7 clock cycles */
	LPC_EMC->StaticWaitTurn3 = 0x00000000; /* ( n + 1 ) -> 1 clock cycles */


}


/******************************************************************************
* FUNC: // 
*   IN:
*  OUT: 
******************************************************************************/

/*********************************************************************//**
 * @brief 		Initialize external NOR FLASH memory
 * @param[in]	mChip < U_SST39VF900A_CHIP_MAX;
 * @return 		None
 **********************************************************************/

void NorFlash_Init(uint8_t mChip)
{
	//TIM_TIMERCFG_Type TIM_ConfigStruct;
	EMC_STATIC_MEM_Config_Type config;
	
	if(mChip >= U_SST39VF900A_CHIP_MAX)
	{
		return;
	}

	LPC_SC->PCONP      |= 0x00000800;

	LPC_EMC->Control = 0x00000001;

	LPC_EMC->Config  = 0x00000000;

	IniPinFunc_NorFlash_Data();
	IniPinFunc_NorFlash_Addr();
	IniPinFunc_NorFlash_CtrlLine();


	/**************************************************************************
	* Initialize EMC for NOR FLASH
	**************************************************************************/
	config.CSn = mChip;
	config.AddressMirror = 0;
	config.ByteLane = 1;
	config.DataWidth = 16;
	config.ExtendedWait = 0;
	config.PageMode = 0;
	config.WaitWEn = 2;
	config.WaitOEn = 2;
	config.WaitWr = 0x1f;
	config.WaitPage = 0x1f;
	config.WaitRd = 0x1f;
	config.WaitTurn = 0x1f;	
	StaticMem_Init(&config);

	// init timer
	//TIM_ConfigStruct.PrescaleOption = TIM_PRESCALE_USVAL;
	//TIM_ConfigStruct.PrescaleValue	= 1;

	// Set configuration for Tim_config and Tim_MatchConfig

	// TIM_Init(LPC_TIM0, TIM_TIMER_MODE,&TIM_ConfigStruct);
	// TIM_Waitms(100);
	// TIM_Waitms(10);
	
	delayUs_tillFinish(100 * 1000); // us 

	delayUs_tillFinish( 10 * 1000); // us 

	
}


/******************************************************************************
* FUNC: // 
*   IN:
*  OUT: 
******************************************************************************/
// 片选地址 + offsetAdr
volatile uint16_t *norFlash_Addr(uint8_t mChip, uint32_t offsetAdr)
{
	if(mChip >= U_SST39VF900A_CHIP_MAX)
	{
		mChip = U_SST39VF900A_Default;
	}
	
	return (volatile uint16_t *)(cstSST39VF900A_BaseAddr[mChip] 
									| ((offsetAdr)<<1)
								);
}
	

// Addr需要word 对齐，否则结果是高字节。
uint16_t norFlash_GetData(uint8_t mChip, uint32_t Addr)
{
	return M16(cstSST39VF900A_BaseAddr[mChip] | Addr);
}

void norFlash_SetData(uint8_t mChip, uint32_t Addr, uint16_t mWord)
{
	M16(cstSST39VF900A_BaseAddr[mChip] | Addr) = mWord;
}


/******************************************************************************
* FUNC: // 操作开始的命令字：
*   IN:
*  OUT: 
******************************************************************************/

void norFlashCommand_Erase(uint8_t mChip)
{
	volatile uint16_t *ip;
	
	// Start Erase  Command
	ip  = norFlash_Addr(mChip, 0x5555);  *ip = 0x00AA;
	ip  = norFlash_Addr(mChip, 0x2aaa);  *ip = 0x0055;
	ip  = norFlash_Addr(mChip, 0x5555);  *ip = 0x0080;
	ip  = norFlash_Addr(mChip, 0x5555);  *ip = 0x00AA;
	ip  = norFlash_Addr(mChip, 0x2aaa);  *ip = 0x0055;
}




void norFlashCommand_CheckIdIn(uint8_t mChip)
{
	volatile uint16_t *ip;
	
	/*  Issue the Software Product ID code to 39VF160   */
	ip  = norFlash_Addr(mChip, 0x5555);  *ip = 0x00AA;
	ip  = norFlash_Addr(mChip, 0x2aaa);  *ip = 0x0055;
	ip  = norFlash_Addr(mChip, 0x5555);  *ip = 0x0090;	
}


void norFlashCommand_CheckIdCfiOut(uint8_t mChip)
{
	volatile uint16_t *ip;
	
	/*  Issue the Software Product ID code to 39VF160   */
	ip  = norFlash_Addr(mChip, 0x5555);  *ip = 0x00AA;
	ip  = norFlash_Addr(mChip, 0x2aaa);  *ip = 0x0055;
	ip  = norFlash_Addr(mChip, 0x5555);  *ip = 0x00F0;	
}

void norFlashCommand_WrWord(uint8_t mChip)
{
	volatile uint16_t *ip;
	
	ip  = norFlash_Addr(mChip, 0x5555);  *ip = 0x00AA;
	ip  = norFlash_Addr(mChip, 0x2aaa);  *ip = 0x0055;
	ip  = norFlash_Addr(mChip, 0x5555);  *ip = 0x00A0;	
}

/*********************************************************************//**
 * @brief 		Toggle Bit check if the data is written or erased
 * @param[in]	Addr	address value
 * @param[in]	Data	expected data
 * @return 		Checking result, could be:
// *  OUT: emNorFlashCommResult: U_NorFlash_Comm_Succeed,  U_NorFlash_Comm_Failed
 **********************************************************************/

uint32_t toggleBitCheck(uint8_t mChip, uint32_t Addr, uint16_t Data )
{
	volatile uint16_t *ip;
	uint16_t temp1, temp2;
  
	NorFlashTimer_Init(cstPollWaitUs[U_POLL_WAIT_WriteWord]);

	while(!bNorFlashTimer_Arrived())
	{
		ip = norFlash_Addr(mChip, Addr);  temp1 = *ip;
		ip = norFlash_Addr(mChip, Addr);  temp2 = *ip;

		if ( (temp1 == temp2) && (temp1 == Data) )
		{
			NorFlashTimer_Close();
		 	return( U_NorFlash_Comm_Succeed );
		}
	}
	NorFlashTimer_Close();
	return ( U_NorFlash_Comm_Failed );
}

/******************************************************************************
* FUNC: // 
*   IN:
*  OUT: 
******************************************************************************/


/*********************************************************************//**
 * @brief 		Check ID from external NOR FLASH memory
 * @param[in]	mChip < U_SST39VF900A_CHIP_MAX;
 * @return 		Checking result, could be:
 * 					- TRUE: Correct
 *					- FALSE: Incorrect
 **********************************************************************/

uint32_t NorFlash_CheckID(uint8_t mChip)
{
uint16_t SST_id1, SST_id2;
volatile uint16_t *ip;
	
	if(mChip >= U_SST39VF900A_CHIP_MAX)
	{
		return FALSE;
	}

	/*  Issue the Software Product ID code to 39VF160   */
	norFlashCommand_CheckIdIn(mChip);	
	delayCnt(10);

	/* Read the product ID from 39VF160 */
	ip  = norFlash_Addr(mChip, 0x0000);  SST_id1 = *ip & 0x00FF;
	ip  = norFlash_Addr(mChip, 0x0001);  SST_id2 = *ip;

	/* Issue the Soffware Product ID Exit code thus returning the 39VF160 */
	/* to the read operating mode */
	norFlashCommand_CheckIdCfiOut(mChip);
	delayCnt(10);

	// PRINT_Log("SST_ID      Value %d   ,",SST_id1);
	// PRINT_Log("SST_39VF800 Value %d   ,",SST_id2);

	/* Check ID */
	if ((SST_id1 == SST_ID) && (SST_id2 ==SST_39VF160))
		return( TRUE );
	else
		return( FALSE );
}

/*********************************************************************//**
 * @brief 		Erase external NOR FLASH memory
 * @param[in]	mChip < U_SST39VF900A_CHIP_MAX;
 * @return 		None
 **********************************************************************/

int NorFlash_EraseChip(uint8_t mChip, uint8_t bWaitForFinish)
{
volatile uint16_t *ip;
uint8_t  result;
	
	if(mChip >= U_SST39VF900A_CHIP_MAX)
	{
		return U_NorFlash_Comm_Failed;
	}
	
	norFlashCommand_Erase(mChip);
	ip  = norFlash_Addr(mChip, 0x5555);  *ip = 0x0010;
	
	if(bWaitForFinish)
	{
		// Wait until Erase completed
		result = (Polling(mChip, (NOR_FLASH_SIZE-1), 
						U_POLL_WAIT_EraseChip)); 	
		// delayCnt(10000000);				/* Use timer 1 */
		
		return result;
	}
	else
	{
		return U_NorFlash_Comm_Succeed;
	}
}

/*********************************************************************//**
 * @brief 		Program one 16-bit data into external NOR FLASH memory
 *				This "uint16_t" for the external flash is 16 bits!!!
 * @param[in]	mChip < U_SST39VF900A_CHIP_MAX;
 * @param[in]	Addr	Address value < NOR_FLASH_SIZE
 * @param[in]	Data	data value
 * @return 		Program result, could be:
// *  OUT: emNorFlashCommResult: U_NorFlash_Comm_Succeed,  U_NorFlash_Comm_Failed
 **********************************************************************/

uint32_t NorFlash_Write1Word(uint8_t mChip, uint32_t Addr, 
										uint16_t Data)
{
volatile uint16_t *ip;
uint8_t  result;
	
	if(mChip >= U_SST39VF900A_CHIP_MAX)
	{
		return U_NorFlash_Comm_Failed;
	}
	if(Addr >= NOR_FLASH_SIZE)
	{
		return U_NorFlash_Comm_Failed;
	}
	
	norFlashCommand_WrWord(mChip);

	ip = norFlash_Addr(mChip, Addr);		/* Program 16-bit word */
	*ip = Data;
	
	result = ( toggleBitCheck(mChip, Addr, Data ) );		
	return result;
}


/******************************************************************************
 * Check if Program/Erase completed
 *    Parameter:      adr:  Block Start Address
 *    Return Value:   
// *  OUT: emNorFlashCommResult: U_NorFlash_Comm_Succeed,  U_NorFlash_Comm_Failed
******************************************************************************/

union fsreg {                  // Flash Status Register
	struct b  {
		unsigned int q0:1;
		unsigned int q1:1;
		unsigned int q2:1;
		unsigned int q3:1;
		unsigned int q4:1;
		unsigned int q5:1;
		unsigned int q6:1;
		unsigned int q7:1;
	} b;
	unsigned int v;
} fsr;

//unsigned long base_adr = cstSST39VF900A_BaseAddr[mChip];


/******************************************************************************
* FUNC: // 等待操作完成
*   IN:
*  OUT: emNorFlashCommResult: U_NorFlash_Comm_Succeed,  U_NorFlash_Comm_Failed
******************************************************************************/


static int Polling (uint8_t mChip, unsigned long adr, emPollWait mPollWait) 
{
	unsigned int q6;
	unsigned int bResult = U_NorFlash_Comm_Succeed;

	NorFlashTimer_Init(cstPollWaitUs[mPollWait]);

	// Check Toggle Bit
	fsr.v = norFlash_GetData(mChip, adr);
	do {
		q6 = fsr.b.q6;
		fsr.v = norFlash_GetData(mChip, adr);

		if(bNorFlashTimer_Arrived())
		{
			bResult = U_NorFlash_Comm_Failed;
			break;
		}
		CallBack_RunInFlashWait(); //等待期间可以执行1cycle常规处理。

	} while (fsr.b.q6 != q6);

	NorFlashTimer_Close();
	return (bResult);  // Done
}

/******************************************************************************
* FUNC: // flash状态，当两次读取的值相同时，idle.
*   IN:
*  OUT: TRUE, FALSE;
******************************************************************************/
static union fsreg   unState;
static unsigned int  unStaQ6;
int bNorFlash_Idle (uint8_t mChip)
{
	if(mChip >= U_SST39VF900A_CHIP_MAX)
	{
		return FALSE;
	}
	unState.v = norFlash_GetData(mChip, 0);
	unStaQ6 = unState.b.q6;
	unState.v = norFlash_GetData(mChip, 0);
	
	if(unState.b.q6 == unStaQ6)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

int bNorFlash_Busy (uint8_t mChip)
{
	if(bNorFlash_Idle(mChip))
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}



/******************************************************************************
* FUNC: // 
 * @param[in]	mChip < U_SST39VF900A_CHIP_MAX;
 * @param[in]	Addr	Address value < NOR_FLASH_SIZE
*  OUT: emNorFlashCommResult: U_NorFlash_Comm_Succeed,  U_NorFlash_Comm_Failed
******************************************************************************/

int NorFlash_EraseAdr_1Sector (uint8_t mChip, unsigned long adr,
										uint8_t bWaitForFinish) 
{
uint8_t  result;

	if(mChip >= U_SST39VF900A_CHIP_MAX)
	{
		return U_NorFlash_Comm_Failed;
	}
	if(adr >= NOR_FLASH_SIZE)
	{
		return U_NorFlash_Comm_Failed;
	}
	
	// Start Erase Sector Command
	norFlashCommand_Erase(mChip);
	norFlash_SetData(mChip, adr, 0x30);
	
	if(bWaitForFinish)
	{
		// Wait until Erase completed
		result = (Polling(mChip, adr, U_POLL_WAIT_EraseSector)); 
		
		return result;
	}
	else
	{
		return U_NorFlash_Comm_Succeed;
	}
}

int NorFlash_EraseSector(uint8_t mChip, uint32_t mSector, 
										uint8_t bWaitForFinish)
{
	return NorFlash_EraseAdr_1Sector(mChip, mSector * SECTOR_SIZE,
											bWaitForFinish);
}

/******************************************************************************
* FUNC: //
 * @param[in]	mChip < U_SST39VF900A_CHIP_MAX;
 * @param[in]	Addr	Address value < NOR_FLASH_SIZE
*  OUT: 
******************************************************************************/

int NorFlash_EraseAdr_1Block(uint8_t mChip, unsigned long adr,
									uint8_t bWaitForFinish)
{
uint8_t  result;

	if(mChip >= U_SST39VF900A_CHIP_MAX)
	{
		return U_NorFlash_Comm_Failed;
	}
	if(adr >= NOR_FLASH_SIZE)
	{
		return U_NorFlash_Comm_Failed;
	}
	
	
	// Start Erase Block Command
	norFlashCommand_Erase(mChip);
	norFlash_SetData(mChip, adr, 0x50);
	
	if(bWaitForFinish)
	{
		// Wait until Erase completed
		result = (Polling(mChip, adr, U_POLL_WAIT_EraseBlock));  
		
		return result;
	}
	else
	{
		return U_NorFlash_Comm_Succeed;
	}
}



int NorFlash_EraseBlock(uint8_t mChip, uint32_t mBlock,
										U8 bWaitForFinish)
{
	return NorFlash_EraseAdr_1Block(mChip, mBlock * BLOCK_SIZE,
										bWaitForFinish);
}

/******************************************************************************
* FUNC: //
 * @param[in]	mChip < U_SST39VF900A_CHIP_MAX;
 * @param[in]	Addr	Address value < NOR_FLASH_SIZE
			// Addr需要word 对齐，否则结果是高字节。
*   IN: sz bytes;  sz=byte个数若为奇数，则会进位至偶数。
*  OUT: 
******************************************************************************/

int NorFlash_WriteNBytes (uint8_t mChip, unsigned long adr, 
				unsigned long sz, unsigned char *buf) 
{
int i;
	
	if(mChip >= U_SST39VF900A_CHIP_MAX)
	{
		return U_NorFlash_Comm_Failed;
	}
	if((adr + sz) > NOR_FLASH_SIZE)
	{
		return U_NorFlash_Comm_Failed;
	}

	for (i = 0; i < ((sz+1)/2); i++)  
	{
		// Start Program Command
		norFlashCommand_WrWord(mChip);
		
		norFlash_SetData(mChip, adr, *((unsigned short *) buf));
		
		if (Polling(mChip, adr, U_POLL_WAIT_WriteWord) != U_NorFlash_Comm_Succeed) 
		{
			return (U_NorFlash_Comm_Failed);
		}
		else
		{
			buf += 2;
			adr += 2;
		}
	}
	
	return (U_NorFlash_Comm_Succeed);
}

/******************************************************************************
* FUNC: //
 * @param[in]	mChip < U_SST39VF900A_CHIP_MAX;
 * @param[in]	Addr	Address value < NOR_FLASH_SIZE
			// Addr需要word 对齐，否则结果是高字节。
*   IN:  sz bytes;  sz=byte个数若为奇数，则会进位至偶数。
*  OUT: 
******************************************************************************/

int NorFlash_ReadNBytes(uint8_t mChip, unsigned long adr, 
			   unsigned long sz, uint8 *buf)
{
	int i; 
	
	if(mChip >= U_SST39VF900A_CHIP_MAX)
	{
		return U_NorFlash_Comm_Failed;
	}
	if((adr + sz) > NOR_FLASH_SIZE)
	{
		return U_NorFlash_Comm_Failed;
	}
	
	for (i = 0; i < ((sz+1)/2); i++)  
	{
		*((unsigned short *) buf)= norFlash_GetData(mChip, adr);
		buf += 2;
		adr += 2;
	}
	return (U_NorFlash_Comm_Succeed);  
}






/******************************************************************************
* FUNC: // END
*   IN:
*  OUT: 
******************************************************************************/
