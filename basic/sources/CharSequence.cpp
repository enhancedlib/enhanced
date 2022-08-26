/*
 * Copyright (C) 2022 Liu Baihao. All rights reserved.
 *
 * Licensed under the Enhanced License, Version 0.5.4 (the "License").
 * You may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     https://sharedwonder.github.io/enhanced-website/ENHANCED-LICENSE.txt
 *
 * UNLESS REQUIRED BY APPLICABLE LAW OR AGREED TO IN WRITING,
 * THE SOFTWARE IS ALWAYS PROVIDED "AS IS",
 * WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY.
 */

#include "enhanced/basic/CharSequence.h"

#include "enhanced/core/defines.h"
#include "enhanced/core/types.h"
#include "enhanced/core/annotations.h"

using enhanced::basic::CharSequence;

template <typename CharType>
CharSequence<CharType>::CharSequence(NotNull CharType* const value, const Size length) : value(value), length(length) {}

template <typename CharType>
CharSequence<CharType>::CharSequence(const CharSequence& other) noexcept : value(other.value), length(other.length), shallowClone(true) {}

template <typename CharType>
CharSequence<CharType>::~CharSequence() = default;

template <typename CharType>
RetCannotIgnored
bool CharSequence<CharType>::isEmpty() const {
    return length == 0;
}

template <typename CharType>
RetCannotIgnored
Size CharSequence<CharType>::getLength() const {
    return length;
}

template <typename CharType>
RetCannotIgnored
CharType* CharSequence<CharType>::getChars() const {
    return value;
}

template <typename CharType>
RetCannotIgnored
const CharType CharSequence<CharType>::at(Size index) const {
    return value[index];
}

template <typename CharType>
RetCannotIgnored
const CharType CharSequence<CharType>::operator[](const Size index) const {
    return value[index];
}

template <typename CharType>
RetCannotIgnored
CharSequence<CharType>::operator CharType*() const {
    return value;
}

template class enhanced::basic::CharSequence<char>;
template class enhanced::basic::CharSequence<wchar>;
