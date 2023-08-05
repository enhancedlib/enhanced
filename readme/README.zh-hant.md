# Enhanced

一個強大的C++開發框架

- 開發中，請在[GitHub Issues](https://github.com/enhancedlib/enhanced/issues)提交bug。

[語言](LANGUAGES.md) | [許可協議](../LICENSE) | [網站](https://enhancedlib.github.io/) | [GitHub倉庫](https://github.com/enhancedlib/enhanced/)

---

## ⚠ **警告：此軟件還不能投入使用！**

該項目仍處於早期階段，許多特性尚不成熟或未實現。

請不要在生產環境中使用。***否則，請自己承擔風險！***

---

## 介紹

此軟件是一個C++庫。
它包含了許多有用的模塊，具有各種功能強大的類和函數：

- 註意：以下許多功能尚未開發，會在未來逐漸添加。

1. 實用的類和函數
2. 更強大的異常處理
3. 集合/容器（列表、組等）
4. 線程
5. 數據處理
6. 網絡
7. 更多……

要使用此庫，應至少使用C++20標準

## 構建

環境：

- 編譯器：[Clang](https://clang.llvm.org/) >= 15.0.0, [Microsoft Visual C++ (MSVC)](https://visualstudio.microsoft.com/vs/features/cplusplus/) >= 17.0.0, [GNU Compiler Collection (GCC)](https://gcc.gnu.org/) >= 11.0.0 **(標明的版本為已測試，其它版本兼容性未知)**
- 操作系統：Microsoft Windows, Linux內核操作系統, Apple macOS
- 處理器：amd64 (x86_64)、x86、arm (arm32)\*、arm64 (aarch64)\* **(「\*」表示未測試)**
- 構建系統: [CMake](https://cmake.org/) >= 3.13 (推薦使用[Ninja](https://ninja-build.org)作為下遊構建系統)
- C++標準：至少為C++20

## 願望

我希望這個庫可以讓使用C++語言開發軟件更加方便和高效。

## 幫助與支持

### 問：為什麽叫做「Enhanced」？

答：因為我想要這個軟件使C++開發更高效和容易。

### 問：這個軟件免費嗎？

答：是的，這個軟件免費並且開源。但使用此軟件必須遵守[許可協議](../LICENSE)，否則，你不得使用此軟件。
