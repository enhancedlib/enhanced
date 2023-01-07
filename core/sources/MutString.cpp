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
#include <enhanced/math/Math.h>
#include <enhanced/exceptions/NotImplementedError.h>

using enhanced::util::move;
using enhanced::util::removeConst;
using enhanced::util::removePtrConst;
using enhanced::math::difference;

namespace enhanced {
    template <typename CharType>
    requires util::isCharType<CharType>
    TMutString<CharType>::TMutString(const CharType* value, sizetype length) :
        TString<CharType>(TStringUtil<CharType>::copy(value, length), length, true) {}

    template <typename CharType>
    requires util::isCharType<CharType>
    TMutString<CharType>::TMutString() : TString<CharType>(TStringUtil<CharType>::make(0), 0, true) {}

    template <typename CharType>
    requires util::isCharType<CharType>
    TMutString<CharType>::TMutString(const CharType*& value) : TMutString<CharType>(removePtrConst(value)) {}

    template <typename CharType>
    requires util::isCharType<CharType>
    TMutString<CharType>::TMutString(CharType* const& value) : TMutString<CharType>(removeConst(value)) {}

    template <typename CharType>
    requires util::isCharType<CharType>
    TMutString<CharType>::TMutString(CharType*& value) : TMutString<CharType>(value, TStringUtil<CharType>::calcLength(value)) {}

    template <typename CharType>
    requires util::isCharType<CharType>
    TMutString<CharType>::TMutString(sizetype length) : TString<CharType>(TStringUtil<CharType>::make(length), length, true) {}

    template <typename CharType>
    requires util::isCharType<CharType>
    TMutString<CharType>::TMutString(const TMutString& other) :
        TString<CharType>(TStringUtil<CharType>::copy(other.value, other.length), other.length, true) {}

    template <typename CharType>
    requires util::isCharType<CharType>
    TMutString<CharType>::TMutString(TMutString&& other) noexcept : TString<CharType>(move(other)) {}

