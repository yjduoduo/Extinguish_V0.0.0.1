/*****************************************************************************
*author:魏新建
*time  :2013年 9.22~10月22日
*****************************************************************************/



#ifndef LCDPG_KEYCALL_H
#define LCDPG_KEYCALL_H

#include "prjDataType.h"

#define __KeyCall_Pg_EX
#ifdef __KeyCall_Pg_EX
#define KEYCALL_PG_EX extern
#else
#define KEYCALL_PG_EX
#endif


#include "lcdCst_PageNum.h"

#define __KeyCall_Pg

#ifdef __KeyCall_Pg

/*****************************************************************************
*FUNC:页面结构体定义，由lcdPg_InitT.c中直接调用
定义各个页面初始化、页面完成、以及页面输入判断、
页面修改、页面上下按键处理、页面停止等。
*****************************************************************************/


#define ARRAYSIZE(A) sizeof(A)/sizeof(A[0])
#define INITENTRY(A) A##_initpgentry()
#define UNINITENTRY(A) FigStop(&pgcom_callb);
//usal界面按键调用
#define KEYCALL(A) \
    if(!pgcom_callb.Used)return;\
    if(pgcom_callb.FunSets.RecvKeyDealfun(&pgcom_callb.FunSets.para_rec))\
        return;

/*定义内部函数调用*/
typedef struct _key_callbackfun key_callbackfun;
typedef struct allowKeyrun allowKeyrun;
typedef struct allowKeyrun{
    BOOL runflag;//是否允许运行
    U8 keytype;//哪个键值
}allowKeyrun;

typedef struct funpara{
    BOOL firstentry;//是否为第一次进入
    U8 fig;
    BOOL flag;
    key_callbackfun* TotalCall;
    allowKeyrun KeyType;
    U8 curRowNow;
    U8 row;//文字显示行
    U8 col;//文字显示列
    U8* str[2];//显示的文字

//定时参数
    U32 tmrMs;//定时时间
    U8 tmrId;//定时ID
    BOOL TmrTaskSetted;//定时是否已经启用,默认为FALSE，不启用
    U8 val;
    U8 PosTextN;//光标等数组的位置
}funpara;


typedef struct interFun{
    funpara para_ini;//初始化参数
    funpara para_ltp;//回路提示
    funpara para_adr;//地址提示
    funpara para_imp;//实现功能函数
    funpara para_jud;//数字输入范围判断
    funpara para_rec;//接收数字按键处理
    funpara para_tmr;//定时函数参数
    void (*iniPagefun)(funpara* para);
    void (*Looptipsfun)(funpara* para);//回路提示
    void (*Addrtipsfun)(funpara* para);//地址提示
    void (*Implementfun)(funpara* para);//实现功能函数
    BOOL (*Modifyfun)(funpara* para);//按键后修改函数
    BOOL (*KeyUpfun)(funpara* para);//按上键后
    BOOL (*KeyDownfun)(funpara* para);//按下键
    BOOL (*JudgeInputNumfun)(funpara *para);//数字输入范围判断
    BOOL (*RecvKeyDealfun)(funpara* para);//接收数字按键处理
    void (*selfInitfun)(void);//初始化本身函数
    //定时功能
    BOOL (*Tmrfun)(funpara* para);//定时函数
    BOOL (*SetTmr)(funpara* para);//设置定时
    BOOL (*GetTmr)(funpara* para);//获取定时
    BOOL (*KillTmr)(funpara* para);//杀掉定时

    U8 tipsfunflag;//是否为提示函数，或者其它
//    BOOL flag;//inputdoneflag
//    U8 exectime;//exec times
}interFun;

