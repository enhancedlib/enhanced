/*
 * Copyright (C) 2023 Liu Baihao. All rights reserved.
 *
 * Licensed under the Enhanced Software License.
 *
 * This file is part of the Enhanced Software, and IT ALWAYS
 * PROVIDES "AS IS" WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY.
 *
 * You may not use this file except in compliance with the License.
 * You should obtain a copy of the License in the distribution,
 * if not, see <https://sharedwonder.github.io/enhanced/LICENSE.txt>
 */

#pragma once

#ifndef __cplusplus
    #error Use the C++ language instead
#endif

// Detect current using which compiler to compile
#ifdef __clang__ // Clang
    #define COMPILER_CLANG __clang__
    #define ABI_CLANG
    #ifdef _MSC_VER
        #define ABI_MSVC
    #elif defined(__GNUC__)
        #define ABI_GCC
    #endif
#elif defined(_MSC_VER) // Microsoft Visual C++
    #define COMPILER_MSVC _MSC_VER
    #define ABI_MSVC
#elif defined(__GNUC__) // GNU Compiler Collections
    #define COMPILER_GCC __GNUC__
    #define ABI_GCC
#else // Unsupported
    #error Unsupported compiler
#endif

#if defined(ABI_MSVC) && defined(_M_CEE)
    #define ABI_MS_CLR
#endif

// Detect the architecture for the current platform
#if defined(_M_IX86) || defined(__i386__) // x86
    #define ARCH_X86
#elif defined(_M_X64) || defined(_M_AMD64) || defined(__x86_64__) // x86_64 (amd64)
    #define ARCH_X64
#elif defined(_M_ARM) || defined(__arm__) // arm (arm32)
    #define ARCH_ARM32
#elif defined(_M_ARM64) || defined(__aarch64__) // arm64 (aarch64)
    #define ARCH_ARM64
#else // Unsupported
    #error Unsupported architecture
#endif

// Detect the operating system
#if defined(_WIN32) || defined(_WIN64) || defined(WIN32) // Microsoft Windows
    #define OS_WINDOWS

#elif defined(__unix__) || defined(__unix) || defined(unix) || (defined(__APPLE__) && defined(__MACH__))
    // Unix-style operating systems
    #define OS_UNIX_STYLE

    #if defined(__linux__) || defined(__linux) || defined(linux) || defined(__LINUX__) // Linux kernel OS
        #define OS_LINUX_KERNEL

        #if defined(__gnu_linux__) || defined(__gnu_linux) // GNU/Linux
            #define OS_GNU_LINUX
        #elif defined(__ANDROID__) // Android
            #define OS_ANDROID
        #endif
    #else
        #include <sys/param.h>
        #ifdef BSD // BSD operating systems
            #define OS_BSD

            #ifdef __FreeBSD__ // FreeBSD
                #define OS_FREE_BSD
            #elif defined(__NetBSD__) // NetBSD
                #define OS_NET_BSD
            #elif defined(__OpenBSD__) // OpenBSD
                #define OS_OPEN_BSD
            #elif defined(__DragonFly__) // DragonFly BSD
                #define OS_DRAGON_FLY_BSD
            #elif defined(__APPLE__) && defined(__MACH__) // Apple operating systems
                #define OS_APPLE
                #include <TargetConditionals.h>
                #if OS_TARGET_MAC == 1 // Apple macOS
                    #define OS_MAC
                #elif OS_TARGET_IPHONE == 1 // Apple iOS
                    #define OS_IPHONE
                #endif
            #endif
        #endif
    #endif
#else // Unsupported
    #error Unsupported operating system
#endif

// Detect the C++ standard
#ifndef COMPILER_MSVC
    #define CXX_STANDARD __cplusplus
#else
    #define CXX_STANDARD _MSVC_LANG
#endif

#if CXX_STANDARD >= 202002L // C++20 or more
    #define CXX_20_OR_LATER
    #if CXX_STANDARD > 202002L // C++23 or more
        #define CXX_23_OR_LATER
    #else // C++20
        #define CXX_20
    #endif
#else // Unknown
    #error Unsupported C++ standard, please use the C++20 standard or later
#endif

#if ((defined(_DEBUG) || defined(DBG)) || !defined(NDEBUG)) && !defined(DEBUG)
    #define DEBUG
#endif

// Pre-processor

#define PRAGMA(...) _Pragma(#__VA_ARGS__)

#define HAS_INCLUDE __has_include
#define HAS_CPP_ATTRIBUTE __has_cpp_attribute

#define EMPTY_MACRO_ARG

#define CURRENT_FUNC __func__
#define CURRENT_FILE __FILE__
#define CURRENT_LINE __LINE__

#define COMPILING_DATE __DATE__
#define COMPILING_TIME __TIME__

// Compiler extensions

#define RESTRICT __restrict

#ifdef ABI_MSVC
    #define FORCE_INLINE __forceinline
    #define NO_INLINE __declspec(noinline)
#elif defined(COMPILER_GCC) || defined(COMPILER_CLANG)
    #define FORCE_INLINE __attribute__((always_inline))
    #define NO_INLINE __attribute__((noinline))
#endif

#ifdef ABI_MSVC
    #define ALLOCATOR __declspec(allocator)
#elif defined(COMPILER_GCC) || defined(COMPILER_CLANG)
    #define ALLOCATOR
#endif

#ifdef ABI_MSVC
    #define RET_RESTRICT __declspec(restrict)
#elif defined(COMPILER_GCC) || defined(COMPILER_CLANG)
    #define RET_RESTRICT [[gnu::malloc]]
#endif

#ifdef COMPILER_GCC
    #define CDECL __attribute__((cdecl))
    #define FASTCALL __attribute__((fastcall))
    #define STDCALL __attribute__((stdcall))
    #define THISCALL __attribute__((thiscall))
#else
    #define CDECL __cdecl
    #define FASTCALL __fastcall
    #define STDCALL __stdcall
    #define THISCALL __thiscall
#endif

#ifdef ABI_MSVC
    #define VECTORCALL __vectorcall
    #ifdef ABI_MS_CLR
        #define CLRCALL __clrcall
    #endif
#endif

// Some identifiers in the stantard library has special meaning and cannot
// be implemented in other header files, so we must include the header files of them

#include <new> // std::nothrow_t, std::align_val_t
#include <typeinfo> // std::type_info, typeid (keyword)
#include <initializer_list> // std::initializer_list
