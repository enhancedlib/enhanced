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

#include <enhanced/Defines.h>

#if defined(_CHAR_UNSIGNED) || defined(__CHAR_UNSIGNED__)
    #define CHAR_IS_UNSIGNED
#endif

#if !defined(MSVC_COMPILER) || defined(_NATIVE_WCHAR_T_DEFINED)
    #define WCHAR_IS_BUILTIN_TYPE
#endif

#if defined(MSVC_COMPILER) || (__SIZEOF_WCHAR_T__ == 2)
    #define WCHAR_16BIT
#endif

#if defined(X86_ARCH) || defined(ARM32_ARCH)
    #define SIZE_TYPE_32BIT
#endif

#if defined(WINDOWS_OS) || defined(X86_ARCH) || defined(ARM32_ARCH)
    #define LONG_EQUALS_INT
#endif

#ifdef MSVC_ABI
    #define LDOUBLE_EQUALS_DOUBLE
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
#ifdef LONG_EQUALS_INT
using int64 = llong;
#else
using int64 = long;
#endif

using uint8 = uchar;
using uint16 = ushort;
using uint32 = uint;
#ifdef LONG_EQUALS_INT
using uint64 = ullong;
#else
using uint64 = ulong;
#endif

using float32 = float;
using float64 = double;

#ifdef WCHAR_IS_BUILTIN_TYPE
using wchar = wchar_t;
#else
#ifdef WCHAR_16BIT
using wchar = uint16;
#else
using wchar = int32;
#endif
#endif

using u8char = char8_t;
using u16char = char16_t;
using u32char = char32_t;

using byte = uint8;
using word = uint16;
using dword = uint32;
using qword = uint64;

// The name "sizetype" is used instead of "size" because "size" is often used as a variable/function name.
#ifdef SIZE_TYPE_32BIT
using sizetype = uint32;
#else
using sizetype = uint64;
#endif

using nulltype = decltype(nullptr);

namespace enhanced {
    using ::llong;
    using ::ldouble;
    using ::schar;
    using ::uchar;
    using ::ushort;
    using ::uint;
    using ::ulong;
    using ::ullong;
    using ::int8;
    using ::int16;
    using ::int32;
    using ::int64;
    using ::uint8;
    using ::uint16;
    using ::uint32;
    using ::uint64;
    using ::float32;
    using ::float64;
    using ::wchar;
    using ::u8char;
    using ::u16char;
    using ::u32char;
    using ::byte;
    using ::word;
    using ::dword;
    using ::qword;
    using ::sizetype;
}

#if defined(ENHANCED_SUPPRESS_OVERWRITE) || defined(ENHANCED_CORE_SUPPRESS_OVERWRITE_LIMITS)
    #pragma push_macro("INT8_MIN")
    #pragma push_macro("INT16_MIN")
    #pragma push_macro("INT32_MIN")
    #pragma push_macro("INT64_MIN")
    #pragma push_macro("CHAR_MIN")
    #pragma push_macro("WCHAR_MIN")
    #pragma push_macro("SCHAR_MIN")
    #pragma push_macro("INT_MIN")
    #pragma push_macro("LONG_MIN")
    #pragma push_macro("LLONG_MIN")
    #pragma push_macro("INT8_MAX")
    #pragma push_macro("INT16_MAX")
    #pragma push_macro("INT32_MAX")
    #pragma push_macro("INT64_MAX")
    #pragma push_macro("UINT8_MAX")
    #pragma push_macro("UINT16_MAX")
    #pragma push_macro("UINT32_MAX")
    #pragma push_macro("UINT64_MAX")
    #pragma push_macro("CHAR_MAX")
    #pragma push_macro("WCHAR_MAX")
    #pragma push_macro("SCHAR_MAX")
    #pragma push_macro("INT_MAX")
    #pragma push_macro("LONG_MAX")
    #pragma push_macro("LLONG_MAX")
    #pragma push_macro("UCHAR_MAX")
    #pragma push_macro("UINT_MAX")
    #pragma push_macro("ULONG_MAX")
    #pragma push_macro("ULLONG_MAX")
    #pragma push_macro("INFINITY")
    #pragma push_macro("NAN")
#endif

#undef INT8_MIN
#undef INT16_MIN
#undef INT32_MIN
#undef INT64_MIN
#undef CHAR_MIN
#undef WCHAR_MIN
#undef SCHAR_MIN
#undef INT_MIN
#undef LONG_MIN
#undef LLONG_MIN
#undef INT8_MAX
#undef INT16_MAX
#undef INT32_MAX
#undef INT64_MAX
#undef UINT8_MAX
#undef UINT16_MAX
#undef UINT32_MAX
#undef UINT64_MAX
#undef CHAR_MAX
#undef WCHAR_MAX
#undef SCHAR_MAX
#undef INT_MAX
#undef LONG_MAX
#undef LLONG_MAX
#undef UCHAR_MAX
#undef UINT_MAX
#undef ULONG_MAX
#undef ULLONG_MAX
#undef INFINITY
#undef NAN

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

