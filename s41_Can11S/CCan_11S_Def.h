/*
*********************************************************************************************************
*                                                
*                                 ������� CCan_11S_Def
*
*                        (c) Copyright 2009-2016, ��ѩ÷
*                              All Rights Reserved
*                                    Ver1.0
* File : CCan_11S_Def.H
* By   : ��ѩ÷
*
*********************************************************************************************************
*/
//#include  "CCan_11S_Def.h"

#ifndef CCan_11S_Def_H
#define CCan_11S_Def_H


//#include <includes.h>	
 
 

#ifdef  CCan_11S_Def_C
#define EX_CCan_11S_Def
#else
#define EX_CCan_11S_Def extern 
#endif

/*================= ���� ============================================*/
typedef enum{
	U_ModuRunTp_Auto = 1,
	U_ModuRunTp_Manu = 2,
	U_ModuRunTp_Remote = 3,
}emModuRunAuMaRemote;
	
// 0x80  ����/����
// 0x00  ֹͣ/����
// 0x04  ������ʱ
typedef enum{
	U_ModuRunSta_Start = 0x80,
	U_ModuRunSta_Stop = 0,
	U_ModuRunSta_Delay = 0x04,
}emModuRunState;
	
// 0--̽��
// 1--����
// 2--����
// 3--�㲥
typedef enum{
	U_DeteClass_Detector = 0,
	U_DeteClass_ModuOut = 1,
	U_DeteClass_HornStrobe = 2,
	U_DeteClass_ModuBroad = 3,
}emDeteCanClass;
	
// 0--��ȱʧӦ����Ϣ
// 80H--��δ�յ�Ӧ��
typedef enum{
	U_AckMissSta_Have = 0x80,
	U_AckMissSta_No = 0,
}emAckMissState;
	
// 0--����ʱ��Ϣ
// 80H--����ʱ����
typedef enum{
	U_ModuRunDelaySta_Have = 0x80,
	U_ModuRunDelaySta_No = 0,
}emModuRunDelayState;
	
// 0--̽�����
// 1--��������
// 2--�������
// 3---��Ⱦ����
// 4---ʧЧ����
typedef enum{
	U_DeteFaultCls_Detector = 0,
	U_DeteFaultCls_ModuOut = 1,
	U_DeteFaultCls_HornStrobe = 2,
	U_DeteFaultCls_Polluted = 3,  // ��Ⱦ
	U_DeteFaultCls_BecomeInvalid = 4,
}emDeteFaultClass; // ��·�ֳ�����������
	
// 0x81--����
// 0x80--�㲥
// 0x84--������

// D7--�����־
// D6--��ʱ������־

// D3~D0--ͨ����ʶ
typedef enum{
	U_DeteResponseCls_HornStrobe = 0x81,
	U_DeteResponseCls_Broad = 0x80,
	U_DeteResponseCls_NoAck = 0x84,
	
}emDeteResponseCls; // �豸����
	
	
typedef enum{
	U_DeteAlarmCls_ManuModu = 0x80, // �ֱ��� 
	
}emDeteAlarmCls; // ��������
	
	
/*******************************************************************/
/******************       ȫ�ֳ��������     *********************/
/*******************************************************************/

#define  cRsv_11S          0	      //��֡���ķ����ֽ���     

#define  c11S_MaxLpAddrNum           215  //��·����󵥻�·����ַ��
#define  c11S_MaxDirPanLpNum         8	  //����������ַ��
#define  c11S_MaxBusAddrNum          50	  //���������ĵ�ַ����	   
#define  c11S_MaxGasPanLpNum         4	  //��������ĵ�ַ����
 
#define  c11S_MaxLpPanLpNum          8	   //��·������·�� 
#define  c11S_MinDirLpMovNum         65	   //�����̻�·ƫ��
#define  c11S_MinGasLpMovNum         85	   //����̻�·ƫ��

//�����ʹ���
#define  cPanDisType	  0
#define  cPanLoopType     1	       
#define  cPanDirType      2	        
#define  cPanBusType      3	       
#define  cPanGasType      4	       
#define  cPanOthType      5	  
#define  cMaxPanType      6  

