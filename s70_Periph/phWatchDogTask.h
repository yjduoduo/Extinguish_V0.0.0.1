#ifndef __phWatchDogTask_H__
#define __phWatchDogTask_H__
/******************************************************************************
* @file    phWatchDogTask.h
* @author  yx
* @version V1.0
* @date    2012-01-05
* @brief   
* 
#include  "phWatchDogTask.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

/*================= extern ============================================*/
#ifdef  __phWatchDogTask_C__
#define EX_phWatchDogTask
#else
#define EX_phWatchDogTask extern 
#endif
/*================= ���� ============================================*/

enum emTaskIdBits{
	
	U_Dog_SysTimer_tick_Bit = ( 1 <<  0),
	U_Dog_HeartBeat_Bit 	= ( 1 <<  1),
};

//#define U_NEED_FEED_DOG_BITS  (U_Dog_SysTimer_tick_Bit)

#define U_NEED_FEED_DOG_BITS  ( U_Dog_SysTimer_tick_Bit  \
							  )

/*================= �ṹ�嶨�� ======================================*/

/*================= ���нṹ�������� ================================*/
/*
typedef struct{
	U8 sequStart;
}TStruct_st;
TStruct_st stStruct;
*/

/*================= ���к������� ====================================*/
//EX_phWatchDogTask 

EX_phWatchDogTask  void WatchDog_AddSupviseBits(uint32 mDogTaskId);
EX_phWatchDogTask  void WatchDog_MoveawaySupviseBits(uint32 mDogTaskId);

EX_phWatchDogTask  void SetWatchDogBits(uint32 mDogTaskId);
EX_phWatchDogTask  void Clear_MyWatchDog(void);



/*================= ˽�к������� ====================================*/
#ifdef  __phWatchDogTask_C__

uint32 bHaveFeedDog;    	//����������ִ��ʱ��λ
#endif
/******************************************************************************
// END :
******************************************************************************/
#endif // __phWatchDogTask_H__

