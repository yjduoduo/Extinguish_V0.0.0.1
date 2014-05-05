#define __hw10_Can_C__
/******************************************************************************
* @file    hw10_Can.c
* @author  yx
* @version V1.0
* @date    2013-07-01
* @Cpu     LPC177x_8x   
* @brief   CANӲ�������� 
		���漰Ӧ�ò㣬ֻ������� callBack.c
* @Master: CanHd_Interface.c
* @Slave:  hw00_CallBack.c
* 
******************************************************************************/
#include  "hw10_Can.h"

#include  "hw00_CallBack.h"
extern void CallBack_Can_RecNew(U8 canPeriId, U8 canMaskBuf, 
								CAN_MSG_Type *pCanMsg);

#include  "hw10_MaskCan.h"
//#include "incFile.h"	

extern void chkHd_Can__CanRx(U8 canPeriId);

/*================= ���� ============================================*/

enum emCanLogicId_ICanECan{  // U8 peri_can_buf_id
	U_Peri_Can1_Buf = 0, // CAN0 ����ӦӲ����
	U_Peri_Can2_Buf = 1, // CAN1
	
};
#define U_Peri_CanBuf_MAX  2

/*================= �ṹ���� ========================================*/

typedef struct{
	CAN_MSG_Type txFrm;
	CAN_MSG_Type rxFrm;
	
	BOOL bTxIdle;
	
	// THdCanFrame_st 
}TRegiCanTask_st;
/*================= ˽�нṹ�������� ================================*/

TRegiCanTask_st stRegiCan[U_Peri_CanBuf_MAX];
/*================= ���к������� ====================================*/

/*================= ˽�к������� ====================================*/

/*=================  ================================================*/
		
/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

// IN: canPeriId��lpc177x_8x_can.h�ﶨ���id; U_PERI_CAN1_ID, U_PERI_CAN2_ID
// IN: baudrate_us, �����ʣ���λus. ���� 1bit�ĳ��ȡ�
void CanRegi_Init(U8 canPeriId, U32 baudrate_us)
{
	#if U_SYS_Test_CanHw == 1
	recordIntStatuInit(canPeriId);
	#endif // U_SYS_Test_CanHw 
		
	canRegi_task_SetTxIdle(canPeriId);
	canRegi_PeriId_Clr_MsgTxRx(canPeriId);
	
	
	CAN_Init_ByTQ(canPeriId, baudrate_us);
	CAN_ModeConfig(canPeriId, CAN_OPERATING_MODE, ENABLE);

	//Enable Receive Interrupt
	CAN_IRQCmd(canPeriId, CANINT_RIE, ENABLE);	
	CAN_IRQCmd(canPeriId, CANINT_TIE1, ENABLE);	
	
	canRegi_ErrorWarning_IntSet(canPeriId);
	// CAN_IRQCmd(canPeriId, CANINT_BEIE, ENABLE); // bus error 	
	canRegi_BusError_IntSet(canPeriId);
	// CAN_IRQCmd(canPeriId, CANINT_EIE, ENABLE); // error or bus status changes 

	//Enable CAN Interrupt
	NVIC_EnableIRQ(CAN_IRQn);	 
	CAN_SetAFMode(CAN_ACC_BP);  //��·�����˲���
	  
}

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

// IN: canPeriId��lpc177x_8x_can.h�ﶨ���id; U_PERI_CAN1_ID, U_PERI_CAN2_ID
void CanRegi_Close(U8 canPeriId)
{
	CAN_DeInit(canPeriId);
}

/******************************************************************************
* FUNC: //  Int:
*   IN: canPeriId��lpc177x_8x_can.h�ﶨ���id;
*  OUT:  
******************************************************************************/
void CanRegi_Int_Enable(U8 canPeriId)
{
	NVIC_EnableIRQ(CAN_IRQn);
}

