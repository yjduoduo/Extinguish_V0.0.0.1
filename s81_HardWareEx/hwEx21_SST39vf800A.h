#ifndef __hwEx21_SST39vf800A_H__
#define __hwEx21_SST39vf800A_H__
/******************************************************************************
* @file    hwEx21_SST39vf800A.h
* @author  yx
* @version V1.0
* @date    2013-08-26
* @brief   NorFlash SST39vf800A 驱动	
	      硬件以Word对齐操作。
		 函数接口是Byte方式。
* @master   "fls_Interface"   
* 
#include  "hwEx21_SST39vf800A.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

#include "lpc177x_8x_emc.h"
/*================= extern ============================================*/
#ifdef  __hwEx21_SST39vf800A_C__
#define EX_hwEx21_SST39vf800A
#else
#define EX_hwEx21_SST39vf800A extern 
#endif
/*================= 常数-芯片选择 ============================================*/
// CS 线决定的

enum emSst39vf800Chip{ // unsigned char mChip;
	U_SST39VF900A_U7 = 0, // CS0 NorFlash
	U_SST39VF900A_U9 = 1, // CS1 NandFlash
	U_SST39VF900A_U8 = 2  // CS2 NorFlash
};
#define U_SST39VF900A_CHIP_MAX    4

#define U_SST39VF900A_Default    U_SST39VF900A_U7 // CS0

#ifdef  __hwEx21_SST39vf800A_C__
const uint32_t cstSST39VF900A_BaseAddr[U_SST39VF900A_CHIP_MAX+1] = 
{
	0x80000000, // CS0 // 0x8000 0000 - 0x83FF FFFF
	0x90000000,
	0x98000000, // CS2 // 0x9000 0000 - 0x93FF FFFF
	0x9C000000, // CS3
	
	//default:
	0x80000000, // CS0 // 0x8000 0000 - 0x83FF FFFF
};

#endif // __hwEx21_SST39vf800A_C__
/*================= 常数-地址 ============================================*/
// SST39LF/VF800A： 8M bits = 1M * Bytes = 512K * 16bits.
// 512K Word = 0x200 * 0x400 *2 = 0x100 000 bytes;
#define NOR_FLASH_SIZE		0x00100000 

 // 32K Word= 0x20*0x400*2 bytes = 0x10 000 bytes 
#define BLOCK_SIZE		  0x00010000   

// 2K Word,    /* Must be 2048 words for 39VF160 */
#define SECTOR_SIZE		  0x001000  
  
#define cBlockSize      (BLOCK_SIZE)        //1块地址空间
#define cBlockSizeMask  (cBlockSize-1)    //1块地址空间

#define  NORFLASH_RW_PAGE_SIZE	 SECTOR_SIZE

/*================= 常数-计算的地址 ============================================*/

#define ADR_Last_BLOCK		(NOR_FLASH_SIZE - BLOCK_SIZE)
#define ADR_Last_SECTOR		(NOR_FLASH_SIZE - SECTOR_SIZE)

#define Flash_adrToBlock(_m_adr)   ( (_m_adr) / BLOCK_SIZE)
#define Flash_adrInSector(_m_adr)  ((_m_adr) & (SECTOR_SIZE-1)) 
#define Flash_adrToSector(_m_adr)  ( (_m_adr) / SECTOR_SIZE)
#define Flash_adrToSectS(_m_adr)   (_m_adr &= ~(SECTOR_SIZE - 1))
/*================= 常数-ID ============================================*/
#define SST_ID			    0xBF    /* SST Manufacturer's ID code   */
#define SST_39VF160	  	0x235B  /* SST 39VF160  device code      */
#define SST_39VF800A		0x2781  /* SST 39VF800A device code      */

/*================= 常数-result ============================================*/
typedef enum {
	U_NorFlash_Comm_Succeed = 1,
	U_NorFlash_Comm_Failed = 0,
	
}emNorFlashCommResult;
	
	
/*================= 常数-典型值 ============================================*/

/*
擦除周期： 100,000;
擦除：Sector:2K Word;  Block:32K Word;
扇区擦除时间：18ms典型
块擦除时间：  18ms典型
芯片擦除时间：70ms典型
字编程时间：  14us典型
芯片重写时间SST39LF/VF160为：15s典型
芯片重写时间SST39LF/VF800A为：8s典型

容量：
SST39LF/VF200A： 2M bits
SST39LF/VF400A： 4M bits
SST39LF/VF800A： 8M bits = 1M * Bytes = 512K * 16bits.
*/

