#define __phIoPwrState_C__
/******************************************************************************
* @file    phIoPwrState.c
* @author  yx
* @version V1.0
* @date    2013-08-22
* @brief   主备电工作状态
* 
******************************************************************************/
#include  "phIoPwrState.h"

#include  "hwEx10_GpioDef.h"

#include  "evt_Buf_incOut.h"
//#include "incFile.h"	


/*================= 常数 ============================================*/

#define U_PwrState_Fault_NUM_MAX   2
#define U_PwrState_ReUsual_NUM_MAX   3
/*================= 结构定义 ========================================*/
typedef struct{
	U8 bFault;
	U8 usualNum;
	U8 ErrNum;
}TPwrStateTask_st;

TPwrStateTask_st  stPwrState[U_Gpio_PwrState_FUNC_MAX];
/*================= 私有结构变量声明 ================================*/

/*================= 公有函数声明 ====================================*/

/*================= 私有函数声明 ====================================*/

/******************************************************************************
* FUNC: // 故障检测(单个检测) 流程代码
*   IN:
*  OUT:
*       2013.5.26 by yx
******************************************************************************/

void chkPwrState_Init(U8 mChnl); //初始化
void chkPwrState_Exec(U8 mChnl); //exec
U8 chkPwrState_bFault_HdChk(U8 mChnl); //硬件检测
void chkPwrState_Result_Usual(U8 mChnl); //result: 恢复正常
void chkPwrState_Result_Fault(U8 mChnl);  //result: 故障
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
void chkPwrState_Init(U8 mChnl) //初始化
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

    if(*pFaultSign == 0) //标志：正常 
    {
        if(!chkPwrState_bFault_HdChk(mChnl)) //检测无故障
        {
            *pUsualNum = 0;
        }
        else
        {
            *pFaultNum += 1;
            if(*pFaultNum >= U_PwrState_Fault_NUM_MAX)
            {
                *pFaultSign = 1;
                //故障处理:
                chkPwrState_Result_Fault(mChnl);
            }
        }
    }
    else  //标志：故障
    {
        if(chkPwrState_bFault_HdChk(mChnl)) //检测有故障
        {
            *pFaultNum = 0;
        }
        else
        {
            *pUsualNum += 1;
            if(*pUsualNum >= U_PwrState_ReUsual_NUM_MAX)
            {
                *pFaultSign = 0;
                //恢复正常处理:
                chkPwrState_Result_Usual(mChnl);
            }
        }
    }    
}

U8 chkPwrState_bFault_HdChk(U8 mChnl) //硬件检测
{
	return (GetGpioPwrState(mChnl) == U_ERR); // OUT: U_ERR, U_USUAL :
}



void chkPwrState_Result_Usual(U8 pwrState) //result: 恢复正常
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

void chkPwrState_Result_Fault(U8 pwrState)  //result: 故障
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

