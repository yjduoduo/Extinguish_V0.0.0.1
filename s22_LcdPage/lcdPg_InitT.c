
#include "lcdPg_InitT.h"
#define __KeyCall_Pg_EX
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


//key_callbackfun *pCall=NULL;
key_callbackfun *pgCall=NULL;
#include "sysDef.h"
#include "sysStatus.h"

#include "lcdPg_ShowLineFun.h"




void SetLanguage(U8 num,key_callbackfun *pgCall)
{
    U8 language;
    language= GetLanguage();
    switch(language)
    {
    case U_Chinese_LANGUAGE://设置光标及数组
        pgCall->curstartrow=AllPosText[num].CnPosText.CursorRow;
        pgCall->curarrayptr=AllPosText[num].CnPosText.CursorArray;
        pgCall->intputMaxnum=AllPosText[num].InputMaxnum;
    break;
	case U_English_LANGUAGE:
		pgCall->curstartrow=AllPosText[num].EnPosText.CursorRow;
        pgCall->curarrayptr=AllPosText[num].EnPosText.CursorArray;
        pgCall->intputMaxnum=AllPosText[num].InputMaxnum;
    default:
        break;
    }


}


//手动启停设备
void p010_initpgentry(void)
{
    pgCall=&pgcom_callb;
    Clear_Key_CallBack(pgCall);//清除参数
    //设置必要参数

    pgCall->pgNum=10;
    SetLanguage(pgCall->pgNum,&pgcom_callb);
    pgCall->JudegInputNumRange=TRUE;//需要判断输入数字的范围
    pgCall->HaveCursor=TRUE;
    //对应关系
    pgCall->FunSets.iniPagefun=p010_inipage;
    pgCall->FunSets.para_ltp.flag=TRUE;
    pgCall->FunSets.Looptipsfun=p010_loopinputtips;
    pgCall->FunSets.Addrtipsfun=p010_addrinputtips;
    pgCall->FunSets.Implementfun=p010_complete;
    pgCall->FunSets.JudgeInputNumfun=p010_InputNum_InRange;
    pgCall->FunSets.RecvKeyDealfun=p010_keyDeal;

    //按键是否需要Enter来确认
    pgCall->FunSets.para_rec.KeyType.runflag=FALSE;
//    pgCall->FunSets.para_rec.KeyType.keytype=U_KEY_Enter;

    //初始化
    pgCall->FunSets.iniPagefun(&pgCall->FunSets.para_ini);
//    回路信息提示
    //第一次需要显示

    pgCall->FunSets.Looptipsfun(&pgCall->FunSets.para_ltp);
}

void p060_initpgentry(void)
{
    pgCall=&pgcom_callb;
    Clear_Key_CallBack(pgCall);//清除参数
    //设置必要参数
    pgCall->pgNum=60;
    SetLanguage(pgCall->pgNum,&pgcom_callb);

    pgCall->JudegInputNumRange=TRUE;//需要判断输入数字的范围
    pgCall->HaveCursor=TRUE;
    //对应关系
    pgCall->FunSets.iniPagefun=p060_inipage;
//    pgCall->FunSets.Looptipsfun=p010_loopinputtips;
//    pgCall->FunSets.Addrtipsfun=p010_addrinputtips;
    pgCall->FunSets.Implementfun=p060_complete;
    pgCall->FunSets.JudgeInputNumfun=p010_InputNum_InRange;
    pgCall->FunSets.RecvKeyDealfun=p010_keyDeal;
    //按键是否需要Enter来确认
    pgCall->FunSets.para_rec.KeyType.runflag=TRUE;
    pgCall->FunSets.para_rec.KeyType.keytype=U_KEY_Enter;

    pgCall->FunSets.iniPagefun(&pgCall->FunSets.para_ini);

}
//自动登记，直接实现即可
void p016_initpgentry(void)
{
    pgCall=&pgcom_callb;
    Clear_Key_CallBack(pgCall);//清除参数
    //设置必要参数
    pgCall->pgNum=16;
    SetLanguage(pgCall->pgNum,&pgcom_callb);

    //对应关系
    pgCall->FunSets.iniPagefun=p016_inipage;
    pgCall->FunSets.Implementfun=p016_complete;
    pgCall->FunSets.para_imp.fig=0;

    pgCall->FunSets.iniPagefun(&pgCall->FunSets.para_ini);
    pgCall->FunSets.Implementfun(&pgCall->FunSets.para_imp);

}

//手动登记
void p017_initpgentry(void)
{
    pgCall=&pgcom_callb;
    Clear_Key_CallBack(pgCall);//清除参数
    //设置必要参数
    
    pgCall->pgNum=17;
    SetLanguage(pgCall->pgNum,&pgcom_callb);
    
    pgCall->JudegInputNumRange=TRUE;//需要判断输入数字的范围
    pgCall->HaveCursor=TRUE;
    //对应关系
    pgCall->FunSets.iniPagefun=p017_inipage;
    pgCall->FunSets.Implementfun=p017_complete;

    pgCall->FunSets.JudgeInputNumfun=p017_InputNum_InRange;
    pgCall->FunSets.RecvKeyDealfun=p010_keyDeal;
    //按键是否需要Enter来确认
    pgCall->FunSets.para_rec.KeyType.runflag=TRUE;
    pgCall->FunSets.para_rec.KeyType.keytype=U_KEY_Enter;

    pgCall->FunSets.iniPagefun(&pgCall->FunSets.para_ini);

}
//手动屏蔽
void p018_initpgentry(void)
{
    pgCall=&pgcom_callb;
    Clear_Key_CallBack(pgCall);//清除参数
    //对应关系
    pgCall->FunSets.iniPagefun=p018_inipage;
    pgCall->FunSets.Implementfun=p018_complete;

    pgCall->FunSets.JudgeInputNumfun=p017_InputNum_InRange;
    pgCall->FunSets.RecvKeyDealfun=p010_keyDeal;
    //设置必要参数
	pgCall->pgNum=18;
    SetLanguage(pgCall->pgNum,&pgcom_callb);
	
    pgCall->JudegInputNumRange=TRUE;//需要判断输入数字的范围
    pgCall->HaveCursor=TRUE;

    //按键是否需要Enter来确认
    pgCall->FunSets.para_rec.KeyType.runflag=TRUE;
    pgCall->FunSets.para_rec.KeyType.keytype=U_KEY_Enter;

    pgCall->FunSets.iniPagefun(&pgCall->FunSets.para_ini);
}
//时间设置
void p013_initpgentry(void)
{
    pgCall=&pgcom_callb;
    Clear_Key_CallBack(pgCall);//清除参数
    //对应关系
    pgCall->FunSets.iniPagefun=p013_inipage;
    pgCall->FunSets.Implementfun=p013_complete;

    pgCall->FunSets.JudgeInputNumfun=p013_InputNum_InRange;
    pgCall->FunSets.RecvKeyDealfun=p010_keyDeal;
    //设置必要参数
	pgCall->pgNum=13;
    SetLanguage(pgCall->pgNum,&pgcom_callb);

	
    pgCall->JudegInputNumRange=TRUE;//需要判断输入数字的范围
    pgCall->HaveCursor=TRUE;
    //按键是否需要Enter来确认
    pgCall->FunSets.para_rec.KeyType.runflag=FALSE;
//    pgCall->FunSets.para_rec.KeyType.keytype=U_KEY_Enter;

    pgCall->FunSets.iniPagefun(&pgCall->FunSets.para_ini);


}
//灭火区设置
void p030_initpgentry(void)
{
    pgCall=&pgcom_callb;
    Clear_Key_CallBack(pgCall);//清除参数
    //对应关系



    pgCall->FunSets.para_imp.str[0]="设置成功";
    pgCall->FunSets.para_imp.str[1]="设置取消";
    pgCall->FunSets.para_imp.row=8;
    pgCall->FunSets.para_imp.col=22;
    pgCall->FunSets.iniPagefun=p030_inipage;
    pgCall->FunSets.Implementfun=pcom_complete;

    pgCall->FunSets.JudgeInputNumfun=p030_InputNum_InRange;
    pgCall->FunSets.RecvKeyDealfun=p010_keyDeal;
    //设置必要参数

//    pgCall->curstartrow=STARTROW_FIG_p030;
//    pgCall->curarrayptr=&cstpos_p030[0];
//    pgCall->intputMaxnum=ARRAYSIZE(cstpos_p030);

    pgCall->pgNum=30;
    SetLanguage(pgCall->pgNum,&pgcom_callb);

    pgCall->JudegInputNumRange=TRUE;//需要判断输入数字的范围
    pgCall->HaveCursor=TRUE;
    //按键是否需要Enter来确认
    pgCall->FunSets.para_rec.KeyType.runflag=FALSE;
//    pgCall->FunSets.para_rec.KeyType.keytype=U_KEY_Enter;

    pgCall->FunSets.iniPagefun(&pgCall->FunSets.para_ini);
}

