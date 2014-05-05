#ifndef __CanBufLib_strFileProp_H__
#define __CanBufLib_strFileProp_H__
/******************************************************************************
* @file    CanBufLib_strFileProp.h
* @author  yx
* @version V1.0
* @date    2013-07-24
* @brief   �ļ�֡��can��id��ı�־.
* 
#include  "CanBufLib_strFileProp.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

/*================= ���� ============================================*/
//#define 
/*================= �ṹ�嶨�� ======================================*/

// ÿ֡���еģ���Ψһ��ʶ��ͬ���ļ�
typedef struct{  
	
		U8 src;  	//Դ��ַ
		U8 dest; 	//Ŀ�ĵ�ַ
		U8 frmId;	//canЭ�������Ϣid.
		//U8 taskId;  // �շ����ã����ϡ�
}TCanFile_sId; 


/*================= �ṹ�嶨�� CanRx: һ�������ļ�֡��head��manage ==========*/
typedef struct{  // file ����
	
		BOOL bUsIng;
		BOOL bRecFinish;
		
		
		// ����ʱ�� lenTotal = �ڷ���buf�е��ֽ�����
		//		lenNow = �ѷ��͵�buf�е��ֽ��ֽ�������outָ�롣
		// 		���� fileHead[1]= (lenTotal+3).
		U32 haveRecLength;
		U32 fileLength;
		
		U8 verifyVal;
}TCanFile_RxN_Prop;


typedef struct{
	TCanFile_RxN_Prop	rxFileProp; //fileProp;
	TCanFile_sId  		fileSId;  //src,dest,id.
	struct{
		U8 recStart_100msNum;
		U8 recFinish_100msNum;
	}tmr;
}TCanRxFileHead_st;

/*================= �ṹ�嶨�� CanRx: һ�������ļ�֡��head��manage ==========*/


typedef struct{  // file ����
	
		BOOL bHaveFile;
		BOOL bSendIng;
		BOOL bSendFinish;
		
				U8 fileId;
		U8 taskId;  // main�����
		U32 haveSendByte;
		U32 needSendTotal; // �� fileLength ��1���ֽڡ� ... verify, FF;
		U32 fileLength;		// file, length, ... , verify;
		U8 verifyVal;
}TCanFile_TxN_Prop;

typedef struct{  // buf �������
	
	TCanFile_TxN_Prop	txFileProp; //buf;  
	TCanFile_sId 		fileSId;
	
	struct{
		U8 loadStart_100msNum;
		U8 sendFinish_100msNum;
	}tmr;
	
}TCanTxFileHead_st;

/*================= ���к������� ====================================*/
//EX_CanBufLib_strFileProp 


/******************************************************************************
// END :
******************************************************************************/
#endif // __CanBufLib_strFileProp_H__

