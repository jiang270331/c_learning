/* 笔记章节：Pointer · 12 → 「字符串与指针」
 * 字符串 = 字符数组 + 结尾 '\0'
 */
#include <stdio.h>

int main(void) {
    char s[] = "cat";   /* 初学用 char s[]，可读可改 */
    char *p;

    printf("逐个字符打印：\n");
    for (p = s; *p != '\0'; p++) {
        printf("  '%c'  地址 %p\n", *p, (void*)p);
    }

    /* 看看结尾那个看不见的字符 */
    printf("\n字符串长度（不含 '\\0'）= %d\n", (int)(p - s));
    printf("结尾字符的编码值 = %d （就是 '\\0'）\n", (int)s[3]);

    /* 演示「坑」：下面这种指向字面量的写法，不要改里面的字符
     * char *lit = "hello";
     * lit[0] = 'H';   <-- 运行时会崩溃
     */
    printf("\nsizeof(s) = %d 字节 （c,a,t 加结尾的 '\\0'）\n", (int)sizeof(s));
    return 0;
}
