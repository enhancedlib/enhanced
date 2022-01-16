# Enhanced
A Powerful C/C++ Development Framework

This product is licensed under [Enhanced License](licenses/COPYING).

Repository:
- [Github](http://github.com/LiuBaihao-Hello/Enhanced)

## ⚠ Warning: Not Production Ready!
This project is still in the early stage, many features are immature or unimplemented.

Do not use in production environment, otherwise the consequences!

## 1.Introducing
This software is a library for the C/C++ language.
It contains many useful modules with a powerful variety of classes and functions (methods)

Including but not limited to:
- 1. Basic data types (e.g. String, Integer)
- 2. More powerful exception handling (including C language support)
- 3. Containers (collection, set, map, etc.)
- 4. Template (generic) classes and functions (C++ only)
- 5. Cross-platform underlying apis

## 2.Install/Uninstall
* There is no installer yet, you can download the source code, build the project yourself.

## 3.How to Use this Software?

### Supported Environment

* These are supported environments using this library, not build environments.

The installer and uninstaller will be provided in the future.

Compiler:
- [Microsoft Visual C++](https://visualstudio.microsoft.com/vs/features/cplusplus/)
- [GNU C/C++ Compiler](http://gcc.gnu.org/)
- [Clang](https://clang.llvm.org/)

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

### Required environment:
- C Standard: C99
- C++ Standard: C++11
- Build System: CMake

### Recommended environment:
- C Standard: C99
- C++ Standard: C++11
- Build System: CMake

## 5.Purpose

I hope to use this library to make the C/C++ language software development more convenient and efficient.

## 6.Technology

### About Generics (Templates) in This Project
A class whose class name is followed by a zero (hereinafter referred to as "the implementation class")
is usually a generic implementation class of a template class.

They separate the implementation of the template class
from the template by type erasure (pseudo-generic).

You should not extend (inherit) the implementation class from another class.
And you should not instantiate the implementation class directly.
The correct approach is to instantiate the template class.
Because the implementation class has no public methods.

Also, you shouldn't instantiate a template class with the implementation class as type,
because the template class usually privately extends (inherits) the implementation class.
