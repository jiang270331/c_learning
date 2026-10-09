/* 笔记章节：Pointer · 15 → 「练习 B：用指针写 swap，交换两个整数」
 * 这是练习答案，也顺手演示「为什么传值做不到」。
 */
#include <stdio.h>
#include "utf8_console.h"   /* 让中文正常显示，详见该文件里的说明 */

/* 错误示范：传值，换不动外面 */
void swap_wrong(int x, int y) {
    int t = x;
    x = y;
    y = t;
    /* 函数结束时 x、y 这两个复印件就被丢掉了 */
}

/* 正确做法：传地址 */
void swap(int *x, int *y) {
    int t = *x;
    *x = *y;
    *y = t;
}

int main(void) {
    enable_utf8_console();   /* 打印中文之前，先把控制台切成 UTF-8 */

    int a = 3, b = 5;

    swap_wrong(a, b);
    printf("用传值版 swap 后：a = %d, b = %d   （没变，这就是坑）\n", a, b);

    swap(&a, &b);
    printf("用指针版 swap 后：a = %d, b = %d   （成功交换）\n", a, b);

    return 0;
}
