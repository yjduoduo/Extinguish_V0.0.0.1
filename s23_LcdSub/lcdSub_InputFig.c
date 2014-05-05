#define __lcdSub_InputFig_C__
/******************************************************************************
* @file    lcdSub_InputFig.c
* @author  yx
* @version V1.0
* @date    2013-09-16
* @brief
*
******************************************************************************/
#include  "lcdSub_InputFig.h"

#include  "tmrTick.h"
#include  "lcdSub_ModeTextFig.h"
#include  "codeComm.h"
#include  "codeFig.h"
#include  "sysDef.h"

//#include "incFile.h"
//-----------------   --------------------------------//


/*================= 常数 ============================================*/

/*================= 结构定义 ========================================*/

/*================= 私有结构变量声明 ================================*/


/*================= 公有函数声明 ====================================*/

/*================= 私有函数声明 ====================================*/

/*=================  ================================================*/



/******************************************************************************
* FUNC: //
*   IN:
*  OUT:
******************************************************************************/

void FigInput_Exec(void)
{

    if(!bFigInputNeed())
    {
        return;
    }

    if(vStFigInput.cursor.bValid)
    {
        figInput_cursorBlink_TmrArried();
    }
}
/******************************************************************************
* FUNC: //
******************************************************************************/
// if 需要数字输入：
BOOL bFigInputNeed(void)
{
    return (vStFigInput.state.NeedNum != 0);
}

/******************************************************************************
* FUNC: //
*   IN:
*  OUT:
******************************************************************************/

void FigInput_Init(void)  //初始化
{
    U8 mIn;

    ClrRamIs00((U8*)(&vStFigInput), sizeof(TFigInput_st)); //全清00

    for(mIn=0; mIn<U_INPUT_NUM_MAX; mIn++)
    {
        vStFigInput.stRl[mIn].iFig = ~0;
        vStFigInput.stRl[mIn].iMax = ~0;

    }

    vStFigInput.state.bFinish = FALSE;

    clr_figInput_exceed();
    figInput_cursorBlink_stop();
}


/******************************************************************************
* FUNC: // 数字输入准备。接下来需要 FigInput_Add...初始化各位。
*   IN:
*  OUT:
******************************************************************************/
void FigInput_ReStart(BOOL bAllowChkExceedWhenInput)
{
    FigInput_Init();

    vStFigInput.state.bAllowChkExceedWhenInput
            = bAllowChkExceedWhenInput;

}


/******************************************************************************
* FUNC: // 数字输入 退出：
*   IN:
*  OUT:
******************************************************************************/
void FigInput_Stop(void)
{
    FigInput_Init();
}


/******************************************************************************
* FUNC: // ini: 输入数字 1个:
*   IN: 需要按先后顺序调用。
*  OUT:
******************************************************************************/

BOOL FigInput_AddIniFig(TYPE_LCD_RL mRow, TYPE_LCD_RL mLine,
                        U8 mFig, U8 mMax)
{
    return figInput_addIniOne(mRow, mLine,
                              mFig, mMax, FALSE);
}
/******************************************************************************
* FUNC: // ini: 输入数字 1个:
*   IN: 需要按先后顺序调用。
*  OUT:
******************************************************************************/

BOOL FigInput_AddIniFig_WithCurHide(TYPE_LCD_RL mRow, TYPE_LCD_RL mLine,
                        U8 mFig, U8 mMax,BOOL CurSorHide)
{
    return figInput_addIniOne(mRow, mLine,
                              mFig, mMax, CurSorHide);
}
/******************************************************************************
* FUNC: //
*   IN: 需要按先后顺序调用。
        mFig>=10表示当前数字未知。
        根据行列，将参数加载到缓存，并不显示
*  OUT:
******************************************************************************/
BOOL figInput_addIniOne(TYPE_LCD_RL mRow, TYPE_LCD_RL mLine,
                        U8 mFig, U8 mMax, BOOL bHideShow)
{
    U8 mIn;

    mIn = vStFigInput.state.NeedNum;
    if(mIn >= U_INPUT_NUM_MAX)
    {
        return FALSE;
    }

    if(mFig >= 10)
    {
        mFig = 0;
    }
    if(mMax >= 10)
    {
        mMax = 10;
    }
    vStFigInput.stRl[mIn].rl.row = mRow;
    vStFigInput.stRl[mIn].rl.line = mLine;
    vStFigInput.stRl[mIn].iFig = mFig;
    vStFigInput.stRl[mIn].iMax = mMax;
    vStFigInput.stRl[mIn].bIsHide = bHideShow;

    vStFigInput.state.NeedNum++;
    return TRUE;
}


