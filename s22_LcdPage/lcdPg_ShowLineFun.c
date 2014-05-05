#include "lcdPg_ShowLineFun.h"

#include "posText.h"

#include  "opeaMenuLib_incOut.h"

#include  "LcdLib_incOut.h" // LCD��ʾ���� �Ѳ���

#include  "lcdSub_ModeTextFig.h" // ��ʾ �ַ������� �Ѳ���
#define __lcdSub_InputFig_C__
#include  "lcdSub_InputFig.h" // ҳ�����������ֹ���. �д��룬δ���ԣ�

#include  "lcdPg_Common.h"  // 2��������ҳ������õ����Ӻ���




//��괦��
#include  "tmrTick.h"
#include  "lcdSub_ModeTextFig.h"
#include  "codeComm.h"
#include  "codeFig.h"
#include  "sysDef.h"






#define __lcdPg_Page_C__
#include "lcdPg_Page.h"










#define U_DevScan_AdrMax    64
#define U_DevScan_AdrHalf   32

// һ����ַ��ռ�� x pix :
#define U_DevScan_Pix_X_1Point   5

//����0�����㻭��������ļ�ͷ
#define U_DevScan_Pix_X_Start_x    13 //the distance from the leftest line

// ���ߵ� Y λ�á� ��Ҫ�������� �ָ���ַ����ʾ���ߡ�
#define U_DevScan_Pix_Y0_Start_N  ((U_LCD_ROW_PIX_MAX/2)-1)

#define U_DevScan_Pix_Y1_Start_N  ((U_LCD_ROW_PIX_MAX )-5)

#define U_DevScan_Pix_Y_End_N  (2)

#define U_DevScan_Pix_X_Start_p061    13+8




// һ����ַ��ռ�� y pix:��Ϊ��ʾ�����ߵ����ֵ
//#define U_DevScan_Pix_Y_1Point   ((U_LCD_ROW_PIX_MAX/4))
#define U_DevScan_Pix_Y_1Point_N   (24)





//��ʾ����
#define U_LCD_AXIX_NUM_POS_Y 180//��ʾ���ֵ�y����
#define U_LCD_AXIX_MUM_POS_X_32 25//��ʾ����32��x����
#define U_LCD_AXIX_MUM_POS_X_64 50//��ʾ����64��x����


#define U_INPUT_NUM_MAX  20


/******************************************************************************
* ҳ��: // P060
******************************************************************************/

// �� ��ʾ���꣺
void dw_devScan_coordinate_new(void)
{
    //��ʾ������Ϣ
    //dw_info_text_axis();
    // �������᣺
    dw_devScan_axis_new();

    // ����ַ��λ��
    dw_devScan_adrPrompt_new();
}

/******************************************************************************
* ҳ��: // ��·���  P060_TsLoopDevScan_
* ����;
*  _ ��·:
* |_________________________> 32
* |_________________________> 64
* ����ַ��λ�ߣ���ַÿ8���������ں�������4����������ʾ��ÿ4�ı�����2���ء�

��64��ַ����2�У�
���ÿ��ַռ 192 / 32 = 6 pix. ��5pix�㣬32*5=160����192-160=32 2�����ֵ�λ�á�
******************************************************************************/

// ��������X�ĳ��ȣ�
#if 0
TYPE_LCD_XY cacu_devScan_coordinateX(void)
{
    return cacu_devScan_deteX(U_DevScan_AdrHalf-1)
            + U_DevScan_Pix_X_1Point;
}
#endif
TYPE_LCD_XY cacu_devScan_coordinateX_p061(void)
{
    return cacu_devScan_deteX_p061(U_DevScan_AdrHalf-1)
            + U_DevScan_Pix_X_1Point;
}

