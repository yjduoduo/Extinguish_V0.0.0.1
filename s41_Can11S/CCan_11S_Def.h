/*
*********************************************************************************************************
*                                                
*                                 ÈÎÎñ¶ÔÏó CCan_11S_Def
*
*                        (c) Copyright 2009-2016, ½¯Ñ©Ã·
*                              All Rights Reserved
*                                    Ver1.0
* File : CCan_11S_Def.H
* By   : ½¯Ñ©Ã·
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

/*================= ³£Êı ============================================*/
typedef enum{
	U_ModuRunTp_Auto = 1,
	U_ModuRunTp_Manu = 2,
	U_ModuRunTp_Remote = 3,
}emModuRunAuMaRemote;
	
// 0x80  Æô¶¯/·¢Éú
// 0x00  Í£Ö¹/³·Ïû
// 0x04  Æô¶¯ÑÓÊ±
typedef enum{
	U_ModuRunSta_Start = 0x80,
	U_ModuRunSta_Stop = 0,
	U_ModuRunSta_Delay = 0x04,
}emModuRunState;
	
// 0--Ì½²â
// 1--Áª¶¯
// 2--Éù¹â
// 3--¹ã²¥
typedef enum{
	U_DeteClass_Detector = 0,
	U_DeteClass_ModuOut = 1,
	U_DeteClass_HornStrobe = 2,
	U_DeteClass_ModuBroad = 3,
}emDeteCanClass;
	
// 0--ÎŞÈ±Ê§Ó¦´ğĞÅÏ¢
// 80H--ÓĞÎ´ÊÕµ½Ó¦´ğ
typedef enum{
	U_AckMissSta_Have = 0x80,
	U_AckMissSta_No = 0,
}emAckMissState;
	
// 0--ÎŞÑÓÊ±ĞÅÏ¢
// 80H--ÓĞÑÓÊ±ÇëÇó
typedef enum{
	U_ModuRunDelaySta_Have = 0x80,
	U_ModuRunDelaySta_No = 0,
}emModuRunDelayState;
	
// 0--Ì½²â¹ÊÕÏ
// 1--Áª¶¯¹ÊÕÏ
// 2--Éù¹â¹ÊÕÏ
// 3---ÎÛÈ¾¹ÊÕÏ
// 4---Ê§Ğ§¹ÊÕÏ
typedef enum{
	U_DeteFaultCls_Detector = 0,
	U_DeteFaultCls_ModuOut = 1,
	U_DeteFaultCls_HornStrobe = 2,
	U_DeteFaultCls_Polluted = 3,  // ÎÛÈ¾
	U_DeteFaultCls_BecomeInvalid = 4,
}emDeteFaultClass; // »ØÂ·ÏÖ³¡²¿¼ş±¨¹ÊÕÏ
	
// 0x81--Éù¹â
// 0x80--¹ã²¥
// 0x84--ÎŞÊäÈë

// D7--Éù¹â±êÖ¾
// D6--ÑÓÊ±Æô¶¯±êÖ¾

// D3~D0--Í¨µÀ±êÊ¶
typedef enum{
	U_DeteResponseCls_HornStrobe = 0x81,
	U_DeteResponseCls_Broad = 0x80,
	U_DeteResponseCls_NoAck = 0x84,
	
}emDeteResponseCls; // Éè±¸ÀàĞÍ
	
	
typedef enum{
	U_DeteAlarmCls_ManuModu = 0x80, // ÊÖ±¨£¿ 
	
}emDeteAlarmCls; // ±¨¾¯ÀàĞÍ
	
	
/*******************************************************************/
/******************       È«¾Ö³£Á¿¶¨Òåı     *********************/
/*******************************************************************/

#define  cRsv_11S          0	      //µ¥Ö¡×î´óµÄ·¢ËÍ×Ö½ÚÊı     

#define  c11S_MaxLpAddrNum           215  //»ØÂ·°å×î´óµ¥»ØÂ·×î´óµØÖ·Êı
#define  c11S_MaxDirPanLpNum         8	  //¶àÏßÅÌ×î´óµØÖ·Êı
#define  c11S_MaxBusAddrNum          50	  //×ÜÏßÅÌ×î´óµÄµØÖ·ÊıÁ¿	   
#define  c11S_MaxGasPanLpNum         4	  //Ãğ»ğÅÌ×î´óµÄµØÖ·ÊıÁ¿
 
