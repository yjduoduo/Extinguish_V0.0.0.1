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


/*================= ���� ============================================*/

/*================= �ṹ���� ========================================*/

/*================= ˽�нṹ�������� ================================*/


/*================= ���к������� ====================================*/

/*================= ˽�к������� ====================================*/

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
// if ��Ҫ�������룺
BOOL bFigInputNeed(void)
{
    return (vStFigInput.state.NeedNum != 0);
}

/******************************************************************************
* FUNC: //
*   IN:
*  OUT:
******************************************************************************/

void FigInput_Init(void)  //��ʼ��
{
    U8 mIn;

    ClrRamIs00((U8*)(&vStFigInput), sizeof(TFigInput_st)); //ȫ��00

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
* FUNC: // ��������׼������������Ҫ FigInput_Add...��ʼ����λ��
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
* FUNC: // �������� �˳���
*   IN:
*  OUT:
******************************************************************************/
void FigInput_Stop(void)
{
    FigInput_Init();
}


/******************************************************************************
* FUNC: // ini: �������� 1��:
*   IN: ��Ҫ���Ⱥ�˳����á�
*  OUT:
******************************************************************************/

BOOL FigInput_AddIniFig(TYPE_LCD_RL mRow, TYPE_LCD_RL mLine,
                        U8 mFig, U8 mMax)
{
    return figInput_addIniOne(mRow, mLine,
                              mFig, mMax, FALSE);
}
/******************************************************************************
* FUNC: // ini: �������� 1��:
*   IN: ��Ҫ���Ⱥ�˳����á�
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
*   IN: ��Ҫ���Ⱥ�˳����á�
        mFig>=10��ʾ��ǰ����δ֪��
        �������У����������ص����棬������ʾ
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

// �����ϣ���ʾini�ַ���
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
        bInverse = TRUE;//���ݹ����˸����ʾ�ǲ�����Ҫȡ�����ڵ�ǰλ
    }


    if(vStFigInput.stRl[mItem].iFig >= 10)
    {
        ShowCodeCharRL(
                    vStFigInput.stRl[mItem].rl.row,
                    vStFigInput.stRl[mItem].rl.line,
                    " ",
                    bInverse);
    }
    else if(vStFigInput.stRl[mItem].bIsHide)//��������λ��ʾ
    {
        ShowCodeCharRL(
                    vStFigInput.stRl[mItem].rl.row,
                    vStFigInput.stRl[mItem].rl.line,
                    "*",
                    bInverse);
    }
    else
    {
        // 1bit���֣�������ʾ | ���ԣ�
        Show_1Fig_if_inverse(
                    vStFigInput.stRl[mItem].rl.row,
                    vStFigInput.stRl[mItem].rl.line,
                    vStFigInput.stRl[mItem].iFig,
                    bInverse
                    );
    }


}

/******************************************************************************
* FUNC: // ���������
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
* FUNC: // ini: �������� hex:
*   IN:
*  OUT:
// ������� GetFigInput_Group() ��ȡ �����һ������
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
        pGroup->itemStart = mInStart; // ����λ��:
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
* FUNC: // ini: ������ʾ������λ��:
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
// if ���볬�ޣ�
BOOL bFigInput_Exceed(void)
{
    // �����Ƿ��г��޵����� - all��
    return cacuFigInput_Exceed();
}


/******************************************************************************
* Public:
* FUNC: //
*   IN:
*  OUT: TRUE= ��ֵ��Ч��groupFig < max;
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
* FUNC: // �����Ƿ��г��޵�����
*   IN:
*  OUT: TRUE = sign = bExceed;
******************************************************************************/
// �����Ƿ��г��޵����� - ��ǰ�����йصģ�
// ֻ�����������ڼ�����ʱ�򣬲��������á�
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
    // ��ǰ������ !exceed:
    if(bExceedPre)
    {
        // �����Ƿ��г��޵����� - all - �������� + group��
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
// �����Ƿ��г��޵����� - all - �������� + group��
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


// �����Ƿ��г��޵����� - all �������֣�
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


// �����Ƿ��г��޵����� - һ�� �������֣�
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

// �����Ƿ��г��޵����� - all group�����
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
* FUNC: // ���� group����������
*   IN:
*  OUT: vStFigInput.group.buf[mGroupNum].hexFigIn;
*  OUT: TRUE= ��ֵ��Ч��groupFig < max;
******************************************************************************/
// ���� group����������
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
* FUNC: // �������룬����λ���б䣺
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
* FUNC: // ���µ����ּ����룺
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
         )//�������λ�ó��޻����ֳ��������
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
    figInput_cursor_leave(vStFigInput.cursor.now);//�����ֹͣ

    if(vStFigInput.cursor.now >= vStFigInput.state.NeedNum)
    {//���޵��������
        vStFigInput.cursor.now = 0;
    }
    ++vStFigInput.cursor.now;//���Ҽ�
//    nowCursor=vStFigInput.cursor.now;
//    vStFigInput.stRl[nowCursor].rl.row=row;
//    vStFigInput.stRl[vStFigInput.cursor.now].rl.line=col+1;
    //��Ҫ����һ�¹������λ�ã�����������ó����������������������
    figInput_cursor_new(vStFigInput.cursor.now);//������ʾ
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
    figInput_cursor_leave(vStFigInput.cursor.now);//�����ֹͣ

    if(vStFigInput.cursor.now >= vStFigInput.state.NeedNum)
    {//���޵��������
        vStFigInput.cursor.now = 0;
    }
//    ++vStFigInput.cursor.now;//���Ҽ�
//    nowCursor=vStFigInput.cursor.now;
//    vStFigInput.stRl[nowCursor].rl.row=row;
    vStFigInput.stRl[vStFigInput.cursor.now].rl.row=Row;
    vStFigInput.stRl[vStFigInput.cursor.now].rl.line=Col;
    //��Ҫ����һ�¹������λ�ã�����������ó����������������������
    figInput_cursor_new(vStFigInput.cursor.now);//������ʾ
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
