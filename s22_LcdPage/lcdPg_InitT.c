
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
//λ�ú�����
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
    case U_Chinese_LANGUAGE://���ù�꼰����
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


//�ֶ���ͣ�豸
void p010_initpgentry(void)
{
    pgCall=&pgcom_callb;
    Clear_Key_CallBack(pgCall);//�������
    //���ñ�Ҫ����

    pgCall->pgNum=10;
    SetLanguage(pgCall->pgNum,&pgcom_callb);
    pgCall->JudegInputNumRange=TRUE;//��Ҫ�ж��������ֵķ�Χ
    pgCall->HaveCursor=TRUE;
    //��Ӧ��ϵ
    pgCall->FunSets.iniPagefun=p010_inipage;
    pgCall->FunSets.para_ltp.flag=TRUE;
    pgCall->FunSets.Looptipsfun=p010_loopinputtips;
    pgCall->FunSets.Addrtipsfun=p010_addrinputtips;
    pgCall->FunSets.Implementfun=p010_complete;
    pgCall->FunSets.JudgeInputNumfun=p010_InputNum_InRange;
    pgCall->FunSets.RecvKeyDealfun=p010_keyDeal;

    //�����Ƿ���ҪEnter��ȷ��
    pgCall->FunSets.para_rec.KeyType.runflag=FALSE;
//    pgCall->FunSets.para_rec.KeyType.keytype=U_KEY_Enter;

    //��ʼ��
    pgCall->FunSets.iniPagefun(&pgCall->FunSets.para_ini);
//    ��·��Ϣ��ʾ
    //��һ����Ҫ��ʾ

    pgCall->FunSets.Looptipsfun(&pgCall->FunSets.para_ltp);
}

void p060_initpgentry(void)
{
    pgCall=&pgcom_callb;
    Clear_Key_CallBack(pgCall);//�������
    //���ñ�Ҫ����
    pgCall->pgNum=60;
    SetLanguage(pgCall->pgNum,&pgcom_callb);

    pgCall->JudegInputNumRange=TRUE;//��Ҫ�ж��������ֵķ�Χ
    pgCall->HaveCursor=TRUE;
    //��Ӧ��ϵ
    pgCall->FunSets.iniPagefun=p060_inipage;
//    pgCall->FunSets.Looptipsfun=p010_loopinputtips;
//    pgCall->FunSets.Addrtipsfun=p010_addrinputtips;
    pgCall->FunSets.Implementfun=p060_complete;
    pgCall->FunSets.JudgeInputNumfun=p010_InputNum_InRange;
    pgCall->FunSets.RecvKeyDealfun=p010_keyDeal;
    //�����Ƿ���ҪEnter��ȷ��
    pgCall->FunSets.para_rec.KeyType.runflag=TRUE;
    pgCall->FunSets.para_rec.KeyType.keytype=U_KEY_Enter;

    pgCall->FunSets.iniPagefun(&pgCall->FunSets.para_ini);

}
//�Զ��Ǽǣ�ֱ��ʵ�ּ���
void p016_initpgentry(void)
{
    pgCall=&pgcom_callb;
    Clear_Key_CallBack(pgCall);//�������
    //���ñ�Ҫ����
    pgCall->pgNum=16;
    SetLanguage(pgCall->pgNum,&pgcom_callb);

    //��Ӧ��ϵ
    pgCall->FunSets.iniPagefun=p016_inipage;
    pgCall->FunSets.Implementfun=p016_complete;
    pgCall->FunSets.para_imp.fig=0;

    pgCall->FunSets.iniPagefun(&pgCall->FunSets.para_ini);
    pgCall->FunSets.Implementfun(&pgCall->FunSets.para_imp);

}

//�ֶ��Ǽ�
void p017_initpgentry(void)
{
    pgCall=&pgcom_callb;
    Clear_Key_CallBack(pgCall);//�������
    //���ñ�Ҫ����
    
    pgCall->pgNum=17;
    SetLanguage(pgCall->pgNum,&pgcom_callb);
    
    pgCall->JudegInputNumRange=TRUE;//��Ҫ�ж��������ֵķ�Χ
    pgCall->HaveCursor=TRUE;
    //��Ӧ��ϵ
    pgCall->FunSets.iniPagefun=p017_inipage;
    pgCall->FunSets.Implementfun=p017_complete;

    pgCall->FunSets.JudgeInputNumfun=p017_InputNum_InRange;
    pgCall->FunSets.RecvKeyDealfun=p010_keyDeal;
    //�����Ƿ���ҪEnter��ȷ��
    pgCall->FunSets.para_rec.KeyType.runflag=TRUE;
    pgCall->FunSets.para_rec.KeyType.keytype=U_KEY_Enter;

    pgCall->FunSets.iniPagefun(&pgCall->FunSets.para_ini);

}
//�ֶ�����
void p018_initpgentry(void)
{
    pgCall=&pgcom_callb;
    Clear_Key_CallBack(pgCall);//�������
    //��Ӧ��ϵ
    pgCall->FunSets.iniPagefun=p018_inipage;
    pgCall->FunSets.Implementfun=p018_complete;

    pgCall->FunSets.JudgeInputNumfun=p017_InputNum_InRange;
    pgCall->FunSets.RecvKeyDealfun=p010_keyDeal;
    //���ñ�Ҫ����
	pgCall->pgNum=18;
    SetLanguage(pgCall->pgNum,&pgcom_callb);
	
    pgCall->JudegInputNumRange=TRUE;//��Ҫ�ж��������ֵķ�Χ
    pgCall->HaveCursor=TRUE;

    //�����Ƿ���ҪEnter��ȷ��
    pgCall->FunSets.para_rec.KeyType.runflag=TRUE;
    pgCall->FunSets.para_rec.KeyType.keytype=U_KEY_Enter;

    pgCall->FunSets.iniPagefun(&pgCall->FunSets.para_ini);
}
//ʱ������
void p013_initpgentry(void)
{
    pgCall=&pgcom_callb;
    Clear_Key_CallBack(pgCall);//�������
    //��Ӧ��ϵ
    pgCall->FunSets.iniPagefun=p013_inipage;
    pgCall->FunSets.Implementfun=p013_complete;

    pgCall->FunSets.JudgeInputNumfun=p013_InputNum_InRange;
    pgCall->FunSets.RecvKeyDealfun=p010_keyDeal;
    //���ñ�Ҫ����
	pgCall->pgNum=13;
    SetLanguage(pgCall->pgNum,&pgcom_callb);

	
    pgCall->JudegInputNumRange=TRUE;//��Ҫ�ж��������ֵķ�Χ
    pgCall->HaveCursor=TRUE;
    //�����Ƿ���ҪEnter��ȷ��
    pgCall->FunSets.para_rec.KeyType.runflag=FALSE;
//    pgCall->FunSets.para_rec.KeyType.keytype=U_KEY_Enter;

    pgCall->FunSets.iniPagefun(&pgCall->FunSets.para_ini);


}
//���������
void p030_initpgentry(void)
{
    pgCall=&pgcom_callb;
    Clear_Key_CallBack(pgCall);//�������
    //��Ӧ��ϵ



    pgCall->FunSets.para_imp.str[0]="���óɹ�";
    pgCall->FunSets.para_imp.str[1]="����ȡ��";
    pgCall->FunSets.para_imp.row=8;
    pgCall->FunSets.para_imp.col=22;
    pgCall->FunSets.iniPagefun=p030_inipage;
    pgCall->FunSets.Implementfun=pcom_complete;

    pgCall->FunSets.JudgeInputNumfun=p030_InputNum_InRange;
    pgCall->FunSets.RecvKeyDealfun=p010_keyDeal;
    //���ñ�Ҫ����

//    pgCall->curstartrow=STARTROW_FIG_p030;
//    pgCall->curarrayptr=&cstpos_p030[0];
//    pgCall->intputMaxnum=ARRAYSIZE(cstpos_p030);

    pgCall->pgNum=30;
    SetLanguage(pgCall->pgNum,&pgcom_callb);

    pgCall->JudegInputNumRange=TRUE;//��Ҫ�ж��������ֵķ�Χ
    pgCall->HaveCursor=TRUE;
    //�����Ƿ���ҪEnter��ȷ��
    pgCall->FunSets.para_rec.KeyType.runflag=FALSE;
//    pgCall->FunSets.para_rec.KeyType.keytype=U_KEY_Enter;

    pgCall->FunSets.iniPagefun(&pgCall->FunSets.para_ini);
}

