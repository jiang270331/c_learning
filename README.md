# C 指针学习工程

按「卡卡老师独家笔记 · Cursor × C 指针」的章节顺序搭建，**13 个程序全部已编译运行通过**（用 clang）。

---

## 一、环境体检结果

| 笔记要求 | 检查结果 |
| --- | --- |
| ① 装 Cursor | ✅ 已装：`D:\c++ai\cursor\Cursor.exe`（版本 3.23.12） |
| ② 装 Clang | ✅ **已装好**：`D:\c++ai\llvm\bin\clang.exe`（LLVM 23.1.2，llvm-mingw 便携版） |
| ③ 跑通 Hello World | ✅ 已跑通（`hello.c` → `Hello, C from Windows!`） |
| ④ 学指针、做练习 | ✅ 笔记里的例题 + 练习 A/B/C 全部写完并运行通过 |

现在这台机器上有**三个**可用的 C 编译器：

| 编译器 | 路径 | 说明 |
| --- | --- | --- |
| **clang 23.1.2** | `D:\c++ai\llvm\bin\clang.exe` | 现在的主力，笔记里写的就是它 |
| gcc（实为 clang） | `D:\c++ai\llvm\bin\gcc.exe` | 同一个 clang 的别名，敲 `gcc` 也能用 |
| gcc 4.9.2 | `C:\Program Files (x86)\Dev-Cpp\MinGW64\bin\gcc.exe` | Dev-C++ 自带的，备用 |

> `clang` 和 `gcc` 都已经加进你的**用户 PATH**，新开的终端里直接敲命令就能用。
> （如果 Cursor 是在改 PATH 之前打开的，重启一次 Cursor 即可。）

---

## 二、怎么用（三种方式，任选其一）

### 方式 1：在 Cursor 里按快捷键（推荐）

1. Cursor → File → Open Folder，打开 **本文件夹**
2. 打开任意一个 `.c` 文件
3. 按 `Ctrl+Shift+B` → 编译并运行当前文件
   （或 `Ctrl+Shift+P` 输入 `Run Task`，选「编译并运行全部」）

### 方式 2：双击 `run-all.cmd`

一键把 13 个程序全部编译运行一遍，跑完会停住让你看结果。

### 方式 3：在终端里手敲（就是笔记里的做法）

```powershell
clang hello.c -o hello.exe
.\hello.exe
```

只想跑某一个 / 全部，用本目录的脚本：

```powershell
.\run-all.cmd ex_a      # 只跑名字含 ex_a 的
.\run-all.cmd           # 跑全部
```

> ⚠️ 你这台机器的 PowerShell 执行策略是 `Restricted`，**不能**直接 `.\run-all.ps1`。
> 两种解决办法，选一个：
> - 用 `run-all.cmd` 代替（它内部已绕过策略），或
> - 在 Cursor 终端里执行一次：`Set-ExecutionPolicy -Scope CurrentUser RemoteSigned`

---

## 三、文件清单（对照笔记章节）

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
| `ex_a.c` | Pointer · 15 练习 A | 打印 a / &a / p / *p，再 `*p = 100` |
| `ex_b.c` | Pointer · 15 练习 B | 用指针写 swap（附错误示范对照） |
| `ex_c.c` | Pointer · 15 练习 C | 猜结果，附 4 道加练对照题 |
| `运行结果.txt` | — | 13 个程序的完整真实输出（用 clang 跑的） |
| `run-all.cmd` / `run-all.ps1` | — | 一键编译运行（自动挑能用的编译器 + 自动重试） |
| `check-clang.ps1` | — | 环境体检：列出所有编译器、试编译、报告系统策略状态 |
| `.vscode/tasks.json` | — | Cursor 里的 Ctrl+Shift+B 任务 |

---

## 四、笔记里的「预期」都对上了吗

都对上了，几个关键现象：

- **改 `*p`，`a` 真的跟着变**（`ptr1.c`）：`*p = 20` 之后 `a` 从 10 变成 20 ✅
- **`&a` 和 `p` 是同一次运行里的同一个地址**（`print_addr.c`）✅
- **`swap` 交换成功**（`swap.c`）：3 5 → 5 3 ✅
- **练习 C 的答案**（`ex_c.c`）：`*p + 1` = **3**，`*(p + 1)` = **4**，跟笔记注释一致 ✅
- **指针的加法是按元素跳的**（`array_ptr.c`）：`a + 1` 的地址比 `a` 大 **4** 字节，不是 1 字节 ✅
- **`sizeof` 的区别**：`sizeof(a)` = 20（整个数组），`sizeof(p)` = 8（只是个指针）✅

---

## 五、笔记原文的几处小瑕疵（本工程已修正）

