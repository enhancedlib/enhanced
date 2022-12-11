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

#if defined(MSVC_ABI) && defined(_M_CEE)
#define CLR_ABI
#endif

// Detect the architecture for the current platform
#if defined(_M_IX86) || defined(__i386__) // x86
    #define X86_ARCH
#elif defined(_M_X64) || defined(_M_AMD64) || defined(__x86_64__) // x86_64 (amd64)
    #define X64_ARCH
#elif defined(_M_ARM) || defined(__arm__) // arm (arm32)
    #define ARM32_ARCH
#elif defined(_M_ARM64) || defined(__aarch64__) // arm64 (aarch64)
    #define ARM64_ARCH
#else // Unsupported
    #error Unsupported architecture
#endif

// Detect the operating system
#if defined(_WIN32) || defined(_WIN64) || defined(WIN32) // Microsoft Windows
    #define WINDOWS_OS

#elif defined(__unix__) || defined(__unix) || defined(unix) || (defined(__APPLE__) && defined(__MACH__))
    // Unix-style operating systems
    #define UNIX_STYLE_OS

    #if defined(__linux__) || defined(__linux) || defined(linux) || defined(__LINUX__) // Linux kernel OS
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

#if ((defined(_DEBUG) || defined(DBG)) || !defined(NDEBUG)) && !defined(DEBUG)
    #define DEBUG
#endif

#define PRAGMA(...) _Pragma(#__VA_ARGS__)

#define EMPTY_MACRO_ARGUMENT

#define CURRENT_FUNC __func__
#define CURRENT_FILE __FILE__
#define CURRENT_LINE __LINE__

#define COMPILING_DATE __DATE__
#define COMPILING_TIME __TIME__

#define RESTRICT __restrict

#define CDECL __cdecl
#define FASTCALL __fastcall
#define STDCALL __stdcall
#define THISCALL __thiscall

#ifdef MSVC_ABI
    #define VECTOR_CALL __vectorcall
    #ifdef CLR_ABI
        #define CLRCALL __clrcall
    #endif
#endif

#include <new>
#include <typeinfo>
#include <initializer_list>

#ifdef WINDOWS_OS
    #include <sal.h>
#endif
