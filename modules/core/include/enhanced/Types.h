/*
 * Copyright (C) 2023 Liu Baihao. All rights reserved.
 *
 * Licensed under the MIT License with the Distribution Exception.
 * You may not use this file except in compliance with the License.
 *
 * THIS FILE IS PART OF THE ENHANCED SOFTWARE, and IT ALWAYS
 * PROVIDES "AS IS" WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY.
 */

#pragma once

#include <enhanced/Defines.h>

#if defined(_CHAR_UNSIGNED) || defined(__CHAR_UNSIGNED__)
    #define CHAR_IS_UNSIGNED
#endif

#if !defined(E_SM_COMPILER_MSVC) || defined(_NATIVE_WCHAR_T_DEFINED)
    #define WCHAR_IS_BUILTIN_TYPE
#endif

#if defined(E_SM_COMPILER_MSVC) || (__SIZEOF_WCHAR_T__ == 2)
    #define WCHAR_16BIT
#endif

#if defined(E_SM_ARCH_X86) || defined(E_SM_ARCH_ARM32)
    #define SIZE_TYPE_32BIT
#endif

#if defined(E_SM_OS_WINDOWS) || defined(E_SM_ARCH_X86) || defined(E_SM_ARCH_ARM32)
    #define LONG_EQUALS_INT
#endif

#ifdef E_SM_COMPATIBILITY_MS
    #define LDOUBLE_EQUALS_DOUBLE
#endif

namespace enhanced {
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

    // Uses to declare variables, wrap array declarators and function declarators so that they are written before the identifier
    template <typename Type>
    using wrap = Type;
}

#define E_INT8_MIN (-0x80) // -128
#define E_INT16_MIN (-0x8000) // -32768
#define E_INT32_MIN (-0x80000000) // -2147483648
#define E_INT64_MIN (-0x8000000000000000) // -9223372036854775808

#define E_UINT8_MIN 0
#define E_UINT16_MIN 0
#define E_UINT32_MIN 0
#define E_UINT64_MIN 0

#define E_FLOAT32_MIN 1.17549435082228750796873653722224568e-38f
#define E_FLOAT64_MIN 2.22507385850720138309023271733240406e-308

#ifdef CHAR_IS_UNSIGNED
    #define E_CHAR_MIN E_UINT8_MIN
#else
    #define E_CHAR_MIN E_INT8_MIN
#endif

#ifdef WCHAR_16BIT
    #define E_WCHAR_MIN E_UINT16_MIN
#else
    #define E_WCHAR_MIN E_INT32_MIN
#endif

#define E_U8CHAR_MIN E_UINT8_MIN
#define E_U16CHAR_MIN E_UINT16_MIN
#define E_U32CHAR_MIN E_UINT32_MIN

#define E_SCHAR_MIN E_INT8_MIN
#define E_SHORT_MIN E_INT16_MIN
#define E_INT_MIN E_INT32_MIN
#ifdef LONG_EQUALS_INT
    #define E_LONG_MIN E_INT32_MIN
#else
    #define E_LONG_MIN E_INT64_MIN
#endif
#define E_LLONG_MIN E_INT64_MIN

#define E_UCHAR_MIN E_UINT8_MIN
#define E_USHORT_MIN E_UINT16_MIN
#define E_UINT_MIN E_UINT32_MIN
#ifdef LONG_EQUALS_INT
    #define E_ULONG_MIN E_UINT32_MIN
#else
    #define E_ULONG_MIN E_UINT64_MIN
#endif
#define E_ULLONG_MIN E_UINT64_MIN

#define E_FLOAT_MIN E_FLOAT32_MIN
#define E_DOUBLE_MIN E_FLOAT64_MIN
#ifdef LDOUBLE_EQUALS_DOUBLE
    #define E_LDOUBLE_MIN E_FLOAT64_MIN
#else
    #define E_LDOUBLE_MIN 3.36210314311209350626267781732175260e-4932l
#endif

#define E_BYTE_MIN E_UINT8_MIN
#define E_WORD_MIN E_UINT16_MIN
#define E_DWORD_MIN E_UINT32_MIN
#define E_QWORD_MIN E_UINT64_MIN

