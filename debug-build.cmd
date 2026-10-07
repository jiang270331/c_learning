@echo off
rem ============================================================
rem  debug-build.cmd - build a debug version for F5 debugging
rem
rem  Usage:  debug-build.cmd ptr1.c
rem
rem  Why a separate script:
rem    1. Debugging needs -g, otherwise the VARIABLES panel is empty.
rem    2. It also needs -Wl,--disable-dynamicbase (turn off ASLR).
rem       Without it, gdb 7.8.1 (shipped with Dev-C++) cannot set
rem       breakpoints and fails with:
rem         "Cannot insert breakpoint 1"
rem         "Cannot access memory at address 0x140001476"
rem    3. That option contains a comma, which PowerShell treats as an
rem       array separator. Running it from a .cmd file avoids the
rem       whole shell-escaping problem.
rem
rem  KEEP THIS FILE PURE ASCII.
rem    cmd.exe reads .cmd files using the OEM codepage (GBK on a
rem    Chinese Windows). Any UTF-8 non-ASCII byte here gets misread
rem    and breaks the script, even inside a rem comment.
rem ============================================================
setlocal

rem Switch the console to UTF-8 (codepage 65001). Source files are
rem UTF-8, so Chinese program output is UTF-8 too, while a fresh
rem Windows console defaults to GBK (936).
chcp 65001 >nul

set "SRC=%~1"
if "%SRC%"=="" (
    echo Usage: debug-build.cmd ^<source-file^>
    exit /b 1
)

set "ROOT=%~dp0"
set "CLANG=D:\c++ai\llvm\bin\clang.exe"
set "NAME=%~n1"
set "OUT=%ROOT%build\%NAME%_debug.exe"

if not exist "%ROOT%build" mkdir "%ROOT%build"
if not exist "%CLANG%" (
    echo [ERROR] clang not found: %CLANG%
    exit /b 1
)

echo compiler : %CLANG%
echo source   : %ROOT%%SRC%
echo output   : %OUT%
echo mode     : debug (-g debug info, ASLR disabled)

"%CLANG%" "%ROOT%%SRC%" -std=c99 -Wall -g -Wl,--disable-dynamicbase -o "%OUT%"

if errorlevel 1 (
    echo.
    echo [FAILED] compile error, see messages above.
    exit /b 1
)

echo.
echo [OK] built %OUT%
exit /b 0
