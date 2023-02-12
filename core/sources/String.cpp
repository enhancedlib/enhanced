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

#include <enhanced/String.h>

#include <enhanced/Defines.h>
#include <enhanced/Types.h>
#include <enhanced/Annotations.h>
#include <enhanced/Memory.h>
#include <enhanced/Array.h>
#include <enhanced/Character.h>
#include <enhanced/CharSequence.h>
#include <enhanced/MutString.h>
#include <enhanced/InitializerList.h>
#include <enhanced/util/Traits.h>
#include <enhanced/collections/ArrayList.h>
#include <enhanced/exceptions/NullPointerException.h>

using enhanced::util::move;
using enhanced::util::removeConst;
using enhanced::util::removePtrConst;
using enhanced::collections::ArrayList;
using enhanced::exceptions::NullPointerException;

namespace enhanced {
    template <typename CharType>
    requires util::isCharType<CharType>
    [[RetNotIgnored]]
    TString<CharType> TString<CharType>::from(bool value) {
        return value ? TString(E_SWITCH_STR(CharType, "true")) : E_SWITCH_STR(CharType, "false");
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    [[RetNotIgnored]]
    TMutString<CharType> TString<CharType>::from(CharType value) {
        TMutString<CharType> string {1};
        string[0] = value;
        return string;
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    [[RetNotIgnored]]
    TMutString<CharType> TString<CharType>::from(qword value, bool isNegative) {
        // TODO: Faster implementation
        if (isNegative) value = -((int64) value);
        CharType bits[21];
        sizetype index = 20;
        for (; value != 0; --index) {
            bits[index] = value % 10 + '0';
            value /= 10;
        }
        if (isNegative) bits[index--] = '-';
        return {bits + index + 1, 20 - index};
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    [[RetNotIgnored]]
    TMutString<CharType> TString<CharType>::join(InitializerList<TString> list) {
        return join(list.toArray(), list.getSize());
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    [[RetNotIgnored]]
    TMutString<CharType> TString<CharType>::join(const TString* strings, sizetype count) {
        sizetype length = 0;
        for (sizetype index = 0; index < count; ++index) {
            length += strings[index].length;
        }

        auto newString = TMutString<CharType>(length);

        sizetype offset = 0;
        for (sizetype index = 0; index < count; ++index) {
            arrayCopy(newString.value + offset, strings[index].value, strings[index].length);
            offset += strings[index].length;
        }

        return newString;
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    TString<CharType>::TString(const CharType* value, sizetype length, bool isMutable) noexcept : CharSequence<CharType>(value, length, isMutable) {}

    template <typename CharType>
    requires util::isCharType<CharType>
    TString<CharType>::TString() noexcept : CharSequence<CharType>(E_SWITCH_STR(CharType, ""), 0) {}

    template <typename CharType>
    requires util::isCharType<CharType>
    TString<CharType>::TString(const CharType* value, sizetype length) noexcept : CharSequence<CharType>(value, length) {}

    template <typename CharType>
    requires util::isCharType<CharType>
    TString<CharType>::TString(const CharType*& value) : TString(removePtrConst(value)) {}

    template <typename CharType>
    requires util::isCharType<CharType>
    TString<CharType>::TString(CharType*& value) : TString<CharType>(value, TStringUtil<CharType>::calcLength(value)) {}

    template <typename CharType>
    requires util::isCharType<CharType>
    TString<CharType>::TString(CharType* const& value) : TString(removeConst(value)) {}

    template <typename CharType>
    requires util::isCharType<CharType>
    TString<CharType>::TString(const TString& other) = default;

    template <typename CharType>
    requires util::isCharType<CharType>
    TString<CharType>::TString(TString&& other) noexcept = default;

    template <typename CharType>
    requires util::isCharType<CharType>
    [[RetNotIgnored]]
    sizetype TString<CharType>::indexOf(const CharType ch) const noexcept {
        for (sizetype index = 0; index < this->length; ++index) {
            if (this->value[index] == ch) return index;
        }

        return INVALID_SIZE;
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    [[RetNotIgnored]]
    sizetype TString<CharType>::indexOf(const TString& string) const noexcept {
        sizetype substringIndex = 0;

        for (sizetype index = 0; index < this->length; ++index) {
            if (this->value[index] == string[substringIndex]) ++substringIndex;
            else substringIndex = 0;

            if (substringIndex == string.length) return index - string.length + 1;
        }

        return INVALID_SIZE;
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    [[RetNotIgnored]]
    sizetype TString<CharType>::indexOf(CharType ch, sizetype getN) const noexcept {
        sizetype indexN = 0;

        for (sizetype index = 0; index < this->length; ++index) {
            if (this->value[index] == ch) {
                if (getN == indexN) return index;
                else ++indexN;
            }
        }

        return INVALID_SIZE;
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    [[RetNotIgnored]]
    sizetype TString<CharType>::indexOf(const TString& string, sizetype getN) const noexcept {
        sizetype indexN = 0;
        sizetype substringIndex = 0;

        for (sizetype index = 0; index < this->length; ++index) {
            if (this->value[index] == string[substringIndex]) ++substringIndex;
            else substringIndex = 0;

            if (substringIndex == string.length) {
                if (getN == indexN) return index - string.length + 1;
                else ++indexN;
            }
        }

        return INVALID_SIZE;
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    [[RetNotIgnored]]
    sizetype TString<CharType>::indexOfLast(CharType ch) const noexcept {
        for (sizetype index = this->length - 1;; --index) {
            if (this->value[index] == ch) return index;
            if (index == 0) break;
        }

        return INVALID_SIZE;
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    [[RetNotIgnored]]
    sizetype TString<CharType>::indexOfLast(const TString& string) const noexcept {
        sizetype substringIndex = string.length - 1;

        for (sizetype index = this->length - 1;; --index) {
            if (this->value[index] == string[substringIndex]) {
                --substringIndex;
            } else {
                substringIndex = string.length - 1;
            }

            if (substringIndex == string.length) return index;
            if (index == 0) break;
        }

        return INVALID_SIZE;
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    [[RetNotIgnored]]
    sizetype TString<CharType>::indexOfLast(CharType ch, sizetype getN) const noexcept {
        sizetype indexN = 0;

        for (sizetype index = this->length - 1;; --index) {
            if (this->value[index] == ch) {
                if (getN == indexN) return index;
                else ++indexN;
            }

            if (index == 0) break;
        }

        return INVALID_SIZE;
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    [[RetNotIgnored]]
    sizetype TString<CharType>::indexOfLast(const TString& string, sizetype getN) const noexcept {
        sizetype indexN = 0;
        sizetype substringIndex = string.length - 1;

        for (sizetype index = this->length - 1;; --index) {
            if (this->value[index] == string[substringIndex]) --substringIndex;
            else substringIndex = string.length - 1;

            if (substringIndex == string.length) {
                if (getN == indexN) return index;
                else ++indexN;
            }

            if (index == 0) break;
        }

        return INVALID_SIZE;
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    [[RetRequiresRelease]]
    ArrayList<sizetype> TString<CharType>::indexOfAll(const CharType ch) const noexcept {
        ArrayList<sizetype> allIndexes;

        for (sizetype index = 0; index < this->length; ++index) {
            if (this->value[index] == ch) allIndexes.add(index);
        }

        return allIndexes;
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    [[RetRequiresRelease]]
    ArrayList<sizetype> TString<CharType>::indexOfAll(const TString& string) const noexcept {
        ArrayList<sizetype> allIndexes;
        sizetype substringIndex = 0;

        for (sizetype index = 0; index < this->length; ++index) {
            if (this->value[index] == string[substringIndex]) ++substringIndex;
            else substringIndex = 0;

            if (substringIndex == string.length) {
                allIndexes.add(index - string.length + 1);
                substringIndex = 0;
            }
        }

        return allIndexes;
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    [[RetNotIgnored]]
    TMutString<CharType> TString<CharType>::toMutable() const {
        return {this->value, this->length};
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    [[RetNotIgnored]]
    TMutString<CharType> TString<CharType>::replace(sizetype start, sizetype end, CharType newChar) const {
        return TMutString<CharType>(this->value).replaceTo(start, end, newChar);
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    [[RetNotIgnored]]
    TMutString<CharType> TString<CharType>::replace(sizetype start, sizetype end, const TString& newSubstring) const {
        return TMutString<CharType>(this->value).replaceTo(start, end, newSubstring);
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    [[RetNotIgnored]]
    TMutString<CharType> TString<CharType>::replace(CharType oldChar, CharType newChar) const {
        return TMutString<CharType>(this->value).replaceTo(oldChar, newChar);
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    [[RetNotIgnored]]
    TMutString<CharType> TString<CharType>::replace(const TString& oldSubstring, const TString& newSubstring) const {
        return TMutString<CharType>(this->value).replaceTo(oldSubstring, newSubstring);
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    [[RetNotIgnored]]
    TMutString<CharType> TString<CharType>::replace(CharType oldChar, const TString& newSubstring) const {
        return TMutString<CharType>(this->value).replaceTo(oldChar, newSubstring);
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    [[RetNotIgnored]]
    TMutString<CharType> TString<CharType>::replace(const TString& oldSubstring, CharType newChar) const {
        return TMutString<CharType>(this->value).replaceTo(oldSubstring, newChar);
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    [[RetNotIgnored]]
    TMutString<CharType> TString<CharType>::replaceAll(CharType oldChar, CharType newChar) const {
        return TMutString<CharType>(this->value).replaceAllTo(oldChar, newChar);
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    [[RetNotIgnored]]
    TMutString<CharType> TString<CharType>::replaceAll(const TString& oldSubstring, const TString& newSubstring) const {
        return TMutString<CharType>(this->value).replaceAllTo(oldSubstring, newSubstring);
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    [[RetNotIgnored]]
    TMutString<CharType> TString<CharType>::replaceAll(CharType oldChar, const TString& newSubstring) const {
        return TMutString<CharType>(this->value).replaceAllTo(oldChar, newSubstring);
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    [[RetNotIgnored]]
    TMutString<CharType> TString<CharType>::replaceAll(const TString& oldSubstring, CharType newChar) const {
        return TMutString<CharType>(this->value).replaceAllTo(oldSubstring, newChar);
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    [[RetNotIgnored]]
    TMutString<CharType> TString<CharType>::uppercase() const {
        return TMutString<CharType>(this->value).toUppercase();
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    [[RetNotIgnored]]
    TMutString<CharType> TString<CharType>::lowercase() const {
        return TMutString<CharType>(this->value).toLowercase();
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    [[RetNotIgnored]]
    bool TString<CharType>::operator==(const TString& string) const noexcept {
        return TStringUtil<CharType>::isEqual(this->value, string.value, this->length, string.length);
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    [[RetNotIgnored]]
    bool TString<CharType>::operator!=(const TString& string) const noexcept {
        return !operator==(string);
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    [[RetNotIgnored]]
    TMutString<CharType> TString<CharType>::operator+(const TString& string) const {
        sizetype newLength = this->length + string.length;
        TMutString<CharType> newString(newLength);

        arrayCopy(newString.value, this->value, this->length);
        arrayCopy(newString.value + this->length, string.value, string.length);

        return newString;
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    [[RetNotIgnored]]
    TMutString<CharType> TString<CharType>::operator+(CharType ch) const {
        sizetype newLength = this->length + 1;
        TMutString<CharType> newString(newLength);

        arrayCopy(newString.value, this->value, this->length);
        newString[this->length] = ch;

        return newString;
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    [[ReturnSelf]]
    TString<CharType>& TString<CharType>::operator=(const TString& other) noexcept {
        CharSequence<CharType>::operator=(other);
        return *this;
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    [[ReturnSelf]]
    TString<CharType>& TString<CharType>::operator=(TString&& other) noexcept {
        CharSequence<CharType>::operator=(move(other));
        return *this;
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    [[RetRequiresRelease]]
    CharType* TStringUtil<CharType>::make(sizetype length) {
        auto str = new CharType[length + 1];
        str[length] = E_SWITCH_CHAR(CharType, '\0');
        return str;
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    [[RetRequiresRelease]]
    CharType* TStringUtil<CharType>::copy(const CharType* source) {
        return copy(source, calcLength(source));
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    [[RetRequiresRelease]]
    CharType* TStringUtil<CharType>::copy(const CharType* source, sizetype length) {
        if (source == nullptr) throw NullPointerException("The given argument 'source' is nullptr");

        auto copy = make(length);
        arrayCopy(copy, source, length);

        return copy;
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    [[RetRequiresRelease]]
    CharType* TStringUtil<CharType>::copy(const CharType* source, sizetype oldLength, sizetype newLength) {
        if (source == nullptr) throw NullPointerException("The given argument 'source' is nullptr");

        auto copy = make(newLength);
        arrayCopy(copy, source, ((newLength > oldLength) ? oldLength : newLength));

        return copy;
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    [[RetNotIgnored]]
    sizetype TStringUtil<CharType>::calcLength(const CharType* string) noexcept {
        if (string == nullptr) return INVALID_SIZE;

        sizetype length;
        for (length = 0; string[length] != E_SWITCH_CHAR(CharType, '\0'); ++length) {}

        return length;
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    [[RetNotIgnored]]
    bool TStringUtil<CharType>::isEqual(const CharType* string1, const CharType* string2) noexcept {
        if (string1 == string2) return true;
        else if (string1 == nullptr || string2 == nullptr) return false;

        for (sizetype index = 0;; ++index) {
            if ((string1[index] == E_SWITCH_CHAR(CharType, '\0')) ^ (string2[index] == E_SWITCH_CHAR(CharType, '\0'))) {
                return false;
            }

            if (string1[index] != string2[index]) return false;
        }
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    [[RetNotIgnored]]
    bool TStringUtil<CharType>::isEqual(const CharType* string1, const CharType* string2, sizetype length1, sizetype length2) noexcept {
        if (length1 != length2) return false;
        if (string1 == string2) return true;
        else if (string1 == nullptr || string2 == nullptr) return false;


        for (sizetype index = 0; index < length1; ++index) {
            if (string1[index] != string2[index]) return false;
        }
        return true;
    }

    template class TString<char>;
    template class TString<wchar>;
    template class TString<u8char>;
    template class TString<u16char>;
    template class TString<u32char>;

    template struct TStringUtil<char>;
    template struct TStringUtil<wchar>;
    template struct TStringUtil<u8char>;
    template struct TStringUtil<u16char>;
    template struct TStringUtil<u32char>;
}