//����ѡ��
void p037_initpgentry(void)
{
    pgCall=&pgcom_callb;
    Clear_Key_CallBack(pgCall);//�������

	
    pgCall->pgNum=37;
    SetLanguage(pgCall->pgNum,&pgcom_callb);
    //��Ӧ��ϵ
    pgCall->FunSets.para_imp.str[0]="�������ĳɹ�";
    pgCall->FunSets.para_imp.str[1]="����Ӣ�ĳɹ�";
    pgCall->FunSets.para_imp.row=8;
    pgCall->FunSets.para_imp.col=8;
    pgCall->FunSets.iniPagefun=p037_inipage;
    pgCall->FunSets.Implementfun=pcom_complete;

    pgCall->FunSets.RecvKeyDealfun=p010_keyDeal;
    //���ñ�Ҫ����
    pgCall->JudegInputNumRange=TRUE;//��Ҫ�ж��������ֵķ�Χ
    pgCall->HaveCursor=FALSE;
    //�����Ƿ���ҪEnter��ȷ��
    pgCall->FunSets.para_rec.KeyType.runflag=FALSE;
    //    pgCall->FunSets.para_rec.KeyType.keytype=U_KEY_Enter;

    pgCall->FunSets.iniPagefun(&pgCall->FunSets.para_ini);

}
//����ģʽ
void p038_initpgentry(void)
{
    pgCall=&pgcom_callb;
    Clear_Key_CallBack(pgCall);//�������
    
    pgCall->pgNum=38;
    SetLanguage(pgCall->pgNum,&pgcom_callb);
    //��Ӧ��ϵ
    pgCall->FunSets.para_imp.str[0]="��������ģʽ�ɹ�";
    pgCall->FunSets.para_imp.str[1]="���õ���ģʽ�ɹ�";
    pgCall->FunSets.para_imp.row=8;
    pgCall->FunSets.para_imp.col=12;
    pgCall->FunSets.iniPagefun=p038_inipage;
    pgCall->FunSets.Implementfun=pcom_complete;

    pgCall->FunSets.RecvKeyDealfun=p010_keyDeal;
    //���ñ�Ҫ����
    pgCall->JudegInputNumRange=TRUE;//��Ҫ�ж��������ֵķ�Χ
    pgCall->HaveCursor=FALSE;
    //�����Ƿ���ҪEnter��ȷ��
    pgCall->FunSets.para_rec.KeyType.runflag=FALSE;
    //    pgCall->FunSets.para_rec.KeyType.keytype=U_KEY_Enter;

    pgCall->FunSets.iniPagefun(&pgCall->FunSets.para_ini);

}
//������Ϣ
void p041_initpgentry(void)
{
    pgCall=&pgcom_callb;
    Clear_Key_CallBack(pgCall);//�������
    pgCall->pgNum=41;
    SetLanguage(pgCall->pgNum,&pgcom_callb);
    //��Ӧ��ϵ
    pgCall->FunSets.iniPagefun=p041_inipage;
    pgCall->FunSets.Implementfun=p041_complete;
//û�а����ĺ�������Ҫֱ�ӵ�����Ӧ����
    pgCall->FunSets.iniPagefun(&pgCall->FunSets.para_ini);
    pgCall->FunSets.Implementfun(NULL);
}
//������Ϣ
void p040_initpgentry(void)
{
    pgCall=&pgcom_callb;
    Clear_Key_CallBack(pgCall);//�������
    pgCall->pgNum=40;
    SetLanguage(pgCall->pgNum,&pgcom_callb);
    //��Ӧ��ϵ
    pgCall->FunSets.iniPagefun=p040_inipage;
    pgCall->FunSets.Implementfun=p041_complete;
//û�а����ĺ�������Ҫֱ�ӵ�����Ӧ����
    pgCall->FunSets.iniPagefun(&pgCall->FunSets.para_ini);
    pgCall->FunSets.Implementfun(NULL);
}
//��ѯ����ע��
void p044_initpgentry(void)
{
    pgCall=&pgcom_callb;
    Clear_Key_CallBack(pgCall);//�������
    //���ñ�Ҫ����
    pgCall->pgNum=44;
    SetLanguage(pgCall->pgNum,&pgcom_callb);
    pgCall->JudegInputNumRange=TRUE;//��Ҫ�ж��������ֵķ�Χ
    pgCall->HaveCursor=TRUE;
    //��Ӧ��ϵ
    pgCall->FunSets.iniPagefun=p044_inipage;
    //��Ӧ��ϵ
    pgCall->Calllast=TRUE;//������ʵ�ֺ���
    pgCall->FunSets.Implementfun=p044_complete;
    pgCall->FunSets.JudgeInputNumfun=p042_InputNum_InRange;
    pgCall->FunSets.RecvKeyDealfun=p010_keyDeal;
    //�����Ƿ���ҪEnter��ȷ��
    pgCall->FunSets.para_rec.KeyType.runflag=FALSE;
    pgCall->FunSets.iniPagefun(&pgCall->FunSets.para_ini);
}
//��ѯ����ģʽ
void p039_initpgentry(void)
{
    pgCall=&pgcom_callb;
    Clear_Key_CallBack(pgCall);//�������
    pgCall->pgNum=39;
    SetLanguage(pgCall->pgNum,&pgcom_callb);
    //��Ӧ��ϵ
    pgCall->FunSets.iniPagefun=p039_inipage;
    pgCall->FunSets.Implementfun=p039_complete;
//û�а����ĺ�������Ҫֱ�ӵ�����Ӧ����
    pgCall->FunSets.iniPagefun(&pgCall->FunSets.para_ini);
    pgCall->FunSets.Implementfun(NULL);
}
//��ѯ���ߵǼǵ�ַ
//ֱ����ʾ,�������ּ���ʾ
//directshow
void p058_initpgentry(void)
{
    pgCall=&pgcom_callb;
    Clear_Key_CallBack(pgCall);//�������
    //���ñ�Ҫ����
    pgCall->pgNum=58;
    SetLanguage(pgCall->pgNum,&pgcom_callb);
  //  pgCall->curstartrow=STARTROW_FIG_p058;
   // pgCall->curarrayptr=&cstpos_p058[0];
   // pgCall->intputMaxnum=ARRAYSIZE(cstpos_p058);
    pgCall->JudegInputNumRange=TRUE;//��Ҫ�ж��������ֵķ�Χ
    pgCall->HaveCursor=TRUE;
    //��Ӧ��ϵ
    pgCall->FunSets.iniPagefun=p058_inipage;
    //��Ӧ��ϵ
    pgCall->Calllast=TRUE;//������ʵ�ֺ���
//    pgCall->FunSets.para_imp.str[0]="���óɹ�";
//    pgCall->FunSets.para_imp.str[1]="����ʧ��";
//    pgCall->FunSets.para_imp.row=8;
//    pgCall->FunSets.para_imp.col=12;
    pgCall->FunSets.Implementfun=p058_complete;
    pgCall->FunSets.JudgeInputNumfun=p058_InputNum_InRange;
    pgCall->FunSets.RecvKeyDealfun=p010_keyDeal;
    //������������룬selfInitfun�����ʼ��
    pgCall->FunSets.Modifyfun=p058_modify;
    pgCall->FunSets.selfInitfun=p058_initpgentry;
    if(!pgCall->FunSets.selfInitfun)
        pgCall->FunSets.selfInitfun=donothingnonepara;
    pgCall->KeyResponseSv=1;
    pgCall->KeyResponseEv=4;
    pgCall->FunSets.KeyUpfun=p058_keyup;
    pgCall->FunSets.KeyDownfun=p058_keydown;
    //�����Ƿ���ҪEnter��ȷ��
    pgCall->FunSets.para_rec.KeyType.runflag=FALSE;
//    pgCall->FunSets.para_rec.KeyType.keytype=U_KEY_Enter;

    pgCall->FunSets.iniPagefun(&pgCall->FunSets.para_ini);
}
//��ѯ�������
void p042_initpgentry(void)
{
    pgCall=&pgcom_callb;
    Clear_Key_CallBack(pgCall);//�������
    //���ñ�Ҫ����
    pgCall->pgNum=42;
    SetLanguage(pgCall->pgNum,&pgcom_callb);
	
    //pgCall->curstartrow=STARTROW_FIG_p042;
    //pgCall->curarrayptr=&cstpos_p010[0];
    //pgCall->intputMaxnum=ARRAYSIZE(cstpos_p010);
    pgCall->JudegInputNumRange=TRUE;//��Ҫ�ж��������ֵķ�Χ
    pgCall->HaveCursor=TRUE;
    //��Ӧ��ϵ
    pgCall->FunSets.iniPagefun=p042_inipage;
    //��Ӧ��ϵ
    pgCall->Calllast=TRUE;//������ʵ�ֺ���
    pgCall->FunSets.Implementfun=p042_complete;
    pgCall->FunSets.JudgeInputNumfun=p042_InputNum_InRange;
    pgCall->FunSets.RecvKeyDealfun=p010_keyDeal;
    //�����Ƿ���ҪEnter��ȷ��
    pgCall->FunSets.para_rec.KeyType.runflag=FALSE;

    pgCall->FunSets.iniPagefun(&pgCall->FunSets.para_ini);
}
//��ѯ����汾��Ϣ
void p047_initpgentry(void)
{
    pgCall=&pgcom_callb;
    Clear_Key_CallBack(pgCall);//�������
    pgCall->pgNum=47;
    SetLanguage(pgCall->pgNum,&pgcom_callb);
	    
    //���ñ�Ҫ����
    pgCall->JudegInputNumRange=TRUE;//��Ҫ�ж��������ֵķ�Χ
    //��Ӧ��ϵ
    pgCall->FunSets.iniPagefun=p047_inipage;
    //��Ӧ��ϵ
    pgCall->FunSets.Implementfun=p047_complete;

    pgCall->FunSets.iniPagefun(&pgCall->FunSets.para_ini);
    pgCall->FunSets.Implementfun(&pgCall->FunSets.para_imp);
}

