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

using enhanced::util::move;
using enhanced::util::removeConst;
using enhanced::util::removePtrConst;

namespace enhanced {
    template <typename CharType>
    TMutString<CharType>::TMutString(const CharType* value, sizetype length) noexcept :
        TString<CharType>(TString<CharType>::copy(value, length), length) {
        this->isDynamic = true;
    }

    template <typename CharType>
    TMutString<CharType>::TMutString() : TString<CharType>(TString<CharType>::make(0), 0) {
        this->isDynamic = true;
    }

    template <typename CharType>
    TMutString<CharType>::TMutString(const CharType*& value) : TMutString<CharType>(removePtrConst(value)) {
        this->isDynamic = true;
    }

    template <typename CharType>
    TMutString<CharType>::TMutString(CharType* const& value) : TMutString<CharType>(removeConst(value)) {
        this->isDynamic = true;
    }

    template <typename CharType>
    TMutString<CharType>::TMutString(CharType*& value) :
        TMutString<CharType>(value, TString<CharType>::calcLength(value)) {
        this->isDynamic = true;
    }

    template <typename CharType>
    TMutString<CharType>::TMutString(sizetype length) : TString<CharType>(TString<CharType>::make(length), length) {
        this->isDynamic = true;
    }

    template <typename CharType>
    TMutString<CharType>::TMutString(const TMutString& other) :
        TString<CharType>(TString<CharType>::copy(other.value, other.length), other.length) {
        this->isDynamic = true;
    }

    template <typename CharType>
    TMutString<CharType>::TMutString(TMutString&& other) noexcept : TString<CharType>(move(other)) {
        this->isDynamic = true;
    }

    template <typename CharType>
    $NoIgnoreReturn
    CharType* TMutString<CharType>::chars() const noexcept {
        return this->value;
    }

    template <typename CharType>
    $NoIgnoreReturn
    CharType& TMutString<CharType>::at(sizetype index) const noexcept {
        return this->value[index];
    }

    template <typename CharType>
    $NoIgnoreReturn
    CharType& TMutString<CharType>::operator[](sizetype index) const noexcept {
        return this->value[index];
    }

    template <typename CharType>
    TMutString<CharType>& TMutString<CharType>::append(const TString<CharType>& string) {
        if (string.length == 0 || string.value == nullptr) {
            return *this;
        }

        sizetype newLength = this->length + string.length;
        auto newString = new CharType[newLength + 1];
        newString[newLength] = ST_CHAR(CharType, '\0');

        arrayCopy(newString, this->value, this->length, sizeof(CharType));
        arrayCopy(newString + this->length, string.value, string.length, sizeof(CharType));

        delete[] this->value;

        this->value = newString;
        this->length = newLength;

        return *this;
    }

    template <typename CharType>
    TMutString<CharType>& TMutString<CharType>::append(CharType ch) {
        sizetype newLength = this->length + 1;
        auto newString = new CharType[newLength + 1];
        newString[newLength] = ST_CHAR(CharType, '\0');

        arrayCopy(newString, this->value, this->length, sizeof(CharType));
        newString[this->length] = ch;

        delete[] this->value;

        this->value = newString;
        this->length = newLength;

        return *this;
    }

    template <typename CharType>
    TMutString<CharType>& TMutString<CharType>::insertFirst(const TString<CharType>& string) {
        if (string.length == 0 || string.value == nullptr) {
            return *this;
        }

        sizetype newLength = this->length + string.length;
        auto newString = new CharType[newLength + 1];
        newString[newLength] = ST_CHAR(CharType, '\0');

        arrayCopy(newString, string.value, string.length, sizeof(CharType));
        arrayCopy(newString + string.length, this->value, this->length, sizeof(CharType));

        delete[] this->value;

        this->value = newString;
        this->length = newLength;

        return *this;
    }

    template <typename CharType>
    TMutString<CharType>& TMutString<CharType>::insertFirst(CharType ch) {
        sizetype newLength = this->length + 1;
        auto newString = new CharType[newLength + 1];
        newString[newLength] = ST_CHAR(CharType, '\0');

        newString[0] = ch;
        arrayCopy(newString + 1, this->value, this->length, sizeof(CharType));

        delete[] this->value;

        this->value = newString;
        this->length = newLength;

        return *this;
    }

