#define __canPrtl_iTx_C__
/******************************************************************************
* @file    canPrtl_iTx.c
* @author  yx
* @version V1.0
* @date    2013-07-01
* @brief   
* 
******************************************************************************/
#include  "canPrtl_iTx.h"


//#include "incFile.h"	
#include  "sysPanel.h"
#include  "CanBufLib_incOut.h"

#include  "phClock.h"
#include  "strFlsItmStruct.h"
#include  "Save_Item_incOut.h"

#include  "CCan_11S_Def.h"
#include  "can11sPrtl_iTx.h"

// ���Է����ã�
#include  "can11sPrtl_eTx.h"
/*================= ���� ============================================*/

/*================= �ṹ���� ========================================*/

/*================= ˽�нṹ�������� ================================*/

THdCanFrame_st  vICanTxFrm;
/*================= ���к������� ====================================*/

/*================= ˽�к������� ====================================*/

/*=================  ================================================*/

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
void iCan_txNewFrm_ToTxBuf(void)
{
	if(vICanTxFrm.length > U_CAN_HARDFRAME_U8_MAX)
	{
		vICanTxFrm.length = U_CAN_HARDFRAME_U8_MAX;
	}
	CanBuf_iCanTx_Add(&vICanTxFrm);
}


/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

// ���ͣ�ID, command, loop, addr:
BOOL iCan11s_tx_DetePrtlPink_InByte1(U8 mCommand,
									U8 mLoop, U8 mAddr)
{
U8 mCanDest;
U8 mTxLoop;

	if(!iCan11s_tx_Dete_PrtlTypePink(mLoop, &mCanDest, &mTxLoop))
	{
		return FALSE;
	}
	
	CompICan11s_tx_1byte_PtoP(mCanDest, mCommand, &vICanTxFrm);
	vICanTxFrm.length += 2;
	vICanTxFrm.rtData.rtU8[1] = mTxLoop;
	vICanTxFrm.rtData.rtU8[2] = mAddr;
	
	return TRUE;
}



/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
void ICan_Tx_Alarm(U8 mAddr)
{
	// ICan_Tx_Clock();
	
	// vICanTxFrm.id.dWord = 0x0A800028; // eCan Tx; Failed
	// vICanTxFrm.id.dWord = 0x00800008; // iCan Tx; OK
	// vICanTxFrm.id.dWord = 0x07800028; // eCan Tx; OK
	// vICanTxFrm.id.dWord = 0x07FFFFFF; // eCan Tx; OK
	// vICanTxFrm.id.dWord = 0x08000000; // eCan Tx; OK
	// vICanTxFrm.id.dWord = 0x0A800000; // eCan Tx; OK
	// vICanTxFrm.id.dWord = 0x0A800008; // eCan Tx; OK
	// vICanTxFrm.id.dWord = 0x0A800028; // eCan Tx; Failed
	// vICanTxFrm.id.dWord = 0x0A800020; // eCan Tx; OK
	// vICanTxFrm.id.dWord = 0x0A8FFF2F; // OK
	// vICanTxFrm.id.dWord = 0x0A800028; // ���ֵ�������⣿iCan eCan������Ҫ�����
	// vICanTxFrm.length = 0;
	
	//CompICan11s_tx_1byte_broad(0x80, &vICanTxFrm);
	CompECan11s_tx_1byte_broad(0x80, &vICanTxFrm);	
	vICanTxFrm.length += 3;
	vICanTxFrm.rtData.rtU8[1] = 1;
	vICanTxFrm.rtData.rtU8[2] = mAddr;
	vICanTxFrm.rtData.rtU8[3] = 2;	
	iCan_txNewFrm_ToTxBuf();
}

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/


void ICan_Tx_Reset(void) // ��λ
{
	CompICan11s_tx_1byte_broad(c11s_BC_Reset, &vICanTxFrm);
	iCan_txNewFrm_ToTxBuf();
}

