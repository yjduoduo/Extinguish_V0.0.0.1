#ifndef __flsErase_H__
#define __flsErase_H__
/******************************************************************************
* @file    flsErase.h
* @author  yx
* @version V1.2
* @date    2013-9-22
* @brief   擦除队列，并执行erase.
* @master  应用程序 | 修改前的擦除。
* @master   saveManage.c
* @in:     FlsErase_New() 及其brother;  
*
* @version history
* V1.2，2013.9.22
*		修改FlsErase_WorkIng_MyFlsId(); FlsErase_HaveFinishPercent();
* V1.1  2013-9-3
*		用buf[out]的数据，start时保存到stEraseTask.nowBuf里使用。 2013-9-3 
* 		引入 mIntegratPart
* V1.0  2013-07-23

*	   
* 
#include  "flsErase.h"
******************************************************************************/
//
#include  "prjCompileCon.h"
#include  "strFlsAdrDef.h"
#include  "bufCircle.h"

/*================= extern ============================================*/
#ifdef  __flsErase_C__
#define EX_flsErase
#else
#define EX_flsErase extern 
#endif
/*================= 常数 ============================================*/
//#define 
/*================= 结构体定义 ======================================*/

/*================= 公有结构变量声明 ================================*/

#define U_FlsErase_Item_MAX    10   // U32 mFlsAppSec;
typedef struct
{
	U8 mFlsItem;
	U8 mPart;
	BOOL mIntegratPart; // TRUE=整个的part.
	U8 taskId;  //比如显示任务，或串口通讯任务。
	U8 flsId;
	TFlsItemAddr stEraseAdr;
	U8 percentS; // 在总的flsId的任务里所处的百分比；
	U8 percentE;
}TFlsEraseBuf_st;  //每次申请分配一个。

typedef struct
{
	U8 bOpeaIng;
	
	TFlsEraseBuf_st  nowBuf; // -> stEraseBuf[]
	
	U32 nowSectAdr;
	TFlsItemAddr stEraseAdr;
	
	U32 sectTotal;
	U32 sectHaveFinish;
}TFlsEraseTask_st;  //

/*================= 私有函数声明 ====================================*/
#ifdef  __flsErase_C__

TBufCircle  vCircleFlsEraseBuf; //
TFlsEraseBuf_st  stEraseBuf[U_FlsErase_Item_MAX];

TFlsEraseTask_st stEraseTask;

void init_FlsEraseOneBuf(TFlsEraseBuf_st *pOne);
static void flsErase_SetIdle(void);
static void flsErase_NotificatResult(U8 bSucc);

// 擦除完毕，修改state 和 queue.point.
static void flsErase_Finish(U8 bSucc);


static BOOL bFlsIdIsExistInBuf(U8 mFlsId, U32 *pRtnBuf);
static BOOL bFlsIdIsEraseIng(U8 mFlsId);

static BOOL flsErase_entryBuf(U8 mFlsItem, U8 mPart, 
					U8 taskId, U8 flsId, 
					TFlsItemAddr *pAdr,
					U8 percentS, U8 percentE);
#endif  //__flsErase_C__
/*================= 公有函数声明-lib内部 ====================================*/
//EX_flsErase 

extern void Init_FlsEraseTask(void);

extern BOOL bFlsEraseBuf_Empty(void);
extern BOOL bFlsErase_isIdle(void);

extern BOOL FlsErase_Start(void);
extern void FlsErase_Exec(void);


/*================= 公有函数声明-lib外部 ====================================*/
//EX_flsErase 

// add Erase FlsItem.Part.pAdr 任务 -> eraseBuf[].
extern BOOL FlsErase_New(U8 mFlsItem, U8 mPart, 
						U8 taskId, U8 flsId,
						TFlsItemAddr *pAdr);
// add Erase FlsItem.Part 任务 -> eraseBuf[].
extern BOOL FlsErase_ItemPart_New(U8 mFlsItem, U8 mPart, 
						U8 taskId, U8 flsId);
//整mFlsItem擦除 -> eraseBuf[].
extern BOOL FlsErase_Item_New(U8 mFlsItem, U8 taskId, U8 flsId); 

//是否Erase FlsId, 包括在erase队列里的:
extern BOOL FlsErase_WorkIng_MyFlsId(U8 mFlsId);
//计算完成的百分比
extern U8 FlsErase_HaveFinishPercent(U8 mFlsId); 

/******************************************************************************
// END :
******************************************************************************/
#endif // __flsErase_H__

