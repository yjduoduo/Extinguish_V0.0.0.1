/**********************************************************************
* $Id$		nandflash_HY27US081G2A.c			2011-06-02
*//**
* @file		nandflash_HY27US081G2A.c
* @brief	This c file contains all functions support for Nand Flash 
*			SamSung HY27US081G2A
* @version	1.0
* @date		02. June. 2011
* @author	NXP MCU SW Application Team
* 
* Copyright(C) 2011, NXP Semiconductor
* All rights reserved.
*
***********************************************************************
* Software that is described herein is for illustrative purposes only
* which provides customers with programming information regarding the
* products. This software is supplied "AS IS" without any warranties.
* NXP Semiconductors assumes no responsibility or liability for the
* use of the software, conveys no license or title under any patent,
* copyright, or mask work right to the product. NXP Semiconductors
* reserves the right to make changes in the software without
* notification. NXP Semiconductors also make no representation or
* warranty that such application will be suitable for the specified
* use without further testing or modification.
**********************************************************************/
 
#include "nandflash_hy27uf081g2a.h"
#include "lpc177x_8x_emc.h"
#include "lpc177x_8x_clkpwr.h"
#include "lpc177x_8x_pinsel.h"
#include "lpc177x_8x_timer.h"

//uint8_t InvalidBlockTable[NANDFLASH_NUMOF_BLOCK];

/*********************************************************************//**
 * @brief 		Ready/Busy check, no timeout, basically, R/B bit should
 * 				once to bail out from this routine
 * @param[in]	None
 * @return 		None
 **********************************************************************/
void HY271G_WaitForReady( void )
{
	uint32_t i;
	for (i=0; i<256; i++)
		if (!( FIO2PIN & (1 << 21) ))
			break;	/* from high to low once */
	while( !(FIO2PIN & (1 << 21)) );	/* from low to high once */
	return;
}

/*********************************************************************//**
 * @brief 		Initialize external NAND FLASH memory
 * @param[in]	None
 * @return 		None
 **********************************************************************/

//#define EMC_StaticConfig_PB				              ((uint32_t )(1 << 7))
//#define EMC_StaticConfig_MW_16BITS              (EMC_StaticConfig_MW(1)) 
 
/* StaticConfig register EMC: Memory width 8bit . */
//#define EMC_StaticConfig_MW_8BITS		(EMC_StaticConfig_MW(0))

void HY271G_Init( void )
{
	uint32_t i;
	TIM_TIMERCFG_Type TIM_ConfigStruct;
	LPC_EMC_TypeDef *pEMC = LPC_EMC;
	/**************************************************************************
	* Initialize EMC for NAND FLASH
	**************************************************************************/
	//EMC_Init();

	pEMC->Control = EMC_Control_E;
	/*
	pEMC->Config = 0;
	pEMC->StaticExtendedWait = 150-1;

	pEMC->StaticConfig1 = 1 << 8;	// 使能扩展等待
	pEMC->StaticWaitWen1 = 0x1f;
	pEMC->StaticWaitOen1 = 0x1f;
	pEMC->StaticWaitRd1 = 0x1f;
	pEMC->StaticWaitPage1 = 0x1f;
	pEMC->StaticWaitWr1 = 0x1f;
	pEMC->StaticWaitTurn1 = 0x1f;
	*/

	EMC_StaMemConfigMW (1,EMC_STATIC_CFG_MW_8BITS);//EMC_StaticConfig_MW_8BITS

	EMC_StaMemConfigPB(1,EMC_CFG_BYTELAND_READ_BITSLOW);//EMC_StaticConfig_PB

	EMC_SetStaMemoryParameter(1, EMC_STA_MEM_WAITWEN, EMC_StaticWaitWen_WAITWEN(2/*0x1f 2*/));

	EMC_SetStaMemoryParameter(1, EMC_STA_MEM_WAITOEN, EMC_StaticWaitOen_WAITOEN(2/* 0 2*/));

	EMC_SetStaMemoryParameter(1, EMC_STA_MEM_WAITRD, EMC_StaticWaitwr_WAITWR(6));//6

	EMC_SetStaMemoryParameter(1, EMC_STA_MEM_WAITPAGE, EMC_StaticwaitPage_WAITPAGE(0x1f));

	EMC_SetStaMemoryParameter(1, EMC_STA_MEM_WAITWR, EMC_StaticWaitwr_WAITWR(0x1f));

	EMC_SetStaMemoryParameter(1, EMC_STA_MEM_WAITTURN, EMC_StaticWaitTurn_WAITTURN(0x1f));

	// Init GPIO pin
	PINSEL_ConfigPin(2,21,0);
	FIO2DIR &= ~(1<<21);

    // init timer
	TIM_ConfigStruct.PrescaleOption = TIM_PRESCALE_USVAL;
	TIM_ConfigStruct.PrescaleValue	= 1;

	// Set configuration for Tim_config and Tim_MatchConfig
	TIM_Init(LPC_TIM0, TIM_TIMER_MODE,&TIM_ConfigStruct);

  	// wait 2ms
	TIM_Waitms(2);

	/* assume all blocks are valid to begin with */
	for ( i = 0; i < NANDFLASH_NUMOF_BLOCK; i++ )
	{
		  InvalidBlockTable[i] = 0;
	}  
	return;
}