TYPE_LCD_XY cacu_devScan_deteX_p061(U32 mAdr)
{
    U32 mPoint;
    TYPE_LCD_XY  dwX;

    if(mAdr < U_DevScan_AdrHalf){//the addr between 0~31
        mPoint = mAdr;//31
        dwX =  U_DevScan_Pix_X_Start_p061;
        dwX += (mPoint) *  U_DevScan_Pix_X_1Point;
        dwX += U_DevScan_Pix_X_1Point; // �����һ����ַ��λ��

    }else{//the addr between 32~63
        mPoint = mAdr%U_DevScan_AdrHalf;//31
        dwX =  U_DevScan_Pix_X_Start_p061;
        dwX += (mPoint) *  U_DevScan_Pix_X_1Point;
        dwX += U_DevScan_Pix_X_1Point; // �����һ����ַ��λ��
    }

    //  if(  (mAdr+1 == U_DevScan_AdrHalf)
    //       || (mAdr+1 == U_DevScan_AdrMax)
    //       )
    //    {//if addr is 31 or 63,as half and whole

    //    }
    //  else
    //    {
    //      mPoint =  mAdr % U_DevScan_AdrHalf;
    //      mPoint += 1;   // (63-32)+1 =32
    //    }

    //  dwX =  U_DevScan_Pix_X_Start;
    //  dwX += (mPoint) *  U_DevScan_Pix_X_1Point;
    //  dwX += U_DevScan_Pix_X_1Point; // �����һ����ַ��λ��

    return dwX;
}

void dw_info_text_axis(void)
{
    ShowCodeCharRL(0, 6, looptext[0], FALSE);
}

void dw_devScan_axis_new(void)
{

    U8 iiy;
  //  ShowCodeCharRL(0, 1, "^", FALSE);//��
    ShowCodeCharRL(0, 0, "mA", FALSE);

    // LcdSw_HvLine(mPixRow_S,mPixLine_S, mPixRow_E,mPixLine_E)
    // ���ߣ�
    LcdSw_HvLine(
                U_DevScan_Pix_Y1_Start_N,
                U_DevScan_Pix_X_Start_x,
                U_DevScan_Pix_Y_End_N,
                U_DevScan_Pix_X_Start_x);//the second column at x,the y to the y1 as top to bottom

    LcdSw_ClrHvLine(
                34,
                U_DevScan_Pix_X_Start_x,
                32,
                U_DevScan_Pix_X_Start_x);



    // show > sign��
  //  ShowCodeCharRL(4, (U_LCD_LINE_MAX - 1), ">", FALSE);
    //��ʾ����0����U_DevScan_Pix_X_Start��
    LcdSw_HvLine(
                U_DevScan_Pix_Y0_Start_N,
                U_DevScan_Pix_X_Start_x,
                U_DevScan_Pix_Y0_Start_N,
                (U_DevScan_Pix_X_Start_x
                 + cacu_devScan_coordinateX())//y0 as row at horital,x from  x and x+cal
                );
    //��ʾ����32
    LcdSw_Fig(U_LCD_AXIX_MUM_POS_X_32, (U_LCD_AXIX_NUM_POS_Y), U_DevScan_AdrHalf, 2);


//    ShowCodeCharRL(8, (U_LCD_LINE_MAX - 1), ">", FALSE);
    // ����2��
    LcdSw_HvLine(
                U_DevScan_Pix_Y1_Start_N,
                U_DevScan_Pix_X_Start_x,
                U_DevScan_Pix_Y1_Start_N,
                (U_DevScan_Pix_X_Start_x
                 + cacu_devScan_coordinateX())
                );
    //��ʾ����64
    LcdSw_Fig(U_LCD_AXIX_MUM_POS_X_64, (U_LCD_AXIX_NUM_POS_Y), U_DevScan_AdrMax, 2);

    for(iiy=0;iiy<6;iiy++){
        //��ʾ�����꣬��ȡ6�����꼴��
        LcdSw_HvLine(
                    yval[iiy],
                U_DevScan_Pix_X_Start_x,
                yval[iiy],
                U_DevScan_Pix_X_Start_x-2
                );
        if(0==iiy%3)
            LcdSw_Ascii88Fig(yval[iiy]-3,0,30,2);
        else if(1==iiy%3)
            LcdSw_Ascii88Fig(yval[iiy]-3,0,20,2);
        if(2==iiy%3)
            LcdSw_Ascii88Fig(yval[iiy]-3,0,10,2);
    }



}
//p061����������
void dw_devScan_axis_p061(void)
{

    U8 iiy;
    U8 tmpnum;
  //  ShowCodeCharRL(0, 1, "^", FALSE);//��
    //ShowCodeCharRL(0, 0, "mA", FALSE);

    // LcdSw_HvLine(mPixRow_S,mPixLine_S, mPixRow_E,mPixLine_E)
    // ���ߣ�
    LcdSw_HvLine(
                U_DevScan_Pix_Y1_Start_N,
                U_DevScan_Pix_X_Start_p061,
                U_DevScan_Pix_Y_End_N,
                U_DevScan_Pix_X_Start_p061);//the second column at x,the y to the y1 as top to bottom
    //��ʾ����32
//    LcdSw_Fig(U_LCD_AXIX_MUM_POS_X_32, (U_LCD_AXIX_NUM_POS_Y), U_DevScan_AdrHalf, 2);
    //��ʾ����64
//    LcdSw_Fig(U_LCD_AXIX_MUM_POS_X_64, (U_LCD_AXIX_NUM_POS_Y), U_DevScan_AdrHalf, 2);


//    ShowCodeCharRL(8, (U_LCD_LINE_MAX - 1), ">", FALSE);
    // ����2��
    LcdSw_HvLine(
                U_DevScan_Pix_Y1_Start_N,
                U_DevScan_Pix_X_Start_p061,
                U_DevScan_Pix_Y1_Start_N,
                ((U_DevScan_Pix_X_Start_p061
                 + cacu_devScan_coordinateX_p061()>192?192-10:(U_DevScan_Pix_X_Start_p061
                 + cacu_devScan_coordinateX_p061())))
                );
#if 1
    tmpnum=120;

    for(iiy=0;iiy<ARRAYSIZE(yval_p061);iiy++){
        //��ʾ�����꣬��ȡ6�����꼴��
        LcdSw_HvLine(
                    yval_p061[iiy],
                U_DevScan_Pix_X_Start_p061,
                yval_p061[iiy],
                U_DevScan_Pix_X_Start_p061-2
                );
        if(0==iiy){
//            tmpnum-=8;
            continue;
        }
        if(tmpnum>=100)
            LcdSw_Ascii88Fig(yval_p061[iiy]-3,0,tmpnum,3);
        else
            LcdSw_Ascii88Fig(yval_p061[iiy]-3,3,tmpnum,2);
        tmpnum-=20;
    }
#endif


}

