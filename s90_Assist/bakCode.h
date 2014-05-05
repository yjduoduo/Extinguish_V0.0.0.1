

#include  "can20_FileRxManage.h"


/*================= 公有函数声明-lib外部 ====================================*/
//EX_can20_FileRxManage 

//main流程里，将intr里收到的文件帧，组织为文件：
extern void CanFrmRx_toFile(void);