#define  c11S_MaxLpPanLpNum          8	   //»ØÂ·°å×î´ó»ØÂ·Êı 
#define  c11S_MinDirLpMovNum         65	   //¶àÏßÅÌ»ØÂ·Æ«ÒÆ
#define  c11S_MinGasLpMovNum         85	   //Ãğ»ğÅÌ»ØÂ·Æ«ÒÆ

//°åÀàĞÍ´úÂë
#define  cPanDisType	  0
#define  cPanLoopType     1	       
#define  cPanDirType      2	        
#define  cPanBusType      3	       
#define  cPanGasType      4	       
#define  cPanOthType      5	  
#define  cMaxPanType      6  

//Òº¾§°å·¢ËÍµÄÃüÁî	¹ã²¥ÃüÁî
#define  c11s_BC_Reset	    1	//¸´Î»
#define  c11s_BC_Register	  2	//×Ô¶¯µÇ¼Ç
#define  c11s_BC_CheckSelf	3	//µÆ¼ì
#define  c11s_BC_Time       4	//¹ã²¥Ê±ÖÓ
#define  c11s_BC_ClrReg     5	//Çå³ıµÇ¼Ç
#define  c11s_BC_ClrPrg     6	//Çå³ı±à³Ì
#define  c11s_BC_EnPro      7	//¼ÆËã»ú±à³Ì
#define  c11s_BC_ClrBusPrg  9	//Çå³ı×ÜÏßÅÌ¶ÔÓ¦¹ØÏµ
#define  c11s_BC_EnAuto     0x0a	//¿ªÆô×Ô¶¯ÔÊĞí
#define  c11s_BC_SlAct      0x0c	//Éù¹â¶¯×÷Ö¸Ê¾ 
#define  c11s_BC_Board      0x0d	//×ÜÏß¹ã²¥ÉêÇëÏûÒô

#define  c11s_BC_FPAns      0x79  	//Ïû·À±Ã»Ø´ğ×´Ì¬
#define  c11s_BC_SysAns     0x78  	//ÏµÍ³Ó¦´ğ×´Ì¬
#define  c11s_BC_AuMa       0x70  	//ÊÖ×Ô¶¯×´Ì¬

 
//Òº¾§°å·¢ËÍµÄÃüÁî  µãµãÉèÖÃÃüÁî
#define  c11s_DS_SetInsul 	1   //µ¥¸öÆÁ±Î
#define  c11s_DS_ManuStar	  2	//ÊÖ¶¯Æô¶¯ÃüÁî 
#define  c11s_DS_ManuStop	  3	//ÊÖ¶¯Í£Ö¹ÃüÁî 
#define  c11s_DS_ClrInsul 	4   //µ¥¸ö½â³ıÆÁ±Î
#define  c11s_DS_SetReg 	  5   //µ¥¸öµØÖ·µÇ¼Ç
#define  c11s_DS_ClrReg 	  6   //µ¥¸ö½â³ıµÇ¼Ç
#define  c11s_DS_SetBusPro 	0x0a   //ÉèÖÃ×ÜÏßÅÌ¶ÔÓ¦¹ØÏµ

#define  c11s_DS_SetDetScope 	0x1d   //ÉèÖÃÌ½²âÆ÷ÁéÃô¶È
#define  c11s_DS_ChkDetScope 	0x1e   //²éÑ¯Ì½²âÆ÷ÁéÃô¶È

//Òº¾§°å·¢ËÍµÄÃüÁî  µãµã²éÑ¯ÃüÁî

#define  c11s_DCk_NdType 	0x09  //²éÑ¯»ØÂ·ÀàĞÍ×´Ì¬
#define  c11s_DCk_LpReg 	0x11  //²éÑ¯»ØÂ·µÇ¼Ç×´Ì¬
 
#define  c11s_DCk_Pro  	  0x13  //²éÑ¯Áª¶¯±à³Ì
#define  c11s_DCk_NdSta 	0x14  //²éÑ¯×´Ì¬ĞÅºÅ	
#define  c11s_DCk_NdCurve  0x15 //Ä£ÄâÁ¿²éÑ¯
#define  c11s_DCk_NdData 	 0x16  //²éÑ¯Êı¾İ
#define  c11s_DCk_NdScan 	 0x17  //»ØÂ·×İÀÀ

