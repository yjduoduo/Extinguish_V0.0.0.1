#define __strDevice_C__
/******************************************************************************
* @file    strDevice.c
* @author  yx
* @version V1.1
* @date    2013-10-24
* @brief   
* 
*BuildToDev_　系列，未分类判断。
******************************************************************************/
#include  "strDevice.h"

#include  "sysDef.h"

#include  "sysPanel.h"
//#include "incFile.h"	


/*================= 常数 ============================================*/
/******************************************************************************
* FUNC: // Dev 结构里的item的 max, mask
******************************************************************************/
/*=================Dev 分类 ============================================*/

typedef struct{
	U32 max;
	U32 mask;
}TDevStructProp;

TDevStructProp  cstStDevStructProp[U_DEV_ITEM_MAX] =
{//  max,    mask
	{0x100,  0xFF}, //U_DEV_ITEM_Machine
	{0x1F,  0xF8000000}, //U_DEV_ITEM_pnType //5
	{0x7F,  0x07F00000}, //U_DEV_ITEM_pnSequ //7
	{0x0F,  0x000F0000}, //U_DEV_ITEM_modu //4
	{0x02,  0x00008000}, //U_DEV_ITEM_evtSubject //1
	{0x1FF, 0x00007FC0}, //U_DEV_ITEM_mduLine
	{0x1FF, 0x00007FC0}, //U_DEV_ITEM_field
	{0x3F,  0x0000003F}, //U_DEV_ITEM_channel
};
	
/*================= 结构定义 ========================================*/

/*================= 私有结构变量声明 ================================*/

/*================= 公有函数声明 ====================================*/

/*================= 私有函数声明 ====================================*/
TDev_un  stDeteEvtStr;

/*=================  ================================================*/
		
/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

#if U_SYS_Test_strDevice == 1 

TDev_un  test_dev_stDev1; 
TDev_un  test_dev_stDev2;
BOOL test_dev_bEqu;
U32 test_dev_mDWord;

void Test_DevCompMask(void);
void Test_DevCompare(void);
void Test_Dev(void)
{
	
	
	Test_DevCompMask();
	
//===== OK ===============================================
	Test_DevCompare();
		
//====================================================
	DevSetInvalid(&test_dev_stDev1);
	
}

void Test_DevCompare(void) //OK
{
	
	
	DevSetInvalid(&test_dev_stDev1);
	DevSetInvalid(&test_dev_stDev2);
	
	BuildToDev_Panel(1, 2, 3, &test_dev_stDev1);
	BuildToDev_Panel(1, 2, 3, &test_dev_stDev2);
	test_dev_bEqu = bDevCompare(&test_dev_stDev1, &test_dev_stDev2);
	
	DevSetInvalid(&test_dev_stDev2);
	ComposeDev_fromBytes((U8*)(&test_dev_stDev1), &test_dev_stDev2);
	
	DevSetInvalid(&test_dev_stDev1);
	ComposeBytes_fromDev(&test_dev_stDev2, (U8*)(&test_dev_stDev1));
	
	test_dev_mDWord = ComposeDWord_fromDev_NoMachine(&test_dev_stDev2);
		
//====================================================
	DevSetInvalid(&test_dev_stDev1);
}

