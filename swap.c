/* 笔记章节：Pointer · 11 → 「函数传地址：swap」 */
#include <stdio.h>
#include "utf8_console.h"   /* 让中文正常显示，详见该文件里的说明 */

void swap(int *x, int *y) {
    int t = *x;
    *x = *y;
    *y = t;
}

int main(void) {
    enable_utf8_console();   /* 打印中文之前，先把控制台切成 UTF-8 */
    int a = 3, b = 5;

    printf("交换前: a = %d, b = %d\n", a, b);
    swap(&a, &b);
    printf("交换后: a = %d, b = %d   （笔记预期 5 3）\n", a, b);
    return 0;
}
