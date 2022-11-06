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
ENHANCED_CORE_API char* stringNew(Size length);

/*!
 * Copies a string to a new string.
 *
 * @param source  The source string.
 * @return char*  The new string.
 */
RetRequiresRelease RetNullable MustInspectResult
ENHANCED_CORE_API char* stringCopy(NotNull const char* source);

/*!
 * Copies a string to a new string.
 *
 * @param source  The source string.
 * @param length  The length of the string
 * @return char*  The new string.
 */
RetRequiresRelease RetNullable MustInspectResult
ENHANCED_CORE_API char* stringCopyExt(NotNull const char* source, Size length);

/*!
 * Copies a string to a new string with a new length.
 *
 * @param string   A string.
 * @param oldSize  The size of the old string.
 * @param newSize  The count of the new string.
 * @return char*   The new string.
 */
RetRequiresRelease RetNullable MustInspectResult
ENHANCED_CORE_API char* stringCopyResize(NotNull const char* string, Size oldSize, Size newSize);

/*!
 * Gets the count of a string.
 *
 * @param string  A string.
 * @return Size   The count of the string.
 */
RetCannotIgnored
ENHANCED_CORE_API Size stringLength(NotNull const char* string);

/*!
 * Verifies two strings are the same.
 *
 * @param string1  A string.
 * @param string2  Another string.
 * @return bool    Whether the string "string1" is equal to the string "string2".
 */
RetCannotIgnored
ENHANCED_CORE_API bool stringEqual(const char* string1, const char* string2);

/*!
 * Verifies two strings are the same.
 *
 * @param string1  A string.
 * @param length1  The length of 'string1'.
 * @param string2  Another string.
 * @param length2  The length of 'string2'.
 * @return bool    Whether the string "string1" is equal to the string "string2".
 */
RetCannotIgnored
ENHANCED_CORE_API bool stringEqualExt(const char* string1, Size length1, const char* string2, Size length2);

/*!
 * Creates a new wide string.
 *
 * @param length  The count of the new wide string.
 */
RetRequiresRelease RetNullable MustInspectResult
ENHANCED_CORE_API wchar* wstringNew(Size length);

/*!
 * Copies a wide string to a new wide string of the same count.
 *
 * @param source  The source wide string.
 * @return char*  The new wide string.
 */
RetRequiresRelease RetNullable MustInspectResult
ENHANCED_CORE_API wchar* wstringCopy(NotNull const wchar* source);

/*!
 * Copies a wide string to a new string.
 *
 * @param source  The source wide string.
 * @param length  The length of the wide string.
 * @return char*  The new string.
 */
RetRequiresRelease RetNullable MustInspectResult
ENHANCED_CORE_API wchar* wstringCopyExt(NotNull const wchar* source, Size length);

/*!
 * Resets the size of a wide string.
 *
 * @param wstring  A wide string.
 * @param oldSize  The size of the old wide string.
 * @param newSize  The count of the new wide string.
 * @return char*   The new wide string.
 */
RetRequiresRelease RetNullable MustInspectResult
ENHANCED_CORE_API wchar* wstringCopyResize(NotNull const wchar* wstring, Size oldSize, Size newSize);

/*!
 * Gets the count of a wide string.
 *
 * @param wstring  A wide string.
 * @return Size    The count of the wide string.
 */
RetCannotIgnored
ENHANCED_CORE_API Size wstringLength(NotNull const wchar* wstring);

/*!
 * Verifies two wide strings are the same.
 *
 * @param wstring1  A wide string.
 * @param wstring2  Another wide string.
 * @return bool     Whether the wide string 'wstring1' is equal to the wide string 'wstring2'.
 */
RetCannotIgnored
ENHANCED_CORE_API bool wstringEqual(const wchar* wstring1, const wchar* wstring2);

/*!
 * Verifies two wide strings are the same.
 *
 * Extension for 'wstringEqual' function
 *
 * @param wstring1  A wide string.
 * @param length1   The length of 'wstring1'.
 * @param wstring2  Another wide string.
 * @param length2   The length of 'wstring2'.
 * @return bool     Whether the string 'string1' is equal to the string 'string2'.
 */
RetCannotIgnored
ENHANCED_CORE_API bool wstringEqualExt(const wchar* wstring1, Size length1, const wchar* wstring2, Size length2);

#ifdef CXX_LANGUAGE

namespace enhanced::core {
    using ::stringNew;
    using ::stringCopy;
    using ::stringCopyExt;
    using ::stringCopyResize;
    using ::stringLength;
    using ::stringEqual;
    using ::stringEqualExt;

    using ::wstringNew;
    using ::wstringCopy;
    using ::wstringCopyExt;
    using ::wstringCopyResize;
    using ::wstringLength;
    using ::wstringEqual;
    using ::wstringEqualExt;

    template <typename CharType>
    ENHANCED_CORE_API CharType* tstringNew(Size length);

    template <typename CharType>
    ENHANCED_CORE_API CharType* tstringCopy(NotNull const CharType* source);

    template <typename CharType>
    ENHANCED_CORE_API CharType* tstringCopyExt(NotNull const CharType* source, Size length);

    template <typename CharType>
    ENHANCED_CORE_API CharType* tstringCopyResize(NotNull const CharType* source, Size oldSize, Size newSize);

    template <typename CharType>
    ENHANCED_CORE_API Size tstringLength(NotNull const CharType* string) noexcept;

    template <typename CharType>
    ENHANCED_CORE_API bool tstringEqual(const CharType* string1, const CharType* string2) noexcept;

    template <typename CharType>
    ENHANCED_CORE_API bool tstringEqualExt(const CharType* string1, Size length1, const CharType* string2, Size length2) noexcept;
}

#endif
