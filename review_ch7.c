/* ============================================================
   review_ch7.c —— 第七章「指针」综合复习自测（7.1 - 7.5）
   
   用法：
     1. 先看「题目」，自己写下答案
     2. 再往下看「答案与解析」
     3. 全部跑通后，第七章就真的过了

   覆盖：地址与指针 / 指针运算 / 指针与数组 / 指针与函数 / 指针与字符串
   ============================================================ */
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdint.h>
#include "utf8_console.h"

/* ============================================================
   第 4 部分要用到的函数
   ============================================================ */
int  sum_array(int arr[], int n)
{
    int i, t = 0;
    for (i = 0; i < n; i++) t += arr[i];
    return t;
}

int  wrong_length(int arr[])          /* ⚠️ 故意写错，用来演示陷阱 */
{
    return (int)(sizeof(arr) / sizeof(arr[0]));
}

void max_min(int arr[], int n, int *out_max, int *out_min)
{
    int i;
    *out_max = *out_min = arr[0];
    for (i = 1; i < n; i++) {
        if (arr[i] > *out_max) *out_max = arr[i];
        if (arr[i] < *out_min) *out_min = arr[i];
    }
}

int my_strlen(const char *s)          /* 用指针自己实现 strlen */
{
    const char *q = s;
    while (*q) q++;
    return (int)(q - s);
}

