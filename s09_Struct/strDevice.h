#ifndef __strDevice_H__
#define __strDevice_H__
/******************************************************************************
* @file    strDevice.h
* @author  yx
* @version V1.1
* @date    2013-10-24
* @brief   
*
* V1.1  2013-10-24
*		U_SYS_LOOP_MAX :  64 -> 4
* 		U_OneBoard_LOOP_MAX: 8 -> 1;
*		add: U_1ExtgLOOP_DETE_MAX, U_1ExtgLOOP_DeteLink_MAX;
* V1.0  2012-01-01
* 
#include  "strDevice.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

#include  "strDevMLAT.h" //dev的详细定义
#include  "loopFieldTypeState.h" //回路现场部件的类型和状态


/*================= extern ============================================*/
#ifdef  __strDevice_C__
#define EX_strDevice
#else
#define EX_strDevice extern 
#endif
/*================= 常数 ============================================*/
//#define 
/*================= 结构体定义 ======================================*/

/*================= 公有结构变量声明 ================================*/

#define U_DEV_ADDR_BYTE_MAX	   5

#pragma pack(1)	
typedef union{
	TCommonMLAT_st  stDete;  //stField
	TModuMLAT_st    pnModu;
	
}TDev_un;  //很可能不是 4 bytes.
#pragma pack()	


/*=================Dev分类 常数 ============================================*/
	//判断stDev的类型，是机器、panel、panel.modu、64回路之一：
enum emDevClass{ 	//dev类型	

	U_DEV_IS_Machine_TYPE	= 0x0, //控制器
	U_DEV_IS_Panel_TYPE		= 0x1, //各单元板
	U_DEV_IS_PnModu_TYPE	= 0x3, //单元-路
	U_DEV_IS_ModuLine_TYPE	= 0x4, //单元-路-功能
	U_DEV_IS_Dete_TYPE		= 0x2, //回路现场部件
	U_DEV_IS_Channel_TYPE		= 0x5, //回路现场部件
	U_DEV_TYPE_MAX			= 0x6 //
};


enum emDevNum{ // 数量定义
	
	U_SYS_LOOP_MAX 		= 4,	// U_OneBoard_LOOP_MAX * U_Board_LOOP_MAX	
	U_1LOOP_DETE_MAX 	= 0x100,
	U_1ExtgLOOP_DETE_MAX 	= 0x40,
	U_1ExtgLOOP_DeteLink_MAX 	= 200,
	U_1DETE_CHNL_MAX 	= 4,

	U_OneBoard_LOOP_MAX	= 0x01,
	U_OneBoard_DrtModu_MAX	= 0x08,
	U_OneBoard_ExtgModu_MAX	= 0x04,

	U_OneModLine_Drt_Dete_MAX	= 0x08,
	U_OneModLine_Extg_Dete_MAX	= 0x40,
	

	U_UNIT_PN_MAX 	= 0xFF //ALL
};
	
	
	
/*================= 私有函数声明 ====================================*/
#ifdef  __strDevice_C__
#endif  //__strDevice_C__

/*=================  ====================================*/
#if U_SYS_Test_strDevice == 1 
EX_strDevice void Test_Dev(void);
#endif // U_SYS_SoftSimulatState

/*================= 公有函数声明 - DEV 组成 ====================================*/
//EX_strDevice 

extern U8 BuildToDev_Machine(U8 machine, TDev_un *pDev);

extern U8 BuildToDev_Panel(U8 machine, U8 pnType, U8 pnSequ, TDev_un *pDev);
extern U8 BuildToDev_Me_Panel(U8 pnType, U8 pnSequ, TDev_un *pDev);

extern U8 BuildToDev_PnModu(U8 machine, U8 pnType, U8 pnSequ, U8 moduNum, TDev_un *pDev);
extern U8 BuildToDev_Me_PnModu(U8 pnType, U8 pnSequ, U8 moduNum, TDev_un *pDev);

extern U8 BuildToDev_PnMduLine(U8 machine, U8 pnType, U8 pnSequ, U8 moduNum, U8 pnModuLine, TDev_un *pDev);
extern U8 BuildToDev_Me_PnMduLine(U8 pnType, U8 pnSequ, U8 moduNum, U8 pnModuLine, TDev_un *pDev);

