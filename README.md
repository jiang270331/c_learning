# C 指针学习工程

按「卡卡老师独家笔记 · Cursor × C 指针」的章节顺序搭建，
现在扩展到**教材（何钦铭《C语言程序设计》第 4 版）第七章「指针」7.1–7.5** 的完整学习材料。

**当前规模：24 个 `.c` 程序（全部编译通过）+ 3 篇讲义 + 1 个全章自测 + 1 个答案核验脚本。**

---

## 🚀 从哪开始

**先看 [`学习顺序.md`](学习顺序.md)** —— 顶部有「今天先做这个」的提醒条，
下面按阶段列了每一步该跑什么。

**如果不知道自己的水平在哪，先跑全章自测：**

```powershell
.\b review_ch7      # 第七章 25 道题，先答题后看解析
```

**哪组错得多，就回去看那节的讲义。**

---

## 一、怎么编译运行（推荐用 `.\b`）

### ⭐ 方式 1：`.\b` 短命令（最可靠）

```powershell
.\b ptr_sizeof        # 编译并运行 ptr_sizeof.c
.\b func_array        # 编译并运行 func_array.c
.\b                   # 编译并运行全部
.\b xxxxx             # 名字不对时，列出所有可用文件
```

**注意 `.\` 不能少** —— PowerShell 出于安全不搜索当前目录。

**为什么推荐它**：`.cmd` 批处理**不受 PowerShell 脚本执行策略限制**，
所以一定跑得起来（见下面「已知限制」一节）。

### 方式 2：Cursor 里的任务

1. Cursor → File → Open Folder，打开**本文件夹**
2. `Ctrl+Shift+P` → 输入 `Run Task` → 选「编译并运行当前文件」

> ⚠️ **`Ctrl+Shift+B` 在本机可能没反应。** 原因：那个任务调用 `.ps1`，
> 而本机 PowerShell 执行策略是 `Restricted`（很可能是组策略强制的，
> `-ExecutionPolicy Bypass` 也绕不过）。**用 `.\b` 代替即可。**

### 方式 3：终端手敲

```powershell
clang hello.c -o hello.exe
.\hello.exe
```

或

```powershell
.\run-all.cmd ex_a      # 只跑名字含 ex_a 的
.\run-all.cmd           # 跑全部（跑完停住，方便看结果）
```

---

## 二、环境（三个编译器，任选）

| 编译器 | 路径 | 说明 |
| --- | --- | --- |
| **clang 23.1.2** | `D:\c++ai\llvm\bin\clang.exe` | llvm-mingw 便携版，主力 |
| gcc（实为 clang） | `D:\c++ai\llvm\bin\gcc.exe` | 同一个 clang 的别名 |
| gcc 4.9.2 | `C:\Program Files (x86)\Dev-Cpp\MinGW64\bin\gcc.exe` | Dev-C++ 自带，SAC 拦截时更稳 |

**目标平台**：`x86_64-w64-windows-gnu`，64 位
**实测字节数**：`char` 1 / `short` 2 / `int` 4 / `long` **4**（Windows）/ `long long` 8 /
`float` 4 / `double` 8 / **任何指针 8**

---

## 三、学习路径（第七章 7.1–7.5）

| 节 | 讲义 | 演示程序 | 状态 |
|---|---|---|---|
| 7.1 指针基本概念 | — | `ptr1.c`、`print_addr.c` | ✅ 已掌握 |
| 7.2 指针变量及运算 | — | `ptr_null.c`、`add_one.c`、`ex_a.c` | ✅ 已掌握 |
| **7.3 指针与数组** | [`笔记/7.3-指针与数组.md`](笔记/7.3-指针与数组.md) | `ptr_array.c`、`ptr_sizeof.c`、`sizes.c`、`ex_7_3.c` | ✅ 已讲完 |
| **7.4 指针和函数** | [`笔记/7.4-指针和函数.md`](笔记/7.4-指针和函数.md) | `func_array.c`、`func_output.c`、`func_return.c` | 📖 待学 |
| **7.5 指针与字符串** | [`笔记/7.5-指针与字符串.md`](笔记/7.5-指针与字符串.md) | `string_basic.c`、`string_func.c`、`string_literal.c`、`string_ptr.c` | 📖 待学 |

**每节的做法都一样**（这个方法对他有效）：

1. **先看讲义开头的"先猜一猜"** —— 自己写答案，别先看解析
2. **跑对应的程序** —— 对照实际输出
3. **答错的回去看讲义那一节**
4. 最后跑 `.\b review_ch7` 验收

---

## 四、文件清单

### 讲义与文档

| 文件 | 讲什么 |
| --- | --- |
| `学习顺序.md` | **主入口**：分阶段学习路线 + 顶部今日提醒 |
| `笔记/7.3-指针与数组.md` | 指针算术、`sizeof` 铁证、数组名退化、6 道预测题 |
| `笔记/7.4-指针和函数.md` | 数组作参数退化、指针作输出参数、野指针陷阱 |
| `笔记/7.5-指针与字符串.md` | `'\0'`、`char[]` vs `char*`、字符串函数、只读字面量 |
| `printf格式符速查表.md` | `%d %f %c %s %p %%`、宽度精度、`%zu` 的坑 |

### 程序（24 个，按讲义归类）

**第七章 7.3–7.5 新增（11 个）**

| 文件 | 讲什么 |
| --- | --- |
| `ptr_array.c` | 指针算术、数组遍历、指针相减 |
| `ptr_sizeof.c` | `p+3` 字节差、`sizeof(a)` vs `sizeof(p)`、`2[a]` 为何合法 |
| `sizes.c` | 各类型字节数实测（含"指针为何 8 字节"） |
| `ex_7_3.c` | 7.3 那 4 道练习题的验证 |
| `func_array.c` | 数组作参数退化 + `wrong_length` 算错长度（陷阱） |
| `func_output.c` | 指针作输出参数、一函数多返回值、二级指针 |
| `func_return.c` | 野指针陷阱 + 三种正确做法（`static`/调用者提供/字面量） |
| `string_basic.c` | 字符串本质、指针遍历、自实现 `strlen`、`%s` vs `%c` |
| `string_func.c` | 字符串函数、**指针赋值 vs `strcpy`**、字符串数组两种写法 |
| `string_literal.c` | 只读字面量：`char a[]` 可改 vs `char *p` 改了崩溃 |
| `review_ch7.c` | **全章综合自测**（5 组 25 题，答案解析用实测数据） |

**早期练习（对照「卡卡老师笔记」章节）**

| 文件 | 对应笔记章节 | 讲什么 |
| --- | --- | --- |
| `hello.c` | Cursor · Windows | Hello World，环境验收 |
| `ptr1.c` | Pointer · 06 | 第一段能跑的指针程序 |
| `print_addr.c` | Pointer · 07 | 打印地址，5 种 printf 写法全跑一遍 |
| `ptr_null.c` | Pointer · 08 | 空指针：纸条上写「无」 |
| `add_one.c` | Pointer · 09 | 传值 vs 传地址，函数改原件 |
| `array_ptr.c` | Pointer · 10 | 指针与数组，`a[i] ≈ *(p+i)` |
| `swap.c` | Pointer · 11 | 函数传地址 swap |
| `string_ptr.c` | Pointer · 12 | 字符串与指针，看结尾的 `'\0'` |
| `malloc_demo.c` | Pointer · 13 | malloc → 读写 → free → 置 NULL |
| `mistakes_demo.c` | Pointer · 14 | 新手最容易翻车（能安全演示的坑） |
| `ex_a.c` | Pointer · 15 练习 A | 打印 `a` / `&a` / `p` / `*p`，再 `*p = 100` |
| `ex_b.c` | Pointer · 15 练习 B | 用指针写 swap（附错误示范对照） |
| `ex_c.c` | Pointer · 15 练习 C | 猜结果，附 4 道加练对照题 |

### 工具脚本

| 文件 | 用途 |
| --- | --- |
| `b.cmd` | **`.\b 文件名`** —— 编译并运行单个/全部（推荐） |
| `verify-answers.py` | **核验讲义数字与程序实际输出一致**（当前 37/37 通过） |
| `run-all.cmd` / `run-all.ps1` | 一键全部编译运行（自动挑编译器 + SAC 拦截自动重试） |
| `debug-build.cmd` | 带调试信息编译，产出 `build\<名字>_debug.exe` 供 F5 调试 |
| `check-clang.ps1` | 环境体检：列出所有编译器、试编译、报告系统策略状态 |
| `verify-git.ps1` | 检查 git 与 GitHub 连通性 |
| `utf8_console.h` | **让中文正常显示**（见下面「已知限制」） |
| `运行结果.txt` | 早期 13 个程序的完整真实输出 |
| `.vscode/` | Cursor 任务与调试配置 |

---

## 五、⚠️ 写新 `.c` 文件必看（两个硬性约定）

### 约定 1：有中文输出就必须加这两行

**否则运行时中文会变成乱码**（如 `值` 显示成 `鍕囧€?`）。

```c
#include <stdio.h>
#include "utf8_console.h"      /* ← 加这行 */

