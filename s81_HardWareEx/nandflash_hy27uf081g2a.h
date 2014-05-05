/**********************************************************************
* $Id$		nandflash_HY27US081G2A.h			2011-06-02
*//**
* @file		nandflash_HY27US081G2A.h
* @brief	The header file contains all macro definitions and function
*			prototypes support for external Nand Flash SamSung HY27US081G2A
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

/* Peripheral group ----------------------------------------------------------- */
/** @defgroup Nandflash_HY27US081G2A NandFlash HY27US081G2A
 * @ingroup LPC177x_8xCMSIS_Board_Support
 * @{
 */

#ifndef __NF_HY27US081G2A_H__
#define __NF_HY27US081G2A_H__


#include  "prjCompileCon.h"	
 
#include  "LPC177x_8x.h"
#include  "lpc177x_8x_emc.h"

/*****************************************************************************
 * Defines and typedefs
 ****************************************************************************/
 // 适用于A24连接ALE, A25连接CLE
//#define HY271G_CLE   ((volatile uint8_t *)	0x92000000)
//#define HY271G_ALE	 ((volatile uint8_t *)	0x91000000)

#define HY271G_CLE   ((volatile uint8_t *)	0x91000000)
#define HY271G_ALE	 ((volatile uint8_t *)	0x92000000)
 

#define HY271G_DATA  ((volatile uint8_t *)	0x90000000)

#define NANDFLASH_BASE_ADDR			0x00000000

#define NANDFLASH_INVALIDBLOCK_CHECK_COLUMM			(2048+0)

// total 1024 blocks in a device
#define NANDFLASH_NUMOF_BLOCK		  1024	// 1024

// total pages in a block
#define NANDFLASH_PAGE_PER_BLOCK	64

#define NANDFLASH_RW_PAGE_SIZE		2048	// bytes/page  0x800

#define NANDFLASH_SPARE_SIZE		64 		//bytes/page  0x40

#define NANDFLASH_PAGE_FSIZE		(NANDFLASH_RW_PAGE_SIZE + NANDFLASH_SPARE_SIZE)// 

#define NANDFLASH_BLOCK_RWSIZE	(NANDFLASH_RW_PAGE_SIZE * NANDFLASH_PAGE_PER_BLOCK)//0x20000

#define NANDFLASH_BLOCK_FSIZE 	(NANDFLASH_PAGE_FSIZE * NANDFLASH_PAGE_PER_BLOCK)


#define NANDFLASH_ADDR_COLUMM_POS		0
#define NANDFLASH_ADDR_ROW_POS			16

#define HY27_ID					        0xADF1801D	/* Byte 3 and 2 only */

#define HY27_READ1            	0x00
#define HY27_READ1_2           	0x30

#define NAND_CMD_RANDOM_WRITE         0x85  //随机写
#define NAND_CMD_RANDOM_READ_1st      0x05
#define NAND_CMD_RANDOM_READ_2st      0xe0


#define HY27_READ_ID           	0x90
#define HY27_RESET             	0xFF
#define HY27_PAGE_PROGRAM_1   	0x80
#define HY27_PAGE_PROGRAM_2   	0x10
#define HY27_BLOCK_ERASE_1     	0x60
#define HY27_BLOCK_ERASE_2     	0xD0
#define HY27_READ_STATUS       	0x70


#define HY27_BUSY              	(1 << 6)
#define HY27_OK                	(1 << 0)

#define FIO_BASE_ADDR		0x20098000
#define FIO2DIR        (*(volatile unsigned long *)(FIO_BASE_ADDR + 0x40))
#define FIO2MASK       (*(volatile unsigned long *)(FIO_BASE_ADDR + 0x50))
#define FIO2PIN        (*(volatile unsigned long *)(FIO_BASE_ADDR + 0x54))
#define FIO2SET        (*(volatile unsigned long *)(FIO_BASE_ADDR + 0x58))
#define FIO2CLR        (*(volatile unsigned long *)(FIO_BASE_ADDR + 0x5C))


#define ERR_RETVAL_OK				(0)
#define ERR_RETVAL_ERROR			(-1)
#define ERR_RETVAL_WRONG_INPUT		(-2)

/*
#ifdef __ICCARM__
  #pragma location="Nand_TabRAM"
  static __no_init uint8_t InvalidBlockTable[NANDFLASH_NUMOF_BLOCK];
#endif
#ifdef __CC_ARM
  static uint8_t InvalidBlockTable[NANDFLASH_NUMOF_BLOCK] __attribute__ ((section ("Nand_TabRAM"), zero_init));
#endif
#ifdef _WINDOWS
  static uint8_t InvalidBlockTable[NANDFLASH_NUMOF_BLOCK];
#endif
*/
static uint8_t InvalidBlockTable[NANDFLASH_NUMOF_BLOCK];

//static uint8_t InvalidBlockTable[NANDFLASH_NUMOF_BLOCK] __attribute__ ((section ("Nand_TabRAM"), zero_init));

extern void HY271G_Init( void );
extern void HY271G_Reset( void );
extern void HY271G_WaitForReady( void );	/* same as CheckBusy, no time out */
extern uint32_t HY271G_ReadId( void );
extern Bool HY271G_ReadStatus( uint32_t Cmd );
extern Bool HY271G_BlockErase( uint32_t blockNum );
extern Bool HY271G_ValidBlockCheck( void );
extern Bool HY271G_PageProgram(uint32_t blockNum, uint32_t pageNum,	uint32_t addrInPage, uint8_t* bufPtr, uint32_t size);
extern Bool HY271G_PageRead( uint32_t pageNum, uint32_t blockNum, uint8_t *bufPtr );

extern int HY271G_PageReadFromBeginning(uint32_t block, uint32_t page, uint8_t* bufPtr);
extern int HY271G_PageReadFromAddr(uint32_t blockNum, uint32_t pageNum,
													uint32_t addrInPage, uint8_t* bufPtr, uint32_t size);
													
extern int HY271G_PageReadDataFromAddr(uint32_t blockNum, uint32_t pageNum,
													uint32_t addrInPage, uint8_t* bufPtr, uint32_t size);		

extern Bool HY271G_PageProgramData(uint32_t blockNum, uint32_t pageNum,	uint32_t addrInPage, uint8_t* bufPtr, uint32_t size);


extern int HY271G_Random_Read(uint32_t pageNum,	uint32_t addrInPage, uint8_t* bufPtr, uint32_t size);



#endif /* __NF_HY27US081G2A_H__ */

/**
 * @}
 */
