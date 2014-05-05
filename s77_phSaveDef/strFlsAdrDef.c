#define __strFlsAdrDef_C__
/******************************************************************************
* @file    strFlsAdrDef.c
* @author  yx
* @version V1.2
* @date    2013-09-04 
* @brief   flash空间分配
* 
******************************************************************************/
#include  "strFlsAdrDef.h"

#include  "flsStoreBytesDef.h"
#include  "historyClsDef.h"
//#include "incFile.h"	
#include  "codeComm.h"
#include  "hwEx21_SST39vf800A.h"

/*================= 常数 ============================================*/

#define U_FlsSave_Part0   0 
#define U_FlsSave_Part1   1 

#define U_FlsSave_Part_MAX   2  // U8 mFlsPart;

#define U_FlsSave_Item_MAX   0x28  //U8 mFlsItem;
/*================= 结构体定义 ======================================*/


typedef struct{
	U8  bHaveShare;
	U8  mFlsItem;
	struct{
		U8  chip;
		U32 adrS;
		U32 adrE;
	}adr[U_FlsSave_Part_MAX];
}TFlashAssign_st;

/*================= 常数定义 ======================================*/

/******************************************************************************
* FUNC: //

//改变以后需要修改：
// cstStFlashAssign[]; 
// U32 GetFlsItemBufBytes(U8 mFlsItem);
// Exec_SaveTask();
// emFlsItem :
******************************************************************************/
#define U_FlsSave_HistPart0Point_Start  0x14 // 6*2=12种，每种2sector, = 24*4K=48K
#define U_FlsSave_HistPart0Point_END    (U_FlsSave_HistPart0Point_Start + U_HIST_CLASS_MAX)
#define U_FlsSave_HistPart1Point_Start  0x1A
#define U_FlsSave_HistPart1Point_END    (U_FlsSave_HistPart1Point_Start + U_HIST_CLASS_MAX)

#define U_FlsSave_Hist_Start  0x20
#define U_FlsSave_Hist_END    (U_FlsSave_Hist_Start + U_HIST_CLASS_MAX)


enum emFlsItem
{
	// OnePageSave:
	U_FlsSave_MeStatus = 4,
	U_FlsSave_PnConfig = 1,
	U_FlsSave_NetMachine = 6,
	U_FlsSave_MachProbat = 3,
	U_FlsSave_UserLogin = 5,
	
	
	U_FlsSave_Disable = 2,
	
	U_FlsSave_Field = 7,
	U_FlsSave_Note = 0x08,
	U_FlsSave_MachAlarmNote = 0x09,
	
#if U_SYS_Test_Flash_InqPoint == 1
	U_FlsSave_Sim = 0x0D,
#endif
	
	U_FlsSave_LinkProg = 0x0E,
	U_FlsSave_ManuProg = 0x0F,
	U_FlsSave_RelateDete = 0x10,
	U_FlsSave_ExtgZoneConfig = 0x12,
	
	U_FlsSave_PowerOff = 0x13,
	
	U_FlsSave_BeforeHist = 0x14,
	//U_FlsSave_HistPart0Point_Start = 0x14
	//U_FlsSave_HistPart1Point_Start = 0x1A
	
	//U_FlsSave_Hist_Start = 0x20 
	
};  
// U_FlsSave_Item_MAX
/*================= //历史记录： ======================================*/
#if U_SYS_Test_Flash_Hist == 1 
	#define U_1HistCls_SectMAX  0x02
#else
	#define U_1HistCls_SectMAX  0x10 // 0x100*0x20条=0x2000条 = 2*4K=8K.
#endif 

#define U_HIST_STORE_PART_MAX  2  //mHistPart

/*================= //历史记录指针： ======================================*/
#define U_HistPoint_STORE_PART_MAX  2  //mPointPart

#define U_1HistClsPoint_SectMAX  2
/*================= //LinkProg： ======================================*/
// 0x1000 存 16条， 1回路256条需要 0x10 sector. 
#define U_LinkProg_SectMAX  0x40  // 64*4=0x100, *0x100 = 0x10,000.
#define U_ManuProg_SectMAX  0x08  // 8Sector 共存 128条。
/*================= //Note： ======================================*/
// 每地址0x20字节，0x1000 存 0x80 条，一回路够了。
// 另外有 主机的报警点 需要存注释。
#define U_Note_SectMAX  0x08  // U_FlsSave_Note
/*================= //PowerOff： ======================================*/
#define U_PowerOff_SectMAX  2