int main(void)
{
    enable_utf8_console();     /* ← 和这行 */
    printf("中文正常了\n");
    return 0;
}
```

**原理**：编译器把源码中文按 **UTF-8** 存进 exe，
但 Windows 控制台默认用 **GBK（代码页 936）** 解码 → 乱码。
`enable_utf8_console()` 调用系统 API 把控制台切成 UTF-8（65001）。

> **不用 `system("chcp 65001")`** —— 那会启动子进程，在开了 SAC 的机器上
> 编译出的 exe 可能被拦截。直接调 API 没这个问题。

### 约定 2：老 gcc 4.9.2 不支持 `%zu`

```c
printf("%zu", sizeof(a));              /* ❌ unknown conversion type 'z' */
printf("%u", (unsigned)sizeof(a));     /* ✅ */
```

**另外**：`long` 在 Windows 上是 4 字节、指针是 8 字节，
所以"指针转整数"要用 `intptr_t`（`#include <stdint.h>`），不能用 `long`。

---

## 六、已知限制（本机特有，不是代码问题）

### 6.1 Smart App Control 会拦新编译的 exe

```
An Application Control policy has blocked this file
```

**随机发生，与编译器、代码都无关**（SAC 按文件哈希查云端信誉，新哈希还没记录）。

| 应对 | 说明 |
|---|---|
| 重编译一次 | 换哈希就有概率过（`run-all.ps1` 已内置重试，最多 12 次） |
| 换编译器 | clang 和 gcc 都试试 |
| 用 F5 调试运行 | 走不同路径，通常能过 |
| 关掉 SAC | ⚠️ **一旦关闭只能重装 Windows 才能重开**，不建议 |

