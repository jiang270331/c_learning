/* 笔记章节：Pointer · 14 → 「新手最容易翻车」
 * 这里把「能安全演示」的坑跑出来看，会崩溃的坑写成注释。
 */
#include <stdio.h>
#include "utf8_console.h"   /* 让中文正常显示，详见该文件里的说明 */

int main(void) {
    enable_utf8_console();   /* 打印中文之前，先把控制台切成 UTF-8 */
    int a = 10;
    int *p = &a;

    /* ---- 坑 4：用 %d 打印地址（应该用 %p）---- */
    printf("正确 %%p 打印地址 : %p\n", (void*)p);
    printf("错误 %%d 打印地址 : %d   <-- 数值被截断，64 位机器上必然不对\n", p);

    /* ---- 坑 5：把地址赋给普通 int ----
     * int p2 = &a;              编译直接报错：整数和指针类型不兼容
     * 就算强转，64 位地址塞进 32 位 int 也会丢一半：
     */
    {
        int truncated = (int)(long)p;
        printf("\n强制塞进 int 后 : %d   <-- 和上面 %%p 的地址对不上，地址被砍了\n", truncated);
    }

    /* ---- 坑 1：未初始化就 *p ----
     * int *q;  *q = 5;          野指针，行为不可预测
     */

    /* ---- 坑 2：对 NULL 解引用 ----
     * int *q = NULL;  printf("%d", *q);    运行时崩溃（访问冲突）
     */

    /* ---- 坑 3：返回局部变量地址 ----
     * int *bad(void) { int x = 5; return &x; }   函数结束后 x 的房子已经拆了
     */

    /* ---- 坑 6：数组越界 / free 后继续用 ----
     * int arr[3];  arr[5] = 1;        越界写，踩坏别人的房子
     * free(p);  printf("%d", *p);     free 之后再用 = 用已归还的地
     */

    printf("\n上面 4、5 两个坑是能当场看到的，其余 4 个只在注释里——千万别真的运行。\n");
    return 0;
}