/******************************************************************************
* FUNC: //
*   IN:
*  OUT:
******************************************************************************/

// 添加完毕，显示ini字符：
void FigInput_AddIniEnd(void)
{
    figInput_showIni();
}

/******************************************************************************
* FUNC: //
*   IN:
*  OUT:
******************************************************************************/

void figInput_showIni(void)
{
    U8 mIn;

    figInput_cursorBlink_start(0);

    for(mIn=0; mIn<vStFigInput.state.NeedNum; mIn++)
    {
        figInput_showOne(mIn);
    }

}

/******************************************************************************
* FUNC: //
******************************************************************************/

void figInput_showOne(U8 mItem)
{
    BOOL bInverse;

    if(mItem >= vStFigInput.state.NeedNum)
    {
        return;
    }

    bInverse = FALSE;

    if(          (vStFigInput.cursor.bValid)
                 &&         (vStFigInput.cursor.bBlink)
                 &&(mItem == vStFigInput.cursor.now)
                 )
    {
        bInverse = TRUE;//根据光标闪烁来标示是不是需要取反，在当前位
    }


    if(vStFigInput.stRl[mItem].iFig >= 10)
    {
        ShowCodeCharRL(
                    vStFigInput.stRl[mItem].rl.row,
                    vStFigInput.stRl[mItem].rl.line,
                    " ",
                    bInverse);
    }
    else if(vStFigInput.stRl[mItem].bIsHide)//根据隐藏位标示
    {
        ShowCodeCharRL(
                    vStFigInput.stRl[mItem].rl.row,
                    vStFigInput.stRl[mItem].rl.line,
                    "*",
                    bInverse);
    }
    else
    {
        // 1bit数字，正常显示 | 反显：
        Show_1Fig_if_inverse(
                    vStFigInput.stRl[mItem].rl.row,
                    vStFigInput.stRl[mItem].rl.line,
                    vStFigInput.stRl[mItem].iFig,
                    bInverse
                    );
    }


}

/******************************************************************************
* FUNC: // 光标闪动：
*   IN:
*  OUT:
******************************************************************************/

void figInput_cursorBlink_start(U8 cursorNow)
{
    if(cursorNow >= vStFigInput.state.NeedNum)
    {
        cursorNow = 0;
    }
    vStFigInput.cursor.now = cursorNow;
    vStFigInput.cursor.bBlink = TRUE;

    SetTmrTickTsk_haveTaskId(TASK_FigInCursor,
                             TMR_FigInCursor,
                             U_SysTask_LcdShow);
    vStFigInput.cursor.bValid = TRUE;
}


void figInput_cursorBlink_stop(void)
{
    vStFigInput.cursor.bValid = FALSE;
    vStFigInput.cursor.now = ~0;
    KillTickTask(TASK_FigInCursor);
}

BOOL figInput_cursorBlink_TmrArried(void)
{
    BOOL bArried;

    if(!vStFigInput.cursor.bValid)
    {
        return FALSE;
    }
    bArried = (GetTickTaskStatus(TASK_FigInCursor));
    if(bArried)
    {
        if(vStFigInput.cursor.bBlink)
            vStFigInput.cursor.bBlink = 0;
        else
            vStFigInput.cursor.bBlink = 1;

        figInput_showOne(vStFigInput.cursor.now);
    }

    return bArried;
}


