#ifndef __lcdSub_InputFig_H__
#define __lcdSub_InputFig_H__
/******************************************************************************
* @file    lcdSub_InputFig.h
* @author  yx
* @version V1.0
* @date    2013-09-16
* @brief
* add: FigInput_AddIniFig_WithCurHide();  FigInput_CursorRight_withRowCol(); 
*
#include  "lcdSub_InputFig.h"
******************************************************************************/
//
#include  "prjCompileCon.h"

#include  "lcd_Para.h"

/*================= extern ============================================*/
#ifdef  __lcdSub_InputFig_C__
#define EX_lcdSub_InputFig
#else
#define EX_lcdSub_InputFig extern
#endif
/*================= ���� ============================================*/

/*================= �ṹ�嶨�� ======================================*/
#ifdef  __lcdSub_InputFig_C__

#define U_INPUT_NUM_MAX  20

typedef struct
{
    U8 			iFig;   //���������
    U8 			iMax;   //���������
    BOOL 		bIsHide; // * ������������
    BOOL 	bRenew; // TRUE=�������롣
    TLcdRL_st  	rl;

}TInputOneFig_st;


typedef struct
{
    U8   	itemStart;
    U8   	itemEnd;  // = last + 1;
    U32 	hexFigIni;   //
    U32 	hexFigMax;   //
    U32		hexFigIn;   //���������
}TInputGroupFig_st;
#define U_INPUT_FIG_GROUP_MAX   5


typedef struct
{
    struct
    {
        U8 now;		//���λ��
        BOOL bValid;
        BOOL bBlink; //������� TRUE��ɫ FALSE����
    }cursor;

    // ȱ�ݣ� hex=0xFF, iMax=[3, 10, 10]; ��2λ�޷��������λ�������жϳ����ޡ�
    // �������� group.
    // in = cursor.now;
    TInputOneFig_st  stRl[U_INPUT_NUM_MAX]; // ÿ������ռ1��λ��

    struct
    {
        U8 		in;
        TInputGroupFig_st buf[U_INPUT_FIG_GROUP_MAX];
    }group;

    struct
    {
        U8 NeedNum;  //��Ҫ������ =0��ʾ����������

        BOOL bFinish;

        BOOL bAllowChkExceedWhenInput;
        BOOL bExceed; // ���ޡ�
        // U8 change;     //���������б仯λ��  usua()���� ĳЩҳ���������������ֻ�����ʾ
    }state;	  //��������

    struct
    {
        U16 RowStart;  //ʵ�ʵ� ����
        U16 LineStart;
        U16 RowEnd;
        U16 LineEnd;
        U8 Prompting;   //��ǰ����ʾ����
    }Prompt; 	//��ʾ���ַ�Χ
    // U8 FunKey[U_PAGE_FUNKEY_MAX];  	//���ܼ�λ��  U_PTASK_FUNKEY_UP

}TFigInput_st;

#endif  //__lcdSub_InputFig_C__
/*================= ���нṹ�������� ================================*/


/*================= ˽�к������� - ����exceed =======================*/
#ifdef  __lcdSub_InputFig_C__

// �����Ƿ��г��޵����� - ��ǰ�����йصģ�
// ֻ�����������ڼ�����ʱ�򣬲��������á�
// *  OUT: TRUE = sign = bExceed;
BOOL cacuFigInput_nowIn_Exceed(U8 mIn, BOOL bExceedPre);

// �����Ƿ��г��޵����� - all - �������� + group��
// *  OUT: TRUE = sign = bExceed;
BOOL cacuFigInput_Exceed(void);
// �����Ƿ��г��޵����� - all �������֣�
BOOL bFigInput_figIn_Exceed(void);
// �����Ƿ��г��޵����� - һ�� �������֣�
BOOL bFigInput_figIn_one_Exceed(U8 mIn);
// �����Ƿ��г��޵����� - all group�����
BOOL bFigInput_group_Exceed(void);

// ���� group����������
// *  OUT: TRUE= ��ֵ��Ч��groupFig < max;
BOOL cacuFigInput_Group(U8 mGroupNum, U32 *pRtnGrpFig);

void set_figInput_exceed(void);
void clr_figInput_exceed(void);
BOOL bGet_figInput_exceed(void);

#endif  //__lcdSub_InputFig_C__
/*================= ˽�к������� ====================================*/
#ifdef  __lcdSub_InputFig_C__

static TFigInput_st  vStFigInput;

void figInput_showIni(void);
void figInput_showOne(U8 mItem);
BOOL figInput_addIniOne(TYPE_LCD_RL mRow, TYPE_LCD_RL mLine,
                        U8 mFig, U8 mMax, BOOL bHideShow);

// ���������
void figInput_cursorBlink_start(U8 cursorNow);
void figInput_cursorBlink_stop(void);
BOOL figInput_cursorBlink_TmrArried(void);



// �������룬����λ���б䣺
void figInput_fig_change(U8 mIn);
void figInput_cursor_leave(U8 mIn);
void figInput_cursor_new(U8 mIn);


#endif  //__lcdSub_InputFig_C__


/*================= ���к������� ====================================*/
//EX_lcdSub_InputFig

extern void FigInput_Init(void);  //��ʼ��
extern void FigInput_Exec(void);


// if ��Ҫ�������룺
extern BOOL bFigInputNeed(void);
// if ���볬�ޣ�
extern BOOL bFigInput_Exceed(void);


/******************************************************************************
˳��
FigInput_ReStart();
FigInput_Add...();  ��Ҫ������ƶ���˳����á�
FigInput_AddIniEnd();
�������֣��ƶ���ꣻ �ڼ� FigInput_Exec(); ���ж�ʱ��
FigInput_Stop();
******************************************************************************/
// ��������׼������������Ҫ FigInput_Add...��ʼ����λ��
extern void FigInput_ReStart(BOOL bAllowChkExceedWhenInput);
// �������� �˳���
extern void FigInput_Stop(void);

// ini: �������� 1��:
extern BOOL FigInput_AddIniFig(
                        TYPE_LCD_RL mRow, TYPE_LCD_RL mLine,
                        U8 mFig, U8 mMax);

BOOL FigInput_AddIniFig_WithCurHide(TYPE_LCD_RL mRow, TYPE_LCD_RL mLine,
                        U8 mFig, U8 mMax,BOOL CurSorHide);
// ini: �������� hex:
// ������� GetFigInput_Group() ��ȡ �����һ������
extern BOOL FigInput_AddIniHex(TYPE_LCD_RL mRow, TYPE_LCD_RL mLine,
                       U32 mFigHex, U32 mFigMaxHex, U8 bitTotal,
                       U8 *pRtnGroupNum);
// *  OUT: TRUE= ��ֵ��Ч��groupFig < max;
extern BOOL GetFigInput_Group(U8 mGroupNum, U32 *pRtnGroupFig);
// ini: ������ʾ������λ��:
extern BOOL FigInput_AddIniHide(TYPE_LCD_RL mRow, TYPE_LCD_RL mLine,
                        U8 mNum);
// �����ϣ���ʾini�ַ���
extern void FigInput_AddIniEnd(void);


// ���µ����ּ����룺
extern BOOL FigInput_newFig(U8 mFig);
extern BOOL FigInput_newUp(void);
extern BOOL FigInput_newDown(void);
extern void FigInput_CursorRight(void);
extern void FigInput_CursorRight_withRowCol(U8 Row,U8 Col);
extern void FigInput_CursorLeft(void);


/******************************************************************************
// END :
******************************************************************************/
#endif // __lcdSub_InputFig_H__

