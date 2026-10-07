/* ============================================================
 * utf8_console.h —— 让程序正确显示中文（Windows 专用）
 *
 * 【为什么需要它】
 *   编译器把源码里的中文字符串按 **UTF-8** 存进 exe。
 *   但 Windows 控制台默认用 **GBK（代码页 936）** 去解码，
 *   结果中文就变成乱码，例如：
 *
 *       a 的值 = 999      →      a 鍕囧€?= 999
 *
 * 【怎么解决】
 *   在打印任何中文之前，把控制台切成 UTF-8（代码页 65001）。
 *   这样控制台就用 UTF-8 解码，和 exe 里的字节一致了。
 *
 * 【怎么用】
 *   在 main 函数的第一行调用  enable_utf8_console();
 *
 *       #include <stdio.h>
 *       #include "utf8_console.h"
 *
 *       int main(void) {
 *           enable_utf8_console();          // 就加这一行
 *           printf("a 的值 = %d\n", 999);   // 中文正常
 *           return 0;
 *       }
 *
 * 【为什么不用 system("chcp 65001")】
 *   那种写法会启动一个子进程（cmd.exe），在开启了
 *   「智能应用控制」的 Windows 上，编译出来的 exe 可能被拦截：
 *       An Application Control policy has blocked this file
 *   直接调用系统 API 没有这个问题。
 *
 * 【注意】
 *   本文件用 GBK/ANSI 无关的纯 C 写法，注释是中文，
 *   所以务必确保源码文件本身保存为 UTF-8（Cursor 默认如此）。
 * ============================================================ */

#ifndef UTF8_CONSOLE_H
#define UTF8_CONSOLE_H

#ifdef _WIN32

#include <windows.h>
#include <stdio.h>

/* 把控制台输入/输出代码页都切成 UTF-8（65001）。
 * 返回 0 表示成功，非 0 表示失败（一般不用管）。 */
static int enable_utf8_console(void)
{
    int ok = 0;

    /* 输出：程序 printf 出去的内容按 UTF-8 解释 */
    if (!SetConsoleOutputCP(65001)) {
        ok = 1;
    }

    /* 输入：用 scanf / fgets 读中文时也需要一致 */
    if (!SetConsoleCP(65001)) {
        ok = 1;
    }

    return ok;
}

#else

/* 非 Windows 平台（Mac / Linux）本来就是 UTF-8，不需要做任何事。
 * 保留这个同名函数，这样同一份代码换平台也能编译通过。 */
static int enable_utf8_console(void)
{
    return 0;
}

#endif /* _WIN32 */

#endif /* UTF8_CONSOLE_H */