#ifdef SIZE_TYPE_32BIT
    #define E_SIZE_TYPE_MIN E_UINT32_MIN
#else
    #define E_SIZE_TYPE_MIN E_UINT64_MIN
#endif

#define E_INT8_MAX 0x7F // 127
#define E_INT16_MAX 0x7FFF // 32767
#define E_INT32_MAX 0x7FFFFFFF // 2147483647
#define E_INT64_MAX 0x7FFFFFFFFFFFFFFF // 9223372036854775807

#define E_UINT8_MAX 0xFFu // 255
#define E_UINT16_MAX 0xFFFFu // 65535
#define E_UINT32_MAX 0xFFFFFFFFu // 4294967295
#define E_UINT64_MAX 0xFFFFFFFFFFFFFFFFu // 18446744073709551615

#define E_FLOAT32_MAX 3.40282346638528859811704183484516925e+38f
#define E_FLOAT64_MAX 1.79769313486231570814527423731704357e+308

#ifdef CHAR_IS_UNSIGNED
    #define E_CHAR_MAX E_UINT8_MAX
#else
    #define E_CHAR_MAX E_INT8_MAX
#endif

#ifdef WCHAR_16BIT
    #define E_WCHAR_MAX E_UINT16_MAX
#else
    #define E_WCHAR_MAX E_INT32_MAX
#endif

#define E_U8CHAR_MAX E_UINT8_MAX
#define E_U16CHAR_MAX E_UINT16_MAX
#define E_U32CHAR_MAX E_UINT32_MAX

#define E_SCHAR_MAX E_INT8_MAX
#define E_SHORT_MAX E_INT16_MAX
#define E_INT_MAX E_INT32_MAX
#ifdef LONG_EQUALS_INT
    #define E_LONG_MAX E_INT32_MAX
#else
    #define E_LONG_MAX E_INT64_MAX
#endif
#define E_LLONG_MAX E_INT64_MAX

#define E_UCHAR_MAX E_UINT8_MAX
#define E_USHORT_MAX E_UINT16_MAX
#define E_UINT_MAX E_UINT32_MAX
#ifdef LONG_EQUALS_INT
    #define E_ULONG_MAX E_UINT32_MAX
#else
    #define E_ULONG_MAX E_UINT64_MAX
#endif
#define E_ULLONG_MAX E_UINT64_MAX

#define E_FLOAT_MAX E_FLOAT32_MAX
#define E_DOUBLE_MAX E_FLOAT64_MAX
#ifdef LDOUBLE_EQUALS_DOUBLE
    #define E_LDOUBLE_MAX E_FLOAT64_MAX
#else
    #define E_LDOUBLE_MAX 1.18973149535723176502126385303097021E+4932l
#endif

#define E_BYTE_MAX E_UINT8_MAX
#define E_WORD_MAX E_UINT16_MAX
#define E_DWORD_MAX E_UINT32_MAX
#define E_QWORD_MAX E_UINT64_MAX

#ifdef SIZE_TYPE_32BIT
    #define E_SIZE_TYPE_MAX E_UINT32_MAX
#else
    #define E_SIZE_TYPE_MAX E_UINT64_MAX
#endif

#ifdef E_SM_COMPILER_MSVC
    #define E_POSITIVE_INFINITY ((double) (1e+300 * 1e+300))
    #define E_NEGATIVE_INFINITY (-E_POSITIVE_INFINITY)
    #define E_INFINITY E_POSITIVE_INFINITY
    #define E_NAN ((double) (E_INFINITY * 0.0))
#else
    #define E_POSITIVE_INFINITY (1.0 / 0.0)
    #define E_NEGATIVE_INFINITY (-1.0 / 0.0)
    #define E_INFINITY E_POSITIVE_INFINITY
    #define E_NAN (0.0 / 0.0)
#endif

