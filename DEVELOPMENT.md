# Telegram Desktop by LBJ - 开发文档

## 项目简介

本项目是基于 Telegram Desktop 官方客户端的修改版本，旨在添加新功能并优化用户体验。

## 编译过程详解

### 1. 编译环境准备

- **开发环境**：Visual Studio 2022 with 10.0.22000.0 SDK

- # **工作目录**：以 D:\TBuild 为例（以下称为 BuildPath）

- **子目录准备**：
  - BuildPath\ThirdParty：第三方库
  - BuildPath\Libraries：编译所需库

### 2. 所需软件

- **Python 3.10**：需添加到 PATH
- **Git**：用于克隆代码

### 3. 获取 API 凭证

# 编译前需要获取 Telegram API 的`api_id`和`api_hash`

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

<<<<<<< HEAD

- **win.bat**：调用 prepare.py 准备构建环境
- **configure.bat**：调用 configure.py 配置项目
- **build.bat**：自动化构建项目

### 2. CMake 文件功能

- **根目录 CMakeLists.txt**：定义项目基本信息与构建选项
- **Telegram/CMakeLists.txt**：添加子模块、设置源文件和资源、链接依赖库
- **cmake/target\_\*.cmake**：提供链接库、设置编译选项等辅助函数
- # **cmake/generate\_\*.cmake**：生成资源和处理平台特定构建需求
- **win.bat**：调用 prepare.py 准备构建环境
- **configure.bat**：调用 configure.py 配置项目
- **build.bat**：自动化构建项目

### 2. CMake 文件功能

- **根目录 CMakeLists.txt**：定义项目基本信息与构建选项
- **Telegram/CMakeLists.txt**：添加子模块、设置源文件和资源、链接依赖库
- **cmake/target\_\*.cmake**：提供链接库、设置编译选项等辅助函数
- **cmake/generate\_\*.cmake**：生成资源和处理平台特定构建需求
  > > > > > > > cb957b7ed9c8db2255cb8672206ad4f55590d3b0

### 3. 编译调用关系

1. `win.bat` → `prepare.py`：准备环境
2. `configure.bat` → `configure.py` → `run_cmake.py`：配置项目生成构建文件
   <<<<<<< HEAD
3. CMake 构建系统处理所有 CMakeLists.txt 文件生成 VS 解决方案
4. # Visual Studio 编译所有文件生成最终的 Telegram.exe
5. CMake 构建系统处理所有 CMakeLists.txt 文件生成 VS 解决方案
6. Visual Studio 编译所有文件生成最终的 Telegram.exe
   > > > > > > > cb957b7ed9c8db2255cb8672206ad4f55590d3b0

## 添加新功能指南

### 1. 添加新的命名空间

假设我们要添加一个名为`MyFeature`的新命名空间：

1. **创建目录和文件结构**：
   <<<<<<< HEAD

   ```
   Telegram\SourceFiles\my_feature\
     ├── my_feature.cpp
     ├── my_feature.h
     └── 其他相关文件...
   ```

2. **修改 CMakeLists.txt**：
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

   - 将图标文件（如 PNG、SVG 格式）放入`Telegram/Resources`目录的适当子文件夹中
   - 建议根据用途放入相应目录：
     - `Telegram/Resources/icons`：一般图标
     - `Telegram/Resources/art`：艺术资源

2. **更新 QRC 资源文件**：

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
   在代码中，通过`st::`命名空间或直接使用 Qt 资源路径访问：

   ```cpp
   // 使用Qt资源路径
   QPixmap pixmap(":/gui/icons/my_feature/my_icon.png");

   // 或添加到样式文件后通过样式对象访问
   auto &iconRef = st::myFeatureIcon;
   ```

5. **注册样式对象**（需要样式支持时）：
   - 在`ui/style/style_*`相关文件中添加图标定义
   - 重新生成 style\_\*.cpp 文件：
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
   - 方式 1：使用 Visual Studio 打开`BuildPath\tdesktop\out\Telegram.sln`并生成
   - 方式 2：命令行编译：
     ```bash
     cd BuildPath\tdesktop\out
     msbuild Telegram.sln /p:Configuration=Debug
     # 或
     msbuild Telegram.sln /p:Configuration=Release
     ```

### 4. 重新编译项目

使用 Visual Studio 编译 TransHub 功能的详细操作步骤
假设你已经实现了 TransHub 功能的所有代码，但还未修改任何编译文件，并且已经用 Visual Studio 打开了 telegram.sln，以下是详细的操作步骤：

