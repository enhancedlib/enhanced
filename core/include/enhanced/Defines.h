/*
 * Copyright (C) 2022 Liu Baihao. All rights reserved.
 *
 * Licensed under the Enhanced Software License.
 * You may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     https://sharedwonder.github.io/enhanced/LICENSE.txt
 *
 * UNLESS REQUIRED BY APPLICABLE LAW OR AGREED TO IN WRITING,
 * THE SOFTWARE IS ALWAYS PROVIDED "AS IS",
 * WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY.
 */

#pragma once

#ifndef __cplusplus
#error Please use the C++ language
#endif

// Detect current using which compiler to compile
#ifdef __clang__ // Clang
#define CLANG_COMPILER __clang__
#ifdef _MSC_VER
#define MSVC_ABI
#elif defined(__GNUC__)
#define GCC_ABI
#else
#define CLANG_ABI
#endif
#elif defined(_MSC_VER) // Microsoft Visual C++
#define MSVC_COMPILER _MSC_VER
#define MSVC_ABI
#elif defined(__GNUC__) // GNU Compiler Collections
#define GCC_COMPILER __GNUC__
#define GCC_ABI
#else // Unsupported
#error Unsupported compiler
#endif

// Detect the architecture for the current platform
#if defined(_M_IX86) || defined(__i386__) // x86
#define X86_ARCH
#elif defined(_M_X64) || defined(_M_AMD64) || defined(__x86_64__) // x86_64 (amd64)
#define X64_ARCH
#elif defined(_M_ARM) || defined(__arm__) // ARM32
#define ARM32_ARCH
#elif defined(_M_ARM64) || defined(__aarch64__) // ARM64 (AArch64)
#define ARM64_ARCH
#else // Unsupported
#error Unsupported architecture
#endif

// Detect the operating system
#if defined(_WIN32) || defined(_WIN64) // Microsoft Windows
#define WINDOWS_OS

#elif defined(__unix__) || defined(__unix) || defined(unix) || (defined(__APPLE__) && defined(__MACH__))
// Unix-style operating systems
#define UNIX_STYLE_OS

#if defined(__linux__) || defined(__linux) || defined(linux) || defined(__LINUX__) // Operating systems based on Linux kernel
#define LINUX_KERNEL_OS

#if defined(__gnu_linux__) || defined(__gnu_linux) // GNU/Linux
#define GNU_LINUX_OS
#elif defined(__ANDROID__) // Android
#define ANDROID_OS
#endif

#else

#include <sys/param.h>
#ifdef BSD // BSD operating systems
#define BSD_OS

#ifdef __FreeBSD__ // FreeBSD
#define FREE_BSD_OS
#elif defined(__NetBSD__) // NetBSD
#define NET_BSD_OS
#elif defined(__OpenBSD__) // OpenBSD
#define OPEN_BSD_OS
#elif defined(__DragonFly__) // DragonFly BSD
#define DRAGON_FLY_BSD_OS
#elif defined(__APPLE__) && defined(__MACH__) // Apple operating systems
#define APPLE_OS

#include <TargetConditionals.h>
#if TARGET_OS_MAC == 1 // Apple macOS
#define MAC_OS
#elif TARGET_OS_IPHONE == 1 // Apple iOS
#define IPHONE_OS
#endif

#endif
#endif

#endif
#else // Unsupported
#error Unsupported operating system
#endif

// Detect the current language and its standard
#ifndef MSVC_COMPILER
#define CXX_LANGUAGE __cplusplus
#else
#define CXX_LANGUAGE _MSVC_LANG
#endif

#if CXX_LANGUAGE >= 202002L // C++20 or more
#define CXX_20_OR_LATER
#if CXX_LANGUAGE > 202002L // C++23 or more
#define CXX_23_OR_LATER
#else // C++20
#define CXX_20
#endif
#else // Unknown
#error Unsupported C++ standard, please use least C++20 standard.
#endif

#if defined(ENHANCED_BUILDING) && !defined(CXX_20_OR_LATER)
#error To build this software, please use the C++20 standard or later.
#endif

#if (defined(_DEBUG) || defined(DBG)) && !defined(NDEBUG) && !defined(DEBUG)
#define DEBUG
#endif

#if (defined(MSVC_COMPILER) && defined(_CHAR_UNSIGNED)) || defined(__CHAR_UNSIGNED__)
#define CHAR_IS_UNSIGNED
#endif

#if !defined(MSVC_COMPILER) || defined(_NATIVE_WCHAR_T_DEFINED)
#define WCHAR_IS_BUILTIN_TYPE
#endif

#if defined(MSVC_COMPILER) || (__SIZEOF_WCHAR_T__ == 2)
#define WCHAR_EQUALS_UINT16
#else
#define WCHAR_EQUALS_INT32
#endif

#define EXTERN_C extern "C"
#define EXTERN_C_START EXTERN_C {
#define EXTERN_C_END }

#define PRAGMA(...) _Pragma(#__VA_ARGS__)

#define CURRENT_FUNC __func__
#define CURRENT_FILE __FILE__
#define CURRENT_LINE __LINE__

#define COMPILING_DATE __DATE__
#define COMPILING_TIME __TIME__

#ifdef CLANG_COMPILER
#define CLANG_WARNING_PUSH PRAGMA(clang diagnostic push)
#define CLANG_WARNING_DISABLE(id) PRAGMA(clang diagnostic warning id)
#define CLANG_WARNING_POP PRAGMA(clang diagnostic pop)
#else
#define CLANG_WARNING_PUSH
#define CLANG_WARNING_DISABLE
#define CLANG_WARNING_POP
#endif

#ifdef MSVC_COMPILER
#define MSVC_WARNING_PUSH PRAGMA(warning(push))
#define MSVC_WARNING_DISABLE(id) PRAGMA(warning(disable: id))
#define MSVC_WARNING_POP PRAGMA(warning(pop))
#else
#define MSVC_WARNING_PUSH
#define MSVC_WARNING_DISABLE(id)
#define MSVC_WARNING_POP
#endif

#ifdef GCC_COMPILER
#define GCC_WARNING_PUSH PRAGMA(gcc diagnostic push)
#define GCC_WARNING_DISABLE(id) PRAGMA(gcc diagnostic warning id)
#define GCC_WARNING_POP PRAGMA(gcc diagnostic pop)
#else
#define GCC_WARNING_PUSH
#define GCC_WARNING_DISABLE(id)
#define GCC_WARNING_POP
#endif

#define func auto
#define let auto
#define val const auto
#define scopedenum enum class
#define abstractclass class
#ifdef MSVC_ABI
#define interface struct __declspec(novtable)
#else
#define interface struct
#endif
#define abstract = 0
