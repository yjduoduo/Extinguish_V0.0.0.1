#define __flsWrite_C__
/******************************************************************************
* @file    flsWrite.c
* @author  yx
* @version V1.0
* @date    2013-07-23
* @brief   flashд���ơ�����д����ֽڲ�ȫFF,����erase.
* 
******************************************************************************/
#include  "flsWrite.h"

#include  "codeComm.h"		//���ݡ�buf�ȳ������
#include  "codeCrc.h"
#include  "bufCircle.h"
#include  "fls_Interface.h"

//#include "incFile.h"	


/*================= ���� ============================================*/

/*================= �ṹ���� ========================================*/

/*================= ˽�нṹ�������� ================================*/

/*================= ���к������� ====================================*/

/*================= ˽�к������� ====================================*/

/*=================  ================================================*/
		
/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
void FlsWr_Init(void)
{
	flsWr_SetIdle();
}

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
BOOL bFlsWr_isIdle(void)
{
	return (stWr.step >= U_FlashWriteStep_MAX);
}

static void flsWr_SetIdle(void)
{
	stWr.step = ~0;
}

/******************************************************************************
* FUNC: // write buf �޸�Ϊ��д����ֽ�
*   IN:
*  OUT: 
******************************************************************************/

static void flsWr_verifyByte_inBuf(U8 *pVerify, U32 mAdrInSect, U8 num)
{
	if((mAdrInSect + num) > U_FLASH_1_SECTOR)
	{
		num = U_FLASH_1_SECTOR - mAdrInSect;
	}
	
	CopyNByte(pVerify, &vWrBuf[mAdrInSect], num); 
}


/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
// �� - �޸� - д��
******************************************************************************/

BOOL FlsWr_Write_nByte(U8 chip, U8 *pStart, U32 num, U32 address)
{
	stWr.chip = chip;
	stWr.address = address;
	stWr.num = num;
	stWr.pByteFrom = pStart;
	stWr.adrInSect = FlsHd_adrInSector(chip, address);
	
	
	stWr.bHaveEnd = FALSE;
	
	stWr.step = U_FlashWriteStep_Start;
	FlsWr_Exec();
	return TRUE;
}



/******************************************************************************
* FUNC: //
�Լ��������ֽڣ�֮��ĵ�ַ������ ������д�ء�
******************************************************************************/
BOOL FlsWr_Write_nByte_meIsEnd(U8 chip, U8 *pStart, U32 num, U32 address)
{
	stWr.chip = chip;
	stWr.address = address;
	stWr.num = num;
	stWr.pByteFrom = pStart;
	stWr.adrInSect = FlsHd_adrInSector(chip, address);
	
	
	stWr.bHaveEnd = TRUE;
	
	
	stWr.step = U_FlashWriteStep_Start;
	FlsWr_Exec();
	return TRUE;
}



/******************************************************************************
* FUNC: //
******************************************************************************/
void FlsWr_Exec(void)
{
	if(!bFlashChip_IsAllIdle())
	{
		return;
	}
WRITEFLASH:	
	switch(stWr.step)
	{
		case U_FlashWriteStep_Start:
			flsWr_step_Start();
			//ֱ�ӽ���next:
			if(stWr.step == U_FlashWriteStep_Write)
			{
//				flsWr_step_Write();
				flsWr_step_WriteDirect();
			}
			else if(stWr.step == U_FlashWriteStep_Erase)
			{
				flsWr_step_Erase();
			}

			if(stWr.step==U_FlashWriteStep_Write)
				goto WRITEFLASH;
			break;
			
		case U_FlashWriteStep_Erase:
			flsWr_step_Erase();
			break;
			
		case U_FlashWriteStep_Write:
			flsWr_step_Write();
			break;
			
		default:
			flsWr_SetIdle();
			break;
	}
}


/******************************************************************************
* FUNC: //
******************************************************************************/

static void flsWr_step_Start(void)
{
	FlsHd_Read_nByte(stWr.chip, &vWrBuf[0], 
			stWr.num, stWr.address);
	if(bAllRamIsFF(&vWrBuf[0], stWr.num))
	{
		stWr.step = U_FlashWriteStep_Write;
	}
	else
	{
		stWr.step = U_FlashWriteStep_Erase;
	}
	
}

/******************************************************************************
* FUNC: //
******************************************************************************/

static void flsWr_step_Erase(void)
{
	FlsHd_Read_1Sec(stWr.chip, &vWrBuf[0], 
			stWr.address);
	FlsHd_EraseSect_FromAdr(stWr.chip, stWr.address, 
						   U_SYS_FLASH_OPEA_WAIT);
	flsWr_verifyByte_inBuf(stWr.pByteFrom, stWr.adrInSect, stWr.num);
	
	//�޸�д������
//	stWr.pByteFrom = &vWrBuf[0];
//	pByteFrom=stWr.pByteFrom;
	if(stWr.bHaveEnd)
	{
        stWr.pByteFrom = &vWrBuf[0];


		stWr.wrNum = stWr.num + stWr.adrInSect;
	}
	else
	{
//        stWr.pByteFrom = &vWrBuf[0];

		stWr.wrNum = U_FLASH_1_SECTOR;
	}
	stWr.address = FlsHd_adrToSectorS(stWr.chip, stWr.address);
	
	//
	stWr.step = U_FlashWriteStep_Write;
	
}

/******************************************************************************
* FUNC: //
******************************************************************************/
static void flsWr_step_Write(void)
{
	FlsHd_Write_nByte(
		stWr.chip, stWr.pByteFrom, stWr.wrNum, stWr.address, 
		U_SYS_FLASH_OPEA_WAIT
		);
	flsWr_SetIdle();
	
}

/******************************************************************************
* FUNC: //not equal to  flsWr_step_Write,the stWr.num is not same with stWr.wrNum
******************************************************************************/
static void flsWr_step_WriteDirect(void)
{
	FlsHd_Write_nByte(
		stWr.chip, stWr.pByteFrom, stWr.num, stWr.address, 
		U_SYS_FLASH_OPEA_WAIT
		);
	flsWr_SetIdle();
	
}

/******************************************************************************
* FUNC: //
******************************************************************************/

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/



/******************************************************************************
* FUNC: // END
*   IN:
*  OUT: 
******************************************************************************/