#ifdef E_SM_MACRO_NO_PREFIX_ALIAS
    // Prevents duplicate macro definition warnings (MSVC C4005)
    #ifdef E_SM_COMPILER_MSVC
        #include <limits.h>
        #include <stdint.h>
        #include <corecrt_math.h>
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

    #define INT8_MIN E_INT8_MIN
    #define INT16_MIN E_INT16_MIN
    #define INT32_MIN E_INT32_MIN
    #define INT64_MIN E_INT64_MIN
    #define UINT8_MIN E_UINT8_MIN
    #define UINT16_MIN E_UINT16_MIN
    #define UINT32_MIN E_UINT32_MIN
    #define UINT64_MIN E_UINT64_MIN
    #define FLOAT32_MIN E_FLOAT32_MIN
    #define FLOAT64_MIN E_FLOAT64_MIN
    #define CHAR_MIN E_CHAR_MIN
    #define WCHAR_MIN E_WCHAR_MIN
    #define U8CHAR_MIN E_U8CHAR_MIN
    #define U16CHAR_MIN E_U16CHAR_MIN
    #define U32CHAR_MIN E_U32CHAR_MIN
    #define SCHAR_MIN E_SCHAR_MIN
    #define SHORT_MIN E_SHORT_MIN
    #define INT_MIN E_INT_MIN
    #define LONG_MIN E_LONG_MIN
    #define LLONG_MIN E_LLONG_MIN
    #define UCHAR_MIN E_UCHAR_MIN
    #define USHORT_MIN E_USHORT_MIN
    #define UINT_MIN E_UINT_MIN
    #define ULONG_MIN E_ULONG_MIN
    #define ULLONG_MIN E_ULLONG_MIN
    #define FLOAT_MIN E_FLOAT_MIN
    #define DOUBLE_MIN E_DOUBLE_MIN
    #define LDOUBLE_MIN E_LDOUBLE_MIN
    #define BYTE_MIN E_BYTE_MIN
    #define WORD_MIN E_WORD_MIN
    #define DWORD_MIN E_DWORD_MIN
    #define QWORD_MIN E_QWORD_MIN
    #define SIZE_TYPE_MIN E_SIZE_TYPE_MIN

    #define INT8_MAX E_INT8_MAX
    #define INT16_MAX E_INT16_MAX
    #define INT32_MAX E_INT32_MAX
    #define INT64_MAX E_INT64_MAX
    #define UINT8_MAX E_UINT8_MAX
    #define UINT16_MAX E_UINT16_MAX
    #define UINT32_MAX E_UINT32_MAX
    #define UINT64_MAX E_UINT64_MAX
    #define FLOAT32_MAX E_FLOAT32_MAX
    #define FLOAT64_MAX E_FLOAT64_MAX
    #define CHAR_MAX E_CHAR_MAX
    #define WCHAR_MAX E_WCHAR_MAX
    #define U8CHAR_MAX E_U8CHAR_MAX
    #define U16CHAR_MAX E_U16CHAR_MAX
    #define U32CHAR_MAX E_U32CHAR_MAX
    #define SCHAR_MAX E_SCHAR_MAX
    #define SHORT_MAX E_SHORT_MAX
    #define INT_MAX E_INT_MAX
    #define LONG_MAX E_LONG_MAX
    #define LLONG_MAX E_LLONG_MAX
    #define UCHAR_MAX E_UCHAR_MAX
    #define USHORT_MAX E_USHORT_MAX
    #define UINT_MAX E_UINT_MAX
    #define ULONG_MAX E_ULONG_MAX
    #define ULLONG_MAX E_ULLONG_MAX
    #define FLOAT_MAX E_FLOAT_MAX
    #define DOUBLE_MAX E_DOUBLE_MAX
    #define LDOUBLE_MAX E_LDOUBLE_MAX
    #define BYTE_MAX E_BYTE_MA
    #define WORD_MAX E_WORD_MAX
    #define DWORD_MAX E_DWORD_MAX
    #define QWORD_MAX E_QWORD_MAX
    #define SIZE_TYPE_MAX E_SIZE_TYPE_MAX

    #define POSITIVE_INFINITY E_POSITIVE_INFINITY
    #define NEGATIVE_INFINITY E_NEGATIVE_INFINITY
    #define INFINITY E_INFINITY
    #define NAN E_NAN
#endif
