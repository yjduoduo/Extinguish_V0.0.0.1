
#define __lcdSub_SwDev_C__
/******************************************************************************
* @file    lcdSub_SwDev.c
* @author  yx
* @version V1.1
* @date    2013-09-06
* @brief   ��ʾstDev.
*
* V1.1��2013-09-06
		�ַ���in textBufһ����ʾ��
* V1.0��2012-01-05
* 

LcdSw_Fig
******************************************************************************/
#include  "lcdSub_SwDev.h"

//#include "..\\s00Prj\\incFile.h"	

#include  "lcdCst_PgStrDeteType.h"

//-----------------   --------------------------------// 
#include  "tsk_lcd_incIn.h"
#include  "codeFig.h"


//----- Me:

/*================= ���� ============================================*/

/*================= �ṹ���� ========================================*/

/*================= ˽�нṹ�������� ================================*/

/*================= ���к������� ====================================*/

/*================= ˽�к������� ====================================*/

/*=================  ================================================*/
		
/******************************************************************************
* FUNC: //
*   IN:
*  OUT: �ַ�����
******************************************************************************/
TYPE_LCD_XY Show_Dev_String(TYPE_LCD_RL mRow, TYPE_LCD_RL mLine, 
										TDev_un *pDev)
{
U8 devType;
TYPE_LCD_XY nowPixLine = 0;

	IniTextBuf(U_ShowUseLib_88orCn_CN);
	devType = JdgDevClass(pDev);
	
	switch(devType)
	{
		
		case U_DEV_IS_Machine_TYPE:	//������
			if(bMachineIdIsMe(pDev->stDete.machine))
			{
				sw_DevMachinMe_String();
			}
			else
			{
				sw_DevMachine_String(pDev);
			}
			break;
			
		case U_DEV_IS_Panel_TYPE:	//����Ԫ��
			sw_DevMachine_String(pDev);
			sw_DevPanel_String(pDev);
			break;
			
		case U_DEV_IS_Dete_TYPE:	//��·�ֳ�����
			sw_Dete_String(pDev);
			// sw_Dete_Char(pDev);
			break;
			
		case U_DEV_IS_PnModu_TYPE:	//�����ֳ�����
		case U_DEV_IS_ModuLine_TYPE:
			sw_DevMachine_String(pDev);			
			sw_DevPanel_String(pDev);
			sw_DevPnModu_String(pDev);
			break;
			
		default:
			break;
	}
	if(!bTextBufEmpty())
	{
		nowPixLine = ShowTextBuf(mRow, mLine);
	}
	return nowPixLine;
}


/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
// OUT: pRtnFigStr-> ����תbcd string.
void sw_dev_Fig(U32 fig, U8 bitTotal, U8 **pRtnFigStr)
{
// charNum  = FigToString(fig, bitTotal,  b�Ҷ���, b��ʾ0, **pRtnStr);
	FigToString(fig, bitTotal, FALSE,FALSE, pRtnFigStr);
}

/******************************************************************************
* FUNC: //
******************************************************************************/
// �ַ���ʽ ��ʾ ��·�ֳ�����:
// OUT: TextBuf[], �ַ���
//�ַ���= 2+4 +2+6 +3+4 +1+4 = 26.
U8 sw_Dete_String(TDev_un *pDev)
{
U8 swTotal = 0;
//U32 mLoop;
U8 *pStr;
	
	//machine:
	if(!bMachineIdIsMe(pDev->stDete.machine))
	{
		sw_dev_Fig(pDev->stDete.machine, 2, &pStr);
		swTotal += AddToTextBuf(pStr);
		swTotal += AddCstStrToTextBuf(&cstChar_Machine);
	}
	else
	{
		swTotal += AddCodeStrToTextBuf(" ");
	}
	
	swTotal += sw_Dete_noMachine(pDev, 0);
	
	return swTotal;
}


/******************************************************************************
* FUNC: //
******************************************************************************/
// ������ʽ ��ʾ ��·�ֳ�����:
// OUT: TextBuf[], �ַ���
//�ַ���= 2+1 +2+1 +3 +1+1 = 11;
U8 sw_Dete_Char(TDev_un *pDev)
{
U8 swTotal = 0;
//U32 mLoop;
U8 *pStr;
	
	//machine:
	if(!bMachineIdIsMe(pDev->stDete.machine))
	{
		sw_dev_Fig(pDev->stDete.machine, 2, &pStr);
		swTotal += AddToTextBuf(pStr);
		swTotal += AddCodeStrToTextBuf("--");
	}
	else
	{
		swTotal += AddCodeStrToTextBuf("   ");
	}

	swTotal += sw_Dete_noMachine(pDev, 0);
	
	return swTotal;
}


