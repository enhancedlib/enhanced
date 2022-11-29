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

#include <enhanced/Defines.h>

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

using llong = long long;
using ldouble = long double;

using schar = signed char;

using uchar = unsigned char;
using ushort = unsigned short;
using uint = unsigned int;
using ulong = unsigned long;
using ullong = unsigned long long;

using int8 = schar;
using int16 = short;
using int32 = int;
#if defined(WINDOWS_OS) || defined(X86_ARCH) || defined(ARM32_ARCH)
using int64 = llong;
#else
using int64 = long;
#endif

using uint8 = uchar;
using uint16 = ushort;
using uint32 = uint;
#if defined(WINDOWS_OS) || defined(X86_ARCH) || defined(ARM32_ARCH)
using uint64 = ullong;
#else
using uint64 = ulong;
#endif

using float32 = float;
using float64 = double;

// The name "sizetype" is used instead of "size" because "size" is often used as a variable/function name.
#if defined(X86_ARCH) || defined(ARM32_ARCH)
using sizetype = uint32;
#else
using sizetype = uint64;
#endif

using byte = uint8;
using word = uint16;
using dword = uint32;
using qword = uint64;

using u8char = char8_t;
using u16char = char16_t;
using u32char = char32_t;

#ifdef WCHAR_IS_BUILTIN_TYPE
using wchar = wchar_t;
#else
#ifdef WCHAR_EQUALS_UINT16
using wchar = uint16;
#else
using wchar = int32;
#endif
#endif

#undef null
#define null nullptr
using nulltype = decltype(null);

#undef INT8_MIN
#undef INT16_MIN
#undef INT32_MIN
#undef INT64_MIN

#undef UINT8_MIN
#undef UINT16_MIN
#undef UINT32_MIN
#undef UINT64_MIN

#undef FLOAT32_MIN
#undef FLOAT64_MIN

#undef CHAR_MIN
#undef WCHAR_MIN
#undef U8CHAR_MIN
#undef U16CHAR_MIN
#undef U32CHAR_MIN

#undef SCHAR_MIN
#undef SHORT_MIN
#undef INT_MIN
#undef LONG_MIN
#undef LLONG_MIN

#undef UCHAR_MIN
#undef USHORT_MIN
#undef UINT_MIN
#undef ULONG_MIN
#undef ULLONG_MIN

#undef FLOAT_MIN
#undef DOUBLE_MIN
#undef LDOUBLE_MIN

#undef INT8_MAX
#undef INT16_MAX
#undef INT32_MAX
#undef INT64_MAX

#undef UINT8_MAX
#undef UINT16_MAX
#undef UINT32_MAX
#undef UINT64_MAX

#undef FLOAT32_MAX
#undef FLOAT64_MAX

#undef CHAR_MAX
#undef WCHAR_MAX
#undef U8CHAR_MAX
#undef U16CHAR_MAX
#undef U32CHAR_MAX

#undef SCHAR_MAX
#undef INT_MAX
#undef SHORT_MAX
#undef LONG_MAX
#undef LLONG_MAX

#undef UCHAR_MAX
#undef USHORT_MAX
#undef UINT_MAX
#undef ULONG_MAX
#undef ULLONG_MAX

#undef FLOAT_MAX
#undef DOUBLE_MAX
#undef LDOUBLE_MAX

#undef INFINITY
#undef NAN

#undef INVALID_SIZE

#define INT8_MIN ((int8) -0x80) // -128
#define INT16_MIN ((int16) -0x8000) // -32768
#define INT32_MIN ((int32) -0x80000000) // -2147483648
#define INT64_MIN ((int64) -0x8000000000000000) // -9223372036854775808

#define UINT8_MIN ((uint8) 0x0)
#define UINT16_MIN ((uint16) 0x0)
#define UINT32_MIN ((uint32) 0x0)
#define UINT64_MIN ((uint64) 0x0)

#define FLOAT32_MIN 1.17549435082228750796873653722224568e-38f
#define FLOAT64_MIN 2.22507385850720138309023271733240406e-308

#ifdef CHAR_IS_UNSIGNED
#define CHAR_MIN UINT8_MIN
#else
#define CHAR_MIN INT8_MIN
#endif

#ifdef WCHAR_EQUALS_UINT16
#define WCHAR_MIN UINT16_MIN
#else
#define WCHAR_MIN INT32_MIN
#endif

#define U8CHAR_MIN UINT8_MIN
#define U16CHAR_MIN UINT16_MIN
#define U32CHAR_MIN UINT32_MIN

#define SCHAR_MIN INT8_MIN
#define SHORT_MIN INT16_MIN
#define INT_MIN INT32_MIN
#if defined(WINDOWS_OS) || defined(X86_ARCH) || defined(ARM32_ARCH)
#define LONG_MIN INT32_MIN
#else
#define LONG_MIN INT64_MIN
#endif
#define LLONG_MIN INT64_MIN

