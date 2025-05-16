# Telegram Desktop by LBJ - 版本变更记录

本文档记录了 Telegram Desktop 客户端的修改历史，包括功能添加、Bug 修复和其他变更。

## [未发布]

### 添加

- 添加了 TransHub 功能入口，在侧边栏提供一个新按钮，用于访问历史消息下载、本地文件上传和消息转发管理功能
  - 采用标准 Telegram 对话框实现，与系统风格一致
  - 将功能文本字符串添加到语言文件中，支持多语言
  - 修复了与`object_ptr`和类继承相关的编译问题

### 修复

- 暂无修复

### 变更

- 暂无变更

## 开发最佳实践

为了保证定制开发能更快完成并与原版保持兼容，开发中应遵循以下原则：

1. **遵循原有代码结构**：尽量理解并复用 Telegram 源码的设计模式和架构

   - 使用正确的类继承关系（如继承`BoxContent`而非`GenericBox`）
   - 使用`object_ptr`处理 Qt 对象所有权，注意所有权传递的正确方式
   - 参考类似功能的实现（如其他对话框的代码组织方式）

2. **使用语言系统**：

   - 所有用户可见的文本都应在`lang.strings`中定义
   - 使用`tr::lng_*`函数引用而非硬编码文本
   - 这样可以方便后续添加多语言支持

3. **UI 开发规范**：

   - 使用 Telegram 预定义的样式变量（如`st::boxWidth`, `st::boxPadding`）
   - 采用响应式布局，通过`widthValue() | rpl::start_with_next`等方式处理尺寸变化
   - 复用现有 UI 组件实现一致的视觉风格

4. **响应式编程**：

   - 熟悉并使用`rpl`库提供的响应式编程工具
   - 合理管理对象生命周期和信号连接

5. **增量开发**：
   - 先搭建基础框架确保编译通过
   - 逐步扩展功能，每次添加功能后确保可以正常编译和运行
   - 将大型功能分解为小模块单独实现

遵循这些最佳实践可以显著减少开发中的问题，更好地与原有代码集成，并提高开发效率。

## [0.1.0] - 2023-11-18

### 变更

- 将应用程序名称由"Telegram Desktop"更改为"Telegram Desktop by LBJ"
- 可能修改的文件包括：
  - `Telegram/Resources/winrc/Telegram.rc` - Windows 资源文件中的应用名称
  - `Telegram/Resources/mac/Info.plist` - macOS 应用信息
  - `Telegram/build/version` - 版本信息
  - `Telegram/SourceFiles/core/version.h` - 版本常量定义
  - `Telegram/SourceFiles/intro/intro_widget.cpp` - 介绍页面
  - `Telegram/SourceFiles/window/window_title.cpp` - 窗口标题
  - `Telegram/SourceFiles/main/main_window.cpp` - 主窗口设置
  - `Telegram/Resources/langs/lang.strings` - 语言文件
  - `CMakeLists.txt` - 项目配置
  - `Telegram/cmake/telegram_options.cmake` - 应用选项
  - `Telegram/SourceFiles/boxes/about_box.cpp` - 关于对话框

## 开发计划

未来计划添加的功能和改进：

1. [待定] - 功能 1
2. [待定] - 功能 2
3. [待定] - 功能 3

## 版本规则说明

版本号格式：主版本号.次版本号.修订号

- 主版本号：重大功能变更，可能不兼容旧版本
- 次版本号：新功能添加，但保持向后兼容
- 修订号：Bug 修复和小改进

## 贡献指南

如果你想为项目做出贡献，请遵循以下步骤：

1. Fork 仓库
2. 创建功能分支
3. 提交更改
4. 推送到分支
5. 创建 Pull Request