/*********************************************************************//**
 * @brief 		Issue Reset command to NAND FLASH memory
 * @param[in]	None
 * @return 		None
 **********************************************************************/
void HY271G_Reset( void )
{
	volatile uint8_t *pCLE;

	/* Reset NAND FLASH  through NAND FLASH command */
	pCLE = HY271G_CLE;
	*pCLE = HY27_RESET;

	TIM_Waitms(2);
	return;
}

/*********************************************************************//**
 * @brief 		Read status from NAND FLASH memory
 * @param[in]	Cmd	command for read operation, should be:
 * 					-  HY27_PAGE_PROGRAM_1
 *					-  HY27_BLOCK_ERASE_1
 *					-  HY27_READ_1
 * @return 		Status, could be:
 *				- TRUE: pass
 *				- FALSE: Failure
 **********************************************************************/
Bool HY271G_ReadStatus(uint32_t Cmd)
{
	volatile uint8_t *pCLE;
	volatile uint8_t *pDATA;
	uint8_t StatusData;

	pCLE  = HY271G_CLE;
	pDATA = HY271G_DATA;

	*pCLE = HY27_READ_STATUS;

#if (_CUR_USING_NANDFLASH == _RUNNING_NANDFLASH_K9F1G08U0C)
	while ( (*pDATA & 0xC0) != 0xC0 );
#else
	/* Wait until bit 5 and 6 are 1, READY, bit 7 should be 1 too, not protected */
	/* if ready bit not set, it gets stuck here */
	while ( (*pDATA & 0xE0) != 0xE0 );
#endif

	StatusData = *pDATA;

	switch (Cmd)
	{
		case HY27_PAGE_PROGRAM_1:
		case HY27_BLOCK_ERASE_1:
		  	if (StatusData & 0x01)	/* Erase/Program failure(1) or pass(0) */
				return(FALSE);
		  	else
				return(TRUE);

		case HY27_READ1_2:				/* bit 5 and 6, Read busy(0) or ready(1) */
		  	return(TRUE);

		default:
		  	break;
	}

	return(FALSE);
}
/*********************************************************************//**
 * @brief 		Read ID from external NAND FLASH memory
 * @param[in]	None
 * @return 		ID value
 **********************************************************************/
uint32_t HY271G_ReadId( void )
{
	uint8_t a, b, c, d;
	volatile uint8_t *pCLE;
	volatile uint8_t *pALE;
	volatile uint8_t *pDATA;

	pCLE  = HY271G_CLE;
	pALE  = HY271G_ALE;
	pDATA = HY271G_DATA;

	*pCLE = HY27_READ_ID;
	*pALE = 0;

	a = *pDATA;
	b = *pDATA;
	c = *pDATA;
	d = *pDATA;

	return ((a << 24) | (b << 16) | (c << 8) | d);
}

/*********************************************************************//**
 * @brief 		Erase the whole NAND FLASH memory block based on the
 *				block number
 * @param[in]	blockNum	number of block that will be erased, should
 *				be in range: 0 .. 1023
 * @return 		Erase status, could be:
 * 					- TRUE: pass
 *					- FALSE: failure
 **********************************************************************/
