#ifndef __strDevice_H__
#define __strDevice_H__
/******************************************************************************
* @file    strDevice.h
* @author  yx
* @version V1.1
* @date    2013-10-24
* @brief   
*
* V1.1  2013-10-24
*		U_SYS_LOOP_MAX :  64 -> 4
* 		U_OneBoard_LOOP_MAX: 8 -> 1;
*		add: U_1ExtgLOOP_DETE_MAX, U_1ExtgLOOP_DeteLink_MAX;
* V1.0  2012-01-01
* 
#include  "strDevice.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

#include  "strDevMLAT.h" //dev����ϸ����
#include  "loopFieldTypeState.h" //��·�ֳ����������ͺ�״̬


/*================= extern ============================================*/
#ifdef  __strDevice_C__
#define EX_strDevice
#else
#define EX_strDevice extern 
#endif
/*================= ���� ============================================*/
//#define 
/*================= �ṹ�嶨�� ======================================*/

/*================= ���нṹ�������� ================================*/

#define U_DEV_ADDR_BYTE_MAX	   5

#pragma pack(1)	
typedef union{
	TCommonMLAT_st  stDete;  //stField
	TModuMLAT_st    pnModu;
	
}TDev_un;  //�ܿ��ܲ��� 4 bytes.
#pragma pack()	


/*=================Dev���� ���� ============================================*/
	//�ж�stDev�����ͣ��ǻ�����panel��panel.modu��64��·֮һ��
enum emDevClass{ 	//dev����	

	U_DEV_IS_Machine_TYPE	= 0x0, //������
	U_DEV_IS_Panel_TYPE		= 0x1, //����Ԫ��
	U_DEV_IS_PnModu_TYPE	= 0x3, //��Ԫ-·
	U_DEV_IS_ModuLine_TYPE	= 0x4, //��Ԫ-·-����
	U_DEV_IS_Dete_TYPE		= 0x2, //��·�ֳ�����
	U_DEV_IS_Channel_TYPE		= 0x5, //��·�ֳ�����
	U_DEV_TYPE_MAX			= 0x6 //
};


enum emDevNum{ // ��������
	
	U_SYS_LOOP_MAX 		= 4,	// U_OneBoard_LOOP_MAX * U_Board_LOOP_MAX	
	U_1LOOP_DETE_MAX 	= 0x100,
	U_1ExtgLOOP_DETE_MAX 	= 0x40,
	U_1ExtgLOOP_DeteLink_MAX 	= 200,
	U_1DETE_CHNL_MAX 	= 4,

	U_OneBoard_LOOP_MAX	= 0x01,
	U_OneBoard_DrtModu_MAX	= 0x08,
	U_OneBoard_ExtgModu_MAX	= 0x04,

	U_OneModLine_Drt_Dete_MAX	= 0x08,
	U_OneModLine_Extg_Dete_MAX	= 0x40,
	

	U_UNIT_PN_MAX 	= 0xFF //ALL
};
	
	
	
/*================= ˽�к������� ====================================*/
#ifdef  __strDevice_C__
#endif  //__strDevice_C__

/*=================  ====================================*/
#if U_SYS_Test_strDevice == 1 
EX_strDevice void Test_Dev(void);
#endif // U_SYS_SoftSimulatState

/*================= ���к������� - DEV ��� ====================================*/
//EX_strDevice 

extern U8 BuildToDev_Machine(U8 machine, TDev_un *pDev);

extern U8 BuildToDev_Panel(U8 machine, U8 pnType, U8 pnSequ, TDev_un *pDev);
extern U8 BuildToDev_Me_Panel(U8 pnType, U8 pnSequ, TDev_un *pDev);

extern U8 BuildToDev_PnModu(U8 machine, U8 pnType, U8 pnSequ, U8 moduNum, TDev_un *pDev);
extern U8 BuildToDev_Me_PnModu(U8 pnType, U8 pnSequ, U8 moduNum, TDev_un *pDev);

extern U8 BuildToDev_PnMduLine(U8 machine, U8 pnType, U8 pnSequ, U8 moduNum, U8 pnModuLine, TDev_un *pDev);
extern U8 BuildToDev_Me_PnMduLine(U8 pnType, U8 pnSequ, U8 moduNum, U8 pnModuLine, TDev_un *pDev);

