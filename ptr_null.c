/* 笔记章节：Pointer · 08 → 「空指针：纸条上写『无』」 */
#include <stdio.h>

int main(void) {
    int *p = NULL;

    if (p == NULL) {
        printf("还没指向任何地方，先别进门\n");
    }

    /* 铁律演示：下面这行千万不要打开，会直接崩溃
     * printf("%d\n", *p);
     */
    return 0;
}
