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

#include <enhanced/core/MutableString.h>

#include <enhanced/core/defines.h>
#include <enhanced/core/types.h>
#include <enhanced/core/annotations.h>
#include <enhanced/core/memory.h>
#include <enhanced/core/stringUtil.h>
#include <enhanced/core/CharSequence.h>
#include <enhanced/core/String.h>
#include <enhanced/core/exception/NotImplementedError.h>

using enhanced::core::MutableBasicString;
using enhanced::core::BasicString;

template <typename CharType>
MutableBasicString<CharType>::MutableBasicString(const NotNull CharType* value) : BasicString<CharType>(tstringCopy(value)) {}

template <typename CharType>
MutableBasicString<CharType>::MutableBasicString(NotNull CharType* value) : BasicString<CharType>(tstringCopy(value)) {}

template <typename CharType>
MutableBasicString<CharType>::MutableBasicString(Size length) : BasicString<CharType>(tstringNew<CharType>(length)) {}

template <typename CharType>
MutableBasicString<CharType>::MutableBasicString(const MutableBasicString<CharType>& other) : BasicString<CharType>(tstringCopy(other.value)) {}

template <typename CharType>
MutableBasicString<CharType>::MutableBasicString(MutableBasicString&& other) noexcept : BasicString<CharType>(other.value) {
    other.value = null;
    other.length = 0;
};

template <typename CharType>
MutableBasicString<CharType>::~MutableBasicString() noexcept {
    delete[] this->value;
}

template <typename CharType>
CharType& MutableBasicString<CharType>::at(Size index) const noexcept {
    return this->value[index];
}

template <typename CharType>
CharType& MutableBasicString<CharType>::operator[](Size index) const noexcept {
    return this->value[index];
}

template <typename CharType>
MutableBasicString<CharType>& MutableBasicString<CharType>::append(const BasicString<CharType>& other) {
    const MutableBasicString<CharType>& string = (MutableBasicString<CharType>) other;

    if (string.length < 1) {
        return *this;
    }

    Size newLength = this->length + string.length;
    auto newString = new CharType[newLength + 1];
    newString[newLength] = '\0';

    memoryCopy(newString, this->value, newLength);
    memoryCopy(newString + this->length, string.value, newLength);

    delete[] this->value;

    this->length = newLength;
    this->value = newString;

    return *this;
}

template <typename CharType>
MutableBasicString<CharType>& MutableBasicString<CharType>::replaceTo(const CharType oldChar, const CharType newChar) {
    NOT_IMPLEMENTED();
}

template <typename CharType>
MutableBasicString<CharType>& MutableBasicString<CharType>::replaceTo(const BasicString<CharType>& oldSubstring, const BasicString<CharType>& newSubstring) {
    NOT_IMPLEMENTED();
}

template <typename CharType>
MutableBasicString<CharType>& MutableBasicString<CharType>::replaceTo(CharType oldChar, const BasicString<CharType>& newSubstring) {
    NOT_IMPLEMENTED();
}

template <typename CharType>
MutableBasicString<CharType>& MutableBasicString<CharType>::replaceTo(const BasicString<CharType>& oldSubstring, CharType newChar) {
    NOT_IMPLEMENTED();
}

template <typename CharType>
MutableBasicString<CharType>& MutableBasicString<CharType>::toUppercase() {
    for (Size index = 0; index < this->length; ++index) {
        if (this->value[index] >= 'a' && this->value[index] <= 'z') {
            (this->value[index] -= 'a') += 'A';
        }
    }
    return *this;
}

template <typename CharType>
MutableBasicString<CharType>& MutableBasicString<CharType>::toLowercase() {
    for (Size index = 0; index < this->length; ++index) {
        if (this->value[index] >= 'A' && this->value[index] <= 'Z') {
            (this->value[index] -= 'A') += 'a';
        }
    }
    return *this;
}

template <typename CharType>
MutableBasicString<CharType>& MutableBasicString<CharType>::operator=(const MutableBasicString& other) = default;

template <typename CharType>
MutableBasicString<CharType>& MutableBasicString<CharType>::operator=(MutableBasicString&& other) noexcept = default;

template <typename CharType>
MutableBasicString<CharType>& MutableBasicString<CharType>::operator+=(const BasicString<CharType>& other) {
    return append(other);
}

template class enhanced::core::MutableBasicString<char>;
template class enhanced::core::MutableBasicString<wchar>;