extern U8 BuildToDev_DeteMLA(U8 machine, U8 loop, U32 addr, TDev_un *pDev);
extern U8 BuildToDev_Me_DeteMLA(U8 loop, U32 addr, TDev_un *pDev);

extern U8 BuildToDev_DeteMLAC(U8 machine, U8 loop, U32 addr, U8 channel, TDev_un *pDev);
extern U8 BuildToDev_Me_DeteMLAC(U8 loop, U32 addr, U8 channel, TDev_un *pDev);

extern U8 BuildToDev_Power(U8 machine, U8 power, TDev_un *pDev);
extern U8 BuildToDev_Me_Power(U8 power, TDev_un *pDev);

extern U8 BuildToDev_PnFlash(U8 machine, U8 pnType, U8 pnSequ, 
							U8 flsItem, U8 mPart, TDev_un *pDev);
extern U8 BuildToDev_Me_Flash(U8 flsItem, U8 mPart, TDev_un *pDev); //��������

/*================= ���к������� - �ж�DEV ====================================*/
//EX_strDevice 
extern BOOL bDevOk(TDev_un *pDev); // �Ա� DevSetInvalid();
extern BOOL bDevIsMachMe(TDev_un *pDev);
extern U8 JdgDevClass(TDev_un *pDev); // OUT:  emDevClass
extern BOOL bDeteHaveChannel(TDev_un *pDev);

extern U8 jdgDevItem_Legal(U8 mDevItem, U32 mChkItemNow); //ֻ���ж��Ƿ񳬳��ֶη�Χ��
extern U8 jdgDevItem_Dete_Legal(U8 loop, U32 addr);

/*================= ���к������� - ���������� ====================================*/
//EX_strDevice 
extern BOOL CacuDeteLoop_1toMax(TDev_un *pDev, U32 *pRtnLoop); //�����·�� 1~
extern BOOL CacuDrtLoop_1toMax(TDev_un *pDev, U32 *pRtnLoop); //������߻�·�� 1~
extern BOOL CacuExtgLoop_1toMax(TDev_un *pDev, U32 *pRtnLoop); //��������·�� 1~

//�����ֳ������� 0~12800
//��·  0~12800
extern BOOL CacuDevSequ_Dete_0toMax(TDev_un *pDev, U32 *pRtnSequ);
//��������ֳ������� 0~
extern BOOL CacuDevSequ_Drt_0toMax(TDev_un *pDev, U32 *pRtnSequ);
//���������ֳ������� 0~
extern BOOL CacuDevSequ_Extg_0toMax(TDev_un *pDev, U32 *pRtnSequ);

//���������ֳ������ź� 0~; ��·������-����������
extern BOOL CacuDevSequ_0toMax(TDev_un *pDev, U32 *pRtnSequ);


//ͨ���ܻ�·�ţ�����panel�ź�panel�ڵĻ�·�š�
extern void CacuDetePnSequAndBdLoop(U8 loop, 
							U8 *pRtnPnSequ, U8 *pRtnBdLoop
							);

/*================= ���к������� - DEV ��ʼ�� ====================================*/
//EX_strDevice 
extern void DevSetInvalid(TDev_un  *m_pDev); // �Ա� bDevOk();
extern void DevSet_all_FF(TDev_un  *m_pDev);
extern void DevSet_all_00(TDev_un  *m_pDev);

extern void DevSet_SimAdr(U8 mIniVal, TDev_un  *m_pDev);
extern void DevSet_all_test1234567(U8 mIniVal, TDev_un  *m_pDev); //������
	
/*================= ���к������� - DEV ���� ====================================*/
//EX_strDevice 
extern BOOL bDevCompare(TDev_un  *pDev1, TDev_un  *pDev2);
extern BOOL bDevCompMask(U8 mDevItem, TDev_un  *pDev1, TDev_un  *pDev2);


extern void ComposeDev_fromBytes(U8 *pByte, TDev_un  *pRtnDev);
extern void ComposeBytes_fromDev(TDev_un  *pDev, U8 *pRtnByte);
extern U32 ComposeDWord_fromDev_NoMachine(TDev_un  *pDev);

/******************************************************************************
// END :
******************************************************************************/
#endif // __strDevice_H__

