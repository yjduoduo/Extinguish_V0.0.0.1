#define __phIoPwrChkSwitch_C__
/******************************************************************************
* @file    phIoPwrChkSwitch.c
* @author  yx
* @version V1.0
* @date    2013-08-22
* @brief   ��Դ���޿���
* 
******************************************************************************/
#include  "phIoPwrChkSwitch.h"

#include  "hwEx10_PinDef.h"
#include  "hwEx10_GpioDef.h"

#include  "hw20_AD.h"

#include  "evt_Buf_incOut.h"
//#include "incFile.h"	


/*================= ���� ============================================*/
#define U_AD_PwrChkSwc_Channel   6 //

#define U_AD_FAULT_VALUE_MAX   50 //

#define U_PwrChkSwc_Fault_NUM_MAX   2
#define U_PwrChkSwc_ReUsual_NUM_MAX   3

/*================= �ṹ���� ========================================*/

typedef struct{
	U8 bFault;
	U8 usualNum;
	U8 ErrNum;
}TPwrChkSwcTask_st;

TPwrChkSwcTask_st  stPwrChkSwc;
/*================= ˽�нṹ�������� ================================*/

/*================= ���к������� ====================================*/

/*================= ˽�к������� ====================================*/
/******************************************************************************
* FUNC: // ���ϼ��(�������) ���̴���
*   IN:
*  OUT:
*       2013.5.26 by yx
******************************************************************************/

void chkPwrChkSwc_Init(void); //��ʼ��
void chkPwrChkSwc_Exec(void); //exec
U8 chkPwrChkSwc_bFault_HdChk(void); //Ӳ�����
void chkPwrChkSwc_Result_Usual(void); //result: �ָ�����
void chkPwrChkSwc_Result_Fault(void);  //result: ����

U32 chkPwrChkSwc_GetAd(void); // AD ����

/*=================  ================================================*/
		
/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
void InitPwrChkSwcTask(void)
{

	CanRegi_AD_Init();
	
		chkPwrChkSwc_Init();
}


/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
*  USE: emGpioPwrState
******************************************************************************/

void ExecPwrChkSwcTask(void)
{
		chkPwrChkSwc_Exec();
}



/******************************************************************************
* FUNC: // 
*   IN:
*  OUT: 

// 24V���� 0x83B = 2107. 
// 12λ������max = 0x1000 = 4096.
24 * (3K1/(47K5+3K1)) = 1.42V  Լ3.3V��һ�롣

******************************************************************************/

U32 chkPwrChkSwc_GetAd(void) // AD ����
{
	return (CanRegi_AD_GetValue(U_AD_PwrChkSwc_Channel));
	
}

/******************************************************************************
******************************************************************************/
void chkPwrChkSwc_Init(void) //��ʼ��
{
    U8 *pFaultNum;
    U8 *pUsualNum;
    U8 *pFaultSign;

    pFaultNum = &stPwrChkSwc.ErrNum;
    pUsualNum = &stPwrChkSwc.usualNum;
    pFaultSign = &stPwrChkSwc.bFault;

    *pFaultNum = 0;
    *pUsualNum = 0;
    *pFaultSign = 0;
}

void chkPwrChkSwc_Exec(void) //exec
{
    U8 *pFaultNum;
    U8 *pUsualNum;
    U8 *pFaultSign;

    pFaultNum = &stPwrChkSwc.ErrNum;
    pUsualNum = &stPwrChkSwc.usualNum;
    pFaultSign = &stPwrChkSwc.bFault;

    if(*pFaultSign == 0) //��־������ 
    {
        if(!chkPwrChkSwc_bFault_HdChk()) //����޹���
        {
            *pUsualNum = 0;
        }
        else
        {
            *pFaultNum += 1;
            if(*pFaultNum >= U_PwrChkSwc_Fault_NUM_MAX)
            {
                *pFaultSign = 1;
                //���ϴ���:
                chkPwrChkSwc_Result_Fault();
            }
        }
    }
    else  //��־������
    {
        if(chkPwrChkSwc_bFault_HdChk()) //����й���
        {
            *pFaultNum = 0;
        }
        else
        {
            *pUsualNum += 1;
            if(*pUsualNum >= U_PwrChkSwc_ReUsual_NUM_MAX)
            {
                *pFaultSign = 0;
                //�ָ���������:
                chkPwrChkSwc_Result_Usual();
            }
        }
    }    
}

U8 chkPwrChkSwc_bFault_HdChk(void) //Ӳ�����
{
U32 mAdVal;

	mAdVal = chkPwrChkSwc_GetAd();
	
	return (mAdVal < U_AD_FAULT_VALUE_MAX);
}



void chkPwrChkSwc_Result_Usual(void) //result: �ָ�����
{
TDev_un unDev;
TEvtTrans_st *pTrans;

	if(BuildToDev_Me_Power(U_Gpio_PwrCheckSwitch_FUNC, &unDev))
	{
		GetEvtTransStrAndClock(&unDev, &pTrans);
		pTrans->thing = U_FaultRstr_EVT;
		Buf_Fault(pTrans);
	}
}

void chkPwrChkSwc_Result_Fault(void)  //result: ����
{
TDev_un unDev;
TEvtTrans_st *pTrans;

	if(BuildToDev_Me_Power(U_Gpio_PwrCheckSwitch_FUNC, &unDev))
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