void Test_DevCompMask(void) //OK
{
	
	DevSetInvalid(&test_dev_stDev1);
	BuildToDev_DeteMLAC(1, 17, 5, 6, &test_dev_stDev1);
	CacuDeteLoop_1toMax(&test_dev_stDev1, &test_dev_bEqu); //借用test_dev_bEqu
	
	// -> Err   // 1
	BuildToDev_DeteMLAC(1, 18, 5, 6, &test_dev_stDev2);
	test_dev_bEqu = bDevCompMask(U_DEV_ITEM_field, &test_dev_stDev1, &test_dev_stDev2); 
	
	// -> Err
	BuildToDev_DeteMLAC(2, 17, 5, 6, &test_dev_stDev2);
	test_dev_bEqu = bDevCompMask(U_DEV_ITEM_Machine, &test_dev_stDev1, &test_dev_stDev2); 
	// -> 1
	BuildToDev_DeteMLAC(1, 17, 5, 6, &test_dev_stDev2);
	test_dev_bEqu = bDevCompMask(U_DEV_ITEM_Machine, &test_dev_stDev1, &test_dev_stDev2); 
	
	// -> 1
	BuildToDev_DeteMLAC(1, 10, 1, 1, &test_dev_stDev2);
	test_dev_bEqu = bDevCompMask(U_DEV_ITEM_pnType, &test_dev_stDev1, &test_dev_stDev2); 
	
	// -> Err
	BuildToDev_DeteMLAC(1, 16, 5, 6, &test_dev_stDev2);
	test_dev_bEqu = bDevCompMask(U_DEV_ITEM_pnSequ, &test_dev_stDev1, &test_dev_stDev2); 
	// -> 1
	BuildToDev_DeteMLAC(1, 17, 1, 1, &test_dev_stDev2);
	test_dev_bEqu = bDevCompMask(U_DEV_ITEM_pnSequ, &test_dev_stDev1, &test_dev_stDev2); 
	
	// -> Err
	BuildToDev_DeteMLAC(1, 18, 5, 6, &test_dev_stDev2);
	test_dev_bEqu = bDevCompMask(U_DEV_ITEM_modu, &test_dev_stDev1, &test_dev_stDev2); 
	// -> 1
	BuildToDev_DeteMLAC(1, 17, 1, 1, &test_dev_stDev2); //1, 17, 5, 6
	test_dev_bEqu = bDevCompMask(U_DEV_ITEM_modu, &test_dev_stDev1, &test_dev_stDev2); 
	
	// -> Err
	BuildToDev_DeteMLAC(1, 18, 5, 6, &test_dev_stDev2);
	test_dev_bEqu = bDevCompMask(U_DEV_ITEM_field, &test_dev_stDev1, &test_dev_stDev2); 
	// -> Err
	BuildToDev_DeteMLAC(1, 17, 4, 6, &test_dev_stDev2);
	test_dev_bEqu = bDevCompMask(U_DEV_ITEM_field, &test_dev_stDev1, &test_dev_stDev2); 
	// -> Err
	BuildToDev_DeteMLAC(2, 17, 5, 6, &test_dev_stDev2);
	test_dev_bEqu = bDevCompMask(U_DEV_ITEM_field, &test_dev_stDev1, &test_dev_stDev2); 
	// -> 1
	BuildToDev_DeteMLAC(1, 17, 5, 1, &test_dev_stDev2); //1, 17, 5, 6
	test_dev_bEqu = bDevCompMask(U_DEV_ITEM_field, &test_dev_stDev1, &test_dev_stDev2); 
	
	
	// -> Err
	BuildToDev_DeteMLAC(1, 17, 5, 7, &test_dev_stDev2);
	test_dev_bEqu = bDevCompMask(U_DEV_ITEM_channel, &test_dev_stDev1, &test_dev_stDev2); 
	// -> 1
	BuildToDev_DeteMLAC(1, 17, 5, 6, &test_dev_stDev2); //1, 17, 5, 6
	test_dev_bEqu = bDevCompMask(U_DEV_ITEM_channel, &test_dev_stDev1, &test_dev_stDev2); 
	
}

#endif // U_SYS_Test_strDevice


/******************************************************************************
* FUNC: //清除
* U_SIGN_bHaveTested;
******************************************************************************/
// 对比 bDevOk();
void DevSetInvalid(TDev_un  *m_pDev)
{
U8 *pByteDev = (U8 *)(m_pDev);
U8 ii;
	//U_DEV_ADDR_BYTE_MAX
	for(ii=0; ii<sizeof(TDev_un); ii++)
	{
		*pByteDev = 0;
		pByteDev++;
	}
	
}