#define  c11s_DCk_LpPanleReg 	0x23  //²éÑ¯»ØÂ·°åµÇ¼Ç×´Ì¬
#define  c11s_CXCk_NdSta 	    0x24  //	È¡Ïû²éÑ¯×´Ì¬ĞÅºÅ	
#define  c11s_CXCk_NdCurve 	  0x25  //	È¡ÏûÄ£ÄâÁ¿²éÑ¯
#define  c11s_CXCk_NdData 	  0x26  //	È¡Ïû²éÑ¯Êı¾İ
#define  c11s_CXCk_NdScan 	  0x27  //	È¡Ïû»ØÂ·×İÀÀ


#define  c11s_DCk_DirDef 	 0x18  //²éÑ¯×¨ÏßÉèÖÃ
#define  c11s_DCk_BusPro    0x1A  //²éÑ¯×ÜÏßÅÌ¶ÔÓ¦¹ØÏµ

#define  c11s_DCk_SoftVer   0x2A   //²éÑ¯×ÜÏßÅÌ¶ÔÓ¦¹ØÏµ
#define  c11s_DS_GasAuto   0x2e   //ÉèÖÃÃğ»ğ×Ô¶¯ÔÊĞí
 

//Òº¾§°å×ª·¢ÆäËû°å¿¨ĞÅÏ¢
#define  c11s_WBI_Fire 	     0x30  //ÆäËû»úÆ÷»ğ¾¯
#define  c11s_WBI_Ans 	     0x31  //ÆäËû»úÆ÷Ó¦´ğ 
#define  c11s_WBI_ClrAns     0x32  //ÆäËû»úÆ÷Ó¦´ğ³·Ïú
#define  c11s_WBI_Fault 	   0x33  //ÆäËû»úÆ÷¹ÊÕÏ 
#define  c11s_WBI_ClrFault   0x34  //ÆäËû»úÆ÷¹ÊÕÏ»Ö¸´
#define  c11s_WBI_Stop       0x35  //ÆäËû»úÆ÷Í£Ö¹
#define  c11s_WBI_Star       0x36  //ÆäËû»úÆ÷Æô¶¯
#define  c11s_WBI_Delay      0x37  //ÆäËû»úÆ÷ÑÓÊ±

//Òº¾§°å·¢ËÍÊÖ×Ô¶¯×´Ì¬ 
#define  c11s_BI_AuMa       0x70  //¹ã²¥ÊÖ×Ô¶¯×´Ì¬	  
#define  c11s_BI_AuMaV      0x0c  //ÊÖ¶¯ÔÊĞí£¬×Ô¶¯ÔÊĞí

//Òº¾§°å×ª·¢ÎÄ¼ş
#define  c11s_FC_Pro        0x04  //ÏÂ·¢±à³ÌÎÄ¼ş
#define  c11s_FC_DirDef     0x05  //ÏÂ·¢¶àÏßÃğ»ğÉèÖÃ


//ÏÂ¼¶°å¿¨·¢ËÍµÄĞÅÏ¢
#define  c11s_DI_SofVer     0x7a  //Èí¼ş°æ±¾ĞÅÏ¢
#define  c11s_DI_MdDelay    0x7b  //Æô¶¯ÑÓÊ±ĞÅÏ¢
#define  c11s_DI_Delay      0x7c  //Æô¶¯ÑÓÊ±ĞÅÏ¢
#define  c11s_DI_AuMa       0x7d  //°å¿¨ÊÖ×Ô¶¯×´Ì¬ÉÏ±¨

//»ØÂ·°åĞÅÏ¢
#define  c11s_LBI_Fire       0x80  //»ğ¾¯ĞÅÏ¢
#define  c11s_LBI_Fault 	   0x81  //¹ÊÕÏ 
#define  c11s_LBI_ClrFault   0x82  //¹ÊÕÏ»Ö¸´
#define  c11s_LBI_AuStar     0x83  //Æô¶¯
#define  c11s_LBI_AuStop     0x84  //Í£Ö¹	
#define  c11s_LBI_Ans 	     0x85  //Ó¦´ğ 
#define  c11s_LBI_ClrAns     0x86  //Ó¦´ğ³·Ïú
#define  c11s_LBI_LpErr 	   0x87  //»ØÂ·¹ÊÕÏ
#define  c11s_LBI_ClrLpErr   0x88  //»ØÂ·¹ÊÕÏ³·Ïú
#define  c11s_LBI_LostAns    0x89  //Ó¦´ğÈ±Ê§

#define  c11s_LBI_MaStar     0x90  //ÊÖ¶¯Æô¶¯
#define  c11s_LBI_MaStop     0x91  //ÊÖ¶¯Í£Ö¹

