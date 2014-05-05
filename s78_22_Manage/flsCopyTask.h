#ifndef __flsCopyTask_H__
#define __flsCopyTask_H__
/******************************************************************************
* @file    flsCopyTask.h
* @author  yx
* @version V1.0
* @date    2013-07-23
* @brief   
* 
#include  "flsCopyTask.h"
******************************************************************************/
//
#include  "prjCompileCon.h"
#include  "strFlsAdrDef.h"
#include  "bufCircle.h"

/*================= extern ============================================*/
#ifdef  __flsCopyTask_C__
#define EX_flsCopyTask
#else
#define EX_flsCopyTask extern 
#endif
/*================= ���� ============================================*/
enum emFlsCopyStep{
	U_FlsCopy_step_write,
	U_FlsCopy_step_sectNext,
	U_FlsCopy_step_finish,
};
/*================= �ṹ�嶨�� ======================================*/

/*================= ���нṹ�������� ================================*/

#define U_FlsCopy_Item_MAX    10 
#define U_FlsCopy_Once_MAX    4


typedef struct
{
	U8 taskId;  //������ʾ���񣬻򴮿�ͨѶ����
	U8 flsId;
	U8 mFlsItemFrom;
	U8 mPartFrom;
	U8 mFlsItemDest;
	U8 mPartDest;
	
}TFlsCopyBuf_st;  //ÿ���������һ����

typedef struct
{
	U8 bOpeaIng;
	U8 step;
	TFlsCopyBuf_st  nowBuf; // -> stCopyBuf[]
	
	U32 sectAdr_From;
	U32 sectAdr_Dest;
	TFlsItemAddr stChipAdrSE_From;
	TFlsItemAddr stChipAdrSE_Dest;
	
}TFlsCopyTask_st;  //

/*================= ˽�к������� ====================================*/
#ifdef  __flsCopyTask_C__
TBufCircle  vCircleFlsCopyBuf; //
TFlsCopyBuf_st  stCopyBuf[U_FlsCopy_Item_MAX];

TFlsCopyTask_st stCopyTask;

static void flsCopy_SetIdle(void);
static void flsCopy_sect_head(void);

// ���������ϣ�����ʷ��¼��
static BOOL flashError_Item_toEvtBuf(U8 flsItem, U8 bErrType);
static BOOL flashError_ItemPart_toEvtBuf(U8 flsItem, U8 mPart, U8 bErrType);

// clr one buf TFlsCopyBuf_st :
void init_FlsCopyOneBuf(TFlsCopyBuf_st *pOne);

// Copy����
// ֪ͨ���û���壬��Ϊ���ᱻ��ʾ��
// Ӧ���ǽ���ʷ��¼��
static void flsCopy_NotificatResult(U8 bSucc);

// * FUNC: // �жϸ�flsItem�Ƿ��д�,�д�->buf[]: 
// histǰ���ж�FlsItem_State��
U32 flsCopy_checkErr_preHist(void);

// * FUNC: // �жϸ�flsItem�Ƿ��д�,�д�->buf[]: 
// hist���ж�FlsItem_State��
void flsCopy_checkErr_hist(void);


// ����������Erase.
static void flsCopy_checkErr_ItemErase(U8 flsItem);
static void flsCopy_checkErr_ItemPartErase(U8 flsItem, U8 mPart);
// ����������Copy.
static void flsCopy_checkErr_ItemCopy(
						U8 mFlsItemFrom, U8 mPartFrom,
						U8 mFlsItemDest, U8 mPartDest);
// ��ʷ��¼��ȷ���ж���ָ��error��
// *  OUT: FALSE = �д���
static BOOL flsCopy_checkErr_hstPt(U8 mHistCls, U8 mHistPart);

#endif  //__flsCopyTask_C__

/*================= ���к�������-lib�ⲿ  ====================================*/
//EX_flsCopyTask 
//���������ֹ��
extern void SetAllow_FlsCopy_CheckItemError(void);
extern void SetForbid_FlsCopy_CheckItemError(void);
extern BOOL bFlsCopy_Allow_CheckItemError(void);
/*================= ���к�������-lib�ڲ�  ====================================*/
//EX_flsCopyTask 

extern void Init_FlsCopyTask(void);

// -> BUF[]
extern BOOL FlsCopy_New(U8 mFlsItemFrom, U8 mPartFrom, 
					  U8 mFlsItemDest, U8 mPartDest, 
					  U8 taskId, U8 flsId);
extern BOOL FlsCopy_ItemPart_New(U8 mFlsItem, U8 mPartFrom, 
						U8 mPartDest, U8 taskId, U8 flsId);
extern BOOL FlsCopy_Item_New(U8 mFlsItemFrom, U8 mFlsItemDest, 
					  U8 taskId, U8 flsId);

//�ж�mFlsItem error:
extern void FlsCopy_CheckError(void);

//
extern BOOL bFlsCopyBuf_Empty(void);
extern BOOL bFlsCopy_isIdle(void);

extern BOOL FlsCopy_Start(void);
extern void FlsCopy_Exec(void);


/******************************************************************************
// END :
******************************************************************************/
#endif // __flsCopyTask_H__