**实测**：同一个 exe 可能 12 次都被拦（该哈希被永久拉黑）；
但同一份代码换个文件名重新编译常常就过了。

### 6.2 PowerShell 执行策略

**本机是 `Restricted`（可能组策略强制），不能直接跑 `.ps1`。**

- ✅ 用 `.\b 文件名`（`.cmd` 不受此限制）
- ✅ 或用 `run-all.cmd`
- ❌ `Ctrl+Shift+B` 会失败（任务调的是 `.ps1`）

---

## 七、笔记原文的几处小瑕疵（本工程已修正）

1. **`malloc` 那一段漏了 `#include <stdlib.h>`** —— 不补会有隐式声明警告，已补。
2. **`add_one` 和 `swap` 的 `main` 没写 `return 0;`** —— 已补。
3. **`char *p = s` 写在 `for` 括号里** —— C99 写法，老编译器会报错，已改成括号外声明。
4. **`%d` 打印地址会怎样** —— 笔记只说"会报警或乱码"，`mistakes_demo.c` 跑出来了：
   真实地址 `00000018694FFE58`，用 `%d` 只剩 `1766850136`（64 位地址被砍成 32 位）。
5. **`char *s = "hello"` 不能改** —— 笔记提醒得对，但没说原因：
   字面量在只读段，改它会直接崩溃（`string_literal.c` 有可选的崩溃演示）。