void DevSet_all_FF(TDev_un  *m_pDev)
{
U8 *pByteDev = (U8 *)(m_pDev);
U8 ii;
	
	for(ii=0; ii<sizeof(TDev_un); ii++)
	{
		*pByteDev = ~0;
		pByteDev++;
	}
	
}
void DevSet_all_00(TDev_un  *m_pDev)
{
U8 *pByteDev = (U8 *)(m_pDev);
U8 ii;
	
	for(ii=0; ii<sizeof(TDev_un); ii++)
	{
		*pByteDev = 0;
		pByteDev++;
	}
	
}


void DevSet_SimAdr(U8 mIniVal, TDev_un  *m_pDev)
{
	m_pDev->stDete.machine = 1;
	m_pDev->stDete.pnType 		= U_PN_Loop_TYPE;
	m_pDev->stDete.pnSequ 		= 1;
	m_pDev->stDete.boardLoop 	= 1;
	m_pDev->stDete.eventSubject = U_EVT_SUBJECT_FIELD;
	m_pDev->stDete.field 		= mIniVal;
	m_pDev->stDete.channel 		= 0;
	
}

void DevSet_all_test1234567(U8 mIniVal, TDev_un  *m_pDev)
{
	m_pDev->stDete.machine 		= mIniVal+1;
	if(m_pDev->stDete.machine >= U_MACHINE_MAX)
	{
		m_pDev->stDete.machine %= U_MACHINE_MAX;
		if(m_pDev->stDete.machine == 0)
		{
			m_pDev->stDete.machine = 1;
		}
	}
	
	m_pDev->stDete.pnType 		= mIniVal+2;
	if(m_pDev->stDete.pnType >= cstStDevStructProp[U_DEV_ITEM_pnType].max)
	{
		m_pDev->stDete.pnType %= cstStDevStructProp[U_DEV_ITEM_pnType].max;
		if(m_pDev->stDete.pnType == 0)
		{
			m_pDev->stDete.pnType = 1;
		}
	}
	
	m_pDev->stDete.pnSequ 		= mIniVal+3;
	if(m_pDev->stDete.pnSequ >= cstStDevStructProp[U_DEV_ITEM_pnSequ].max)
	{
		m_pDev->stDete.pnSequ %= cstStDevStructProp[U_DEV_ITEM_pnSequ].max;
		if(m_pDev->stDete.pnSequ == 0)
		{
			m_pDev->stDete.pnSequ = 1;
		}
	}
	
	m_pDev->stDete.boardLoop 	= mIniVal+4;
	
	m_pDev->stDete.eventSubject = mIniVal+5;
	
	m_pDev->stDete.field 		= mIniVal+6;
	if(m_pDev->stDete.field >= cstStDevStructProp[U_DEV_ITEM_field].max)
	{
		m_pDev->stDete.field %= cstStDevStructProp[U_DEV_ITEM_field].max;
		if(m_pDev->stDete.field == 0)
		{
			m_pDev->stDete.field = 1;
		}
	}
	
	m_pDev->stDete.channel 		= mIniVal+7;
	if(m_pDev->stDete.channel >= cstStDevStructProp[U_DEV_ITEM_channel].max)
	{
		m_pDev->stDete.channel %= cstStDevStructProp[U_DEV_ITEM_channel].max;
		if(m_pDev->stDete.channel == 0)
		{
			m_pDev->stDete.channel = 1;
		}
	}
	
	
}









/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

/******************************************************************************
* FUNC: //
******************************************************************************/
// 对比 DevSetInvalid();
BOOL bDevOk(TDev_un *pDev)
{
	return (jdgDevItem_Legal(U_DEV_ITEM_Machine, pDev->stDete.machine));
}


/******************************************************************************
* FUNC: //
******************************************************************************/
BOOL bDevIsMachMe(TDev_un *pDev)
{
	return (bMachineIdIsMe(pDev->stDete.machine));
}


