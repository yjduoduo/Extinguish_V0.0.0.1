#define __phIoPwrChkSwitch_C__
/******************************************************************************
* @file    phIoPwrChkSwitch.c
* @author  yx
* @version V1.0
* @date    2013-08-22
* @brief   电源检修开关
* 
******************************************************************************/
#include  "phIoPwrChkSwitch.h"

#include  "hwEx10_PinDef.h"
#include  "hwEx10_GpioDef.h"

#include  "hw20_AD.h"

#include  "evt_Buf_incOut.h"
//#include "incFile.h"	


/*================= 常数 ============================================*/
#define U_AD_PwrChkSwc_Channel   6 //

#define U_AD_FAULT_VALUE_MAX   50 //

#define U_PwrChkSwc_Fault_NUM_MAX   2
#define U_PwrChkSwc_ReUsual_NUM_MAX   3

/*================= 结构定义 ========================================*/

typedef struct{
	U8 bFault;
	U8 usualNum;
	U8 ErrNum;
}TPwrChkSwcTask_st;

TPwrChkSwcTask_st  stPwrChkSwc;
/*================= 私有结构变量声明 ================================*/

/*================= 公有函数声明 ====================================*/

/*================= 私有函数声明 ====================================*/
/******************************************************************************
* FUNC: // 故障检测(单个检测) 流程代码
*   IN:
*  OUT:
*       2013.5.26 by yx
******************************************************************************/

void chkPwrChkSwc_Init(void); //初始化
void chkPwrChkSwc_Exec(void); //exec
U8 chkPwrChkSwc_bFault_HdChk(void); //硬件检测
void chkPwrChkSwc_Result_Usual(void); //result: 恢复正常
void chkPwrChkSwc_Result_Fault(void);  //result: 故障

U32 chkPwrChkSwc_GetAd(void); // AD 采样

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

// 24V接入 0x83B = 2107. 
// 12位采样，max = 0x1000 = 4096.
24 * (3K1/(47K5+3K1)) = 1.42V  约3.3V的一半。

******************************************************************************/

U32 chkPwrChkSwc_GetAd(void) // AD 采样
{
	return (CanRegi_AD_GetValue(U_AD_PwrChkSwc_Channel));
	
}

/******************************************************************************
******************************************************************************/
void chkPwrChkSwc_Init(void) //初始化
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

    if(*pFaultSign == 0) //标志：正常 
    {
        if(!chkPwrChkSwc_bFault_HdChk()) //检测无故障
        {
            *pUsualNum = 0;
        }
        else
        {
            *pFaultNum += 1;
            if(*pFaultNum >= U_PwrChkSwc_Fault_NUM_MAX)
            {
                *pFaultSign = 1;
                //故障处理:
                chkPwrChkSwc_Result_Fault();
            }
        }
    }
    else  //标志：故障
    {
        if(chkPwrChkSwc_bFault_HdChk()) //检测有故障
        {
            *pFaultNum = 0;
        }
        else
        {
            *pUsualNum += 1;
            if(*pUsualNum >= U_PwrChkSwc_ReUsual_NUM_MAX)
            {
                *pFaultSign = 0;
                //恢复正常处理:
                chkPwrChkSwc_Result_Usual();
            }
        }
    }    
}

U8 chkPwrChkSwc_bFault_HdChk(void) //硬件检测
{
U32 mAdVal;

	mAdVal = chkPwrChkSwc_GetAd();
	
	return (mAdVal < U_AD_FAULT_VALUE_MAX);
}



void chkPwrChkSwc_Result_Usual(void) //result: 恢复正常
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

void chkPwrChkSwc_Result_Fault(void)  //result: 故障
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
