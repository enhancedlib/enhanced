/*
 * Copyright (C) 2022 Liu Baihao. All rights reserved.
 *
 * Licensed under the Enhanced Software License, latest version.
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
#include <enhanced/core/CharSequence.h>
#include <enhanced/core/collections/ArrayList.h>

#ifdef CXX_LANGUAGE

NAMESPACE_L2_BEGIN(enhanced, core)

template <typename CharType>
class MutableBasicString;

template <typename CharType>
class ENHANCED_CORE_API BasicString : public CharSequence<CharType> {
protected:
    BasicString(CharType* value, sizetype length) noexcept;

public:
    BasicString(const CharType* value) noexcept;

    BasicString(CharType* value) noexcept;

    BasicString(const BasicString& other) noexcept;

    BasicString(BasicString&& other) noexcept;

    NoIgnoreRet
    sizetype indexOf(CharType ch) const noexcept;

    NoIgnoreRet
    sizetype indexOf(CharType ch, sizetype getN) const noexcept;

    NoIgnoreRet
    sizetype indexOf(const BasicString& string) const noexcept;

    NoIgnoreRet
    sizetype indexOf(const BasicString& string, sizetype getN) const noexcept;

    NoIgnoreRet
    sizetype lastIndexOf(const BasicString& string) const noexcept;

    NoIgnoreRet
    sizetype lastIndexOf(const BasicString& string, sizetype getN) const noexcept;

    NoIgnoreRet
    sizetype lastIndexOf(CharType ch) const noexcept;

    NoIgnoreRet
    sizetype lastIndexOf(CharType ch, sizetype getN) const noexcept;

    RetRequiresRelease
    collections::ArrayList<sizetype> indexOfAll(CharType ch) const noexcept;

    RetRequiresRelease
    collections::ArrayList<sizetype> indexOfAll(const BasicString& string) const noexcept;

    NoIgnoreRet
    MutableBasicString<CharType> replace(CharType oldChar, CharType newChar) const;

    NoIgnoreRet
    MutableBasicString<CharType> replace(const BasicString& oldSubstring, const BasicString& newSubstring) const;

    NoIgnoreRet
    MutableBasicString<CharType> replace(CharType oldChar, const BasicString& newSubstring) const;

    NoIgnoreRet
    MutableBasicString<CharType> replace(const BasicString& oldSubstring, CharType newChar) const;

    NoIgnoreRet
    MutableBasicString<CharType> uppercase() const;

    NoIgnoreRet
    MutableBasicString<CharType> lowercase() const;

    NoIgnoreRet
    bool operator==(const BasicString& string) const noexcept;

    NoIgnoreRet
    MutableBasicString<CharType> operator+(const BasicString& string) const;

    BasicString& operator=(const BasicString& other) noexcept;

    BasicString& operator=(BasicString&& other) noexcept;
};

using String = BasicString<char>;
using WideString = BasicString<wchar>;
#ifdef CXX_U8CHAR_SUPPORTED
using U8String = BasicString<u8char>;
#endif
#ifdef CXX_11_OR_LATER
using U16String = BasicString<u16char>;
using U32String = BasicString<u32char>;
#endif

NAMESPACE_L2_END

#endif
