/* ============================================================
   ptr_array.c —— 指针与数组（教材 7.3）
   重点：指针的算术运算 —— p+1 不是"地址加1"，而是"往后挪一个元素"
   ============================================================ */
#include <stdio.h>
#include <stddef.h>   /* ptrdiff_t: 专门用来装"两个指针之差" */
#include <stdint.h>   /* intptr_t:  专门用来装"指针转成的整数" */
#include "utf8_console.h"   /* 让中文正常显示，详见该文件里的说明 */

int main(void)
{
    enable_utf8_console();   /* 打印中文之前，先把控制台切成 UTF-8 */

    int a[5] = {10, 20, 30, 40, 50};
    int *p = a;          /* 数组名 a 就是首元素地址，等于 &a[0] */
    int i;

    /* ---------- 1. 三种写法，完全等价 ---------- */
    printf("=== 1. 三种等价的写法 ===\n");
    printf("a[0]   = %d\n", a[0]);
    printf("*p     = %d\n", *p);
    printf("*(a+0) = %d\n", *(a + 0));
    printf("*(p+0) = %d\n", *(p + 0));

    /* ---------- 2. 指针的算术运算：p+1 挪多远？ ---------- */
    printf("\n=== 2. p+1 到底挪了多少字节 ===\n");
    printf("p     = %p\n", (void *)p);
    printf("p + 1 = %p\n", (void *)(p + 1));
    printf("p + 2 = %p\n", (void *)(p + 2));
    printf("字节差 (long)(p+1)-(long)p = %ld  (真正的字节差)\n", (long)((intptr_t)(p + 1) - (intptr_t)p));
    printf("元素差 (p+1)-p             = %ld  (元素个数)\n", (long)(ptrdiff_t)((p + 1) - p));
    printf("sizeof(int)  = %u 字节\n", (unsigned)sizeof(int));
    printf("=> p+1 挪了 4 个字节, 但元素差只算 1 个 —— 两回事!\n");

    /* ---------- 3. 用指针访问每个元素 ---------- */
    printf("\n=== 3. 用 *(p+i) 访问每个元素 ===\n");
    for (i = 0; i < 5; i++) {
        printf("*(p+%d) = %d   (地址 %p)\n", i, *(p + i), (void *)(p + i));
    }

    /* ---------- 4. 数组名和指针的区别 ---------- */
    printf("\n=== 4. 数组名 != 指针（sizeof 露馅）===\n");
    printf("sizeof(a) = %u  (整个数组: 5 * 4 = 20)\n", (unsigned)sizeof(a));
    printf("sizeof(p) = %u  (只是一个指针)\n", (unsigned)sizeof(p));

    /* ---------- 5. 指针自己会走 ---------- */
    printf("\n=== 5. 让指针自己往后走 ===\n");
    p = a;                       /* 重新指回开头 */
    for (i = 0; i < 5; i++) {
        printf("第%d次: *p = %2d, 然后 p++\n", i + 1, *p);
        p++;                     /* 指针往后挪一个元素 */
    }
    printf("走完后 p 指向第 %ld 个元素之后\n", (long)(ptrdiff_t)(p - a));

    /* ---------- 6. 指针相减：算出元素个数 ---------- */
    printf("\n=== 6. 两个指针相减 = 相差几个元素 ===\n");
    {
        int *q = &a[0];
        int *r = &a[4];
        printf("&a[4] - &a[0] = %ld  (元素个数，不是字节数)\n", (long)(ptrdiff_t)(r - q));
    }

    return 0;
}
