#ifndef __lcdCst_PgString_H__
#define __lcdCst_PgString_H__
/******************************************************************************
* @file    lcdCst_PgString.h
* @author  yx
* @version V1.0
* @date    2012-01-05
* @brief   页面用到的字符串
* 
#include  "lcdCst_PgString.h"
******************************************************************************/

#include  "prjCompileCon.h"
/*================= extern ============================================*/
// #define EX_lcdCst_PgString extern 

/*================= 常数 ============================================*/
//#define 
/*================= 结构体定义 ======================================*/
typedef struct{  //U_Language_MAX
	const char *pCn;
	const char *pEn;
	const char *pComplex;
}TCstChar_st;


/*================= 字符串定义 ======================================*/

extern const TCstChar_st  cstChar_Default;

extern const TCstChar_st  cstChar_ExtgMachineIni;
extern const TCstChar_st  cstChar_RunUsual;
extern const TCstChar_st  cstChar_Auto;
extern const TCstChar_st  cstChar_Manu;
extern const TCstChar_st  cstChar_Forbid;
extern const TCstChar_st  cstChar_Allow;

extern const TCstChar_st  cstChar_PageDefError;
extern const TCstChar_st  cstChar_PageNoCode;

extern const TCstChar_st  cstChar_FirAlarm; //首警:
extern const TCstChar_st  cstChar_Machine;
extern const TCstChar_st  cstChar_MachinMe;

extern const TCstChar_st  cstChar_Loop;
extern const TCstChar_st  cstChar_Addr;
extern const TCstChar_st  cstChar_Channel;

extern const TCstChar_st  cstChar_Pn_Loop;
extern const TCstChar_st  cstChar_Pn_Opea;
extern const TCstChar_st  cstChar_Pn_Drt;
extern const TCstChar_st  cstChar_Pn_Bus;
extern const TCstChar_st  cstChar_Pn_Extg;
extern const TCstChar_st  cstChar_Pn_Broad;
extern const TCstChar_st  cstChar_Pn_Power;
extern const TCstChar_st  cstChar_Pn_Other;

extern const TCstChar_st  cstChar_Modu_Loop;
extern const TCstChar_st  cstChar_Modu_Pad;

extern const TCstChar_st  cstChar_Total;
extern const TCstChar_st  cstChar_Delay;
extern const TCstChar_st  cstChar_Second;
extern const TCstChar_st  cstChar_StatusColon;


extern const TCstChar_st  cstChar_DongZuo;
extern const TCstChar_st  cstChar_Extinguish;


extern const TCstChar_st  cstChar_Action;
extern const TCstChar_st  cstChar_Stop;
extern const TCstChar_st  cstChar_Ack;
extern const TCstChar_st  cstChar_AckRstr;
extern const TCstChar_st  cstChar_AckMiss;

extern const TCstChar_st  cstChar_Run;
extern const TCstChar_st  cstChar_pwrMain;
extern const TCstChar_st  cstChar_pwrBty;



/*================= 公有函数声明 ====================================*/
//EX_lcdCst_PgString 



/******************************************************************************
// END :
******************************************************************************/
#endif // __lcdCst_PgString_H__

