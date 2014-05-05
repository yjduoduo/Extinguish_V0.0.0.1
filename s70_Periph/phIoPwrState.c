#define __phIoPwrState_C__
/******************************************************************************
* @file    phIoPwrState.c
* @author  yx
* @version V1.0
* @date    2013-08-22
* @brief   �����繤��״̬
* 
******************************************************************************/
#include  "phIoPwrState.h"

#include  "hwEx10_GpioDef.h"

#include  "evt_Buf_incOut.h"
//#include "incFile.h"	


/*================= ���� ============================================*/

#define U_PwrState_Fault_NUM_MAX   2
#define U_PwrState_ReUsual_NUM_MAX   3
/*================= �ṹ���� ========================================*/
typedef struct{
	U8 bFault;
	U8 usualNum;
	U8 ErrNum;
}TPwrStateTask_st;

TPwrStateTask_st  stPwrState[U_Gpio_PwrState_FUNC_MAX];
/*================= ˽�нṹ�������� ================================*/

/*================= ���к������� ====================================*/

/*================= ˽�к������� ====================================*/

/******************************************************************************
* FUNC: // ���ϼ��(�������) ���̴���
*   IN:
*  OUT:
*       2013.5.26 by yx
******************************************************************************/

void chkPwrState_Init(U8 mChnl); //��ʼ��
void chkPwrState_Exec(U8 mChnl); //exec
U8 chkPwrState_bFault_HdChk(U8 mChnl); //Ӳ�����
void chkPwrState_Result_Usual(U8 mChnl); //result: �ָ�����
void chkPwrState_Result_Fault(U8 mChnl);  //result: ����
/*=================  ================================================*/
		
/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
void InitPwrStateTask(void)
{
U8 pwrState;

	IniGpioPwrState();
	
	for(pwrState=0; pwrState<U_Gpio_PwrState_FUNC_MAX;pwrState++)
	{
		chkPwrState_Init(pwrState);
	}
}


/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
*  USE: emGpioPwrState
******************************************************************************/

void ExecPwrStateTask(void)
{
U8 pwrState;

	for(pwrState=0; pwrState<U_Gpio_PwrState_FUNC_MAX;pwrState++)
	{
		chkPwrState_Exec(pwrState);
	}
}




/******************************************************************************
******************************************************************************/
void chkPwrState_Init(U8 mChnl) //��ʼ��
{
    U8 *pFaultNum;
    U8 *pUsualNum;
    U8 *pFaultSign;

    pFaultNum = &stPwrState[mChnl].ErrNum;
    pUsualNum = &stPwrState[mChnl].usualNum;
    pFaultSign = &stPwrState[mChnl].bFault;

    *pFaultNum = 0;
    *pUsualNum = 0;
    *pFaultSign = 0;
}

void chkPwrState_Exec(U8 mChnl) //exec
{
    U8 *pFaultNum;
    U8 *pUsualNum;
    U8 *pFaultSign;

    pFaultNum = &stPwrState[mChnl].ErrNum;
    pUsualNum = &stPwrState[mChnl].usualNum;
    pFaultSign = &stPwrState[mChnl].bFault;

    if(*pFaultSign == 0) //��־������ 
    {
        if(!chkPwrState_bFault_HdChk(mChnl)) //����޹���
        {
            *pUsualNum = 0;
        }
        else
        {
            *pFaultNum += 1;
            if(*pFaultNum >= U_PwrState_Fault_NUM_MAX)
            {
                *pFaultSign = 1;
                //���ϴ���:
                chkPwrState_Result_Fault(mChnl);
            }
        }
    }
    else  //��־������
    {
        if(chkPwrState_bFault_HdChk(mChnl)) //����й���
        {
            *pFaultNum = 0;
        }
        else
        {
            *pUsualNum += 1;
            if(*pUsualNum >= U_PwrState_ReUsual_NUM_MAX)
            {
                *pFaultSign = 0;
                //�ָ���������:
                chkPwrState_Result_Usual(mChnl);
            }
        }
    }    
}

U8 chkPwrState_bFault_HdChk(U8 mChnl) //Ӳ�����
{
	return (GetGpioPwrState(mChnl) == U_ERR); // OUT: U_ERR, U_USUAL :
}



void chkPwrState_Result_Usual(U8 pwrState) //result: �ָ�����
{
TDev_un unDev;
TEvtTrans_st *pTrans;

	if(BuildToDev_Me_Power(pwrState, &unDev))
	{
		GetEvtTransStrAndClock(&unDev, &pTrans);
		pTrans->thing = U_FaultRstr_EVT;
		Buf_Fault(pTrans);
	}
}

void chkPwrState_Result_Fault(U8 pwrState)  //result: ����
{
TDev_un unDev;
TEvtTrans_st *pTrans;

	if(BuildToDev_Me_Power(pwrState, &unDev))
	{
		GetEvtTransStrAndClock(&unDev, &pTrans);
		pTrans->thing = U_Fault_EVT;
		Buf_Fault(pTrans);
	}

}


/******************************************************************************
* FUNC: // END
*   IN:
*  OUT:
******************************************************************************/

