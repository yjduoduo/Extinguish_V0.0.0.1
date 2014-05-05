#ifndef __flsWrApplyBuf_H__
#define __flsWrApplyBuf_H__
/******************************************************************************
* @file    flsWrApplyBuf.h
* @author  yx
* @version V1.0
* @date    2013-07-23
* @brief   配合flsWrApplySave.c， 做buf[]. 
		IN: FlsWr_AlyBuf_NewApply();
		存实际数据，因为各item的长度相差很大，所以不按 定长存储。
* @master: "flsWrApplySave.c"
* 
*
#include  "flsWrApplyBuf.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

/*================= extern ============================================*/
#ifdef  __flsWrApplyBuf_C__
#define EX_flsWrApplyBuf
#else
#define EX_flsWrApplyBuf extern 
#endif
/*================= 常数 ============================================*/
//#define 

/*================= 公用 ============================================*/
// #if U_SYS_Test_FlsApplyBuf == 1
	// #define U_FlsAly_One_Head_Bytes  1  //每次分配都带Head;
// #else
	// #define U_FlsAly_One_Head_Bytes  8  //每次分配都带Head;
// #endif

typedef union
{
	U32 dword[2];
	struct{
		U32 strFlsItemBytes; //不包括head自身,不对齐
		U8 mFlsItem;
		U8 taskId;  //比如显示任务，或串口通讯任务。
		U8 flsId;
	}head;
}TFlsAlyOneHead_un; //给 task读出属性用。

//后面是各不同的需要wrFlash的struct: "strFlsItmStruct.h"

/*================= 公用-分配空间 ============================================*/

#if U_SYS_Test_FlsApplyBuf == 1
	#define U_FlsAly_BufByte_MAX  (0x80 ) // U32 mFlsAppBytes;
	#define U_FlsAly_SecNum_MAX    10   // U32 mFlsAppSec;
#else
	#define U_FlsAly_BufByte_MAX  (8 * KBytes ) // U32 mFlsAppBytes;

	//最多分配次数。以最小分配单位计算
	#define U_FlsAly_SecNum_MAX    200   // U32 mFlsAppSec;
#endif //U_SYS_Test_FlsApplyBuf

typedef struct
{
	U32 strFlsItmByte;
	U8 mFlsItem;
	U8 taskId;  //比如显示任务，或串口通讯任务。
	U8 flsId;
	
	// void *pAppBuf;  //对应不同的类别
	
	U32 adrS; //对应 vFlsAppBuf[]
	U32 adrE;
}TFlsAlySec_st;  //每次申请分配一个。


/*================= 结构体定义 ======================================*/

/*================= 公有结构变量声明 ================================*/

/*================= 私有函数声明 ====================================*/
#ifdef  __flsWrApplyBuf_C__

#endif  //__flsWrApplyBuf_C__

/*================= 公有函数声明-lib内部 ====================================*/
//EX_flsWrApplyBuf 

extern void Init_FlsApplyBuf(void);


// * FUNC: // 申请空间, 把要写入的内容->buf
// *   IN:  	(bSaveItemValid(mFlsItem))
		// taskId < U_SYS_TASK_ID_MAX
		// flsId
		// pSrc ->  TFlsSysSet_un ...
// *  OUT: U_SUCC
extern BOOL FlsWr_AlyBuf_NewApply(U8 mFlsItem, U8 taskId, 
										U8 flsId, U8 *pSrc);


// * FUNC: // 待写flash的任务，读出。
// *   IN:
// *  OUT: U_SUCC
		// *pByteDest.. = 各结构体自身
extern BOOL FlsWr_AlyBuf_Read(U8 *pByteDest, 
							 TFlsAlyOneHead_un *pRtnAlyHead);

extern BOOL bFlsWr_AlyBuf_Empty(void);


/******************************************************************************
// END :
******************************************************************************/
#endif // __flsWrApplyBuf_H__

