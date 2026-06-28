# 编译指南

## 系统环境准备

### 1. 安装 Visual Studio 2019+

- 下载：https://visualstudio.microsoft.com/
- 选择 "Desktop development with C++" 工作负载
- 包含 Windows SDK 和 CMake 工具

### 2. 安装 CMake

```bash
# 方式一：使用 chocolatey
choco install cmake

# 方式二：下载安装
# https://cmake.org/download/
```

### 3. 安装 OpenCV

**方式一：使用 vcpkg（推荐）**

```bash
# 克隆 vcpkg
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg
.\bootstrap-vcpkg.bat

# 安装 OpenCV
.\vcpkg install opencv:x64-windows

# 集成到 Visual Studio
.\vcpkg integrate install
```

**方式二：预编译版本**

下载预编译的 OpenCV：https://opencv.org/releases/

解压到合适位置，记住路径。

**方式三：从源代码编译**

```bash
git clone https://github.com/opencv/opencv.git
cd opencv
mkdir build && cd build
cmake -G "Visual Studio 16 2019" -A x64 ..
cmake --build . --config Release
cmake --install .
```

## 编译步骤

### 方式一：使用 CMake GUI

1. 打开 CMake GUI
2. 设置源代码目录：`C:\path\to\ValorantESP`
3. 设置编译目录：`C:\path\to\ValorantESP\build`
4. 点击 "Configure"
   - 选择 "Visual Studio 16 2019"
   - 选择 "x64" 平台
5. 如果使用预编译 OpenCV，设置 `OpenCV_DIR`
6. 点击 "Generate"
7. 打开生成的 `ValorantESP.sln`
8. 在 Visual Studio 中编译

### 方式二：命令行编译

```bash
# 创建编译目录
mkdir build
cd build

# 配置项目（使用 vcpkg）
cmake -G "Visual Studio 16 2019" -A x64 ^
  -DCMAKE_TOOLCHAIN_FILE=C:\path\to\vcpkg\scripts\buildsystems\vcpkg.cmake ..

# 或配置项目（使用预编译 OpenCV）
cmake -G "Visual Studio 16 2019" -A x64 ^
  -DOpenCV_DIR=C:\path\to\opencv\build ..

# 编译
cmake --build . --config Release

# 或使用 Visual Studio 直接编译
msbuild ValorantESP.sln /p:Configuration=Release /p:Platform=x64
```

## 调试步骤

### 在 Visual Studio 中调试

1. 打开 `build/ValorantESP.sln`
2. 设置启动项目为 ValorantESP
3. 设置调试器为 "Native Only"
4. 按 F5 启动调试

### 命令行调试

```bash
# 编译为 Debug 版本
cmake --build . --config Debug

# 运行调试版本
bin\Debug\ValorantESP.exe
```

## 常见编译错误

### 1. 找不到 OpenCV

**错误**：`Could not find OpenCV`

**解决**：
```bash
# 指定 OpenCV 路径
cmake -DOpenCV_DIR=C:\path\to\opencv\build ..

# 或使用 vcpkg
cmake -DCMAKE_TOOLCHAIN_FILE=path/to/vcpkg.cmake ..
```

### 2. DirectX SDK 缺失

**错误**：`Cannot open include file 'd3d11.h'`

**解决**：
- 确保安装了 Windows SDK
- 在 Visual Studio 中修改 Include 目录：
  - 项目属性 > VC++ 目录 > 包含目录
  - 添加 Windows SDK 路径

### 3. C++17 不支持

**错误**：`C++ standard not recognized`

**解决**：
- 在 CMakeLists.txt 中确认设置了 C++17
- 或在 Visual Studio 中：
  - 项目属性 > C/C++ > 语言 > C++ 语言标准 > ISO C++17

### 4. 链接错误

**错误**：`Unresolved external symbol`

**解决**：
- 检查库文件路径是否正确
- 确保添加了所有必要的库：
  ```cmake
  target_link_libraries(ValorantESP PRIVATE
      d3d11.lib dxgi.lib dxguid.lib user32.lib gdi32.lib
      ${OpenCV_LIBS}
  )
  ```

## 性能优化编译

为了获得最佳性能，编译为 Release 版本并启用优化：

```bash
cmake --build . --config Release

# 或添加优化标志
cmake -G "Visual Studio 16 2019" -A x64 ^
  -DCMAKE_BUILD_TYPE=Release ^
  -DCMAKE_CXX_FLAGS="/O2 /arch:AVX2" ..
```

## 静态链接库

如果想要独立的可执行文件，使用静态链接：

编辑 `CMakeLists.txt`：

```cmake
# 使用静态链接
set(CMAKE_CXX_FLAGS_RELEASE "/MT")
set(CMAKE_CXX_FLAGS_DEBUG "/MTd")
```

## 生成可执行文件

编译完成后：

1. 可执行文件位置：`build/bin/Release/ValorantESP.exe`
2. 确保 OpenCV DLL 在同一目录或系统 PATH 中
3. 可以使用 `cpack` 打包分发

```bash
# 生成安装包
cpack -C Release
```

## 疑难排解

### 验证编译环境

```bash
# 检查 CMake 版本
cmake --version

# 检查 Visual Studio 版本
msbuild /version

# 检查 OpenCV 安装
echo %OPENCV_DIR%
```

### 生成详细编译日志

```bash
cmake --build . --config Release --verbose
```

### 清理编译文件

```bash
# 删除编译目录
rmdir /s /q build

# 重新创建
mkdir build
cd build
cmake ..
```

## 下一步

- 修改代码进行功能扩展
- 调整敌人检测参数
- 添加更多 Overlay 功能
- 见 README.md 中的配置调整部分
