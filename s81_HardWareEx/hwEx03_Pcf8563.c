/*
*********************************************************************************************************
*                               ����: hwEx03_Pcf8563
*                        (c) Copyright 2000-2004, ������
*                              All Rights Reserved
;* File : hwEx03_Pcf8563.c
;* Ver1.0
;* ʱ�� : 2004-7-12
*********************************************************************************************************
*/
#define   hwEx03_Pcf8563_C

#include  "hwEx03_Pcf8563.h"
#include  "hw16_IIC.h" 
					  
/*================= ���� ============================================*/

/*================= ���� ============================================*/
#define  PCF8563ADR 0xA2	//������ַ0A2H   cI2CAddr_PCF8563 

#define  cPCF8563Start      1 
#define  cPCF8563Stop       0

/**********************************************************************************************************
 *  ����ת��
 **********************************************************************************************************/
#define  BCD_to_HEC(b)   ((((b&0xf0)>>4)*10)+(b&0x0f))  //((b/16)*10 + b%16)    //
#define  HEC_to_BCD(h)   ((h/10)*16 + h%10)      //(((h/10)<<4)|(h%10))

/*******************************************************************/
/********************* ˽�г�Ա����,����������    *******************/
/*******************************************************************/
//Private:
#ifdef  hwEx03_Pcf8563_C

#define  cClockBufNum    16
#define  cClockMaxTime   10

#define  cAddr_Sencond  0x02            //���ŵ�ַ
#define  cAddr_AlarmM   0x09            //�����ִ�ŵ�ַ




//��ַ ����	  λ����

//02h ��      VL  00 59 BCD ���ʽ��	 0
//03h ����        00 59 BCD ���ʽ��	 1
//04h Сʱ        00 59 BCD ���ʽ��	 2
//05h ��          01 31 BCD ���ʽ��	 3
//06h ����        0   6				     4
//07h ��/����  C  01 12 BCD ���ʽ��     5
//08h ��          00 99 BCD ���ʽ��     6
//09h ���ӱ��� AE 00 59 BCD ���ʽ��
//0Ah Сʱ���� AE 00 23 BCD ���ʽ��
//0BH �ձ���AE 01 31 BCD ���ʽ��
//0CH ���ڱ��� AE

//00H ����/״̬�Ĵ���   1  TEST1 0 STOP 0      TESTC  0    0   0
//01H ����/״̬�Ĵ���   2  0     0 0    TI/TP  AF     TF   AIE TIE
//0DH CLKOUT ����Ĵ��� FE -     - -    -      -      -    FD1 FD0
//0EH ��ʱ�����ƼĴ���  TE -     - -    -      -      -    TD1 TD0	

//#define BCD_TO_DEC(x) ((x%16) + (x/16)*10) 
//#define DEC_TO_BCD(x) ((x%10) + ((x/10)*16))


//CLOCK *pAlarmClock;	


/*================= ��ʱ������ ====================================*/

#define TimerOn         0x80
#define TimerOff        0x00
#define TimerClk4096Hz  0x00
#define TimerClk64Hz    0x01
#define TimerClk1Hz     0x02
#define TimerClk1_64Hz  0x03

/*================= �ж����� ====================================*/
#define SetINT      0x80
#define ClearINT    0x40
#define TITP        0x10
#define AIE         0x02
#define TIE         0x01

#endif // hwEx03_Pcf8563_C
/*================= ˽�нṹ�������� ================================*/
U8  m_ClockBuf[cClockBufNum];

TEvtClock_st *pCurClock;	 
/*=================  ================================*/

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
void   Init_PCF8563(void) //��ʼ������
{
    // IniPinFunc_IIC();
	Init_CI2c();
	
	SS_PCF8563(cPCF8563Start); 
}

 

void  SetPCF8563(TEvtClock_st *pCurClock)
{   
	  U8 i=0;  
	  m_ClockBuf[i++]= 0x00;
	  m_ClockBuf[i++]= 0x1f;
    m_ClockBuf[i++]= HEC_to_BCD(pCurClock->sec);
    m_ClockBuf[i++]= HEC_to_BCD(pCurClock->min);
    m_ClockBuf[i++]= HEC_to_BCD(pCurClock->hour);
    m_ClockBuf[i++]= HEC_to_BCD(pCurClock->day);
    m_ClockBuf[i++]= 02;
    m_ClockBuf[i++]= HEC_to_BCD(pCurClock->month);	
	  m_ClockBuf[i++]= HEC_to_BCD(pCurClock->year);	  
    I2C_WriteNByte(PCF8563ADR,0, m_ClockBuf, i);  
}	

//������ر�
U8  SS_PCF8563(U8 vComm)
{
	 U8 temp; 
   if (vComm== cPCF8563Start)
      temp = 0;
   else
      temp = 0x20;
   return(I2C_WriteNByte(PCF8563ADR,0x00, &temp, 1));  
}