/******************************************************************************
* FUNC: // ini: 输入数字 hex:
*   IN:
*  OUT:
// 可以配合 GetFigInput_Group() 读取 输入的一组结果。
******************************************************************************/

BOOL FigInput_AddIniHex(TYPE_LCD_RL mRow, TYPE_LCD_RL mLine,
                        U32 mFigHex, U32 mFigMaxHex, U8 bitTotal,
                        U8 *pRtnGroupNum)
{
    U8 bcdNum;
    U32 mBcdFig;
    U32 mBcdMax;
    U8 iMax;
    U8 mInStart;
    TInputGroupFig_st *pGroup;


    bcdNum = bitTotal;
    mInStart = vStFigInput.state.NeedNum;
    *pRtnGroupNum = ~0;

    HexToBcd_LimitBcdNum(mFigHex, bitTotal, &mBcdFig);
    HexToBcd_LimitBcdNum(mFigMaxHex, bitTotal, &mBcdMax);

    iMax = (U8)(mBcdMax >> (4*(bcdNum-1))) + 1;
    if(iMax > 10)
    {
        iMax = 10;
    }
    if(!FigInput_AddIniFig( mRow, mLine,
                            (U8)(mBcdFig >> (4*(bcdNum-1))),
                            iMax))
    {
        return FALSE;
    }
    bcdNum--;
    mLine++;
    for(; bcdNum!=0; bcdNum--)
    {
        if(!FigInput_AddIniFig( mRow, mLine,
                                (U8)(mBcdFig >> (4*(bcdNum-1))),
                                10))
        {
            return FALSE;
        }
        mLine++;
    }


    if(vStFigInput.group.in < U_INPUT_FIG_GROUP_MAX)
    {
        pGroup = &vStFigInput.group.buf[vStFigInput.group.in];
        pGroup->itemStart = mInStart; // 输入位置:
        pGroup->itemEnd = vStFigInput.state.NeedNum;
        pGroup->hexFigIni = mFigHex;
        pGroup->hexFigMax = mFigMaxHex;
        pGroup->hexFigIn = 0;

        *pRtnGroupNum = vStFigInput.group.in;
        vStFigInput.group.in++;
        return TRUE;
    }
    else
    {
        return FALSE;
    }

}



/******************************************************************************
* FUNC: // ini: 隐藏显示的输入位置:
*   IN:
*  OUT:
******************************************************************************/

BOOL FigInput_AddIniHide(TYPE_LCD_RL mRow, TYPE_LCD_RL mLine,
                         U8 mNum)
{
    U8 ii;
    BOOL bResult;

    for(ii=0; ii<mNum; ii++)
    {
        bResult = figInput_addIniOne(mRow, mLine,
                                     0, ~0, TRUE);
        mLine++;
        if(!bResult)
        {
            break;
        }
    }
    return bResult;
}



/******************************************************************************
* Public:
* FUNC: //
*   IN:
*  OUT:
******************************************************************************/
// if 输入超限：
BOOL bFigInput_Exceed(void)
{
    // 计算是否有超限的输入 - all：
    return cacuFigInput_Exceed();
}


/******************************************************************************
* Public:
* FUNC: //
*   IN:
*  OUT: TRUE= 数值有效，groupFig < max;
******************************************************************************/
BOOL GetFigInput_Group(U8 mGroupNum, U32 *pRtnGroupFig)
{
    TInputGroupFig_st *pGroup;

    *pRtnGroupFig = 0;
    if(mGroupNum >= vStFigInput.group.in)
    {
        return FALSE;
    }
    pGroup = &vStFigInput.group.buf[mGroupNum];
    *pRtnGroupFig = pGroup->hexFigIn;
    return (pGroup->hexFigIn < pGroup->hexFigMax);
}



