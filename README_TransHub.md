# TransHub 功能实现指南

本文档用于指导开发人员实现 TransHub 功能，包括界面设计、语言文件管理和功能开发等方面。

## 文档概述

TransHub 功能开发涉及以下几个文件：

1. **UI.md** - 详细的界面设计文档，描述了四个主要功能模块的界面元素和交互要求
2. **transhub_language_example.strings** - 英文语言文件示例，需添加到 `lang.strings`
3. **transhub_language_example_zh.strings** - 中文语言文件示例，需添加到 `out/Release/Resources/lang_zh-hans.strings`
4. **images/** - 存放界面设计图片的目录

## 实现步骤

### 1. 前期准备

- 熟悉 Telegram Desktop 的代码结构和开发惯例
- 理解 `rpl` 响应式编程库的使用方法
- 掌握 Qt 和 Telegram UI 组件的基本用法

### 2. 目录结构创建

在 `Telegram/SourceFiles/` 目录下创建 `transhub` 文件夹，并按照以下结构组织代码：

```
transhub/
├── transhub_forward.cpp/h    // 转发功能
├── transhub_download.cpp/h   // 下载功能
├── transhub_upload.cpp/h     // 上传功能
├── transhub_monitor.cpp/h    // 监听功能
├── transhub_common.cpp/h     // 公共组件
└── transhub_window.cpp/h     // 主窗口管理
```

### 3. 语言文件添加

将 `transhub_language_example.strings` 中的文本添加到 `Telegram/Resources/langs/lang.strings` 文件中，同时将 `transhub_language_example_zh.strings` 中的翻译添加到 `out/Release/Resources/lang_zh-hans.strings` 文件中。

### 4. 窗口类型选择

- TransHub 窗口应该使用 Telegram 中的 Layer 类型，而非简单对话框
- 参考以下类型选择：
  1. **首选方案**：使用 `Ui::LayerWidget` 作为基类，类似于 `info/info_layer_widget.h` 实现
  2. **备选方案**：使用 `Ui::SectionWidget` 作为基类，类似于 `settings/settings_common.h` 实现
- 实现 `TransHub::Window` 类：

  ```cpp
  // transhub/transhub_window.h
  class Window : public Ui::LayerWidget {
  public:
    Window(QWidget* parent, not_null<Window::SessionController*> controller);

    // 必要的覆盖方法...
  private:
    const not_null<Window::SessionController*> _controller;
    // 其他成员...
  };
  ```

- 这种窗口类型可以提供更大的界面空间，适合复杂的多标签页界面

### 5. 功能模块开发顺序

1. 先实现基础框架 (`transhub_window.cpp/h` 和 `transhub_common.cpp/h`)
2. 按照优先级顺序实现各功能模块：
   - 转发功能
   - 下载功能
   - 上传功能
   - 监听功能
3. **实现顺序备注**：
   - 各功能模块内的规则显示区域内容暂时留空
   - 先实现框架、标签页切换和基本控件
   - 规则显示区域内容等"规则"按钮的点击界面实现后再实现
   - 保持界面结构一致，但内容可以在稍后阶段填充

### 6. 界面实现注意事项

- 使用 `object_ptr` 管理 UI 对象
- 使用响应式设计处理窗口大小变化
- 所有文本使用 `tr::lng_*` 方式引用，避免硬编码
- 遵循 Telegram 的风格和设计模式
- 使用 `rpl::producer` 连接信号和数据流
- 处理好窗口关闭和资源释放的逻辑

### 7. 替换现有临时对话框

- 目前侧边栏中的 TransHub 按钮实现在 `window/window_filters_menu.cpp` 文件中
- 该按钮创建为特殊的文件夹按钮，使用固定 ID `-2` 和 `Ui::FilterIcon::TransHub` 图标
- 替换方法：
  1. 保持 `window/window_filters_menu.cpp` 中的按钮不变
  2. 修改点击回调，调用新的 TransHub 窗口代码而非 `ShowTransHubBox`
  3. 具体代码如下：
     ```cpp
     _transhub->setClickedCallback([=] {
       if (_reordering) {
         return;
       }
       // Boxes::ShowTransHubBox(_session); // 旧代码
       _session->showTransHub(); // 新代码，需在 SessionController 中实现
     });
     ```
  4. 在 `window/window_session_controller.h` 中声明 `showTransHub()` 方法：
     ```cpp
     // window/window_session_controller.h
     class SessionController : public ... {
     public:
       // 其他现有方法...
       void showTransHub();
     };
     ```
  5. 在 `window/window_session_controller.cpp` 中实现此方法：
     ```cpp
     // window/window_session_controller.cpp
     void SessionController::showTransHub() {
       const auto layerWidget = std::make_shared<TransHub::Window>(
         nullptr, // parent 将由 showLayer 设置
         this
       );
       showLayer(layerWidget, LayerOption::KeepOther);
     }
     ```

### 8. 修改 CMakeLists.txt

在 `Telegram/CMakeLists.txt` 文件中添加新的源文件：

### 9. 保留侧边栏入口点

- TransHub 的入口点应继续保留在侧边栏，与当前实现位置相同
- 不需要在`window/main_window.cpp`中添加新入口点
- 只需修改现有的侧边栏入口点的行为：
  1. 保留`window/window_filters_menu.cpp`中的按钮创建代码不变
  2. 只修改点击回调函数，使其打开新的 TransHub 窗口而非临时对话框
  3. 确保图标、位置等保持一致，保证用户体验的延续性
- 新窗口应在`SessionController`中实现，替代原有的临时对话框

### 10. 测试和调试

- 确保每个功能模块单独编译通过
- 测试不同窗口大小下的界面表现
- 测试中英文环境下的文本显示
- 测试所有交互流程，包括：
  1. 按钮点击响应
  2. 标签页切换
  3. 规则编辑保存
  4. 任务执行与取消
  5. 状态显示和更新

### 11.注意所有代码注释均使用英文

## 参考资源

- `Telegram/SourceFiles/boxes/` - 对话框实现示例
- `Telegram/SourceFiles/info/` - 复杂 UI 组件示例（特别参考 `info_layer_widget.h/.cpp`）
- `Telegram/SourceFiles/settings/` - 标签页切换示例
- `UI.md` - 详细的界面设计文档
- `window/window_session_controller.*` - 了解如何正确集成窗口

## 提交规范

实现新功能后，请更新以下文件：

1. 更新 `TODO.md`，标记已完成的功能
2. 更新 `CHANGELOG.md`，记录新添加的功能
3. 必要时更新 `DEVELOPMENT.md`，添加开发注意事项
