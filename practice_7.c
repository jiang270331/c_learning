/* ============================================================
   practice_7.c —— 第七章动手练习台（填空式，自动判分）

   怎么用：
     1. 下面 7 道题，每题有一个函数，函数体写着 TODO 和提示
     2. 你只改 TODO 那部分（函数名、参数别动）
     3. 编译运行：  .\b practice_7
     4. 它会自动测你的实现，输出 通过/失败

   ⚠️ 一开始编译会有几条警告（返回类型、未使用参数等），
      那是【正常】的 —— 因为还没填。填完就没了。

   建议：先自己写，卡住再看 笔记/7.4、笔记/7.5 的讲义。
   ============================================================ */
#include <stdio.h>
#include <stddef.h>
#include "utf8_console.h"

/* ============================================================
   题 1（7.4）：交换两个整数
   要求：让 main 里的 a、b 真的换过来
   ============================================================ */
void my_swap(int *x, int *y)
{
    /* TODO: 用 *x 和 *y 交换
       提示：需要一个临时变量 int t = *x; 然后... */
    (void)x; (void)y;   /* 填好后把这行删掉 */
}


/* ============================================================
   题 2（7.4）：一个函数带回最大值和最小值
   要求：通过 out_max / out_min 把结果写回调用者的变量
   ============================================================ */
void my_max_min(int arr[], int n, int *out_max, int *out_min)
{
    /* TODO: 先让 *out_max = *out_min = arr[0];
       然后从 i=1 开始遍历，遇到更大的更新 out_max，更小的更新 out_min
       注意：写的是 *out_max，不是 out_max */
    (void)arr; (void)n; (void)out_max; (void)out_min;
}


/* ============================================================
   题 3（7.4）：在函数里正确算出数组长度
   要求：返回 arr 的元素个数
   ⚠️ 注意：arr 在这里已经退化成了指针，sizeof 算不出来！
      所以要靠 n 参数（这是唯一正确做法）
   ============================================================ */
int my_length(int arr[], int n)
{
    /* TODO: 这题很简单 —— 想清楚为什么不能写 sizeof(arr)/sizeof(arr[0]) */
    (void)arr;
    return -1;
}


/* ============================================================
   题 4（7.4）：把函数的结果写进调用者给的数组
   要求：让 out[0..n-1] 依次等于 1, 4, 9, 16, ...（即 (i+1) 的平方）
   ============================================================ */
void fill_squares(int *out, int n)
{
    /* TODO: for 循环，out[i] = (i+1)*(i+1); */
    (void)out; (void)n;
}


/* ============================================================
   题 5（7.5）：用指针自己实现 strlen
   要求：不用 <string.h> 的 strlen，用指针遍历
   ============================================================ */
int my_strlen(const char *s)
{
    /* TODO: 定义 const char *p = s; 然后 while (*p) p++;
       最后 return (int)(p - s); */
    (void)s;
    return -1;
}


/* ============================================================
   题 6（7.5）：用指针实现 strcpy
   要求：把 src 的字符逐个抄到 dest，别忘了结尾的 '\0'
   ============================================================ */
void my_strcpy(char *dest, const char *src)
{
    /* TODO: while (*src) { *dest = *src; dest++; src++; }
       循环结束后别忘了 *dest = '\0';  */
    (void)dest; (void)src;
}


/* ============================================================
   题 7（7.5）：判断字符串是否回文（正读反读都一样）
   要求：用两个指针，一个从头、一个从尾，向中间靠拢比较
   返回 1 表示是回文，0 表示不是
   ============================================================ */
int is_palindrome(const char *s)
{
    /* TODO:
       const char *left = s;
       const char *right = s + my_strlen(s) - 1;   ← 可以用你题 5 写的
       while (left < right) {
           if (*left != *right) return 0;
           left++; right--;
       }
       return 1;                                        */
    (void)s;
    return -1;
}


/* ============================================================
   ↓↓↓ 下面是测试台，不用改 ↓↓↓
   ============================================================ */

static int passed = 0;
static int failed = 0;

static void ok(const char *what)
{
    printf("  [通过] %s\n", what);
    passed++;
}

static void no(const char *what)
{
    printf("  [失败] %s\n", what);
    failed++;
}