    template <typename CharType>
    requires util::isCharType<CharType>
    $NoIgnoreReturn
    CharType* TMutString<CharType>::chars() const noexcept {
        return this->value;
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    $NoIgnoreReturn
    CharType& TMutString<CharType>::at(sizetype index) const noexcept {
        return this->value[index];
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    $NoIgnoreReturn
    CharType& TMutString<CharType>::operator[](sizetype index) const noexcept {
        return this->value[index];
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    TMutString<CharType>& TMutString<CharType>::append(const TString<CharType>& string) {
        if (string.length == 0) return *this;

        sizetype newLength = this->length + string.length;
        auto newString = TStringUtil<CharType>::make(newLength);

        arrayCopy(newString, this->value, this->length);
        arrayCopy(newString + this->length, string.value, string.length);

        delete[] this->value;

        this->value = newString;
        this->length = newLength;

        return *this;
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    TMutString<CharType>& TMutString<CharType>::append(CharType ch) {
        sizetype newLength = this->length + 1;
        auto newString = TStringUtil<CharType>::make(newLength);

        arrayCopy(newString, this->value, this->length);
        newString[this->length] = ch;

        delete[] this->value;

        this->value = newString;
        this->length = newLength;

        return *this;
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    TMutString<CharType>& TMutString<CharType>::insertFirst(const TString<CharType>& string) {
        if (string.length == 0) return *this;

        sizetype newLength = this->length + string.length;
        auto newString = TStringUtil<CharType>::make(newLength);

        arrayCopy(newString, string.value, string.length);
        arrayCopy(newString + string.length, this->value, this->length);

        delete[] this->value;

        this->value = newString;
        this->length = newLength;

        return *this;
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    TMutString<CharType>& TMutString<CharType>::insertFirst(CharType ch) {
        sizetype newLength = this->length + 1;
        auto newString = TStringUtil<CharType>::make(newLength);

        newString[0] = ch;
        arrayCopy(newString + 1, this->value, this->length);

        delete[] this->value;

        this->value = newString;
        this->length = newLength;

        return *this;
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    TMutString<CharType>& TMutString<CharType>::replaceTo(sizetype start, sizetype end, CharType newChar) {
        sizetype newLength = this->length - (end - start) + 1;
        auto newString = TStringUtil<CharType>::make(newLength);

        arrayCopy(newString, this->value, start);
        newString[start] = newChar;
        arrayCopy(newString + start + 1, this->value + end, this->length - end);

        delete[] this->value;

        this->value = newString;
        this->length = newLength;

        return *this;
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    TMutString<CharType>& TMutString<CharType>::replaceTo(sizetype start, sizetype end, const TString<CharType>& newSubstring) {
        sizetype newLength = this->length - (end - start) + newSubstring.length;
        auto newString = TStringUtil<CharType>::make(newLength);

        arrayCopy(newString, this->value, start);
        arrayCopy(newString + start, newSubstring.value, newSubstring.length);
        arrayCopy(newString + start + newSubstring.length, this->value + end, this->length - end);

        delete[] this->value;

        this->value = newString;
        this->length = newLength;

        return *this;
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    TMutString<CharType>& TMutString<CharType>::replaceTo(const CharType oldChar, const CharType newChar) {
        sizetype index = this->indexOf(oldChar);
        if (index == INVALID_SIZE) return *this;
        this->value[index] = newChar;
        return *this;
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    TMutString<CharType>& TMutString<CharType>::replaceTo(const TString<CharType>& oldSubstring, const TString<CharType>& newSubstring) {
        sizetype index = this->indexOf(oldSubstring);
        if (index == INVALID_SIZE) return *this;
        return this->replaceTo(index, index + oldSubstring.length, newSubstring);
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    TMutString<CharType>& TMutString<CharType>::replaceTo(CharType oldChar, const TString<CharType>& newSubstring) {
        sizetype index = this->indexOf(oldChar);
        if (index == INVALID_SIZE) return *this;
        return this->replaceTo(index, index + 1, newSubstring);
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    TMutString<CharType>& TMutString<CharType>::replaceTo(const TString<CharType>& oldSubstring, CharType newChar) {
        sizetype index = this->indexOf(oldSubstring);
        if (index == INVALID_SIZE) return *this;
        return this->replaceTo(index, index + oldSubstring.length, newChar);
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    TMutString<CharType>& TMutString<CharType>::replaceAllTo(CharType oldChar, CharType newChar) {
        auto result = this->indexOfAll(oldChar);
        for (auto index : result) {
            this->value[index] = newChar;
        }
        return *this;
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    TMutString<CharType>& TMutString<CharType>::replaceAllTo(const TString<CharType>& oldSubstring, const TString<CharType>& newSubstring) {
        auto result = this->indexOfAll(oldSubstring);
        if (result.isEmpty()) return *this;

        sizetype diff = difference(newSubstring.length, oldSubstring.length) * result.getSize();
        sizetype newLength = (newSubstring.length > oldSubstring.length) ? this->length + diff : this->length - diff;

        auto newString = TStringUtil<CharType>::make(newLength);

        arrayCopy(newString, this->value, result[0]);

        sizetype offset = result[0];
        auto iterator = result.iterator();
        while (iterator.hasNext()) {
            iterator.next();
            arrayCopy(newString + offset, newSubstring.value, newSubstring.length);
            offset += newSubstring.length;

            sizetype begin = iterator.get() + oldSubstring.length;
            if (iterator.hasNext()) {
                arrayCopy(newString + offset, this->value + begin, iterator.next().get() - begin);
                offset += iterator.get() - begin;
                iterator.prev();
            } else {
                arrayCopy(newString + offset, this->value + begin, this->length - begin);
            }
        }

        delete[] this->value;

        this->value = newString;
        this->length = newLength;

        return *this;
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    TMutString<CharType>& TMutString<CharType>::replaceAllTo(CharType oldChar, const TString<CharType>& newSubstring) {
        auto result = this->indexOfAll(oldChar);
        if (result.isEmpty()) return *this;

        sizetype diff = difference(newSubstring.length, 1u) * result.getSize();
        sizetype newLength = (newSubstring.length > 1) ? this->length + diff : this->length - diff;

        auto newString = TStringUtil<CharType>::make(newLength);

        arrayCopy(newString, this->value, result[0]);

        sizetype offset = result[0];
        auto iterator = result.iterator();
        while (iterator.hasNext()) {
            iterator.next();
            arrayCopy(newString + offset, newSubstring.value, newSubstring.length);
            offset += newSubstring.length;

            sizetype begin = iterator.get() + 1;
            if (iterator.hasNext()) {
                arrayCopy(newString + offset, this->value + begin, iterator.next().get() - begin);
                offset += iterator.get() - begin;
                iterator.prev();
            } else {
                arrayCopy(newString + offset, this->value + begin, this->length - begin);
            }
        }

        delete[] this->value;

        this->value = newString;
        this->length = newLength;

        return *this;
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    TMutString<CharType>& TMutString<CharType>::replaceAllTo(const TString<CharType>& oldSubstring, CharType newChar) {
        auto result = this->indexOfAll(oldSubstring);
        if (result.isEmpty()) return *this;

        sizetype diff = difference(1u, oldSubstring.length) * result.getSize();
        sizetype newLength = (1 > oldSubstring.length) ? this->length + diff : this->length - diff;

        auto newString = TStringUtil<CharType>::make(newLength);

        arrayCopy(newString, this->value, result[0]);

        sizetype offset = result[0];
        auto iterator = result.iterator();
        while (iterator.hasNext()) {
            iterator.next();
            newString[offset] = newChar;
            offset += 1;

            sizetype begin = iterator.get() + oldSubstring.length;
            if (iterator.hasNext()) {
                arrayCopy(newString + offset, this->value + begin, iterator.next().get() - begin);
                offset += iterator.get() - begin;
                iterator.prev();
            } else {
                arrayCopy(newString + offset, this->value + begin, this->length - begin);
            }
        }

        delete[] this->value;

        this->value = newString;
        this->length = newLength;

        return *this;
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    TMutString<CharType>& TMutString<CharType>::fill(CharType ch) {
        arrayFill(this->value, ch, this->length);

        return *this;
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    TMutString<CharType>& TMutString<CharType>::toUppercase() {
        for (sizetype index = 0; index < this->length; ++index) {
            this->value[index] = uppercase(this->value[index]);
        }
        return *this;
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    TMutString<CharType>& TMutString<CharType>::toLowercase() {
        for (sizetype index = 0; index < this->length; ++index) {
            this->value[index] = lowercase(this->value[index]);
        }
        return *this;
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    $ReturnSelf
    TMutString<CharType>& TMutString<CharType>::operator=(const TMutString& other) {
        TString<CharType>::operator=(other);
        return *this;
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    $ReturnSelf
    TMutString<CharType>& TMutString<CharType>::operator=(TMutString&& other) noexcept {
        TString<CharType>::operator=(move(other));
        return *this;
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    TMutString<CharType>& TMutString<CharType>::operator+=(const TString<CharType>& string) {
        return append(string);
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    TMutString<CharType>& TMutString<CharType>::operator+=(CharType ch) {
        return append(ch);
    }

    template class TMutString<char>;
    template class TMutString<wchar>;
    template class TMutString<u8char>;
    template class TMutString<u16char>;
    template class TMutString<u32char>;
}
