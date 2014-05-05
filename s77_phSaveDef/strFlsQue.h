#ifndef __strFlsQue_H__
#define __strFlsQue_H__
/******************************************************************************
* @file    strFlsQue.h
* @author  yx
* @version V1.0
* @date    2013-07-23
* @brief   
* 
#include  "strFlsQue.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

#include  "strFlsAdrDef.h"
/*================= extern ============================================*/
#ifdef  __strFlsQue_C__
#define EX_strFlsQue
#else
#define EX_strFlsQue extern 
#endif
/*================= 常数 ============================================*/


/*================= 结构体定义 ======================================*/

/*================= 公有结构变量声明 ================================*/

typedef struct{
	//flsAddress:
	U32 headAdr; //Flash存储指针。
	U32 endAdr; //Flash存储指针。
}TFlsQueuePoint_st;

typedef struct{
	U8 mFlsItem;
	BOOL bIsQueue;
	U32 pointId;
	U32 itemBytes;
	U32 sectBytes;
	// sectorMax 无用。都用 != sectEnd做判断，为将来动态分配准备。
	TFlsItemAddr stAdr;
}TFlsQueueProp; //队列类型的flsItem存储

/*================= 私有函数声明 ====================================*/
#ifdef  __strFlsQue_C__

#endif  //__strFlsQue_C__
/*================= 公有函数声明 ====================================*/
//EX_strFlsAdrDef
extern U32 GetFlsQueHeadAdr(U8 mFlsItem, U8 mPatNum);
extern U32 GetFlsQueEndAdr(U8 mFlsItem, U8 mPatNum);
extern BOOL GetFlsQueHeadEndAdr(U8 mFlsItem, U8 mFlsPart,
				TFlsQueuePoint_st *pRtnHeadEnd);
extern void SetFlsQueHeadAdr(U8 mFlsItem, U8 mPatNum, U32 flsAdr);
extern void SetFlsQueEndAdr(U8 mFlsItem, U8 mPatNum, U32 flsAdr);

extern BOOL bEqu_FlsQueHeadEnd(TFlsQueuePoint_st *p1, 
					           TFlsQueuePoint_st *p2
							   );


extern void ClrOneItem_FlsQueHeadEnd(U8 mFlsItem, U8 mPart);
extern void ClrAll_FlsQueHeadEnd(void);

extern void InitAll_FlsQueHeadEnd(void);

extern void InitOneItem_FlsQueHeadEnd(U8 mFlsItem, U8 mPart);
/*================= 公有函数声明 ====================================*/
//判断用sectorStart + CRC 来界定。
enum emFlsQueSectorState{  //U8 mFlsHistState;
	
	U_FlsQueSectorSta_NotMe, //包括space
	U_FlsQueSectorSta_SectIsFull, //全是历史记录
	U_FlsQueSectorSta_SectNotFull, //不满
	
};
extern U8 FlsQueRd_JdgFlsSect(U8 chip, U32 mAdr, U8 mFlsItem);

//1条的校验正确:
extern BOOL bFlsQueRd_OneItem_isOK(U8 chip, U32 mAdr, U8 mFlsItem);

/*================= 公有函数声明-lib内部 ====================================*/
//EX_strFlsAdrDef
extern BOOL FlsQueue_Prop(U8 mFlsItem, U8 mFlsPart, 
								TFlsQueueProp *pProp
								);
extern BOOL bFlsItem_isQueue(U8 mFlsItem);
extern U32 FlsItemQue_itemBytes(U8 mFlsItem);
extern BOOL getFlsQueue_pointId(U8 mFlsItem, U32 *pRtnPointId);


extern BOOL bAdr_Mid_QueHeadEnd(U8 mFlsItem, U8 mPart, U32 flsAdr);

/******************************************************************************
// END :
读出前一个有效的地址；
队列指针初始化；
******************************************************************************/
#endif // __strFlsQue_H__