/*================= 常数-时间 ============================================*/


// 写命令执行 最少20us.
typedef enum {
	U_POLL_WAIT_WriteWord,
	U_POLL_WAIT_EraseSector,
	U_POLL_WAIT_EraseBlock,
	U_POLL_WAIT_EraseChip,
	
	U_POLL_WAIT_MAX,
}emPollWait;
	
#define U_Delay_Flash_WAIT_WriteWord_us      30
#define U_Delay_Flash_WAIT_EraseSector_us    25*1000
#define U_Delay_Flash_WAIT_EraseBlock_us     25*1000
#define U_Delay_Flash_WAIT_EraseChip_us      99*1000

#ifdef  __hwEx21_SST39vf800A_C__
const uint32_t  cstPollWaitUs[U_POLL_WAIT_MAX] =
{
	U_Delay_Flash_WAIT_WriteWord_us,
	U_Delay_Flash_WAIT_EraseSector_us,
	U_Delay_Flash_WAIT_EraseBlock_us,
	U_Delay_Flash_WAIT_EraseChip_us,	
};
#endif // __hwEx21_SST39vf800A_C__	
/*================= 私有函数声明 ====================================*/
#ifdef  __hwEx21_SST39vf800A_C__

static void delayCnt(uint32_t delayCnt);
static void delayUs_tillFinish(uint32_t mUs);

// 片选地址 + offsetAdr
volatile uint16_t *NorFlash_Addr(uint8_t mChip, uint32_t offsetAdr);

// Addr需要word 对齐，否则结果是高字节。
uint16_t norFlash_GetData(uint8_t mChip, uint32_t Addr);
void norFlash_SetData(uint8_t mChip, uint32_t Addr, uint16_t mWord);

// 操作开始的命令字：
void norFlashCommand_Erase(uint8_t mChip);
void norFlashCommand_CheckIdIn(uint8_t mChip);
void norFlashCommand_CheckIdCfiOut(uint8_t mChip);
void norFlashCommand_WrWord(uint8_t mChip);

// 等待操作完成
// *  OUT: emNorFlashCommResult: U_NorFlash_Comm_Succeed,  U_NorFlash_Comm_Failed
static int Polling (uint8_t mChip, unsigned long adr, emPollWait mPollWait);
uint32_t toggleBitCheck(uint8_t mChip, uint32_t Addr, uint16_t Data );

#endif // __hwEx21_SST39vf800A_C__
/*================= 公有函数声明 ====================================*/
//EX_hwEx21_SST39vf800A 

extern void NorFlash_Init(uint8_t mChip);


 // * 					- TRUE: Correct
 // *					- FALSE: Incorrect
extern uint32_t NorFlash_CheckID(uint8_t mChip);

extern int bNorFlash_Idle (uint8_t mChip);
extern int bNorFlash_Busy (uint8_t mChip);



// *  OUT: emNorFlashCommResult: U_NorFlash_Comm_Succeed,  U_NorFlash_Comm_Failed
extern int NorFlash_EraseChip(uint8_t mChip, uint8_t bWaitForFinish);
extern int NorFlash_EraseAdr_1Block(uint8_t mChip, unsigned long adr,
											uint8_t bWaitForFinish); 
extern int NorFlash_EraseAdr_1Sector(uint8_t mChip, unsigned long adr,
											uint8_t bWaitForFinish);
extern int NorFlash_EraseBlock(uint8_t mChip, uint32_t mBlock,
											uint8_t bWaitForFinish); 
extern int NorFlash_EraseSector(uint8_t mChip, uint32_t mSector,
											uint8_t bWaitForFinish);


// *  OUT: emNorFlashCommResult: U_NorFlash_Comm_Succeed
extern uint32_t NorFlash_Write1Word(uint8_t mChip, uint32_t Addr, 
								 uint16_t Data);

extern int NorFlash_WriteNBytes(uint8_t mChip, unsigned long adr, 
					  unsigned long sz, uint8 *buf);
extern int NorFlash_ReadNBytes(uint8_t mChip, unsigned long adr, 
					  unsigned long sz, uint8 *buf); 


/******************************************************************************
// END :
******************************************************************************/
#endif // __hwEx21_SST39vf800A_H__

