/* 笔记章节：Pointer · 06 → 「第一段能跑的指针程序」 */
#include <stdio.h>

int main(void) {
    int a = 10;
    int *p = &a;

    printf("a 的值 = %d\n", a);
    printf("a 的地址 = %p\n", (void*)&a);
    printf("p 里的地址 = %p\n", (void*)p);
    printf("*p = %d\n", *p);

    *p = 20;
    printf("修改后 a = %d\n", a);
    return 0;
}