/******************************************************************************
* 
* FUNC: //只是判断是否超出字段范围。
*   IN: mDevItem = emDevClass
// if(jdgDevItem_Legal(pDev, U_DEV_ITEM_Machine))
******************************************************************************/
U8 jdgDevItem_Legal(U8 mDevItem, U32 mChkItemNow) //只是判断是否超出字段范围。
{
U32 mChkItemMax;

	if(mDevItem >= U_DEV_ITEM_MAX)
	{
		return FALSE;
	}
	
	mChkItemMax = cstStDevStructProp[mDevItem].max;
	switch(mDevItem)
	{
		case U_DEV_ITEM_Machine:
			if(mChkItemNow == U_MACHINE_SELF)
			{
				return TRUE;
			}
			mChkItemMax = U_MACHINE_MAX;
			break;
			
		case U_DEV_ITEM_pnType:
			break;			
		case U_DEV_ITEM_pnSequ:
			break;
			
			
		case U_DEV_ITEM_evtSubject:
			return TRUE;  //都合法
			
		case U_DEV_ITEM_modu:
			break;
		case U_DEV_ITEM_mduLine:
			break;
		case U_DEV_ITEM_field:
			break;
		case U_DEV_ITEM_channel:
			break;
			
		default:
			return FALSE;
	}
	
	if((mChkItemNow == 0) || (mChkItemNow >= mChkItemMax))
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
	
}


U8 jdgDevItem_Dete_Legal(U8 loop, U32 addr)
{
	if((loop == 0) || (loop > U_SYS_LOOP_MAX))
	{
		return FALSE;
	}
	return ((addr > 0) && (addr < U_1LOOP_DETE_MAX));
}

BOOL bDeteHaveChannel(TDev_un *pDev)
{
	return (pDev->stDete.channel != 0);
}




/******************************************************************************
* FUNC: 
* U_SIGN_bHaveTested
******************************************************************************/

BOOL CacuDeteLoop_1toMax(TDev_un *pDev, U32 *pRtnLoop) //计算回路数 1~
{
U32 mLoop;

	if(pDev->stDete.pnType == U_PN_Loop_TYPE)
	{
		mLoop = (pDev->stDete.pnSequ - 1) * U_OneBoard_LOOP_MAX;
		mLoop += pDev->stDete.boardLoop;
		*pRtnLoop = mLoop;
		return TRUE;
	}
	else
	{
		*pRtnLoop = U_SYS_LOOP_MAX+1;
		return FALSE;
	}
}

BOOL CacuDrtLoop_1toMax(TDev_un *pDev, U32 *pRtnLoop) //计算多线回路数 1~
{
U32 mLoop;

	if(pDev->pnModu.pnType == U_PN_Drt_TYPE)
	{
		mLoop = (pDev->pnModu.pnSequ - 1) * U_OneBoard_DrtModu_MAX;
		mLoop += pDev->pnModu.modu;
		*pRtnLoop = mLoop;
		return TRUE;
	}
	else
	{
		mLoop = U_Board_DRT_MAX * U_OneBoard_DrtModu_MAX;
		*pRtnLoop = mLoop;
		return FALSE;
	}
}


BOOL CacuExtgLoop_1toMax(TDev_un *pDev, U32 *pRtnLoop) //计算灭火回路数 1~
{
U32 mLoop;

	if(pDev->pnModu.pnType == U_PN_Extg_TYPE)
	{
		mLoop = (pDev->pnModu.pnSequ - 1) * U_OneBoard_ExtgModu_MAX;
		mLoop += pDev->pnModu.modu;
		*pRtnLoop = mLoop;
		return TRUE;
	}
	else
	{
		mLoop = U_Board_EXTG_MAX * U_OneBoard_ExtgModu_MAX;
		*pRtnLoop = mLoop;
		return FALSE;
	}
}


/******************************************************************************
* FUNC: 

******************************************************************************/
//计算回路现场部件数 0~12800
BOOL CacuDevSequ_Dete_0toMax(TDev_un *pDev, U32 *pRtnSequ) 
{
U32 mLoop;
	
	if(CacuDeteLoop_1toMax(pDev, &mLoop)) //计算回路数 1~	
	{
		*pRtnSequ = U_1LOOP_DETE_MAX * (mLoop - 1) + (pDev->stDete.field);
		return TRUE;
	}
	else
	{
		*pRtnSequ = ~0;
		return FALSE;
	}
}

