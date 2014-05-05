#ifndef __CanBufLib_ReDef_H__
#define __CanBufLib_ReDef_H__
/******************************************************************************
* @file    CanBufLib_ReDef.h
* @author  yx
* @version V1.0
* @date    2013-07-23
* @brief   
* 
#include  "CanBufLib_ReDef.h"
******************************************************************************/
//

/*================= sysDef.h ============================================*/

#define U_MACHINE_MAX		0x30 //
#define U_PANEL_TOTAL_SEQU_MAX      250

/*================= 常数 ============================================*/

enum emCanLogicId_ICanECan{  // uint8 can_id
	U_iCAN_ID = 0, // CAN0 不对应硬件的
	U_eCAN_ID = 1, // CAN1
};
#define U_CAN_ID_MAX  2

#define U_CAN_ID_Default  U_iCAN_ID

#define bCanHdIdValid(_canId_)  (_canId_ < U_CAN_ID_MAX)

/******************************************************************************
// END :
******************************************************************************/
#endif // __CanBufLib_ReDef_H__

