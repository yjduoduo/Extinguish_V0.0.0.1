#ifndef __lcdShowTask_H__
#define __lcdShowTask_H__
/******************************************************************************
* @file    lcdShowTask.h
* @author  yx
* @version V1.0
* @date    2013-07-01
* @brief   
* 
#include  "lcdShowTask.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

/*================= extern ============================================*/
#ifdef  __lcdShowTask_C__
#define EX_lcdShowTask
#else
#define EX_lcdShowTask extern 
#endif
/*================= 常数 ============================================*/
//#define 
/*================= 结构体定义 ======================================*/

/*================= 公有结构变量声明 ================================*/
/*
typedef struct{
	U8 sequStart;
}TStruct_st;
TStruct_st stStruct;
*/

/*-----------------    ----------------------------------*/

/*================= 私有函数声明 ====================================*/
#ifdef  __lcdShowTask_C__

// 判断按键。 emKey 
// 其slave函数  OUT: TRUE=已处理。
void lcdTask_JdgKey(void);

//OUT: TRUE=已处理。
BOOL lcdTask_keyCheckIng(U8 mKey); // 按键检测
BOOL lcdTask_keyReset(U8 mKey);
BOOL lcdTask_keySilence(U8 mKey);
BOOL lcdTask_keyReturn(U8 mKey); 
BOOL lcdTask_keyEsc(U8 mKey);
BOOL lcdTask_keyEnter(U8 mKey);
BOOL lcdTask_keyInputFig(U8 mKey); // 数字和方向键



#endif  //__lcdShowTask_C__
/*================= 公有函数声明 ====================================*/
//EX_lcdShowTask 

extern void Init_LcdTask(void);
extern void Exec_LcdTask(void);

/******************************************************************************
// END :
******************************************************************************/
#endif // __lcdShowTask_H__

