/* ============================================================
   string_basic.c —— 字符串与指针：基础（教材 7.5）
   字符串 = 字符数组 + 结尾的 '\0'
   ============================================================ */
#include <stdio.h>
#include <string.h>         /* strlen 等字符串函数 */
#include "utf8_console.h"

int main(void)
{
    enable_utf8_console();

    /* ---------- 1. 字符串的本质 ---------- */
    printf("========== 1. 字符串就是「字符数组 + 结尾的 \\0」 ==========\n");
    {
        char s[] = "cat";
        int i;
        printf("char s[] = \"cat\";\n");
        printf("它在内存里其实是这样（共 %u 字节）:\n", (unsigned)sizeof(s));
        for (i = 0; i < (int)sizeof(s); i++) {
            if (s[i] == '\0') {
                printf("   s[%d] = '\\0'  (编码值 %d)  <-- 看不见的结尾标记\n",
                       i, (int)s[i]);
            } else {
                printf("   s[%d] = '%c'   (编码值 %d)\n", i, s[i], (int)s[i]);
            }
        }
        printf("=> 3 个字母却占 4 字节, 多的那 1 字节就是 '\\0'\n");
    }

    /* ---------- 2. 两种定义方式，本质不同 ---------- */
    printf("\n========== 2. char s[] 和 char *p 的区别 ==========\n");
    {
        char s[] = "cat";        /* 数组: 拷贝一份, 可读可改 */
        char *p  = "cat";        /* 指针: 指向只读区的字面量 */

        printf("char s[] = \"cat\";   sizeof(s) = %u  <-- 整个数组\n",
               (unsigned)sizeof(s));
        printf("char *p  = \"cat\";   sizeof(p) = %u  <-- 只是个指针\n",
               (unsigned)sizeof(p));
        printf("\n两者都能打印: s = %s,  p = %s\n", s, p);

        s[0] = 'C';              /* ✅ 数组可以改 */
        printf("s[0]='C' 之后: s = %s   (数组能改)\n", s);
        printf("p 仍然是: %s\n", p);
        printf("=> p[0]='C' 会崩溃! 字面量在只读区, 详见 string_literal.c\n");
    }

    /* ---------- 3. 用指针遍历字符串 ---------- */
    printf("\n========== 3. 用指针遍历字符串 ==========\n");
    {
        char s[] = "hello";
        char *p;

        printf("写法 A: for (p = s; *p != '\\0'; p++)\n");
        for (p = s; *p != '\0'; p++) {
            printf("   *p = '%c'   地址 %p\n", *p, (void *)p);
        }

        printf("\n写法 B: while (*p) —— 简洁, 意思一样\n");
        p = s;
        while (*p) {                 /* 遇到 '\0' (值 0) 就停 */
            printf("   '%c' ", *p);
            p++;
        }
        printf("\n");

        printf("\n写完指针走到的位置 - 开头 = %d  <-- 就是字符串长度\n",
               (int)(p - s));
    }

    /* ---------- 4. 用指针自己算长度（不用 strlen） ---------- */
    printf("\n========== 4. 自己实现一个 strlen ==========\n");
    {
        const char *text = "pointer";
        const char *q = text;
        while (*q != '\0') {
            q++;
        }
        printf("\"%s\" 的长度 = %d\n", text, (int)(q - text));
        printf("原理: 从开头一直走到 '\\0', 走了几步就是几个字符\n");
    }

    /* ---------- 5. %s 和 %c 的区别（常见错） ---------- */
    printf("\n========== 5. ⚠️ %%s 和 %%c 别搞混 ==========\n");
    {
        char s[] = "cat";
        char *p = s;
        printf("*(p+1) 是字符:  %%c -> %c\n", *(p + 1));
        printf("p       是地址:  %%s -> %s   (%%s 从该地址一直打到 '\\0')\n", p);
        printf("p+1     从 'a' 开始 -> %s\n", p + 1);
        printf("=> %%s 要的是【地址】, 不是字符! 写 printf(\"%%s\", *p) 是错的\n");
    }

    /* ---------- 6. 字符数组 vs 字符串 的长度 ---------- */
    printf("\n========== 6. sizeof 和 strlen 不一样 ==========\n");
    {
        char s[] = "cat";
        printf("sizeof(s) = %u   <-- 数组总大小 (含 '\\0')\n", (unsigned)sizeof(s));
        printf("strlen(s) = %u   <-- 实际字符数 (不含 '\\0')\n",
               (unsigned)strlen(s));
        printf("=> 差 1, 就差在那个看不见的 '\\0' 上\n");
    }

    return 0;
}