Bool HY271G_BlockErase( uint32_t blockNum )
{
	volatile uint8_t *pCLE;
	volatile uint8_t *pALE;
	uint32_t rowAddr;

	pCLE  = HY271G_CLE;
	pALE  = HY271G_ALE;

	rowAddr = blockNum * NANDFLASH_PAGE_PER_BLOCK;

	*pCLE = HY27_BLOCK_ERASE_1;
	*pALE = (uint8_t)(rowAddr & 0x00FF);			/* column address low */
	*pALE = (uint8_t)((rowAddr & 0xFF00) >> 8);	/* column address high */
	*pCLE = HY27_BLOCK_ERASE_2;

	HY271G_WaitForReady();

	return(HY271G_ReadStatus(HY27_BLOCK_ERASE_1));
}

/*********************************************************************//**
 * @brief 		This routine is used to check if the block is valid or
 *				not.
 * @param[in]	None
 * @return 		Checking status, could be:
 * 					- TRUE: all blocks are valid
 *					- FALSE: invalid block is found, an initial invalid
 *						     table will be created
 **********************************************************************/
Bool HY271G_ValidBlockCheck( void )
{
//	volatile uint8_t *pCLE;
//	volatile uint8_t *pALE;
//	volatile uint8_t *pDATA;
	uint32_t block, page;
	Bool retValue = TRUE;
	//uint32_t curAddr, tmp;

	uint8_t data[16];

//	pCLE  = HY271G_CLE;
//	pALE  = HY271G_ALE;
//	pDATA = HY271G_DATA;

	for ( block = 0; block < NANDFLASH_NUMOF_BLOCK; block++ )
	{
		for ( page = 0; page < 2; page++ )
		{
			/* Check column address 2048 at first page and second page */
			HY271G_PageReadFromAddr(block, page, NANDFLASH_RW_PAGE_SIZE, data, 16);

			if(data[0] != 0xFF)
			{
				// found invalid block number, mark block number in the invalid
				// block table
				InvalidBlockTable[block] = 1;

				//At least one block is invalid
				retValue = FALSE;
			}
		}
	}

	return(retValue);
}

/*********************************************************************//**
 * @brief 		Write a full page of program into NAND flash based on the
 *				page number, write up to 2112 bytes of data at a time.
 * @param[in]	pageNum		number of page that will be programmed, should
 * 				be in range: 0..63
 * @param[in]	blockNum	number of block that will be programmed, should
 * 				be in range: 0..1023
 * @param[in]	bufPtr		pointer to the buffer that contain data will be
 * 				programmed in flash memory
 * @return 		Program status, could be:
 * 					- TRUE: success
 * 					- FALSE: fail
 **********************************************************************/
Bool HY271G_PageProgram(uint32_t blockNum, uint32_t pageNum,	uint32_t addrInPage, uint8_t* bufPtr, uint32_t size)
{
 	 volatile uint8_t *pCLE;
 	 volatile uint8_t *pALE;
 	 volatile uint8_t *pDATA;
//	uint32_t rowNum, colNum;
//	uint32_t curAddr = 0, sizeBk;
   uint32_t rowNum;
	 uint32_t colNum=addrInPage;
   uint32_t sizeBk;
	
	 HY271G_WaitForReady();
	
	 pCLE  = HY271G_CLE;
	 pALE  = HY271G_ALE;
	 pDATA = HY271G_DATA;
	
	//Get data from the current address in the page til the end of the page
	if (size + addrInPage >= NANDFLASH_PAGE_FSIZE)
		size = NANDFLASH_PAGE_FSIZE - addrInPage;
	// rowNum是A12-A27
 	rowNum = blockNum * NANDFLASH_PAGE_PER_BLOCK + pageNum;
	*pCLE = HY27_PAGE_PROGRAM_1;
	*pALE = colNum & 0xFF;
	*pALE = (colNum >> 8); 
 	*pALE = rowNum & 0xFF;
 	*pALE = rowNum >> 8;

 	sizeBk = size;
	while (sizeBk--)
	{
		*pDATA = *bufPtr++; 
	}

	*pCLE = HY27_PAGE_PROGRAM_2;
	
	HY271G_WaitForReady();

	return( HY271G_ReadStatus( HY27_PAGE_PROGRAM_1 ) );
}