void CanRegi_Int_Disable(U8 canPeriId)
{
	NVIC_DisableIRQ(CAN_IRQn);
}

/******************************************************************************
* FUNC: //
*   IN:
*  OUT:  
U8 peri_can_buf_id;
	peri_can_buf_id = canRegi_GetBuf_FromPeriId(canPeriId);
******************************************************************************/

U8 canRegi_GetBuf_FromPeriId(U8 canPeriId)
{
	if(canPeriId == U_PERI_CAN1_ID)
	{
		return U_Peri_Can1_Buf;
	}
	else
	{
		return U_Peri_Can2_Buf;
	}
}

/******************************************************************************
* FUNC: // 
*   IN:
*  OUT: 
******************************************************************************/

void canRegi_PeriId_Clr_MsgTxRx(U8 canPeriId) 
{
U8 peri_can_buf_id;

	peri_can_buf_id = canRegi_GetBuf_FromPeriId(canPeriId);
	canRegi_buf_Clr_MsgTxRx(peri_can_buf_id);
}

void canRegi_buf_Clr_MsgTxRx(U8 peri_can_buf_id) 
{
	if(peri_can_buf_id < U_Peri_CanBuf_MAX)
	{
		canRegi_Clr_1Msg(&stRegiCan[peri_can_buf_id].rxFrm);
		canRegi_Clr_1Msg(&stRegiCan[peri_can_buf_id].txFrm);
	}
}

void canRegi_Clr_1Msg(CAN_MSG_Type *pMsg) 
{
	U32 i;
	pMsg->format = EXT_ID_FORMAT;
	pMsg->id = 0x00;
	pMsg->len = 0x00;
	pMsg->type = DATA_FRAME;
	
	for(i=0;i<4;i++)
	{
	    pMsg->dataA[i]= 0;
		pMsg->dataB[i]= 0;
	}
}

/******************************************************************************
* FUNC: // hw10_can�ڲ���txIdle��־�� get()δʵ��Ӧ�á�
		�ⲿ����Ӧ��bCanRegi_Tx_Idle()�õ�ʵʱ�ķ���״̬��
*   IN:
*  OUT: 
******************************************************************************/
unsigned char bCanRegi_task_TxIdle(U8 canPeriId)
{
U8 peri_can_buf_id;

	peri_can_buf_id = canRegi_GetBuf_FromPeriId(canPeriId);
	
	return stRegiCan[peri_can_buf_id].bTxIdle;
}

void canRegi_task_SetTxIdle(U8 canPeriId)
{
U8 peri_can_buf_id;

	peri_can_buf_id = canRegi_GetBuf_FromPeriId(canPeriId);
	
	stRegiCan[peri_can_buf_id].bTxIdle = TRUE;
}

void canRegi_task_ClrTxIdle(U8 canPeriId)
{
U8 peri_can_buf_id;

	peri_can_buf_id = canRegi_GetBuf_FromPeriId(canPeriId);
	
	stRegiCan[peri_can_buf_id].bTxIdle = FALSE;
	
}

/******************************************************************************
* FUNC: // ����: �ж� can��Tx״̬�Ĵ�����
*   IN:
*  OUT: 
******************************************************************************/
BOOL CanRegi_Send(U8 canPeriId, CAN_MSG_Type *pMsg)
{
BOOL bSucc = FALSE;

	if(!bCanRegi_Tx_Idle(canPeriId))
	{
		return FALSE;
	}
	
	if(CAN_SendMsg(canPeriId, pMsg) == SUCCESS)
	{
		bSucc = TRUE;
		
		
		canRegi_task_ClrTxIdle(canPeriId);
		CallBack_Can_setTxIng(canPeriId);
	}
	
	
	return bSucc;
}


/******************************************************************************
* FUNC: // get ����͵�һ֡��driver�ṹ
*   IN:
*  OUT: 
******************************************************************************/
CAN_MSG_Type *pGetCanRegi_TxBuf(U8 canPeriId)
{
U8 peri_can_buf_id;

	peri_can_buf_id = canRegi_GetBuf_FromPeriId(canPeriId);
	
	return &stRegiCan[peri_can_buf_id].txFrm;
	
}

