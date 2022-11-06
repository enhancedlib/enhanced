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
CharSequence<CharType>::CharSequence(NotNull CharType* value, const Size length) : value(value), length(length) {}

template <typename CharType>
CharSequence<CharType>::CharSequence(const CharSequence& other) noexcept = default;

template <typename CharType>
CharSequence<CharType>::CharSequence(CharSequence&& other) noexcept = default;

template <typename CharType>
CharSequence<CharType>::~CharSequence() noexcept = default;

template <typename CharType>
RetCannotIgnored
bool CharSequence<CharType>::isEmpty() const noexcept {
    return length == 0;
}

template <typename CharType>
RetCannotIgnored
Size CharSequence<CharType>::getLength() const noexcept {
    return length;
}

template <typename CharType>
RetCannotIgnored
CharType* CharSequence<CharType>::getChars() const noexcept {
    return value;
}

template <typename CharType>
RetCannotIgnored
const CharType CharSequence<CharType>::at(Size index) const noexcept {
    return value[index];
}

template <typename CharType>
RetCannotIgnored
const CharType CharSequence<CharType>::operator[](const Size index) const noexcept {
    return value[index];
}

template <typename CharType>
CharSequence<CharType>& CharSequence<CharType>::operator=(const CharSequence& other) noexcept = default;

template <typename CharType>
CharSequence<CharType>& CharSequence<CharType>::operator=(CharSequence&& other) noexcept = default;

template <typename CharType>
RetCannotIgnored
CharSequence<CharType>::operator CharType*() const noexcept {
    return value;
}

template class enhanced::core::CharSequence<char>;
template class enhanced::core::CharSequence<wchar>;
