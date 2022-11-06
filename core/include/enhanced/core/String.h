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

namespace enhanced::core {
    template <typename CharType>
    class MutableBasicString;

    template <typename CharType>
    class ENHANCED_CORE_API BasicString : public CharSequence<CharType> {
    protected:
        BasicString(NotNull CharType* value, Size length) noexcept;

    public:
        BasicString(NotNull const CharType* value) noexcept;

        BasicString(NotNull CharType* value) noexcept;

        BasicString(const BasicString& other) noexcept;

        BasicString(BasicString&& other) noexcept;

        RetCannotIgnored
        Size indexOf(CharType ch) const noexcept;

        RetCannotIgnored
        Size indexOf(CharType ch, Size getN) const noexcept;

        RetCannotIgnored
        Size indexOf(const BasicString& string) const noexcept;

        RetCannotIgnored
        Size indexOf(const BasicString& string, Size getN) const noexcept;

        RetCannotIgnored
        Size lastIndexOf(const BasicString& string) const noexcept;

        RetCannotIgnored
        Size lastIndexOf(const BasicString& string, Size getN) const noexcept;

        RetCannotIgnored
        Size lastIndexOf(CharType ch) const noexcept;

        RetCannotIgnored
        Size lastIndexOf(CharType ch, Size getN) const noexcept;

        RetRequiresRelease
        collections::ArrayList<Size> indexOfAll(CharType ch) const noexcept;

        RetRequiresRelease
        collections::ArrayList<Size> indexOfAll(const BasicString& string) const noexcept;

        RetCannotIgnored
        MutableBasicString<CharType> replace(CharType oldChar, CharType newChar) const;

        RetCannotIgnored
        MutableBasicString<CharType> replace(const BasicString& oldSubstring, const BasicString& newSubstring) const;

        RetCannotIgnored
        MutableBasicString<CharType> replace(CharType oldChar, const BasicString& newSubstring) const;

        RetCannotIgnored
        MutableBasicString<CharType> replace(const BasicString& oldSubstring, CharType newChar) const;

        RetCannotIgnored
        MutableBasicString<CharType> uppercase() const;

        RetCannotIgnored
        MutableBasicString<CharType> lowercase() const;

        RetCannotIgnored
        bool operator==(const BasicString& string) const noexcept;

        RetCannotIgnored
        MutableBasicString<CharType> operator+(const BasicString& string) const;

        BasicString& operator=(const BasicString& other) noexcept;

        BasicString& operator=(BasicString&& other) noexcept;
    };

    using String = BasicString<char>;
    using WideString = BasicString<wchar>;
}

#endif
