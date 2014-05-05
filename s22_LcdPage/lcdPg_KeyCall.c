#include "lcdPg_KeyCall.h"
#include "lcdSub_ModeTextFig.h"
#define __lcdSub_InputFig_C__
#include "lcdSub_InputFig.h"

#define __lcdPg_Page_C__
#include "lcdPg_Page.h"
//#define __lcdPg_Status_C__
#include "lcdPg_Status.h"
#include "phIoKeyScan.h"

//位置和文字
#include "posText.h"

#include "Lcd_swBuf_Task.h"

#include "tmrTick.h"

#include "lcdCst_PageNum.h"

#include "sysStatus.h"

#include "sysDef.h"

#include "lcdPg_ShowLineFun.h"

#include "lcdPg_ShowLineFun.h"

#define U_DevScan_Pix_Y1_Start_N  ((U_LCD_ROW_PIX_MAX )-5)

const U8 yval[6]={U_DevScan_Pix_Y1_Start_N-8-8-8-8-4-8-8,
                  U_DevScan_Pix_Y1_Start_N-8-8-8-8-4-8,
                  U_DevScan_Pix_Y1_Start_N-8-8-8-8-4,
                  U_DevScan_Pix_Y1_Start_N-8-8-8,
                  U_DevScan_Pix_Y1_Start_N-8-8,
                  U_DevScan_Pix_Y1_Start_N-8};

const U8 yval_p061[7]={U_DevScan_Pix_Y1_Start_N-8-8-8-8-8-8-3,
                       U_DevScan_Pix_Y1_Start_N-8-8-8-8-8-8,
                       U_DevScan_Pix_Y1_Start_N-8-8-8-8-8,
                       U_DevScan_Pix_Y1_Start_N-8-8-8-8,
                       U_DevScan_Pix_Y1_Start_N-8-8-8,
                       U_DevScan_Pix_Y1_Start_N-8-8,
                       U_DevScan_Pix_Y1_Start_N-8};



key_callbackfun pgcom_callb;//实现共用的结构

void donothingnonepara(void)
{

}

void donothing(funpara* para)
{
    (void)para;

}
BOOL donothingKey(funpara* para)
{
    (void)para;
    return FALSE;

}
void ClearPara(funpara* para)
{
    para->fig=0;
    para->flag=FALSE;
    para->KeyType.runflag=FALSE;
    para->KeyType.keytype=~0;
    para->TotalCall=0;
    para->curRowNow=0;
    para->col=0;
    para->row=0;
    //默认定时ID和时间
    para->tmrId=0;
    para->tmrMs=0;
    para->TmrTaskSetted=FALSE;
    para->firstentry=TRUE;
    para->val=0;
    para->TotalCall=&pgcom_callb;//默认所有的参数都指向这个地址
}

/*****************************************************************************
*FUNC:设置按键输入回调函数初始化，置Used为真
*IN:
*OUT:
*****************************************************************************/
void Clear_Key_CallBack(key_callbackfun* callb)
{
    U8 ii;
    callb->FunSets.Looptipsfun=donothing;
    callb->FunSets.Addrtipsfun=donothing;
    callb->FunSets.Implementfun=donothing;
    callb->FunSets.iniPagefun=donothing;
    callb->FunSets.JudgeInputNumfun=donothingKey;
    callb->FunSets.RecvKeyDealfun=donothingKey;
    callb->FunSets.Modifyfun=donothingKey;
    callb->FunSets.KeyUpfun=donothingKey;
    callb->FunSets.KeyDownfun=donothingKey;
    callb->FunSets.Tmrfun=donothingKey;
    callb->FunSets.SetTmr=donothingKey;
    callb->FunSets.GetTmr=donothingKey;
    callb->FunSets.KillTmr=donothingKey;
    //    callb->FunSets.selfInitfun=donothingnonepara;//不能在此做清空
    ClearPara(&callb->FunSets.para_ltp);
    ClearPara(&callb->FunSets.para_adr);
    ClearPara(&callb->FunSets.para_jud);
    ClearPara(&callb->FunSets.para_rec);
    ClearPara(&callb->FunSets.para_imp);
    ClearPara(&callb->FunSets.para_tmr);
    ClearPara(&callb->FunSets.para_ini);
    //    ClearPara(&callb->FunSets.para_cur);

    callb->curstartrow=0;
    callb->intputMaxnum=0;//记录最多输入数字的个数
    for(ii=0;ii<ARRAYSIZE(callb->inputFig);ii++)
        callb->inputFig[ii]=0;//记录输入数字
    callb->WhichPos=0;
    callb->overflag=FALSE;
    callb->pracpos=0;
    callb->JudegInputNumRange=FALSE;
    callb->HaveCursor=FALSE;
    callb->Calllast=FALSE;//默认函数在判断数字中调用，即先调用
    callb->KeyResponseSv=0;
    callb->KeyResponseEv=0;
    callb->hidecursor=FALSE;
    callb->hideInputNum=FALSE;
    //默认定时功能不启用
    callb->ortmrflag=FALSE;
    callb->execTmrTaskOnOverfg=FALSE;//默认不立即执行，在初始化阶段定义
    callb->pgNum=0;//默认界面
    callb->Used=TRUE;
    callb->ExecOnceNum=0;

}

/*****************************************************************************
*FUNC:设置按键输入结束后调用的函数，其callb->Used=FALSE;不被用
*IN:
*OUT:
*****************************************************************************/
void Clear_Key_CallBack_Over(key_callbackfun* callb)
{
    U8 ii;
    callb->FunSets.Looptipsfun=donothing;
    callb->FunSets.Addrtipsfun=donothing;
    callb->FunSets.Implementfun=donothing;
    callb->FunSets.iniPagefun=donothing;
    callb->FunSets.JudgeInputNumfun=donothingKey;
    callb->FunSets.RecvKeyDealfun=donothingKey;
    callb->FunSets.Modifyfun=donothingKey;
    callb->FunSets.KeyUpfun=donothingKey;
    callb->FunSets.KeyDownfun=donothingKey;
    //    callb->FunSets.selfInitfun=donothingnonepara;//不能在此做清空
    ClearPara(&callb->FunSets.para_ltp);
    ClearPara(&callb->FunSets.para_adr);
    ClearPara(&callb->FunSets.para_jud);
    ClearPara(&callb->FunSets.para_rec);
    ClearPara(&callb->FunSets.para_imp);
    //    ClearPara(&callb->FunSets.para_cur);

    callb->curstartrow=0;
    callb->intputMaxnum=0;//记录最多输入数字的个数
    for(ii=0;ii<ARRAYSIZE(callb->inputFig);ii++)
        callb->inputFig[ii]=0;//记录输入数字
    callb->WhichPos=0;
    callb->overflag=FALSE;
    callb->pracpos=0;
    callb->JudegInputNumRange=FALSE;
    callb->HaveCursor=FALSE;
    callb->Calllast=FALSE;//默认函数在判断数字中调用，即先调用
    callb->KeyResponseSv=0;
    callb->KeyResponseEv=0;
    callb->hidecursor=FALSE;
    callb->hideInputNum=FALSE;
    callb->Used=FALSE;
}

BOOL JudgeFigInRange(U8 fig,U8 startFig,U8 endFig)
{
    /*    if(0==startFig&&0==endFig&&0==fig)
        return TRUE;
    else */
    if(fig>=startFig&&fig<=endFig)
        return TRUE;
    else
        return FALSE;

}
//p010使用1，2来停止和启动相关功能
BOOL BootOrExit(U8 key,key_callbackfun* TotalCall)
{
    U8 ii;
    funpara para;
    if(TotalCall->Calllast)//即如果后期调用的话
        return FALSE;
    para.fig=key;
    para.TotalCall=TotalCall;
    para.row=TotalCall->FunSets.para_imp.row;
    para.col=TotalCall->FunSets.para_imp.col;
    for(ii=0;ii<ARRAYSIZE(para.str);ii++){
        para.str[ii]=TotalCall->FunSets.para_imp.str[ii];
    }
    switch(key){
    case 0x01://1键值启动命令
        TotalCall->FunSets.para_adr.flag=FALSE;
        TotalCall->FunSets.Implementfun(&para);
        break;
    case 0x02://2键值停止命令
        TotalCall->FunSets.para_adr.flag=FALSE;
        TotalCall->FunSets.Implementfun(&para);
        break;
    default:
        return TRUE;
    }
    return FALSE;
}

//数字输入范围的判断
BOOL p010_InputNum_InRange(funpara* pa)
{
    if(pa->TotalCall->WhichPos>4){
        return TRUE;

    }else if(0==pa->TotalCall->WhichPos){//第一次输入的数字判断
        if(!JudgeFigInRange(pa->fig,1,4))
            return TRUE;
    }else if(1==pa->TotalCall->WhichPos){//the second
        if(!JudgeFigInRange(pa->fig,0,2))
            return TRUE;
    }else if(2==pa->TotalCall->WhichPos){//the third
        if(2==pa->TotalCall->inputFig[pa->TotalCall->WhichPos-1])
            if(!JudgeFigInRange(pa->fig,0,0))
                return TRUE;

    }else if(3==pa->TotalCall->WhichPos){//the fourth
        if(2==pa->TotalCall->inputFig[pa->TotalCall->WhichPos-2])
            if(0==pa->TotalCall->inputFig[pa->TotalCall->WhichPos-1])
                if(!JudgeFigInRange(pa->fig,0,0))
                    return TRUE;
    }else if(4==pa->TotalCall->WhichPos){//the fifth,实现功能
        if(!JudgeFigInRange(pa->fig,1,2))
            return  TRUE;
        if(BootOrExit(pa->fig,pa->TotalCall))
            return TRUE;
        pa->TotalCall->WhichPos++;
        return  TRUE;
    }
    return FALSE;
}

BOOL p058_InputNum_InRange(funpara* pa)
{
    if(pa->TotalCall->WhichPos>1){
        return FALSE;

    }else if(0==pa->TotalCall->WhichPos){//需要立即实现
        if(!JudgeFigInRange(pa->fig,1,4))
            return  TRUE;
    }
    return FALSE;
}
BOOL p015_InputNum_InRange(funpara* para)
{
    if(para->TotalCall->WhichPos>1){
        return FALSE;

    }else if(0==para->TotalCall->WhichPos){//需要立即实现
        if(!JudgeFigInRange(para->fig,1,2))
            return  TRUE;
        if(BootOrExit(para->fig,para->TotalCall))
            return TRUE;
        para->TotalCall->WhichPos++;
        return  TRUE;
    }
    return FALSE;
}
BOOL p083_InputNum_InRange(funpara* para)
{
    if(para->TotalCall->WhichPos>para->TotalCall->intputMaxnum){
        return FALSE;

    }else if(2==para->TotalCall->WhichPos){
        para->TotalCall->curstartrow+=2;
    }else if(5==para->TotalCall->WhichPos){
        para->TotalCall->curstartrow+=2;
    }else if(9==para->TotalCall->WhichPos){
        //        para->TotalCall->curstartrow+=2;
        if(!JudgeFigInRange(para->fig,1,2))
            return  TRUE;
        if(BootOrExit(para->fig,para->TotalCall))
            return TRUE;
        para->TotalCall->WhichPos++;
        return  TRUE;
    }
    return FALSE;
}
BOOL pcom_InputNum_InRange(funpara* pa)
{
    //    if(pa->TotalCall->WhichPos>1){
    //        return FALSE;

    //    }else if(0==pa->TotalCall->WhichPos){//需要立即实现
    ////        if(!JudgeFigInRange(pa->fig,1,4))
    ////            return  TRUE;
    ////        if(BootOrExit(para->fig,para->TotalCall))
    ////            return TRUE;
    ////        para->TotalCall->WhichPos++;
    ////        return  TRUE;
    //    }
    return FALSE;
}

BOOL p042_InputNum_InRange(funpara* pa)
{
    if(pa->TotalCall->WhichPos>1){
        return FALSE;

    }else if(3==pa->TotalCall->WhichPos){//需要立即实现
        //        if(!JudgeFigInRange(pa->fig,1,4))
        //            return  TRUE;
    }
    return FALSE;
}
BOOL p016_InputNum_InRange_DirectExec(funpara* pa)
{
    if(BootOrExit(pa->fig,pa->TotalCall))
        return TRUE;
    return FALSE;
}
//数字输入范围的判断
BOOL p017_InputNum_InRange(funpara *para)
{
    if(para->TotalCall->WhichPos>5){
        return FALSE;

    }else if(0==para->TotalCall->WhichPos){//第一次输入的数字判断
        if(!JudgeFigInRange(para->fig,1,4))
            return TRUE;
    }else if(1==para->TotalCall->WhichPos){//the second
        if(!JudgeFigInRange(para->fig,0,2))
            return TRUE;
    }else if(2==para->TotalCall->WhichPos){//the third
        if(2==para->TotalCall->inputFig[para->TotalCall->WhichPos-1])
            if(!JudgeFigInRange(para->fig,0,0))
                return TRUE;

    }else if(3==para->TotalCall->WhichPos){//the fourth
        if(2==para->TotalCall->inputFig[para->TotalCall->WhichPos-2])
            if(0==para->TotalCall->inputFig[para->TotalCall->WhichPos-1])
                if(!JudgeFigInRange(para->fig,0,0))
                    return TRUE;
    }else if(4==para->TotalCall->WhichPos){//the fifth,实现功能
        if(!JudgeFigInRange(para->fig,1,5))
            return  TRUE;
    }else if(5==para->TotalCall->WhichPos){//按键1或2开启与关闭功能
        if(!JudgeFigInRange(para->fig,1,2))
            return  TRUE;
        if(BootOrExit(para->fig,para->TotalCall))
            return TRUE;
        para->TotalCall->WhichPos++;
        return  TRUE;
    }
    return FALSE;
}