    template <typename CharType>
    TMutString<CharType>& TMutString<CharType>::replaceTo(sizetype start, sizetype end, CharType newChar) {
        NOT_IMPLEMENTED();
    }

    template <typename CharType>
    TMutString<CharType>& TMutString<CharType>::replaceTo(sizetype start, sizetype end, const TString<CharType>& newSubstring) {
        NOT_IMPLEMENTED();
    }

    template <typename CharType>
    TMutString<CharType>& TMutString<CharType>::replaceTo(const CharType oldChar, const CharType newChar) {
        this->value[this->indexOf(oldChar)] = newChar;
        return *this;
    }

    template <typename CharType>
    TMutString<CharType>& TMutString<CharType>::replaceTo(const TString<CharType>& oldSubstring, const TString<CharType>& newSubstring) {
        NOT_IMPLEMENTED();
    }

    template <typename CharType>
    TMutString<CharType>& TMutString<CharType>::replaceTo(CharType oldChar, const TString<CharType>& newSubstring) {
        NOT_IMPLEMENTED();
    }

    template <typename CharType>
    TMutString<CharType>& TMutString<CharType>::replaceTo(const TString<CharType>& oldSubstring, CharType newChar) {
        NOT_IMPLEMENTED();
    }

    template <typename CharType>
    TMutString<CharType>& TMutString<CharType>::replaceAllTo(CharType oldChar, CharType newChar) {
        NOT_IMPLEMENTED();
    }

    template <typename CharType>
    TMutString<CharType>& TMutString<CharType>::replaceAllTo(const TString<CharType>& oldSubstring, const TString<CharType>& newSubstring) {
        NOT_IMPLEMENTED();
    }

    template <typename CharType>
    TMutString<CharType>& TMutString<CharType>::replaceAllTo(CharType oldChar, const TString<CharType>& newSubstring) {
        NOT_IMPLEMENTED();
    }

    template <typename CharType>
    TMutString<CharType>& TMutString<CharType>::replaceAllTo(const TString<CharType>& oldSubstring, CharType newChar) {
        NOT_IMPLEMENTED();
    }

    template <typename CharType>
    TMutString<CharType>& TMutString<CharType>::fill(CharType ch) {
        arrayFill(this->value, ch, this->length, sizeof(char));

        return *this;
    }

    template <typename CharType>
    TMutString<CharType>& TMutString<CharType>::toUppercase() {
        for (sizetype index = 0; index < this->length; ++index) {
            if (this->value[index] >= ST_CHAR(CharType, 'a') && this->value[index] <= ST_CHAR(CharType, 'z')) {
                this->value[index] -= ST_CHAR(CharType, 'a') += ST_CHAR(CharType, 'A');
            }
        }
        return *this;
    }

    template <typename CharType>
    TMutString<CharType>& TMutString<CharType>::toLowercase() {
        for (sizetype index = 0; index < this->length; ++index) {
            if (this->value[index] >= ST_CHAR(CharType, 'A') && this->value[index] <= ST_CHAR(CharType, 'Z')) {
                (this->value[index] -= ST_CHAR(CharType, 'A')) += ST_CHAR(CharType, 'a');
            }
        }
        return *this;
    }

    template <typename CharType>
    TMutString<CharType>& TMutString<CharType>::operator=(const TMutString& other) {
        if (this == &other) return *this;

        delete[] this->value;

        this->value = TString<CharType>::copy(other.value, other.length);
        this->length = other.length;

        return *this;
    }

    template <typename CharType>
    TMutString<CharType>& TMutString<CharType>::operator=(TMutString&& other) noexcept {
        if (this == &other) return *this;

        delete[] this->value;

        this->value = other.value;
        this->length = other.length;

        other.value = nullptr;
        other.length = INVALID_SIZE;
        other.isDynamic = false;

        return *this;
    }

    template <typename CharType>
    TMutString<CharType>& TMutString<CharType>::operator+=(const TString<CharType>& string) {
        return append(string);
    }

    template <typename CharType>
    TMutString<CharType>& TMutString<CharType>::operator+=(CharType ch) {
        return append(ch);
    }

    template class TMutString<char>;
    template class TMutString<wchar>;
    template class TMutString<u8char>;
    template class TMutString<u16char>;
    template class TMutString<u32char>;
}