/******************************************************************************
* FUNC: //
******************************************************************************/
// ��ʾ ��·�ֳ�����, �޻����ţ�����" ":
// OUT: TextBuf[], �ַ���
//�ַ���= bChar0Cn1=0: 2+1 + 3+1 +1   + 1 = 9;
//�ַ���= bChar0Cn1=1: 2+4 + 3+4 +1+4 + 1 = 19;
U8 sw_Dete_noMachine(TDev_un *pDev, BOOL bChar0Cn1)
{
U8 swTotal = 0;
U32 mLoop;
U8 *pStr;
	
	//�ַ���= 0
	//loop:
	CacuDeteLoop_1toMax(pDev, &mLoop);
	sw_dev_Fig(mLoop, 2, &pStr);
	swTotal += AddToTextBuf(pStr);
	if(bChar0Cn1 == 0)
	{
		swTotal += AddCodeStrToTextBuf("-");
	}
	else
	{
		swTotal += AddCstStrToTextBuf(&cstChar_Loop);
	}
	
	//�ַ���= 2+1 
	//addr:
	sw_dev_Fig(pDev->stDete.field, 3, &pStr);
	swTotal += AddToTextBuf(pStr);
	if(bChar0Cn1 == 0)
	{
	}
	else
	{
		 swTotal += AddCstStrToTextBuf(&cstChar_Addr);
	}
	
	
	//�ַ���= 2+1 +3
	//channel:
	if(!bDeteHaveChannel(pDev))
	{
		swTotal += AddCodeStrToTextBuf(" ");
		return swTotal;
		//�ַ���= 2+1 +3  = 9;
	}	
	if(bChar0Cn1 == 0)
	{
		swTotal += AddCodeStrToTextBuf("-");
	}
	else
	{
	}
	
	sw_dev_Fig(pDev->stDete.channel, 1, &pStr);
	swTotal += AddToTextBuf(pStr);
	if(bChar0Cn1 == 0)
	{
	}
	else
	{
		swTotal += AddCstStrToTextBuf(&cstChar_Channel);
	}
	swTotal += AddCodeStrToTextBuf(" ");
	
	
	return swTotal;
}


/******************************************************************************
* FUNC: //
******************************************************************************/
// OUT: TextBuf[], �ַ���
U8 sw_DevPnModu_String(TDev_un *pDev)
{
U8 pnType;
U8 swTotal;
U8 mduLine;
U8 *pStr;
	
	swTotal = 0;
	
	pnType = pDev->pnModu.pnType;
		
	switch(pnType)
	{
		case U_PN_Loop_TYPE:
			if(pDev->pnModu.modu >= U_OneBoard_LOOP_MAX)
			{
				break;
			}
			sw_dev_Fig(pDev->pnModu.modu, 1, &pStr);
			swTotal += AddToTextBuf(pStr);
			swTotal += AddCstStrToTextBuf(&cstChar_Modu_Loop); //��·//
			break;
			
		case U_PN_Opea_TYPE:
			break;
			
		case U_PN_Drt_TYPE:
			if(pDev->pnModu.modu >= U_OneBoard_DrtModu_MAX)
			{
				break;
			}
			sw_dev_Fig(pDev->pnModu.modu, 1, &pStr);
			swTotal += AddToTextBuf(pStr);
			swTotal += AddCstStrToTextBuf(&cstChar_Modu_Pad); //·//
			
			
			mduLine = pDev->pnModu.mduLine;
			if(mduLine >= U_Drt_MduFunc_MAX)
			{
				break;
			}
			switch(mduLine)
			{
				case U_Drt_MduFunc_Action:
					swTotal += AddCstStrToTextBuf(&cstChar_Action);
					break;
				case U_Drt_MduFunc_Stop:
					swTotal += AddCstStrToTextBuf(&cstChar_Stop);	
					break;
				case U_Drt_MduFunc_Ack:
					swTotal += AddCstStrToTextBuf(&cstChar_Ack);	
					break;
				case U_Drt_MduFunc_AckRstr:
					swTotal += AddCstStrToTextBuf(&cstChar_AckRstr);	
					break;
				case U_Drt_MduFunc_AckMiss:
					swTotal += AddCstStrToTextBuf(&cstChar_AckMiss);	
					break;
				default:
					break;
			}
			break;
			
		case U_PN_Bus_TYPE:
			break;
			
		case U_PN_Extg_TYPE:
			if(pDev->pnModu.modu >= U_OneBoard_ExtgModu_MAX)
			{
				break;
			}
			sw_dev_Fig(pDev->pnModu.modu, 1, &pStr);
			swTotal += AddToTextBuf(pStr);
			swTotal += AddCstStrToTextBuf(&cstChar_Modu_Pad); //·
			
			
			mduLine = pDev->pnModu.mduLine;
			if(mduLine >= U_Extg_MduFunc_MAX)
			{
				break;
			}
			switch(mduLine)
			{
				case U_Extg_MduFunc_Action:
					swTotal += AddCstStrToTextBuf(&cstChar_Action);
					break;
				default:
					break;
			}
			
			break;
			
		case U_PN_Broad_TYPE:			
			break;
			
		case U_PN_Power_TYPE:
			mduLine = pDev->pnModu.mduLine;
			switch(mduLine)
			{
				case U_Power_MduFunc_pwrMain:
					swTotal += AddCstStrToTextBuf(&cstChar_pwrMain);
					break;
				case U_Power_MduFunc_pwrBty:
					swTotal += AddCstStrToTextBuf(&cstChar_pwrBty);
					break;
				default:
					break;
			}
			break;
			
		case U_PN_Other_TYPE:
		default:
			break;		
	}
	return swTotal;
}


