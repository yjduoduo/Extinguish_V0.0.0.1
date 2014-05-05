#ifndef __fls_Interface_H__
#define __fls_Interface_H__
/******************************************************************************
* @file    fls_Interface.h
* @author  yx
* @version V1.0
* @date    2012-01-05
* @brief   flash�ӿں���.ʵ��hd flash�Ľӿڡ�
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
/*================= ���� ============================================*/

enum emFlashOpeaState{
	U_FLASH_NoOpea_STA = 0,  //����
	U_FLASH_OpeaSucc_STA = 1,  //succ
	U_FLASH_TimerOut_STA = 2,  //failed
	U_FLASH_WaitContinue_STA = 3, //usual
};
	// SST39LF/VF800A�� 8M bits = 1M * Bytes = 512K * 16bits.
// #define NOR_FLASH_SIZE		0x00100000 

 // 32K Word= 0x20*0x400*2 bytes = 0x10 000 bytes 
// #define BLOCK_SIZE		  0x00010000   

// 2K Word,    /* Must be 2048 words for 39VF160 */
// #define SECTOR_SIZE		  0x001000  
/*================= �ṹ�嶨�� ======================================*/

/*================= ���нṹ�������� ================================*/
/*================= ˽�к������� ====================================*/
#ifdef  __fls_Interface_C__

#endif  // __fls_Interface_C__
/*================= ���к������� ====================================*/
//EX_fls_Interface 

extern U8 *pFlsHd_GetBufS(void);

extern void   FlsHd_All_Init(void);
extern void   FlsHd_Init(U8 chip);

// *  OUT:emFlashOpeaState
extern U8   FlsHd_NowOpeaState(U8 chip);

extern U8   bFlsHd_ReadAllow(U8 chip);

extern BOOL bFlsHd_CheckIntervalArrived(void); //�������
extern BOOL bFlsHd_OpeaTimerArrived(U8 chip); //�����ʱ���ѵ�
extern BOOL bFlsHd_bOpeaSucc(U8 chip); //��hdStatus, �Ƿ�BUSY.

extern BOOL bFlashChip_IsAllIdle(void); // ����ִ�У�

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

