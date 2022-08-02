/*
 * Copyright (C) 2022 Liu Baihao. All rights reserved.
 *
 * This software is licensed under Enhanced License.
 * You may not use this file except in compliance with the License.
 * You should see a copy of Enhanced License in this software, if not, visit
 * <https://sharedwonder.github.io/enhanced-website/ENHANCED-LICENSE.txt>
 *
 * The Software is always provided "AS IS",
 * WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY.
 */

#pragma once

#include "defines.h"

// Prevents system definitions from conflicting with the definitions of this header file.
#ifdef COMPILER_MSVC
#include <limits.h>
#else
#define _INC_LIMITS
#ifdef COMPILER_GCC
#define _GCC_LIMITS_H_
#endif // COMPILER_GCC
#endif // COMPILER_MSVC

typedef char int8;
typedef short int16;
typedef int int32;
#if defined(WINDOWS_OS) || defined(X86_PROCESSOR)
typedef long long int64;
#elif defined(LINUX_OS)
typedef long int64;
#endif // defined(WINDOWS_OS)

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
#if defined(WINDOWS_OS) || defined(X86_PROCESSOR)
typedef unsigned long long uint64;
#elif defined(LINUX_OS)
typedef unsigned long uint64;
#endif // defined(WINDOWS_OS) || defined(X86_PROCESSOR)

typedef float float32;
typedef double float64;
#ifndef COMPILER_MSVC
#if defined(X86_PROCESSOR)
typedef long double float96;
#elif defined(X64_PROCESSOR)
typedef long double float128;
#endif // defined(X86_PROCESSOR)
#endif // !COMPILER_MSVC

typedef int64 llong;

typedef uint8 uchar;
typedef uint16 ushort;
typedef uint32 uint;
#if defined(WINDOWS_OS) || defined(X86_PROCESSOR)
typedef uint32 ulong;
#elif defined(LINUX_OS)
typedef uint64 ulong;
#endif // defined(WINDOWS_OS) || defined(X86_PROCESSOR)
typedef uint64 ullong;

#ifndef COMPILER_MSVC
#if defined(X86_PROCESSOR)
typedef float96 ldouble;
#elif defined(X64_PROCESSOR)
typedef float128 ldouble;
#endif // defined(X86_PROCESSOR)
#else
typedef float64 ldouble;
#endif // !COMPILER_MSVC

typedef uint16 WChar;
#if defined(X86_PROCESSOR)
typedef uint32 Size;
#elif defined(X64_PROCESSOR)
typedef uint64 Size;
#else // Unknown
typedef uint32 Size;
#endif // defined(X86_PROCESSOR)

typedef uint8 byte;
typedef uint16 word;
typedef uint32 dword;
typedef uint64 qword;

#ifdef C_LANGUAGE
#ifdef C_99_OR_MORE
typedef _Bool bool;
#else
typedef uint8 bool;
#endif // C_99_OR_MORE

#ifdef false
#undef false
#endif // false
#ifdef true
#undef true
#endif // true

#define false 0
#define true 1
#endif // C_LANGUAGE

#ifdef CXX_LANGUAGE
#ifdef CXX_11_OR_MORE
#define null nullptr
typedef decltype(null) NullType;
#else
#if defined(WINDOWS_OS) && defined(X64_PROCESSOR)
#define null 0LL
typedef llong NullType;
#else
#define null 0
typedef int NullType;
#endif // defined(WINDOWS_OS) && defined(X64_PROCESSOR)
#endif // CXX_11_OR_MORE
#else
#define null ((void*) 0)
typedef void* NullType;
#endif // CXX_LANGUAGE

#ifdef INT8_MIN
#undef INT8_MIN
#endif // INT8_MIN
#ifdef INT16_MIN
#undef INT16_MIN
#endif // INT16_MIN
#ifdef INT32_MIN
#undef INT32_MIN
#endif // INT32_MIN
#ifdef INT64_MIN
#undef INT64_MIN
#endif // INT64_MIN

#ifdef UINT8_MIN
#undef UINT8_MIN
#endif // UINT8_MIN
#ifdef UINT16_MIN
#undef UINT16_MIN
#endif // UINT16_MIN
#ifdef UINT32_MIN
#undef UINT32_MIN
#endif // UINT32_MIN
#ifdef UINT64_MIN
#undef UINT64_MIN
#endif // UINT64_MIN

#ifdef FLOAT32_MIN
#undef FLOAT32_MIN
#endif // FLOAT32_MIN
#ifdef FLOAT64_MIN
#undef FLOAT64_MIN
#endif // FLOAT64_MIN
#ifdef FLOAT96_MIN
#undef FLOAT96_MIN
#endif // FLOAT96_MIN
#ifdef FLOAT128_MIN
#undef FLOAT128_MIN
#endif // FLOAT128_MIN

