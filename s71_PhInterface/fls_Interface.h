#ifndef __fls_Interface_H__
#define __fls_Interface_H__
/******************************************************************************
* @file    fls_Interface.h
* @author  yx
* @version V1.0
* @date    2012-01-05
* @brief   flash接口函数.实际hd flash的接口。
* @slave   "hwEx21_SST39vf800A"   
* 
#include  "fls_Interface.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

/*================= extern ============================================*/
#ifdef  __fls_Interface_C__
#define EX_fls_Interface
#else
#define EX_fls_Interface extern 
#endif
/*================= 常数 ============================================*/

enum emFlashOpeaState{
	U_FLASH_NoOpea_STA = 0,  //空闲
	U_FLASH_OpeaSucc_STA = 1,  //succ
	U_FLASH_TimerOut_STA = 2,  //failed
	U_FLASH_WaitContinue_STA = 3, //usual
};
	// SST39LF/VF800A： 8M bits = 1M * Bytes = 512K * 16bits.
// #define NOR_FLASH_SIZE		0x00100000 

 // 32K Word= 0x20*0x400*2 bytes = 0x10 000 bytes 
// #define BLOCK_SIZE		  0x00010000   

// 2K Word,    /* Must be 2048 words for 39VF160 */
// #define SECTOR_SIZE		  0x001000  
/*================= 结构体定义 ======================================*/

/*================= 公有结构变量声明 ================================*/
/*================= 私有函数声明 ====================================*/
#ifdef  __fls_Interface_C__

#endif  // __fls_Interface_C__
/*================= 公有函数声明 ====================================*/
//EX_fls_Interface 

extern U8 *pFlsHd_GetBufS(void);

extern void   FlsHd_All_Init(void);
extern void   FlsHd_Init(U8 chip);

// *  OUT:emFlashOpeaState
extern U8   FlsHd_NowOpeaState(U8 chip);

extern U8   bFlsHd_ReadAllow(U8 chip);

extern BOOL bFlsHd_CheckIntervalArrived(void); //检测周期
extern BOOL bFlsHd_OpeaTimerArrived(U8 chip); //最长操作时间已到
extern BOOL bFlsHd_bOpeaSucc(U8 chip); //读hdStatus, 是否BUSY.

extern BOOL bFlashChip_IsAllIdle(void); // 周期执行：

extern U32 FlsHd_ByteMax_1Chip(U8 chip);
extern U32 FlsHd_adrInSector(U8 chip, U32 mAdr);
extern U32 FlsHd_adrToSectorS(U8 chip, U32 mAdr);


extern BOOL FlsHd_EraseChip(U8 chip, U8 bWaitForFinish);
extern BOOL FlsHd_EraseBlock(U8 chip, U8 block, U8 bWaitForFinish);
extern BOOL FlsHd_EraseSector(U8 chip, U8 sector, U8 bWaitForFinish);
extern BOOL FlsHd_EraseSect_FromAdr(U8 chip, U32 address, U8 bWaitForFinish);

extern void FlsHd_Write_1Sec(U8 chip, U8 *pStart, U32 address,U8 bWaitForFinish);
extern BOOL FlsHd_Write_nByte(U8 chip, U8 *pStart, U32 num, U32 address, U8 bWaitForFinish);

extern void FlsHd_Read_1Sec(U8 chip, U8 *pStart, U32 address);
extern void FlsHd_Read_nByte(U8 chip, U8 *pStart, U32 num, U32 address);

/******************************************************************************
// END :  FlsHd_EraseSect_FromAdr
******************************************************************************/
#endif // __fls_Interface_H__

