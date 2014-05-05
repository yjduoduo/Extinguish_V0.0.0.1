#ifndef __prjBool_H__
#define __prjBool_H__
/******************************************************************************
* @file    prjBool.h
* @author  yx
* @version V1.0
* @date    2012-01-05
* @brief   Use in ".c"
* 
#include  "prjBool.h"
******************************************************************************/
//
/******************************************************************************
// BOOL :
******************************************************************************/
#define FALSE   (0)
#define TRUE    (1)
#define U_SUCC	TRUE
#define U_FAILED	FALSE

#define ALLOW		1	
#define FORBID	0
#define U_ALLOW		1	
#define U_FORBID	0
					
#define	U_WRITE	0
#define	U_READ	1
#define	ACK		0
#define	NACK		1	  

#define	U_MANU	0	
#define	U_AUTO	1	
	   
#define	U_ADD	0	
#define	U_INC	0	
#define	U_DEC	1	
  				  	
#define	U_USUAL	0
#define	U_ERR	1 
	
#define	U_IDLE	0 
#define	U_WORK	1  
#define	U_OFF	0 
#define	U_ON		1 

#define	U_BEFORE	0 
#define	U_NEXT	1	 

#define	U_HIGH	0 
#define	U_LOW	1	 

#define	U_ENABLE	0 
#define	U_DISABLE	1	

#define	U_CallFromIntr	0 
#define	U_CallFromMain	1	

#define U_MIN  0
#define U_MAX  1

#define U_FIG_BCD  0
#define U_FIG_HEX  1


/******************************************************************************
// END :
******************************************************************************/
#endif // __prjBool_H__

