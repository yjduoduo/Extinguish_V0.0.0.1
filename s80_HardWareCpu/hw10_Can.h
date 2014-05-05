#ifndef __hw10_Can_H__
#define __hw10_Can_H__
/******************************************************************************
* @file    hw10_Can.h
* @author  yx
* @version V1.0
* @date    2013-07-01
* @Cpu     LPC177x_8x   
* @brief   
* 
#include  "hw10_Can.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

#include  "lpc177x_8x_can.h" 
#include  "LPC177x_8x.h"

/*================= extern ============================================*/
#ifdef  __hw10_Can_C__
#define EX_hw10_Can
#else
#define EX_hw10_Can extern 
#endif
/*================= 常数 ============================================*/

#define U_PERI_CAN1_ID		  (CAN_1) // 只是重命名
#define U_PERI_CAN2_ID		  (CAN_2) // 不要改动

/*================= 结构体定义 ======================================*/

/*================= 公有结构变量声明 ================================*/
/*================= 私有函数声明- 测试 ====================================*/
#ifdef  __hw10_Can_C__

	#if U_SYS_Test_CanHw == 1


void recordIntStatuInit(U8 canPeriId);
void recordInsStatus(U8 canPeriId, U32 IntStatus);
	#endif // U_SYS_Test_CanHw 

#endif  //__hw10_Can_C__
/*================= 私有函数声明 ====================================*/
#ifdef  __hw10_Can_C__

void canRegi_PeriId_Clr_MsgTxRx(U8 canPeriId);
void canRegi_buf_Clr_MsgTxRx(U8 peri_can_buf_id);
void canRegi_Clr_1Msg(CAN_MSG_Type *pMsg);

CAN_MSG_Type *pGetCanRegi_RxBuf(U8 canPeriId);
U8 canRegi_GetBuf_FromPeriId(U8 canPeriId);

extern void canRegi_task_SetTxIdle(U8 canPeriId);
extern void canRegi_task_ClrTxIdle(U8 canPeriId);
extern unsigned char bCanRegi_task_TxIdle(U8 canPeriId);

void canRegi_ArbitrationLost_IntSet(U8 canPeriId);
void canRegi_BusError_IntSet(U8 canPeriId);
void canRegi_ErrorWarning_IntSet(U8 canPeriId);
void canRegi_JdgError(U8 canPeriId, U32 IntStatus);

// 包含 接收 和 error处理。
void canRegi_Interupt(U8 canPeriId); // 中断处理

#endif  //__hw10_Can_C__
/*================= 公有函数声明 ====================================*/
//EX_hw10_Can 

// IN: canPeriId：lpc177x_8x_can.h里定义的id; U_PERI_CAN1_ID, U_PERI_CAN2_ID
// IN: baudrate_us, 波特率，单位us. 定义 1bit的长度。
extern void CanRegi_Init(U8 canPeriId, U32 baudrate_us);
extern void CanRegi_Close(U8 canPeriId);

// Int:
extern void CanRegi_Int_Enable(U8 canPeriId);
extern void CanRegi_Int_Disable(U8 canPeriId);

// get 最后发送的一帧，driver结构
extern CAN_MSG_Type *pGetCanRegi_TxBuf(U8 canPeriId);

// 判断CAN寄存器，是否正在发送
extern BOOL bCanRegi_Tx_Idle(U8 canPeriId);

// void  CAN_IRQHandler(void);  // 中断处理

// 发送: 判断 can的Tx状态寄存器：
extern BOOL CanRegi_Send(U8 canPeriId, CAN_MSG_Type *pMsg);


/******************************************************************************
// END :
******************************************************************************/
#endif // __hw10_Can_H__