//Һ���巢�͵�����	�㲥����
#define  c11s_BC_Reset	    1	//��λ
#define  c11s_BC_Register	  2	//�Զ��Ǽ�
#define  c11s_BC_CheckSelf	3	//�Ƽ�
#define  c11s_BC_Time       4	//�㲥ʱ��
#define  c11s_BC_ClrReg     5	//����Ǽ�
#define  c11s_BC_ClrPrg     6	//������
#define  c11s_BC_EnPro      7	//��������
#define  c11s_BC_ClrBusPrg  9	//��������̶�Ӧ��ϵ
#define  c11s_BC_EnAuto     0x0a	//�����Զ�����
#define  c11s_BC_SlAct      0x0c	//���⶯��ָʾ 
#define  c11s_BC_Board      0x0d	//���߹㲥��������

#define  c11s_BC_FPAns      0x79  	//�����ûش�״̬
#define  c11s_BC_SysAns     0x78  	//ϵͳӦ��״̬
#define  c11s_BC_AuMa       0x70  	//���Զ�״̬

 
//Һ���巢�͵�����  �����������
#define  c11s_DS_SetInsul 	1   //��������
#define  c11s_DS_ManuStar	  2	//�ֶ��������� 
#define  c11s_DS_ManuStop	  3	//�ֶ�ֹͣ���� 
#define  c11s_DS_ClrInsul 	4   //�����������
#define  c11s_DS_SetReg 	  5   //������ַ�Ǽ�
#define  c11s_DS_ClrReg 	  6   //��������Ǽ�
#define  c11s_DS_SetBusPro 	0x0a   //���������̶�Ӧ��ϵ

#define  c11s_DS_SetDetScope 	0x1d   //����̽����������
#define  c11s_DS_ChkDetScope 	0x1e   //��ѯ̽����������

//Һ���巢�͵�����  ����ѯ����

#define  c11s_DCk_NdType 	0x09  //��ѯ��·����״̬
#define  c11s_DCk_LpReg 	0x11  //��ѯ��·�Ǽ�״̬
 
#define  c11s_DCk_Pro  	  0x13  //��ѯ�������
#define  c11s_DCk_NdSta 	0x14  //��ѯ״̬�ź�	
#define  c11s_DCk_NdCurve  0x15 //ģ������ѯ
#define  c11s_DCk_NdData 	 0x16  //��ѯ����
#define  c11s_DCk_NdScan 	 0x17  //��·����

#define  c11s_DCk_LpPanleReg 	0x23  //��ѯ��·��Ǽ�״̬
#define  c11s_CXCk_NdSta 	    0x24  //	ȡ����ѯ״̬�ź�	
#define  c11s_CXCk_NdCurve 	  0x25  //	ȡ��ģ������ѯ
#define  c11s_CXCk_NdData 	  0x26  //	ȡ����ѯ����
#define  c11s_CXCk_NdScan 	  0x27  //	ȡ����·����


#define  c11s_DCk_DirDef 	 0x18  //��ѯר������
#define  c11s_DCk_BusPro    0x1A  //��ѯ�����̶�Ӧ��ϵ

#define  c11s_DCk_SoftVer   0x2A   //��ѯ�����̶�Ӧ��ϵ
#define  c11s_DS_GasAuto   0x2e   //��������Զ�����
 

//Һ����ת�������忨��Ϣ
#define  c11s_WBI_Fire 	     0x30  //����������
#define  c11s_WBI_Ans 	     0x31  //��������Ӧ�� 
#define  c11s_WBI_ClrAns     0x32  //��������Ӧ����
#define  c11s_WBI_Fault 	   0x33  //������������ 
#define  c11s_WBI_ClrFault   0x34  //�����������ϻָ�
#define  c11s_WBI_Stop       0x35  //��������ֹͣ
#define  c11s_WBI_Star       0x36  //������������
#define  c11s_WBI_Delay      0x37  //����������ʱ

