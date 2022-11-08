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

#include <enhanced/core/defines.h>
#include <enhanced/core/export.h>
#include <enhanced/core/types.h>
#include <enhanced/core/annotations.h>

/*!
 * Creates a new string.
 *
 * @param length  The count of the new string.
 */
RetRequiresRelease RetNullable MustInspectResult
ENHANCED_CORE_API char* stringNew(sizetype length);

/*!
 * Copies a string to a new string.
 *
 * @param source  The source string.
 * @return char*  The new string.
 */
RetRequiresRelease RetNullable MustInspectResult
ENHANCED_CORE_API char* stringCopy(const char* source);

/*!
 * Copies a string to a new string.
 *
 * @param source  The source string.
 * @param length  The length of the string
 * @return char*  The new string.
 */
RetRequiresRelease RetNullable MustInspectResult
ENHANCED_CORE_API char* stringCopyExt(const char* source, sizetype length);

/*!
 * Copies a string to a new string with a new length.
 *
 * @param string   A string.
 * @param oldSize  The size of the old string.
 * @param newSize  The count of the new string.
 * @return char*   The new string.
 */
RetRequiresRelease RetNullable MustInspectResult
ENHANCED_CORE_API char* stringCopyResize(const char* string, sizetype oldSize, sizetype newSize);

/*!
 * Gets the count of a string.
 *
 * @param string  A string.
 * @return sizetype   The count of the string.
 */
NoIgnoreRet
ENHANCED_CORE_API sizetype stringLength(const char* string);

/*!
 * Verifies two strings are the same.
 *
 * @param string1  A string.
 * @param string2  Another string.
 * @return bool    Whether the string "string1" is equal to the string "string2".
 */
NoIgnoreRet
ENHANCED_CORE_API bool stringEqual(const char* string1, const char* string2);

/*!
 * Creates a new wide string.
 *
 * @param length  The count of the new wide string.
 */
RetRequiresRelease RetNullable MustInspectResult
ENHANCED_CORE_API wchar* wstringNew(sizetype length);

/*!
 * Copies a wide string to a new wide string of the same count.
 *
 * @param source  The source wide string.
 * @return char*  The new wide string.
 */
RetRequiresRelease RetNullable MustInspectResult
ENHANCED_CORE_API wchar* wstringCopy(const wchar* source);

/*!
 * Copies a wide string to a new string.
 *
 * @param source  The source wide string.
 * @param length  The length of the wide string.
 * @return char*  The new string.
 */
RetRequiresRelease RetNullable MustInspectResult
ENHANCED_CORE_API wchar* wstringCopyExt(const wchar* source, sizetype length);

/*!
 * Resets the size of a wide string.
 *
 * @param wstring  A wide string.
 * @param oldSize  The size of the old wide string.
 * @param newSize  The count of the new wide string.
 * @return char*   The new wide string.
 */
RetRequiresRelease RetNullable MustInspectResult
ENHANCED_CORE_API wchar* wstringCopyResize(const wchar* wstring, sizetype oldSize, sizetype newSize);

/*!
 * Gets the count of a wide string.
 *
 * @param wstring  A wide string.
 * @return sizetype    The count of the wide string.
 */
NoIgnoreRet
ENHANCED_CORE_API sizetype wstringLength(const wchar* wstring);

/*!
 * Verifies two wide strings are the same.
 *
 * @param wstring1  A wide string.
 * @param wstring2  Another wide string.
 * @return bool     Whether the wide string 'wstring1' is equal to the wide string 'wstring2'.
 */
NoIgnoreRet
ENHANCED_CORE_API bool wstringEqual(const wchar* wstring1, const wchar* wstring2);

#ifdef CXX_LANGUAGE

NAMESPACE_L2_BEGIN(enhanced, core)

using ::stringNew;
using ::stringCopy;
using ::stringCopyExt;
using ::stringCopyResize;
using ::stringLength;
using ::stringEqual;

using ::wstringNew;
using ::wstringCopy;
using ::wstringCopyExt;
using ::wstringCopyResize;
using ::wstringLength;
using ::wstringEqual;

template <typename CharType>
ENHANCED_CORE_API CharType* tstringNew(sizetype length);

template <typename CharType>
ENHANCED_CORE_API CharType* tstringCopy(const CharType* source);

template <typename CharType>
ENHANCED_CORE_API CharType* tstringCopyExt(const CharType* source, sizetype length);

template <typename CharType>
ENHANCED_CORE_API CharType* tstringCopyResize(const CharType* source, sizetype oldSize, sizetype newSize);

template <typename CharType>
ENHANCED_CORE_API sizetype tstringLength(const CharType* string) noexcept;

template <typename CharType>
ENHANCED_CORE_API bool tstringEqual(const CharType* string1, const CharType* string2) noexcept;

NAMESPACE_L2_END

#endif
