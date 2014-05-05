#ifndef __Save_Manage_incOut_H__
#define __Save_Manage_incOut_H__
/******************************************************************************
* @file    Save_Manage_incOut.h
* @author  yx
* @version V1.4
* @date    2013.9.22
* @brief   
	   
* @Version history 
* V1.4, 2013.9.22  《DriverFlsSave_V0.0.0.1_0.1.5》
*	FlsResultNotificat()的结果，用U8表示，.0表示part0,.1表示part1.
* V1.3, 2013-09-4
* V1.0, 2013-07-23
* 
#include  "Save_Manage_incOut.h"
******************************************************************************/
//
#include  "prjCompileCon.h"
#include  "strDevice.h"
#include  "strEvtTrans.h"

/******************************************************************************
//分配ID号：flash存储 有唯一的id号(关机时间和历史记录除外)
//若不在意存储结果，可以用默认的flsId: FlsId_DefaultValue();

// 使用示例：
void store(void) // 保存：
{
static U8 mFlsId;
U8 bSucc;
	if(FlsIdNewAssign(taskId, &mFlsId))
	{
		//存储(内容， taskId, mFlsId);  //FlsSave_PnConfig(taskId); 等
	}
}

void saveResult(void) // 读取保存结果：
{
	if(bIsFinish_FlsExe(mFlsId, &bSucc))  //查看结果：
	{
		//根据存储结果处理。
		// 清除分配：FlsIdClrAssign();
	}
}


void read(void)  //读取
{
	if(FlsRdFlsItem_ChipAllow(mFlsItem))
	{
		// 读
	}
}


* FUNC: //lib 用法：
// *****************************************************************************   *  /
1. 存储：
	得到flsId: FlsIdNewAssign(U8 taskId, U8 *pRtnFlsId);
	FlsSave_PnConfig(taskId); 等
	查看结果：bIsFinish_FlsExe();
	清除分配：FlsIdClrAssign();
	
2. 读：
	判断 FlsRdFlsItem_ChipAllow();

3. 管理：
	定时100ms, 调用 FlsIdAssign_TmrAdd(); 若超时，清除此flsId.
	历史记录存储，定时到|记录的buf满，将buf里的都写入。

******************************************************************************/


/*================= 公有函数声明-lib外部 ====================================*/
//EX_flashIdAssign 

//分配ID号：flash存储 有唯一的id号(关机时间和历史记录除外)
//若不在意存储结果，可以用默认的flsId: FlsId_DefaultValue();

// 分配存储任务唯一id, Clr:
extern void FlsIdAssign_Init(void);

extern BOOL bFlsId_Valid(U8 mFlsId);

//定时判断结果超时，需要master定时100ms执行:
// 若超时，清除结果。
extern void FlsIdAssign_TmrAdd(void);

//默认值，给不关心结果的task使用。
extern U8 FlsId_DefaultValue(void);


// 新分配任务号，给master判断存储结果用。
// master需要先得到一个flsId, 然后再调用 FlsSave_PnConfig()等。
extern BOOL FlsIdNewAssign(U8 taskId, U8 *pRtnFlsId);

extern void FlsIdClrAssign(U8 mFlsId);

//清除所有taskId所分配的flsId.
extern void FlsIdClr_FromTaskId(U8 mTaskId);

//结果读取：
// *  OUT: BOOL=是否操作完毕；
// *pRtnSucc = 读出比较的结果 // .0=1=part0 Succ; .1=1=part1 Succ
extern BOOL bIsFinish_FlsExe(U8 flsId, U8 *pRtnSucc);

extern BOOL bFlsId_AllFinish_FromTaskId(U8 mTaskId);
extern BOOL bFlsId_AllSucc_FromTaskId(U8 mTaskId);



/*================= 公有函数声明-lib外部 ====================================*/
//EX_flsCopyTask 
//设置允许禁止：
//未完成。准备纠错，用onePart  cover another.
extern void SetAllow_FlsCopy_CheckItemError(void);
extern void SetForbid_FlsCopy_CheckItemError(void);
extern BOOL bFlsCopy_Allow_CheckItemError(void);

/*================= 公有函数声明-lib外部 ====================================*/
//EX_flsItemState 

// TRUE=允许读, (!Error + !Erase + !Renew)
// extern BOOL bFlsItem_IsReadAllow(U8 mFlsItem, U8 mPart);

/*================= 公有函数声明-lib外部-允许读 ====================================*/
//EX_saveManage 
// 因为flash 写期间 禁止读操作，所以应用层读取前要判断：

//需要的项目允许读
//有1part允许就可以：
extern BOOL FlsRdFlsItem_ChipAllow(U8 mFlsItem);
extern BOOL FlsRdFlsItem_PartN_ChipAllow(U8 mFlsItem, U8 mPart);

/*================= 公有函数声明-lib外部 ====================================*/
//EX_saveManage 
// 检查master和lib定义的一致性
extern BOOL bSave_CheckReDef(void);

extern void Init_SaveManage(void);

// flash 存储管理 exe, 需要main循环调用。
extern void SaveManage_Exec(void);

/******************************************************************************
// END :
******************************************************************************/
#endif // __Save_Manage_incOut_H__

