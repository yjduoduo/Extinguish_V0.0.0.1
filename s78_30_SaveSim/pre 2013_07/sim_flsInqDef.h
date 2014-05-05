#ifndef __sim_flsInqDef_H__
#define __sim_flsInqDef_H__
/******************************************************************************
* @file    sim_flsInqDef.h
* @author  yx
* @version V1.0
* @date    2013-01-04
* @brief   
* 
#include  "sim_flsInqDef.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

/*=================   ============================================*/

/*=================   ============================================*/

//----------------------------------------------------------------------
	#if U_SYS_Test_Flash_InqPoint == 1
		#if U_SYS_Test_Flash_InqPoint_SimX == 1
			#define U_InqPoint_FlsItem_SectMAX  (0x20) //
		#elif U_SYS_Test_Flash_InqPoint_SimX == 2
			#define U_InqPoint_FlsItem_SectMAX  3
		#endif // U_SYS_Test_Flash_InqPoint_SimX
		
		#define U_SimFlsPoit_FlsItmCls    9 //(U_FlsSave_Sim)
		#define U_SimFlsPoit_1SectorBytes  0x100 //(U_FLASH_1_SECTOR)
		#define U_SimFlsPoit_1ItemBytes  (0x08) //根据测试的内容，不同。
		
		#define U_SimFlsPoit_AdrS  0x1000

	/*
	sim1, V1.2, 2013.7.7 
	1. U_InqPoint_FlsItem_SectMAX   U_SimFlsPoit_1SectorBytes U_SimFlsPoit_1ItemBytes  totalItem
			0x20 				0x1000 					0x10 
			0x04 				0x1000 					0x10 
			0x04 				0x100 					0x10 
			0x04 				0x100 					0x08 
			0x04 				0x100 					0x04 


	sim2, V1.2, 2013.7.7 
	1. U_InqPoint_FlsItem_SectMAX   U_SimFlsPoit_1SectorBytes U_SimFlsPoit_1ItemBytes  totalItem
			2 					0x1000 					0x10 		0X200
			2 					0x100 					0x10 		0X20
			2 					0x100 					0x08 		0X40
			3 					0x100 					0x08 		0x60
			3 					0x1000 					0x08 		0x600
			3 					0x1000 					0x10 		0x300
			3 					0x1000 					0x20 		0x180

	*/

	#else
	#endif // U_SYS_Test_Flash_InqPoint

//----------------------------------------------------------------------





/******************************************************************************
// END :
******************************************************************************/
#endif // __sim_flsInqDef_H__

