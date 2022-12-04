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

#include <enhanced/CharSequence.h>

#include <enhanced/Defines.h>
#include <enhanced/Types.h>
#include <enhanced/Annotations.h>
#include <enhanced/util/Traits.h>

using enhanced::util::removePtrConst;

namespace enhanced {
    template <typename CharType>
    CharSequence<CharType>::CharSequence(const CharType* value, sizetype length) : value(removePtrConst(value)), length(length) {}

    template <typename CharType>
    CharSequence<CharType>::CharSequence(const CharSequence& other) noexcept = default;

    template <typename CharType>
    CharSequence<CharType>::CharSequence(CharSequence&& other) noexcept : value(other.value), length(other.length) {
        other.value = nullptr;
        other.length = INVALID_SIZE;
        other.isDynamic = false;
    }

    template <typename CharType>
    CharSequence<CharType>::~CharSequence() noexcept {
        if (isDynamic) delete[] this->value;
    }

    template <typename CharType>
    $NoIgnoreReturn
    bool CharSequence<CharType>::isEmpty() const noexcept {
        return length == 0;
    }

    template <typename CharType>
    $NoIgnoreReturn
    sizetype CharSequence<CharType>::getLength() const noexcept {
        return length;
    }

    template <typename CharType>
    $NoIgnoreReturn
    const CharType* CharSequence<CharType>::chars() const noexcept {
        return value;
    }

    template <typename CharType>
    $NoIgnoreReturn
    const CharType CharSequence<CharType>::at(sizetype index) const noexcept {
        return value[index];
    }

    template <typename CharType>
    $NoIgnoreReturn
    const CharType CharSequence<CharType>::operator[](sizetype index) const noexcept {
        return value[index];
    }

    template <typename CharType>
    CharSequence<CharType>& CharSequence<CharType>::operator=(const CharSequence& other) noexcept {
        if (this == &other) return *this;

        this->value = other.value;
        this->length = other.length;

        return *this;
    }

    template <typename CharType>
    CharSequence<CharType>& CharSequence<CharType>::operator=(CharSequence&& other) noexcept {
        if (this == &other) return *this;

        this->value = other.value;
        this->length = other.length;

        other.value = nullptr;
        other.length = INVALID_SIZE;
        other.length = false;

        return *this;
    }

    template <typename CharType>
    CharSequence<CharType>::operator const CharType *() const noexcept {
        return chars();
    }

    template class CharSequence<char>;
    template class CharSequence<wchar>;
    template class CharSequence<u8char>;
    template class CharSequence<u16char>;
    template class CharSequence<u32char>;
}
