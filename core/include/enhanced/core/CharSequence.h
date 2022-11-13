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
#include <enhanced/core/types.h>
#include <enhanced/core/annotations.h>

namespace enhanced::core {
    template <typename CharType>
    class ENHANCED_CORE_API CharSequence {
        template <typename>
        friend class TMutString;

    protected:
        CharType* value;

        sizetype length;

    public:
        CharSequence(const CharType* value, sizetype length);

        CharSequence(const CharSequence& other) noexcept;

        CharSequence(CharSequence&& other) noexcept;

        virtual ~CharSequence() noexcept;

        $(NoIgnoreReturn)
        func getLength() const noexcept -> sizetype;

        $(NoIgnoreReturn)
        func isEmpty() const noexcept -> bool;

        $(NoIgnoreReturn)
        func getChars() const noexcept -> CharType*;

        $(NoIgnoreReturn)
        func at(sizetype index) const noexcept -> const CharType;

        $(NoIgnoreReturn)
        func operator[](sizetype index) const noexcept -> const CharType;

        func operator=(const CharSequence& other) noexcept -> CharSequence&;

        func operator=(CharSequence&& other) noexcept -> CharSequence&;

        $(NoIgnoreReturn)
        operator CharType*() const noexcept;
    };
}