#ifdef CHAR_MIN
#undef CHAR_MIN
#endif // CHAR_MIN
#ifdef SHORT_MIN
#undef SHORT_MIN
#endif // SHORT_MIN
#ifdef INT_MIN
#undef INT_MIN
#endif // INT_MIN
#ifdef LONG_MIN
#undef LONG_MIN
#endif // LONG_MIN
#ifdef LLONG_MIN
#undef LLONG_MIN
#endif // LLONG_MIN

#ifdef UCHAR_MIN
#undef UCHAR_MIN
#endif // UCHAR_MIN
#ifdef USHORT_MIN
#undef USHORT_MIN
#endif // USHORT_MIN
#ifdef UINT_MIN
#undef UINT_MIN
#endif // UINT_MIN
#ifdef ULONG_MIN
#undef ULONG_MIN
#endif // ULONG_MIN
#ifdef ULLONG_MIN
#undef ULLONG_MIN
#endif // ULLONG_MIN

#ifdef FLOAT_MIN
#undef FLOAT_MIN
#endif // FLOAT_MIN
#ifdef DOUBLE_MIN
#undef DOUBLE_MIN
#endif // DOUBLE_MIN
#ifdef LDOUBLE_MIN
#undef LDOUBLE_MIN
#endif // LDOUBLE_MIN

#ifdef BYTE_TYPE_MIN
#undef BYTE_TYPE_MIN
#endif // BYTE_TYPE_MIN
#ifdef WCHAR_TYPE_MIN
#undef WCHAR_TYPE_MIN
#endif // WCHAR_TYPE_MIN
#ifdef SIZE_TYPE_MIN
#undef SIZE_TYPE_MIN
#endif // SIZE_TYPE_MIN

#ifdef BYTE_MIN
#undef BYTE_MIN
#endif // BYTE_MIN
#ifdef WORD_MIN
#undef WORD_MIN
#endif // WORD_MIN
#ifdef DWORD_MIN
#undef DWORD_MIN
#endif // DWORD_MIN
#ifdef QWORD_MIN
#undef QWORD_MIN
#endif // QWORD_MIN

#define INT8_MIN ((int8) (-(0xff >> 1) - 1)) // -128
#define INT16_MIN ((int16) (-(0xffff >> 1) - 1)) // -32768
#define INT32_MIN ((int32) (-(0xffffffff >> 1) - 1)) // -2147483648
#define INT64_MIN ((int64) (-(0xffffffffffffffff >> 1) - 1)) // -9223372036854775808

#define UINT8_MIN ((uint8) 0x0) // 0
#define UINT16_MIN ((uint16) 0x0) // 0
#define UINT32_MIN ((uint32) 0x0) // 0
#define UINT64_MIN ((uint64) 0x0) // 0

#define FLOAT32_MIN ((float32) 1.17549435082228750796873653722224568E-38)
#define FLOAT64_MIN ((float64) 2.22507385850720138309023271733240406E-308)
#ifndef COMPILER_MSVC
#if defined(X86_PROCESSOR)
#define FLOAT96_MIN ((float96) 3.36210314311209350626267781732175260E-4932L) // Why is it the same as float128? (Tested)
#elif defined(X64_PROCESSOR)
#define FLOAT128_MIN ((float128) 3.36210314311209350626267781732175260E-4932L)
#endif // defined(X86_PROCESSOR)
#endif // !COMPILER_MSVC

#define CHAR_MIN INT8_MIN
#define SHORT_MIN INT16_MIN
#define INT_MIN INT32_MIN
#if defined(WINDOWS_OS) || defined(X86_PROCESSOR)
#define LONG_MIN INT32_MIN
#elif defined(LINUX_OS)
#define LONG_MIN INT64_MIN
#else // Unknown
#define LONG_MIN INT64_MIN
#endif // defined(WINDOWS_OS) || defined(X86_PROCESSOR)
#define LLONG_MIN INT64_MIN

#define UCHAR_MIN UINT8_MIN;
#define USHORT_MIN UINT16_MIN;
#define UINT_MIN UINT32_MIN;
#if defined(WINDOWS_OS)|| defined(X86_PROCESSOR)
#define ULONG_MIN UINT32_MIN
#elif defined(LINUX_OS
#define ULONG_MIN UINT64_MIN
#else // Unknown
#define ULONG_MIN UINT64_MIN
#endif // defined(WINDOWS_OS) || defined(X86_PROCESSOR)
#define ULLONG_MIN UINT64_MIN