#ifdef WCHAR_16BIT
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
#ifdef LONG_EQUALS_INT
    #define LONG_MIN INT32_MIN
#else
    #define LONG_MIN INT64_MIN
#endif
#define LLONG_MIN INT64_MIN

#define UCHAR_MIN UINT8_MIN
#define USHORT_MIN UINT16_MIN
#define UINT_MIN UINT32_MIN
#ifdef LONG_EQUALS_INT
    #define ULONG_MIN UINT32_MIN
#else
    #define ULONG_MIN UINT64_MIN
#endif
#define ULLONG_MIN UINT64_MIN

#define FLOAT_MIN FLOAT32_MIN
#define DOUBLE_MIN FLOAT64_MIN
#ifdef LDOUBLE_EQUALS_DOUBLE
    #define LDOUBLE_MIN FLOAT64_MIN
#else
    #define LDOUBLE_MIN 3.36210314311209350626267781732175260e-4932l
#endif

#define BYTE_MIN UINT8_MIN
#define WORD_MIN UINT16_MIN
#define DWORD_MIN UINT32_MIN
#define QWORD_MIN UINT64_MIN

#ifdef SIZE_TYPE_32BIT
    #define SIZE_TYPE_MIN UINT32_MIN
#else
    #define SIZE_TYPE_MIN UINT64_MIN
#endif

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

#ifdef WCHAR_16BIT
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
#ifdef LONG_EQUALS_INT
    #define LONG_MAX INT32_MAX
#else
    #define LONG_MAX INT64_MAX
#endif
#define LLONG_MAX INT64_MAX

#define UCHAR_MAX UINT8_MAX
#define USHORT_MAX UINT16_MAX
#define UINT_MAX UINT32_MAX
#ifdef LONG_EQUALS_INT
    #define ULONG_MAX UINT32_MAX
#else
    #define ULONG_MAX UINT64_MAX
#endif
#define ULLONG_MAX UINT64_MAX

#define FLOAT_MAX FLOAT32_MAX
#define DOUBLE_MAX FLOAT64_MAX
#ifdef LDOUBLE_EQUALS_DOUBLE
    #define LDOUBLE_MAX FLOAT64_MAX
#else
    #define LDOUBLE_MAX 1.18973149535723176502126385303097021E+4932l
#endif

#define BYTE_MAX UINT8_MAX
#define WORD_MAX UINT16_MAX
#define DWORD_MAX UINT32_MAX
#define QWORD_MAX UINT64_MAX

#ifdef SIZE_TYPE_32BIT
    #define SIZE_TYPE_MAX UINT32_MAX
#else
    #define SIZE_TYPE_MAX UINT64_MAX
#endif

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

#if defined(ENHANCED_SUPPRESS_OVERWRITE) || defined(ENHANCED_CORE_SUPPRESS_OVERWRITE_LIMITS)
    #pragma pop_macro("INT8_MIN")
    #pragma pop_macro("INT16_MIN")
    #pragma pop_macro("INT32_MIN")
    #pragma pop_macro("INT64_MIN")
    #pragma pop_macro("CHAR_MIN")
    #pragma pop_macro("WCHAR_MIN")
    #pragma pop_macro("SCHAR_MIN")
    #pragma pop_macro("INT_MIN")
    #pragma pop_macro("LONG_MIN")
    #pragma pop_macro("LLONG_MIN")
    #pragma pop_macro("INT8_MAX")
    #pragma pop_macro("INT16_MAX")
    #pragma pop_macro("INT32_MAX")
    #pragma pop_macro("INT64_MAX")
    #pragma pop_macro("UINT8_MAX")
    #pragma pop_macro("UINT16_MAX")
    #pragma pop_macro("UINT32_MAX")
    #pragma pop_macro("UINT64_MAX")
    #pragma pop_macro("CHAR_MAX")
    #pragma pop_macro("WCHAR_MAX")
    #pragma pop_macro("SCHAR_MAX")
    #pragma pop_macro("INT_MAX")
    #pragma pop_macro("LONG_MAX")
    #pragma pop_macro("LLONG_MAX")
    #pragma pop_macro("UCHAR_MAX")
    #pragma pop_macro("UINT_MAX")
    #pragma pop_macro("ULONG_MAX")
    #pragma pop_macro("ULLONG_MAX")
    #pragma pop_macro("INFINITY")
    #pragma pop_macro("NAN")
#endif