// ��ַ��λ����ʾ������ַ��λ�ߣ�
/*****************************************************************************
*FUNC:paint the locate line at the horictal line��the first and the end must be careful
*IN:
*OUT:
*****************************************************************************/
void dw_devScan_adrPrompt_new(void)
{
    U32 mAdr;
    //from 0-64,need to paint total 18 lines

    for(mAdr=0; mAdr<U_DevScan_AdrMax; mAdr++)//0~31//32~63
    {
        if((mAdr % 4) == 0||31==mAdr||63==mAdr)
        {
            dw_devScan_adrPrpt_one(mAdr);
        }
    }

    //  add_digital_num_at_axis();

}
void dw_devScan_adrPrompt_half(void)
{
    U32 mAdr;
    //from 0-64,need to paint total 18 lines

    for(mAdr=U_DevScan_AdrHalf; mAdr<U_DevScan_AdrMax; mAdr++)//0~31//32~63
    {
        if((mAdr % 4) == 0||31==mAdr||63==mAdr)
        {
            dw_devScan_adrPrpt_one_p061(mAdr);
        }
    }

    //  add_digital_num_at_axis();

}

/*��ʾ���������֣�����û��̫С�ģ��Ų���*/
void add_digital_num_at_axis(void)
{
    //  TYPE_LCD_RL mRow=10;
    //  TYPE_LCD_RL mLine=20;
    //  TShowFigPara_st pShowFigPara;
    //  pShowFigPara.colorText=1;
    //  Show88_Figure(mRow,mLine,&pShowFigPara);
    //  ShowXY_Fig_LeftAllign(mRow,mLine,1,1,8);
    //  Show88_Fig_Pre0(mRow,mLine,1,8);
    //  Show_1Fig_usual(mRow,mLine,32);
    //  Show88_1Fig_if_inverse(5,2,1,FALSE);
    ////  Show88_1Fig_if_inverse(5,5,4,FALSE);
    //  Show88_1Fig_if_inverse(5,8,8,FALSE);
    //  Show88_1Fig_if_inverse(8,8,3,FALSE);

    //  showLib_Fig_LeftAllign(0,8,8,32,16);
    //  showLib_1Fig_if_inverse(0,8,8,32,16);
    //  U8 i;
    //  for(i=0;i<5;i++)
    //    Show88CodeCharRL(5,2+6*i,"1",FALSE);

    U8 beginnum=2;
    U8 rownum=5;
    Show88CodeCharRL(rownum,beginnum,"1",FALSE);beginnum+=6;
    Show88CodeCharRL(rownum,beginnum,"8",FALSE);beginnum+=6;
    Show88CodeCharRL(rownum,beginnum,"16",FALSE);beginnum+=7;
    Show88CodeCharRL(rownum,beginnum,"24",FALSE);beginnum+=6;
    Show88CodeCharRL(rownum,beginnum,"32",FALSE);
    beginnum=1;
    rownum=9;
    Show88CodeCharRL(rownum,beginnum,"33",FALSE);beginnum+=6;
    Show88CodeCharRL(rownum,beginnum,"40",FALSE);beginnum+=7;
    Show88CodeCharRL(rownum,beginnum,"48",FALSE);beginnum+=7;
    Show88CodeCharRL(rownum,beginnum,"56",FALSE);beginnum+=6;
    Show88CodeCharRL(rownum,beginnum,"64",FALSE);


}