void ICan_Tx_RegistAll(void) // �Զ��Ǽ�
{
	CompICan11s_tx_1byte_broad(c11s_BC_Register, &vICanTxFrm);
	iCan_txNewFrm_ToTxBuf();
}


void ICan_Tx_HornLedCheck(void) // �Ƽ�
{
	CompICan11s_tx_1byte_broad(c11s_BC_CheckSelf, &vICanTxFrm);
	iCan_txNewFrm_ToTxBuf();
}

void ICan_Tx_Clock(void) // ʱ��
{
TEvtClock_st *pClock;

	GetRamTimer(&pClock);
	CompICan11s_tx_1byte_broad(c11s_BC_Time, &vICanTxFrm);
	vICanTxFrm.length += 2;
	vICanTxFrm.rtData.rtU8[1] = pClock->min;
	vICanTxFrm.rtData.rtU8[2] = pClock->sec;
	iCan_txNewFrm_ToTxBuf();
}

void ICan_Tx_ClrRegist(void) // ����Ǽ�
{
	CompICan11s_tx_1byte_broad(c11s_BC_ClrReg, &vICanTxFrm);
	iCan_txNewFrm_ToTxBuf();
}


void ICan_Tx_ClrLinkProg(void) // ������
{
	CompICan11s_tx_1byte_broad(c11s_BC_ClrPrg, &vICanTxFrm);
	iCan_txNewFrm_ToTxBuf();
}


void ICan_Tx_PcLoadIng(void) // ��������
{
	CompICan11s_tx_1byte_broad(c11s_BC_EnPro, &vICanTxFrm);
	iCan_txNewFrm_ToTxBuf();
}


void ICan_Tx_MachMaster_EnAuto(void) // ���������ӻ� �Զ�����
{
	CompICan11s_tx_1byte_broad(c11s_BC_EnAuto, &vICanTxFrm);
	vICanTxFrm.length += 2;
	vICanTxFrm.rtData.rtU8[1] = 0x5A;
	vICanTxFrm.rtData.rtU8[2] = 0xA5;
	iCan_txNewFrm_ToTxBuf();
}

void ICan_Tx_Silence(void) // ����
{
	CompICan11s_tx_1byte_broad(0x0B, &vICanTxFrm);
	iCan_txNewFrm_ToTxBuf();
}

void ICan_Tx_HornStrobe_On(void) // ���� ON
{
	CompICan11s_tx_1byte_broad(c11s_BC_SlAct, &vICanTxFrm);
	vICanTxFrm.length += 1;
	vICanTxFrm.rtData.rtU8[1] = 0x80;
	iCan_txNewFrm_ToTxBuf();
}

void ICan_Tx_HornStrobe_Off(void) // ���� ON
{
	CompICan11s_tx_1byte_broad(c11s_BC_SlAct, &vICanTxFrm);
	vICanTxFrm.length += 1;
	vICanTxFrm.rtData.rtU8[1] = 0;
	iCan_txNewFrm_ToTxBuf();
}



void ICan_Tx_WorkMode_Debug_On(void) // ����ģʽ
{
	CompICan11s_tx_1byte_broad(0x78, &vICanTxFrm);
	vICanTxFrm.length += 1;
	vICanTxFrm.rtData.rtU8[1] = 0x80;
	iCan_txNewFrm_ToTxBuf();
}

void ICan_Tx_WorkMode_Debug_Off(void)
{
	CompICan11s_tx_1byte_broad(0x78, &vICanTxFrm);
	vICanTxFrm.length += 1;
	vICanTxFrm.rtData.rtU8[1] = 0;
	iCan_txNewFrm_ToTxBuf();
}


