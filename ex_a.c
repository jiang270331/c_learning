/* 笔记章节：Pointer · 15 → 「动手练习 A（必做）」
 * 要求：
 *   1. int a = 7;
 *   2. 指针 p 指向 a
 *   3. 打印 a、&a、p、*p
 *   4. *p = 100; 后再打印 a
 */
#include <stdio.h>

int main(void) {
    int a = 7;
    int *p = &a;

    printf("a  = %d\n", a);
    printf("&a = %p\n", (void*)&a);
    printf("p  = %p\n", (void*)p);
    printf("*p = %d\n", *p);

    *p = 100;
    printf("a  = %d   （注意：改的是 *p，变的是 a）\n", a);
    return 0;
}
