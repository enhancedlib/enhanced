/*
 * Copyright (C) 2022 Liu Baihao. All rights reserved.
 * This software is licensed under Enhanced License.
 *
 * This copyright disclaimer is subject to change without notice.
 *
 * This software is a free software,
 * everyone can change, copy, publication, demonstrate, use, etc.
 *
 * If you change and publication this software,
 * must credit the original software source and author's name,
 * and include this copyright disclaimer and
 * the license of this software in your software.
 *
 * This software and documentation may provide
 * third-party content, product and other information.
 * I am not responsible for any loss or damage caused
 * by your access to or use of third-party content, products, etc.
 */

#ifndef ENHANCED_CORE_DEFINES_H
#define ENHANCED_CORE_DEFINES_H

// Detect current using which compiler to compile.
#if defined(__GNUC__) // GNU C/C++ Compiler
#define COMPILER_GCC
#elif defined(__clang__) // Clang
#define COMPILER_CLANG
#elif defined(_MSC_VER) // Microsoft Visual C++
#define COMPILER_MSVC
#else // Unknown
#define COMPILER_UNKNOWN
#endif // defined(__GNUC__)

// Detect the architecture for the current platform
#if defined(_M_IX86) || defined(__i386__) // 32-bit
#define ARCH_32_BIT
#elif defined(_M_X64) || defined(_M_AMD64) || defined(__x86_64__) // 64-bit
#define ARCH_64_BIT
#else // Unknown
#define ARCH_UNKNOWN
#endif // defined(_M_IX86) || defined(__i386__)

// Detect current operating system.
#if defined(_WIN32) || defined(_WIN64) // Microsoft Windows Operating System
#define WINDOWS_OS
#elif defined(__linux__) || defined(__linux) // Linux (GNU/Linux)
#define LINUX_OS
#else // Unknown
#define UNKNOWN_OS
#endif // defined(_WIN32)

// Detect the current language and its standard.
#ifdef __cplusplus // C++ language

#ifdef COMPILER_MSVC // Microsoft Visual C++
#define CXX_LANGUAGE _MSVC_LANG
#else // Non Microsoft Visual C++ compiler
#define CXX_LANGUAGE __cplusplus
#endif // COMPILER_MSVC

#if CXX_LANGUAGE >= 199711L // C++98 or more
#define CXX_98_OR_MORE
#if CXX_LANGUAGE >= 201103L // C++11 or more
#define CXX_11_OR_MORE
#if CXX_LANGUAGE >= 201402L // C++14 or more
#define CXX_14_OR_MORE
#if CXX_LANGUAGE >= 201703L // C++17 or more
#define CXX_17_OR_MORE
#if CXX_LANGUAGE > 201703L // C++20 or more
#define CXX_20_OR_MORE
#define CXX_20
#else // C++17
#define CXX_17
#endif // CXX_LANGUAGE >= 202004L
#else // C++14
#define CXX_14
#endif // CXX_LANGUAGE >= 201703L
#else // C++11
#define CXX_11
#endif // CXX_LANGUAGE >= 201402L
#else // C++98
#define CXX_98
#endif // CXX_LANGUAGE >= 201103L
#else // Unknown
#define CXX_STD_UNKNOWN
#endif // CXX_LANGUAGE >= 199711L

#else // C language

#define C_LANGUAGE __STDC_VERSION__

#if C_LANGUAGE >= 199409L // C89 or more
#define C_89_OR_MORE
#if C_LANGUAGE >= 199901L // C99 or more
#define C_99_OR_MORE
#if C_LANGUAGE >= 201112L // C11 or more
#define C_11_OR_MORE
#define C_11
#else // C99
#define C_99
#endif // C_LANGUAGE >= 201112L
#else // C89
#define C_89
#endif // C_LANGUAGE >= 199901L
#else // Unknown
#define C_STD_UNKNOWN
#endif // C_LANGUAGE >= 199409L

#endif // __cplusplus

#if (defined(_DEBUG) || defined(DBG)) && !defined(DEBUG)
#define DEBUG
#endif // defined(_DEBUG) && !defined(DEBUG)

#if defined(NDEBUG) && !defined(RELEASE)
#define RELEASE
#endif // defined(NDEBUG) && !defined(RELEASE)

#define CURRENT_FILE __FILE__
#define CURRENT_LINE __LINE__
#ifdef __func__
#define CURRENT_FUNC __func__
#else
#define CURRENT_FUNC __FUNCTION__
#endif // __func__

#define COMPILING_DATE __DATE__
#define COMPILING_TIME __TIME__

#ifdef C_LANGUAGE
#define using(name) typedef name ALIAS_ ## name
#endif // C_LANGUAGE

#if defined(CXX_LANGUAGE) && !defined(CXX_11_OR_MORE)
#define constexpr
#define override
#define final
#define noexcept throw()
#endif // defined(CXX_LANGUAGE) && !defined(CXX_11_OR_MORE)

#ifdef CXX_LANGUAGE
#define EXTERN_C extern "C"
#define EXTERN_C_START EXTERN_C {
#define EXTERN_C_END }
#else
#define EXTERN_C extern
#define EXTERN_C_START
#define EXTERN_C_END
#endif // CXX_LANGUAGE

#if defined(CXX_LANGUAGE) && !defined(CXX_11_OR_MORE)
#warning The C++ standard is too old. May not be compatible.
#endif // defined(CXX_LANGUAGE) && !defined(CXX_11_OR_MORE)

typedef const char *ModuleFullName;
typedef const struct {
    int major;
    int minor;
    int patch;
    double build;
    const char *releaseLevel;
    int serial;
} ModuleVersion;
typedef const char *ModuleAuthor;
typedef const char *ModuleAbout;
enum MODULE_RELATIONS {
    MODULE_RELATION_REQUIRES_MODULE, MODULE_RELATION_EXPORTS_PACKAGE
};
typedef const struct {
    enum MODULE_RELATIONS relation;
    const char *content;
} ModuleRelations[];

#define MODULE_INFO_START
#define MODULE_INFO_END
#define MODULE(name)
#define MODULE_FULL_NAME(name, fullName) ModuleFullName name ## FullName = (fullName);
#define MODULE_VERSION(name, major, minor, patch, build, releaseLevel, serial) \
    ModuleVersion name ## Version = {major, minor, patch, build, releaseLevel, serial};
#define MODULE_AUTHOR(name, author) ModuleAuthor name ## Author = (author);
#define MODULE_ABOUT(name, about) ModuleAbout name ## About = (about);
#define MODULE_RELATIONS(name, ...) ModuleRelations name ## Relations = {__VA_ARGS__};
#define REQUIRES_MODULE(module) {MODULE_RELATION_REQUIRES_MODULE, module}
#define EXPORTS_PACKAGE(package) {MODULE_RELATION_EXPORTS_PACKAGE, package}

#endif // !ENHANCED_CORE_DEFINES_H
