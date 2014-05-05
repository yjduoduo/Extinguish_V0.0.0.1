#ifndef __flsErase_H__
#define __flsErase_H__
/******************************************************************************
* @file    flsErase.h
* @author  yx
* @version V1.2
* @date    2013-9-22
* @brief   �������У���ִ��erase.
* @master  Ӧ�ó��� | �޸�ǰ�Ĳ�����
* @master   saveManage.c
* @in:     FlsErase_New() ����brother;  
*
* @version history
* V1.2��2013.9.22
*		�޸�FlsErase_WorkIng_MyFlsId(); FlsErase_HaveFinishPercent();
* V1.1  2013-9-3
*		��buf[out]�����ݣ�startʱ���浽stEraseTask.nowBuf��ʹ�á� 2013-9-3 
* 		���� mIntegratPart
* V1.0  2013-07-23

*	   
* 
#include  "flsErase.h"
******************************************************************************/
//
#include  "prjCompileCon.h"
#include  "strFlsAdrDef.h"
#include  "bufCircle.h"

/*================= extern ============================================*/
#ifdef  __flsErase_C__
#define EX_flsErase
#else
#define EX_flsErase extern 
#endif
/*================= ���� ============================================*/
//#define 
/*================= �ṹ�嶨�� ======================================*/

/*================= ���нṹ�������� ================================*/

#define U_FlsErase_Item_MAX    10   // U32 mFlsAppSec;
typedef struct
{
	U8 mFlsItem;
	U8 mPart;
	BOOL mIntegratPart; // TRUE=������part.
	U8 taskId;  //������ʾ���񣬻򴮿�ͨѶ����
	U8 flsId;
	TFlsItemAddr stEraseAdr;
	U8 percentS; // ���ܵ�flsId�������������İٷֱȣ�
	U8 percentE;
}TFlsEraseBuf_st;  //ÿ���������һ����

typedef struct
{
	U8 bOpeaIng;
	
	TFlsEraseBuf_st  nowBuf; // -> stEraseBuf[]
	
	U32 nowSectAdr;
	TFlsItemAddr stEraseAdr;
	
	U32 sectTotal;
	U32 sectHaveFinish;
}TFlsEraseTask_st;  //

/*================= ˽�к������� ====================================*/
#ifdef  __flsErase_C__

TBufCircle  vCircleFlsEraseBuf; //
TFlsEraseBuf_st  stEraseBuf[U_FlsErase_Item_MAX];

TFlsEraseTask_st stEraseTask;

void init_FlsEraseOneBuf(TFlsEraseBuf_st *pOne);
static void flsErase_SetIdle(void);
static void flsErase_NotificatResult(U8 bSucc);

// ������ϣ��޸�state �� queue.point.
static void flsErase_Finish(U8 bSucc);


static BOOL bFlsIdIsExistInBuf(U8 mFlsId, U32 *pRtnBuf);
static BOOL bFlsIdIsEraseIng(U8 mFlsId);

static BOOL flsErase_entryBuf(U8 mFlsItem, U8 mPart, 
					U8 taskId, U8 flsId, 
					TFlsItemAddr *pAdr,
					U8 percentS, U8 percentE);
#endif  //__flsErase_C__
/*================= ���к�������-lib�ڲ� ====================================*/
//EX_flsErase 

extern void Init_FlsEraseTask(void);

extern BOOL bFlsEraseBuf_Empty(void);
extern BOOL bFlsErase_isIdle(void);

extern BOOL FlsErase_Start(void);
extern void FlsErase_Exec(void);


/*================= ���к�������-lib�ⲿ ====================================*/
//EX_flsErase 

// add Erase FlsItem.Part.pAdr ���� -> eraseBuf[].
extern BOOL FlsErase_New(U8 mFlsItem, U8 mPart, 
						U8 taskId, U8 flsId,
						TFlsItemAddr *pAdr);
// add Erase FlsItem.Part ���� -> eraseBuf[].
extern BOOL FlsErase_ItemPart_New(U8 mFlsItem, U8 mPart, 
						U8 taskId, U8 flsId);
//��mFlsItem���� -> eraseBuf[].
extern BOOL FlsErase_Item_New(U8 mFlsItem, U8 taskId, U8 flsId); 

//�Ƿ�Erase FlsId, ������erase�������:
extern BOOL FlsErase_WorkIng_MyFlsId(U8 mFlsId);
//������ɵİٷֱ�
extern U8 FlsErase_HaveFinishPercent(U8 mFlsId); 

/******************************************************************************
// END :
******************************************************************************/
#endif // __flsErase_H__

