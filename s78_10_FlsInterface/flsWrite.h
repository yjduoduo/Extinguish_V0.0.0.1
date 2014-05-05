#ifndef __flsWrite_H__
#define __flsWrite_H__
/******************************************************************************
* @file    flsWrite.h
* @author  yx
* @version V1.1
* @date    2013.9.22
* @brief   flash写控制。若待写入的字节不全FF,负责erase.

* V1.1, 2013.9.22
*  	FlsWr_Exec() 改错：改bFlsWr_isIdle()为bFlashChip_IsAllIdle(), 此时 exec.
* V1.0, 2013-07-23
* 
#include  "flsWrite.h"
******************************************************************************/
//
#include  "prjCompileCon.h"
#include  "flsStoreBytesDef.h"

/*================= extern ============================================*/
#ifdef  __flsWrite_C__
#define EX_flsWrite
#else
#define EX_flsWrite extern 
#endif
/*================= 常数 ============================================*/
enum emFlashWriteStep{
	U_FlashWriteStep_Start,
	U_FlashWriteStep_Erase,
	U_FlashWriteStep_Write,
	
};
#define U_FlashWriteStep_MAX 0x04
/*================= 结构体定义 ======================================*/

/*================= 公有结构变量声明 ================================*/
#ifdef  __flsWrite_C__

typedef struct{
	U8 step;
	
	U8 chip;
	U32 address;
	U32 num;
	U8 *pByteFrom;
	
	U32 wrNum;
	U32 adrInSect;
	U8 bHaveEnd;
	// U32 endInSect;
}TFlashWrite_st;


#endif  //__flsWrite_C__

/*================= 私有函数声明 ====================================*/
#ifdef  __flsWrite_C__

static TFlashWrite_st   stWr;
static U8 vWrBuf[U_FLASH_1_SECTOR];

static void flsWr_SetIdle(void);
static void flsWr_verifyByte_inBuf(U8 *pVerify, U32 mAdrInSect, U8 num);

static void flsWr_step_Start(void);
static void flsWr_step_Erase(void);
static void flsWr_step_Write(void);
static void flsWr_step_WriteDirect(void);



#endif  //__flsWrite_C__
/*================= 公有函数声明-lib内部 ====================================*/
//EX_flsWrite 

extern void FlsWr_Init(void);
extern BOOL bFlsWr_isIdle(void);
extern void FlsWr_Exec(void);

extern BOOL FlsWr_Write_nByte(
					U8 chip, U8 *pStart, U32 num, U32 address);
extern BOOL FlsWr_Write_nByte_meIsEnd(
					U8 chip, U8 *pStart, U32 num, U32 address);

//FlsHd_Write_nByte


/******************************************************************************
// END :
******************************************************************************/
#endif // __flsWrite_H__

