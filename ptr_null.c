/* 笔记章节：Pointer · 08 → 「空指针：纸条上写『无』」 */
#include <stdio.h>
#include "utf8_console.h"   /* 让中文正常显示，详见该文件里的说明 */

int main(void) {
    enable_utf8_console();   /* 打印中文之前，先把控制台切成 UTF-8 */
    int *p = NULL;

    if (p == NULL) {
        printf("还没指向任何地方，先别进门\n");
    }

    /* 铁律演示：下面这行千万不要打开，会直接崩溃
     * printf("%d\n", *p);
     */
    return 0;
}
