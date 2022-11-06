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

namespace enhanced::core {
    template <typename CharType>
    class ENHANCED_CORE_API MutableBasicString : public BasicString<CharType> {
    public:
        MutableBasicString(NotNull const CharType* value);

        MutableBasicString(NotNull CharType* value);

        explicit MutableBasicString(Size length);

        MutableBasicString(const MutableBasicString& other);

        MutableBasicString(MutableBasicString&& other) noexcept;

        ~MutableBasicString() noexcept;

        RetCannotIgnored
        CharType& at(Size index) const noexcept;

        RetCannotIgnored
        CharType& operator[](Size index) const noexcept;

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
}

#endif