void ICan_Tx_AutoManu(void) // �ֶ��Զ�
{
TFlsSysSet_un *pSysSet;
U8 mByte = 0;

	pSysSet = pGetFlsSysSet();
	CompICan11s_tx_1byte_broad(c11s_BC_AuMa, &vICanTxFrm);
	
// ACC.3=1  �ֶ�����
// ACC.3=0  �ֶ���ֹ

// ACC.2=1  �Զ�����
// ACC.2=0  �Զ���ֹ
	if(pSysSet->stSet.runManu)
	{
		mByte |= (1<<3);
	}
	if(pSysSet->stSet.runAuto)
	{
		mByte |= (1<<2);
	}
		
	vICanTxFrm.length += 1;
	vICanTxFrm.rtData.rtU8[1] = mByte;
	iCan_txNewFrm_ToTxBuf();
}



/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

// IN: pnType: emPanelType ;
// IN: pnSequ: ��ţ�1~ ;

void ICan_Tx_InqireCommand_Stop(U8 mLoop, U8 mAddr) // ��������
{
	// ���ͣ�ID, command, loop, addr:
	if(!iCan11s_tx_DetePrtlPink_InByte1(0x3B, mLoop, mAddr))
	{
		return;
	}
	iCan_txNewFrm_ToTxBuf();
}


/******************************************************************************
* FUNC: //
******************************************************************************/
void ICan_Tx_InqireCommand_Analog_Start(U8 mLoop, U8 mAddr) // ��������-ģ������
{
	// ���ͣ�ID, command, loop, addr:
	if(!iCan11s_tx_DetePrtlPink_InByte1(0x3A, mLoop, mAddr))
	{
		return;
	}
	vICanTxFrm.rtData.rtU8[vICanTxFrm.length] = 1;
	vICanTxFrm.length ++;
	iCan_txNewFrm_ToTxBuf();
}

void ICan_Tx_InqireCommand_Analog_Stop(U8 mLoop, U8 mAddr) // ��������-ģ������
{
	ICan_Tx_InqireCommand_Stop(mLoop, mAddr);
}

/******************************************************************************
* FUNC: //
******************************************************************************/
void ICan_Tx_InqireCommand_DeteData_Start(U8 mLoop, U8 mAddr) // ��������-̽�����ڲ�����
{
	// ���ͣ�ID, command, loop, addr:
	if(!iCan11s_tx_DetePrtlPink_InByte1(0x3A, mLoop, mAddr))
	{
		return;
	}
	vICanTxFrm.rtData.rtU8[vICanTxFrm.length] = 2;
	vICanTxFrm.length++;
	iCan_txNewFrm_ToTxBuf();
	
}

void ICan_Tx_InqireCommand_DeteData_Stop(U8 mLoop, U8 mAddr) // ��������-̽�����ڲ�����
{
	ICan_Tx_InqireCommand_Stop(mLoop, mAddr);
}


/******************************************************************************
* FUNC: // 
*   IN:
*  OUT: 
******************************************************************************/

// IN: mModuType:  emModuRunAuMaRemote
// mModuRunState
void ICan_Tx_DevRunMess_Run(U8 mLoop, U8 mAddr, 
								U8 mModuType) // ģ������
{
	// ���ͣ�ID, command, loop, addr:
	if(!iCan11s_tx_DetePrtlPink_InByte1(0x3C, mLoop, mAddr))
	{
		return;
	}
	vICanTxFrm.rtData.rtU8[vICanTxFrm.length] = U_ModuRunSta_Start;
	vICanTxFrm.length ++;
	vICanTxFrm.rtData.rtU8[vICanTxFrm.length] = mModuType;
	vICanTxFrm.length ++;
	iCan_txNewFrm_ToTxBuf();
}



void ICan_Tx_DevRunMess_Stop(U8 mLoop, U8 mAddr,
								U8 mModuType) // ģ��ֹͣ
{
	// ���ͣ�ID, command, loop, addr:
	if(!iCan11s_tx_DetePrtlPink_InByte1(0x3C, mLoop, mAddr))
	{
		return;
	}
	vICanTxFrm.rtData.rtU8[vICanTxFrm.length] = U_ModuRunSta_Stop;
	vICanTxFrm.length ++;
	vICanTxFrm.rtData.rtU8[vICanTxFrm.length] = mModuType;
	vICanTxFrm.length ++;
	iCan_txNewFrm_ToTxBuf();
}

