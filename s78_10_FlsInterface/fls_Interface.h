#ifndef __fls_Interface_H__
#define __fls_Interface_H__
/******************************************************************************
* @file    fls_Interface.h
* @author  yx
* @version V1.0
* @date    2013-01-04
* @brief   
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

/*================= �ṹ�嶨�� ======================================*/

/*================= ���нṹ�������� ================================*/
/*================= ���к������� ====================================*/
//EX_fls_Interface 
extern U8 *pFlsHd_GetBufS(void);

extern U8   FlsHd_NowOpeaState(U8 chip);
extern U8   bFlsHd_ReadAllow(U8 chip);

extern BOOL bFlsHd_CheckIntervalArrived(void); //�������
extern BOOL bFlsHd_OpeaTimerArrived(U8 chip); //�����ʱ���ѵ�
extern BOOL bFlsHd_bOpeaSucc(U8 chip); //��hdStatus, �Ƿ�BUSY.

extern BOOL bFlashChip_IsAllIdle(void);

extern U32 FlsHd_ByteMax_1Chip(U8 chip);
extern U32 FlsHd_adrInSector(U8 chip, U32 mAdr);
extern U32 FlsHd_adrToSectorS(U8 chip, U32 mAdr);


extern BOOL FlsHd_EraseChip(U8 chip, U8 bWaitForFinish);
extern BOOL FlsHd_EraseBlock(U8 chip, U8 block, U8 bWaitForFinish);
extern BOOL FlsHd_EraseSector(U8 chip, U8 block, U8 sector, U8 bWaitForFinish);
extern BOOL FlsHd_EraseSect_FromAdr(U8 chip, U32 address, U8 bWaitForFinish);

extern void FlsHd_Write_1Sec(U8 chip, U8 *pStart, U32 address,U8 bWaitForFinish);
extern BOOL FlsHd_Write_nByte(U8 chip, U8 *pStart, U32 num, U32 address, U8 bWaitForFinish);

extern void FlsHd_Read_1Sec(U8 chip, U8 *pStart, U32 address);
extern void FlsHd_Read_nByte(U8 chip, U8 *pStart, U32 num, U32 address);

/******************************************************************************
// END :
******************************************************************************/
#endif // __fls_Interface_H__

