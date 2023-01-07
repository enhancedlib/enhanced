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

#include <enhanced/CharSequence.h>

#include <enhanced/Defines.h>
#include <enhanced/Types.h>
#include <enhanced/Annotations.h>
#include <enhanced/String.h>
#include <enhanced/util/Traits.h>

using enhanced::util::removePtrConst;

namespace enhanced {
    template <typename CharType>
    requires util::isCharType<CharType>
    CharSequence<CharType>::CharSequence(const CharType* value, sizetype length, bool isMutable) :
        value(removePtrConst(value)), length(length), isMutable(isMutable) {}

    template <typename CharType>
    requires util::isCharType<CharType>
    CharSequence<CharType>::CharSequence(const CharType* value, sizetype length) : value(removePtrConst(value)), length(length) {}

    template <typename CharType>
    requires util::isCharType<CharType>
    CharSequence<CharType>::CharSequence(const CharSequence& other) :
        value(other.isMutable ? TStringUtil<CharType>::copy(other.value) : other.value), length(other.length), isMutable(other.isMutable) {}

    template <typename CharType>
    requires util::isCharType<CharType>
    CharSequence<CharType>::CharSequence(CharSequence&& other) noexcept : value(other.value), length(other.length), isMutable(other.isMutable) {
        other.value = nullptr;
        other.length = INVALID_SIZE;
        other.isMutable = false;
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    CharSequence<CharType>::~CharSequence() noexcept {
        if (isMutable) delete[] value;
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    $NoIgnoreReturn
    bool CharSequence<CharType>::isEmpty() const noexcept {
        return length == 0;
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    $NoIgnoreReturn
    sizetype CharSequence<CharType>::getLength() const noexcept {
        return length;
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    $NoIgnoreReturn
    const CharType* CharSequence<CharType>::chars() const noexcept {
        return value;
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    $NoIgnoreReturn
    const byte* CharSequence<CharType>::toBytes() const noexcept {
        return reinterpret_cast<const byte*>(value);
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    $NoIgnoreReturn
    const CharType CharSequence<CharType>::at(sizetype index) const noexcept {
        return value[index];
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    $NoIgnoreReturn
    const CharType CharSequence<CharType>::operator[](sizetype index) const noexcept {
        return value[index];
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    $ReturnSelf
    CharSequence<CharType>& CharSequence<CharType>::operator=(const CharSequence& other) noexcept {
        if (this == &other) return *this;

        if (isMutable) delete[] value;

        value = other.value;
        length = other.length;
        isMutable = other.isMutable;

        return *this;
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    $ReturnSelf
    CharSequence<CharType>& CharSequence<CharType>::operator=(CharSequence&& other) noexcept {
        if (this == &other) return *this;

        if (isMutable) delete[] value;

        value = other.value;
        length = other.length;
        isMutable = other.isMutable;

        other.value = nullptr;
        other.length = INVALID_SIZE;
        other.isMutable = false;

        return *this;
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    CharSequence<CharType>::operator const CharType*() const noexcept {
        return chars();
    }

    template class CharSequence<char>;
    template class CharSequence<wchar>;
    template class CharSequence<u8char>;
    template class CharSequence<u16char>;
    template class CharSequence<u32char>;
}
