#include "lcdPg_ShowLineFun.h"

#include "posText.h"

#include  "opeaMenuLib_incOut.h"

#include  "LcdLib_incOut.h" // LCD显示驱动 已测试

#include  "lcdSub_ModeTextFig.h" // 显示 字符或数字 已测试
#define __lcdSub_InputFig_C__
#include  "lcdSub_InputFig.h" // 页面上输入数字管理. 有代码，未测试；

#include  "lcdPg_Common.h"  // 2个或以上页面可能用到的子函数




//光标处理
#include  "tmrTick.h"
#include  "lcdSub_ModeTextFig.h"
#include  "codeComm.h"
#include  "codeFig.h"
#include  "sysDef.h"






#define __lcdPg_Page_C__
#include "lcdPg_Page.h"










#define U_DevScan_AdrMax    64
#define U_DevScan_AdrHalf   32

// 一个地址点占的 x pix :
#define U_DevScan_Pix_X_1Point   5

//不是0，方便画竖线上面的箭头
#define U_DevScan_Pix_X_Start_x    13 //the distance from the leftest line

// 横线的 Y 位置。 需要在线下留 分隔地址的提示短线。
#define U_DevScan_Pix_Y0_Start_N  ((U_LCD_ROW_PIX_MAX/2)-1)

#define U_DevScan_Pix_Y1_Start_N  ((U_LCD_ROW_PIX_MAX )-5)

#define U_DevScan_Pix_Y_End_N  (2)

#define U_DevScan_Pix_X_Start_p061    13+8




// 一个地址点占的 y pix:此为显示的竖线的最大值
//#define U_DevScan_Pix_Y_1Point   ((U_LCD_ROW_PIX_MAX/4))
#define U_DevScan_Pix_Y_1Point_N   (24)





//显示汉字
#define U_LCD_AXIX_NUM_POS_Y 180//显示汉字的y坐标
#define U_LCD_AXIX_MUM_POS_X_32 25//显示汉字32的x坐标
#define U_LCD_AXIX_MUM_POS_X_64 50//显示汉字64的x坐标


#define U_INPUT_NUM_MAX  20


/******************************************************************************
* 页面: // P060
******************************************************************************/

// 画 提示坐标：
void dw_devScan_coordinate_new(void)
{
    //显示文字信息
    //dw_info_text_axis();
    // 画坐标轴：
    dw_devScan_axis_new();

    // 画地址定位：
    dw_devScan_adrPrompt_new();
}

/******************************************************************************
* 页面: // 回路浏览  P060_TsLoopDevScan_
* 先做;
*  _ 回路:
* |_________________________> 32
* |_________________________> 64
* 画地址定位线：地址每8的整数倍在横线下用4像素竖线提示；每4的倍数用2像素。

共64地址，分2行，
最多每地址占 192 / 32 = 6 pix. 按5pix算，32*5=160，余192-160=32 2个汉字的位置。
******************************************************************************/

// 计算坐标X的长度：
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
        dwX += U_DevScan_Pix_X_1Point; // 后面空一个地址的位置

    }else{//the addr between 32~63
        mPoint = mAdr%U_DevScan_AdrHalf;//31
        dwX =  U_DevScan_Pix_X_Start_p061;
        dwX += (mPoint) *  U_DevScan_Pix_X_1Point;
        dwX += U_DevScan_Pix_X_1Point; // 后面空一个地址的位置
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
    //  dwX += U_DevScan_Pix_X_1Point; // 后面空一个地址的位置

    return dwX;
}

void dw_info_text_axis(void)
{
    ShowCodeCharRL(0, 6, looptext[0], FALSE);
}

