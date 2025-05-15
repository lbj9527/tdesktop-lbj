# Telegram Desktop by LBJ - 开发文档

## 项目简介

本项目是基于 Telegram Desktop 官方客户端的修改版本，旨在添加新功能并优化用户体验。

## 开发环境设置

### 所需工具

- **CMake** (版本 3.25 - 3.31)
- **Visual Studio 2022** (Windows 开发)
- **Git** (版本控制)
- **Python** (用于构建脚本)

### 克隆仓库

```bash
git clone <repository-url>
cd tdesktop-lbj
git submodule update --init --recursive
```

### 构建项目

#### Windows (Visual Studio 2022)

1. 创建构建目录：

```bash
mkdir build
cd build
```

2. 生成 VS 解决方案：

```bash
cmake .. -G "Visual Studio 17 2022" -A x64
```

3. 在 Visual Studio 中打开解决方案：
   - 打开 `Telegram.sln`
   - 将配置设置为 "Release" 或 "Debug"
   - 将 Telegram 项目设为启动项目
   - 构建解决方案

#### Debug 版本构建

```bash
cmake --build . --config Debug
```

#### Release 版本构建

```bash
cmake --build . --config Release
```

## 项目结构

- `Telegram/` - 主要源代码目录
  - `SourceFiles/` - C++源代码
  - `Resources/` - 资源文件
  - `ThirdParty/` - 第三方库
- `cmake/` - CMake 配置文件
- `CHANGELOG.md` - 版本变更记录

## 开发指南

### 代码风格

- 使用 4 空格缩进
- 使用驼峰命名法
- 类名以大写字母开头
- 变量和函数名以小写字母开头

### 提交流程

1. 创建新分支进行开发：

```bash
git checkout -b feature/your-feature-name
```

2. 进行代码修改

3. 提交代码：

```bash
git add .
git commit -m "描述你的修改"
```

4. 推送到仓库：

```bash
git push origin feature/your-feature-name
```

### 版本发布流程

1. 更新版本号
2. 更新 CHANGELOG.md
3. 创建新的标签
4. 构建 Release 版本
5. 发布

## 常见问题

### 编译中断或停滞

- 检查系统资源使用情况
- 尝试减少并行构建数量
- 确保有足够的磁盘空间

### 依赖问题

- 确保所有子模块已正确初始化
- 检查 CMake 版本是否兼容

## 联系方式

如有问题或建议，请联系项目维护者。

---

_最后更新: 2023-11-18_
