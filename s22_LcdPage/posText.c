#include "posText.h"

//���λ��
const U8* nulT[1]={""};
const U8* nulArray[5]={"","","","",""};
const U8 cstpos_p010[4]={1,6,7,8};//p010cursor��λ��
const U8 cstpos_p061[4]={5,10,11,12};
const U8 cstpos_p060[1]={6};//��λ��
const U8 cstpos_p062[1]={1};
const U8 cstpos_p030[12]={26,
                          9,15,22,29,
                          5,19,
                          16,17,
                          17,18,19
                         };
const U8 cstpos_p058[1]={3};
const U8 cstpos_p024[4]={11,12,25,26};
const U8 cstpos_p027[10]={1,2,5,6,11,12,13,21,22,23};
const U8 cstpos_p083[9]={10,11,12,
                        10,11,12,
                        10,11,12};
//������ ʱ����
#define START013 4
const U8 cstpos_p013[12]={START013,
                          START013+1,
                          START013+2+2,
                          START013+2+2+1,
                          START013+2+2+2+2,
                          START013+2+2+2+2+1,
                          START013+2+2+2+2+2+2,
                          START013+2+2+2+2+2+2+1,
                          START013+2+2+2+2+2+2+2+2,
                          START013+2+2+2+2+2+2+2+2+1,
                          START013+2+2+2+2+2+2+2+2+2+2,
                          START013+2+2+2+2+2+2+2+2+2+2+1
                         };

#define START017 10
const U8 cstpos_p017[5]={START017,START017+5,START017+6,START017+7,
                         START017+12};//p010cursor��λ��
//const U8 cstpos_pnull[0]={};//��λ��
const U8* looptext[1]={"_��·"};
const U8* addrtext[1]={"___��ַ"};
const U8* typetext[1]={"_����"};
const U8* handleregtext[5]={"1̽��","2����","3��ͣ��ť","4���Զ���","5����"};
const U8* registerorshit[3]={"1.�Ǽ�","2.ȡ��","1.����"};
const U8* timedatetext[1]={"20__��__��__��__ʱ__��__��"};




//�������ģ�Ӣ�ģ���������ԣ�ͬʱ���й��λ�õ���Ϣ
typedef struct TextCursorPosSets{
    const U8* CNText[5];//����
    const U8* ENText[5];//Ӣ��
    const U8* CPText[5];//����
    U8 cursorColPos[12];
    U8 cursorRowPos[5];

}TextCursorPosSets;


TextCursorPosSets ActTextPos[1]=
{
    {"","","",{0},{0}}

};










