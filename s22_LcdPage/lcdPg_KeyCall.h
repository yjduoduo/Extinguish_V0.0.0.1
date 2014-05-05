/*****************************************************************************
*author:κ�½�
*time  :2013�� 9.22~10��22��
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
*FUNC:ҳ��ṹ�嶨�壬��lcdPg_InitT.c��ֱ�ӵ���
�������ҳ���ʼ����ҳ����ɡ��Լ�ҳ�������жϡ�
ҳ���޸ġ�ҳ�����°�������ҳ��ֹͣ�ȡ�
*****************************************************************************/


#define ARRAYSIZE(A) sizeof(A)/sizeof(A[0])
#define INITENTRY(A) A##_initpgentry()
#define UNINITENTRY(A) FigStop(&pgcom_callb);
//usal���水������
#define KEYCALL(A) \
    if(!pgcom_callb.Used)return;\
    if(pgcom_callb.FunSets.RecvKeyDealfun(&pgcom_callb.FunSets.para_rec))\
        return;

/*�����ڲ���������*/
typedef struct _key_callbackfun key_callbackfun;
typedef struct allowKeyrun allowKeyrun;
typedef struct allowKeyrun{
    BOOL runflag;//�Ƿ���������
    U8 keytype;//�ĸ���ֵ
}allowKeyrun;

typedef struct funpara{
    BOOL firstentry;//�Ƿ�Ϊ��һ�ν���
    U8 fig;
    BOOL flag;
    key_callbackfun* TotalCall;
    allowKeyrun KeyType;
    U8 curRowNow;
    U8 row;//������ʾ��
    U8 col;//������ʾ��
    U8* str[2];//��ʾ������

//��ʱ����
    U32 tmrMs;//��ʱʱ��
    U8 tmrId;//��ʱID
    BOOL TmrTaskSetted;//��ʱ�Ƿ��Ѿ�����,Ĭ��ΪFALSE��������
    U8 val;
    U8 PosTextN;//���������λ��
}funpara;


typedef struct interFun{
    funpara para_ini;//��ʼ������
    funpara para_ltp;//��·��ʾ
    funpara para_adr;//��ַ��ʾ
    funpara para_imp;//ʵ�ֹ��ܺ���
    funpara para_jud;//�������뷶Χ�ж�
    funpara para_rec;//�������ְ�������
    funpara para_tmr;//��ʱ��������
    void (*iniPagefun)(funpara* para);
    void (*Looptipsfun)(funpara* para);//��·��ʾ
    void (*Addrtipsfun)(funpara* para);//��ַ��ʾ
    void (*Implementfun)(funpara* para);//ʵ�ֹ��ܺ���
    BOOL (*Modifyfun)(funpara* para);//�������޸ĺ���
    BOOL (*KeyUpfun)(funpara* para);//���ϼ���
    BOOL (*KeyDownfun)(funpara* para);//���¼�
    BOOL (*JudgeInputNumfun)(funpara *para);//�������뷶Χ�ж�
    BOOL (*RecvKeyDealfun)(funpara* para);//�������ְ�������
    void (*selfInitfun)(void);//��ʼ��������
    //��ʱ����
    BOOL (*Tmrfun)(funpara* para);//��ʱ����
    BOOL (*SetTmr)(funpara* para);//���ö�ʱ
    BOOL (*GetTmr)(funpara* para);//��ȡ��ʱ
    BOOL (*KillTmr)(funpara* para);//ɱ����ʱ

    U8 tipsfunflag;//�Ƿ�Ϊ��ʾ��������������
//    BOOL flag;//inputdoneflag
//    U8 exectime;//exec times
}interFun;