//计算多线现场部件数 0~
BOOL CacuDevSequ_Drt_0toMax(TDev_un *pDev, U32 *pRtnSequ) 
{
U32 mLoop;
	
	if(CacuDrtLoop_1toMax(pDev, &mLoop)) //计算多线回路数 1~
	{
		*pRtnSequ = U_OneBoard_DrtModu_MAX * (mLoop - 1) 
					+ (pDev->pnModu.mduLine);
		return TRUE;
	}
	else
	{
		*pRtnSequ = ~0;
		return FALSE;
	}
}


//计算气灭现场部件数 0~
BOOL CacuDevSequ_Extg_0toMax(TDev_un *pDev, U32 *pRtnSequ) 
{
U32 mLoop;
	
	if(CacuExtgLoop_1toMax(pDev, &mLoop)) //计算气灭回路数 1~
	{
		*pRtnSequ = U_OneBoard_ExtgModu_MAX * (mLoop - 1) 
					+ (pDev->pnModu.mduLine);
		return TRUE;
	}
	else
	{
		*pRtnSequ = ~0;
		return FALSE;
	}
}


/******************************************************************************
* FUNC: //回路—多线-气灭总排序。

******************************************************************************/
//计算所有现场部件排号 0~
BOOL CacuDevSequ_0toMax(TDev_un *pDev, U32 *pRtnSequ) 
{
U32 mAdr;

	if(pDev->stDete.pnType == U_PN_Loop_TYPE)
	{
		//计算回路现场部件数 0~12800
		if(CacuDevSequ_Dete_0toMax(pDev, &mAdr))
		{
			*pRtnSequ = mAdr;
			return TRUE;			
		}
	}
	else if(pDev->pnModu.pnType == U_PN_Drt_TYPE)
	{
		if(CacuDevSequ_Drt_0toMax(pDev, &mAdr)) //计算多线现场部件数 0~
		{
			mAdr += (U_1LOOP_DETE_MAX * U_SYS_LOOP_MAX);
			*pRtnSequ = mAdr;
			return TRUE;
		}
	}
	else if(pDev->pnModu.pnType == U_PN_Extg_TYPE)
	{
		if(CacuDevSequ_Extg_0toMax(pDev, &mAdr)) //计算气灭现场部件数 1~
		{
			mAdr += (U_1LOOP_DETE_MAX * U_SYS_LOOP_MAX);
			mAdr += (U_OneModLine_Drt_Dete_MAX 
					* U_OneBoard_DrtModu_MAX 
					* U_Board_DRT_MAX
					);
			*pRtnSequ = mAdr;
			return TRUE;
		}
	}
	
	*pRtnSequ = ~0;
	return FALSE;
	
}

/******************************************************************************
* FUNC: 

******************************************************************************/



/******************************************************************************
* FUNC: //通过总回路号，计算panel号和panel内的回路号。
* U_SIGN_bHaveTested
******************************************************************************/
void CacuDetePnSequAndBdLoop(U8 loop, U8 *pRtnPnSequ, U8 *pRtnBdLoop)
{
	myAssert((loop != 0)&&(loop <= U_SYS_LOOP_MAX));
	
	*pRtnPnSequ = (loop-1)/U_OneBoard_LOOP_MAX+1;
	if((loop%U_OneBoard_LOOP_MAX) == 0)
	{
		*pRtnBdLoop = U_OneBoard_LOOP_MAX;
	}
	else
	{
		*pRtnBdLoop = (loop%U_OneBoard_LOOP_MAX);
	}
	
}


