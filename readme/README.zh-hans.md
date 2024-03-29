# Enhanced

***一个强大的C++开发框架***

- 开发中，请在[GitHub Issues](https://github.com/enhancedlib/enhanced/issues)提交bug。

[语言](LANGUAGES.md) | [许可协议](../LICENSE) | [网站](https://enhancedlib.github.io/) | [GitHub仓库](https://github.com/enhancedlib/enhanced/)

---

## ⚠ **警告：此软件还不能投入使用！**

该项目仍处于早期阶段，许多特性尚不成熟或未实现。

请不要在生产环境中使用。***否则，请自己承担风险！***

---

## 介绍

此软件是一个C++库。
它包含了许多有用的模块，具有各种功能强大的类和函数：

- 注意：以下许多功能尚未开发，会在未来逐渐添加。

1. 实用的类和函数
2. 更强大的异常处理
3. 集合/容器（列表、组等）
4. 线程
5. 数据处理
6. 网络
7. 还有更多……

要使用此库，应至少使用C++20标准

## 构建

环境：

- 编译器：[Clang](https://clang.llvm.org/) >= 15.0.0, [Microsoft Visual C++ (MSVC)](https://visualstudio.microsoft.com/vs/features/cplusplus/) >= 17.0.0, [GNU Compiler Collection (GCC)](https://gcc.gnu.org/) >= 11.0.0 **(标明的版本为已测试，其它版本兼容性未知)**
- 操作系统：Microsoft Windows, Linux內核操作系統, Apple macOS
- 处理器：amd64 (x86_64)，x86，arm (arm32)\*，arm64 (aarch64)\* **(“\*”表示未经测试)**
- 构建系统: [CMake](https://cmake.org/) >= 3.13 (推荐使用[Ninja](https://ninja-build.org)作为下游构建系统)
- C++标准：至少为C++20

## 愿望

我希望这个库可以让使用C++语言开发软件更加方便和高效。