CAN_MSG_Type *pGetCanRegi_RxBuf(U8 canPeriId)
{
U8 peri_can_buf_id;

	peri_can_buf_id = canRegi_GetBuf_FromPeriId(canPeriId);
	
	return &stRegiCan[peri_can_buf_id].rxFrm;
}

/******************************************************************************
* FUNC: // 
*   IN:
*  OUT: 
******************************************************************************/

void  CAN_IRQHandler(void)
{
   canRegi_Interupt(U_Peri_Can1_Buf);
   canRegi_Interupt(U_Peri_Can2_Buf);
}

/******************************************************************************
* FUNC: // �ж�CAN�Ĵ������Ƿ����ڷ���
*   IN:
*  OUT: 
******************************************************************************/
BOOL bCanRegi_Tx_Idle(U8 canPeriId)
{
U32 GsrStatus; 
// U32 SrStatus;

	// �ο� CAN_SR_RBS ��P508��LPC177x_178x_UM_SimpCHN.pdf�� .
	// SrStatus = CAN_GetCTRLStatus (canPeriId, CANCTRL_STS); // SR 
	// if(SrStatus & CAN_SR_TBS1) // 1=tx ing
	// {
		// return FALSE;
	// }
	// return TRUE;

	
	// �ο� CAN_GSR_RBS ��P500��LPC177x_178x_UM_SimpCHN.pdf�� .
	GsrStatus = CAN_GetCTRLStatus (canPeriId, CANCTRL_GLOBAL_STS);
	if(GsrStatus & CAN_GSR_TS) // 1=tx ing
	{
		return FALSE;
	}
	return TRUE;
}


/******************************************************************************
* FUNC: // 
*   IN:
*  OUT: 
******************************************************************************/

void canRegi_BusError_IntSet(U8 canPeriId)
{
	CAN_IRQCmd(canPeriId, CANINT_BEIE, ENABLE); // bus error 	
}

void canRegi_ErrorWarning_IntSet(U8 canPeriId)
{
	CAN_IRQCmd(canPeriId, CANINT_EIE, ENABLE); // error or bus status changes 
}

void canRegi_ArbitrationLost_IntSet(U8 canPeriId)
{
	CAN_IRQCmd(canPeriId, CANINT_ALIE, ENABLE); // Arbitration Lost int
}

/******************************************************************************
* FUNC: // 
******************************************************************************/
void canRegi_JdgError(U8 canPeriId, U32 IntStatus)
{
U32 errBits;
U32 GsrStatus; 

	if(IntStatus & CAN_ICR_BEI) // ���ߴ����ж� 16~23bits����ҪBEIE=1
	{
		errBits = ((IntStatus >> 22) & 0x03); // CAN_ICR_ERRC
		// errBits = ((IntStatus & CAN_ICR_ERRC(~0)) >> 22);
		switch(errBits)
		{
			case 0: // λ����
				CallBack_Can_BitError(canPeriId);
				break;
				
			case 1: // ��ʽ����
			case 2: // ������
			case 3: // ��������
			default:
				break;
		}
	}
	if(IntStatus & CAN_ICR_EI) // �����жϣ�ES|BS
	{
		// �ο� CAN_GSR_RBS ��P500��LPC177x_178x_UM_SimpCHN.pdf�� .
		GsrStatus = CAN_GetCTRLStatus (canPeriId, CANCTRL_GLOBAL_STS);
		if(GsrStatus & CAN_GSR_ES) // 1=CAN Error Status�� tx��rx����������
		{
			// CallBack_Can_SendFailed(canPeriId);
		}
		if(GsrStatus & CAN_GSR_BS) // 1=CAN Bus Status�����߹رա�
		{
			CallBack_Can_BusOff(canPeriId);
		}
	}
	// if(IntStatus & CAN_ICR_ALI) // �ٲö�ʧ�ж� 24~31bits����ҪALIE=1
	// {
	// }
	
}