//callback
typedef struct _key_callbackfun{
    interFun FunSets;
    U8 curstartrow;//光标开始位置
    const U8 *curarrayptr;
    U8 intputMaxnum;//输入数字的个数
    U8 inputFig[20];//记录每次输入数字，这个范围尽可能大些，时间设置里面出现过问题，当时设置为10实际需要12
    U8 WhichPos;//输入的第几个数字
    U8 pracpos;//光标实际所在位置
    BOOL overflag;//页面退出后，重新计数
    BOOL execTmrTaskOnOverfg;//用户输入结束是否立即执行的定时内容，默认为不立即执行FALSE
    BOOL JudegInputNumRange;//是否判断输入数字的范围
    U8 KeyResponseSv;//响应按键的开始值
    U8 KeyResponseEv;//响应按键的结束值
    BOOL HaveCursor;//是否需要光标，FALSE表示没有
//    BOOL CursorChangeLine;//光标是否需要换行
    BOOL Calllast;//实现功能是否最后调用，真：最后调用，假：先前调用
    BOOL hidecursor;//默认为FALSE：不隐藏，密码等需要隐藏
    BOOL hideInputNum;//隐藏输入的内容，默认不隐藏FALSE
    //定时内容
    
    BOOL Used;//此结构体中的内容是否已经被初始化，默认为TRUE，消失为FALSE
    U8 ExecOnceNum;//使用定时时，需要对一些静态变量进行初始化为0，默认为0
	BOOL ortmrflag;//是否需要定时,默认无定时FALSE，需要定时TRUE
    U8 pgNum;//界面的位置，属于哪个界面
}key_callbackfun;

typedef struct TextPos{
    U8 pos[5];//列位置
    const U8* text[5];//各行文本
    U8 CursorRow;//光标行
    const U8* CursorArray;//光标数组
}TextPos;

//定义显示字体及位置，包括中英文
typedef struct defposText{
    U8 pgNum;//页面号
    TextPos CnPosText;//中文内容
    TextPos EnPosText;//英文内容
    U8 InputMaxnum;//输入最大值
}defposText;

// 画坐标轴：
//横坐标y值
KEYCALL_PG_EX const U8 yval[6];
KEYCALL_PG_EX const U8 yval_p061[7];
//typedef struct defposText defposText;
KEYCALL_PG_EX const defposText AllPosText[MAX_PAGE];


KEYCALL_PG_EX key_callbackfun pgcom_callb;//实现共用的结构

#endif

#define MANUACTTEXTCOLUMNPOS 50
#define STARTROW_FIG_p010 3
#define STARTROW_FIG_p017 0
#define STARTROW_FIG_p060 0
#define STARTROW_FIG_p013 3
#define STARTROW_FIG_p030 0
#define STARTROW_FIG_p058 0
#define STARTROW_FIG_p042 2
#define STARTROW_FIG_p024 2
#define STARTROW_FIG_p019 2

