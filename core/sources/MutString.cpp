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

#include <enhanced/MutString.h>

#include <enhanced/Defines.h>
#include <enhanced/Types.h>
#include <enhanced/Annotations.h>
#include <enhanced/Memory.h>
#include <enhanced/Array.h>
#include <enhanced/Character.h>
#include <enhanced/util/Traits.h>
#include <enhanced/CharSequence.h>
#include <enhanced/String.h>
#include <enhanced/exceptions/NotImplementedError.h>

using enhanced::util::removeConst;
using enhanced::util::removePtrConst;

namespace enhanced {
    template <typename CharType>
    TMutString<CharType>::TMutString(const CharType* value, sizetype length) noexcept :
        TString<CharType>(TString<CharType>::copy(value, length), length) {}

    template <typename CharType>
    TMutString<CharType>::TMutString() : TString<CharType>(TString<CharType>::make(0), 0) {}

    template <typename CharType>
    TMutString<CharType>::TMutString(const CharType*& value) : TMutString<CharType>(removePtrConst(value)) {}

    template <typename CharType>
    TMutString<CharType>::TMutString(CharType* const& value) : TMutString<CharType>(removeConst(value)) {}

    template <typename CharType>
    TMutString<CharType>::TMutString(CharType*& value) :
        TMutString<CharType>(value, TString<CharType>::calcLength(value)) {}

    template <typename CharType>
    TMutString<CharType>::TMutString(sizetype length) : TString<CharType>(TString<CharType>::make(length), length) {}

    template <typename CharType>
    TMutString<CharType>::TMutString(const TMutString& other) :
        TString<CharType>(TString<CharType>::copy(other.value, other.length), other.length) {}

    template <typename CharType>
    TMutString<CharType>::TMutString(TMutString&& other) noexcept : TString<CharType>(other.value) {
        other.value = null;
        other.length = INVALID_SIZE;
    }

    template <typename CharType>
    TMutString<CharType>::~TMutString() noexcept {
        delete[] this->value;
    }

    template <typename CharType>
    $NoIgnoreReturn
    func TMutString<CharType>::chars() const noexcept -> CharType* {
        return this->value;
    }

    template <typename CharType>
    $NoIgnoreReturn
    func TMutString<CharType>::at(sizetype index) const noexcept -> CharType& {
        return this->value[index];
    }

    template <typename CharType>
    $NoIgnoreReturn
    func TMutString<CharType>::operator[](sizetype index) const noexcept -> CharType& {
        return this->value[index];
    }

    template <typename CharType>
    func TMutString<CharType>::append(const TString<CharType>& other) -> TMutString& {
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
    func TMutString<CharType>::replaceTo(sizetype start, sizetype end, CharType newChar) -> TMutString& {
        NOT_IMPLEMENTED();
    }

    template <typename CharType>
    func TMutString<CharType>::replaceTo(sizetype start, sizetype end, const TString<CharType>& newSubstring) -> TMutString& {
        NOT_IMPLEMENTED();
    }

    template <typename CharType>
    func TMutString<CharType>::replaceTo(const CharType oldChar, const CharType newChar) -> TMutString& {
        this->value[this->indexOf(oldChar)] = newChar;
        return *this;
    }

    template <typename CharType>
    func TMutString<CharType>::replaceTo(const TString<CharType>& oldSubstring, const TString<CharType>& newSubstring) -> TMutString& {
        NOT_IMPLEMENTED();
    }

    template <typename CharType>
    func TMutString<CharType>::replaceTo(CharType oldChar, const TString<CharType>& newSubstring) -> TMutString& {
        NOT_IMPLEMENTED();
    }

    template <typename CharType>
    func TMutString<CharType>::replaceTo(const TString<CharType>& oldSubstring, CharType newChar) -> TMutString& {
        NOT_IMPLEMENTED();
    }

    template <typename CharType>
    func TMutString<CharType>::replaceAllTo(CharType oldChar, CharType newChar) -> TMutString& {
        NOT_IMPLEMENTED();
    }

    template <typename CharType>
    func TMutString<CharType>::replaceAllTo(const TString<CharType>& oldSubstring, const TString<CharType>& newSubstring) -> TMutString& {
        NOT_IMPLEMENTED();
    }

    template <typename CharType>
    func TMutString<CharType>::replaceAllTo(CharType oldChar, const TString<CharType>& newSubstring) -> TMutString& {
        NOT_IMPLEMENTED();
    }

    template <typename CharType>
    func TMutString<CharType>::replaceAllTo(const TString<CharType>& oldSubstring, CharType newChar) -> TMutString& {
        NOT_IMPLEMENTED();
    }

    template <typename CharType>
    func TMutString<CharType>::fill(CharType ch) -> TMutString& {
        arrayFill(this->value, ch, this->length, sizeof(char));

        return *this;
    }

    template <typename CharType>
    func TMutString<CharType>::toUppercase() -> TMutString& {
        for (sizetype index = 0; index < this->length; ++index) {
            if (this->value[index] >= TCHAR(CharType, 'a') && this->value[index] <= TCHAR(CharType, 'z')) {
                this->value[index] -= TCHAR(CharType, 'a') += TCHAR(CharType, 'A');
            }
        }
        return *this;
    }

    template <typename CharType>
    func TMutString<CharType>::toLowercase() -> TMutString& {
        for (sizetype index = 0; index < this->length; ++index) {
            if (this->value[index] >= TCHAR(CharType, 'A') && this->value[index] <= TCHAR(CharType, 'Z')) {
                (this->value[index] -= TCHAR(CharType, 'A')) += TCHAR(CharType, 'a');
            }
        }
        return *this;
    }

    template <typename CharType>
    func TMutString<CharType>::operator=(const TMutString& other) -> TMutString& {
        if (this == &other) return *this;

        delete[] this->value;

        this->value = TString<CharType>::copy(other.value, other.length);
        this->length = other.length;

        return *this;
    }

    template <typename CharType>
    func TMutString<CharType>::operator=(TMutString&& other) noexcept -> TMutString& {
        if (this == &other) return *this;

        delete[] this->value;

        this->value = other.value;
        this->length = other.length;

        other.value = null;
        other.length = INVALID_SIZE;

        return *this;
    }

    template <typename CharType>
    func TMutString<CharType>::operator+=(const TString<CharType>& other) -> TMutString& {
        return append(other);
    }

    template class TMutString<char>;
    template class TMutString<wchar>;
    template class TMutString<u8char>;
    template class TMutString<u16char>;
    template class TMutString<u32char>;
}
