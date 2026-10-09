/* ============================================================
   func_array.c —— 数组作函数参数（教材 7.4）
   核心：数组传进函数会"退化"成指针，长度信息丢失
   ============================================================ */
#include <stdio.h>
#include "utf8_console.h"

/* ---------- 写法 1：数组形式（推荐，最易读） ---------- */
/* n 必须单独传！因为 sizeof 在函数里已经拿不到数组长度了 */
int sum_array(int arr[], int n)
{
    int i, total = 0;
    printf("  [函数内] sizeof(arr) = %u  <-- 退化成了指针, 拿不到长度\n",
           (unsigned)sizeof(arr));
    for (i = 0; i < n; i++) {
        total += arr[i];
    }
    return total;
}

/* ---------- 写法 2：指针形式（和写法 1 完全等价） ---------- */
int sum_ptr(int *arr, int n)
{
    int total = 0;
    while (n-- > 0) {
        total += *arr;
        arr++;              /* 指针自己往后走 */
    }
    return total;
}

/* ---------- 演示：函数里改数组，外面会变 ---------- */
void double_all(int arr[], int n)
{
    int i;
    for (i = 0; i < n; i++) {
        arr[i] *= 2;        /* 改的是原始数组，不是副本 */
    }
}

/* ---------- ⚠️ 陷阱：在函数里 sizeof 算长度是错的 ---------- */
int wrong_length(int arr[])
{
    /* 想自动算长度 —— 但 arr 已经是指针，算出来是本机指针大小 8 */
    return (int)(sizeof(arr) / sizeof(arr[0]));
}

void print_array(int arr[], int n)
{
    int i;
    printf("  [");
    for (i = 0; i < n; i++) {
        printf("%d%s", arr[i], (i < n - 1) ? ", " : "");
    }
    printf("]\n");
}

int main(void)
{
    enable_utf8_console();

    int a[5] = {10, 20, 30, 40, 50};
    int n = (int)(sizeof(a) / sizeof(a[0]));   /* 在 main 里算长度是对的 */

    printf("========== 1. 数组名退化是个什么现象 ==========\n");
    printf("在 main 里:   sizeof(a) = %u  (整个数组)\n", (unsigned)sizeof(a));
    printf("算出的元素个数 n = %d\n", n);
    printf("\n调用函数看看:\n");
    printf("  sum_array 的结果 = %d\n", sum_array(a, n));

    printf("\n========== 2. 两种写法完全等价 ==========\n");
    printf("sum_array(a, n) = %d   (int arr[] 形式)\n", sum_array(a, n));
    printf("sum_ptr(a, n)   = %d   (int *arr 形式)\n", sum_ptr(a, n));
    printf("=> int arr[] 和 int *arr 在参数里是同一件事\n");

    printf("\n========== 3. ⚠️ 陷阱: 在函数里算长度是错的 ==========\n");
    printf("wrong_length(a) = %d   <-- 不是 5!\n", wrong_length(a));
    printf("因为函数里的 arr 已经是指针, sizeof(arr)=%u, 除以 sizeof(int)=%u\n",
           (unsigned)sizeof(int *), (unsigned)sizeof(int));
    printf("=> 正确做法: 长度单独作为参数传进来 (n)\n");

    printf("\n========== 4. 函数里改数组, 外面真的会变 ==========\n");
    printf("改之前: "); print_array(a, n);
    double_all(a, n);
    printf("double_all 之后: "); print_array(a, n);
    printf("=> 因为传的是地址, 函数直接改到了原始数组\n");
    printf("   (对比 ex_b.c 的 swap_wrong: 传值改不动, 传地址能改)\n");

    return 0;
}