//callback
typedef struct _key_callbackfun{
    interFun FunSets;
    U8 curstartrow;//��꿪ʼλ��
    const U8 *curarrayptr;
    U8 intputMaxnum;//�������ֵĸ���
    U8 inputFig[20];//��¼ÿ���������֣������Χ�����ܴ�Щ��ʱ������������ֹ����⣬��ʱ����Ϊ10ʵ����Ҫ12
    U8 WhichPos;//����ĵڼ�������
    U8 pracpos;//���ʵ������λ��
    BOOL overflag;//ҳ���˳������¼���
    BOOL execTmrTaskOnOverfg;//�û���������Ƿ�����ִ�еĶ�ʱ���ݣ�Ĭ��Ϊ������ִ��FALSE
    BOOL JudegInputNumRange;//�Ƿ��ж��������ֵķ�Χ
    U8 KeyResponseSv;//��Ӧ�����Ŀ�ʼֵ
    U8 KeyResponseEv;//��Ӧ�����Ľ���ֵ
    BOOL HaveCursor;//�Ƿ���Ҫ��꣬FALSE��ʾû��
//    BOOL CursorChangeLine;//����Ƿ���Ҫ����
    BOOL Calllast;//ʵ�ֹ����Ƿ������ã��棺�����ã��٣���ǰ����
    BOOL hidecursor;//Ĭ��ΪFALSE�������أ��������Ҫ����
    BOOL hideInputNum;//������������ݣ�Ĭ�ϲ�����FALSE
    //��ʱ����
    
    BOOL Used;//�˽ṹ���е������Ƿ��Ѿ�����ʼ����Ĭ��ΪTRUE����ʧΪFALSE
    U8 ExecOnceNum;//ʹ�ö�ʱʱ����Ҫ��һЩ��̬�������г�ʼ��Ϊ0��Ĭ��Ϊ0
	BOOL ortmrflag;//�Ƿ���Ҫ��ʱ,Ĭ���޶�ʱFALSE����Ҫ��ʱTRUE
    U8 pgNum;//�����λ�ã������ĸ�����
}key_callbackfun;

typedef struct TextPos{
    U8 pos[5];//��λ��
    const U8* text[5];//�����ı�
    U8 CursorRow;//�����
    const U8* CursorArray;//�������
}TextPos;

//������ʾ���弰λ�ã�������Ӣ��
typedef struct defposText{
    U8 pgNum;//ҳ���
    TextPos CnPosText;//��������
    TextPos EnPosText;//Ӣ������
    U8 InputMaxnum;//�������ֵ
}defposText;

// �������᣺
//������yֵ
KEYCALL_PG_EX const U8 yval[6];
KEYCALL_PG_EX const U8 yval_p061[7];
//typedef struct defposText defposText;
KEYCALL_PG_EX const defposText AllPosText[MAX_PAGE];


KEYCALL_PG_EX key_callbackfun pgcom_callb;//ʵ�ֹ��õĽṹ

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
*FUNC:����ҳ���ʼ��ҳ��
*****************************************************************************/
KEYCALL_PG_EX void p010_inipage(funpara* para);
KEYCALL_PG_EX void p011_inipage(funpara *para);
//12��ʱ����
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
*FUNC:��·��ʾ
*****************************************************************************/
KEYCALL_PG_EX void p010_addrinputtips(funpara *para);
/*****************************************************************************
*FUNC:������ɺ������õĺ���
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
*FUNC:ҳ���޸ģ�ҳ������
*****************************************************************************/
KEYCALL_PG_EX BOOL p058_modify(funpara* para);




/*****************************************************************************
*FUNC:ҳ�水�ϼ����¼�
*****************************************************************************/
KEYCALL_PG_EX BOOL p058_keyup(funpara* para);



KEYCALL_PG_EX BOOL p058_keydown(funpara* para);






/*****************************************************************************
*FUNC:ҳ�涨ʱ����
*****************************************************************************/
BOOL p011_tmrtask(funpara* para);//����flash�ö�ʱ��ʾ����


KEYCALL_PG_EX BOOL p061_tmrtask(funpara* para);



//���ö�ʱ
KEYCALL_PG_EX BOOL doTmrTaskSet(funpara* para);
KEYCALL_PG_EX BOOL doTmrTaskGet(funpara* para);
KEYCALL_PG_EX BOOL doTmrTaskKill(funpara* para);
/*****************************************************************************
*FUNC:����ֹͣ���������
*****************************************************************************/
KEYCALL_PG_EX void FigStop(key_callbackfun* pg);




#endif // LCDPG_KEYCALL_H