extern U8 BuildToDev_DeteMLA(U8 machine, U8 loop, U32 addr, TDev_un *pDev);
extern U8 BuildToDev_Me_DeteMLA(U8 loop, U32 addr, TDev_un *pDev);

extern U8 BuildToDev_DeteMLAC(U8 machine, U8 loop, U32 addr, U8 channel, TDev_un *pDev);
extern U8 BuildToDev_Me_DeteMLAC(U8 loop, U32 addr, U8 channel, TDev_un *pDev);

extern U8 BuildToDev_Power(U8 machine, U8 power, TDev_un *pDev);
extern U8 BuildToDev_Me_Power(U8 power, TDev_un *pDev);

extern U8 BuildToDev_PnFlash(U8 machine, U8 pnType, U8 pnSequ, 
							U8 flsItem, U8 mPart, TDev_un *pDev);
extern U8 BuildToDev_Me_Flash(U8 flsItem, U8 mPart, TDev_un *pDev); //本机本板

/*================= 公有函数声明 - 判断DEV ====================================*/
//EX_strDevice 
extern BOOL bDevOk(TDev_un *pDev); // 对比 DevSetInvalid();
extern BOOL bDevIsMachMe(TDev_un *pDev);
extern U8 JdgDevClass(TDev_un *pDev); // OUT:  emDevClass
extern BOOL bDeteHaveChannel(TDev_un *pDev);

extern U8 jdgDevItem_Legal(U8 mDevItem, U32 mChkItemNow); //只是判断是否超出字段范围。
extern U8 jdgDevItem_Dete_Legal(U8 loop, U32 addr);

/*================= 公有函数声明 - 计算总数字 ====================================*/
//EX_strDevice 
extern BOOL CacuDeteLoop_1toMax(TDev_un *pDev, U32 *pRtnLoop); //计算回路数 1~
extern BOOL CacuDrtLoop_1toMax(TDev_un *pDev, U32 *pRtnLoop); //计算多线回路数 1~
extern BOOL CacuExtgLoop_1toMax(TDev_un *pDev, U32 *pRtnLoop); //计算灭火回路数 1~

//计算现场部件数 0~12800
//回路  0~12800
extern BOOL CacuDevSequ_Dete_0toMax(TDev_un *pDev, U32 *pRtnSequ);
//计算多线现场部件数 0~
extern BOOL CacuDevSequ_Drt_0toMax(TDev_un *pDev, U32 *pRtnSequ);
//计算气灭现场部件数 0~
extern BOOL CacuDevSequ_Extg_0toMax(TDev_un *pDev, U32 *pRtnSequ);

//计算所有现场部件排号 0~; 回路—多线-气灭总排序。
extern BOOL CacuDevSequ_0toMax(TDev_un *pDev, U32 *pRtnSequ);


//通过总回路号，计算panel号和panel内的回路号。
extern void CacuDetePnSequAndBdLoop(U8 loop, 
							U8 *pRtnPnSequ, U8 *pRtnBdLoop
							);

/*================= 公有函数声明 - DEV 初始化 ====================================*/
//EX_strDevice 
extern void DevSetInvalid(TDev_un  *m_pDev); // 对比 bDevOk();
extern void DevSet_all_FF(TDev_un  *m_pDev);
extern void DevSet_all_00(TDev_un  *m_pDev);

extern void DevSet_SimAdr(U8 mIniVal, TDev_un  *m_pDev);
extern void DevSet_all_test1234567(U8 mIniVal, TDev_un  *m_pDev); //测试用
	
/*================= 公有函数声明 - DEV 操作 ====================================*/
//EX_strDevice 
extern BOOL bDevCompare(TDev_un  *pDev1, TDev_un  *pDev2);
extern BOOL bDevCompMask(U8 mDevItem, TDev_un  *pDev1, TDev_un  *pDev2);


extern void ComposeDev_fromBytes(U8 *pByte, TDev_un  *pRtnDev);
extern void ComposeBytes_fromDev(TDev_un  *pDev, U8 *pRtnByte);
extern U32 ComposeDWord_fromDev_NoMachine(TDev_un  *pDev);

/******************************************************************************
// END :
******************************************************************************/
#endif // __strDevice_H__

