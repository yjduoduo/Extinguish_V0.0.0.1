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


/*================= ���� ============================================*/

// TRUE = write �� erase �ڼ䣬ִֻ��һЩ��falsh������ cycle������
//FALSE = ���ȴ�flash����polling��ϣ���������������
#define U_SYS_FLASH_OPEA_WAIT    TRUE  //flash ������

// TRUE: ��startʱ�Ѱ������¶����ꡣ
//FALSE: ��Ҫһֱ SaveManage_Exec() �������
//		�ڼ����ִ������task����ע���ж�����ǰ��
// 		Ҫ��FlsRdFlsItem_ChipAllow()�����Ƶĺ����ж��������
#define U_FLASH_TASK_WAIT        FALSE  //flash Manage 

/*================= ���� ============================================*/

/*================= ��洢��ص� ====================================*/

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

