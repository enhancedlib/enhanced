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
        other.value = null;
        other.length = INVALID_SIZE;
    }

    template <typename CharType>
    CharSequence<CharType>::~CharSequence() noexcept = default;

    template <typename CharType>
    $NoIgnoreReturn
    func CharSequence<CharType>::isEmpty() const noexcept -> bool {
        return length == 0;
    }

    template <typename CharType>
    $NoIgnoreReturn
    func CharSequence<CharType>::getLength() const noexcept -> sizetype {
        return length;
    }

    template <typename CharType>
    $NoIgnoreReturn
    func CharSequence<CharType>::getChars() const noexcept -> const CharType* {
        return value;
    }

    template <typename CharType>
    $NoIgnoreReturn
    func CharSequence<CharType>::at(sizetype index) const noexcept -> const CharType {
        return value[index];
    }

    template <typename CharType>
    $NoIgnoreReturn
    func CharSequence<CharType>::operator[](sizetype index) const noexcept -> const CharType {
        return value[index];
    }

    template <typename CharType>
    func CharSequence<CharType>::operator=(const CharSequence& other) noexcept -> CharSequence<CharType>& {
        if (this == &other) return *this;

        this->value = other.value;
        this->length = other.length;

        return *this;
    }

    template <typename CharType>
    func CharSequence<CharType>::operator=(CharSequence&& other) noexcept -> CharSequence<CharType>& {
        if (this == &other) return *this;

        this->value = other.value;
        this->length = other.length;

        other.value = null;
        other.length = INVALID_SIZE;

        return *this;
    }

    template <typename CharType>
    CharSequence<CharType>::operator const CharType *() const noexcept {
        return getChars();
    }

    template class CharSequence<char>;
    template class CharSequence<wchar>;
    template class CharSequence<u8char>;
    template class CharSequence<u16char>;
    template class CharSequence<u32char>;
}