6. **`utf8_console.h` 的使用** —— 早期 10 个文件都漏了，2026-10-10 已统一补齐。

---

## 八、笔记里的「预期」都对上了吗

都对上了，几个关键现象：

- **改 `*p`，`a` 真的跟着变**（`ptr1.c`）：`*p = 20` 之后 `a` 从 10 变成 20 ✅
- **`&a` 和 `p` 是同一个地址**（`print_addr.c`）：实测都是 `...62FE4C` ✅
- **`swap` 交换成功**（`swap.c`）：3 5 → 5 3 ✅
- **练习 C 的答案**（`ex_c.c`）：`*p + 1` = **3**，`*(p + 1)` = **4** ✅
- **指针加法按元素跳**（`array_ptr.c`）：地址递增 **4** 字节，不是 1 字节 ✅
- **`sizeof` 的区别**：`sizeof(a)` = 20（整个数组），`sizeof(p)` = 8（指针）✅
- **`sizeof(a)/sizeof(a[0])` = 5**（自动数元素个数）✅
- **`2[a]` 合法**，等于 `a[2]`（`[]` 只是 `*()` 的语法糖）✅
- **数组作参数会退化**：`wrong_length(a)` 返回 **2** 而不是 5 ✅
- **`char *p = "..."` 改了就崩**：字面量在只读段 ✅

---

## 九、Clang 是怎么装上的（以及中间踩到的坑）

### 9.1 先说结论

笔记让你「Windows 装 LLVM」，但**官方 LLVM 安装包在这台机器上装不了**
—— 不是你操作有问题，是系统策略拦的。最后改用 **llvm-mingw 便携版**，
效果完全一样：命令还是 `clang`，版本更新（23.1.2），体积还更小（0.7 GB vs 官方 3~4 GB）。

### 9.2 官方 LLVM 安装包为什么装不了

**根因：Windows 开着「智能应用控制（Smart App Control，简称 SAC）」。**
SAC 会拦未签名的程序，而 **LLVM 官方安装包本身就没有数字签名**。

| 尝试 | 结果 |
| --- | --- |
| 双击 `LLVM-23.1.2-win64.msi` | 没反应（被策略拦下） |
| 命令行 `msiexec /i` | 装到一半中止，日志返回 **1625**（"此安装被系统策略禁止"） |
| `msiexec /a` 提取文件模式 | 同样 1625 |

排除了其他可能：安装包完好（SHA256 与官方一致）、没有组策略限制、
没有 AppLocker、磁盘空间充足、`.msi` 关联正常。

### 9.3 最后采用的方案：llvm-mingw 便携版

- 来源：<https://github.com/mstorsjo/llvm-mingw>
- 版本：`llvm-mingw-20260922-ucrt-x86_64`
- 校验：SHA256 与 GitHub 官方 API 公布值一致
- 位置：`D:\c++ai\llvm`（和 Cursor 放在一起）
- **为什么比官方版更合适**：官方 Windows 版 clang 需要 **Visual Studio 工具链**
  才能链接出 exe（否则报 `'stdio.h' file not found`），而这台机器没有 VS / Windows SDK；
  llvm-mingw **自带 MinGW 运行时，开箱即用**。

> 下载说明：GitHub 直连在你这网络上是断的，走了加速镜像并断点续传。
> 两个安装包的 SHA256 都与官方 API 公布值逐一核对一致。

### 9.4 官方安装包还留着

`C:\Users\Jiang\Downloads\LLVM-23.1.2-win64.msi`（609.8 MB）还在，没删。
以后如果需要（比如关了 SAC），可以直接双击。当前**不需要**它。

---

## 十、Git 与 GitHub

- 仓库：<https://github.com/jiang270331/c_learning>
- 本机 Git：MinGit 2.55.0
- **你这网络对 `github.com` 时通时断** —— `git push` 失败就隔几秒重试，通常第 1~3 次能过
- 每次学完把笔记和程序推上去，就是最可靠的备份

```powershell
git add -A
git commit -m "说明"
git push origin main          # 失败就重试
```
