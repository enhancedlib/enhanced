/*
 * Copyright (C) 2023 Liu Baihao. All rights reserved.
 *
 * Licensed under the MIT License with the Distribution Exception.
 * You may not use this file except in compliance with the License.
 *
 * THIS FILE IS PART OF THE ENHANCED SOFTWARE, and IT ALWAYS
 * PROVIDES "AS IS" WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY.
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
    CharSequence<CharType>::CharSequence(const CharType* value, sizetype length, bool isOwn) :
        value(removePtrConst(value)), length(length), isOwn(isOwn) {}

    template <typename CharType>
    requires util::isCharType<CharType>
    CharSequence<CharType>::CharSequence(const CharType* value, sizetype length) : value(removePtrConst(value)), length(length) {}

    template <typename CharType>
    requires util::isCharType<CharType>
    CharSequence<CharType>::CharSequence(const CharSequence& other) :
        value(other.isOwn ? TStringUtil<CharType>::copy(other.value) : other.value), length(other.length), isOwn(other.isOwn) {}

    template <typename CharType>
    requires util::isCharType<CharType>
    CharSequence<CharType>::CharSequence(CharSequence&& other) noexcept : value(other.value), length(other.length), isOwn(other.isOwn) {
        other.value = nullptr;
        other.length = SIZE_TYPE_MAX;
        other.isOwn = false;
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    CharSequence<CharType>::~CharSequence() noexcept {
        if (isOwn) delete[] value;
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    E_ANNOTATE(RetNotIgnored)
    bool CharSequence<CharType>::isEmpty() const noexcept {
        return length == 0;
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    E_ANNOTATE(RetNotIgnored)
    sizetype CharSequence<CharType>::getLength() const noexcept {
        return length;
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    E_ANNOTATE(RetNotIgnored)
    CharType* CharSequence<CharType>::chars() const noexcept {
        return value;
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    E_ANNOTATE(RetNotIgnored)
    const byte* CharSequence<CharType>::toBytes() const noexcept {
        return reinterpret_cast<const byte*>(value);
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    E_ANNOTATE(RetNotIgnored)
    const CharType CharSequence<CharType>::at(sizetype index) const noexcept {
        return value[index];
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    E_ANNOTATE(RetNotIgnored)
    const CharType CharSequence<CharType>::operator[](sizetype index) const noexcept {
        return value[index];
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    E_ANNOTATE(ReturnSelf)
    CharSequence<CharType>& CharSequence<CharType>::operator=(const CharSequence& other) noexcept {
        if (this == &other) return *this;

        if (isOwn) delete[] value;

        value = other.value;
        length = other.length;
        isOwn = other.isOwn;

        return *this;
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    E_ANNOTATE(ReturnSelf)
    CharSequence<CharType>& CharSequence<CharType>::operator=(CharSequence&& other) noexcept {
        if (this == &other) return *this;

        if (isOwn) delete[] value;

        value = other.value;
        length = other.length;
        isOwn = other.isOwn;

        other.value = nullptr;
        other.length = SIZE_TYPE_MAX;
        other.isOwn = false;

        return *this;
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    CharSequence<CharType>::operator CharType*() const noexcept {
        return chars();
    }

    template class CharSequence<char>;
    template class CharSequence<wchar>;
    template class CharSequence<u8char>;
    template class CharSequence<u16char>;
    template class CharSequence<u32char>;
}
