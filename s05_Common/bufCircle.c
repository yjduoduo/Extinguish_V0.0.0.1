#define __bufCircle_C__
/******************************************************************************
* @file    bufCircle.c
* @author  yx
* @version V1.2
* @date    2013.10.11
* @brief   
* 
******************************************************************************/
#include  "bufCircle.h"


#include  "sysDef.h"
//#include "incFile.h"	


/*================= ���� ============================================*/

/*================= �ṹ���� ========================================*/

/*================= ˽�нṹ�������� ================================*/

/*================= ���к������� ====================================*/

/*================= ˽�к������� ====================================*/

/*=================  ================================================*/
		
/******************************************************************************
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/

/******************************************************************************
* NAME: 
* FUNC: //
*   IN:
*  OUT: 
// intr-add + main-rd, ���Բ��ؿ��ơ�
// main-add + intr-rd, main���������������ƶ�inָ��, ��ֹ�ж����У���������Ч�������
******************************************************************************/
void BufCircleIni(U32 max, TBufCircle *pBufCircle)
{
	pBufCircle->in = 0;
	pBufCircle->out = 0;
	pBufCircle->max = max;
	pBufCircle->bFull = FALSE;
}

/******************************************************************************
* FUNC: //
******************************************************************************/
BOOL bFullBufCircle(TBufCircle *pBufCircle)
{
	return (pBufCircle->bFull);
}

/******************************************************************************
* FUNC: //
******************************************************************************/
BOOL bEmptyBufCircle(TBufCircle *pBufCircle)
{
	if(pBufCircle->bFull)
	{
		return FALSE;
	}
	else
	{
		return (pBufCircle->in == pBufCircle->out);
	}
}


/******************************************************************************
* FUNC: //
******************************************************************************/
U32 BufCircle_GetIn(TBufCircle *pBufCircle) //in
{
	return pBufCircle->in;
}

/******************************************************************************
* FUNC: //
******************************************************************************/
void BufCircle_InInc(TBufCircle *pBufCircle) 
{
U32 mIn;

	pBufCircle->in++;
	if(pBufCircle->in >= pBufCircle->max)
	{
		pBufCircle->in = 0;
	}
	
	mIn = pBufCircle->in + 1;
	if(mIn >= pBufCircle->max)
	{
		mIn = 0;
	}
	if(mIn == pBufCircle->out)
	{
		pBufCircle->bFull = TRUE;
	}
	
}

/******************************************************************************
* FUNC: //
******************************************************************************/
void BufCircle_InDec(TBufCircle *pBufCircle)
{
	if(bEmptyBufCircle(pBufCircle))
	{
		return;
	}
	if(pBufCircle->in == 0)
	{
		pBufCircle->in = (pBufCircle->max - 1);
	}
	else
	{
		pBufCircle->in--;
	}
	pBufCircle->bFull = FALSE;
}

/******************************************************************************
* FUNC: //
******************************************************************************/
U32 BufCircle_GetOut(TBufCircle *pBufCircle) //out
{
	return pBufCircle->out;
}

/******************************************************************************
* FUNC: //
******************************************************************************/
void BufCircle_OutInc(TBufCircle *pBufCircle) //
{
	pBufCircle->out++;
	if(pBufCircle->out >= pBufCircle->max)
	{
		pBufCircle->out = 0;
	}
	
	// if(pBufCircle->bFull)
	// {
		pBufCircle->bFull = FALSE;
	// }
}

/******************************************************************************
* FUNC: //
******************************************************************************/
void BufCircle_OutDec(TBufCircle *pBufCircle)
{
U32 mDecOut;
	if(bEmptyBufCircle(pBufCircle))
	{
		return;
	}
	if(pBufCircle->out == 0)
	{
		mDecOut = (pBufCircle->max - 1);
	}
	else
	{
		mDecOut = (pBufCircle->out - 1);
	}
	
	if(mDecOut != pBufCircle->in) // ��ֱֹ�ӱ� empty.
	{
		pBufCircle->out = mDecOut;
	}
	
}


/******************************************************************************
* NAME: 
* FUNC: //
*   IN:
*  OUT: 
******************************************************************************/
U32 CircleAdd(U32 now, U32 vary, U32 max)
{
	U32 num = now + vary;
	if(num >= max)
	{
		return (num - max);
	}
	else
	{
		return num;
	}
}

U32 CircleSub(U32 now, U32 vary, U32 max)
{
	if(now < vary)
	{
		return (now + max - vary);
	}
	else
	{
		return (now - vary);
	}
}


