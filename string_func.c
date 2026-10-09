/* ============================================================
   string_func.c —— 字符串函数与指针（教材 7.5）
   含：strlen / strcpy / strcat / strcmp + 常见陷阱
   ============================================================ */
#include <stdio.h>
#include <string.h>         /* 字符串函数都在这里 */
#include "utf8_console.h"

/* 用指针实现 strcpy（理解原理） */
char *my_strcpy(char *dest, const char *src)
{
    char *start = dest;          /* 记住开头，最后要返回它 */
    while (*src != '\0') {
        *dest = *src;            /* 一个字符一个字符地抄 */
        dest++;
        src++;
    }
    *dest = '\0';                /* ⚠️ 别忘了补结尾的 '\0'！ */
    return start;
}

/* 用指针实现 strcmp 的核心逻辑 */
int my_strcmp(const char *a, const char *b)
{
    while (*a != '\0' && *a == *b) {
        a++;
        b++;
    }
    return (int)(unsigned char)*a - (int)(unsigned char)*b;
}

int main(void)
{
    enable_utf8_console();

    printf("========== 1. 常用字符串函数 ==========\n");
    {
        char s1[20] = "hello";
        char s2[] = "world";

        printf("strlen(s1) = %u          取长度（不含 '\\0'）\n",
               (unsigned)strlen(s1));

        strcat(s1, " ");            /* 追加 */
        strcat(s1, s2);
        printf("strcat 之后 s1 = \"%s\"\n", s1);

        printf("strcmp(\"abc\",\"abc\") = %d   <-- 0 表示相等\n",
               strcmp("abc", "abc"));
        printf("strcmp(\"abc\",\"abd\") = %d   <-- 负数表示前者小\n",
               strcmp("abc", "abd"));
        printf("strcmp(\"abd\",\"abc\") = %d   <-- 正数表示前者大\n",
               strcmp("abd", "abc"));
        printf("=> strcmp 返回 0 才表示相等, 不能直接 if (strcmp(a,b)) 判断相等\n");
    }

    printf("\n========== 2. ⚠️ 字符串不能直接赋值 ==========\n");
    {
        char s1[20] = "hello";
        char s2[20];

        /* s2 = s1;   ❌ 编译错误! 数组名不能被赋值 */
        printf("s2 = s1;  这样写是错的（数组名是地址, 不能整体赋值）\n");

        strcpy(s2, s1);             /* ✅ 正确的是用 strcpy */
        printf("strcpy(s2, s1) 之后: s2 = \"%s\"\n", s2);
    }

    printf("\n========== 3. 指针赋值 vs strcpy（关键区别） ==========\n");
    {
        char s1[20] = "hello";
        char *p;

        p = s1;                     /* 指针赋值: 两个指针指向同一块内存 */
        printf("p = s1 之后: p = \"%s\"\n", p);
        p[0] = 'H';                 /* 改 p 就是改 s1！ */
        printf("改 p[0]='H' 之后: s1 = \"%s\"   <-- s1 也变了!\n", s1);
        printf("=> 指针赋值只是复制了「地址」, 两份指着同一块地\n");

        {
            char s3[20] = "hello";
            char s4[20];
            strcpy(s4, s3);         /* strcpy: 复制内容, 两块独立的内存 */
            s4[0] = 'H';
            printf("\nstrcpy 之后改 s4[0]: s3 = \"%s\", s4 = \"%s\"\n", s3, s4);
            printf("=> strcpy 复制的是内容, 改一个不影响另一个\n");
        }
    }

    printf("\n========== 4. 自己用指针实现 strcpy ==========\n");
    {
        char src[] = "pointer";
        char dst[20];
        my_strcpy(dst, src);
        printf("my_strcpy 结果: dst = \"%s\"\n", dst);
        printf("和 strcpy 效果一样: %d\n", strcmp(dst, src) == 0);
        printf("原理: while (*src) *dest++ = *src++;  然后补 '\\0'\n");
        printf("⚠️ 忘记补 '\\0' 是经典 bug —— 后面会打出乱码\n");
    }

    printf("\n========== 5. 字符串数组（指针数组） ==========\n");
    {
        /* 每个元素都是 char*，指向不同的字面量 */
        const char *names[] = {"apple", "banana", "cherry"};
        int i;
        printf("const char *names[3] = {\"apple\", \"banana\", \"cherry\"};\n");
        for (i = 0; i < 3; i++) {
            printf("   names[%d] = %-8s  地址 %p\n",
                   i, names[i], (const void *)names[i]);
        }
        printf("=> 每个元素是一个指针（%u 字节）, 指向各自的字符串\n",
               (unsigned)sizeof(names[0]));
        printf("   整个数组大小 = %u 字节 = 3 x %u\n",
               (unsigned)sizeof(names), (unsigned)sizeof(names[0]));
    }

    printf("\n========== 6. 两种「字符串数组」写法对比 ==========\n");
    {
        /* 法一：二维字符数组 —— 每行固定长度, 浪费空间 */
        char a[3][16] = {"apple", "banana", "cherry"};
        /* 法二：指针数组 —— 每行长度按需, 省空间 */
        const char *b[3] = {"apple", "banana", "cherry"};

        printf("char a[3][16]    总大小 = %u 字节  (3 x 16, 每行固定, 不管实际多长)\n",
               (unsigned)sizeof(a));
        printf("const char *b[3] 总大小 = %u 字节  (3 x %u)\n",
               (unsigned)sizeof(b), (unsigned)sizeof(b[0]));
        printf("=> 数组里存的是字符: 定长, 会浪费\n");
        printf("=> 指针数组里存的是地址: 灵活省空间, 但字面量不能改\n");
        printf("a[0] = \"%s\"   b[0] = \"%s\"\n", a[0], b[0]);
    }

    return 0;
}
