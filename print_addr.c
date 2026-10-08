/* 笔记章节：Pointer · 07 → 「怎么打印地址」
 * 口诀：用 %p，指针前面加 (void*)
 * 对照表（笔记里的 5 行）全部在这里跑一遍。
 */
#include <stdio.h>

int main(void) {
    int a = 10;
    int b = 20;
    int *p = &a;

    printf("a 的值       printf(\"%%d\\n\", a)            -> %d\n", a);
    printf("a 的地址     printf(\"%%p\\n\", (void*)&a)     -> %p\n", (void*)&a);
    printf("p 里的地址   printf(\"%%p\\n\", (void*)p)      -> %p\n", (void*)p);
    printf("p 指向的内容 printf(\"%%d\\n\", *p)            -> %d\n", *p);
    printf("p 自己的地址 printf(\"%%p\\n\", (void*)&p)     -> %p\n", (void*)&p);
    printf("b 的地址     printf(\"%%p\\n\", (void*)&b)     -> %p\n", (void*)&b);
    /* 关键验证：&a 和 p 是同一次运行里的同一个地址 */ 
    printf("&a 的地址     printf(\"%%p\\n\", (void*)&a)     -> %p\n", (void*)&a);
    printf("\n&a 与 p 相同吗？ %s\n", (&a == p) ? "相同（因为 p 抄的就是 a 的门牌）" : "不同");
    return 0;
}