//随机写数据区，不处理隐藏区
Bool HY271G_PageProgramData(uint32_t blockNum, uint32_t pageNum,	uint32_t addrInPage, uint8_t* bufPtr, uint32_t size) 
{
 	 volatile uint8_t *pCLE;
 	 volatile uint8_t *pALE;
 	 volatile uint8_t *pDATA;
 
   uint32_t rowNum;
   uint32_t sizeBk; 
	 uint32_t colNum=addrInPage&0x7ff;
	
	 pCLE  = HY271G_CLE;
	 pALE  = HY271G_ALE;
	 pDATA = HY271G_DATA;
	
	//Get data from the current address in the page til the end of the page
	if (size + addrInPage >= NANDFLASH_PAGE_FSIZE)
		size = NANDFLASH_PAGE_FSIZE - addrInPage;
	// rowNum是A12-A27
 	rowNum = blockNum * NANDFLASH_PAGE_PER_BLOCK + pageNum;
	
	*pCLE = HY27_PAGE_PROGRAM_1; 
	*pALE = 0;
	*pALE = 0; 
 	*pALE = (uint8_t)(rowNum & 0xFF);
 	*pALE = (uint8_t) (rowNum >> 8);
	
	*pCLE = NAND_CMD_RANDOM_WRITE; 
	*pALE = (uint8_t)(colNum & 0xFF);
 	*pALE = (uint8_t) (colNum >> 8)& 0xFF; 
 	sizeBk = size;
	while (sizeBk--)
	{
		*pDATA = *bufPtr++; 
	} 
	*pCLE = HY27_PAGE_PROGRAM_2; 
	HY271G_WaitForReady(); 
	return( HY271G_ReadStatus( HY27_PAGE_PROGRAM_1 ) );
}

/*********************************************************************//**
 * @brief 		Read the whole NAND FLASH memory page based on the
 *				page number, the data will be stored in the pointer
 *				to the buffer.
 * @param[in]	pageNum		number of page that will be read, should
 * 				be in range: 0..63
 * @param[in]	blockNum	number of block that will be read, should
 * 				be in range: 0..1023
 * @param[in]	bufPtr		pointer to the buffer that contain data will be
 * 				read from flash memory
 * @return 		Read status, could be:
 * 					- TRUE: success
 * 					- FALSE: fail
 **********************************************************************/
Bool HY271G_PageRead( uint32_t pageNum, uint32_t blockNum, uint8_t *bufPtr )
{
	//return (HY271G_PageReadFromBeginning(pageNum, blockNum, bufPtr) != 0);
	  if(HY271G_PageReadFromBeginning(pageNum, blockNum, bufPtr))
		{
			  return FALSE;
		}
		else
		{
			  return TRUE;
		}
	  //return (!HY271G_PageReadFromBeginning(pageNum, blockNum, bufPtr));
}

/*********************************************************************//**
 * @brief 		Read the whole NAND FLASH memory page based on the
 *				page number, the data will be stored in the pointer
 *				to the buffer.
 * @param[in]	pageNum		number of page that will be read, should
 * 				be in range: 0..63
 * @param[in]	blockNum	number of block that will be read, should
 * 				be in range: 0..1023
 * @param[in]	bufPtr		pointer to the buffer that contain data will be
 * 				read from flash memory
 * @return 		number of byte(s) read til the end of the page
 **********************************************************************/
int HY271G_PageReadFromBeginning(uint32_t blockNum, uint32_t pageNum, uint8_t* bufPtr)
{
	return (HY271G_PageReadFromAddr(blockNum, pageNum, 0, bufPtr, NANDFLASH_PAGE_FSIZE));
}

/*********************************************************************//**
 * @brief 		Read the whole NAND FLASH memory page based on the
 *				page number, the data will be stored in the pointer
 *				to the buffer.
 * @param[in]	blockNum	number of block that will be read, should
 * 							be in range: 0..1023
 * @param[in]	pageNum		number of page that will be read, should
 * 				be in range: 0..63
 * @param[in]	addrInPage	the address in NandFlash to be read,
 * 							calculated from the beginning of page
 * @param[in]	bufPtr		pointer to the buffer that contain data will be
 * 							read from flash memory
 * @param[in]	size	the number of byte(s) to be read and stored to the buffer
 * @return 		number of byte(s) read til the end of the page
 **********************************************************************/
