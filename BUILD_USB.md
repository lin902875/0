# 编译并打包成 U 盘版本

这个脚本会自动编译项目并生成可以在 U 盘上运行的版本。

## Windows 编译脚本

创建一个 `build_usb.bat` 文件：

```batch
@echo off
REM ============================================
REM Build and Package for USB
REM ============================================

setlocal enabledelayedexpansion

set PROJECT_DIR=%cd%
set BUILD_DIR=%PROJECT_DIR%\build
set OUTPUT_DIR=%PROJECT_DIR%\usb_package
set VCPKG_DIR=D:\vcpkg

echo ============================================
echo Build Valorant ESP for USB
echo ============================================
echo.

REM Check dependencies
if not exist "%VCPKG_DIR%" (
    echo [ERROR] vcpkg not found at %VCPKG_DIR%
    echo Please modify VCPKG_DIR in this script
    pause
    exit /b 1
)

REM Create build directory
if not exist "%BUILD_DIR%" mkdir "%BUILD_DIR%"
cd /d "%BUILD_DIR%"

REM Configure
echo [1/4] Configuring project...
cmake -G "Visual Studio 16 2019" -A x64 ^
  -DCMAKE_TOOLCHAIN_FILE=%VCPKG_DIR%\scripts\buildsystems\vcpkg.cmake ^
  -DCMAKE_BUILD_TYPE=Release ^
  ..

if %errorlevel% neq 0 (
    echo [ERROR] Configuration failed
    pause
    exit /b 1
)

REM Build
echo [2/4] Building project...
cmake --build . --config Release

if %errorlevel% neq 0 (
    echo [ERROR] Build failed
    pause
    exit /b 1
)

REM Create USB package structure
echo [3/4] Creating USB package...
if exist "%OUTPUT_DIR%" rmdir /s /q "%OUTPUT_DIR%"
mkdir "%OUTPUT_DIR%\bin"
mkdir "%OUTPUT_DIR%\lib"
mkdir "%OUTPUT_DIR%\config"
mkdir "%OUTPUT_DIR%\logs"

REM Copy executable
copy "%BUILD_DIR%\bin\Release\ValorantESP.exe" "%OUTPUT_DIR%\bin\"

REM Copy DLLs from vcpkg
echo [4/4] Copying dependencies...
for /r "%VCPKG_DIR%\installed\x64-windows\bin" %%F in (opencv*.dll) do (
    copy "%%F" "%OUTPUT_DIR%\lib\"
)

REM Copy configuration and scripts
copy "%PROJECT_DIR%\launch.bat" "%OUTPUT_DIR%\"
copy "%PROJECT_DIR%\config\settings.ini" "%OUTPUT_DIR%\config\"
copy "%PROJECT_DIR%\USB_GUIDE.md" "%OUTPUT_DIR%\README_USB.md"

echo.
echo ============================================
echo Build Complete!
echo ============================================
echo.
echo USB Package Location: %OUTPUT_DIR%
echo.
echo Next steps:
echo 1. Insert USB drive
echo 2. Copy everything from %OUTPUT_DIR% to USB root
echo 3. Run launch.bat on the USB drive
echo.
pause
```

## 使用方法

1. **修改脚本中的路径**
   ```batch
   set VCPKG_DIR=D:\vcpkg  # 改成你的 vcpkg 路径
   ```

2. **运行编译脚本**
   ```batch
   build_usb.bat
   ```

3. **等待编译完成**
   - 会在项目目录生成 `usb_package` 文件夹

4. **复制到 U 盘**
   ```
   usb_package 文件夹中的所有文件 → 复制到 U 盘根目录
   ```

5. **在 U 盘上运行**
   ```
   在 U 盘中双击 launch.bat
   ```

## 生成的 U 盘结构

```
U:\
├── launch.bat
├── README_USB.md
├── bin\
│   └── ValorantESP.exe
├── lib\
│   ├── opencv_core480.dll
│   ├── opencv_imgproc480.dll
│   └── ...
├── config\
│   └── settings.ini
└── logs\
```

## 常见问题

### Q: 复制 DLL 出错

A: 手动从 `D:\vcpkg\installed\x64-windows\bin\` 复制所有 `opencv*.dll`

### Q: 程序无法运行

A: 检查是否所有 DLL 都已复制到 `lib` 文件夹

### Q: U 盘空间不足

A: 最少需要 500MB 自由空间

---

现在你可以随时从 U 盘启动程序了！
