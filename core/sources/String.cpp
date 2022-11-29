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

using enhanced::util::removeConst;
using enhanced::util::removePtrConst;
using enhanced::collections::ArrayList;
using enhanced::exceptions::NullPointerException;

namespace enhanced {
    template <typename CharType>
    $RetRequiresRelease
    func TString<CharType>::make(sizetype length) -> CharType* {
        let str = new CharType[length + 1];
        str[length] = TCHAR(CharType, '\0');
        return str;
    }

    template <typename CharType>
    $RetRequiresRelease
    func TString<CharType>::copy(const CharType* source) -> CharType* {
        return copy(source, calcLength(source));
    }

    template <typename CharType>
    $RetRequiresRelease
    func TString<CharType>::copy(const CharType* source, sizetype length) -> CharType* {
        if (source == null) throw NullPointerException("The given argument 'source' is null");

        let copy = make(length);
        arrayCopy(copy, source, length, sizeof(CharType));

        return copy;
    }

    template <typename CharType>
    $RetRequiresRelease
    func TString<CharType>::copy(const CharType* source, sizetype oldLength, sizetype newLength) -> CharType* {
        if (source == null) throw NullPointerException("The given argument 'source' is null");

        let copy = make(newLength);
        arrayCopy(copy, source, ((newLength > oldLength) ? oldLength : newLength), sizeof(CharType));

        return copy;
    }

    template <typename CharType>
    $NoIgnoreReturn
    func TString<CharType>::calcLength(const CharType* string) noexcept -> sizetype {
        if (string == null) return INVALID_SIZE;

        sizetype length;
        for (length = 0; string[length] != TCHAR(CharType, '\0'); ++length) {}

        return length;
    }

    template <typename CharType>
    $NoIgnoreReturn
    func TString<CharType>::isEqual(const CharType* string1, const CharType* string2) noexcept -> bool {
        if (string1 == string2) return true;
        else if (string1 == null || string2 == null) return false;

        for (sizetype index = 0;; ++index) {
            if ((string1[index] == TCHAR(CharType, '\0')) ^ (string2[index] == TCHAR(CharType, '\0'))) {
                return false;
            }

            if (string1[index] != string2[index]) return false;
        }
        return true;
    }

    template <typename CharType>
    $NoIgnoreReturn
    func TString<CharType>::isEqual(const CharType* string1, const CharType* string2, sizetype length1, sizetype length2) noexcept -> bool {
        if (length1 != length2) return false;
        if (string1 == string2) return true;
        else if (string1 == null || string2 == null) return false;


        for (sizetype index = 0; index < length1; ++index) {
            if (string1[index] != string2[index]) return false;
        }
        return true;
    }

    template <typename CharType>
    func TString<CharType>::join(InitializerList<TString> list) -> TMutString<CharType> {
        return join(initListToArray(list), initListSize(list));
    }

    template <typename CharType>
    func TString<CharType>::join(const TString* strings, sizetype count) -> TMutString<CharType> {
        sizetype length = 0;
        for (sizetype index = 0; index < count; ++index) {
            length += strings[index].length;
        }

        let newString = TMutString<CharType>(length);

        sizetype offset = 0;
        for (sizetype index = 0; index < count; ++index) {
            arrayCopy(newString.value + offset, strings[index].value, strings[index].length, sizeof(CharType));
            offset += strings[index].length;
        }

        return newString;
    }

    template <typename CharType>
    TString<CharType>::TString() noexcept : CharSequence<CharType>(TSTRING(CharType, ""), 0) {}

    template <typename CharType>
    TString<CharType>::TString(const CharType* value, sizetype length) noexcept : CharSequence<CharType>(value, length) {}

    template <typename CharType>
    TString<CharType>::TString(const CharType*& value) : TString(removePtrConst(value)) {}

    template <typename CharType>
    TString<CharType>::TString(CharType*& value) : TString<CharType>(value, calcLength(value)) {}

    template <typename CharType>
    TString<CharType>::TString(CharType* const& value) : TString(removeConst(value)) {}

    template <typename CharType>
    TString<CharType>::TString(const TString& other) noexcept = default;

    template <typename CharType>
    TString<CharType>::TString(TString&& other) noexcept = default;

    template <typename CharType>
    $NoIgnoreReturn
    func TString<CharType>::indexOf(const CharType ch) const noexcept -> sizetype {
        for (sizetype index = 0; index < this->length; ++index) {
            if (this->value[index] == ch) return index;
        }

        return INVALID_SIZE;
    }

    template <typename CharType>
    $NoIgnoreReturn
    func TString<CharType>::indexOf(const TString& string) const noexcept -> sizetype {
        sizetype substringIndex = 0;

        for (sizetype index = 0; index < this->length; ++index) {
            if (this->value[index] == string[substringIndex]) ++substringIndex;
            else substringIndex = 0;

            if (substringIndex == string.length) return index - string.length + 1;
        }

        return INVALID_SIZE;
    }