//数字输入范围的判断，年月日时分秒
BOOL p013_InputNum_InRange(funpara *para)
{
    if(para->TotalCall->WhichPos>12){
        return FALSE;

    }else if(0==para->TotalCall->WhichPos){//第一次年
        //        if(!JudgeFigInRange(para->fig,1,4))
        //            return TRUE;
    }else if(1==para->TotalCall->WhichPos){//the second
        //        if(!JudgeFigInRange(para->fig,0,2))
        //            return TRUE;
    }else if(2==para->TotalCall->WhichPos){//the third月
        if(!JudgeFigInRange(para->fig,0,1))
            return TRUE;
    }else if(3==para->TotalCall->WhichPos){//the fourth
        if(1==para->TotalCall->inputFig[para->TotalCall->WhichPos-1])
            if(!JudgeFigInRange(para->fig,0,2))
                return TRUE;
    }else if(4==para->TotalCall->WhichPos){//the fifth,日
        if(!JudgeFigInRange(para->fig,0,3))
            return  TRUE;
    }else if(5==para->TotalCall->WhichPos){//
        if(3==para->TotalCall->inputFig[para->TotalCall->WhichPos-1])
            if(!JudgeFigInRange(para->fig,0,1))
                return  TRUE;
    }else if(6==para->TotalCall->WhichPos){//时
        if(!JudgeFigInRange(para->fig,0,2))
            return  TRUE;
    }else if(7==para->TotalCall->WhichPos){//
        if(2==para->TotalCall->inputFig[para->TotalCall->WhichPos-1])
            if(!JudgeFigInRange(para->fig,0,3))
                return  TRUE;
    }else if(8==para->TotalCall->WhichPos){//分
        if(!JudgeFigInRange(para->fig,0,5))
            return  TRUE;
    }else if(9==para->TotalCall->WhichPos){//

    }else if(10==para->TotalCall->WhichPos){//秒
        if(!JudgeFigInRange(para->fig,0,5))
            return  TRUE;
    }else if(11==para->TotalCall->WhichPos){//

    }else if(12==para->TotalCall->WhichPos){//按键1或2开启与关闭功能
        if(!JudgeFigInRange(para->fig,1,2))
            return  TRUE;
        if(BootOrExit(para->fig,para->TotalCall))
            return TRUE;
        para->TotalCall->WhichPos++;
        return  TRUE;
    }
    return FALSE;
}
//数字输入范围的判断，年月日时分秒
//灭火盘控制
BOOL p030_InputNum_InRange(funpara *para)
{
    if(para->TotalCall->WhichPos>12){
        return FALSE;

    }else if(0==para->TotalCall->WhichPos){//分区
        if(!JudgeFigInRange(para->fig,1,4))
            return TRUE;
        para->TotalCall->curstartrow+=2;//光标换行

    }else if(1==para->TotalCall->WhichPos){//the second
        if(!JudgeFigInRange(para->fig,0,1))
            return TRUE;
    }else if(2==para->TotalCall->WhichPos){//the third月
        if(!JudgeFigInRange(para->fig,0,1))
            return TRUE;
    }else if(3==para->TotalCall->WhichPos){//the fourth
        if(!JudgeFigInRange(para->fig,0,1))
            return TRUE;
    }else if(4==para->TotalCall->WhichPos){//the fifth,日
        if(!JudgeFigInRange(para->fig,0,1))
            return  TRUE;
        para->TotalCall->curstartrow+=2;
    }else if(5==para->TotalCall->WhichPos){//
        if(!JudgeFigInRange(para->fig,0,1))
            return  TRUE;
    }else if(6==para->TotalCall->WhichPos){//故障检测
        if(!JudgeFigInRange(para->fig,0,1))
            return  TRUE;
        para->TotalCall->curstartrow+=2;
    }else if(7==para->TotalCall->WhichPos){//启动延时
        if(!JudgeFigInRange(para->fig,0,3))
            return  TRUE;
    }else if(8==para->TotalCall->WhichPos){//
        if(3==para->TotalCall->inputFig[para->TotalCall->WhichPos-1])
            if(!JudgeFigInRange(para->fig,0,0))
                return  TRUE;
        para->TotalCall->curstartrow+=2;
    }else if(9==para->TotalCall->WhichPos){//喷洒时间
        if(!JudgeFigInRange(para->fig,1,6))
            return  TRUE;
    }else if(10==para->TotalCall->WhichPos){//
        if(6==para->TotalCall->inputFig[para->TotalCall->WhichPos-1])
            if(!JudgeFigInRange(para->fig,0,0))
                return  TRUE;
    }else if(11==para->TotalCall->WhichPos){//
        if(6==para->TotalCall->inputFig[para->TotalCall->WhichPos-2])
            if(!JudgeFigInRange(para->fig,0,0))
                return  TRUE;


    }else if(12==para->TotalCall->WhichPos){//按键1或2开启与关闭功能
        if(!JudgeFigInRange(para->fig,1,2))
            return  TRUE;
        if(BootOrExit(para->fig,para->TotalCall))
            return TRUE;
        para->TotalCall->WhichPos++;
        return  TRUE;
    }
    return FALSE;
}



/*****************************************************************************
*FUNC:需要按键输入时，定时调用显示相关内容
*IN:
*OUT:
*****************************************************************************/
BOOL pg_keyDeal(U8 cursorrow,U8 *pracpos,const U8 *cstpos,U8 size,key_callbackfun* TotalCall,allowKeyrun* runF)
{
    //定时调用显示相关内容
    if(TotalCall->overflag&&TotalCall->ortmrflag&&TotalCall->execTmrTaskOnOverfg){
        TotalCall->FunSets.SetTmr(&TotalCall->FunSets.para_tmr);
        if(!TotalCall->FunSets.GetTmr(&TotalCall->FunSets.para_tmr))
            TotalCall->FunSets.Tmrfun(&TotalCall->FunSets.para_tmr);
    }
    FigInput_Exec();//光标闪烁
    if(!bGetPageKey(&vThisPageKey))
    {
        return TRUE;
    }

    switch(vThisPageKey)
    {
    case 0x00:
    case 0x01:
    case 0x02:
    case 0x03:
    case 0x04:
    case 0x05:
    case 0x06:
    case 0x07:
    case 0x08:
    case 0x09:
        InputNum_Show_common_call(cursorrow,pracpos,
                                  vThisPageKey,cstpos,
                                  size,TotalCall);
        break;
    case U_KEY_Enter:
    case U_KEY_Star:
        //        if(vThisPageKey==runF->keytype)
    case U_KEY_Pound:
        if(runF->runflag)
            if(vThisPageKey==runF->keytype)
                if(TotalCall->overflag)
                    TotalCall->FunSets.Implementfun(&TotalCall->FunSets.para_imp);
        break;
    case U_KEY_Left:
        TotalCall->FunSets.Modifyfun(NULL);
        break;
    case U_KEY_Up:
        TotalCall->FunSets.KeyUpfun(NULL);
        break;
    case U_KEY_Down:
        TotalCall->FunSets.KeyDownfun(NULL);
        break;
    default:
        return TRUE;
    }
    return FALSE;
}

//按键处理，不需要处理时返回真
BOOL p010_keyDeal(funpara* para)
{
    (void)para;//默认不使用，直接在结构中设置
    if(pg_keyDeal(pgcom_callb.curstartrow,
                  &pgcom_callb.pracpos,
                  pgcom_callb.curarrayptr,
                  pgcom_callb.intputMaxnum,
                  &pgcom_callb,&pgcom_callb.FunSets.para_rec.KeyType))
        return TRUE;
    return FALSE;
}

void InputNum_Show_common_call(U8 cursorrow,U8 *pracpos,U8 fig,const U8 *cstpos,U8 size,key_callbackfun* TotalCall)
{
    U8 ii;
    funpara para;
    para.fig=fig;
    para.TotalCall=TotalCall;
    for(ii=0;ii<ARRAYSIZE(para.str);ii++){
        para.str[ii]=TotalCall->FunSets.para_imp.str[ii];
    }
    para.row=TotalCall->FunSets.para_imp.row;
    para.col=TotalCall->FunSets.para_imp.col;
    if(!TotalCall->HaveCursor){//没有光标直接执行的
        TotalCall->FunSets.Implementfun(&para);
        TotalCall->overflag=TRUE;
        return;
    }
    if(TotalCall->overflag)//稍后执行定时功能,置标志位，定时功能再执行
        TotalCall->execTmrTaskOnOverfg=TRUE;

    if(TotalCall->JudegInputNumRange&&TotalCall->HaveCursor){
        if(TotalCall->FunSets.JudgeInputNumfun(&para))
            return;
    }


    if(*pracpos<size&&TotalCall->HaveCursor){//必须为<，不然会越界，越界就会出现左边字符
        FigInput_AddIniFig_WithCurHide(cursorrow,*(cstpos+*pracpos),fig,10,TotalCall->hideInputNum);

        //记录第一个数字
        if(*pracpos < TotalCall->intputMaxnum){
            if(*pracpos>ARRAYSIZE(TotalCall->inputFig))
                ShowCodeCharRL(4,0,"数字数组越界",FALSE);
            TotalCall->inputFig[TotalCall->WhichPos]=fig;
            TotalCall->WhichPos++;
        }
        TotalCall->FunSets.para_adr.flag=TRUE;//显示第二个地址
        if(TotalCall->FunSets.para_adr.flag){
            TotalCall->FunSets.Looptipsfun(&TotalCall->FunSets.para_ltp);
            TotalCall->FunSets.Addrtipsfun(&TotalCall->FunSets.para_adr);
        }

        //如何设置光标
        if(size-1==*pracpos)//设置最后一位并停止
        {//最后一个数，光标右移两位并停止
            FigInput_AddIniEnd();
            figInput_cursorBlink_stop();
            FigInput_Stop();
            TotalCall->FunSets.para_imp.flag=TRUE;//数字内容输入结束
            TotalCall->overflag=TRUE;
            if(TotalCall->Calllast){//是否需要最后实现
                TotalCall->FunSets.Implementfun(&para);
            }
        }else if(*pracpos<size)
            FigInput_CursorRight_withRowCol(TotalCall->curstartrow,*(cstpos+*pracpos+1));//光标总是在输入数字的后面
        else{
            FigInput_CursorRight_withRowCol(TotalCall->curstartrow,*(cstpos+*pracpos));
        }
        FigInput_AddIniEnd();
        (*pracpos)++;

    }else{//输入内容后的其它处理

    }

}










void CursorInit(void)
{
    FigInput_Init();
    figInput_cursorBlink_start(0);//show cursor
}
//光标是否闪动
void HaveCursor(void)
{
    if(pgcom_callb.HaveCursor){
        CursorInit();
        FigInput_AddIniFig_WithCurHide(pgcom_callb.curstartrow,*pgcom_callb.curarrayptr,0,10,pgcom_callb.hidecursor);
    }

}

#define MAXROW 5
//行的内容
const U8 PosRow[MAXROW]={0,2,4,6,8};
const defposText AllPosText[MAX_PAGE]={
    {U_P000_MAIN},
    {U_P001_FireAlarm},
    {U_P002_Monitor},
    {U_P003_Disable},
    {U_P004_Fault},
    {U_P005_Link},
    {U_P006_Extg},
    {U_P007_Status},
    {U_P008_MENU},
    {U_P009_UserLogin},
    {U_P010_ManuActModu,//手动启停设备
     {{1,1,0,1,1},{"手动启停设备 ","_回路___地址 功能：","","提示：","1.启动 2.停止"},2,&cstpos_p010[0]},//中文
     {{1,1,0,1,1},{"manual start","_loop___addr func:","","tips:","1.start 2.stop"},2,&cstpos_p010[0]},//英文
     4},
    {U_P011_Help,//
     {{1,0,0,0,0},{"帮助：","","","",""},0,},//中文
     {{1,1,0,1,1},{"","","","",""},2,},//英文
     0},
    {U_P012_ManuAuto},
    {U_P013_SetClock,
     {{1,2,0,1,1},{"时间设置","20__年__月__日__时__分__秒","","1.设置 2.取消","提示："},2,&cstpos_p013[0]},//中文
     {{1,1,0,1,1},{"","","","",""},0,},//英文
     12},
    {U_P014_MiniEvent},
    {U_P015_SetDefault,//
     {{10,1,0,0,0},{"恢复默认设置?","1:是   2:退出","","",""},0,},//中文
     {{1,1,0,1,1},{"","","","",""},2,},//英文
     0},
    {U_P016_AutoRegist,
     {{1,},{"自动登记",},0,},//中文
     {{1,1,0,1,1},{"","","","",""},0,},//英文
     0},
    {U_P017_ManuRegist,
     {{1,1,1,1,1},{"手动登记 _回路___地址_类型","提示：","1探测 2联动 3启停按钮","4手自动盒 5声光","1.登记 2.取消"},0,&cstpos_p017[0]},//中文
     {{1,1,1,1,1},{"","","","",""},0,},//英文
     5},
    {U_P018_SetDisable,
     {{1,1,1,1,1},{"手动屏蔽 _回路___地址_类型","提示：","1探测 2联动 3启停按钮","4手自动盒 5声光","1.屏蔽 2.取消"},0,&cstpos_p017[0]},//中文
     {{1,1,1,1,1},{"","","","",""},0,},//英文
     5},
    {U_P019_SetNote,//
     {{1,1,1,0,0},{"手动注释","_回路___地址","注释内容:","",""},2,&cstpos_p010[0]},//中文
     {{1,1,0,1,1},{"","","","",""},2,},//英文
     4},
    {U_P020_SetLinkLogic,//
     {{1,1,1,0,0},{"设置联动编程","_回路___地址","内容:","",""},2,&cstpos_p010[0]},//中文
     {{1,1,0,1,1},{"","","","",""},2,},//英文
     4},
    {U_P021_P},
    {U_P022_P},
    {U_P023_P},
    {U_P024_SetMachNet,
     {{1,1,0,0,0},{"设置联网控制器","本机地址：__  主机地址：__","","",""},2,&cstpos_p024[0]},//中文
     {{1,1,0,1,1},{"","","","",""},2,&cstpos_p024[0]},//英文
     4},
    {U_P025_P},
    {U_P026_P},
    {U_P027_SetAddrRelation,
     {{1,1,0,0,0},{"设置本机关联地址","__机__回路___地址 ~ ___地址","","",""},2,&cstpos_p027[0]},//中文
     {{1,1,0,1,1},{"","","","",""},2,&cstpos_p027[0]},//英文
     10},
    {U_P028_QrAddrRelation,//
     {{1,1,1,0,0},{"查询关联地址","_回路___地址","内容:","",""},2,&cstpos_p010[0]},//中文
     {{1,1,0,1,1},{"","","","",""},2,},//英文
     4},
    {U_P029_P},
    {U_P030_SetUnitRegi,
     {{1,1,1,1,1},{"灭火区设置      分区(1~4)_","登记标志_ 回路_ 输入1_ 输入2_","灭火_     故障检测_","启动延时(0~30s)__  1.设置2.取消","喷洒时间(1~600s)___"},0,&cstpos_p030[0]},//中文
     {{1,1,1,1,1},{"","","","",""},0,},//英文
     12},
    {U_P031_P},
    {U_P032_P},
    {U_P033_P},
    {U_P034_P},
    {U_P035_P},
    {U_P036_P},
    {U_P037_SetLanguage,//选择中英文
     {{12,2,2,0,0},{"语言选择","1.中文","2.英文","",""},0,},//中文
     {{1,1,0,1,1},{"","","","",""},2,},//英文
     0},
    {U_P038_SetModeFieldDebug,//模式设置
     {{12,2,2,0,0},{"模式设置","1.正常运行模式","2.调试模式","",""},0,},//中文
     {{1,1,0,1,1},{"","","","",""},2,},//英文
     0},
    {U_P039_QrModeFieldDebug,//
     {{1,0,0,0,0},{"查询调试模式","","","",""},0,},//中文
     {{1,1,0,1,1},{"","","","",""},2,},//英文
     0},
    {U_P040_QrNowFault,//故障信息：
     {{1,0,0,0,0},{"故障信息：","","","",""},0,},//中文
     {{1,1,0,1,1},{"","","","",""},2,},//英文
     0},
    {U_P041_QrNowDisable,//屏蔽信息：
     {{1,0,0,0,0},{"屏蔽信息：","","","",""},0,},//中文
     {{1,1,0,1,1},{"","","","",""},2,},//英文
     0},
    {U_P042_QrLoopLinkLgc,
     {{1,1,0,0,0},{"查询联动编程","_回路___地址","","",""},2,&cstpos_p010[0]},//中文
     {{1,1,0,1,1},{"","","","",""},2,&cstpos_p010[0]},//英文
     4},
    {U_P043_P},
    {U_P044_QrNote,//
     {{1,0,0,0,0},{"_回路___地址","","","",""},0,&cstpos_p010[0]},//中文
     {{1,1,0,1,1},{"","","","",""},0,&cstpos_p010[0]},//英文
     4},
    {U_P045_P},
    {U_P046_P},
    {U_P047_QrSoftVer,//
     {{1,1,0,0,0},{"版本查询","类型  盘号  版本","","",""},0,},//中文
     {{1,1,0,1,1},{"","","","",""},2,},//英文
     0},
    {U_P048_QrUnitRegi,//
     {{1,0,0,0,0},{"查询灭火区设置","","","",""},0,},//中文
     {{1,1,0,1,1},{"","","","",""},2,},//英文
     0},
    {U_P049_QrMachNet,//
     {{1,0,0,0,0},{"查询组网控制器","","","",""},0,},//中文
     {{1,1,0,1,1},{"","","","",""},2,},//英文
     0},
    {U_P050_P},
    {U_P051_P},
    {U_P052_QrHistAll,//
     {{1,0,0,0,0},{"全部历史信息","","","",""},0,},//中文
     {{1,1,0,1,1},{"","","","",""},2,},//英文
     0},
    {U_P053_QrHistAlarm,//
     {{1,0,0,0,0},{"火警历史信息","","","",""},0,},//中文
     {{1,1,0,1,1},{"","","","",""},2,},//英文
     0},
    {U_P054_QrHistLink,//
     {{1,0,0,0,0},{"联动历史信息","","","",""},0,},//中文
     {{1,1,0,1,1},{"","","","",""},2,},//英文
     0},
    {U_P055_QrHistFault,//
     {{1,0,0,0,0},{"故障历史信息","","","",""},0,},//中文
     {{1,1,0,1,1},{"","","","",""},2,},//英文
     0},
    {U_P056_QrHistOpea,//
     {{1,0,0,0,0},{"操作历史信息","","","",""},0,},//中文
     {{1,1,0,1,1},{"","","","",""},2,},//英文
     0},
    {U_P057_QrHistOthers,//
     {{1,0,0,0,0},{"其它历史信息","","","",""},0,},//中文
     {{1,1,0,1,1},{"","","","",""},2,},//英文
     0},
    {U_P058_QrFieldRegist,
     {{3,0,0,0,0},{"_区 登记信息","","","",""},0,&cstpos_p058[0]},//中文
     {{1,1,0,1,1},{"","","","",""},2,&cstpos_p058[0]},//英文
     1},
    {U_P059_QrAutoManu,
     {{1,1,1,1,1},{"查询手动自动","一区:","二区:","三区:","四区:"},0,},//中文
     {{1,1,1,1,1},{"","","","",""},2,},//英文
     0},
    {U_P060_TsLoopDevScan,
     {{6,0,0,0,0},{"_回路","","","",""},0,&cstpos_p060[0]},//中文
     {{1,1,0,1,1},{"","","","",""},2,&cstpos_p060[0]},//英文
     1},
    {U_P061_TsDeteCurve,
     {{5,0,0,0,0},{"_回路___地址","","","",""},0,&cstpos_p061[0]},//中文
     {{1,0,0,0,0},{"","","","",""},0,&cstpos_p061[0]},//英文
     4},
    {U_P062_TsLoopData,
     {{1,1,1,1,0},{"回路参数查询","_回路","回路背景电流:","回路24V时电流:",""},2,&cstpos_p062[0]},//中文
     {{1,0,0,0,0},{"","","","",""},2,&cstpos_p062[0]},//英文
     1},
    {U_P063_TsDeteType,
     {{1,1,1,1,0},{"现场设备类型状态","_回路___地址","部件类型:","部件状态:",""},2,&cstpos_p010[0]},//中文
     {{1,0,0,0,0},{"","","","",""},2,&cstpos_p010[0]},//英文
     4},
    {U_P064_TsDeteData,
     {{1,1,1,1,0},{"现场部件数据查询","_回路___地址","部件类型:","部件状态:",""},2,&cstpos_p010[0]},//中文
     {{1,0,0,0,0},{"","","","",""},2,&cstpos_p010[0]},//英文
     4},
    {U_P065_TsCSoundAndLed,//
     {{1,0,0,0,0},{"声、指示灯自检","","","",""},0,},//中文
     {{1,1,0,1,1},{"","","","",""},2,},//英文
     0},
    {U_P066_P},
    {U_P067_TsCKey,//
     {{1,0,0,0,0},{"按键检测","","","",""},0,},//中文
     {{1,1,0,1,1},{"","","","",""},2,},//英文
     0},
    {U_P068_TsAllHardware},
    {U_P069_P},
    {U_P070_P},
    {U_P071_P},
    {U_P072_TsCommUnit,//
     {{1,1,1,1,1},{"测试单元通讯","接收1区帧数:","接收2区帧数:","接收3区帧数:","接收4区帧数:"},0,},//中文
     {{1,1,1,1,1},{"","","","",""},2,},//英文
     0},
    {U_P073_TsCommMach,//
     {{1,1,0,0,0},{"测试机器通讯","接收主机帧数:","","",""},0,},//中文
     {{1,1,0,1,1},{"","","","",""},2,},//英文
     0},
    {U_P074_P},
    {U_P075_P},
    {U_P076_P},
    {U_P077_ClrLinkLogic,//
     {{1,1,0,0,0},{"清除联动编程","1:是   2:退出","","",""},2,},//中文
     {{1,1,0,1,1},{"","","","",""},2,},//英文
     0},
    {U_P078_ClrNote,//
     {{1,1,0,0,0},{"清除注释","1:是   2:退出","","",""},2,},//中文
     {{1,1,0,1,1},{"","","","",""},2,},//英文
     0},
    {U_P079_P},
    {U_P080_ClrLoopRegi,//
     {{1,1,0,0,0},{"清除回路登记","1:是   2:退出","","",""},2,},//中文
     {{1,1,0,1,1},{"","","","",""},2,},//英文
     0},
    {U_P081_ClrAddrRelation,//
     {{1,1,0,0,0},{"清除关联地址","1:是   2:退出","","",""},2,},//中文
     {{1,1,0,1,1},{"","","","",""},2,},//英文
     0},
    {U_P082_P},
    {U_P083_Pssw1_Change,
     {{1,1,1,1,1},{"修改1级密码","原有密码:___","新设密码:___","再次确认:___","1:是   2:退出"},2,&cstpos_p083[0]},//中文
     {{1,1,0,1,1},{"","","","",""},2,&cstpos_p083[0]},//英文
     9},
    {U_P084_Pssw2_Change,
     {{1,1,1,1,1},{"修改2级密码","原有密码:___","新设密码:___","再次确认:___","1:是   2:退出"},2,&cstpos_p083[0]},//中文
     {{1,1,0,1,1},{"","","","",""},2,&cstpos_p083[0]},//英文
     9},
    {U_P085_P},
    {U_P086_P},
    {U_PXXX},
    //    {{0,2,4,6,8},{"","","","",""},{"","","","",""}},
    //    {}
};