//语言选择
void p037_initpgentry(void)
{
    pgCall=&pgcom_callb;
    Clear_Key_CallBack(pgCall);//清除参数

	
    pgCall->pgNum=37;
    SetLanguage(pgCall->pgNum,&pgcom_callb);
    //对应关系
    pgCall->FunSets.para_imp.str[0]="设置中文成功";
    pgCall->FunSets.para_imp.str[1]="设置英文成功";
    pgCall->FunSets.para_imp.row=8;
    pgCall->FunSets.para_imp.col=8;
    pgCall->FunSets.iniPagefun=p037_inipage;
    pgCall->FunSets.Implementfun=pcom_complete;

    pgCall->FunSets.RecvKeyDealfun=p010_keyDeal;
    //设置必要参数
    pgCall->JudegInputNumRange=TRUE;//需要判断输入数字的范围
    pgCall->HaveCursor=FALSE;
    //按键是否需要Enter来确认
    pgCall->FunSets.para_rec.KeyType.runflag=FALSE;
    //    pgCall->FunSets.para_rec.KeyType.keytype=U_KEY_Enter;

    pgCall->FunSets.iniPagefun(&pgCall->FunSets.para_ini);

}
//调试模式
void p038_initpgentry(void)
{
    pgCall=&pgcom_callb;
    Clear_Key_CallBack(pgCall);//清除参数
    
    pgCall->pgNum=38;
    SetLanguage(pgCall->pgNum,&pgcom_callb);
    //对应关系
    pgCall->FunSets.para_imp.str[0]="设置正常模式成功";
    pgCall->FunSets.para_imp.str[1]="设置调试模式成功";
    pgCall->FunSets.para_imp.row=8;
    pgCall->FunSets.para_imp.col=12;
    pgCall->FunSets.iniPagefun=p038_inipage;
    pgCall->FunSets.Implementfun=pcom_complete;

    pgCall->FunSets.RecvKeyDealfun=p010_keyDeal;
    //设置必要参数
    pgCall->JudegInputNumRange=TRUE;//需要判断输入数字的范围
    pgCall->HaveCursor=FALSE;
    //按键是否需要Enter来确认
    pgCall->FunSets.para_rec.KeyType.runflag=FALSE;
    //    pgCall->FunSets.para_rec.KeyType.keytype=U_KEY_Enter;

    pgCall->FunSets.iniPagefun(&pgCall->FunSets.para_ini);

}
//屏蔽信息
void p041_initpgentry(void)
{
    pgCall=&pgcom_callb;
    Clear_Key_CallBack(pgCall);//清除参数
    pgCall->pgNum=41;
    SetLanguage(pgCall->pgNum,&pgcom_callb);
    //对应关系
    pgCall->FunSets.iniPagefun=p041_inipage;
    pgCall->FunSets.Implementfun=p041_complete;
//没有按键的函数，需要直接调用相应功能
    pgCall->FunSets.iniPagefun(&pgCall->FunSets.para_ini);
    pgCall->FunSets.Implementfun(NULL);
}
//故障信息
void p040_initpgentry(void)
{
    pgCall=&pgcom_callb;
    Clear_Key_CallBack(pgCall);//清除参数
    pgCall->pgNum=40;
    SetLanguage(pgCall->pgNum,&pgcom_callb);
    //对应关系
    pgCall->FunSets.iniPagefun=p040_inipage;
    pgCall->FunSets.Implementfun=p041_complete;
//没有按键的函数，需要直接调用相应功能
    pgCall->FunSets.iniPagefun(&pgCall->FunSets.para_ini);
    pgCall->FunSets.Implementfun(NULL);
}
//查询汉字注释
void p044_initpgentry(void)
{
    pgCall=&pgcom_callb;
    Clear_Key_CallBack(pgCall);//清除参数
    //设置必要参数
    pgCall->pgNum=44;
    SetLanguage(pgCall->pgNum,&pgcom_callb);
    pgCall->JudegInputNumRange=TRUE;//需要判断输入数字的范围
    pgCall->HaveCursor=TRUE;
    //对应关系
    pgCall->FunSets.iniPagefun=p044_inipage;
    //对应关系
    pgCall->Calllast=TRUE;//最后调用实现函数
    pgCall->FunSets.Implementfun=p044_complete;
    pgCall->FunSets.JudgeInputNumfun=p042_InputNum_InRange;
    pgCall->FunSets.RecvKeyDealfun=p010_keyDeal;
    //按键是否需要Enter来确认
    pgCall->FunSets.para_rec.KeyType.runflag=FALSE;
    pgCall->FunSets.iniPagefun(&pgCall->FunSets.para_ini);
}
//查询调试模式
void p039_initpgentry(void)
{
    pgCall=&pgcom_callb;
    Clear_Key_CallBack(pgCall);//清除参数
    pgCall->pgNum=39;
    SetLanguage(pgCall->pgNum,&pgcom_callb);
    //对应关系
    pgCall->FunSets.iniPagefun=p039_inipage;
    pgCall->FunSets.Implementfun=p039_complete;
//没有按键的函数，需要直接调用相应功能
    pgCall->FunSets.iniPagefun(&pgCall->FunSets.para_ini);
    pgCall->FunSets.Implementfun(NULL);
}
//查询总线登记地址
//直接显示,输入数字即显示
//directshow
void p058_initpgentry(void)
{
    pgCall=&pgcom_callb;
    Clear_Key_CallBack(pgCall);//清除参数
    //设置必要参数
    pgCall->pgNum=58;
    SetLanguage(pgCall->pgNum,&pgcom_callb);
  //  pgCall->curstartrow=STARTROW_FIG_p058;
   // pgCall->curarrayptr=&cstpos_p058[0];
   // pgCall->intputMaxnum=ARRAYSIZE(cstpos_p058);
    pgCall->JudegInputNumRange=TRUE;//需要判断输入数字的范围
    pgCall->HaveCursor=TRUE;
    //对应关系
    pgCall->FunSets.iniPagefun=p058_inipage;
    //对应关系
    pgCall->Calllast=TRUE;//最后调用实现函数
//    pgCall->FunSets.para_imp.str[0]="设置成功";
//    pgCall->FunSets.para_imp.str[1]="设置失败";
//    pgCall->FunSets.para_imp.row=8;
//    pgCall->FunSets.para_imp.col=12;
    pgCall->FunSets.Implementfun=p058_complete;
    pgCall->FunSets.JudgeInputNumfun=p058_InputNum_InRange;
    pgCall->FunSets.RecvKeyDealfun=p010_keyDeal;
    //按左键重新输入，selfInitfun必须初始化
    pgCall->FunSets.Modifyfun=p058_modify;
    pgCall->FunSets.selfInitfun=p058_initpgentry;
    if(!pgCall->FunSets.selfInitfun)
        pgCall->FunSets.selfInitfun=donothingnonepara;
    pgCall->KeyResponseSv=1;
    pgCall->KeyResponseEv=4;
    pgCall->FunSets.KeyUpfun=p058_keyup;
    pgCall->FunSets.KeyDownfun=p058_keydown;
    //按键是否需要Enter来确认
    pgCall->FunSets.para_rec.KeyType.runflag=FALSE;
//    pgCall->FunSets.para_rec.KeyType.keytype=U_KEY_Enter;

    pgCall->FunSets.iniPagefun(&pgCall->FunSets.para_ini);
}
//查询联动编程
void p042_initpgentry(void)
{
    pgCall=&pgcom_callb;
    Clear_Key_CallBack(pgCall);//清除参数
    //设置必要参数
    pgCall->pgNum=42;
    SetLanguage(pgCall->pgNum,&pgcom_callb);
	
    //pgCall->curstartrow=STARTROW_FIG_p042;
    //pgCall->curarrayptr=&cstpos_p010[0];
    //pgCall->intputMaxnum=ARRAYSIZE(cstpos_p010);
    pgCall->JudegInputNumRange=TRUE;//需要判断输入数字的范围
    pgCall->HaveCursor=TRUE;
    //对应关系
    pgCall->FunSets.iniPagefun=p042_inipage;
    //对应关系
    pgCall->Calllast=TRUE;//最后调用实现函数
    pgCall->FunSets.Implementfun=p042_complete;
    pgCall->FunSets.JudgeInputNumfun=p042_InputNum_InRange;
    pgCall->FunSets.RecvKeyDealfun=p010_keyDeal;
    //按键是否需要Enter来确认
    pgCall->FunSets.para_rec.KeyType.runflag=FALSE;

    pgCall->FunSets.iniPagefun(&pgCall->FunSets.para_ini);
}
//查询软件版本信息
void p047_initpgentry(void)
{
    pgCall=&pgcom_callb;
    Clear_Key_CallBack(pgCall);//清除参数
    pgCall->pgNum=47;
    SetLanguage(pgCall->pgNum,&pgcom_callb);
	    
    //设置必要参数
    pgCall->JudegInputNumRange=TRUE;//需要判断输入数字的范围
    //对应关系
    pgCall->FunSets.iniPagefun=p047_inipage;
    //对应关系
    pgCall->FunSets.Implementfun=p047_complete;

    pgCall->FunSets.iniPagefun(&pgCall->FunSets.para_ini);
    pgCall->FunSets.Implementfun(&pgCall->FunSets.para_imp);
}