//Һ���巢�����Զ�״̬ 
#define  c11s_BI_AuMa       0x70  //�㲥���Զ�״̬	  
#define  c11s_BI_AuMaV      0x0c  //�ֶ������Զ�����

//Һ����ת���ļ�
#define  c11s_FC_Pro        0x04  //�·�����ļ�
#define  c11s_FC_DirDef     0x05  //�·������������


//�¼��忨���͵���Ϣ
#define  c11s_DI_SofVer     0x7a  //����汾��Ϣ
#define  c11s_DI_MdDelay    0x7b  //������ʱ��Ϣ
#define  c11s_DI_Delay      0x7c  //������ʱ��Ϣ
#define  c11s_DI_AuMa       0x7d  //�忨���Զ�״̬�ϱ�

//��·����Ϣ
#define  c11s_LBI_Fire       0x80  //����Ϣ
#define  c11s_LBI_Fault 	   0x81  //���� 
#define  c11s_LBI_ClrFault   0x82  //���ϻָ�
#define  c11s_LBI_AuStar     0x83  //����
#define  c11s_LBI_AuStop     0x84  //ֹͣ	
#define  c11s_LBI_Ans 	     0x85  //Ӧ�� 
#define  c11s_LBI_ClrAns     0x86  //Ӧ����
#define  c11s_LBI_LpErr 	   0x87  //��·����
#define  c11s_LBI_ClrLpErr   0x88  //��·���ϳ���
#define  c11s_LBI_LostAns    0x89  //Ӧ��ȱʧ

#define  c11s_LBI_MaStar     0x90  //�ֶ�����
#define  c11s_LBI_MaStop     0x91  //�ֶ�ֹͣ

#define  c11s_LBI_ClrInsul     0x97  //�ڵ��Ѿ��Ǽ�
#define  c11s_LBI_HasInsul     0x98  //�ڵ��Ѿ��Ǽ�

#define  c11s_LBI_HasReg     0x99  //�ڵ��Ѿ��Ǽ�
#define  c11s_LBI_NdFault    0x9c  //��ַ�й���     ������Ϣ��ʾ

#define  c11s_LBI_AnNdSta    0xA1  //�ش�ڵ�״̬���� 
#define  c11s_LBI_AnNdCur    0xA0  //�ش�ڵ�״̬���͡����ݲ�ѯ��ģ����
	
#define  c11s_FI_LpReg      0x02 //��·�Ǽ��ļ� 
#define  c11s_FI_Pro        0x05 //��������ļ�
#define  c11s_FI_LpScan     0x08 //��·����ļ� 
#define  c11s_FI_DirDef     0x09 //�����̻�·�Ǽ��ļ�
#define  c11s_FI_LpPanReg   0x0b //��·��Ǽ��ļ� 



//CD8  ����Ϣ
#define  c11s_DirFlg        0xf2 //�����̱�־λ

#define  c11s_DDI_MaStar     0x51  //�ֶ�����
#define  c11s_DDI_MaStop     0x52  //�ֶ�ֹͣ 
#define  c11s_DDI_Ans 	     0x53  //Ӧ�� 
#define  c11s_DDI_ClrAns     0x54  //Ӧ����
#define  c11s_DDI_AuStar     0x55  //����
#define  c11s_DDI_AuStop     0x56  //ֹͣ
#define  c11s_DDI_Delay      0x57  //������ʱ
#define  c11s_DDI_LostAns    0x58  //Ӧ��ȱʧ
#define  c11s_DDI_Fault 	   0x59  //��·����
#define  c11s_DDI_ClrFault   0x5A  //��·���ϳ���

//CK50  ����Ϣ
#define  c11s_DBI_MaStar     0x02  //�ֶ�����
#define  c11s_DBI_MaStop     0x03  //�ֶ�ֹͣ 
#define  c11s_DBI_AnsPro     0x9d  //�ش��Ӧ��ϵ
 

//CE4  ����Ϣ
#define  c11s_GasFlg            0xfA  //����̱�־λ