/*********************************************************************************************************
** Function name:       PCF8563_Read
** Descriptions:        ��ȡPCF8563
** input parameters:    tp:    ָ��ʱ��ṹ���ָ��
** Output parameters:   FALSE or TRUE
** Returned value:      NONE
*********************************************************************************************************/
U8 PCF8563_Read(TEvtClock_st *tp)
{ 
   if (I2C_ReadNByte(PCF8563ADR,0x02, m_ClockBuf, 7)==0)
      return 0;

   tp->sec       = BCD_to_HEC((m_ClockBuf[0]&0x7f));
   tp->min    = BCD_to_HEC((m_ClockBuf[1]&0x7f));
   tp->hour      = BCD_to_HEC((m_ClockBuf[2]&0x3f));
   tp->day       = BCD_to_HEC((m_ClockBuf[3]&0x3f));
   //tp->week       = BCD_to_HEC((m_ClockBuf[4]&0x07));  
   tp->month = BCD_to_HEC((m_ClockBuf[5]&0x1f));
   tp->year  = BCD_to_HEC(m_ClockBuf[6]);
   return 1;
}

//���ñ���ʱ��
void   SetAlarm_PCF8563(TEvtClock_st *pClock)
{ 
	  m_ClockBuf[cAddr_AlarmM+2]=0x80|HEC_to_BCD(pClock->day);       //���ڱ���
	  m_ClockBuf[cAddr_AlarmM+1]=0x80|HEC_to_BCD(pClock->hour);      //Сʱ����
	  m_ClockBuf[cAddr_AlarmM]=0x80|HEC_to_BCD(pClock->min);	  //���ӱ���  
	  I2C_WriteNByte(PCF8563ADR,cAddr_AlarmM,&m_ClockBuf[cAddr_AlarmM],3);   
}

//��ȡ����ʱ��
void  GetAlarm_PCF8563(TEvtClock_st *pClock)
{
	if(I2C_ReadNByte(PCF8563ADR,2,&m_ClockBuf[2],10))
	{	  
			U8 i;	 
		  i=m_ClockBuf[cAddr_AlarmM+2];
		  pClock->day=BCD_to_HEC(i&0x3f); 
		
		  i=m_ClockBuf[cAddr_AlarmM+1];
			pClock->hour=BCD_to_HEC(i&0x3f); 
		
		  i=m_ClockBuf[cAddr_AlarmM];
			pClock->min =BCD_to_HEC(i&0x7f); 
		
		  for(i=0;i<3;i++)
			{
				  m_ClockBuf[cAddr_AlarmM+i]=0x80|m_ClockBuf[3+i];	  //���ӱ���   
			}
		  I2C_WriteNByte(PCF8563ADR,cAddr_AlarmM,&m_ClockBuf[cAddr_AlarmM],3); 
	} 
}

/*********************************************************************************************************
** Function name:       PCF8563_Set_Timer
** Descriptions:        ����PCF8563�Ķ�ʱ��
** input parameters:    cmd     TimerOn         ʹ�ܶ�ʱ��
**                              TimerOff        ���ܶ�ʱ��
**                              TimerClk4096Hz  ���ö�ʱ��ʱ��ԴƵ��Ϊ4096Hz
**                              TimerClk64Hz    ���ö�ʱ��ʱ��ԴƵ��Ϊ64Hz
**                              TimerClk1Hz     ���ö�ʱ��ʱ��ԴƵ��Ϊ1Hz
**                              TimerClk1_64Hz  ���ö�ʱ��ʱ��ԴƵ��Ϊ1/64Hz
**                      cnt     ��ʱֵ
** Output parameters:   NONE
** Returned value:      TimerOn|TimerClk4096Hz    ʹ�ܶ�ʱ��,����ʱ��ԴƵ��4096Hz
*********************************************************************************************************/
U8 PCF8563_Set_Timer(U8 cmd, U8 cnt)
{
   U8 b[2];
   b[0] = cmd;
   b[1] = cnt;
   return(I2C_WriteNByte(PCF8563ADR,0x0E, b, 2));
}

/*********************************************************************************************************
** Function name:       PCF8563_INT_State
** Descriptions:        �����жϻ��ȡ�ж�״̬
** input parameters:    cmd     SetINT      �����ж�
*                               ClearINT    ��������жϱ���
*                               TITP        ʹ��INT�������
*                               AIE         ʹ�ܱ����ж�
*                               TIE         ʹ�ܶ�ʱ���ж�
** Output parameters:   �����ж�״̬
** Returned value:      NONE
*********************************************************************************************************/
U8 PCF8563_INT_State(U8 cmd)
{
   U8 temp,INTstate;
   temp = 0;

   if ((cmd&SetINT) == SetINT){
      temp = (cmd&0x1f);
      I2C_WriteNByte(PCF8563ADR, 0x01, &temp, 1);
      I2C_ReadNByte(PCF8563ADR,0x01, &temp, 1);
      return (temp&0x1f);
   }
   else if ((cmd&0x40) == ClearINT){
      I2C_ReadNByte(PCF8563ADR,0x01, &temp, 1);
      INTstate = (temp&0x1f);
      temp &= 0x13;
      I2C_WriteNByte(PCF8563ADR,0x01, &temp, 1);
      return INTstate;
   }
   return 0;
}

/******************************************************************************
* FUNC: // END
*   IN:
*  OUT: 
******************************************************************************/
