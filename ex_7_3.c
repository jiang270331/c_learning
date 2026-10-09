/* ============================================================
   ex_7_3.c —— 教材 7.3 练习：验证 4 道题
   ============================================================ */
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include "utf8_console.h"

int main(void)
{
    enable_utf8_console();

    int b[4] = {100, 200, 300, 400};
    int *q = b;

    printf("原始数组: b[4] = {100, 200, 300, 400}\n\n");

    printf("========== ① *(q + 2) ==========\n");
    printf("*(q + 2) = %d\n", *(q + 2));
    printf("b[2]     = %d   <-- 同一个东西\n", b[2]);

    printf("\n========== ② q+2 比 q 多几个字节 ==========\n");
    printf("q     = %p\n", (void *)q);
    printf("q + 2 = %p\n", (void *)(q + 2));
    printf("字节差 = %ld 字节\n", (long)((intptr_t)(q + 2) - (intptr_t)q));
    printf("算法: 2 个元素 x sizeof(int)=%u = %u 字节\n",
           (unsigned)sizeof(int), (unsigned)(2 * sizeof(int)));

    printf("\n========== ③ sizeof(b) 和 sizeof(q) ==========\n");
    printf("sizeof(b) = %u   <-- 整个数组: 4 个 int x 4 = 16\n",
           (unsigned)sizeof(b));
    printf("sizeof(q) = %u   <-- 只是个指针 (64位系统固定 8)\n",
           (unsigned)sizeof(q));
    printf("对照上一题: int a[5] -> sizeof(a)=20;  int *p -> sizeof(p)=8\n");

    printf("\n========== ④ sizeof(b) / sizeof(b[0]) ==========\n");
    printf("sizeof(b)    = %u\n", (unsigned)sizeof(b));
    printf("sizeof(b[0]) = %u\n", (unsigned)sizeof(b[0]));
    printf("%u / %u = %u\n",
           (unsigned)sizeof(b), (unsigned)sizeof(b[0]),
           (unsigned)(sizeof(b) / sizeof(b[0])));
    printf("=> 这个写法的用途: 自动算出数组元素个数\n");
    printf("   b 是 4 个元素, 所以答案是 4 —— 不是 1!\n");

    printf("\n========== 复习: 下标 vs 字节 ==========\n");
    printf("sizeof(b[0]) 问的是「一个元素多大」= %u 字节\n", (unsigned)sizeof(b[0]));
    printf("sizeof(b)    问的是「整个数组多大」= %u 字节\n", (unsigned)sizeof(b));
    printf("sizeof(b)/sizeof(b[0]) 问的是「有几个元素」= %u 个\n",
           (unsigned)(sizeof(b) / sizeof(b[0])));

    return 0;
}
