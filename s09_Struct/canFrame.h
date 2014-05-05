#ifndef __canFrame_H__
#define __canFrame_H__
/******************************************************************************
* @file    canFrame.h
* @author  yx
* @version V1.1
* @date    2013-07-26
* @brief   CAN֡��ʽ����Э���йصĲ����� "canProtocalStr.h"��
* 
V1.1, add taskId; 2013.7.26, yx;

#include  "canFrame.h"
******************************************************************************/

#include  "prjCompileCon.h"
#include  "canProtocalStr.h"
/*================= extern ============================================*/
#ifdef  __canFrame_C__
#define EX_canFrame
#else
#define EX_canFrame extern 
#endif


/*================= �ṹ�嶨�� ======================================*/

/*================= ���нṹ�������� ================================*/
#define U_CAN_HARDFRAME_U8_MAX		8	   
#define U_CAN_HARDFRAME_U32_MAX		2	
  
//#pragma pack(4)
typedef struct
{			   
	U8 length; //��У���ֽ�
	U8 taskId;
	
	CanID id;
	
	union{	
		U8  rtU8[U_CAN_HARDFRAME_U8_MAX];
		U32 rtU32[U_CAN_HARDFRAME_U32_MAX]; 
	}rtData;
}THdCanFrame_st;  
//#pragma pack()


/*================= ���� ============================================*/
#define U_CAN_1Frame_FileByte (U_CAN_HARDFRAME_U8_MAX-1)	   

/*================= ���к������� ====================================*/
//EX_canFrame 

extern void CanFrmSetInvalid(THdCanFrame_st  *pFrm);
extern void CanFrmSet_all_FF(THdCanFrame_st  *pFrm);
extern void CanFrmSet_all_00(THdCanFrame_st  *pFrm);
extern void CanFrmSet_all_test12345(U8 mIniVal, THdCanFrame_st  *pFrm);



/******************************************************************************
// END :
******************************************************************************/
#endif // __canFrame_H__