int HY271G_PageReadFromAddr(uint32_t blockNum, uint32_t pageNum,	uint32_t addrInPage, uint8_t* bufPtr, uint32_t size)
{
	volatile uint8_t *pCLE;
	volatile uint8_t *pALE;
	volatile uint8_t *pDATA;
  
	uint32_t rowNum; 
	uint32_t  sizeBk;
	
	HY271G_WaitForReady();
	pCLE  = HY271G_CLE;
	pALE  = HY271G_ALE;
	pDATA = HY271G_DATA;
	
	//Get data from the current address in the page til the end of the page
	if (size + addrInPage >= NANDFLASH_PAGE_FSIZE)
		size = NANDFLASH_PAGE_FSIZE - addrInPage;
	// rowNum是A12-A27
	rowNum = blockNum * NANDFLASH_PAGE_PER_BLOCK + pageNum;
	*pCLE = HY27_READ1;
	*pALE = addrInPage & 0xFF;
	*pALE =(addrInPage >> 8);
	*pALE = rowNum & 0xFF;
	*pALE = rowNum >> 8;
	*pCLE = HY27_READ1_2;
	
	HY271G_WaitForReady();
 	sizeBk = size;
	while (size--)
	{
		*bufPtr = *pDATA;
		bufPtr++;
	}
 	HY271G_WaitForReady();
 	return sizeBk; 
}

//随机读取数据 
int HY271G_PageReadDataFromAddr(uint32_t blockNum, uint32_t pageNum,
													uint32_t addrInPage, uint8_t* bufPtr, uint32_t size)
{
	volatile uint8_t *pCLE;
	volatile uint8_t *pALE;
	volatile uint8_t *pDATA;
 
	uint32_t rowNum; 
	uint32_t  sizeBk; 
  uint32_t colNum=addrInPage&0x7ff;
	
	
	pCLE  = HY271G_CLE;
	pALE  = HY271G_ALE;
	pDATA = HY271G_DATA;
	
	//Get data from the current address in the page til the end of the page
	if (size + addrInPage >= NANDFLASH_PAGE_FSIZE)
		size = NANDFLASH_PAGE_FSIZE - addrInPage;
	// rowNum是A12-A27
	rowNum = blockNum * NANDFLASH_PAGE_PER_BLOCK + pageNum;
	*pCLE = HY27_READ1; 
  *pALE = 0;
	*pALE = 0; 
 	*pALE = (uint8_t)(rowNum & 0xFF);
 	*pALE = (uint8_t) (rowNum >> 8);
	*pCLE = HY27_READ1_2;	
	HY271G_WaitForReady();
	
	
	*pCLE = NAND_CMD_RANDOM_READ_1st;  
 	*pALE = (uint8_t)(colNum & 0xFF);
 	*pALE = (uint8_t) (colNum >> 8)& 0xFF;
	*pCLE = NAND_CMD_RANDOM_READ_2st;   
	sizeBk = size;
	while (sizeBk--)
	{
		*bufPtr = *pDATA;
		 bufPtr++;
	}  
 	return size; 
}

int HY271G_Random_Read(uint32_t pageNum,	uint32_t addrInPage, uint8_t* bufPtr, uint32_t size)
{
	  volatile uint8_t *pCLE;
	  volatile uint8_t *pALE;
	  volatile uint8_t *pDATA;
	
	
/*FlashComand  = NAND_CMD_READ_1st;
	FlashAddress = 0;
	FlashAddress = 0;
	FlashAddress = paddr&0xff;
	FlashAddress = (paddr>>8)&0xff;
	FlashAddress = (paddr>>16)&0xff;
	FlashComand  = NAND_CMD_READ_2st;      
	detect_nand_busy();

	FlashComand  = NAND_CMD_RANDOM_READ_1st;
	FlashAddress = offset&0xff; //写入页内偏移地址
	FlashAddress = (offset>>8)&0xff; 
	FlashComand  = NAND_CMD_RANDOM_READ_2st;
*/ 
		uint32_t  sizeBk; 
 
		pCLE  = HY271G_CLE;
		pALE  = HY271G_ALE;
		pDATA = HY271G_DATA;  
	 
		*pCLE = NAND_CMD_RANDOM_READ_1st;
		HY271G_WaitForReady();
	
		*pALE = (uint8_t)(addrInPage & 0xFF);
		*pALE = (uint8_t)((addrInPage >> 8)& 0x07);  
		*pCLE = NAND_CMD_RANDOM_READ_2st;
	
	HY271G_WaitForReady();
 	sizeBk = size;
	while (sizeBk--)
	{
		*bufPtr = *pDATA;
		bufPtr++;
	}
 	HY271G_WaitForReady();
 	return size;  
	
	
}








