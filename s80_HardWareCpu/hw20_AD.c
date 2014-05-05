#define __hw20_AD_C__
/******************************************************************************
* @file    hw20_AD.c
* @author  yx
* @version V1.0
* @date    2013-07-01
* @Cpu     LPC177x_8x   
* @brief   
* 
******************************************************************************/
#include  "hw20_AD.h"


#include  "hwEx10_PinDef.h"
#include  "lpc177x_8x_adc.h"
//#include "incFile.h"	


/*================= 常数 ============================================*/

/*================= 结构定义 ========================================*/

/*================= 私有结构变量声明 ================================*/

/*================= 公有函数声明 ====================================*/

/*================= 私有函数声明 ====================================*/

/*=================  ================================================*/
		
/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

void CanRegi_AD_Init(void)
{
	IniPinFunc_AD_PwrCheckSwitch();
	
	ADC_Init(LPC_ADC, 50);
	
	ADC_BurstCmd(LPC_ADC, DISABLE);
	
	ADC_PowerdownCmd(LPC_ADC, ENABLE); // 1=正常工作
	
}


/******************************************************************************
* FUNC: //
*   IN:  mChnl = 0~7
******************************************************************************/

U32 CanRegi_AD_GetValue(U8 mChnl)
{
U16 adResult;
U32 wait;

	ADC_ChannelCmd(LPC_ADC, mChnl, ENABLE);
	
	ADC_StartCmd(LPC_ADC, ADC_START_NOW);
	
	for(wait=0; wait<10000; wait++)
	{
		if(ADC_ChannelGetStatus(LPC_ADC, mChnl, ADC_DATA_DONE))
		{
			adResult = ADC_ChannelGetData(LPC_ADC, mChnl);
			return (U32)(adResult);
		}
	}
	return ~0;
}


/******************************************************************************
* FUNC: // END
*   IN:
*  OUT: 
******************************************************************************/