#define MAXROWNUMS 5

void ShowText(funpara* para)
{
    U8 num;
    U8 language;
    language= GetLanguage();

    for(num=0;num<MAXROWNUMS;num++){
        if(U_Chinese_LANGUAGE==language){//中文
            if(0 == AllPosText[para->PosTextN].CnPosText.pos[num])
                continue;
            //            ShowCodeCharRL(0, (cstpos_p010[0]), "手动启停设备", FALSE);
            ShowCodeCharRL(PosRow[num],
                           AllPosText[para->PosTextN].CnPosText.pos[num],
                           AllPosText[para->PosTextN].CnPosText.text[num],
                           FALSE);
        }else if(U_English_LANGUAGE == language){
            if(0 == AllPosText[para->PosTextN].EnPosText.pos[num])
                continue;
            ShowCodeCharRL(PosRow[num],
                           AllPosText[para->PosTextN].EnPosText.pos[num],
                           AllPosText[para->PosTextN].EnPosText.text[num],
                           FALSE);
        }
    }
}
void HaveCursorNot(funpara* para)
{
    if(para->TotalCall->HaveCursor)
        HaveCursor();
}

//p010初始化界面
void p010_inipage(funpara* para)
{
    ClrWindow_Page();
    (void)para;
    para->PosTextN=para->TotalCall->pgNum;
    ShowText(para);
    HaveCursorNot(para);
}
//p060初始化界面 回路浏览
void p060_inipage(funpara* para)
{
    ClrWindow_Page();
    (void)para;
    //need to transfer one value


    para->PosTextN=para->TotalCall->pgNum;
    ShowText(para);
    HaveCursorNot(para);

    dw_devScan_coordinate_new();
    //	dw_devScan_coordinate();
}
void p016_inipage(funpara *para)
{
    ClrWindow_Page();
    (void)para;
    para->PosTextN=para->TotalCall->pgNum;
    ShowText(para);
    HaveCursorNot(para);

    //    ShowXYCodeCharRL(0,0,1,"自动登记",FALSE);
}
void p017_inipage(funpara *para)
{
    ClrWindow_Page();
    (void)para;
    para->PosTextN=para->TotalCall->pgNum;
    ShowText(para);
    HaveCursorNot(para);

}
void p018_inipage(funpara *para)
{
    ClrWindow_Page();
    (void)para;
    para->PosTextN=para->TotalCall->pgNum;
    ShowText(para);
    HaveCursorNot(para);
}
void p013_inipage(funpara *para)
{
    ClrWindow_Page();
    (void)para;

    //    ShowXYCodeCharRL(0,0,1,"时间设置",FALSE);

    //    ShowXYCodeCharRL(3,0,2,timedatetext[0],FALSE);
    //    ShowCodeCharRL(6, (cstpos_p010[0]), "1.设置", FALSE);
    //    ShowCodeCharRL(6, (cstpos_p010[0]+10), "2.取消", FALSE);
    //    ShowCodeCharRL(8,1,"提示：",FALSE);
    //    //光标是否闪动
    //    HaveCursor();

    para->PosTextN=para->TotalCall->pgNum;
    ShowText(para);
    HaveCursorNot(para);


}
void p030_inipage(funpara *para)
{
    ClrWindow_Page();
    (void)para;
    //    ShowXYCodeCharRL(0,0,1,"灭火区设置",FALSE);
    //    ShowXYCodeCharRL(0,6,5,"分区(1~4)_",FALSE);
    //    ShowXYCodeCharRL(2,0,1,"登记标志_",FALSE);
    //    ShowXYCodeCharRL(2,4,3,"回路_",FALSE);
    //    ShowXYCodeCharRL(2,6,5,"输入1_",FALSE);
    //    ShowXYCodeCharRL(2,9,6,"输入2_",FALSE);
    //    ShowXYCodeCharRL(4,0,1,"灭火_",FALSE);
    //    ShowXYCodeCharRL(4,4,3,"故障检测_",FALSE);
    //    ShowXYCodeCharRL(6,0,1,"启动延时(0~30s)__",FALSE);
    //    ShowXYCodeCharRL(6,8,3,"1.设置 2.取消",FALSE);
    //    ShowXYCodeCharRL(8,0,1,"喷洒时间(1~600s)___",FALSE);

    //    //光标是否闪动
    //    HaveCursor();

    para->PosTextN=para->TotalCall->pgNum;
    ShowText(para);
    HaveCursorNot(para);

}
void p037_inipage(funpara *para)
{
    ClrWindow_Page();
    //    (void)para;
    //    ShowXYCodeCharRL(1,2,5,"语言选择",FALSE);
    //    ShowXYCodeCharRL(3,0,2,"1.中文",FALSE);
    //    ShowXYCodeCharRL(5,0,2,"2.英文",FALSE);

    para->PosTextN=para->TotalCall->pgNum;
    ShowText(para);
    HaveCursorNot(para);

}
void p038_inipage(funpara *para)
{
    ClrWindow_Page();
    //    (void)para;
    //    ShowXYCodeCharRL(1,2,8,"模式设置",FALSE);
    //    ShowXYCodeCharRL(3,0,2,"1.正常运行模式",FALSE);
    //    ShowXYCodeCharRL(5,0,2,"2.调试模式",FALSE);

    para->PosTextN=para->TotalCall->pgNum;
    ShowText(para);
    HaveCursorNot(para);

}
void p041_inipage(funpara *para)
{
    ClrWindow_Page();
    //    (void)para;
    //    ShowXYCodeCharRL(0,0,1,"屏蔽信息：",FALSE);

    para->PosTextN=para->TotalCall->pgNum;
    ShowText(para);
    HaveCursorNot(para);

}
void p040_inipage(funpara *para)
{
    ClrWindow_Page();
    //    (void)para;
    //    ShowXYCodeCharRL(0,0,1,"故障信息：",FALSE);

    para->PosTextN=para->TotalCall->pgNum;
    ShowText(para);
    HaveCursorNot(para);

}
void p044_inipage(funpara *para)
{
    ClrWindow_Page();
    //    (void)para;
    ////    ShowXYCodeCharRL(0,0,1,"汉字注释：",FALSE);
    //    ShowXYCodeCharRL(0,0,1,"_回路",FALSE);
    //    ShowXYCodeCharRL(0,2,2,"___地址",FALSE);
    ////    ShowXYCodeCharRL(0,8,0,"__控制器",FALSE);
    //    //光标是否闪动
    //    HaveCursor();

    para->PosTextN=para->TotalCall->pgNum;
    ShowText(para);
    HaveCursorNot(para);

}
void p039_inipage(funpara *para)
{
    ClrWindow_Page();
    //    (void)para;
    //    ShowXYCodeCharRL(0,0,1,"查询调试模式",FALSE);

    para->PosTextN=para->TotalCall->pgNum;
    ShowText(para);
    HaveCursorNot(para);

}
void p058_inipage(funpara *para)
{
    ClrWindow_Page();
    //    (void)para;
    //    ShowXYCodeCharRL(0,1,1,"_区",FALSE);
    //    ShowXYCodeCharRL(0,3,1,"登记信息",FALSE);
    //    //光标是否闪动
    //    HaveCursor();

    para->PosTextN=para->TotalCall->pgNum;
    ShowText(para);
    HaveCursorNot(para);

}
void p024_inipage(funpara *para)
{
    ClrWindow_Page();
    //    (void)para;
    //    ShowXYCodeCharRL(0,0,1,"设置联网控制器",FALSE);
    //    ShowXYCodeCharRL(2,0,1,"本机地址：__",FALSE);
    //    ShowXYCodeCharRL(2,7,1,"主机地址：__",FALSE);
    //    //光标是否闪动
    //    HaveCursor();

    para->PosTextN=para->TotalCall->pgNum;
    ShowText(para);
    HaveCursorNot(para);

}

void p027_inipage(funpara *para)
{
    ClrWindow_Page();
    //    (void)para;
    //    ShowXYCodeCharRL(0,0,1,"设置本机关联地址",FALSE);
    //    ShowXYCodeCharRL(2,0,1,"__机__回路___地址 ~ ___地址",FALSE);
    //    //光标是否闪动
    //    HaveCursor();

    para->PosTextN=para->TotalCall->pgNum;
    ShowText(para);
    HaveCursorNot(para);

}
void p015_inipage(funpara *para)
{
    //    (void)para;
    //    ShowXYCodeCharRL(2,2,1,"恢复默认设置?",FALSE);
    //    ShowXYCodeCharRL(4,2,1,"1:是   2:退出",FALSE);
    ////    //光标是否闪动
    ////    HaveCursor();

    para->PosTextN=para->TotalCall->pgNum;
    ShowText(para);
    HaveCursorNot(para);


}
//* 页面: // 手动注释
//*      _回路_ _地址
//* 	注释内容: 注释输入暂时延后做
void p019_inipage(funpara *para)
{
    //    (void)para;
    //    ShowXYCodeCharRL(0,0,1,"手动注释",FALSE);
    //    ShowXYCodeCharRL(2,0,1,"_回路___地址",FALSE);
    //    ShowXYCodeCharRL(4,0,1,"注释内容:",FALSE);
    ////    //光标是否闪动
    //    HaveCursor();
    para->PosTextN=para->TotalCall->pgNum;
    ShowText(para);
    HaveCursorNot(para);
}
void p020_inipage(funpara *para)
{/*
    (void)para;
    ShowXYCodeCharRL(0,0,1,"设置联动编程",FALSE);
    ShowXYCodeCharRL(2,0,1,"_回路___地址",FALSE);
    ShowXYCodeCharRL(4,0,1,"内容:",FALSE);
//    //光标是否闪动
    HaveCursor();*/

    para->PosTextN=para->TotalCall->pgNum;
    ShowText(para);
    HaveCursorNot(para);
}
void p028_inipage(funpara *para)
{/*
    (void)para;
    ShowXYCodeCharRL(0,0,1,"查询关联地址",FALSE);
    ShowXYCodeCharRL(2,0,1,"_回路___地址",FALSE);
//    ShowXYCodeCharRL(4,0,1,"内容:",FALSE);
//    //光标是否闪动
    HaveCursor();*/
    para->PosTextN=para->TotalCall->pgNum;
    ShowText(para);
    HaveCursorNot(para);
}

