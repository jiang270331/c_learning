/* ============================================================
   string_literal.c —— ⚠️ 字符串字面量不能改（教材 7.5 易错点）

   本文件有两部分：
     上半部分：安全演示（只读，能正常运行）
     下半部分：崩溃演示（默认被注释掉，想亲眼看就取消注释）

   ★ 运行 crash_demo 会让程序直接崩溃（Segmentation fault），
     这是【故意】的，用来让你亲眼看到"改字面量"的后果。

   ⚠️ 本机提示：这个文件编译出的 exe 可能被 Windows 的
      「智能应用控制(SAC)」拦截（提示 An Application Control policy
      has blocked this file）。这是系统安全策略，不是代码问题。
      多编译几次、或用 .\b string_literal 重试，有时能过。
      代码本身逻辑是好的，用 F5 调试运行也可以。
   ============================================================ */
#include <stdio.h>
#include "utf8_console.h"

/* ============================================================
   崩溃演示：改字符串字面量
   ============================================================ */
void crash_demo(void)
{
    char *p = "hello";        /* p 指向只读数据区的字面量 */

    printf("即将执行 p[0] = 'H';  （改只读区）\n");
    printf("...如果没崩溃，说明你的平台没保护只读区（更危险！）\n");
    fflush(stdout);

    p[0] = 'H';               /* ❌ 写只读内存 → Segmentation fault */

    printf("没崩溃? p = %s\n", p);
}

int main(void)
{
    enable_utf8_console();

    printf("========== 1. 两种写法的本质区别 ==========\n");
    {
        char a[] = "hello";       /* 数组：在栈上拷贝一份，可读可改 */
        char *b  = "hello";       /* 指针：指向只读数据区的字面量 */

        printf("char  a[] = \"hello\";   sizeof(a) = %u  (整个数组, 在自己的栈上)\n",
               (unsigned)sizeof(a));
        printf("char *b   = \"hello\";   sizeof(b) = %u  (只是个指针)\n",
               (unsigned)sizeof(b));
        printf("\n地址对比:\n");
        printf("  a 的地址 = %p   <-- 栈 (可写)\n", (void *)a);
        printf("  b 指向的 = %p   <-- 只读数据区 (不可写)\n", (void *)b);

        printf("\n改数组是安全的:\n");
        a[0] = 'H';
        printf("  a[0]='H' 之后 a = \"%s\"\n", a);
        printf("\n改指针指向的字面量会崩溃:\n");
        printf("  b[0]='H';  → Segmentation fault\n");
    }

    printf("\n========== 2. 正确写法: 要改就用数组, 或先拷贝 ==========\n");
    {
        /* 方法 1: 用数组 */
        char s1[] = "hello";
        s1[0] = 'H';
        printf("方法1 (数组):        s1 = \"%s\"\n", s1);

        /* 方法 2: 用指针 + 可写缓冲区 */
        const char *src = "hello";
        char buf[20];
        int i;
        for (i = 0; src[i] != '\0'; i++) {   /* 手动拷一份到可写内存 */
            buf[i] = src[i];
        }
        buf[i] = '\0';
        buf[0] = 'H';
        printf("方法2 (指针+缓冲区): buf = \"%s\"   (源 src 仍是 \"%s\")\n",
               buf, src);
    }

    printf("\n========== 3. 为什么 const 很重要 ==========\n");
    {
        const char *p = "hello";
        const char *q = "world";
        printf("const char *p = \"hello\";   读出 p = \"%s\"\n", p);
        /* p[0] = 'H';    ❌ 编译期就报错: assignment of read-only location */
        p = q;                 /* ✅ p 自己可以改（换指向） */
        printf("p = q 之后 p = \"%s\"        (p 自己能改)\n", p);
        printf("=> 加上 const, 编译器会阻止你写 p[0]='H'\n");
        printf("   这是【编译期】就拦下来, 比运行时崩溃好得多\n");
        printf("   凡是「只读、不打算改」的字符串, 都应该写 const char *\n");
        printf("\n坑: 下面这两行的区别很微妙\n");
        printf("  const char *p;    // 指向的内容不能改, p 自己能改\n");
        printf("  char * const p;   // p 自己不能改, 指向的内容能改\n");
    }

    printf("\n========== 4. 常见错误对照表 ==========\n");
    puts("  X  char *p = \"hi\"; p[0]='H';   崩溃 (改只读区)");
    puts("  O  char p[] = \"hi\"; p[0]='H';  安全 (改自己的数组)");
    puts("  X  char s[10]; s = \"hi\";       编译错误 (数组不能整体赋值)");
    puts("  O  char s[10]; strcpy(s,\"hi\"); 安全 (复制内容)");
    puts("  X  printf(\"%s\", *p);          错 (%s 要地址, *p 是字符)");
    puts("  O  printf(\"%s\", p);           对");
    puts("  O  printf(\"%c\", *p);          对 (%c 才是字符)");

    printf("\n========== 5. 想看崩溃现场? ==========\n");
    printf("本文件里的 crash_demo() 函数演示了\n");
    printf("  char *p = \"hello\";  p[0] = 'H';   的后果。\n");
    printf("默认没被调用（调用了程序会直接崩溃）。\n");
    printf("\n想亲眼看:  把下面这行的注释去掉, 重新编译运行即可\n");
    printf("     crash_demo();\n");
    printf("\n崩溃时会看到:  Segmentation fault (core dumped)\n");
    printf("=> 这就是 7.5 最经典的坑: 混淆了「数组」和「指向字面量的指针」\n");

    /* 取消下面这行的注释，就能亲眼看到崩溃： */
    /* crash_demo(); */

    return 0;
}
