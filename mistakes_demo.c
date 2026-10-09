/* ============================================================
   mistakes_demo.c —— 第七章「指针」七类陷阱总集
   
   设计原则：能【安全演示】的就真跑出来给你看；
             会【崩溃】的只写在注释里，并说明怎么自己验证。

   ⚠️ 编译时会有 2 条警告 —— 那是【故意的】，
      正好演示"编译器能帮你发现这些错"。
   ============================================================ */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdint.h>
#include "utf8_console.h"

/* ============================================================
   ⚠️ 下面两条 pragma 是【故意】抑制警告的，因为本文件就是要演示错误写法。
      真实项目里绝对不要这样写！这里只是为了让演示程序能"干净地"编译，
      同时把警告信息用文字打在屏幕上给你看。

      MSVC 用 #pragma warning，GCC/Clang 用 #pragma GCC diagnostic
   ============================================================ */
#ifdef _MSC_VER
#  pragma warning(disable: 4172)   /* returning address of local variable */
#  pragma warning(disable: 4311)   /* pointer truncation */
#  pragma warning(disable: 4477)   /* format string mismatch */
#else
#  pragma GCC diagnostic ignored "-Wreturn-local-addr"
#  pragma GCC diagnostic ignored "-Wformat"
#  pragma GCC diagnostic ignored "-Wpointer-to-int-cast"
#endif

/* 用于演示"返回局部变量地址"的错误 */
int *bad_return(void)
{
    int x = 5;
    return &x;      /* ❌ 警告: function returns address of local variable */
}

/* 用于演示"返回局部数组地址"的错误 */
int *bad_array(void)
{
    int arr[3] = {1, 2, 3};
    return arr;     /* ❌ 同样危险 */
}

