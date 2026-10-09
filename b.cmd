@echo off
rem ============================================================
rem  b.cmd  --  quick build & run one .c file
rem  usage:  b ptr_sizeof        (name without .c)
rem          b                   (build & run ALL .c files)
rem  pure ASCII on purpose: cmd.exe reads this file as GBK
rem ============================================================
setlocal

set "HERE=%~dp0"
set "GCC=C:\Program Files (x86)\Dev-Cpp\MinGW64\bin\gcc.exe"
set "CLANG=D:\c++ai\llvm\bin\clang.exe"
if not exist "%GCC%" set "GCC="

if not exist "%HERE%build" mkdir "%HERE%build"

set "CC="
if defined GCC (
    "%GCC%" --version >nul 2>&1 && set "CC=%GCC%"
)
if not defined CC if exist "%CLANG%" set "CC=%CLANG%"

if not defined CC (
    echo [X] No C compiler found.
    exit /b 1
)

if "%~1"=="" goto :ALL

set "SRC=%HERE%%~1.c"
if not exist "%SRC%" (
    echo [X] Not found: %~1.c
    echo     Available:
    for %%f in ("%HERE%*.c") do echo       %%~nf
    exit /b 1
)

set "EXE=%HERE%build\%~1.exe"
echo [build] %~1.c
"%CC%" "%SRC%" -std=c99 -Wall -o "%EXE%"
if not exist "%EXE%" (
    echo [X] Compile failed.
    exit /b 1
)
echo [run]   %~1.exe
echo ------------------------------------------------------------
"%EXE%"
echo ------------------------------------------------------------
exit /b 0

:ALL
for %%f in ("%HERE%*.c") do (
    echo.
    echo ========== %%~nf.c ==========
    "%CC%" "%%f" -std=c99 -Wall -o "%HERE%build\%%~nf.exe" 2>nul
    if exist "%HERE%build\%%~nf.exe" (
        "%HERE%build\%%~nf.exe"
    ) else (
        echo   [compile failed]
    )
)
exit /b 0
