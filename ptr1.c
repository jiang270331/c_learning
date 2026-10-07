/* 笔记章节：Pointer · 06 → 「第一段能跑的指针程序」 */
#include <stdio.h>
#include "utf8_console.h"   /* 让中文正常显示，详见该文件里的说明 */

int main(void) {
    enable_utf8_console();   /* 打印中文之前，先把控制台切成 UTF-8 */

    int a = 999;
    int *p = &a;

    printf("a 的值 = %d\n", a);
    printf("a 的地址 = %p\n", (void*)&a);
    printf("p 里的地址 = %p\n", (void*)p);
    printf("*p = %d\n", *p);

    *p = 20;
    printf("修改后 a = %d\n", a);
    printf("修改后 *p = %d\n", *p);
    return 0;
}
