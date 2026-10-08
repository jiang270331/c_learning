@echo off
rem ============================================================
rem  debug-build.cmd - build a debug version for F5 debugging
rem
rem  Usage:  debug-build.cmd ptr1.c
rem
rem  The compiler is auto-selected, and the choice is decided by
rem  actually TRYING to compile - never by an error code alone.
rem
rem  Why: Smart App Control (SAC) on this machine blocks
rem  llvm-mingw's clang at random. Measured behaviour:
rem    - clang --version may succeed, while the real compile is
rem      blocked and produces no output file at all
rem    - clang then exits with -1058471934 (an unsigned 32-bit
rem      value) and cmd's "if errorlevel 1" does NOT reliably catch it
rem  Both checks below therefore look for the OUTPUT FILE, which is
rem  the only trustworthy signal. Verified: gcc 5/5 - and gcc is what
rem  actually runs on this machine today.
rem
rem  Why a separate script instead of putting the command into
rem  .vscode/tasks.json:
rem    1. Debug needs -g, else the VARIABLES panel stays empty.
rem    2. clang additionally needs -Wl,--disable-dynamicbase, and that
rem       option contains a comma which PowerShell treats as an array
rem       separator. A .cmd file avoids all the escaping trouble.
rem
rem  RULES FOR EDITING THIS FILE:
rem    RULE 1: keep it pure ASCII. cmd.exe reads .cmd with the OEM
rem            codepage (GBK on Chinese Windows), so any UTF-8
rem            non-ASCII byte - even inside a rem comment - breaks it.
rem    RULE 2: do NOT add "chcp 65001" here. The default GBK console
rem            is what makes the Chinese program output show correctly.
rem    RULE 3: never put "set X=C:\Program Files (x86)\..." inside a
rem            parenthesised if-block. The ")" in "(x86)" closes the
rem            block early; cmd then reports something like
rem            "\Dev-Cpp\MinGW64\bin\gcc.exe was unexpected at this
rem            time". Assign such paths on their own line instead.
rem ============================================================
setlocal

set "SRC=%~1"
if "%SRC%"=="" (
    echo Usage: debug-build.cmd ^<source-file^>
    exit /b 1
)

set "ROOT=%~dp0"
set "NAME=%~n1"
set "OUT=%ROOT%build\%NAME%_debug.exe"
set "PROBE=%ROOT%build\_probe.exe"
set "PROBESRC=%ROOT%build\_probe.c"

if not exist "%ROOT%build" mkdir "%ROOT%build"

rem Tiny program used only to test whether a compiler really works.
> "%PROBESRC%" echo #include ^<stdio.h^>
>>"%PROBESRC%" echo int main(void^){return 0;}

rem ---------------- candidates ----------------
rem Paths assigned OUTSIDE any if-block on purpose (see RULE 3).
set "CLANG=D:\c++ai\llvm\bin\clang.exe"
set "GCC=C:\Program Files (x86)\Dev-Cpp\MinGW64\bin\gcc.exe"

set "CC="
set "CCNAME="
set "EXTRA="

call :probe "%CLANG%" "-Wl,--disable-dynamicbase" "clang"
if defined CC goto have_cc

call :probe "%GCC%" "-static" "gcc (Dev-C++)"
if defined CC goto have_cc

echo [ERROR] no usable C compiler found.
echo         tried clang: %CLANG%
echo         tried gcc  : %GCC%
del "%PROBESRC%" "%PROBE%" >nul 2>&1
exit /b 1

rem ----------------------------------------------------------
rem  :probe <compiler> <extra-flags> <label>
rem  Compiles the probe program and trusts only the produced .exe.
rem ----------------------------------------------------------
:probe
if not exist %1 exit /b 0
del "%PROBE%" >nul 2>&1
%1 "%PROBESRC%" -std=c99 %~2 -o "%PROBE%" >nul 2>&1
if not exist "%PROBE%" exit /b 0
set "CC=%~1"
set "CCNAME=%~3"
set "EXTRA=%~2"
exit /b 0

:have_cc
del "%PROBESRC%" "%PROBE%" >nul 2>&1

echo compiler : %CC%   [%CCNAME%]
echo source   : %ROOT%%SRC%
echo output   : %OUT%
echo mode     : debug (-g, -O0, debug-friendly link)

del "%OUT%" >nul 2>&1
"%CC%" "%ROOT%%SRC%" -std=c99 -Wall -g -O0 %EXTRA% -o "%OUT%"

rem Decide by the artefact, not the exit code (see header note).
if not exist "%OUT%" (
    echo.
    echo [FAILED] no output file produced. The compiler was most
    echo          likely blocked by Smart App Control. Just run it
    echo          again - the block is intermittent.
    exit /b 1
)

echo.
echo [OK] built %OUT%
exit /b 0