#define UCHAR_MIN UINT8_MIN;
#define USHORT_MIN UINT16_MIN;
#define UINT_MIN UINT32_MIN;
#if defined(WINDOWS_OS) || defined(X86_ARCH) || defined(ARM32_ARCH)
#define ULONG_MIN UINT32_MIN
#else
#define ULONG_MIN UINT64_MIN
#endif
#define ULLONG_MIN UINT64_MIN

#define FLOAT_MIN FLOAT32_MIN
#define DOUBLE_MIN FLOAT64_MIN
#ifdef MSVC_ABI
#define LDOUBLE_MIN FLOAT64_MIN
#else
#define LDOUBLE_MIN 3.36210314311209350626267781732175260e-4932l
#endif

#if defined(X86_ARCH) || defined(ARM32_ARCH)
#define SIZE_TYPE_MIN UINT64_MIN
#else
#define SIZE_TYPE_MIN UINT32_MIN
#endif

#define BYTE_MIN UINT8_MIN
#define WORD_MIN UINT16_MIN
#define DWORD_MIN UINT32_MIN
#define QWORD_MIN UINT64_MIN

#define INT8_MAX ((int8) 0x7F) // 127
#define INT16_MAX ((int16) 0x7FFF) // 32767
#define INT32_MAX ((int32) 0x7FFFFFFF) // 2147483647
#define INT64_MAX ((int64) 0x7FFFFFFFFFFFFFFF) // 9223372036854775807

#define UINT8_MAX ((uint8) 0xFFu) // 255
#define UINT16_MAX ((uint16) 0xFFFFu) // 65535
#define UINT32_MAX ((uint32) 0xFFFFFFFFu) // 4294967295
#define UINT64_MAX ((uint64) 0xFFFFFFFFFFFFFFFFu) // 18446744073709551615

#define FLOAT32_MAX 3.40282346638528859811704183484516925e+38f
#define FLOAT64_MAX 1.79769313486231570814527423731704357e+308

#ifdef CHAR_IS_UNSIGNED
#define CHAR_MAX UINT8_MAX
#else
#define CHAR_MAX INT8_MAX
#endif

#ifdef WCHAR_EQUALS_UINT16
#define WCHAR_MAX UINT16_MAX
#else
#define WCHAR_MAX INT32_MAX
#endif

#define U8CHAR_MAX UINT8_MAX
#define U16CHAR_MAX UINT16_MAX
#define U32CHAR_MAX UINT32_MAX

#define SCHAR_MAX INT8_MAX
#define SHORT_MAX INT16_MAX
#define INT_MAX INT32_MAX
#if defined(WINDOWS_OS) || defined(X86_ARCH) || defined(ARM32_ARCH)
#define LONG_MAX INT32_MAX
#else
#define LONG_MAX INT64_MAX
#endif
#define LLONG_MAX INT64_MAX

#define UCHAR_MAX UINT8_MAX
#define USHORT_MAX UINT16_MAX
#define UINT_MAX UINT32_MAX
#if defined(WINDOWS_OS) || defined(X86_ARCH) || defined(ARM32_ARCH)
#define ULONG_MAX UINT32_MAX
#else
#define ULONG_MAX UINT64_MAX
#endif
#define ULLONG_MAX UINT64_MAX

#define FLOAT_MAX FLOAT32_MAX
#define DOUBLE_MAX FLOAT64_MAX
#ifdef MSVC_ABI
#define LDOUBLE_MAX FLOAT64_MAX
#else
#define LDOUBLE_MAX 1.18973149535723176502126385303097021E+4932l
#endif

#if defined(X86_ARCH) || defined(ARM32_ARCH)
#define SIZE_TYPE_MAX UINT32_MAX
#else
#define SIZE_TYPE_MAX UINT64_MAX
#endif

#define BYTE_MAX UINT8_MAX
#define WORD_MAX UINT16_MAX
#define DWORD_MAX UINT32_MAX
#define QWORD_MAX UINT64_MAX

#ifdef MSVC_COMPILER
#define POSITIVE_INFINITY ((double) (1e+300 * 1e+300))
#define NEGATIVE_INFINITY (-POSITIVE_INFINITY)
#define INFINITY POSITIVE_INFINITY
#define NAN ((double) (INFINITY * 0.0))
#else
#define POSITIVE_INFINITY (1.0 / 0.0)
#define NEGATIVE_INFINITY (-1.0 / 0.0)
#define INFINITY POSITIVE_INFINITY
#define NAN (0.0 / 0.0)
#endif

#define INVALID_SIZE SIZE_TYPE_MAX