/*================= 结构定义 ========================================*/
/*

参考1：一台控制器的注释需要的字节： 
256点/回路 * 64回路 * 32字节/点 =  0x100 * 0x40 * 0x20 = 0x80000 = 0x200K = 512K =0.5M.

参考2：6种每种5000条历史记录的容量(不存注释的情况，若存注释，* 3)：
0x1400 = 5120 .
16字节/条 * 0x1400 * 6 = 0x10 * 0x1400 * 6 = 0x14000 * 6 = 0x50K * 6 = 0x1E0K = 480K .
// 历史记录： 0x1400=5120条 = 5K, 5K*0x10= 0x50K  用 0x80K. 0x400K/0x80K = 8

*/

#define U_IdleFlsS  (0x0FF*SecBytes)
#define U_IdleFlsE  (0x100*SecBytes)

const TFlashAssign_st cstStFlashAssign[U_FlsSave_Item_MAX] =
{ 
//bHaveShare, chip1, adrS1, adrE1, 		chip2, adrS2, adrE2
{1 ,U_FlsSave_MeStatus,
  {{0,(  0*SecBytes),(  1*SecBytes)}, {U_SST39VF900A_U8,(  0*SecBytes),(  1*SecBytes)}} }, // U_FlsSave_MeStatus = 0,
{1 ,U_FlsSave_PnConfig,
  {{0,(  1*SecBytes),(  2*SecBytes)}, {U_SST39VF900A_U8,(  1*SecBytes),(  2*SecBytes)}} }, // U_FlsSave_PnConfig = 1,
{1 ,U_FlsSave_Disable,
  {{0,(  2*SecBytes),(  3*SecBytes)}, {U_SST39VF900A_U8,(  2*SecBytes),(  3*SecBytes)}} }, // U_FlsSave_Disable = 2,
{1 ,U_FlsSave_MachProbat,
  {{0,(  3*SecBytes),(  4*SecBytes)}, {U_SST39VF900A_U8,(  3*SecBytes),(  4*SecBytes)}} }, // U_FlsSave_MachProbat = 3,

{1 ,U_FlsSave_UserLogin,
  {{0,(  5*SecBytes),(  6*SecBytes)}, {U_SST39VF900A_U8,(  5*SecBytes),(  6*SecBytes)}} }, // U_FlsSave_UserLogin = 5,
{1 ,U_FlsSave_NetMachine,
  {{0,(  6*SecBytes),(  7*SecBytes)}, {U_SST39VF900A_U8,(  6*SecBytes),(  7*SecBytes)}} }, // U_FlsSave_NetMachine = 6,
{1 ,U_FlsSave_Field,
  {{0,(  7*SecBytes),(  8*SecBytes)}, {U_SST39VF900A_U8,(  7*SecBytes),(  8*SecBytes)}} }, // U_FlsSave_Field = 7,

{1 ,U_FlsSave_RelateDete,
  {{0,(  8*SecBytes),(  9*SecBytes)}, {U_SST39VF900A_U8,(  8*SecBytes),(  9*SecBytes)}} }, // U_FlsSave_RelateDete = 0x0C,
{1 ,U_FlsSave_ExtgZoneConfig,
  {{0,(  9*SecBytes),(0x0A*SecBytes)}, {U_SST39VF900A_U8,( 9*SecBytes),(0x0A*SecBytes)}} }, // U_FlsSave_ExtgZoneConfig = 0x0E,

  
  
  
#if U_SYS_Test_Flash_InqPoint == 1
// {1 ,U_FlsSave_Sim,
    // {{0,((U_SimFlsPoit_AdrS) + ((0*U_InqPoint_FlsItem_SectMAX)*U_SimFlsPoit_1SectorBytes)), // U_FlsSave_Sim = 0x0E
		// ((U_SimFlsPoit_AdrS) + ((1*U_InqPoint_FlsItem_SectMAX)*U_SimFlsPoit_1SectorBytes))}, 
     // {U_SST39VF900A_U8,((U_SimFlsPoit_AdrS) + ((0*U_InqPoint_FlsItem_SectMAX)*U_SimFlsPoit_1SectorBytes)),
		// ((U_SimFlsPoit_AdrS) + ((1*U_InqPoint_FlsItem_SectMAX)*U_SimFlsPoit_1SectorBytes))}  } }, 
{1 ,U_FlsSave_Sim,
  {{0,(0x0D*SecBytes),(0x0D*SecBytes + U_SimFlsPoit_1SectorBytes)}, 
   {U_SST39VF900A_U8,(0x0D*SecBytes),(0x0D*SecBytes + U_SimFlsPoit_1SectorBytes)}} }, // U_FlsSave_Sim,

#else

#endif

{1 ,U_FlsSave_Note,
  {{0,(0x0E*SecBytes),(0x12*SecBytes)}, 
   {U_SST39VF900A_U8,(0x0E*SecBytes),(0x12*SecBytes)}} }, //  U_FlsSave_Note
{1 ,U_FlsSave_MachAlarmNote,
  {{0,(0x12*SecBytes),(0x16*SecBytes)}, 
   {U_SST39VF900A_U8,(0x12*SecBytes),(0x16*SecBytes)}} }, //  U_FlsSave_MachAlarmNote

		

{1 ,U_FlsSave_PowerOff,
    {{0,((0x16*SecBytes) + ((0*U_PowerOff_SectMAX)*SecBytes)), // U_FlsSave_PowerOff 
		((0x16*SecBytes) + ((1*U_PowerOff_SectMAX)*SecBytes))}, 
     {U_SST39VF900A_U8,((0x16*SecBytes) + ((0*U_PowerOff_SectMAX)*SecBytes)),
		((0x16*SecBytes) + ((1*U_PowerOff_SectMAX)*SecBytes))}  } }, 
		
{1 ,U_FlsSave_LinkProg,
    {{0,((0x18*SecBytes) + ((0*U_LinkProg_SectMAX)*SecBytes)), // U_FlsSave_LinkProg 
		((0x18*SecBytes) + ((1*U_LinkProg_SectMAX)*SecBytes))}, //排在联动编程后面
     {U_SST39VF900A_U8,((0x18*SecBytes) + ((0*U_LinkProg_SectMAX)*SecBytes)),
		((0x18*SecBytes) + ((1*U_LinkProg_SectMAX)*SecBytes))}  } }, 
		
{1 ,U_FlsSave_ManuProg,
    {{0,((0x58*SecBytes) + ((0*U_ManuProg_SectMAX)*SecBytes)), // U_FlsSave_ManuProg
		((0x58*SecBytes) + ((1*U_ManuProg_SectMAX)*SecBytes))}, //排在联动编程后面
     {U_SST39VF900A_U8,((0x58*SecBytes) + ((0*U_ManuProg_SectMAX)*SecBytes)),
		((0x58*SecBytes) + ((1*U_ManuProg_SectMAX)*SecBytes))}  } }, 
		// 
		
		
// U_FlsSave_HistPart0Point_Start = 
{1 ,U_FlsSave_HistPart0Point_Start+0,
	{{0,((0x60*SecBytes) + ((0*U_1HistClsPoint_SectMAX)*SecBytes)), // + 0
		((0x60*SecBytes) + ((1*U_1HistClsPoint_SectMAX)*SecBytes))}, 
     {U_SST39VF900A_U8,((0x60*SecBytes) + ((0*U_1HistClsPoint_SectMAX)*SecBytes)),
		((0x60*SecBytes) + ((1*U_1HistClsPoint_SectMAX)*SecBytes))}  } }, 
{1 ,U_FlsSave_HistPart0Point_Start+1,
	{{0,((0x60*SecBytes) + ((1*U_1HistClsPoint_SectMAX)*SecBytes)), // + 1
		((0x60*SecBytes) + ((2*U_1HistClsPoint_SectMAX)*SecBytes))}, 
     {U_SST39VF900A_U8,((0x60*SecBytes) + ((1*U_1HistClsPoint_SectMAX)*SecBytes)),
		((0x60*SecBytes) + ((2*U_1HistClsPoint_SectMAX)*SecBytes))}  } }, 
{1 ,U_FlsSave_HistPart0Point_Start+2,
	{{0,((0x60*SecBytes) + ((2*U_1HistClsPoint_SectMAX)*SecBytes)), // + 2
		((0x60*SecBytes) + ((3*U_1HistClsPoint_SectMAX)*SecBytes))}, 
     {U_SST39VF900A_U8,((0x60*SecBytes) + ((2*U_1HistClsPoint_SectMAX)*SecBytes)),
		((0x60*SecBytes) + ((3*U_1HistClsPoint_SectMAX)*SecBytes))}  } }, 
{1 ,U_FlsSave_HistPart0Point_Start+3,
	{{0,((0x60*SecBytes) + ((3*U_1HistClsPoint_SectMAX)*SecBytes)), // + 3
		((0x60*SecBytes) + ((4*U_1HistClsPoint_SectMAX)*SecBytes))}, 
     {U_SST39VF900A_U8,((0x60*SecBytes) + ((3*U_1HistClsPoint_SectMAX)*SecBytes)),
		((0x60*SecBytes) + ((4*U_1HistClsPoint_SectMAX)*SecBytes))}  } }, 
{1 ,U_FlsSave_HistPart0Point_Start+4,
	{{0,((0x60*SecBytes) + ((4*U_1HistClsPoint_SectMAX)*SecBytes)), // + 4
		((0x60*SecBytes) + ((5*U_1HistClsPoint_SectMAX)*SecBytes))}, 
     {U_SST39VF900A_U8,((0x60*SecBytes) + ((4*U_1HistClsPoint_SectMAX)*SecBytes)),
		((0x60*SecBytes) + ((5*U_1HistClsPoint_SectMAX)*SecBytes))}  } }, 
{1 ,U_FlsSave_HistPart0Point_Start+5,
	{{0,((0x60*SecBytes) + ((5*U_1HistClsPoint_SectMAX)*SecBytes)), // + 5
		((0x60*SecBytes) + ((6*U_1HistClsPoint_SectMAX)*SecBytes))}, 
     {U_SST39VF900A_U8,((0x60*SecBytes) + ((5*U_1HistClsPoint_SectMAX)*SecBytes)),
		((0x60*SecBytes) + ((6*U_1HistClsPoint_SectMAX)*SecBytes))}  } }, 
		
// U_FlsSave_HistPart1Point_Start = 
{1 ,U_FlsSave_HistPart1Point_Start+0,
	{{0,((0x60*SecBytes) + ((8*U_1HistClsPoint_SectMAX)*SecBytes)), // + 0
		((0x60*SecBytes) + ((9*U_1HistClsPoint_SectMAX)*SecBytes))}, 
     {U_SST39VF900A_U8,((0x60*SecBytes) + ((8*U_1HistClsPoint_SectMAX)*SecBytes)),
		((0x60*SecBytes) + ((9*U_1HistClsPoint_SectMAX)*SecBytes))}  } }, 
{1 ,U_FlsSave_HistPart1Point_Start+1,
	{{0,((0x60*SecBytes) + ((9*U_1HistClsPoint_SectMAX)*SecBytes)), // + 1
		((0x60*SecBytes) + ((10*U_1HistClsPoint_SectMAX)*SecBytes))}, 
     {U_SST39VF900A_U8,((0x60*SecBytes) + ((9*U_1HistClsPoint_SectMAX)*SecBytes)),
		((0x60*SecBytes) + ((10*U_1HistClsPoint_SectMAX)*SecBytes))}  } }, 
{1 ,U_FlsSave_HistPart1Point_Start+2,
	{{0,((0x60*SecBytes) + ((10*U_1HistClsPoint_SectMAX)*SecBytes)), // + 2
		((0x60*SecBytes) + ((11*U_1HistClsPoint_SectMAX)*SecBytes))}, 
     {U_SST39VF900A_U8,((0x60*SecBytes) + ((10*U_1HistClsPoint_SectMAX)*SecBytes)),
		((0x60*SecBytes) + ((11*U_1HistClsPoint_SectMAX)*SecBytes))}  } }, 
{1 ,U_FlsSave_HistPart1Point_Start+3,
	{{0,((0x60*SecBytes) + ((11*U_1HistClsPoint_SectMAX)*SecBytes)), // + 3
		((0x60*SecBytes) + ((12*U_1HistClsPoint_SectMAX)*SecBytes))}, 
     {U_SST39VF900A_U8,((0x60*SecBytes) + ((11*U_1HistClsPoint_SectMAX)*SecBytes)),
		((0x60*SecBytes) + ((12*U_1HistClsPoint_SectMAX)*SecBytes))}  } }, 
{1 ,U_FlsSave_HistPart1Point_Start+4,
	{{0,((0x60*SecBytes) + ((12*U_1HistClsPoint_SectMAX)*SecBytes)), // + 4
		((0x60*SecBytes) + ((13*U_1HistClsPoint_SectMAX)*SecBytes))}, 
     {U_SST39VF900A_U8,((0x60*SecBytes) + ((12*U_1HistClsPoint_SectMAX)*SecBytes)),
		((0x60*SecBytes) + ((13*U_1HistClsPoint_SectMAX)*SecBytes))}  } }, 
{1 ,U_FlsSave_HistPart1Point_Start+5,
	{{0,((0x60*SecBytes) + ((13*U_1HistClsPoint_SectMAX)*SecBytes)), // + 5
		((0x60*SecBytes) + ((14*U_1HistClsPoint_SectMAX)*SecBytes))}, 
     {U_SST39VF900A_U8,((0x60*SecBytes) + ((13*U_1HistClsPoint_SectMAX)*SecBytes)),
		((0x60*SecBytes) + ((14*U_1HistClsPoint_SectMAX)*SecBytes))}  } }, 
		
		
// U_FlsSave_Hist_Start = 0x20, 1cls占0x20*SecBytes = 0x20000 = 128K.  128K*8= 1M
{1 ,U_FlsSave_Hist_Start+0,
    {{0,((0x80 + (0*U_1HistCls_SectMAX))*SecBytes), // U_FlsSave_Hist_Alarm
		((0x80 + (1*U_1HistCls_SectMAX))*SecBytes)}, 
     {U_SST39VF900A_U8,((0x80 + (0*U_1HistCls_SectMAX))*SecBytes),
		((0x80 + (1*U_1HistCls_SectMAX))*SecBytes)}  } }, 
{1 ,U_FlsSave_Hist_Start+1,
    {{0,((0x80 + (1*U_1HistCls_SectMAX))*SecBytes), // U_FlsSave_Hist_Fault
		((0x80 + (2*U_1HistCls_SectMAX))*SecBytes)}, 
     {U_SST39VF900A_U8,((0x80 + (1*U_1HistCls_SectMAX))*SecBytes),
		((0x80 + (2*U_1HistCls_SectMAX))*SecBytes)}  } }, 
{1 ,U_FlsSave_Hist_Start+2,
    {{0,((0x80 + (2*U_1HistCls_SectMAX))*SecBytes), // U_FlsSave_Hist_Link
		((0x80 + (3*U_1HistCls_SectMAX))*SecBytes)}, 
     {U_SST39VF900A_U8,((0x80 + (2*U_1HistCls_SectMAX))*SecBytes),
		((0x80 + (3*U_1HistCls_SectMAX))*SecBytes)}  } }, 
{1 ,U_FlsSave_Hist_Start+3,
	{{0,((0x80 + (3*U_1HistCls_SectMAX))*SecBytes), // U_FlsSave_Hist_Opea
		((0x80 + (4*U_1HistCls_SectMAX))*SecBytes)}, 
     {U_SST39VF900A_U8,((0x80 + (3*U_1HistCls_SectMAX))*SecBytes),
		((0x80 + (4*U_1HistCls_SectMAX))*SecBytes)}  } }, 
{1 ,U_FlsSave_Hist_Start+4,
	{{0,((0x80 + (4*U_1HistCls_SectMAX))*SecBytes), // U_FlsSave_Hist_Super
		((0x80 + (5*U_1HistCls_SectMAX))*SecBytes)}, 
     {U_SST39VF900A_U8,((0x80 + (4*U_1HistCls_SectMAX))*SecBytes),
		((0x80 + (5*U_1HistCls_SectMAX))*SecBytes)}  } }, 
{1 ,U_FlsSave_Hist_Start+5,
	{{0,((0x80 + (5*U_1HistCls_SectMAX))*SecBytes), // U_FlsSave_Hist_All 
		((0x80 + (6*U_1HistCls_SectMAX))*SecBytes)}, 
     {U_SST39VF900A_U8,((0x80 + (5*U_1HistCls_SectMAX))*SecBytes),
		((0x80 + (6*U_1HistCls_SectMAX))*SecBytes)}  } }, 
		
		
//
};


