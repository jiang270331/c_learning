@echo off
rem ============================================================
rem  cpp.cmd  --  build & run one C++ file (with C++17)
rem  usage:  cpp cpp17_test        (name without .cpp)
rem          cpp                   (build & run ALL .cpp files)
rem
rem  PURE ASCII on purpose: cmd.exe reads .cmd as GBK.
rem
rem  Why this exists:
rem    The algorithm-association selection requires C++17.
rem    `g++` in PATH is clang 23 (supports C++17/20) - verified.
rem    Dev-C++'s g++ 4.9.2 does NOT support C++17, so it is only
rem    used as a last-resort fallback (with -std=c++11).
rem ============================================================
setlocal

set "HERE=%~dp0"
set "LLVM_GPP=D:\c++ai\llvm\bin\g++.exe"
set "LLVM_CLANGPP=D:\c++ai\llvm\bin\clang++.exe"
set "DEVGPP=C:\Program Files (x86)\Dev-Cpp\MinGW64\bin\g++.exe"

if not exist "%HERE%build" mkdir "%HERE%build"

rem Pick a C++17-capable compiler first.
set "CC="
set "STD=-std=c++17"
if exist "%LLVM_GPP%" (
    set "CC=%LLVM_GPP%"
) else if exist "%LLVM_CLANGPP%" (
    set "CC=%LLVM_CLANGPP%"
) else if exist "%DEVGPP%" (
    set "CC=%DEVGPP%"
    set "STD=-std=c++11"
)

if not defined CC (
    echo [X] No C++ compiler found.
    exit /b 1
)

if "%~1"=="" goto :ALL

set "SRC=%HERE%%~1.cpp"
if not exist "%SRC%" (
    echo [X] Not found: %~1.cpp
    echo     Available .cpp files:
    for %%f in ("%HERE%*.cpp") do echo       %%~nf
    exit /b 1
)

set "EXE=%HERE%build\%~1.exe"
echo [build] %~1.cpp   (%STD%)
"%CC%" %STD% -O2 -Wall "%SRC%" -o "%EXE%"
if not exist "%EXE%" (
    echo [X] Compile failed.
    exit /b 1
)
echo [run]   %~1.exe
echo ------------------------------------------------------------
"%EXE%"
set RC=%ERRORLEVEL%
echo ------------------------------------------------------------
echo [exit]  %RC%   (0 = normal, other = runtime error / WA)
exit /b %RC%

:ALL
for %%f in ("%HERE%*.cpp") do (
    echo.
    echo ========== %%~nf.cpp ==========
    "%CC%" %STD% -O2 -Wall "%%f" -o "%HERE%build\%%~nf.exe" 2>nul
    if exist "%HERE%build\%%~nf.exe" (
        "%HERE%build\%%~nf.exe"
        echo [exit] %ERRORLEVEL%
    ) else (
        echo   [compile failed]
    )
)
exit /b 0
