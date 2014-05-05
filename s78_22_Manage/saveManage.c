#define __saveManage_C__
/******************************************************************************
* @file    saveManage.c
* @author  yx
* @version V1.1
* @date    2013.9.22
* @brief   дflash����
*
******************************************************************************/
#include  "saveManage.h"

#include  "saveInc_Common.h"
#include  "saveInc_Extern.h"
#include  "flsReDef.h"

#include  "strFlsQue.h"

#include  "flsWrApplySave.h"
#include  "flsWrApplyBuf.h"

#include  "saveHistory.h" //��ָ���
#include  "historyWrite.h" //��ʷ��¼
#include  "historyWrBuf.h"

#include  "flsCopyTask.h"
#include  "savePowerOff.h"
#include  "flashIdAssign.h"

/*================= ���� ============================================*/
/*================= �ṹ���� ========================================*/

/*================= ˽�нṹ�������� ================================*/

/*================= ���к������� ====================================*/

/*================= ˽�к������� ====================================*/

/*=================  ================================================*/
		

/******************************************************************************
* FUNC: 
// �ж��Ƿ���δ����������������Ҫ��������
// TRUE = !Erase & !FlsWr & !WorkHist & !WorkPwrOff & !WorkItem;
// �����flsTask_OpeaOne()������һ�¡��� copyTask();
*   IN:
*  OUT: 
// �ο�: bStartOrExec_common_exeTillFinish();
******************************************************************************/

static BOOL bFlsTask_isIdle(void)
{
	if(!bFlashChip_IsAllIdle())
	{
		return FALSE;
	}
	
	if(		(bFlsErase_isIdle())
		&&	(bFlsWr_isIdle())
		&&	(bFlsSave_isIdle())
		&&	(bFlsWr_Hist_isIdle())
		&&	(bFlsWr_pwrOff_isIdle())
	  )
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}


// TRUE = flash busy or opeaOne; FALSE=idle;
static BOOL flsTask_OpeaOne(void)
{
	
	if(!bFlashChip_IsAllIdle())
	{
		return TRUE;
	}
	
#if U_FLASH_TASK_WAIT == TRUE // ��startʱ�Ѱ������¶����ꡣ
	return FALSE; 

#else // U_FLASH_TASK_WAIT

	//������Ĳ������ȣ�
	if(		(bIfWorkIngExec_Erase())
		||	(bIfWorkIngExec_FlsWr())
	  )
	{
		return TRUE;
	}
	
	//�����������������ֻ��һ�� "!Idle"
	if(		(bIfWorkIngExec_Item())
	  ||	(bIfWorkIngExec_Hist())
	  ||	(bIfWorkIngExec_PwrOff())
	  // ��  (bIfWorkIngExec_FlsCopy()), 
	  // ֻ���� bStartOrExec_...()Ҳû�е�����²ż�����
	  )
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
	
#endif // U_FLASH_TASK_WAIT
}


/******************************************************************************
* FUNC: // flash �洢���� exe, ��Ҫmainѭ�����á�
*   IN:
*  OUT: 
******************************************************************************/

void SaveManage_Exec(void)
{
	// �ж��Ƿ���δ����������������Ҫ��������
	// TRUE = !Erase & !FlsWr & !WorkHist & !WorkPwrOff & !WorkItem;
	if(!bFlsTask_isIdle()) 
	{
		flsTask_OpeaOne();
		return;
	}
	
	// �����ȼ�˳����Ҵ���������
	
	//��������������ģ��ȴ���
	if(bStartOpea_Erase())
	{
		return;
	}
	
	//������Ҫ�����ȼ����У�
	if(		(bStartOpea_Item())
	  ||	(bStartOpea_Hist())
	  ||	(bStartOpea_PwrOff())
	  )
	{
		return;
	}
	
	
	if(bStartOrExec_FlsCopy())
	{
		return;
	}
}

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
static BOOL bIfWorkIngExec_PwrOff(void)
{
	if(bFlsWr_pwrOff_isIdle())
	{
		return FALSE;
	}
	else
	{
		FlsWr_pwrOff_Exec();
		return TRUE;
	}
}

static BOOL bStartOpea_PwrOff(void)
{

    if(!bSavePwrOff_Arrived())
    {
       return FALSE;
   }

   FlsWr_pwrOff_Start();

   return bStartOrExec_common_exeTillFinish(
               emSave_Opea_PwrOff);

}


/******************************************************************************
* FUNC: //
******************************************************************************/
static BOOL bIfWorkIngExec_FlsCopy(void)
{
	if(bFlsCopy_isIdle())
	{
		return FALSE;
	}
	else
	{
		FlsCopy_Exec();
		return TRUE;
	}
	
}

