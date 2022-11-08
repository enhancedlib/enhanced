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
#include <enhanced/core/String.h>
#include <enhanced/core/collections/List.h>

#ifdef CXX_LANGUAGE

NAMESPACE_L2_BEGIN(enhanced, core)

template <typename CharType>
class ENHANCED_CORE_API MutableBasicString : public BasicString<CharType> {
public:
    MutableBasicString(const CharType* value);

    MutableBasicString(CharType* value);

    explicit MutableBasicString(sizetype length);

    MutableBasicString(const MutableBasicString& other);

    MutableBasicString(MutableBasicString&& other) noexcept;

    ~MutableBasicString() noexcept;

    NoIgnoreRet
    CharType& at(sizetype index) const noexcept;

    NoIgnoreRet
    CharType& operator[](sizetype index) const noexcept;

    MutableBasicString& append(const BasicString<CharType>& other);

    MutableBasicString& replaceTo(CharType oldChar, CharType newChar);

    MutableBasicString& replaceTo(const BasicString<CharType>& oldSubstring, const BasicString<CharType>& newSubstring);

    MutableBasicString& replaceTo(CharType oldChar, const BasicString<CharType>& newSubstring);

    MutableBasicString& replaceTo(const BasicString<CharType>& oldSubstring, CharType newChar);

    MutableBasicString& toUppercase();

    MutableBasicString& toLowercase();

    MutableBasicString& operator=(const MutableBasicString& other);

    MutableBasicString& operator=(MutableBasicString&& other) noexcept;

    MutableBasicString& operator+=(const BasicString<CharType>& other);
};

using MutableString = MutableBasicString<char>;
using MutableWideString = MutableBasicString<wchar>;
#ifdef CXX_U8CHAR_SUPPORTED
using U8MutableString = MutableBasicString<u8char>;
#endif
#ifdef CXX_11_OR_LATER
using U16MutableString = MutableBasicString<u16char>;
using U32MutableString = MutableBasicString<u32char>;
#endif

NAMESPACE_L2_END

#endif
