/* ============================================================
   func_correct.c —— 数组作函数参数：正确做法对照

   起因：func_array.c 里演示了错误做法（函数里 sizeof(arr) 得到 8），
         但没有演示【正确做法】。这个文件补上。

   三组对照：
     ❌ 错法一：想在函数里算长度   -> 得到 8，不是元素个数
     ✅ 对法一：长度当参数传进来   <- 最常用、推荐
     ✅ 对法二：传"指向整个数组的指针" -> 长度藏在类型里
   外加一个实用技巧：宏 SIZEOF_ARRAY / 哨兵值约定
   ============================================================ */
#include <stdio.h>
#include "utf8_console.h"

/* 一个方便算数组长度的宏（只能用在"数组还在作用域里"的地方） */
#define SIZEOF_ARRAY(a)  ((int)(sizeof(a) / sizeof((a)[0])))

/* ============================================================
   ❌ 错法一：函数里想自己算长度
   ============================================================ */
int length_wrong(int arr[])
{
    /* arr 已经退化成指针，sizeof(arr) = 8
       8 / 4 = 2 —— 和真实元素个数毫无关系 */
    return (int)(sizeof(arr) / sizeof(arr[0]));
}

/* ============================================================
   ✅ 对法一：长度当参数传（最常用）
   ============================================================ */
int sum_with_n(int arr[], int n)      /* n 就是长度 */
{
    int i, total = 0;
    for (i = 0; i < n; i++) {
        total += arr[i];
    }
    return total;
}

/* ============================================================
   ✅ 对法二：传"指向整个数组的指针"
   类型写成 int (*arr)[N]，N 是数组长度 —— 长度藏在【类型】里
   ⚠️ 缺点：N 写死了，只能接长度为 N 的数组
   ============================================================ */
int sum_whole_array(int (*arr)[5], int n)
{
    int i, total = 0;
    /* 注意：arr 是"指向数组的指针"，要先 *arr 取出数组 */
    for (i = 0; i < n; i++) {
        total += (*arr)[i];
    }
    /* 这里 sizeof(*arr) 才是整个数组！ */
    return total;
}

/* ============================================================
   实用技巧：哨兵值约定
   用数组里一个特殊值（比如 -1）表示"到这里结束"，就不需要传长度
   ⚠️ 缺点：这个值不能出现在正常数据里
   ============================================================ */
int sum_until_sentinel(const int arr[], int sentinel)
{
    int i = 0, total = 0;
    while (arr[i] != sentinel) {
        total += arr[i];
        i++;
    }
    return total;
}