#define  c11s_LBI_ClrInsul     0x97  //½ÚµãÒÑ¾­µÇ¼Ç
#define  c11s_LBI_HasInsul     0x98  //½ÚµãÒÑ¾­µÇ¼Ç

#define  c11s_LBI_HasReg     0x99  //½ÚµãÒÑ¾­µÇ¼Ç
#define  c11s_LBI_NdFault    0x9c  //µØÖ·ÓĞ¹ÊÕÏ     ·´À¡ĞÅÏ¢ÏÔÊ¾

#define  c11s_LBI_AnNdSta    0xA1  //»Ø´ğ½Úµã×´Ì¬µçÁ÷ 
#define  c11s_LBI_AnNdCur    0xA0  //»Ø´ğ½Úµã×´Ì¬ÀàĞÍ¡¢Êı¾İ²éÑ¯¡¢Ä£ÄâÁ¿
	
#define  c11s_FI_LpReg      0x02 //»ØÂ·µÇ¼ÇÎÄ¼ş 
#define  c11s_FI_Pro        0x05 //Áª¶¯±à³ÌÎÄ¼ş
#define  c11s_FI_LpScan     0x08 //»ØÂ·ä¯ÀÀÎÄ¼ş 
#define  c11s_FI_DirDef     0x09 //¶àÏßÅÌ»ØÂ·µÇ¼ÇÎÄ¼ş
#define  c11s_FI_LpPanReg   0x0b //»ØÂ·°åµÇ¼ÇÎÄ¼ş 



//CD8  °åĞÅÏ¢
#define  c11s_DirFlg        0xf2 //¶àÏßÅÌ±êÖ¾Î»

#define  c11s_DDI_MaStar     0x51  //ÊÖ¶¯Æô¶¯
#define  c11s_DDI_MaStop     0x52  //ÊÖ¶¯Í£Ö¹ 
#define  c11s_DDI_Ans 	     0x53  //Ó¦´ğ 
#define  c11s_DDI_ClrAns     0x54  //Ó¦´ğ³·Ïú
#define  c11s_DDI_AuStar     0x55  //Æô¶¯
#define  c11s_DDI_AuStop     0x56  //Í£Ö¹
#define  c11s_DDI_Delay      0x57  //Æô¶¯ÑÓÊ±
#define  c11s_DDI_LostAns    0x58  //Ó¦´ğÈ±Ê§
#define  c11s_DDI_Fault 	   0x59  //»ØÂ·¹ÊÕÏ
#define  c11s_DDI_ClrFault   0x5A  //»ØÂ·¹ÊÕÏ³·Ïú

//CK50  °åĞÅÏ¢
#define  c11s_DBI_MaStar     0x02  //ÊÖ¶¯Æô¶¯
#define  c11s_DBI_MaStop     0x03  //ÊÖ¶¯Í£Ö¹ 
#define  c11s_DBI_AnsPro     0x9d  //»Ø´ğ¶ÔÓ¦¹ØÏµ
 

//CE4  °åĞÅÏ¢
#define  c11s_GasFlg            0xfA  //Ãğ»ğÅÌ±êÖ¾Î»

#define  c11s_GDI_Faule         0x01 //¹ÊÕÏ
#define  c11s_GDI_FauleClr      0x02 //¹ÊÕÏ»Ö¸´
#define  c11s_GDI_OpAns         0x03 //ÅçÈ÷»Ø´ğ
#define  c11s_GDI_OpAnsClr      0x04 //ÅçÈ÷»Ø´ğ³·Ïú 
#define  c11s_GDI_SLStar        0x05 //Éù¹âÆô¶¯
#define  c11s_GDI_SLStop        0x06 //Éù¹âÍ£Ö¹ 
#define  c11s_GDI_DvStar        0x07 //Ïà¹ØÉè±¸Æô¶¯
#define  c11s_GDI_DvStop        0x08 //Ïà¹ØÉè±¸Í£Ö¹
#define  c11s_GDI_ZnStar        0x09 //·À»ğÇøÆô¶¯
#define  c11s_GDI_ZnStop        0x0A //·À»ğÇøÍ£Ö¹
#define  c11s_GDI_OpStar        0x0B //ÅçÈ÷Æô¶¯  
#define  c11s_GDI_Contrl        0x0C //¿ØÖÆ·½Ê½

#define  c11s_GAM_Auto          0x01 //×Ô¶¯·½Ê½
#define  c11s_GAM_Manu          0x02 //ÊÖ¶¯·½Ê½
#define  c11s_GAM_Extn          0x03 //Ô¶³Ì·½Ê½ 

