#ifndef __strFlsQue_H__
#define __strFlsQue_H__
/******************************************************************************
* @file    strFlsQue.h
* @author  yx
* @version V1.1
* @date    2013-07-23
* @brief   队列类型的存储，判断属性，查找和读取指针。
* @Slave   flsInqPoint.c
* 

V1.1, ADD bAdr_Mid_QueHeadEnd();  2013.7.23, by yx;


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
	U32 pointId;   // flsItem的存储，队列类型的，排号。
	U32 itemBytes; // 1条的字节数
	U32 sectBytes; // 1 Sector 的字节数
	// sectorMax 无用。都用 != sectEnd做判断，为将来动态分配准备。
	TFlsItemAddr stAdr; // chip, adrS, adrE.
}TFlsQueueProp; //队列类型的flsItem存储

/*================= 私有函数声明 ====================================*/
#ifdef  __strFlsQue_C__

#endif  //__strFlsQue_C__
/*================= 公有函数声明-lib内部 ====================================*/
//EX_strFlsAdrDef

// 读取 head,end; 
extern U32 GetFlsQueHeadAdr(U8 mFlsItem, U8 mPatNum);
extern U32 GetFlsQueEndAdr(U8 mFlsItem, U8 mPatNum);
extern BOOL GetFlsQueHeadEndAdr(U8 mFlsItem, U8 mFlsPart,
				TFlsQueuePoint_st *pRtnHeadEnd);

// 设置 head,end; 
extern void SetFlsQueHeadAdr(U8 mFlsItem, U8 mPatNum, U32 flsAdr);
extern void SetFlsQueEndAdr(U8 mFlsItem, U8 mPatNum, U32 flsAdr);

// 比较2组 head & end 是否equal:
extern BOOL bEqu_FlsQueHeadEnd(TFlsQueuePoint_st *p1, 
					           TFlsQueuePoint_st *p2
							   );

// CLR: head & end = stAdr.adrS
extern void ClrOneItem_FlsQueHeadEnd(U8 mFlsItem, U8 mPart);
extern void ClrAll_FlsQueHeadEnd(void);

// * FUNC: // 读取flash，判断queue.head & end.
// *  OUT: SetFlsQueHeadAdr();  SetFlsQueEndAdr();
// *Slave: flsInqPoint.c
extern void InitAll_FlsQueHeadEnd(void);
extern void InitOneItem_FlsQueHeadEnd(U8 mFlsItem, U8 mPart);

// if 地址在 head,end之间:
extern BOOL bAdr_Mid_QueHeadEnd(U8 mFlsItem, U8 mPart, U32 flsAdr);

/*================= 公有函数声明-lib内部 ====================================*/
//判断用sectorStart + CRC 来界定。
enum emFlsQueSectorState{  //U8 mFlsHistState;
	
	U_FlsQueSectorSta_NotMe,       //包括space
	U_FlsQueSectorSta_SectIsFull,  //全是历史记录
	U_FlsQueSectorSta_SectNotFull, //不满
	
};
	
// * FUNC: // 判断mAdr所在sector存储的情况。
// *  OUT:  emFlsQueSectorState
extern U8 FlsQueRd_JdgFlsSect(U8 chip, U32 mAdr, U8 mFlsItem);

// 1条的校验正确, crc;
extern BOOL bFlsQueRd_OneItem_isOK(U8 chip, U32 mAdr, U8 mFlsItem);

/*================= 公有函数声明-lib内部 ====================================*/
//EX_strFlsAdrDef

//队列属性 TFlsQueueProp :
extern BOOL FlsQueue_Prop(U8 mFlsItem, U8 mFlsPart, 
								TFlsQueueProp *pProp
								);

// if 是 Queue类型存储：
extern BOOL bFlsItem_isQueue(U8 mFlsItem);
// 每条的字节数:
extern U32 FlsItemQue_itemBytes(U8 mFlsItem);
// flsItem的存储，队列类型的，排号:
extern BOOL getFlsQueue_pointId(U8 mFlsItem, U32 *pRtnPointId);



/******************************************************************************
// END :
读出前一个有效的地址；
队列指针初始化；
******************************************************************************/
#endif // __strFlsQue_H__