//查询组网控制器
void p049_initpgentry(void)
{
    pgCall=&pgcom_callb;
    Clear_Key_CallBack(pgCall);//清除参数
    pgCall->pgNum=49;
    SetLanguage(pgCall->pgNum,&pgcom_callb);
    //设置必要参数
    pgCall->JudegInputNumRange=TRUE;//需要判断输入数字的范围
    //对应关系
    pgCall->FunSets.iniPagefun=p049_inipage;
    //对应关系
    pgCall->FunSets.Implementfun=p049_complete;

    pgCall->FunSets.iniPagefun(&pgCall->FunSets.para_ini);
    pgCall->FunSets.Implementfun(&pgCall->FunSets.para_imp);
}
//查询灭火区设置
void p048_initpgentry(void)
{
    pgCall=&pgcom_callb;
    Clear_Key_CallBack(pgCall);//清除参数
    pgCall->pgNum=48;
    SetLanguage(pgCall->pgNum,&pgcom_callb);
    //设置必要参数
    pgCall->JudegInputNumRange=TRUE;//需要判断输入数字的范围
    pgCall->HaveCursor=FALSE;
    //对应关系
    pgCall->FunSets.iniPagefun=p048_inipage;
    //对应关系
    pgCall->FunSets.Implementfun=p048_complete;

    pgCall->FunSets.iniPagefun(&pgCall->FunSets.para_ini);
    pgCall->FunSets.Implementfun(&pgCall->FunSets.para_imp);
}
//设置联网控制器
/*
* 页面: //设置联网控制器
* 	本机地址: _ _
*	主机地址: _ _
*/
void p024_initpgentry(void)
{
    pgCall=&pgcom_callb;
    Clear_Key_CallBack(pgCall);//清除参数
    //设置必要参数
    pgCall->pgNum=24;
    SetLanguage(pgCall->pgNum,&pgcom_callb);
    //pgCall->curstartrow=STARTROW_FIG_p024;
    //pgCall->curarrayptr=&cstpos_p024[0];
    //pgCall->intputMaxnum=ARRAYSIZE(cstpos_p024);
    pgCall->JudegInputNumRange=TRUE;//需要判断输入数字的范围
    pgCall->HaveCursor=TRUE;
    //对应关系
    pgCall->FunSets.iniPagefun=p024_inipage;
    //对应关系
    pgCall->Calllast=TRUE;//最后调用实现函数
    pgCall->FunSets.Implementfun=p024_complete;
    //范围？？
    pgCall->FunSets.JudgeInputNumfun=pcom_InputNum_InRange;
    pgCall->FunSets.RecvKeyDealfun=p010_keyDeal;

//    pgCall->FunSets.Modifyfun=p058_modify;
    //按左键重新输入，selfInitfun必须初始化
    pgCall->FunSets.selfInitfun=p024_initpgentry;
    if(!pgCall->FunSets.selfInitfun)
        pgCall->FunSets.selfInitfun=donothingnonepara;
//    pgCall->KeyResponseSv=1;
//    pgCall->KeyResponseEv=4;
//    pgCall->FunSets.KeyUpfun=p058_keyup;
//    pgCall->FunSets.KeyDownfun=p058_keydown;
    //按键是否需要Enter来确认
    pgCall->FunSets.para_rec.KeyType.runflag=FALSE;
//    pgCall->FunSets.para_rec.KeyType.keytype=U_KEY_Enter;

    pgCall->FunSets.iniPagefun(&pgCall->FunSets.para_ini);
}
/******************************************************************************
* 页面: //设置本机关联地址
* 	_ _机_ _回路_ _ _地址 ~ _ _ _地址
*	key: 添加  key:删除  key:查看现有关联
* 查看现有关联，与 P028_QrAddrRelation 不是一个界面，二者用户权限不同。
* 可以共用子函数。
******************************************************************************/
void p027_initpgentry(void)
{
    pgCall=&pgcom_callb;
    Clear_Key_CallBack(pgCall);//清除参数
    //设置必要参数
    pgCall->pgNum=27;
    SetLanguage(pgCall->pgNum,&pgcom_callb);
	
    //pgCall->curstartrow=STARTROW_FIG_p024;
    //pgCall->curarrayptr=&cstpos_p027[0];
    //pgCall->intputMaxnum=ARRAYSIZE(cstpos_p027);
    pgCall->JudegInputNumRange=TRUE;//需要判断输入数字的范围
    pgCall->HaveCursor=TRUE;
    //对应关系
    pgCall->FunSets.iniPagefun=p027_inipage;
    //对应关系
    pgCall->Calllast=TRUE;//最后调用实现函数
    pgCall->FunSets.Implementfun=p027_complete;
    //范围？？
    pgCall->FunSets.JudgeInputNumfun=pcom_InputNum_InRange;
    pgCall->FunSets.RecvKeyDealfun=p010_keyDeal;

    //按左键重新输入，selfInitfun必须初始化
    pgCall->FunSets.selfInitfun=p027_initpgentry;
    if(!pgCall->FunSets.selfInitfun)
        pgCall->FunSets.selfInitfun=donothingnonepara;
    //按键是否需要Enter来确认
    pgCall->FunSets.para_rec.KeyType.runflag=FALSE;

    pgCall->FunSets.iniPagefun(&pgCall->FunSets.para_ini);
}
/******************************************************************************
* 页面: // 恢复默认设置
* 	恢复默认设置？
*	  key:是   key:退出
*
******************************************************************************/
void p015_initpgentry(void)
{
    pgCall=&pgcom_callb;
    Clear_Key_CallBack(pgCall);//清除参数
    pgCall->pgNum=15;
    SetLanguage(pgCall->pgNum,&pgcom_callb);    
    //设置必要参数
/*    pgCall->curstartrow=STARTROW_FIG_p024;
    pgCall->curarrayptr=&cstpos_p027[0];
    pgCall->intputMaxnum=ARRAYSIZE(cstpos_p027)*/;
    pgCall->JudegInputNumRange=TRUE;//需要判断输入数字的范围
    pgCall->HaveCursor=TRUE;
    //对应关系
    pgCall->FunSets.iniPagefun=p015_inipage;
    //对应关系
    pgCall->Calllast=FALSE;//最后调用实现函数
    pgCall->FunSets.Implementfun=p015_complete;
    //范围？？
    pgCall->FunSets.JudgeInputNumfun=p015_InputNum_InRange;
    pgCall->FunSets.RecvKeyDealfun=p010_keyDeal;

    //按左键重新输入，selfInitfun必须初始化
    pgCall->FunSets.selfInitfun=p015_initpgentry;
    if(!pgCall->FunSets.selfInitfun)
        pgCall->FunSets.selfInitfun=donothingnonepara;
    //按键是否需要Enter来确认
    pgCall->FunSets.para_rec.KeyType.runflag=FALSE;

    pgCall->FunSets.iniPagefun(&pgCall->FunSets.para_ini);
}
/******************************************************************************
* 页面: // 手动注释
*      _回路_ _地址
* 	注释内容: 注释输入暂时延后做
*
******************************************************************************/
void p019_initpgentry(void)
{
    pgCall=&pgcom_callb;
    Clear_Key_CallBack(pgCall);//清除参数
    //设置必要参数
    pgCall->pgNum=19;
    SetLanguage(pgCall->pgNum,&pgcom_callb);  
    //pgCall->curstartrow=STARTROW_FIG_p019;
    //pgCall->curarrayptr=&cstpos_p010[0];
    //pgCall->intputMaxnum=ARRAYSIZE(cstpos_p010);
    pgCall->JudegInputNumRange=TRUE;//需要判断输入数字的范围
    pgCall->HaveCursor=TRUE;
    //对应关系
    pgCall->FunSets.iniPagefun=p019_inipage;
    //对应关系
    pgCall->Calllast=FALSE;//最后调用实现函数
    pgCall->FunSets.Implementfun=p015_complete;
    //范围？？
    pgCall->FunSets.JudgeInputNumfun=pcom_InputNum_InRange;
    pgCall->FunSets.RecvKeyDealfun=p010_keyDeal;

    //按左键重新输入，selfInitfun必须初始化
    pgCall->FunSets.selfInitfun=p019_initpgentry;
    if(!pgCall->FunSets.selfInitfun)
        pgCall->FunSets.selfInitfun=donothingnonepara;
    //按键是否需要Enter来确认
    pgCall->FunSets.para_rec.KeyType.runflag=FALSE;

    pgCall->FunSets.iniPagefun(&pgCall->FunSets.para_ini);
}
/******************************************************************************
* 页面: // 设置联动编程
*      _回路_ _地址
* 	内容:  暂时延后做
*
******************************************************************************/
void p020_initpgentry(void)
{
    pgCall=&pgcom_callb;
    Clear_Key_CallBack(pgCall);//清除参数
    //设置必要参数
    pgCall->pgNum=20;
    SetLanguage(pgCall->pgNum,&pgcom_callb); 
	
    //pgCall->curstartrow=STARTROW_FIG_p019;
    //pgCall->curarrayptr=&cstpos_p010[0];
    //pgCall->intputMaxnum=ARRAYSIZE(cstpos_p010);
    pgCall->JudegInputNumRange=TRUE;//需要判断输入数字的范围
    pgCall->HaveCursor=TRUE;
    //对应关系
    pgCall->FunSets.iniPagefun=p020_inipage;
    //对应关系
    pgCall->Calllast=FALSE;//最后调用实现函数
    pgCall->FunSets.Implementfun=p015_complete;
    //范围？？
    pgCall->FunSets.JudgeInputNumfun=pcom_InputNum_InRange;
    pgCall->FunSets.RecvKeyDealfun=p010_keyDeal;

    //按左键重新输入，selfInitfun必须初始化
    pgCall->FunSets.selfInitfun=p020_initpgentry;
    if(!pgCall->FunSets.selfInitfun)
        pgCall->FunSets.selfInitfun=donothingnonepara;
    //按键是否需要Enter来确认
    pgCall->FunSets.para_rec.KeyType.runflag=FALSE;

    pgCall->FunSets.iniPagefun(&pgCall->FunSets.para_ini);
}
// 查询关联地址
void p028_initpgentry(void)
{
    pgCall=&pgcom_callb;
    Clear_Key_CallBack(pgCall);//清除参数
    //设置必要参数
    pgCall->pgNum=28;
    SetLanguage(pgCall->pgNum,&pgcom_callb); 
    //pgCall->curstartrow=STARTROW_FIG_p019;
    //pgCall->curarrayptr=&cstpos_p010[0];
    //pgCall->intputMaxnum=ARRAYSIZE(cstpos_p010);
    pgCall->JudegInputNumRange=TRUE;//需要判断输入数字的范围
    pgCall->HaveCursor=TRUE;
    //对应关系
    pgCall->FunSets.iniPagefun=p028_inipage;
    //对应关系
    pgCall->Calllast=FALSE;//最后调用实现函数
    pgCall->FunSets.Implementfun=p028_complete;
    //范围？？
    pgCall->FunSets.JudgeInputNumfun=pcom_InputNum_InRange;
    pgCall->FunSets.RecvKeyDealfun=p010_keyDeal;

    //按左键重新输入，selfInitfun必须初始化
    pgCall->FunSets.selfInitfun=p028_initpgentry;
    if(!pgCall->FunSets.selfInitfun)
        pgCall->FunSets.selfInitfun=donothingnonepara;
    //按键是否需要Enter来确认
    pgCall->FunSets.para_rec.KeyType.runflag=FALSE;

    pgCall->FunSets.iniPagefun(&pgCall->FunSets.para_ini);
}
//清除回路登记
void p080_initpgentry(void)
{
    pgCall=&pgcom_callb;
    Clear_Key_CallBack(pgCall);//清除参数
    //设置必要参数
    pgCall->pgNum=80;
    SetLanguage(pgCall->pgNum,&pgcom_callb); 

    pgCall->JudegInputNumRange=TRUE;//需要判断输入数字的范围
    pgCall->HaveCursor=FALSE;
    //对应关系
    pgCall->FunSets.iniPagefun=p080_inipage;
    //对应关系
    pgCall->Calllast=FALSE;//最后调用实现函数
    pgCall->FunSets.Implementfun=p080_complete;
    //范围？？
    pgCall->FunSets.JudgeInputNumfun=p015_InputNum_InRange;
    pgCall->FunSets.RecvKeyDealfun=p010_keyDeal;

    //按左键重新输入，selfInitfun必须初始化
    pgCall->FunSets.selfInitfun=p080_initpgentry;
    if(!pgCall->FunSets.selfInitfun)
        pgCall->FunSets.selfInitfun=donothingnonepara;
    //按键是否需要Enter来确认
    pgCall->FunSets.para_rec.KeyType.runflag=FALSE;

    pgCall->FunSets.iniPagefun(&pgCall->FunSets.para_ini);
}
//清除联动编程
void p077_initpgentry(void)
{
    pgCall=&pgcom_callb;
    Clear_Key_CallBack(pgCall);//清除参数
    //设置必要参数

	pgCall->pgNum=77;
    SetLanguage(pgCall->pgNum,&pgcom_callb); 
	
    pgCall->JudegInputNumRange=TRUE;//需要判断输入数字的范围
    pgCall->HaveCursor=TRUE;
    //对应关系
    pgCall->FunSets.iniPagefun=p077_inipage;
    //对应关系
    pgCall->Calllast=FALSE;//最后调用实现函数
    pgCall->FunSets.Implementfun=p077_complete;
    //范围？？
    pgCall->FunSets.JudgeInputNumfun=p015_InputNum_InRange;
    pgCall->FunSets.RecvKeyDealfun=p010_keyDeal;

    //按左键重新输入，selfInitfun必须初始化
    pgCall->FunSets.selfInitfun=p077_initpgentry;
    if(!pgCall->FunSets.selfInitfun)
        pgCall->FunSets.selfInitfun=donothingnonepara;
    //按键是否需要Enter来确认
    pgCall->FunSets.para_rec.KeyType.runflag=FALSE;

    pgCall->FunSets.iniPagefun(&pgCall->FunSets.para_ini);
}
//清除注释
void p078_initpgentry(void)
{
    pgCall=&pgcom_callb;
    Clear_Key_CallBack(pgCall);//清除参数
    //设置必要参数
	pgCall->pgNum=78;
	SetLanguage(pgCall->pgNum,&pgcom_callb); 

    pgCall->JudegInputNumRange=TRUE;//需要判断输入数字的范围
    pgCall->HaveCursor=TRUE;
    //对应关系
    pgCall->FunSets.iniPagefun=p078_inipage;
    //对应关系
    pgCall->Calllast=FALSE;//最后调用实现函数
    pgCall->FunSets.Implementfun=p078_complete;
    //范围？？
    pgCall->FunSets.JudgeInputNumfun=p015_InputNum_InRange;
    pgCall->FunSets.RecvKeyDealfun=p010_keyDeal;

    //按左键重新输入，selfInitfun必须初始化
    pgCall->FunSets.selfInitfun=p078_initpgentry;
    if(!pgCall->FunSets.selfInitfun)
        pgCall->FunSets.selfInitfun=donothingnonepara;
    //按键是否需要Enter来确认
    pgCall->FunSets.para_rec.KeyType.runflag=FALSE;

    pgCall->FunSets.iniPagefun(&pgCall->FunSets.para_ini);
}
//清除关联地址
void p081_initpgentry(void)
{
    pgCall=&pgcom_callb;
    Clear_Key_CallBack(pgCall);//清除参数
    //设置必要参数
	pgCall->pgNum=81;
	SetLanguage(pgCall->pgNum,&pgcom_callb); 
	
    pgCall->JudegInputNumRange=TRUE;//需要判断输入数字的范围
    pgCall->HaveCursor=TRUE;
    //对应关系
    pgCall->FunSets.iniPagefun=p081_inipage;
    //对应关系
    pgCall->Calllast=FALSE;//最后调用实现函数
    pgCall->FunSets.Implementfun=p081_complete;
    //范围？？
    pgCall->FunSets.JudgeInputNumfun=p015_InputNum_InRange;
    pgCall->FunSets.RecvKeyDealfun=p010_keyDeal;

    //按左键重新输入，selfInitfun必须初始化
    pgCall->FunSets.selfInitfun=p081_initpgentry;
    if(!pgCall->FunSets.selfInitfun)
        pgCall->FunSets.selfInitfun=donothingnonepara;
    //按键是否需要Enter来确认
    pgCall->FunSets.para_rec.KeyType.runflag=FALSE;

    pgCall->FunSets.iniPagefun(&pgCall->FunSets.para_ini);
}
/******************************************************************************
* 页面: // 修改1级密码
* 输入的密码用 * 显示；

* 原有密码: _ _ _
* 新设密码: _ _ _
* 再次确认: _ _ _
******************************************************************************/
void p083_initpgentry(void)
{
    pgCall=&pgcom_callb;
    Clear_Key_CallBack(pgCall);//清除参数
    //设置必要参数
    pgCall->pgNum=83;
	SetLanguage(pgCall->pgNum,&pgcom_callb); 
    //pgCall->curstartrow=STARTROW_FIG_p019;
    //pgCall->curarrayptr=&cstpos_p083[0];
    //pgCall->intputMaxnum=ARRAYSIZE(cstpos_p083);
    pgCall->JudegInputNumRange=TRUE;//需要判断输入数字的范围
    pgCall->HaveCursor=TRUE;
    //对应关系
    pgCall->hidecursor=TRUE;//光标闪烁*来表示
    pgCall->hideInputNum=TRUE;//隐藏输入的内容
    pgCall->FunSets.iniPagefun=p083_inipage;
    //对应关系
    pgCall->Calllast=FALSE;//最后调用实现函数
    pgCall->FunSets.Implementfun=p083_complete;
    //范围？？
    pgCall->FunSets.JudgeInputNumfun=p083_InputNum_InRange;
    pgCall->FunSets.RecvKeyDealfun=p010_keyDeal;

    //按左键重新输入，selfInitfun必须初始化
    pgCall->FunSets.selfInitfun=p083_initpgentry;
    if(!pgCall->FunSets.selfInitfun)
        pgCall->FunSets.selfInitfun=donothingnonepara;
    //按键是否需要Enter来确认
    pgCall->FunSets.para_rec.KeyType.runflag=FALSE;

    pgCall->FunSets.iniPagefun(&pgCall->FunSets.para_ini);
}
/******************************************************************************
* 页面: // 修改2级密码
* 输入的密码用 * 显示；

* 原有密码: _ _ _
* 新设密码: _ _ _
* 再次确认: _ _ _
******************************************************************************/
void p084_initpgentry(void)
{
    pgCall=&pgcom_callb;
    Clear_Key_CallBack(pgCall);//清除参数
    //设置必要参数
    pgCall->pgNum=84;
	SetLanguage(pgCall->pgNum,&pgcom_callb); 
    //pgCall->curstartrow=STARTROW_FIG_p019;
    //pgCall->curarrayptr=&cstpos_p083[0];
    //pgCall->intputMaxnum=ARRAYSIZE(cstpos_p083);
    pgCall->JudegInputNumRange=TRUE;//需要判断输入数字的范围
    pgCall->HaveCursor=TRUE;
    //对应关系
    pgCall->hidecursor=TRUE;//光标闪烁*来表示
    pgCall->hideInputNum=TRUE;//隐藏输入的内容
    pgCall->FunSets.iniPagefun=p084_inipage;
    //对应关系
    pgCall->Calllast=FALSE;//最后调用实现函数
    pgCall->FunSets.Implementfun=p084_complete;
    //范围？？
    pgCall->FunSets.JudgeInputNumfun=p083_InputNum_InRange;
    pgCall->FunSets.RecvKeyDealfun=p010_keyDeal;

    //按左键重新输入，selfInitfun必须初始化
    pgCall->FunSets.selfInitfun=p084_initpgentry;
    if(!pgCall->FunSets.selfInitfun)
        pgCall->FunSets.selfInitfun=donothingnonepara;
    //按键是否需要Enter来确认
    pgCall->FunSets.para_rec.KeyType.runflag=FALSE;

    pgCall->FunSets.iniPagefun(&pgCall->FunSets.para_ini);
}
/******************************************************************************
* 页面: // 显示 模拟量曲线
*  _回路_ _ _地址: _ _ _ (显示当前值)
* |
* |_________________________>
* 把当前值用一个点显示，高度对应值的大小，最大128.
* 每得到一个新的值，X轴向上右移一个显示位置；若满，从左侧开始刷新，同时把其右侧16个像素清掉；
* 看效果，视觉上不舒服可以改，比如每次得到值，用横向2个像素表示；
******************************************************************************/
void p061_initpgentry(void)
{
    pgCall=&pgcom_callb;
    Clear_Key_CallBack(pgCall);//清除参数
    //设置必要参数
    pgCall->pgNum=61;
	SetLanguage(pgCall->pgNum,&pgcom_callb); 
    //pgCall->curstartrow=STARTROW_FIG_p017;
    //pgCall->curarrayptr=&cstpos_p061[0];
    //pgCall->intputMaxnum=ARRAYSIZE(cstpos_p061);
    pgCall->JudegInputNumRange=TRUE;//需要判断输入数字的范围
    pgCall->HaveCursor=TRUE;
    //对应关系
    pgCall->FunSets.iniPagefun=p061_inipage;
    //对应关系
    pgCall->Calllast=FALSE;//最后调用实现函数
    pgCall->FunSets.Implementfun=donothing;
    //范围？？
    pgCall->FunSets.JudgeInputNumfun=p010_InputNum_InRange;
    pgCall->FunSets.RecvKeyDealfun=p010_keyDeal;

    //按左键重新输入，selfInitfun必须初始化
    pgCall->FunSets.selfInitfun=p061_initpgentry;
    if(!pgCall->FunSets.selfInitfun)
        pgCall->FunSets.selfInitfun=donothingnonepara;
    //按键是否需要Enter来确认
    pgCall->FunSets.para_rec.KeyType.runflag=FALSE;
    //测试定时功能的处理
    //需要有定时处理任务
    pgCall->ortmrflag=TRUE;//定时标志
    pgCall->FunSets.Tmrfun=p061_tmrtask;
    pgCall->FunSets.para_tmr.tmrId=8;//暂时使用，现在还没有使用
    pgCall->FunSets.para_tmr.tmrMs=100;//3s,单位为毫秒
    pgCall->FunSets.SetTmr=doTmrTaskSet;
    pgCall->FunSets.GetTmr=doTmrTaskGet;
    pgCall->FunSets.KillTmr=doTmrTaskKill;

    //是否立即执行定义还是等待再执行，默认不立即执行
//    pgCall->execTmrTaskOnOverfg=TRUE;


    pgCall->FunSets.iniPagefun(&pgCall->FunSets.para_ini);
}