/*****************************************************************************
*FUNC:
*****************************************************************************/
KEYCALL_PG_EX void donothingnonepara(void);
KEYCALL_PG_EX void donothing(funpara *para);
KEYCALL_PG_EX BOOL donothingKey(funpara* para);
KEYCALL_PG_EX void Clear_Key_CallBack(key_callbackfun* callb);
/*****************************************************************************
*FUNC:
*****************************************************************************/
BOOL JudgeFigInRange(U8 fig,U8 startFig,U8 endFig);
/*****************************************************************************
*FUNC:
*****************************************************************************/
BOOL pcom_InputNum_InRange(funpara* pa);
BOOL p010_InputNum_InRange(funpara *pa);
BOOL p017_InputNum_InRange(funpara *para);
BOOL p016_InputNum_InRange_DirectExec(funpara* pa);
BOOL p013_InputNum_InRange(funpara *para);
BOOL p030_InputNum_InRange(funpara *para);
BOOL p058_InputNum_InRange(funpara* pa);
BOOL p015_InputNum_InRange(funpara* pa);
BOOL p083_InputNum_InRange(funpara* para);
BOOL p042_InputNum_InRange(funpara* pa);
/*****************************************************************************
*FUNC:
*****************************************************************************/
BOOL pg_keyDeal(U8 cursorrow,U8 *pracpos,const U8 *cstpos,U8 size,key_callbackfun* TotalCall,allowKeyrun* runF);
/*****************************************************************************
*FUNC:
*****************************************************************************/
BOOL p010_keyDeal(funpara *para);
/*****************************************************************************
*FUNC:
*****************************************************************************/
BOOL p060_keyDeal(void);
/*****************************************************************************
*FUNC:
*****************************************************************************/
KEYCALL_PG_EX void InputNum_Show_common_call(U8 cursorrow,U8 *pracpos,U8 fig,const U8 *cstpos,U8 size,key_callbackfun* TotalCall);
/*****************************************************************************
*FUNC:各个页面初始化页面
*****************************************************************************/
KEYCALL_PG_EX void p010_inipage(funpara* para);
KEYCALL_PG_EX void p011_inipage(funpara *para);
//12暂时不做
KEYCALL_PG_EX void p013_inipage(funpara *para);
//14
KEYCALL_PG_EX void p015_inipage(funpara *para);
KEYCALL_PG_EX void p016_inipage(funpara *para);
KEYCALL_PG_EX void p017_inipage(funpara *para);
KEYCALL_PG_EX void p018_inipage(funpara *para);
KEYCALL_PG_EX void p019_inipage(funpara *para);
KEYCALL_PG_EX void p020_inipage(funpara *para);
//{U_P021_P,	},	  //
//{U_P022_P,	},	  //
//{U_P023_P,},
KEYCALL_PG_EX void p024_inipage(funpara *para);
//{U_P025_P,},	  //
//{U_P026_P,},
KEYCALL_PG_EX void p027_inipage(funpara *para);
KEYCALL_PG_EX void p028_inipage(funpara *para);
//{U_P029_P,},	  //
KEYCALL_PG_EX void p030_inipage(funpara *para);
//{U_P031_P,},	  //
//{U_P032_P,},	  //
//{U_P033_P,},	  //
//{U_P034_P,},	  //
//{U_P035_P,},	  //
//{U_P036_P,},	  //
KEYCALL_PG_EX void p037_inipage(funpara *para);
KEYCALL_PG_EX void p038_inipage(funpara *para);
KEYCALL_PG_EX void p039_inipage(funpara *para);
KEYCALL_PG_EX void p040_inipage(funpara *para);
KEYCALL_PG_EX void p041_inipage(funpara *para);
KEYCALL_PG_EX void p042_inipage(funpara *para);
//{U_P043_P,},	  //
KEYCALL_PG_EX void p044_inipage(funpara *para);
//{U_P045_P,},	  //
//{U_P046_P,},	  //
KEYCALL_PG_EX void p047_inipage(funpara *para);
KEYCALL_PG_EX void p048_inipage(funpara* para);
KEYCALL_PG_EX void p049_inipage(funpara* para);
//{U_P050_P,},	  //
//{U_P051_P,},	  //

