#ifndef POSTEXT_H
#define POSTEXT_H
#include "prjDataType.h"

#define POSTEXT_EX
#ifdef POSTEXT_EX
#define EXT extern
#else
#define EXT
#endif

//定义文字部分内容
EXT const U8 cstpos_p010[4];//p010cursor列位置
EXT const U8 cstpos_p061[4];//p010cursor列位置
EXT const U8 cstpos_p083[9];//p010cursor列位置
EXT const U8 cstpos_p060[1];//列位置
EXT const U8 cstpos_p058[1];//列位置
EXT const U8 cstpos_p062[1];//列位置
EXT const U8 cstpos_p024[4];
EXT const U8 cstpos_p027[10];
EXT const U8 cstpos_p017[5];//p010cursor列位置
EXT const U8 cstpos_p013[12];
EXT const U8 cstpos_p030[12];//灭火区光标跳动位置
EXT const U8* looptext[1];
EXT const U8* addrtext[1];
EXT const U8* typetext[1];
EXT const U8* handleregtext[5];
EXT const U8* registerorshit[3];//登记或屏蔽或取消
EXT const U8* timedatetext[1];//日期和时间
EXT const U8* nulT[1];
EXT const U8* nulArray[5];



typedef struct TextCursorPosSets TextCursorPosSets;


#endif // POSTEXT_H
