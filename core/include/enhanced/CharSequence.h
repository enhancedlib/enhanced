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
#include <enhanced/ExportCore.h>
#include <enhanced/Types.h>
#include <enhanced/Annotations.h>
#include <enhanced/util/Traits.h>

namespace enhanced {
    template <typename CharType>
    requires util::isCharType<CharType>
    class ENHANCED_CORE_API CharSequence {
        template <typename Type>
        requires util::isCharType<Type>
        friend class TMutString;

    protected:
        CharType* value;

        sizetype length;

        bool isMutable = false;

        CharSequence(const CharType* value, sizetype length, bool isMutable);

    public:
        CharSequence(const CharType* value, sizetype length);

        CharSequence(const CharSequence& other);

        CharSequence(CharSequence&& other) noexcept;

        ~CharSequence() noexcept;

        [[NoIgnoreReturn]]
        sizetype getLength() const noexcept;

        [[NoIgnoreReturn]]
        bool isEmpty() const noexcept;

        [[NoIgnoreReturn]]
        const CharType* chars() const noexcept;

        [[NoIgnoreReturn]]
        const byte* toBytes() const noexcept;

        [[NoIgnoreReturn]]
        const CharType at(sizetype index) const noexcept;

        [[NoIgnoreReturn]]
        const CharType operator[](sizetype index) const noexcept;

        [[ReturnSelf]]
        CharSequence& operator=(const CharSequence& other) noexcept;

        [[ReturnSelf]]
        CharSequence& operator=(CharSequence&& other) noexcept;

        explicit operator const CharType*() const noexcept;
    };
}