#define FLOAT_MIN FLOAT32_MIN
#define DOUBLE_MIN FLOAT64_MIN
#ifdef COMPILER_MSVC
#define LDOUBLE_MIN FLOAT32_MIN
#else // Another compiler
#if defined(X86_PROCESSOR)
#define LDOUBLE_MIN FLOAT96_MIN
#elif defined(X64_PROCESSOR)
#define LDOUBLE_MIN FLOAT128_MIN
#else // Unknown
#define LDOUBLE_MIN FLOAT32_MIN
#endif // defined(X86_PROCESSOR)
#endif // COMPILER_MSVC

#define BYTE_TYPE_MIN UINT8_MIN
#define WCHAR_TYPE_MIN UINT16_MIN
#if defined(X86_PROCESSOR)
#define SIZE_TYPE_MIN UINT32_MIN
#elif defined(X64_PROCESSOR)
#define SIZE_TYPE_MIN UINT64_MIN
#else // Unknown
#define SIZE_TYPE_MIN UINT32_MIN
#endif // X64_PROCESSOR

#define BYTE_MIN UINT8_MIN
#define WORD_MIN UINT16_MIN
#define DWORD_MIN UINT32_MIN
#define QWORD_MIN UINT64_MIN

#ifdef INT8_MAX
#undef INT8_MAX
#endif // INT8_MAX
#ifdef INT16_MAX
#undef INT16_MAX
#endif // INT16_MAX
#ifdef INT32_MAX
#undef INT32_MAX
#endif // INT32_MAX
#ifdef INT64_MAX
#undef INT64_MAX
#endif // INT64_MAX

#ifdef UINT8_MAX
#undef UINT8_MAX
#endif // UINT8_MAX
#ifdef UINT16_MAX
#undef UINT16_MAX
#endif // UINT16_MAX
#ifdef UINT32_MAX
#undef UINT32_MAX
#endif // UINT32_MAX
#ifdef UINT64_MAX
#undef UINT64_MAX
#endif // UINT64_MAX

#ifdef FLOAT32_MAX
#undef FLOAT32_MAX
#endif // FLOAT32_MAX
#ifdef FLOAT64_MAX
#undef FLOAT64_MAX
#endif // FLOAT64_MAX
#ifdef FLOAT96_MAX
#undef FLOAT96_MAX
#endif // FLOAT96_MAX
#ifdef FLOAT128_MAX
#undef FLOAT128_MAX
#endif // FLOAT128_MAX

#ifdef CHAR_MAX
#undef CHAR_MAX
#endif // CHAR_MAX
#ifdef SHORT_MAX
#undef SHORT_MAX
#endif // SHORT_MAX
#ifdef INT_MAX
#undef INT_MAX
#endif // INT_MAX
#ifdef LONG_MAX
#undef LONG_MAX
#endif // LONG_MAX
#ifdef LLONG_MAX
#undef LLONG_MAX
#endif // LLONG_MAX

#ifdef UCHAR_MAX
#undef UCHAR_MAX
#endif // UCHAR_MAX
#ifdef USHORT_MAX
#undef USHORT_MAX
#endif // USHORT_MAX
#ifdef UINT_MAX
#undef UINT_MAX
#endif // UINT_MAX
#ifdef ULONG_MAX
#undef ULONG_MAX
#endif // ULONG_MAX
#ifdef ULLONG_MAX
#undef ULLONG_MAX
#endif // ULLONG_MAX

#ifdef FLOAT_MAX
#undef FLOAT_MAX
#endif // FLOAT_MAX
#ifdef DOUBLE_MAX
#undef DOUBLE_MAX
#endif // DOUBLE_MAX
#ifdef LDOUBLE_MAX
#undef LDOUBLE_MAX
#endif // LDOUBLE_MAX

#ifdef BYTE_MAX
#undef BYTE_MAX
#endif // BYTE_MAX
#ifdef WCHAR_MAX
#undef WCHAR_MAX
#endif // WCHAR_MAX
#ifdef SIZE_MAX
#undef SIZE_MAX
#endif // SIZE_MAX

#ifdef BYTE_MAX
#undef BYTE_MAX
#endif // BYTE_MAX
#ifdef WORD_MAX
#undef WORD_MAX
#endif // WORD_MAX
#ifdef DWORD_MAX
#undef DWORD_MAX
#endif // DWORD_MAX
#ifdef QWORD_MAX
#undef QWORD_MAX
#endif // QWORD_MAX

