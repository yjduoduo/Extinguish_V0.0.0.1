#ifndef __flsWrApplyBuf_H__
#define __flsWrApplyBuf_H__
/******************************************************************************
* @file    flsWrApplyBuf.h
* @author  yx
* @version V1.0
* @date    2013-07-23
* @brief   ���flsWrApplySave.c�� ��buf[]. 
		IN: FlsWr_AlyBuf_NewApply();
		��ʵ�����ݣ���Ϊ��item�ĳ������ܴ����Բ��� �����洢��
* @master: "flsWrApplySave.c"
* 
*
#include  "flsWrApplyBuf.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

/*================= extern ============================================*/
#ifdef  __flsWrApplyBuf_C__
#define EX_flsWrApplyBuf
#else
#define EX_flsWrApplyBuf extern 
#endif
/*================= ���� ============================================*/
//#define 

/*================= ���� ============================================*/
// #if U_SYS_Test_FlsApplyBuf == 1
	// #define U_FlsAly_One_Head_Bytes  1  //ÿ�η��䶼��Head;
// #else
	// #define U_FlsAly_One_Head_Bytes  8  //ÿ�η��䶼��Head;
// #endif

typedef union
{
	U32 dword[2];
	struct{
		U32 strFlsItemBytes; //������head����,������
		U8 mFlsItem;
		U8 taskId;  //������ʾ���񣬻򴮿�ͨѶ����
		U8 flsId;
	}head;
}TFlsAlyOneHead_un; //�� task���������á�

//�����Ǹ���ͬ����ҪwrFlash��struct: "strFlsItmStruct.h"

/*================= ����-����ռ� ============================================*/

#if U_SYS_Test_FlsApplyBuf == 1
	#define U_FlsAly_BufByte_MAX  (0x80 ) // U32 mFlsAppBytes;
	#define U_FlsAly_SecNum_MAX    10   // U32 mFlsAppSec;
#else
	#define U_FlsAly_BufByte_MAX  (8 * KBytes ) // U32 mFlsAppBytes;

	//���������������С���䵥λ����
	#define U_FlsAly_SecNum_MAX    200   // U32 mFlsAppSec;
#endif //U_SYS_Test_FlsApplyBuf

typedef struct
{
	U32 strFlsItmByte;
	U8 mFlsItem;
	U8 taskId;  //������ʾ���񣬻򴮿�ͨѶ����
	U8 flsId;
	
	// void *pAppBuf;  //��Ӧ��ͬ�����
	
	U32 adrS; //��Ӧ vFlsAppBuf[]
	U32 adrE;
}TFlsAlySec_st;  //ÿ���������һ����


/*================= �ṹ�嶨�� ======================================*/

/*================= ���нṹ�������� ================================*/

/*================= ˽�к������� ====================================*/
#ifdef  __flsWrApplyBuf_C__

#endif  //__flsWrApplyBuf_C__

/*================= ���к�������-lib�ڲ� ====================================*/
//EX_flsWrApplyBuf 

extern void Init_FlsApplyBuf(void);


// * FUNC: // ����ռ�, ��Ҫд�������->buf
// *   IN:  	(bSaveItemValid(mFlsItem))
		// taskId < U_SYS_TASK_ID_MAX
		// flsId
		// pSrc ->  TFlsSysSet_un ...
// *  OUT: U_SUCC
extern BOOL FlsWr_AlyBuf_NewApply(U8 mFlsItem, U8 taskId, 
										U8 flsId, U8 *pSrc);


// * FUNC: // ��дflash�����񣬶�����
// *   IN:
// *  OUT: U_SUCC
		// *pByteDest.. = ���ṹ������
extern BOOL FlsWr_AlyBuf_Read(U8 *pByteDest, 
							 TFlsAlyOneHead_un *pRtnAlyHead);

extern BOOL bFlsWr_AlyBuf_Empty(void);


/******************************************************************************
// END :
******************************************************************************/
#endif // __flsWrApplyBuf_H__

