/* 笔记章节：Cursor · Windows → 「Windows：在 Cursor 里运行 C」 */
#include <stdio.h>
#include "utf8_console.h"   /* 让中文正常显示，详见该文件里的说明 */

int main(void)
 {
    enable_utf8_console();   /* 打印中文之前，先把控制台切成 UTF-8 */
    printf("Hello,worlds!\n");
    return 0;
}