int main(void)
{
    enable_utf8_console();

    printf("############################################################\n");
    printf("#        第七章动手练习台（自动判分）                      #\n");
    printf("############################################################\n\n");

    /* ---- 题 1 ---- */
    printf("题 1：交换两个整数 my_swap\n");
    {
        int a = 3, b = 5;
        my_swap(&a, &b);
        if (a == 5 && b == 3) {
            ok("a=3,b=5 交换后变成 a=5,b=3");
        } else {
            printf("  [失败] 交换后 a=%d, b=%d（应该 a=5, b=3）\n", a, b);
            failed++;
        }
        /* 再测一组：相等的情况不能出错 */
        a = 7; b = 7;
        my_swap(&a, &b);
        if (a == 7 && b == 7) ok("两个相等的数交换后仍相等");
        else no("两个相等的数交换出错");
    }

    /* ---- 题 2 ---- */
    printf("\n题 2：一次带回最大最小值 my_max_min\n");
    {
        int d[6] = {23, 7, 91, 45, 12, 68};
        int mx = 0, mn = 0;
        my_max_min(d, 6, &mx, &mn);
        if (mx == 91 && mn == 7) {
            ok("数组 {23,7,91,45,12,68} -> max=91 min=7");
        } else {
            printf("  [失败] max=%d（应 91）, min=%d（应 7）\n", mx, mn);
            failed++;
        }
        /* 单元素 */
        int e[1] = {-5};
        mx = mn = 0;
        my_max_min(e, 1, &mx, &mn);
        if (mx == -5 && mn == -5) ok("只有一个元素时 max=min=-5");
        else no("单元素情况出错");
    }

    /* ---- 题 3 ---- */
    printf("\n题 3：在函数里拿到数组长度 my_length\n");
    {
        int a5[5] = {1, 2, 3, 4, 5};
        int a1[1] = {9};
        int a8[8] = {0};
        if (my_length(a5, 5) == 5) ok("5 个元素 -> 返回 5");
        else {
            printf("  [失败] my_length(a5,5) = %d（应 5）\n", my_length(a5, 5));
            failed++;
        }
        if (my_length(a1, 1) == 1) ok("1 个元素 -> 返回 1");
        else no("单元素长度出错");
        if (my_length(a8, 8) == 8) ok("8 个元素 -> 返回 8");
        else no("8 元素长度出错");
        printf("  （提示：这题正确答案就是 return n —— 因为 sizeof(arr) 在函数里没用）\n");
    }

    /* ---- 题 4 ---- */
    printf("\n题 4：把结果写进调用者的数组 fill_squares\n");
    {
        int buf[5] = {0};
        fill_squares(buf, 5);
        if (buf[0] == 1 && buf[1] == 4 && buf[2] == 9 &&
            buf[3] == 16 && buf[4] == 25) {
            ok("n=5 -> [1, 4, 9, 16, 25]");
        } else {
            printf("  [失败] 得到 [%d, %d, %d, %d, %d]（应 [1, 4, 9, 16, 25]）\n",
                   buf[0], buf[1], buf[2], buf[3], buf[4]);
            failed++;
        }
        int b3[3] = {0};
        fill_squares(b3, 3);
        if (b3[0] == 1 && b3[1] == 4 && b3[2] == 9) ok("n=3 -> [1, 4, 9]");
        else no("n=3 出错");
    }

    /* ---- 题 5 ---- */
    printf("\n题 5：用指针实现 my_strlen\n");
    {
        struct { const char *s; int want; } cases[] = {
            {"", 0}, {"a", 1}, {"hello", 5}, {"pointer", 7},
            {"Hello World", 11},
        };
        int i, allok = 1;
        for (i = 0; i < 5; i++) {
            int got = my_strlen(cases[i].s);
            if (got != cases[i].want) {
                printf("  [失败] my_strlen(\"%s\") = %d（应 %d）\n",
                       cases[i].s, got, cases[i].want);
                failed++;
                allok = 0;
            }
        }
        if (allok) ok("空串/单字符/多字符 全部正确");
        /* 验证不修改原串 */
        {
            char t[] = "test";
            my_strlen(t);
            if (t[0] == 't' && t[3] == 't') ok("不修改原字符串");
            else no("把原字符串改坏了");
        }
    }

    /* ---- 题 6 ---- */
    printf("\n题 6：用指针实现 my_strcpy\n");
    {
        char dst[32];
        int i;
        my_strcpy(dst, "hello");
        if (dst[0] == 'h' && dst[4] == 'o' && dst[5] == '\0') {
            ok("拷贝 \"hello\" 成功，且补上了 '\\0'");
        } else {
            printf("  [失败] dst = \"%s\"（检查是否忘了结尾的 '\\0'）\n", dst);
            failed++;
        }
        my_strcpy(dst, "");
        if (dst[0] == '\0') ok("拷贝空串 -> dst[0] == '\\0'");
        else no("空串拷贝出错");
        /* 目标缓冲区必须逐个字节正确 */
        my_strcpy(dst, "abc");
        for (i = 0; i < 4; i++) { }
        if (dst[0]=='a' && dst[1]=='b' && dst[2]=='c' && dst[3]=='\0')
            ok("逐字节校验 \"abc\" 正确");
        else no("逐字节校验失败");
    }

    /* ---- 题 7 ---- */
    printf("\n题 7：判断回文 is_palindrome\n");
    {
        struct { const char *s; int want; } cases[] = {
            {"a", 1}, {"ab", 0}, {"aa", 1}, {"aba", 1},
            {"abba", 1}, {"abcba", 1}, {"abc", 0}, {"", 1},
            {"level", 1}, {"hello", 0},
        };
        int i, allok = 1;
        for (i = 0; i < 10; i++) {
            int got = is_palindrome(cases[i].s);
            if (got != cases[i].want) {
                printf("  [失败] is_palindrome(\"%s\") = %d（应 %d）\n",
                       cases[i].s, got, cases[i].want);
                failed++;
                allok = 0;
            }
        }
        if (allok) ok("10 个用例（含空串、单字符、奇偶长度）全部正确");
    }

    /* ---- 汇总 ---- */
    printf("\n############################################################\n");
    printf("#  通过 %d 项，失败 %d 项\n", passed, failed);
    if (failed == 0) {
        printf("#  全部通过！第七章的指针基本用法你掌握了。\n");
    } else {
        printf("#  还有 %d 项没通过 —— 回去看对应讲义的「现在就做」那节。\n",
               failed);
    }
    printf("############################################################\n");
    printf("\n对照答案：笔记/7.4-指针和函数.md、笔记/7.5-指针与字符串.md\n");

    return failed == 0 ? 0 : 1;
}
