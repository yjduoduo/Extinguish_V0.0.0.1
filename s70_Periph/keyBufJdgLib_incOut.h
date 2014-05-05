#ifndef __keyBufJdgLib_incOut_H__
#define __keyBufJdgLib_incOut_H__
/******************************************************************************
* @file    keyBufJdgLib_incOut.h
* @author  yx
* @version V1.5
* @date    2013-09-29
* @brief   按键扫描结果判断。
		只能处理 32个以内的按键。因为读取1周期的扫描结果用了U32.
*
* V1.5, 2013-09-29  《KeyBuf_Driver_V0.0.0.1_0.0.5》
*		“keyBufJdgLib_Inc_Extern”按键修改按下和等待的时间。emKeyDownTmr
* V1.3, 加密码的处理。 
		按键过期clr.
		2013-08-28
* V1.1, 有按键未处理时，不增加新的按键。 
		加 ClrKeyValue();
		2013-08-27,yx
* V1.0, 2013-07-01
* 
#include  "keyBufJdgLib_incOut.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

/*================= 常数 ============================================*/

/*================= 公有函数声明 ====================================*/
//EX_keyBufJdgLib 

extern void InitKeyJudgeTask(void);


// 解析key扫描数据
// 扫描周期 * bufMax 内必须执行一次。
// 接收的扫描数据，bit=1表示有按键。
extern void Task_ExecKeyTask(void);

// 当前有有效的按键被按下：
extern BOOL bHaveKeyValidDown(void);

// 读取有效按键。
// OUT:　emKey, 用户数字键或功能键的定义。
extern BOOL GetKeyValue(U8 *pGetKey);

// * 应用程序，当new page时，退出用。
extern void ClrKeyValue(void);

// master: lcdSub_Pssw.c
// UserGrade确认正确后，set key:
extern void SetKeyValueWhenPsswOk(U8 mKeyValue);


// master: phIoKeyScan.c
//按键保持时间。超时，自动clr key.
// 调用后，需要定时器自动停止。
extern void TmrArrived_KeySave(void);


/******************************************************************************
// END :
******************************************************************************/
#endif // __keyBufJdgLib_incOut_H__