void show_currentresult_p061(funpara* para)
{

    U8 i;
    U8 CurrentVal[32];
    
    //the current value tranfered to the lcd to show

    (void)para;
    for(i=0;i<32;i++)
    {
        if(0==i%2)
            CurrentVal[i]=60;
        else
            CurrentVal[i]=200;
    }
    dw_devScan_current_all_p061(CurrentVal,U_DevScan_AdrHalf,dw_devScan_current_one_p061);

}

/******************************************************************************
* NAME:
* FUNC: //
*   IN:
*  OUT:
******************************************************************************/

//�� lcdPg_Page.c��ĩβ��������º�����
//pAddr = {1,2,3,6,7,9,11,12,13};
//showConsequentAddr(2, 5,   9, U8 *pAddr)
//ϣ����ʾΪ��
//     9: 1~3,6~7,9,11,
//12~13;
//void showConsequentAddr(U8 mRow, U8 mLineS, U8 mAddrNum, U8 *pAddr)
//{

//}

void showConsequentAddr(U8 mRow, U8 mLineS, U8 mAddrNum, U8 *pAddr,U8 size)
{
    U8 ii;
    U8 tmp[30];//�洢����
    U8 tmpsign[30];//�洢����
    U8 tmpsignnum=0;
    U8 tmpnum=0;
    U8 var;
    U8 BreakNum=0;
    U8 Colon=(U8)':';
    U8 Wavylines=(U8)'~';
    U8 Comma=(U8)',';
    U8 tmpline=mLineS;
    tmp[tmpnum++]=mAddrNum;
    tmpsign[tmpsignnum++]=Colon;

    if(size>30)//��ֹ�������
        size=30;

    for(ii=0;ii<size;ii++){
        if(0==ii){//��һ�β��ж�
            tmp[tmpnum]=*(pAddr+ii);
            var=*(pAddr+ii);//��¼�˴ε�ֵ
            tmpnum++;
        }else{
            if(var+1==*(pAddr+ii)){//if
                var=*(pAddr+ii);//��¼�ڶ���
                if(0==BreakNum){
                    tmpsign[tmpsignnum]=Wavylines;
                    tmpsignnum++;
                }
                BreakNum++;
            }else{
                if(0==BreakNum){//Ϊֻ��һ���������������һ������
                    BreakNum=0;
                    tmpsign[tmpsignnum]=Comma;
                    tmpsignnum++;
                    tmp[tmpnum]=*(pAddr+ii);//���һ����ֵ
                    tmpnum++;
                    var=*(pAddr+ii);
                }else{
                    //��¼�ϴε��Ǹ�����,ͬʱ���һ�����ţ�ͬʱ��varΪ��ֵ
                    tmp[tmpnum]=var;
                    tmpnum++;
                    BreakNum=0;
                    tmpsign[tmpsignnum]=Comma;
                    tmpsignnum++;
                    tmp[tmpnum]=*(pAddr+ii);//���һ����ֵ
                    tmpnum++;
                    var=*(pAddr+ii);
                }
            }
        }

    }

    for(ii=0;ii<tmpnum;ii++){
        if(tmp[ii]>=100&&tmp[ii]<256){
            Show_Fig_Pre0(mRow,tmpline,tmp[ii],3);
            tmpline+=3;
        }else if(tmp[ii]>=10&&tmp[ii]<100){
            Show_Fig_Pre0(mRow,tmpline,tmp[ii],2);
            tmpline+=2;
        }else{
            Show_Fig_Pre0(mRow,tmpline,tmp[ii],1);
            tmpline+=1;
        }
        if(58==tmpsign[ii]){
            ShowCodeCharRL(mRow,tmpline,":",FALSE);
            tmpline+=1;
        }else if(126==tmpsign[ii]){
            ShowCodeCharRL(mRow,tmpline,"~",FALSE);
            tmpline+=1;
        }else if(44==tmpsign[ii]){
            ShowCodeCharRL(mRow,tmpline,",",FALSE);
            tmpline+=1;
        }else{

        }
    }
}