/*================= 私有结构变量声明 ================================*/

/*================= 公有函数声明 ====================================*/

/*================= 私有函数声明 ====================================*/
	
/*=================  ================================================*/

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
BOOL bGetFlsCst(U8 mFlsItem, U8 *pRtnFlsItmSequ)
{
U8 ii;
U8 sequ = U_FlsSave_Item_MAX;

	

	*pRtnFlsItmSequ = U_FlsSave_Item_MAX;
	if(mFlsItem >= U_FlsSave_Item_MAX)
	{
		return FALSE;
	}
	
	for(ii=0; ii<U_FlsSave_Item_MAX; ii++)
	{
		if(cstStFlashAssign[ii].mFlsItem == mFlsItem)
		{
			sequ = ii;
			break;
		}
	}
	if(ii >= U_FlsSave_Item_MAX) //未找到
	{
		return FALSE;
	}
	ii += 1;
	//已找到，看看是否有重复定义：
	
	for(; ii<U_FlsSave_Item_MAX; ii++)
	{
		if(cstStFlashAssign[ii].mFlsItem == mFlsItem)
		{
			return FALSE;
		}
	}
	*pRtnFlsItmSequ = sequ;
	return TRUE;
}

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
BOOL getFlsItem_Addr(U8 mFlsItem, U8 mFlsPart, TFlsItemAddr *pRtnAdr)
{
U8 mSequ;

	if(!bGetFlsCst(mFlsItem, &mSequ))
	{
		return FALSE;
	}
	
	if(!bFls_item_share_valid(mSequ, mFlsPart))
	{
		return FALSE;
	}
	pRtnAdr->chip = cstStFlashAssign[mSequ].adr[mFlsPart].chip;
	pRtnAdr->adrS = cstStFlashAssign[mSequ].adr[mFlsPart].adrS;
	pRtnAdr->adrE = cstStFlashAssign[mSequ].adr[mFlsPart].adrE;
	return TRUE;
	
}

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
// if 范围相等:
BOOL bEquFlsItemAddr(TFlsItemAddr *pAdr1, TFlsItemAddr *pAdr2)
{
	return( (pAdr1->chip == pAdr2->chip)
		&&	(pAdr1->adrS == pAdr2->adrS)
		&&	(pAdr1->adrE == pAdr2->adrE)
	  );
}

