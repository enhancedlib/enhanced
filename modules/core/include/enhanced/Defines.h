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
#elif defined(_MSC_VER) // Microsoft Visual C++
    #define E_SM_COMPILER_MSVC
#elif defined(__GNUC__) // GNU Compiler Collections
    #define E_SM_COMPILER_GCC
#else // Unsupported
    #error Unsupported compiler
#endif

#if defined(E_SM_COMPATIBILITY_MS) && defined(_M_CEE)
    #define E_SM_MS_CLR
#endif

// Detect the architecture for the current platform
#if defined(_M_IX86) || defined(__i386__) // x86
    #define E_SM_ARCH_X86
#elif defined(_M_X64) || defined(_M_AMD64) || defined(__x86_64__) // x86_64 (amd64)
    #define E_SM_ARCH_X64
#elif defined(_M_ARM) || defined(__arm__) // arm (arm32)
    #define E_SM_ARCH_ARM32
#elif defined(_M_ARM64) || defined(__aarch64__) // arm64 (aarch64)
    #define E_SM_ARCH_ARM64
#else // Unsupported
    #error Unsupported architecture
#endif

// Detect the operating system
#if defined(_WIN32) || defined(_WIN64) || defined(WIN32) // Microsoft Windows
    #define E_SM_OS_WINDOWS

#elif defined(__unix__) || defined(__unix) || defined(unix) || (defined(__APPLE__) && defined(__MACH__))
    // Unix-style operating systems
    #define E_SM_OS_UNIX_STYLE

    #if defined(__linux__) || defined(__linux) || defined(linux) || defined(__LINUX__) // Linux kernel OS
        #define E_SM_OS_LINUX_KERNEL

        #if defined(__gnu_linux__) || defined(__gnu_linux) // GNU/Linux
            #define E_SM_OS_GNU_LINUX

        #elif defined(__ANDROID__) // Android
            #define E_SM_OS_ANDROID
        #endif
    #else
        #include <sys/param.h>
        #ifdef BSD // BSD operating systems
            #define E_SM_OS_BSD

            #ifdef __FreeBSD__ // FreeBSD
                #define E_SM_OS_FREE_BSD
            #elif defined(__NetBSD__) // NetBSD
                #define E_SM_OS_NET_BSD
            #elif defined(__OpenBSD__) // OpenBSD
                #define E_SM_OS_OPEN_BSD
            #elif defined(__DragonFly__) // DragonFly BSD
                #define E_SM_OS_DRAGON_FLY_BSD
            #elif defined(__APPLE__) && defined(__MACH__) // Apple operating systems
                #define E_SM_OS_APPLE
                #include <TargetConditionals.h>
                #if OS_TARGET_MAC == 1 // Apple macOS
                    #define E_SM_OS_MAC
                #elif OS_TARGET_IPHONE == 1 // Apple iOS
                    #define E_SM_OS_IPHONE
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

// Detect the C++ standard
#if E_CXX_STANDARD >= 202002L // C++20 or later
    #if E_CXX_STANDARD > 202002L // C++23 or later
        #define E_SM_CXX_23_OR_LATER
    #else // C++20
        #define E_SM_CXX_20
    #endif
#else // Unsupported
    #error Unsupported C++ standard, please use the C++20 standard or later
#endif

// Determine whether debugging information is enabled
#if ((defined(_DEBUG) || defined(DBG)) || !defined(NDEBUG)) && !defined(DEBUG)
    #define E_SM_DEBUG
#endif

// Pre-processor

#if defined(_MSVC_TRADITIONAL) && _MSVC_TRADITIONAL
    #error MSVC traditional pre-processor mode is not supported
#endif

#define E_PRAGMA(...) _Pragma(#__VA_ARGS__)

#define E_HAS_INCLUDE __has_include
#define E_HAS_CPP_ATTRIBUTE __has_cpp_attribute

#define E_EMPTY_MACRO_ARG

#define E_LEFT_BRACKET (
#define E_RIGHT_BRACKET )

#define E_PACK_BRACKET_IF(...) __VA_OPT__(E_LEFT_BRACKET) __VA_ARGS__ __VA_OPT__(E_RIGHT_BRACKET)

#define _E_UNPACK_BRACKET_IMPL(...) __VA_ARGS__
#define E_UNPACK_BRACKET(...) _E_UNPACK_BRACKET_IMPL __VA_ARGS__

// Uses to expand macros to be converted into a string literal
#define _E_STRING_LITERAL_IMPL(...) #__VA_ARGS__
#define E_STRING_LITERAL(...) _E_STRING_LITERAL_IMPL(__VA_ARGS__)

#define E_CURRENT_FUNC __func__
#define E_CURRENT_FILE __FILE__
#define E_CURRENT_LINE __LINE__

#define E_COMPILING_DATE __DATE__
#define E_COMPILING_TIME __TIME__

// Compiler extensions

#define E_RESTRICT __restrict

#ifdef E_SM_COMPATIBILITY_MS
    #define E_FORCE_INLINE __forceinline
    #define E_NO_INLINE __declspec(noinline)
    #define E_ALLOCATOR __declspec(allocator)
    #define E_RET_RESTRICT __declspec(restrict)
#else
    #define E_FORCE_INLINE [[gnu::always_inline]]
    #define E_NO_INLINE [[gnu::noinline]]
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

#ifdef E_SM_OS_WINDOWS
    #define E_LIB_EXPORT __declspec(dllexport)
    #define E_LIB_IMPORT __declspec(dllimport)
#elif defined(E_SM_COMPILER_GCC)
    #define E_LIB_EXPORT __attribute__((visibility("default")))
    #define E_LIB_IMPORT __attribute__((visibility("default")))
#else
    #define E_LIB_EXPORT
    #define E_LIB_IMPORT
#endif

// Enhanced Macros

#define E_API(MODULE) _E_API_##MODULE

#define E_CLASS(NAME) \
    private: \
        using _enhanced_Class = NAME;

#define E_CLASS_HEADER private:
#define E_CLASS_BODY public:
#define E_CLASS_TYPE _enhanced_Class

#define _E_INTERNAL _enhanced_internal
