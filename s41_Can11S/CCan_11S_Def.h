/*
*********************************************************************************************************
*                                                
*                                 任务对象 CCan_11S_Def
*
*                        (c) Copyright 2009-2016, 蒋雪梅
*                              All Rights Reserved
*                                    Ver1.0
* File : CCan_11S_Def.H
* By   : 蒋雪梅
*
*********************************************************************************************************
*/
//#include  "CCan_11S_Def.h"

#ifndef CCan_11S_Def_H
#define CCan_11S_Def_H


//#include <includes.h>	
 
 

#ifdef  CCan_11S_Def_C
#define EX_CCan_11S_Def
#else
#define EX_CCan_11S_Def extern 
#endif

/*================= 常数 ============================================*/
typedef enum{
	U_ModuRunTp_Auto = 1,
	U_ModuRunTp_Manu = 2,
	U_ModuRunTp_Remote = 3,
}emModuRunAuMaRemote;
	
// 0x80  启动/发生
// 0x00  停止/撤消
// 0x04  启动延时
typedef enum{
	U_ModuRunSta_Start = 0x80,
	U_ModuRunSta_Stop = 0,
	U_ModuRunSta_Delay = 0x04,
}emModuRunState;
	
// 0--探测
// 1--联动
// 2--声光
// 3--广播
typedef enum{
	U_DeteClass_Detector = 0,
	U_DeteClass_ModuOut = 1,
	U_DeteClass_HornStrobe = 2,
	U_DeteClass_ModuBroad = 3,
}emDeteCanClass;
	
// 0--无缺失应答信息
// 80H--有未收到应答
typedef enum{
	U_AckMissSta_Have = 0x80,
	U_AckMissSta_No = 0,
}emAckMissState;
	
// 0--无延时信息
// 80H--有延时请求
typedef enum{
	U_ModuRunDelaySta_Have = 0x80,
	U_ModuRunDelaySta_No = 0,
}emModuRunDelayState;
	
// 0--探测故障
// 1--联动故障
// 2--声光故障
// 3---污染故障
// 4---失效故障
typedef enum{
	U_DeteFaultCls_Detector = 0,
	U_DeteFaultCls_ModuOut = 1,
	U_DeteFaultCls_HornStrobe = 2,
	U_DeteFaultCls_Polluted = 3,  // 污染
	U_DeteFaultCls_BecomeInvalid = 4,
}emDeteFaultClass; // 回路现场部件报故障
	
// 0x81--声光
// 0x80--广播
// 0x84--无输入

// D7--声光标志
// D6--延时启动标志

// D3~D0--通道标识
typedef enum{
	U_DeteResponseCls_HornStrobe = 0x81,
	U_DeteResponseCls_Broad = 0x80,
	U_DeteResponseCls_NoAck = 0x84,
	
}emDeteResponseCls; // 设备类型
	
	
typedef enum{
	U_DeteAlarmCls_ManuModu = 0x80, // 手报？ 
	
}emDeteAlarmCls; // 报警类型
	
	
/*******************************************************************/
/******************       全局常量定义�     *********************/
/*******************************************************************/

#define  cRsv_11S          0	      //单帧最大的发送字节数     

#define  c11S_MaxLpAddrNum           215  //回路板最大单回路最大地址数
#define  c11S_MaxDirPanLpNum         8	  //多线盘最大地址数
#define  c11S_MaxBusAddrNum          50	  //总线盘最大的地址数量	   
#define  c11S_MaxGasPanLpNum         4	  //灭火盘最大的地址数量
 
#define  c11S_MaxLpPanLpNum          8	   //回路板最大回路数 
#define  c11S_MinDirLpMovNum         65	   //多线盘回路偏移
#define  c11S_MinGasLpMovNum         85	   //灭火盘回路偏移

//板类型代码
#define  cPanDisType	  0
#define  cPanLoopType     1	       
#define  cPanDirType      2	        
#define  cPanBusType      3	       
#define  cPanGasType      4	       
#define  cPanOthType      5	  
#define  cMaxPanType      6  

//液晶板发送的命令	广播命令
#define  c11s_BC_Reset	    1	//复位
#define  c11s_BC_Register	  2	//自动登记
#define  c11s_BC_CheckSelf	3	//灯检
#define  c11s_BC_Time       4	//广播时钟
#define  c11s_BC_ClrReg     5	//清除登记
#define  c11s_BC_ClrPrg     6	//清除编程
#define  c11s_BC_EnPro      7	//计算机编程
#define  c11s_BC_ClrBusPrg  9	//清除总线盘对应关系
#define  c11s_BC_EnAuto     0x0a	//开启自动允许
#define  c11s_BC_SlAct      0x0c	//声光动作指示 
#define  c11s_BC_Board      0x0d	//总线广播申请消音