void showConsequentAddrTest(void)
{
    U8 pAddr[] = {1,2,3,4,5,6,7,8,9,16,17,21};
    showConsequentAddr(6,2,125,pAddr,ARRAYSIZE(pAddr));
    showConsequentAddr(8,0,124,pAddr,ARRAYSIZE(pAddr));
}





void dw_devScan_adrPrpt_one_p061(U32 mAdr)
{
    TYPE_LCD_XY  dwX;
    TYPE_LCD_XY  dwY;

    dwX = cacu_devScan_deteX_p061(mAdr);
    dwY = cacu_devScan_deteY(mAdr);

    if((mAdr % 8) == 0)
    {
        LcdSw_HvLine(dwY,dwX, (dwY+4),dwX);
    }
    else if((mAdr % 4) == 0)
    {
        LcdSw_HvLine(dwY,dwX, (dwY+2),dwX);
    }
    else
    {
        LcdSw_HvLine(dwY,dwX, (dwY+4),dwX);

    }
}


// �� ��ʾ���꣺
void dw_devScan_coordinate_p061(void)
{
    //��ʾ������Ϣ
//    dw_info_text_axis();
    // �������᣺
    dw_devScan_axis_p061();
//    dw_devScan_axis();

    // ����ַ��λ��
    dw_devScan_adrPrompt_half();
}

void dw_devScan_current_all_p061(U8 *pCurrent,U8 ShowNums,void (*dw_devScan_current)(U32 mAdr, U8 mCurrent))
{
    U32 mAdr;
    for(mAdr=0; mAdr<ShowNums; mAdr++)//loop for 64 times
    {
        dw_devScan_current(mAdr, *pCurrent);//first time,
        pCurrent++;//auto incresement
    }
}



//void dw_devScan_current_one_p061(U32 mAdr, U8 mCurrent)
//{

//    TYPE_LCD_XY  dwX;
//    TYPE_LCD_XY  dwY;
//    U8  lvLineY;

//    dwX = cacu_devScan_deteX_p061(mAdr);//mAdr from 0 to 63
//    lvLineY = (mCurrent / 2);//the current value as theput value
//    if(lvLineY >= U_DevScan_Pix_Y_1Point_N)//out of range
//    {
//        lvLineY = (U_DevScan_Pix_Y_1Point_N - 1);
//    }

//    dwY = cacu_devScan_deteY(mAdr+32);

//    LcdSw_HvLine(dwY - lvLineY, dwX,
//                 dwY,           dwX);
//    ExecLcdShow();//the lcd buffer maybe full if called many times,so deal

//}
void dw_devScan_current_one_p061(U32 mAdr, U8 mCurrent)
{

    TYPE_LCD_XY  dwX;
    TYPE_LCD_XY  dwY;
    U8  lvLineY;

    dwX = cacu_devScan_deteX_p061(mAdr);//mAdr from 0 to 63
    lvLineY = (mCurrent / 2);//the current value as theput value
    if(lvLineY >= U_DevScan_Pix_Y_1Point)//out of range
    {
        lvLineY = (U_DevScan_Pix_Y_1Point - 1);
    }

    dwY = cacu_devScan_deteY(mAdr+32);

    LcdSw_HvLine(dwY - lvLineY, dwX,
                 dwY,           dwX);
    ExecLcdShow();//the lcd buffer maybe full if called many times,so deal

}