#define INT8_MAX ((int8) (0xff >> 1)) // 127
#define INT16_MAX ((int16) (0xffff >> 1)) // 32767
#define INT32_MAX ((int32) (0xffffffff >> 1)) // 2147483647
#define INT64_MAX ((int64) (0xffffffffffffffff >> 1)) // 9223372036854775807

#define UINT8_MAX ((uint8) 0xff) // 255
#define UINT16_MAX ((uint16) 0xffff) // 65535
#define UINT32_MAX ((uint32) 0xffffffff) // 4294967295
#define UINT64_MAX ((uint64) 0xffffffffffffffff) // 18446744073709551615

#define FLOAT32_MAX ((float32) 3.40282346638528859811704183484516925E+38)
#define FLOAT64_MAX ((float64) 1.79769313486231570814527423731704357E+308)
#ifndef COMPILER_MSVC
#if defined(X86_PROCESSOR)
#define FLOAT96_MAX ((float96) 1.18973149535723176502126385303097021E+4932L) // Why is it the same as float128? (Tested)
#elif defined(X64_PROCESSOR)
#define FLOAT128_MAX ((float128) 1.18973149535723176502126385303097021E+4932L)
#endif // defined(X86_PROCESSOR)
#endif // !COMPILER_MSVC

#define CHAR_MAX INT8_MAX
#define SHORT_MAX INT16_MAX
#define INT_MAX INT32_MAX
#if defined(WINDOWS_OS) || defined(X86_PROCESSOR)
#define LONG_MAX INT32_MAX
#elif defined(LINUX_OS)
#define LONG_MAX INT64_MAX
#else // Unknown
#define LONG_MAX INT64_MAX
#endif // defined(WINDOWS_OS) || defined(X86_PROCESSOR)
#define LLONG_MAX INT64_MAX

#define UCHAR_MAX UINT8_MAX
#define USHORT_MAX UINT16_MAX
#define UINT_MAX UINT32_MAX
#if defined(WINDOWS_OS) || defined(X86_PROCESSOR)
#define ULONG_MAX UINT32_MAX
#elif defined(LINUX_OS)
#define ULONG_MAX UINT64_MAX
#else // Unknown
#define ULONG_MAX UINT64_MAX
#endif // defined(WINDOWS_OS) || defined(X86_PROCESSOR)
#define ULLONG_MAX UINT64_MAX

#define FLOAT_MAX FLOAT32_MAX
#define DOUBLE_MAX FLOAT64_MAX
#ifdef COMPILER_MSVC
#define LDOUBLE_MAX FLOAT32_MAX
#else // Another compiler
#if defined(X86_PROCESSOR)
#define LDOUBLE_MAX FLOAT96_MAX
#elif defined(X64_PROCESSOR)
#define LDOUBLE_MAX FLOAT128_MAX
#else // Unknown
#define LDOUBLE_MAX FLOAT32_MAX
#endif // defined(X86_PROCESSOR)
#endif // COMPILER_MSVC

#define BYTE_MAX UINT8_MAX
#define WCHAR_MAX UINT16_MAX
#if defined(X86_PROCESSOR)
#define SIZE_MAX UINT32_MAX
#elif defined(X64_PROCESSOR)
#define SIZE_MAX UINT64_MAX
#else // Unknown
#define SIZE_MAX UINT32_MAX
#endif // X64_PROCESSOR

#define BYTE_MAX UINT8_MAX
#define WORD_MAX UINT16_MAX
#define DWORD_MAX UINT32_MAX
#define QWORD_MAX UINT64_MAX

#ifdef POSITIVE_INFINITY
#undef POSITIVE_INFINITY
#endif // POSITIVE_INFINITY
#ifdef NEGATIVE_INFINITY
#undef NEGATIVE_INFINITY
#endif // NEGATIVE_INFINITY
#ifdef INFINITY
#undef INFINITY
#endif // INFINITY
#ifdef NAN
#undef NAN
#endif // NaN

#ifdef COMPILER_MSVC
#define POSITIVE_INFINITY ((double) (1e+300 * 1e+300)) // Positive infinity: inf
#define NEGATIVE_INFINITY (-POSITIVE_INFINITY) // Negative infinity: -inf
#define INFINITY POSITIVE_INFINITY // Infinity: inf
#define NAN ((double) (INFINITY * 0.0)) // Not-a-Number: -nan(ind)
#else // Another compiler
#define POSITIVE_INFINITY (1.0 / 0.0) // Positive infinity: inf
#define NEGATIVE_INFINITY (-1.0 / 0.0) // Negative infinity: -inf
#define INFINITY POSITIVE_INFINITY // Infinity: inf
#define NAN (0.0 / 0.0) // Not-a-Number: nan
#endif // COMPILER_MSVC
