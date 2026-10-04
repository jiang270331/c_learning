/* 笔记章节：Pointer · 11 → 「函数传地址：swap」 */
#include <stdio.h>

void swap(int *x, int *y) {
    int t = *x;
    *x = *y;
    *y = t;
}

int main(void) {
    int a = 3, b = 5;

    printf("交换前: a = %d, b = %d\n", a, b);
    swap(&a, &b);
    printf("交换后: a = %d, b = %d   （笔记预期 5 3）\n", a, b);
    return 0;
}