void p080_inipage(funpara *para)
{/*
    (void)para;
    ShowXYCodeCharRL(0,0,1,"清除回路登记",FALSE);
    ShowXYCodeCharRL(2,0,1,"1:是   2:退出",FALSE);
//    ShowXYCodeCharRL(2,0,1,"_回路___地址",FALSE);
//    ShowXYCodeCharRL(4,0,1,"内容:",FALSE);
//    //光标是否闪动
//    HaveCursor();*/
    para->PosTextN=para->TotalCall->pgNum;
    ShowText(para);
    HaveCursorNot(para);
}
void p077_inipage(funpara *para)
{
    //    (void)para;
    //    ShowXYCodeCharRL(0,0,1,"清除联动编程",FALSE);
    //    ShowXYCodeCharRL(2,0,1,"1:是   2:退出",FALSE);
    ////    ShowXYCodeCharRL(2,0,1,"_回路___地址",FALSE);
    ////    ShowXYCodeCharRL(4,0,1,"内容:",FALSE);
    ////    //光标是否闪动
    //    HaveCursor();

    para->PosTextN=para->TotalCall->pgNum;
    ShowText(para);
    HaveCursorNot(para);

}
void p078_inipage(funpara *para)
{
    //    (void)para;
    //    ShowXYCodeCharRL(0,0,1,"清除注释",FALSE);
    //    ShowXYCodeCharRL(2,0,1,"1:是   2:退出",FALSE);
    ////    ShowXYCodeCharRL(2,0,1,"_回路___地址",FALSE);
    ////    ShowXYCodeCharRL(4,0,1,"内容:",FALSE);
    ////    //光标是否闪动
    ////    HaveCursor();
    para->PosTextN=para->TotalCall->pgNum;
    ShowText(para);
    HaveCursorNot(para);
}

void p081_inipage(funpara *para)
{
    //    (void)para;
    //    ShowXYCodeCharRL(0,0,1,"清除关联地址",FALSE);
    //    ShowXYCodeCharRL(2,0,1,"1:是   2:退出",FALSE);
    ////    ShowXYCodeCharRL(2,0,1,"_回路___地址",FALSE);
    ////    ShowXYCodeCharRL(4,0,1,"内容:",FALSE);
    ////    //光标是否闪动
    ////    HaveCursor();
    para->PosTextN=para->TotalCall->pgNum;
    ShowText(para);
    HaveCursorNot(para);
}

void p083_inipage(funpara *para)
{
    //    (void)para;
    //    ShowXYCodeCharRL(0,0,1,"修改1级密码",FALSE);
    //    ShowXYCodeCharRL(2,0,1,"原有密码:___",FALSE);
    //    ShowXYCodeCharRL(4,0,1,"新设密码:___",FALSE);
    //    ShowXYCodeCharRL(6,0,1,"再次确认:___",FALSE);
    //    ShowXYCodeCharRL(8,0,1,"1:是   2:退出",FALSE);
    ////    ShowXYCodeCharRL(2,0,1,"_回路___地址",FALSE);
    ////    ShowXYCodeCharRL(4,0,1,"内容:",FALSE);
    ////    //光标是否闪动
    //    HaveCursor();

    para->PosTextN=para->TotalCall->pgNum;
    ShowText(para);
    HaveCursorNot(para);

}
void p084_inipage(funpara *para)
{
    //    (void)para;
    //    ShowXYCodeCharRL(0,0,1,"修改2级密码",FALSE);
    //    ShowXYCodeCharRL(2,0,1,"原有密码:___",FALSE);
    //    ShowXYCodeCharRL(4,0,1,"新设密码:___",FALSE);
    //    ShowXYCodeCharRL(6,0,1,"再次确认:___",FALSE);
    //    ShowXYCodeCharRL(8,0,1,"1:是   2:退出",FALSE);
    ////    ShowXYCodeCharRL(2,0,1,"_回路___地址",FALSE);
    ////    ShowXYCodeCharRL(4,0,1,"内容:",FALSE);
    ////    //光标是否闪动
    //    HaveCursor();

    para->PosTextN=para->TotalCall->pgNum;
    ShowText(para);
    HaveCursorNot(para);

}

void p061_inipage(funpara *para)
{
    ClrWindow_Page();
    //    (void)para;
    ////    ShowXYCodeCharRL(0,0,1,"探测器模拟曲线",FALSE);
    //    ShowXYCodeCharRL(0,2,1,"_回路___地址",FALSE);
    //    dw_devScan_coordinate_p061();
    //    HaveCursor();

    para->PosTextN=para->TotalCall->pgNum;
    ShowText(para);
    HaveCursorNot(para);
    dw_devScan_coordinate_p061();

}/*
* 页面: // 回路参数查询
*  	_回路:
*   回路背景电流:
*  回路24V时电流:*/
void p062_inipage(funpara *para)
{
    //    (void)para;
    //    ShowXYCodeCharRL(0,0,1,"回路参数查询",FALSE);
    //    ShowXYCodeCharRL(2,0,1,"_回路",FALSE);
    //    ShowXYCodeCharRL(4,0,1,"回路背景电流:",FALSE);
    //    ShowXYCodeCharRL(6,0,1,"回路24V时电流:",FALSE);
    //    HaveCursor();

    para->PosTextN=para->TotalCall->pgNum;
    ShowText(para);
    HaveCursorNot(para);

}
/******************************************************************************
* 页面: // 现场设备类型状态
*  	_回路_ _ _地址:
*   部件类型:
*   部件状态:
******************************************************************************/
void p063_inipage(funpara *para)
{
    //    (void)para;
    //    ShowXYCodeCharRL(0,0,1,"现场设备类型状态",FALSE);
    //    ShowXYCodeCharRL(2,0,1,"_回路___地址",FALSE);
    //    ShowXYCodeCharRL(4,0,1,"部件类型:",FALSE);
    //    ShowXYCodeCharRL(6,0,1,"部件状态:",FALSE);
    //    HaveCursor();

    para->PosTextN=para->TotalCall->pgNum;
    ShowText(para);
    HaveCursorNot(para);


}
void p064_inipage(funpara *para)
{
    //    (void)para;
    //    ShowXYCodeCharRL(0,0,1,"现场部件数据查询",FALSE);
    //    ShowXYCodeCharRL(2,0,1,"_回路___地址",FALSE);
    ////    ShowXYCodeCharRL(4,0,1,"部件类型:",FALSE);
    ////    ShowXYCodeCharRL(6,0,1,"部件状态:",FALSE);
    //    HaveCursor();

    para->PosTextN=para->TotalCall->pgNum;
    ShowText(para);
    HaveCursorNot(para);

}
void p065_inipage(funpara *para)
{
    //    (void)para;
    //    ShowXYCodeCharRL(0,0,1,"声、指示灯自检",FALSE);
    ////    ShowXYCodeCharRL(2,0,1,"_回路___地址",FALSE);
    ////    ShowXYCodeCharRL(4,0,1,"部件类型:",FALSE);
    ////    ShowXYCodeCharRL(6,0,1,"部件状态:",FALSE);
    ////    HaveCursor();
    para->PosTextN=para->TotalCall->pgNum;
    ShowText(para);
    HaveCursorNot(para);


}
void p067_inipage(funpara *para)
{
    //    (void)para;
    //    ShowXYCodeCharRL(0,0,1,"按键检测",FALSE);
    ////    ShowXYCodeCharRL(2,0,1,"_回路___地址",FALSE);
    ////    ShowXYCodeCharRL(4,0,1,"部件类型:",FALSE);
    ////    ShowXYCodeCharRL(6,0,1,"部件状态:",FALSE);
    ////    HaveCursor();

    para->PosTextN=para->TotalCall->pgNum;
    ShowText(para);
    HaveCursorNot(para);
}
/******************************************************************************
* 页面: // 测试 通讯-iCan;
* 接收1区帧数:
* 接收2区帧数:
* 接收3区帧数:
* 接收4区帧数:
******************************************************************************/
void p072_inipage(funpara *para)
{
    //    (void)para;
    //    ShowXYCodeCharRL(0,0,1,"测试单元通讯",FALSE);
    //    ShowXYCodeCharRL(2,0,1,"接收1区帧数:",FALSE);
    //    ShowXYCodeCharRL(4,0,1,"接收2区帧数:",FALSE);
    //    ShowXYCodeCharRL(6,0,1,"接收3区帧数:",FALSE);
    //    ShowXYCodeCharRL(8,0,1,"接收4区帧数:",FALSE);
    ////    ExecLcdShow();
    ////    HaveCursor();
    para->PosTextN=para->TotalCall->pgNum;
    ShowText(para);
    HaveCursorNot(para);

}
/******************************************************************************
* 页面: // 测试 通讯-eCan;
* 接收主机帧数:
* 其他控制器若在线，显示接收帧数；
******************************************************************************/
void p073_inipage(funpara *para)
{
    //    (void)para;
    //    ShowXYCodeCharRL(0,0,1,"测试机器通讯",FALSE);
    //    ShowXYCodeCharRL(2,0,1,"接收主机帧数:",FALSE);
    ////    ShowXYCodeCharRL(4,0,1,"接收2区帧数:",FALSE);
    ////    ShowXYCodeCharRL(6,0,1,"接收3区帧数:",FALSE);
    ////    ShowXYCodeCharRL(8,0,1,"接收4区帧数:",FALSE);
    ////    ExecLcdShow();
    ////    HaveCursor();

    para->PosTextN=para->TotalCall->pgNum;
    ShowText(para);
    HaveCursorNot(para);

}
/******************************************************************************
* 页面: // 帮助
* 暂时 显示生产厂名称
******************************************************************************/
void p011_inipage(funpara *para)
{
    ClrWindow_Page();
    //    (void)para;
    //    ShowXYCodeCharRL(0,0,1,"生产厂名称:",FALSE);

    para->PosTextN=para->TotalCall->pgNum;
    ShowText(para);
    HaveCursorNot(para);
}
/******************************************************************************
* 页面: //查询手动自动
* 显示已登记的区的手动自动  参考 ShowStr_AutoManuNowState();
* 一区:
* 二区:
* 三区:
* 四区:
******************************************************************************/
void p059_inipage(funpara *para)
{
    //    (void)para;
    //    ShowXYCodeCharRL(0,0,1,"查询手动自动",FALSE);
    //    ShowXYCodeCharRL(2,0,1,"一区:",FALSE);
    //    ShowXYCodeCharRL(4,0,1,"二区:",FALSE);
    //    ShowXYCodeCharRL(6,0,1,"三区:",FALSE);
    //    ShowXYCodeCharRL(8,0,1,"四区:",FALSE);

    para->PosTextN=para->TotalCall->pgNum;
    ShowText(para);
    HaveCursorNot(para);
}
void p052_inipage(funpara *para)
{
    //    (void)para;
    //    ShowXYCodeCharRL(0,0,1,"全部历史信息",FALSE);

    para->PosTextN=para->TotalCall->pgNum;
    ShowText(para);
    HaveCursorNot(para);
}
void p053_inipage(funpara *para)
{
    //    (void)para;
    //    ShowXYCodeCharRL(0,0,1,"火警历史信息",FALSE);

    para->PosTextN=para->TotalCall->pgNum;
    ShowText(para);
    HaveCursorNot(para);
}
void p054_inipage(funpara *para)
{
    //    (void)para;
    //    ShowXYCodeCharRL(0,0,1,"联动历史信息",FALSE);

    para->PosTextN=para->TotalCall->pgNum;
    ShowText(para);
    HaveCursorNot(para);
}
void p055_inipage(funpara *para)
{
    //    (void)para;
    //    ShowXYCodeCharRL(0,0,1,"故障历史信息",FALSE);

    para->PosTextN=para->TotalCall->pgNum;
    ShowText(para);
    HaveCursorNot(para);
}
void p056_inipage(funpara *para)
{
    //    (void)para;
    //    ShowXYCodeCharRL(0,0,1,"操作历史信息",FALSE);

    para->PosTextN=para->TotalCall->pgNum;
    ShowText(para);
    HaveCursorNot(para);
}
void p057_inipage(funpara *para)
{
    //    (void)para;
    //    ShowXYCodeCharRL(0,0,1,"其它历史信息",FALSE);

    para->PosTextN=para->TotalCall->pgNum;
    ShowText(para);
    HaveCursorNot(para);
}
void p042_inipage(funpara *para)
{
    //    (void)para;
    //    ShowXYCodeCharRL(0,0,1,"查询联动编程",FALSE);
    //    ShowXYCodeCharRL(2,0,1,"_回路",FALSE);
    //    ShowXYCodeCharRL(2,2,2,"___地址",FALSE);
    //    //光标是否闪动
    //    HaveCursor();

    para->PosTextN=para->TotalCall->pgNum;
    ShowText(para);
    HaveCursorNot(para);


}
void p047_inipage(funpara *para)
{
    //    (void)para;
    //    ShowXYCodeCharRL(0,0,1,"版本查询",FALSE);
    //    ShowXYCodeCharRL(2,0,1,"类型",FALSE);
    //    ShowXYCodeCharRL(2,4,1,"盘号",FALSE);
    //    ShowXYCodeCharRL(2,8,1,"版本",FALSE);
    //    //光标是否闪动
    ////    HaveCursor();

    para->PosTextN=para->TotalCall->pgNum;
    ShowText(para);
    HaveCursorNot(para);

}
void p049_inipage(funpara* para)
{
    //    (void)para;
    //    ShowXYCodeCharRL(0,0,1,"查询组网控制器",FALSE);
    para->PosTextN=para->TotalCall->pgNum;
    ShowText(para);
    HaveCursorNot(para);
}

void p048_inipage(funpara* para)
{
    //    (void)para;
    //    ShowXYCodeCharRL(0,0,1,"查询灭火区设置",FALSE);

    para->PosTextN=para->TotalCall->pgNum;
    ShowText(para);
    HaveCursorNot(para);


}
//开始各个页面的函数定义
//p010页面

//输入回路提示
void p010_loopinputtips(funpara* para)
{
    if(para->flag)
        ShowCodeCharRL(6, (cstpos_p010[0]+6), "回路范围1~4", FALSE);
    else
        ShowCodeCharRL(6, (cstpos_p010[0]+6), "          ", FALSE);
}
void p010_addrinputtips(funpara* para)
{
    if(para->flag)
        ShowCodeCharRL(6, (cstpos_p010[0]+5), "地址范围1~200", FALSE);
    else
        ShowCodeCharRL(6, (cstpos_p010[0]+5), "            ", FALSE);
}
//输入结束
void p010_complete(funpara* para)
{
    ShowCodeCharRL(6, (cstpos_p010[0]+5), "                ", FALSE);
    if(1==para->fig){
        ShowCodeCharRL(2, (cstpos_p010[0]+5+8+5), "启动", FALSE);
        ShowCodeCharRL(6, (cstpos_p010[0]+5), "设备已启动", FALSE);
    }
    else if(2==para->fig){
        ShowCodeCharRL(2, (cstpos_p010[0]+5+8+5), "停止", FALSE);
        ShowCodeCharRL(6, (cstpos_p010[0]+5), "设备已停止", FALSE);
    }
    else{
        ShowCodeCharRL(6, (cstpos_p010[0]+5), "         ", FALSE);
    }

}
void p016_complete(funpara* para)
{
    (void)para;
    ShowCodeCharRL(4,1,"系统正在登记...",FALSE);
    //    ShowCstCharRL()
    //添加登记功能。。。。。。。。。。
}
void p017_complete(funpara* para)
{
    switch(para->fig){
    case 0x01:
        ShowCodeCharRL(2,7,"地址已登记",FALSE);
        break;
    case 0x02:
        ShowCodeCharRL(2,7,"地址已取消",FALSE);
        break;
    default:
        break;
    }
}
void p018_complete(funpara* para)
{
    switch(para->fig){
    case 0x01:
        ShowCodeCharRL(2,7,"地址已屏蔽",FALSE);
        break;
    case 0x02:
        ShowCodeCharRL(2,7,"地址已取消",FALSE);
        break;
    default:
        break;
    }
}
#include "phClock.h"
extern TEvtClock_st stRamClock;
void p013_complete(funpara* para)
{
    //    const TEvtClock_st cstDefaultClock = {13, 10, 29,   16, 50, 0}; //年月日  时分秒

    switch(para->fig){
    case 0x01:
        stRamClock.year=para->TotalCall->inputFig[0]*10+para->TotalCall->inputFig[1];
        stRamClock.month=para->TotalCall->inputFig[2]*10+para->TotalCall->inputFig[3];
        stRamClock.day=para->TotalCall->inputFig[4]*10+para->TotalCall->inputFig[5];
        stRamClock.hour=para->TotalCall->inputFig[6]*10+para->TotalCall->inputFig[7];
        stRamClock.min=para->TotalCall->inputFig[8]*10+para->TotalCall->inputFig[9];
        stRamClock.sec=para->TotalCall->inputFig[10]*10+para->TotalCall->inputFig[11];
        if(SetClock(&stRamClock)){
            ShowCodeCharRL(8,8,"设置成功",FALSE);
        }else{
            ShowCodeCharRL(8,8,"设置失败",FALSE);
        }

        break;
    case 0x02:
        ShowCodeCharRL(8,8,"设置取消",FALSE);
        break;
    default:
        break;
    }

}