// ����in=4, out=5, max=8: return 7
// ����in=4, out=6, max=8: return 6
U32 CircleDiffValue(U32 in, U32 out, U32 max)
{
	return ((in + max - out) % max);
}

/******************************************************************************
* FUNC: // 
*   IN:
*  OUT: 
******************************************************************************/
BOOL BufCircle_In_Add(U32 vary, TBufCircle *pBufCircle)
{
	pBufCircle->in = CircleAdd(pBufCircle->in, vary, pBufCircle->max);
	return TRUE;
}

BOOL BufCircle_Out_Add(U32 vary, TBufCircle *pBufCircle)
{
	pBufCircle->out = CircleAdd(pBufCircle->out, vary, pBufCircle->max);
	return TRUE;
}

/******************************************************************************
* FUNC: //������ֽ���
*   IN:
*  OUT: 
******************************************************************************/
U32 CircleSpaceBytes(TBufCircle *pBufCircle)
{
U32 max = pBufCircle->max;
U32 mBytes;


	if(bEmptyBufCircle(pBufCircle))
	{
		return (pBufCircle->max - 1);
	}
	if(pBufCircle->bFull) // ����in=4, out=5, max=8: return 0;
	{
		return 0;
	}
	// ����in=4, out=6, max=8: return (2-1);
	mBytes = (pBufCircle->out + (max - pBufCircle->in));
	mBytes %= max;
	return (mBytes - 1);
}

// �Ѵ洢���ֽڸ���
U32 CircleFillBytes(TBufCircle *pBufCircle)
{
	return CircleDiffValue(pBufCircle->in, pBufCircle->out, 
						pBufCircle->max);
}


/******************************************************************************
* FUNC: // *pCopySrc++ -> ����*(pBufS + mIn)++
*   IN: ����ǰҪȷ�� copyMax < circle->max.
*  OUT: ����allign(4)���������FF���롣
*		.in ���䡣
******************************************************************************/
void CircleCopyBytAllign4(U8 *pBufS, U8 *pCopySrc, U32 copyMax, TBufCircle *pBufCircle)
{
U32 mAllignByte;
U8 *pBufNow;
U32 mIn;
U32 ii;

	mAllignByte = (4 - (copyMax & 0x03))%4;
	
	mIn = CircleCopyByte(pBufS,pCopySrc, copyMax, pBufCircle);
	if(mAllignByte != 0)
	{
		pBufNow = pBufS + mIn;
		for(ii=0; ii<mAllignByte; ii++)
		{
			*pBufNow = ~0;
			pBufNow++;
		}
	}
}


/******************************************************************************
* FUNC: // *pCopySrc++ -> ����*(pBufS + mIn)++
*   IN: ����ǰҪȷ�� copyMax < circle->max.
*  OUT: copyied.next, ����DWord���롣
******************************************************************************/
U32 CircleCopyByte(U8 *pBufS, U8 *pCopySrc, U32 copyMax, TBufCircle *pBufCircle)
{
U8 *pBufNow;
U8 *pBufE;
U32 copyNum;
	
	if(copyMax >= pBufCircle->max)
	{
		return pBufCircle->in;
	}
	
	pBufE = pBufS + pBufCircle->max;
	pBufNow = pBufS + pBufCircle->in;
	for(copyNum=0; copyNum<copyMax; copyNum++)
	{
		*pBufNow = *pCopySrc;
		pCopySrc++;
		pBufNow++;
		if(pBufNow == pBufE)
		{
			pBufNow = pBufS;
		}
	}
	return (pBufNow - pBufS);
}


/******************************************************************************
* FUNC: // ����*(pBufS + mOut)++ -> *pCopyDest++
*   IN: ����ǰҪȷ�� copyMax < circle->max.
*  OUT: 
******************************************************************************/
void ByteCopyFromCircle(U8 *pBufS, U8 *pCopyDest, U32 copyMax, TBufCircle *pBufCircle)
{
U8 *pBufNow;
U8 *pBufE;
U32 copyNum;
	
	if(copyMax >= pBufCircle->max)
	{
		return;
	}
	
	pBufE = pBufS + pBufCircle->max;
	pBufNow = pBufS + pBufCircle->out;
	for(copyNum=0; copyNum<copyMax; copyNum++)
	{
		*pCopyDest = *pBufNow;
		pCopyDest++;
		pBufNow++;
		if(pBufNow == pBufE)
		{
			pBufNow = pBufS;
		}
	}
}

/******************************************************************************
* FUNC: // END
*   IN:
*  OUT: 
******************************************************************************/
