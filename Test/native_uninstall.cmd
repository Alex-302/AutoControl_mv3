@echo off
rem native_uninstall.cmd - one-click launcher for native_uninstall.ps1.
rem
rem PowerShell execution policy (Restricted on a fresh Windows) blocks a .ps1
rem started by double-click; a .cmd is NOT covered by that policy. This wrapper
rem runs the real script in a single bypassed PowerShell process (no admin).
rem All flags are forwarded, e.g.:
rem   native_uninstall.cmd -Force -KeepFiles
rem   native_uninstall.cmd -KeepProcesses -KeepRegistry
powershell -NoProfile -ExecutionPolicy Bypass -File "%~dp0native_uninstall.ps1" %*
exit /b %ERRORLEVEL%