1. **将新文件添加到项目中**：
   在 Visual Studio 的解决方案资源管理器中，找到 Telegram 项目
   展开项目树，找到现有的源文件和头文件组织结构
   添加头文件：
   找到 boxes 文件夹（如果存在的话，否则找到存放其他对话框头文件的文件夹）
   右键点击该文件夹，选择"添加" > "现有项..."
   浏览到你创建的 transhub_box.h 文件路径，选择并点击"添加"
   添加源文件：
   同样，找到相应的源文件目录或 boxes 文件夹
   右键点击该文件夹，选择"添加" > "现有项..."
   浏览到你创建的 transhub_box.cpp 文件路径，选择并点击"添加"

2. **确保资源文件被正确包含**：
   找到项目中的资源文件部分（通常有 Resources 或类似名称的过滤器/文件夹）
   确认 TransHub 图标文件已经被添加到项目中：
   如果没有，右键点击相应的资源文件夹，选择"添加" > "现有项..."
   浏览到 folders_transhub.png 及其@2x、@3x 版本的位置
   选择这些文件并点击"添加"

3. **确保项目知道这些文件的存在**：
   在 Visual Studio 中，点击"项目" > "显示所有文件"
   这会显示物理存在但未包含在项目中的文件（显示为灰色图标）
   如果看到你的 TransHub 相关文件是灰色的，说明它们还未包含在项目中
   右键点击每个灰色的 TransHub 相关文件，选择"包含在项目中"
   这会将文件正式添加到项目的编译列表中

4. **编译项目**：
   确认编译配置：
   在工具栏上选择适当的配置（Debug 或 Release）
   确保选择了正确的平台（通常是 x64）
   开始编译：
   点击"生成" > "生成解决方案"（或按 F7）
   或者右键点击 Telegram 项目，选择"生成"进行增量编译
   观察输出窗口中的编译过程：
   确认 transhub_box.cpp 和其他修改过的文件正在被编译
   检查是否有编译错误

5. **处理可能出现的编译错误**：
   如果出现编译错误，按照以下步骤解决：
   包含文件错误：
   确保头文件中的包含路径正确
   可能需要添加#include "boxes/transhub_box.h"到依赖该头文件的其他源文件中
   未定义引用错误：
   检查函数声明和定义是否匹配
   确保所有函数都有正确的访问限定符（public/private）
   资源文件错误：
   确保资源文件路径正确，并且已正确包含在项目中

6. **运行和测试**：
   编译成功后，点击"调试" > "开始调试"（或按 F5）启动应用程序
   测试 TransHub 功能：
   登录 Telegram 账户后，查看侧边栏中是否有 TransHub 按钮
   点击 TransHub 按钮，确认对话框能正确显示
   确认所有功能按预期工作

7. **额外提示**：
   项目设置查看：
   如果你想确认文件确实被包含在编译中，可以右键点击项目，选择"属性"
   在属性页中，选择"配置属性" > "C/C++" > "常规"，查看"附加包含目录"
   确保包含了你的文件所在目录
   使用增量编译加速开发：
   修改代码后，可以只编译修改的文件：右键点击该文件，选择"编译"
   然后右键点击 Telegram 项目，选择"生成"，这样只会重新链接而不是重新编译所有文件
   查看编译器输出获取详细信息：
   在"输出"窗口中选择"生成"输出
   这里会显示哪些文件被编译以及是否有警告/错误
   按照以上步骤，你应该能够成功地将 TransHub 功能添加到项目中并进行编译，而无需修改任何编译配置文件。Visual Studio 会根据你添加的文件自动处理依赖关系和编译过程。

### 5. 开发注意事项

1. **代码风格**：

   - 遵循项目现有代码风格和命名规范
   - 使用`auto`关键字定义变量类型（项目规范）

2. **项目库使用**：

   - RPL 库：项目使用`rpl::`命名空间下的响应式编程库
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

## Telegram 代码库最佳实践

为加快开发效率并确保代码兼容性，请遵循以下 Telegram 特有的开发实践：

### 1. 类继承及对象生命周期

1. **正确理解类继承层次**：

   - `Ui::BoxContent`是对话框基类，而不是`Ui::GenericBox`（后者是 final 类）
   - 使用适当的基类构造器初始化：`Widget(QWidget*)`、`BoxContent(QWidget*)`等

2. **对象指针管理**：

   - 优先使用`object_ptr<T>`而非原始指针（除接口参数外）
   - 转换原始指针到`object_ptr`：`object_ptr<T>::fromRaw(ptr)`
   - 从容器获取添加的部件：`auto raw = container->add(...); auto widget = object_ptr<T>::fromRaw(raw);`

