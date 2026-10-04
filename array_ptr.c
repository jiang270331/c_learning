/* 笔记章节：Pointer · 10 → 「指针与数组」
 * 公式：a[i]  ≈  *(p + i)
 */
#include <stdio.h>

int main(void) {
    int a[5] = {10, 20, 30, 40, 50};
    int *p = a;   /* 指向首元素 */
    int i;

    printf("a[i] 与 *(p + i) 对照：\n");
    for (i = 0; i < 5; i++) {
        printf("  a[%d] = %-3d   *(p + %d) = %-3d   地址 %p\n",
               i, a[i], i, *(p + i), (void*)(p + i));
    }

    printf("\n数组名 a  = %p （首元素门牌）\n", (void*)a);
    printf("指针   p  = %p\n", (void*)p);
    printf("a + 1     = %p （跳过 1 个 int，不是 1 个字节）\n", (void*)(a + 1));

    printf("\nsizeof(a) = %d 字节（整个数组）\n", (int)sizeof(a));
    printf("sizeof(p) = %d 字节（只是个指针，跟数组长度无关）\n", (int)sizeof(p));
    return 0;
}