//��ѯ����������
void p049_initpgentry(void)
{
    pgCall=&pgcom_callb;
    Clear_Key_CallBack(pgCall);//�������
    pgCall->pgNum=49;
    SetLanguage(pgCall->pgNum,&pgcom_callb);
    //���ñ�Ҫ����
    pgCall->JudegInputNumRange=TRUE;//��Ҫ�ж��������ֵķ�Χ
    //��Ӧ��ϵ
    pgCall->FunSets.iniPagefun=p049_inipage;
    //��Ӧ��ϵ
    pgCall->FunSets.Implementfun=p049_complete;

    pgCall->FunSets.iniPagefun(&pgCall->FunSets.para_ini);
    pgCall->FunSets.Implementfun(&pgCall->FunSets.para_imp);
}
//��ѯ���������
void p048_initpgentry(void)
{
    pgCall=&pgcom_callb;
    Clear_Key_CallBack(pgCall);//�������
    pgCall->pgNum=48;
    SetLanguage(pgCall->pgNum,&pgcom_callb);
    //���ñ�Ҫ����
    pgCall->JudegInputNumRange=TRUE;//��Ҫ�ж��������ֵķ�Χ
    pgCall->HaveCursor=FALSE;
    //��Ӧ��ϵ
    pgCall->FunSets.iniPagefun=p048_inipage;
    //��Ӧ��ϵ
    pgCall->FunSets.Implementfun=p048_complete;

    pgCall->FunSets.iniPagefun(&pgCall->FunSets.para_ini);
    pgCall->FunSets.Implementfun(&pgCall->FunSets.para_imp);
}
//��������������
/*
* ҳ��: //��������������
* 	������ַ: _ _
*	������ַ: _ _
*/
void p024_initpgentry(void)
{
    pgCall=&pgcom_callb;
    Clear_Key_CallBack(pgCall);//�������
    //���ñ�Ҫ����
    pgCall->pgNum=24;
    SetLanguage(pgCall->pgNum,&pgcom_callb);
    //pgCall->curstartrow=STARTROW_FIG_p024;
    //pgCall->curarrayptr=&cstpos_p024[0];
    //pgCall->intputMaxnum=ARRAYSIZE(cstpos_p024);
    pgCall->JudegInputNumRange=TRUE;//��Ҫ�ж��������ֵķ�Χ
    pgCall->HaveCursor=TRUE;
    //��Ӧ��ϵ
    pgCall->FunSets.iniPagefun=p024_inipage;
    //��Ӧ��ϵ
    pgCall->Calllast=TRUE;//������ʵ�ֺ���
    pgCall->FunSets.Implementfun=p024_complete;
    //��Χ����
    pgCall->FunSets.JudgeInputNumfun=pcom_InputNum_InRange;
    pgCall->FunSets.RecvKeyDealfun=p010_keyDeal;

//    pgCall->FunSets.Modifyfun=p058_modify;
    //������������룬selfInitfun�����ʼ��
    pgCall->FunSets.selfInitfun=p024_initpgentry;
    if(!pgCall->FunSets.selfInitfun)
        pgCall->FunSets.selfInitfun=donothingnonepara;
//    pgCall->KeyResponseSv=1;
//    pgCall->KeyResponseEv=4;
//    pgCall->FunSets.KeyUpfun=p058_keyup;
//    pgCall->FunSets.KeyDownfun=p058_keydown;
    //�����Ƿ���ҪEnter��ȷ��
    pgCall->FunSets.para_rec.KeyType.runflag=FALSE;
//    pgCall->FunSets.para_rec.KeyType.keytype=U_KEY_Enter;

    pgCall->FunSets.iniPagefun(&pgCall->FunSets.para_ini);
}
/******************************************************************************
* ҳ��: //���ñ���������ַ
* 	_ _��_ _��·_ _ _��ַ ~ _ _ _��ַ
*	key: ���  key:ɾ��  key:�鿴���й���
* �鿴���й������� P028_QrAddrRelation ����һ�����棬�����û�Ȩ�޲�ͬ��
* ���Թ����Ӻ�����
******************************************************************************/
void p027_initpgentry(void)
{
    pgCall=&pgcom_callb;
    Clear_Key_CallBack(pgCall);//�������
    //���ñ�Ҫ����
    pgCall->pgNum=27;
    SetLanguage(pgCall->pgNum,&pgcom_callb);
	
    //pgCall->curstartrow=STARTROW_FIG_p024;
    //pgCall->curarrayptr=&cstpos_p027[0];
    //pgCall->intputMaxnum=ARRAYSIZE(cstpos_p027);
    pgCall->JudegInputNumRange=TRUE;//��Ҫ�ж��������ֵķ�Χ
    pgCall->HaveCursor=TRUE;
    //��Ӧ��ϵ
    pgCall->FunSets.iniPagefun=p027_inipage;
    //��Ӧ��ϵ
    pgCall->Calllast=TRUE;//������ʵ�ֺ���
    pgCall->FunSets.Implementfun=p027_complete;
    //��Χ����
    pgCall->FunSets.JudgeInputNumfun=pcom_InputNum_InRange;
    pgCall->FunSets.RecvKeyDealfun=p010_keyDeal;

    //������������룬selfInitfun�����ʼ��
    pgCall->FunSets.selfInitfun=p027_initpgentry;
    if(!pgCall->FunSets.selfInitfun)
        pgCall->FunSets.selfInitfun=donothingnonepara;
    //�����Ƿ���ҪEnter��ȷ��
    pgCall->FunSets.para_rec.KeyType.runflag=FALSE;

    pgCall->FunSets.iniPagefun(&pgCall->FunSets.para_ini);
}
/******************************************************************************
* ҳ��: // �ָ�Ĭ������
* 	�ָ�Ĭ�����ã�
*	  key:��   key:�˳�
*
******************************************************************************/
void p015_initpgentry(void)
{
    pgCall=&pgcom_callb;
    Clear_Key_CallBack(pgCall);//�������
    pgCall->pgNum=15;
    SetLanguage(pgCall->pgNum,&pgcom_callb);    
    //���ñ�Ҫ����
/*    pgCall->curstartrow=STARTROW_FIG_p024;
    pgCall->curarrayptr=&cstpos_p027[0];
    pgCall->intputMaxnum=ARRAYSIZE(cstpos_p027)*/;
    pgCall->JudegInputNumRange=TRUE;//��Ҫ�ж��������ֵķ�Χ
    pgCall->HaveCursor=TRUE;
    //��Ӧ��ϵ
    pgCall->FunSets.iniPagefun=p015_inipage;
    //��Ӧ��ϵ
    pgCall->Calllast=FALSE;//������ʵ�ֺ���
    pgCall->FunSets.Implementfun=p015_complete;
    //��Χ����
    pgCall->FunSets.JudgeInputNumfun=p015_InputNum_InRange;
    pgCall->FunSets.RecvKeyDealfun=p010_keyDeal;

    //������������룬selfInitfun�����ʼ��
    pgCall->FunSets.selfInitfun=p015_initpgentry;
    if(!pgCall->FunSets.selfInitfun)
        pgCall->FunSets.selfInitfun=donothingnonepara;
    //�����Ƿ���ҪEnter��ȷ��
    pgCall->FunSets.para_rec.KeyType.runflag=FALSE;

    pgCall->FunSets.iniPagefun(&pgCall->FunSets.para_ini);
}
/******************************************************************************
* ҳ��: // �ֶ�ע��
*      _��·_ _��ַ
* 	ע������: ע��������ʱ�Ӻ���
*
******************************************************************************/
void p019_initpgentry(void)
{
    pgCall=&pgcom_callb;
    Clear_Key_CallBack(pgCall);//�������
    //���ñ�Ҫ����
    pgCall->pgNum=19;
    SetLanguage(pgCall->pgNum,&pgcom_callb);  
    //pgCall->curstartrow=STARTROW_FIG_p019;
    //pgCall->curarrayptr=&cstpos_p010[0];
    //pgCall->intputMaxnum=ARRAYSIZE(cstpos_p010);
    pgCall->JudegInputNumRange=TRUE;//��Ҫ�ж��������ֵķ�Χ
    pgCall->HaveCursor=TRUE;
    //��Ӧ��ϵ
    pgCall->FunSets.iniPagefun=p019_inipage;
    //��Ӧ��ϵ
    pgCall->Calllast=FALSE;//������ʵ�ֺ���
    pgCall->FunSets.Implementfun=p015_complete;
    //��Χ����
    pgCall->FunSets.JudgeInputNumfun=pcom_InputNum_InRange;
    pgCall->FunSets.RecvKeyDealfun=p010_keyDeal;

    //������������룬selfInitfun�����ʼ��
    pgCall->FunSets.selfInitfun=p019_initpgentry;
    if(!pgCall->FunSets.selfInitfun)
        pgCall->FunSets.selfInitfun=donothingnonepara;
    //�����Ƿ���ҪEnter��ȷ��
    pgCall->FunSets.para_rec.KeyType.runflag=FALSE;

    pgCall->FunSets.iniPagefun(&pgCall->FunSets.para_ini);
}
/******************************************************************************
* ҳ��: // �����������
*      _��·_ _��ַ
* 	����:  ��ʱ�Ӻ���
*
******************************************************************************/
void p020_initpgentry(void)
{
    pgCall=&pgcom_callb;
    Clear_Key_CallBack(pgCall);//�������
    //���ñ�Ҫ����
    pgCall->pgNum=20;
    SetLanguage(pgCall->pgNum,&pgcom_callb); 
	
    //pgCall->curstartrow=STARTROW_FIG_p019;
    //pgCall->curarrayptr=&cstpos_p010[0];
    //pgCall->intputMaxnum=ARRAYSIZE(cstpos_p010);
    pgCall->JudegInputNumRange=TRUE;//��Ҫ�ж��������ֵķ�Χ
    pgCall->HaveCursor=TRUE;
    //��Ӧ��ϵ
    pgCall->FunSets.iniPagefun=p020_inipage;
    //��Ӧ��ϵ
    pgCall->Calllast=FALSE;//������ʵ�ֺ���
    pgCall->FunSets.Implementfun=p015_complete;
    //��Χ����
    pgCall->FunSets.JudgeInputNumfun=pcom_InputNum_InRange;
    pgCall->FunSets.RecvKeyDealfun=p010_keyDeal;

    //������������룬selfInitfun�����ʼ��
    pgCall->FunSets.selfInitfun=p020_initpgentry;
    if(!pgCall->FunSets.selfInitfun)
        pgCall->FunSets.selfInitfun=donothingnonepara;
    //�����Ƿ���ҪEnter��ȷ��
    pgCall->FunSets.para_rec.KeyType.runflag=FALSE;

    pgCall->FunSets.iniPagefun(&pgCall->FunSets.para_ini);
}
// ��ѯ������ַ
void p028_initpgentry(void)
{
    pgCall=&pgcom_callb;
    Clear_Key_CallBack(pgCall);//�������
    //���ñ�Ҫ����
    pgCall->pgNum=28;
    SetLanguage(pgCall->pgNum,&pgcom_callb); 
    //pgCall->curstartrow=STARTROW_FIG_p019;
    //pgCall->curarrayptr=&cstpos_p010[0];
    //pgCall->intputMaxnum=ARRAYSIZE(cstpos_p010);
    pgCall->JudegInputNumRange=TRUE;//��Ҫ�ж��������ֵķ�Χ
    pgCall->HaveCursor=TRUE;
    //��Ӧ��ϵ
    pgCall->FunSets.iniPagefun=p028_inipage;
    //��Ӧ��ϵ
    pgCall->Calllast=FALSE;//������ʵ�ֺ���
    pgCall->FunSets.Implementfun=p028_complete;
    //��Χ����
    pgCall->FunSets.JudgeInputNumfun=pcom_InputNum_InRange;
    pgCall->FunSets.RecvKeyDealfun=p010_keyDeal;

    //������������룬selfInitfun�����ʼ��
    pgCall->FunSets.selfInitfun=p028_initpgentry;
    if(!pgCall->FunSets.selfInitfun)
        pgCall->FunSets.selfInitfun=donothingnonepara;
    //�����Ƿ���ҪEnter��ȷ��
    pgCall->FunSets.para_rec.KeyType.runflag=FALSE;

    pgCall->FunSets.iniPagefun(&pgCall->FunSets.para_ini);
}
//�����·�Ǽ�
void p080_initpgentry(void)
{
    pgCall=&pgcom_callb;
    Clear_Key_CallBack(pgCall);//�������
    //���ñ�Ҫ����
    pgCall->pgNum=80;
    SetLanguage(pgCall->pgNum,&pgcom_callb); 

    pgCall->JudegInputNumRange=TRUE;//��Ҫ�ж��������ֵķ�Χ
    pgCall->HaveCursor=FALSE;
    //��Ӧ��ϵ
    pgCall->FunSets.iniPagefun=p080_inipage;
    //��Ӧ��ϵ
    pgCall->Calllast=FALSE;//������ʵ�ֺ���
    pgCall->FunSets.Implementfun=p080_complete;
    //��Χ����
    pgCall->FunSets.JudgeInputNumfun=p015_InputNum_InRange;
    pgCall->FunSets.RecvKeyDealfun=p010_keyDeal;

    //������������룬selfInitfun�����ʼ��
    pgCall->FunSets.selfInitfun=p080_initpgentry;
    if(!pgCall->FunSets.selfInitfun)
        pgCall->FunSets.selfInitfun=donothingnonepara;
    //�����Ƿ���ҪEnter��ȷ��
    pgCall->FunSets.para_rec.KeyType.runflag=FALSE;

    pgCall->FunSets.iniPagefun(&pgCall->FunSets.para_ini);
}
//����������
void p077_initpgentry(void)
{
    pgCall=&pgcom_callb;
    Clear_Key_CallBack(pgCall);//�������
    //���ñ�Ҫ����

	pgCall->pgNum=77;
    SetLanguage(pgCall->pgNum,&pgcom_callb); 
	
    pgCall->JudegInputNumRange=TRUE;//��Ҫ�ж��������ֵķ�Χ
    pgCall->HaveCursor=TRUE;
    //��Ӧ��ϵ
    pgCall->FunSets.iniPagefun=p077_inipage;
    //��Ӧ��ϵ
    pgCall->Calllast=FALSE;//������ʵ�ֺ���
    pgCall->FunSets.Implementfun=p077_complete;
    //��Χ����
    pgCall->FunSets.JudgeInputNumfun=p015_InputNum_InRange;
    pgCall->FunSets.RecvKeyDealfun=p010_keyDeal;

    //������������룬selfInitfun�����ʼ��
    pgCall->FunSets.selfInitfun=p077_initpgentry;
    if(!pgCall->FunSets.selfInitfun)
        pgCall->FunSets.selfInitfun=donothingnonepara;
    //�����Ƿ���ҪEnter��ȷ��
    pgCall->FunSets.para_rec.KeyType.runflag=FALSE;

    pgCall->FunSets.iniPagefun(&pgCall->FunSets.para_ini);
}
//���ע��
void p078_initpgentry(void)
{
    pgCall=&pgcom_callb;
    Clear_Key_CallBack(pgCall);//�������
    //���ñ�Ҫ����
	pgCall->pgNum=78;
	SetLanguage(pgCall->pgNum,&pgcom_callb); 

    pgCall->JudegInputNumRange=TRUE;//��Ҫ�ж��������ֵķ�Χ
    pgCall->HaveCursor=TRUE;
    //��Ӧ��ϵ
    pgCall->FunSets.iniPagefun=p078_inipage;
    //��Ӧ��ϵ
    pgCall->Calllast=FALSE;//������ʵ�ֺ���
    pgCall->FunSets.Implementfun=p078_complete;
    //��Χ����
    pgCall->FunSets.JudgeInputNumfun=p015_InputNum_InRange;
    pgCall->FunSets.RecvKeyDealfun=p010_keyDeal;

    //������������룬selfInitfun�����ʼ��
    pgCall->FunSets.selfInitfun=p078_initpgentry;
    if(!pgCall->FunSets.selfInitfun)
        pgCall->FunSets.selfInitfun=donothingnonepara;
    //�����Ƿ���ҪEnter��ȷ��
    pgCall->FunSets.para_rec.KeyType.runflag=FALSE;

    pgCall->FunSets.iniPagefun(&pgCall->FunSets.para_ini);
}
//���������ַ
void p081_initpgentry(void)
{
    pgCall=&pgcom_callb;
    Clear_Key_CallBack(pgCall);//�������
    //���ñ�Ҫ����
	pgCall->pgNum=81;
	SetLanguage(pgCall->pgNum,&pgcom_callb); 
	
    pgCall->JudegInputNumRange=TRUE;//��Ҫ�ж��������ֵķ�Χ
    pgCall->HaveCursor=TRUE;
    //��Ӧ��ϵ
    pgCall->FunSets.iniPagefun=p081_inipage;
    //��Ӧ��ϵ
    pgCall->Calllast=FALSE;//������ʵ�ֺ���
    pgCall->FunSets.Implementfun=p081_complete;
    //��Χ����
    pgCall->FunSets.JudgeInputNumfun=p015_InputNum_InRange;
    pgCall->FunSets.RecvKeyDealfun=p010_keyDeal;

    //������������룬selfInitfun�����ʼ��
    pgCall->FunSets.selfInitfun=p081_initpgentry;
    if(!pgCall->FunSets.selfInitfun)
        pgCall->FunSets.selfInitfun=donothingnonepara;
    //�����Ƿ���ҪEnter��ȷ��
    pgCall->FunSets.para_rec.KeyType.runflag=FALSE;

    pgCall->FunSets.iniPagefun(&pgCall->FunSets.para_ini);
}
/******************************************************************************
* ҳ��: // �޸�1������
* ����������� * ��ʾ��

* ԭ������: _ _ _
* ��������: _ _ _
* �ٴ�ȷ��: _ _ _
******************************************************************************/
void p083_initpgentry(void)
{
    pgCall=&pgcom_callb;
    Clear_Key_CallBack(pgCall);//�������
    //���ñ�Ҫ����
    pgCall->pgNum=83;
	SetLanguage(pgCall->pgNum,&pgcom_callb); 
    //pgCall->curstartrow=STARTROW_FIG_p019;
    //pgCall->curarrayptr=&cstpos_p083[0];
    //pgCall->intputMaxnum=ARRAYSIZE(cstpos_p083);
    pgCall->JudegInputNumRange=TRUE;//��Ҫ�ж��������ֵķ�Χ
    pgCall->HaveCursor=TRUE;
    //��Ӧ��ϵ
    pgCall->hidecursor=TRUE;//�����˸*����ʾ
    pgCall->hideInputNum=TRUE;//�������������
    pgCall->FunSets.iniPagefun=p083_inipage;
    //��Ӧ��ϵ
    pgCall->Calllast=FALSE;//������ʵ�ֺ���
    pgCall->FunSets.Implementfun=p083_complete;
    //��Χ����
    pgCall->FunSets.JudgeInputNumfun=p083_InputNum_InRange;
    pgCall->FunSets.RecvKeyDealfun=p010_keyDeal;

    //������������룬selfInitfun�����ʼ��
    pgCall->FunSets.selfInitfun=p083_initpgentry;
    if(!pgCall->FunSets.selfInitfun)
        pgCall->FunSets.selfInitfun=donothingnonepara;
    //�����Ƿ���ҪEnter��ȷ��
    pgCall->FunSets.para_rec.KeyType.runflag=FALSE;

    pgCall->FunSets.iniPagefun(&pgCall->FunSets.para_ini);
}
/******************************************************************************
* ҳ��: // �޸�2������
* ����������� * ��ʾ��

* ԭ������: _ _ _
* ��������: _ _ _
* �ٴ�ȷ��: _ _ _
******************************************************************************/
void p084_initpgentry(void)
{
    pgCall=&pgcom_callb;
    Clear_Key_CallBack(pgCall);//�������
    //���ñ�Ҫ����
    pgCall->pgNum=84;
	SetLanguage(pgCall->pgNum,&pgcom_callb); 
    //pgCall->curstartrow=STARTROW_FIG_p019;
    //pgCall->curarrayptr=&cstpos_p083[0];
    //pgCall->intputMaxnum=ARRAYSIZE(cstpos_p083);
    pgCall->JudegInputNumRange=TRUE;//��Ҫ�ж��������ֵķ�Χ
    pgCall->HaveCursor=TRUE;
    //��Ӧ��ϵ
    pgCall->hidecursor=TRUE;//�����˸*����ʾ
    pgCall->hideInputNum=TRUE;//�������������
    pgCall->FunSets.iniPagefun=p084_inipage;
    //��Ӧ��ϵ
    pgCall->Calllast=FALSE;//������ʵ�ֺ���
    pgCall->FunSets.Implementfun=p084_complete;
    //��Χ����
    pgCall->FunSets.JudgeInputNumfun=p083_InputNum_InRange;
    pgCall->FunSets.RecvKeyDealfun=p010_keyDeal;

    //������������룬selfInitfun�����ʼ��
    pgCall->FunSets.selfInitfun=p084_initpgentry;
    if(!pgCall->FunSets.selfInitfun)
        pgCall->FunSets.selfInitfun=donothingnonepara;
    //�����Ƿ���ҪEnter��ȷ��
    pgCall->FunSets.para_rec.KeyType.runflag=FALSE;

    pgCall->FunSets.iniPagefun(&pgCall->FunSets.para_ini);
}
/******************************************************************************
* ҳ��: // ��ʾ ģ��������
*  _��·_ _ _��ַ: _ _ _ (��ʾ��ǰֵ)
* |
* |_________________________>
* �ѵ�ǰֵ��һ������ʾ���߶ȶ�Ӧֵ�Ĵ�С�����128.
* ÿ�õ�һ���µ�ֵ��X����������һ����ʾλ�ã�����������࿪ʼˢ�£�ͬʱ�����Ҳ�16�����������
* ��Ч�����Ӿ��ϲ�������Ըģ�����ÿ�εõ�ֵ���ú���2�����ر�ʾ��
******************************************************************************/
void p061_initpgentry(void)
{
    pgCall=&pgcom_callb;
    Clear_Key_CallBack(pgCall);//�������
    //���ñ�Ҫ����
    pgCall->pgNum=61;
	SetLanguage(pgCall->pgNum,&pgcom_callb); 
    //pgCall->curstartrow=STARTROW_FIG_p017;
    //pgCall->curarrayptr=&cstpos_p061[0];
    //pgCall->intputMaxnum=ARRAYSIZE(cstpos_p061);
    pgCall->JudegInputNumRange=TRUE;//��Ҫ�ж��������ֵķ�Χ
    pgCall->HaveCursor=TRUE;
    //��Ӧ��ϵ
    pgCall->FunSets.iniPagefun=p061_inipage;
    //��Ӧ��ϵ
    pgCall->Calllast=FALSE;//������ʵ�ֺ���
    pgCall->FunSets.Implementfun=donothing;
    //��Χ����
    pgCall->FunSets.JudgeInputNumfun=p010_InputNum_InRange;
    pgCall->FunSets.RecvKeyDealfun=p010_keyDeal;

    //������������룬selfInitfun�����ʼ��
    pgCall->FunSets.selfInitfun=p061_initpgentry;
    if(!pgCall->FunSets.selfInitfun)
        pgCall->FunSets.selfInitfun=donothingnonepara;
    //�����Ƿ���ҪEnter��ȷ��
    pgCall->FunSets.para_rec.KeyType.runflag=FALSE;
    //���Զ�ʱ���ܵĴ���
    //��Ҫ�ж�ʱ��������
    pgCall->ortmrflag=TRUE;//��ʱ��־
    pgCall->FunSets.Tmrfun=p061_tmrtask;
    pgCall->FunSets.para_tmr.tmrId=8;//��ʱʹ�ã����ڻ�û��ʹ��
    pgCall->FunSets.para_tmr.tmrMs=100;//3s,��λΪ����
    pgCall->FunSets.SetTmr=doTmrTaskSet;
    pgCall->FunSets.GetTmr=doTmrTaskGet;
    pgCall->FunSets.KillTmr=doTmrTaskKill;

    //�Ƿ�����ִ�ж��廹�ǵȴ���ִ�У�Ĭ�ϲ�����ִ��
//    pgCall->execTmrTaskOnOverfg=TRUE;


    pgCall->FunSets.iniPagefun(&pgCall->FunSets.para_ini);
}