void pcom_complete(funpara* para)
{
    switch(para->fig){
    case 0x01:
        ShowCodeCharRL(para->row,para->col,para->str[para->fig-1],FALSE);
        break;
    case 0x02:
        ShowCodeCharRL(para->row,para->col,para->str[para->fig-1],FALSE);
        break;
    default:
        break;
    }

}
void p058_complete(funpara *para)
{
   (void)para;
    ShowXYCodeCharRL(2,0,1,"相关总线登记信息",FALSE);
}

void p041_complete(funpara* para)
{
    (void)para;
    ShowXYCodeCharRL(2,0,1,"主要有、、、",FALSE);
}
void p042_complete(funpara* para)
{
    (void)para;
    ShowXYCodeCharRL(4,0,1,"联动编程信息有：",FALSE);
}
void p047_complete(funpara* para)
{
    (void)para;
    ShowXYCodeCharRL(6,0,1,"相关版本信息：",FALSE);
}

void p048_complete(funpara* para)
{
    (void)para;
    //    ShowXYCodeCharRL(6,0,1,"组网控制器信息：",FALSE);
}
void p049_complete(funpara* para)
{
    (void)para;
    ShowXYCodeCharRL(6,0,1,"组网控制器信息：",FALSE);
}
void p039_complete(funpara *para)
{
    (void)para;
    ShowXYCodeCharRL(2,0,1,"模式为。。。",FALSE);
}
void p044_complete(funpara* para)
{
    (void)para;
    ShowXYCodeCharRL(2,0,1,"汉字注释信息有：",FALSE);
}

void p024_complete(funpara* para)
{
    (void)para;
}


void p027_complete(funpara* para)
{
    (void)para;
}
void p015_complete(funpara* para)
{
    (void)para;
    if(1==para->fig)
        ShowXYCodeCharRL(6,0,1,"已经恢复",FALSE);
    if(2==para->fig)
        ShowXYCodeCharRL(6,0,1,"取消恢复",FALSE);
}
void p028_complete(funpara* para)
{
    (void)para;
}
void p080_complete(funpara *para)
{
    (void)para;
    if(1==para->fig)
        ShowXYCodeCharRL(6,0,1,"回路登记已经清除",FALSE);
    if(2==para->fig)
        ShowXYCodeCharRL(6,0,1,"回路登记已经取消",FALSE);
}
void p077_complete(funpara *para)
{
    (void)para;
    if(1==para->fig)
        ShowXYCodeCharRL(6,0,1,"联动编程已经清除",FALSE);
    if(2==para->fig)
        ShowXYCodeCharRL(6,0,1,"联动编程已经取消",FALSE);
}
void p078_complete(funpara *para)
{
    (void)para;
    if(1==para->fig)
        ShowXYCodeCharRL(6,0,1,"注释已经清除",FALSE);
    if(2==para->fig)
        ShowXYCodeCharRL(6,0,1,"注释已经取消",FALSE);
}

void p081_complete(funpara *para)
{
    (void)para;
    if(1==para->fig)
        ShowXYCodeCharRL(6,0,1,"关联地址已经清除",FALSE);
    if(2==para->fig)
        ShowXYCodeCharRL(6,0,1,"关联地址已经取消",FALSE);
}
void p083_complete(funpara *para)
{
    (void)para;
    if(1==para->fig)
        ShowXYCodeCharRL(8,8,1,"1级密码已经设置",FALSE);
    if(2==para->fig)
        ShowXYCodeCharRL(8,8,1,"1级密码已经取消",FALSE);
}
void p084_complete(funpara *para)
{
    (void)para;
    if(1==para->fig)
        ShowXYCodeCharRL(8,8,1,"2级密码已经设置",FALSE);
    if(2==para->fig)
        ShowXYCodeCharRL(8,8,1,"2级密码已经取消",FALSE);
}
void p060_complete(funpara *para)
{
    (void)para;
    show_currentresult(para);//show_currentresult显示正常
}

void p061_complete(funpara *para)
{
    (void)para;

}
void p062_complete(funpara *para)
{
    (void)para;

}
void p063_complete(funpara *para)
{
    (void)para;

}

void p064_complete(funpara *para)
{
    (void)para;

}
void p065_complete(funpara *para)
{
    (void)para;

}

void p067_complete(funpara *para)
{
    (void)para;

}

void p072_complete(funpara *para)
{

}
void p073_complete(funpara *para)
{
    (void)para;

}
#define __sim_saveItem_C__
#include "sim_saveItem.h"
#include "saveMeStatus.h"
#include "savePowerOff.h"
#include "lcdSub_SwOneEvt.h"

extern U8 extbSucc;
#include "hwEx21_SST39vf800A.h"
#include "fls_Interface.h"

U8 flscon[1024];
#define WRITESIZE 400

#define FLASHBOTTONTESTflag 0 //ok
#define FLSPOWEROFflag 0// wrong
#define RD_POEWROFF_MANUAL_flag 0 //ok
#define WR_RD_POWEROFFVALUE_WITHHEAD_flag 0

#define WR_RD_HEAD_10NUMS_flag 0
#define WR_RD_HEADLOTS_10NUMS_flag 0
#define WR_RD_HEADLOTS_10NUMSCRC_flag 0
#define SYSSTATUS_flag 0

#define TESTCRC_flag 0


//#define

/*=========================================
call bottom call to test erase ,write and read=====
=========================================*/
#if 1//flash call bottom fun to test whether write
//底层调用感觉很正常，重启下试：
void flsWrTest(U8 chip,unsigned long adrWr)
{
    U32 nn;
//    unsigned long adrWr;
//    adrWr=0x10;
    for(nn=0;nn<1024;nn++){
        flscon[nn]=nn%255;
    }
//    NorFlash_EraseAdr_1Sector(0,adr,1);
    NorFlash_EraseAdr_1Block(chip,adrWr,1);//need wait,third para
    NorFlash_WriteNBytes(chip,adrWr,1024,&flscon[0]);
    ShowXYCodeCharRL(6,0,1,"写完成",FALSE);
}


void flsGetValueTmr(U8 chip,unsigned long adrRd)
{
    U8 tmpvalue;
    static U8 rowval=0;
    static unsigned long adr=0;
    static BOOL OnceFlag=TRUE;
    if(OnceFlag){
        adr=adrRd;
        OnceFlag=FALSE;
    }

    if(rowval>13)rowval=0;
    ClrWindow_Page();
    ShowXYCodeCharRL(2,0,1,"开始读",FALSE);
    if(adr>1024+0x10){
        //        adr=0x10;
        return;
    }

    NorFlash_ReadNBytes(chip,adr,1,&tmpvalue);
    ShowXY_Fig_Pre0(6,rowval,1,tmpvalue,4);
    adr+=1;
    rowval++;
    //    ShowXY_1Fig_if_inverse(6,0,1,tmpvalue,FALSE);

}
#endif//flash call bottom fun to test whether write


#if 1//test the poweroff storage
//wrote poweroff time to storage
void WriteT_PowerOffSS(void)
{
    TEvtClock_st pClock;
    static U8 USED=TRUE;
    if(USED){
        //先擦除再写入
        GetRamEvtTimer(&pClock);
        FlsWr_pwrOff_New(&pClock);//设置关机内容，相关标识，才能被大循环中存储任务识别保存
        USED=FALSE;
    }
}
//read poweroff time from storage
void ReadT_PowerOff_Tmr(void)
{
    TEvtClock_st pClockget;
    static U8 pos=0;
    ClrWindow_Page();
    ShowXYCodeCharRL(2,0,1,"读取关机时间",FALSE);

    //    if(bFlsWr_pwrOff_Finished()){

    //        FlsRd_PwrOff(&pClockget);
    //        Show_SysTime_YMDHMS(8,pos>8?pos%8:pos,&pClockget);
    //        pos++;
    //    }
    if(FlsRd_PwrOff(&pClockget)){
        Show_SysTime_YMDHMS(8,pos>8?1:pos,&pClockget);
    }else{
        ShowXYCodeCharRL(6,0,1,"正在读取",FALSE);
    }

    pos++;

}

#endif
//执行一次函数
BOOL ExecOnceFun(void (*fun)(void))
{
    static BOOL OnceFlag=TRUE;
    if(OnceFlag){
        fun();
        OnceFlag=FALSE;
        return TRUE;
    }
    return FALSE;
}


void EraseTwoChip(void)
{
    NorFlash_EraseChip(0,0);
    NorFlash_EraseChip(1,0);
}

#if 1
//向0x16000开始的处写数据，写1024个字节，先擦除，后写入
void WritePowerOffValueToFls(void)
{
    U32 nn;
    unsigned long adrWr;
    adrWr=0x16000;
    for(nn=0;nn<1024;nn++){
#if 1
        flscon[nn]=nn%255;
#else
        flscon[nn]=6;
#endif
    }
//    NorFlash_EraseAdr_1Sector(0,adrWr,1);
    NorFlash_EraseAdr_1Block(0,adrWr,1);
    NorFlash_WriteNBytes(0,adrWr,1024,&flscon[0]);
    ShowXYCodeCharRL(6,0,1,"写完成",FALSE);
}


void ReadPowerOffValueFromFlsTmr(void)
{
    U8 tmpvalue;
    static U8 rowval=0;
    static unsigned long adr=0x16000;

    if(rowval>13)rowval=0;
    ClrWindow_Page();
    ShowXYCodeCharRL(2,0,1,"开始读",FALSE);

    NorFlash_ReadNBytes(0,adr,1,&tmpvalue);
    ShowXY_Fig_Pre0(6,rowval,1,tmpvalue,4);
    adr+=1;
    rowval++;

}
void ReadPowerOffValuesFromFlsTmr(void)
{
    U8 tmpvalue[5];
    U8 nn;
    static U8 rowval=5;
    static unsigned long adr=0x16000;

    if(rowval>13)rowval=0;
    ClrWindow_Page();
    ShowXYCodeCharRL(2,0,1,"开始读",FALSE);

    NorFlash_ReadNBytes(0,adr,5,&tmpvalue[0]);
    for(nn=0;nn<5;nn++){
        ShowXY_Fig_Pre0(nn*2,rowval,1,tmpvalue[nn],4);
        adr+=1;//每次地址加1，循环5次
    }
//    ShowXY_Fig_Pre0(6,rowval,1,tmpvalue[],4);
//    adr+=1;
//    rowval++;

}

#endif
#include "strFlsItmStrCacu.h"
#if 1//为关机时间写入falsh添加头
//向存储部分添加头4个字节，但占用大小为
//向地址0x16000,处写4个字节，然后再写入1024个内容
void WritePowerOffValueWithHead(void)
{
    U32 nn;
    unsigned long adrWr;
    TFlsSecStart_un pRtnSecStart;
    adrWr=0x16000;

    NorFlash_EraseAdr_1Sector(0,adrWr,1);//擦除需要等待，添加成功了。
    Init_StrFlsSectStart(getFlsItem_PowerOff(),&pRtnSecStart);



    //添加头
    NorFlash_WriteNBytes(0,adrWr,sizeof(TFlsSecStart_un),(unsigned char *)&pRtnSecStart);
    adrWr+=sizeof(TFlsSecStart_un);


    for(nn=0;nn<1024;nn++){
#if 1
        flscon[nn]=nn%255;
#else
        flscon[nn]=6;
#endif
    }
//    NorFlash_EraseAdr_1Block(0,adrWr,0);
    NorFlash_WriteNBytes(0,adrWr,1024,&flscon[0]);
    ShowXYCodeCharRL(6,0,1,"写完成",FALSE);
}

void ReadPowerOffValuesFromFlsWithHeadTmr(void)
{
    U8 tmpvalue[5];
    U8 nn;
    static U8 rowval=5;
    static unsigned long adr=0x16000;

    if(rowval>13)rowval=0;
    ClrWindow_Page();
    ShowXYCodeCharRL(2,0,1,"开始读",FALSE);

    NorFlash_ReadNBytes(0,adr,5,&tmpvalue[0]);
    for(nn=0;nn<5;nn++){
        ShowXY_Fig_Pre0(nn*2,rowval,1,tmpvalue[nn],4);
        adr+=1;//每次地址加1，循环5次
    }
}

#endif


#if 0
//test ok
//存取关机时间正确了，但是结果
//自动存储关机时间的，此处触发一次自动存取
void AutoSavePowerOff()
{
    TEvtClock_st pClock;
    static U8 USED=TRUE;
    if(USED){
        //先擦除再写入
        GetRamEvtTimer(&pClock);
        FlsWr_pwrOff_New(&pClock);//设置关机
        USED=TRUE;
    }
}


void AutoSavePowerOffTmr()
{
    TEvtClock_st pClockget;
    static U8 pos=0;
    static U8 RowPos=0;
    static U8 nums=0;
    if(RowPos>10){
        ClrWindow_Page();
        RowPos=0;
        nums++;
    }
    ShowXYCodeCharRL(0,0,0,"读关机时间",FALSE);




    if(bFlsWr_pwrOff_Finished()){
        if(nums%2)
            FlsRd_PwrOffWithChip(&pClockget,0);
        else
            FlsRd_PwrOffWithChip(&pClockget,1);
        Show_SysTime_YMDHMS(RowPos,13,&pClockget);
        pos++;
    }else{
        ShowXYCodeCharRL(RowPos,0,RowPos,"正在读取",FALSE);
    }
    RowPos+=2;
//    if(FlsRd_PwrOff(&pClockget)){
//        Show_SysTime_YMDHMS(8,pos>8?1:pos,&pClockget);
//    }else{
//        ShowXYCodeCharRL(6,0,1,"正在读取",FALSE);
//    }

//    pos++;
}


#endif



#if 1
//test ok
//为关机时间写入falsh添加头
//向存储部分添加头10个字节，但占用大小为
//向地址0x16000,处写10个字节，然后再写入1024个内容
void WriteValueWithHead_NUM10(void)
{
    U32 nn;
    unsigned long adrWr;
    TFlsSecStart_un pRtnSecStart;
    U8 WrNums=0x10;
    adrWr=0x16000;

    NorFlash_EraseAdr_1Sector(0,adrWr,1);//擦除需要等待，添加成功了。
    Init_StrFlsSectStart(getFlsItem_PowerOff(),&pRtnSecStart);



    //添加头
    NorFlash_WriteNBytes(0,adrWr,WrNums,(unsigned char *)&pRtnSecStart);
    adrWr+=WrNums;


    for(nn=0;nn<20;nn++){
#if 1
        flscon[nn]=nn%255;
#else
        flscon[nn]=6;
#endif
    }
//    NorFlash_EraseAdr_1Block(0,adrWr,0);
    NorFlash_WriteNBytes(0,adrWr,20,&flscon[0]);
    ShowXYCodeCharRL(6,0,1,"写完成",FALSE);
}

