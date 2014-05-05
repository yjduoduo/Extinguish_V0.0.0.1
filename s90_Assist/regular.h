#ifndef __regular_H__
#define __regular_H__
/******************************************************************************
* @file    regular.h
* @author  yx
* @version V1.1
* @date    2013-07-02
* @brief   ��ƣ�
			��¼һЩ�㷨��

* V1.1�� 2013-07-02
* V1.0�� 2012-01-05
******************************************************************************/

/******************************************************************************
** ��� ����: **


#define LoopPn		LoopPanel		//��·��
#define DirectPn		DirectPanel		//������
#define ExtgPn		Extinguish		//�����
#define BusPn			BusPanel			//������
#define BroadPn		BroadCastPanel	//�㲥��

#define cmpnt		component	//����������panel,�ֳ���������Դ��������ɿ������Ĳ�����
#define dete		detector //̽��������ָ��·��������ֳ���������δ��ȷָ��ʱ��������·��Ĳ��ԡ�

******************************************************************************/

/*
const=cst    ˽�б��� private=v ;  �������� MyIn = m ;
*/

/*=================  ================================================*/
/*
���� pwrMain, powerMain
���� pwrBty,  powerBattery
���� run 

����  link 
����  action 
����  ack
���  spvs 		supervise
����  dsab       disable
#define Rstr		restore	//�ָ�,���ϻָ�����������
*/

/*================= ����1 ��� < ======================================
#define Af		Alarm and Fault	//
#define AorF		AutoOrForbid	//
#define Annu		Annunciator,audible and/or visible alarm //���⾯����
#define Broad		BroadCast	//��Ƶ�㲥
#define Brd		Broad  //�㲥��Ϣ
#define Chnl		Channel		//
#define Corres	Correspond		//��Ӧ
#define cmpnt		component	//����������panel,�ֳ���������Դ��������ɿ������Ĳ�����
#define Cls		Class		//����
#define cfg		Config
#define dev 		Device   //���� ͬcomponent��������
#define dete		detector //̽��������ָ��·��������ֳ���������δ��ȷָ��ʱ��������·��Ĳ��ԡ�
#define Drt		Direct  //����(·)
#define Extg		Extinguish	//���
#define Ft		Fault  //����
#define Modu		Module		//ģ�� ��·�ֳ�����������ģ��
#define Pn		Panel		//��
#define Prt		Print		//
#define Pwr		Power		//
#define RoS		Run and/or Stop		//��ͣ
#define Rstr		restore	//�ָ�,���ϻָ�����������
#define Rq		Inquire		//��ѯ   require	//��Ҫ, Ҫ��, ����
#define OnOff		On and/or Off		//����
#define Opea		Operate		//����
#define Stdard		standardize	//�궨
#define Senstiv		sensitivity	//������
#define spray     //����
#define UnDisable  UnDisable	//ȡ������
#define scr  Screen	//��Ļ
#define Vry Verify	//

#define Ack		Feedback	//ģ��ķ���

#define Rsps		response	//����
#define SudLedShow		s	//���졢ָʾ�ơ���ʾ�仯���ܳ�
#define S		s	//
#define S		s	//
#define S		s	//
#define S		s	//
#define S		s	//
#define S		s	//
#define S		s	//


blk	block
chk	check
cst	const
cur	current
dev	device  �ֳ����� ����
dly	delay
evt	event
fig	figure
fls	flash
frm	frame
hd	hard
hist	history
HMSM	Hours Minites Seconds Milliseconds
YMDHMS	Year Month Day Hour Minite Second
	
int	interrupt
inx	index
item	�¼�buf����¼�
jdg	judge
mach	machine  
num	number
pg	page
prb	probation 
psw	password
rd	read
str	struct
sys	system
tmr	timer
wr	write
WR	�ɶ���д
	
	
	Annunciator

=================== ����1 ��� > ====================================*/

