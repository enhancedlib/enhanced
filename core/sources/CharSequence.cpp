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
#include <enhanced/core/util/traits.h>

using enhanced::core::CharSequence;
using enhanced::core::util::traits::removePtrConst;

template <typename CharType>
CharSequence<CharType>::CharSequence(const CharType* value, const sizetype length) : value(removePtrConst(value)), length(length) {}

template <typename CharType>
CharSequence<CharType>::CharSequence(const CharSequence& other) noexcept = default;

template <typename CharType>
CharSequence<CharType>::CharSequence(CharSequence&& other) noexcept = default;

template <typename CharType>
CharSequence<CharType>::~CharSequence() noexcept = default;

template <typename CharType>
$(NoIgnoreReturn)
func CharSequence<CharType>::isEmpty() const noexcept -> bool {
    return length == 0;
}

template <typename CharType>
$(NoIgnoreReturn)
func CharSequence<CharType>::getLength() const noexcept -> sizetype {
    return length;
}

template <typename CharType>
$(NoIgnoreReturn)
func CharSequence<CharType>::getChars() const noexcept -> CharType* {
    return value;
}

template <typename CharType>
$(NoIgnoreReturn)
func CharSequence<CharType>::at(sizetype index) const noexcept -> const CharType {
    return value[index];
}

template <typename CharType>
$(NoIgnoreReturn)
func CharSequence<CharType>::operator[](const sizetype index) const noexcept -> const CharType {
    return value[index];
}

template <typename CharType>
func CharSequence<CharType>::operator=(const CharSequence& other) noexcept -> CharSequence<CharType>& = default;

template <typename CharType>
func CharSequence<CharType>::operator=(CharSequence&& other) noexcept -> CharSequence<CharType>& = default;

template <typename CharType>
$(NoIgnoreReturn)
CharSequence<CharType>::operator CharType*() const noexcept {
    return value;
}

template class enhanced::core::CharSequence<char>;
template class enhanced::core::CharSequence<wchar>;
template class enhanced::core::CharSequence<u8char>;
template class enhanced::core::CharSequence<u16char>;
template class enhanced::core::CharSequence<u32char>;