void p062_initpgentry(void)
{
    pgCall=&pgcom_callb;
    Clear_Key_CallBack(pgCall);//�������
    //���ñ�Ҫ����
    pgCall->pgNum=62;
	SetLanguage(pgCall->pgNum,&pgcom_callb); 
//    pgCall->curstartrow=STARTROW_FIG_p042;
//    pgCall->curarrayptr=&cstpos_p062[0];
//    pgCall->intputMaxnum=ARRAYSIZE(cstpos_p062);
    pgCall->JudegInputNumRange=TRUE;//��Ҫ�ж��������ֵķ�Χ
    pgCall->HaveCursor=TRUE;
    //��Ӧ��ϵ
    pgCall->FunSets.iniPagefun=p062_inipage;
    //��Ӧ��ϵ
    pgCall->Calllast=TRUE;//������ʵ�ֺ���
    pgCall->FunSets.Implementfun=p062_complete;
    //��Χ����
    pgCall->FunSets.JudgeInputNumfun=p058_InputNum_InRange;
    pgCall->FunSets.RecvKeyDealfun=p010_keyDeal;

    //������������룬selfInitfun�����ʼ��
    pgCall->FunSets.selfInitfun=p062_initpgentry;
    if(!pgCall->FunSets.selfInitfun)
        pgCall->FunSets.selfInitfun=donothingnonepara;
    //�����Ƿ���ҪEnter��ȷ��
    pgCall->FunSets.para_rec.KeyType.runflag=FALSE;

    pgCall->FunSets.iniPagefun(&pgCall->FunSets.para_ini);
}
/******************************************************************************
* ҳ��: // �ֳ��豸����״̬
*  	_��·_ _ _��ַ:
*   ��������:
*   ����״̬:
******************************************************************************/
void p063_initpgentry(void)
{
    pgCall=&pgcom_callb;
    Clear_Key_CallBack(pgCall);//�������
    //���ñ�Ҫ����
    pgCall->pgNum=63;
	SetLanguage(pgCall->pgNum,&pgcom_callb); 
	
    //pgCall->curstartrow=STARTROW_FIG_p042;
    //pgCall->curarrayptr=&cstpos_p010[0];
    //pgCall->intputMaxnum=ARRAYSIZE(cstpos_p010);
    pgCall->JudegInputNumRange=TRUE;//��Ҫ�ж��������ֵķ�Χ
    pgCall->HaveCursor=TRUE;
    //��Ӧ��ϵ
    pgCall->FunSets.iniPagefun=p063_inipage;
    //��Ӧ��ϵ
    pgCall->Calllast=TRUE;//������ʵ�ֺ���
    pgCall->FunSets.Implementfun=p063_complete;
    //��Χ����
    pgCall->FunSets.JudgeInputNumfun=p010_InputNum_InRange;
    pgCall->FunSets.RecvKeyDealfun=p010_keyDeal;

    //������������룬selfInitfun�����ʼ��
    pgCall->FunSets.selfInitfun=p063_initpgentry;
    if(!pgCall->FunSets.selfInitfun)
        pgCall->FunSets.selfInitfun=donothingnonepara;
    //�����Ƿ���ҪEnter��ȷ��
    pgCall->FunSets.para_rec.KeyType.runflag=FALSE;

    pgCall->FunSets.iniPagefun(&pgCall->FunSets.para_ini);
}
/******************************************************************************
* ҳ��: //
*  _��·_ _ _��ַ
*  ʮ���������ݣ�˳����ʾ�� ��������ͷˢ����ʾ�����������2���ֽڡ�
*
******************************************************************************/
void p064_initpgentry(void)
{
    pgCall=&pgcom_callb;
    Clear_Key_CallBack(pgCall);//�������
    //���ñ�Ҫ����
    pgCall->pgNum=64;
	SetLanguage(pgCall->pgNum,&pgcom_callb); 
	
    //pgCall->curstartrow=STARTROW_FIG_p042;
    //pgCall->curarrayptr=&cstpos_p010[0];
    //pgCall->intputMaxnum=ARRAYSIZE(cstpos_p010);
    pgCall->JudegInputNumRange=TRUE;//��Ҫ�ж��������ֵķ�Χ
    pgCall->HaveCursor=TRUE;
    //��Ӧ��ϵ
    pgCall->FunSets.iniPagefun=p064_inipage;
    //��Ӧ��ϵ
    pgCall->Calllast=TRUE;//������ʵ�ֺ���
    pgCall->FunSets.Implementfun=p064_complete;
    //��Χ����
    pgCall->FunSets.JudgeInputNumfun=p010_InputNum_InRange;
    pgCall->FunSets.RecvKeyDealfun=p010_keyDeal;

    //������������룬selfInitfun�����ʼ��
    pgCall->FunSets.selfInitfun=p064_initpgentry;
    if(!pgCall->FunSets.selfInitfun)
        pgCall->FunSets.selfInitfun=donothingnonepara;
    //�����Ƿ���ҪEnter��ȷ��
    pgCall->FunSets.para_rec.KeyType.runflag=FALSE;

    pgCall->FunSets.iniPagefun(&pgCall->FunSets.para_ini);
}
/******************************************************************************
* ҳ��: // �Լ죻Һ��ɨ��������ƣ���������˳����������
*
******************************************************************************/
void p065_initpgentry(void)
{
    pgCall=&pgcom_callb;
    Clear_Key_CallBack(pgCall);//�������
    //���ñ�Ҫ����
    pgCall->pgNum=65;
	SetLanguage(pgCall->pgNum,&pgcom_callb); 
	
    //��Ӧ��ϵ
    pgCall->FunSets.iniPagefun=p065_inipage;
    //��Ӧ��ϵ
//    pgCall->Calllast=TRUE;//������ʵ�ֺ���
    pgCall->FunSets.Implementfun=p064_complete;
    //��Χ����
//    pgCall->FunSets.JudgeInputNumfun=p010_InputNum_InRange;
//    pgCall->FunSets.RecvKeyDealfun=p010_keyDeal;

    //������������룬selfInitfun�����ʼ��
    pgCall->FunSets.selfInitfun=p065_initpgentry;
    if(!pgCall->FunSets.selfInitfun)
        pgCall->FunSets.selfInitfun=donothingnonepara;
    //�����Ƿ���ҪEnter��ȷ��
    pgCall->FunSets.para_rec.KeyType.runflag=FALSE;

    pgCall->FunSets.iniPagefun(&pgCall->FunSets.para_ini);
    pgCall->FunSets.Implementfun(&pgCall->FunSets.para_imp);
}
/******************************************************************************
* ҳ��: // ���԰�����
* ����Ļ�ϰ���ʵ�ʼ���˳�򻭱�־����ĳ�������£����ɫ��
* ����6���ް������룬���Զ��˳����˵�
******************************************************************************/
void p067_initpgentry(void)
{
    pgCall=&pgcom_callb;
    Clear_Key_CallBack(pgCall);//�������
    //���ñ�Ҫ����
    pgCall->pgNum=67;
	SetLanguage(pgCall->pgNum,&pgcom_callb); 

    pgCall->JudegInputNumRange=TRUE;//��Ҫ�ж��������ֵķ�Χ
//    pgCall->HaveCursor=TRUE;
    //��Ӧ��ϵ
    pgCall->FunSets.iniPagefun=p067_inipage;
    //��Ӧ��ϵ
//    pgCall->Calllast=TRUE;//������ʵ�ֺ���
    pgCall->FunSets.Implementfun=p067_complete;
    //��Χ����
//    pgCall->FunSets.JudgeInputNumfun=p010_InputNum_InRange;
//    pgCall->FunSets.RecvKeyDealfun=p010_keyDeal;

    //������������룬selfInitfun�����ʼ��
    pgCall->FunSets.selfInitfun=p067_initpgentry;
    if(!pgCall->FunSets.selfInitfun)
        pgCall->FunSets.selfInitfun=donothingnonepara;
    //�����Ƿ���ҪEnter��ȷ��
    pgCall->FunSets.para_rec.KeyType.runflag=FALSE;

    pgCall->FunSets.iniPagefun(&pgCall->FunSets.para_ini);
    pgCall->FunSets.Implementfun(&pgCall->FunSets.para_imp);
}
/******************************************************************************
* ҳ��: // ���� ͨѶ-iCan;
* ����1��֡��:
* ����2��֡��:
* ����3��֡��:
* ����4��֡��:
******************************************************************************/
void p072_initpgentry(void)
{
    pgCall=&pgcom_callb;
    Clear_Key_CallBack(pgCall);//�������
    //���ñ�Ҫ����
    pgCall->pgNum=72;
	SetLanguage(pgCall->pgNum,&pgcom_callb); 

    pgCall->JudegInputNumRange=TRUE;//��Ҫ�ж��������ֵķ�Χ
//    pgCall->HaveCursor=TRUE;
    //��Ӧ��ϵ
    pgCall->FunSets.iniPagefun=p072_inipage;
    //��Ӧ��ϵ
//    pgCall->Calllast=TRUE;//������ʵ�ֺ���
    pgCall->FunSets.Implementfun=p072_complete;
    //��Χ����
//    pgCall->FunSets.JudgeInputNumfun=p010_InputNum_InRange;
//    pgCall->FunSets.RecvKeyDealfun=p010_keyDeal;

    //������������룬selfInitfun�����ʼ��
    pgCall->FunSets.selfInitfun=p072_initpgentry;
    if(!pgCall->FunSets.selfInitfun)
        pgCall->FunSets.selfInitfun=donothingnonepara;
    //�����Ƿ���ҪEnter��ȷ��
    pgCall->FunSets.para_rec.KeyType.runflag=FALSE;

    pgCall->FunSets.iniPagefun(&pgCall->FunSets.para_ini);
    pgCall->FunSets.Implementfun(&pgCall->FunSets.para_imp);
}
/******************************************************************************
* ҳ��: // ���� ͨѶ-eCan;
* ��������֡��:
* ���������������ߣ���ʾ����֡����
******************************************************************************/
void p073_initpgentry(void)
{
    pgCall=&pgcom_callb;
    Clear_Key_CallBack(pgCall);//�������
    //���ñ�Ҫ����
	pgCall->pgNum=73;
	SetLanguage(pgCall->pgNum,&pgcom_callb); 
    pgCall->JudegInputNumRange=TRUE;//��Ҫ�ж��������ֵķ�Χ
//    pgCall->HaveCursor=TRUE;
    //��Ӧ��ϵ
    pgCall->FunSets.iniPagefun=p073_inipage;
    //��Ӧ��ϵ
//    pgCall->Calllast=TRUE;//������ʵ�ֺ���
    pgCall->FunSets.Implementfun=p073_complete;
    //��Χ����
//    pgCall->FunSets.JudgeInputNumfun=p010_InputNum_InRange;
//    pgCall->FunSets.RecvKeyDealfun=p010_keyDeal;

    //������������룬selfInitfun�����ʼ��
    pgCall->FunSets.selfInitfun=p073_initpgentry;
    if(!pgCall->FunSets.selfInitfun)
        pgCall->FunSets.selfInitfun=donothingnonepara;
    //�����Ƿ���ҪEnter��ȷ��
    pgCall->FunSets.para_rec.KeyType.runflag=FALSE;

    pgCall->FunSets.iniPagefun(&pgCall->FunSets.para_ini);
    pgCall->FunSets.Implementfun(&pgCall->FunSets.para_imp);
}
/******************************************************************************
* ҳ��: // ����
* ��ʱ ��ʾ����������
******************************************************************************/
void p011_initpgentry(void)
{
    pgCall=&pgcom_callb;
    Clear_Key_CallBack(pgCall);//�������
    //���ñ�Ҫ����
	pgCall->pgNum=11;
	SetLanguage(pgCall->pgNum,&pgcom_callb); 
    pgCall->JudegInputNumRange=TRUE;//��Ҫ�ж��������ֵķ�Χ
//    pgCall->HaveCursor=TRUE;
    //��Ӧ��ϵ
    pgCall->FunSets.iniPagefun=p011_inipage;
    //��Ӧ��ϵ
//    pgCall->Calllast=TRUE;//������ʵ�ֺ���
    pgCall->FunSets.Implementfun=p011_complete;
    //��Χ����
//    pgCall->FunSets.JudgeInputNumfun=p010_InputNum_InRange;
    pgCall->FunSets.RecvKeyDealfun=p010_keyDeal;//��ʱ��Ҫ���ã���ʱ�����ڴ˶�Ӧ��

    //������������룬selfInitfun�����ʼ��
    pgCall->FunSets.selfInitfun=p011_initpgentry;
    if(!pgCall->FunSets.selfInitfun)
        pgCall->FunSets.selfInitfun=donothingnonepara;
    //�����Ƿ���ҪEnter��ȷ��
    pgCall->FunSets.para_rec.KeyType.runflag=FALSE;



    //���Զ�ʱ���ܵĴ���
    //��Ҫ�ж�ʱ�������񣬶�ʱ�������ڰ��������е��õ�
    pgCall->overflag=TRUE;
    pgCall->execTmrTaskOnOverfg=TRUE;//��Ϊû�а�������
    pgCall->ortmrflag=TRUE;//��ʱ��־
    pgCall->FunSets.Tmrfun=p011_tmrtask;
    pgCall->FunSets.para_tmr.tmrId=8;//��ʱʹ�ã����ڻ�û��ʹ��
    pgCall->FunSets.para_tmr.tmrMs=1000;//3s,��λΪ����
    pgCall->FunSets.SetTmr=doTmrTaskSet;
    pgCall->FunSets.GetTmr=doTmrTaskGet;
    pgCall->FunSets.KillTmr=doTmrTaskKill;



    pgCall->FunSets.iniPagefun(&pgCall->FunSets.para_ini);
    pgCall->FunSets.Implementfun(&pgCall->FunSets.para_imp);





}
/******************************************************************************
* ҳ��: //��ѯ�ֶ��Զ�
* ��ʾ�ѵǼǵ������ֶ��Զ�  �ο� ShowStr_AutoManuNowState();
* һ��:
* ����:
* ����:
* ����:
******************************************************************************/
void p059_initpgentry(void)
{
    pgCall=&pgcom_callb;
    Clear_Key_CallBack(pgCall);//�������
    //���ñ�Ҫ����
	pgCall->pgNum=59;
	SetLanguage(pgCall->pgNum,&pgcom_callb); 
    pgCall->JudegInputNumRange=TRUE;//��Ҫ�ж��������ֵķ�Χ
//    pgCall->HaveCursor=TRUE;
    //��Ӧ��ϵ
    pgCall->FunSets.iniPagefun=p059_inipage;
    //��Ӧ��ϵ
//    pgCall->Calllast=TRUE;//������ʵ�ֺ���
    pgCall->FunSets.Implementfun=p059_complete;
    //��Χ����
//    pgCall->FunSets.JudgeInputNumfun=p010_InputNum_InRange;
//    pgCall->FunSets.RecvKeyDealfun=p010_keyDeal;

    //������������룬selfInitfun�����ʼ��
    pgCall->FunSets.selfInitfun=p059_initpgentry;
    if(!pgCall->FunSets.selfInitfun)
        pgCall->FunSets.selfInitfun=donothingnonepara;
    //�����Ƿ���ҪEnter��ȷ��
    pgCall->FunSets.para_rec.KeyType.runflag=FALSE;

    pgCall->FunSets.iniPagefun(&pgCall->FunSets.para_ini);
    pgCall->FunSets.Implementfun(&pgCall->FunSets.para_imp);
}
/******************************************************************************
* ҳ��: // ��ѯ��ʷ��¼-����
*
******************************************************************************/
void p052_initpgentry(void)
{
    pgCall=&pgcom_callb;
    Clear_Key_CallBack(pgCall);//�������
    //���ñ�Ҫ����
    pgCall->pgNum=52;
	SetLanguage(pgCall->pgNum,&pgcom_callb); 

    pgCall->JudegInputNumRange=TRUE;//��Ҫ�ж��������ֵķ�Χ
//    pgCall->HaveCursor=TRUE;
    //��Ӧ��ϵ
    pgCall->FunSets.iniPagefun=p052_inipage;
    //��Ӧ��ϵ
//    pgCall->Calllast=TRUE;//������ʵ�ֺ���
    pgCall->FunSets.Implementfun=p052_complete;
    //��Χ����
//    pgCall->FunSets.JudgeInputNumfun=p010_InputNum_InRange;
//    pgCall->FunSets.RecvKeyDealfun=p010_keyDeal;

    //������������룬selfInitfun�����ʼ��
    pgCall->FunSets.selfInitfun=p052_initpgentry;
    if(!pgCall->FunSets.selfInitfun)
        pgCall->FunSets.selfInitfun=donothingnonepara;
    //�����Ƿ���ҪEnter��ȷ��
    pgCall->FunSets.para_rec.KeyType.runflag=FALSE;

    pgCall->FunSets.iniPagefun(&pgCall->FunSets.para_ini);
    pgCall->FunSets.Implementfun(&pgCall->FunSets.para_imp);
}
/******************************************************************************
* ҳ��: // ��ѯ��ʷ��¼-��
*
******************************************************************************/
void p053_initpgentry(void)
{
    pgCall=&pgcom_callb;
    Clear_Key_CallBack(pgCall);//�������
    //���ñ�Ҫ����
    pgCall->pgNum=53;
	SetLanguage(pgCall->pgNum,&pgcom_callb); 
    pgCall->JudegInputNumRange=TRUE;//��Ҫ�ж��������ֵķ�Χ
//    pgCall->HaveCursor=TRUE;
    //��Ӧ��ϵ
    pgCall->FunSets.iniPagefun=p053_inipage;
    //��Ӧ��ϵ
//    pgCall->Calllast=TRUE;//������ʵ�ֺ���
    pgCall->FunSets.Implementfun=p053_complete;
    //��Χ����
//    pgCall->FunSets.JudgeInputNumfun=p010_InputNum_InRange;
//    pgCall->FunSets.RecvKeyDealfun=p010_keyDeal;

    //������������룬selfInitfun�����ʼ��
    pgCall->FunSets.selfInitfun=p053_initpgentry;
    if(!pgCall->FunSets.selfInitfun)
        pgCall->FunSets.selfInitfun=donothingnonepara;
    //�����Ƿ���ҪEnter��ȷ��
    pgCall->FunSets.para_rec.KeyType.runflag=FALSE;

    pgCall->FunSets.iniPagefun(&pgCall->FunSets.para_ini);
    pgCall->FunSets.Implementfun(&pgCall->FunSets.para_imp);
}
/******************************************************************************
* ҳ��: // ��ѯ��ʷ��¼-����
*
******************************************************************************/
void p054_initpgentry(void)
{
    pgCall=&pgcom_callb;
    Clear_Key_CallBack(pgCall);//�������
    //���ñ�Ҫ����
    pgCall->pgNum=54;
	SetLanguage(pgCall->pgNum,&pgcom_callb); 
    pgCall->JudegInputNumRange=TRUE;//��Ҫ�ж��������ֵķ�Χ
//    pgCall->HaveCursor=TRUE;
    //��Ӧ��ϵ
    pgCall->FunSets.iniPagefun=p054_inipage;
    //��Ӧ��ϵ
//    pgCall->Calllast=TRUE;//������ʵ�ֺ���
    pgCall->FunSets.Implementfun=p054_complete;
    //��Χ����
//    pgCall->FunSets.JudgeInputNumfun=p010_InputNum_InRange;
//    pgCall->FunSets.RecvKeyDealfun=p010_keyDeal;

    //������������룬selfInitfun�����ʼ��
    pgCall->FunSets.selfInitfun=p054_initpgentry;
    if(!pgCall->FunSets.selfInitfun)
        pgCall->FunSets.selfInitfun=donothingnonepara;
    //�����Ƿ���ҪEnter��ȷ��
    pgCall->FunSets.para_rec.KeyType.runflag=FALSE;

    pgCall->FunSets.iniPagefun(&pgCall->FunSets.para_ini);
    pgCall->FunSets.Implementfun(&pgCall->FunSets.para_imp);
}
/******************************************************************************
* ҳ��: // ��ѯ��ʷ��¼-����
*
******************************************************************************/
void p055_initpgentry(void)
{
    pgCall=&pgcom_callb;
    Clear_Key_CallBack(pgCall);//�������
    //���ñ�Ҫ����
    pgCall->pgNum=55;
	SetLanguage(pgCall->pgNum,&pgcom_callb); 
    pgCall->JudegInputNumRange=TRUE;//��Ҫ�ж��������ֵķ�Χ
//    pgCall->HaveCursor=TRUE;
    //��Ӧ��ϵ
    pgCall->FunSets.iniPagefun=p055_inipage;
    //��Ӧ��ϵ
//    pgCall->Calllast=TRUE;//������ʵ�ֺ���
    pgCall->FunSets.Implementfun=p055_complete;
    //��Χ����
//    pgCall->FunSets.JudgeInputNumfun=p010_InputNum_InRange;
//    pgCall->FunSets.RecvKeyDealfun=p010_keyDeal;

    //������������룬selfInitfun�����ʼ��
    pgCall->FunSets.selfInitfun=p055_initpgentry;
    if(!pgCall->FunSets.selfInitfun)
        pgCall->FunSets.selfInitfun=donothingnonepara;
    //�����Ƿ���ҪEnter��ȷ��
    pgCall->FunSets.para_rec.KeyType.runflag=FALSE;

    pgCall->FunSets.iniPagefun(&pgCall->FunSets.para_ini);
    pgCall->FunSets.Implementfun(&pgCall->FunSets.para_imp);
}
void p056_initpgentry(void)
{
    pgCall=&pgcom_callb;
    Clear_Key_CallBack(pgCall);//�������
    //���ñ�Ҫ����
	pgCall->pgNum=56;
	SetLanguage(pgCall->pgNum,&pgcom_callb); 
	
    pgCall->JudegInputNumRange=TRUE;//��Ҫ�ж��������ֵķ�Χ
//    pgCall->HaveCursor=TRUE;
    //��Ӧ��ϵ
    pgCall->FunSets.iniPagefun=p056_inipage;
    //��Ӧ��ϵ
//    pgCall->Calllast=TRUE;//������ʵ�ֺ���
    pgCall->FunSets.Implementfun=p056_complete;
    //��Χ����
//    pgCall->FunSets.JudgeInputNumfun=p010_InputNum_InRange;
//    pgCall->FunSets.RecvKeyDealfun=p010_keyDeal;

    //������������룬selfInitfun�����ʼ��
    pgCall->FunSets.selfInitfun=p056_initpgentry;
    if(!pgCall->FunSets.selfInitfun)
        pgCall->FunSets.selfInitfun=donothingnonepara;
    //�����Ƿ���ҪEnter��ȷ��
    pgCall->FunSets.para_rec.KeyType.runflag=FALSE;

    pgCall->FunSets.iniPagefun(&pgCall->FunSets.para_ini);
    pgCall->FunSets.Implementfun(&pgCall->FunSets.para_imp);
}
void p057_initpgentry(void)
{
    pgCall=&pgcom_callb;
    Clear_Key_CallBack(pgCall);//�������
    //���ñ�Ҫ����
    pgCall->pgNum=57;
	SetLanguage(pgCall->pgNum,&pgcom_callb);
    pgCall->JudegInputNumRange=TRUE;//��Ҫ�ж��������ֵķ�Χ
//    pgCall->HaveCursor=TRUE;
    //��Ӧ��ϵ
    pgCall->FunSets.iniPagefun=p057_inipage;
    //��Ӧ��ϵ
//    pgCall->Calllast=TRUE;//������ʵ�ֺ���
    pgCall->FunSets.Implementfun=p057_complete;
    //��Χ����
//    pgCall->FunSets.JudgeInputNumfun=p010_InputNum_InRange;
//    pgCall->FunSets.RecvKeyDealfun=p010_keyDeal;

    //������������룬selfInitfun�����ʼ��
    pgCall->FunSets.selfInitfun=p057_initpgentry;
    if(!pgCall->FunSets.selfInitfun)
        pgCall->FunSets.selfInitfun=donothingnonepara;
    //�����Ƿ���ҪEnter��ȷ��
    pgCall->FunSets.para_rec.KeyType.runflag=FALSE;

    pgCall->FunSets.iniPagefun(&pgCall->FunSets.para_ini);
    pgCall->FunSets.Implementfun(&pgCall->FunSets.para_imp);
}
