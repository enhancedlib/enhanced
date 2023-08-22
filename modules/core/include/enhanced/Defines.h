/*
 * This file is part of Enhanced Framework.
 *
 * Copyright (C) 2023 sharedwonder (Liu Baihao). All rights reserved.
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
 *    distribution of the Software, except for distributing modified versions and
 *    products that use the Software.
 *
 * 5. If you use this Software in your product, you shall indicate it.
 *
 * 6. Neither the name of the author nor the names of its contributors may
 *    be used to endorse or promote products derived from the Software.
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
    #define E_COMPATIBILITY_MS
    #ifdef E_COMPATIBILITY_MS
        #define SM_COMPATIBILITY_MS
    #endif
#elif defined(__GNUC__)
    #define E_COMPATIBILITY_GNU
    #ifdef E_COMPATIBILITY_GNU
        #define SM_COMPATIBILITY_GNU
    #endif
#endif

// Detect current using which compiler to compile
#ifdef __clang__ // Clang
    #define E_COMPILER_CLANG
    #define E_COMPILER_CLANG_VERSION_MAJOR __clang_major__
    #define E_COMPILER_CLANG_VERSION_MINOR __clang_minor__
    #define E_COMPILER_CLANG_VERSION_PATCH __clang_patchlevel__
#elif defined(_MSC_VER) // Microsoft Visual C++
    #define E_COMPILER_MSVC
    #define E_COMPILER_MSVC_VERSION_ID _MSC_VER
#elif defined(__GNUC__) // GNU Compiler Collection
    #define E_COMPILER_GCC
    #define E_COMPILER_GCC_VERSION_MAJOR __GNUC__
    #define E_COMPILER_GCC_VERSION_MINOR __GNUC_MINOR__
    #define E_COMPILER_GCC_VERSION_PATCH __GNUC_PATCHLEVEL__
#else // Unsupported
    #error Unsupported compiler
#endif

#if defined(E_COMPATIBILITY_MS) && defined(_M_CEE)
    #define E_MS_CLR
#endif

// Detect the architecture for the current platform
#if defined(_M_IX86) || defined(__i386__) // x86
    #define E_ARCH_X86
#elif defined(_M_X64) || defined(_M_AMD64) || defined(__x86_64__) // x86_64 (amd64)
    #define E_ARCH_X64
#elif defined(_M_ARM) || defined(__arm__) // arm (arm32)
    #define E_ARCH_ARM32
#elif defined(_M_ARM64) || defined(__aarch64__) // arm64 (aarch64)
    #define E_ARCH_ARM64
#else // Unsupported
    #error Unsupported architecture
#endif

// Detect the operating system
#if defined(_WIN32) || defined(_WIN64) || defined(WIN32) // Microsoft Windows
    #define E_OS_WINDOWS

#elif defined(__unix__) || defined(__unix) || defined(unix) || (defined(__APPLE__) && defined(__MACH__))
    // Unix-style operating systems
    #define E_OS_UNIX_STYLE

    #if defined(__linux__) || defined(__linux) || defined(linux) || defined(__LINUX__) // Linux kernel OS
        #define E_OS_LINUX_KERNEL

        #if defined(__gnu_linux__) || defined(__gnu_linux) // GNU/Linux
            #define E_OS_GNU_LINUX

        #elif defined(__ANDROID__) // Android
            #define E_OS_ANDROID
        #endif
    #else
        #include <sys/param.h>
        #ifdef BSD // BSD operating systems
            #define E_OS_BSD

            #ifdef __FreeBSD__ // FreeBSD
                #define E_OS_FREE_BSD
            #elif defined(__NetBSD__) // NetBSD
                #define E_OS_NET_BSD
            #elif defined(__OpenBSD__) // OpenBSD
                #define E_OS_OPEN_BSD
            #elif defined(__DragonFly__) // DragonFly BSD
                #define E_OS_DRAGON_FLY_BSD
            #elif defined(__APPLE__) && defined(__MACH__) // Apple operating systems
                #define E_OS_APPLE
                #include <TargetConditionals.h>
                #if OS_TARGET_MAC == 1 // Apple macOS
                    #define E_OS_MAC
                #elif OS_TARGET_IPHONE == 1 // Apple iOS
                    #define E_OS_IPHONE
                #endif
            #endif
        #endif
    #endif
#else // Unsupported
    #error Unsupported operating system
#endif

#ifndef E_COMPILER_MSVC
    #define E_CXX_STANDARD __cplusplus
#else
    #define E_CXX_STANDARD _MSVC_LANG
#endif

// Detect the C++ standard
#if E_CXX_STANDARD >= 202002L // C++20 or later
    #if E_CXX_STANDARD > 202002L // C++23 or later
        #define E_CXX_23_OR_LATER
    #else // C++20
        #define E_CXX_20
    #endif
#else // Unsupported
    #error Unsupported C++ standard, please use the C++20 standard or later
#endif

// Determine whether debugging information is enabled
#if ((defined(_DEBUG) || defined(DBG)) || !defined(NDEBUG)) && !defined(DEBUG)
    #define E_DEBUG
#endif

#define E_CURRENT_FUNC __func__
#define E_CURRENT_FILE __FILE__
#define E_CURRENT_LINE __LINE__

#define E_COMPILING_DATE __DATE__
#define E_COMPILING_TIME __TIME__

// Pre-processor

#if defined(_MSVC_TRADITIONAL) && _MSVC_TRADITIONAL
    #error MSVC traditional pre-processor mode is not supported
#endif

#define E_PRAGMA(...) _Pragma(#__VA_ARGS__)

#define E_HAS_INCLUDE __has_include
#define E_HAS_CPP_ATTRIBUTE __has_cpp_attribute

#define E_LEFT_BRACKET (
#define E_RIGHT_BRACKET )
#define E_COMMA ,
#define E_EMPTY

#define E_CONNECT(A, B) A##B
#define E_EXPANDED_CONNECT(A, B) E_CONNECT(A, B)

#define E_RAW_STRING(...) #__VA_ARGS__
#define E_STRING_LITERAL(...) E_RAW_STRING(__VA_ARGS__)

#define E_IF_NOT_EMPTY(VALUE, ...) __VA_OPT__(VALUE)

#define E_PACK_BRACKET_IF_NOT_EMPTY(...) E_IF_NOT_EMPTY((__VA_ARGS__), __VA_ARGS__)

#define _E_UNPACK_BRACKET(...) __VA_ARGS__
#define E_UNPACK_BRACKET(BLOCK) _E_UNPACK_BRACKET BLOCK

#define E_EXPAND_MACRO(MACRO, ARGS) MACRO ARGS

#define _E_CONNECT_ELEMENTS(LAST, ...) LAST
#define _E_CONNECT_ELEMENTS_(LAST, ...) LAST, __VA_ARGS__
#define E_CONNECT_ELEMENTS(LAST, ...) E_EXPANDED_CONNECT(_E_CONNECT_ELEMENTS, E_IF_NOT_EMPTY(_, __VA_ARGS__))(LAST, __VA_ARGS__)

// Used to extract element(s) from a sequence/vararg
#define E_EXTRACT(NUMBER, ...) _E_EXTRACT_##NUMBER(__VA_ARGS__,,,,,,,,,,,,,,,,,,,)
#define E_EXTRACT_FROM(FROM, ...) E_IF_NOT_EMPTY(_E_EXTRACT_FROM_##FROM(__VA_ARGS__), E_EXTRACT(FROM, __VA_ARGS__))
#define E_EXTRACT_TO(TO, ...) _E_EXTRACT_TO_##TO(__VA_ARGS__,,,,,,,,,,,,,,,,,,,)
#define E_EXTRACT_FROM_TO(FROM, TO, ...) E_EXTRACT_FROM(FROM, E_EXTRACT_TO(TO, __VA_ARGS__))

#define E_EXTRACT_PACKED(NUMBER, BLOCK) E_EXTRACT(NUMBER, E_UNPACK_BRACKET(BLOCK))
#define E_EXTRACT_PACKED_FROM(FROM, BLOCK) E_EXTRACT_FROM(FROM, E_UNPACK_BRACKET(BLOCK))
#define E_EXTRACT_PACKED_TO(TO, BLOCK) E_EXTRACT_TO(TO, E_UNPACK_BRACKET(BLOCK))
#define E_EXTRACT_PACKED_FROM_TO(FROM, TO, BLOCK) E_EXTRACT_FROM_TO(FROM, TO, E_UNPACK_BRACKET(BLOCK))

// E_EXTRACT
#define _E_EXTRACT_1(P1, ...) P1
#define _E_EXTRACT_2(P1, P2, ...) P2
#define _E_EXTRACT_3(P1, P2, P3, ...) P3
#define _E_EXTRACT_4(P1, P2, P3, P4, ...) P4
#define _E_EXTRACT_5(P1, P2, P3, P4, P5, ...) P5
#define _E_EXTRACT_6(P1, P2, P3, P4, P5, P6, ...) P6
#define _E_EXTRACT_7(P1, P2, P3, P4, P5, P6, P7, ...) P7
#define _E_EXTRACT_8(P1, P2, P3, P4, P5, P6, P7, P8, ...) P8
#define _E_EXTRACT_9(P1, P2, P3, P4, P5, P6, P7, P8, P9, ...) P9
#define _E_EXTRACT_10(P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, ...) P10
#define _E_EXTRACT_11(P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, ...) P11
#define _E_EXTRACT_12(P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, ...) P12
#define _E_EXTRACT_13(P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, ...) P13
#define _E_EXTRACT_14(P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, ...) P14
#define _E_EXTRACT_15(P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15, ...) P15
#define _E_EXTRACT_16(P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15, P16, ...) P16
#define _E_EXTRACT_17(P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15, P16, P17, ...) P17
#define _E_EXTRACT_18(P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15, P16, P17, P18, ...) P18
#define _E_EXTRACT_19(P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15, P16, P17, P18, P19, ...) P19
#define _E_EXTRACT_20(P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15, P16, P17, P18, P19, P20, ...) P20

// E_EXTRACT_FROM
#define _E_EXTRACT_FROM_1(P1, ...) E_CONNECT_ELEMENTS(P1, __VA_ARGS__)
#define _E_EXTRACT_FROM_2(P1, P2, ...) E_CONNECT_ELEMENTS(P2, __VA_ARGS__)
#define _E_EXTRACT_FROM_3(P1, P2, P3, ...) E_CONNECT_ELEMENTS(P3, __VA_ARGS__)
#define _E_EXTRACT_FROM_4(P1, P2, P3, P4, ...) E_CONNECT_ELEMENTS(P4, __VA_ARGS__)
#define _E_EXTRACT_FROM_5(P1, P2, P3, P4, P5, ...) E_CONNECT_ELEMENTS(P5, __VA_ARGS__)
#define _E_EXTRACT_FROM_6(P1, P2, P3, P4, P5, P6, ...) E_CONNECT_ELEMENTS(P6, __VA_ARGS__)
#define _E_EXTRACT_FROM_7(P1, P2, P3, P4, P5, P6, P7, ...) E_CONNECT_ELEMENTS(P7, __VA_ARGS__)
#define _E_EXTRACT_FROM_8(P1, P2, P3, P4, P5, P6, P7, P8, ...) E_CONNECT_ELEMENTS(P8, __VA_ARGS__)
#define _E_EXTRACT_FROM_9(P1, P2, P3, P4, P5, P6, P7, P8, P9, ...) E_CONNECT_ELEMENTS(P9, __VA_ARGS__)
#define _E_EXTRACT_FROM_10(P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, ...) E_CONNECT_ELEMENTS(P10, __VA_ARGS__)
#define _E_EXTRACT_FROM_11(P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, ...) E_CONNECT_ELEMENTS(P11, __VA_ARGS__)
#define _E_EXTRACT_FROM_12(P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, ...) E_CONNECT_ELEMENTS(P12, __VA_ARGS__)
#define _E_EXTRACT_FROM_13(P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, ...) E_CONNECT_ELEMENTS(P13, __VA_ARGS__)
#define _E_EXTRACT_FROM_14(P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, ...) E_CONNECT_ELEMENTS(P14, __VA_ARGS__)
#define _E_EXTRACT_FROM_15(P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15, ...) E_CONNECT_ELEMENTS(P15, __VA_ARGS__)
#define _E_EXTRACT_FROM_16(P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15, P16, ...) E_CONNECT_ELEMENTS(P16, __VA_ARGS__)
#define _E_EXTRACT_FROM_17(P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15, P16, P17, ...) E_CONNECT_ELEMENTS(P17, __VA_ARGS__)
#define _E_EXTRACT_FROM_18(P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15, P16, P17, P18, ...) E_CONNECT_ELEMENTS(P18, __VA_ARGS__)
#define _E_EXTRACT_FROM_19(P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15, P16, P17, P18, P19, ...) E_CONNECT_ELEMENTS(P19, __VA_ARGS__)
#define _E_EXTRACT_FROM_20(P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15, P16, P17, P18, P19, P20, ...) E_CONNECT_ELEMENTS(P20, __VA_ARGS__)

// E_EXTRACT_TO
#define _E_EXTRACT_TO_1(P1, ...) P1
#define _E_EXTRACT_TO_2(P1, P2, ...) E_CONNECT_ELEMENTS(P1, P2)
#define _E_EXTRACT_TO_3(P1, P2, P3, ...) E_CONNECT_ELEMENTS(P1, _E_EXTRACT_TO_2(P2, P3))
#define _E_EXTRACT_TO_4(P1, P2, P3, P4, ...) E_CONNECT_ELEMENTS(P1, _E_EXTRACT_TO_3(P2, P3, P4))
#define _E_EXTRACT_TO_5(P1, P2, P3, P4, P5, ...) E_CONNECT_ELEMENTS(P1, _E_EXTRACT_TO_4(P2, P3, P4, P5))
#define _E_EXTRACT_TO_6(P1, P2, P3, P4, P5, P6, ...) E_CONNECT_ELEMENTS(P1, _E_EXTRACT_TO_5(P2, P3, P4, P5, P6))
#define _E_EXTRACT_TO_7(P1, P2, P3, P4, P5, P6, P7, ...) E_CONNECT_ELEMENTS(P1, _E_EXTRACT_TO_6(P2, P3, P4, P5, P6, P7))
#define _E_EXTRACT_TO_8(P1, P2, P3, P4, P5, P6, P7, P8, ...) E_CONNECT_ELEMENTS(P1, _E_EXTRACT_TO_7(P2, P3, P4, P5, P6, P7, P8))
#define _E_EXTRACT_TO_9(P1, P2, P3, P4, P5, P6, P7, P8, P9, ...) E_CONNECT_ELEMENTS(P1, _E_EXTRACT_TO_8(P2, P3, P4, P5, P6, P7, P8, P9))
#define _E_EXTRACT_TO_10(P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, ...) E_CONNECT_ELEMENTS(P1, _E_EXTRACT_TO_9(P2, P3, P4, P5, P6, P7, P8, P9, P10))
#define _E_EXTRACT_TO_11(P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, ...) E_CONNECT_ELEMENTS(P1, _E_EXTRACT_TO_10(P2, P3, P4, P5, P6, P7, P8, P9, P10, P11))
#define _E_EXTRACT_TO_12(P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, ...) E_CONNECT_ELEMENTS(P1, _E_EXTRACT_TO_11(P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12))
#define _E_EXTRACT_TO_13(P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, ...) \
    E_CONNECT_ELEMENTS(P1, _E_EXTRACT_TO_12(P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13))
#define _E_EXTRACT_TO_14(P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, ...) \
    E_CONNECT_ELEMENTS(P1, _E_EXTRACT_TO_13(P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14))
#define _E_EXTRACT_TO_15(P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15, ...) \
    E_CONNECT_ELEMENTS(P1, _E_EXTRACT_TO_14(P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15))
#define _E_EXTRACT_TO_16(P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15, P16, ...) \
    E_CONNECT_ELEMENTS(P1, _E_EXTRACT_TO_15(P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15, P16))
#define _E_EXTRACT_TO_17(P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15, P16, P17, ...) \
    E_CONNECT_ELEMENTS(P1, _E_EXTRACT_TO_16(P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15, P16, P17))
#define _E_EXTRACT_TO_18(P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15, P16, P17, P18, ...) \
    E_CONNECT_ELEMENTS(P1, _E_EXTRACT_TO_17(P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15, P16, P17, P18))
#define _E_EXTRACT_TO_19(P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15, P16, P17, P18, P19, ...) \
    E_CONNECT_ELEMENTS(P1, _E_EXTRACT_TO_18(P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15, P16, P17, P18, P19))
#define _E_EXTRACT_TO_20(P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15, P16, P17, P18, P19, P20, ...) \
    E_CONNECT_ELEMENTS(P1, _E_EXTRACT_TO_19(P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15, P16, P17, P18, P19, P20))

// Compiler extensions

#define E_RESTRICT __restrict

#ifdef E_COMPATIBILITY_MS
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

#ifdef E_COMPILER_GCC
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

#ifdef E_COMPATIBILITY_MS
    #define E_VECTORCALL __vectorcall
#else
    #define E_VECTORCALL
#endif

#ifdef E_MS_CLR
    #define E_CLRCALL __clrcall
#else
    #define E_CLRCALL
#endif

#ifdef E_OS_WINDOWS
    #define E_LIB_EXPORT __declspec(dllexport)
    #define E_LIB_IMPORT __declspec(dllimport)
#elif defined(E_COMPILER_GCC)
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