/******************************************************************************
* FUNC: // 
*   IN:
*  OUT: 
******************************************************************************/

/******************************************************************************
* FUNC: // 
*   IN:
*  OUT: 
******************************************************************************/

// IN:   mDeteClass: emDeteCanClass ;
void ICan_Tx_OpeaDete_Disable(BOOL bDisable, 
				U8 mLoop, U8 mAddr, U8 mDeteClass) // ����������
{
U8 mCommand = 0x04;

	if(bDisable)
	{
		mCommand = 0x01;
	}
	// ���ͣ�ID, command, loop, addr:
	// ������ȷ�� dest:
	if(!iCan11s_tx_DetePrtlPink_InByte1(mCommand, mLoop, mAddr))
	{
		return;
	}
	if(bDisable)
	{
		vICanTxFrm.rtData.rtU8[vICanTxFrm.length] = mDeteClass;
	}
	else
	{
		vICanTxFrm.rtData.rtU8[vICanTxFrm.length] = 0;
	}
	vICanTxFrm.length++;
	iCan_txNewFrm_ToTxBuf();
}


void ICan_Tx_OpeaDete_ManuRunOrStop(
					BOOL bRun, U8 mLoop, U8 mAddr, U8 mChannel) // ������ģ������/ֹͣ
{
U8 mCommand = 0x03;

	if(bRun)
	{
		mCommand = 0x02;
	}
	// ���ͣ�ID, command, loop, addr:
	// ������ȷ�� dest:
	if(!iCan11s_tx_DetePrtlPink_InByte1(mCommand, mLoop, mAddr))
	{
		return;
	}
	vICanTxFrm.rtData.rtU8[vICanTxFrm.length] = mChannel;
	vICanTxFrm.length ++;
	iCan_txNewFrm_ToTxBuf();
}



// IN:   mDeteClass: emDeteCanClass ;
void ICan_Tx_OpeaDete_SignalRegist(BOOL bRegist, 
				U8 mLoop, U8 mAddr, U8 mDeteClass) // �����������Ǽ�
{
U8 mCommand = 0x06;

	if(bRegist)
	{
		mCommand = 0x05;
	}
	// ���ͣ�ID, command, loop, addr:
	// ������ȷ�� dest:
	if(!iCan11s_tx_DetePrtlPink_InByte1(mCommand,
									mLoop, mAddr))
	{
		return;
	}
	if(bRegist)
	{
		vICanTxFrm.rtData.rtU8[vICanTxFrm.length] = mDeteClass;
	}
	else
	{
		vICanTxFrm.rtData.rtU8[vICanTxFrm.length] = 0;
	}
	vICanTxFrm.length++;
	iCan_txNewFrm_ToTxBuf();
}



void ICan_Tx_OpeaDete_InquireStateAndType(
						U8 mLoop, U8 mAddr) // ��������ѯ״̬������
{
	// ���ͣ�ID, command, loop, addr:
	// ������ȷ�� dest:
	if(!iCan11s_tx_DetePrtlPink_InByte1(0x09, mLoop, mAddr))
	{
		return;
	}
	vICanTxFrm.rtData.rtU8[vICanTxFrm.length] = 0;
	vICanTxFrm.length++;
	iCan_txNewFrm_ToTxBuf();
}


/******************************************************************************
* FUNC: // 
*   IN:
*  OUT: 
******************************************************************************/

void ICan_Tx_Inquire_DeteInline(U8 mLoop) // ��ѯ����
{
U8 mCanDest;
U8 mTxLoop;

	if(!iCan11s_tx_Dete_PrtlTypeBrown(mLoop, &mCanDest, &mTxLoop))
	{
		return;
	}
	
	CompICan11s_tx_1byte_PtoP(mCanDest, 0x10, &vICanTxFrm);
	vICanTxFrm.length += 3;
	vICanTxFrm.rtData.rtU8[1] = mTxLoop;
	vICanTxFrm.rtData.rtU8[2] = 1;
	vICanTxFrm.rtData.rtU8[3] = 1;
	
	iCan_txNewFrm_ToTxBuf();
	
}


