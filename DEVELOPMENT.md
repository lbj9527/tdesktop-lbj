# Telegram Desktop by LBJ - 开发文档

## 项目简介

本项目是基于 Telegram Desktop 官方客户端的修改版本，旨在添加新功能并优化用户体验。

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

3. **添加中文语言包支持**：

   - 在`out/Release/Resources/lang_zh-hans.strings`文件中添加相应的中文翻译
   - 格式：`"lng_key_name" = "中文翻译内容";`
   - 确保添加在对应的英文条目相同位置，保持文件结构一致
   - 如果遇到硬编码的字符串（如`u"TransHub"_q`），可在语言包中直接添加对应的翻译项：`"TransHub" = "传输中心";`

4. **加载自定义语言包**：

   - 在设置界面，按住 Shift+Alt 点击"语言"按钮可打开自定义语言包加载对话框
   - 也可在任意聊天中输入`loadlang`作为特殊代码触发加载
   - 选择语言包文件后，应用会加载并应用所有翻译内容

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

## 新功能开发指南

### 1. 添加新的功能文件

1. **添加新的命名空间**：

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
