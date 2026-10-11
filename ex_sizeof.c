/* ============================================================
   ex_sizeof.c —— 数组 vs 指针：sizeof 预测自测

   你上次在 ex_7_3 里答错的两道题就是 sizeof：
       sizeof(b) 答成 4        （那是一个元素）
       sizeof(b)/sizeof(b[0]) 答成 1

   这个程序专练这个点。

   【怎么用】
     1. 下面每题有一个 #define，把你自己预测的数字填进去
     2. 编译运行：  .\b ex_sizeof
     3. 它会自动批改，告诉你哪题错了

   【核心提醒】sizeof 只看两件事：
       · 括号里是「数组名」还是「指针」
       · 那个类型占几个字节
     数组名 -> 整个数组的大小
     指针   -> 永远是指针本身的大小（本机 8）
   ============================================================ */
#include <stdio.h>
#include "utf8_console.h"

/* ============================================================
   ↓↓↓ 把你的预测填在等号后面（把 -1 改掉）↓↓↓

   已知：本机 sizeof(int)=4  sizeof(char)=1  sizeof(double)=8  任何指针=8

   预备变量：
       int     ai[5] = {1,2,3,4,5};
       int    *pi    = ai;
       char    ac[6] = "hello";
       char   *pc    = ac;
       double  ad[3];
       double *pd    = ad;
   ============================================================ */

#define A1  -1   /* 题 1  sizeof(ai)      —— 5 个 int 的数组 */
#define A2  -1   /* 题 2  sizeof(pi)      —— 指向 int 的指针 */
#define A3  -1   /* 题 3  sizeof(ai[0])   —— 一个 int 元素 */
#define A4  -1   /* 题 4  sizeof(ai)/sizeof(ai[0])  —— 元素个数 */
#define A5  -1   /* 题 5  sizeof(ac)      —— char[6]="hello"，注意结尾 */
#define A6  -1   /* 题 6  sizeof(pc)      —— 指向 char 的指针 */
#define A7  -1   /* 题 7  sizeof(ad)      —— 3 个 double 的数组 */
#define A8  -1   /* 题 8  sizeof(pd)      —— 指向 double 的指针 */
#define A9  -1   /* 题 9  sizeof(int*) 和 sizeof(char*) 相等吗？相等填 1，不等填 0 */
#define A10 -1   /* 题 10 函数里 void f(int arr[]) 的 sizeof(arr) 是多少？ */


/* ============================================================
   ↓↓↓ 下面是批改台，不用改 ↓↓↓
   ============================================================ */

/* 模拟"数组作参数"的函数 —— 题 10 用它 */
long probe_arr_size(int arr[]);

static int passed = 0, failed = 0, skipped = 0;

static void check(const char *label, long ans, long mine)
{
    if (mine < 0) {
        printf("  [未作答] %-42s 正确答案 = %ld\n", label, ans);
        skipped++;
    } else if (mine == ans) {
        printf("  [正确]   %-42s = %ld\n", label, mine);
        passed++;
    } else {
        printf("  [错误]   %-42s 你答 %ld，正确答案 %ld\n", label, mine, ans);
        failed++;
    }
}

int main(void)
{
    enable_utf8_console();

    int     ai[5] = {1, 2, 3, 4, 5};
    int    *pi    = ai;
    char    ac[6] = "hello";
    char   *pc    = ac;
    double  ad[3];
    double *pd    = ad;

    printf("############################################################\n");
    printf("#        数组 vs 指针：sizeof 预测自测                     #\n");
    printf("############################################################\n\n");

    printf("本机基础: sizeof(int)=%u  sizeof(char)=%u  sizeof(double)=%u  指针=%u\n\n",
           (unsigned)sizeof(int), (unsigned)sizeof(char),
           (unsigned)sizeof(double), (unsigned)sizeof(void *));

    /* ---- 逐题批改：答案写成字面值，避免"拿实际值当答案"这种假批改 ---- */
    check("题 1  sizeof(ai)   5 个 int",          20, A1);
    check("题 2  sizeof(pi)   指针",               8, A2);
    check("题 3  sizeof(ai[0])  一个 int",         4, A3);
    check("题 4  sizeof(ai)/sizeof(ai[0])",        5, A4);
    check("题 5  sizeof(ac)   char[6]=\"hello\"",  6, A5);
    check("题 6  sizeof(pc)   指针",               8, A6);
    check("题 7  sizeof(ad)   3 个 double",       24, A7);
    check("题 8  sizeof(pd)   指针",               8, A8);
    check("题 9  sizeof(int*)==sizeof(char*)",     1, A9);
    check("题 10 函数里 sizeof(arr)  (作参数)",    8, A10);

    printf("\n############################################################\n");
    printf("#  正确 %d 项，错误 %d 项，未作答 %d 项\n", passed, failed, skipped);
    if (skipped == 10) {
        printf("#  你还没填答案 —— 把上面的 #define 改了再跑一次。\n");
    } else if (failed == 0 && skipped == 0) {
        printf("#  全对！sizeof 这块你过关了。\n");
    } else {
        printf("#  错的地方看下面的规律表。\n");
    }
    printf("############################################################\n");

    /* ---- 用真实变量再打一遍，交叉验证上面的字面值没写错 ---- */
    printf("\n========== 真实变量实测（交叉验证）==========\n");
    printf("  int     ai[5]   sizeof = %2u   期望 20\n", (unsigned)sizeof(ai));
    printf("  int    *pi      sizeof = %2u   期望 8\n",  (unsigned)sizeof(pi));
    printf("  char    ac[6]   sizeof = %2u   期望 6\n",  (unsigned)sizeof(ac));
    printf("  char   *pc      sizeof = %2u   期望 8\n",  (unsigned)sizeof(pc));
    printf("  double  ad[3]   sizeof = %2u   期望 24\n", (unsigned)sizeof(ad));
    printf("  double *pd      sizeof = %2u   期望 8\n",  (unsigned)sizeof(pd));
    printf("  sizeof(int*)==sizeof(char*) -> %ld   期望 1\n",
           (long)(sizeof(int *) == sizeof(char *)));
    printf("  函数里 sizeof(arr) -> %ld   期望 8\n", probe_arr_size(ai));

    printf("\n========== 规律（背下来）==========\n");
    printf("  sizeof(数组名) = 元素个数 x 单个元素大小    <- 整个数组\n");
    printf("  sizeof(指针)   = 8                          <- 和指向什么无关\n");
    printf("  sizeof(a)/sizeof(a[0]) = 元素个数\n\n");
    printf("  ⚠️ 两个最容易错的:\n");
    printf("     sizeof(\"hello\" 的数组) 是 6 不是 5 —— 结尾还有个 '\\0'\n");
    printf("     函数里 sizeof(arr) 是 8 不是 20/24 —— 数组作参数会退化成指针\n");

    return (failed == 0 && skipped == 0) ? 0 : 1;
}

/* 数组作参数 —— 这里的 sizeof 拿不到整个数组 */
long probe_arr_size(int arr[])
{
    return (long)sizeof(arr);
}
