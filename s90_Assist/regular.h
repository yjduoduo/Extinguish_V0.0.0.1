#ifndef __regular_H__
#define __regular_H__
/******************************************************************************
* @file    regular.h
* @author  yx
* @version V1.1
* @date    2013-07-02
* @brief   简称；
			记录一些算法；

* V1.1， 2013-07-02
* V1.0， 2012-01-05
******************************************************************************/

/******************************************************************************
** 简称 常用: **


#define LoopPn		LoopPanel		//回路板
#define DirectPn		DirectPanel		//多线盘
#define ExtgPn		Extinguish		//灭火盘
#define BusPn			BusPanel			//总线盘
#define BroadPn		BroadCastPanel	//广播盘

#define cmpnt		component	//部件，包括panel,现场部件、电源等所有组成控制器的部件。
#define dete		detector //探测器，泛指回路所管理的现场部件，在未明确指出时，包括回路里的层显。

******************************************************************************/

/*
const=cst    私有变量 private=v ;  函数输入 MyIn = m ;
*/

/*=================  ================================================*/
/*
主电 pwrMain, powerMain
备电 pwrBty,  powerBattery
运行 run 

联动  link 
启动  action 
反馈  ack
监管  spvs 		supervise
屏蔽  dsab       disable
#define Rstr		restore	//恢复,故障恢复，反馈撤销
*/

/*================= 规则1 简称 < ======================================
#define Af		Alarm and Fault	//
#define AorF		AutoOrForbid	//
#define Annu		Annunciator,audible and/or visible alarm //声光警报器
#define Broad		BroadCast	//音频广播
#define Brd		Broad  //广播消息
#define Chnl		Channel		//
#define Corres	Correspond		//对应
#define cmpnt		component	//部件，包括panel,现场部件、电源等所有组成控制器的部件。
#define Cls		Class		//分类
#define cfg		Config
#define dev 		Device   //释义 同component，部件。
#define dete		detector //探测器，泛指回路所管理的现场部件，在未明确指出时，包括回路里的层显。
#define Drt		Direct  //多线(路)
#define Extg		Extinguish	//灭火
#define Ft		Fault  //故障
#define Modu		Module		//模块 回路现场部件里的输出模块
#define Pn		Panel		//盘
#define Prt		Print		//
#define Pwr		Power		//
#define RoS		Run and/or Stop		//启停
#define Rstr		restore	//恢复,故障恢复，反馈撤销
#define Rq		Inquire		//查询   require	//需要, 要求, 命令
#define OnOff		On and/or Off		//开关
#define Opea		Operate		//操作
#define Stdard		standardize	//标定
#define Senstiv		sensitivity	//灵敏度
#define spray     //喷洒
#define UnDisable  UnDisable	//取消屏蔽
#define scr  Screen	//屏幕
#define Vry Verify	//

#define Ack		Feedback	//模块的反馈

#define Rsps		response	//反馈
#define SudLedShow		s	//音响、指示灯、显示变化的总称
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
dev	device  现场部件 待定
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
item	事件buf里各事件
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
WR	可读可写
	
	
	Annunciator

=================== 规则1 简称 > ====================================*/

/*================= 规则2 < ===========================================

定义函数，名称和‘(’间无空格； 函数实体，名称和‘(’间1空格。
返回值为TURE/FALSE的函数，用b1/0…开始。
1.	Min Max
Min定义为最小的一个数，Max定义为允许的最大数+1. 
2.	Adr  Addr
Addr专指回路现场部件的地址。 其它包括flash都用Adr. 
3.	item sequ
item可以是任意一条
sequ是顺序的一条。
3. num, locat

4.	结构
需要尽快找到结构体的定义
需要尽快找到结构对应的结构体
typedef struct 
{
	U8    IsUsing;     
    U8   Sign;      
    TMRWORD   SetMSec;    
    TMRWORD   OrgMSec;    
}TTaskTimer_st;
TTaskTimer_st stTaskTimer  //1空格,无所谓，找定义时加分号就可以了。找结构原型在结构前加}.
5.	变量命名
变量名的平均长度在8~20个字符，调试程序所需花费的气力是最小的；
避免使用短的变量名
类似于Total, Sum, Average, Max Min, Record, Sting, Pointer这样的限定词来修改某个名字，那么请记住把限定词加到名字的最后。 例外，Num的限定词的位置已约定成俗，Num放在变量名的开始位置代表一个总数：numCustomers表示的是当前员工的总数。Num放在变量名的结束位置代表一个下标：customerNum表示的是当前员工的序号。但这样使用Num常常会带来麻烦，因此可能最好的办法是避开这些问题，，用Count或者Total来代表员工的总数，用Index来指代某个特定的员工。这样customerCount就代表员工的总数，customerIndex代表某个特定的员工。
在循环嵌套里，应该给循环变量赋予更长的名字以提高可读性
为状态变量取一个比flag更好的名字
警惕临时变量。 比如用discriminant:判别式  代替 temp
6.	为布尔变量命名
典型的布尔变量名:  done  error   found    success或ok . 如果完成处理就表示这个程序执行成功，那么或许你应该用processingComplete来取而代之。
给布尔变量赋予隐含“真/假”含义的名字，比如不用status或sourceFile.
使用肯定的布尔变量名。 比如不用notDone.
7.	对仗词
begin/end;  first/last; locked/unlocked;  min/max;  next/previous;  old/new;  opened/closed; visible/unvisible;  source/ target;  source/detination;  up/down.
Add / remove ;  increment / decrement ;  open / close ;   begin /end ;   insert / delete ;   show / hide ;  create / destroy ;   lock / unlock  ;   source / target ;   first / last ;   min / max ;   start / stop ;   get / put ;    next / previous ;  up / down  ;    get / set ;    old / new .

8.	格式
word一行的字符数：最长80字符。



=================== 规则2 > =========================================*/




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
** 名词: **

EPI: Extended Peripheral Interface (EPI)
高速并行总线。

NMI: PB7: External non-maskable interrupt signal (NMI)
*****************************************************************************
*/

/*
*****************************************************************************
// 双指针
** 语法: 双指针**
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
// const 固定地址存储：
** 语法: **
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
