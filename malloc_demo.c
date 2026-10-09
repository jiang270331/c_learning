/* 笔记章节：Pointer · 13 → 「malloc：临时租一块地」
 * 口诀：租地 → 使用 → 归还：malloc → 读写 → free + 置 NULL
 * 注：笔记原文漏了 #include <stdlib.h>，这里补上，否则 malloc/free 会有警告。
 */
#include <stdio.h>
#include "utf8_console.h"   /* 让中文正常显示，详见该文件里的说明 */
#include <stdlib.h>

int main(void) {
    enable_utf8_console();   /* 打印中文之前，先把控制台切成 UTF-8 */
    int *p = malloc(5 * sizeof(int));
    int i;

    if (p == NULL) {
        printf("租地失败，不能用\n");
        return 1;   /* 笔记原文这里没写 return 值，main 返回 int 补上 */
    }

    for (i = 0; i < 5; i++) {
        p[i] = (i + 1) * 10;
        printf("p[%d] = %d   地址 %p\n", i, p[i], (void*)&p[i]);
    }

    free(p);      /* 归还 */
    p = NULL;     /* 防止野指针 */
    printf("\n已 free 并置 NULL，p == NULL 吗？ %s\n", (p == NULL) ? "是" : "否");
    return 0;
}
