/*
*********************************************************************************************************
*                               对象: hwEx03_Pcf8563
*                        (c) Copyright 2000-2004, 勾利金
*                              All Rights Reserved
;* File : hwEx03_Pcf8563.c
;* Ver1.0
;* 时间 : 2004-7-12
*********************************************************************************************************
*/
#define   hwEx03_Pcf8563_C

#include  "hwEx03_Pcf8563.h"
#include  "hw16_IIC.h" 
					  
/*================= 常数 ============================================*/

/*================= 常数 ============================================*/
#define  PCF8563ADR 0xA2	//器件地址0A2H   cI2CAddr_PCF8563 

#define  cPCF8563Start      1 
#define  cPCF8563Stop       0

/**********************************************************************************************************
 *  数据转换
 **********************************************************************************************************/
#define  BCD_to_HEC(b)   ((((b&0xf0)>>4)*10)+(b&0x0f))  //((b/16)*10 + b%16)    //
#define  HEC_to_BCD(h)   ((h/10)*16 + h%10)      //(((h/10)<<4)|(h%10))

/*******************************************************************/
/********************* 私有成员变量,函数及常量    *******************/
/*******************************************************************/
//Private:
#ifdef  hwEx03_Pcf8563_C

#define  cClockBufNum    16
#define  cClockMaxTime   10

#define  cAddr_Sencond  0x02            //秒存放地址
#define  cAddr_AlarmM   0x09            //报警分存放地址




//地址 内容	  位定义

//02h 秒      VL  00 59 BCD 码格式数	 0
//03h 分钟        00 59 BCD 码格式数	 1
//04h 小时        00 59 BCD 码格式数	 2
//05h 日          01 31 BCD 码格式数	 3
//06h 星期        0   6				     4
//07h 月/世纪  C  01 12 BCD 码格式数     5
//08h 年          00 99 BCD 码格式数     6
//09h 分钟报警 AE 00 59 BCD 码格式数
//0Ah 小时报警 AE 00 23 BCD 码格式数
//0BH 日报警AE 01 31 BCD 码格式数
//0CH 星期报警 AE

//00H 控制/状态寄存器   1  TEST1 0 STOP 0      TESTC  0    0   0
//01H 控制/状态寄存器   2  0     0 0    TI/TP  AF     TF   AIE TIE
//0DH CLKOUT 输出寄存器 FE -     - -    -      -      -    FD1 FD0
//0EH 定时器控制寄存器  TE -     - -    -      -      -    TD1 TD0	

//#define BCD_TO_DEC(x) ((x%16) + (x/16)*10) 
//#define DEC_TO_BCD(x) ((x%10) + ((x/10)*16))


//CLOCK *pAlarmClock;	


/*================= 定时器设置 ====================================*/

#define TimerOn         0x80
#define TimerOff        0x00
#define TimerClk4096Hz  0x00
#define TimerClk64Hz    0x01
#define TimerClk1Hz     0x02
#define TimerClk1_64Hz  0x03

/*================= 中断设置 ====================================*/
#define SetINT      0x80
#define ClearINT    0x40
#define TITP        0x10
#define AIE         0x02
#define TIE         0x01

#endif // hwEx03_Pcf8563_C
/*================= 私有结构变量声明 ================================*/
U8  m_ClockBuf[cClockBufNum];

TEvtClock_st *pCurClock;	 
/*=================  ================================*/

/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
void   Init_PCF8563(void) //初始化函数
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

//开启或关闭
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
** Descriptions:        读取PCF8563
** input parameters:    tp:    指向时间结构体的指针
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

//设置报警时间
void   SetAlarm_PCF8563(TEvtClock_st *pClock)
{ 
	  m_ClockBuf[cAddr_AlarmM+2]=0x80|HEC_to_BCD(pClock->day);       //日期报警
	  m_ClockBuf[cAddr_AlarmM+1]=0x80|HEC_to_BCD(pClock->hour);      //小时报警
	  m_ClockBuf[cAddr_AlarmM]=0x80|HEC_to_BCD(pClock->min);	  //分钟报警  
	  I2C_WriteNByte(PCF8563ADR,cAddr_AlarmM,&m_ClockBuf[cAddr_AlarmM],3);   
}

//读取报警时间
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
				  m_ClockBuf[cAddr_AlarmM+i]=0x80|m_ClockBuf[3+i];	  //分钟报警   
			}
		  I2C_WriteNByte(PCF8563ADR,cAddr_AlarmM,&m_ClockBuf[cAddr_AlarmM],3); 
	} 
}

/*********************************************************************************************************
** Function name:       PCF8563_Set_Timer
** Descriptions:        设置PCF8563的定时器
** input parameters:    cmd     TimerOn         使能定时器
**                              TimerOff        禁能定时器
**                              TimerClk4096Hz  设置定时器时钟源频率为4096Hz
**                              TimerClk64Hz    设置定时器时钟源频率为64Hz
**                              TimerClk1Hz     设置定时器时钟源频率为1Hz
**                              TimerClk1_64Hz  设置定时器时钟源频率为1/64Hz
**                      cnt     定时值
** Output parameters:   NONE
** Returned value:      TimerOn|TimerClk4096Hz    使能定时器,设置时钟源频率4096Hz
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
** Descriptions:        设置中断或读取中断状态
** input parameters:    cmd     SetINT      设置中断
*                               ClearINT    清除所有中断标致
*                               TITP        使能INT脉冲输出
*                               AIE         使能报警中断
*                               TIE         使能定时器中断
** Output parameters:   返回中断状态
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
