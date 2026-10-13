@echo off
rem ============================================================
rem  Interview prep reminder launcher
rem
rem  Fired by scheduled task: DSH_InterviewPrep -> 2026/10/17 20:00
rem  NOT in the Startup folder, so it never runs on boot.
rem
rem  PURE ASCII on purpose - cmd.exe reads .cmd as GBK.
rem  The Chinese text lives in interview_prep.txt (UTF-8),
rem  read by PowerShell with explicit UTF-8 encoding.
rem ============================================================
setlocal

set "HERE=%~dp0"
set "TXT=%HERE%interview_prep.txt"
set "FLAG=%HERE%interview_prep.flag"

if exist "%FLAG%" exit /b 0

if not exist "%TXT%" (
    echo [X] Text file not found:
    echo     %TXT%
    pause
    exit /b 1
)

powershell -NoProfile -ExecutionPolicy Bypass -Command "[Console]::OutputEncoding=[System.Text.Encoding]::UTF8; $t = Get-Content -LiteralPath '%TXT%' -Encoding UTF8 -Raw; Write-Host $t"

echo done > "%FLAG%"

echo.
echo ============================================================
echo   Press any key to close this window.
echo ============================================================
pause
exit /b 0
