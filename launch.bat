@echo off
REM Valorant ESP Launcher

echo Starting Valorant ESP...
echo.

REM Check if executable exists
if not exist "bin\ValorantESP.exe" (
    echo Error: ValorantESP.exe not found!
    echo Please build the project first.
    pause
    exit /b 1
)

REM Set library path
set PATH=%~dp0lib;%PATH%

REM Run the application
cd /d "%~dp0"
bin\ValorantESP.exe

if errorlevel 1 (
    echo.
    echo An error occurred!
    pause
)