/******************************************************************************
* FUNC: // 计算是否有超限的输入
*   IN:
*  OUT: TRUE = sign = bExceed;
******************************************************************************/
// 计算是否有超限的输入 - 当前输入有关的：
// 只在允许输入期间计算的时候，才能起作用。
BOOL cacuFigInput_nowIn_Exceed(U8 mIn, BOOL bExceedPre)
{
    U8 mGrpNum;
    TInputGroupFig_st *pGroup;
    U32 mGrpFig;

    if(!vStFigInput.state.bAllowChkExceedWhenInput)
    {
        return FALSE;
    }

    if(bFigInput_figIn_one_Exceed(mIn))
    {
        set_figInput_exceed();
        return TRUE;
    }
    for(mGrpNum=0; mGrpNum<vStFigInput.group.in; mGrpNum++)
    {
        pGroup = &vStFigInput.group.buf[mGrpNum];
        if((mIn >= pGroup->itemStart) && (mIn < pGroup->itemEnd))
        {
            if(!cacuFigInput_Group(mGrpNum, &mGrpFig))
            {
                set_figInput_exceed();
                return TRUE;
            }
        }
    }
    // 当前的输入 !exceed:
    if(bExceedPre)
    {
        // 计算是否有超限的输入 - all - 单个数字 + group：
        return cacuFigInput_Exceed();
    }
    else
    {
        return FALSE;
    }
}


/******************************************************************************
* Private:
* FUNC: //
******************************************************************************/
void set_figInput_exceed(void)
{
    vStFigInput.state.bExceed = TRUE;
}
void clr_figInput_exceed(void)
{
    vStFigInput.state.bExceed = FALSE;
}
BOOL bGet_figInput_exceed(void)
{
    return vStFigInput.state.bExceed;
}

/******************************************************************************
* Private:
* FUNC: //
*  OUT: TRUE = sign = bExceed;
******************************************************************************/
// 计算是否有超限的输入 - all - 单个数字 + group：
BOOL cacuFigInput_Exceed(void)
{
    if(  (bFigInput_figIn_Exceed())
         || (bFigInput_group_Exceed())
         )
    {
        set_figInput_exceed();
        return TRUE;
    }
    else
    {
        clr_figInput_exceed();
        return FALSE;
    }
}


// 计算是否有超限的输入 - all 单个数字：
BOOL bFigInput_figIn_Exceed(void)
{
    U8 mIn;

    for(mIn=0; mIn<vStFigInput.state.NeedNum; mIn++)
    {
        if(bFigInput_figIn_one_Exceed(mIn))
        {
            return TRUE;
        }
    }
    return FALSE;
}


// 计算是否有超限的输入 - 一个 单个数字：
BOOL bFigInput_figIn_one_Exceed(U8 mIn)
{
    TInputOneFig_st *pOneFig;
    BOOL bExceed;

    if(mIn >= vStFigInput.state.NeedNum)
    {
        return TRUE;
    }

    pOneFig = &vStFigInput.stRl[mIn];


    bExceed = (pOneFig->iFig  >=  pOneFig->iMax);

    return bExceed;
}

// 计算是否有超限的输入 - all group结果：
BOOL bFigInput_group_Exceed(void)
{
    U8 mGrpNum;
    U32 mGrpFig;
    BOOL bExceed = FALSE;

    for(mGrpNum=0; mGrpNum<vStFigInput.group.in; mGrpNum++)
    {
        if(!cacuFigInput_Group(mGrpNum, &mGrpFig))
        {
            bExceed = TRUE;
        }
    }
    return bExceed;
}


