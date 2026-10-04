<#
  check-clang.ps1 —— C 编译环境体检

  做三件事：
    1. 列出这台机器上所有能找到的 C 编译器
    2. 逐个试编译一个最小程序，看谁真的能产出 exe
    3. 报告「智能应用控制」的状态（它会影响新编译出的 exe 能否运行）

  用法（在 Cursor 的终端里，切到本目录）：
      powershell -NoProfile -ExecutionPolicy Bypass -File .\check-clang.ps1
#>

try { [Console]::OutputEncoding = [System.Text.Encoding]::UTF8 } catch {}
$ErrorActionPreference = 'Continue'

function Section($t) { Write-Host "`n=== $t ===" -ForegroundColor Cyan }

$tmp = Join-Path $env:TEMP 'cc_check'
New-Item -ItemType Directory -Force -Path $tmp | Out-Null
$src = Join-Path $tmp 'probe.c'
$exe = Join-Path $tmp 'probe.exe'
Set-Content -Encoding ASCII -Path $src -Value @'
#include <stdio.h>
int main(void) { printf("ok\n"); return 0; }
'@

# ------------------------------------------------ 1. 收集候选编译器
Section "1. 找到的 C 编译器"

$cands = New-Object System.Collections.Generic.List[object]

foreach ($n in @('clang','gcc')) {
    $c = Get-Command $n -ErrorAction SilentlyContinue
    if ($c) { $cands.Add([pscustomobject]@{ Name = "$n (PATH 里)"; Path = $c.Source }) }
}
foreach ($p in @(
    'D:\c++ai\llvm\bin\clang.exe',
    'C:\Program Files\LLVM\bin\clang.exe',
    'C:\Program Files (x86)\Dev-Cpp\MinGW64\bin\gcc.exe',
    'C:\msys64\ucrt64\bin\gcc.exe',
    'C:\MinGW\bin\gcc.exe')) {
    if ((Test-Path $p) -and -not ($cands | Where-Object { $_.Path -eq $p })) {
        $cands.Add([pscustomobject]@{ Name = (Split-Path $p -Leaf); Path = $p })
    }
}

if ($cands.Count -eq 0) {
    Write-Host "没找到任何 C 编译器。" -ForegroundColor Red
    Write-Host "  → 本目录的 run-all.cmd 需要至少一个可用的编译器。" -ForegroundColor Red
    exit 1
}
$cands | ForEach-Object { Write-Host ("  {0,-24} {1}" -f $_.Name, $_.Path) }

# ------------------------------------------------ 2. 逐个试编译
Section "2. 试编译（真能产出 exe 的才算数）"

$usable = @()
foreach ($c in $cands) {
    Remove-Item $exe -Force -ErrorAction SilentlyContinue
    $ok = $false
    try {
        & $c.Path $src -std=c99 -o $exe *> $null
        $ok = Test-Path $exe
    } catch { $ok = $false }

    if ($ok) {
        $ver = (& $c.Path --version 2>&1 | Select-Object -First 1)
        Write-Host ("  [可用] {0}" -f $c.Name) -ForegroundColor Green
        Write-Host ("         {0}" -f $ver) -ForegroundColor DarkGray
        $usable += $c
    } else {
        Write-Host ("  [不可用] {0}  编译不出 exe" -f $c.Name) -ForegroundColor Red
    }
}
Remove-Item $src, $exe -Force -ErrorAction SilentlyContinue

# ------------------------------------------------ 3. 智能应用控制状态
Section "3. 智能应用控制（Smart App Control）状态"

$state = $null
try { $state = (Get-ItemProperty 'HKLM:\SYSTEM\CurrentControlSet\Control\CI\Policy' -ErrorAction Stop).VerifiedAndReputablePolicyState } catch {}

switch ($state) {
    0 {
        Write-Host "  已关闭 —— 新编译出的 exe 不会被拦。" -ForegroundColor Green
    }
    1 {
        Write-Host "  开启并强制执行。" -ForegroundColor Yellow
        Write-Host "  影响：刚编译出来的 exe 偶尔会在第一次运行时被拦下，报错类似" -ForegroundColor Yellow
        Write-Host "        「An Application Control policy has blocked this file」。" -ForegroundColor Yellow
        Write-Host "        这是随机的（与编译器无关），重新编译一次换个文件哈希通常就通过；" -ForegroundColor Yellow
        Write-Host "        本目录的 run-all.cmd 已内置自动重编译重试，不用你手动管。" -ForegroundColor Yellow
    }
    2 {
        Write-Host "  仅评估模式（不拦截）。" -ForegroundColor Green
    }
    default {
        Write-Host "  读不到状态（可能是较旧的 Windows）。" -ForegroundColor DarkGray
    }
}

# ------------------------------------------------ 4. 结论
Section "4. 结论"
if ($usable.Count -gt 0) {
    Write-Host ("  可用编译器 {0} 个，首选：{1}" -f $usable.Count, $usable[0].Path) -ForegroundColor Green
    Write-Host "  直接双击 run-all.cmd 即可编译运行本目录全部 13 个程序。" -ForegroundColor Green
} else {
    Write-Host "  没有可用的编译器，请先装一个。" -ForegroundColor Red
}