// if 地址在范围内：
BOOL bInFlsItemAddr(U32 nowAdr, TFlsItemAddr *pAdr)
{
	return( (nowAdr >= pAdr->adrS)
		&&	(nowAdr <  pAdr->adrE)
	  );
}

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
BOOL bFls_item_share_valid(U8 mFlsSequ, U8 mFlsPart)
{
	if(mFlsSequ >= U_FlsSave_Item_MAX)
	{
		return FALSE;
	}
	if(mFlsPart >= U_FlsSave_Part_MAX)
	{
		return FALSE;
	}
	if((mFlsPart == 1)&&(!(cstStFlashAssign[mFlsSequ].bHaveShare)))
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

#if U_SYS_Test_FlsAdrDef == 1
static TFlsItemAddr stAdr[U_FlsSave_Item_MAX];
static U8 bResult[U_FlsSave_Item_MAX];
void Sim_FlsAdrDef(void)
{
U8 ii;

	for(ii=0; ii<U_FlsSave_Item_MAX; ii++)
	{
		bResult[ii] = FALSE;
		if(getFlsItem_Addr(ii, 1, &stAdr[ii]))
		{
			bResult[ii] = TRUE;
		}
	}
	for(ii=U_FlsSave_Hist_Start; ii<U_FlsSave_Hist_Start+6; ii++)
	{
		bResult[ii] = FALSE;
		if(getFlsItem_Addr(ii, 1, &stAdr[ii]))
		{
			bResult[ii] = TRUE;
		}
	}
	bResult[0]=bResult[0];
}
#endif //U_SYS_Test_FlsAdrDef
		
/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/


BOOL bFlsItem_HaveShare(U8 mFlsItem)
{
U8 mSequ;

	if(!bGetFlsCst(mFlsItem, &mSequ))
	{
		return FALSE;
	}

	return cstStFlashAssign[mSequ].bHaveShare;
}

/******************************************************************************
* FUNC: //
******************************************************************************/
// flsItem part max
U8 FlsItem_PartMax(U8 mFlsItem) //
{
	if(bFlsItemIsHist(mFlsItem))
	{
		return FlsHistPartMax();
	}
	else if(bFlsItemIs_hstPoint(mFlsItem))
	{
		return FlsHistPointPartMax();
	}
	else
	{
		if(bFlsItem_HaveShare(mFlsItem))
		{
			return GetSaveItmPartMax();
		}
		else
		{
			return 1;
		}
	}
}

/******************************************************************************
* FUNC: //
U32 oneSector_ByteMax;
******************************************************************************/
U32 getFlsItem_1SectorBytes(U8 mFlsItem)
{
#if U_SYS_Test_Flash_InqPoint == 1
	if(mFlsItem == U_SimFlsPoit_FlsItmCls)
	{
		return U_SimFlsPoit_1SectorBytes;
	}
#endif // U_SYS_Test_Flash_InqPoint

	return U_FLASH_1_SECTOR;
}

/******************************************************************************
* FUNC: //
******************************************************************************/

U32 getFlsItem_Chip(U8 mFlsItem, U8 mFlsPart)
{
U8 mSequ;

	if(!bGetFlsCst(mFlsItem, &mSequ))
	{
		return ~0;
	}
	
	if(!bFls_item_share_valid(mSequ, mFlsPart))
	{
		return ~0;
	}	
	return cstStFlashAssign[mSequ].adr[mFlsPart].chip;
}

/******************************************************************************
* FUNC: //
******************************************************************************/
U32 getFlsItem_AdrS(U8 mFlsItem, U8 mFlsPart)
{
U8 mSequ;

	if(!bGetFlsCst(mFlsItem, &mSequ))
	{
		return ~0;
	}
	
	if(!bFls_item_share_valid(mSequ, mFlsPart))
	{
		return ~0;
	}	
	return cstStFlashAssign[mSequ].adr[mFlsPart].adrS;
}

/******************************************************************************
* FUNC: //
******************************************************************************/
U32 getFlsItem_AdrE(U8 mFlsItem, U8 mFlsPart)
{
U8 mSequ;

	if(!bGetFlsCst(mFlsItem, &mSequ))
	{
		return ~0;
	}
	
	if(!bFls_item_share_valid(mSequ, mFlsPart))
	{
		return ~0;
	}	
	return cstStFlashAssign[mSequ].adr[mFlsPart].adrE;
}


/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
U8 getFlsItem_hist(U8 mHistCls)
{
	return (U_FlsSave_Hist_Start + mHistCls);
}

BOOL bFlsItemIsHist(U8 mflsItem)
{
	return (bInDomain(mflsItem, 	U_FlsSave_Hist_Start, 
									U_FlsSave_Hist_END)
			);
}

U8 FlsHistPartMax(void)
{
	return U_HIST_STORE_PART_MAX;
}

/******************************************************************************
// public
* FUNC: // 
*   IN: 
*  OUT: 
******************************************************************************/

U8 getFlsItem_hstPart0Point(U8 mHistCls)
{
	return (U_FlsSave_HistPart0Point_Start + mHistCls);
}
U8 getFlsItem_hstPart1Point(U8 mHistCls)
{
	return (U_FlsSave_HistPart1Point_Start + mHistCls);
}

U8 getFlsItem_hstPoint(U8 mHistCls, U8 mHistPart)
{
	if(mHistPart == 0)
	{
		return (U_FlsSave_HistPart0Point_Start + mHistCls);
	}
	else
	{
		return (U_FlsSave_HistPart1Point_Start + mHistCls);
	}
}



/******************************************************************************
* FUNC: // 
******************************************************************************/
BOOL bFlsItemIs_hstPart0Point(U8 mFlsItem)
{
	return (bInDomain(mFlsItem, 	U_FlsSave_HistPart0Point_Start, 
									U_FlsSave_HistPart0Point_END)
			);
}

BOOL bFlsItemIs_hstPart1Point(U8 mFlsItem)
{
	return (bInDomain(mFlsItem, 	U_FlsSave_HistPart1Point_Start, 
									U_FlsSave_HistPart1Point_END)
			);
}

BOOL bFlsItemIs_hstPoint(U8 mflsItem)
{
	if( (bFlsItemIs_hstPart0Point(mflsItem))
	  ||(bFlsItemIs_hstPart1Point(mflsItem))
	  )
	{
		return TRUE;
	}
	return FALSE;
}




/******************************************************************************
* FUNC: // 
******************************************************************************/
U8 FlsHistPointPartMax(void)
{
	return U_HistPoint_STORE_PART_MAX;
}

/******************************************************************************
* FUNC: 历史记录之前的flsItem 的 MAX.
	 历史记录因为要与指针存储对应，特殊处理。
*   IN:
*  OUT: 
******************************************************************************/

U8 getFlsItem_BeforeHist(void)
{
	return U_FlsSave_BeforeHist;
}

/******************************************************************************
* FUNC: // 
*   IN: emFlsItem:
*  OUT: 
******************************************************************************/
BOOL bFlsItemIs_OnePageSave(U8 mFlsItem)
{
	if(  (mFlsItem == U_FlsSave_MeStatus)
	  || (mFlsItem == U_FlsSave_PnConfig)
	  || (mFlsItem == U_FlsSave_NetMachine)
	  || (mFlsItem == U_FlsSave_UserLogin)
	  || (mFlsItem == U_FlsSave_MachProbat)
	  || (mFlsItem == U_FlsSave_ExtgZoneConfig)
	  )
	{
		return TRUE;
	}
	return FALSE;
}

BOOL bFlsItemIs_Disable(U8 mFlsItem)
{
	if(  (mFlsItem == U_FlsSave_Disable))
	{
		return TRUE;
	}
	return FALSE;
}

U8 getFlsItem_MeStatus(void)
{
	return U_FlsSave_MeStatus;
}
U8 getFlsItem_PnConfig(void)
{
	return U_FlsSave_PnConfig;
}
U8 getFlsItem_NetMachine(void)
{
	return U_FlsSave_NetMachine;
}
U8 getFlsItem_MachProbat(void)
{
	return U_FlsSave_MachProbat;
}
U8 getFlsItem_UserLogin(void)
{
	return U_FlsSave_UserLogin;
}

U8 getFlsItem_Disable(void)
{
	return U_FlsSave_Disable;
}
U8 getFlsItem_Field(void)
{
	return U_FlsSave_Field;
}

U8 getFlsItem_Note(void)
{
	return U_FlsSave_Note;
}
U8 getFlsItem_MachAlarmNote(void)
{
	return U_FlsSave_MachAlarmNote;
}

#if U_SYS_Test_Flash_InqPoint == 1
U8 getFlsItem_Sim(void)
{
	return U_FlsSave_Sim;
}
#endif

U8 getFlsItem_LinkProg(void)
{
	return U_FlsSave_LinkProg;
}
U8 getFlsItem_ManuProg(void)
{
	return U_FlsSave_ManuProg;
}
U8 getFlsItem_PowerOff(void)
{
	return U_FlsSave_PowerOff;
}

U8 getFlsItem_RelateDete(void)
{
	return U_FlsSave_RelateDete;
}

U8 getFlsItem_ExtgZoneConfig(void)
{
	return U_FlsSave_ExtgZoneConfig;
}



/******************************************************************************
* FUNC: // 
*   IN: 
*  OUT: 
******************************************************************************/


U8 getFlsItem_SectorMax(U8 mFlsItem)
{
	if(mFlsItem < U_FlsSave_Item_MAX)
	{
		return ((cstStFlashAssign[mFlsItem].adr[0].adrE
			    -cstStFlashAssign[mFlsItem].adr[0].adrS)
			   / U_FLASH_1_SECTOR);
	}
	return 0;
}

/******************************************************************************
* FUNC: // 
*   IN:
*  OUT: 
******************************************************************************/

// 检查地址范围的定义是否超限
	// cstStFlashAssign[U_FlsSave_Item_MAX];
BOOL bCheckSaveItemConstDef(void)
{
U8 ii;
U8 mPart;

	for(ii=0; ii<U_FlsSave_Item_MAX; ii++)
	{
		if(cstStFlashAssign[ii].bHaveShare >= U_FlsSave_Part_MAX)
		{
			return FALSE;
		}
		for(mPart=0; mPart<U_FlsSave_Part_MAX; mPart++)
		{
			if(  (cstStFlashAssign[ii].adr[mPart].chip >= U_SST39VF900A_CHIP_MAX)
			  || (cstStFlashAssign[ii].adr[mPart].adrS >= NOR_FLASH_SIZE)
			  || (cstStFlashAssign[ii].adr[mPart].adrE >  NOR_FLASH_SIZE)
			  )
			{
				return FALSE;
			}
		}
		
		
	}
	
	return TRUE;
}


U8 GetSaveItemMax(void)
{
	return U_FlsSave_Item_MAX;
}
BOOL bSaveItemValid(U8 mFlsItem)
{
	return (mFlsItem < U_FlsSave_Item_MAX);
}

U8 GetSaveItmPartMax(void)
{
	return U_FlsSave_Part_MAX;
}
BOOL bSaveItmPartValid(U8 mPart)
{
	return (mPart < U_FlsSave_Part_MAX);
}

/******************************************************************************
* FUNC: // END
*   IN:
*  OUT: 
******************************************************************************/