void p062_initpgentry(void)
{
    pgCall=&pgcom_callb;
    Clear_Key_CallBack(pgCall);//清除参数
    //设置必要参数
    pgCall->pgNum=62;
	SetLanguage(pgCall->pgNum,&pgcom_callb); 
//    pgCall->curstartrow=STARTROW_FIG_p042;
//    pgCall->curarrayptr=&cstpos_p062[0];
//    pgCall->intputMaxnum=ARRAYSIZE(cstpos_p062);
    pgCall->JudegInputNumRange=TRUE;//需要判断输入数字的范围
    pgCall->HaveCursor=TRUE;
    //对应关系
    pgCall->FunSets.iniPagefun=p062_inipage;
    //对应关系
    pgCall->Calllast=TRUE;//最后调用实现函数
    pgCall->FunSets.Implementfun=p062_complete;
    //范围？？
    pgCall->FunSets.JudgeInputNumfun=p058_InputNum_InRange;
    pgCall->FunSets.RecvKeyDealfun=p010_keyDeal;

    //按左键重新输入，selfInitfun必须初始化
    pgCall->FunSets.selfInitfun=p062_initpgentry;
    if(!pgCall->FunSets.selfInitfun)
        pgCall->FunSets.selfInitfun=donothingnonepara;
    //按键是否需要Enter来确认
    pgCall->FunSets.para_rec.KeyType.runflag=FALSE;

    pgCall->FunSets.iniPagefun(&pgCall->FunSets.para_ini);
}
/******************************************************************************
* 页面: // 现场设备类型状态
*  	_回路_ _ _地址:
*   部件类型:
*   部件状态:
******************************************************************************/
void p063_initpgentry(void)
{
    pgCall=&pgcom_callb;
    Clear_Key_CallBack(pgCall);//清除参数
    //设置必要参数
    pgCall->pgNum=63;
	SetLanguage(pgCall->pgNum,&pgcom_callb); 
	
    //pgCall->curstartrow=STARTROW_FIG_p042;
    //pgCall->curarrayptr=&cstpos_p010[0];
    //pgCall->intputMaxnum=ARRAYSIZE(cstpos_p010);
    pgCall->JudegInputNumRange=TRUE;//需要判断输入数字的范围
    pgCall->HaveCursor=TRUE;
    //对应关系
    pgCall->FunSets.iniPagefun=p063_inipage;
    //对应关系
    pgCall->Calllast=TRUE;//最后调用实现函数
    pgCall->FunSets.Implementfun=p063_complete;
    //范围？？
    pgCall->FunSets.JudgeInputNumfun=p010_InputNum_InRange;
    pgCall->FunSets.RecvKeyDealfun=p010_keyDeal;

    //按左键重新输入，selfInitfun必须初始化
    pgCall->FunSets.selfInitfun=p063_initpgentry;
    if(!pgCall->FunSets.selfInitfun)
        pgCall->FunSets.selfInitfun=donothingnonepara;
    //按键是否需要Enter来确认
    pgCall->FunSets.para_rec.KeyType.runflag=FALSE;

    pgCall->FunSets.iniPagefun(&pgCall->FunSets.para_ini);
}
/******************************************************************************
* 页面: //
*  _回路_ _ _地址
*  十六进制数据，顺序显示； 若满，回头刷新显示，并清除其后的2个字节。
*
******************************************************************************/
void p064_initpgentry(void)
{
    pgCall=&pgcom_callb;
    Clear_Key_CallBack(pgCall);//清除参数
    //设置必要参数
    pgCall->pgNum=64;
	SetLanguage(pgCall->pgNum,&pgcom_callb); 
	
    //pgCall->curstartrow=STARTROW_FIG_p042;
    //pgCall->curarrayptr=&cstpos_p010[0];
    //pgCall->intputMaxnum=ARRAYSIZE(cstpos_p010);
    pgCall->JudegInputNumRange=TRUE;//需要判断输入数字的范围
    pgCall->HaveCursor=TRUE;
    //对应关系
    pgCall->FunSets.iniPagefun=p064_inipage;
    //对应关系
    pgCall->Calllast=TRUE;//最后调用实现函数
    pgCall->FunSets.Implementfun=p064_complete;
    //范围？？
    pgCall->FunSets.JudgeInputNumfun=p010_InputNum_InRange;
    pgCall->FunSets.RecvKeyDealfun=p010_keyDeal;

    //按左键重新输入，selfInitfun必须初始化
    pgCall->FunSets.selfInitfun=p064_initpgentry;
    if(!pgCall->FunSets.selfInitfun)
        pgCall->FunSets.selfInitfun=donothingnonepara;
    //按键是否需要Enter来确认
    pgCall->FunSets.para_rec.KeyType.runflag=FALSE;

    pgCall->FunSets.iniPagefun(&pgCall->FunSets.para_ini);
}
/******************************************************************************
* 页面: // 自检；液晶扫屏；跑马灯；扬声器按顺序几种音调。
*
******************************************************************************/
void p065_initpgentry(void)
{
    pgCall=&pgcom_callb;
    Clear_Key_CallBack(pgCall);//清除参数
    //设置必要参数
    pgCall->pgNum=65;
	SetLanguage(pgCall->pgNum,&pgcom_callb); 
	
    //对应关系
    pgCall->FunSets.iniPagefun=p065_inipage;
    //对应关系
//    pgCall->Calllast=TRUE;//最后调用实现函数
    pgCall->FunSets.Implementfun=p064_complete;
    //范围？？
//    pgCall->FunSets.JudgeInputNumfun=p010_InputNum_InRange;
//    pgCall->FunSets.RecvKeyDealfun=p010_keyDeal;

    //按左键重新输入，selfInitfun必须初始化
    pgCall->FunSets.selfInitfun=p065_initpgentry;
    if(!pgCall->FunSets.selfInitfun)
        pgCall->FunSets.selfInitfun=donothingnonepara;
    //按键是否需要Enter来确认
    pgCall->FunSets.para_rec.KeyType.runflag=FALSE;

    pgCall->FunSets.iniPagefun(&pgCall->FunSets.para_ini);
    pgCall->FunSets.Implementfun(&pgCall->FunSets.para_imp);
}
/******************************************************************************
* 页面: // 测试按键。
* 在屏幕上按照实际键盘顺序画标志；若某按键按下，则变色；
* 界面6秒无按键输入，则自动退出到菜单
******************************************************************************/
void p067_initpgentry(void)
{
    pgCall=&pgcom_callb;
    Clear_Key_CallBack(pgCall);//清除参数
    //设置必要参数
    pgCall->pgNum=67;
	SetLanguage(pgCall->pgNum,&pgcom_callb); 

    pgCall->JudegInputNumRange=TRUE;//需要判断输入数字的范围
//    pgCall->HaveCursor=TRUE;
    //对应关系
    pgCall->FunSets.iniPagefun=p067_inipage;
    //对应关系
//    pgCall->Calllast=TRUE;//最后调用实现函数
    pgCall->FunSets.Implementfun=p067_complete;
    //范围？？
//    pgCall->FunSets.JudgeInputNumfun=p010_InputNum_InRange;
//    pgCall->FunSets.RecvKeyDealfun=p010_keyDeal;

    //按左键重新输入，selfInitfun必须初始化
    pgCall->FunSets.selfInitfun=p067_initpgentry;
    if(!pgCall->FunSets.selfInitfun)
        pgCall->FunSets.selfInitfun=donothingnonepara;
    //按键是否需要Enter来确认
    pgCall->FunSets.para_rec.KeyType.runflag=FALSE;

    pgCall->FunSets.iniPagefun(&pgCall->FunSets.para_ini);
    pgCall->FunSets.Implementfun(&pgCall->FunSets.para_imp);
}
/******************************************************************************
* 页面: // 测试 通讯-iCan;
* 接收1区帧数:
* 接收2区帧数:
* 接收3区帧数:
* 接收4区帧数:
******************************************************************************/
void p072_initpgentry(void)
{
    pgCall=&pgcom_callb;
    Clear_Key_CallBack(pgCall);//清除参数
    //设置必要参数
    pgCall->pgNum=72;
	SetLanguage(pgCall->pgNum,&pgcom_callb); 

    pgCall->JudegInputNumRange=TRUE;//需要判断输入数字的范围
//    pgCall->HaveCursor=TRUE;
    //对应关系
    pgCall->FunSets.iniPagefun=p072_inipage;
    //对应关系
//    pgCall->Calllast=TRUE;//最后调用实现函数
    pgCall->FunSets.Implementfun=p072_complete;
    //范围？？
//    pgCall->FunSets.JudgeInputNumfun=p010_InputNum_InRange;
//    pgCall->FunSets.RecvKeyDealfun=p010_keyDeal;

    //按左键重新输入，selfInitfun必须初始化
    pgCall->FunSets.selfInitfun=p072_initpgentry;
    if(!pgCall->FunSets.selfInitfun)
        pgCall->FunSets.selfInitfun=donothingnonepara;
    //按键是否需要Enter来确认
    pgCall->FunSets.para_rec.KeyType.runflag=FALSE;

    pgCall->FunSets.iniPagefun(&pgCall->FunSets.para_ini);
    pgCall->FunSets.Implementfun(&pgCall->FunSets.para_imp);
}
/******************************************************************************
* 页面: // 测试 通讯-eCan;
* 接收主机帧数:
* 其他控制器若在线，显示接收帧数；
******************************************************************************/
void p073_initpgentry(void)
{
    pgCall=&pgcom_callb;
    Clear_Key_CallBack(pgCall);//清除参数
    //设置必要参数
	pgCall->pgNum=73;
	SetLanguage(pgCall->pgNum,&pgcom_callb); 
    pgCall->JudegInputNumRange=TRUE;//需要判断输入数字的范围
//    pgCall->HaveCursor=TRUE;
    //对应关系
    pgCall->FunSets.iniPagefun=p073_inipage;
    //对应关系
//    pgCall->Calllast=TRUE;//最后调用实现函数
    pgCall->FunSets.Implementfun=p073_complete;
    //范围？？
//    pgCall->FunSets.JudgeInputNumfun=p010_InputNum_InRange;
//    pgCall->FunSets.RecvKeyDealfun=p010_keyDeal;

    //按左键重新输入，selfInitfun必须初始化
    pgCall->FunSets.selfInitfun=p073_initpgentry;
    if(!pgCall->FunSets.selfInitfun)
        pgCall->FunSets.selfInitfun=donothingnonepara;
    //按键是否需要Enter来确认
    pgCall->FunSets.para_rec.KeyType.runflag=FALSE;

    pgCall->FunSets.iniPagefun(&pgCall->FunSets.para_ini);
    pgCall->FunSets.Implementfun(&pgCall->FunSets.para_imp);
}
/******************************************************************************
* 页面: // 帮助
* 暂时 显示生产厂名称
******************************************************************************/
void p011_initpgentry(void)
{
    pgCall=&pgcom_callb;
    Clear_Key_CallBack(pgCall);//清除参数
    //设置必要参数
	pgCall->pgNum=11;
	SetLanguage(pgCall->pgNum,&pgcom_callb); 
    pgCall->JudegInputNumRange=TRUE;//需要判断输入数字的范围
//    pgCall->HaveCursor=TRUE;
    //对应关系
    pgCall->FunSets.iniPagefun=p011_inipage;
    //对应关系
//    pgCall->Calllast=TRUE;//最后调用实现函数
    pgCall->FunSets.Implementfun=p011_complete;
    //范围？？
//    pgCall->FunSets.JudgeInputNumfun=p010_InputNum_InRange;
    pgCall->FunSets.RecvKeyDealfun=p010_keyDeal;//定时需要调用，定时函数在此对应中

    //按左键重新输入，selfInitfun必须初始化
    pgCall->FunSets.selfInitfun=p011_initpgentry;
    if(!pgCall->FunSets.selfInitfun)
        pgCall->FunSets.selfInitfun=donothingnonepara;
    //按键是否需要Enter来确认
    pgCall->FunSets.para_rec.KeyType.runflag=FALSE;



    //测试定时功能的处理
    //需要有定时处理任务，定时任务是在按键函数中调用的
    pgCall->overflag=TRUE;
    pgCall->execTmrTaskOnOverfg=TRUE;//因为没有按键输入
    pgCall->ortmrflag=TRUE;//定时标志
    pgCall->FunSets.Tmrfun=p011_tmrtask;
    pgCall->FunSets.para_tmr.tmrId=8;//暂时使用，现在还没有使用
    pgCall->FunSets.para_tmr.tmrMs=1000;//3s,单位为毫秒
    pgCall->FunSets.SetTmr=doTmrTaskSet;
    pgCall->FunSets.GetTmr=doTmrTaskGet;
    pgCall->FunSets.KillTmr=doTmrTaskKill;



    pgCall->FunSets.iniPagefun(&pgCall->FunSets.para_ini);
    pgCall->FunSets.Implementfun(&pgCall->FunSets.para_imp);





}
/******************************************************************************
* 页面: //查询手动自动
* 显示已登记的区的手动自动  参考 ShowStr_AutoManuNowState();
* 一区:
* 二区:
* 三区:
* 四区:
******************************************************************************/
void p059_initpgentry(void)
{
    pgCall=&pgcom_callb;
    Clear_Key_CallBack(pgCall);//清除参数
    //设置必要参数
	pgCall->pgNum=59;
	SetLanguage(pgCall->pgNum,&pgcom_callb); 
    pgCall->JudegInputNumRange=TRUE;//需要判断输入数字的范围
//    pgCall->HaveCursor=TRUE;
    //对应关系
    pgCall->FunSets.iniPagefun=p059_inipage;
    //对应关系
//    pgCall->Calllast=TRUE;//最后调用实现函数
    pgCall->FunSets.Implementfun=p059_complete;
    //范围？？
//    pgCall->FunSets.JudgeInputNumfun=p010_InputNum_InRange;
//    pgCall->FunSets.RecvKeyDealfun=p010_keyDeal;

    //按左键重新输入，selfInitfun必须初始化
    pgCall->FunSets.selfInitfun=p059_initpgentry;
    if(!pgCall->FunSets.selfInitfun)
        pgCall->FunSets.selfInitfun=donothingnonepara;
    //按键是否需要Enter来确认
    pgCall->FunSets.para_rec.KeyType.runflag=FALSE;

    pgCall->FunSets.iniPagefun(&pgCall->FunSets.para_ini);
    pgCall->FunSets.Implementfun(&pgCall->FunSets.para_imp);
}
/******************************************************************************
* 页面: // 查询历史记录-所有
*
******************************************************************************/
void p052_initpgentry(void)
{
    pgCall=&pgcom_callb;
    Clear_Key_CallBack(pgCall);//清除参数
    //设置必要参数
    pgCall->pgNum=52;
	SetLanguage(pgCall->pgNum,&pgcom_callb); 

    pgCall->JudegInputNumRange=TRUE;//需要判断输入数字的范围
//    pgCall->HaveCursor=TRUE;
    //对应关系
    pgCall->FunSets.iniPagefun=p052_inipage;
    //对应关系
//    pgCall->Calllast=TRUE;//最后调用实现函数
    pgCall->FunSets.Implementfun=p052_complete;
    //范围？？
//    pgCall->FunSets.JudgeInputNumfun=p010_InputNum_InRange;
//    pgCall->FunSets.RecvKeyDealfun=p010_keyDeal;

    //按左键重新输入，selfInitfun必须初始化
    pgCall->FunSets.selfInitfun=p052_initpgentry;
    if(!pgCall->FunSets.selfInitfun)
        pgCall->FunSets.selfInitfun=donothingnonepara;
    //按键是否需要Enter来确认
    pgCall->FunSets.para_rec.KeyType.runflag=FALSE;

    pgCall->FunSets.iniPagefun(&pgCall->FunSets.para_ini);
    pgCall->FunSets.Implementfun(&pgCall->FunSets.para_imp);
}
/******************************************************************************
* 页面: // 查询历史记录-火警
*
******************************************************************************/
void p053_initpgentry(void)
{
    pgCall=&pgcom_callb;
    Clear_Key_CallBack(pgCall);//清除参数
    //设置必要参数
    pgCall->pgNum=53;
	SetLanguage(pgCall->pgNum,&pgcom_callb); 
    pgCall->JudegInputNumRange=TRUE;//需要判断输入数字的范围
//    pgCall->HaveCursor=TRUE;
    //对应关系
    pgCall->FunSets.iniPagefun=p053_inipage;
    //对应关系
//    pgCall->Calllast=TRUE;//最后调用实现函数
    pgCall->FunSets.Implementfun=p053_complete;
    //范围？？
//    pgCall->FunSets.JudgeInputNumfun=p010_InputNum_InRange;
//    pgCall->FunSets.RecvKeyDealfun=p010_keyDeal;

    //按左键重新输入，selfInitfun必须初始化
    pgCall->FunSets.selfInitfun=p053_initpgentry;
    if(!pgCall->FunSets.selfInitfun)
        pgCall->FunSets.selfInitfun=donothingnonepara;
    //按键是否需要Enter来确认
    pgCall->FunSets.para_rec.KeyType.runflag=FALSE;

    pgCall->FunSets.iniPagefun(&pgCall->FunSets.para_ini);
    pgCall->FunSets.Implementfun(&pgCall->FunSets.para_imp);
}
/******************************************************************************
* 页面: // 查询历史记录-联动
*
******************************************************************************/
void p054_initpgentry(void)
{
    pgCall=&pgcom_callb;
    Clear_Key_CallBack(pgCall);//清除参数
    //设置必要参数
    pgCall->pgNum=54;
	SetLanguage(pgCall->pgNum,&pgcom_callb); 
    pgCall->JudegInputNumRange=TRUE;//需要判断输入数字的范围
//    pgCall->HaveCursor=TRUE;
    //对应关系
    pgCall->FunSets.iniPagefun=p054_inipage;
    //对应关系
//    pgCall->Calllast=TRUE;//最后调用实现函数
    pgCall->FunSets.Implementfun=p054_complete;
    //范围？？
//    pgCall->FunSets.JudgeInputNumfun=p010_InputNum_InRange;
//    pgCall->FunSets.RecvKeyDealfun=p010_keyDeal;

    //按左键重新输入，selfInitfun必须初始化
    pgCall->FunSets.selfInitfun=p054_initpgentry;
    if(!pgCall->FunSets.selfInitfun)
        pgCall->FunSets.selfInitfun=donothingnonepara;
    //按键是否需要Enter来确认
    pgCall->FunSets.para_rec.KeyType.runflag=FALSE;

    pgCall->FunSets.iniPagefun(&pgCall->FunSets.para_ini);
    pgCall->FunSets.Implementfun(&pgCall->FunSets.para_imp);
}
/******************************************************************************
* 页面: // 查询历史记录-故障
*
******************************************************************************/
void p055_initpgentry(void)
{
    pgCall=&pgcom_callb;
    Clear_Key_CallBack(pgCall);//清除参数
    //设置必要参数
    pgCall->pgNum=55;
	SetLanguage(pgCall->pgNum,&pgcom_callb); 
    pgCall->JudegInputNumRange=TRUE;//需要判断输入数字的范围
//    pgCall->HaveCursor=TRUE;
    //对应关系
    pgCall->FunSets.iniPagefun=p055_inipage;
    //对应关系
//    pgCall->Calllast=TRUE;//最后调用实现函数
    pgCall->FunSets.Implementfun=p055_complete;
    //范围？？
//    pgCall->FunSets.JudgeInputNumfun=p010_InputNum_InRange;
//    pgCall->FunSets.RecvKeyDealfun=p010_keyDeal;

    //按左键重新输入，selfInitfun必须初始化
    pgCall->FunSets.selfInitfun=p055_initpgentry;
    if(!pgCall->FunSets.selfInitfun)
        pgCall->FunSets.selfInitfun=donothingnonepara;
    //按键是否需要Enter来确认
    pgCall->FunSets.para_rec.KeyType.runflag=FALSE;

    pgCall->FunSets.iniPagefun(&pgCall->FunSets.para_ini);
    pgCall->FunSets.Implementfun(&pgCall->FunSets.para_imp);
}
void p056_initpgentry(void)
{
    pgCall=&pgcom_callb;
    Clear_Key_CallBack(pgCall);//清除参数
    //设置必要参数
	pgCall->pgNum=56;
	SetLanguage(pgCall->pgNum,&pgcom_callb); 
	
    pgCall->JudegInputNumRange=TRUE;//需要判断输入数字的范围
//    pgCall->HaveCursor=TRUE;
    //对应关系
    pgCall->FunSets.iniPagefun=p056_inipage;
    //对应关系
//    pgCall->Calllast=TRUE;//最后调用实现函数
    pgCall->FunSets.Implementfun=p056_complete;
    //范围？？
//    pgCall->FunSets.JudgeInputNumfun=p010_InputNum_InRange;
//    pgCall->FunSets.RecvKeyDealfun=p010_keyDeal;

    //按左键重新输入，selfInitfun必须初始化
    pgCall->FunSets.selfInitfun=p056_initpgentry;
    if(!pgCall->FunSets.selfInitfun)
        pgCall->FunSets.selfInitfun=donothingnonepara;
    //按键是否需要Enter来确认
    pgCall->FunSets.para_rec.KeyType.runflag=FALSE;

    pgCall->FunSets.iniPagefun(&pgCall->FunSets.para_ini);
    pgCall->FunSets.Implementfun(&pgCall->FunSets.para_imp);
}
void p057_initpgentry(void)
{
    pgCall=&pgcom_callb;
    Clear_Key_CallBack(pgCall);//清除参数
    //设置必要参数
    pgCall->pgNum=57;
	SetLanguage(pgCall->pgNum,&pgcom_callb);
    pgCall->JudegInputNumRange=TRUE;//需要判断输入数字的范围
//    pgCall->HaveCursor=TRUE;
    //对应关系
    pgCall->FunSets.iniPagefun=p057_inipage;
    //对应关系
//    pgCall->Calllast=TRUE;//最后调用实现函数
    pgCall->FunSets.Implementfun=p057_complete;
    //范围？？
//    pgCall->FunSets.JudgeInputNumfun=p010_InputNum_InRange;
//    pgCall->FunSets.RecvKeyDealfun=p010_keyDeal;

    //按左键重新输入，selfInitfun必须初始化
    pgCall->FunSets.selfInitfun=p057_initpgentry;
    if(!pgCall->FunSets.selfInitfun)
        pgCall->FunSets.selfInitfun=donothingnonepara;
    //按键是否需要Enter来确认
    pgCall->FunSets.para_rec.KeyType.runflag=FALSE;

    pgCall->FunSets.iniPagefun(&pgCall->FunSets.para_ini);
    pgCall->FunSets.Implementfun(&pgCall->FunSets.para_imp);
}