int main(void)
{
    enable_utf8_console();

    /* ==========================================================
       题 目 区
       ========================================================== */
    printf("############################################################\n");
    printf("#       第七章「指针」综合复习自测（7.1 - 7.5）            #\n");
    printf("############################################################\n\n");
    printf("【怎么用】先自己写下答案, 再往下看解析对照。\n");
    printf("          猜错的地方才是真正要补的。\n\n");

    printf("========== 第 1 组：地址与指针（7.1 / 7.2）==========\n");
    printf("  int a = 7;  int *p = &a;\n");
    printf("  1-1  p 里装的是什么?          ______\n");
    printf("  1-2  *p 是什么?               ______\n");
    printf("  1-3  &p 是什么?               ______\n");
    printf("  1-4  &a 和 p 相等吗?          ______\n");
    printf("  1-5  *p = 100; 之后 a 是多少? ______\n");

    printf("\n========== 第 2 组：指针运算（7.2 / 7.3）==========\n");
    printf("  int b[4] = {100, 200, 300, 400};  int *q = b;\n");
    printf("  2-1  *(q + 2) = ?             ______\n");
    printf("  2-2  q + 2 比 q 多几个字节?   ______\n");
    printf("  2-3  (q+2) - q 等于几?        ______\n");
    printf("  2-4  sizeof(int) 是多少?      ______\n");
    printf("  2-5  任何指针占几个字节?      ______\n");

    printf("\n========== 第 3 组：数组 vs 指针（7.3）==========\n");
    printf("  int c[5] = {1,2,3,4,5};  int *r = c;\n");
    printf("  3-1  sizeof(c) = ?            ______\n");
    printf("  3-2  sizeof(r) = ?            ______\n");
    printf("  3-3  sizeof(c)/sizeof(c[0]) = ? ______\n");
    printf("  3-4  2[c] 合法吗? 值是多少?   ______\n");
    printf("  3-5  数组名什么时候不退化成指针? ______\n");

    printf("\n========== 第 4 组：指针与函数（7.4）==========\n");
    printf("  4-1  数组传进函数后 sizeof(arr) = ? ______\n");
    printf("  4-2  所以函数里能算出数组长度吗?  ______\n");
    printf("  4-3  int arr[] 和 int *arr 作参数有区别吗? ______\n");
    printf("  4-4  想让函数改外面的 int, 要传什么? ______\n");
    printf("  4-5  int *f(void){int x=5; return &x;} 有问题吗? ______\n");

    printf("\n========== 第 5 组：指针与字符串（7.5）==========\n");
    printf("  char s1[] = \"cat\";   char *s2 = \"cat\";\n");
    printf("  5-1  sizeof(s1) = ?  sizeof(s2) = ?   ______\n");
    printf("  5-2  s1[0]='C' 能跑吗? s2[0]='C' 呢?  ______\n");
    printf("  5-3  printf(\"%%s\", *s2) 对吗?         ______\n");
    printf("  5-4  strlen(\"cat\") = ?              ______\n");
    printf("  5-5  p = s1 和 strcpy(d,s1) 有什么区别? ______\n");

    printf("\n\n");
    printf("############################################################\n");
    printf("#                      答 案 与 解 析                      #\n");
    printf("############################################################\n\n");

    /* ==========================================================
       解 析 区
       ========================================================== */

    /* ---------- 第 1 组 ---------- */
    printf("========== 第 1 组：地址与指针 ==========\n");
    {
        int a = 7;
        int *p = &a;
        printf("  实测: a=%d  &a=%p  p=%p  *p=%d  &p=%p\n",
               a, (void *)&a, (void *)p, *p, (void *)&p);
        printf("\n  1-1  p 里装的是【a 的地址】—— 一张写着门牌号的纸条\n");
        printf("  1-2  *p 是【a 的值】= %d —— 顺着纸条找到房间, 看里面的东西\n", *p);
        printf("  1-3  &p 是【p 自己的地址】—— 纸条放在哪\n");
        printf("  1-4  相等。因为 p = &a, 抄的就是 a 的门牌: %s\n",
               (&a == p) ? "相同" : "不同");
        *p = 100;
        printf("  1-5  a = %d —— 改的是 *p, 变的是 a\n", a);
        printf("  >>> 口诀: & 问路, * 进门\n");
        a = 7;   /* 恢复 */
    }

    /* ---------- 第 2 组 ---------- */
    printf("\n========== 第 2 组：指针运算 ==========\n");
    {
        int b[4] = {100, 200, 300, 400};
        int *q = b;
        printf("  实测: *(q+2)=%d   q=%p  q+2=%p\n",
               *(q + 2), (void *)q, (void *)(q + 2));
        printf("        字节差=%ld   元素差=%ld\n",
               (long)((intptr_t)(q + 2) - (intptr_t)q), (long)(ptrdiff_t)((q + 2) - q));
        printf("\n  2-1  *(q+2) = 300  (就是 b[2])\n");
        printf("  2-2  8 字节 —— 2 个元素 x sizeof(int)=4\n");
        printf("  2-3  2 —— 指针相减得到的是【元素个数】, 不是字节数\n");
        printf("  2-4  sizeof(int) = %u\n", (unsigned)sizeof(int));
        printf("  2-5  %u 字节 —— 只和系统位数有关(64 位), 与指向类型无关\n",
               (unsigned)sizeof(void *));
        printf("  >>> 核心: 字节差 = 元素差 x sizeof(元素类型)\n");
    }

    /* ---------- 第 3 组 ---------- */
    printf("\n========== 第 3 组：数组 vs 指针 ==========\n");
    {
        int c[5] = {1, 2, 3, 4, 5};
        int *r = c;
        printf("  实测: sizeof(c)=%u  sizeof(r)=%u  sizeof(c)/sizeof(c[0])=%u\n",
               (unsigned)sizeof(c), (unsigned)sizeof(r),
               (unsigned)(sizeof(c) / sizeof(c[0])));
        printf("        c[2]=%d  *(c+2)=%d  2[c]=%d\n", c[2], *(c + 2), 2 [c]);
        printf("\n  3-1  sizeof(c) = 20   (5 x 4, 整个数组)\n");
        printf("  3-2  sizeof(r) = 8    (只是个指针)\n");
        printf("  3-3  20/4 = 5  —— 这就是\"自动数元素个数\"的写法\n");
        printf("  3-4  合法, 值是 3。理由: c[2] ≡ *(c+2) ≡ *(2+c) ≡ 2[c]\n");
        printf("       加法交换律 + [] 只是 *() 的语法糖 => 顺序无关\n");
        printf("       ⚠️ 但别这么写!\n");
        printf("  3-5  只有两种场合不退化: sizeof(数组名)  和  &数组名\n");
        printf("  >>> 铁证: sizeof(c)=20 而 sizeof(r)=8\n");
    }

    /* ---------- 第 4 组 ---------- */
    printf("\n========== 第 4 组：指针与函数 ==========\n");
    {
        int d[5] = {10, 20, 30, 40, 50};
        int n = (int)(sizeof(d) / sizeof(d[0]));
        int mx, mn;
        printf("  实测: main 里 sizeof(d)=%u\n", (unsigned)sizeof(d));
        printf("        sum_array(d,5) = %d\n", sum_array(d, n));
        printf("        wrong_length(d) = %d   <-- 不是 5!\n", wrong_length(d));
        max_min(d, n, &mx, &mn);
        printf("        max_min 带回: max=%d min=%d\n", mx, mn);
        printf("        my_strlen(\"hello\") = %d\n", my_strlen("hello"));
        printf("\n  4-1  sizeof(arr) = 8 —— 数组作参数会【退化】成指针\n");
        printf("  4-2  不能! 长度信息丢了。wrong_length 算出的 8/4=2 就是错的\n");
        printf("  4-3  没区别, 完全等价。推荐写 int arr[], 语义更清楚\n");
        printf("  4-4  传【地址】int *, 函数里用 *p = ... 改\n");
        printf("       想改 int * 本身, 则要传 int ** (二级指针)\n");
        printf("  4-5  有问题! 局部变量在栈上, 函数返回后内存被回收\n");
        printf("       返回它的地址 = 【野指针/悬空指针】\n");
        printf("       gcc 会警告: returns address of local variable\n");
        printf("       正确做法: 用 static / 让调用者提供数组 / 用 malloc\n");
        printf("  >>> 对比: size 用 return 带回, 平均用指针带回 —— 一函数多返回值\n");
    }

    /* ---------- 第 5 组 ---------- */
    printf("\n========== 第 5 组：指针与字符串 ==========\n");
    {
        char s1[] = "cat";
        char *s2 = "cat";
        char buf[20];
        char *sp;
        printf("  实测: sizeof(s1)=%u  sizeof(s2)=%u\n",
               (unsigned)sizeof(s1), (unsigned)sizeof(s2));
        printf("        s1 地址=%p (栈)   s2 指向=%p (只读区)\n",
               (void *)s1, (void *)s2);
        printf("        strlen(\"cat\")=%u\n", (unsigned)strlen("cat"));
        s1[0] = 'C';
        printf("        s1[0]='C' 之后 s1=\"%s\"  (数组能改)\n", s1);
        strcpy(buf, "cat");
        sp = buf;
        sp[0] = 'C';
        printf("        sp=buf 后改 sp[0], buf=\"%s\"  (指同一块地, 一起变)\n", buf);
        printf("\n  5-1  sizeof(s1)=4 (c,a,t,+'\\0')   sizeof(s2)=8 (只是个指针)\n");
        printf("  5-2  s1[0]='C' 能跑(改自己的栈数组)\n");
        printf("       s2[0]='C' 崩溃! 字面量在只读区, 写它 = Segmentation fault\n");
        printf("  5-3  错! %%s 要的是【地址】, *s2 是一个字符 'c'\n");
        printf("       正确: printf(\"%%s\", s2);  或 printf(\"%%c\", *s2);\n");
        printf("  5-4  3 —— strlen 不数结尾的 '\\0'\n");
        printf("  5-5  p = s1   复制【地址】-> 两个指针指向同一块, 改一个都变\n");
        printf("       strcpy(d,s1) 复制【内容】-> 两块独立内存, 互不影响\n");
        printf("  >>> 这和 7.4 的\"传值 vs 传地址\"是同一个思想\n");
    }

    /* ==========================================================
       总 结
       ========================================================== */
    printf("\n\n############################################################\n");
    printf("#                      第 七 章 核 心                       #\n");
    printf("############################################################\n\n");
    printf("  ① p 是地址, *p 是值, &p 是 p 自己的地址       (& 问路, * 进门)\n");
    printf("  ② p + i 往后挪 i 个【元素】\n");
    printf("     字节差 = 元素差 x sizeof(类型)\n");
    printf("  ③ a[i] ≡ *(a+i) ≡ 2[a]        ([] 只是 *() 的语法糖)\n");
    printf("  ④ sizeof(数组) = 整个数组;  sizeof(指针) = 8\n");
    printf("     数组作函数参数会【退化】成指针, 长度必须另外传\n");
    printf("  ⑤ 字符串 = 字符数组 + '\\0'\n");
    printf("     char s[] 可改,  char *p = \"...\" 不可改(只读区)\n");
    printf("  ⑥ 想让函数改外面的东西, 就传它的地址\n");
    printf("     不要返回局部变量的地址(野指针)\n");
    printf("  ⑦ 各类型字节数: char 1 / int 4 / double 8 / 任何指针 8\n\n");
    printf("  ★ 全对 = 第七章过关。有错就回去看对应的讲义那一节。\n\n");

    return 0;
}
