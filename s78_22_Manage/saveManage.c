#define __saveManage_C__
/******************************************************************************
* @file    saveManage.c
* @author  yx
* @version V1.1
* @date    2013.9.22
* @brief   写flash管理。
*
******************************************************************************/
#include  "saveManage.h"

#include  "saveInc_Common.h"
#include  "saveInc_Extern.h"
#include  "flsReDef.h"

#include  "strFlsQue.h"

#include  "flsWrApplySave.h"
#include  "flsWrApplyBuf.h"

#include  "saveHistory.h" //读指针等
#include  "historyWrite.h" //历史记录
#include  "historyWrBuf.h"

#include  "flsCopyTask.h"
#include  "savePowerOff.h"
#include  "flashIdAssign.h"

/*================= 常数 ============================================*/
/*================= 结构定义 ========================================*/

/*================= 私有结构变量声明 ================================*/

/*================= 公有函数声明 ====================================*/

/*================= 私有函数声明 ====================================*/

/*=================  ================================================*/
		

/******************************************************************************
* FUNC: 
// 判断是否有未完结的任务，若有则需要继续处理。
// TRUE = !Erase & !FlsWr & !WorkHist & !WorkPwrOff & !WorkItem;
// 相对于flsTask_OpeaOne()，二者一致。无 copyTask();
*   IN:
*  OUT: 
// 参考: bStartOrExec_common_exeTillFinish();
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
	
#if U_FLASH_TASK_WAIT == TRUE // 在start时已把所有事都做完。
	return FALSE; 

#else // U_FLASH_TASK_WAIT

	//任务里的操作优先：
	if(		(bIfWorkIngExec_Erase())
		||	(bIfWorkIngExec_FlsWr())
	  )
	{
		return TRUE;
	}
	
	//下面是任务，正常情况只有一个 "!Idle"
	if(		(bIfWorkIngExec_Item())
	  ||	(bIfWorkIngExec_Hist())
	  ||	(bIfWorkIngExec_PwrOff())
	  // 无  (bIfWorkIngExec_FlsCopy()), 
	  // 只有在 bStartOrExec_...()也没有的情况下才继续。
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
* FUNC: // flash 存储管理 exe, 需要main循环调用。
*   IN:
*  OUT: 
******************************************************************************/

void SaveManage_Exec(void)
{
	// 判断是否有未完结的任务，若有则需要继续处理。
	// TRUE = !Erase & !FlsWr & !WorkHist & !WorkPwrOff & !WorkItem;
	if(!bFlsTask_isIdle()) 
	{
		flsTask_OpeaOne();
		return;
	}
	
	// 按优先级顺序查找待处理任务：
	
	//擦除是任务引起的，先处理：
	if(bStartOpea_Erase())
	{
		return;
	}
	
	//以下需要按优先级排列：
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
* FUNC: // FlsCopy,中间可以被其他任务打断。
		所以在判断其他任务都idle且 bStartOrExec_...()都=FALSE的情况下执行。
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
// 任务开始时：
// Start后，U_FLASH_TASK_WAIT == FALSE：在 SaveManage_Exec() 里调度；
//          U_FLASH_TASK_WAIT == TRUE:  一直等待完成：

// 参考: flsTask_OpeaOne();
******************************************************************************/
static BOOL bStartOrExec_common_exeTillFinish(
									emSaveOpeaClass mOpeaClass)
{

#if U_FLASH_TASK_WAIT == FALSE
	return TRUE;

#else // U_FLASH_TASK_WAIT == TRUE  // 在start时已把所有事都做完。
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
* FUNC: //直接等待至此task完毕.
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
	
	// 分配存储任务唯一id, Clr:
	FlsIdAssign_Init();
	
	//task init:
	Init_FlsEraseTask();
	Init_FlsCopyTask();
	FlsWr_Init();
	FlsSave_Init();
	
	FlsWr_pwrOff_Init();
	
	//flash 判断：
	FlsSave_CheckFlash();
	InitAll_FlsQueHeadEnd(); //读取队列的headEnd;
	
	
	// clr buf;
	// 比较指针和记录是否相符:
	// * 需要预先执行 InitAll_FlsQueHeadEnd(); 
	SaveHist_Init();
	SaveHist_Tmr_Init();
	
#if U_SYS_bShowNoFinished == 1 
	U_SYS_bShowNoFinished = 1;
	//需要读出常用的状态。
#endif // U_SYS_bShowNoFinished
}

/******************************************************************************
* FUNC: // 检查master和lib定义的一致性
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
//需要的项目允许读
//有1part允许就可以：
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
* FUNC: //需要的项目允许读
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