/******************************************************************************
* FUNC: // 计算 group的输入结果：
*   IN:
*  OUT: vStFigInput.group.buf[mGroupNum].hexFigIn;
*  OUT: TRUE= 数值有效，groupFig < max;
******************************************************************************/
// 计算 group的输入结果：
BOOL cacuFigInput_Group(U8 mGroupNum, U32 *pRtnGrpFig)
{
    U32 mBcd = 0;
    U32 mHex;
    U8 mIn;
    TInputGroupFig_st *pGroup;

    *pRtnGrpFig = 0;
    if(mGroupNum >= vStFigInput.group.in)
    {
        return FALSE;
    }
    pGroup = &vStFigInput.group.buf[mGroupNum];
    for(mIn=(pGroup->itemStart); mIn<(pGroup->itemEnd); mIn++)
    {
        mBcd <<= 4;
        mBcd &= (~0x0F);
        mBcd |= vStFigInput.stRl[mIn].iFig;
    }
    mHex = BcdToHexU32(mBcd);
    vStFigInput.group.buf[mGroupNum].hexFigIn = mHex;
    *pRtnGrpFig = mHex;

    return (mHex < vStFigInput.group.buf[mGroupNum].hexFigMax);
}







/******************************************************************************
* FUNC: // 数字输入，或光标位置有变：
*   IN:
*  OUT:
******************************************************************************/
void figInput_fig_change(U8 mIn)
{
    figInput_showOne(mIn);
    cacuFigInput_nowIn_Exceed( mIn,
                               bGet_figInput_exceed());
    vStFigInput.stRl[mIn].bRenew = TRUE;
}

void figInput_cursor_leave(U8 mIn)
{
    if(vStFigInput.stRl[mIn].iFig >= 10)
    {
        vStFigInput.stRl[mIn].iFig = 0;
    }
    figInput_cursorBlink_stop();
    figInput_fig_change(mIn);

    if(mIn == (vStFigInput.state.NeedNum - 1))
    {
        vStFigInput.state.bFinish = TRUE;
    }
}

void figInput_cursor_new(U8 mIn)
{
    figInput_cursorBlink_start(mIn);
    figInput_showOne(mIn);
}

/******************************************************************************
* FUNC: // 有新的数字键输入：
*   IN:
*  OUT:
******************************************************************************/

BOOL FigInput_newFig(U8 mFig)
{
    U8 mIn;

    if(  (vStFigInput.state.NeedNum == 0)
         || (vStFigInput.state.NeedNum >= U_INPUT_NUM_MAX))
    {
        return FALSE;
    }

    mIn = vStFigInput.cursor.now;
    if(  (mIn >= U_INPUT_NUM_MAX)
         || (mFig >= vStFigInput.stRl[mIn].iMax)
         )//光标输入位置超限或数字超过最大数
    {
        return FALSE;
    }

    vStFigInput.stRl[mIn].iFig = mFig;

    FigInput_CursorRight();

    return TRUE;
}


/******************************************************************************
* FUNC: //
******************************************************************************/
BOOL FigInput_newUp(void)
{
    U8 mIn;
    TInputOneFig_st *pOneFig;

    if(  (vStFigInput.state.NeedNum == 0)
         || (vStFigInput.state.NeedNum >= U_INPUT_NUM_MAX))
    {
        return FALSE;
    }

    mIn = vStFigInput.cursor.now;
    pOneFig = &vStFigInput.stRl[mIn];

    pOneFig->iFig++;
    if(pOneFig->iFig >= pOneFig->iMax)
    {
        pOneFig->iFig = 0;
    }

    figInput_cursorBlink_start(vStFigInput.cursor.now);
    figInput_fig_change(vStFigInput.cursor.now);
    return TRUE;
}



/******************************************************************************
* FUNC: //
******************************************************************************/
BOOL FigInput_newDown(void)
{
    U8 mIn;
    TInputOneFig_st *pOneFig;

    if(  (vStFigInput.state.NeedNum == 0)
         || (vStFigInput.state.NeedNum >= U_INPUT_NUM_MAX))
    {
        return FALSE;
    }

    mIn = vStFigInput.cursor.now;
    pOneFig = &vStFigInput.stRl[mIn];

    if(pOneFig->iFig == 0)
    {
        pOneFig->iFig = (pOneFig->iMax - 1);
    }
    else
    {
        pOneFig->iFig--;
    }

    figInput_cursorBlink_start(vStFigInput.cursor.now);
    figInput_fig_change(vStFigInput.cursor.now);
    return TRUE;

}



