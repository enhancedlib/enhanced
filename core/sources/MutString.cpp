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

#include <enhanced/core/MutString.h>

#include <enhanced/core/defines.h>
#include <enhanced/core/types.h>
#include <enhanced/core/annotations.h>
#include <enhanced/core/memory.h>
#include <enhanced/core/array.h>
#include <enhanced/core/charUtil.h>
#include <enhanced/core/CharSequence.h>
#include <enhanced/core/String.h>
#include <enhanced/core/exception/NotImplementedError.h>

using enhanced::core::TMutString;
using enhanced::core::TString;
using enhanced::core::arrayFillPtr;
using enhanced::core::arrayCopy;

template <typename CharType>
TMutString<CharType>::TMutString() : TString<CharType>(TString<CharType>::make(0)) {}

template <typename CharType>
TMutString<CharType>::TMutString(const CharType* value) : TString<CharType>(TString<CharType>::copy(value)) {}

template <typename CharType>
TMutString<CharType>::TMutString(CharType* value) : TString<CharType>(TString<CharType>::copy(value)) {}

template <typename CharType>
TMutString<CharType>::TMutString(sizetype length) : TString<CharType>(TString<CharType>::make(length)) {}

template <typename CharType>
TMutString<CharType>::TMutString(const TMutString<CharType>& other) : TString<CharType>(TString<CharType>::copy(other.value)) {}

template <typename CharType>
TMutString<CharType>::TMutString(TMutString&& other) noexcept : TString<CharType>(other.value) {
    other.value = null;
    other.length = SIZE_TYPE_MAX;
};

template <typename CharType>
TMutString<CharType>::~TMutString() noexcept {
    delete[] this->value;
}

template <typename CharType>
$(NoIgnoreReturn)
func TMutString<CharType>::at(sizetype index) const noexcept -> CharType& {
    return this->value[index];
}

template <typename CharType>
$(NoIgnoreReturn)
func TMutString<CharType>::operator[](sizetype index) const noexcept -> CharType& {
    return this->value[index];
}

template <typename CharType>
func TMutString<CharType>::append(const TString<CharType>& other) -> TMutString<CharType>& {
    if (other.length == 0 || other.value == null) {
        return *this;
    }

    sizetype newLength = other.length + other.length;
    let newString = new CharType[newLength + 1];
    newString[newLength] = TCHAR(CharType, '\0');

    arrayCopy(newString, this->value, newLength, sizeof(CharType));
    arrayCopy(newString + this->length, other.value, newLength, sizeof(CharType));

    delete[] this->value;

    this->length = newLength;
    this->value = newString;

    return *this;
}

template <typename CharType>
func TMutString<CharType>::replaceTo(sizetype start, sizetype end, CharType newChar) -> TMutString<CharType>& {
    NOT_IMPLEMENTED();
}

template <typename CharType>
func TMutString<CharType>::replaceTo(sizetype start, sizetype end, const TString<CharType>& newSubstring) -> TMutString<CharType>& {
    NOT_IMPLEMENTED();
}

template <typename CharType>
func TMutString<CharType>::replaceTo(const CharType oldChar, const CharType newChar) -> TMutString<CharType>& {
    this->value[this->indexOf(oldChar)] = newChar;
    return *this;
}

template <typename CharType>
func TMutString<CharType>::replaceTo(const TString<CharType>& oldSubstring, const TString<CharType>& newSubstring) -> TMutString<CharType>& {
    NOT_IMPLEMENTED();
}

template <typename CharType>
func TMutString<CharType>::replaceTo(CharType oldChar, const TString<CharType>& newSubstring) -> TMutString<CharType>& {
    NOT_IMPLEMENTED();
}

template <typename CharType>
func TMutString<CharType>::replaceTo(const TString<CharType>& oldSubstring, CharType newChar) -> TMutString<CharType>& {
    NOT_IMPLEMENTED();
}

template <typename CharType>
func TMutString<CharType>::replaceAllTo(CharType oldChar, CharType newChar) -> TMutString<CharType>& {
    NOT_IMPLEMENTED();
}

template <typename CharType>
func TMutString<CharType>::replaceAllTo(const TString<CharType>& oldSubstring, const TString<CharType>& newSubstring) -> TMutString<CharType>& {
    NOT_IMPLEMENTED();
}

template <typename CharType>
func TMutString<CharType>::replaceAllTo(CharType oldChar, const TString<CharType>& newSubstring) -> TMutString<CharType>& {
    NOT_IMPLEMENTED();
}

template <typename CharType>
func TMutString<CharType>::replaceAllTo(const TString<CharType>& oldSubstring, CharType newChar) -> TMutString<CharType>& {
    NOT_IMPLEMENTED();
}

template <typename CharType>
func TMutString<CharType>::fill(CharType ch) -> TMutString<CharType>& {
    arrayFillPtr(this->value, &ch, this->length, sizeof(CharType));

    return *this;
}

template <typename CharType>
func TMutString<CharType>::toUppercase() -> TMutString<CharType>& {
    for (sizetype index = 0; index < this->length; ++index) {
        if (this->value[index] >= TCHAR(CharType, 'a') && this->value[index] <= TCHAR(CharType, 'z')) {
            this->value[index] -= TCHAR(CharType, 'a') += TCHAR(CharType, 'A');
        }
    }
    return *this;
}

template <typename CharType>
func TMutString<CharType>::toLowercase() -> TMutString<CharType>& {
    for (sizetype index = 0; index < this->length; ++index) {
        if (this->value[index] >= TCHAR(CharType, 'A') && this->value[index] <= TCHAR(CharType, 'Z')) {
            (this->value[index] -= TCHAR(CharType, 'A')) += TCHAR(CharType, 'a');
        }
    }
    return *this;
}

template <typename CharType>
func TMutString<CharType>::operator=(const TMutString& other) -> TMutString<CharType>& = default;

template <typename CharType>
func TMutString<CharType>::operator=(TMutString&& other) noexcept -> TMutString<CharType>& = default;

template <typename CharType>
func TMutString<CharType>::operator+=(const TString<CharType>& other) -> TMutString<CharType>& {
    return append(other);
}

template class enhanced::core::TMutString<char>;
template class enhanced::core::TMutString<wchar>;
template class enhanced::core::TMutString<u8char>;
template class enhanced::core::TMutString<u16char>;
template class enhanced::core::TMutString<u32char>;
