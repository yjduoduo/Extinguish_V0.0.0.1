/*****************************************************************************
*author:魏新建
*time  :2013年 9.22~10月22日
*****************************************************************************/
#ifndef LCDPG_INITT_H
#define LCDPG_INITT_H
#define __KeyCall_Pg
#define __KeyCall_Pg_EX
#include "lcdPg_KeyCall.h"


#ifdef __KeyCall_INITT_EX
#define KEYCALL_INITT_EX extern
#else
#define KEYCALL_INITT_EX
#endif




extern key_callbackfun *pgCall;
/*****************************************************************************
*FUNC:各种页面初始化函数，由lcdPg_Page.c中直接调用
*****************************************************************************/

KEYCALL_INITT_EX void p010_initpgentry(void);//手动启停设备
KEYCALL_INITT_EX void p011_initpgentry(void);// 帮助
KEYCALL_INITT_EX void p013_initpgentry(void);//时间设置
KEYCALL_INITT_EX void p016_initpgentry(void);//自动登记
KEYCALL_INITT_EX void p017_initpgentry(void);//手动登记
KEYCALL_INITT_EX void p018_initpgentry(void);//手动屏蔽
KEYCALL_INITT_EX void p060_initpgentry(void);//回路浏览

KEYCALL_INITT_EX void p030_initpgentry(void);//灭火区设置
KEYCALL_INITT_EX void p037_initpgentry(void);//语言选择
KEYCALL_INITT_EX void p038_initpgentry(void);//调试模式
KEYCALL_INITT_EX void p041_initpgentry(void);//屏蔽信息
KEYCALL_INITT_EX void p040_initpgentry(void);//故障信息
KEYCALL_INITT_EX void p044_initpgentry(void);//查询汉字注释
KEYCALL_INITT_EX void p039_initpgentry(void);//查询调试模式
KEYCALL_INITT_EX void p058_initpgentry(void);//查询总线登记地址
KEYCALL_INITT_EX void p042_initpgentry(void);
KEYCALL_INITT_EX void p047_initpgentry(void);
KEYCALL_INITT_EX void p048_initpgentry(void);
KEYCALL_INITT_EX void p049_initpgentry(void);
KEYCALL_INITT_EX void p024_initpgentry(void);
KEYCALL_INITT_EX void p027_initpgentry(void);
KEYCALL_INITT_EX void p015_initpgentry(void);
KEYCALL_INITT_EX void p019_initpgentry(void);
KEYCALL_INITT_EX void p020_initpgentry(void);
KEYCALL_INITT_EX void p028_initpgentry(void);
KEYCALL_INITT_EX void p080_initpgentry(void);
KEYCALL_INITT_EX void p077_initpgentry(void);
KEYCALL_INITT_EX void p078_initpgentry(void);
KEYCALL_INITT_EX void p081_initpgentry(void);
KEYCALL_INITT_EX void p083_initpgentry(void);
KEYCALL_INITT_EX void p084_initpgentry(void);
KEYCALL_INITT_EX void p061_initpgentry(void);// 显示 模拟量曲线
KEYCALL_INITT_EX void p062_initpgentry(void);
KEYCALL_INITT_EX void p063_initpgentry(void);
KEYCALL_INITT_EX void p064_initpgentry(void);
KEYCALL_INITT_EX void p065_initpgentry(void);
KEYCALL_INITT_EX void p067_initpgentry(void);
KEYCALL_INITT_EX void p072_initpgentry(void);
KEYCALL_INITT_EX void p073_initpgentry(void);
KEYCALL_INITT_EX void p059_initpgentry(void);
KEYCALL_INITT_EX void p052_initpgentry(void);
KEYCALL_INITT_EX void p053_initpgentry(void);
KEYCALL_INITT_EX void p054_initpgentry(void);
KEYCALL_INITT_EX void p055_initpgentry(void);
KEYCALL_INITT_EX void p056_initpgentry(void);
KEYCALL_INITT_EX void p057_initpgentry(void);
#endif // LCDPG_INITT_H