/******************************************************************************
* FUNC: //
******************************************************************************/
void FigInput_CursorRight(void)
{
 //   U8 nowCursor;
//    U8 row;
   // U8 col;
//    U8 ii;
    if(  (vStFigInput.state.NeedNum == 0)
         || (vStFigInput.state.NeedNum >= U_INPUT_NUM_MAX))
    {
        return;
    }

//    nowCursor=vStFigInput.cursor.now;
//    row=vStFigInput.stRl[nowCursor].rl.row;
  //  col=vStFigInput.stRl[nowCursor].rl.line;
    figInput_cursor_leave(vStFigInput.cursor.now);//光标先停止

    if(vStFigInput.cursor.now >= vStFigInput.state.NeedNum)
    {//超限到达最左边
        vStFigInput.cursor.now = 0;
    }
    ++vStFigInput.cursor.now;//向右加
//    nowCursor=vStFigInput.cursor.now;
//    vStFigInput.stRl[nowCursor].rl.row=row;
//    vStFigInput.stRl[vStFigInput.cursor.now].rl.line=col+1;
    //需要设置一下光标所在位置，不能在这里得出，必须是上面调用来设置
    figInput_cursor_new(vStFigInput.cursor.now);//重新显示
//    for(ii=0;ii<U_INPUT_NUM_MAX;ii++){
//        if()
//        vStFigInput.stRl[ii].rl.row=row;
//        vStFigInput.stRl[ii].rl.line=col+1;
//        bBlink
//    }

}

/******************************************************************************
* FUNC: //
******************************************************************************/
void FigInput_CursorRight_withRowCol(U8 Row,U8 Col)
{
 //   U8 nowCursor;
//    U8 row;
   // U8 col;
//    U8 ii;
    if(  (vStFigInput.state.NeedNum == 0)
         || (vStFigInput.state.NeedNum >= U_INPUT_NUM_MAX))
    {
        return;
    }

    //nowCursor=vStFigInput.cursor.now;
//    row=vStFigInput.stRl[nowCursor].rl.row;
    //col=vStFigInput.stRl[nowCursor].rl.line;
    figInput_cursor_leave(vStFigInput.cursor.now);//光标先停止

    if(vStFigInput.cursor.now >= vStFigInput.state.NeedNum)
    {//超限到达最左边
        vStFigInput.cursor.now = 0;
    }
//    ++vStFigInput.cursor.now;//向右加
//    nowCursor=vStFigInput.cursor.now;
//    vStFigInput.stRl[nowCursor].rl.row=row;
    vStFigInput.stRl[vStFigInput.cursor.now].rl.row=Row;
    vStFigInput.stRl[vStFigInput.cursor.now].rl.line=Col;
    //需要设置一下光标所在位置，不能在这里得出，必须是上面调用来设置
    figInput_cursor_new(vStFigInput.cursor.now);//重新显示
//    for(ii=0;ii<U_INPUT_NUM_MAX;ii++){
//        if()
//        vStFigInput.stRl[ii].rl.row=row;
//        vStFigInput.stRl[ii].rl.line=col+1;
//        bBlink
//    }

}
void FigInput_CursorLeft(void)
{
    if(  (vStFigInput.state.NeedNum == 0)
         || (vStFigInput.state.NeedNum >= U_INPUT_NUM_MAX))
    {
        return;
    }

    figInput_cursor_leave(vStFigInput.cursor.now);

    if(vStFigInput.cursor.now == 0)
    {
        vStFigInput.cursor.now = (vStFigInput.state.NeedNum - 1);
    }
    else
    {
        vStFigInput.cursor.now--;
    }
    figInput_cursor_new(vStFigInput.cursor.now);
}

/******************************************************************************
* FUNC: // END
*   IN:
*  OUT:
******************************************************************************/