#define  c11s_BC_FPAns      0x79  	//消防泵回答状态
#define  c11s_BC_SysAns     0x78  	//系统应答状态
#define  c11s_BC_AuMa       0x70  	//手自动状态

 
//液晶板发送的命令  点点设置命令
#define  c11s_DS_SetInsul 	1   //单个屏蔽
#define  c11s_DS_ManuStar	  2	//手动启动命令 
#define  c11s_DS_ManuStop	  3	//手动停止命令 
#define  c11s_DS_ClrInsul 	4   //单个解除屏蔽
#define  c11s_DS_SetReg 	  5   //单个地址登记
#define  c11s_DS_ClrReg 	  6   //单个解除登记
#define  c11s_DS_SetBusPro 	0x0a   //设置总线盘对应关系

#define  c11s_DS_SetDetScope 	0x1d   //设置探测器灵敏度
#define  c11s_DS_ChkDetScope 	0x1e   //查询探测器灵敏度

//液晶板发送的命令  点点查询命令

#define  c11s_DCk_NdType 	0x09  //查询回路类型状态
#define  c11s_DCk_LpReg 	0x11  //查询回路登记状态
 
#define  c11s_DCk_Pro  	  0x13  //查询联动编程
#define  c11s_DCk_NdSta 	0x14  //查询状态信号	
#define  c11s_DCk_NdCurve  0x15 //模拟量查询
#define  c11s_DCk_NdData 	 0x16  //查询数据
#define  c11s_DCk_NdScan 	 0x17  //回路纵览

#define  c11s_DCk_LpPanleReg 	0x23  //查询回路板登记状态
#define  c11s_CXCk_NdSta 	    0x24  //	取消查询状态信号	
#define  c11s_CXCk_NdCurve 	  0x25  //	取消模拟量查询
#define  c11s_CXCk_NdData 	  0x26  //	取消查询数据
#define  c11s_CXCk_NdScan 	  0x27  //	取消回路纵览


#define  c11s_DCk_DirDef 	 0x18  //查询专线设置
#define  c11s_DCk_BusPro    0x1A  //查询总线盘对应关系

#define  c11s_DCk_SoftVer   0x2A   //查询总线盘对应关系
#define  c11s_DS_GasAuto   0x2e   //设置灭火自动允许
 

//液晶板转发其他板卡信息
#define  c11s_WBI_Fire 	     0x30  //其他机器火警
#define  c11s_WBI_Ans 	     0x31  //其他机器应答 
#define  c11s_WBI_ClrAns     0x32  //其他机器应答撤销
#define  c11s_WBI_Fault 	   0x33  //其他机器故障 
#define  c11s_WBI_ClrFault   0x34  //其他机器故障恢复
#define  c11s_WBI_Stop       0x35  //其他机器停止
#define  c11s_WBI_Star       0x36  //其他机器启动
#define  c11s_WBI_Delay      0x37  //其他机器延时

//液晶板发送手自动状态 
#define  c11s_BI_AuMa       0x70  //广播手自动状态	  
#define  c11s_BI_AuMaV      0x0c  //手动允许，自动允许

//液晶板转发文件
#define  c11s_FC_Pro        0x04  //下发编程文件
#define  c11s_FC_DirDef     0x05  //下发多线灭火设置


//下级板卡发送的信息
#define  c11s_DI_SofVer     0x7a  //软件版本信息
#define  c11s_DI_MdDelay    0x7b  //启动延时信息
#define  c11s_DI_Delay      0x7c  //启动延时信息
#define  c11s_DI_AuMa       0x7d  //板卡手自动状态上报

//回路板信息
#define  c11s_LBI_Fire       0x80  //火警信息
#define  c11s_LBI_Fault 	   0x81  //故障 
#define  c11s_LBI_ClrFault   0x82  //故障恢复
#define  c11s_LBI_AuStar     0x83  //启动
#define  c11s_LBI_AuStop     0x84  //停止	
#define  c11s_LBI_Ans 	     0x85  //应答 
#define  c11s_LBI_ClrAns     0x86  //应答撤销
#define  c11s_LBI_LpErr 	   0x87  //回路故障
#define  c11s_LBI_ClrLpErr   0x88  //回路故障撤销
#define  c11s_LBI_LostAns    0x89  //应答缺失

#define  c11s_LBI_MaStar     0x90  //手动启动
#define  c11s_LBI_MaStop     0x91  //手动停止

#define  c11s_LBI_ClrInsul     0x97  //节点已经登记
#define  c11s_LBI_HasInsul     0x98  //节点已经登记

#define  c11s_LBI_HasReg     0x99  //节点已经登记
#define  c11s_LBI_NdFault    0x9c  //地址有故障     反馈信息显示

#define  c11s_LBI_AnNdSta    0xA1  //回答节点状态电流 
#define  c11s_LBI_AnNdCur    0xA0  //回答节点状态类型、数据查询、模拟量
	
#define  c11s_FI_LpReg      0x02 //回路登记文件 
#define  c11s_FI_Pro        0x05 //联动编程文件
#define  c11s_FI_LpScan     0x08 //回路浏览文件 
#define  c11s_FI_DirDef     0x09 //多线盘回路登记文件
#define  c11s_FI_LpPanReg   0x0b //回路板登记文件 



