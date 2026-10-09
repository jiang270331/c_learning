/* ============================================================
   sizes.c —— 各种类型到底占几个字节（教材 7.3 必备基础）
   注意：C 标准不规定死字节数，只规定"至少多大"，
         所以要看具体平台。本程序打印你这台机器上的真实值。
   ============================================================ */
#include <stdio.h>
#include <stddef.h>
#include "utf8_console.h"

int main(void)
{
    enable_utf8_console();

    printf("========== 1. 基本整型 ==========\n");
    printf("char        %u 字节   范围约 -128 ~ 127\n",        (unsigned)sizeof(char));
    printf("short       %u 字节   范围约 -32768 ~ 32767\n",   (unsigned)sizeof(short));
    printf("int         %u 字节\n",                            (unsigned)sizeof(int));
    printf("long        %u 字节\n",                            (unsigned)sizeof(long));
    printf("long long   %u 字节\n",                            (unsigned)sizeof(long long));
    printf("unsigned int %u 字节\n",                           (unsigned)sizeof(unsigned int));

    printf("\n========== 2. 浮点型 ==========\n");
    printf("float       %u 字节   约 6~7 位有效数字\n",        (unsigned)sizeof(float));
    printf("double      %u 字节   约 15~16 位有效数字\n",      (unsigned)sizeof(double));
    printf("long double %u 字节\n",                            (unsigned)sizeof(long double));

    printf("\n========== 3. 字符型 ==========\n");
    printf("char        %u 字节\n",                            (unsigned)sizeof(char));
    printf("wchar_t     %u 字节   (宽字符, Windows 上是 2)\n", (unsigned)sizeof(wchar_t));

    printf("\n========== 4. 指针 —— 全部一样大! ==========\n");
    printf("char   *    %u 字节\n", (unsigned)sizeof(char *));
    printf("int    *    %u 字节\n", (unsigned)sizeof(int *));
    printf("double *    %u 字节\n", (unsigned)sizeof(double *));
    printf("void   *    %u 字节\n", (unsigned)sizeof(void *));
    printf("==> 指针大小和它指向什么类型无关, 只和系统位数有关\n");
    printf("    你这台是 64 位系统 => 地址用 8 字节表示\n");

    printf("\n========== 5. 数组 ==========\n");
    {
        int  ai[5];
        char ac[5];
        double ad[5];
        printf("int    ai[5]  %u 字节  (5 x %u)\n", (unsigned)sizeof(ai), (unsigned)sizeof(int));
        printf("char   ac[5]  %u 字节  (5 x %u)\n", (unsigned)sizeof(ac), (unsigned)sizeof(char));
        printf("double ad[5]  %u 字节  (5 x %u)\n", (unsigned)sizeof(ad), (unsigned)sizeof(double));
        printf("==> 数组大小 = 元素个数 x 单个元素大小\n");
    }

    printf("\n========== 6. 为什么指针是 8 字节 ==========\n");
    {
        int x = 42;
        int *p = &x;
        printf("变量 x 的地址 = %p\n", (void *)p);
        printf("这个地址有 %u 位十六进制数字, 每个数字 4 位\n",
               (unsigned)(sizeof(void *) * 2));
        printf("=> %u 字节 x 8 = %u 位, 所以能表示 2^%u 个地址\n",
               (unsigned)sizeof(void *), (unsigned)(sizeof(void *) * 8),
               (unsigned)(sizeof(void *) * 8));
    }

    printf("\n========== 7. 记住这几个就够了 ==========\n");
    printf("在你这台机器上 (64 位 Windows + MinGW):\n");
    printf("  char   = 1      int   = 4      double = 8\n");
    printf("  任何指针 = 8\n");
    printf("  ==> 所以 p+1 挪 4 字节 (int*), q+1 挪 1 字节 (char*)\n");

    return 0;
}