3. **事件和信号处理**：
   - 使用 RPL 库连接事件，而非 Qt 信号槽（除非必须）
   - 使用`lifetime`管理对象生命周期和连接

### 2. UI 组件和布局规范

1. **组件层次**：

   - 主窗口 → 会话控制器 → 会话视图
   - 对话框 → 垂直布局 → UI 元素

2. **创建 UI 组件标准模式**：

   ```cpp
   // 创建布局容器
   const auto content = Ui::CreateChild<Ui::VerticalLayout>(this);

   // 添加标签
   const auto label = content->add(
       object_ptr<Ui::FlatLabel>(
           content,
           tr::lng_some_text(),
           st::someStyle),
       st::somePadding);

   // 添加按钮
   const auto button = content->add(
       object_ptr<Ui::RoundButton>(
           content,
           tr::lng_button_text(),
           st::someButtonStyle),
       st::somePadding);
   ```

3. **响应式布局**：
   ```cpp
   // 监听宽度变化
   widthValue() | rpl::start_with_next([=](int width) {
       // 根据宽度调整UI
       updateGeometry(width);
   }, lifetime());
   ```

### 3. 语言和本地化

1. **字符串定义方式**：

   - 在`lang.strings`中定义：`"lng_key_name" = "String value";`
   - 在`lang_keys.h`声明：`inline constexpr auto lng_key_name = "key_name";`

2. **使用本地化字符串**：

   ```cpp
   // 直接使用
   setTitle(tr::lng_some_title());

   // 带参数
   setText(tr::lng_some_text(tr::now, lt_count, count));

   // 响应式使用
   label->setText(tr::lng_some_text());
   ```

### 4. 样式和主题

1. **样式定义**：

   - 在`.style`文件中定义样式变量
   - 在代码中通过`st::`命名空间访问

2. **样式继承和变量**：

   ```cpp
   // 样式文件(.style)
   myFancyButton: RoundButton(defaultActiveButton) {
     width: 200px;
     height: 40px;
     textFg: windowFg;
   }

   // 代码中使用
   auto button = object_ptr<Ui::RoundButton>(this, tr::lng_button(), st::myFancyButton);
   ```

### 5. APIs 和会话管理

1. **会话及控制器访问**：

   ```cpp
   // 通过控制器访问会话
   not_null<Main::Session*> session = _controller->session();

   // 通过会话访问API
   auto &api = session->api();
   ```

2. **数据模型和存储**：

   ```cpp
   // 访问数据
   auto &data = session->data();

   // 获取特定实体
   auto user = data.user(userId);
   auto chat = data.chat(chatId);
   ```

3. **事件订阅**：
   ```cpp
   // 监听全局更新
   session->changes().messageUpdates(
   ) | rpl::start_with_next([=](const Data::MessageUpdate &update) {
       // 处理消息更新
   }, lifetime());
   ```

### 6. 调试和测试

1. **日志和断言**：

   ```cpp
   // 日志信息
   LOG(("Some debug info: %1").arg(value));

   // 断言
   Expects(condition);
   ```

2. **安全检查**：
   - 使用`not_null<T*>`标记不应为 null 的指针参数
   - 使用`std::optional<T>`标记可能不存在的值

# 遵循以上实践可以显著减少开发中的问题，提高代码质量和开发效率。

```
Telegram\SourceFiles\my_feature\
  ├── my_feature.cpp
  ├── my_feature.h
  └── 其他相关文件...
```

2. **修改 CMakeLists.txt**：
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

   - 将图标文件（如 PNG、SVG 格式）放入`Telegram/Resources`目录的适当子文件夹中
   - 建议根据用途放入相应目录：
     - `Telegram/Resources/icons`：一般图标
     - `Telegram/Resources/art`：艺术资源

2. **更新 QRC 资源文件**：

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
   在代码中，通过`st::`命名空间或直接使用 Qt 资源路径访问：

   ```cpp
   // 使用Qt资源路径
   QPixmap pixmap(":/gui/icons/my_feature/my_icon.png");

   // 或添加到样式文件后通过样式对象访问
   auto &iconRef = st::myFeatureIcon;
   ```

5. **注册样式对象**（需要样式支持时）：
   - 在`ui/style/style_*`相关文件中添加图标定义
   - 重新生成 style\_\*.cpp 文件：
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
   - 方式 1：使用 Visual Studio 打开`BuildPath\tdesktop\out\Telegram.sln`并生成
   - 方式 2：命令行编译：
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

   - RPL 库：项目使用`rpl::`命名空间下的响应式编程库
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

> > > > > > > cb957b7ed9c8db2255cb8672206ad4f55590d3b0
