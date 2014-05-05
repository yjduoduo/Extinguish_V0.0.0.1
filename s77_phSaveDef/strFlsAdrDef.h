#ifndef __strFlsAdrDef_H__
#define __strFlsAdrDef_H__
/******************************************************************************
* @file    strFlsAdrDef.h
* @author  yx
* @version V1.4
* @date    2013-10-24
* @brief   flash�ռ����
* 
* @Version history
  
* V1.5 2013-11-02
*		����: ��ʷ��¼�ĵ�ַ�Ķ������
*		add: bCheckSaveItemConstDef();
* V1.4 2013-10-24
*		add: U_FlsSave_RelateDete,  U_FlsSave_ExtgZoneConfig, 
*			    U_FlsSave_MachAlarmNote;
* V1.3  2013.9.22 22:10
*		ȥ�� getFlsItem_HistSectorMax(), ����ʷ��¼�Ĵ洢�ռ���ܲ�һ�¡�
* V1.2   2013-09-04, yx:
*		add: bEquFlsItemAddr();  bInFlsItemAddr();   
*		add: FlsItem_PartMax();
* V1.1 2013.7.15, yx: ��cstStFlashAssign[]�İ��Ų�����emFlsItem��˳��
* 
#include  "strFlsAdrDef.h"
******************************************************************************/
//
#include  "prjCompileCon.h"
#include  "historyClsDef.h"


/*================= extern ============================================*/
#ifdef  __strFlsAdrDef_C__
#define EX_strFlsAdrDef
#else
#define EX_strFlsAdrDef extern 
#endif
/******************************************************************************
* FUNC: //

******************************************************************************/
extern U8 getFlsItem_PnConfig(void);
extern U8 getFlsItem_MachProbat(void);
extern U8 getFlsItem_MeStatus(void);
extern U8 getFlsItem_UserLogin(void);
extern U8 getFlsItem_NetMachine(void);

extern U8 getFlsItem_Disable(void);
extern U8 getFlsItem_Field(void);

extern U8 getFlsItem_Note(void);
extern U8 getFlsItem_MachAlarmNote(void);
#if U_SYS_Test_Flash_InqPoint == 1
extern U8 getFlsItem_Sim(void);
#endif
extern U8 getFlsItem_LinkProg(void);
extern U8 getFlsItem_ManuProg(void);
extern U8 getFlsItem_PowerOff(void);

extern U8 getFlsItem_RelateDete(void);
extern U8 getFlsItem_ExtgZoneConfig(void);



// * FUNC: ��ʷ��¼֮ǰ��flsItem �� MAX.
// 		��ʷ��¼��ΪҪ��ָ��洢��Ӧ�����⴦��
extern U8 getFlsItem_BeforeHist(void);

extern BOOL bFlsItemIs_OnePageSave(U8 mFlsItem);


/*================= //��ʷ��¼�� ======================================*/

extern U8 getFlsItem_hist(U8 mHistCls);
extern BOOL bFlsItemIsHist(U8 mflsItem);
extern U8 FlsHistPartMax(void);

/*================= //��ʷ��¼ָ�룺 ======================================*/

extern BOOL bFlsItemIs_hstPart0Point(U8 mFlsItem);
extern BOOL bFlsItemIs_hstPart1Point(U8 mFlsItem);
extern BOOL bFlsItemIs_hstPoint(U8 mflsItem);
extern U8 getFlsItem_hstPart0Point(U8 mHistCls);
extern U8 getFlsItem_hstPart1Point(U8 mHistCls);
extern U8 getFlsItem_hstPoint(U8 mHistCls, U8 mHistPart);

extern U8 FlsHistPointPartMax(void);



/*================= �ṹ�嶨�� ======================================*/


#pragma pack(1)	
typedef struct{
	U8 chip;
	U32 adrS;
	U32 adrE;
}TFlsItemAddr;
#pragma pack()	


/*================= ���нṹ�������� ================================*/

/*================= ���к������� ====================================*/

#if U_SYS_Test_FlsAdrDef == 1
extern void Sim_FlsAdrDef(void);
#endif //U_SYS_Test_FlsAdrDef
/*================= ˽�к�������====================================*/
#ifdef  __strFlsAdrDef_C__
BOOL bFls_item_share_valid(U8 mFlsSequ, U8 mFlsPart);

#endif

/*================= ���к������� ====================================*/
//EX_strFlsAdrDef 

// ����ַ��Χ�Ķ����Ƿ���
extern BOOL bCheckSaveItemConstDef(void); 

extern U8 GetSaveItemMax(void);
extern BOOL bSaveItemValid(U8 mFlsItem);
extern U8 GetSaveItmPartMax(void);
extern U8 FlsItem_PartMax(U8 mFlsItem); // flsItem part max
extern BOOL bSaveItmPartValid(U8 mPart);

/*================= ���к������� ====================================*/
//EX_strFlsAdrDef 

extern BOOL bFlsItem_HaveShare(U8 mFlsItem); //

extern U32 getFlsItem_1SectorBytes(U8 mFlsItem);
extern U8 getFlsItem_SectorMax(U8 mFlsItem);

extern U32 getFlsItem_Chip(U8 mFlsItem, U8 mFlsPart);
extern U32 getFlsItem_AdrS(U8 mFlsItem, U8 mFlsPart);
extern U32 getFlsItem_AdrE(U8 mFlsItem, U8 mFlsPart);

extern BOOL getFlsItem_Addr(U8 mFlsItem, U8 mFlsPart, TFlsItemAddr *pRtnAdr);

// if ��Χ���:
extern BOOL bEquFlsItemAddr(TFlsItemAddr *pAdr1, TFlsItemAddr *pAdr2);
// if ��ַ�ڷ�Χ�ڣ�
extern BOOL bInFlsItemAddr(U32 nowAdr, TFlsItemAddr *pAdr);
extern BOOL bFlsItemIs_Disable(U8 mFlsItem);

/******************************************************************************
// END :
******************************************************************************/
#endif // __strFlsAdrDef_H__