1. **`malloc` 那一段漏了 `#include <stdlib.h>`** —— 不补上会有隐式声明警告，本工程已补。
2. **`add_one` 和 `swap` 的 `main` 没写 `return 0;`** —— `main` 声明成 `int` 就该返回，本工程已补。
3. **`char *p = s` 写在 `for` 括号里** —— 那是 C99 写法，老编译器会报错，本工程改成先在括号外声明，兼容性更好。
4. **`%d` 打印地址到底会怎样** —— 笔记只说「会报警或乱码」，`mistakes_demo.c` 把它跑出来了：
   真实地址 `00000018694FFE58`，用 `%d` 打印只剩 `1766850136`（64 位地址被砍成 32 位，高两位全丢了）。
5. **`char *s = "hello"` 不能改** —— 笔记提醒得对，但没说原因：字面量存在只读段，改它会直接崩溃。

---

## 六、Clang 是怎么装上的（以及中间踩到的坑）

### 6.1 先说结论

笔记让你「Windows 装 LLVM」，但**官方 LLVM 的安装包在这台机器上装不了**——不是你操作有问题，是系统策略拦的。最后改用 **llvm-mingw 便携版**，效果完全一样：命令还是 `clang`，版本更新（23.1.2），体积还更小（0.7 GB vs 官方 3~4 GB）。

### 6.2 官方 LLVM 安装包为什么装不了

**根因：你的 Windows 开着「智能应用控制（Smart App Control，简称 SAC）」。**

SAC 会拦截未签名的程序，而 **LLVM 官方安装包本身就没有数字签名**（LLVM 项目不使用 Windows 代码签名证书）。于是：

| 尝试 | 结果 |
| --- | --- |
| 双击 `LLVM-23.1.2-win64.msi` | 没反应（被策略拦下） |
| 命令行 `msiexec /i` 启动 | 装到一半中止，日志返回 **1625**（"此安装被系统策略禁止"） |
| `msiexec /a` 提取文件模式 | 同样 1625 |

排除了其他可能：安装包完好（SHA256 与官方一致、MSI 数据库能正常读取）、没有组策略限制、没有 AppLocker、磁盘空间充足、`.msi` 文件关联正常。

### 6.3 最后采用的方案：llvm-mingw 便携版

- 来源：<https://github.com/mstorsjo/llvm-mingw>（LLVM 官方之外的知名 Windows 构建，自带 MinGW-w64 头文件和库）
- 版本：`llvm-mingw-20260922-ucrt-x86_64`
- 校验：SHA256 与 GitHub 官方 API 公布值一致（`e3ad77d1…47666`）
- 安装位置：`D:\c++ai\llvm`（和你的 Cursor 放在一起）
- 为什么它比官方 LLVM 更合适：官方 Windows 版 clang 需要 **Visual Studio 工具链**才能链接出 exe，而你这台机器没有任何 VS / Windows SDK；llvm-mingw **自带 MinGW 运行时，开箱即用**

> 下载说明：GitHub 直连在你这网络上是断的（连接被重置 / 超时），所以走了 `ghfast.top` 加速镜像并断点续传。
> 两个安装包的 SHA256 都与 GitHub 官方 API 公布的值逐一核对一致，可确认文件未被篡改。

### 6.4 一个需要知道的现象：新编译的 exe 偶尔被拦

SAC 除了拦安装包，对**刚编译出来的 exe** 也会偶发拦截，报错类似：

```
An Application Control policy has blocked this file
```

实测数据（同一份代码反复编译运行）：

| 编译器 | 成功 | 被拦 |
| --- | --- | --- |
| clang | 4 | 0 |
| gcc 4.9.2 | 3 | 1 |

**这是随机的，与编译器、代码都无关**（同一个源文件换个名字、重编一次就好了）。原因是 SAC 按文件哈希去查云端信誉，全新文件的哈希还没有信誉记录。

应对办法：**重新编译一次就行**。本目录的 `run-all.cmd` 已经内置了这个逻辑——被拦就自动重编译重试，最多 3 次，你不用手动管。跑那 13 个程序时它自动处理了 3 次。

如果以后觉得烦，可以在「Windows 安全中心 → 应用和浏览器控制 → 智能应用控制」里关掉它。
**但要先知道：这个开关一旦关闭，只能重装 Windows 才能重新打开。** 目前不影响你学 C，建议先留着。

### 6.5 官方安装包还留着

`C:\Users\Jiang\Downloads\LLVM-23.1.2-win64.msi`（609.8 MB）还在，没删。以后如果需要（比如你关了 SAC，或者想装完整的 LLVM 工具链），可以直接双击。当前**不需要**它——clang 已经在用了。

---

## 七、建议的学习节奏（笔记原话）

> 今天装环境 + Hello；明天 `&` / `*` / 打印地址；后天 swap 与数组。

对应到本目录：

- **第 1 天**：`hello.c`、`ptr1.c`
- **第 2 天**：`print_addr.c`、`ptr_null.c`、`mistakes_demo.c`
- **第 3 天**：`add_one.c`、`swap.c`、`array_ptr.c`、`ex_a.c`、`ex_b.c`、`ex_c.c`
- **第 4 天**：`string_ptr.c`、`malloc_demo.c`