    template <typename CharType>
    $NoIgnoreReturn
    func TString<CharType>::indexOf(CharType ch, sizetype getN) const noexcept -> sizetype {
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
    $NoIgnoreReturn
    func TString<CharType>::indexOf(const TString& string, sizetype getN) const noexcept -> sizetype {
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
    $NoIgnoreReturn
    func TString<CharType>::indexOfLast(CharType ch) const noexcept -> sizetype {
        for (sizetype index = this->length - 1;; --index) {
            if (this->value[index] == ch) return index;
            if (index == 0) break;
        }

        return INVALID_SIZE;
    }

    template <typename CharType>
    $NoIgnoreReturn
    func TString<CharType>::indexOfLast(const TString& string) const noexcept -> sizetype {
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
    $NoIgnoreReturn
    func TString<CharType>::indexOfLast(CharType ch, sizetype getN) const noexcept -> sizetype {
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
    $NoIgnoreReturn
    func TString<CharType>::indexOfLast(const TString& string, sizetype getN) const noexcept -> sizetype {
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
    $RetRequiresRelease
    func TString<CharType>::indexOfAll(const CharType ch) const noexcept -> ArrayList<sizetype> {
        ArrayList<sizetype> allIndexes;

        for (sizetype index = 0; index < this->length; ++index) {
            if (this->value[index] == ch) allIndexes.add(index);
        }

        return allIndexes;
    }

    template <typename CharType>
    $RetRequiresRelease
    func TString<CharType>::indexOfAll(const TString& string) const noexcept -> ArrayList<sizetype> {
        ArrayList<sizetype> allIndexes;
        sizetype substringIndex = 0;

        for (sizetype index = 0; index < this->length; ++index) {
            if (this->value[index] == string[substringIndex]) ++substringIndex;
            else substringIndex = 0;

            if (substringIndex == string.length) {
                allIndexes.add(index - string.length + 1);
            }
        }

        return allIndexes;
    }

    template <typename CharType>
    $NoIgnoreReturn
    func TString<CharType>::replace(sizetype start, sizetype end, CharType newChar) const -> TMutString<CharType> {
        return TMutString<CharType>(this->value).replaceTo(start, end, newChar);
    }

    template <typename CharType>
    $NoIgnoreReturn
    func TString<CharType>::replace(sizetype start, sizetype end, const TString& newSubstring) const -> TMutString<CharType> {
        return TMutString<CharType>(this->value).replaceTo(start, end, newSubstring);
    }

    template <typename CharType>
    $NoIgnoreReturn
    func TString<CharType>::replace(CharType oldChar, CharType newChar) const -> TMutString<CharType> {
        return TMutString<CharType>(this->value).replaceTo(oldChar, newChar);
    }

    template <typename CharType>
    $NoIgnoreReturn
    func TString<CharType>::replace(const TString& oldSubstring, const TString& newSubstring) const -> TMutString<CharType> {
        return TMutString<CharType>(this->value).replaceTo(oldSubstring, newSubstring);
    }

    template <typename CharType>
    $NoIgnoreReturn
    func TString<CharType>::replace(CharType oldChar, const TString& newSubstring) const -> TMutString<CharType> {
        return TMutString<CharType>(this->value).replaceTo(oldChar, newSubstring);
    }

    template <typename CharType>
    $NoIgnoreReturn
    func TString<CharType>::replace(const TString& oldSubstring, CharType newChar) const -> TMutString<CharType> {
        return TMutString<CharType>(this->value).replaceTo(oldSubstring, newChar);
    }

    template <typename CharType>
    $NoIgnoreReturn
    func TString<CharType>::replaceAll(CharType oldChar, CharType newChar) const -> TMutString<CharType> {
        return TMutString<CharType>(this->value).replaceAllTo(oldChar, newChar);
    }

    template <typename CharType>
    $NoIgnoreReturn
    func TString<CharType>::replaceAll(const TString& oldSubstring, const TString& newSubstring) const -> TMutString<CharType> {
        return TMutString<CharType>(this->value).replaceAllTo(oldSubstring, newSubstring);
    }

    template <typename CharType>
    $NoIgnoreReturn
    func TString<CharType>::replaceAll(CharType oldChar, const TString& newSubstring) const -> TMutString<CharType> {
        return TMutString<CharType>(this->value).replaceAllTo(oldChar, newSubstring);
    }

    template <typename CharType>
    $NoIgnoreReturn
    func TString<CharType>::replaceAll(const TString& oldSubstring, CharType newChar) const -> TMutString<CharType> {
        return TMutString<CharType>(this->value).replaceAllTo(oldSubstring, newChar);
    }

    template <typename CharType>
    $NoIgnoreReturn
    func TString<CharType>::uppercase() const -> TMutString<CharType> {
        return TMutString<CharType>(this->value).toUppercase();
    }

    template <typename CharType>
    $NoIgnoreReturn
    func TString<CharType>::lowercase() const -> TMutString<CharType> {
        return TMutString<CharType>(this->value).toLowercase();
    }

    template <typename CharType>
    $NoIgnoreReturn
    func TString<CharType>::operator==(const TString& string) const noexcept -> bool {
        return isEqual(this->value, string.value, this->length, string.length);
    }

    template <typename CharType>
    $NoIgnoreReturn
    func TString<CharType>::operator+(const TString& string) const -> TMutString<CharType> {
        sizetype newLength = this->length + string.length;
        TMutString<CharType> newString(newLength);

        arrayCopy(newString.value, this->value, this->length, sizeof(CharType));
        arrayCopy(newString.value + this->length, string.value, string.length, sizeof(CharType));

        return newString;
    }

    template <typename CharType>
    func TString<CharType>::operator=(const TString& other) noexcept -> TString<CharType>& = default;

    template <typename CharType>
    func TString<CharType>::operator=(TString&& other) noexcept -> TString<CharType>& = default;

    template class TString<char>;
    template class TString<wchar>;
    template class TString<u8char>;
    template class TString<u16char>;
    template class TString<u32char>;
}
