/* ============================================================
   ptr_sizeof.c —— 补讲 ②④⑤ 三个点（教材 7.3 收尾）
     ②  p+3 比 p 地址上多几个字节
     ④  sizeof(a) 和 sizeof(p) 为什么不一样
     ⑤  2[a] 为什么居然合法
   ============================================================ */
#include <stdio.h>
#include <stddef.h>   /* ptrdiff_t */
#include <stdint.h>   /* intptr_t  */
#include "utf8_console.h"   /* 让中文正常显示，详见该文件里的说明 */

/* 一个函数，用来证明"数组传进来就退化成指针了" */
void show_size(int arr[])
{
    printf("  在函数里: sizeof(arr) = %u  <-- 已经不是整个数组了!\n",
           (unsigned)sizeof(arr));
}

int main(void)
{
    enable_utf8_console();   /* 打印中文之前，先把控制台切成 UTF-8 */

    int a[5] = {10, 20, 30, 40, 50};
    int *p = a;

    /* ================= ② p+3 多几个字节 ================= */
    printf("========== ② p+3 比 p 多几个字节 ==========\n");
    printf("p     = %p\n", (void *)p);
    printf("p + 3 = %p\n", (void *)(p + 3));
    printf("字节差 = %ld 字节   <-- 3 个元素 x 4 字节 = 12\n",
           (long)((intptr_t)(p + 3) - (intptr_t)p));
    printf("元素差 = %ld 个元素\n", (long)(ptrdiff_t)((p + 3) - p));
    printf("规律: 字节差 = 元素差 x sizeof(元素类型)\n");
    printf("      3 x %u = %u\n", (unsigned)sizeof(int),
           (unsigned)(3 * sizeof(int)));

    /* ================= ④ sizeof(a) vs sizeof(p) ================= */
    printf("\n========== ④ sizeof 为什么不一样 ==========\n");
    printf("sizeof(a) = %u   <-- 整个数组: 5 个 int x 4 = 20\n",
           (unsigned)sizeof(a));
    printf("sizeof(p) = %u   <-- 只是个指针变量, 装一个地址\n",
           (unsigned)sizeof(p));
    printf("元素个数 = sizeof(a) / sizeof(a[0]) = %u\n",
           (unsigned)(sizeof(a) / sizeof(a[0])));
    printf("=> 常用写法: int n = sizeof(a)/sizeof(a[0]);  自动算出长度\n");

    /* 数组名在两种场合会"退化"成指针 */
    printf("\n--- 数组名什么时候会退化成指针? ---\n");
    printf("sizeof(a)    = %u   <-- 不退化的例外之一\n", (unsigned)sizeof(a));
    printf("sizeof(a+0)  = %u   <-- 一参与运算就退化了\n",
           (unsigned)sizeof(a + 0));
    printf("&a 的地址    = %p\n", (void *)&a);
    printf("a 的地址     = %p   <-- 数值相同, 但含义不同\n", (void *)a);

    printf("\n--- 变成函数参数之后 ---\n");
    printf("调用前: sizeof(a) = %u\n", (unsigned)sizeof(a));
    show_size(a);
    printf("=> 数组作为函数参数, 传递的其实是指针, 长度信息丢失了\n");

    /* ================= ⑤ 2[a] 为什么合法 ================= */
    printf("\n========== ⑤ 2[a] 为什么合法 ==========\n");
    printf("a[2]  = %d\n", a[2]);
    printf("*(a+2)= %d\n", *(a + 2));
    printf("2[a]  = %d   <-- 居然也对!\n", 2 [a]);
    printf("*(2+a)= %d\n", *(2 + a));
    printf("\n原因: a[i] 的定义就是 *(a + i)\n");
    printf("      而加法满足交换律: a + 2  和  2 + a  完全一样\n");
    printf("      所以 *(a+2) == *(2+a), 即 a[2] == 2[a]\n");
    printf("      => 方括号 [] 只是 *( ) 的语法糖, 不要求顺序\n");
    printf("\n结论: 别这么写! 能跑不代表该写。这只说明 C 的数组下标本质是指针运算。\n");

    return 0;
}