/******************************************************************************
* NAME: 
* FUNC: //判断stDev的类型，是机器、panel、panel.modu、64回路之一：
		显示等
*   IN:
*  OUT:  emDevClass
******************************************************************************/
U8 JdgDevClass(TDev_un *pDev) // OUT:  emDevClass
{
U8 pnSequ = 0;
U8 pnType;
	
	pnType = pDev->pnModu.pnType;
	pnSequ = pDev->pnModu.pnSequ;
	if(!bPnSequIsValid(pnType, pnSequ))
	{
		return U_DEV_IS_Machine_TYPE;
	}
	
	if(pDev->pnModu.modu == 0)
	{
		return U_DEV_IS_Panel_TYPE;
	}
	
	
	
	if(pDev->pnModu.eventSubject == U_EVT_SUBJECT_BOARD)
	{
		return U_DEV_IS_PnModu_TYPE;
	}
	else //U_EVT_SUBJECT_FIELD
	{
		if(pDev->pnModu.mduLine == 0) //pDev->stDete.field
		{
			return U_DEV_IS_PnModu_TYPE;
		}
		else
		{
			if(pnType == U_PN_Loop_TYPE)
			{
				if(pDev->stDete.channel == 0)
					return U_DEV_IS_Dete_TYPE;
				else
					return U_DEV_IS_Channel_TYPE;
			}
			else
			{
				return U_DEV_IS_ModuLine_TYPE;
			}
		}
	}
	
}














/******************************************************************************
* FUNC: // -> stDete.
*   IN:
*  OUT: 可以利用这些函数判断 in是否有效。
******************************************************************************/


/******************************************************************************
* NAME: 
* FUNC: // 机器 -> stDete
*   IN:
*  OUT: 
******************************************************************************/
//
U8 BuildToDev_Machine(U8 machine, TDev_un *pDev)
{
	DevSetInvalid(pDev);
	if(!jdgDevItem_Legal(U_DEV_ITEM_Machine, machine))
	{
		return FALSE;
	}
	pDev->stDete.machine = machine;
	pDev->stDete.eventSubject = U_EVT_SUBJECT_BOARD;
	return TRUE;
}

/******************************************************************************
* FUNC: // 机器-panel类型- 拨码 -> stDete.
* U_SIGN_bHaveTested;
******************************************************************************/
//panel
U8 BuildToDev_Panel(U8 machine, U8 pnType, U8 pnSequ, TDev_un *pDev)
{
	DevSetInvalid(pDev);
	
	if(  (!jdgDevItem_Legal(U_DEV_ITEM_Machine, machine))
	  || (!bPnSequIsValid(pnType, pnSequ))
	  )
	{
		return FALSE;
	}
	
	pDev->stDete.machine = machine;
	pDev->stDete.pnType = pnType;
	pDev->stDete.pnSequ = pnSequ;

	pDev->stDete.eventSubject = U_EVT_SUBJECT_BOARD;
	return TRUE;
}

U8 BuildToDev_Me_Panel(U8 pnType, U8 pnSequ, TDev_un *pDev)
{
	return BuildToDev_Panel(U_MACHINE_SELF, pnType, pnSequ, pDev);
}

/******************************************************************************
* FUNC: // //panel modu
******************************************************************************/

U8 BuildToDev_PnModu(U8 machine, U8 pnType, U8 pnSequ, U8 moduNum, TDev_un *pDev)
{
	if(!BuildToDev_Panel(machine, pnType, pnSequ, pDev))
	{
		return FALSE;
	}
	
	if(!jdgDevItem_Legal(U_DEV_ITEM_modu, moduNum))
	{
		return FALSE;
	}
	pDev->pnModu.modu = moduNum;
	
	pDev->stDete.eventSubject = U_EVT_SUBJECT_BOARD;
	return TRUE;
	
}

U8 BuildToDev_Me_PnModu(U8 pnType, U8 pnSequ, U8 moduNum, TDev_un *pDev)
{
	return BuildToDev_PnModu(U_MACHINE_SELF, pnType, pnSequ, moduNum, pDev);
}

/******************************************************************************
* FUNC: // panel modu line
******************************************************************************/

U8 BuildToDev_PnMduLine(U8 machine, U8 pnType, U8 pnSequ, U8 moduNum, U8 pnModuLine, TDev_un *pDev)
{
	if(!BuildToDev_Panel(machine, pnType, pnSequ, pDev))
	{
		return FALSE;
	}
	
	if(!jdgDevItem_Legal(U_DEV_ITEM_modu, moduNum))
	{
		return FALSE;
	}
	pDev->pnModu.modu = moduNum;
	
	if(!jdgDevItem_Legal(U_DEV_ITEM_mduLine, pnModuLine))
	{
		return FALSE;
	}
	pDev->pnModu.mduLine = pnModuLine;
	
	
	pDev->stDete.eventSubject = U_EVT_SUBJECT_FIELD;
	return TRUE;
	
}

