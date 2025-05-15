# Telegram Desktop by LBJ - 版本变更记录

本文档记录了 Telegram Desktop 客户端的修改历史，包括功能添加、Bug 修复和其他变更。

## [未发布]

### 添加

- 暂无新功能

### 修复

- 暂无修复

### 变更

- 暂无变更

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