void ReadValueHeadTmr_NUM10(void)
{
    U8 tmpvalue[5];
    U8 nn;
    static U8 rowval=5;
    static unsigned long adr=0x16000;

    if(rowval>13)rowval=0;
    ClrWindow_Page();
    ShowXYCodeCharRL(2,0,1,"开始读",FALSE);

    NorFlash_ReadNBytes(0,adr,5,&tmpvalue[0]);
    for(nn=0;nn<5;nn++){
        ShowXY_Fig_Pre0(nn*2,rowval,1,tmpvalue[nn],4);
        adr+=1;//每次地址加1，循环5次
    }
}

#endif



#if 1
//test ok
//为关机时间写入falsh添加多个头
//向地址0x16000,处写10个字节，写入多个内容，用来判断其队列最后值是否发生变化，然后再写入1024个内容
//如果endaddr发生变化，说明其肯定会判断值的变化，同时也对整个值的写入有作用
void WriteValueWithHeadLOTS_NUM10(void)
{
    U32 nn;
    unsigned long adrWr;
    TFlsSecStart_un pRtnSecStart;
    U8 WrNums=0x10;
    adrWr=0x16000;

    NorFlash_EraseAdr_1Sector(0,adrWr,1);//擦除需要等待，添加成功了。
    Init_StrFlsSectStart(getFlsItem_PowerOff(),&pRtnSecStart);
    //添加头
    NorFlash_WriteNBytes(0,adrWr,WrNums,(unsigned char *)&pRtnSecStart);
    adrWr+=WrNums;

    //give value
    for(nn=0;nn<1024;nn++){
#if 1
        flscon[nn]=8%255;
#else
        flscon[nn]=6;
#endif
    }



    //添加内容
    for(nn=0;nn<3;nn++){
#if 1//添加头
        NorFlash_WriteNBytes(0,adrWr,WrNums,(unsigned char *)&pRtnSecStart);
        adrWr+=WrNums;
#else//添加内容
//        NorFlash_EraseAdr_1Sector(0,adrWr,1);
        NorFlash_WriteNBytes(0,adrWr,WrNums,&flscon[0]);
        adrWr+=WrNums;
#endif
    }





    ShowXYCodeCharRL(6,0,1,"写完成",FALSE);
}

void ReadValueHeadTmrLOTS_NUM10(void)
{
    U8 tmpvalue[5];
    U8 nn;
    static U8 rowval=5;
    static unsigned long adr=0x16000;

    if(rowval>13)rowval=0;
    ClrWindow_Page();
    ShowXYCodeCharRL(2,0,1,"开始读",FALSE);

    NorFlash_ReadNBytes(0,adr,5,&tmpvalue[0]);
    for(nn=0;nn<5;nn++){
        ShowXY_Fig_Pre0(nn*2,rowval,1,tmpvalue[nn],4);
        adr+=1;//每次地址加1，循环5次
    }
}

//原来之前只写了4个字节，其余全部为空，没有写16个
//0 2 3 4  1 1 1 1 1 1 1 1 1 1 1 1
void WriteValueWithHeadLOTS_NUM10_Addr(U8 chip,unsigned long adrWrOrg)
{
    U32 nn;
    TFlsSecStart_un pRtnSecStart;
    U8 WrNums=0x10;
    U8 HeadSize=U_FLS_SectorStart_BYTES;//0x04;

    unsigned long adrWr=adrWrOrg;

    NorFlash_EraseAdr_1Sector(chip,adrWr,1);//擦除需要等待，添加成功了。
    Init_StrFlsSectStart(getFlsItem_PowerOff(),&pRtnSecStart);
    //添加头
    NorFlash_WriteNBytes(chip,adrWr,HeadSize,(unsigned char *)&pRtnSecStart);
    adrWr+=WrNums;

    //give value
    for(nn=0;nn<1024;nn++){
#if 1
        flscon[nn]=8%255;
#else
        flscon[nn]=6;
#endif
    }



    //添加内容
    for(nn=0;nn<3;nn++){
#if 1//添加头
        NorFlash_WriteNBytes(chip,adrWr,WrNums,(unsigned char *)&flscon[0]);
        adrWr+=WrNums;
#else//添加内容
//        NorFlash_EraseAdr_1Sector(0,adrWr,1);
        NorFlash_WriteNBytes(chip,adrWr,WrNums,&flscon[0]);
        adrWr+=WrNums;
#endif
    }
    ShowXYCodeCharRL(6,0,1,"写完成",FALSE);
}

#endif




#define __flsWrite_C__
#include "flsWrite.h"

#if 0
//未成功校验成功，咋回事，不能写进去幽幽幽幽幽幽幽幽幽幽幽幽幽幽幽幽xx
//* FUNC: // 1条的校验正确, crc;
//BOOL bFlsQueRd_OneItem_isOK(U8 chip, U32 mAdr, U8 mFlsItem)

//写入带校验的数据CRC
//向地址0x16000,处写10个字节，写入多个内容，用来判断其队列最后值是否发生变化，然后再写入1024个内容
//如果endaddr发生变化，说明其肯定会判断值的变化，同时也对整个值的写入有作用
void WriteValueWithHeadLOTS_NUM10CRC(void)
{
    U32 nn;
    unsigned long adrWr;
    TFlsSecStart_un pRtnSecStart;
    TEvtClock_st pStClock;
    TSavePowerOff_st  stPwr;

    U8 WrNums=0x10;
    adrWr=0x16000;

    NorFlash_EraseAdr_1Sector(0,adrWr,1);//擦除需要等待，添加成功了。



    GetRamEvtTimer(&pStClock);
    stPwr.mFlsItem = getFlsItem_PowerOff();
    stPwr.mPart = U_FlsSave_Part0;
    if(!getFlsItem_Addr(stPwr.mFlsItem, stPwr.mPart, &stPwr.stAdr))
    {
        return;
    }


    ClrRamIsFF(&stPwr.unNewClock.byte[0], U_FLS_1PowerOff_BYTE_MAX); //全清FF

    stPwr.unNewClock.stPwrOff.stClock = pStClock;//put time to the value
    //数据检验值
    stPwr.unNewClock.byte[U_FLS_1PowerOff_BYTE_MAX-1] =
            (U8)(CacuCrcValue(&stPwr.unNewClock.byte[0],
                              (U_FLS_1PowerOff_BYTE_MAX-1)));





    Init_StrFlsSectStart(getFlsItem_PowerOff(),&pRtnSecStart);
    //添加头
    NorFlash_WriteNBytes(0,adrWr,WrNums,(unsigned char *)&pRtnSecStart);
    adrWr+=WrNums;


//    adrWr=0x17000;
//    NorFlash_EraseAdr_1Sector(0,adrWr,1);//擦除需要等待，添加成功了。
//    NorFlash_WriteNBytes(0,adrWr,WrNums,(unsigned char *)&pRtnSecStart);


//    adrWr=0x18000;
//    NorFlash_EraseAdr_1Sector(0,adrWr,1);//擦除需要等待，添加成功了。
//    NorFlash_WriteNBytes(0,adrWr,WrNums,(unsigned char *)&pRtnSecStart);


#if 0
    //添加内容带校验值
    for(nn=0;nn<1;nn++){
#if 0//添加头
        NorFlash_WriteNBytes(0,adrWr,WrNums,(unsigned char *)&pRtnSecStart);
        adrWr+=WrNums;
#else//添加内容

        NorFlash_EraseAdr_1Sector(0,adrWr,1);

        FlsHd_Write_nByte(
            0, &stPwr.unNewClock.byte[0], 0x16, adrWr,
            U_SYS_FLASH_OPEA_WAIT
            );
//        flsWr_SetIdle();



//        NorFlash_EraseAdr_1Sector(0,adrWr,1);
//        NorFlash_WriteNBytes(0,adrWr,WrNums,&flscon[0]);
        adrWr+=WrNums;
#endif
    }

    #endif

    //        FlsWr_Write_nByte_meIsEnd(stPwr.stAdr.chip,
    //                                  &stPwr.unNewClock.byte[0],
    //                                  U_FLS_1PowerOff_BYTE_MAX,
    //                                  mAdrEnd
    //                                  );


    //        pByteFrom = &stSectHead.byte[0];

    //        FlsWr_Write_nByte_meIsEnd(0,
    //                                  &stPwr.unNewClock.byte[0],
    //                                  WrNums,
    //                                  adrWr
    //                                  );

    //        stWr.chip = chip;
    //        stWr.address = address;
    //        stWr.num = num;
    //        stWr.pByteFrom = pStart;
    //        stWr.adrInSect = FlsHd_adrInSector(chip, address);


    //        stWr.bHaveEnd = TRUE;


    //        stWr.step = U_FlashWriteStep_Start;
    //        FlsWr_Exec();



    //        FlsHd_Read_nByte(chip, &vWrBuf[0],
    //                WrNums, adrWr);
    //        if(bAllRamIsFF(&vWrBuf[0], stWr.num))
    //        {
    //            stWr.step = U_FlashWriteStep_Write;
    //        }
    //        else
    //        {
    //            stWr.step = U_FlashWriteStep_Erase;
    //        }



    //        flsWr_step_Start();
    //        //直接进行next:
    //        if(stWr.step == U_FlashWriteStep_Write)
    //        {
    //            flsWr_step_Write();
    //        }
    //        else if(stWr.step == U_FlashWriteStep_Erase)
    //        {
    //            flsWr_step_Erase();
    //        }


    ShowXYCodeCharRL(6,0,1,"写完成",FALSE);
}

void ReadValueHeadTmrLOTS_NUM10CRC(void)
{
    U8 tmpvalue[16];
    U8 nn;
    BOOL CRCRES;
    static U8 rowval=5;
    static unsigned long adr=0x16000;

    if(rowval>13)rowval=0;
    ClrWindow_Page();
    ShowXYCodeCharRL(2,0,1,"开始读",FALSE);

    for(nn=0;nn<4;nn++){

        NorFlash_ReadNBytes(0,adr,0x10,&tmpvalue[0]);

        CRCRES = bFlsQueRd_OneItem_isOK(0,adr,getFlsItem_PowerOff());
        if(CRCRES){
            ShowXY_Fig_Pre0(nn*2,rowval,1,1,1);
        }else{
            ShowXY_Fig_Pre0(nn*2,rowval,1,0,1);
        }
        adr+=0x10;//每次地址加1，循环5次
    }

    //看校验值对不对？

}

#endif

#if 0
//未完成，未成功
//设置与获取本机信息
#include "saveTmrPwroffAndHist.h"
#include "flashIdAssign.h"
#include "saveItemAux.h"

void SetMeStatusTest(void)
{
    //    U8* passwd1=(U8*)"000";
    U8 passwd1[3];
    U8 iy;
    for(iy=0;iy<sizeof(passwd1);iy++){
        passwd1[iy]=8;
    }

//    FlsSetMeStatus_pssw1(&passwd1[0],12,3);
    FlsSetMeStatus_runAuto(52,10,2);
//    FlsSetMeStatus_machAdr(36,11,2);

}
void MeStatusTest(void)
{
    TFlsSysSet_un *pSysSet;



    if(FlsRd_MeStatus())
    {
        ShowXYCodeCharRL(2,0,1,"读取正常",FALSE);
        pSysSet = pGetFlsSysSet();
        ShowXY_Fig_Pre0(4,0,1,pSysSet->stSet.pssw1[0],3);
        ShowXY_Fig_Pre0(6,0,1,pSysSet->stSet.runAuto,3);
        //        ShowXY_Fig_Pre0(6,0,1,pSysSet->stSet.pssw2[0],3);
        //        ShowXY_Fig_Pre0(8,0,1,pSysSet->stSet.language,3);
        ShowXY_Fig_Pre0(8,0,1,pSysSet->stSet.machAdr,3);


    }else{
        ShowXYCodeCharRL(2,0,1,"读取错误",FALSE);
    }
}

#endif


#if 0
//test ok
void RD_Time(void)
{
    TEvtClock_st stClock;
    TFlsQueuePoint_st stHeadEnd;
    TFlsItemAddr stAdr;
    U32 adr_sectorHead;
    U32 adr;
    U8 mPart;
    TFlsPwrOff_un  *pPwrOff;
    U8 *pBufS;
    U8 mFlsItem = getFlsItem_PowerOff();//U_FlsSave_PowerOff 0x13  19

    for(mPart=0; mPart<FlsItem_PartMax(mFlsItem); mPart++)
    {
        if(!getFlsItem_Addr(mFlsItem, mPart, &stAdr))//stAdr为芯片的地址
        {
            ShowXYCodeCharRL(4,2,1,"地址不符",FALSE);
            continue;
        }
        if(!bFlsItem_IsReadAllow(mFlsItem, mPart))
        {
            ShowXYCodeCharRL(4,2,1,"不允许读",FALSE);
            continue;
        }

        GetFlsQueHeadEndAdr(mFlsItem, mPart, &stHeadEnd);
//        if(stHeadEnd.headAdr == stHeadEnd.endAdr)
//        {
//            ShowXYCodeCharRL(4,2,1,"头尾相等",FALSE);
//            ShowXY_Fig_Pre0(6,3,1,stHeadEnd.headAdr,2);

//            continue;
//        }
        adr = stHeadEnd.endAdr;
        adr = FlsItm_adr_itemBefore(adr, mFlsItem,
                                    U_FLS_1PowerOff_BYTE_MAX, &stAdr
                                    );
        adr_sectorHead = hist_sector_start(adr);
        adr=0x16020;
        if(adr == adr_sectorHead)
        {
            if(adr == stHeadEnd.headAdr)
            {
                continue;
            }
            adr = FlsItm_adr_itemBefore(adr, mFlsItem,
                                        U_FLS_1PowerOff_BYTE_MAX, &stAdr
                                        );
        }
        pBufS = pFlsHd_GetBufS();
        FlsHd_Read_nByte(stAdr.chip, pBufS,
                         U_FLS_1PowerOff_BYTE_MAX, adr);
        if(!JdgCrcOK(pBufS, U_FLS_1PowerOff_BYTE_MAX))
        {
            ShowXYCodeCharRL(4,2,1,"检验错误",FALSE);
            continue;
        }

        pPwrOff = (TFlsPwrOff_un*)(pBufS);
        stClock = pPwrOff->stPwrOff.stClock;
        //    FlsRd_PwrOff(&pClockget);
        Show_SysTime_YMDHMS(8,1,&stClock);
    }


}
void RD_Time_withAddr(U8 chip,U32 readAdr)
{
    static U8 ROWPOS=0;

    TEvtClock_st stClock;
    TFlsPwrOff_un  *pPwrOff;
    U8 *pBufS;
    ROWPOS=ROWPOS>8?0:ROWPOS;
    pBufS = pFlsHd_GetBufS();
    FlsHd_Read_nByte(chip, pBufS,
                     U_FLS_1PowerOff_BYTE_MAX, readAdr);
    if(!JdgCrcOK(pBufS, U_FLS_1PowerOff_BYTE_MAX))
    {
        ShowXYCodeCharRL(ROWPOS,0,1,"CRC ERR",FALSE);
    }else{
        ShowXYCodeCharRL(ROWPOS,0,1,"CRC OK",FALSE);
    }
    ShowXY_Fig_Pre0(ROWPOS,0,10,chip,1);

    pPwrOff = (TFlsPwrOff_un*)(pBufS);
    stClock = pPwrOff->stPwrOff.stClock;
    Show_SysTime_YMDHMS(ROWPOS,12,&stClock);
    ROWPOS+=2;


}
#endif