//Ck50  ×ÜÏßÅÌĞÅÏ¢
#define  c11s_BDC_MaStar        0x02  //ÊÖ¶¯Æô¶¯ÃüÁî
#define  c11s_BDC_MaStop        0x03  //ÊÖ¶¯Í£Ö¹ÃüÁî
#define  c11s_BDI_BusPro        0x9D  //·´À¡×ÜÏßÅÌ°´¼ü¶ÔÓ¦¹ØÏµ 

//ÍâCAN ĞÅÏ¢
#define  cw11s_BC_Reset	      1	     //¸´Î»
#define  cw11s_BC_MaStar      0x02  //ÊÖ¶¯Æô¶¯ÃüÁî
#define  cw11s_BC_MaStop	    0x03  //ÊÖ¶¯Í£Ö¹ÃüÁî
#define  cw11s_BC_AutoOn	    0x04  //×Ô¶¯ÔÊĞí¿ªÆô
#define  cw11s_BC_Insul       0x05   //ÆÁ±Î
#define  cw11s_BC_ClrInsul	  0x06   //½â³ıÆÁ±Î

#define  cw11s_BC_CkLed        7	    //¿ç»úµÆ¼ì 
#define  cw11s_BC_AnsCkLed     0x08   //·¢ËÍ¿ç»ú×Ô¼ìÃüÁî
#define  cw11s_BC_AutoReg      0x09   //×Ô¶¯µÇ¼Ç¹ã²¥

#define  cw11s_BC_SLAct        0x0c   //Éù¹âÃüÁî
#define  cw11s_BC_TimeYMD      0x0d   //ÍâCAN¹ã²¥Ê±¼ä  ÄêÔÂÈÕ
#define  cw11s_BC_TimeHMS      0x0e   //ÍâCAN¹ã²¥Ê±¼ä  Ê±·ÖÃë

#define  cw11s_BC_CkGasAuto    0x0f   //ÍâCAN²éÑ¯Ãğ»ğÅÌ×Ô¶¯×´Ì¬ 
#define  cw11s_BC_SetGasAuto   0x2e   //ÍâCAN²éÑ¯Ãğ»ğÅÌ×Ô¶¯×´Ì¬ 
#define  cw11s_BC_AnsGasAuto   0x2f   //»Ø´ğÍâCAN²éÑ¯Ãğ»ğÅÌ×Ô¶¯×´Ì¬½á¹û 1~8 
//·ÀÖ¹¶Ô11s/sc Ôì³ÉÓ°Ïì
#define  cw11s_BC_AnsGasAuto1  0x30   //»Ø´ğÍâCAN²éÑ¯Ãğ»ğÅÌ×Ô¶¯×´Ì¬½á¹û 9~14


#define  cw11s_BI_PanSta	    0x70  //ÅÌ×´Ì¬
#define  cw11s_BI_MPowSta     0x71  //Ö÷µç×´Ì¬
#define  cw11s_BI_BPowSta	    0x72  //±¸µç×´Ì¬
#define  cw11s_BI_24VPowSta	  0x74  //24VµçÑ¹¼ì²é

#define  cw11s_BI_MachDelay       0x7b  //·¢ËÍ±¾»úÑÓÊ±ĞÅÏ¢
#define  cw11s_BI_MachLstAns      0x7f  //·¢ËÍ±¾»úÓ¦´ğÈ±Ê§
#define  cw11s_BI_MachLsAns       cw11s_BI_MachLstAns
#define  cw11s_BI_MaunAlarm       0x8b//·¢ËÍ±¾»úĞéÄâ»ğ¾¯ 


#define  c11s_Fault_Ocu       0x80  //¹ÊÕÏ·¢Éú
#define  c11s_Fault_Clr       0x90  //¹ÊÕÏ³·Ïú   
/*******************************************************************/
/******************       Êı¾İ½á¹¹¶¨Òåı     *********************/
/*******************************************************************/


/*******************************************************************/
/****************     ¹«ÓĞ³ÉÔ±±äÁ¿,º¯Êı¼°³£Á¿     ******************/
/*******************************************************************/
//public:


/*******************************************************************/
/********************* Ë½ÓĞ³ÉÔ±±äÁ¿,º¯Êı¼°³£Á¿    *******************/
/*******************************************************************/
//Private:
#ifdef  CCan_11S_Def_C   




#endif
#endif