KEYCALL_PG_EX void p052_inipage(funpara *para);
KEYCALL_PG_EX void p053_inipage(funpara *para);
KEYCALL_PG_EX void p054_inipage(funpara *para);
KEYCALL_PG_EX void p055_inipage(funpara *para);
KEYCALL_PG_EX void p056_inipage(funpara *para);
KEYCALL_PG_EX void p057_inipage(funpara *para);
KEYCALL_PG_EX void p058_inipage(funpara *para);
KEYCALL_PG_EX void p059_inipage(funpara *para);
KEYCALL_PG_EX void p060_inipage(funpara* para);
KEYCALL_PG_EX void p061_inipage(funpara *para);
KEYCALL_PG_EX void p062_inipage(funpara *para);
KEYCALL_PG_EX void p063_inipage(funpara *para);
KEYCALL_PG_EX void p064_inipage(funpara *para);
KEYCALL_PG_EX void p065_inipage(funpara *para);
//{U_P066_P,},	  //
KEYCALL_PG_EX void p067_inipage(funpara *para);
//68,yx
//{U_P069_P,},	  //
//{U_P070_P,},	  //
//{U_P071_P,},	  //
KEYCALL_PG_EX void p072_inipage(funpara *para);
KEYCALL_PG_EX void p073_inipage(funpara *para);
//{U_P074_P,},	  //
//{U_P075_P,},	  //
//{U_P076_P,},	  //
KEYCALL_PG_EX void p077_inipage(funpara *para);
KEYCALL_PG_EX void p078_inipage(funpara *para);
//{U_P079_P, },	  //
KEYCALL_PG_EX void p080_inipage(funpara *para);
KEYCALL_PG_EX void p081_inipage(funpara *para);
//{U_P082_P,},	  //
KEYCALL_PG_EX void p083_inipage(funpara *para);
KEYCALL_PG_EX void p084_inipage(funpara *para);
//{U_P085_P,},	//
//{U_P086_P,	},	  //
//KEYCALL_PG_EX BOOL p030_curSS(funpara *para);
KEYCALL_PG_EX void p010_loopinputtips(funpara *para);
/*****************************************************************************
*FUNC:回路提示
*****************************************************************************/
KEYCALL_PG_EX void p010_addrinputtips(funpara *para);
/*****************************************************************************
*FUNC:输入完成后界面调用的函数
*****************************************************************************/
KEYCALL_PG_EX void p010_complete(funpara* para);
KEYCALL_PG_EX void p011_complete(funpara *para);
KEYCALL_PG_EX void p016_complete(funpara* para);
KEYCALL_PG_EX void p017_complete(funpara *para);
KEYCALL_PG_EX void p018_complete(funpara* para);
KEYCALL_PG_EX void p013_complete(funpara* para);
KEYCALL_PG_EX void pcom_complete(funpara* para);
KEYCALL_PG_EX void p041_complete(funpara* para);
KEYCALL_PG_EX void p044_complete(funpara* para);
KEYCALL_PG_EX void p042_complete(funpara* para);
KEYCALL_PG_EX void p047_complete(funpara* para);
KEYCALL_PG_EX void p048_complete(funpara* para);
KEYCALL_PG_EX void p049_complete(funpara* para);
KEYCALL_PG_EX void p058_complete(funpara *para);
KEYCALL_PG_EX void p039_complete(funpara *para);
KEYCALL_PG_EX void p024_complete(funpara* para);
KEYCALL_PG_EX void p027_complete(funpara* para);
KEYCALL_PG_EX void p015_complete(funpara* para);
KEYCALL_PG_EX void p028_complete(funpara* para);
KEYCALL_PG_EX void p080_complete(funpara *para);
KEYCALL_PG_EX void p077_complete(funpara *para);
KEYCALL_PG_EX void p078_complete(funpara *para);
KEYCALL_PG_EX void p081_complete(funpara *para);
KEYCALL_PG_EX void p083_complete(funpara *para);
KEYCALL_PG_EX void p084_complete(funpara *para);
KEYCALL_PG_EX void p060_complete(funpara *para);
KEYCALL_PG_EX void p061_complete(funpara *para);
KEYCALL_PG_EX void p062_complete(funpara *para);
KEYCALL_PG_EX void p063_complete(funpara *para);
KEYCALL_PG_EX void p064_complete(funpara *para);
KEYCALL_PG_EX void p065_complete(funpara *para);
KEYCALL_PG_EX void p067_complete(funpara *para);
KEYCALL_PG_EX void p072_complete(funpara *para);
KEYCALL_PG_EX void p073_complete(funpara *para);
KEYCALL_PG_EX void p059_complete(funpara *para);
KEYCALL_PG_EX void p052_complete(funpara *para);
KEYCALL_PG_EX void p053_complete(funpara *para);
KEYCALL_PG_EX void p054_complete(funpara *para);
KEYCALL_PG_EX void p055_complete(funpara *para);
KEYCALL_PG_EX void p056_complete(funpara *para);
KEYCALL_PG_EX void p057_complete(funpara *para);

/*****************************************************************************
*FUNC:页面修改，页面重置
*****************************************************************************/
KEYCALL_PG_EX BOOL p058_modify(funpara* para);




/*****************************************************************************
*FUNC:页面按上键、下键
*****************************************************************************/
KEYCALL_PG_EX BOOL p058_keyup(funpara* para);



KEYCALL_PG_EX BOOL p058_keydown(funpara* para);






/*****************************************************************************
*FUNC:页面定时任务
*****************************************************************************/
BOOL p011_tmrtask(funpara* para);//测试flash用定时显示数据


KEYCALL_PG_EX BOOL p061_tmrtask(funpara* para);



//设置定时
KEYCALL_PG_EX BOOL doTmrTaskSet(funpara* para);
KEYCALL_PG_EX BOOL doTmrTaskGet(funpara* para);
KEYCALL_PG_EX BOOL doTmrTaskKill(funpara* para);
/*****************************************************************************
*FUNC:界面停止，清空内容
*****************************************************************************/
KEYCALL_PG_EX void FigStop(key_callbackfun* pg);




#endif // LCDPG_KEYCALL_H
