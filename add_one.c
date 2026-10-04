/* 笔记章节：Pointer · 09 → 「为什么要指针？函数想改原件」
 * 对比：值传递（复印件）改不了原件，传地址（门牌）才能改原件。
 */
#include <stdio.h>

/* 传值：拿到的只是复印件，改不动外面 */
void add_one_copy(int x) {
    x = x + 1;
}

/* 传地址：拿到原件门牌，进门改的是同一个房子 */
void add_one(int *p) {
    *p = *p + 1;
}

int main(void) {
    int a = 10;

    add_one_copy(a);
    printf("传值之后   a = %d   （外面没变）\n", a);

    add_one(&a);
    printf("传地址之后 a = %d   （原件被改了）\n", a);

    return 0;
}