#if 0
//test ok
//系统配置存储
void MeStatusSave()
{

//    extern BOOL FlsSysSetMeStatus_Save(U8 taskId, U8 flsId);

//    // 读flash内容
//    extern BOOL FlsRd_MeStatus(void);

    U8 RunAutomSet=1;
    U8 taskId=12;
    U8 flsId=0;
    U8 passwd1[U_PSSW1_BYTE_MAX];
    U8 passwd2[U_PSSW2_BYTE_MAX];
    U8 ii;
    for(ii=0; ii<U_PSSW1_BYTE_MAX; ii++)
    {
        passwd1[ii] = (ii+2)%10;
    }
    for(ii=0; ii<U_PSSW2_BYTE_MAX; ii++)
    {
        passwd2[ii] = (ii+5)%10;
    }

    FlsSetMeStatus_runAuto(RunAutomSet,taskId,flsId);
    FlsSetMeStatus_runManu(RunAutomSet, taskId, flsId);
    FlsSetMeStatus_machAdr(10, taskId, flsId);
    FlsSetMeStatus_machMasterOrSlave(U_MACHINE_MASTER, taskId, flsId);
    FlsSetMeStatus_language(3, taskId, flsId);
    FlsSetMeStatus_pssw1(passwd1, taskId, flsId);
    FlsSetMeStatus_pssw2(passwd2, taskId, flsId);
    ShowXYCodeCharRL(8,0,0,"系统配置存储成功",FALSE);
}


void RDMeStatusTmr()
{

    TFlsSysSet_un *pSysSet;
    U8 ii;

    ClrWindow_Page();
    ShowXYCodeCharRL(0,0,0,"读系统配置",FALSE);



    if(FlsRd_MeStatus())
    {
        ShowXYCodeCharRL(0,5,1,"读取正常",FALSE);
        pSysSet = pGetFlsSysSet();
        for(ii=0; ii<U_PSSW1_BYTE_MAX; ii++)
        {
            ShowXY_Fig_Pre0(2,1,ii,pSysSet->stSet.pssw1[ii],1);
        }

        ShowXY_Fig_Pre0(4,0,1,pSysSet->stSet.runAuto,3);
        for(ii=0; ii<U_PSSW2_BYTE_MAX; ii++)
        {
            ShowXY_Fig_Pre0(6,1,ii,pSysSet->stSet.pssw2[ii],1);
        }

//        ShowXY_Fig_Pre0(8,0,1,pSysSet->stSet.language,3);
//        ShowXY_Fig_Pre0(8,0,1,pSysSet->stSet.machAdr,3);
        ShowXY_Fig_Pre0(8,0,1,pSysSet->stSet.machMasterOrSlave,3);


    }else{
        ShowXYCodeCharRL(0,5,1,"读取错误",FALSE);
    }

}
#endif


enum{
    NORFLASH0=0,
    NORFLASH1=2
};
#if 0
//test ok
void RD_Time_TwoChip()
{
/*
读取norflan 0和1片关机时间的地址处的内容是否是正确的。
分屏显示
*/
    U8 chip;
    static U8 order=0;
    ClrWindow_Page();
    //chip 0
    if(0==order%2){
        chip=NORFLASH0;
        RD_Time_withAddr(chip,0x16000);
        RD_Time_withAddr(chip,0x16010);
        RD_Time_withAddr(chip,0x16020);
        RD_Time_withAddr(chip,0x16030);
        RD_Time_withAddr(chip,0x16040);
    }else{
        //chip 1
        chip=NORFLASH1;
        RD_Time_withAddr(chip,0x16000);
        RD_Time_withAddr(chip,0x16010);
        RD_Time_withAddr(chip,0x16020);
        RD_Time_withAddr(chip,0x16030);
        RD_Time_withAddr(chip,0x16040);
    }
    order++;


}
#endif

#if 1
//test ok
#include "saveField.h"
U8 pRegistByte[24];
TFlsFieldHead_st pHead;
void pHeadSet()
{
    pHead.mLoop=2;
    pHead.mAddrS=110;
    pHead.mAddrE=116;
}

void FlsSave_FieldTest(void)
{
    U8 taskId=13;
    U8 flsId=1;
    U8 ii;
    pHeadSet();
    for(ii=0;ii<sizeof(pRegistByte);ii++)
        pRegistByte[ii]=(ii+5)%10;



    FlsSave_Field(&pHead, pRegistByte,
                            taskId,  flsId);

}
void FlsSave_FieldTestTmr(void)
{
//    TFlsFieldHead_st pHead;
    U8 ii;

    ClrWindow_Page();
    //需要提供pHead属性内容
    pHeadSet();


    ShowXYCodeCharRL(0,0,0,"读系区域配置",FALSE);

    if(FlsRd_Field(&pHead,pRegistByte)){
        ShowXYCodeCharRL(0,5,1,"读取正常",FALSE);
        ShowXY_Fig_Pre0(2,0,1,pHead.mLoop,1);
        ShowXY_Fig_Pre0(2,0,3,pHead.mAddrS,4);
        ShowXY_Fig_Pre0(2,5,1,pHead.mAddrE,4);

        for(ii=0; ii<sizeof(pRegistByte); ii++)
        {
            ShowXY_Fig_Pre0(4,0,ii,pRegistByte[ii],1);
        }


    }else{
        ShowXYCodeCharRL(0,5,1,"读取err",FALSE);
    }



}

#endif


#if 1
//Note 存储目前需要查找相应的地址。？？？？？？？？？？？、、、
#include "saveNote.h"
#include "sysPanel.h"

TDev_un pDev;
void DevSet()
{

#if 1
    pDev.stDete.machine=U_MACHINE_SELF;
    pDev.stDete.pnType = GetPanelType_Extg();
    pDev.stDete.pnSequ=3;

//    pDev.pnModu.pnType= GetPanelType_Extg();
//    pDev.pnModu.pnSequ= 2;


#else
    pDev.pnModu.pnType=1;
    pDev.pnModu.machine=U_MACHINE_SELF;
    pDev.pnModu.pnSequ=2;
    pDev.pnModu.modu=1;
#endif
}

void FlsRd_NoteTest()
{
    U8 taskId=13;
    U8 flsId=1;
//    U8 ii;
//    ExecOnceFun();
//    U8 *pNoteByte="你好吗？111楼";


#if 0
    U8 iy;
    U8 pNoteCon[U_FLS_NOTE_BYTE_MAX];
    for(iy=0;iy<sizeof(pNoteCon);iy++){
        pNoteCon[iy]=8;
    }
#else
    U8 *pNoteCon="你好吗？111楼111111111111111111111111111111111111111111111";
#endif
    DevSet();
    FlsSave_Note(&pDev, pNoteCon,
                            taskId, flsId);

}

void FlsRd_NoteTmrTest()
{
    U8 pRtnNote[32];
    U8 iy;
    //		U8* pRtnNote;
    DevSet();

    if(FlsRd_Note(&pDev, pRtnNote)){
        ShowXYCodeCharRL(0,5,1,"读取ok",FALSE);
//        ShowXYCodeCharRL(8,5,1,pRtnNote,FALSE);
        for(iy=0;iy<sizeof(pRtnNote)/2;iy++){
//            pNoteCon[iy]=8;
            ShowXY_Fig_Pre0(4,iy,1,pRtnNote[iy],1);
        }
//        ShowXY_Fig_Pre0(4,iy,1,pRtnNote,1);
        ShowXYCodeCharRL(8,0,1,pRtnNote,FALSE);



    }else{
        ShowXYCodeCharRL(0,5,1,"读取err",FALSE);
    }

}
#endif


#if 1
//test ok
//气体灭火区域的存储
#include "saveExtgZoneConfig.h"
#include "codeComm.h"

U8 mExtgZone;
void ExtZoneCom(void)
{
  mExtgZone=2;
}

void ExtZoneSave_Test(void)
{
    U8 taskId=13;
    U8 flsId=1;
    U8 ii;
    U8 pConfigByte[16];
    for(ii=0;ii<16;ii++){
        pConfigByte[ii]=ii%10;
    }
//    U8 *pConfigByte="test1111111111111111";
    ExtZoneCom();

//    U_FLS_ExtgZoneConfig_One_BYTE_MAX
    
    FlsSave_ExtgZoneConfig(mExtgZone,pConfigByte,taskId,flsId);
}


void ExtZoneSave_TestTmr(void)
{
    U8 buf[16];
    U8 ii;
//    ClrRamIsFF(buf,16);
    ClrRamIs00((U8 *)buf,16);

    ExtZoneCom();
    if(FlsRd_ExtgZoneConfig(mExtgZone,buf)){

        ShowXYCodeCharRL(0,5,1,"读取ok",FALSE);
        ShowXYCodeCharRL(2,0,1,buf,FALSE);

        for(ii=0;ii<sizeof(buf);ii++){
//            ShowXYCodeCharRL(8,0,ii,buf[ii],FALSE);
            ShowXY_Fig_Pre0(8,1,ii,buf[ii],1);
        }
    }else{
        ShowXYCodeCharRL(0,5,1,"读取err",FALSE);
    }

}



#endif






#if 1
#include "Save_Hist_incOut.h"
#include "evt_Class.h"

void Histroy_test(void)
{
#if 0
    TEvtTrans_st pEvtTrans;
    GetClock(&pEvtTrans.evtClock);
    pEvtTrans.type=2;
    pEvtTrans.thiFurther=1;
    pEvtTrans.thing=3;
    pEvtTrans.unDev.pnModu.machine=U_MACHINE_SELF;
    pEvtTrans.unDev.pnModu.pnType=GetPanelType_Extg();

    HistNewEvent(&pEvtTrans);

#else
    TEvtTrans_st  stEvt;//用来记录事件的

    DevSetInvalid(&stEvt.unDev);
    stEvt.thing = GetEvtThingDef_PwrOff();
    HistNewEvent(&stEvt);

#endif


}
//test ok
//测试所有的存储内容

void Histroy_testAllTmr(void)
{

    static U8 Num=0;
    static U8 thingsFirst=0;
    TEvtTrans_st  stEvt;//用来记录事件的

    DevSetInvalid(&stEvt.unDev);
    stEvt.thing = thingsFirst;
    HistNewEvent(&stEvt);


    Num=Num>6?0:Num;
    ClrWindow_Page();
    ShowXY_Fig_Pre0(2,4,6,stEvt.thing,3);
    if(1){
        ShowXY_Fig_Pre0(0,4,1,Num,2);
        ShowXY_Fig_Pre0(0,4,6,Num+1,2);
        ShowXY_Fig_Pre0(2,0,1,HistRd_CacuItem_HistCls(Num,0),3);
        ShowXY_Fig_Pre0(4,0,1,HistRd_CacuItem_HistCls(Num,1),3);
        ShowXY_Fig_Pre0(6,0,1,HistRd_CacuItem_HistCls(Num+1,0),3);
        ShowXY_Fig_Pre0(8,0,1,HistRd_CacuItem_HistCls(Num+1,1),3);
    }
    Num+=1;
    thingsFirst++;

}


void Histroy_testTmr(void)
{
    
    static U8 Num=0;
    Num=Num>20?0:Num;
    ClrWindow_Page();
    if(1){
        ShowXY_Fig_Pre0(0,4,1,Num,2);
        ShowXY_Fig_Pre0(0,4,6,Num+1,2);
        ShowXY_Fig_Pre0(2,0,1,HistRd_CacuItem_HistCls(Num,0),3);
        ShowXY_Fig_Pre0(4,0,1,HistRd_CacuItem_HistCls(Num,1),3);
        ShowXY_Fig_Pre0(6,0,1,HistRd_CacuItem_HistCls(Num+1,0),3);
        ShowXY_Fig_Pre0(8,0,1,HistRd_CacuItem_HistCls(Num+1,1),3);
    }
    Num+=2;
//    if(Num%10)
//        PwrOff_toHist();

////    HistRd_CacuItemNum(0,0,)




}
#endif

#include "saveDisable.h"


void simSave_Disable(void)
{
    TDev_un stDev;
    BOOL bSucc;
    U8 *pBufS;
    U8 *pBufNow;
    U32 ii;
    TFlsDisable_un stDisable;

    pBufS = pFlsHd_GetBufS();

    bSucc = BuildToDev_DeteMLA(1, 2, 3, &stDev);
    ShowXY_Fig_Pre0(0,0,1,bSucc,2);
    bSucc = bDevOk(&stDev);
    ShowXY_Fig_Pre0(2,0,1,bSucc,2);

    pBufNow = pBufS;
    for(ii=0; ii<0x100; ii++)
    {
        *pBufNow = ~0;
        pBufNow++;
        if(ii == (0x100-1))
        {
            ii = ii;
        }
    }
    stDisable.stDisable.bAdd = TRUE;
    stDisable.stDisable.stDev = stDev;
    bSucc = FlsDisable_RamChange(pBufS, &stDisable); // TRUE;
    ShowXY_Fig_Pre0(4,0,1,bSucc,2);

    bSucc = BuildToDev_DeteMLA(1, 2, 4, &stDev);
    ShowXY_Fig_Pre0(6,0,1,bSucc,2);
    stDisable.stDisable.stDev = stDev;
    bSucc = FlsDisable_RamChange(pBufS, &stDisable); // TRUE;

    ShowXY_Fig_Pre0(8,0,1,bSucc,2);
    bSucc = bSucc;
}

//存了2条，第2次存的偏移量是 0x20 .



//系统掉电 test ok
void powerDown()
{
    LPC_SC->PCONP = 0x00; // 关闭定时器、RTC、UART等功能部件
    LPC_SC->PCON=0x02; // 系统进入掉电模式
}





typedef void (*VOIDFUN)(funpara* para);
void LoopNTimes(U8 times,VOIDFUN fun,funpara *para)
{
    U8 ii;
    for(ii=0;ii<times;ii++){
      fun(para);
      ShowXY_Fig_Pre0(ii*2,14+ii,1,ii,1);
    }
}



#define DISABLE_f 1
#if 1
//待测试，need to test
#include "saveDisable.h"
TDev_un pDev;
void DisableCommon()
{
//    pDev.stDete.boardLoop=2;
//    pDev.stDete.channel=1;
//    pDev.stDete.machine=U_DEV_ITEM_pnType;
//    pDev.stDete.pnSequ=2;
//    pDev.stDete.eventSubject=1;
//    pDev.stDete.pnType=1;
}

void EraseFromAddrForDisable(void)
{
    TFlsItemAddr stAdr;
    U8 part=0;
    U8 chip=0;
    U8 mFlsItem=getFlsItem_Disable();
    if(!getFlsItem_Addr(mFlsItem, part, &stAdr))
    {
        return;
    }
    FlsHd_EraseSect_FromAdr(chip, stAdr.adrS,
                               U_SYS_FLASH_OPEA_WAIT);
    chip=2;
    FlsHd_EraseSect_FromAdr(chip, stAdr.adrS,
                               U_SYS_FLASH_OPEA_WAIT);

}
//是否擦除
#define ERASEDISABLE

#define FALSEflag 01

void Disable_org(funpara *para)
{
    BOOL bSucc;
    U8 taskId=13;
    U8 flsId=1;

    //machine num should start from 1
    static U8 Machinenum=10;


#if FALSEflag
    //调用disable好像没有执行删除功能
    BOOL bDisable=FALSE;
#else
    
    BOOL bDisable=TRUE;

#ifdef ERASEDISABLE
    if(ExecOnceFun(EraseFromAddrForDisable))
        return;
#endif
#endif

//        EraseTwoChip();
//    if(para->TotalCall->Used)
//        Machinenum=Machinenum>5?0:Machinenum;
//    DisableCommon();
    
    bSucc = BuildToDev_DeteMLA(Machinenum, 2, 3, &pDev);
    bSucc = bDevOk(&pDev);

    if(FlsAdd_Disable(&pDev, bDisable, taskId,flsId)){
        ShowXYCodeCharRL(0,5,1,"存储ok",FALSE);
    }else{
        ShowXYCodeCharRL(0,5,1,"存储err",FALSE);
    }
    Machinenum++;
}
void Disable_testtmr_org(funpara *para)
{
    BOOL bRtnDevValid=FALSE;
    TFlsDisable_un pRtnDsabOne;
    static U8 Sequ=0;

    if(para->TotalCall->Used&&!para->TotalCall->ExecOnceNum){
        para->TotalCall->ExecOnceNum++;
        Sequ=0;
    }
    Sequ=Sequ>21?0:Sequ;

    ClrWindow_Page();
//    DisableCommon();

    if(FlsRd_DisableInBuf(Sequ, &bRtnDevValid,&pRtnDsabOne)){
        ShowXYCodeCharRL(0,5,1,"read ok",FALSE);
        ShowXY_Fig_Pre0(4,0,1,bRtnDevValid,2);
        ShowXY_Fig_Pre0(2,0,1,Sequ,2);
    }else{
        ShowXYCodeCharRL(0,5,1,"read err",FALSE);
    }
    Sequ++;

}
void Disable_test(funpara *para)
{
#if FALSEflag
    LoopNTimes(1,Disable_org,para);
#else
    LoopNTimes(22,Disable_org,para);
#endif
//    LoopNTimes(1,simSave_Disable);
}