int main(void)
{
    enable_utf8_console();

    int a[5] = {10, 20, 30, 40, 50};
    int b[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    int c[3] = {100, 200, 300};
    int d[5] = {7, 14, 21, 28, -1};      /* 带哨兵 -1 */

    printf("############################################################\n");
    printf("#   数组作函数参数：错法 vs 对法（三组对照）                #\n");
    printf("############################################################\n\n");

    /* ---------- 第一组：错法 vs 对法一 ---------- */
    printf("========== 第 1 组：想在函数里算长度（错）==========\n\n");
    printf("  在 main 里（数组还在作用域内）：\n");
    printf("      sizeof(a)          = %u   (整个数组 5 x 4)\n",
           (unsigned)sizeof(a));
    printf("      sizeof(a[0])       = %u   (一个元素)\n",
           (unsigned)sizeof(a[0]));
    printf("      真实的元素个数      = %d   <- 这样算才对\n", SIZEOF_ARRAY(a));

    printf("\n  但传进函数后：\n");
    printf("      sizeof(arr)        = %u   <- 退化成指针了\n",
           (unsigned)sizeof(int *));
    printf("      函数里算出来的「长度」  = %d   <- 完全错的！\n",
           length_wrong(a));
    printf("\n  ⚠️ 这就是你上次错的那个点：\n");
    printf("     函数里 sizeof(arr) 是 8（指针大小），不是 20（整个数组）\n");
    printf("     8 / 4 = 2，和 5 个元素毫无关系\n");

    /* ---------- 第二组：对法一 ---------- */
    printf("\n========== 第 2 组：长度当参数传（✅ 推荐）==========\n\n");
    printf("  调用者在外面算好长度，传进去：\n");
    printf("      int n = SIZEOF_ARRAY(a);   // = %d\n", SIZEOF_ARRAY(a));
    printf("      sum_with_n(a, n);\n\n");
    printf("  实测：\n");
    printf("      a[5] = {10,20,30,40,50}  ->  sum_with_n(a, %d) = %d\n",
           SIZEOF_ARRAY(a), sum_with_n(a, SIZEOF_ARRAY(a)));
    printf("      b[8] = {1..8}            ->  sum_with_n(b, %d) = %d\n",
           SIZEOF_ARRAY(b), sum_with_n(b, SIZEOF_ARRAY(b)));
    printf("      c[3] = {100,200,300}     ->  sum_with_n(c, %d) = %d\n",
           SIZEOF_ARRAY(c), sum_with_n(c, SIZEOF_ARRAY(c)));
    printf("\n  ✅ 同一个函数能处理不同长度的数组 —— 这才灵活\n");

    /* ---------- 第三组：对法二 ---------- */
    printf("\n========== 第 3 组：传指向整个数组的指针（✅ 长度藏在类型里）==========\n\n");
    printf("  函数签名：int sum_whole_array(int (*arr)[5], int n)\n");
    printf("                         ↑ 这个 [5] 就是长度信息\n\n");
    printf("  实测：\n");
    printf("      sum_whole_array(&a, %d) = %d\n",
           SIZEOF_ARRAY(a), sum_whole_array(&a, SIZEOF_ARRAY(a)));
    printf("\n  函数里 sizeof(*arr) = %u  <- 这才是整个数组！\n",
           (unsigned)sizeof(int[5]));
    printf("  因为 *arr 的类型是 int[5]，不是 int*\n");
    printf("\n  ⚠️ 缺点：长度写死在类型里（[5]），只能接长度正好是 5 的数组\n");
    printf("     所以这个方法用得少，但理解了它，就真正理解「数组类型」了\n");

    /* ---------- 附加：哨兵值 ---------- */
    printf("\n========== 附加技巧：哨兵值约定（不传长度）==========\n\n");
    printf("  数组 d = {7, 14, 21, 28, -1}，用 -1 表示结束\n");
    printf("  sum_until_sentinel(d, -1) = %d\n", sum_until_sentinel(d, -1));
    printf("  注意：只加到 -1 之前，28 后面的 -1 不算进去\n");
    printf("\n  ⚠️ 缺点：那个特殊值不能出现在正常数据里\n");
    printf("     字符串其实就是这个思路 —— 用 '\\0' 当哨兵\n");

    /* ---------- 汇总 ---------- */
    printf("\n############################################################\n");
    printf("#  三种做法对照                                            #\n");
    printf("############################################################\n\n");
    printf("  做法                长度从哪来          缺点\n");
    printf("  ------------------  ------------------  ------------------\n");
    printf("  int arr[] + int n   参数 n 传进来        ⭐ 推荐，最灵活\n");
    printf("  int (*arr)[N]       类型里的 N          长度写死\n");
    printf("  arr[] + 哨兵值      数据里的特殊值      特殊值不能是正常数据\n");
    printf("  sizeof(arr) 直接算  ❌ 算不出来          只在函数外有效\n\n");
    printf("  ★ 一句话：sizeof 只在【数组还在作用域里】的地方有效；\n");
    printf("    一旦作为参数传进函数，它退化成了指针，长度就丢了。\n");
    printf("    所以标准做法是：谁有数组，谁负责算长度，然后把长度传下去。\n");

    return 0;
}