/******************************************************************************
* FUNC: //
******************************************************************************/
// OUT: TextBuf[], �ַ���
U8 sw_DevPanel_String(TDev_un *pDev)
{
U8 pnType;
U8 swTotal = 0;
U8 *pStr;
	
	
	sw_dev_Fig(pDev->pnModu.pnSequ, 2, &pStr);
	swTotal += AddToTextBuf(pStr);
	
	
	pnType = pDev->pnModu.pnType;
	
	switch(pnType)
	{
		case U_PN_Loop_TYPE:
			swTotal += AddCstStrToTextBuf(&cstChar_Pn_Loop);
			break;
		case U_PN_Opea_TYPE:
			swTotal += AddCstStrToTextBuf(&cstChar_Pn_Opea);
			break;
		case U_PN_Drt_TYPE:
			swTotal += AddCstStrToTextBuf(&cstChar_Pn_Drt);
			break;
		case U_PN_Bus_TYPE:
			swTotal += AddCstStrToTextBuf(&cstChar_Pn_Bus);
			break;
		case U_PN_Extg_TYPE:
			swTotal += AddCstStrToTextBuf(&cstChar_Pn_Extg);
			break;
		case U_PN_Broad_TYPE:
			swTotal += AddCstStrToTextBuf(&cstChar_Pn_Broad);
			break;
		case U_PN_Power_TYPE:
			swTotal += AddCstStrToTextBuf(&cstChar_Pn_Power);
			break;
		case U_PN_Other_TYPE:
		default:
			swTotal += AddCstStrToTextBuf(&cstChar_Pn_Other);
			break;		
	}
	return swTotal;
	
}


/******************************************************************************
* FUNC: //
******************************************************************************/
// OUT: TextBuf[], �ַ���
U8 sw_DevMachine_String(TDev_un *pDev)
{
U32 swTotal = 0;
U8 *pStr;

	if(!bMachineIdIsMe(pDev->stDete.machine))
	{
		sw_dev_Fig(pDev->stDete.machine, 2, &pStr);
		swTotal += AddToTextBuf(pStr);
		swTotal += AddCstStrToTextBuf(&cstChar_Machine);
	}
	return swTotal;
}

// OUT: TextBuf[], �ַ���
U8 sw_DevMachinMe_String(void)
{
U32 swTotal = 0;
	
		swTotal += AddCstStrToTextBuf(&cstChar_MachinMe);
	return swTotal;
}


/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
// ��ʾ��·�ֳ����� �豸����
// OUT: TextBuf[], �ַ���
U8 sw_DeteType_String(U8 mType)
{
const TCstChar_st *pDeteCstChar;
U32 swTotal = 0;
	
	if(GetCstChar_DeteType(mType, &pDeteCstChar))
	{
		swTotal += AddCstStrToTextBuf(pDeteCstChar);
	}
	
	return swTotal;
}

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/


// �ַ���ʽ ��ʾ ��·�ֳ����� �豸����:
TYPE_LCD_XY Show_Dete_Type_String(TYPE_LCD_RL mRow, TYPE_LCD_RL mLine, 
											U8 type)
{
	IniTextBuf(U_ShowUseLib_88orCn_CN);
	sw_DeteType_String(type);
	return ShowTextBuf(mRow, mLine);
}

// �ַ���ʽ ��ʾ ��·�ֳ�����:
TYPE_LCD_XY Show_Dete_String(TYPE_LCD_RL mRow, TYPE_LCD_RL mLine, 
											TDev_un *pDev)
{
	IniTextBuf(U_ShowUseLib_88orCn_CN);
	sw_Dete_String(pDev);
	return ShowTextBuf(mRow, mLine);
}


//OUT: ��ʾ�ַ�����
// ������ʽ ��ʾ ��·�ֳ�����:
TYPE_LCD_XY Show_Dete_Char(TYPE_LCD_RL mRow, TYPE_LCD_RL mLine, 
											TDev_un *pDev)
{
	IniTextBuf(U_ShowUseLib_88orCn_CN);
	//sw_Dete_Char(pDev);
	sw_Dete_String(pDev);
	return ShowTextBuf(mRow, mLine);

}

/******************************************************************************
* FUNC: //
******************************************************************************/



/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