int main(void)
{
    enable_utf8_console();

    printf("############################################################\n");
    printf("#        第七章「指针」七类陷阱（能演示的都真跑）          #\n");
    printf("############################################################\n");

    /* ============================================================
       坑 1：野指针 —— 指针没初始化就用
       ============================================================ */
    printf("\n========== 坑 1：野指针（未初始化的指针）==========\n");
    printf("  错误代码（不要运行）:\n");
    printf("      int *p;        /* 没初始化 */\n");
    printf("      *p = 5;        /* 往一个随机地址写 -> 崩溃或踩坏别人 */\n");
    printf("\n  ✅ 正确做法: 定义时就给 NULL, 用之前先判\n");
    {
        int *p = NULL;          /* 初始化为空 */
        int a = 42;

        if (p == NULL) {
            printf("      int *p = NULL;  然后 if (p == NULL) 拦住了 -> 安全\n");
        }
        p = &a;                  /* 真正要用时才赋有效地址 */
        printf("      p = &a 之后 *p = %d -> 可以用了\n", *p);
    }
    printf("  >>> 口诀: 指针定义时就初始化, 不确定就写 NULL\n");

    /* ============================================================
       坑 2：对 NULL 解引用
       ============================================================ */
    printf("\n========== 坑 2：对 NULL 解引用 ==========\n");
    printf("  错误代码（不要运行）:\n");
    printf("      int *p = NULL;\n");
    printf("      printf(\"%%d\", *p);   /* 读地址 0 -> 必然崩溃 */\n");
    printf("\n  实测: NULL 的值 = %p  (就是 0)\n", (void *)NULL);
    printf("        C 语言不检查这个, 直接让操作系统杀掉进程\n");
    printf("        -> Segmentation fault (core dumped)\n");
    printf("  ✅ 正确做法: 解引用前一律先判 if (p != NULL)\n");
    printf("  >>> 对比: free(NULL) 是【安全】的, 但 *NULL 一定崩\n");

    /* ============================================================
       坑 3：返回局部变量的地址（野指针的变种）
       ============================================================ */
    printf("\n========== 坑 3：返回局部变量的地址 ==========\n");
    {
        int *bad = bad_return();
        int *bada = bad_array();
        printf("  编译时会看到两条警告:\n");
        printf("      warning: function returns address of local variable\n");
        printf("  ⚠️ 这个警告是故意保留的 —— 编译器能发现这类错误!\n\n");
        printf("  实测拿到的地址: bad_return() = %p   bad_array() = %p\n",
               (void *)bad, (void *)bada);
        printf("  这两个地址都在【栈区】(0x62xxxx 开头)\n");
        printf("  函数一返回, 那块内存就被回收了 -> 随时可能被别的函数覆盖\n");
        printf("  ✅ 三种正确做法:\n");
        printf("     ① 用 static         -> static int arr[3];\n");
        printf("     ② 调用者提供数组     -> void fill(int *out, int n)   ⭐推荐\n");
        printf("     ③ 用 malloc          -> int *p = malloc(...);\n");
        printf("  >>> 返回【值】是安全的(拷贝带走), 返回【地址】才危险\n");
    }

    /* ============================================================
       坑 4：用 %d 打印地址
       ============================================================ */
    printf("\n========== 坑 4：用 %%d 打印地址（应该用 %%p）==========\n");
    {
        int a = 10;
        int *p = &a;
        printf("  正确 %%p : %p\n", (void *)p);
        printf("  错误 %%d : %d   <-- 64 位地址被砍成 32 位, 高 32 位全丢\n", p);
        printf("  ⚠️ 编译警告: format '%%d' expects 'int', but argument has type 'int *'\n");
        printf("  >>> 这种警告不是可以忽略的 —— 它真的会丢数据\n");
    }

    /* ============================================================
       坑 5：把地址塞进 int
       ============================================================ */
    printf("\n========== 坑 5：把地址塞进普通 int ==========\n");
    printf("  错误代码（编译直接报错）:\n");
    printf("      int p2 = &a;      /* 整数和指针类型不兼容 */\n");
    {
        int a = 7;
        intptr_t full = (intptr_t)&a;        /* 完整的 8 字节地址 */
        int truncated = (int)full;           /* 就算强转也会丢高 32 位 */
        /* 注意: 老 gcc / MinGW 不支持 %lld, 所以拆成高低两半打印 */
        unsigned long hi = (unsigned long)((uint64_t)full >> 32);
        unsigned long lo = (unsigned long)((uint64_t)full & 0xFFFFFFFFUL);
        printf("\n  实测: 真实地址 (intptr_t) = %08lX%08lX\n", hi, lo);
        printf("        强转成 int 后      = %d  (= 0x%08lX)\n", truncated, lo);
        printf("        地址占 %u 字节, int 只占 %u 字节 -> 必然丢一半\n",
               (unsigned)sizeof(void *), (unsigned)sizeof(int));
        printf("  ✅ 要装地址就用指针类型; 要转整数就用 intptr_t(8字节)\n");
  }

    /* ============================================================
       坑 6：数组越界
       ============================================================ */
    printf("\n========== 坑 6：数组越界（C 不检查！）==========\n");
    {
        int arr[3] = {10, 20, 30};
        int i;
        printf("  int arr[3] = {10, 20, 30};\n");
        printf("  合法下标: 0, 1, 2\n\n");
        printf("  实测合法访问:\n");
        for (i = 0; i < 3; i++) {
            printf("      arr[%d] = %-4d 地址 %p\n", i, arr[i], (void *)&arr[i]);
        }
        printf("\n  再来看看越界的下标会怎样【只是读，不写】:\n");
        for (i = 3; i <= 4; i++) {
            printf("      arr[%d] = %-4d 地址 %p   <-- 已经出了数组!\n",
                   i, arr[i], (void *)&arr[i]);
        }
        printf("  ⚠️ 读越界可能只是拿到垃圾值; 【写】越界会踩坏别的变量, 后果严重\n");
        printf("  错误代码（不要运行）:\n");
        printf("      arr[5] = 999;     /* 越界写, 踩坏别人的房子 */\n");
        printf("  ✅ 正确做法: 循环边界用 sizeof(arr)/sizeof(arr[0]) 算, 别写死数字\n");
    }

    /* ============================================================
       坑 7：指针自增的优先级陷阱
       ============================================================ */
    printf("\n========== 坑 7：*p++ / (*p)++ / ++*p 三者不同! ==========\n");
    {
        int arr[4] = {10, 20, 30, 40};
        int *p;
        int v;

        printf("  三种写法意思完全不同:\n");
        printf("      (*p)++   把 p 指向的【值】加 1, 指针不动\n");
        printf("      *p++     先取值, 然后【指针】往后移一格  等价 *(p++)\n");
        printf("      ++*p     把 p 指向的【值】加 1  等价 ++(*p)\n\n");

        /* 演示 (*p)++ : 改值, 指针不动 */
        arr[0] = 10;
        p = arr;
        v = (*p)++;
        printf("  (*p)++  : 返回值 = %d, 现在 arr[0] = %d, p 仍指向 arr[%d]\n",
               v, arr[0], (int)(p - arr));

        /* 演示 *p++ : 取值, 指针移动 */
        arr[0] = 10;
        p = arr;
        v = *p++;
        printf("  *p++    : 返回值 = %d, 现在 p 指向 arr[%d]  (指针动了!)\n",
               v, (int)(p - arr));

        /* 演示 ++*p : 改值 */
        arr[0] = 10;
        p = arr;
        v = ++*p;
        printf("  ++*p    : 返回值 = %d, 现在 arr[0] = %d\n", v, arr[0]);

        printf("\n  >>> 记住: 加号在前就先加; 括号决定改值还是移指针\n");
        printf("      *p++ 最容易错 —— 它移动的是【指针】, 不是值\n");
    }

    printf("\n############################################################\n");
    printf("#                      七 类 陷 阱 速 记                    #\n");
    printf("############################################################\n\n");
    puts("  1. 野指针        -> 定义时初始化为 NULL, 用前先判");
    puts("  2. 对 NULL 解引用 -> 解引用前一律 if (p != NULL)");
    puts("  3. 返回局部变量地址 -> 用 static / 调用者提供 / malloc");
    puts("  4. %d 打印地址    -> 要用 %p (并且加 (void*) 转换)");
    puts("  5. 地址塞进 int   -> 用指针类型或 intptr_t(8字节)");
    puts("  6. 数组越界       -> 用 sizeof 算边界, C 不会帮你检查");
    puts("  7. *p++ 优先级    -> 加号在前先加, 括号决定改值还是移指针");
    puts("");
    printf("  ★ 前 3 个会导致崩溃; 第 4、5 个会静默丢数据(更隐蔽);\n");
    printf("    第 6、7 个是逻辑错误, 编译器不报错, 最难查。\n\n");

    return 0;
}
