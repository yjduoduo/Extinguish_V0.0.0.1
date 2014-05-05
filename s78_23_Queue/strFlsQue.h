#ifndef __strFlsQue_H__
#define __strFlsQue_H__
/******************************************************************************
* @file    strFlsQue.h
* @author  yx
* @version V1.1
* @date    2013-07-23
* @brief   �������͵Ĵ洢���ж����ԣ����ҺͶ�ȡָ�롣
* @Slave   flsInqPoint.c
* 

V1.1, ADD bAdr_Mid_QueHeadEnd();  2013.7.23, by yx;


#include  "strFlsQue.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

#include  "strFlsAdrDef.h"
/*================= extern ============================================*/
#ifdef  __strFlsQue_C__
#define EX_strFlsQue
#else
#define EX_strFlsQue extern 
#endif
/*================= ���� ============================================*/


/*================= �ṹ�嶨�� ======================================*/

/*================= ���нṹ�������� ================================*/

typedef struct{
	//flsAddress:
	U32 headAdr; //Flash�洢ָ�롣
	U32 endAdr; //Flash�洢ָ�롣
}TFlsQueuePoint_st;

typedef struct{
	U8 mFlsItem;
	BOOL bIsQueue;
	U32 pointId;   // flsItem�Ĵ洢���������͵ģ��źš�
	U32 itemBytes; // 1�����ֽ���
	U32 sectBytes; // 1 Sector ���ֽ���
	// sectorMax ���á����� != sectEnd���жϣ�Ϊ������̬����׼����
	TFlsItemAddr stAdr; // chip, adrS, adrE.
}TFlsQueueProp; //�������͵�flsItem�洢

/*================= ˽�к������� ====================================*/
#ifdef  __strFlsQue_C__

#endif  //__strFlsQue_C__
/*================= ���к�������-lib�ڲ� ====================================*/
//EX_strFlsAdrDef

// ��ȡ head,end; 
extern U32 GetFlsQueHeadAdr(U8 mFlsItem, U8 mPatNum);
extern U32 GetFlsQueEndAdr(U8 mFlsItem, U8 mPatNum);
extern BOOL GetFlsQueHeadEndAdr(U8 mFlsItem, U8 mFlsPart,
				TFlsQueuePoint_st *pRtnHeadEnd);

// ���� head,end; 
extern void SetFlsQueHeadAdr(U8 mFlsItem, U8 mPatNum, U32 flsAdr);
extern void SetFlsQueEndAdr(U8 mFlsItem, U8 mPatNum, U32 flsAdr);

// �Ƚ�2�� head & end �Ƿ�equal:
extern BOOL bEqu_FlsQueHeadEnd(TFlsQueuePoint_st *p1, 
					           TFlsQueuePoint_st *p2
							   );

// CLR: head & end = stAdr.adrS
extern void ClrOneItem_FlsQueHeadEnd(U8 mFlsItem, U8 mPart);
extern void ClrAll_FlsQueHeadEnd(void);

// * FUNC: // ��ȡflash���ж�queue.head & end.
// *  OUT: SetFlsQueHeadAdr();  SetFlsQueEndAdr();
// *Slave: flsInqPoint.c
extern void InitAll_FlsQueHeadEnd(void);
extern void InitOneItem_FlsQueHeadEnd(U8 mFlsItem, U8 mPart);

// if ��ַ�� head,end֮��:
extern BOOL bAdr_Mid_QueHeadEnd(U8 mFlsItem, U8 mPart, U32 flsAdr);

/*================= ���к�������-lib�ڲ� ====================================*/
//�ж���sectorStart + CRC ���綨��
enum emFlsQueSectorState{  //U8 mFlsHistState;
	
	U_FlsQueSectorSta_NotMe,       //����space
	U_FlsQueSectorSta_SectIsFull,  //ȫ����ʷ��¼
	U_FlsQueSectorSta_SectNotFull, //����
	
};
	
// * FUNC: // �ж�mAdr����sector�洢�������
// *  OUT:  emFlsQueSectorState
extern U8 FlsQueRd_JdgFlsSect(U8 chip, U32 mAdr, U8 mFlsItem);

// 1����У����ȷ, crc;
extern BOOL bFlsQueRd_OneItem_isOK(U8 chip, U32 mAdr, U8 mFlsItem);

/*================= ���к�������-lib�ڲ� ====================================*/
//EX_strFlsAdrDef

//�������� TFlsQueueProp :
extern BOOL FlsQueue_Prop(U8 mFlsItem, U8 mFlsPart, 
								TFlsQueueProp *pProp
								);

// if �� Queue���ʹ洢��
extern BOOL bFlsItem_isQueue(U8 mFlsItem);
// ÿ�����ֽ���:
extern U32 FlsItemQue_itemBytes(U8 mFlsItem);
// flsItem�Ĵ洢���������͵ģ��ź�:
extern BOOL getFlsQueue_pointId(U8 mFlsItem, U32 *pRtnPointId);



/******************************************************************************
// END :
����ǰһ����Ч�ĵ�ַ��
����ָ���ʼ����
******************************************************************************/
#endif // __strFlsQue_H__