/******************************************************************************
* ҳ��: // ��ʾ ģ��������
*  _��·_ _ _��ַ: _ _ _ (��ʾ��ǰֵ)
* |
* |_________________________>
* �ѵ�ǰֵ��һ������ʾ���߶ȶ�Ӧֵ�Ĵ�С�����128.
* ÿ�õ�һ���µ�ֵ��X����������һ����ʾλ�ã�����������࿪ʼˢ�£�ͬʱ�����Ҳ�16�����������
* ��Ч�����Ӿ��ϲ�������Ըģ�����ÿ�εõ�ֵ���ú���2�����ر�ʾ��
******************************************************************************/
void show_Simulated_curves(funpara* para)
{

    U8 interval;
    U8 endrow;
    U8 startrow;
    U8 Remainder;
    static U8 seqnum=0;//��ʾ�����˳��
    static U8 iy=0;
    para->val++;
    para->val=para->val>127?1:para->val;
//    para->val=58;
    if(para->firstentry)//���Ϊ��һ�Σ���ص�������Ҫ������λ��
    {
        iy=0;
        seqnum=0;
        para->firstentry=FALSE;
    }
    (void)para;
    //    yval_p061[0];
    endrow=yval_p061[6]+8;//not change
    startrow=yval_p061[0];
    interval=endrow-startrow;//���ֵ

    if(0==iy)
        iy=U_DevScan_Pix_X_Start_p061+5;


    if(para->val>128)
        para->val=128;

    Remainder=(interval*para->val)%128;
    if(Remainder>=64){
        startrow=endrow-(interval*para->val)/128-1;
    }else{
        startrow=endrow-(interval*para->val)/128;
    }

    if(startrow<yval_p061[0])
        startrow=yval_p061[0];


    seqnum++;





    //    showVLine(startrow,endrow,iy);//���ߵķ�ʽ��ʾ
//    showVLine(startrow,startrow+1,iy);//��ķ�ʽ��ʾ
    showHLine(startrow,iy,iy+3);

    iy+=5;
    //    LcdSw_HvLine(0, iy,
    //                 63, iy);

    //        ClrWindow_Page();
    //������16������
    if(32==seqnum){
        seqnum=0;
        iy=0;
        //        ClrWindow_Page();
        //��ʾ���ʼ�����������Ƶ�����
        LcdSw_ClrRectangle(0,U_DevScan_Pix_X_Start_p061+5,
                           endrow,U_DevScan_Pix_X_Start_p061+5*17);
        ShowXYCodeCharRL(0,2,1,"_��·___��ַ",FALSE);
        ShowXY_Fig_Pre0(0,2,1,para->TotalCall->inputFig[0],1);
        ShowXY_Fig_Pre0(0,4,2,para->TotalCall->inputFig[1],1);
        ShowXY_Fig_Pre0(0,4,3,para->TotalCall->inputFig[2],1);
        ShowXY_Fig_Pre0(0,4,4,para->TotalCall->inputFig[3],1);
        //        ShowXYCodeCharRL(0,2,1,"_��·___��ַ",FALSE);
        //        ShowXYCodeCharRL(0,2,1,"_��·___��ַ",FALSE);
        //        ClrWindow_Page();
        //������16��

    }else if(16==seqnum){//����ұ�16������
        LcdSw_ClrRectangle(0,U_DevScan_Pix_X_Start_p061+5*17,
                           endrow,U_DevScan_Pix_X_Start_p061+5*33);
        ShowXYCodeCharRL(0,2,1,"_��·___��ַ",FALSE);
        ShowXY_Fig_Pre0(0,2,1,para->TotalCall->inputFig[0],1);
        ShowXY_Fig_Pre0(0,4,2,para->TotalCall->inputFig[1],1);
        ShowXY_Fig_Pre0(0,4,3,para->TotalCall->inputFig[2],1);
        ShowXY_Fig_Pre0(0,4,4,para->TotalCall->inputFig[3],1);
    }
}



//
/******************************************************************************
* ҳ��: // ��·���
******************************************************************************/

void show_currentresult(funpara* para)
{
    U8 i;
    //the current value tranfered to the lcd to show
    U8 CurrentVal[64];
    (void)para;
    for(i=0;i<64;i++)
    {
        if(0==i%2)
            CurrentVal[i]=60;
        else
            CurrentVal[i]=200;
    }
    dw_devScan_current_all(CurrentVal);
}
//��ʾ����
void showHLine(U8 row,U8 firstcol,U8 endcol)
{
    if(firstcol>endcol)
        return;
    if(!(row<64))
        return;
    if(!(firstcol<191))
        return;
    if(!(endcol<191))
        return;
    LcdSw_HvLine(row, firstcol,
                 row, endcol);
}
