#ifndef __saveHistPoint_H__
#define __saveHistPoint_H__
/******************************************************************************
* @file    saveHistPoint.h
* @author  yx
* @version V1.0
* @date    2013-07-08
* @brief   ������ʷ��¼��ָ�룬��ʷ��¼ÿ����1sector����һ�Ρ���powerOffһ������
* @master  historyWrite.c
* 
#include  "saveHistPoint.h"
******************************************************************************/
//
#include  "prjCompileCon.h"
#include  "strFlsAdrDef.h"
#include  "strFlsItmStruct.h"

/*================= extern ============================================*/
#ifdef  __saveHistPoint_C__
#define EX_saveHistPoint
#else
#define EX_saveHistPoint extern 
#endif
/*================= ���� ============================================*/
enum emSaveHistPointStep{
	U_SaveHistPointStep_01_Start = 1,
	U_SaveHistPointStep_02_EraseNextSector = 2,
	U_SaveHistPointStep_03_WriteSectorHead = 3,
	U_SaveHistPointStep_04_WriteNew = 4,
	U_SaveHistPointStep_05_NextSectorHead = 5,
	U_SaveHistPointStep_06_Finish = 6,
};
/*================= �ṹ�嶨�� ======================================*/

/*================= ���нṹ�������� ================================*/

typedef struct{
	U8 bOpeaIng;
	U8 step;
	BOOL bNeedEraseNextSector;
	U32 adrSectNext;
	
	U8 mHistCls;
	U8 mFlsItem;
	U8 mPart;  //ָ���part
	TFlsItemAddr stAdr;
	
	//��д��ĵ�ַ
	THistPoint_un unNewAdr; //U_FLS_1HistPoint_BYTE_MAX
	
}TSaveHistPoint_st;


/*================= ˽�к������� ====================================*/
#ifdef  __saveHistPoint_C__

static TSaveHistPoint_st  stHistPt;

void flsWr_histPoint_SectorHead(void); //д sectorNext.head

static void wrHp_Step_01_Start(void);
static void wrHp_Step_02_EraseNextSector(void);
static void wrHp_Step_03_WriteSectorHead(void);
static void wrHp_Step_04_WriteNew(void);
static void wrHp_Step_05_NextSectorHead(void);

#endif  //__saveHistPoint_C__

/*================= ���к�������-lib�ڲ� ====================================*/

EX_saveHistPoint void FlsWr_HistPoint_Init(void);
EX_saveHistPoint BOOL FlsWr_HistPoint_New(U8 mHistCls,  
						U8 mHistPart, U8 mPointPart,
						TFlsQueuePoint_st  mStHistPoint);
EX_saveHistPoint void FlsWr_HistPoint_Exec(void);

EX_saveHistPoint void FlsWr_HistPoint_SetFinish(void);
EX_saveHistPoint BOOL bFlsWr_HistPoint_Finished(void);
EX_saveHistPoint BOOL bFlsWr_HistPoint_isIdle(void);


/******************************************************************************
// END :
******************************************************************************/
#endif // __saveHistPoint_H__