//CD8  板信息
#define  c11s_DirFlg        0xf2 //多线盘标志位

#define  c11s_DDI_MaStar     0x51  //手动启动
#define  c11s_DDI_MaStop     0x52  //手动停止 
#define  c11s_DDI_Ans 	     0x53  //应答 
#define  c11s_DDI_ClrAns     0x54  //应答撤销
#define  c11s_DDI_AuStar     0x55  //启动
#define  c11s_DDI_AuStop     0x56  //停止
#define  c11s_DDI_Delay      0x57  //启动延时
#define  c11s_DDI_LostAns    0x58  //应答缺失
#define  c11s_DDI_Fault 	   0x59  //回路故障
#define  c11s_DDI_ClrFault   0x5A  //回路故障撤销

//CK50  板信息
#define  c11s_DBI_MaStar     0x02  //手动启动
#define  c11s_DBI_MaStop     0x03  //手动停止 
#define  c11s_DBI_AnsPro     0x9d  //回答对应关系
 

//CE4  板信息
#define  c11s_GasFlg            0xfA  //灭火盘标志位

#define  c11s_GDI_Faule         0x01 //故障
#define  c11s_GDI_FauleClr      0x02 //故障恢复
#define  c11s_GDI_OpAns         0x03 //喷洒回答
#define  c11s_GDI_OpAnsClr      0x04 //喷洒回答撤销 
#define  c11s_GDI_SLStar        0x05 //声光启动
#define  c11s_GDI_SLStop        0x06 //声光停止 
#define  c11s_GDI_DvStar        0x07 //相关设备启动
#define  c11s_GDI_DvStop        0x08 //相关设备停止
#define  c11s_GDI_ZnStar        0x09 //防火区启动
#define  c11s_GDI_ZnStop        0x0A //防火区停止
#define  c11s_GDI_OpStar        0x0B //喷洒启动  
#define  c11s_GDI_Contrl        0x0C //控制方式

#define  c11s_GAM_Auto          0x01 //自动方式
#define  c11s_GAM_Manu          0x02 //手动方式
#define  c11s_GAM_Extn          0x03 //远程方式 

//Ck50  总线盘信息
#define  c11s_BDC_MaStar        0x02  //手动启动命令
#define  c11s_BDC_MaStop        0x03  //手动停止命令
#define  c11s_BDI_BusPro        0x9D  //反馈总线盘按键对应关系 

//外CAN 信息
#define  cw11s_BC_Reset	      1	     //复位
#define  cw11s_BC_MaStar      0x02  //手动启动命令
#define  cw11s_BC_MaStop	    0x03  //手动停止命令
#define  cw11s_BC_AutoOn	    0x04  //自动允许开启
#define  cw11s_BC_Insul       0x05   //屏蔽
#define  cw11s_BC_ClrInsul	  0x06   //解除屏蔽

#define  cw11s_BC_CkLed        7	    //跨机灯检 
#define  cw11s_BC_AnsCkLed     0x08   //发送跨机自检命令
#define  cw11s_BC_AutoReg      0x09   //自动登记广播

#define  cw11s_BC_SLAct        0x0c   //声光命令
#define  cw11s_BC_TimeYMD      0x0d   //外CAN广播时间  年月日
#define  cw11s_BC_TimeHMS      0x0e   //外CAN广播时间  时分秒

#define  cw11s_BC_CkGasAuto    0x0f   //外CAN查询灭火盘自动状态 
#define  cw11s_BC_SetGasAuto   0x2e   //外CAN查询灭火盘自动状态 
#define  cw11s_BC_AnsGasAuto   0x2f   //回答外CAN查询灭火盘自动状态结果 1~8 
//防止对11s/sc 造成影响
#define  cw11s_BC_AnsGasAuto1  0x30   //回答外CAN查询灭火盘自动状态结果 9~14


#define  cw11s_BI_PanSta	    0x70  //盘状态
#define  cw11s_BI_MPowSta     0x71  //主电状态
#define  cw11s_BI_BPowSta	    0x72  //备电状态
#define  cw11s_BI_24VPowSta	  0x74  //24V电压检查

#define  cw11s_BI_MachDelay       0x7b  //发送本机延时信息
#define  cw11s_BI_MachLstAns      0x7f  //发送本机应答缺失
#define  cw11s_BI_MachLsAns       cw11s_BI_MachLstAns
#define  cw11s_BI_MaunAlarm       0x8b//发送本机虚拟火警 


#define  c11s_Fault_Ocu       0x80  //故障发生
#define  c11s_Fault_Clr       0x90  //故障撤销   
/*******************************************************************/
/******************       数据结构定义�     *********************/
/*******************************************************************/


/*******************************************************************/
/****************     公有成员变量,函数及常量     ******************/
/*******************************************************************/
//public:


/*******************************************************************/
/********************* 私有成员变量,函数及常量    *******************/
/*******************************************************************/
//Private:
#ifdef  CCan_11S_Def_C   




#endif
#endif
