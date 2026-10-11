/* ============================================================
   sort3.c —— 指针练习：三个整数从小到大排序

   题目要求：
     1. 写 void swap(int *x, int *y)
     2. 写 void sort3(int *a, int *b, int *c)，只能通过调用 swap 来交换
     3. main 里输入三个数，输出一行，中间一个空格
     4. main 里不要自己写临时变量来交换

   思路（关键）：不要想"怎么排序"，只想"哪两个不对就换哪两个"
     三个数从小到大 = 保证 a <= b <= c
     所以只要检查三对：
        如果 *a > *b  ->  swap(a, b)
        如果 *a > *c  ->  swap(a, c)
        如果 *b > *c  ->  swap(b, c)
     三对都检查完，顺序必然正确。
   ============================================================ */
#include <stdio.h>
#include "utf8_console.h"

/* 交换两个整数：必须传地址，否则改不到外面 */
void swap(int *x, int *y)
{
    int t = *x;
    *x = *y;
    *y = t;
}

/* 三个数排序：只通过 swap 来交换，不直接赋值 */
void sort3(int *a, int *b, int *c)
{
    /* 第一轮：把最小的送到 *a */
    if (*a > *b) {
        swap(a, b);
    }
    /* 第二轮：保证 *a 是三者最小（和 *c 再比一次） */
    if (*a > *c) {
        swap(a, c);
    }
    /* 第三轮：此时 *a 已最小，只需把 *b、*c 排好 */
    if (*b > *c) {
        swap(b, c);
    }
}

/* 测试辅助：把三个数排序后打印，并检查结果是否正确 */
static int check(int x, int y, int z)
{
    int a = x, b = y, c = z;
    sort3(&a, &b, &c);
    printf("  输入 %3d %3d %3d  ->  输出 %3d %3d %3d", x, y, z, a, b, c);

    /* 校验：必须递增，且三个数就是原来的三个（不多不少） */
    int sorted_ok = (a <= b && b <= c);
    int sum_ok = (a + b + c == x + y + z);
    /* 简单校验元素一致：三个数和相等 + 递增，对本题足够 */
    if (sorted_ok && sum_ok) {
        printf("   OK\n");
        return 1;
    }
    printf("   X 错误!\n");
    return 0;
}

int main(void)
{
    enable_utf8_console();

    printf("==================================================\n");
    printf("第 1 题：三个整数从小到大（用 swap + sort3）\n");
    printf("==================================================\n\n");

    printf("题目给的两个样例：\n");
    check(3, 1, 2);      /* 样例1：期望 1 2 3 */
    check(9, 9, 1);      /* 样例2：期望 1 9 9 */

    printf("\n再测一些容易出错的情况：\n");
    check(1, 2, 3);      /* 已经有序，不该乱动 */
    check(3, 2, 1);      /* 完全逆序 */
    check(2, 3, 1);      /* 中间情况 */
    check(1, 3, 2);
    check(2, 1, 3);
    check(5, 5, 5);      /* 全相等 */
    check(-1, -5, 3);    /* 有负数 */
    check(0, -0, 0);
    check(100, 1, 50);
    check(1, 1, 0);      /* 有重复 + 最小值在最后 */

    printf("\n==================================================\n");
    printf("正式做题时 main 只要这样写：\n");
    printf("==================================================\n");
    printf("    int a, b, c;\n");
    printf("    scanf(\"%%d %%d %%d\", &a, &b, &c);\n");
    printf("    sort3(&a, &b, &c);\n");
    printf("    printf(\"%%d %%d %%d\\n\", a, b, c);\n");
    printf("\n（注意 sort3 传的是 &a &b &c，不是 a b c）\n");

    return 0;
}
