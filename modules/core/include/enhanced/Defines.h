/*
 * This file is part of Enhanced Framework.
 *
 * Copyright (C) 2023 Liu Baihao (sharedwonder). All rights reserved.
 *
 * Permission is hereby granted, to any person obtaining a copy of this software
 * and associated documentation files (the "Software"), to deal in the Software,
 * including without limitation the rights to use, copy, modify, merge,
 * distribute. Unless you have obtained permission from the copyright holders,
 * subject to the following restrictions:
 *
 * 1. The above copyright notice and this permission notice shall be included in
 *    all copies of the Software and modified versions.
 *
 * 2. You may not misrepresent the source of the Software, and you may not claim
 *    that you wrote the original version.
 *
 * 3. You may not misrepresent the modified version as the original version.
 *
 * 4. You may not charge any fees or receive other compensation for the
 *    distribution of the Software, excluding distribution of modified versions
 *    and products using the Software.
 *
 * 5. If you use this Software in your product, you shall indicate it.
 *
 * 6. Neither the name of the author nor the names of its contributors may
 *    be used to endorse or promote products derived from the Software
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#pragma once

#ifndef __cplusplus
    #error Use the C++ language instead
#endif

#ifdef _MSC_VER
    #define E_SM_COMPATIBILITY_MS
    #ifdef E_SM_COMPATIBILITY_MS
        #define SM_COMPATIBILITY_MS
    #endif
#elif defined(__GNUC__)
    #define E_SM_COMPATIBILITY_GNU
    #ifdef E_SM_COMPATIBILITY_GNU
        #define SM_COMPATIBILITY_GNU
    #endif
#endif

// Detect current using which compiler to compile
#ifdef __clang__ // Clang
    #define E_SM_COMPILER_CLANG
    #ifdef E_SM_MACRO_NO_PREFIX_ALIAS
        #define SM_COMPILER_CLANG
    #endif
#elif defined(_MSC_VER) // Microsoft Visual C++
    #define E_SM_COMPILER_MSVC
    #ifdef E_SM_MACRO_NO_PREFIX_ALIAS
        #define SM_COMPILER_MSVC
    #endif
#elif defined(__GNUC__) // GNU Compiler Collections
    #define E_SM_COMPILER_GCC
    #ifdef E_SM_MACRO_NO_PREFIX_ALIAS
        #define SM_COMPILER_GCC
    #endif
#else // Unsupported
    #error Unsupported compiler
#endif

#if defined(E_SM_COMPATIBILITY_MS) && defined(_M_CEE)
    #define E_SM_MS_CLR
    #ifdef E_SM_MACRO_NO_PREFIX_ALIAS
        #define SM_MS_CLR
    #endif
#endif

// Detect the architecture for the current platform
#if defined(_M_IX86) || defined(__i386__) // x86
    #define E_SM_ARCH_X86
    #ifdef E_SM_MACRO_NO_PREFIX_ALIAS
        #define SM_ARCH_X86
    #endif
#elif defined(_M_X64) || defined(_M_AMD64) || defined(__x86_64__) // x86_64 (amd64)
    #define E_SM_ARCH_X64
    #ifdef E_SM_MACRO_NO_PREFIX_ALIAS
        #define SM_ARCH_X64
    #endif
#elif defined(_M_ARM) || defined(__arm__) // arm (arm32)
    #define E_SM_ARCH_ARM32
    #ifdef E_SM_MACRO_NO_PREFIX_ALIAS
        #define SM_ARCH_ARM32
    #endif
#elif defined(_M_ARM64) || defined(__aarch64__) // arm64 (aarch64)
    #define E_SM_ARCH_ARM64
    #ifdef E_SM_MACRO_NO_PREFIX_ALIAS
        #define SM_ARCH_ARM64
    #endif
#else // Unsupported
    #error Unsupported architecture
#endif

// Detect the operating system
#if defined(_WIN32) || defined(_WIN64) || defined(WIN32) // Microsoft Windows
    #define E_SM_OS_WINDOWS
    #ifdef E_SM_MACRO_NO_PREFIX_ALIAS
        #define SM_OS_WINDOWS
    #endif

#elif defined(__unix__) || defined(__unix) || defined(unix) || (defined(__APPLE__) && defined(__MACH__))
    // Unix-style operating systems
    #define E_SM_OS_UNIX_STYLE
    #ifdef E_SM_MACRO_NO_PREFIX_ALIAS
        #define SM_OS_UNIX_STYLE
    #endif

    #if defined(__linux__) || defined(__linux) || defined(linux) || defined(__LINUX__) // Linux kernel OS
        #define E_SM_OS_LINUX_KERNEL
        #ifdef E_SM_MACRO_NO_PREFIX_ALIAS
            #define SM_OS_LINUX_KERNEL
        #endif

        #if defined(__gnu_linux__) || defined(__gnu_linux) // GNU/Linux
            #define E_SM_OS_GNU_LINUX
            #ifdef E_SM_MACRO_NO_PREFIX_ALIAS
                #define SM_OS_GNU_LINUX
            #endif

        #elif defined(__ANDROID__) // Android
            #define E_SM_OS_ANDROID
            #ifdef E_SM_MACRO_NO_PREFIX_ALIAS
                #define SM_OS_ANDROID
            #endif
        #endif
    #else
        #include <sys/param.h>
        #ifdef BSD // BSD operating systems
            #define E_SM_OS_BSD
            #ifdef E_SM_MACRO_NO_PREFIX_ALIAS
                #define SM_OS_BSD
            #endif

            #ifdef __FreeBSD__ // FreeBSD
                #define E_SM_OS_FREE_BSD
                #ifdef E_SM_MACRO_NO_PREFIX_ALIAS
                    #define SM_OS_FREE_BSD
                #endif
            #elif defined(__NetBSD__) // NetBSD
                #define E_SM_OS_NET_BSD
                #ifdef E_SM_MACRO_NO_PREFIX_ALIAS
                    #define SM_OS_NET_BSD
                #endif
            #elif defined(__OpenBSD__) // OpenBSD
                #define E_SM_OS_OPEN_BSD
                #ifdef E_SM_MACRO_NO_PREFIX_ALIAS
                    #define SM_OS_OPEN_BSD
                #endif
            #elif defined(__DragonFly__) // DragonFly BSD
                #define E_SM_OS_DRAGON_FLY_BSD
                #ifdef E_SM_MACRO_NO_PREFIX_ALIAS
                    #define SM_OS_DRAGON_FLY_BSD
                #endif
            #elif defined(__APPLE__) && defined(__MACH__) // Apple operating systems
                #define E_SM_OS_APPLE
                #ifdef E_SM_MACRO_NO_PREFIX_ALIAS
                    #define SM_OS_APPLE
                #endif
                #include <TargetConditionals.h>
                #if OS_TARGET_MAC == 1 // Apple macOS
                    #define E_SM_OS_MAC
                    #ifdef E_SM_MACRO_NO_PREFIX_ALIAS
                        #define SM_OS_MAC
                    #endif
                #elif OS_TARGET_IPHONE == 1 // Apple iOS
                    #define E_SM_OS_IPHONE
                    #ifdef E_SM_MACRO_NO_PREFIX_ALIAS
                        #define SM_OS_IPHONE
                    #endif
                #endif
            #endif
        #endif
    #endif
#else // Unsupported
    #error Unsupported operating system
#endif

#ifndef E_SM_COMPILER_MSVC
    #define E_CXX_STANDARD __cplusplus
#else
    #define E_CXX_STANDARD _MSVC_LANG
#endif

#ifdef E_SM_MACRO_NO_PREFIX_ALIAS
    #define CXX_STANDARD E_CXX_STANDARD
#endif

// Detect the C++ standard
#if E_CXX_STANDARD >= 202002L // C++20 or later
    #if E_CXX_STANDARD > 202002L // C++23 or later
        #define E_SM_CXX_23_OR_LATER
        #ifdef E_SM_MACRO_NO_PREFIX_ALIAS
            #define SM_CXX_23_OR_LATER
        #endif
    #else // C++20
        #define E_SM_CXX_20
        #ifdef E_SM_MACRO_NO_PREFIX_ALIAS
            #define SM_CXX_20
        #endif
    #endif
#else // Unsupported
    #error Unsupported C++ standard, please use the C++20 standard or later
#endif

// Determine whether debugging information is enabled
#if ((defined(_DEBUG) || defined(DBG)) || !defined(NDEBUG)) && !defined(DEBUG)
    #define E_SM_DEBUG
    #ifdef E_SM_MACRO_NO_PREFIX_ALIAS
        #define SM_DEBUG
    #endif
#endif

// Pre-processor

#define E_PRAGMA(...) _Pragma(#__VA_ARGS__)

#define E_HAS_INCLUDE __has_include
#define E_HAS_CPP_ATTRIBUTE __has_cpp_attribute

#define E_EMPTY_MACRO_ARG

#define __E_TO_STR_IMPL(...) #__VA_ARGS__
#define E_TO_STR(...) __E_TO_STR_IMPL(__VA_ARGS__)

#define E_CURRENT_FUNC __func__
#define E_CURRENT_FILE __FILE__
#define E_CURRENT_LINE __LINE__

#define E_COMPILING_DATE __DATE__
#define E_COMPILING_TIME __TIME__

#ifdef E_SM_MACRO_NO_PREFIX_ALIAS
    #define PRAGMA E_PRAGMA

    #define HAS_INCLUDE E_HAS_INCLUDE
    #define HAS_CPP_ATTRIBUTE E_HAS_CPP_ATTRIBUTE

    #define EMPTY_MACRO_ARG E_EMPTY_MACRO_ARG

    #define CURRENT_FUNC E_CURRENT_FUNC
    #define CURRENT_FILE E_CURRENT_FILE
    #define CURRENT_LINE E_CURRENT_LINE

    #define COMPILING_DATE E_COMPILING_DATE
    #define COMPILING_TIME E_COMPILING_TIME
#endif

// Compiler extensions

#define E_RESTRICT __restrict

#ifdef E_SM_COMPATIBILITY_MS
    #define E_FORCE_INLINE __forceinline
    #define E_NO_INLINE __declspec(noinline)
    #define E_ALLOCATOR __declspec(allocator)
    #define E_RET_RESTRICT __declspec(restrict)
#else
    #define E_FORCE_INLINE __attribute__((always_inline))
    #define E_NO_INLINE __attribute__((noinline))
    #define E_ALLOCATOR
    #define E_RET_RESTRICT [[gnu::malloc]]
#endif

#ifdef E_SM_COMPILER_GCC
    #define E_CDECL __attribute__((cdecl))
    #define E_FASTCALL __attribute__((fastcall))
    #define E_STDCALL __attribute__((stdcall))
    #define E_THISCALL __attribute__((thiscall))
#else
    #define E_CDECL __cdecl
    #define E_FASTCALL __fastcall
    #define E_STDCALL __stdcall
    #define E_THISCALL __thiscall
#endif

#ifdef E_SM_COMPATIBILITY_MS
    #define E_VECTORCALL __vectorcall
#else
    #define E_VECTORCALL
#endif

#ifdef E_SM_MS_CLR
    #define E_CLRCALL __clrcall
#else
    #define E_CLRCALL
#endif

#ifdef E_SM_MACRO_NO_PREFIX_ALIAS
    #define RESTRICT E_RESTRICT

    #define FORCE_INLINE E_FORCE_INLINE
    #define NO_INLINE E_NO_INLINE
    #define ALLOCATOR E_ALLOCATOR
    #define RET_RESTRICT E_RET_RESTRICT

    #define CDECL E_CDECL
    #define FASTCALL E_FASTCALL
    #define STDCALL E_STDCALL
    #define THISCALL E_THISCALL
    #define VECTORCALL E_VECTORCALL
    #define CLRCALL E_CLRCALL
#endif

#ifdef E_SM_OS_WINDOWS
    #define E_LIB_EXPORT __declspec(dllexport)
    #define E_LIB_IMPORT __declspec(dllimport)
#elif defined(E_SM_COMPILER_GCC)
    #define E_LIB_EXPORT [[gnu::visibility("default")]]
    #define E_LIB_IMPORT [[gnu::visibility("default")]]
#endif
