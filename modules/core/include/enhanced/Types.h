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

#include <enhanced/Defines.h>

#if defined(_CHAR_UNSIGNED) || defined(__CHAR_UNSIGNED__)
    #define E_SM_CHAR_IS_UNSIGNED
#endif

#if !defined(E_SM_COMPILER_MSVC) || defined(_NATIVE_WCHAR_T_DEFINED)
    #define E_SM_WCHAR_IS_BUILTIN_TYPE
#endif

#if defined(E_SM_COMPILER_MSVC) || (__SIZEOF_WCHAR_T__ == 2)
    #define E_SM_WCHAR_16BIT
#endif

#if defined(E_SM_ARCH_X86) || defined(E_SM_ARCH_ARM32)
    #define E_SM_SIZE_TYPE_32BIT
#endif

#if defined(E_SM_OS_WINDOWS) || defined(E_SM_ARCH_X86) || defined(E_SM_ARCH_ARM32)
    #define E_SM_LONG_EQUALS_INT
#endif

#ifdef E_SM_COMPATIBILITY_MS
    #define E_SM_LDOUBLE_EQUALS_DOUBLE
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
#ifdef E_SM_LONG_EQUALS_INT
    using int64 = llong;
#else
    using int64 = long;
#endif

    using uint8 = uchar;
    using uint16 = ushort;
    using uint32 = uint;
#ifdef E_SM_LONG_EQUALS_INT
    using uint64 = ullong;
#else
    using uint64 = ulong;
#endif

    using float32 = float;
    using float64 = double;

#ifdef E_SM_WCHAR_IS_BUILTIN_TYPE
    using wchar = wchar_t;
#else
    #ifdef E_SM_WCHAR_16BIT
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
#ifdef E_SM_SIZE_TYPE_32BIT
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

#ifdef E_SM_CHAR_IS_UNSIGNED
    #define E_CHAR_MIN E_UINT8_MIN
#else
    #define E_CHAR_MIN E_INT8_MIN
#endif

#ifdef E_SM_WCHAR_16BIT
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
#ifdef E_SM_LONG_EQUALS_INT
    #define E_LONG_MIN E_INT32_MIN
#else
    #define E_LONG_MIN E_INT64_MIN
#endif
#define E_LLONG_MIN E_INT64_MIN

#define E_UCHAR_MIN E_UINT8_MIN
#define E_USHORT_MIN E_UINT16_MIN
#define E_UINT_MIN E_UINT32_MIN
#ifdef E_SM_LONG_EQUALS_INT
    #define E_ULONG_MIN E_UINT32_MIN
#else
    #define E_ULONG_MIN E_UINT64_MIN
#endif
#define E_ULLONG_MIN E_UINT64_MIN

#define E_FLOAT_MIN E_FLOAT32_MIN
#define E_DOUBLE_MIN E_FLOAT64_MIN
#ifdef E_SM_LDOUBLE_EQUALS_DOUBLE
    #define E_LDOUBLE_MIN E_FLOAT64_MIN
#else
    #define E_LDOUBLE_MIN 3.36210314311209350626267781732175260e-4932l
#endif

#define E_BYTE_MIN E_UINT8_MIN
#define E_WORD_MIN E_UINT16_MIN
#define E_DWORD_MIN E_UINT32_MIN
#define E_QWORD_MIN E_UINT64_MIN

#ifdef E_SM_SIZE_TYPE_32BIT
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

#ifdef E_SM_CHAR_IS_UNSIGNED
    #define E_CHAR_MAX E_UINT8_MAX
#else
    #define E_CHAR_MAX E_INT8_MAX
#endif

#ifdef E_SM_WCHAR_16BIT
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
#ifdef E_SM_LONG_EQUALS_INT
    #define E_LONG_MAX E_INT32_MAX
#else
    #define E_LONG_MAX E_INT64_MAX
#endif
#define E_LLONG_MAX E_INT64_MAX

#define E_UCHAR_MAX E_UINT8_MAX
#define E_USHORT_MAX E_UINT16_MAX
#define E_UINT_MAX E_UINT32_MAX
#ifdef E_SM_LONG_EQUALS_INT
    #define E_ULONG_MAX E_UINT32_MAX
#else
    #define E_ULONG_MAX E_UINT64_MAX
#endif
#define E_ULLONG_MAX E_UINT64_MAX

#define E_FLOAT_MAX E_FLOAT32_MAX
#define E_DOUBLE_MAX E_FLOAT64_MAX
#ifdef E_SM_LDOUBLE_EQUALS_DOUBLE
    #define E_LDOUBLE_MAX E_FLOAT64_MAX
#else
    #define E_LDOUBLE_MAX 1.18973149535723176502126385303097021E+4932l
#endif

#define E_BYTE_MAX E_UINT8_MAX
#define E_WORD_MAX E_UINT16_MAX
#define E_DWORD_MAX E_UINT32_MAX
#define E_QWORD_MAX E_UINT64_MAX

#ifdef E_SM_SIZE_TYPE_32BIT
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
