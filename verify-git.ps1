# verify-git.ps1 —— 确认 git / clang / cursor 三件套都能用
#
# 背景：环境变量是「进程启动时」继承的。用脚本改了 PATH 之后，
#       已经在运行的窗口（包括 Cursor、已开的终端）不会自动更新，
#       需要重启 Cursor，或者注销 / 重新登录一次 Windows。
#
# 用法：在 Cursor 的终端里
#       powershell -NoProfile -ExecutionPolicy Bypass -File .\verify-git.ps1

try { [Console]::OutputEncoding = [System.Text.Encoding]::UTF8 } catch {}
$ErrorActionPreference = 'Continue'

Write-Host "`n=== 三件套检查 ===" -ForegroundColor Cyan

$tools = @(
    @{ Name = 'git';    Note = '版本管理（MinGit 便携版，无需管理员）' },
    @{ Name = 'clang';  Note = 'C 编译器（笔记里的主力）' },
    @{ Name = 'cursor'; Note = 'Cursor 命令行入口' }
)

$bad = 0
foreach ($t in $tools) {
    $c = Get-Command $t.Name -ErrorAction SilentlyContinue
    if ($c) {
        Write-Host ("  [可用] {0,-7} {1}" -f $t.Name, $c.Source) -ForegroundColor Green
    } else {
        Write-Host ("  [缺失] {0,-7} {1}" -f $t.Name, $t.Note) -ForegroundColor Red
        $bad++
    }
}

Write-Host "`n=== 版本 ===" -ForegroundColor Cyan
if (Get-Command git -ErrorAction SilentlyContinue)   { git --version }
if (Get-Command clang -ErrorAction SilentlyContinue) { (clang --version | Select-Object -First 1) }

Write-Host "`n=== Git 身份（提交时显示的作者） ===" -ForegroundColor Cyan
if (Get-Command git -ErrorAction SilentlyContinue) {
    "  user.name  : " + (git config --global --get user.name)
    "  user.email : " + (git config --global --get user.email)
}

Write-Host "`n=== 结论 ===" -ForegroundColor Cyan
if ($bad -eq 0) {
    Write-Host "  三件套齐全，可以直接跟着笔记往下学。" -ForegroundColor Green
} else {
    Write-Host "  有 $bad 项找不到。" -ForegroundColor Yellow
    Write-Host "  如果刚改过 PATH，请先【重启 Cursor】或【注销并重新登录 Windows】再跑一次本脚本。" -ForegroundColor Yellow
}

Write-Host "`n=== 用户 PATH 现状 ===" -ForegroundColor Cyan
[Environment]::GetEnvironmentVariable('Path','User') -split ';' |
    Where-Object { $_ } | ForEach-Object { "  $_" }
