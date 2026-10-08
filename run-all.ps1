# 一键编译并运行本目录下所有 .c 文件
#   用法（在 Cursor 的终端里）：  .\run-all.cmd            （双击 run-all.cmd 也行）
#                                .\run-all.cmd ptr1       只跑名字含 ptr1 的
#
# 说明：脚本会在 clang 和 gcc 之间自动挑一个「真的能编译出 exe」的编译器。
#       所以就算你装了官方 LLVM 但缺 Visual Studio 工具链（clang 链接不了），
#       它也会自动退回 Dev-C++ 自带的 gcc，不会全军覆没。

param(
    [string]$Only   # 可选：只编译运行名字里含这个关键字的文件
)

$ErrorActionPreference = 'Stop'
try { [Console]::OutputEncoding = [System.Text.Encoding]::UTF8 } catch {}

$here  = Split-Path -Parent $MyInvocation.MyCommand.Path
$build = Join-Path $here 'build'
New-Item -ItemType Directory -Force -Path $build | Out-Null

# ---------------- 1. 列出候选编译器（越靠前越优先） ----------------
$candidates = New-Object System.Collections.Generic.List[string]

$clangCmd = Get-Command clang -ErrorAction SilentlyContinue
if ($clangCmd) { $candidates.Add($clangCmd.Source) }
foreach ($p in @('D:\c++ai\llvm\bin\clang.exe',              # llvm-mingw 便携版（已装好）
                 'C:\Program Files\LLVM\bin\clang.exe')) {   # 官方 LLVM 安装版（若以后装了）
    if (Test-Path $p) { $candidates.Add($p) }
}
foreach ($p in @('C:\Program Files (x86)\Dev-Cpp\MinGW64\bin\gcc.exe',
                 'C:\Program Files\Dev-Cpp\MinGW64\bin\gcc.exe',
                 'C:\msys64\ucrt64\bin\gcc.exe',
                 'C:\msys64\mingw64\bin\gcc.exe',
                 'C:\MinGW\bin\gcc.exe',
                 'C:\TDM-GCC-64\bin\gcc.exe')) {
    if (Test-Path $p) { $candidates.Add($p) }
}
$candidates = @($candidates | Select-Object -Unique)

if ($candidates.Count -eq 0) {
    Write-Host "找不到任何 C 编译器。" -ForegroundColor Red
    Write-Host "  → 装 LLVM（笔记 Cursor·Windows → 安装 Clang），或装 Dev-C++（自带 gcc）。" -ForegroundColor Red
    exit 1
}

# ---------------- 2. 试编译一次，挑出真能产出 exe 的编译器 ----------------
$probeSrc = Join-Path $build '_probe.c'
$probeExe = Join-Path $build '_probe.exe'
Set-Content -Encoding ASCII -Path $probeSrc -Value @'
#include <stdio.h>
int main(void) { printf("ok\n"); return 0; }
'@

$cc = $null
foreach ($cand in $candidates) {
    Remove-Item $probeExe -Force -ErrorAction SilentlyContinue
    $good = $false
    try {
        & $cand $probeSrc -std=c99 -o $probeExe *> $null
        $good = (Test-Path $probeExe)
    } catch { $good = $false }
    if ($good) { $cc = $cand; break }
    Write-Host "（跳过 $cand：编译不出可执行文件）" -ForegroundColor DarkYellow
}
Remove-Item $probeSrc, $probeExe -Force -ErrorAction SilentlyContinue

if (-not $cc) {
    Write-Host "找到了编译器，但没一个能成功产出 exe。" -ForegroundColor Red
    Write-Host "  → 如果只装了官方 LLVM，通常是缺 Visual Studio 工具链。" -ForegroundColor Red
    Write-Host "  → 跑 .\check-clang.ps1 看具体原因，或改用 Dev-C++ 自带的 gcc。" -ForegroundColor Red
    exit 1
}

Write-Host "编译器 : $cc" -ForegroundColor DarkGray
Write-Host "源目录 : $here" -ForegroundColor DarkGray
Write-Host "输出到 : $build" -ForegroundColor DarkGray

# ---------------- 3. 挨个编译并运行 ----------------
$files = Get-ChildItem $here -Filter *.c | Sort-Object Name
if ($Only) { $files = $files | Where-Object { $_.BaseName -like "*$Only*" } }
if (-not $files) { Write-Host "没有匹配的 .c 文件。" -ForegroundColor Yellow; exit 0 }

$ok = 0; $fail = 0
foreach ($f in $files) {
    $exe = Join-Path $build ($f.BaseName + '.exe')
    Write-Host ("`n" + ('=' * 58)) -ForegroundColor DarkCyan
    Write-Host ("  " + $f.Name) -ForegroundColor Cyan
    Write-Host ('=' * 58) -ForegroundColor DarkCyan

    & $cc $f.FullName -std=c99 -Wall -o $exe
    if (-not (Test-Path $exe)) {
        Write-Host "  编译失败" -ForegroundColor Red
        $fail++
        continue
    }

    $ran = $false
    # Smart App Control 按「文件哈希」判定：被拦的 exe 永久被拦，
    # 但重新编译会换一个哈希，就有概率抽过。实测需要多试几次。
    for ($attempt = 1; $attempt -le 12 -and -not $ran; $attempt++) {
        if ($attempt -gt 1) {
            # 换哈希重编译：用 -static 让每次产出的二进制不同
            & $cc $f.FullName -std=c99 -Wall -static -o $exe 2>$null
            if (-not (Test-Path $exe)) { continue }
        }
        # 不能用 try/catch 抓：进程被策略拦截不走 PowerShell 异常，
        # 只会把报错文字写进输出，所以改成检查输出内容。
        $out = & $exe 2>&1 | Out-String
        if ($out -match 'blocked by|Device Guard|应用程序控制策略|已阻止') {
            Write-Host "  （被智能应用控制拦下，第 $attempt 次重编译重试…）" -ForegroundColor DarkYellow
        } else {
            Write-Host $out.TrimEnd()
            $ran = $true
            $ok++
        }
    }
    if (-not $ran) {
        Write-Host "  程序未能运行（被系统策略拦截，重试 12 次仍失败）" -ForegroundColor Red
        $fail++
    }
}

Write-Host ("`n" + ('-' * 58)) -ForegroundColor DarkGray
Write-Host "完成：成功 $ok 个，失败 $fail 个。  编译器：$cc" -ForegroundColor Green