/*================= ����2 < ===========================================

���庯�������ƺ͡�(�����޿ո� ����ʵ�壬���ƺ͡�(����1�ո�
����ֵΪTURE/FALSE�ĺ�������b1/0����ʼ��
1.	Min Max
Min����Ϊ��С��һ������Max����Ϊ����������+1. 
2.	Adr  Addr
Addrרָ��·�ֳ������ĵ�ַ�� ��������flash����Adr. 
3.	item sequ
item����������һ��
sequ��˳���һ����
3. num, locat

4.	�ṹ
��Ҫ�����ҵ��ṹ��Ķ���
��Ҫ�����ҵ��ṹ��Ӧ�Ľṹ��
typedef struct 
{
	U8    IsUsing;     
    U8   Sign;      
    TMRWORD   SetMSec;    
    TMRWORD   OrgMSec;    
}TTaskTimer_st;
TTaskTimer_st stTaskTimer  //1�ո�,����ν���Ҷ���ʱ�ӷֺžͿ����ˡ��ҽṹԭ���ڽṹǰ��}.
5.	��������
��������ƽ��������8~20���ַ������Գ������軨�ѵ���������С�ģ�
����ʹ�ö̵ı�����
������Total, Sum, Average, Max Min, Record, Sting, Pointer�������޶������޸�ĳ�����֣���ô���ס���޶��ʼӵ����ֵ���� ���⣬Num���޶��ʵ�λ����Լ�����ף�Num���ڱ������Ŀ�ʼλ�ô���һ��������numCustomers��ʾ���ǵ�ǰԱ����������Num���ڱ������Ľ���λ�ô���һ���±꣺customerNum��ʾ���ǵ�ǰԱ������š�������ʹ��Num����������鷳����˿�����õİ취�Ǳܿ���Щ���⣬����Count����Total������Ա������������Index��ָ��ĳ���ض���Ա��������customerCount�ʹ���Ա����������customerIndex����ĳ���ض���Ա����
��ѭ��Ƕ���Ӧ�ø�ѭ�����������������������߿ɶ���
Ϊ״̬����ȡһ����flag���õ�����
������ʱ������ ������discriminant:�б�ʽ  ���� temp
6.	Ϊ������������
���͵Ĳ���������:  done  error   found    success��ok . �����ɴ���ͱ�ʾ�������ִ�гɹ�����ô������Ӧ����processingComplete��ȡ����֮��
����������������������/�١���������֣����粻��status��sourceFile.
ʹ�ÿ϶��Ĳ����������� ���粻��notDone.
7.	���̴�
begin/end;  first/last; locked/unlocked;  min/max;  next/previous;  old/new;  opened/closed; visible/unvisible;  source/ target;  source/detination;  up/down.
Add / remove ;  increment / decrement ;  open / close ;   begin /end ;   insert / delete ;   show / hide ;  create / destroy ;   lock / unlock  ;   source / target ;   first / last ;   min / max ;   start / stop ;   get / put ;    next / previous ;  up / down  ;    get / set ;    old / new .

8.	��ʽ
wordһ�е��ַ������80�ַ���



=================== ����2 > =========================================*/




/*

#if defined(TARGET_IS_DUSTDEVIL_RA0) || \
    defined(TARGET_IS_TEMPEST_RB1) || \
    defined(TARGET_IS_TEMPEST_RC1) || \
    defined(TARGET_IS_TEMPEST_RC3) || \
    defined(TARGET_IS_TEMPEST_RC5) || \
    defined(TARGET_IS_FIRESTORM_RA2) || \
    defined(TARGET_IS_BLIZZARD_RA1)
#define ROM_ADCSequenceDataGet                                                \
        ((long (*)(unsigned long ulBase,                                      \
                   unsigned long ulSequenceNum,                               \
                   unsigned long *pulBuffer))ROM_ADCTABLE[0])
#endif
*/


/*
*****************************************************************************
** ����: **

EPI: Extended Peripheral Interface (EPI)
���ٲ������ߡ�

NMI: PB7: External non-maskable interrupt signal (NMI)
*****************************************************************************
*/

/*
*****************************************************************************
// ˫ָ��
** �﷨: ˫ָ��**
U8 vBuf1[0x10];
U8 vBuf2[0x10];
U8 mByte;
U8 *pByte;

void test_DoublePoint(U8 ii, U8 **pRtnByte)
{
	*pRtnByte = &vBuf1[ii];
}

void test_Point(void)
{
U32 ii;
	
	for(ii=0; ii<0x10; ii++)
	{
		vBuf1[ii] = 0x10+ii;
		vBuf2[ii] = ~0;
	}
	
	for(ii=0; ii<10; ii++)
	{
		test_DoublePoint(ii, &pByte);
		mByte = *pByte;
		vBuf2[ii] = mByte;
	}
}



*****************************************************************************
*/


/*
*****************************************************************************
// const �̶���ַ�洢��
** �﷨: **
#define CS_EEPROM_ON   	do{TRIS_CS_EEPROM=0; 	P_CS_EEPROM=0;}		while(0)
#define SECS_PER_YEAR   (365*24*3600)UL   // UL = unsigned long

U8 FlashBuf[U_SECTOR_BYTE_MAX] __attribute__ ((aligned (4)));

#include <absacc.h> 
const  U8  HZK16[] __at(0x10000) = {
..............................
};


*****************************************************************************
*/

/******************************************************************************
* FUNC: //END
******************************************************************************/
#endif // __regular_H__