#define  c11s_GDI_Faule         0x01 //����
#define  c11s_GDI_FauleClr      0x02 //���ϻָ�
#define  c11s_GDI_OpAns         0x03 //�����ش�
#define  c11s_GDI_OpAnsClr      0x04 //�����ش��� 
#define  c11s_GDI_SLStar        0x05 //��������
#define  c11s_GDI_SLStop        0x06 //����ֹͣ 
#define  c11s_GDI_DvStar        0x07 //����豸����
#define  c11s_GDI_DvStop        0x08 //����豸ֹͣ
#define  c11s_GDI_ZnStar        0x09 //����������
#define  c11s_GDI_ZnStop        0x0A //������ֹͣ
#define  c11s_GDI_OpStar        0x0B //��������  
#define  c11s_GDI_Contrl        0x0C //���Ʒ�ʽ

#define  c11s_GAM_Auto          0x01 //�Զ���ʽ
#define  c11s_GAM_Manu          0x02 //�ֶ���ʽ
#define  c11s_GAM_Extn          0x03 //Զ�̷�ʽ 

//Ck50  ��������Ϣ
#define  c11s_BDC_MaStar        0x02  //�ֶ���������
#define  c11s_BDC_MaStop        0x03  //�ֶ�ֹͣ����
#define  c11s_BDI_BusPro        0x9D  //���������̰�����Ӧ��ϵ 

//��CAN ��Ϣ
#define  cw11s_BC_Reset	      1	     //��λ
#define  cw11s_BC_MaStar      0x02  //�ֶ���������
#define  cw11s_BC_MaStop	    0x03  //�ֶ�ֹͣ����
#define  cw11s_BC_AutoOn	    0x04  //�Զ�������
#define  cw11s_BC_Insul       0x05   //����
#define  cw11s_BC_ClrInsul	  0x06   //�������

#define  cw11s_BC_CkLed        7	    //����Ƽ� 
#define  cw11s_BC_AnsCkLed     0x08   //���Ϳ���Լ�����
#define  cw11s_BC_AutoReg      0x09   //�Զ��Ǽǹ㲥

#define  cw11s_BC_SLAct        0x0c   //��������
#define  cw11s_BC_TimeYMD      0x0d   //��CAN�㲥ʱ��  ������
#define  cw11s_BC_TimeHMS      0x0e   //��CAN�㲥ʱ��  ʱ����

#define  cw11s_BC_CkGasAuto    0x0f   //��CAN��ѯ������Զ�״̬ 
#define  cw11s_BC_SetGasAuto   0x2e   //��CAN��ѯ������Զ�״̬ 
#define  cw11s_BC_AnsGasAuto   0x2f   //�ش���CAN��ѯ������Զ�״̬��� 1~8 
//��ֹ��11s/sc ���Ӱ��
#define  cw11s_BC_AnsGasAuto1  0x30   //�ش���CAN��ѯ������Զ�״̬��� 9~14


#define  cw11s_BI_PanSta	    0x70  //��״̬
#define  cw11s_BI_MPowSta     0x71  //����״̬
#define  cw11s_BI_BPowSta	    0x72  //����״̬
#define  cw11s_BI_24VPowSta	  0x74  //24V��ѹ���

#define  cw11s_BI_MachDelay       0x7b  //���ͱ�����ʱ��Ϣ
#define  cw11s_BI_MachLstAns      0x7f  //���ͱ���Ӧ��ȱʧ
#define  cw11s_BI_MachLsAns       cw11s_BI_MachLstAns
#define  cw11s_BI_MaunAlarm       0x8b//���ͱ�������� 


#define  c11s_Fault_Ocu       0x80  //���Ϸ���
#define  c11s_Fault_Clr       0x90  //���ϳ���   
/*******************************************************************/
/******************       ���ݽṹ�����     *********************/
/*******************************************************************/


/*******************************************************************/
/****************     ���г�Ա����,����������     ******************/
/*******************************************************************/
//public:


/*******************************************************************/
/********************* ˽�г�Ա����,����������    *******************/
/*******************************************************************/
//Private:
#ifdef  CCan_11S_Def_C   




#endif
#endif