U8 BuildToDev_Me_PnMduLine(U8 pnType, U8 pnSequ, U8 moduNum, U8 pnModuLine, TDev_un *pDev)
{
	return BuildToDev_PnMduLine(U_MACHINE_SELF, pnType, pnSequ, moduNum, pnModuLine, pDev);
	
}

/******************************************************************************
* FUNC: // 回路现场部件Dete
* U_SIGN_bHaveTested
******************************************************************************/

U8 BuildToDev_DeteMLA(U8 machine, U8 loop, U32 addr, TDev_un *pDev)
{
	// DevSetInvalid(pDev);
U8 pnSequ;
U8 moduNum;

	CacuDetePnSequAndBdLoop(loop, &pnSequ, &moduNum);
	if(!BuildToDev_Panel(machine, U_PN_Loop_TYPE, pnSequ, pDev))
	{
		return FALSE;
	}
	if(!jdgDevItem_Dete_Legal(loop, addr))
	{
		return FALSE;
	}
	
	pDev->stDete.boardLoop = moduNum;
	pDev->stDete.field = addr;
		
	pDev->stDete.eventSubject = U_EVT_SUBJECT_FIELD;
	return TRUE;
	
}

U8 BuildToDev_Me_DeteMLA(U8 loop, U32 addr, TDev_un *pDev)
{
	return BuildToDev_DeteMLA(U_MACHINE_SELF, loop, addr, pDev);
}

//------------------------------
// U_SIGN_bHaveTested
U8 BuildToDev_DeteMLAC(U8 machine, U8 loop, U32 addr, U8 channel, TDev_un *pDev)
{
	
	// DevSetInvalid(pDev);
	if(!BuildToDev_DeteMLA(machine, loop, addr, pDev))
	{
		return FALSE;
	}
	
	if(!jdgDevItem_Legal(U_DEV_ITEM_channel, channel))
	{
		return FALSE;
	}
	pDev->stDete.channel = channel;
	
	
	pDev->stDete.eventSubject = U_EVT_SUBJECT_FIELD;
	return TRUE;
	
}

U8 BuildToDev_Me_DeteMLAC(U8 loop, U32 addr, U8 channel, TDev_un *pDev)
{
	return BuildToDev_DeteMLAC(U_MACHINE_SELF, loop, addr, channel, pDev);
}


/******************************************************************************
* FUNC: //主电备电
*   IN: power = U_Power_MduFunc_pwrMain, 
******************************************************************************/

U8 BuildToDev_Power(U8 machine, U8 power, TDev_un *pDev)
{
	if(!BuildToDev_Panel(machine, U_PN_Power_TYPE, 1, pDev))
	{
		return FALSE;
	}
	
	if(!jdgDevItem_Legal(U_DEV_ITEM_mduLine, power))
	{
		return FALSE;
	}
	pDev->pnModu.mduLine = power;
	
	pDev->stDete.eventSubject = U_EVT_SUBJECT_BOARD;
	return TRUE;
}

U8 BuildToDev_Me_Power(U8 power, TDev_un *pDev)
{
	return BuildToDev_Power(U_MACHINE_SELF, power,pDev);
}

/******************************************************************************
* FUNC: //flash
*   IN: flsItem = U_Fls_MduFunc_Config ... 
******************************************************************************/

U8 BuildToDev_PnFlash(U8 machine, U8 pnType, U8 pnSequ, 
						U8 flsItem, U8 mPart, TDev_un *pDev)
{
	
	if(!BuildToDev_Panel(machine, pnType, pnSequ, pDev))
	{
		return FALSE;
	}
	
	if(!jdgDevItem_Legal(U_DEV_ITEM_mduLine, flsItem))
	{
		return FALSE;
	}
	pDev->pnModu.mduLine = flsItem;
	
	
	pDev->stDete.eventSubject = U_EVT_SUBJECT_BOARD;
	return TRUE;
}

