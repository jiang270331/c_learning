@echo off
chcp 65001 >nul
setlocal
rem Double-click this file to compile and run every .c file in this folder.
rem It wraps the PowerShell script so the Restricted execution policy cannot block it.

set "PS=powershell"
if exist "%SystemRoot%\System32\WindowsPowerShell\v1.0\powershell.exe" set "PS=%SystemRoot%\System32\WindowsPowerShell\v1.0\powershell.exe"
where pwsh >nul 2>nul && set "PS=pwsh"

"%PS%" -NoProfile -ExecutionPolicy Bypass -File "%~dp0run-all.ps1" %*
echo.
pause
endlocal