void ICan_Tx_Inquire_Regist(U8 mLoop) // ��ѯ�Ǽ� ?
{
U8 mCanDest;
U8 mTxLoop;

	if(!iCan11s_tx_Dete_PrtlTypeBrown(mLoop, &mCanDest, &mTxLoop))
	{
		return;
	}
	
	CompICan11s_tx_1byte_PtoP(mCanDest, 0x11, &vICanTxFrm);
	vICanTxFrm.length += 3;
	vICanTxFrm.rtData.rtU8[1] = mTxLoop;
	vICanTxFrm.rtData.rtU8[2] = 1;
	vICanTxFrm.rtData.rtU8[3] = 1;
	
	iCan_txNewFrm_ToTxBuf();
	
}


void ICan_Tx_Set_LoopDisable(U8 mLoop) // ���� ��·����
{
U8 mCanDest;
U8 mTxLoop;

	if(!iCan11s_tx_Dete_PrtlTypeBrown(mLoop, &mCanDest, &mTxLoop))
	{
		return;
	}
	
	CompICan11s_tx_1byte_PtoP(mCanDest, 0x12, &vICanTxFrm);
	vICanTxFrm.length += 3;
	vICanTxFrm.rtData.rtU8[1] = mTxLoop;
	vICanTxFrm.rtData.rtU8[2] = 0;
	vICanTxFrm.rtData.rtU8[3] = 0;
	
	iCan_txNewFrm_ToTxBuf();
	
}

/******************************************************************************
* FUNC: // 
*   IN:
*  OUT: 
******************************************************************************/


// ȡ�� ��ѯ�ֳ����� ���ԣ�״̬�����ߣ��ڲ����ݣ�
static void ICan_Tx_InquireCheck_Dete_Stop(U8 mCommand, U8 mLoop, U8 mAddr) 
{
	// ���ͣ�ID, command, loop, addr:
	if(!iCan11s_tx_DetePrtlPink_InByte1(mCommand, mLoop, mAddr))
	{
		return;
	}
	vICanTxFrm.rtData.rtU8[vICanTxFrm.length] = 0;
	vICanTxFrm.length ++;
	iCan_txNewFrm_ToTxBuf();
}

/******************************************************************************
* FUNC: // 
******************************************************************************/

// ��ѯ�ֳ����� ״̬��
void ICan_Tx_Inquire_DeteState(U8 mLoop, U8 mAddr)
{
	// ���ͣ�ID, command, loop, addr:
	if(!iCan11s_tx_DetePrtlPink_InByte1(0x14, mLoop, mAddr))
	{
		return;
	}
	vICanTxFrm.rtData.rtU8[vICanTxFrm.length] = 0;
	vICanTxFrm.length ++;
	iCan_txNewFrm_ToTxBuf();	
}

// ȡ�� ��ѯ�ֳ����� ״̬��
void ICan_Tx_Inquire_DeteStaStop(U8 mLoop, U8 mAddr)
{
	ICan_Tx_InquireCheck_Dete_Stop(0x24, mLoop, mAddr);
}


// ��ѯ�ֳ����� ģ�����ߣ�
void ICan_Tx_Inquire_DeteCurv(U8 mLoop, U8 mAddr) 
{
	// ���ͣ�ID, command, loop, addr:
	if(!iCan11s_tx_DetePrtlPink_InByte1(0x15, mLoop, mAddr))
	{
		return;
	}
	vICanTxFrm.rtData.rtU8[vICanTxFrm.length] = 0;
	vICanTxFrm.length ++;
	iCan_txNewFrm_ToTxBuf();
}


// ȡ�� ��ѯ�ֳ����� ģ�����ߣ�
void ICan_Tx_Inquire_DeteCuvStop(U8 mLoop, U8 mAddr) 
{
	ICan_Tx_InquireCheck_Dete_Stop(0x25, mLoop, mAddr);
}


