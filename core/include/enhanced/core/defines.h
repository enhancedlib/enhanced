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

// Detect current using which compiler to compile
#ifdef __clang__ // Clang
#define COMPILER_CLANG __clang__
#elif defined(_MSC_VER) // Microsoft Visual C++
#define COMPILER_MSVC _MSC_VER
#elif defined(__GNUC__) // GNU C/C++ Compiler
#define COMPILER_GCC __GNUC__
#else // Unsupported
#error Unsupported compiler
#endif

// Detect the architecture for the current platform
#if defined(_M_IX86) || defined(__i386__) // x86
#define ARCH_X86
#elif defined(_M_X64) || defined(_M_AMD64) || defined(__x86_64__) // x86_64 (amd64)
#define ARCH_X64
#elif defined(_M_ARM) || defined(__arm__) // ARM32
#define ARCH_ARM32
#elif defined(_M_ARM64) || defined(__aarch64__) // ARM64 (AArch64)
#define ARCH_ARM64
#else // Unsupported
#error Unsupported architecture
#endif

// Detect the operating system
#if defined(_WIN32) || defined(_WIN64) // Microsoft Windows
#define WINDOWS_OS

#elif defined(__unix__) || defined(__unix) || defined(unix) || (defined(__APPLE__) && defined(__MACH__))
// Unix-style operating systems
#define UNIX_STYLE_OS

#if defined(__linux__) || defined(__linux) || defined(linux) // Operating systems based on Linux kernel
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
#if TARGET_OS_MAC == 1 // macOS
#define MAC_OS
#elif TARGET_OS_IPHONE == 1 // iOS
#define IPHONE_OS
#endif

#endif
#endif

#endif
#else // Unsupported
#error Unsupported operating system
#endif

// Detect the current language and its standard
#ifdef __cplusplus // C++ language
#ifdef COMPILER_MSVC
#define CXX_LANGUAGE _MSVC_LANG
#else
#define CXX_LANGUAGE __cplusplus
#endif

#if CXX_LANGUAGE >= 199711L // C++98 or more
#define CXX_98_OR_LATER
#if CXX_LANGUAGE >= 201103L // C++11 or more
#define CXX_11_OR_LATER
#if CXX_LANGUAGE >= 201402L // C++14 or more
#define CXX_14_OR_LATER
#if CXX_LANGUAGE >= 201703L // C++17 or more
#define CXX_17_OR_LATER
#if CXX_LANGUAGE >= 202002L // C++20 or more
#define CXX_20_OR_LATER
#if CXX_LANGUAGE > 202002L // C++23 or more
#define CXX_23_OR_LATER
#else // C++20
#define CXX_20
#endif
#else // C++17
#define CXX_17
#endif
#else // C++14
#define CXX_14
#endif
#else // C++11
#define CXX_11
#endif
#else // C++98
#define CXX_98
#endif
#else // Unknown
#error Unknown C++ standard
#endif

#else // C language

#if defined(COMPILER_MSVC) && !defined(__STDC_VERSION__)
#define C_LANGUAGE 199409L
#else
#define C_LANGUAGE __STDC_VERSION__
#endif

#if C_LANGUAGE >= 199409L // C89 or more
#define C_89_OR_LATER
#if C_LANGUAGE >= 199901L // C99 or more
#define C_99_OR_LATER
#if C_LANGUAGE >= 201112L // C11 or more
#define C_11_OR_LATER
#if C_LANGUAGE >= 201710L // C17 or more
#define C_17_OR_LATER
#if C_LANGUAGE == 201710L // C17
#define C_17
#endif
#else // C11
#define C_11
#endif
#else // C99
#define C_99
#endif
#else // C89
#define C_89
#endif
#else // Unknown
#error Unknown C standard
#endif

#endif

#if (defined(_DEBUG) || defined(DBG)) && !defined(NDEBUG) && !defined(DEBUG)
#define DEBUG
#endif

#ifdef WINDOWS_OS
#define SAL_SUPPORTED
#endif