static BOOL bStartOpea_FlsCopy(void)
{
	if(!bFlsCopy_Allow_CheckItemError())
	{
		return FALSE;
	}
	
	
	if(bFlsCopyBuf_Empty())
	{
		FlsCopy_CheckError();
	}
	if(bFlsCopyBuf_Empty())
	{
		return FALSE;
	}
		
	return FlsCopy_Start();
	
}


/******************************************************************************
* FUNC: //
******************************************************************************/
static BOOL bIfWorkIngExec_Hist(void)
{
	if(bFlsWr_Hist_isIdle())
	{
		return FALSE;
	}
	else
	{
		FlsWr_Hist_Exec();
		return TRUE;
	}
}


static BOOL bStartOpea_Hist(void)
{
BOOL bStartSucc;

	if(bHistBuf_isEmpty())
	{
		return FALSE;
	}
	if(!( (bSaveHist_Arrived())
	  ||(bHistBuf_NumNeedSave())
	  ))
	{
		return FALSE;
	}
	
	bStartSucc = FlsWr_Hist_Start();
	if(!bStartSucc)
	{
		return FALSE;
	}
	
	return bStartOrExec_common_exeTillFinish(
										emSave_Opea_Hist);

}



/******************************************************************************
* FUNC: //
******************************************************************************/
static BOOL bIfWorkIngExec_Item(void)
{
	if(bFlsSave_isIdle())
	{
		return FALSE;
	}
	else
	{
		FlsSave_Exec();
		return TRUE;
	}
}


static BOOL bStartOpea_Item(void)
{
BOOL bStartSucc;

	if(bFlsWr_AlyBuf_Empty())
	{
		return FALSE;
	}
	
	bStartSucc = FlsSave_Start();
	if(!bStartSucc)
	{
		return FALSE;
	}
	
	return bStartOrExec_common_exeTillFinish(
										emSave_Opea_Item);

	
}

/******************************************************************************
* FUNC: //
******************************************************************************/
// Write Ing, flashIdle->next step;
static BOOL bIfWorkIngExec_FlsWr(void)
{
	if(bFlsWr_isIdle())
	{
		return FALSE;
	}
	else
	{
		FlsWr_Exec();
		return TRUE;
	}
}


/******************************************************************************
* FUNC: //
******************************************************************************/
static BOOL bIfWorkIngExec_Erase(void)
{
	if(bFlsErase_isIdle())
	{
		return FALSE;
	}
	else
	{
		FlsErase_Exec();
		return TRUE;
	}
}


static BOOL bStartOpea_Erase(void)
{
BOOL bStartSucc;
	if(bFlsEraseBuf_Empty())
	{
		return FALSE;
	}
	bStartSucc = FlsErase_Start();
	if(!bStartSucc)
	{
		return FALSE;
	}
	
	return bStartOrExec_common_exeTillFinish(
										emSave_Opea_Erase);
	
}


/******************************************************************************
* FUNC: // FlsCopy,�м���Ա����������ϡ�
		�������ж���������idle�� bStartOrExec_...()��=FALSE�������ִ�С�
*   IN:
*  OUT: 
******************************************************************************/

static BOOL bStartOrExec_FlsCopy(void)
{

	if(bIfWorkIngExec_FlsCopy())
	{
		return TRUE;
	}
	

	if(bStartOpea_FlsCopy())
	{
		return bStartOrExec_common_exeTillFinish(
										emSave_Opea_FlsCopy);
	}
	else
	{
		return FALSE;
	}
	
}

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
// ����ʼʱ��
// Start��U_FLASH_TASK_WAIT == FALSE���� SaveManage_Exec() ����ȣ�
//          U_FLASH_TASK_WAIT == TRUE:  һֱ�ȴ���ɣ�

// �ο�: flsTask_OpeaOne();
******************************************************************************/
static BOOL bStartOrExec_common_exeTillFinish(
									emSaveOpeaClass mOpeaClass)
{

#if U_FLASH_TASK_WAIT == FALSE
	return TRUE;

#else // U_FLASH_TASK_WAIT == TRUE  // ��startʱ�Ѱ������¶����ꡣ
BOOL bFinish;

	while(1)
	{
		RunCycle_OnTime();
		
		if(!bFlashChip_IsAllIdle())
		{
			continue;
		}
		if(bIfWorkIngExec_Erase())
		{
			continue;
		}
		
		if(bIfWorkIngExec_FlsWr())
		{
			continue;
		}
		
		switch(mOpeaClass)
		{
			case emSave_Opea_PwrOff:
				bFinish = !bIfWorkIngExec_PwrOff();
				break;
				
			case emSave_Opea_Hist:
				bFinish = !bIfWorkIngExec_Hist();
				break;
				
			case emSave_Opea_Item:
				bFinish = !bIfWorkIngExec_Item();
				break;
				
			// case emSave_Opea_Erase: 
				// bFinish = !bIfWorkIngExec_Erase();
				// break;
				
			case emSave_Opea_FlsCopy:
				bFinish = !bIfWorkIngExec_FlsCopy();
				break;
				
			default:
				bFinish = TRUE;
		}
		
		if(bFinish)
		{
			return TRUE;
		}
		else
		{
			continue;
		}
	
	}
	return TRUE;
#endif // U_FLASH_TASK_WAIT
	
	
}