void dw_devScan_axis_new(void)
{

    U8 iiy;
  //  ShowCodeCharRL(0, 1, "^", FALSE);//∧
    ShowCodeCharRL(0, 0, "mA", FALSE);

    // LcdSw_HvLine(mPixRow_S,mPixLine_S, mPixRow_E,mPixLine_E)
    // 竖线：
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



    // show > sign：
  //  ShowCodeCharRL(4, (U_LCD_LINE_MAX - 1), ">", FALSE);
    //显示横线0，从U_DevScan_Pix_X_Start到
    LcdSw_HvLine(
                U_DevScan_Pix_Y0_Start_N,
                U_DevScan_Pix_X_Start_x,
                U_DevScan_Pix_Y0_Start_N,
                (U_DevScan_Pix_X_Start_x
                 + cacu_devScan_coordinateX())//y0 as row at horital,x from  x and x+cal
                );
    //显示汉字32
    LcdSw_Fig(U_LCD_AXIX_MUM_POS_X_32, (U_LCD_AXIX_NUM_POS_Y), U_DevScan_AdrHalf, 2);


//    ShowCodeCharRL(8, (U_LCD_LINE_MAX - 1), ">", FALSE);
    // 横线2：
    LcdSw_HvLine(
                U_DevScan_Pix_Y1_Start_N,
                U_DevScan_Pix_X_Start_x,
                U_DevScan_Pix_Y1_Start_N,
                (U_DevScan_Pix_X_Start_x
                 + cacu_devScan_coordinateX())
                );
    //显示汉字64
    LcdSw_Fig(U_LCD_AXIX_MUM_POS_X_64, (U_LCD_AXIX_NUM_POS_Y), U_DevScan_AdrMax, 2);

    for(iiy=0;iiy<6;iiy++){
        //显示纵坐标，获取6个坐标即可
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
//p061的坐标设置
void dw_devScan_axis_p061(void)
{

    U8 iiy;
    U8 tmpnum;
  //  ShowCodeCharRL(0, 1, "^", FALSE);//∧
    //ShowCodeCharRL(0, 0, "mA", FALSE);

    // LcdSw_HvLine(mPixRow_S,mPixLine_S, mPixRow_E,mPixLine_E)
    // 竖线：
    LcdSw_HvLine(
                U_DevScan_Pix_Y1_Start_N,
                U_DevScan_Pix_X_Start_p061,
                U_DevScan_Pix_Y_End_N,
                U_DevScan_Pix_X_Start_p061);//the second column at x,the y to the y1 as top to bottom
    //显示汉字32
//    LcdSw_Fig(U_LCD_AXIX_MUM_POS_X_32, (U_LCD_AXIX_NUM_POS_Y), U_DevScan_AdrHalf, 2);
    //显示汉字64
//    LcdSw_Fig(U_LCD_AXIX_MUM_POS_X_64, (U_LCD_AXIX_NUM_POS_Y), U_DevScan_AdrHalf, 2);


//    ShowCodeCharRL(8, (U_LCD_LINE_MAX - 1), ">", FALSE);
    // 横线2：
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
        //显示纵坐标，获取6个坐标即可
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

// 地址的位置提示：画地址定位线：
/*****************************************************************************
*FUNC:paint the locate line at the horictal line，the first and the end must be careful
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

/*显示横坐标数字，数字没有太小的，放不下*/
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

//在 lcdPg_Page.c的末尾，添加如下函数：
//pAddr = {1,2,3,6,7,9,11,12,13};
//showConsequentAddr(2, 5,   9, U8 *pAddr)
//希望显示为：
//     9: 1~3,6~7,9,11,
//12~13;
//void showConsequentAddr(U8 mRow, U8 mLineS, U8 mAddrNum, U8 *pAddr)
//{

//}

void showConsequentAddr(U8 mRow, U8 mLineS, U8 mAddrNum, U8 *pAddr,U8 size)
{
    U8 ii;
    U8 tmp[30];//存储数字
    U8 tmpsign[30];//存储符号
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

    if(size>30)//防止数据溢出
        size=30;

    for(ii=0;ii<size;ii++){
        if(0==ii){//第一次不判断
            tmp[tmpnum]=*(pAddr+ii);
            var=*(pAddr+ii);//记录此次的值
            tmpnum++;
        }else{
            if(var+1==*(pAddr+ii)){//if
                var=*(pAddr+ii);//记录第二次
                if(0==BreakNum){
                    tmpsign[tmpsignnum]=Wavylines;
                    tmpsignnum++;
                }
                BreakNum++;
            }else{
                if(0==BreakNum){//为只有一个不连续数的添加一个逗号
                    BreakNum=0;
                    tmpsign[tmpsignnum]=Comma;
                    tmpsignnum++;
                    tmp[tmpnum]=*(pAddr+ii);//添加一个新值
                    tmpnum++;
                    var=*(pAddr+ii);
                }else{
                    //记录上次的那个内容,同时添加一个逗号，同时置var为新值
                    tmp[tmpnum]=var;
                    tmpnum++;
                    BreakNum=0;
                    tmpsign[tmpsignnum]=Comma;
                    tmpsignnum++;
                    tmp[tmpnum]=*(pAddr+ii);//添加一个新值
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


// 画 提示坐标：
void dw_devScan_coordinate_p061(void)
{
    //显示文字信息
//    dw_info_text_axis();
    // 画坐标轴：
    dw_devScan_axis_p061();
//    dw_devScan_axis();

    // 画地址定位：
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
* 页面: // 显示 模拟量曲线
*  _回路_ _ _地址: _ _ _ (显示当前值)
* |
* |_________________________>
* 把当前值用一个点显示，高度对应值的大小，最大128.
* 每得到一个新的值，X轴向上右移一个显示位置；若满，从左侧开始刷新，同时把其右侧16个像素清掉；
* 看效果，视觉上不舒服可以改，比如每次得到值，用横向2个像素表示；
******************************************************************************/
void show_Simulated_curves(funpara* para)
{

    U8 interval;
    U8 endrow;
    U8 startrow;
    U8 Remainder;
    static U8 seqnum=0;//表示坐标的顺序
    static U8 iy=0;
    para->val++;
    para->val=para->val>127?1:para->val;
//    para->val=58;
    if(para->firstentry)//如果为第一次，相关的内容需要重新置位。
    {
        iy=0;
        seqnum=0;
        para->firstentry=FALSE;
    }
    (void)para;
    //    yval_p061[0];
    endrow=yval_p061[6]+8;//not change
    startrow=yval_p061[0];
    interval=endrow-startrow;//间隔值

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





    //    showVLine(startrow,endrow,iy);//竖线的方式表示
//    showVLine(startrow,startrow+1,iy);//点的方式表示
    showHLine(startrow,iy,iy+3);

    iy+=5;
    //    LcdSw_HvLine(0, iy,
    //                 63, iy);

    //        ClrWindow_Page();
    //清除左边16个像素
    if(32==seqnum){
        seqnum=0;
        iy=0;
        //        ClrWindow_Page();
        //显示与初始化界面相类似的内容
        LcdSw_ClrRectangle(0,U_DevScan_Pix_X_Start_p061+5,
                           endrow,U_DevScan_Pix_X_Start_p061+5*17);
        ShowXYCodeCharRL(0,2,1,"_回路___地址",FALSE);
        ShowXY_Fig_Pre0(0,2,1,para->TotalCall->inputFig[0],1);
        ShowXY_Fig_Pre0(0,4,2,para->TotalCall->inputFig[1],1);
        ShowXY_Fig_Pre0(0,4,3,para->TotalCall->inputFig[2],1);
        ShowXY_Fig_Pre0(0,4,4,para->TotalCall->inputFig[3],1);
        //        ShowXYCodeCharRL(0,2,1,"_回路___地址",FALSE);
        //        ShowXYCodeCharRL(0,2,1,"_回路___地址",FALSE);
        //        ClrWindow_Page();
        //清空左边16个

    }else if(16==seqnum){//清除右边16个像素
        LcdSw_ClrRectangle(0,U_DevScan_Pix_X_Start_p061+5*17,
                           endrow,U_DevScan_Pix_X_Start_p061+5*33);
        ShowXYCodeCharRL(0,2,1,"_回路___地址",FALSE);
        ShowXY_Fig_Pre0(0,2,1,para->TotalCall->inputFig[0],1);
        ShowXY_Fig_Pre0(0,4,2,para->TotalCall->inputFig[1],1);
        ShowXY_Fig_Pre0(0,4,3,para->TotalCall->inputFig[2],1);
        ShowXY_Fig_Pre0(0,4,4,para->TotalCall->inputFig[3],1);
    }
}



//
/******************************************************************************
* 页面: // 回路浏览
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
//显示横线
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
