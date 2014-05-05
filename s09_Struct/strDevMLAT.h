#ifndef __strDevMLAT_H__
#define __strDevMLAT_H__
/******************************************************************************
* @file    strDevMLAT.h
* @author  yx
* @version V1.0
* @date    2013-07-01
* @brief   DEV�Ľṹ ϸ�ڶ��塣 subject to "strDevice.h";
* 
#include  "strDevMLAT.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

/*================= ���� ============================================*/

/******************************************************************************
* FUNC: // DEV �ṹ
******************************************************************************/

enum emEvtSubject{
	U_EVT_SUBJECT_FIELD = 0, // ����·�ֳ������ķ�ʽ��
	U_EVT_SUBJECT_BOARD = 1  //��������������ֻ��U_EVT_SUBJECT_FIELD�жϡ�
};

/*================= ���нṹ�������� ================================*/
//modu, mduLine, 
#pragma pack(1)	
typedef struct{
	
	U32 channel:6; //1~
	U32 field:9;		//1~ //mduLine  //�����ࡣ�������ֳ�����,�в�ͬ�Ķ��塣 
	
	//���½ṹ���ܱ�,���ƿɱ䡣
	U32 eventSubject:1; 	// U_EVT_SUBJECT_FIELD, U_EVT_SUBJECT_BOARD ����������
	U32 boardLoop:4;	//1~  //���ڻ�·-num,  //modu
	U32 pnSequ:7;  		//1~ //panel�������-num, 128
	U32 pnType:5;  		//0~ //panel����  // emPanelSign 
	
	U8  machine;
}TCommonMLAT_st; //machine-loop-addr-channel
#pragma pack()	
//���ı��ֶΣ���Ҫ�� cstStDevStructProp[];

/*=================  ======================================*/
#pragma pack(1)	
typedef struct{
	
	U32 state:6; 
	U32 mduLine:9;  //  
	
	//���½ṹ���ܱ�,���ƿɱ䡣
	U32 eventSubject:1; // U_EVT_SUBJECT_FIELD, U_EVT_SUBJECT_BOARD
	U32 modu:4; //1~ //��Ԫ�ڷ��� 
	U32 pnSequ:7; //1~ //panel�������-num, 128
	U32 pnType:5; //0~ //panel����  // emPanelType
	
	U8  machine;
}TModuMLAT_st; //machine-loop-addr-channel
#pragma pack()



/******************************************************************************
* FUNC: // Dev �ṹ���item�� max, mask
******************************************************************************/
/*=================Dev ���� ============================================*/
enum emDevItem{ // U8 mDevItem;
	U_DEV_ITEM_Machine = 0,
	U_DEV_ITEM_pnType = 1,
	U_DEV_ITEM_pnSequ = 2,
	U_DEV_ITEM_modu = 3,
	U_DEV_ITEM_evtSubject = 4,
	U_DEV_ITEM_mduLine = 5,
	U_DEV_ITEM_field = 6,
	U_DEV_ITEM_channel = 7
	
};
#define U_DEV_ITEM_MAX  8  
	
// TDevStructProp  cstStDevStructProp[U_DEV_ITEM_MAX];

/******************************************************************************
* FUNC: // mduLine ��· �� �¼� ����
******************************************************************************/

//==== << pDev->pnModu.mduLine ===========	
//ʵ�ʵİ��Ϸ�������·  //
//U_EVT_SUBJECT_FIELD �൱���ֳ���������
enum emMduLineFunc{  
	//����  �ο�ͨѶЭ��
	U_Drt_MduFunc_Action = 0,
	U_Drt_MduFunc_Stop = 1,
	U_Drt_MduFunc_Ack = 2,
	U_Drt_MduFunc_AckRstr = 3, //��������
	U_Drt_MduFunc_AckMiss = 4, //����ȱʧ
	
	U_Drt_MduFunc_MAX = 5,
	
	//�������  �ο�ͨѶЭ��
	U_Extg_MduFunc_Action = 0,
	U_Extg_MduFunc_MAX = 3
	
};
	
//==== << pDev->pnModu.mduLine ===========	
//����ĸ����ϵ��¼�. ע��ͬ����¼������Ͳ�����ͬ��
// U_EVT_SUBJECT_BOARD 
enum emMduLineEvtFunc{
	U_MduFunc_BoardNoCommunicate = 0x10,
	
	//��Դ mduLine
	U_Power_MduFunc_pwrMain = 0,
	U_Power_MduFunc_pwrBty = 1,
	
	//flsItem
	U_Fls_MduFunc_Config = 0x20,
	
	//��ʾ��Ԫ��
	U_MduLine_Print = 0x30,
	
	
	U_MduLine_Invalid = 0x1FF
};

/******************************************************************************
// END :
******************************************************************************/
#endif // __strDevMLAT_H__

