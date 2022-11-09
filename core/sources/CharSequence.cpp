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

#include <enhanced/core/CharSequence.h>

#include <enhanced/core/defines.h>
#include <enhanced/core/types.h>
#include <enhanced/core/annotations.h>

using enhanced::core::CharSequence;

template <typename CharType>
CharSequence<CharType>::CharSequence(CharType* value, const sizetype length) : value(value), length(length) {}

template <typename CharType>
CharSequence<CharType>::CharSequence(const CharSequence& other) noexcept = default;

template <typename CharType>
CharSequence<CharType>::CharSequence(CharSequence&& other) noexcept = default;

template <typename CharType>
CharSequence<CharType>::~CharSequence() noexcept = default;

template <typename CharType>
NoIgnoreRet
bool CharSequence<CharType>::isEmpty() const noexcept {
    return length == 0;
}

template <typename CharType>
NoIgnoreRet
sizetype CharSequence<CharType>::getLength() const noexcept {
    return length;
}

template <typename CharType>
NoIgnoreRet
CharType* CharSequence<CharType>::getChars() const noexcept {
    return value;
}

template <typename CharType>
NoIgnoreRet
const CharType CharSequence<CharType>::at(sizetype index) const noexcept {
    return value[index];
}

template <typename CharType>
NoIgnoreRet
const CharType CharSequence<CharType>::operator[](const sizetype index) const noexcept {
    return value[index];
}

template <typename CharType>
CharSequence<CharType>& CharSequence<CharType>::operator=(const CharSequence& other) noexcept = default;

template <typename CharType>
CharSequence<CharType>& CharSequence<CharType>::operator=(CharSequence&& other) noexcept = default;

template <typename CharType>
NoIgnoreRet
CharSequence<CharType>::operator CharType*() const noexcept {
    return value;
}

template class enhanced::core::CharSequence<char>;
template class enhanced::core::CharSequence<wchar>;
template class enhanced::core::CharSequence<u8char>;
template class enhanced::core::CharSequence<u16char>;
template class enhanced::core::CharSequence<u32char>;
