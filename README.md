# Enhanced

A Powerful C/C++ Development Framework

This software is licensed under [Enhanced License](LICENSE).

Repositories:
- [GitHub](http://github.com/any-possible/Enhanced)

[Other Languages](docs/README.Languages.md) | [Website](http://any-possible.github.io/enhanced-website) | [Read Me](README.md) | [Help & Support](docs/en-US/Help-Support.md) | [About](docs/en-US/About.md)

---

## ⚠ Warning: Not Production Ready!
This project is still in the early stage, many features are immature or unimplemented.

Do not use in production environment. Otherwise, do so at your own risk!

---

## 1.Introducing
This software is a library for the C/C++ language.
It contains many useful modules with a powerful variety of classes and functions (methods):

Note: many functions have not been developed yet, and will be gradually added in the future.

- 1. Basic data types (e.g. String, Integer)
- 2. More powerful exception handling (including C language support)
- 3. Containers (collection, set, map, etc.)
- 4. Template (generic) classes and functions (C++ only)
- 5. Threading.
- 6. Cross-platform underlying APIs
- 7. Data processing.
- 8. ...

## 2.Install/Uninstall
There is no installer yet, you can download the source code, build the project yourself.
* The installer and uninstaller will be provided in the future.

## 3.How to Use this Software?

### Supported Environment

* These are supported environments using this library, not build environments.

Compiler:
- [Microsoft Visual C++](http://visualstudio.microsoft.com/vs/features/cplusplus/)
- [GNU C/C++ Compiler](http://gcc.gnu.org/)
- [Clang](http://clang.llvm.org/)

Operating system:
- Microsoft Windows Operating System
- Linux

Processor architecture:
- amd64 (x86_64)
- x86

Supported C Standard:
- C89, C99, C11

Supported C++ Standard:
- C++98, C++11, C++14, C++17, C++20

## 4.Build

### Required environments:
- C Standard: C99
- C++ Standard: C++11
- Build System: CMake

### Recommended environments:
- C Standard: C11
- C++ Standard: C++20
- Build System: CMake with Ninja

## 5.Purpose

I hope to use this library to make the C/C++ language software development more convenient and efficient.

## 6.Technology

### About Generics (Templates) in This Project
A class whose class name is followed by a zero (hereinafter referred to as "the implementation class") is usually a generic implementation class of a template class.

They separate the implementation of the template class from the template by type erasure (pseudo-generic).

You should not extend (inherit) the implementation class from another class, and you should not instantiate the implementation class directly.
The correct approach is to instantiate the template class, because the implementation class has no public methods.

Also, you shouldn't instantiate a template class with the implementation class as type, because the template class usually privately extends (inherits) the implementation class.
