#ifndef __lcdSub_InputFig_H__
#define __lcdSub_InputFig_H__
/******************************************************************************
* @file    lcdSub_InputFig.h
* @author  yx
* @version V1.0
* @date    2013-09-16
* @brief
* add: FigInput_AddIniFig_WithCurHide();  FigInput_CursorRight_withRowCol(); 
*
#include  "lcdSub_InputFig.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

#include  "lcd_Para.h"

/*================= extern ============================================*/
#ifdef  __lcdSub_InputFig_C__
#define EX_lcdSub_InputFig
#else
#define EX_lcdSub_InputFig extern
#endif
/*================= 常数 ============================================*/

/*================= 结构体定义 ======================================*/
#ifdef  __lcdSub_InputFig_C__

#define U_INPUT_NUM_MAX  20

typedef struct
{
    U8 			iFig;   //输入的数字
    U8 			iMax;   //输入的数字
    BOOL 		bIsHide; // * 隐藏输入内容
    BOOL 	bRenew; // TRUE=已有输入。
    TLcdRL_st  	rl;

}TInputOneFig_st;


typedef struct
{
    U8   	itemStart;
    U8   	itemEnd;  // = last + 1;
    U32 	hexFigIni;   //
    U32 	hexFigMax;   //
    U32		hexFigIn;   //输入的数字
}TInputGroupFig_st;
#define U_INPUT_FIG_GROUP_MAX   5


typedef struct
{
    struct
    {
        U8 now;		//光标位置
        BOOL bValid;
        BOOL bBlink; //光标闪动 TRUE变色 FALSE正常
    }cursor;

    // 缺陷： hex=0xFF, iMax=[3, 10, 10]; 第2位无法根据最高位的输入判断出超限。
    // 所以引入 group.
    // in = cursor.now;
    TInputOneFig_st  stRl[U_INPUT_NUM_MAX]; // 每个数字占1个位置

    struct
    {
        U8 		in;
        TInputGroupFig_st buf[U_INPUT_FIG_GROUP_MAX];
    }group;

    struct
    {
        U8 NeedNum;  //需要的总数 =0表示无输入数字

        BOOL bFinish;

        BOOL bAllowChkExceedWhenInput;
        BOOL bExceed; // 超限。
        // U8 change;     //数字输入有变化位置  usua()里清 某些页面里根据输入的数字会有提示
    }state;	  //输入数字

    struct
    {
        U16 RowStart;  //实际的 行列
        U16 LineStart;
        U16 RowEnd;
        U16 LineEnd;
        U8 Prompting;   //当前有提示文字
    }Prompt; 	//提示文字范围
    // U8 FunKey[U_PAGE_FUNKEY_MAX];  	//功能键位置  U_PTASK_FUNKEY_UP

}TFigInput_st;

#endif  //__lcdSub_InputFig_C__
/*================= 公有结构变量声明 ================================*/


/*================= 私有函数声明 - 计算exceed =======================*/
#ifdef  __lcdSub_InputFig_C__

// 计算是否有超限的输入 - 当前输入有关的：
// 只在允许输入期间计算的时候，才能起作用。
// *  OUT: TRUE = sign = bExceed;
BOOL cacuFigInput_nowIn_Exceed(U8 mIn, BOOL bExceedPre);

// 计算是否有超限的输入 - all - 单个数字 + group：
// *  OUT: TRUE = sign = bExceed;
BOOL cacuFigInput_Exceed(void);
// 计算是否有超限的输入 - all 单个数字：
BOOL bFigInput_figIn_Exceed(void);
// 计算是否有超限的输入 - 一个 单个数字：
BOOL bFigInput_figIn_one_Exceed(U8 mIn);
// 计算是否有超限的输入 - all group结果：
BOOL bFigInput_group_Exceed(void);

// 计算 group的输入结果：
// *  OUT: TRUE= 数值有效，groupFig < max;
BOOL cacuFigInput_Group(U8 mGroupNum, U32 *pRtnGrpFig);

void set_figInput_exceed(void);
void clr_figInput_exceed(void);
BOOL bGet_figInput_exceed(void);

#endif  //__lcdSub_InputFig_C__
/*================= 私有函数声明 ====================================*/
#ifdef  __lcdSub_InputFig_C__

static TFigInput_st  vStFigInput;

void figInput_showIni(void);
void figInput_showOne(U8 mItem);
BOOL figInput_addIniOne(TYPE_LCD_RL mRow, TYPE_LCD_RL mLine,
                        U8 mFig, U8 mMax, BOOL bHideShow);

// 光标闪动：
void figInput_cursorBlink_start(U8 cursorNow);
void figInput_cursorBlink_stop(void);
BOOL figInput_cursorBlink_TmrArried(void);



// 数字输入，或光标位置有变：
void figInput_fig_change(U8 mIn);
void figInput_cursor_leave(U8 mIn);
void figInput_cursor_new(U8 mIn);


#endif  //__lcdSub_InputFig_C__


/*================= 公有函数声明 ====================================*/
//EX_lcdSub_InputFig

extern void FigInput_Init(void);  //初始化
extern void FigInput_Exec(void);


// if 需要数字输入：
extern BOOL bFigInputNeed(void);
// if 输入超限：
extern BOOL bFigInput_Exceed(void);


/******************************************************************************
顺序：
FigInput_ReStart();
FigInput_Add...();  需要按光标移动的顺序调用。
FigInput_AddIniEnd();
输入数字，移动光标； 期间 FigInput_Exec(); 内有定时。
FigInput_Stop();
******************************************************************************/
// 数字输入准备。接下来需要 FigInput_Add...初始化各位。
extern void FigInput_ReStart(BOOL bAllowChkExceedWhenInput);
// 数字输入 退出：
extern void FigInput_Stop(void);

// ini: 输入数字 1个:
extern BOOL FigInput_AddIniFig(
                        TYPE_LCD_RL mRow, TYPE_LCD_RL mLine,
                        U8 mFig, U8 mMax);

BOOL FigInput_AddIniFig_WithCurHide(TYPE_LCD_RL mRow, TYPE_LCD_RL mLine,
                        U8 mFig, U8 mMax,BOOL CurSorHide);
// ini: 输入数字 hex:
// 可以配合 GetFigInput_Group() 读取 输入的一组结果。
extern BOOL FigInput_AddIniHex(TYPE_LCD_RL mRow, TYPE_LCD_RL mLine,
                       U32 mFigHex, U32 mFigMaxHex, U8 bitTotal,
                       U8 *pRtnGroupNum);
// *  OUT: TRUE= 数值有效，groupFig < max;
extern BOOL GetFigInput_Group(U8 mGroupNum, U32 *pRtnGroupFig);
// ini: 隐藏显示的输入位置:
extern BOOL FigInput_AddIniHide(TYPE_LCD_RL mRow, TYPE_LCD_RL mLine,
                        U8 mNum);
// 添加完毕，显示ini字符：
extern void FigInput_AddIniEnd(void);


// 有新的数字键输入：
extern BOOL FigInput_newFig(U8 mFig);
extern BOOL FigInput_newUp(void);
extern BOOL FigInput_newDown(void);
extern void FigInput_CursorRight(void);
extern void FigInput_CursorRight_withRowCol(U8 Row,U8 Col);
extern void FigInput_CursorLeft(void);


/******************************************************************************
// END :
******************************************************************************/
#endif // __lcdSub_InputFig_H__