/******************************************************************************
* FUNC: //ֱ�ӵȴ�����task���.
*   IN:
*  OUT: 
*Master: FlashSaveNew() + U_FLASH_TASK_WAIT=TRUE;
	    FlsErase_New() + U_FLASH_TASK_WAIT=TRUE;
******************************************************************************/

#if U_FLASH_TASK_WAIT == TRUE
BOOL bWaitForFlsOpeaFinish(U8 mFlsId)
{
U8 bAllowCopy;
U8 bSucc = FALSE;
	

    if(!bFlsId_Valid(mFlsId))
        return FALSE;

    bAllowCopy = bFlsCopy_Allow_CheckItemError();
    if(bAllowCopy)
    {
        SetForbid_FlsCopy_CheckItemError();
    }

    // ----- <
    while(1)
    {
        SaveManage_Exec();
        if(bIsFinish_FlsExe(mFlsId, &bSucc))
        {
            break;
        }
    }
    // ----- >

    if(bAllowCopy)
    {
        SetAllow_FlsCopy_CheckItemError();
    }
    return bSucc;
}
#endif // U_FLASH_TASK_WAIT

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
void Init_SaveManage(void)
{
	// space, error,  ...
	FlsItem_StateAll_Init();
	
	// ����洢����Ψһid, Clr:
	FlsIdAssign_Init();
	
	//task init:
	Init_FlsEraseTask();
	Init_FlsCopyTask();
	FlsWr_Init();
	FlsSave_Init();
	
	FlsWr_pwrOff_Init();
	
	//flash �жϣ�
	FlsSave_CheckFlash();
	InitAll_FlsQueHeadEnd(); //��ȡ���е�headEnd;
	
	
	// clr buf;
	// �Ƚ�ָ��ͼ�¼�Ƿ����:
	// * ��ҪԤ��ִ�� InitAll_FlsQueHeadEnd(); 
	SaveHist_Init();
	SaveHist_Tmr_Init();
	
#if U_SYS_bShowNoFinished == 1 
	U_SYS_bShowNoFinished = 1;
	//��Ҫ�������õ�״̬��
#endif // U_SYS_bShowNoFinished
}

/******************************************************************************
* FUNC: // ���master��lib�����һ����
*   IN:
*  OUT: 
******************************************************************************/

BOOL bSave_CheckReDef(void)
{
	if(  (U_MACHINE_MAX != GetMachineMax())
	  || (U_PANEL_TOTAL_SEQU_MAX != GetPanelTotalSequMax())
	  || (U_FlsSave_Item_MAX != GetSaveItemMax())
	  || (U_FlsSave_Part_MAX != GetSaveItmPartMax())
	  )
	{
		return FALSE;
	}
	return TRUE;
}


/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
//��Ҫ����Ŀ�����
//��1part����Ϳ��ԣ�
BOOL FlsRdFlsItem_ChipAllow(U8 mFlsItem) 
{
U8 mPart;
	
	for(mPart=0; mPart<FlsItem_PartMax(mFlsItem); mPart++)
	{
		if(FlsRdFlsItem_PartN_ChipAllow(mFlsItem, mPart))
		{
			return TRUE;
		}
	}
	return FALSE;
}

/******************************************************************************
* FUNC: //��Ҫ����Ŀ�����
******************************************************************************/
BOOL FlsRdFlsItem_PartN_ChipAllow(U8 mFlsItem, U8 mPart) 
{
TFlsItemAddr stAdr;

	if(!getFlsItem_Addr(mFlsItem, mPart, &stAdr))
	{
		return FALSE;
	}
	
	if(!bFlsItem_IsReadAllow(mFlsItem, mPart))
	{
		return FALSE;
	}
	return bFlsHd_ReadAllow(stAdr.chip);

}

/******************************************************************************
* FUNC: // END
*   IN:
*  OUT: 
******************************************************************************/
