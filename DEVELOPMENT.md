# Telegram Desktop by LBJ - 开发文档

## 项目简介

本项目是基于 Telegram Desktop 官方客户端的修改版本，旨在添加新功能并优化用户体验。

## 编译过程详解

### 1. 编译环境准备

- **开发环境**：Visual Studio 2022 with 10.0.22000.0 SDK
- **工作目录**：以D:\TBuild为例（以下称为BuildPath）
- **子目录准备**：
  - BuildPath\ThirdParty：第三方库
  - BuildPath\Libraries：编译所需库

### 2. 所需软件

- **Python 3.10**：需添加到PATH
- **Git**：用于克隆代码

### 3. 获取API凭证

编译前需要获取Telegram API的`api_id`和`api_hash`

### 4. 源代码准备

```bash
# 在BuildPath目录执行
git clone --recursive https://github.com/telegramdesktop/tdesktop.git
tdesktop\Telegram\build\prepare\win.bat
```

### 5. 项目配置与构建

```bash
# 进入Telegram目录
cd BuildPath\tdesktop\Telegram

# 配置项目
configure.bat -D TDESKTOP_API_ID=YOUR_API_ID -D TDESKTOP_API_HASH=YOUR_API_HASH

# 打开生成的解决方案
# BuildPath\tdesktop\out\Telegram.sln

# 选择Telegram项目，构建Debug或Release版本
# 编译结果位于 BuildPath\tdesktop\out\Debug 或 Release
```

## 核心文件与目录结构

### 1. 主要脚本文件

- **win.bat**：调用prepare.py准备构建环境
- **configure.bat**：调用configure.py配置项目
- **build.bat**：自动化构建项目

### 2. CMake文件功能

- **根目录CMakeLists.txt**：定义项目基本信息与构建选项
- **Telegram/CMakeLists.txt**：添加子模块、设置源文件和资源、链接依赖库
- **cmake/target_*.cmake**：提供链接库、设置编译选项等辅助函数
- **cmake/generate_*.cmake**：生成资源和处理平台特定构建需求

### 3. 编译调用关系

1. `win.bat` → `prepare.py`：准备环境
2. `configure.bat` → `configure.py` → `run_cmake.py`：配置项目生成构建文件
3. CMake构建系统处理所有CMakeLists.txt文件生成VS解决方案
4. Visual Studio编译所有文件生成最终的Telegram.exe

## 添加新功能指南

### 1. 添加新的命名空间

假设我们要添加一个名为`MyFeature`的新命名空间：

1. **创建目录和文件结构**：
   ```
   Telegram\SourceFiles\my_feature\
     ├── my_feature.cpp
     ├── my_feature.h
     └── 其他相关文件...
   ```

2. **修改CMakeLists.txt**：
   在`Telegram/CMakeLists.txt`文件中的`nice_target_sources`部分添加新文件：
   ```cmake
   nice_target_sources(Telegram ${src_loc}
   PRIVATE
       ${style_files}
       
       # 其他现有文件...
       
       # 添加新命名空间的文件
       my_feature/my_feature.cpp
       my_feature/my_feature.h
       # 其他新增文件...
   )
   ```

3. **添加依赖项**（如需）：
   ```cmake
   target_link_libraries(Telegram
   PRIVATE
       # 现有依赖项...
       
       # 如果需要，添加新的依赖库
       desktop-app::your_new_dependency
   )
   ```

4. **创建独立模块**（可选）：
   如果功能较大，可创建独立库模块：
   - 在`Telegram`目录下创建`lib_my_feature`文件夹
   - 添加`lib_my_feature/CMakeLists.txt`文件
   - 在主`Telegram/CMakeLists.txt`添加：`add_subdirectory(lib_my_feature)`

### 2. 添加新的图标资源

要添加新的图标资源，需要：

1. **准备图标文件**：
   - 将图标文件（如PNG、SVG格式）放入`Telegram/Resources`目录的适当子文件夹中
   - 建议根据用途放入相应目录：
     - `Telegram/Resources/icons`：一般图标
     - `Telegram/Resources/art`：艺术资源

2. **更新QRC资源文件**：
   - 编辑`Telegram/Resources/telegram.qrc`文件，添加新图标路径：
   ```xml
   <qresource prefix="/gui">
       <!-- 现有图标... -->
       <file>icons/my_feature/my_icon.png</file>
   </qresource>
   ```

3. **对于主题相关图标**：
   - 如果图标需要支持多主题，需要同时添加到不同主题的资源文件：
     - `Telegram/Resources/icons/settings/themes/day.svg`
     - `Telegram/Resources/icons/settings/themes/night.svg`
   - 并更新样式表文件：
     - 编辑`ui/td_colors.palette`等颜色配置文件

4. **使用自定义图标**：
   在代码中，通过`st::`命名空间或直接使用Qt资源路径访问：
   ```cpp
   // 使用Qt资源路径
   QPixmap pixmap(":/gui/icons/my_feature/my_icon.png");
   
   // 或添加到样式文件后通过样式对象访问
   auto &iconRef = st::myFeatureIcon;
   ```

5. **注册样式对象**（需要样式支持时）：
   - 在`ui/style/style_*`相关文件中添加图标定义
   - 重新生成style_*.cpp文件：
     ```bash
     cd BuildPath\tdesktop\Telegram
     configure.bat -D TDESKTOP_API_ID=YOUR_API_ID -D TDESKTOP_API_HASH=YOUR_API_HASH
     ```

### 3. 重新编译项目

完成上述修改后，需要：

1. **重新配置项目**：
   ```bash
   cd BuildPath\tdesktop\Telegram
   configure.bat -D TDESKTOP_API_ID=YOUR_API_ID -D TDESKTOP_API_HASH=YOUR_API_HASH
   ```

2. **编译项目**：
   - 方式1：使用Visual Studio打开`BuildPath\tdesktop\out\Telegram.sln`并生成
   - 方式2：命令行编译：
     ```bash
     cd BuildPath\tdesktop\out
     msbuild Telegram.sln /p:Configuration=Debug
     # 或
     msbuild Telegram.sln /p:Configuration=Release
     ```

### 4. 开发注意事项

1. **代码风格**：
   - 遵循项目现有代码风格和命名规范
   - 使用`auto`关键字定义变量类型（项目规范）

2. **项目库使用**：
   - RPL库：项目使用`rpl::`命名空间下的响应式编程库
   - 示例：
     ```cpp
     auto subscription = rpl::single(123) | rpl::start_with_next([](int value) {
         // 处理逻辑
     }, lifetime);
     ```

3. **文档更新**：
   - 修改`CHANGELOG.md`添加新功能说明
   - 更新`DEVELOPMENT.md`补充开发文档
   - 在`TODO.md`中标记完成的功能

4. **预编译头**：
   - 新文件通常需要包含预编译头：
     ```cpp
     #include "stdafx.h"
     #include "my_feature/my_feature.h"
     ```