#if defined(__CHAR_UNSIGNED__) || (defined(COMPILER_MSVC) && defined(_CHAR_UNSIGNED))
#define CHAR_IS_UNSIGNED
#endif

#if (defined(COMPILER_MSVC) && defined(_NATIVE_WCHAR_T_DEFINED)) || (!defined(COMPILER_MSVC) && defined(CXX_LANGUAGE))
#define WCHAR_IS_BUILTIN_TYPE
#endif

#if defined(COMPILER_MSVC) || (__SIZEOF_WCHAR_T__ == 2)
#define WCHAR_EQUALS_UINT16
#else
#define WCHAR_EQUALS_INT32
#endif

#ifdef CXX_LANGUAGE
#ifdef __cpp_char8_t
#define CXX_U8CHAR_SUPPORTED
#endif

#ifndef CXX_11_OR_LATER
#define noexcept throw()
#define constexpr const
#define final
#define override

#define NOEXCEPT_EXT(condition)
#define DEFAULT_CONS {}
#define DEFAULT_DEST {}
#else
#define NOEXCEPT_EXT(condition) noexcept(condition)
#define DEFAULT_CONS = default
#define DEFAULT_DEST = default
#endif

#ifndef CXX_17_OR_LATER

#define INLINE_VAR

#define NAMESPACE_L1_BEGIN(level1) namespace level1 {
#define NAMESPACE_L1_END }

#define NAMESPACE_L2_BEGIN(level1, level2) namespace level1 { namespace level2 {
#define NAMESPACE_L2_END } }

#define NAMESPACE_L3_BEGIN(level1, level2, level3) namespace level1 { namespace level2 { namespace level3 {
#define NAMESPACE_L3_END } } }

#define NAMESPACE_L4_BEGIN(level1, level2, level3, level4) namespace level1 { namespace level2 { namespace level3 { namespace level4 {
#define NAMESPACE_L4_END } } } }

#define NAMESPACE_L5_BEGIN(level1, level2, level3, level4, level5) namespace level1 { namespace level2 { namespace level3 { namespace level4 { \
                                                                   namespace level5 {
#define NAMESPACE_L5_END } } } } }

#else

#define INLINE_VAR inline

#define NAMESPACE_L1_BEGIN(level1) namespace level1 {
#define NAMESPACE_L1_END }

#define NAMESPACE_L2_BEGIN(level1, level2) namespace level1::level2 {
#define NAMESPACE_L2_END }

#define NAMESPACE_L3_BEGIN(level1, level2, level3) namespace level1::level2::level3 {
#define NAMESPACE_L3_END }

#define NAMESPACE_L4_BEGIN(level1, level2, level3, level4) namespace level1::level2::level3::level4 {
#define NAMESPACE_L4_END }

#define NAMESPACE_L5_BEGIN(level1, level2, level3, level4, level5) namespace level1::level2::level3::level4::level5 {
#define NAMESPACE_L5_END }

#endif

#ifndef CXX_20_OR_LATER
#define consteval constexpr
#endif

#define EXTERN_C extern "C"
#define EXTERN_C_START EXTERN_C {
#define EXTERN_C_END }

#else

#define EXTERN_C extern
#define EXTERN_C_START
#define EXTERN_C_END

#endif

#define CURRENT_FILE __FILE__
#define CURRENT_LINE __LINE__
#if defined(C_99_OR_LATER) || defined(CXX_11_OR_LATER)
#define CURRENT_FUNC __func__
#else
#define CURRENT_FUNC __FUNCTION__
#endif

#define COMPILING_DATE __DATE__
#define COMPILING_TIME __TIME__

#ifdef ENHANCED_BUILDING
#if defined(CXX_LANGUAGE) && !defined(CXX_20_OR_LATER)
#error To build this software, please use the C++ 20 standard or later.
#elif defined(C_LANGUAGE) && !defined(C_17_OR_LATER)
#error To build this software, please use the C 17 standard or later.
#endif
#endif