// ��ѯ�ֳ����� �ڲ����ݣ�
void ICan_Tx_Inquire_DeteInterData(U8 mLoop, U8 mAddr) 
{
	// ���ͣ�ID, command, loop, addr:
	if(!iCan11s_tx_DetePrtlPink_InByte1(0x16, mLoop, mAddr))
	{
		return;
	}
	vICanTxFrm.rtData.rtU8[vICanTxFrm.length] = 0;
	vICanTxFrm.length ++;
	iCan_txNewFrm_ToTxBuf();
	
}
// ȡ�� ��ѯ�ֳ����� �ڲ����ݣ�
void ICan_Tx_Inquire_DeteInterDatStop(U8 mLoop, U8 mAddr) 
{
	ICan_Tx_InquireCheck_Dete_Stop(0x25, mLoop, mAddr);
}


// ��ѯ�ֳ����� ��·��� ��·������
void ICan_Tx_Inquire_LoopBrowse(U8 mLoop)
{
	// ���ͣ�ID, command, loop, addr:
	// ������ȷ�� dest:
	if(!iCan11s_tx_DetePrtlPink_InByte1(0x17, mLoop, 1))
	{
		return;
	}
	vICanTxFrm.rtData.rtU8[vICanTxFrm.length-1] = 0;
	vICanTxFrm.rtData.rtU8[vICanTxFrm.length] = 0;
	vICanTxFrm.length ++;
	iCan_txNewFrm_ToTxBuf();
	
}

// ȡ�� ��ѯ�ֳ����� ��·��� ��·������
void ICan_Tx_Inquire_LoopBrowsStop(U8 mLoop)
{
	// ���ͣ�ID, command, loop, addr:
	// ������ȷ�� dest:
	if(!iCan11s_tx_DetePrtlPink_InByte1(0x27, mLoop, 1))
	{
		return;
	}
	vICanTxFrm.rtData.rtU8[vICanTxFrm.length-1] = 0;
	vICanTxFrm.rtData.rtU8[vICanTxFrm.length] = 0;
	vICanTxFrm.length ++;
	iCan_txNewFrm_ToTxBuf();
}



/******************************************************************************
* FUNC: // 
*   IN:
*  OUT: 
******************************************************************************/
void ICan_Tx_Inquire_DeteRegist(U8 mLoop) // ��ѯ��·�ֳ������Ǽ�
{
U8 mCanDest;
U8 mTxLoop;

	if(!iCan11s_tx_Dete_PrtlTypePink(mLoop, &mCanDest, &mTxLoop))
	{
		return;
	}
	
	CompICan11s_tx_1byte_PtoP(mCanDest, 0x23, &vICanTxFrm);
	vICanTxFrm.length += 3;
	vICanTxFrm.rtData.rtU8[1] = mTxLoop;
	vICanTxFrm.rtData.rtU8[2] = 0;
	vICanTxFrm.rtData.rtU8[3] = 0;
	
	iCan_txNewFrm_ToTxBuf();
	
}


/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
void ICan_Tx_Inquire_SoftVersion(U8 mLoop)
{
U8 mCanDest;
U8 mTxLoop;

	if(!iCan11s_tx_Dete_PrtlTypePink(mLoop, &mCanDest, &mTxLoop))
	{
		return;
	}
	
	CompICan11s_tx_1byte_PtoP(mCanDest, 0x2A, &vICanTxFrm);
	vICanTxFrm.length += 3;
	vICanTxFrm.rtData.rtU8[1] = mTxLoop;
	vICanTxFrm.rtData.rtU8[2] = 0;
	vICanTxFrm.rtData.rtU8[3] = 0;
	
	iCan_txNewFrm_ToTxBuf();
}

/*

*/

/******************************************************************************
* FUNC: // END
*   IN:
*  OUT: 
******************************************************************************/