U8 BuildToDev_Me_Flash(U8 flsItem, U8 mPart, TDev_un *pDev) //本机本板
{
	return BuildToDev_PnFlash(U_MACHINE_SELF, U_PN_Opea_TYPE, 1, flsItem, mPart, pDev);
}



/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
* U_SIGN_bHaveTested;
******************************************************************************/
BOOL bDevCompare(TDev_un  *pDev1, TDev_un  *pDev2)
{
U8 *pByteDev1 = (U8 *)(pDev1);
U8 *pByteDev2 = (U8 *)(pDev2);
U8 ii;
	
	for(ii=0; ii<U_DEV_ADDR_BYTE_MAX; ii++)
	{
		if(*pByteDev1 != *pByteDev2)
		{
			return FALSE;
		}
		pByteDev1++;
		pByteDev2++;
	}
	return TRUE;
}



/******************************************************************************
* FUNC: // 比较，带mask.
*   IN:  mDevItem<U_DEV_ITEM_MAX; 小于mDevItem的都需要匹配。
*  USE: cstStDevStructProp[U_DEV_ITEM_MAX]
* U_SIGN_bHaveTested
******************************************************************************/
BOOL bDevCompMask(U8 mDevItem, TDev_un  *pDev1, TDev_un  *pDev2)
{
U32 mMaskBits = 0;
U8 ii;
U32 mDWordDev1;
U32 mDWordDev2;
	
	if(mDevItem >= U_DEV_ITEM_MAX)
	{
		return FALSE;
	}
	if(pDev1->pnModu.machine != pDev2->pnModu.machine)
	{
		return FALSE;
	}
	
	
	if(mDevItem == U_DEV_ITEM_Machine)
	{
		return TRUE;
	}
	
	mDWordDev1 = ComposeDWord_fromDev_NoMachine(pDev1);
	mDWordDev2 = ComposeDWord_fromDev_NoMachine(pDev2);
	
	for(ii=U_DEV_ITEM_pnType; ii<=mDevItem; ii++)
	{
		mMaskBits |= cstStDevStructProp[ii].mask;
	}
	
	return ((mDWordDev1 & mMaskBits) == (mDWordDev2 & mMaskBits));
}




/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
* 小端
* // U_SIGN_bHaveTested;
******************************************************************************/
void ComposeDev_fromBytes(U8 *pByte, TDev_un  *pRtnDev)
{
#if U_Sys_Endian == U_Sys_Little_Endian
U8 *pByteRtnDev = (U8 *)(pRtnDev);
U8 ii;

	for(ii=0; ii<U_DEV_ADDR_BYTE_MAX; ii++)
	{
		*pByteRtnDev = *pByte;
		pByte++;
		pByteRtnDev++;
	}
#endif //U_Sys_Endian
}


/******************************************************************************
* FUNC: //
// U_SIGN_bHaveTested;
******************************************************************************/
void ComposeBytes_fromDev(TDev_un  *pDev, U8 *pRtnByte)
{
#if U_Sys_Endian == U_Sys_Little_Endian
U8 *pByte = (U8 *)(pDev);
U8 ii;

	for(ii=0; ii<U_DEV_ADDR_BYTE_MAX; ii++)
	{
		*pRtnByte = *pByte;
		pRtnByte++;
		pByte++;
	}
#endif //U_Sys_Endian
}

/******************************************************************************
* FUNC: //
// U_SIGN_bHaveTested;
******************************************************************************/
U32 ComposeDWord_fromDev_NoMachine(TDev_un  *pDev)
{
U32 mDWord = 0;
#if U_Sys_Endian == U_Sys_Little_Endian
U8 *pByte = (U8 *)(pDev);
	
	mDWord  = *pByte;  			pByte++;
	mDWord |= (*pByte << 8);  	pByte++;
	mDWord |= (*pByte << 16);  	pByte++;
	mDWord |= (*pByte << 24);  	pByte++;
	
#endif //U_Sys_Endian
	return mDWord;
}

/******************************************************************************
* FUNC: //END
*   IN:
*  OUT: 
******************************************************************************/