/******************************************************************************
* FUNC: // 
*   IN:
*  OUT: 
******************************************************************************/
	#if U_SYS_Test_CanHw == 1
extern U32 GetTickTmrNowMs(void);
		
#define U_RECORD_INT_STATUS_MAX   6
U32 vRcdIntStatus[U_Peri_CanBuf_MAX][U_RECORD_INT_STATUS_MAX][2];
U32 vRcdIntStaNum[U_Peri_CanBuf_MAX];

void recordIntStatuInit(U8 canPeriId)
{
U32 num;
	if(canPeriId >= U_Peri_CanBuf_MAX)
	{
		return;
	}

	for(num=0; num<U_RECORD_INT_STATUS_MAX; num++)
	{
		vRcdIntStatus[canPeriId][num][0] = ~0;
		vRcdIntStatus[canPeriId][num][1] = ~0;
	}
	
	vRcdIntStaNum[canPeriId] = 0;
	
}

void recordInsStatus(U8 canPeriId, U32 IntStatus)
{
U32 *pNum;

	pNum = &vRcdIntStaNum[canPeriId];
	
	if(  (canPeriId >= U_Peri_CanBuf_MAX)
	  || (*pNum >= U_RECORD_INT_STATUS_MAX)
	  )
	{
		return;
	}
	
	vRcdIntStatus[canPeriId][*pNum][0] = IntStatus;
	vRcdIntStatus[canPeriId][*pNum][1] = GetTickTmrNowMs();
	
	vRcdIntStaNum[canPeriId] ++;
	
	
}
	#endif // U_SYS_Test_CanHw 

/******************************************************************************
* FUNC: // 
*   IN:
*  OUT: 
******************************************************************************/
		
		
		
void canRegi_Interupt(U8 canPeriId)
{
	U8 canMaskBuf;
U32 IntStatus; 
CAN_MSG_Type *pCanMsg;
   
	/* get interrupt status
	 * Note that: Interrupt register CANICR will be reset after read.
	 * So function "CAN_IntGetStatus" should be call only one time
	 * 
	 */
	//�ο� CAN_ICR_RI��P503��LPC177x_178x_UM_SimpCHN.pdf�� .
	IntStatus = CAN_IntGetStatus(canPeriId); 
	
	
	if(IntStatus == 0) 
	{
		return;
	}
	
	#if U_SYS_Test_CanHw == 1
	recordInsStatus(canPeriId, IntStatus);
	#endif // U_SYS_Test_CanHw 
	
	if(IntStatus & CAN_ICR_RI)  //�н�����Ϣ
	{
		pCanMsg = pGetCanRegi_RxBuf(canPeriId);
		CAN_ReceiveMsg(canPeriId, pCanMsg);
		
		// chkHd_Can__CanRx(canPeriId);
	
#ifdef U_USE_CAN_MASK  //
#else //
		canMaskBuf = canMaskBuf;
		CallBack_Can_RecNew(canPeriId, U_iCanRxMaskBuf_Broad, pCanMsg);
		// if(!JdgCanFrmMaskBuf(canPeriId,0,pCanMsg, &canMaskBuf))
		// {
			// CallBack_Can_RecNew(canPeriId, canMaskBuf, pCanMsg);
		// }

#endif //

	}
	if(IntStatus & CAN_ICR_TI1)  //���ͳɹ�
	{
		canRegi_task_SetTxIdle(canPeriId);
		CallBack_Can_SendSucc(canPeriId);
	}
	
	canRegi_JdgError(canPeriId, IntStatus);
	
}

/******************************************************************************
* FUNC: // END
*   IN:
*  OUT: 
******************************************************************************/