void Disable_testtmr(funpara *para)
{

    LoopNTimes(1,Disable_testtmr_org,para);
//    LoopNTimes(1,Disable_org);

}
#endif


//#define DISABLE_f 1
#if 1//待测试，need to test
#include "saveDisable.h"
TDev_un pDev;
void Login_common()
{

    pDev.pnModu.machine=U_MACHINE_SELF;
    pDev.pnModu.pnType=GetPanelType_Loop();
    pDev.pnModu.modu=1;
    pDev.pnModu.pnSequ=2;
    pDev.pnModu.eventSubject=U_EVT_SUBJECT_FIELD;
}


void Login_test()
{
    U8 taskId=13;
    U8 flsId=1;
    Login_common();

    if(FlsAdd_Disable(&pDev, TRUE, taskId,flsId)){
        ShowXYCodeCharRL(0,5,1,"存储ok",FALSE);
    }else{
        ShowXYCodeCharRL(0,5,1,"存储err",FALSE);
    }


}
void Login_testtmr()
{
    BOOL bRtnDevValid;
    TFlsDisable_un pRtnDsabOne;

    ClrWindow_Page();
    Login_common();

    if(FlsRd_DisableInBuf(1, &bRtnDevValid,&pRtnDsabOne)){
        ShowXYCodeCharRL(0,5,1,"read ok",FALSE);
        ShowXYCodeCharRL(2,0,1,pRtnDsabOne.byte,FALSE);
        ShowXY_Fig_Pre0(4,0,1,pRtnDsabOne.stDisable.stDev.pnModu.pnType,2);
        ShowXY_Fig_Pre0(6,0,1,pRtnDsabOne.stDisable.stDev.pnModu.machine,2);
        ShowXY_Fig_Pre0(8,0,1,pRtnDsabOne.stDisable.stDev.pnModu.eventSubject,2);
    }else{
        ShowXYCodeCharRL(0,5,1,"read err",FALSE);
    }

}
#endif

//多线盘配置,test err
#define PnConfig_flag 1
#if 1
#include "Save_Item_incOut.h"

void PnConfig_common()
{

}


void PnConfig_test()
{
    U8 taskId=13;
    U8 flsId=1;
    U8 pnType=U_PN_Extg_TYPE;
    U8 mSequS=2;
    U8 mSequE=20;
    PnConfig_common();
    if(FlsSave_PnConfig_Add(pnType,mSequS,mSequE,taskId,flsId)){
        ShowXYCodeCharRL(0,5,1,"存储ok",FALSE);
    }else{
        ShowXYCodeCharRL(0,5,1,"存储err",FALSE);
    }


}
void PnConfig_testtmr()
{
    static U8 ii=0;
    static U8 netnum=0;
    if(0==ii||10==ii)ClrWindow_Page();
    netnum=netnum>U_PANEL_TOTAL_SEQU_MAX?0:netnum;
    PnConfig_common();
    ShowXY_Fig_Pre0(0,8,4,netnum,3);

    if(FlsRd_PnConfig()){
        ShowXYCodeCharRL(0,5,1,"read ok",FALSE);
        ii=ii>8?0:ii;

        ShowXY_Fig_Pre0(ii,3,1,bExtgUnit_Regist(netnum),1);
        ii+=2;

    }else{
        ShowXYCodeCharRL(0,5,1,"read err",FALSE);
    }
    netnum++;

}
#endif



#if 1
//网络机器的存储,test ok
#define NETMACHINE_TEST_flag 0

#include "saveNetMachine.h"
#include "sysMachine.h"
#include "codeComm.h"

U8 NetMachine;
void NetMachineCom(void)
{
  NetMachine=2;
}

void NetMachineSave_Test(void)
{
    U8 taskId=13;
    U8 flsId=1;
    U8 mMachS=1;
    U8 mMachE=30;

    NetMachineCom();


    FlsSave_NetMachine_Add(mMachS,mMachE,taskId,flsId);
    FlsSave_NetMachine_Delete(3,6,taskId,flsId);
}


void NetMachineSave_TestTmr(void)
{
    static U8 ii=0;
    static U8 netnum=0;
    if(0==ii||10==ii)ClrWindow_Page();
    netnum=netnum>0x30?0:netnum;
    NetMachineCom();
    ShowXY_Fig_Pre0(0,8,4,netnum,2);
    if(FlsRd_NetMachine()){
        ShowXYCodeCharRL(0,5,1,"读取ok",FALSE);
            ii=ii>8?0:ii;

            ShowXY_Fig_Pre0(ii,3,1,GetMachine_Regist(netnum),1);
            ii+=2;
    }else{
        ShowXYCodeCharRL(0,5,1,"读取err",FALSE);
    }
    netnum++;

}

#endif






//关机时间
#define AUTOSAVEPOWEROFF_flag    0
//系统配置
#define MESTATUS_flag 0

#define FIELDTEST_flag 1
#define NOTE_flag 0
#define EXTZONE_flag 0
#define HISTORY_flag 0
#define HISTORYALL_flag 0
#define RD_ADDR_TIME_flag 0

#define RD_FLASH0 0

#define HEAD_TEST_flag 1




#include "historyWrite.h"

//帮助界面
void p011_complete(funpara *para)
{
#if DISABLE_f
    Disable_test(para);
#elif FLASHBOTTONTESTflag
    #if RD_FLASH0
        flsWrTest(0,0x10);
    #else
        flsWrTest(2,0x10);//第二片norflash在硬件上的内容为2，
    #endif
#elif FLSPOWEROFflag
    WriteT_PowerOffSS();
#elif RD_POEWROFF_MANUAL_flag
    WritePowerOffValueToFls();
#elif WR_RD_POWEROFFVALUE_WITHHEAD_flag
    WritePowerOffValueWithHead();
#elif AUTOSAVEPOWEROFF_flag
//    ExecOnceFun(EraseTwoChip);



    AutoSavePowerOff();
#elif MESTATUS_flag
    MeStatusSave();
#elif FIELDTEST_flag
    FlsSave_FieldTest();
#elif NOTE_flag
    FlsRd_NoteTest();
#elif EXTZONE_flag
    ExtZoneSave_Test();
#elif NETMACHINE_TEST_flag
    NetMachineSave_Test();
#elif PnConfig_flag
    PnConfig_test();

#elif HISTORY_flag
    Histroy_test();
  //  FlsWr_Hist_Start();
#elif HISTORYALL_flag
//    Histroy_testAllTmr();

#elif WR_RD_HEAD_10NUMS_flag
    WriteValueWithHead_NUM10();
#elif WR_RD_HEADLOTS_10NUMS_flag
    WriteValueWithHeadLOTS_NUM10();
#elif WR_RD_HEADLOTS_10NUMSCRC_flag
    WriteValueWithHeadLOTS_NUM10CRC();
#elif SYSSTATUS_flag
    SetMeStatusTest();
#elif TESTCRC_flag//添加头
    EraseTwoChip();
//    WriteValueWithHeadLOTS_NUM10_Addr(0,0x16000);
//    WriteValueWithHeadLOTS_NUM10_Addr(0,0x17000);
//    WriteValueWithHeadLOTS_NUM10_Addr(1,0x16000);
//    WriteValueWithHeadLOTS_NUM10_Addr(1,0x17000);
//    WriteValueWithHeadLOTS_NUM10_Addr(1,0x18000);

//    WriteValueWithHeadLOTS_NUM10_Addr(0x18000);
#elif RD_ADDR_TIME_flag

#elif HEAD_TEST_flag
    static BOOL OnceExec=TRUE;
    if(OnceExec){
        //先写一个头
        WriteValueWithHeadLOTS_NUM10_Addr(NORFLASH0,0x16000);
//        WriteValueWithHeadLOTS_NUM10_Addr(0,0x17000);
        WriteValueWithHeadLOTS_NUM10_Addr(NORFLASH1,0x16000);//
        OnceExec=FALSE;
    }


#endif



}
BOOL p011_tmrtask(funpara* para)
{
#if DISABLE_f
    Disable_testtmr(para);
#elif FLASHBOTTONTESTflag
#if RD_FLASH0
    flsGetValueTmr(0,0x10);
#else
    flsGetValueTmr(2,0x10);//实际上其线序为2
#endif
//    flsGetValueTmr(1,0x10);
#elif FLSPOWEROFflag
    ReadT_PowerOff_Tmr();
#elif RD_POEWROFF_MANUAL_flag
//    ReadPowerOffValueFromFlsTmr();
    ReadPowerOffValuesFromFlsTmr();
#elif WR_RD_POWEROFFVALUE_WITHHEAD_flag

    ReadPowerOffValuesFromFlsWithHeadTmr();
#elif AUTOSAVEPOWEROFF_flag//自动读取关机时间

    AutoSavePowerOffTmr();

#elif MESTATUS_flag
    RDMeStatusTmr();
#elif FIELDTEST_flag
    FlsSave_FieldTestTmr();
#elif NOTE_flag
    FlsRd_NoteTmrTest();
#elif EXTZONE_flag
    ExtZoneSave_TestTmr();
#elif NETMACHINE_TEST_flag
    NetMachineSave_TestTmr();
#elif PnConfig_flag
    PnConfig_testtmr();
#elif HISTORY_flag
    Histroy_testTmr();
#elif HISTORYALL_flag
    Histroy_testAllTmr();
#elif WR_RD_HEAD_10NUMS_flag

    ReadValueHeadTmr_NUM10();
#elif WR_RD_HEADLOTS_10NUMS_flag
    ReadValueHeadTmrLOTS_NUM10();
#elif WR_RD_HEADLOTS_10NUMSCRC_flag
    ReadValueHeadTmrLOTS_NUM10CRC();

#elif SYSSTATUS_flag
    MeStatusTest();
#elif TESTCRC_flag//添加头

#elif RD_ADDR_TIME_flag
    RD_Time_TwoChip();


#elif HEAD_TEST_flag



#endif
    return FALSE;
}







//获取历史条数
void GetHistoryNumTest(void)
{
    U32 hisnum=HistRd_CacuItem_HistCls(U_SysTask_History, 0);
    ShowXY_Fig_Pre0(4,0,1,hisnum,4);
}





void p059_complete(funpara *para)
{
    (void)para;

}
void p052_complete(funpara *para)
{
    (void)para;
    ShowXYCodeCharRL(2,0,1,"全部历史信息。。。",FALSE);

}
void p053_complete(funpara *para)
{
    (void)para;
    ShowXYCodeCharRL(2,0,1,"火警历史信息。。。",FALSE);

}
void p054_complete(funpara *para)
{
    (void)para;
    ShowXYCodeCharRL(2,0,1,"联动历史信息。。。",FALSE);

}
void p055_complete(funpara *para)
{
    (void)para;
    ShowXYCodeCharRL(2,0,1,"故障历史信息。。。",FALSE);

}
void p056_complete(funpara *para)
{
    (void)para;
    ShowXYCodeCharRL(2,0,1,"操作历史信息。。。",FALSE);

}
void p057_complete(funpara *para)
{
    (void)para;
    ShowXYCodeCharRL(2,0,1,"其它历史信息。。。",FALSE);

}



BOOL p058_modify(funpara* para)
{
    (void)para;
//    Clear_Key_CallBack(&pgcom_callb);
    ClrWindow_Page();
    pgcom_callb.FunSets.selfInitfun();


    return FALSE;
}

void NoteTest(void)
{
    ClrWindow_Page();




}





//模拟曲线定时显示内容
BOOL p061_tmrtask(funpara* para)
{
    show_Simulated_curves(para);
    ExecLcdShow();

    return FALSE;
}

BOOL doTmrTaskSet(funpara* para)
{
    if(0==para->tmrId||0==para->tmrMs)//不符合条件返回
        return TRUE;
    if(!para->TmrTaskSetted){
        SetTmrTickTask(para->tmrId,para->tmrMs);
        para->TmrTaskSetted=TRUE;
    }
    return FALSE;
}
//不符合返回
BOOL doTmrTaskGet(funpara* para)
{
    if(0==para->tmrId||0==para->tmrMs)//不符合条件返回
        return TRUE;
    if(!GetTickTaskStatus(para->tmrId))
    {
        return TRUE;
    }
    return FALSE;
}

BOOL doTmrTaskKill(funpara* para)
{
    if(0==para->tmrId||0==para->tmrMs)//不符合条件返回
        return TRUE;
    if(!KillTickTask(para->tmrId)){
        return TRUE;
    }
    return FALSE;
}






//回路加1
BOOL p058_keyup(funpara* para)
{
    key_callbackfun *pgcb;
    U8 tmp;
    (void)para;
    pgcb=&pgcom_callb;
    if(0==pgcb->KeyResponseSv&&0==pgcb->KeyResponseEv)
        return TRUE;
    if(0==pgcb->WhichPos)
        InputNum_Show_common_call(pgcb->curstartrow,
                                  &pgcb->pracpos,
                                  pgcb->KeyResponseSv,
                                  pgcb->curarrayptr,
                                  pgcb->intputMaxnum,
                                  pgcb);
    else if(pgcb->WhichPos<pgcb->KeyResponseEv){
        tmp=pgcb->inputFig[pgcb->WhichPos-1];//因为只有一位数
        pgcb->FunSets.selfInitfun();
        InputNum_Show_common_call(pgcb->curstartrow,
                                  &pgcb->pracpos,
                                  tmp+1,
                                  pgcb->curarrayptr,
                                  pgcb->intputMaxnum,
                                  pgcb);
    }


    return FALSE;
}



BOOL p058_keydown(funpara* para)
{
    key_callbackfun *pgcb;
    U8 tmp;
    (void)para;
    pgcb=&pgcom_callb;
    if(0==pgcb->KeyResponseSv&&0==pgcb->KeyResponseEv)
        return TRUE;
    if(0==pgcb->WhichPos)
        InputNum_Show_common_call(pgcb->curstartrow,
                                  &pgcb->pracpos,
                                  pgcb->KeyResponseEv,
                                  pgcb->curarrayptr,
                                  pgcb->intputMaxnum,
                                  pgcb);
    else if(pgcb->WhichPos<pgcb->KeyResponseEv){
        tmp=pgcb->inputFig[pgcb->WhichPos-1];//因为只有一位数
        pgcb->FunSets.selfInitfun();
        InputNum_Show_common_call(pgcb->curstartrow,
                                  &pgcb->pracpos,
                                  tmp-1,
                                  pgcb->curarrayptr,
                                  pgcb->intputMaxnum,
                                  pgcb);
    }


    return FALSE;
}
#if 1//进入各个界面函数设置
/******************************************************************************
* 页面按键返回后的处理
*
******************************************************************************/
void FigStop(key_callbackfun* pg)
{
    if(!pg->Used)
        return;
    FigInput_Stop();
    Clear_Key_CallBack_Over(pg);
    pg->FunSets.KillTmr(&pg->FunSets.para_tmr);
}
#endif ////进入各个界面函数设置

