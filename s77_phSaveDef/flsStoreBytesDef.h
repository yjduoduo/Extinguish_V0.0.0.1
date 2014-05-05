#ifndef __flsStoreBytesDef_H__
#define __flsStoreBytesDef_H__
/******************************************************************************
* @file    flsStoreBytesDef.h
* @author  yx
* @version V1.0
* @date    2012-01-05
* @brief   
* 
#include  "flsStoreBytesDef.h"
******************************************************************************/
//
#include  "prjCompileCon.h"


/*================= 常数 ============================================*/

// TRUE = write 或 erase 期间，只执行一些无falsh操作的 cycle函数。
//FALSE = 不等待flash操作polling完毕，即进行其他操作
#define U_SYS_FLASH_OPEA_WAIT    TRUE  //flash 驱动层

// TRUE: 在start时已把所有事都做完。
//FALSE: 需要一直 SaveManage_Exec() 完成任务。
//		期间可以执行其他task，但注意有读操作前，
// 		要用FlsRdFlsItem_ChipAllow()或类似的函数判断允许读。
#define U_FLASH_TASK_WAIT        FALSE  //flash Manage 

/*================= 常数 ============================================*/

/*================= 与存储相关的 ====================================*/

#if U_SYS_Test_Flash_Hist == 1
	#define U_FLASH_1_SECTOR   0x100 // U_W25X80_1Sector_Bytes
#elif U_SYS_Test_Flash_InqPoint == 1
	#define U_FLASH_1_SECTOR   0x1000
	#define U_SimFlsPoit_1SectorBytes   0x100
#else
	#define U_FLASH_1_SECTOR   0x1000 // U_W25X80_1Sector_Bytes
#endif

#define SecBytes        (U_FLASH_1_SECTOR)

#define U_Hist_1SectorBytes  (U_FLASH_1_SECTOR)
//----------------------------------------------------------
#define U_FLASH_1_PAGE   0x100
#define U_FLASH_ERASE_MIN  U_FLASH_1_SECTOR // U_W25X80_1Sector_Bytes

#define U_FLS_1HISTORY_BYTE_MAX   0x10
#define U_FLS_1HistPoint_BYTE_MAX   0x10
#define U_FLS_1PowerOff_BYTE_MAX   0x10
#define U_FLS_NOTE_BYTE_MAX   32
#define U_FLS_LINK_PROG_BYTE_MAX   0x100

/******************************************************************************
// END :
******************************************************************************/
#endif // __flsStoreBytesDef_H__

